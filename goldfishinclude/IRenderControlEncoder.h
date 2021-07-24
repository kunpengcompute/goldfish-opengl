/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2017-2019. All rights reserved.
 * Description: render control encoder interface
 */
#ifndef IRENDER_CONTROL_ENCODER_H
#define IRENDER_CONTROL_ENCODER_H

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include "IStream.h"

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

class IRenderControlEncoder {
public:
    IRenderControlEncoder() {};
    virtual ~IRenderControlEncoder() {};

    virtual GLint rcGetRendererVersion() = 0;
    virtual EGLint rcGetEGLVersion(EGLint* major, EGLint* minor) = 0;
    virtual EGLint rcQueryEGLString(EGLenum name, void* buffer, EGLint bufferSize) = 0;
    virtual EGLint rcGetGLString(EGLenum name, void* buffer, EGLint bufferSize) = 0;
    virtual EGLint rcGetNumConfigs(uint32_t* numAttribs) = 0;
    virtual EGLint rcGetConfigs(uint32_t bufSize, GLuint* buffer) = 0;
    virtual EGLint rcChooseConfig(EGLint* attribs, uint32_t attribSize, uint32_t* configs, uint32_t configSize) = 0;
    virtual EGLint rcGetFBParam(EGLint param) = 0;
    virtual uint32_t rcCreateContext(uint32_t config, uint32_t share, uint32_t glVersion,
                                     const EGLint *attribList) = 0;
    virtual void rcDestroyContext(uint32_t context) = 0;
    virtual uint32_t rcCreateWindowSurface(uint32_t config, uint32_t width, uint32_t height,
        void* window, int32_t type) = 0;
    virtual void rcDestroyWindowSurface(uint32_t windowSurface) = 0;
    virtual uint32_t rcCreateColorBuffer(uint32_t width, uint32_t height, GLenum internalFormat,
        GLenum internalType, int32_t pixelFormat) = 0;
    virtual void rcOpenColorBuffer(uint32_t colorBuffer) = 0;
    virtual void rcCloseColorBuffer(uint32_t colorBuffer) = 0;
    virtual void rcSetWindowColorBuffer(uint32_t windowSurface, uint32_t colorBuffer) = 0;
    virtual int rcFlushWindowColorBuffer(uint32_t windowSurface, EGLint* rects, EGLint rectsNum) = 0;
    virtual EGLint rcMakeCurrent(uint32_t context, uint32_t drawSurf, uint32_t readSurf) = 0;
    virtual void rcFBPost(uint32_t colorBuffer) = 0;
    virtual void rcFBSetSwapInterval(EGLint interval) = 0;
    virtual void rcBindTexture(uint32_t colorBuffer) = 0;
    virtual void rcBindRenderbuffer(uint32_t colorBuffer) = 0;
    virtual EGLint rcColorBufferCacheFlush(uint32_t colorBuffer, EGLint postCount, int forRead) = 0;
    virtual void rcReadColorBuffer(uint32_t colorBuffer, GLint x, GLint y, GLint width, GLint height,
        GLenum format, GLenum type, void* pixels) = 0;
    virtual int rcUpdateColorBuffer(uint32_t colorBuffer, GLint x, GLint y, GLint width, GLint height,
        GLenum format, GLenum type, void* pixels) = 0;
    virtual int rcOpenColorBuffer2(uint32_t colorBuffer) = 0;
    virtual uint32_t rcCreateClientImage(uint32_t context, EGLenum target, GLuint buffer) = 0;
    virtual int rcDestroyClientImage(uint32_t image) = 0;
    virtual void rcSelectChecksumHelper(uint32_t newProtocol, uint32_t reserved) = 0;
    virtual void rcFlushWindowColorBufferAsync(uint32_t windowSurface, EGLint* rects, EGLint rectsNum) = 0;

    virtual void rcCreateSyncKHR(EGLenum type, EGLint* attribs, uint32_t numAttribs,
        int destroyWhenSignaled, uint64_t* glsyncOut, uint64_t* syncThreadOut) = 0;
    virtual int rcDestroySyncKHR(uint64_t sync) = 0;
    virtual void rcWaitSyncKHR(uint64_t sync, EGLint flags) = 0;
    virtual EGLint rcClientWaitSyncKHR(uint64_t sync, EGLint flags, uint64_t timeout) = 0;

    virtual void setGLESMaxVersion(GLESMaxVersion ver) = 0;
    virtual GLESMaxVersion getGLESMaxVersion() const = 0;
    virtual void setSyncImpl(SyncImpl syncImpl) = 0;
    virtual bool hasNativeSync() const = 0;
    virtual bool hasNativeSyncV3() const = 0;
};

IRenderControlEncoder* InstantiateRenderControlEncoder(IStream *stream);

#endif  // IRENDER_CONTROL_ENCODER_H
