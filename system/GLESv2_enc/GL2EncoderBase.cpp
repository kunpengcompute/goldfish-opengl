/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description:  GL2Encoder base class.
 */
#define LOG_TAG "GL2EncoderBase"
#include "GL2EncoderBase.h"
#include "GL2Encoder.h"
#include <string>
#include <climits>
#include <cstdlib>
#include <dlfcn.h>

createGLESv2Encoder_proc_t GL2EncoderBase::createGLESv2EncoderFunc = nullptr;
glActiveTexture_client_proc_t GL2EncoderBase::glActiveTextureFunc = nullptr;
glAttachShader_client_proc_t GL2EncoderBase::glAttachShaderFunc = nullptr;
glBindAttribLocation_client_proc_t GL2EncoderBase::glBindAttribLocationFunc = nullptr;
glBindBuffer_client_proc_t GL2EncoderBase::glBindBufferFunc = nullptr;
glBindFramebuffer_client_proc_t GL2EncoderBase::glBindFramebufferFunc = nullptr;
glBindRenderbuffer_client_proc_t GL2EncoderBase::glBindRenderbufferFunc = nullptr;
glBindTexture_client_proc_t GL2EncoderBase::glBindTextureFunc = nullptr;
glBlendColor_client_proc_t GL2EncoderBase::glBlendColorFunc = nullptr;
glBlendEquation_client_proc_t GL2EncoderBase::glBlendEquationFunc = nullptr;
glBlendEquationSeparate_client_proc_t GL2EncoderBase::glBlendEquationSeparateFunc = nullptr;
glBlendFunc_client_proc_t GL2EncoderBase::glBlendFuncFunc = nullptr;
glBlendFuncSeparate_client_proc_t GL2EncoderBase::glBlendFuncSeparateFunc = nullptr;
glBufferData_client_proc_t GL2EncoderBase::glBufferDataFunc = nullptr;
glBufferSubData_client_proc_t GL2EncoderBase::glBufferSubDataFunc = nullptr;
glCheckFramebufferStatus_client_proc_t GL2EncoderBase::glCheckFramebufferStatusFunc = nullptr;
glClear_client_proc_t GL2EncoderBase::glClearFunc = nullptr;
glClearColor_client_proc_t GL2EncoderBase::glClearColorFunc = nullptr;
bool GL2EncoderBase::m_isInit = false;
void *GL2EncoderBase::m_libHandle = nullptr;

void *LoadLibrary(const std::string &path)
{
    if (path.empty()) {
        ALOGE("Failed to open library, path is empty");
        return nullptr;
    }

    auto realPath = realpath(path.c_str(), nullptr);
    if (realPath == nullptr) {
        return nullptr;
    }
    auto library = dlopen(realPath, RTLD_LAZY | RTLD_LOCAL);
    free(realPath);
    realPath = nullptr;
    if (library == nullptr) {
        const char *reason = dlerror();
        if (reason == nullptr) {
            reason = "Unknow";
        }
        ALOGE("Failed to open library, path:%s, reason:%s", path.c_str(), reason);
    }
    return library;
}

void *GetProcAddress(void *library, const std::string &name)
{
    if (library == nullptr || name.empty()) {
        ALOGE("Failed to get function:%s, library == nullptr", name.c_str());
        return nullptr;
    }
    void *symbol = dlsym(library, name.c_str());
    if (symbol == nullptr) {
        const char *reason = dlerror();
        if (reason == nullptr) {
            reason = "Unknow";
        }
        ALOGE("Failed to get function:%s, reason:%s", name.c_str(), reason);
    }
    return symbol;
}

/**
 * @brief: GL2EncoderBase constructor function
 */
GL2EncoderBase::GL2EncoderBase()
{
    glActiveTexture = glActiveTexture_s;
    glAttachShader = glAttachShader_s;
    glBindAttribLocation = glBindAttribLocation_s;
    glBindBuffer = glBindBuffer_s;
    glBindFramebuffer = glBindFramebuffer_s;
    glBindRenderbuffer = glBindRenderbuffer_s;
    glBindTexture = glBindTexture_s;
    glBlendColor = glBlendColor_s;
    glBlendEquation = glBlendEquation_s;
    glBlendEquationSeparate = glBlendEquationSeparate_s;
    glBlendFunc = glBlendFunc_s;
    glBlendFuncSeparate = glBlendFuncSeparate_s;
    glBufferData = glBufferData_s;
    glBufferSubData = glBufferSubData_s;
    glCheckFramebufferStatus = glCheckFramebufferStatus_s;
    glClear = glClear_s;
    glClearColor = glClearColor_s;
    InitGLESv2Export();
}

GL2EncoderBase::~GL2EncoderBase()
{
    if (m_libHandle == nullptr) {
        return;
    }
    if (dlclose(m_libHandle) != 0) {
        const char *reason = dlerror();
        if (reason == nullptr) {
            reason = "Unknow";
        }
        ALOGE("Failed to close library, reason:%s", reason);
    }
    m_libHandle = nullptr;
}

bool GL2EncoderBase::InitGLESv2Export()
{
    ALOGD("GL2EncoderBase::InitGLESv2Export begin");
    if (m_isInit) {
        return true;
    }

#if defined(__LP64__)
    const std::string libName = "/vendor/lib64/libInstructionEngine.so";
#else
    const std::string libName = "/vendor/lib/libInstructionEngine.so";
#endif
    m_libHandle = LoadLibrary(libName);
    if (m_libHandle == nullptr) {
        ALOGE("Failed to LoadLibrary %s, m_libHandle == nullptr", libName.c_str());
        return false;
    }
    std::function<void *(const char *)> func = std::bind(&GetProcAddress, m_libHandle, std::placeholders::_1);
    if (func == nullptr) {
        return false;
    }

    createGLESv2EncoderFunc = reinterpret_cast<decltype(createGLESv2EncoderFunc)>(func("CreateVmiGLESv2Encoder"));
    glActiveTextureFunc = reinterpret_cast<decltype(glActiveTextureFunc)>(func("VmiGlActiveTexture"));
    glAttachShaderFunc = reinterpret_cast<decltype(glAttachShaderFunc)>(func("VmiGlAttachShader"));
    glBindAttribLocationFunc = reinterpret_cast<decltype(glBindAttribLocationFunc)>(func("VmiGlBindAttribLocation"));
    glBindBufferFunc = reinterpret_cast<decltype(glBindBufferFunc)>(func("VmiGlBindBuffer"));
    glBindFramebufferFunc = reinterpret_cast<decltype(glBindFramebufferFunc)>(func("VmiGlBindFramebuffer"));
    glBindRenderbufferFunc = reinterpret_cast<decltype(glBindRenderbufferFunc)>(func("VmiGlBindRenderbuffer"));
    glBindTextureFunc = reinterpret_cast<decltype(glBindTextureFunc)>(func("VmiGlBindTexture"));
    glBlendColorFunc = reinterpret_cast<decltype(glBlendColorFunc)>(func("VmiGlBlendColor"));
    glBlendEquationFunc = reinterpret_cast<decltype(glBlendEquationFunc)>(func("VmiGlBlendEquation"));
    glBlendEquationSeparateFunc =
        reinterpret_cast<decltype(glBlendEquationSeparateFunc)>(func("VmiGlBlendEquationSeparate"));
    glBlendFuncFunc = reinterpret_cast<decltype(glBlendFuncFunc)>(func("VmiGlBlendFunc"));
    glBlendFuncSeparateFunc = reinterpret_cast<decltype(glBlendFuncSeparateFunc)>(func("VmiGlBlendFuncSeparate"));
    glBufferDataFunc = reinterpret_cast<decltype(glBufferDataFunc)>(func("VmiGlBufferData"));
    glBufferSubDataFunc = reinterpret_cast<decltype(glBufferSubDataFunc)>(func("VmiGlBufferSubData"));
    glCheckFramebufferStatusFunc =
        reinterpret_cast<decltype(glCheckFramebufferStatusFunc)>(func("VmiGlCheckFramebufferStatus"));
    glClearFunc = reinterpret_cast<decltype(glClearFunc)>(func("VmiGlClear"));
    glClearColorFunc = reinterpret_cast<decltype(glClearColorFunc)>(func("VmiGlClearColor"));

    m_isInit = true;
    ALOGD("GL2EncoderBase::InitGLESv2Export success!");
    return true;
}

void *GL2EncoderBase::GetGLESv2Encoder(void *self)
{
    GL2Encoder *ctx = static_cast<GL2Encoder *>(self);
    return dynamic_cast<VmiGLESv2Encoder *>(ctx);
}

bool GL2EncoderBase::CreateVmiGLESv2Encoder(void *stream)
{
    if (createGLESv2EncoderFunc == nullptr) {
        return false;
    }
    m_GLESv2Encoder = createGLESv2EncoderFunc(stream);
    if (m_GLESv2Encoder == nullptr) {
        return false;
    }
    return true;
}

void GL2EncoderBase::glActiveTexture_s(void *self, unsigned int texture)
{
    GL2EncoderBase *ctx = static_cast<GL2EncoderBase *>(self);
    if (ctx == nullptr) {
        ALOGE("glActiveTexture_s: parameters error. ctx==nullptr");
        return;
    }
    ctx->glActiveTextureFunc(ctx->GetGLESv2Encoder(self), texture);
}

void GL2EncoderBase::glAttachShader_s(void *self, GLuint program, GLuint shader)
{
    GL2EncoderBase *ctx = static_cast<GL2EncoderBase *>(self);
    if (ctx == nullptr) {
        ALOGE("glAttachShader_s: parameters error. ctx==nullptr");
        return;
    }
    ctx->glAttachShaderFunc(ctx->GetGLESv2Encoder(self), program, shader);
}

void GL2EncoderBase::glBindAttribLocation_s(void *self, GLuint program, GLuint index, const GLchar *name)
{
    GL2EncoderBase *ctx = static_cast<GL2EncoderBase *>(self);
    if (ctx == nullptr) {
        ALOGE("glBindAttribLocation_s: parameters error. ctx==nullptr");
        return;
    }
    ctx->glBindAttribLocationFunc(ctx->GetGLESv2Encoder(self), program, index, name);
}

void GL2EncoderBase::glBindBuffer_s(void *self, GLenum target, GLuint buffer)
{
    GL2EncoderBase *ctx = static_cast<GL2EncoderBase *>(self);
    if (ctx == nullptr) {
        ALOGE("glBindBuffer_s: parameters error. ctx==nullptr");
        return;
    }
    ctx->glBindBufferFunc(ctx->GetGLESv2Encoder(self), target, buffer);
}

void GL2EncoderBase::glBindFramebuffer_s(void *self, GLenum target, GLuint framebuffer)
{
    GL2EncoderBase *ctx = static_cast<GL2EncoderBase *>(self);
    if (ctx == nullptr) {
        ALOGE("glBindFramebuffer_s: parameters error. ctx==nullptr");
        return;
    }
    ctx->glBindFramebufferFunc(ctx->GetGLESv2Encoder(self), target, framebuffer);
}

void GL2EncoderBase::glBindRenderbuffer_s(void *self, GLenum target, GLuint renderbuffer)
{
    GL2EncoderBase *ctx = static_cast<GL2EncoderBase *>(self);
    if (ctx == nullptr) {
        ALOGE("glBindRenderbuffer_s: parameters error. ctx==nullptr");
        return;
    }
    ctx->glBindRenderbufferFunc(ctx->GetGLESv2Encoder(self), target, renderbuffer);
}

void GL2EncoderBase::glBindTexture_s(void *self, GLenum target, GLuint texture)
{
    GL2EncoderBase *ctx = static_cast<GL2EncoderBase *>(self);
    if (ctx == nullptr) {
        ALOGE("glBindTexture_s: parameters error. ctx==nullptr");
        return;
    }
    ctx->glBindTextureFunc(ctx->GetGLESv2Encoder(self), target, texture);
}

void GL2EncoderBase::glBlendColor_s(void *self, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
    GL2EncoderBase *ctx = static_cast<GL2EncoderBase *>(self);
    if (ctx == nullptr) {
        ALOGE("glBlendColor_s: parameters error. ctx==nullptr");
        return;
    }
    ctx->glBlendColorFunc(ctx->GetGLESv2Encoder(self), red, green, blue, alpha);
}

void GL2EncoderBase::glBlendEquation_s(void *self, GLenum mode)
{
    GL2EncoderBase *ctx = static_cast<GL2EncoderBase *>(self);
    if (ctx == nullptr) {
        ALOGE("glBlendEquation_s: parameters error. ctx==nullptr");
        return;
    }
    ctx->glBlendEquationFunc(ctx->GetGLESv2Encoder(self), mode);
}

void GL2EncoderBase::glBlendEquationSeparate_s(void *self, GLenum modeRGB, GLenum modeAlpha)
{
    GL2EncoderBase *ctx = static_cast<GL2EncoderBase *>(self);
    if (ctx == nullptr) {
        ALOGE("glBlendEquationSeparate_s: parameters error. ctx==nullptr");
        return;
    }
    ctx->glBlendEquationSeparateFunc(ctx->GetGLESv2Encoder(self), modeRGB, modeAlpha);
}

void GL2EncoderBase::glBlendFunc_s(void *self, GLenum sfactor, GLenum dfactor)
{
    GL2EncoderBase *ctx = static_cast<GL2EncoderBase *>(self);
    if (ctx == nullptr) {
        ALOGE("glBlendFunc_s: parameters error. ctx==nullptr");
        return;
    }
    ctx->glBlendFuncFunc(ctx->GetGLESv2Encoder(self), sfactor, dfactor);
}

void GL2EncoderBase::glBlendFuncSeparate_s(void *self, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
    GL2EncoderBase *ctx = static_cast<GL2EncoderBase *>(self);
    if (ctx == nullptr) {
        ALOGE("glBlendFuncSeparate_s: parameters error. ctx==nullptr");
        return;
    }
    ctx->glBlendFuncSeparateFunc(ctx->GetGLESv2Encoder(self), srcRGB, dstRGB, srcAlpha, dstAlpha);
}

void GL2EncoderBase::glBufferData_s(void *self, GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage)
{
    GL2EncoderBase *ctx = static_cast<GL2EncoderBase *>(self);
    if (ctx == nullptr) {
        ALOGE("glBufferData_s: parameters error. ctx==nullptr");
        return;
    }
    ctx->glBufferDataFunc(ctx->GetGLESv2Encoder(self), target, size, data, usage);
}

void GL2EncoderBase::glBufferSubData_s(void *self, GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data)
{
    GL2EncoderBase *ctx = static_cast<GL2EncoderBase *>(self);
    if (ctx == nullptr) {
        ALOGE("glBufferSubData_s: parameters error. ctx==nullptr");
        return;
    }
    ctx->glBufferSubDataFunc(ctx->GetGLESv2Encoder(self), target, offset, size, data);
}

GLenum GL2EncoderBase::glCheckFramebufferStatus_s(void *self, GLenum target)
{
    GL2EncoderBase *ctx = static_cast<GL2EncoderBase *>(self);
    if (ctx == nullptr) {
        ALOGE("glCheckFramebufferStatus_s: parameters error. ctx==nullptr");
    }
    return ctx->glCheckFramebufferStatusFunc(ctx->GetGLESv2Encoder(self), target);
}

void GL2EncoderBase::glClear_s(void *self, GLbitfield mask)
{
    GL2EncoderBase *ctx = static_cast<GL2EncoderBase *>(self);
    if (ctx == nullptr) {
        ALOGE("glClear_s: parameters error. ctx==nullptr");
        return;
    }
    ctx->glClearFunc(ctx->GetGLESv2Encoder(self), mask);
}

void GL2EncoderBase::glClearColor_s(void *self, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
    GL2EncoderBase *ctx = static_cast<GL2EncoderBase *>(self);
    if (ctx == nullptr) {
        ALOGE("glClearColor_s: parameters error. ctx==nullptr");
        return;
    }
    ctx->glClearColorFunc(ctx->GetGLESv2Encoder(self), red, green, blue, alpha);
}