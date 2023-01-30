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
#include "EmulatorFeatureInfo.h"

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
typedef void (*rcCloseColorBuffer_proc_t) (uint32_t handle, uint32_t, uint32_t);
typedef void (*rcSetWindowColorBuffer_proc_t) (uint32_t handle, uint32_t, uint32_t, uint32_t);
typedef int (*rcFlushWindowColorBuffer_proc_t) (uint32_t handle, uint32_t, uint32_t, uint32_t, EGLint *rects, EGLint rectsNum);
typedef EGLint (*rcMakeCurrent_proc_t) (uint32_t handle, uint32_t, uint32_t, uint32_t);
typedef void (*rcFBPost_proc_t) (uint32_t handle, uint32_t, uint32_t);
typedef void (*rcFBSetSwapInterval_proc_t) (uint32_t handle, EGLint);
typedef void (*rcBindTexture_proc_t) (uint32_t handle, uint32_t, uint32_t, uint32_t);
typedef void (*rcBindRenderbuffer_proc_t) (uint32_t handle, uint32_t, uint32_t);
typedef EGLint (*rcColorBufferCacheFlush_proc_t) (uint32_t handle, uint32_t, EGLint, int);
typedef void (*rcReadColorBuffer_proc_t) (uint32_t handle, uint32_t, uint32_t, GLint, GLint, GLint, GLint, GLenum, GLenum, void*);
typedef int (*rcUpdateColorBuffer_proc_t) (uint32_t handle, uint32_t, uint32_t, GLint, GLint, GLint, GLint, GLenum, GLenum, void*);
typedef int (*rcOpenColorBuffer2_proc_t) (uint32_t handle, uint32_t, uint32_t);
typedef uint32_t (*rcCreateClientImage_proc_t) (uint32_t handle, uint32_t, EGLenum, GLuint);
typedef int (*rcDestroyClientImage_proc_t) (uint32_t handle, uint32_t);
typedef void (*rcSelectChecksumHelper_proc_t) (uint32_t handle, uint32_t, uint32_t);
typedef void (*rcCreateSyncKHR_proc_t) (uint32_t handle, EGLenum, EGLint*, uint32_t, int, uint64_t*, uint64_t*);
typedef EGLint (*rcClientWaitSyncKHR_proc_t) (uint32_t handle, uint64_t, EGLint, uint64_t);
typedef void (*rcFlushWindowColorBufferAsync_proc_t) (uint32_t handle, uint32_t, uint32_t, uint32_t, EGLint *rects, EGLint rectsNum);
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

    //void setSyncImpl(SyncImpl syncImpl) { m_featureInfo.syncImpl = syncImpl; }
    void setDmaImpl(DmaImpl dmaImpl) { m_featureInfo.dmaImpl = dmaImpl; }
    void setHostComposition(HostComposition hostComposition) {
        m_featureInfo.hostComposition = hostComposition; }
    //bool hasNativeSync() const { return m_featureInfo.syncImpl >= SYNC_IMPL_NATIVE_SYNC_V2; }
    //bool hasNativeSyncV3() const { return m_featureInfo.syncImpl >= SYNC_IMPL_NATIVE_SYNC_V3; }
    bool hasNativeSyncV4() const { return m_featureInfo.syncImpl >= SYNC_IMPL_NATIVE_SYNC_V4; }
    bool hasHostCompositionV1() const {
        return m_featureInfo.hostComposition == HOST_COMPOSITION_V1; }
    bool hasHostCompositionV2() const {
        return m_featureInfo.hostComposition == HOST_COMPOSITION_V2; }
    bool hasYUVCache() const {
        return m_featureInfo.hasYUVCache; }
    bool hasAsyncUnmapBuffer() const {
        return m_featureInfo.hasAsyncUnmapBuffer; }
    DmaImpl getDmaVersion() const { return m_featureInfo.dmaImpl; }
    //void setGLESMaxVersion(GLESMaxVersion ver) { m_featureInfo.glesMaxVersion = ver; }
    //GLESMaxVersion getGLESMaxVersion() const { return m_featureInfo.glesMaxVersion; }
    bool hasDirectMem() const {
        return m_featureInfo.hasDirectMem;
    }
    const EmulatorFeatureInfo* featureInfo_const() const { return &m_featureInfo; }
    EmulatorFeatureInfo* featureInfo() { return &m_featureInfo; }

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
    EmulatorFeatureInfo m_featureInfo;
};

#endif
