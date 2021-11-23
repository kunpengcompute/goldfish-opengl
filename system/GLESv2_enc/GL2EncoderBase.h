/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description:  GL2Encoder base class.
 */

#ifndef GL2_ENCODER_BASE_H
#define GL2_ENCODER_BASE_H

#include <string>
#include <vector>
#include <functional>
#include <mutex>
#include <memory>
#include <log/log.h>
#include "GLES3/gl32.h"
#include "GLES2/gl2ext.h"
#include "gl2_client_proc.h"
#include "LoadSharedLib.h"

typedef void *(*createGLESv2Encoder_proc_t)(void *stream);
typedef void (*deleteGLESv2Encoder_proc_t)(void *self);

class GL2EncoderBase {
public:
    GL2EncoderBase();
    ~GL2EncoderBase();

    void *GetGLESv2Encoder(void *self);
    bool InitGLESv2Export();
    bool CreateVmiGLESv2Encoder(void *stream);
    void DeleteVmiGLESv2Encoder();
    static createGLESv2Encoder_proc_t createGLESv2EncoderFunc;
    static deleteGLESv2Encoder_proc_t deleteGLESv2EncoderFunc;
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
    static glClearDepthf_client_proc_t glClearDepthfFunc;
    static glClearStencil_client_proc_t glClearStencilFunc;
    static glColorMask_client_proc_t glColorMaskFunc;
    static glCompileShader_client_proc_t glCompileShaderFunc;
    static glCompressedTexImage2D_client_proc_t glCompressedTexImage2DFunc;
    static glCompressedTexSubImage2D_client_proc_t glCompressedTexSubImage2DFunc;
    static glCopyTexImage2D_client_proc_t glCopyTexImage2DFunc;
    static glCopyTexSubImage2D_client_proc_t glCopyTexSubImage2DFunc;
    static glCreateProgram_client_proc_t glCreateProgramFunc;
    static glCreateShader_client_proc_t glCreateShaderFunc;
    static glCullFace_client_proc_t glCullFaceFunc;
    static glDeleteBuffers_client_proc_t glDeleteBuffersFunc;
    static glDeleteFramebuffers_client_proc_t glDeleteFramebuffersFunc;
    static glDeleteProgram_client_proc_t glDeleteProgramFunc;
    static glDeleteRenderbuffers_client_proc_t glDeleteRenderbuffersFunc;
    static glDeleteShader_client_proc_t glDeleteShaderFunc;
    static glDeleteTextures_client_proc_t glDeleteTexturesFunc;
    static glDepthFunc_client_proc_t glDepthFuncFunc;
    static glDepthMask_client_proc_t glDepthMaskFunc;
    static glDepthRangef_client_proc_t glDepthRangefFunc;
    static glDetachShader_client_proc_t glDetachShaderFunc;
    static glDisable_client_proc_t glDisableFunc;
    static glDisableVertexAttribArray_client_proc_t glDisableVertexAttribArrayFunc;
    static glDrawArrays_client_proc_t glDrawArraysFunc;
    static glDrawElements_client_proc_t glDrawElementsFunc;
    static glEnable_client_proc_t glEnableFunc;
    static glEnableVertexAttribArray_client_proc_t glEnableVertexAttribArrayFunc;
    static glFlush_client_proc_t glFlushFunc;
    static glFramebufferRenderbuffer_client_proc_t glFramebufferRenderbufferFunc;
    static glFramebufferTexture2D_client_proc_t glFramebufferTexture2DFunc;
    static glFrontFace_client_proc_t glFrontFaceFunc;
    static glGenBuffers_client_proc_t glGenBuffersFunc;
    static glGenerateMipmap_client_proc_t glGenerateMipmapFunc;
    static glGenFramebuffers_client_proc_t glGenFramebuffersFunc;
    static glGenRenderbuffers_client_proc_t glGenRenderbuffersFunc;
    static glGenTextures_client_proc_t glGenTexturesFunc;
    static glGetActiveAttrib_client_proc_t glGetActiveAttribFunc;
    static glGetActiveUniform_client_proc_t glGetActiveUniformFunc;
    static glGetAttachedShaders_client_proc_t glGetAttachedShadersFunc;
    static glGetAttribLocation_client_proc_t glGetAttribLocationFunc;
    static glGetBooleanv_client_proc_t glGetBooleanvFunc;
    static glGetBufferParameteriv_client_proc_t glGetBufferParameterivFunc;
    static glGetError_client_proc_t glGetErrorFunc;
    static glGetFloatv_client_proc_t glGetFloatvFunc;
    static glGetFramebufferAttachmentParameteriv_client_proc_t glGetFramebufferAttachmentParameterivFunc;
    static glGetIntegerv_client_proc_t glGetIntegervFunc;
    static glGetProgramiv_client_proc_t glGetProgramivFunc;
    static glGetProgramInfoLog_client_proc_t glGetProgramInfoLogFunc;
    static glGetRenderbufferParameteriv_client_proc_t glGetRenderbufferParameterivFunc;
    static glGetShaderiv_client_proc_t glGetShaderivFunc;
    static glGetShaderInfoLog_client_proc_t glGetShaderInfoLogFunc;
    static glGetShaderPrecisionFormat_client_proc_t glGetShaderPrecisionFormatFunc;
    static glGetShaderSource_client_proc_t glGetShaderSourceFunc;
    static glGetString_client_proc_t glGetStringFunc;
    static glGetTexParameterfv_client_proc_t glGetTexParameterfvFunc;
    static glGetTexParameteriv_client_proc_t glGetTexParameterivFunc;
    static glGetUniformfv_client_proc_t glGetUniformfvFunc;
    static glGetUniformiv_client_proc_t glGetUniformivFunc;
    static glGetUniformLocation_client_proc_t glGetUniformLocationFunc;
    static glGetVertexAttribfv_client_proc_t glGetVertexAttribfvFunc;
    static glGetVertexAttribiv_client_proc_t glGetVertexAttribivFunc;
    static glGetVertexAttribPointerv_client_proc_t glGetVertexAttribPointervFunc;
    static glHint_client_proc_t glHintFunc;
    static glIsBuffer_client_proc_t glIsBufferFunc;
    static glIsEnabled_client_proc_t glIsEnabledFunc;
    static glIsFramebuffer_client_proc_t glIsFramebufferFunc;
    static glIsProgram_client_proc_t glIsProgramFunc;
    static glIsRenderbuffer_client_proc_t glIsRenderbufferFunc;
    static glIsShader_client_proc_t glIsShaderFunc;
    static glIsTexture_client_proc_t glIsTextureFunc;
    static glLineWidth_client_proc_t glLineWidthFunc;
    static glLinkProgram_client_proc_t glLinkProgramFunc;
    static glPixelStorei_client_proc_t glPixelStoreiFunc;
    static glPolygonOffset_client_proc_t glPolygonOffsetFunc;
    static glReadPixels_client_proc_t glReadPixelsFunc;
    static glReleaseShaderCompiler_client_proc_t glReleaseShaderCompilerFunc;
    static glRenderbufferStorage_client_proc_t glRenderbufferStorageFunc;
    static glSampleCoverage_client_proc_t glSampleCoverageFunc;
    static glScissor_client_proc_t glScissorFunc;
    static glShaderBinary_client_proc_t glShaderBinaryFunc;
    static glShaderSource_client_proc_t glShaderSourceFunc;
    static glStencilFunc_client_proc_t glStencilFuncFunc;
    static glStencilFuncSeparate_client_proc_t glStencilFuncSeparateFunc;
    static glStencilMask_client_proc_t glStencilMaskFunc;
    static glStencilMaskSeparate_client_proc_t glStencilMaskSeparateFunc;
    static glStencilOp_client_proc_t glStencilOpFunc;
    static glStencilOpSeparate_client_proc_t glStencilOpSeparateFunc;
    static glTexImage2D_client_proc_t glTexImage2DFunc;
    static glTexParameterf_client_proc_t glTexParameterfFunc;
    static glTexParameterfv_client_proc_t glTexParameterfvFunc;
    static glTexParameteri_client_proc_t glTexParameteriFunc;
    static glTexParameteriv_client_proc_t glTexParameterivFunc;
    static glTexSubImage2D_client_proc_t glTexSubImage2DFunc;
    static glUniform1f_client_proc_t glUniform1fFunc;
    static glUniform1fv_client_proc_t glUniform1fvFunc;
    static glUniform1i_client_proc_t glUniform1iFunc;
    static glUniform1iv_client_proc_t glUniform1ivFunc;
    static glUniform2f_client_proc_t glUniform2fFunc;
    static glUniform2fv_client_proc_t glUniform2fvFunc;
    static glUniform2i_client_proc_t glUniform2iFunc;
    static glUniform2iv_client_proc_t glUniform2ivFunc;
    static glUniform3f_client_proc_t glUniform3fFunc;
    static glUniform3fv_client_proc_t glUniform3fvFunc;
    static glUniform3i_client_proc_t glUniform3iFunc;
    static glUniform3iv_client_proc_t glUniform3ivFunc;
    static glUniform4f_client_proc_t glUniform4fFunc;
    static glUniform4fv_client_proc_t glUniform4fvFunc;
    static glUniform4i_client_proc_t glUniform4iFunc;
    static glUniform4iv_client_proc_t glUniform4ivFunc;
    static glUniformMatrix2fv_client_proc_t glUniformMatrix2fvFunc;
    static glUniformMatrix3fv_client_proc_t glUniformMatrix3fvFunc;
    static glUniformMatrix4fv_client_proc_t glUniformMatrix4fvFunc;
    static glUseProgram_client_proc_t glUseProgramFunc;
    static glValidateProgram_client_proc_t glValidateProgramFunc;
    static glVertexAttrib1f_client_proc_t glVertexAttrib1fFunc;
    static glVertexAttrib1fv_client_proc_t glVertexAttrib1fvFunc;
    static glVertexAttrib2f_client_proc_t glVertexAttrib2fFunc;
    static glVertexAttrib2fv_client_proc_t glVertexAttrib2fvFunc;
    static glVertexAttrib3f_client_proc_t glVertexAttrib3fFunc;
    static glVertexAttrib3fv_client_proc_t glVertexAttrib3fvFunc;
    static glVertexAttrib4f_client_proc_t glVertexAttrib4fFunc;
    static glVertexAttrib4fv_client_proc_t glVertexAttrib4fvFunc;
    static glVertexAttribPointer_client_proc_t glVertexAttribPointerFunc;
    static glViewport_client_proc_t glViewportFunc;
    static glEGLImageTargetTexture2DOES_client_proc_t glEGLImageTargetTexture2DOESFunc;
    static glEGLImageTargetRenderbufferStorageOES_client_proc_t glEGLImageTargetRenderbufferStorageOESFunc;
    static glGetProgramBinaryOES_client_proc_t glGetProgramBinaryOESFunc;
    static glProgramBinaryOES_client_proc_t glProgramBinaryOESFunc;
    static glMapBufferOES_client_proc_t glMapBufferOESFunc;
    static glUnmapBufferOES_client_proc_t glUnmapBufferOESFunc;
    static glTexImage3DOES_client_proc_t glTexImage3DOESFunc;
    static glTexSubImage3DOES_client_proc_t glTexSubImage3DOESFunc;
    static glCopyTexSubImage3DOES_client_proc_t glCopyTexSubImage3DOESFunc;
    static glCompressedTexImage3DOES_client_proc_t glCompressedTexImage3DOESFunc;
    static glCompressedTexSubImage3DOES_client_proc_t glCompressedTexSubImage3DOESFunc;
    static glFramebufferTexture3DOES_client_proc_t glFramebufferTexture3DOESFunc;
    static glBindVertexArrayOES_client_proc_t glBindVertexArrayOESFunc;
    static glDeleteVertexArraysOES_client_proc_t glDeleteVertexArraysOESFunc;
    static glGenVertexArraysOES_client_proc_t glGenVertexArraysOESFunc;
    static glIsVertexArrayOES_client_proc_t glIsVertexArrayOESFunc;
    static glDiscardFramebufferEXT_client_proc_t glDiscardFramebufferEXTFunc;
    static glMultiDrawArraysEXT_client_proc_t glMultiDrawArraysEXTFunc;
    static glMultiDrawElementsEXT_client_proc_t glMultiDrawElementsEXTFunc;
    static glGetPerfMonitorGroupsAMD_client_proc_t glGetPerfMonitorGroupsAMDFunc;
    static glGetPerfMonitorCountersAMD_client_proc_t glGetPerfMonitorCountersAMDFunc;
    static glGetPerfMonitorGroupStringAMD_client_proc_t glGetPerfMonitorGroupStringAMDFunc;
    static glGetPerfMonitorCounterStringAMD_client_proc_t glGetPerfMonitorCounterStringAMDFunc;
    static glGetPerfMonitorCounterInfoAMD_client_proc_t glGetPerfMonitorCounterInfoAMDFunc;
    static glGenPerfMonitorsAMD_client_proc_t glGenPerfMonitorsAMDFunc;
    static glDeletePerfMonitorsAMD_client_proc_t glDeletePerfMonitorsAMDFunc;
    static glSelectPerfMonitorCountersAMD_client_proc_t glSelectPerfMonitorCountersAMDFunc;
    static glBeginPerfMonitorAMD_client_proc_t glBeginPerfMonitorAMDFunc;
    static glEndPerfMonitorAMD_client_proc_t glEndPerfMonitorAMDFunc;
    static glGetPerfMonitorCounterDataAMD_client_proc_t glGetPerfMonitorCounterDataAMDFunc;
    static glRenderbufferStorageMultisampleIMG_client_proc_t glRenderbufferStorageMultisampleIMGFunc;
    static glFramebufferTexture2DMultisampleIMG_client_proc_t glFramebufferTexture2DMultisampleIMGFunc;
    static glDeleteFencesNV_client_proc_t glDeleteFencesNVFunc;
    static glGenFencesNV_client_proc_t glGenFencesNVFunc;
    static glIsFenceNV_client_proc_t glIsFenceNVFunc;
    static glTestFenceNV_client_proc_t glTestFenceNVFunc;
    static glGetFenceivNV_client_proc_t glGetFenceivNVFunc;
    static glFinishFenceNV_client_proc_t glFinishFenceNVFunc;
    static glSetFenceNV_client_proc_t glSetFenceNVFunc;
    static glCoverageMaskNV_client_proc_t glCoverageMaskNVFunc;
    static glCoverageOperationNV_client_proc_t glCoverageOperationNVFunc;
    static glGetDriverControlsQCOM_client_proc_t glGetDriverControlsQCOMFunc;
    static glGetDriverControlStringQCOM_client_proc_t glGetDriverControlStringQCOMFunc;
    static glEnableDriverControlQCOM_client_proc_t glEnableDriverControlQCOMFunc;
    static glDisableDriverControlQCOM_client_proc_t glDisableDriverControlQCOMFunc;
    static glExtGetTexturesQCOM_client_proc_t glExtGetTexturesQCOMFunc;
    static glExtGetBuffersQCOM_client_proc_t glExtGetBuffersQCOMFunc;
    static glExtGetRenderbuffersQCOM_client_proc_t glExtGetRenderbuffersQCOMFunc;
    static glExtGetFramebuffersQCOM_client_proc_t glExtGetFramebuffersQCOMFunc;
    static glExtGetTexLevelParameterivQCOM_client_proc_t glExtGetTexLevelParameterivQCOMFunc;
    static glExtTexObjectStateOverrideiQCOM_client_proc_t glExtTexObjectStateOverrideiQCOMFunc;
    static glExtGetTexSubImageQCOM_client_proc_t glExtGetTexSubImageQCOMFunc;
    static glExtGetBufferPointervQCOM_client_proc_t glExtGetBufferPointervQCOMFunc;
    static glExtGetShadersQCOM_client_proc_t glExtGetShadersQCOMFunc;
    static glExtGetProgramsQCOM_client_proc_t glExtGetProgramsQCOMFunc;
    static glExtIsProgramBinaryQCOM_client_proc_t glExtIsProgramBinaryQCOMFunc;
    static glExtGetProgramBinarySourceQCOM_client_proc_t glExtGetProgramBinarySourceQCOMFunc;
    static glStartTilingQCOM_client_proc_t glStartTilingQCOMFunc;
    static glEndTilingQCOM_client_proc_t glEndTilingQCOMFunc;
    static glGenVertexArrays_client_proc_t glGenVertexArraysFunc;
    static glBindVertexArray_client_proc_t glBindVertexArrayFunc;
    static glDeleteVertexArrays_client_proc_t glDeleteVertexArraysFunc;
    static glIsVertexArray_client_proc_t glIsVertexArrayFunc;
    static glMapBufferRange_client_proc_t glMapBufferRangeFunc;
    static glUnmapBuffer_client_proc_t glUnmapBufferFunc;
    static glFlushMappedBufferRange_client_proc_t glFlushMappedBufferRangeFunc;
    static glBindBufferRange_client_proc_t glBindBufferRangeFunc;
    static glBindBufferBase_client_proc_t glBindBufferBaseFunc;
    static glCopyBufferSubData_client_proc_t glCopyBufferSubDataFunc;
    static glClearBufferiv_client_proc_t glClearBufferivFunc;
    static glClearBufferuiv_client_proc_t glClearBufferuivFunc;
    static glClearBufferfv_client_proc_t glClearBufferfvFunc;
    static glClearBufferfi_client_proc_t glClearBufferfiFunc;
    static glGetBufferParameteri64v_client_proc_t glGetBufferParameteri64vFunc;
    static glGetBufferPointerv_client_proc_t glGetBufferPointervFunc;
    static glUniformBlockBinding_client_proc_t glUniformBlockBindingFunc;
    static glGetUniformBlockIndex_client_proc_t glGetUniformBlockIndexFunc;
    static glGetUniformIndices_client_proc_t glGetUniformIndicesFunc;
    static glGetActiveUniformBlockiv_client_proc_t glGetActiveUniformBlockivFunc;
    static glGetActiveUniformBlockName_client_proc_t glGetActiveUniformBlockNameFunc;
    static glUniform1ui_client_proc_t glUniform1uiFunc;
    static glUniform2ui_client_proc_t glUniform2uiFunc;
    static glUniform3ui_client_proc_t glUniform3uiFunc;
    static glUniform4ui_client_proc_t glUniform4uiFunc;
    static glUniform1uiv_client_proc_t glUniform1uivFunc;
    static glUniform2uiv_client_proc_t glUniform2uivFunc;
    static glUniform3uiv_client_proc_t glUniform3uivFunc;
    static glUniform4uiv_client_proc_t glUniform4uivFunc;
    static glUniformMatrix2x3fv_client_proc_t glUniformMatrix2x3fvFunc;
    static glUniformMatrix3x2fv_client_proc_t glUniformMatrix3x2fvFunc;
    static glUniformMatrix2x4fv_client_proc_t glUniformMatrix2x4fvFunc;
    static glUniformMatrix4x2fv_client_proc_t glUniformMatrix4x2fvFunc;
    static glUniformMatrix3x4fv_client_proc_t glUniformMatrix3x4fvFunc;
    static glUniformMatrix4x3fv_client_proc_t glUniformMatrix4x3fvFunc;
    static glGetUniformuiv_client_proc_t glGetUniformuivFunc;
    static glGetActiveUniformsiv_client_proc_t glGetActiveUniformsivFunc;
    static glVertexAttribI4i_client_proc_t glVertexAttribI4iFunc;
    static glVertexAttribI4ui_client_proc_t glVertexAttribI4uiFunc;
    static glVertexAttribI4iv_client_proc_t glVertexAttribI4ivFunc;
    static glVertexAttribI4uiv_client_proc_t glVertexAttribI4uivFunc;
    static glVertexAttribIPointer_client_proc_t glVertexAttribIPointerFunc;
    static glGetVertexAttribIiv_client_proc_t glGetVertexAttribIivFunc;
    static glGetVertexAttribIuiv_client_proc_t glGetVertexAttribIuivFunc;
    static glVertexAttribDivisor_client_proc_t glVertexAttribDivisorFunc;
    static glDrawArraysInstanced_client_proc_t glDrawArraysInstancedFunc;
    static glDrawElementsInstanced_client_proc_t glDrawElementsInstancedFunc;
    static glDrawRangeElements_client_proc_t glDrawRangeElementsFunc;
    static glFenceSync_client_proc_t glFenceSyncFunc;
    static glClientWaitSync_client_proc_t glClientWaitSyncFunc;
    static glWaitSync_client_proc_t glWaitSyncFunc;
    static glDeleteSync_client_proc_t glDeleteSyncFunc;
    static glIsSync_client_proc_t glIsSyncFunc;
    static glGetSynciv_client_proc_t glGetSyncivFunc;
    static glDrawBuffers_client_proc_t glDrawBuffersFunc;
    static glReadBuffer_client_proc_t glReadBufferFunc;
    static glBlitFramebuffer_client_proc_t glBlitFramebufferFunc;
    static glInvalidateFramebuffer_client_proc_t glInvalidateFramebufferFunc;
    static glInvalidateSubFramebuffer_client_proc_t glInvalidateSubFramebufferFunc;
    static glFramebufferTextureLayer_client_proc_t glFramebufferTextureLayerFunc;
    static glRenderbufferStorageMultisample_client_proc_t glRenderbufferStorageMultisampleFunc;
    static glTexStorage2D_client_proc_t glTexStorage2DFunc;
    static glGetInternalformativ_client_proc_t glGetInternalformativFunc;
    static glBeginTransformFeedback_client_proc_t glBeginTransformFeedbackFunc;
    static glEndTransformFeedback_client_proc_t glEndTransformFeedbackFunc;
    static glGenTransformFeedbacks_client_proc_t glGenTransformFeedbacksFunc;
    static glDeleteTransformFeedbacks_client_proc_t glDeleteTransformFeedbacksFunc;
    static glBindTransformFeedback_client_proc_t glBindTransformFeedbackFunc;
    static glPauseTransformFeedback_client_proc_t glPauseTransformFeedbackFunc;
    static glResumeTransformFeedback_client_proc_t glResumeTransformFeedbackFunc;
    static glIsTransformFeedback_client_proc_t glIsTransformFeedbackFunc;
    static glTransformFeedbackVaryings_client_proc_t glTransformFeedbackVaryingsFunc;
    static glGetTransformFeedbackVarying_client_proc_t glGetTransformFeedbackVaryingFunc;
    static glGenSamplers_client_proc_t glGenSamplersFunc;
    static glDeleteSamplers_client_proc_t glDeleteSamplersFunc;
    static glBindSampler_client_proc_t glBindSamplerFunc;
    static glSamplerParameterf_client_proc_t glSamplerParameterfFunc;
    static glSamplerParameteri_client_proc_t glSamplerParameteriFunc;
    static glSamplerParameterfv_client_proc_t glSamplerParameterfvFunc;
    static glSamplerParameteriv_client_proc_t glSamplerParameterivFunc;
    static glGetSamplerParameterfv_client_proc_t glGetSamplerParameterfvFunc;
    static glGetSamplerParameteriv_client_proc_t glGetSamplerParameterivFunc;
    static glIsSampler_client_proc_t glIsSamplerFunc;
    static glGenQueries_client_proc_t glGenQueriesFunc;
    static glDeleteQueries_client_proc_t glDeleteQueriesFunc;
    static glBeginQuery_client_proc_t glBeginQueryFunc;
    static glEndQuery_client_proc_t glEndQueryFunc;
    static glGetQueryiv_client_proc_t glGetQueryivFunc;
    static glGetQueryObjectuiv_client_proc_t glGetQueryObjectuivFunc;
    static glIsQuery_client_proc_t glIsQueryFunc;
    static glProgramParameteri_client_proc_t glProgramParameteriFunc;
    static glProgramBinary_client_proc_t glProgramBinaryFunc;
    static glGetProgramBinary_client_proc_t glGetProgramBinaryFunc;
    static glGetFragDataLocation_client_proc_t glGetFragDataLocationFunc;
    static glGetInteger64v_client_proc_t glGetInteger64vFunc;
    static glGetIntegeri_v_client_proc_t glGetIntegeri_vFunc;
    static glGetInteger64i_v_client_proc_t glGetInteger64i_vFunc;
    static glTexImage3D_client_proc_t glTexImage3DFunc;
    static glTexStorage3D_client_proc_t glTexStorage3DFunc;
    static glTexSubImage3D_client_proc_t glTexSubImage3DFunc;
    static glCompressedTexImage3D_client_proc_t glCompressedTexImage3DFunc;
    static glCompressedTexSubImage3D_client_proc_t glCompressedTexSubImage3DFunc;
    static glCopyTexSubImage3D_client_proc_t glCopyTexSubImage3DFunc;
    static glGetStringi_client_proc_t glGetStringiFunc;
    static glGetBooleani_v_client_proc_t glGetBooleani_vFunc;
    static glMemoryBarrier_client_proc_t glMemoryBarrierFunc;
    static glMemoryBarrierByRegion_client_proc_t glMemoryBarrierByRegionFunc;
    static glGenProgramPipelines_client_proc_t glGenProgramPipelinesFunc;
    static glDeleteProgramPipelines_client_proc_t glDeleteProgramPipelinesFunc;
    static glBindProgramPipeline_client_proc_t glBindProgramPipelineFunc;
    static glGetProgramPipelineiv_client_proc_t glGetProgramPipelineivFunc;
    static glGetProgramPipelineInfoLog_client_proc_t glGetProgramPipelineInfoLogFunc;
    static glValidateProgramPipeline_client_proc_t glValidateProgramPipelineFunc;
    static glIsProgramPipeline_client_proc_t glIsProgramPipelineFunc;
    static glUseProgramStages_client_proc_t glUseProgramStagesFunc;
    static glActiveShaderProgram_client_proc_t glActiveShaderProgramFunc;
    static glCreateShaderProgramv_client_proc_t glCreateShaderProgramvFunc;
    static glProgramUniform1f_client_proc_t glProgramUniform1fFunc;
    static glProgramUniform2f_client_proc_t glProgramUniform2fFunc;
    static glProgramUniform3f_client_proc_t glProgramUniform3fFunc;
    static glProgramUniform4f_client_proc_t glProgramUniform4fFunc;
    static glProgramUniform1i_client_proc_t glProgramUniform1iFunc;
    static glProgramUniform2i_client_proc_t glProgramUniform2iFunc;
    static glProgramUniform3i_client_proc_t glProgramUniform3iFunc;
    static glProgramUniform4i_client_proc_t glProgramUniform4iFunc;
    static glProgramUniform1ui_client_proc_t glProgramUniform1uiFunc;
    static glProgramUniform2ui_client_proc_t glProgramUniform2uiFunc;
    static glProgramUniform3ui_client_proc_t glProgramUniform3uiFunc;
    static glProgramUniform4ui_client_proc_t glProgramUniform4uiFunc;
    static glProgramUniform1fv_client_proc_t glProgramUniform1fvFunc;
    static glProgramUniform2fv_client_proc_t glProgramUniform2fvFunc;
    static glProgramUniform3fv_client_proc_t glProgramUniform3fvFunc;
    static glProgramUniform4fv_client_proc_t glProgramUniform4fvFunc;
    static glProgramUniform1iv_client_proc_t glProgramUniform1ivFunc;
    static glProgramUniform2iv_client_proc_t glProgramUniform2ivFunc;
    static glProgramUniform3iv_client_proc_t glProgramUniform3ivFunc;
    static glProgramUniform4iv_client_proc_t glProgramUniform4ivFunc;
    static glProgramUniform1uiv_client_proc_t glProgramUniform1uivFunc;
    static glProgramUniform2uiv_client_proc_t glProgramUniform2uivFunc;
    static glProgramUniform3uiv_client_proc_t glProgramUniform3uivFunc;
    static glProgramUniform4uiv_client_proc_t glProgramUniform4uivFunc;
    static glProgramUniformMatrix2fv_client_proc_t glProgramUniformMatrix2fvFunc;
    static glProgramUniformMatrix3fv_client_proc_t glProgramUniformMatrix3fvFunc;
    static glProgramUniformMatrix4fv_client_proc_t glProgramUniformMatrix4fvFunc;
    static glProgramUniformMatrix2x3fv_client_proc_t glProgramUniformMatrix2x3fvFunc;
    static glProgramUniformMatrix3x2fv_client_proc_t glProgramUniformMatrix3x2fvFunc;
    static glProgramUniformMatrix2x4fv_client_proc_t glProgramUniformMatrix2x4fvFunc;
    static glProgramUniformMatrix4x2fv_client_proc_t glProgramUniformMatrix4x2fvFunc;
    static glProgramUniformMatrix3x4fv_client_proc_t glProgramUniformMatrix3x4fvFunc;
    static glProgramUniformMatrix4x3fv_client_proc_t glProgramUniformMatrix4x3fvFunc;
    static glGetProgramInterfaceiv_client_proc_t glGetProgramInterfaceivFunc;
    static glGetProgramResourceiv_client_proc_t glGetProgramResourceivFunc;
    static glGetProgramResourceIndex_client_proc_t glGetProgramResourceIndexFunc;
    static glGetProgramResourceLocation_client_proc_t glGetProgramResourceLocationFunc;
    static glGetProgramResourceName_client_proc_t glGetProgramResourceNameFunc;
    static glBindImageTexture_client_proc_t glBindImageTextureFunc;
    static glDispatchCompute_client_proc_t glDispatchComputeFunc;
    static glDispatchComputeIndirect_client_proc_t glDispatchComputeIndirectFunc;
    static glBindVertexBuffer_client_proc_t glBindVertexBufferFunc;
    static glVertexAttribBinding_client_proc_t glVertexAttribBindingFunc;
    static glVertexAttribFormat_client_proc_t glVertexAttribFormatFunc;
    static glVertexAttribIFormat_client_proc_t glVertexAttribIFormatFunc;
    static glVertexBindingDivisor_client_proc_t glVertexBindingDivisorFunc;
    static glDrawArraysIndirect_client_proc_t glDrawArraysIndirectFunc;
    static glDrawElementsIndirect_client_proc_t glDrawElementsIndirectFunc;
    static glTexStorage2DMultisample_client_proc_t glTexStorage2DMultisampleFunc;
    static glSampleMaski_client_proc_t glSampleMaskiFunc;
    static glGetMultisamplefv_client_proc_t glGetMultisamplefvFunc;
    static glFramebufferParameteri_client_proc_t glFramebufferParameteriFunc;
    static glGetFramebufferParameteriv_client_proc_t glGetFramebufferParameterivFunc;
    static glGetTexLevelParameterfv_client_proc_t glGetTexLevelParameterfvFunc;
    static glGetTexLevelParameteriv_client_proc_t glGetTexLevelParameterivFunc;
    static glEnableiEXT_client_proc_t glEnableiEXTFunc;
    static glDisableiEXT_client_proc_t glDisableiEXTFunc;
    static glBlendEquationiEXT_client_proc_t glBlendEquationiEXTFunc;
    static glBlendEquationSeparateiEXT_client_proc_t glBlendEquationSeparateiEXTFunc;
    static glBlendFunciEXT_client_proc_t glBlendFunciEXTFunc;
    static glBlendFuncSeparateiEXT_client_proc_t glBlendFuncSeparateiEXTFunc;
    static glColorMaskiEXT_client_proc_t glColorMaskiEXTFunc;
    static glIsEnablediEXT_client_proc_t glIsEnablediEXTFunc;
    static glCopyImageSubDataEXT_client_proc_t glCopyImageSubDataEXTFunc;
    static glBlendBarrierKHR_client_proc_t glBlendBarrierKHRFunc;
    static glTexParameterIivEXT_client_proc_t glTexParameterIivEXTFunc;
    static glTexParameterIuivEXT_client_proc_t glTexParameterIuivEXTFunc;
    static glGetTexParameterIivEXT_client_proc_t glGetTexParameterIivEXTFunc;
    static glGetTexParameterIuivEXT_client_proc_t glGetTexParameterIuivEXTFunc;
    static glSamplerParameterIivEXT_client_proc_t glSamplerParameterIivEXTFunc;
    static glSamplerParameterIuivEXT_client_proc_t glSamplerParameterIuivEXTFunc;
    static glGetSamplerParameterIivEXT_client_proc_t glGetSamplerParameterIivEXTFunc;
    static glGetSamplerParameterIuivEXT_client_proc_t glGetSamplerParameterIuivEXTFunc;
    static glVertexAttribPointerData_client_proc_t glVertexAttribPointerDataFunc;
    static glVertexAttribPointerOffset_client_proc_t glVertexAttribPointerOffsetFunc;
    static glDrawElementsOffset_client_proc_t glDrawElementsOffsetFunc;
    static glDrawElementsData_client_proc_t glDrawElementsDataFunc;
    static glGetCompressedTextureFormats_client_proc_t glGetCompressedTextureFormatsFunc;
    static glShaderString_client_proc_t glShaderStringFunc;
    static glFinishRoundTrip_client_proc_t glFinishRoundTripFunc;
    static glMapBufferRangeAEMU_client_proc_t glMapBufferRangeAEMUFunc;
    static glUnmapBufferAEMU_client_proc_t glUnmapBufferAEMUFunc;
    static glFlushMappedBufferRangeAEMU_client_proc_t glFlushMappedBufferRangeAEMUFunc;
    static glReadPixelsOffsetAEMU_client_proc_t glReadPixelsOffsetAEMUFunc;
    static glCompressedTexImage2DOffsetAEMU_client_proc_t glCompressedTexImage2DOffsetAEMUFunc;
    static glCompressedTexSubImage2DOffsetAEMU_client_proc_t glCompressedTexSubImage2DOffsetAEMUFunc;
    static glTexImage2DOffsetAEMU_client_proc_t glTexImage2DOffsetAEMUFunc;
    static glTexSubImage2DOffsetAEMU_client_proc_t glTexSubImage2DOffsetAEMUFunc;
    static glGetUniformIndicesAEMU_client_proc_t glGetUniformIndicesAEMUFunc;
    static glVertexAttribIPointerOffsetAEMU_client_proc_t glVertexAttribIPointerOffsetAEMUFunc;
    static glVertexAttribIPointerDataAEMU_client_proc_t glVertexAttribIPointerDataAEMUFunc;
    static glDrawElementsInstancedDataAEMU_client_proc_t glDrawElementsInstancedDataAEMUFunc;
    static glDrawElementsInstancedOffsetAEMU_client_proc_t glDrawElementsInstancedOffsetAEMUFunc;
    static glDrawRangeElementsDataAEMU_client_proc_t glDrawRangeElementsDataAEMUFunc;
    static glDrawRangeElementsOffsetAEMU_client_proc_t glDrawRangeElementsOffsetAEMUFunc;
    static glFenceSyncAEMU_client_proc_t glFenceSyncAEMUFunc;
    static glClientWaitSyncAEMU_client_proc_t glClientWaitSyncAEMUFunc;
    static glWaitSyncAEMU_client_proc_t glWaitSyncAEMUFunc;
    static glDeleteSyncAEMU_client_proc_t glDeleteSyncAEMUFunc;
    static glIsSyncAEMU_client_proc_t glIsSyncAEMUFunc;
    static glGetSyncivAEMU_client_proc_t glGetSyncivAEMUFunc;
    static glTransformFeedbackVaryingsAEMU_client_proc_t glTransformFeedbackVaryingsAEMUFunc;
    static glTexImage3DOffsetAEMU_client_proc_t glTexImage3DOffsetAEMUFunc;
    static glTexSubImage3DOffsetAEMU_client_proc_t glTexSubImage3DOffsetAEMUFunc;
    static glCompressedTexImage3DOffsetAEMU_client_proc_t glCompressedTexImage3DOffsetAEMUFunc;
    static glCompressedTexSubImage3DOffsetAEMU_client_proc_t glCompressedTexSubImage3DOffsetAEMUFunc;
    static glCreateShaderProgramvAEMU_client_proc_t glCreateShaderProgramvAEMUFunc;
    static glDrawArraysIndirectDataAEMU_client_proc_t glDrawArraysIndirectDataAEMUFunc;
    static glDrawArraysIndirectOffsetAEMU_client_proc_t glDrawArraysIndirectOffsetAEMUFunc;
    static glDrawElementsIndirectDataAEMU_client_proc_t glDrawElementsIndirectDataAEMUFunc;
    static glDrawElementsIndirectOffsetAEMU_client_proc_t glDrawElementsIndirectOffsetAEMUFunc;
    static glUniformLayout_client_proc_t glUniformLayoutFunc;
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
    static void glClearDepthf_s(void *self, GLfloat d);
    static void glClearStencil_s(void *self, GLint s);
    static void glColorMask_s(void *self, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
    static void glCompileShader_s(void *self, GLuint shader);
    static void glCompressedTexImage2D_s(void *self, GLenum target, GLint level, GLenum internalformat, GLsizei width,
        GLsizei height, GLint border, GLsizei imageSize, const void *data);
    static void glCompressedTexSubImage2D_s(void *self, GLenum target, GLint level, GLint xoffset, GLint yoffset,
        GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
    static void glCopyTexImage2D_s(void *self, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y,
        GLsizei width, GLsizei height, GLint border);
    static void glCopyTexSubImage2D_s(void *self, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x,
        GLint y, GLsizei width, GLsizei height);
    static GLuint glCreateProgram_s(void *self);
    static GLuint glCreateShader_s(void *self, GLenum type);
    static void glCullFace_s(void *self, GLenum mode);
    static void glDeleteBuffers_s(void *self, GLsizei n, const GLuint *buffers);
    static void glDeleteFramebuffers_s(void *self, GLsizei n, const GLuint *framebuffers);
    static void glDeleteProgram_s(void *self, GLuint program);
    static void glDeleteRenderbuffers_s(void *self, GLsizei n, const GLuint *renderbuffers);
    static void glDeleteShader_s(void *self, GLuint shader);
    static void glDeleteTextures_s(void *self, GLsizei n, const GLuint *textures);
    static void glDepthFunc_s(void *self, GLenum func);
    static void glDepthMask_s(void *self, GLboolean flag);
    static void glDepthRangef_s(void *self, GLclampf zNear, GLclampf zFar);
    static void glDetachShader_s(void *self, GLuint program, GLuint shader);
    static void glDisable_s(void *self, GLenum cap);
    static void glDisableVertexAttribArray_s(void *self, GLuint index);
    static void glDrawArrays_s(void *self, GLenum mode, GLint first, GLsizei count);
    static void glDrawElements_s(void *self, GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
    static void glEnable_s(void *self, GLenum cap);
    static void glEnableVertexAttribArray_s(void *self, GLuint index);
    static void glFlush_s(void *self);
    static void glFramebufferRenderbuffer_s(void *self, GLenum target, GLenum attachment, GLenum renderbuffertarget,
        GLuint renderbuffer);
    static void glFramebufferTexture2D_s(void *self, GLenum target, GLenum attachment, GLenum textarget, GLuint texture,
        GLint level);
    static void glFrontFace_s(void *self, GLenum mode);
    static void glGenBuffers_s(void *self, GLsizei n, GLuint *buffers);
    static void glGenerateMipmap_s(void *self, GLenum target);
    static void glGenFramebuffers_s(void *self, GLsizei n, GLuint *framebuffers);
    static void glGenRenderbuffers_s(void *self, GLsizei n, GLuint *renderbuffers);
    static void glGenTextures_s(void *self, GLsizei n, GLuint *textures);
    static void glGetActiveAttrib_s(void *self, GLuint program, GLuint index, GLsizei bufsize, GLsizei *length,
        GLint *size, GLenum *type, GLchar *name);
    static void glGetActiveUniform_s(void *self, GLuint program, GLuint index, GLsizei bufsize, GLsizei *length,
        GLint *size, GLenum *type, GLchar *name);
    static void glGetAttachedShaders_s(void *self, GLuint program, GLsizei maxcount, GLsizei *count, GLuint *shaders);
    static int glGetAttribLocation_s(void *self, GLuint program, const GLchar *name);
    static void glGetBooleanv_s(void *self, GLenum pname, GLboolean *params);
    static void glGetBufferParameteriv_s(void *self, GLenum target, GLenum pname, GLint *params);
    static GLenum glGetError_s(void *self);
    static void glGetFloatv_s(void *self, GLenum pname, GLfloat *params);
    static void glGetFramebufferAttachmentParameteriv_s(void *self, GLenum target, GLenum attachment, GLenum pname,
        GLint *params);
    static void glGetIntegerv_s(void *self, GLenum pname, GLint *params);
    static void glGetProgramiv_s(void *self, GLuint program, GLenum pname, GLint *params);
    static void glGetProgramInfoLog_s(void *self, GLuint program, GLsizei bufsize, GLsizei *length, GLchar *infolog);
    static void glGetRenderbufferParameteriv_s(void *self, GLenum target, GLenum pname, GLint *params);
    static void glGetShaderiv_s(void *self, GLuint shader, GLenum pname, GLint *params);
    static void glGetShaderInfoLog_s(void *self, GLuint shader, GLsizei bufsize, GLsizei *length, GLchar *infolog);
    static void glGetShaderPrecisionFormat_s(void *self, GLenum shadertype, GLenum precisiontype, GLint *range,
        GLint *precision);
    static void glGetShaderSource_s(void *self, GLuint shader, GLsizei bufsize, GLsizei *length, GLchar *source);
    static const GLubyte * glGetString_s(void *self, GLenum name);
    static void glGetTexParameterfv_s(void *self, GLenum target, GLenum pname, GLfloat *params);
    static void glGetTexParameteriv_s(void *self, GLenum target, GLenum pname, GLint *params);
    static void glGetUniformfv_s(void *self, GLuint program, GLint location, GLfloat *params);
    static void glGetUniformiv_s(void *self, GLuint program, GLint location, GLint *params);
    static GLint glGetUniformLocation_s(void *self, GLuint program, const GLchar *name);
    static void glGetVertexAttribfv_s(void *self, GLuint index, GLenum pname, GLfloat *params);
    static void glGetVertexAttribiv_s(void *self, GLuint index, GLenum pname, GLint *params);
    static void glGetVertexAttribPointerv_s(void *self, GLuint index, GLenum pname, void **pointer);
    static void glHint_s(void *self, GLenum target, GLenum mode);
    static GLboolean glIsBuffer_s(void *self, GLuint buffer);
    static GLboolean glIsEnabled_s(void *self, GLenum cap);
    static GLboolean glIsFramebuffer_s(void *self, GLuint framebuffer);
    static GLboolean glIsProgram_s(void *self, GLuint program);
    static GLboolean glIsRenderbuffer_s(void *self, GLuint renderbuffer);
    static GLboolean glIsShader_s(void *self, GLuint shader);
    static GLboolean glIsTexture_s(void *self, GLuint texture);
    static void glLineWidth_s(void *self, GLfloat width);
    static void glLinkProgram_s(void *self, GLuint program);
    static void glPixelStorei_s(void *self, GLenum pname, GLint param);
    static void glPolygonOffset_s(void *self, GLfloat factor, GLfloat units);
    static void glReadPixels_s(void *self, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type,
        void *pixels);
    static void glReleaseShaderCompiler_s(void *self);
    static void glRenderbufferStorage_s(void *self, GLenum target, GLenum internalformat, GLsizei width,
        GLsizei height);
    static void glSampleCoverage_s(void *self, GLfloat value, GLboolean invert);
    static void glScissor_s(void *self, GLint x, GLint y, GLsizei width, GLsizei height);
    static void glShaderBinary_s(void *self, GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length);
    static void glShaderSource_s(void *self, GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
    static void glStencilFunc_s(void *self, GLenum func, GLint ref, GLuint mask);
    static void glStencilFuncSeparate_s(void *self, GLenum face, GLenum func, GLint ref, GLuint mask);
    static void glStencilMask_s(void *self, GLuint mask);
    static void glStencilMaskSeparate_s(void *self, GLenum face, GLuint mask);
    static void glStencilOp_s(void *self, GLenum fail, GLenum zfail, GLenum zpass);
    static void glStencilOpSeparate_s(void *self, GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
    static void glTexImage2D_s(void *self, GLenum target, GLint level, GLint internalformat, GLsizei width,
        GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
    static void glTexParameterf_s(void *self, GLenum target, GLenum pname, GLfloat param);
    static void glTexParameterfv_s(void *self, GLenum target, GLenum pname, const GLfloat *params);
    static void glTexParameteri_s(void *self, GLenum target, GLenum pname, GLint param);
    static void glTexParameteriv_s(void *self, GLenum target, GLenum pname, const GLint *params);
    static void glTexSubImage2D_s(void *self, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width,
        GLsizei height, GLenum format, GLenum type, const void *pixels);
    static void glUniform1f_s(void *self, GLint location, GLfloat v0);
    static void glUniform1fv_s(void *self, GLint location, GLsizei count, const GLfloat *value);
    static void glUniform1i_s(void *self, GLint location, GLint v0);
    static void glUniform1iv_s(void *self, GLint location, GLsizei count, const GLint *value);
    static void glUniform2f_s(void *self, GLint location, GLfloat v0, GLfloat v1);
    static void glUniform2fv_s(void *self, GLint location, GLsizei count, const GLfloat *value);
    static void glUniform2i_s(void *self, GLint location, GLint v0, GLint v1);
    static void glUniform2iv_s(void *self, GLint location, GLsizei count, const GLint *value);
    static void glUniform3f_s(void *self, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
    static void glUniform3fv_s(void *self, GLint location, GLsizei count, const GLfloat *value);
    static void glUniform3i_s(void *self, GLint location, GLint v0, GLint v1, GLint v2);
    static void glUniform3iv_s(void *self, GLint location, GLsizei count, const GLint *value);
    static void glUniform4f_s(void *self, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
    static void glUniform4fv_s(void *self, GLint location, GLsizei count, const GLfloat *value);
    static void glUniform4i_s(void *self, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
    static void glUniform4iv_s(void *self, GLint location, GLsizei count, const GLint *value);
    static void glUniformMatrix2fv_s(void *self, GLint location, GLsizei count, GLboolean transpose,
        const GLfloat *value);
    static void glUniformMatrix3fv_s(void *self, GLint location, GLsizei count, GLboolean transpose,
        const GLfloat *value);
    static void glUniformMatrix4fv_s(void *self, GLint location, GLsizei count, GLboolean transpose,
        const GLfloat *value);
    static void glUseProgram_s(void *self, GLuint program);
    static void glValidateProgram_s(void *self, GLuint program);
    static void glVertexAttrib1f_s(void *self, GLuint index, GLfloat x);
    static void glVertexAttrib1fv_s(void *self, GLuint index, const GLfloat *v);
    static void glVertexAttrib2f_s(void *self, GLuint index, GLfloat x, GLfloat y);
    static void glVertexAttrib2fv_s(void *self, GLuint index, const GLfloat *v);
    static void glVertexAttrib3f_s(void *self, GLuint index, GLfloat x, GLfloat y, GLfloat z);
    static void glVertexAttrib3fv_s(void *self, GLuint index, const GLfloat *v);
    static void glVertexAttrib4f_s(void *self, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    static void glVertexAttrib4fv_s(void *self, GLuint index, const GLfloat *v);
    static void glVertexAttribPointer_s(void *self, GLuint index, GLint size, GLenum type, GLboolean normalized,
        GLsizei stride, const void *pointer);
    static void glViewport_s(void *self, GLint x, GLint y, GLsizei width, GLsizei height);
    static void glEGLImageTargetTexture2DOES_s(void *self, GLenum target, GLeglImageOES image);
    static void glEGLImageTargetRenderbufferStorageOES_s(void *self, GLenum target, GLeglImageOES image);
    static void glGetProgramBinaryOES_s(void *self, GLuint program, GLsizei bufSize, GLsizei *length,
        GLenum *binaryFormat, void *binary);
    static void glProgramBinaryOES_s(void *self, GLuint program, GLenum binaryFormat, const void *binary, GLint length);
    static void *glMapBufferOES_s(void *self, GLenum target, GLenum access);
    static GLboolean glUnmapBufferOES_s(void *self, GLenum target);
    static void glTexImage3DOES_s(void *self, GLenum target, GLint level, GLenum internalformat, GLsizei width,
        GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels);
    static void glTexSubImage3DOES_s(void *self, GLenum target, GLint level, GLint xoffset, GLint yoffset,
        GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
    static void glCopyTexSubImage3DOES_s(void *self, GLenum target, GLint level, GLint xoffset, GLint yoffset,
        GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
    static void glCompressedTexImage3DOES_s(void *self, GLenum target, GLint level, GLenum internalformat,
        GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data);
    static void glCompressedTexSubImage3DOES_s(void *self, GLenum target, GLint level, GLint xoffset, GLint yoffset,
        GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize,
        const void *data);
    static void glFramebufferTexture3DOES_s(void *self, GLenum target, GLenum attachment, GLenum textarget,
        GLuint texture, GLint level, GLint zoffset);
    static void glBindVertexArrayOES_s(void *self, GLuint array);
    static void glDeleteVertexArraysOES_s(void *self, GLsizei n, const GLuint *arrays);
    static void glGenVertexArraysOES_s(void *self, GLsizei n, GLuint *arrays);
    static GLboolean glIsVertexArrayOES_s(void *self, GLuint array);
    static void glDiscardFramebufferEXT_s(void *self, GLenum target, GLsizei numAttachments, const GLenum *attachments);
    static void glMultiDrawArraysEXT_s(void *self, GLenum mode, const GLint *first, const GLsizei *count,
        GLsizei primcount);
    static void glMultiDrawElementsEXT_s(void *self, GLenum mode, const GLsizei *count, GLenum type,
        const void * const * indices, GLsizei primcount);
    static void glGetPerfMonitorGroupsAMD_s(void *self, GLint *numGroups, GLsizei groupsSize, GLuint *groups);
    static void glGetPerfMonitorCountersAMD_s(void *self, GLuint group, GLint *numCounters, GLint *maxActiveCounters,
        GLsizei counterSize, GLuint *counters);
    static void glGetPerfMonitorGroupStringAMD_s(void *self, GLuint group, GLsizei bufSize, GLsizei *length,
        GLchar *groupString);
    static void glGetPerfMonitorCounterStringAMD_s(void *self, GLuint group, GLuint counter, GLsizei bufSize,
        GLsizei *length, GLchar *counterString);
    static void glGetPerfMonitorCounterInfoAMD_s(void *self, GLuint group, GLuint counter, GLenum pname, void *data);
    static void glGenPerfMonitorsAMD_s(void *self, GLsizei n, GLuint *monitors);
    static void glDeletePerfMonitorsAMD_s(void *self, GLsizei n, GLuint *monitors);
    static void glSelectPerfMonitorCountersAMD_s(void *self, GLuint monitor, GLboolean enable, GLuint group,
        GLint numCounters, GLuint *counterList);
    static void glBeginPerfMonitorAMD_s(void *self, GLuint monitor);
    static void glEndPerfMonitorAMD_s(void *self, GLuint monitor);
    static void glGetPerfMonitorCounterDataAMD_s(void *self, GLuint monitor, GLenum pname, GLsizei dataSize,
        GLuint *data, GLint *bytesWritten);
    static void glRenderbufferStorageMultisampleIMG_s(void *self, GLenum target, GLsizei samples, GLenum internalformat,
        GLsizei width, GLsizei height);
    static void glFramebufferTexture2DMultisampleIMG_s(void *self, GLenum target, GLenum attachment, GLenum textarget,
        GLuint texture, GLint level, GLsizei samples);
    static void glDeleteFencesNV_s(void *self, GLsizei n, const GLuint *fences);
    static void glGenFencesNV_s(void *self, GLsizei n, GLuint *fences);
    static GLboolean glIsFenceNV_s(void *self, GLuint fence);
    static GLboolean glTestFenceNV_s(void *self, GLuint fence);
    static void glGetFenceivNV_s(void *self, GLuint fence, GLenum pname, GLint *params);
    static void glFinishFenceNV_s(void *self, GLuint fence);
    static void glSetFenceNV_s(void *self, GLuint fence, GLenum condition);
    static void glCoverageMaskNV_s(void *self, GLboolean mask);
    static void glCoverageOperationNV_s(void *self, GLenum operation);
    static void glGetDriverControlsQCOM_s(void *self, GLint *num, GLsizei size, GLuint *driverControls);
    static void glGetDriverControlStringQCOM_s(void *self, GLuint driverControl, GLsizei bufSize, GLsizei *length,
        GLchar *driverControlString);
    static void glEnableDriverControlQCOM_s(void *self, GLuint driverControl);
    static void glDisableDriverControlQCOM_s(void *self, GLuint driverControl);
    static void glExtGetTexturesQCOM_s(void *self, GLuint *textures, GLint maxTextures, GLint *numTextures);
    static void glExtGetBuffersQCOM_s(void *self, GLuint *buffers, GLint maxBuffers, GLint *numBuffers);
    static void glExtGetRenderbuffersQCOM_s(void *self, GLuint *renderbuffers, GLint maxRenderbuffers,
        GLint *numRenderbuffers);
    static void glExtGetFramebuffersQCOM_s(void *self, GLuint *framebuffers, GLint maxFramebuffers,
        GLint *numFramebuffers);
    static void glExtGetTexLevelParameterivQCOM_s(void *self, GLuint texture, GLenum face, GLint level, GLenum pname,
        GLint *params);
    static void glExtTexObjectStateOverrideiQCOM_s(void *self, GLenum target, GLenum pname, GLint param);
    static void glExtGetTexSubImageQCOM_s(void *self, GLenum target, GLint level, GLint xoffset, GLint yoffset,
        GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, void *texels);
    static void glExtGetBufferPointervQCOM_s(void *self, GLenum target, void **params);
    static void glExtGetShadersQCOM_s(void *self, GLuint *shaders, GLint maxShaders, GLint *numShaders);
    static void glExtGetProgramsQCOM_s(void *self, GLuint *programs, GLint maxPrograms, GLint *numPrograms);
    static GLboolean glExtIsProgramBinaryQCOM_s(void *self, GLuint program);
    static void glExtGetProgramBinarySourceQCOM_s(void *self, GLuint program, GLenum shadertype, GLchar *source,
        GLint *length);
    static void glStartTilingQCOM_s(void *self, GLuint x, GLuint y, GLuint width, GLuint height,
        GLbitfield preserveMask);
    static void glEndTilingQCOM_s(void *self, GLbitfield preserveMask);
    static void glGenVertexArrays_s(void *self, GLsizei n, GLuint *arrays);
    static void glBindVertexArray_s(void *self, GLuint array);
    static void glDeleteVertexArrays_s(void *self, GLsizei n, const GLuint *arrays);
    static GLboolean glIsVertexArray_s(void *self, GLuint array);
    static void *glMapBufferRange_s(void *self, GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
    static GLboolean glUnmapBuffer_s(void *self, GLenum target);
    static void glFlushMappedBufferRange_s(void *self, GLenum target, GLintptr offset, GLsizeiptr length);
    static void glBindBufferRange_s(void *self, GLenum target, GLuint index, GLuint buffer, GLintptr offset,
        GLsizeiptr size);
    static void glBindBufferBase_s(void *self, GLenum target, GLuint index, GLuint buffer);
    static void glCopyBufferSubData_s(void *self, GLenum readTarget, GLenum writeTarget, GLintptr readOffset,
        GLintptr writeOffset, GLsizeiptr size);
    static void glClearBufferiv_s(void *self, GLenum buffer, GLint drawbuffer, const GLint *value);
    static void glClearBufferuiv_s(void *self, GLenum buffer, GLint drawbuffer, const GLuint *value);
    static void glClearBufferfv_s(void *self, GLenum buffer, GLint drawbuffer, const GLfloat *value);
    static void glClearBufferfi_s(void *self, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
    static void glGetBufferParameteri64v_s(void *self, GLenum target, GLenum pname, GLint64 *params);
    static void glGetBufferPointerv_s(void *self, GLenum target, GLenum pname, void **params);
    static void glUniformBlockBinding_s(void *self, GLuint program, GLuint uniformBlockIndex,
        GLuint uniformBlockBinding);
    static GLuint glGetUniformBlockIndex_s(void *self, GLuint program, const GLchar *uniformBlockName);
    static void glGetUniformIndices_s(void *self, GLuint program, GLsizei uniformCount,
        const GLchar * const * uniformNames, GLuint *uniformIndices);
    static void glGetActiveUniformBlockiv_s(void *self, GLuint program, GLuint uniformBlockIndex, GLenum pname,
        GLint *params);
    static void glGetActiveUniformBlockName_s(void *self, GLuint program, GLuint uniformBlockIndex, GLsizei bufSize,
        GLsizei *length, GLchar *uniformBlockName);
    static void glUniform1ui_s(void *self, GLint location, GLuint v0);
    static void glUniform2ui_s(void *self, GLint location, GLuint v0, GLuint v1);
    static void glUniform3ui_s(void *self, GLint location, GLuint v0, GLuint v1, GLuint v2);
    static void glUniform4ui_s(void *self, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
    static void glUniform1uiv_s(void *self, GLint location, GLsizei count, const GLuint *value);
    static void glUniform2uiv_s(void *self, GLint location, GLsizei count, const GLuint *value);
    static void glUniform3uiv_s(void *self, GLint location, GLsizei count, const GLuint *value);
    static void glUniform4uiv_s(void *self, GLint location, GLsizei count, const GLuint *value);
    static void glUniformMatrix2x3fv_s(void *self, GLint location, GLsizei count, GLboolean transpose,
        const GLfloat *value);
    static void glUniformMatrix3x2fv_s(void *self, GLint location, GLsizei count, GLboolean transpose,
        const GLfloat *value);
    static void glUniformMatrix2x4fv_s(void *self, GLint location, GLsizei count, GLboolean transpose,
        const GLfloat *value);
    static void glUniformMatrix4x2fv_s(void *self, GLint location, GLsizei count, GLboolean transpose,
        const GLfloat *value);
    static void glUniformMatrix3x4fv_s(void *self, GLint location, GLsizei count, GLboolean transpose,
        const GLfloat *value);
    static void glUniformMatrix4x3fv_s(void *self, GLint location, GLsizei count, GLboolean transpose,
        const GLfloat *value);
    static void glGetUniformuiv_s(void *self, GLuint program, GLint location, GLuint *params);
    static void glGetActiveUniformsiv_s(void *self, GLuint program, GLsizei uniformCount, const GLuint *uniformIndices,
        GLenum pname, GLint *params);
    static void glVertexAttribI4i_s(void *self, GLuint index, GLint x, GLint y, GLint z, GLint w);
    static void glVertexAttribI4ui_s(void *self, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
    static void glVertexAttribI4iv_s(void *self, GLuint index, const GLint *v);
    static void glVertexAttribI4uiv_s(void *self, GLuint index, const GLuint *v);
    static void glVertexAttribIPointer_s(void *self, GLuint index, GLint size, GLenum type, GLsizei stride,
        const void *pointer);
    static void glGetVertexAttribIiv_s(void *self, GLuint index, GLenum pname, GLint *params);
    static void glGetVertexAttribIuiv_s(void *self, GLuint index, GLenum pname, GLuint *params);
    static void glVertexAttribDivisor_s(void *self, GLuint index, GLuint divisor);
    static void glDrawArraysInstanced_s(void *self, GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
    static void glDrawElementsInstanced_s(void *self, GLenum mode, GLsizei count, GLenum type, const void *indices,
        GLsizei instancecount);
    static void glDrawRangeElements_s(void *self, GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type,
        const void *indices);
    static GLsync glFenceSync_s(void *self, GLenum condition, GLbitfield flags);
    static GLenum glClientWaitSync_s(void *self, GLsync sync, GLbitfield flags, GLuint64 timeout);
    static void glWaitSync_s(void *self, GLsync sync, GLbitfield flags, GLuint64 timeout);
    static void glDeleteSync_s(void *self, GLsync sync);
    static GLboolean glIsSync_s(void *self, GLsync sync);
    static void glGetSynciv_s(void *self, GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values);
    static void glDrawBuffers_s(void *self, GLsizei n, const GLenum *bufs);
    static void glReadBuffer_s(void *self, GLenum src);
    static void glBlitFramebuffer_s(void *self, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0,
        GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
    static void glInvalidateFramebuffer_s(void *self, GLenum target, GLsizei numAttachments, const GLenum *attachments);
    static void glInvalidateSubFramebuffer_s(void *self, GLenum target, GLsizei numAttachments,
        const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
    static void glFramebufferTextureLayer_s(void *self, GLenum target, GLenum attachment, GLuint texture, GLint level,
        GLint layer);
    static void glRenderbufferStorageMultisample_s(void *self, GLenum target, GLsizei samples, GLenum internalformat,
        GLsizei width, GLsizei height);
    static void glTexStorage2D_s(void *self, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width,
        GLsizei height);
    static void glGetInternalformativ_s(void *self, GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize,
        GLint *params);
    static void glBeginTransformFeedback_s(void *self, GLenum primitiveMode);
    static void glEndTransformFeedback_s(void *self);
    static void glGenTransformFeedbacks_s(void *self, GLsizei n, GLuint *ids);
    static void glDeleteTransformFeedbacks_s(void *self, GLsizei n, const GLuint *ids);
    static void glBindTransformFeedback_s(void *self, GLenum target, GLuint id);
    static void glPauseTransformFeedback_s(void *self);
    static void glResumeTransformFeedback_s(void *self);
    static GLboolean glIsTransformFeedback_s(void *self, GLuint id);
    static void glTransformFeedbackVaryings_s(void *self, GLuint program, GLsizei count,
        const GLchar * const * varyings, GLenum bufferMode);
    static void glGetTransformFeedbackVarying_s(void *self, GLuint program, GLuint index, GLsizei bufSize,
        GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);
    static void glGenSamplers_s(void *self, GLsizei count, GLuint *samplers);
    static void glDeleteSamplers_s(void *self, GLsizei count, const GLuint *samplers);
    static void glBindSampler_s(void *self, GLuint unit, GLuint sampler);
    static void glSamplerParameterf_s(void *self, GLuint sampler, GLenum pname, GLfloat param);
    static void glSamplerParameteri_s(void *self, GLuint sampler, GLenum pname, GLint param);
    static void glSamplerParameterfv_s(void *self, GLuint sampler, GLenum pname, const GLfloat *param);
    static void glSamplerParameteriv_s(void *self, GLuint sampler, GLenum pname, const GLint *param);
    static void glGetSamplerParameterfv_s(void *self, GLuint sampler, GLenum pname, GLfloat *params);
    static void glGetSamplerParameteriv_s(void *self, GLuint sampler, GLenum pname, GLint *params);
    static GLboolean glIsSampler_s(void *self, GLuint sampler);
    static void glGenQueries_s(void *self, GLsizei n, GLuint *ids);
    static void glDeleteQueries_s(void *self, GLsizei n, const GLuint *ids);
    static void glBeginQuery_s(void *self, GLenum target, GLuint id);
    static void glEndQuery_s(void *self, GLenum target);
    static void glGetQueryiv_s(void *self, GLenum target, GLenum pname, GLint *params);
    static void glGetQueryObjectuiv_s(void *self, GLuint id, GLenum pname, GLuint *params);
    static GLboolean glIsQuery_s(void *self, GLuint id);
    static void glProgramParameteri_s(void *self, GLuint program, GLenum pname, GLint value);
    static void glProgramBinary_s(void *self, GLuint program, GLenum binaryFormat, const void *binary, GLsizei length);
    static void glGetProgramBinary_s(void *self, GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat,
        void *binary);
    static GLint glGetFragDataLocation_s(void *self, GLuint program, const GLchar *name);
    static void glGetInteger64v_s(void *self, GLenum pname, GLint64 *data);
    static void glGetIntegeri_v_s(void *self, GLenum target, GLuint index, GLint *data);
    static void glGetInteger64i_v_s(void *self, GLenum target, GLuint index, GLint64 *data);
    static void glTexImage3D_s(void *self, GLenum target, GLint level, GLint internalformat, GLsizei width,
        GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels);
    static void glTexStorage3D_s(void *self, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width,
        GLsizei height, GLsizei depth);
    static void glTexSubImage3D_s(void *self, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset,
        GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
    static void glCompressedTexImage3D_s(void *self, GLenum target, GLint level, GLenum internalformat, GLsizei width,
        GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data);
    static void glCompressedTexSubImage3D_s(void *self, GLenum target, GLint level, GLint xoffset, GLint yoffset,
        GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize,
        const void *data);
    static void glCopyTexSubImage3D_s(void *self, GLenum target, GLint level, GLint xoffset, GLint yoffset,
        GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
    static const GLubyte *glGetStringi_s(void *self, GLenum name, GLuint index);
    static void glGetBooleani_v_s(void *self, GLenum target, GLuint index, GLboolean *data);
    static void glMemoryBarrier_s(void *self, GLbitfield barriers);
    static void glMemoryBarrierByRegion_s(void *self, GLbitfield barriers);
    static void glGenProgramPipelines_s(void *self, GLsizei n, GLuint *pipelines);
    static void glDeleteProgramPipelines_s(void *self, GLsizei n, const GLuint *pipelines);
    static void glBindProgramPipeline_s(void *self, GLuint pipeline);
    static void glGetProgramPipelineiv_s(void *self, GLuint pipeline, GLenum pname, GLint *params);
    static void glGetProgramPipelineInfoLog_s(void *self, GLuint pipeline, GLsizei bufSize, GLsizei *length,
        GLchar *infoLog);
    static void glValidateProgramPipeline_s(void *self, GLuint pipeline);
    static GLboolean glIsProgramPipeline_s(void *self, GLuint pipeline);
    static void glUseProgramStages_s(void *self, GLuint pipeline, GLbitfield stages, GLuint program);
    static void glActiveShaderProgram_s(void *self, GLuint pipeline, GLuint program);
    static GLuint glCreateShaderProgramv_s(void *self, GLenum type, GLsizei count, const GLchar * const * strings);
    static void glProgramUniform1f_s(void *self, GLuint program, GLint location, GLfloat v0);
    static void glProgramUniform2f_s(void *self, GLuint program, GLint location, GLfloat v0, GLfloat v1);
    static void glProgramUniform3f_s(void *self, GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
    static void glProgramUniform4f_s(void *self, GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2,
        GLfloat v3);
    static void glProgramUniform1i_s(void *self, GLuint program, GLint location, GLint v0);
    static void glProgramUniform2i_s(void *self, GLuint program, GLint location, GLint v0, GLint v1);
    static void glProgramUniform3i_s(void *self, GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
    static void glProgramUniform4i_s(void *self, GLuint program, GLint location, GLint v0, GLint v1, GLint v2,
        GLint v3);
    static void glProgramUniform1ui_s(void *self, GLuint program, GLint location, GLuint v0);
    static void glProgramUniform2ui_s(void *self, GLuint program, GLint location, GLuint v0, GLuint v1);
    static void glProgramUniform3ui_s(void *self, GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
    static void glProgramUniform4ui_s(void *self, GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2,
        GLuint v3);
    static void glProgramUniform1fv_s(void *self, GLuint program, GLint location, GLsizei count, const GLfloat *value);
    static void glProgramUniform2fv_s(void *self, GLuint program, GLint location, GLsizei count, const GLfloat *value);
    static void glProgramUniform3fv_s(void *self, GLuint program, GLint location, GLsizei count, const GLfloat *value);
    static void glProgramUniform4fv_s(void *self, GLuint program, GLint location, GLsizei count, const GLfloat *value);
    static void glProgramUniform1iv_s(void *self, GLuint program, GLint location, GLsizei count, const GLint *value);
    static void glProgramUniform2iv_s(void *self, GLuint program, GLint location, GLsizei count, const GLint *value);
    static void glProgramUniform3iv_s(void *self, GLuint program, GLint location, GLsizei count, const GLint *value);
    static void glProgramUniform4iv_s(void *self, GLuint program, GLint location, GLsizei count, const GLint *value);
    static void glProgramUniform1uiv_s(void *self, GLuint program, GLint location, GLsizei count, const GLuint *value);
    static void glProgramUniform2uiv_s(void *self, GLuint program, GLint location, GLsizei count, const GLuint *value);
    static void glProgramUniform3uiv_s(void *self, GLuint program, GLint location, GLsizei count, const GLuint *value);
    static void glProgramUniform4uiv_s(void *self, GLuint program, GLint location, GLsizei count, const GLuint *value);
    static void glProgramUniformMatrix2fv_s(void *self, GLuint program, GLint location, GLsizei count,
        GLboolean transpose, const GLfloat *value);
    static void glProgramUniformMatrix3fv_s(void *self, GLuint program, GLint location, GLsizei count,
        GLboolean transpose, const GLfloat *value);
    static void glProgramUniformMatrix4fv_s(void *self, GLuint program, GLint location, GLsizei count,
        GLboolean transpose, const GLfloat *value);
    static void glProgramUniformMatrix2x3fv_s(void *self, GLuint program, GLint location, GLsizei count,
        GLboolean transpose, const GLfloat *value);
    static void glProgramUniformMatrix3x2fv_s(void *self, GLuint program, GLint location, GLsizei count,
        GLboolean transpose, const GLfloat *value);
    static void glProgramUniformMatrix2x4fv_s(void *self, GLuint program, GLint location, GLsizei count,
        GLboolean transpose, const GLfloat *value);
    static void glProgramUniformMatrix4x2fv_s(void *self, GLuint program, GLint location, GLsizei count,
        GLboolean transpose, const GLfloat *value);
    static void glProgramUniformMatrix3x4fv_s(void *self, GLuint program, GLint location, GLsizei count,
        GLboolean transpose, const GLfloat *value);
    static void glProgramUniformMatrix4x3fv_s(void *self, GLuint program, GLint location, GLsizei count,
        GLboolean transpose, const GLfloat *value);
    static void glGetProgramInterfaceiv_s(void *self, GLuint program, GLenum programInterface, GLenum pname,
        GLint *params);
    static void glGetProgramResourceiv_s(void *self, GLuint program, GLenum programInterface, GLuint index,
        GLsizei propCount, const GLenum *props, GLsizei bufSize, GLsizei *length, GLint *params);
    static GLuint glGetProgramResourceIndex_s(void *self, GLuint program, GLenum programInterface, const GLchar *name);
    static GLint glGetProgramResourceLocation_s(void *self, GLuint program, GLenum programInterface,
        const GLchar *name);
    static void glGetProgramResourceName_s(void *self, GLuint program, GLenum programInterface, GLuint index,
        GLsizei bufSize, GLsizei *length, GLchar *name);
    static void glBindImageTexture_s(void *self, GLuint unit, GLuint texture, GLint level, GLboolean layered,
        GLint layer, GLenum access, GLenum format);
    static void glDispatchCompute_s(void *self, GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
    static void glDispatchComputeIndirect_s(void *self, GLintptr indirect);
    static void glBindVertexBuffer_s(void *self, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
    static void glVertexAttribBinding_s(void *self, GLuint attribindex, GLuint bindingindex);
    static void glVertexAttribFormat_s(void *self, GLuint attribindex, GLint size, GLenum type, GLboolean normalized,
        GLuint relativeoffset);
    static void glVertexAttribIFormat_s(void *self, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
    static void glVertexBindingDivisor_s(void *self, GLuint bindingindex, GLuint divisor);
    static void glDrawArraysIndirect_s(void *self, GLenum mode, const void *indirect);
    static void glDrawElementsIndirect_s(void *self, GLenum mode, GLenum type, const void *indirect);
    static void glTexStorage2DMultisample_s(void *self, GLenum target, GLsizei samples, GLenum internalformat,
        GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
    static void glSampleMaski_s(void *self, GLuint maskNumber, GLbitfield mask);
    static void glGetMultisamplefv_s(void *self, GLenum pname, GLuint index, GLfloat *val);
    static void glFramebufferParameteri_s(void *self, GLenum target, GLenum pname, GLint param);
    static void glGetFramebufferParameteriv_s(void *self, GLenum target, GLenum pname, GLint *params);
    static void glGetTexLevelParameterfv_s(void *self, GLenum target, GLint level, GLenum pname, GLfloat *params);
    static void glGetTexLevelParameteriv_s(void *self, GLenum target, GLint level, GLenum pname, GLint *params);
    static void glEnableiEXT_s(void *self, GLenum target, GLuint index);
    static void glDisableiEXT_s(void *self, GLenum target, GLuint index);
    static void glBlendEquationiEXT_s(void *self, GLuint buf, GLenum mode);
    static void glBlendEquationSeparateiEXT_s(void *self, GLuint buf, GLenum modeRGB, GLenum modeAlpha);
    static void glBlendFunciEXT_s(void *self, GLuint buf, GLenum src, GLenum dst);
    static void glBlendFuncSeparateiEXT_s(void *self, GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha,
        GLenum dstAlpha);
    static void glColorMaskiEXT_s(void *self, GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
    static GLboolean glIsEnablediEXT_s(void *self, GLenum target, GLuint index);
    static void glCopyImageSubDataEXT_s(void *self, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX,
        GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ,
        GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
    static void glBlendBarrierKHR_s(void *self);
    static void glTexParameterIivEXT_s(void *self, GLenum target, GLenum pname, const GLint *params);
    static void glTexParameterIuivEXT_s(void *self, GLenum target, GLenum pname, const GLuint *params);
    static void glGetTexParameterIivEXT_s(void *self, GLenum target, GLenum pname, GLint *params);
    static void glGetTexParameterIuivEXT_s(void *self, GLenum target, GLenum pname, GLuint *params);
    static void glSamplerParameterIivEXT_s(void *self, GLuint sampler, GLenum pname, const GLint *param);
    static void glSamplerParameterIuivEXT_s(void *self, GLuint sampler, GLenum pname, const GLuint *param);
    static void glGetSamplerParameterIivEXT_s(void *self, GLuint sampler, GLenum pname, GLint *params);
    static void glGetSamplerParameterIuivEXT_s(void *self, GLuint sampler, GLenum pname, GLuint *params);
    static void glVertexAttribPointerData_s(void *self, GLuint indx, GLint size, GLenum type, GLboolean normalized,
        GLsizei stride, void *data, GLuint datalen);
    static void glVertexAttribPointerOffset_s(void *self, GLuint indx, GLint size, GLenum type, GLboolean normalized,
        GLsizei stride, GLuint offset);
    static void glDrawElementsOffset_s(void *self, GLenum mode, GLsizei count, GLenum type, GLuint offset);
    static void glDrawElementsData_s(void *self, GLenum mode, GLsizei count, GLenum type, void *data, GLuint datalen);
    static void glGetCompressedTextureFormats_s(void *self, int count, GLint *formats);
    static void glShaderString_s(void *self, GLuint shader, const GLchar *string, GLsizei len);
    static int glFinishRoundTrip_s(void *self);
    static void glMapBufferRangeAEMU_s(void *self, GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access,
        void *mapped);
    static void glUnmapBufferAEMU_s(void *self, GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access,
        void *guest_buffer, GLboolean *out_res);
    static void glFlushMappedBufferRangeAEMU_s(void *self, GLenum target, GLintptr offset, GLsizeiptr length,
        GLbitfield access, void *guest_buffer);
    static void glReadPixelsOffsetAEMU_s(void *self, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format,
        GLenum type, GLuint offset);
    static void glCompressedTexImage2DOffsetAEMU_s(void *self, GLenum target, GLint level, GLenum internalformat,
        GLsizei width, GLsizei height, GLint border, GLsizei imageSize, GLuint offset);
    static void glCompressedTexSubImage2DOffsetAEMU_s(void *self, GLenum target, GLint level, GLint xoffset,
        GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, GLuint offset);
    static void glTexImage2DOffsetAEMU_s(void *self, GLenum target, GLint level, GLint internalformat, GLsizei width,
        GLsizei height, GLint border, GLenum format, GLenum type, GLuint offset);
    static void glTexSubImage2DOffsetAEMU_s(void *self, GLenum target, GLint level, GLint xoffset, GLint yoffset,
        GLsizei width, GLsizei height, GLenum format, GLenum type, GLuint offset);
    static void glGetUniformIndicesAEMU_s(void *self, GLuint program, GLsizei uniformCount,
        const GLchar *packedUniformNames, GLsizei packedLen, GLuint *uniformIndices);
    static void glVertexAttribIPointerOffsetAEMU_s(void *self, GLuint index, GLint size, GLenum type, GLsizei stride,
        GLuint offset);
    static void glVertexAttribIPointerDataAEMU_s(void *self, GLuint index, GLint size, GLenum type, GLsizei stride,
        void *data, GLuint datalen);
    static void glDrawElementsInstancedDataAEMU_s(void *self, GLenum mode, GLsizei count, GLenum type,
        const void *indices, GLsizei primcount, GLsizei datalen);
    static void glDrawElementsInstancedOffsetAEMU_s(void *self, GLenum mode, GLsizei count, GLenum type, GLuint offset,
        GLsizei primcount);
    static void glDrawRangeElementsDataAEMU_s(void *self, GLenum mode, GLuint start, GLuint end, GLsizei count,
        GLenum type, const GLvoid *indices, GLsizei datalen);
    static void glDrawRangeElementsOffsetAEMU_s(void *self, GLenum mode, GLuint start, GLuint end, GLsizei count,
        GLenum type, GLuint offset);
    static uint64_t glFenceSyncAEMU_s(void *self, GLenum condition, GLbitfield flags);
    static GLenum glClientWaitSyncAEMU_s(void *self, uint64_t wait_on, GLbitfield flags, GLuint64 timeout);
    static void glWaitSyncAEMU_s(void *self, uint64_t wait_on, GLbitfield flags, GLuint64 timeout);
    static void glDeleteSyncAEMU_s(void *self, uint64_t to_delete);
    static GLboolean glIsSyncAEMU_s(void *self, uint64_t sync);
    static void glGetSyncivAEMU_s(void *self, uint64_t sync, GLenum pname, GLsizei bufSize, GLsizei *length,
        GLint *values);
    static void glTransformFeedbackVaryingsAEMU_s(void *self, GLuint program, GLsizei count, const char *packedVaryings,
        GLuint packedVaryingsLen, GLenum bufferMode);
    static void glTexImage3DOffsetAEMU_s(void *self, GLenum target, GLint level, GLint internalFormat, GLsizei width,
        GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, GLuint offset);
    static void glTexSubImage3DOffsetAEMU_s(void *self, GLenum target, GLint level, GLint xoffset, GLint yoffset,
        GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLuint offset);
    static void glCompressedTexImage3DOffsetAEMU_s(void *self, GLenum target, GLint level, GLenum internalformat,
        GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, GLuint offset);
    static void glCompressedTexSubImage3DOffsetAEMU_s(void *self, GLenum target, GLint level, GLint xoffset,
        GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize,
        GLuint data);
    static GLuint glCreateShaderProgramvAEMU_s(void *self, GLenum type, GLsizei count, const char *packedStrings,
        GLuint packedLen);
    static void glDrawArraysIndirectDataAEMU_s(void *self, GLenum mode, const void *indirect, GLuint datalen);
    static void glDrawArraysIndirectOffsetAEMU_s(void *self, GLenum mode, GLuint offset);
    static void glDrawElementsIndirectDataAEMU_s(void *self, GLenum mode, GLenum type, const void *indirect,
        GLuint datalen);
    static void glDrawElementsIndirectOffsetAEMU_s(void *self, GLenum mode, GLenum type, GLuint offset);
    static void glUniformLayout_s(void *self, GLuint program);
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
    glClearDepthf_client_proc_t glClearDepthf = nullptr;
    glClearStencil_client_proc_t glClearStencil = nullptr;
    glColorMask_client_proc_t glColorMask = nullptr;
    glCompileShader_client_proc_t glCompileShader = nullptr;
    glCompressedTexImage2D_client_proc_t glCompressedTexImage2D = nullptr;
    glCompressedTexSubImage2D_client_proc_t glCompressedTexSubImage2D = nullptr;
    glCopyTexImage2D_client_proc_t glCopyTexImage2D = nullptr;
    glCopyTexSubImage2D_client_proc_t glCopyTexSubImage2D = nullptr;
    glCreateProgram_client_proc_t glCreateProgram = nullptr;
    glCreateShader_client_proc_t glCreateShader = nullptr;
    glCullFace_client_proc_t glCullFace = nullptr;
    glDeleteBuffers_client_proc_t glDeleteBuffers = nullptr;
    glDeleteFramebuffers_client_proc_t glDeleteFramebuffers = nullptr;
    glDeleteProgram_client_proc_t glDeleteProgram = nullptr;
    glDeleteRenderbuffers_client_proc_t glDeleteRenderbuffers = nullptr;
    glDeleteShader_client_proc_t glDeleteShader = nullptr;
    glDeleteTextures_client_proc_t glDeleteTextures = nullptr;
    glDepthFunc_client_proc_t glDepthFunc = nullptr;
    glDepthMask_client_proc_t glDepthMask = nullptr;
    glDepthRangef_client_proc_t glDepthRangef = nullptr;
    glDetachShader_client_proc_t glDetachShader = nullptr;
    glDisable_client_proc_t glDisable = nullptr;
    glDisableVertexAttribArray_client_proc_t glDisableVertexAttribArray = nullptr;
    glDrawArrays_client_proc_t glDrawArrays = nullptr;
    glDrawElements_client_proc_t glDrawElements = nullptr;
    glEnable_client_proc_t glEnable = nullptr;
    glEnableVertexAttribArray_client_proc_t glEnableVertexAttribArray = nullptr;
    glFinish_client_proc_t glFinish = nullptr;
    glFlush_client_proc_t glFlush = nullptr;
    glFramebufferRenderbuffer_client_proc_t glFramebufferRenderbuffer = nullptr;
    glFramebufferTexture2D_client_proc_t glFramebufferTexture2D = nullptr;
    glFrontFace_client_proc_t glFrontFace = nullptr;
    glGenBuffers_client_proc_t glGenBuffers = nullptr;
    glGenerateMipmap_client_proc_t glGenerateMipmap = nullptr;
    glGenFramebuffers_client_proc_t glGenFramebuffers = nullptr;
    glGenRenderbuffers_client_proc_t glGenRenderbuffers = nullptr;
    glGenTextures_client_proc_t glGenTextures = nullptr;
    glGetActiveAttrib_client_proc_t glGetActiveAttrib = nullptr;
    glGetActiveUniform_client_proc_t glGetActiveUniform = nullptr;
    glGetAttachedShaders_client_proc_t glGetAttachedShaders = nullptr;
    glGetAttribLocation_client_proc_t glGetAttribLocation = nullptr;
    glGetBooleanv_client_proc_t glGetBooleanv = nullptr;
    glGetBufferParameteriv_client_proc_t glGetBufferParameteriv = nullptr;
    glGetError_client_proc_t glGetError = nullptr;
    glGetFloatv_client_proc_t glGetFloatv = nullptr;
    glGetFramebufferAttachmentParameteriv_client_proc_t glGetFramebufferAttachmentParameteriv = nullptr;
    glGetIntegerv_client_proc_t glGetIntegerv = nullptr;
    glGetProgramiv_client_proc_t glGetProgramiv = nullptr;
    glGetProgramInfoLog_client_proc_t glGetProgramInfoLog = nullptr;
    glGetRenderbufferParameteriv_client_proc_t glGetRenderbufferParameteriv = nullptr;
    glGetShaderiv_client_proc_t glGetShaderiv = nullptr;
    glGetShaderInfoLog_client_proc_t glGetShaderInfoLog = nullptr;
    glGetShaderPrecisionFormat_client_proc_t glGetShaderPrecisionFormat = nullptr;
    glGetShaderSource_client_proc_t glGetShaderSource = nullptr;
    glGetString_client_proc_t glGetString = nullptr;
    glGetTexParameterfv_client_proc_t glGetTexParameterfv = nullptr;
    glGetTexParameteriv_client_proc_t glGetTexParameteriv = nullptr;
    glGetUniformfv_client_proc_t glGetUniformfv = nullptr;
    glGetUniformiv_client_proc_t glGetUniformiv = nullptr;
    glGetUniformLocation_client_proc_t glGetUniformLocation = nullptr;
    glGetVertexAttribfv_client_proc_t glGetVertexAttribfv = nullptr;
    glGetVertexAttribiv_client_proc_t glGetVertexAttribiv = nullptr;
    glGetVertexAttribPointerv_client_proc_t glGetVertexAttribPointerv = nullptr;
    glHint_client_proc_t glHint = nullptr;
    glIsBuffer_client_proc_t glIsBuffer = nullptr;
    glIsEnabled_client_proc_t glIsEnabled = nullptr;
    glIsFramebuffer_client_proc_t glIsFramebuffer = nullptr;
    glIsProgram_client_proc_t glIsProgram = nullptr;
    glIsRenderbuffer_client_proc_t glIsRenderbuffer = nullptr;
    glIsShader_client_proc_t glIsShader = nullptr;
    glIsTexture_client_proc_t glIsTexture = nullptr;
    glLineWidth_client_proc_t glLineWidth = nullptr;
    glLinkProgram_client_proc_t glLinkProgram = nullptr;
    glPixelStorei_client_proc_t glPixelStorei = nullptr;
    glPolygonOffset_client_proc_t glPolygonOffset = nullptr;
    glReadPixels_client_proc_t glReadPixels = nullptr;
    glReleaseShaderCompiler_client_proc_t glReleaseShaderCompiler = nullptr;
    glRenderbufferStorage_client_proc_t glRenderbufferStorage = nullptr;
    glSampleCoverage_client_proc_t glSampleCoverage = nullptr;
    glScissor_client_proc_t glScissor = nullptr;
    glShaderBinary_client_proc_t glShaderBinary = nullptr;
    glShaderSource_client_proc_t glShaderSource = nullptr;
    glStencilFunc_client_proc_t glStencilFunc = nullptr;
    glStencilFuncSeparate_client_proc_t glStencilFuncSeparate = nullptr;
    glStencilMask_client_proc_t glStencilMask = nullptr;
    glStencilMaskSeparate_client_proc_t glStencilMaskSeparate = nullptr;
    glStencilOp_client_proc_t glStencilOp = nullptr;
    glStencilOpSeparate_client_proc_t glStencilOpSeparate = nullptr;
    glTexImage2D_client_proc_t glTexImage2D = nullptr;
    glTexParameterf_client_proc_t glTexParameterf = nullptr;
    glTexParameterfv_client_proc_t glTexParameterfv = nullptr;
    glTexParameteri_client_proc_t glTexParameteri = nullptr;
    glTexParameteriv_client_proc_t glTexParameteriv = nullptr;
    glTexSubImage2D_client_proc_t glTexSubImage2D = nullptr;
    glUniform1f_client_proc_t glUniform1f = nullptr;
    glUniform1fv_client_proc_t glUniform1fv = nullptr;
    glUniform1i_client_proc_t glUniform1i = nullptr;
    glUniform1iv_client_proc_t glUniform1iv = nullptr;
    glUniform2f_client_proc_t glUniform2f = nullptr;
    glUniform2fv_client_proc_t glUniform2fv = nullptr;
    glUniform2i_client_proc_t glUniform2i = nullptr;
    glUniform2iv_client_proc_t glUniform2iv = nullptr;
    glUniform3f_client_proc_t glUniform3f = nullptr;
    glUniform3fv_client_proc_t glUniform3fv = nullptr;
    glUniform3i_client_proc_t glUniform3i = nullptr;
    glUniform3iv_client_proc_t glUniform3iv = nullptr;
    glUniform4f_client_proc_t glUniform4f = nullptr;
    glUniform4fv_client_proc_t glUniform4fv = nullptr;
    glUniform4i_client_proc_t glUniform4i = nullptr;
    glUniform4iv_client_proc_t glUniform4iv = nullptr;
    glUniformMatrix2fv_client_proc_t glUniformMatrix2fv = nullptr;
    glUniformMatrix3fv_client_proc_t glUniformMatrix3fv = nullptr;
    glUniformMatrix4fv_client_proc_t glUniformMatrix4fv = nullptr;
    glUseProgram_client_proc_t glUseProgram = nullptr;
    glValidateProgram_client_proc_t glValidateProgram = nullptr;
    glVertexAttrib1f_client_proc_t glVertexAttrib1f = nullptr;
    glVertexAttrib1fv_client_proc_t glVertexAttrib1fv = nullptr;
    glVertexAttrib2f_client_proc_t glVertexAttrib2f = nullptr;
    glVertexAttrib2fv_client_proc_t glVertexAttrib2fv = nullptr;
    glVertexAttrib3f_client_proc_t glVertexAttrib3f = nullptr;
    glVertexAttrib3fv_client_proc_t glVertexAttrib3fv = nullptr;
    glVertexAttrib4f_client_proc_t glVertexAttrib4f = nullptr;
    glVertexAttrib4fv_client_proc_t glVertexAttrib4fv = nullptr;
    glVertexAttribPointer_client_proc_t glVertexAttribPointer = nullptr;
    glViewport_client_proc_t glViewport = nullptr;
    glEGLImageTargetTexture2DOES_client_proc_t glEGLImageTargetTexture2DOES = nullptr;
    glEGLImageTargetRenderbufferStorageOES_client_proc_t glEGLImageTargetRenderbufferStorageOES = nullptr;
    glGetProgramBinaryOES_client_proc_t glGetProgramBinaryOES = nullptr;
    glProgramBinaryOES_client_proc_t glProgramBinaryOES = nullptr;
    glMapBufferOES_client_proc_t glMapBufferOES = nullptr;
    glUnmapBufferOES_client_proc_t glUnmapBufferOES = nullptr;
    glTexImage3DOES_client_proc_t glTexImage3DOES = nullptr;
    glTexSubImage3DOES_client_proc_t glTexSubImage3DOES = nullptr;
    glCopyTexSubImage3DOES_client_proc_t glCopyTexSubImage3DOES = nullptr;
    glCompressedTexImage3DOES_client_proc_t glCompressedTexImage3DOES = nullptr;
    glCompressedTexSubImage3DOES_client_proc_t glCompressedTexSubImage3DOES = nullptr;
    glFramebufferTexture3DOES_client_proc_t glFramebufferTexture3DOES = nullptr;
    glBindVertexArrayOES_client_proc_t glBindVertexArrayOES = nullptr;
    glDeleteVertexArraysOES_client_proc_t glDeleteVertexArraysOES = nullptr;
    glGenVertexArraysOES_client_proc_t glGenVertexArraysOES = nullptr;
    glIsVertexArrayOES_client_proc_t glIsVertexArrayOES = nullptr;
    glDiscardFramebufferEXT_client_proc_t glDiscardFramebufferEXT = nullptr;
    glMultiDrawArraysEXT_client_proc_t glMultiDrawArraysEXT = nullptr;
    glMultiDrawElementsEXT_client_proc_t glMultiDrawElementsEXT = nullptr;
    glGetPerfMonitorGroupsAMD_client_proc_t glGetPerfMonitorGroupsAMD = nullptr;
    glGetPerfMonitorCountersAMD_client_proc_t glGetPerfMonitorCountersAMD = nullptr;
    glGetPerfMonitorGroupStringAMD_client_proc_t glGetPerfMonitorGroupStringAMD = nullptr;
    glGetPerfMonitorCounterStringAMD_client_proc_t glGetPerfMonitorCounterStringAMD = nullptr;
    glGetPerfMonitorCounterInfoAMD_client_proc_t glGetPerfMonitorCounterInfoAMD = nullptr;
    glGenPerfMonitorsAMD_client_proc_t glGenPerfMonitorsAMD = nullptr;
    glDeletePerfMonitorsAMD_client_proc_t glDeletePerfMonitorsAMD = nullptr;
    glSelectPerfMonitorCountersAMD_client_proc_t glSelectPerfMonitorCountersAMD = nullptr;
    glBeginPerfMonitorAMD_client_proc_t glBeginPerfMonitorAMD = nullptr;
    glEndPerfMonitorAMD_client_proc_t glEndPerfMonitorAMD = nullptr;
    glGetPerfMonitorCounterDataAMD_client_proc_t glGetPerfMonitorCounterDataAMD = nullptr;
    glRenderbufferStorageMultisampleIMG_client_proc_t glRenderbufferStorageMultisampleIMG = nullptr;
    glFramebufferTexture2DMultisampleIMG_client_proc_t glFramebufferTexture2DMultisampleIMG = nullptr;
    glDeleteFencesNV_client_proc_t glDeleteFencesNV = nullptr;
    glGenFencesNV_client_proc_t glGenFencesNV = nullptr;
    glIsFenceNV_client_proc_t glIsFenceNV = nullptr;
    glTestFenceNV_client_proc_t glTestFenceNV = nullptr;
    glGetFenceivNV_client_proc_t glGetFenceivNV = nullptr;
    glFinishFenceNV_client_proc_t glFinishFenceNV = nullptr;
    glSetFenceNV_client_proc_t glSetFenceNV = nullptr;
    glCoverageMaskNV_client_proc_t glCoverageMaskNV = nullptr;
    glCoverageOperationNV_client_proc_t glCoverageOperationNV = nullptr;
    glGetDriverControlsQCOM_client_proc_t glGetDriverControlsQCOM = nullptr;
    glGetDriverControlStringQCOM_client_proc_t glGetDriverControlStringQCOM = nullptr;
    glEnableDriverControlQCOM_client_proc_t glEnableDriverControlQCOM = nullptr;
    glDisableDriverControlQCOM_client_proc_t glDisableDriverControlQCOM = nullptr;
    glExtGetTexturesQCOM_client_proc_t glExtGetTexturesQCOM = nullptr;
    glExtGetBuffersQCOM_client_proc_t glExtGetBuffersQCOM = nullptr;
    glExtGetRenderbuffersQCOM_client_proc_t glExtGetRenderbuffersQCOM = nullptr;
    glExtGetFramebuffersQCOM_client_proc_t glExtGetFramebuffersQCOM = nullptr;
    glExtGetTexLevelParameterivQCOM_client_proc_t glExtGetTexLevelParameterivQCOM = nullptr;
    glExtTexObjectStateOverrideiQCOM_client_proc_t glExtTexObjectStateOverrideiQCOM = nullptr;
    glExtGetTexSubImageQCOM_client_proc_t glExtGetTexSubImageQCOM = nullptr;
    glExtGetBufferPointervQCOM_client_proc_t glExtGetBufferPointervQCOM = nullptr;
    glExtGetShadersQCOM_client_proc_t glExtGetShadersQCOM = nullptr;
    glExtGetProgramsQCOM_client_proc_t glExtGetProgramsQCOM = nullptr;
    glExtIsProgramBinaryQCOM_client_proc_t glExtIsProgramBinaryQCOM = nullptr;
    glExtGetProgramBinarySourceQCOM_client_proc_t glExtGetProgramBinarySourceQCOM = nullptr;
    glStartTilingQCOM_client_proc_t glStartTilingQCOM = nullptr;
    glEndTilingQCOM_client_proc_t glEndTilingQCOM = nullptr;
    glGenVertexArrays_client_proc_t glGenVertexArrays = nullptr;
    glBindVertexArray_client_proc_t glBindVertexArray = nullptr;
    glDeleteVertexArrays_client_proc_t glDeleteVertexArrays = nullptr;
    glIsVertexArray_client_proc_t glIsVertexArray = nullptr;
    glMapBufferRange_client_proc_t glMapBufferRange = nullptr;
    glUnmapBuffer_client_proc_t glUnmapBuffer = nullptr;
    glFlushMappedBufferRange_client_proc_t glFlushMappedBufferRange = nullptr;
    glBindBufferRange_client_proc_t glBindBufferRange = nullptr;
    glBindBufferBase_client_proc_t glBindBufferBase = nullptr;
    glCopyBufferSubData_client_proc_t glCopyBufferSubData = nullptr;
    glClearBufferiv_client_proc_t glClearBufferiv = nullptr;
    glClearBufferuiv_client_proc_t glClearBufferuiv = nullptr;
    glClearBufferfv_client_proc_t glClearBufferfv = nullptr;
    glClearBufferfi_client_proc_t glClearBufferfi = nullptr;
    glGetBufferParameteri64v_client_proc_t glGetBufferParameteri64v = nullptr;
    glGetBufferPointerv_client_proc_t glGetBufferPointerv = nullptr;
    glUniformBlockBinding_client_proc_t glUniformBlockBinding = nullptr;
    glGetUniformBlockIndex_client_proc_t glGetUniformBlockIndex = nullptr;
    glGetUniformIndices_client_proc_t glGetUniformIndices = nullptr;
    glGetActiveUniformBlockiv_client_proc_t glGetActiveUniformBlockiv = nullptr;
    glGetActiveUniformBlockName_client_proc_t glGetActiveUniformBlockName = nullptr;
    glUniform1ui_client_proc_t glUniform1ui = nullptr;
    glUniform2ui_client_proc_t glUniform2ui = nullptr;
    glUniform3ui_client_proc_t glUniform3ui = nullptr;
    glUniform4ui_client_proc_t glUniform4ui = nullptr;
    glUniform1uiv_client_proc_t glUniform1uiv = nullptr;
    glUniform2uiv_client_proc_t glUniform2uiv = nullptr;
    glUniform3uiv_client_proc_t glUniform3uiv = nullptr;
    glUniform4uiv_client_proc_t glUniform4uiv = nullptr;
    glUniformMatrix2x3fv_client_proc_t glUniformMatrix2x3fv = nullptr;
    glUniformMatrix3x2fv_client_proc_t glUniformMatrix3x2fv = nullptr;
    glUniformMatrix2x4fv_client_proc_t glUniformMatrix2x4fv = nullptr;
    glUniformMatrix4x2fv_client_proc_t glUniformMatrix4x2fv = nullptr;
    glUniformMatrix3x4fv_client_proc_t glUniformMatrix3x4fv = nullptr;
    glUniformMatrix4x3fv_client_proc_t glUniformMatrix4x3fv = nullptr;
    glGetUniformuiv_client_proc_t glGetUniformuiv = nullptr;
    glGetActiveUniformsiv_client_proc_t glGetActiveUniformsiv = nullptr;
    glVertexAttribI4i_client_proc_t glVertexAttribI4i = nullptr;
    glVertexAttribI4ui_client_proc_t glVertexAttribI4ui = nullptr;
    glVertexAttribI4iv_client_proc_t glVertexAttribI4iv = nullptr;
    glVertexAttribI4uiv_client_proc_t glVertexAttribI4uiv = nullptr;
    glVertexAttribIPointer_client_proc_t glVertexAttribIPointer = nullptr;
    glGetVertexAttribIiv_client_proc_t glGetVertexAttribIiv = nullptr;
    glGetVertexAttribIuiv_client_proc_t glGetVertexAttribIuiv = nullptr;
    glVertexAttribDivisor_client_proc_t glVertexAttribDivisor = nullptr;
    glDrawArraysInstanced_client_proc_t glDrawArraysInstanced = nullptr;
    glDrawElementsInstanced_client_proc_t glDrawElementsInstanced = nullptr;
    glDrawRangeElements_client_proc_t glDrawRangeElements = nullptr;
    glFenceSync_client_proc_t glFenceSync = nullptr;
    glClientWaitSync_client_proc_t glClientWaitSync = nullptr;
    glWaitSync_client_proc_t glWaitSync = nullptr;
    glDeleteSync_client_proc_t glDeleteSync = nullptr;
    glIsSync_client_proc_t glIsSync = nullptr;
    glGetSynciv_client_proc_t glGetSynciv = nullptr;
    glDrawBuffers_client_proc_t glDrawBuffers = nullptr;
    glReadBuffer_client_proc_t glReadBuffer = nullptr;
    glBlitFramebuffer_client_proc_t glBlitFramebuffer = nullptr;
    glInvalidateFramebuffer_client_proc_t glInvalidateFramebuffer = nullptr;
    glInvalidateSubFramebuffer_client_proc_t glInvalidateSubFramebuffer = nullptr;
    glFramebufferTextureLayer_client_proc_t glFramebufferTextureLayer = nullptr;
    glRenderbufferStorageMultisample_client_proc_t glRenderbufferStorageMultisample = nullptr;
    glTexStorage2D_client_proc_t glTexStorage2D = nullptr;
    glGetInternalformativ_client_proc_t glGetInternalformativ = nullptr;
    glBeginTransformFeedback_client_proc_t glBeginTransformFeedback = nullptr;
    glEndTransformFeedback_client_proc_t glEndTransformFeedback = nullptr;
    glGenTransformFeedbacks_client_proc_t glGenTransformFeedbacks = nullptr;
    glDeleteTransformFeedbacks_client_proc_t glDeleteTransformFeedbacks = nullptr;
    glBindTransformFeedback_client_proc_t glBindTransformFeedback = nullptr;
    glPauseTransformFeedback_client_proc_t glPauseTransformFeedback = nullptr;
    glResumeTransformFeedback_client_proc_t glResumeTransformFeedback = nullptr;
    glIsTransformFeedback_client_proc_t glIsTransformFeedback = nullptr;
    glTransformFeedbackVaryings_client_proc_t glTransformFeedbackVaryings = nullptr;
    glGetTransformFeedbackVarying_client_proc_t glGetTransformFeedbackVarying = nullptr;
    glGenSamplers_client_proc_t glGenSamplers = nullptr;
    glDeleteSamplers_client_proc_t glDeleteSamplers = nullptr;
    glBindSampler_client_proc_t glBindSampler = nullptr;
    glSamplerParameterf_client_proc_t glSamplerParameterf = nullptr;
    glSamplerParameteri_client_proc_t glSamplerParameteri = nullptr;
    glSamplerParameterfv_client_proc_t glSamplerParameterfv = nullptr;
    glSamplerParameteriv_client_proc_t glSamplerParameteriv = nullptr;
    glGetSamplerParameterfv_client_proc_t glGetSamplerParameterfv = nullptr;
    glGetSamplerParameteriv_client_proc_t glGetSamplerParameteriv = nullptr;
    glIsSampler_client_proc_t glIsSampler = nullptr;
    glGenQueries_client_proc_t glGenQueries = nullptr;
    glDeleteQueries_client_proc_t glDeleteQueries = nullptr;
    glBeginQuery_client_proc_t glBeginQuery = nullptr;
    glEndQuery_client_proc_t glEndQuery = nullptr;
    glGetQueryiv_client_proc_t glGetQueryiv = nullptr;
    glGetQueryObjectuiv_client_proc_t glGetQueryObjectuiv = nullptr;
    glIsQuery_client_proc_t glIsQuery = nullptr;
    glProgramParameteri_client_proc_t glProgramParameteri = nullptr;
    glProgramBinary_client_proc_t glProgramBinary = nullptr;
    glGetProgramBinary_client_proc_t glGetProgramBinary = nullptr;
    glGetFragDataLocation_client_proc_t glGetFragDataLocation = nullptr;
    glGetInteger64v_client_proc_t glGetInteger64v = nullptr;
    glGetIntegeri_v_client_proc_t glGetIntegeri_v = nullptr;
    glGetInteger64i_v_client_proc_t glGetInteger64i_v = nullptr;
    glTexImage3D_client_proc_t glTexImage3D = nullptr;
    glTexStorage3D_client_proc_t glTexStorage3D = nullptr;
    glTexSubImage3D_client_proc_t glTexSubImage3D = nullptr;
    glCompressedTexImage3D_client_proc_t glCompressedTexImage3D = nullptr;
    glCompressedTexSubImage3D_client_proc_t glCompressedTexSubImage3D = nullptr;
    glCopyTexSubImage3D_client_proc_t glCopyTexSubImage3D = nullptr;
    glGetStringi_client_proc_t glGetStringi = nullptr;
    glGetBooleani_v_client_proc_t glGetBooleani_v = nullptr;
    glMemoryBarrier_client_proc_t glMemoryBarrier = nullptr;
    glMemoryBarrierByRegion_client_proc_t glMemoryBarrierByRegion = nullptr;
    glGenProgramPipelines_client_proc_t glGenProgramPipelines = nullptr;
    glDeleteProgramPipelines_client_proc_t glDeleteProgramPipelines = nullptr;
    glBindProgramPipeline_client_proc_t glBindProgramPipeline = nullptr;
    glGetProgramPipelineiv_client_proc_t glGetProgramPipelineiv = nullptr;
    glGetProgramPipelineInfoLog_client_proc_t glGetProgramPipelineInfoLog = nullptr;
    glValidateProgramPipeline_client_proc_t glValidateProgramPipeline = nullptr;
    glIsProgramPipeline_client_proc_t glIsProgramPipeline = nullptr;
    glUseProgramStages_client_proc_t glUseProgramStages = nullptr;
    glActiveShaderProgram_client_proc_t glActiveShaderProgram = nullptr;
    glCreateShaderProgramv_client_proc_t glCreateShaderProgramv = nullptr;
    glProgramUniform1f_client_proc_t glProgramUniform1f = nullptr;
    glProgramUniform2f_client_proc_t glProgramUniform2f = nullptr;
    glProgramUniform3f_client_proc_t glProgramUniform3f = nullptr;
    glProgramUniform4f_client_proc_t glProgramUniform4f = nullptr;
    glProgramUniform1i_client_proc_t glProgramUniform1i = nullptr;
    glProgramUniform2i_client_proc_t glProgramUniform2i = nullptr;
    glProgramUniform3i_client_proc_t glProgramUniform3i = nullptr;
    glProgramUniform4i_client_proc_t glProgramUniform4i = nullptr;
    glProgramUniform1ui_client_proc_t glProgramUniform1ui = nullptr;
    glProgramUniform2ui_client_proc_t glProgramUniform2ui = nullptr;
    glProgramUniform3ui_client_proc_t glProgramUniform3ui = nullptr;
    glProgramUniform4ui_client_proc_t glProgramUniform4ui = nullptr;
    glProgramUniform1fv_client_proc_t glProgramUniform1fv = nullptr;
    glProgramUniform2fv_client_proc_t glProgramUniform2fv = nullptr;
    glProgramUniform3fv_client_proc_t glProgramUniform3fv = nullptr;
    glProgramUniform4fv_client_proc_t glProgramUniform4fv = nullptr;
    glProgramUniform1iv_client_proc_t glProgramUniform1iv = nullptr;
    glProgramUniform2iv_client_proc_t glProgramUniform2iv = nullptr;
    glProgramUniform3iv_client_proc_t glProgramUniform3iv = nullptr;
    glProgramUniform4iv_client_proc_t glProgramUniform4iv = nullptr;
    glProgramUniform1uiv_client_proc_t glProgramUniform1uiv = nullptr;
    glProgramUniform2uiv_client_proc_t glProgramUniform2uiv = nullptr;
    glProgramUniform3uiv_client_proc_t glProgramUniform3uiv = nullptr;
    glProgramUniform4uiv_client_proc_t glProgramUniform4uiv = nullptr;
    glProgramUniformMatrix2fv_client_proc_t glProgramUniformMatrix2fv = nullptr;
    glProgramUniformMatrix3fv_client_proc_t glProgramUniformMatrix3fv = nullptr;
    glProgramUniformMatrix4fv_client_proc_t glProgramUniformMatrix4fv = nullptr;
    glProgramUniformMatrix2x3fv_client_proc_t glProgramUniformMatrix2x3fv = nullptr;
    glProgramUniformMatrix3x2fv_client_proc_t glProgramUniformMatrix3x2fv = nullptr;
    glProgramUniformMatrix2x4fv_client_proc_t glProgramUniformMatrix2x4fv = nullptr;
    glProgramUniformMatrix4x2fv_client_proc_t glProgramUniformMatrix4x2fv = nullptr;
    glProgramUniformMatrix3x4fv_client_proc_t glProgramUniformMatrix3x4fv = nullptr;
    glProgramUniformMatrix4x3fv_client_proc_t glProgramUniformMatrix4x3fv = nullptr;
    glGetProgramInterfaceiv_client_proc_t glGetProgramInterfaceiv = nullptr;
    glGetProgramResourceiv_client_proc_t glGetProgramResourceiv = nullptr;
    glGetProgramResourceIndex_client_proc_t glGetProgramResourceIndex = nullptr;
    glGetProgramResourceLocation_client_proc_t glGetProgramResourceLocation = nullptr;
    glGetProgramResourceName_client_proc_t glGetProgramResourceName = nullptr;
    glBindImageTexture_client_proc_t glBindImageTexture = nullptr;
    glDispatchCompute_client_proc_t glDispatchCompute = nullptr;
    glDispatchComputeIndirect_client_proc_t glDispatchComputeIndirect = nullptr;
    glBindVertexBuffer_client_proc_t glBindVertexBuffer = nullptr;
    glVertexAttribBinding_client_proc_t glVertexAttribBinding = nullptr;
    glVertexAttribFormat_client_proc_t glVertexAttribFormat = nullptr;
    glVertexAttribIFormat_client_proc_t glVertexAttribIFormat = nullptr;
    glVertexBindingDivisor_client_proc_t glVertexBindingDivisor = nullptr;
    glDrawArraysIndirect_client_proc_t glDrawArraysIndirect = nullptr;
    glDrawElementsIndirect_client_proc_t glDrawElementsIndirect = nullptr;
    glTexStorage2DMultisample_client_proc_t glTexStorage2DMultisample = nullptr;
    glSampleMaski_client_proc_t glSampleMaski = nullptr;
    glGetMultisamplefv_client_proc_t glGetMultisamplefv = nullptr;
    glFramebufferParameteri_client_proc_t glFramebufferParameteri = nullptr;
    glGetFramebufferParameteriv_client_proc_t glGetFramebufferParameteriv = nullptr;
    glGetTexLevelParameterfv_client_proc_t glGetTexLevelParameterfv = nullptr;
    glGetTexLevelParameteriv_client_proc_t glGetTexLevelParameteriv = nullptr;
    glEnableiEXT_client_proc_t glEnableiEXT = nullptr;
    glDisableiEXT_client_proc_t glDisableiEXT = nullptr;
    glBlendEquationiEXT_client_proc_t glBlendEquationiEXT = nullptr;
    glBlendEquationSeparateiEXT_client_proc_t glBlendEquationSeparateiEXT = nullptr;
    glBlendFunciEXT_client_proc_t glBlendFunciEXT = nullptr;
    glBlendFuncSeparateiEXT_client_proc_t glBlendFuncSeparateiEXT = nullptr;
    glColorMaskiEXT_client_proc_t glColorMaskiEXT = nullptr;
    glIsEnablediEXT_client_proc_t glIsEnablediEXT = nullptr;
    glCopyImageSubDataEXT_client_proc_t glCopyImageSubDataEXT = nullptr;
    glBlendBarrierKHR_client_proc_t glBlendBarrierKHR = nullptr;
    glTexParameterIivEXT_client_proc_t glTexParameterIivEXT = nullptr;
    glTexParameterIuivEXT_client_proc_t glTexParameterIuivEXT = nullptr;
    glGetTexParameterIivEXT_client_proc_t glGetTexParameterIivEXT = nullptr;
    glGetTexParameterIuivEXT_client_proc_t glGetTexParameterIuivEXT = nullptr;
    glSamplerParameterIivEXT_client_proc_t glSamplerParameterIivEXT = nullptr;
    glSamplerParameterIuivEXT_client_proc_t glSamplerParameterIuivEXT = nullptr;
    glGetSamplerParameterIivEXT_client_proc_t glGetSamplerParameterIivEXT = nullptr;
    glGetSamplerParameterIuivEXT_client_proc_t glGetSamplerParameterIuivEXT = nullptr;
    glVertexAttribPointerData_client_proc_t glVertexAttribPointerData = nullptr;
    glVertexAttribPointerOffset_client_proc_t glVertexAttribPointerOffset = nullptr;
    glDrawElementsOffset_client_proc_t glDrawElementsOffset = nullptr;
    glDrawElementsData_client_proc_t glDrawElementsData = nullptr;
    glGetCompressedTextureFormats_client_proc_t glGetCompressedTextureFormats = nullptr;
    glShaderString_client_proc_t glShaderString = nullptr;
    glFinishRoundTrip_client_proc_t glFinishRoundTrip = nullptr;
    glMapBufferRangeAEMU_client_proc_t glMapBufferRangeAEMU = nullptr;
    glUnmapBufferAEMU_client_proc_t glUnmapBufferAEMU = nullptr;
    glFlushMappedBufferRangeAEMU_client_proc_t glFlushMappedBufferRangeAEMU = nullptr;
    glReadPixelsOffsetAEMU_client_proc_t glReadPixelsOffsetAEMU = nullptr;
    glCompressedTexImage2DOffsetAEMU_client_proc_t glCompressedTexImage2DOffsetAEMU = nullptr;
    glCompressedTexSubImage2DOffsetAEMU_client_proc_t glCompressedTexSubImage2DOffsetAEMU = nullptr;
    glTexImage2DOffsetAEMU_client_proc_t glTexImage2DOffsetAEMU = nullptr;
    glTexSubImage2DOffsetAEMU_client_proc_t glTexSubImage2DOffsetAEMU = nullptr;
    glGetUniformIndicesAEMU_client_proc_t glGetUniformIndicesAEMU = nullptr;
    glVertexAttribIPointerOffsetAEMU_client_proc_t glVertexAttribIPointerOffsetAEMU = nullptr;
    glVertexAttribIPointerDataAEMU_client_proc_t glVertexAttribIPointerDataAEMU = nullptr;
    glDrawElementsInstancedDataAEMU_client_proc_t glDrawElementsInstancedDataAEMU = nullptr;
    glDrawElementsInstancedOffsetAEMU_client_proc_t glDrawElementsInstancedOffsetAEMU = nullptr;
    glDrawRangeElementsDataAEMU_client_proc_t glDrawRangeElementsDataAEMU = nullptr;
    glDrawRangeElementsOffsetAEMU_client_proc_t glDrawRangeElementsOffsetAEMU = nullptr;
    glFenceSyncAEMU_client_proc_t glFenceSyncAEMU = nullptr;
    glClientWaitSyncAEMU_client_proc_t glClientWaitSyncAEMU = nullptr;
    glWaitSyncAEMU_client_proc_t glWaitSyncAEMU = nullptr;
    glDeleteSyncAEMU_client_proc_t glDeleteSyncAEMU = nullptr;
    glIsSyncAEMU_client_proc_t glIsSyncAEMU = nullptr;
    glGetSyncivAEMU_client_proc_t glGetSyncivAEMU = nullptr;
    glTransformFeedbackVaryingsAEMU_client_proc_t glTransformFeedbackVaryingsAEMU = nullptr;
    glTexImage3DOffsetAEMU_client_proc_t glTexImage3DOffsetAEMU = nullptr;
    glTexSubImage3DOffsetAEMU_client_proc_t glTexSubImage3DOffsetAEMU = nullptr;
    glCompressedTexImage3DOffsetAEMU_client_proc_t glCompressedTexImage3DOffsetAEMU = nullptr;
    glCompressedTexSubImage3DOffsetAEMU_client_proc_t glCompressedTexSubImage3DOffsetAEMU = nullptr;
    glCreateShaderProgramvAEMU_client_proc_t glCreateShaderProgramvAEMU = nullptr;
    glDrawArraysIndirectDataAEMU_client_proc_t glDrawArraysIndirectDataAEMU = nullptr;
    glDrawArraysIndirectOffsetAEMU_client_proc_t glDrawArraysIndirectOffsetAEMU = nullptr;
    glDrawElementsIndirectDataAEMU_client_proc_t glDrawElementsIndirectDataAEMU = nullptr;
    glDrawElementsIndirectOffsetAEMU_client_proc_t glDrawElementsIndirectOffsetAEMU = nullptr;
    glUniformLayout_client_proc_t glUniformLayout = nullptr;

private:
    static bool m_isInit;
    void *m_GLESv2Encoder = nullptr;
    static std::unique_ptr<LoadSharedLib> m_loader;
    static std::mutex m_lock;
};
#endif // GL2_ENCODER_BASE_H
