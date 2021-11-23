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
#ifndef __EXTENDED_RC_ENCODER_CONTEXT_H
#define __EXTENDED_RC_ENCODER_CONTEXT_H

#include "LoadSharedLib.h"
#include <stdint.h>
#include <EGL/egl.h>
#include "glUtils.h"
#include <string>
#include <memory>
#include <mutex>

enum SyncImpl {
    SYNC_IMPL_NONE = 0,
    SYNC_IMPL_NATIVE_SYNC_V2 = 1,
    SYNC_IMPL_NATIVE_SYNC_V3 = 2,
};

// OpenGL ES max supported version 	19
enum GLESMaxVersion {
    GLES_MAX_VERSION_2 = 0,
    GLES_MAX_VERSION_3_0 = 1,
    GLES_MAX_VERSION_3_1 = 2,
    GLES_MAX_VERSION_3_2 = 3,
};

typedef void (*setGLESMaxVersion_proc_t)(uint32_t handle, GLESMaxVersion ver);
typedef GLESMaxVersion (*getGLESMaxVersion_proc_t)(uint32_t handle);
typedef void (*setSyncImpl_proc_t)(uint32_t handle, SyncImpl syncImpl);
typedef bool (*hasNativeSync_proc_t)(uint32_t handle);
typedef bool (*hasNativeSyncV3_proc_t)(uint32_t handle);
typedef uint32_t (*createVmiRenderControlEncoder_proc_t)(uint32_t stream);
typedef void (*deleteVmiRenderControlEncoder_proc_t)(uint32_t handle);
typedef GLint (*rcGetRendererVersion_proc_t) (uint32_t handle);
typedef EGLint (*rcGetEGLVersion_proc_t) (uint32_t handle, EGLint*, EGLint*);
typedef EGLint (*rcQueryEGLString_proc_t) (uint32_t handle, EGLenum, void*, EGLint);
typedef EGLint (*rcGetGLString_proc_t) (uint32_t handle, EGLenum, void*, EGLint);
typedef EGLint (*rcGetNumConfigs_proc_t) (uint32_t handle, uint32_t*);
typedef EGLint (*rcGetConfigs_proc_t) (uint32_t handle, uint32_t, GLuint*);
typedef EGLint (*rcChooseConfig_proc_t) (uint32_t handle, EGLint*, uint32_t, uint32_t*, uint32_t);
typedef EGLint (*rcGetFBParam_proc_t) (uint32_t handle, EGLint);
typedef uint32_t (*rcCreateContext_proc_t) (uint32_t handle, uint32_t, uint32_t, uint32_t, const EGLint *);
typedef void (*rcDestroyContext_proc_t) (uint32_t handle, uint32_t);
typedef uint32_t (*rcCreateWindowSurface_proc_t) (uint32_t handle, uint32_t, uint32_t, uint32_t, void*, int32_t);
typedef void (*rcDestroyWindowSurface_proc_t) (uint32_t handle, uint32_t);
typedef uint32_t (*rcCreateColorBuffer_proc_t) (uint32_t handle, uint32_t, uint32_t, GLenum, GLenum, int32_t);
typedef void (*rcOpenColorBuffer_proc_t) (uint32_t handle, uint32_t);
typedef void (*rcCloseColorBuffer_proc_t) (uint32_t handle, uint32_t);
typedef void (*rcSetWindowColorBuffer_proc_t) (uint32_t handle, uint32_t, uint32_t);
typedef int (*rcFlushWindowColorBuffer_proc_t) (uint32_t handle, uint32_t, EGLint *rects, EGLint rectsNum);
typedef EGLint (*rcMakeCurrent_proc_t) (uint32_t handle, uint32_t, uint32_t, uint32_t);
typedef void (*rcFBPost_proc_t) (uint32_t handle, uint32_t);
typedef void (*rcFBSetSwapInterval_proc_t) (uint32_t handle, EGLint);
typedef void (*rcBindTexture_proc_t) (uint32_t handle, uint32_t);
typedef void (*rcBindRenderbuffer_proc_t) (uint32_t handle, uint32_t);
typedef EGLint (*rcColorBufferCacheFlush_proc_t) (uint32_t handle, uint32_t, EGLint, int);
typedef void (*rcReadColorBuffer_proc_t) (uint32_t handle, uint32_t, GLint, GLint, GLint, GLint, GLenum, GLenum, void*);
typedef int (*rcUpdateColorBuffer_proc_t) (uint32_t handle, uint32_t, GLint, GLint, GLint, GLint, GLenum, GLenum, void*);
typedef int (*rcOpenColorBuffer2_proc_t) (uint32_t handle, uint32_t);
typedef uint32_t (*rcCreateClientImage_proc_t) (uint32_t handle, uint32_t, EGLenum, GLuint);
typedef int (*rcDestroyClientImage_proc_t) (uint32_t handle, uint32_t);
typedef void (*rcSelectChecksumHelper_proc_t) (uint32_t handle, uint32_t, uint32_t);
typedef void (*rcCreateSyncKHR_proc_t) (uint32_t handle, EGLenum, EGLint*, uint32_t, int, uint64_t*, uint64_t*);
typedef EGLint (*rcClientWaitSyncKHR_proc_t) (uint32_t handle, uint64_t, EGLint, uint64_t);
typedef void (*rcFlushWindowColorBufferAsync_proc_t) (uint32_t handle, uint32_t, EGLint *rects, EGLint rectsNum);
typedef int (*rcDestroySyncKHR_proc_t) (uint32_t handle, uint64_t);
typedef void (*rcSetPuid_proc_t) (uint32_t handle, uint64_t);
typedef int (*rcUpdateColorBufferDMA_proc_t) (uint32_t handle, uint32_t, GLint, GLint, GLint, GLint, GLenum, GLenum, void*, uint32_t);
typedef uint32_t (*rcCreateColorBufferDMA_proc_t) (uint32_t handle, uint32_t, uint32_t, GLenum, int);
typedef void (*rcWaitSyncKHR_proc_t) (uint32_t handle, uint64_t, EGLint);

class ExtendedRCEncoderContext {
public:
    ExtendedRCEncoderContext();
    ~ExtendedRCEncoderContext();
    int initDispatchByName(void *(*getProc)(const char *, void *userData), void *userData);
    bool InitRenderControlExport();
    uint32_t GetRenderControlEncoder(void *self);
    bool CreateVmiRenderControlEncoder(uint32_t stream);
    void DeleteVmiRenderControlEncoder();
public:
    rcGetRendererVersion_proc_t rcGetRendererVersion;
    rcGetEGLVersion_proc_t rcGetEGLVersion;
    rcQueryEGLString_proc_t rcQueryEGLString;
    rcGetGLString_proc_t rcGetGLString;
    rcGetNumConfigs_proc_t rcGetNumConfigs;
    rcGetConfigs_proc_t rcGetConfigs;
    rcChooseConfig_proc_t rcChooseConfig;
    rcGetFBParam_proc_t rcGetFBParam;
    rcCreateContext_proc_t rcCreateContext;
    rcDestroyContext_proc_t rcDestroyContext;
    rcCreateWindowSurface_proc_t rcCreateWindowSurface;
    rcDestroyWindowSurface_proc_t rcDestroyWindowSurface;
    rcCreateColorBuffer_proc_t rcCreateColorBuffer;
    rcOpenColorBuffer_proc_t rcOpenColorBuffer;
    rcCloseColorBuffer_proc_t rcCloseColorBuffer;
    rcSetWindowColorBuffer_proc_t rcSetWindowColorBuffer;
    rcFlushWindowColorBuffer_proc_t rcFlushWindowColorBuffer;
    rcMakeCurrent_proc_t rcMakeCurrent;
    rcFBPost_proc_t rcFBPost;
    rcFBSetSwapInterval_proc_t rcFBSetSwapInterval;
    rcBindTexture_proc_t rcBindTexture;
    rcBindRenderbuffer_proc_t rcBindRenderbuffer;
    rcColorBufferCacheFlush_proc_t rcColorBufferCacheFlush;
    rcReadColorBuffer_proc_t rcReadColorBuffer;
    rcUpdateColorBuffer_proc_t rcUpdateColorBuffer;
    rcOpenColorBuffer2_proc_t rcOpenColorBuffer2;
    rcCreateClientImage_proc_t rcCreateClientImage;
    rcDestroyClientImage_proc_t rcDestroyClientImage;
    rcSelectChecksumHelper_proc_t rcSelectChecksumHelper;
    rcCreateSyncKHR_proc_t rcCreateSyncKHR;
    rcClientWaitSyncKHR_proc_t rcClientWaitSyncKHR;
    rcFlushWindowColorBufferAsync_proc_t rcFlushWindowColorBufferAsync;
    rcDestroySyncKHR_proc_t rcDestroySyncKHR;
    rcSetPuid_proc_t rcSetPuid;
    rcUpdateColorBufferDMA_proc_t rcUpdateColorBufferDMA;
    rcCreateColorBufferDMA_proc_t rcCreateColorBufferDMA;
    rcWaitSyncKHR_proc_t rcWaitSyncKHR;
    setSyncImpl_proc_t setSyncImpl;
    hasNativeSync_proc_t hasNativeSync;
    hasNativeSyncV3_proc_t hasNativeSyncV3;
    setGLESMaxVersion_proc_t setGLESMaxVersion;
    getGLESMaxVersion_proc_t getGLESMaxVersion;
    createVmiRenderControlEncoder_proc_t createVmiRenderControlEncoderFunc;
    deleteVmiRenderControlEncoder_proc_t deleteVmiRenderControlEncoderFunc;
private:
    uint32_t m_renderControlWrap = 0;
    static void *m_implLib;
    static std::mutex m_lock;
};

#endif
