/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2017-2021. All rights reserved.
 * Description:  Hook and encode OpenGL ES APIs as stream.
 */

#ifndef VMI_GLES_V2_ENCODER_H
#define VMI_GLES_V2_ENCODER_H

#include "GLESAPIEntryList.h"
#include "VmiPixelDataAlignment.h"
#include "IStream.h"

struct TexImageInfo;
struct TexSubImageInfo;
class BufferWriter;
class VmiUniformLayout;

class VmiGLESv2Encoder {
public:
    // m_stream need to explode to GL2Encoder to call, make it public.
    VmiRebuildStream* m_stream = nullptr;
    // declare all the GLES function pointer members, called by goldfish Opengl, make it public.
    FOREACH_OPENGL_DEDUCE(GLES_DECLARE_MEMBER_DEDUCE)
    FOREACH_OPENGL_MANUAL(GLES_DECLARE_MEMBER_MANUAL)

    /**
     * @brief: VmiGLESv2Encoder constructor function
     * @param [in] stream: server to client stream
     */
    explicit VmiGLESv2Encoder(void* stream);

    /**
     * @brief: VmiGLESv2Encoder destructor function
     */
    virtual ~VmiGLESv2Encoder() = default;

    /**
     * @brief: Hook and encode all the GLES APIs members.
     */
    void InitVmiGLESEntryList();

    VmiPixelDataAlignment GetPixelDataAlignment();

    void PixelDataSetAlignment(uint32_t param, GLint value);

    void SendClientGLTexImage2D(TexImageInfo &texInfo);
    void SendClientGLTexSubImage2D(TexSubImageInfo &texInfo);
    void EncodeBlocks(BufferWriter &writer, VmiUniformLayout &layout);
    uint32_t GetEncodeSize(VmiUniformLayout &layout);
    void EncodeUniforms(BufferWriter &writer, VmiUniformLayout &layout);
    void EncodeUniformLayout(GLuint program, VmiUniformLayout &layout);
    bool InitStateMachine();
    IStream* GetStream();
private:
    VmiPixelDataAlignment m_pixelData = VmiPixelDataAlignment();
    void InitVmiGLESFunPtrs();
    void InitVertexArrayFunPtrs();
    void InitDispatchComputeFunPtrs();
    void InitEGLImageTargetFunPtrs();
    void InitFinishRoundTripFunPtrs();
    void InitFenceFunPtrs();
    void InitPixelFunPtrs();
    void InitTransformFeedbackFunPtrs();
    void InitDrawFunPtrs();
    void InitFramebufferFunPtrs();
    void InitBlendFunPtrs();
    void InitRenderbufferFunPtrs();
    void InitBufferFunPtrs();
    void InitTextureFunPtrs();
    void InitVertexAttribFunPtrs();
    void InitGetFunPtrs();
    void InitUniformFunPtrs();
    void InitProgramFunPtrs();
    void InitSamplerFunPtrs();
    void InitShaderFunPtrs();
    void InitAttribLocationFunPtrs();
    void InitAEMUFunPtrs();
    void InitLocalCallNoRetFunPtrs();
    void InitCallAndEncodeFunPtrs();
    void InitCallAndRetFunPtrs();
    void InitAMDFunPtrs();
    void InitQCOMFunPtrs();
};
#endif // VMI_GLES_V2_ENCODER_H
