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
#ifndef __COMMON_HOST_CONNECTION_H
#define __COMMON_HOST_CONNECTION_H

#include "IOStream.h"
#include "renderControl_enc.h"
#include "ChecksumCalculator.h"
#include "goldfish_dma.h"

#include <cutils/native_handle.h>
#include <string>

class GLEncoder;
struct gl_client_context_t;
class GL2Encoder;
struct gl2_client_context_t;
class VkEncoder;

// SyncImpl determines the presence of host/guest OpenGL fence sync
// capabilities. It corresponds exactly to EGL_ANDROID_native_fence_sync
// capability, but for the emulator, we need to make sure that
// OpenGL pipe protocols match, so we use a special extension name
// here.
// SYNC_IMPL_NONE means that the native fence sync capability is
// not present, and we will end up using the equivalent of glFinish
// in order to preserve buffer swapping order.
// SYNC_IMPL_NATIVE_SYNC means that we do have native fence sync
// capability, and we will use a fence fd to synchronize buffer swaps.
enum SyncImpl {
    SYNC_IMPL_NONE = 0,
    SYNC_IMPL_NATIVE_SYNC_V2 = 1,
    SYNC_IMPL_NATIVE_SYNC_V3 = 2,
};

// Interface:
// Use the highest of v2 or v3 that show up, making us
// SYNC_IMPL_NATIVE_SYNC_V2 or SYNC_IMPL_NATIVE_SYNC_V3.
static const char kRCNativeSyncV2[] = "ANDROID_EMU_native_sync_v2";
static const char kRCNativeSyncV3[] = "ANDROID_EMU_native_sync_v3";

// DMA for OpenGL
enum DmaImpl {
    DMA_IMPL_NONE = 0,
    DMA_IMPL_v1 = 1,
};

static const char kDmaExtStr_v1[] = "ANDROID_EMU_dma_v1";

// OpenGL ES max supported version
enum GLESMaxVersion {
    GLES_MAX_VERSION_2 = 0,
    GLES_MAX_VERSION_3_0 = 1,
    GLES_MAX_VERSION_3_1 = 2,
    GLES_MAX_VERSION_3_2 = 3,
};

static const char kGLESMaxVersion_2[] = "ANDROID_EMU_gles_max_version_2";
static const char kGLESMaxVersion_3_0[] = "ANDROID_EMU_gles_max_version_3_0";
static const char kGLESMaxVersion_3_1[] = "ANDROID_EMU_gles_max_version_3_1";
static const char kGLESMaxVersion_3_2[] = "ANDROID_EMU_gles_max_version_3_2";

enum HostComposition {
    HOST_COMPOSITION_NONE = 0,
    HOST_COMPOSITION_V1,
};
static const char kHostCompositionV1[] = "ANDROID_EMU_host_composition_v1";

// No querying errors from host extension
static const char kGLESNoHostError[] = "ANDROID_EMU_gles_no_host_error";

// ExtendedRCEncoderContext is an extended version of renderControl_encoder_context_t
// that will be used to track SyncImpl.
class ExtendedRCEncoderContext : public renderControl_encoder_context_t {
public:
    ExtendedRCEncoderContext(IOStream *stream, ChecksumCalculator *checksumCalculator)
        : renderControl_encoder_context_t(stream, checksumCalculator) {
        m_dmaCxt = NULL;
        }
    void setSyncImpl(SyncImpl syncImpl) { m_syncImpl = syncImpl; }
    void setDmaImpl(DmaImpl dmaImpl) { m_dmaImpl = dmaImpl; }
    void setHostComposition(HostComposition hostComposition) {
        m_hostComposition = hostComposition; }
    bool hasNativeSync() const { return m_syncImpl >= SYNC_IMPL_NATIVE_SYNC_V2; }
    bool hasNativeSyncV3() const { return m_syncImpl >= SYNC_IMPL_NATIVE_SYNC_V3; }
    bool hasHostCompositionV1() const {
        return m_hostComposition == HOST_COMPOSITION_V1; }
    DmaImpl getDmaVersion() const { return m_dmaImpl; }
    void bindDmaContext(struct goldfish_dma_context* cxt) { m_dmaCxt = cxt; }
    virtual uint64_t lockAndWriteDma(void* data, uint32_t size) {
        ALOGV("%s: call", __FUNCTION__);
        if (!m_dmaCxt) {
            ALOGE("%s: ERROR: No DMA context bound!",
                  __FUNCTION__);
            return 0;
        }
        goldfish_dma_lock(m_dmaCxt);
        goldfish_dma_write(m_dmaCxt, data, size);
        uint64_t paddr = goldfish_dma_guest_paddr(m_dmaCxt);
        ALOGV("%s: paddr=0x%llx", __FUNCTION__, (unsigned long long)paddr);
        return paddr;
    }
    void setGLESMaxVersion(GLESMaxVersion ver) { m_glesMaxVersion = ver; }
    GLESMaxVersion getGLESMaxVersion() const { return m_glesMaxVersion; }
private:
    SyncImpl m_syncImpl;
    DmaImpl m_dmaImpl;
    HostComposition m_hostComposition;
    struct goldfish_dma_context* m_dmaCxt;
    GLESMaxVersion m_glesMaxVersion;
};

// Abstraction for gralloc handle conversion
class Gralloc {
public:
    virtual uint32_t getHostHandle(native_handle_t const* handle) = 0;
    virtual int getFormat(native_handle_t const* handle) = 0;
    virtual ~Gralloc() {}
};

// Abstraction for process pipe helper
class ProcessPipe {
public:
    virtual bool processPipeInit(renderControl_encoder_context_t *rcEnc) = 0;
    virtual ~ProcessPipe() {}
};

struct EGLThreadInfo;

class HostConnection
{
public:
    static HostConnection *get();
    static HostConnection *getWithThreadInfo(EGLThreadInfo* tInfo);
    static void exit();
    ~HostConnection();

    GLEncoder *glEncoder();
    GL2Encoder *gl2Encoder();
    VkEncoder *vkEncoder();
    ExtendedRCEncoderContext *rcEncoder();
    ChecksumCalculator *checksumHelper() { return &m_checksumHelper; }
    Gralloc *grallocHelper() { return m_grallocHelper; }

    void flush() {
        if (m_stream) {
            m_stream->flush();
        }
    }

    void setGrallocOnly(bool gralloc_only) {
        m_grallocOnly = gralloc_only;
    }

    bool isGrallocOnly() const { return m_grallocOnly; }

private:
    HostConnection();
    static gl_client_context_t  *s_getGLContext();
    static gl2_client_context_t *s_getGL2Context();

    const std::string& queryGLExtensions(ExtendedRCEncoderContext *rcEnc);
    // setProtocol initilizes GL communication protocol for checksums
    // should be called when m_rcEnc is created
    void setChecksumHelper(ExtendedRCEncoderContext *rcEnc);
    void queryAndSetSyncImpl(ExtendedRCEncoderContext *rcEnc);
    void queryAndSetDmaImpl(ExtendedRCEncoderContext *rcEnc);
    void queryAndSetGLESMaxVersion(ExtendedRCEncoderContext *rcEnc);
    void queryAndSetNoErrorState(ExtendedRCEncoderContext *rcEnc);
    void queryAndSetHostCompositionImpl(ExtendedRCEncoderContext *rcEnc);

private:
    IOStream *m_stream;
    GLEncoder   *m_glEnc;
    GL2Encoder  *m_gl2Enc;
    VkEncoder  *m_vkEnc;
    ExtendedRCEncoderContext *m_rcEnc;
    ChecksumCalculator m_checksumHelper;
    Gralloc *m_grallocHelper;
    ProcessPipe *m_processPipe;
    std::string m_glExtensions;
    bool m_grallocOnly;
    bool m_noHostError;
};

#endif
