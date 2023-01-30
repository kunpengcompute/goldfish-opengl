/*
* Copyright (C) 2011 The Android Open Source Project
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#include "HostConnection.h"

#include "GLEncoder.h"
#include "GL2Encoder.h"
#include "QemuPipeStream.h"
#include "ThreadInfo.h"
#include <cutils/log.h>
#include "../../shared/gralloc_cb/include/gralloc_cb_bp.h"
#include "../../system/vulkan_enc/VkEncoder.h"
#include "../../system/vulkan_enc/SipcStream.h"
#include "AddressSpaceStream.h"

#include "gralloc_cb.h"
using goldfish_vk::VkEncoder;

#define STREAM_BUFFER_SIZE  (4*1024*1024)
#define STREAM_PORT_NUM     22468

/* Set to 1 to use a QEMU pipe, or 0 for a TCP connection */
#define  USE_QEMU_PIPE  1

GetStreamFunc HostConnection::getStream = nullptr;
ReleaseStreamFunc HostConnection::releaseStream = nullptr;
WaitRebuildStateMachineFunc HostConnection::waitRebuildStateMachine = nullptr;
GetOpSizeFunc HostConnection::getOpSize = nullptr;
bool HostConnection::m_streamLoaded = false;
std::mutex HostConnection::m_loaderLock {};
std::unique_ptr<LoadSharedLib> HostConnection::m_loader = nullptr;

class GoldfishGralloc : public Gralloc
{
public:
    virtual uint32_t createColorBuffer(
        ExtendedRCEncoderContext* rcEnc,
        int width, int height, uint32_t glformat) {

        GLenum type = GL_UNSIGNED_BYTE;
        int32_t format = HAL_PIXEL_FORMAT_RGBA_8888;
        switch (glformat) {
            case GL_RGB:
            case GL_RGB565_OES: {
                format = HAL_PIXEL_FORMAT_RGBA_8888;
                break;
            }

            case GL_RGBA:
            case GL_RGB5_A1_OES:
            case GL_RGBA4_OES: {
                format = HAL_PIXEL_FORMAT_RGBA_8888;
                break;
            }

            default: {
                format = HAL_PIXEL_FORMAT_RGBA_8888;
            }
        }

        return rcEnc->rcCreateColorBuffer(
            rcEnc->GetRenderControlEncoder(rcEnc), width, height, glformat, type, format);
    }

    virtual uint32_t getHostHandle(native_handle_t const* handle)
    {
        // Current Gralloc module alloc cb_handle_t buffer, not cb_handle_t_v11.
        // Should used cb_handle_t_v11::from(handle) to convert with struct cb_handle_t_v11
        const cb_handle_t* cb = static_cast<const cb_handle_t*>(handle);
        return cb->hostHandle;
    }

    virtual int getFormat(native_handle_t const* handle)
    {
        // Current Gralloc module alloc cb_handle_t buffer, not cb_handle_t_v11.
        // Should used cb_handle_t_v11::from(handle) to convert with struct cb_handle_t_v11
        const cb_handle_t* cb = static_cast<const cb_handle_t*>(handle);
        return cb->format;
    }

    virtual size_t getAllocatedSize(native_handle_t const* handle)
    {
        // Current Gralloc module alloc cb_handle_t buffer, not cb_handle_t_v11.
        // Should used cb_handle_t_v11::from(handle) to convert with struct cb_handle_t_v11
        const cb_handle_t* cb = static_cast<const cb_handle_t*>(handle);
        return cb->ashmemSize;
    }
};
static GoldfishGralloc m_goldfishGralloc;

HostConnection::HostConnection() :
    m_streamHandle(0),
    m_glEnc(NULL),
    m_gl2Enc(NULL),
    m_vkEnc(NULL),
    m_rcEnc(NULL),
    m_checksumHelper(),
    m_glExtensions(),
    m_grallocOnly(true),
    m_noHostError(false),
    m_iostream(NULL),
    m_grallocHelper(&m_goldfishGralloc)
{
}

HostConnection::~HostConnection()
{
    delete m_glEnc;
    m_glEnc = nullptr;
    delete m_gl2Enc;
    m_gl2Enc = nullptr;
    delete m_rcEnc;
    m_rcEnc = nullptr;
    delete m_iostream;
    m_iostream = nullptr;
    // stream对象应该最后析构，因为m_gl2Enc、m_rcEnc等依赖stream对象，stream对象应该最晚析构
    releaseStream(m_streamHandle);
    m_streamHandle = 0;
}

HostConnection *HostConnection::get() {
    return getWithThreadInfo(getEGLThreadInfo());
}

HostConnection *HostConnection::getWithThreadInfo(EGLThreadInfo* tinfo) {

    /* TODO: Make this configurable with a system property */
    const int useQemuPipe = USE_QEMU_PIPE;

    // Get thread info
    if (!tinfo) {
        return NULL;
    }

    if (tinfo->hostConn == NULL) {
        HostConnection *con = new (std::nothrow) HostConnection();
        if (NULL == con) {
            return NULL;
        }

        if (!con->initStreamExport()) {
            return NULL;
        }
        con->m_streamHandle = con->getStream();
        if (con->m_streamHandle == 0) {
            ALOGE("Failed to create stream for host connection!!!");
            return NULL;
        }
        QemuPipeStream* qStream = new (std::nothrow) QemuPipeStream();
        if (qStream == NULL) {
            ERR("Failed to create QemuPipeStream for host connection!!!");
            return NULL;
        }
        con->m_iostream = qStream;
        ALOGD("HostConnection::get() New Host Connection established %p, tid %d\n", con, gettid());
        tinfo->hostConn = con;
    }

    return tinfo->hostConn;
}

void HostConnection::exit() {
    EGLThreadInfo *tinfo = getEGLThreadInfo();
    if (!tinfo) {
        return;
    }

    if (tinfo->hostConn) {
        delete tinfo->hostConn;
        tinfo->hostConn = NULL;
    }
}



GLEncoder *HostConnection::glEncoder()
{
    if (!m_glEnc) {
        m_glEnc = new (std::nothrow) GLEncoder(m_iostream, checksumHelper());
        ALOGD("HostConnection::glEncoder new encoder %p, tid %d", m_glEnc, gettid());
        m_glEnc->setContextAccessor(s_getGLContext);
    }
    return m_glEnc;
}

GL2Encoder *HostConnection::gl2Encoder()
{
    if (!m_gl2Enc) {
        m_gl2Enc = new (std::nothrow) GL2Encoder();
        if (!m_gl2Enc) {
            ALOGD("HostConnection::gl2Encoder new failed");
            return nullptr;
        }
        if (!m_gl2Enc->CreateVmiGLESv2Encoder(m_streamHandle)) {
            ALOGD("HostConnection::gl2Encoder init statemachine exports failed");
            return nullptr;
        }
        ALOGD("HostConnection::gl2Encoder new encoder %p, tid %d", m_gl2Enc, gettid());
        m_gl2Enc->setNoHostError(m_noHostError);
    }
    waitRebuildStateMachine(m_streamHandle);
    return m_gl2Enc;
}

VkEncoder *HostConnection::vkEncoder()
{
    if (!m_vkEnc) {
        // 8MB is enough for send buffer, Avoid subsequent buffer reallocations
        SipcStream* ioStream = new SipcStream(8 * 1024 * 1024);
        m_vkEnc = new VkEncoder(ioStream);
    }
    return m_vkEnc;
}

ExtendedRCEncoderContext *HostConnection::rcEncoder()
{
    if (!m_rcEnc) {
        m_rcEnc = new (std::nothrow) ExtendedRCEncoderContext();
        if (m_rcEnc == nullptr) {
            ALOGE("Failed to instantiate VmiRenderControlWrap");
            return nullptr;
        }
        if (!m_rcEnc->InitRenderControlExport()) {
            delete m_rcEnc;
            m_rcEnc = nullptr;
            return nullptr;
        }
        if (!m_rcEnc->CreateVmiRenderControlEncoder(m_streamHandle)) {
            ALOGE("HostConnection::rcEncoder CreateVmiRenderControlEncoder failed");
            delete m_rcEnc;
            m_rcEnc = nullptr;
            return nullptr;
        }
        ALOGD("HostConnection::rcEncoder new encoder %p, tid %d", m_rcEnc, gettid());
        queryAndSetSyncImpl(m_rcEnc);
        queryAndSetGLESMaxVersion(m_rcEnc);
        queryAndSetNoErrorState(m_rcEnc);
    }
    waitRebuildStateMachine(m_streamHandle);
    return m_rcEnc;
}

gl_client_context_t *HostConnection::s_getGLContext()
{
    EGLThreadInfo *ti = getEGLThreadInfo();
    if (ti->hostConn) {
        return ti->hostConn->m_glEnc;
    }
    return NULL;
}

gl2_client_context_t *HostConnection::s_getGL2Context()
{
    EGLThreadInfo *ti = getEGLThreadInfo();
    if (ti->hostConn) {
        return (gl2_client_context_t*)ti->hostConn->m_gl2Enc;
    }
    return NULL;
}

const std::string& HostConnection::queryGLExtensions(ExtendedRCEncoderContext *rcEnc) {
    if (!m_glExtensions.empty()) {
        return m_glExtensions;
    }

    // Extensions strings are usually quite long, preallocate enough here.
    std::string extensions_buffer(1023, '\0');

    // rcGetGLString() returns required size including the 0-terminator, so
    // account it when passing/using the sizes.
    int extensionSize = rcEnc->rcGetGLString(rcEnc->GetRenderControlEncoder(rcEnc),
                                             GL_EXTENSIONS,
                                             &extensions_buffer[0],
                                             extensions_buffer.size() + 1);
    if (extensionSize < 0) {
        extensions_buffer.resize(-extensionSize);
        extensionSize = rcEnc->rcGetGLString(rcEnc->GetRenderControlEncoder(rcEnc),
                                             GL_EXTENSIONS,
                                             &extensions_buffer[0],
                                            -extensionSize + 1);
    }

    if (extensionSize > 0) {
        extensions_buffer.resize(extensionSize - 1);
        m_glExtensions.swap(extensions_buffer);
    }

    return m_glExtensions;
}

void HostConnection::queryAndSetSyncImpl(ExtendedRCEncoderContext *rcEnc) {
    const std::string& glExtensions = queryGLExtensions(rcEnc);
#if PLATFORM_SDK_VERSION <= 16 || (!defined(__i386__) && !defined(__x86_64__))
    rcEnc->setSyncImpl(rcEnc->GetRenderControlEncoder(rcEnc), SYNC_IMPL_NONE);
#else
    if (glExtensions.find(kRCNativeSyncV3) != std::string::npos) {
        rcEnc->setSyncImpl(rcEnc->GetRenderControlEncoder(rcEnc), SYNC_IMPL_NATIVE_SYNC_V3);
    } else if (glExtensions.find(kRCNativeSyncV2) != std::string::npos) {
        rcEnc->setSyncImpl(rcEnc->GetRenderControlEncoder(rcEnc), SYNC_IMPL_NATIVE_SYNC_V2);
    } else {
        rcEnc->setSyncImpl(rcEnc->GetRenderControlEncoder(rcEnc), SYNC_IMPL_NONE);
    }
#endif
}

void HostConnection::queryAndSetGLESMaxVersion(ExtendedRCEncoderContext* rcEnc) {
    std::string glExtensions = queryGLExtensions(rcEnc);
    if (glExtensions.find(kGLESMaxVersion_2) != std::string::npos) {
        rcEnc->setGLESMaxVersion(rcEnc->GetRenderControlEncoder(rcEnc), GLES_MAX_VERSION_2);
    } else if (glExtensions.find(kGLESMaxVersion_3_0) != std::string::npos) {
        rcEnc->setGLESMaxVersion(rcEnc->GetRenderControlEncoder(rcEnc), GLES_MAX_VERSION_3_0);
    } else if (glExtensions.find(kGLESMaxVersion_3_1) != std::string::npos) {
        rcEnc->setGLESMaxVersion(rcEnc->GetRenderControlEncoder(rcEnc), GLES_MAX_VERSION_3_1);
    } else if (glExtensions.find(kGLESMaxVersion_3_2) != std::string::npos) {
        rcEnc->setGLESMaxVersion(rcEnc->GetRenderControlEncoder(rcEnc), GLES_MAX_VERSION_3_2);
    } else {
        ALOGW("Unrecognized GLES max version string in extensions: %s",
              glExtensions.c_str());
        rcEnc->setGLESMaxVersion(rcEnc->GetRenderControlEncoder(rcEnc), GLES_MAX_VERSION_2);
    }
}

void HostConnection::queryAndSetNoErrorState(ExtendedRCEncoderContext* rcEnc) {
    std::string glExtensions = queryGLExtensions(rcEnc);
    if (glExtensions.find(kGLESNoHostError) != std::string::npos) {
        m_noHostError = true;
    }
}

bool HostConnection::initStreamExport() {
    std::lock_guard<std::mutex> lock(m_loaderLock);
    if (m_streamLoaded) {
        ALOGD("already Init stream export!");
        return true;
    }
    ALOGD("hostconnect init stream export begin");

#if defined(__LP64__)
    const std::string libName = "/vendor/lib64/libVmiInstructionEngine.so";
#else
    const std::string libName = "/vendor/lib/libVmiInstructionEngine.so";
#endif
    m_loader = std::make_unique<LoadSharedLib>(libName);
    if (m_loader == nullptr) {
        ALOGE("Failed to create loader %s", libName.c_str());
        return false;
    }

    getStream = reinterpret_cast<decltype(getStream)>(m_loader->GetProcAddress("GetStream"));
    if (getStream == nullptr) {
        ALOGE("Failed to find GetStream Api!");
        return false;
    }
    releaseStream = reinterpret_cast<decltype(releaseStream)>(m_loader->GetProcAddress("ReleaseStream"));
    if (releaseStream == nullptr) {
        ALOGE("Failed to find RelaseStream Api!");
        return false;
    }
    // getOpSize为非必要接口，用来获取本次指令网络包数据大小，平时关闭
    getOpSize = reinterpret_cast<decltype(getOpSize)>(m_loader->GetProcAddress("GetOpSize"));
    if (getOpSize == nullptr) {
        ALOGE("Failed to find GetOpSize Api!");
    }
    waitRebuildStateMachine = reinterpret_cast<decltype(waitRebuildStateMachine)>(m_loader->
        GetProcAddress("WaitRebuildStateMachine"));
    if (waitRebuildStateMachine == nullptr) {
        ALOGE("Failed to find WaitRebuildStateMachine Api!");
        return false;
    }

    m_streamLoaded = true;
    return true;
}