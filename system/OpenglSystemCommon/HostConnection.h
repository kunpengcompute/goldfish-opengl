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
#include "LoadSharedLib.h"
#include "ExtendedRCEncoderContext.h"
#include <string>
#include <memory>
#include <mutex>
#include "cutils/native_handle.h"

class GLEncoder;
struct gl_client_context_t;
class GL2Encoder;
struct gl2_client_context_t;

namespace goldfish_vk {
class VkEncoder;
}

typedef uint32_t (*GetStreamFunc)();
typedef void (*ReleaseStreamFunc)(uint32_t streamHandle);
typedef void (*WaitRebuildStateMachineFunc)(uint32_t streamHandle);

// DMA for OpenGL
class Gralloc {
public:
    virtual uint32_t createColorBuffer(
        ExtendedRCEncoderContext* rcEnc, int width, int height, uint32_t glformat) = 0;
    virtual uint32_t getHostHandle(native_handle_t const* handle) = 0;
    virtual int getFormat(native_handle_t const* handle) = 0;
    virtual size_t getAllocatedSize(native_handle_t const* handle) = 0;
    virtual ~Gralloc() {}
};


struct EGLThreadInfo;

class HostConnection
{
public:
    static HostConnection *get();
    static HostConnection *getWithThreadInfo(EGLThreadInfo* tInfo);
    static void exit();
    ~HostConnection();

    bool initStreamExport();
    static GetStreamFunc getStream;
    static ReleaseStreamFunc releaseStream;
    static WaitRebuildStateMachineFunc waitRebuildStateMachine;
    GLEncoder *glEncoder();
    GL2Encoder *gl2Encoder();
    goldfish_vk::VkEncoder *vkEncoder();
    ExtendedRCEncoderContext *rcEncoder();
    ChecksumCalculator *checksumHelper() { return &m_checksumHelper; }
	Gralloc *grallocHelper() { return m_grallocHelper; }

    void setGrallocOnly(bool gralloc_only) {
        m_grallocOnly = gralloc_only;
    }

    bool isGrallocOnly() const { return m_grallocOnly; }

    int getPipeFd() const { return m_pipeFd; }

private:
    HostConnection();
    static gl_client_context_t  *s_getGLContext();
    static gl2_client_context_t *s_getGL2Context();
    const std::string& queryGLExtensions(ExtendedRCEncoderContext *rcEnc);
    // setProtocol initilizes GL communication protocol for checksums
    // should be called when m_rcEnc is created
    //void setChecksumHelper(ExtendedRCEncoderContext *rcEnc);
    void queryAndSetSyncImpl(ExtendedRCEncoderContext *rcEnc);
    //void queryAndSetDmaImpl(ExtendedRCEncoderContext *rcEnc);
    void queryAndSetGLESMaxVersion(ExtendedRCEncoderContext *rcEnc);
    void queryAndSetNoErrorState(ExtendedRCEncoderContext *rcEnc);

private:
    IOStream *m_iostream;
    uint32_t m_streamHandle;
    GLEncoder   *m_glEnc;
    GL2Encoder  *m_gl2Enc;
    goldfish_vk::VkEncoder  *m_vkEnc;
    ExtendedRCEncoderContext *m_rcEnc;
    ChecksumCalculator m_checksumHelper;
	Gralloc *m_grallocHelper;
    std::string m_glExtensions;
    bool m_grallocOnly;
    int m_pipeFd;
    bool m_noHostError;
    static std::unique_ptr<LoadSharedLib> m_loader;
    static bool m_streamLoaded;
    static std::mutex m_loaderLock;
};

#endif
