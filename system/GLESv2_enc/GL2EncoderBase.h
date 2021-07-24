/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description:  GL2Encoder base class.
 */

#ifndef GL2_ENCODER_BASE_H
#define GL2_ENCODER_BASE_H

#include <string>
#include <vector>
#include <functional>
#include <log/log.h>
#include "GLES3/gl32.h"
#include "GLES2/gl2ext.h"
#include "gl2_client_proc.h"

typedef void *(*createGLESv2Encoder_proc_t)(void *stream);

class GL2EncoderBase {
public:
    GL2EncoderBase();
    ~GL2EncoderBase();

    void *GetGLESv2Encoder(void *self);
    bool InitGLESv2Export();

    bool CreateVmiGLESv2Encoder(void *stream);
    static createGLESv2Encoder_proc_t createGLESv2EncoderFunc;

    static glActiveTexture_client_proc_t glActiveTextureFunc;
    static glAttachShader_client_proc_t glAttachShaderFunc;
    static glBindAttribLocation_client_proc_t glBindAttribLocationFunc;
    static glBindBuffer_client_proc_t glBindBufferFunc;
    static glBindFramebuffer_client_proc_t glBindFramebufferFunc;
    static glBindRenderbuffer_client_proc_t glBindRenderbufferFunc;
    static glBindTexture_client_proc_t glBindTextureFunc;
    static glBlendColor_client_proc_t glBlendColorFunc;
    static glBlendEquation_client_proc_t glBlendEquationFunc;
    static glBlendEquationSeparate_client_proc_t glBlendEquationSeparateFunc;
    static glBlendFunc_client_proc_t glBlendFuncFunc;
    static glBlendFuncSeparate_client_proc_t glBlendFuncSeparateFunc;
    static glBufferData_client_proc_t glBufferDataFunc;
    static glBufferSubData_client_proc_t glBufferSubDataFunc;
    static glCheckFramebufferStatus_client_proc_t glCheckFramebufferStatusFunc;
    static glClear_client_proc_t glClearFunc;
    static glClearColor_client_proc_t glClearColorFunc;
    static void glActiveTexture_s(void *self, unsigned int texture);
    static void glAttachShader_s(void *self, GLuint program, GLuint shader);
    static void glBindAttribLocation_s(void *self, GLuint program, GLuint index, const GLchar *name);
    static void glBindBuffer_s(void *self, GLenum target, GLuint buffer);
    static void glBindFramebuffer_s(void *self, GLenum target, GLuint framebuffer);
    static void glBindRenderbuffer_s(void *self, GLenum target, GLuint renderbuffer);
    static void glBindTexture_s(void *self, GLenum target, GLuint texture);
    static void glBlendColor_s(void *self, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
    static void glBlendEquation_s(void *self, GLenum mode);
    static void glBlendEquationSeparate_s(void *self, GLenum modeRGB, GLenum modeAlpha);
    static void glBlendFunc_s(void *self, GLenum sfactor, GLenum dfactor);
    static void glBlendFuncSeparate_s(void *self, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
    static void glBufferData_s(void *self, GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
    static void glBufferSubData_s(void *self, GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data);
    static GLenum glCheckFramebufferStatus_s(void *self, GLenum target);
    static void glClear_s(void *self, GLbitfield mask);
    static void glClearColor_s(void *self, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
    glActiveTexture_client_proc_t glActiveTexture = nullptr;
    glAttachShader_client_proc_t glAttachShader = nullptr;
    glBindAttribLocation_client_proc_t glBindAttribLocation = nullptr;
    glBindBuffer_client_proc_t glBindBuffer = nullptr;
    glBindFramebuffer_client_proc_t glBindFramebuffer = nullptr;
    glBindRenderbuffer_client_proc_t glBindRenderbuffer = nullptr;
    glBindTexture_client_proc_t glBindTexture = nullptr;
    glBlendColor_client_proc_t glBlendColor = nullptr;
    glBlendEquation_client_proc_t glBlendEquation = nullptr;
    glBlendEquationSeparate_client_proc_t glBlendEquationSeparate = nullptr;
    glBlendFunc_client_proc_t glBlendFunc = nullptr;
    glBlendFuncSeparate_client_proc_t glBlendFuncSeparate = nullptr;
    glBufferData_client_proc_t glBufferData = nullptr;
    glBufferSubData_client_proc_t glBufferSubData = nullptr;
    glCheckFramebufferStatus_client_proc_t glCheckFramebufferStatus = nullptr;
    glClear_client_proc_t glClear = nullptr;
    glClearColor_client_proc_t glClearColor = nullptr;

private:
    static bool m_isInit;
    static void *m_libHandle;
    void *m_GLESv2Encoder = nullptr;
    std::function<void *(const char *)> m_func = nullptr;
};
#endif // GL2_ENCODER_BASE_H
