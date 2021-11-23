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
#include "IRenderControlEncoder.h"
#include "ChecksumCalculator.h"
#include "goldfish_dma.h"
#include "LoadSharedLib.h"

#include <string>
#include <memory>
#include <mutex>

class GLEncoder;
struct gl_client_context_t;
class GL2Encoder;
struct gl2_client_context_t;

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
// enum SyncImpl {
//     SYNC_IMPL_NONE = 0,
//     SYNC_IMPL_NATIVE_SYNC_V2 = 1,
//     SYNC_IMPL_NATIVE_SYNC_V3 = 2,
// };

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

// // OpenGL ES max supported version
// enum GLESMaxVersion {
//     GLES_MAX_VERSION_2 = 0,
//     GLES_MAX_VERSION_3_0 = 1,
//     GLES_MAX_VERSION_3_1 = 2,
//     GLES_MAX_VERSION_3_2 = 3,
// };

static const char kGLESMaxVersion_2[] = "ANDROID_EMU_gles_max_version_2";
static const char kGLESMaxVersion_3_0[] = "ANDROID_EMU_gles_max_version_3_0";
static const char kGLESMaxVersion_3_1[] = "ANDROID_EMU_gles_max_version_3_1";
static const char kGLESMaxVersion_3_2[] = "ANDROID_EMU_gles_max_version_3_2";

// No querying errors from host extension
static const char kGLESNoHostError[] = "ANDROID_EMU_gles_no_host_error";

typedef void *(*GetStreamFunc)();
typedef void (*ReleaseStreamFunc)(void* stream);
typedef void (*WaitRebuildStateMachineFunc)(void* stream);

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
    IRenderControlEncoder *rcEncoder();
    ChecksumCalculator *checksumHelper() { return &m_checksumHelper; }

    void setGrallocOnly(bool gralloc_only) {
        m_grallocOnly = gralloc_only;
    }

    bool isGrallocOnly() const { return m_grallocOnly; }

    int getPipeFd() const { return m_pipeFd; }

private:
    HostConnection();
    static gl_client_context_t  *s_getGLContext();
    static gl2_client_context_t *s_getGL2Context();
    const std::string& queryGLExtensions(IRenderControlEncoder *rcEnc);
    // setProtocol initilizes GL communication protocol for checksums
    // should be called when m_rcEnc is created
    //void setChecksumHelper(ExtendedRCEncoderContext *rcEnc);
    void queryAndSetSyncImpl(IRenderControlEncoder *rcEnc);
    //void queryAndSetDmaImpl(ExtendedRCEncoderContext *rcEnc);
    void queryAndSetGLESMaxVersion(IRenderControlEncoder *rcEnc);
    void queryAndSetNoErrorState(IRenderControlEncoder *rcEnc);

private:
    IOStream *m_iostream;
    void *m_stream;
    GLEncoder   *m_glEnc;
    GL2Encoder  *m_gl2Enc;
    IRenderControlEncoder *m_rcEnc;
    ChecksumCalculator m_checksumHelper;
    std::string m_glExtensions;
    bool m_grallocOnly;
    int m_pipeFd;
    bool m_noHostError;
    static std::unique_ptr<LoadSharedLib> m_loader;
    static bool m_streamLoaded;
    static std::mutex m_loaderLock;
};

#endif
