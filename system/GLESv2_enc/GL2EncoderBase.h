/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description:  GL2Encoder base class.
 */

#ifndef GL2_ENCODER_BASE_H
#define GL2_ENCODER_BASE_H

#include <string>
#include <vector>
#include <log/log.h>
#include "GLES3/gl32.h"
#include "GLES2/gl2ext.h"
#include "gl2_client_proc.h"

typedef void* (*createGLESv2Encoder_proc_t) (void * stream);

class GL2EncoderBase {
public:
    GL2EncoderBase();
    ~GL2EncoderBase();

    void * GetGLESv2Encoder(void * self);
    bool InitGLESv2Export();

    bool CreateVmiGLESv2Encoder(void * stream);
    static createGLESv2Encoder_proc_t createGLESv2EncoderFunc;

    static glActiveTexture_client_proc_t glActiveTextureFunc;
    static void glActiveTexture_s(void * self, unsigned int texture);
    glActiveTexture_client_proc_t glActiveTexture = nullptr;
private:
    static bool m_isInit;
    static void* m_libHandle;
    void* m_GLESv2Encoder = nullptr;
    std::function<void *(const char *)> m_func = nullptr;
};
#endif // GL2_ENCODER_BASE_H
