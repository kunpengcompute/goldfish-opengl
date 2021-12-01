/*
 * Description:  GL2Encoder base class.
 */
#define LOG_TAG "GL2EncoderBase"
#include "GL2EncoderBase.h"
#include "GL2Encoder.h"
#include <string>
#include <climits>
#include <cstdlib>
#include <dlfcn.h>

#define GET_CONTEXT GL2EncoderBase *ctx = static_cast<GL2EncoderBase *>(self)

createGLESv2Encoder_proc_t GL2EncoderBase::createGLESv2EncoderFunc = nullptr;
deleteGLESv2Encoder_proc_t GL2EncoderBase::deleteGLESv2EncoderFunc = nullptr;
glActiveTexture_proc_t GL2EncoderBase::glActiveTextureFunc = nullptr;
glAttachShader_proc_t GL2EncoderBase::glAttachShaderFunc = nullptr;
glBindAttribLocation_proc_t GL2EncoderBase::glBindAttribLocationFunc = nullptr;
glBindBuffer_proc_t GL2EncoderBase::glBindBufferFunc = nullptr;
glBindFramebuffer_proc_t GL2EncoderBase::glBindFramebufferFunc = nullptr;
glBindRenderbuffer_proc_t GL2EncoderBase::glBindRenderbufferFunc = nullptr;
glBindTexture_proc_t GL2EncoderBase::glBindTextureFunc = nullptr;
glBlendColor_proc_t GL2EncoderBase::glBlendColorFunc = nullptr;
glBlendEquation_proc_t GL2EncoderBase::glBlendEquationFunc = nullptr;
glBlendEquationSeparate_proc_t GL2EncoderBase::glBlendEquationSeparateFunc = nullptr;
glBlendFunc_proc_t GL2EncoderBase::glBlendFuncFunc = nullptr;
glBlendFuncSeparate_proc_t GL2EncoderBase::glBlendFuncSeparateFunc = nullptr;
glBufferData_proc_t GL2EncoderBase::glBufferDataFunc = nullptr;
glBufferSubData_proc_t GL2EncoderBase::glBufferSubDataFunc = nullptr;
glCheckFramebufferStatus_proc_t GL2EncoderBase::glCheckFramebufferStatusFunc = nullptr;
glClear_proc_t GL2EncoderBase::glClearFunc = nullptr;
glClearColor_proc_t GL2EncoderBase::glClearColorFunc = nullptr;
glClearDepthf_proc_t GL2EncoderBase::glClearDepthfFunc = nullptr;
glClearStencil_proc_t GL2EncoderBase::glClearStencilFunc = nullptr;
glColorMask_proc_t GL2EncoderBase::glColorMaskFunc = nullptr;
glCompileShader_proc_t GL2EncoderBase::glCompileShaderFunc = nullptr;
glCompressedTexImage2D_proc_t GL2EncoderBase::glCompressedTexImage2DFunc = nullptr;
glCompressedTexSubImage2D_proc_t GL2EncoderBase::glCompressedTexSubImage2DFunc = nullptr;
glCopyTexImage2D_proc_t GL2EncoderBase::glCopyTexImage2DFunc = nullptr;
glCopyTexSubImage2D_proc_t GL2EncoderBase::glCopyTexSubImage2DFunc = nullptr;
glCreateProgram_proc_t GL2EncoderBase::glCreateProgramFunc = nullptr;
glCreateShader_proc_t GL2EncoderBase::glCreateShaderFunc = nullptr;
glCullFace_proc_t GL2EncoderBase::glCullFaceFunc = nullptr;
glDeleteBuffers_proc_t GL2EncoderBase::glDeleteBuffersFunc = nullptr;
glDeleteFramebuffers_proc_t GL2EncoderBase::glDeleteFramebuffersFunc = nullptr;
glDeleteProgram_proc_t GL2EncoderBase::glDeleteProgramFunc = nullptr;
glDeleteRenderbuffers_proc_t GL2EncoderBase::glDeleteRenderbuffersFunc = nullptr;
glDeleteShader_proc_t GL2EncoderBase::glDeleteShaderFunc = nullptr;
glDeleteTextures_proc_t GL2EncoderBase::glDeleteTexturesFunc = nullptr;
glDepthFunc_proc_t GL2EncoderBase::glDepthFuncFunc = nullptr;
glDepthMask_proc_t GL2EncoderBase::glDepthMaskFunc = nullptr;
glDepthRangef_proc_t GL2EncoderBase::glDepthRangefFunc = nullptr;
glDetachShader_proc_t GL2EncoderBase::glDetachShaderFunc = nullptr;
glDisable_proc_t GL2EncoderBase::glDisableFunc = nullptr;
glDisableVertexAttribArray_proc_t GL2EncoderBase::glDisableVertexAttribArrayFunc = nullptr;
glDrawArrays_proc_t GL2EncoderBase::glDrawArraysFunc = nullptr;
glDrawElements_proc_t GL2EncoderBase::glDrawElementsFunc = nullptr;
glEnable_proc_t GL2EncoderBase::glEnableFunc = nullptr;
glEnableVertexAttribArray_proc_t GL2EncoderBase::glEnableVertexAttribArrayFunc = nullptr;
glFlush_proc_t GL2EncoderBase::glFlushFunc = nullptr;
glFramebufferRenderbuffer_proc_t GL2EncoderBase::glFramebufferRenderbufferFunc = nullptr;
glFramebufferTexture2D_proc_t GL2EncoderBase::glFramebufferTexture2DFunc = nullptr;
glFrontFace_proc_t GL2EncoderBase::glFrontFaceFunc = nullptr;
glGenBuffers_proc_t GL2EncoderBase::glGenBuffersFunc = nullptr;
glGenerateMipmap_proc_t GL2EncoderBase::glGenerateMipmapFunc = nullptr;
glGenFramebuffers_proc_t GL2EncoderBase::glGenFramebuffersFunc = nullptr;
glGenRenderbuffers_proc_t GL2EncoderBase::glGenRenderbuffersFunc = nullptr;
glGenTextures_proc_t GL2EncoderBase::glGenTexturesFunc = nullptr;
glGetActiveAttrib_proc_t GL2EncoderBase::glGetActiveAttribFunc = nullptr;
glGetActiveUniform_proc_t GL2EncoderBase::glGetActiveUniformFunc = nullptr;
glGetAttachedShaders_proc_t GL2EncoderBase::glGetAttachedShadersFunc = nullptr;
glGetAttribLocation_proc_t GL2EncoderBase::glGetAttribLocationFunc = nullptr;
glGetBooleanv_proc_t GL2EncoderBase::glGetBooleanvFunc = nullptr;
glGetBufferParameteriv_proc_t GL2EncoderBase::glGetBufferParameterivFunc = nullptr;
glGetError_proc_t GL2EncoderBase::glGetErrorFunc = nullptr;
glGetFloatv_proc_t GL2EncoderBase::glGetFloatvFunc = nullptr;
glGetFramebufferAttachmentParameteriv_proc_t GL2EncoderBase::glGetFramebufferAttachmentParameterivFunc = nullptr;
glGetIntegerv_proc_t GL2EncoderBase::glGetIntegervFunc = nullptr;
glGetProgramiv_proc_t GL2EncoderBase::glGetProgramivFunc = nullptr;
glGetProgramInfoLog_proc_t GL2EncoderBase::glGetProgramInfoLogFunc = nullptr;
glGetRenderbufferParameteriv_proc_t GL2EncoderBase::glGetRenderbufferParameterivFunc = nullptr;
glGetShaderiv_proc_t GL2EncoderBase::glGetShaderivFunc = nullptr;
glGetShaderInfoLog_proc_t GL2EncoderBase::glGetShaderInfoLogFunc = nullptr;
glGetShaderPrecisionFormat_proc_t GL2EncoderBase::glGetShaderPrecisionFormatFunc = nullptr;
glGetShaderSource_proc_t GL2EncoderBase::glGetShaderSourceFunc = nullptr;
glGetString_proc_t GL2EncoderBase::glGetStringFunc = nullptr;
glGetTexParameterfv_proc_t GL2EncoderBase::glGetTexParameterfvFunc = nullptr;
glGetTexParameteriv_proc_t GL2EncoderBase::glGetTexParameterivFunc = nullptr;
glGetUniformfv_proc_t GL2EncoderBase::glGetUniformfvFunc = nullptr;
glGetUniformiv_proc_t GL2EncoderBase::glGetUniformivFunc = nullptr;
glGetUniformLocation_proc_t GL2EncoderBase::glGetUniformLocationFunc = nullptr;
glGetVertexAttribfv_proc_t GL2EncoderBase::glGetVertexAttribfvFunc = nullptr;
glGetVertexAttribiv_proc_t GL2EncoderBase::glGetVertexAttribivFunc = nullptr;
glGetVertexAttribPointerv_proc_t GL2EncoderBase::glGetVertexAttribPointervFunc = nullptr;
glHint_proc_t GL2EncoderBase::glHintFunc = nullptr;
glIsBuffer_proc_t GL2EncoderBase::glIsBufferFunc = nullptr;
glIsEnabled_proc_t GL2EncoderBase::glIsEnabledFunc = nullptr;
glIsFramebuffer_proc_t GL2EncoderBase::glIsFramebufferFunc = nullptr;
glIsProgram_proc_t GL2EncoderBase::glIsProgramFunc = nullptr;
glIsRenderbuffer_proc_t GL2EncoderBase::glIsRenderbufferFunc = nullptr;
glIsShader_proc_t GL2EncoderBase::glIsShaderFunc = nullptr;
glIsTexture_proc_t GL2EncoderBase::glIsTextureFunc = nullptr;
glLineWidth_proc_t GL2EncoderBase::glLineWidthFunc = nullptr;
glLinkProgram_proc_t GL2EncoderBase::glLinkProgramFunc = nullptr;
glPixelStorei_proc_t GL2EncoderBase::glPixelStoreiFunc = nullptr;
glPolygonOffset_proc_t GL2EncoderBase::glPolygonOffsetFunc = nullptr;
glReadPixels_proc_t GL2EncoderBase::glReadPixelsFunc = nullptr;
glReleaseShaderCompiler_proc_t GL2EncoderBase::glReleaseShaderCompilerFunc = nullptr;
glRenderbufferStorage_proc_t GL2EncoderBase::glRenderbufferStorageFunc = nullptr;
glSampleCoverage_proc_t GL2EncoderBase::glSampleCoverageFunc = nullptr;
glScissor_proc_t GL2EncoderBase::glScissorFunc = nullptr;
glShaderBinary_proc_t GL2EncoderBase::glShaderBinaryFunc = nullptr;
glShaderSource_proc_t GL2EncoderBase::glShaderSourceFunc = nullptr;
glStencilFunc_proc_t GL2EncoderBase::glStencilFuncFunc = nullptr;
glStencilFuncSeparate_proc_t GL2EncoderBase::glStencilFuncSeparateFunc = nullptr;
glStencilMask_proc_t GL2EncoderBase::glStencilMaskFunc = nullptr;
glStencilMaskSeparate_proc_t GL2EncoderBase::glStencilMaskSeparateFunc = nullptr;
glStencilOp_proc_t GL2EncoderBase::glStencilOpFunc = nullptr;
glStencilOpSeparate_proc_t GL2EncoderBase::glStencilOpSeparateFunc = nullptr;
glTexImage2D_proc_t GL2EncoderBase::glTexImage2DFunc = nullptr;
glTexParameterf_proc_t GL2EncoderBase::glTexParameterfFunc = nullptr;
glTexParameterfv_proc_t GL2EncoderBase::glTexParameterfvFunc = nullptr;
glTexParameteri_proc_t GL2EncoderBase::glTexParameteriFunc = nullptr;
glTexParameteriv_proc_t GL2EncoderBase::glTexParameterivFunc = nullptr;
glTexSubImage2D_proc_t GL2EncoderBase::glTexSubImage2DFunc = nullptr;
glUniform1f_proc_t GL2EncoderBase::glUniform1fFunc = nullptr;
glUniform1fv_proc_t GL2EncoderBase::glUniform1fvFunc = nullptr;
glUniform1i_proc_t GL2EncoderBase::glUniform1iFunc = nullptr;
glUniform1iv_proc_t GL2EncoderBase::glUniform1ivFunc = nullptr;
glUniform2f_proc_t GL2EncoderBase::glUniform2fFunc = nullptr;
glUniform2fv_proc_t GL2EncoderBase::glUniform2fvFunc = nullptr;
glUniform2i_proc_t GL2EncoderBase::glUniform2iFunc = nullptr;
glUniform2iv_proc_t GL2EncoderBase::glUniform2ivFunc = nullptr;
glUniform3f_proc_t GL2EncoderBase::glUniform3fFunc = nullptr;
glUniform3fv_proc_t GL2EncoderBase::glUniform3fvFunc = nullptr;
glUniform3i_proc_t GL2EncoderBase::glUniform3iFunc = nullptr;
glUniform3iv_proc_t GL2EncoderBase::glUniform3ivFunc = nullptr;
glUniform4f_proc_t GL2EncoderBase::glUniform4fFunc = nullptr;
glUniform4fv_proc_t GL2EncoderBase::glUniform4fvFunc = nullptr;
glUniform4i_proc_t GL2EncoderBase::glUniform4iFunc = nullptr;
glUniform4iv_proc_t GL2EncoderBase::glUniform4ivFunc = nullptr;
glUniformMatrix2fv_proc_t GL2EncoderBase::glUniformMatrix2fvFunc = nullptr;
glUniformMatrix3fv_proc_t GL2EncoderBase::glUniformMatrix3fvFunc = nullptr;
glUniformMatrix4fv_proc_t GL2EncoderBase::glUniformMatrix4fvFunc = nullptr;
glUseProgram_proc_t GL2EncoderBase::glUseProgramFunc = nullptr;
glValidateProgram_proc_t GL2EncoderBase::glValidateProgramFunc = nullptr;
glVertexAttrib1f_proc_t GL2EncoderBase::glVertexAttrib1fFunc = nullptr;
glVertexAttrib1fv_proc_t GL2EncoderBase::glVertexAttrib1fvFunc = nullptr;
glVertexAttrib2f_proc_t GL2EncoderBase::glVertexAttrib2fFunc = nullptr;
glVertexAttrib2fv_proc_t GL2EncoderBase::glVertexAttrib2fvFunc = nullptr;
glVertexAttrib3f_proc_t GL2EncoderBase::glVertexAttrib3fFunc = nullptr;
glVertexAttrib3fv_proc_t GL2EncoderBase::glVertexAttrib3fvFunc = nullptr;
glVertexAttrib4f_proc_t GL2EncoderBase::glVertexAttrib4fFunc = nullptr;
glVertexAttrib4fv_proc_t GL2EncoderBase::glVertexAttrib4fvFunc = nullptr;
glVertexAttribPointer_proc_t GL2EncoderBase::glVertexAttribPointerFunc = nullptr;
glViewport_proc_t GL2EncoderBase::glViewportFunc = nullptr;
glEGLImageTargetTexture2DOES_proc_t GL2EncoderBase::glEGLImageTargetTexture2DOESFunc = nullptr;
glEGLImageTargetRenderbufferStorageOES_proc_t GL2EncoderBase::glEGLImageTargetRenderbufferStorageOESFunc =
    nullptr;
glGetProgramBinaryOES_proc_t GL2EncoderBase::glGetProgramBinaryOESFunc = nullptr;
glProgramBinaryOES_proc_t GL2EncoderBase::glProgramBinaryOESFunc = nullptr;
glMapBufferOES_proc_t GL2EncoderBase::glMapBufferOESFunc = nullptr;
glUnmapBufferOES_proc_t GL2EncoderBase::glUnmapBufferOESFunc = nullptr;
glTexImage3DOES_proc_t GL2EncoderBase::glTexImage3DOESFunc = nullptr;
glTexSubImage3DOES_proc_t GL2EncoderBase::glTexSubImage3DOESFunc = nullptr;
glCopyTexSubImage3DOES_proc_t GL2EncoderBase::glCopyTexSubImage3DOESFunc = nullptr;
glCompressedTexImage3DOES_proc_t GL2EncoderBase::glCompressedTexImage3DOESFunc = nullptr;
glCompressedTexSubImage3DOES_proc_t GL2EncoderBase::glCompressedTexSubImage3DOESFunc = nullptr;
glFramebufferTexture3DOES_proc_t GL2EncoderBase::glFramebufferTexture3DOESFunc = nullptr;
glBindVertexArrayOES_proc_t GL2EncoderBase::glBindVertexArrayOESFunc = nullptr;
glDeleteVertexArraysOES_proc_t GL2EncoderBase::glDeleteVertexArraysOESFunc = nullptr;
glGenVertexArraysOES_proc_t GL2EncoderBase::glGenVertexArraysOESFunc = nullptr;
glIsVertexArrayOES_proc_t GL2EncoderBase::glIsVertexArrayOESFunc = nullptr;
glDiscardFramebufferEXT_proc_t GL2EncoderBase::glDiscardFramebufferEXTFunc = nullptr;
glMultiDrawArraysEXT_proc_t GL2EncoderBase::glMultiDrawArraysEXTFunc = nullptr;
glMultiDrawElementsEXT_proc_t GL2EncoderBase::glMultiDrawElementsEXTFunc = nullptr;
glGetPerfMonitorGroupsAMD_proc_t GL2EncoderBase::glGetPerfMonitorGroupsAMDFunc = nullptr;
glGetPerfMonitorCountersAMD_proc_t GL2EncoderBase::glGetPerfMonitorCountersAMDFunc = nullptr;
glGetPerfMonitorGroupStringAMD_proc_t GL2EncoderBase::glGetPerfMonitorGroupStringAMDFunc = nullptr;
glGetPerfMonitorCounterStringAMD_proc_t GL2EncoderBase::glGetPerfMonitorCounterStringAMDFunc = nullptr;
glGetPerfMonitorCounterInfoAMD_proc_t GL2EncoderBase::glGetPerfMonitorCounterInfoAMDFunc = nullptr;
glGenPerfMonitorsAMD_proc_t GL2EncoderBase::glGenPerfMonitorsAMDFunc = nullptr;
glDeletePerfMonitorsAMD_proc_t GL2EncoderBase::glDeletePerfMonitorsAMDFunc = nullptr;
glSelectPerfMonitorCountersAMD_proc_t GL2EncoderBase::glSelectPerfMonitorCountersAMDFunc = nullptr;
glBeginPerfMonitorAMD_proc_t GL2EncoderBase::glBeginPerfMonitorAMDFunc = nullptr;
glEndPerfMonitorAMD_proc_t GL2EncoderBase::glEndPerfMonitorAMDFunc = nullptr;
glGetPerfMonitorCounterDataAMD_proc_t GL2EncoderBase::glGetPerfMonitorCounterDataAMDFunc = nullptr;
glRenderbufferStorageMultisampleIMG_proc_t GL2EncoderBase::glRenderbufferStorageMultisampleIMGFunc = nullptr;
glFramebufferTexture2DMultisampleIMG_proc_t GL2EncoderBase::glFramebufferTexture2DMultisampleIMGFunc = nullptr;
glDeleteFencesNV_proc_t GL2EncoderBase::glDeleteFencesNVFunc = nullptr;
glGenFencesNV_proc_t GL2EncoderBase::glGenFencesNVFunc = nullptr;
glIsFenceNV_proc_t GL2EncoderBase::glIsFenceNVFunc = nullptr;
glTestFenceNV_proc_t GL2EncoderBase::glTestFenceNVFunc = nullptr;
glGetFenceivNV_proc_t GL2EncoderBase::glGetFenceivNVFunc = nullptr;
glFinishFenceNV_proc_t GL2EncoderBase::glFinishFenceNVFunc = nullptr;
glSetFenceNV_proc_t GL2EncoderBase::glSetFenceNVFunc = nullptr;
glCoverageMaskNV_proc_t GL2EncoderBase::glCoverageMaskNVFunc = nullptr;
glCoverageOperationNV_proc_t GL2EncoderBase::glCoverageOperationNVFunc = nullptr;
glGetDriverControlsQCOM_proc_t GL2EncoderBase::glGetDriverControlsQCOMFunc = nullptr;
glGetDriverControlStringQCOM_proc_t GL2EncoderBase::glGetDriverControlStringQCOMFunc = nullptr;
glEnableDriverControlQCOM_proc_t GL2EncoderBase::glEnableDriverControlQCOMFunc = nullptr;
glDisableDriverControlQCOM_proc_t GL2EncoderBase::glDisableDriverControlQCOMFunc = nullptr;
glExtGetTexturesQCOM_proc_t GL2EncoderBase::glExtGetTexturesQCOMFunc = nullptr;
glExtGetBuffersQCOM_proc_t GL2EncoderBase::glExtGetBuffersQCOMFunc = nullptr;
glExtGetRenderbuffersQCOM_proc_t GL2EncoderBase::glExtGetRenderbuffersQCOMFunc = nullptr;
glExtGetFramebuffersQCOM_proc_t GL2EncoderBase::glExtGetFramebuffersQCOMFunc = nullptr;
glExtGetTexLevelParameterivQCOM_proc_t GL2EncoderBase::glExtGetTexLevelParameterivQCOMFunc = nullptr;
glExtTexObjectStateOverrideiQCOM_proc_t GL2EncoderBase::glExtTexObjectStateOverrideiQCOMFunc = nullptr;
glExtGetTexSubImageQCOM_proc_t GL2EncoderBase::glExtGetTexSubImageQCOMFunc = nullptr;
glExtGetBufferPointervQCOM_proc_t GL2EncoderBase::glExtGetBufferPointervQCOMFunc = nullptr;
glExtGetShadersQCOM_proc_t GL2EncoderBase::glExtGetShadersQCOMFunc = nullptr;
glExtGetProgramsQCOM_proc_t GL2EncoderBase::glExtGetProgramsQCOMFunc = nullptr;
glExtIsProgramBinaryQCOM_proc_t GL2EncoderBase::glExtIsProgramBinaryQCOMFunc = nullptr;
glExtGetProgramBinarySourceQCOM_proc_t GL2EncoderBase::glExtGetProgramBinarySourceQCOMFunc = nullptr;
glStartTilingQCOM_proc_t GL2EncoderBase::glStartTilingQCOMFunc = nullptr;
glEndTilingQCOM_proc_t GL2EncoderBase::glEndTilingQCOMFunc = nullptr;
glGenVertexArrays_proc_t GL2EncoderBase::glGenVertexArraysFunc = nullptr;
glBindVertexArray_proc_t GL2EncoderBase::glBindVertexArrayFunc = nullptr;
glDeleteVertexArrays_proc_t GL2EncoderBase::glDeleteVertexArraysFunc = nullptr;
glIsVertexArray_proc_t GL2EncoderBase::glIsVertexArrayFunc = nullptr;
glMapBufferRange_proc_t GL2EncoderBase::glMapBufferRangeFunc = nullptr;
glUnmapBuffer_proc_t GL2EncoderBase::glUnmapBufferFunc = nullptr;
glFlushMappedBufferRange_proc_t GL2EncoderBase::glFlushMappedBufferRangeFunc = nullptr;
glBindBufferRange_proc_t GL2EncoderBase::glBindBufferRangeFunc = nullptr;
glBindBufferBase_proc_t GL2EncoderBase::glBindBufferBaseFunc = nullptr;
glCopyBufferSubData_proc_t GL2EncoderBase::glCopyBufferSubDataFunc = nullptr;
glClearBufferiv_proc_t GL2EncoderBase::glClearBufferivFunc = nullptr;
glClearBufferuiv_proc_t GL2EncoderBase::glClearBufferuivFunc = nullptr;
glClearBufferfv_proc_t GL2EncoderBase::glClearBufferfvFunc = nullptr;
glClearBufferfi_proc_t GL2EncoderBase::glClearBufferfiFunc = nullptr;
glGetBufferParameteri64v_proc_t GL2EncoderBase::glGetBufferParameteri64vFunc = nullptr;
glGetBufferPointerv_proc_t GL2EncoderBase::glGetBufferPointervFunc = nullptr;
glUniformBlockBinding_proc_t GL2EncoderBase::glUniformBlockBindingFunc = nullptr;
glGetUniformBlockIndex_proc_t GL2EncoderBase::glGetUniformBlockIndexFunc = nullptr;
glGetUniformIndices_proc_t GL2EncoderBase::glGetUniformIndicesFunc = nullptr;
glGetActiveUniformBlockiv_proc_t GL2EncoderBase::glGetActiveUniformBlockivFunc = nullptr;
glGetActiveUniformBlockName_proc_t GL2EncoderBase::glGetActiveUniformBlockNameFunc = nullptr;
glUniform1ui_proc_t GL2EncoderBase::glUniform1uiFunc = nullptr;
glUniform2ui_proc_t GL2EncoderBase::glUniform2uiFunc = nullptr;
glUniform3ui_proc_t GL2EncoderBase::glUniform3uiFunc = nullptr;
glUniform4ui_proc_t GL2EncoderBase::glUniform4uiFunc = nullptr;
glUniform1uiv_proc_t GL2EncoderBase::glUniform1uivFunc = nullptr;
glUniform2uiv_proc_t GL2EncoderBase::glUniform2uivFunc = nullptr;
glUniform3uiv_proc_t GL2EncoderBase::glUniform3uivFunc = nullptr;
glUniform4uiv_proc_t GL2EncoderBase::glUniform4uivFunc = nullptr;
glUniformMatrix2x3fv_proc_t GL2EncoderBase::glUniformMatrix2x3fvFunc = nullptr;
glUniformMatrix3x2fv_proc_t GL2EncoderBase::glUniformMatrix3x2fvFunc = nullptr;
glUniformMatrix2x4fv_proc_t GL2EncoderBase::glUniformMatrix2x4fvFunc = nullptr;
glUniformMatrix4x2fv_proc_t GL2EncoderBase::glUniformMatrix4x2fvFunc = nullptr;
glUniformMatrix3x4fv_proc_t GL2EncoderBase::glUniformMatrix3x4fvFunc = nullptr;
glUniformMatrix4x3fv_proc_t GL2EncoderBase::glUniformMatrix4x3fvFunc = nullptr;
glGetUniformuiv_proc_t GL2EncoderBase::glGetUniformuivFunc = nullptr;
glGetActiveUniformsiv_proc_t GL2EncoderBase::glGetActiveUniformsivFunc = nullptr;
glVertexAttribI4i_proc_t GL2EncoderBase::glVertexAttribI4iFunc = nullptr;
glVertexAttribI4ui_proc_t GL2EncoderBase::glVertexAttribI4uiFunc = nullptr;
glVertexAttribI4iv_proc_t GL2EncoderBase::glVertexAttribI4ivFunc = nullptr;
glVertexAttribI4uiv_proc_t GL2EncoderBase::glVertexAttribI4uivFunc = nullptr;
glVertexAttribIPointer_proc_t GL2EncoderBase::glVertexAttribIPointerFunc = nullptr;
glGetVertexAttribIiv_proc_t GL2EncoderBase::glGetVertexAttribIivFunc = nullptr;
glGetVertexAttribIuiv_proc_t GL2EncoderBase::glGetVertexAttribIuivFunc = nullptr;
glVertexAttribDivisor_proc_t GL2EncoderBase::glVertexAttribDivisorFunc = nullptr;
glDrawArraysInstanced_proc_t GL2EncoderBase::glDrawArraysInstancedFunc = nullptr;
glDrawElementsInstanced_proc_t GL2EncoderBase::glDrawElementsInstancedFunc = nullptr;
glDrawRangeElements_proc_t GL2EncoderBase::glDrawRangeElementsFunc = nullptr;
glFenceSync_proc_t GL2EncoderBase::glFenceSyncFunc = nullptr;
glClientWaitSync_proc_t GL2EncoderBase::glClientWaitSyncFunc = nullptr;
glWaitSync_proc_t GL2EncoderBase::glWaitSyncFunc = nullptr;
glDeleteSync_proc_t GL2EncoderBase::glDeleteSyncFunc = nullptr;
glIsSync_proc_t GL2EncoderBase::glIsSyncFunc = nullptr;
glGetSynciv_proc_t GL2EncoderBase::glGetSyncivFunc = nullptr;
glDrawBuffers_proc_t GL2EncoderBase::glDrawBuffersFunc = nullptr;
glReadBuffer_proc_t GL2EncoderBase::glReadBufferFunc = nullptr;
glBlitFramebuffer_proc_t GL2EncoderBase::glBlitFramebufferFunc = nullptr;
glInvalidateFramebuffer_proc_t GL2EncoderBase::glInvalidateFramebufferFunc = nullptr;
glInvalidateSubFramebuffer_proc_t GL2EncoderBase::glInvalidateSubFramebufferFunc = nullptr;
glFramebufferTextureLayer_proc_t GL2EncoderBase::glFramebufferTextureLayerFunc = nullptr;
glRenderbufferStorageMultisample_proc_t GL2EncoderBase::glRenderbufferStorageMultisampleFunc = nullptr;
glTexStorage2D_proc_t GL2EncoderBase::glTexStorage2DFunc = nullptr;
glGetInternalformativ_proc_t GL2EncoderBase::glGetInternalformativFunc = nullptr;
glBeginTransformFeedback_proc_t GL2EncoderBase::glBeginTransformFeedbackFunc = nullptr;
glEndTransformFeedback_proc_t GL2EncoderBase::glEndTransformFeedbackFunc = nullptr;
glGenTransformFeedbacks_proc_t GL2EncoderBase::glGenTransformFeedbacksFunc = nullptr;
glDeleteTransformFeedbacks_proc_t GL2EncoderBase::glDeleteTransformFeedbacksFunc = nullptr;
glBindTransformFeedback_proc_t GL2EncoderBase::glBindTransformFeedbackFunc = nullptr;
glPauseTransformFeedback_proc_t GL2EncoderBase::glPauseTransformFeedbackFunc = nullptr;
glResumeTransformFeedback_proc_t GL2EncoderBase::glResumeTransformFeedbackFunc = nullptr;
glIsTransformFeedback_proc_t GL2EncoderBase::glIsTransformFeedbackFunc = nullptr;
glTransformFeedbackVaryings_proc_t GL2EncoderBase::glTransformFeedbackVaryingsFunc = nullptr;
glGetTransformFeedbackVarying_proc_t GL2EncoderBase::glGetTransformFeedbackVaryingFunc = nullptr;
glGenSamplers_proc_t GL2EncoderBase::glGenSamplersFunc = nullptr;
glDeleteSamplers_proc_t GL2EncoderBase::glDeleteSamplersFunc = nullptr;
glBindSampler_proc_t GL2EncoderBase::glBindSamplerFunc = nullptr;
glSamplerParameterf_proc_t GL2EncoderBase::glSamplerParameterfFunc = nullptr;
glSamplerParameteri_proc_t GL2EncoderBase::glSamplerParameteriFunc = nullptr;
glSamplerParameterfv_proc_t GL2EncoderBase::glSamplerParameterfvFunc = nullptr;
glSamplerParameteriv_proc_t GL2EncoderBase::glSamplerParameterivFunc = nullptr;
glGetSamplerParameterfv_proc_t GL2EncoderBase::glGetSamplerParameterfvFunc = nullptr;
glGetSamplerParameteriv_proc_t GL2EncoderBase::glGetSamplerParameterivFunc = nullptr;
glIsSampler_proc_t GL2EncoderBase::glIsSamplerFunc = nullptr;
glGenQueries_proc_t GL2EncoderBase::glGenQueriesFunc = nullptr;
glDeleteQueries_proc_t GL2EncoderBase::glDeleteQueriesFunc = nullptr;
glBeginQuery_proc_t GL2EncoderBase::glBeginQueryFunc = nullptr;
glEndQuery_proc_t GL2EncoderBase::glEndQueryFunc = nullptr;
glGetQueryiv_proc_t GL2EncoderBase::glGetQueryivFunc = nullptr;
glGetQueryObjectuiv_proc_t GL2EncoderBase::glGetQueryObjectuivFunc = nullptr;
glIsQuery_proc_t GL2EncoderBase::glIsQueryFunc = nullptr;
glProgramParameteri_proc_t GL2EncoderBase::glProgramParameteriFunc = nullptr;
glProgramBinary_proc_t GL2EncoderBase::glProgramBinaryFunc = nullptr;
glGetProgramBinary_proc_t GL2EncoderBase::glGetProgramBinaryFunc = nullptr;
glGetFragDataLocation_proc_t GL2EncoderBase::glGetFragDataLocationFunc = nullptr;
glGetInteger64v_proc_t GL2EncoderBase::glGetInteger64vFunc = nullptr;
glGetIntegeri_v_proc_t GL2EncoderBase::glGetIntegeri_vFunc = nullptr;
glGetInteger64i_v_proc_t GL2EncoderBase::glGetInteger64i_vFunc = nullptr;
glTexImage3D_proc_t GL2EncoderBase::glTexImage3DFunc = nullptr;
glTexStorage3D_proc_t GL2EncoderBase::glTexStorage3DFunc = nullptr;
glTexSubImage3D_proc_t GL2EncoderBase::glTexSubImage3DFunc = nullptr;
glCompressedTexImage3D_proc_t GL2EncoderBase::glCompressedTexImage3DFunc = nullptr;
glCompressedTexSubImage3D_proc_t GL2EncoderBase::glCompressedTexSubImage3DFunc = nullptr;
glCopyTexSubImage3D_proc_t GL2EncoderBase::glCopyTexSubImage3DFunc = nullptr;
glGetStringi_proc_t GL2EncoderBase::glGetStringiFunc = nullptr;
glGetBooleani_v_proc_t GL2EncoderBase::glGetBooleani_vFunc = nullptr;
glMemoryBarrier_proc_t GL2EncoderBase::glMemoryBarrierFunc = nullptr;
glMemoryBarrierByRegion_proc_t GL2EncoderBase::glMemoryBarrierByRegionFunc = nullptr;
glGenProgramPipelines_proc_t GL2EncoderBase::glGenProgramPipelinesFunc = nullptr;
glDeleteProgramPipelines_proc_t GL2EncoderBase::glDeleteProgramPipelinesFunc = nullptr;
glBindProgramPipeline_proc_t GL2EncoderBase::glBindProgramPipelineFunc = nullptr;
glGetProgramPipelineiv_proc_t GL2EncoderBase::glGetProgramPipelineivFunc = nullptr;
glGetProgramPipelineInfoLog_proc_t GL2EncoderBase::glGetProgramPipelineInfoLogFunc = nullptr;
glValidateProgramPipeline_proc_t GL2EncoderBase::glValidateProgramPipelineFunc = nullptr;
glIsProgramPipeline_proc_t GL2EncoderBase::glIsProgramPipelineFunc = nullptr;
glUseProgramStages_proc_t GL2EncoderBase::glUseProgramStagesFunc = nullptr;
glActiveShaderProgram_proc_t GL2EncoderBase::glActiveShaderProgramFunc = nullptr;
glCreateShaderProgramv_proc_t GL2EncoderBase::glCreateShaderProgramvFunc = nullptr;
glProgramUniform1f_proc_t GL2EncoderBase::glProgramUniform1fFunc = nullptr;
glProgramUniform2f_proc_t GL2EncoderBase::glProgramUniform2fFunc = nullptr;
glProgramUniform3f_proc_t GL2EncoderBase::glProgramUniform3fFunc = nullptr;
glProgramUniform4f_proc_t GL2EncoderBase::glProgramUniform4fFunc = nullptr;
glProgramUniform1i_proc_t GL2EncoderBase::glProgramUniform1iFunc = nullptr;
glProgramUniform2i_proc_t GL2EncoderBase::glProgramUniform2iFunc = nullptr;
glProgramUniform3i_proc_t GL2EncoderBase::glProgramUniform3iFunc = nullptr;
glProgramUniform4i_proc_t GL2EncoderBase::glProgramUniform4iFunc = nullptr;
glProgramUniform1ui_proc_t GL2EncoderBase::glProgramUniform1uiFunc = nullptr;
glProgramUniform2ui_proc_t GL2EncoderBase::glProgramUniform2uiFunc = nullptr;
glProgramUniform3ui_proc_t GL2EncoderBase::glProgramUniform3uiFunc = nullptr;
glProgramUniform4ui_proc_t GL2EncoderBase::glProgramUniform4uiFunc = nullptr;
glProgramUniform1fv_proc_t GL2EncoderBase::glProgramUniform1fvFunc = nullptr;
glProgramUniform2fv_proc_t GL2EncoderBase::glProgramUniform2fvFunc = nullptr;
glProgramUniform3fv_proc_t GL2EncoderBase::glProgramUniform3fvFunc = nullptr;
glProgramUniform4fv_proc_t GL2EncoderBase::glProgramUniform4fvFunc = nullptr;
glProgramUniform1iv_proc_t GL2EncoderBase::glProgramUniform1ivFunc = nullptr;
glProgramUniform2iv_proc_t GL2EncoderBase::glProgramUniform2ivFunc = nullptr;
glProgramUniform3iv_proc_t GL2EncoderBase::glProgramUniform3ivFunc = nullptr;
glProgramUniform4iv_proc_t GL2EncoderBase::glProgramUniform4ivFunc = nullptr;
glProgramUniform1uiv_proc_t GL2EncoderBase::glProgramUniform1uivFunc = nullptr;
glProgramUniform2uiv_proc_t GL2EncoderBase::glProgramUniform2uivFunc = nullptr;
glProgramUniform3uiv_proc_t GL2EncoderBase::glProgramUniform3uivFunc = nullptr;
glProgramUniform4uiv_proc_t GL2EncoderBase::glProgramUniform4uivFunc = nullptr;
glProgramUniformMatrix2fv_proc_t GL2EncoderBase::glProgramUniformMatrix2fvFunc = nullptr;
glProgramUniformMatrix3fv_proc_t GL2EncoderBase::glProgramUniformMatrix3fvFunc = nullptr;
glProgramUniformMatrix4fv_proc_t GL2EncoderBase::glProgramUniformMatrix4fvFunc = nullptr;
glProgramUniformMatrix2x3fv_proc_t GL2EncoderBase::glProgramUniformMatrix2x3fvFunc = nullptr;
glProgramUniformMatrix3x2fv_proc_t GL2EncoderBase::glProgramUniformMatrix3x2fvFunc = nullptr;
glProgramUniformMatrix2x4fv_proc_t GL2EncoderBase::glProgramUniformMatrix2x4fvFunc = nullptr;
glProgramUniformMatrix4x2fv_proc_t GL2EncoderBase::glProgramUniformMatrix4x2fvFunc = nullptr;
glProgramUniformMatrix3x4fv_proc_t GL2EncoderBase::glProgramUniformMatrix3x4fvFunc = nullptr;
glProgramUniformMatrix4x3fv_proc_t GL2EncoderBase::glProgramUniformMatrix4x3fvFunc = nullptr;
glGetProgramInterfaceiv_proc_t GL2EncoderBase::glGetProgramInterfaceivFunc = nullptr;
glGetProgramResourceiv_proc_t GL2EncoderBase::glGetProgramResourceivFunc = nullptr;
glGetProgramResourceIndex_proc_t GL2EncoderBase::glGetProgramResourceIndexFunc = nullptr;
glGetProgramResourceLocation_proc_t GL2EncoderBase::glGetProgramResourceLocationFunc = nullptr;
glGetProgramResourceName_proc_t GL2EncoderBase::glGetProgramResourceNameFunc = nullptr;
glBindImageTexture_proc_t GL2EncoderBase::glBindImageTextureFunc = nullptr;
glDispatchCompute_proc_t GL2EncoderBase::glDispatchComputeFunc = nullptr;
glDispatchComputeIndirect_proc_t GL2EncoderBase::glDispatchComputeIndirectFunc = nullptr;
glBindVertexBuffer_proc_t GL2EncoderBase::glBindVertexBufferFunc = nullptr;
glVertexAttribBinding_proc_t GL2EncoderBase::glVertexAttribBindingFunc = nullptr;
glVertexAttribFormat_proc_t GL2EncoderBase::glVertexAttribFormatFunc = nullptr;
glVertexAttribIFormat_proc_t GL2EncoderBase::glVertexAttribIFormatFunc = nullptr;
glVertexBindingDivisor_proc_t GL2EncoderBase::glVertexBindingDivisorFunc = nullptr;
glDrawArraysIndirect_proc_t GL2EncoderBase::glDrawArraysIndirectFunc = nullptr;
glDrawElementsIndirect_proc_t GL2EncoderBase::glDrawElementsIndirectFunc = nullptr;
glTexStorage2DMultisample_proc_t GL2EncoderBase::glTexStorage2DMultisampleFunc = nullptr;
glSampleMaski_proc_t GL2EncoderBase::glSampleMaskiFunc = nullptr;
glGetMultisamplefv_proc_t GL2EncoderBase::glGetMultisamplefvFunc = nullptr;
glFramebufferParameteri_proc_t GL2EncoderBase::glFramebufferParameteriFunc = nullptr;
glGetFramebufferParameteriv_proc_t GL2EncoderBase::glGetFramebufferParameterivFunc = nullptr;
glGetTexLevelParameterfv_proc_t GL2EncoderBase::glGetTexLevelParameterfvFunc = nullptr;
glGetTexLevelParameteriv_proc_t GL2EncoderBase::glGetTexLevelParameterivFunc = nullptr;
glEnableiEXT_proc_t GL2EncoderBase::glEnableiEXTFunc = nullptr;
glDisableiEXT_proc_t GL2EncoderBase::glDisableiEXTFunc = nullptr;
glBlendEquationiEXT_proc_t GL2EncoderBase::glBlendEquationiEXTFunc = nullptr;
glBlendEquationSeparateiEXT_proc_t GL2EncoderBase::glBlendEquationSeparateiEXTFunc = nullptr;
glBlendFunciEXT_proc_t GL2EncoderBase::glBlendFunciEXTFunc = nullptr;
glBlendFuncSeparateiEXT_proc_t GL2EncoderBase::glBlendFuncSeparateiEXTFunc = nullptr;
glColorMaskiEXT_proc_t GL2EncoderBase::glColorMaskiEXTFunc = nullptr;
glIsEnablediEXT_proc_t GL2EncoderBase::glIsEnablediEXTFunc = nullptr;
glCopyImageSubDataEXT_proc_t GL2EncoderBase::glCopyImageSubDataEXTFunc = nullptr;
glBlendBarrierKHR_proc_t GL2EncoderBase::glBlendBarrierKHRFunc = nullptr;
glTexParameterIivEXT_proc_t GL2EncoderBase::glTexParameterIivEXTFunc = nullptr;
glTexParameterIuivEXT_proc_t GL2EncoderBase::glTexParameterIuivEXTFunc = nullptr;
glGetTexParameterIivEXT_proc_t GL2EncoderBase::glGetTexParameterIivEXTFunc = nullptr;
glGetTexParameterIuivEXT_proc_t GL2EncoderBase::glGetTexParameterIuivEXTFunc = nullptr;
glSamplerParameterIivEXT_proc_t GL2EncoderBase::glSamplerParameterIivEXTFunc = nullptr;
glSamplerParameterIuivEXT_proc_t GL2EncoderBase::glSamplerParameterIuivEXTFunc = nullptr;
glGetSamplerParameterIivEXT_proc_t GL2EncoderBase::glGetSamplerParameterIivEXTFunc = nullptr;
glGetSamplerParameterIuivEXT_proc_t GL2EncoderBase::glGetSamplerParameterIuivEXTFunc = nullptr;
glVertexAttribPointerData_proc_t GL2EncoderBase::glVertexAttribPointerDataFunc = nullptr;
glVertexAttribPointerOffset_proc_t GL2EncoderBase::glVertexAttribPointerOffsetFunc = nullptr;
glDrawElementsOffset_proc_t GL2EncoderBase::glDrawElementsOffsetFunc = nullptr;
glDrawElementsData_proc_t GL2EncoderBase::glDrawElementsDataFunc = nullptr;
glGetCompressedTextureFormats_proc_t GL2EncoderBase::glGetCompressedTextureFormatsFunc = nullptr;
glShaderString_proc_t GL2EncoderBase::glShaderStringFunc = nullptr;
glFinishRoundTrip_proc_t GL2EncoderBase::glFinishRoundTripFunc = nullptr;
glMapBufferRangeAEMU_proc_t GL2EncoderBase::glMapBufferRangeAEMUFunc = nullptr;
glUnmapBufferAEMU_proc_t GL2EncoderBase::glUnmapBufferAEMUFunc = nullptr;
glFlushMappedBufferRangeAEMU_proc_t GL2EncoderBase::glFlushMappedBufferRangeAEMUFunc = nullptr;
glReadPixelsOffsetAEMU_proc_t GL2EncoderBase::glReadPixelsOffsetAEMUFunc = nullptr;
glCompressedTexImage2DOffsetAEMU_proc_t GL2EncoderBase::glCompressedTexImage2DOffsetAEMUFunc = nullptr;
glCompressedTexSubImage2DOffsetAEMU_proc_t GL2EncoderBase::glCompressedTexSubImage2DOffsetAEMUFunc = nullptr;
glTexImage2DOffsetAEMU_proc_t GL2EncoderBase::glTexImage2DOffsetAEMUFunc = nullptr;
glTexSubImage2DOffsetAEMU_proc_t GL2EncoderBase::glTexSubImage2DOffsetAEMUFunc = nullptr;
glGetUniformIndicesAEMU_proc_t GL2EncoderBase::glGetUniformIndicesAEMUFunc = nullptr;
glVertexAttribIPointerOffsetAEMU_proc_t GL2EncoderBase::glVertexAttribIPointerOffsetAEMUFunc = nullptr;
glVertexAttribIPointerDataAEMU_proc_t GL2EncoderBase::glVertexAttribIPointerDataAEMUFunc = nullptr;
glDrawElementsInstancedDataAEMU_proc_t GL2EncoderBase::glDrawElementsInstancedDataAEMUFunc = nullptr;
glDrawElementsInstancedOffsetAEMU_proc_t GL2EncoderBase::glDrawElementsInstancedOffsetAEMUFunc = nullptr;
glDrawRangeElementsDataAEMU_proc_t GL2EncoderBase::glDrawRangeElementsDataAEMUFunc = nullptr;
glDrawRangeElementsOffsetAEMU_proc_t GL2EncoderBase::glDrawRangeElementsOffsetAEMUFunc = nullptr;
glFenceSyncAEMU_proc_t GL2EncoderBase::glFenceSyncAEMUFunc = nullptr;
glClientWaitSyncAEMU_proc_t GL2EncoderBase::glClientWaitSyncAEMUFunc = nullptr;
glWaitSyncAEMU_proc_t GL2EncoderBase::glWaitSyncAEMUFunc = nullptr;
glDeleteSyncAEMU_proc_t GL2EncoderBase::glDeleteSyncAEMUFunc = nullptr;
glIsSyncAEMU_proc_t GL2EncoderBase::glIsSyncAEMUFunc = nullptr;
glGetSyncivAEMU_proc_t GL2EncoderBase::glGetSyncivAEMUFunc = nullptr;
glTransformFeedbackVaryingsAEMU_proc_t GL2EncoderBase::glTransformFeedbackVaryingsAEMUFunc = nullptr;
glTexImage3DOffsetAEMU_proc_t GL2EncoderBase::glTexImage3DOffsetAEMUFunc = nullptr;
glTexSubImage3DOffsetAEMU_proc_t GL2EncoderBase::glTexSubImage3DOffsetAEMUFunc = nullptr;
glCompressedTexImage3DOffsetAEMU_proc_t GL2EncoderBase::glCompressedTexImage3DOffsetAEMUFunc = nullptr;
glCompressedTexSubImage3DOffsetAEMU_proc_t GL2EncoderBase::glCompressedTexSubImage3DOffsetAEMUFunc = nullptr;
glCreateShaderProgramvAEMU_proc_t GL2EncoderBase::glCreateShaderProgramvAEMUFunc = nullptr;
glDrawArraysIndirectDataAEMU_proc_t GL2EncoderBase::glDrawArraysIndirectDataAEMUFunc = nullptr;
glDrawArraysIndirectOffsetAEMU_proc_t GL2EncoderBase::glDrawArraysIndirectOffsetAEMUFunc = nullptr;
glDrawElementsIndirectDataAEMU_proc_t GL2EncoderBase::glDrawElementsIndirectDataAEMUFunc = nullptr;
glDrawElementsIndirectOffsetAEMU_proc_t GL2EncoderBase::glDrawElementsIndirectOffsetAEMUFunc = nullptr;
glUniformLayout_proc_t GL2EncoderBase::glUniformLayoutFunc = nullptr;
bool GL2EncoderBase::m_isInit = false;
std::mutex GL2EncoderBase::m_lock {};
std::unique_ptr<LoadSharedLib> GL2EncoderBase::m_loader = nullptr;

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
    glClearDepthf = glClearDepthf_s;
    glClearStencil = glClearStencil_s;
    glColorMask = glColorMask_s;
    glCompileShader = glCompileShader_s;
    glCompressedTexImage2D = glCompressedTexImage2D_s;
    glCompressedTexSubImage2D = glCompressedTexSubImage2D_s;
    glCopyTexImage2D = glCopyTexImage2D_s;
    glCopyTexSubImage2D = glCopyTexSubImage2D_s;
    glCreateProgram = glCreateProgram_s;
    glCreateShader = glCreateShader_s;
    glCullFace = glCullFace_s;
    glDeleteBuffers = glDeleteBuffers_s;
    glDeleteFramebuffers = glDeleteFramebuffers_s;
    glDeleteProgram = glDeleteProgram_s;
    glDeleteRenderbuffers = glDeleteRenderbuffers_s;
    glDeleteShader = glDeleteShader_s;
    glDeleteTextures = glDeleteTextures_s;
    glDepthFunc = glDepthFunc_s;
    glDepthMask = glDepthMask_s;
    glDepthRangef = glDepthRangef_s;
    glDetachShader = glDetachShader_s;
    glDisable = glDisable_s;
    glDisableVertexAttribArray = glDisableVertexAttribArray_s;
    glDrawArrays = glDrawArrays_s;
    glDrawElements = glDrawElements_s;
    glEnable = glEnable_s;
    glEnableVertexAttribArray = glEnableVertexAttribArray_s;
    glFlush = glFlush_s;
    glFramebufferRenderbuffer = glFramebufferRenderbuffer_s;
    glFramebufferTexture2D = glFramebufferTexture2D_s;
    glFrontFace = glFrontFace_s;
    glGenBuffers = glGenBuffers_s;
    glGenerateMipmap = glGenerateMipmap_s;
    glGenFramebuffers = glGenFramebuffers_s;
    glGenRenderbuffers = glGenRenderbuffers_s;
    glGenTextures = glGenTextures_s;
    glGetActiveAttrib = glGetActiveAttrib_s;
    glGetActiveUniform = glGetActiveUniform_s;
    glGetAttachedShaders = glGetAttachedShaders_s;
    glGetAttribLocation = glGetAttribLocation_s;
    glGetBooleanv = glGetBooleanv_s;
    glGetBufferParameteriv = glGetBufferParameteriv_s;
    glGetError = glGetError_s;
    glGetFloatv = glGetFloatv_s;
    glGetFramebufferAttachmentParameteriv = glGetFramebufferAttachmentParameteriv_s;
    glGetIntegerv = glGetIntegerv_s;
    glGetProgramiv = glGetProgramiv_s;
    glGetProgramInfoLog = glGetProgramInfoLog_s;
    glGetRenderbufferParameteriv = glGetRenderbufferParameteriv_s;
    glGetShaderiv = glGetShaderiv_s;
    glGetShaderInfoLog = glGetShaderInfoLog_s;
    glGetShaderPrecisionFormat = glGetShaderPrecisionFormat_s;
    glGetShaderSource = glGetShaderSource_s;
    glGetString = glGetString_s;
    glGetTexParameterfv = glGetTexParameterfv_s;
    glGetTexParameteriv = glGetTexParameteriv_s;
    glGetUniformfv = glGetUniformfv_s;
    glGetUniformiv = glGetUniformiv_s;
    glGetUniformLocation = glGetUniformLocation_s;
    glGetVertexAttribfv = glGetVertexAttribfv_s;
    glGetVertexAttribiv = glGetVertexAttribiv_s;
    glGetVertexAttribPointerv = glGetVertexAttribPointerv_s;
    glHint = glHint_s;
    glIsBuffer = glIsBuffer_s;
    glIsEnabled = glIsEnabled_s;
    glIsFramebuffer = glIsFramebuffer_s;
    glIsProgram = glIsProgram_s;
    glIsRenderbuffer = glIsRenderbuffer_s;
    glIsShader = glIsShader_s;
    glIsTexture = glIsTexture_s;
    glLineWidth = glLineWidth_s;
    glLinkProgram = glLinkProgram_s;
    glPixelStorei = glPixelStorei_s;
    glPolygonOffset = glPolygonOffset_s;
    glReadPixels = glReadPixels_s;
    glReleaseShaderCompiler = glReleaseShaderCompiler_s;
    glRenderbufferStorage = glRenderbufferStorage_s;
    glSampleCoverage = glSampleCoverage_s;
    glScissor = glScissor_s;
    glStencilFunc = glStencilFunc_s;
    glStencilFuncSeparate = glStencilFuncSeparate_s;
    glStencilMask = glStencilMask_s;
    glStencilMaskSeparate = glStencilMaskSeparate_s;
    glStencilOp = glStencilOp_s;
    glStencilOpSeparate = glStencilOpSeparate_s;
    glTexImage2D = glTexImage2D_s;
    glTexParameterf = glTexParameterf_s;
    glTexParameterfv = glTexParameterfv_s;
    glTexParameteri = glTexParameteri_s;
    glTexParameteriv = glTexParameteriv_s;
    glTexSubImage2D = glTexSubImage2D_s;
    glUniform1f = glUniform1f_s;
    glUniform1fv = glUniform1fv_s;
    glUniform1i = glUniform1i_s;
    glUniform1iv = glUniform1iv_s;
    glUniform2f = glUniform2f_s;
    glUniform2fv = glUniform2fv_s;
    glUniform2i = glUniform2i_s;
    glUniform2iv = glUniform2iv_s;
    glUniform3f = glUniform3f_s;
    glUniform3fv = glUniform3fv_s;
    glUniform3i = glUniform3i_s;
    glUniform3iv = glUniform3iv_s;
    glUniform4f = glUniform4f_s;
    glUniform4fv = glUniform4fv_s;
    glUniform4i = glUniform4i_s;
    glUniform4iv = glUniform4iv_s;
    glUniformMatrix2fv = glUniformMatrix2fv_s;
    glUniformMatrix3fv = glUniformMatrix3fv_s;
    glUniformMatrix4fv = glUniformMatrix4fv_s;
    glUseProgram = glUseProgram_s;
    glValidateProgram = glValidateProgram_s;
    glVertexAttrib1f = glVertexAttrib1f_s;
    glVertexAttrib1fv = glVertexAttrib1fv_s;
    glVertexAttrib2f = glVertexAttrib2f_s;
    glVertexAttrib2fv = glVertexAttrib2fv_s;
    glVertexAttrib3f = glVertexAttrib3f_s;
    glVertexAttrib3fv = glVertexAttrib3fv_s;
    glVertexAttrib4f = glVertexAttrib4f_s;
    glVertexAttrib4fv = glVertexAttrib4fv_s;
    glVertexAttribPointer = glVertexAttribPointer_s;
    glViewport = glViewport_s;
    glEGLImageTargetTexture2DOES = glEGLImageTargetTexture2DOES_s;
    glEGLImageTargetRenderbufferStorageOES = glEGLImageTargetRenderbufferStorageOES_s;
    glGetProgramBinaryOES = glGetProgramBinaryOES_s;
    glProgramBinaryOES = glProgramBinaryOES_s;
    glMapBufferOES = glMapBufferOES_s;
    glUnmapBufferOES = glUnmapBufferOES_s;
    glTexImage3DOES = glTexImage3DOES_s;
    glTexSubImage3DOES = glTexSubImage3DOES_s;
    glCopyTexSubImage3DOES = glCopyTexSubImage3DOES_s;
    glCompressedTexImage3DOES = glCompressedTexImage3DOES_s;
    glCompressedTexSubImage3DOES = glCompressedTexSubImage3DOES_s;
    glFramebufferTexture3DOES = glFramebufferTexture3DOES_s;
    glBindVertexArrayOES = glBindVertexArrayOES_s;
    glDeleteVertexArraysOES = glDeleteVertexArraysOES_s;
    glGenVertexArraysOES = glGenVertexArraysOES_s;
    glIsVertexArrayOES = glIsVertexArrayOES_s;
    glDiscardFramebufferEXT = glDiscardFramebufferEXT_s;
    glMultiDrawArraysEXT = glMultiDrawArraysEXT_s;
    glMultiDrawElementsEXT = glMultiDrawElementsEXT_s;
    glGetPerfMonitorGroupsAMD = glGetPerfMonitorGroupsAMD_s;
    glGetPerfMonitorCountersAMD = glGetPerfMonitorCountersAMD_s;
    glGetPerfMonitorGroupStringAMD = glGetPerfMonitorGroupStringAMD_s;
    glGetPerfMonitorCounterStringAMD = glGetPerfMonitorCounterStringAMD_s;
    glGetPerfMonitorCounterInfoAMD = glGetPerfMonitorCounterInfoAMD_s;
    glGenPerfMonitorsAMD = glGenPerfMonitorsAMD_s;
    glDeletePerfMonitorsAMD = glDeletePerfMonitorsAMD_s;
    glSelectPerfMonitorCountersAMD = glSelectPerfMonitorCountersAMD_s;
    glBeginPerfMonitorAMD = glBeginPerfMonitorAMD_s;
    glEndPerfMonitorAMD = glEndPerfMonitorAMD_s;
    glGetPerfMonitorCounterDataAMD = glGetPerfMonitorCounterDataAMD_s;
    glRenderbufferStorageMultisampleIMG = glRenderbufferStorageMultisampleIMG_s;
    glFramebufferTexture2DMultisampleIMG = glFramebufferTexture2DMultisampleIMG_s;
    glDeleteFencesNV = glDeleteFencesNV_s;
    glGenFencesNV = glGenFencesNV_s;
    glIsFenceNV = glIsFenceNV_s;
    glTestFenceNV = glTestFenceNV_s;
    glGetFenceivNV = glGetFenceivNV_s;
    glFinishFenceNV = glFinishFenceNV_s;
    glSetFenceNV = glSetFenceNV_s;
    glCoverageMaskNV = glCoverageMaskNV_s;
    glCoverageOperationNV = glCoverageOperationNV_s;
    glGetDriverControlsQCOM = glGetDriverControlsQCOM_s;
    glGetDriverControlStringQCOM = glGetDriverControlStringQCOM_s;
    glEnableDriverControlQCOM = glEnableDriverControlQCOM_s;
    glDisableDriverControlQCOM = glDisableDriverControlQCOM_s;
    glExtGetTexturesQCOM = glExtGetTexturesQCOM_s;
    glExtGetBuffersQCOM = glExtGetBuffersQCOM_s;
    glExtGetRenderbuffersQCOM = glExtGetRenderbuffersQCOM_s;
    glExtGetFramebuffersQCOM = glExtGetFramebuffersQCOM_s;
    glExtGetTexLevelParameterivQCOM = glExtGetTexLevelParameterivQCOM_s;
    glExtTexObjectStateOverrideiQCOM = glExtTexObjectStateOverrideiQCOM_s;
    glExtGetTexSubImageQCOM = glExtGetTexSubImageQCOM_s;
    glExtGetBufferPointervQCOM = glExtGetBufferPointervQCOM_s;
    glExtGetShadersQCOM = glExtGetShadersQCOM_s;
    glExtGetProgramsQCOM = glExtGetProgramsQCOM_s;
    glExtIsProgramBinaryQCOM = glExtIsProgramBinaryQCOM_s;
    glExtGetProgramBinarySourceQCOM = glExtGetProgramBinarySourceQCOM_s;
    glStartTilingQCOM = glStartTilingQCOM_s;
    glEndTilingQCOM = glEndTilingQCOM_s;
    glGenVertexArrays = glGenVertexArrays_s;
    glBindVertexArray = glBindVertexArray_s;
    glDeleteVertexArrays = glDeleteVertexArrays_s;
    glIsVertexArray = glIsVertexArray_s;
    glMapBufferRange = glMapBufferRange_s;
    glUnmapBuffer = glUnmapBuffer_s;
    glFlushMappedBufferRange = glFlushMappedBufferRange_s;
    glBindBufferRange = glBindBufferRange_s;
    glBindBufferBase = glBindBufferBase_s;
    glCopyBufferSubData = glCopyBufferSubData_s;
    glClearBufferiv = glClearBufferiv_s;
    glClearBufferuiv = glClearBufferuiv_s;
    glClearBufferfv = glClearBufferfv_s;
    glClearBufferfi = glClearBufferfi_s;
    glGetBufferParameteri64v = glGetBufferParameteri64v_s;
    glGetBufferPointerv = glGetBufferPointerv_s;
    glUniformBlockBinding = glUniformBlockBinding_s;
    glGetUniformBlockIndex = glGetUniformBlockIndex_s;
    glGetUniformIndices = glGetUniformIndices_s;
    glGetActiveUniformBlockiv = glGetActiveUniformBlockiv_s;
    glGetActiveUniformBlockName = glGetActiveUniformBlockName_s;
    glUniform1ui = glUniform1ui_s;
    glUniform2ui = glUniform2ui_s;
    glUniform3ui = glUniform3ui_s;
    glUniform4ui = glUniform4ui_s;
    glUniform1uiv = glUniform1uiv_s;
    glUniform2uiv = glUniform2uiv_s;
    glUniform3uiv = glUniform3uiv_s;
    glUniform4uiv = glUniform4uiv_s;
    glUniformMatrix2x3fv = glUniformMatrix2x3fv_s;
    glUniformMatrix3x2fv = glUniformMatrix3x2fv_s;
    glUniformMatrix2x4fv = glUniformMatrix2x4fv_s;
    glUniformMatrix4x2fv = glUniformMatrix4x2fv_s;
    glUniformMatrix3x4fv = glUniformMatrix3x4fv_s;
    glUniformMatrix4x3fv = glUniformMatrix4x3fv_s;
    glGetUniformuiv = glGetUniformuiv_s;
    glGetActiveUniformsiv = glGetActiveUniformsiv_s;
    glVertexAttribI4i = glVertexAttribI4i_s;
    glVertexAttribI4ui = glVertexAttribI4ui_s;
    glVertexAttribI4iv = glVertexAttribI4iv_s;
    glVertexAttribI4uiv = glVertexAttribI4uiv_s;
    glVertexAttribIPointer = glVertexAttribIPointer_s;
    glGetVertexAttribIiv = glGetVertexAttribIiv_s;
    glGetVertexAttribIuiv = glGetVertexAttribIuiv_s;
    glVertexAttribDivisor = glVertexAttribDivisor_s;
    glDrawArraysInstanced = glDrawArraysInstanced_s;
    glDrawElementsInstanced = glDrawElementsInstanced_s;
    glDrawRangeElements = glDrawRangeElements_s;
    glFenceSync = glFenceSync_s;
    glClientWaitSync = glClientWaitSync_s;
    glWaitSync = glWaitSync_s;
    glDeleteSync = glDeleteSync_s;
    glIsSync = glIsSync_s;
    glGetSynciv = glGetSynciv_s;
    glDrawBuffers = glDrawBuffers_s;
    glReadBuffer = glReadBuffer_s;
    glBlitFramebuffer = glBlitFramebuffer_s;
    glInvalidateFramebuffer = glInvalidateFramebuffer_s;
    glInvalidateSubFramebuffer = glInvalidateSubFramebuffer_s;
    glFramebufferTextureLayer = glFramebufferTextureLayer_s;
    glRenderbufferStorageMultisample = glRenderbufferStorageMultisample_s;
    glTexStorage2D = glTexStorage2D_s;
    glGetInternalformativ = glGetInternalformativ_s;
    glBeginTransformFeedback = glBeginTransformFeedback_s;
    glEndTransformFeedback = glEndTransformFeedback_s;
    glGenTransformFeedbacks = glGenTransformFeedbacks_s;
    glDeleteTransformFeedbacks = glDeleteTransformFeedbacks_s;
    glBindTransformFeedback = glBindTransformFeedback_s;
    glPauseTransformFeedback = glPauseTransformFeedback_s;
    glResumeTransformFeedback = glResumeTransformFeedback_s;
    glIsTransformFeedback = glIsTransformFeedback_s;
    glTransformFeedbackVaryings = glTransformFeedbackVaryings_s;
    glGetTransformFeedbackVarying = glGetTransformFeedbackVarying_s;
    glGenSamplers = glGenSamplers_s;
    glDeleteSamplers = glDeleteSamplers_s;
    glBindSampler = glBindSampler_s;
    glSamplerParameterf = glSamplerParameterf_s;
    glSamplerParameteri = glSamplerParameteri_s;
    glSamplerParameterfv = glSamplerParameterfv_s;
    glSamplerParameteriv = glSamplerParameteriv_s;
    glGetSamplerParameterfv = glGetSamplerParameterfv_s;
    glGetSamplerParameteriv = glGetSamplerParameteriv_s;
    glIsSampler = glIsSampler_s;
    glGenQueries = glGenQueries_s;
    glDeleteQueries = glDeleteQueries_s;
    glBeginQuery = glBeginQuery_s;
    glEndQuery = glEndQuery_s;
    glGetQueryiv = glGetQueryiv_s;
    glGetQueryObjectuiv = glGetQueryObjectuiv_s;
    glIsQuery = glIsQuery_s;
    glProgramParameteri = glProgramParameteri_s;
    glProgramBinary = glProgramBinary_s;
    glGetProgramBinary = glGetProgramBinary_s;
    glGetFragDataLocation = glGetFragDataLocation_s;
    glGetInteger64v = glGetInteger64v_s;
    glGetIntegeri_v = glGetIntegeri_v_s;
    glGetInteger64i_v = glGetInteger64i_v_s;
    glTexImage3D = glTexImage3D_s;
    glTexStorage3D = glTexStorage3D_s;
    glTexSubImage3D = glTexSubImage3D_s;
    glCompressedTexImage3D = glCompressedTexImage3D_s;
    glCompressedTexSubImage3D = glCompressedTexSubImage3D_s;
    glCopyTexSubImage3D = glCopyTexSubImage3D_s;
    glGetStringi = glGetStringi_s;
    glGetBooleani_v = glGetBooleani_v_s;
    glMemoryBarrier = glMemoryBarrier_s;
    glMemoryBarrierByRegion = glMemoryBarrierByRegion_s;
    glGenProgramPipelines = glGenProgramPipelines_s;
    glDeleteProgramPipelines = glDeleteProgramPipelines_s;
    glBindProgramPipeline = glBindProgramPipeline_s;
    glGetProgramPipelineiv = glGetProgramPipelineiv_s;
    glGetProgramPipelineInfoLog = glGetProgramPipelineInfoLog_s;
    glValidateProgramPipeline = glValidateProgramPipeline_s;
    glIsProgramPipeline = glIsProgramPipeline_s;
    glUseProgramStages = glUseProgramStages_s;
    glActiveShaderProgram = glActiveShaderProgram_s;
    glCreateShaderProgramv = glCreateShaderProgramv_s;
    glProgramUniform1f = glProgramUniform1f_s;
    glProgramUniform2f = glProgramUniform2f_s;
    glProgramUniform3f = glProgramUniform3f_s;
    glProgramUniform4f = glProgramUniform4f_s;
    glProgramUniform1i = glProgramUniform1i_s;
    glProgramUniform2i = glProgramUniform2i_s;
    glProgramUniform3i = glProgramUniform3i_s;
    glProgramUniform4i = glProgramUniform4i_s;
    glProgramUniform1ui = glProgramUniform1ui_s;
    glProgramUniform2ui = glProgramUniform2ui_s;
    glProgramUniform3ui = glProgramUniform3ui_s;
    glProgramUniform4ui = glProgramUniform4ui_s;
    glProgramUniform1fv = glProgramUniform1fv_s;
    glProgramUniform2fv = glProgramUniform2fv_s;
    glProgramUniform3fv = glProgramUniform3fv_s;
    glProgramUniform4fv = glProgramUniform4fv_s;
    glProgramUniform1iv = glProgramUniform1iv_s;
    glProgramUniform2iv = glProgramUniform2iv_s;
    glProgramUniform3iv = glProgramUniform3iv_s;
    glProgramUniform4iv = glProgramUniform4iv_s;
    glProgramUniform1uiv = glProgramUniform1uiv_s;
    glProgramUniform2uiv = glProgramUniform2uiv_s;
    glProgramUniform3uiv = glProgramUniform3uiv_s;
    glProgramUniform4uiv = glProgramUniform4uiv_s;
    glProgramUniformMatrix2fv = glProgramUniformMatrix2fv_s;
    glProgramUniformMatrix3fv = glProgramUniformMatrix3fv_s;
    glProgramUniformMatrix4fv = glProgramUniformMatrix4fv_s;
    glProgramUniformMatrix2x3fv = glProgramUniformMatrix2x3fv_s;
    glProgramUniformMatrix3x2fv = glProgramUniformMatrix3x2fv_s;
    glProgramUniformMatrix2x4fv = glProgramUniformMatrix2x4fv_s;
    glProgramUniformMatrix4x2fv = glProgramUniformMatrix4x2fv_s;
    glProgramUniformMatrix3x4fv = glProgramUniformMatrix3x4fv_s;
    glProgramUniformMatrix4x3fv = glProgramUniformMatrix4x3fv_s;
    glGetProgramInterfaceiv = glGetProgramInterfaceiv_s;
    glGetProgramResourceiv = glGetProgramResourceiv_s;
    glGetProgramResourceIndex = glGetProgramResourceIndex_s;
    glGetProgramResourceLocation = glGetProgramResourceLocation_s;
    glGetProgramResourceName = glGetProgramResourceName_s;
    glBindImageTexture = glBindImageTexture_s;
    glDispatchCompute = glDispatchCompute_s;
    glDispatchComputeIndirect = glDispatchComputeIndirect_s;
    glBindVertexBuffer = glBindVertexBuffer_s;
    glVertexAttribBinding = glVertexAttribBinding_s;
    glVertexAttribFormat = glVertexAttribFormat_s;
    glVertexAttribIFormat = glVertexAttribIFormat_s;
    glVertexBindingDivisor = glVertexBindingDivisor_s;
    glDrawArraysIndirect = glDrawArraysIndirect_s;
    glDrawElementsIndirect = glDrawElementsIndirect_s;
    glTexStorage2DMultisample = glTexStorage2DMultisample_s;
    glSampleMaski = glSampleMaski_s;
    glGetMultisamplefv = glGetMultisamplefv_s;
    glFramebufferParameteri = glFramebufferParameteri_s;
    glGetFramebufferParameteriv = glGetFramebufferParameteriv_s;
    glGetTexLevelParameterfv = glGetTexLevelParameterfv_s;
    glGetTexLevelParameteriv = glGetTexLevelParameteriv_s;
    glEnableiEXT = glEnableiEXT_s;
    glDisableiEXT = glDisableiEXT_s;
    glBlendEquationiEXT = glBlendEquationiEXT_s;
    glBlendEquationSeparateiEXT = glBlendEquationSeparateiEXT_s;
    glBlendFunciEXT = glBlendFunciEXT_s;
    glBlendFuncSeparateiEXT = glBlendFuncSeparateiEXT_s;
    glColorMaskiEXT = glColorMaskiEXT_s;
    glIsEnablediEXT = glIsEnablediEXT_s;
    glCopyImageSubDataEXT = glCopyImageSubDataEXT_s;
    glBlendBarrierKHR = glBlendBarrierKHR_s;
    glTexParameterIivEXT = glTexParameterIivEXT_s;
    glTexParameterIuivEXT = glTexParameterIuivEXT_s;
    glGetTexParameterIivEXT = glGetTexParameterIivEXT_s;
    glGetTexParameterIuivEXT = glGetTexParameterIuivEXT_s;
    glSamplerParameterIivEXT = glSamplerParameterIivEXT_s;
    glSamplerParameterIuivEXT = glSamplerParameterIuivEXT_s;
    glGetSamplerParameterIivEXT = glGetSamplerParameterIivEXT_s;
    glGetSamplerParameterIuivEXT = glGetSamplerParameterIuivEXT_s;
    glVertexAttribPointerData = glVertexAttribPointerData_s;
    glVertexAttribPointerOffset = glVertexAttribPointerOffset_s;
    glDrawElementsOffset = glDrawElementsOffset_s;
    glDrawElementsData = glDrawElementsData_s;
    glGetCompressedTextureFormats = glGetCompressedTextureFormats_s;
    glShaderString = glShaderString_s;
    glFinishRoundTrip = glFinishRoundTrip_s;
    glMapBufferRangeAEMU = glMapBufferRangeAEMU_s;
    glUnmapBufferAEMU = glUnmapBufferAEMU_s;
    glFlushMappedBufferRangeAEMU = glFlushMappedBufferRangeAEMU_s;
    glReadPixelsOffsetAEMU = glReadPixelsOffsetAEMU_s;
    glCompressedTexImage2DOffsetAEMU = glCompressedTexImage2DOffsetAEMU_s;
    glCompressedTexSubImage2DOffsetAEMU = glCompressedTexSubImage2DOffsetAEMU_s;
    glTexImage2DOffsetAEMU = glTexImage2DOffsetAEMU_s;
    glTexSubImage2DOffsetAEMU = glTexSubImage2DOffsetAEMU_s;
    glGetUniformIndicesAEMU = glGetUniformIndicesAEMU_s;
    glVertexAttribIPointerOffsetAEMU = glVertexAttribIPointerOffsetAEMU_s;
    glVertexAttribIPointerDataAEMU = glVertexAttribIPointerDataAEMU_s;
    glDrawElementsInstancedDataAEMU = glDrawElementsInstancedDataAEMU_s;
    glDrawElementsInstancedOffsetAEMU = glDrawElementsInstancedOffsetAEMU_s;
    glDrawRangeElementsDataAEMU = glDrawRangeElementsDataAEMU_s;
    glDrawRangeElementsOffsetAEMU = glDrawRangeElementsOffsetAEMU_s;
    glFenceSyncAEMU = glFenceSyncAEMU_s;
    glClientWaitSyncAEMU = glClientWaitSyncAEMU_s;
    glWaitSyncAEMU = glWaitSyncAEMU_s;
    glDeleteSyncAEMU = glDeleteSyncAEMU_s;
    glIsSyncAEMU = glIsSyncAEMU_s;
    glGetSyncivAEMU = glGetSyncivAEMU_s;
    glTransformFeedbackVaryingsAEMU = glTransformFeedbackVaryingsAEMU_s;
    glTexImage3DOffsetAEMU = glTexImage3DOffsetAEMU_s;
    glTexSubImage3DOffsetAEMU = glTexSubImage3DOffsetAEMU_s;
    glCompressedTexImage3DOffsetAEMU = glCompressedTexImage3DOffsetAEMU_s;
    glCompressedTexSubImage3DOffsetAEMU = glCompressedTexSubImage3DOffsetAEMU_s;
    glCreateShaderProgramvAEMU = glCreateShaderProgramvAEMU_s;
    glDrawArraysIndirectDataAEMU = glDrawArraysIndirectDataAEMU_s;
    glDrawArraysIndirectOffsetAEMU = glDrawArraysIndirectOffsetAEMU_s;
    glDrawElementsIndirectDataAEMU = glDrawElementsIndirectDataAEMU_s;
    glDrawElementsIndirectOffsetAEMU = glDrawElementsIndirectOffsetAEMU_s;
    glUniformLayout = glUniformLayout_s;
    InitGLESv2Export();
}

GL2EncoderBase::~GL2EncoderBase()
{
    DeleteVmiGLESv2Encoder();
}

bool GL2EncoderBase::InitGLESv2Export()
{
    std::lock_guard<std::mutex> lock(m_lock);
    ALOGD("GL2EncoderBase::InitGLESv2Export begin");
    if (m_isInit) {
        return true;
    }

#if defined(__LP64__)
    const std::string libName = "/vendor/lib64/libVmiInstructionEngine.so";
#else
    const std::string libName = "/vendor/lib/libVmiInstructionEngine.so";
#endif
    m_loader = std::make_unique<LoadSharedLib>(libName); // 静态变量，进程退出后，再自动释放此加载库
    if (m_loader == nullptr) {
        ALOGE("Failed to create loader %s", libName.c_str());
        return false;
    }
    std::function<void *(const char *)> func =
        std::bind(&LoadSharedLib::GetProcAddress, m_loader.get(), std::placeholders::_1);
    if (func == nullptr) {
        return false;
    }

    createGLESv2EncoderFunc = reinterpret_cast<decltype(createGLESv2EncoderFunc)>(func("CreateVmiGLESv2Encoder"));
    deleteGLESv2EncoderFunc = reinterpret_cast<decltype(deleteGLESv2EncoderFunc)>(func("DeleteVmiGLESv2Encoder"));
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
    glClearDepthfFunc = reinterpret_cast<decltype(glClearDepthfFunc)>(func("VmiGlClearDepthf"));
    glClearStencilFunc = reinterpret_cast<decltype(glClearStencilFunc)>(func("VmiGlClearStencil"));
    glColorMaskFunc = reinterpret_cast<decltype(glColorMaskFunc)>(func("VmiGlColorMask"));
    glCompileShaderFunc = reinterpret_cast<decltype(glCompileShaderFunc)>(func("VmiGlCompileShader"));
    glCompressedTexImage2DFunc =
        reinterpret_cast<decltype(glCompressedTexImage2DFunc)>(func("VmiGlCompressedTexImage2D"));
    glCompressedTexSubImage2DFunc =
        reinterpret_cast<decltype(glCompressedTexSubImage2DFunc)>(func("VmiGlCompressedTexSubImage2D"));
    glCopyTexImage2DFunc = reinterpret_cast<decltype(glCopyTexImage2DFunc)>(func("VmiGlCopyTexImage2D"));
    glCopyTexSubImage2DFunc = reinterpret_cast<decltype(glCopyTexSubImage2DFunc)>(func("VmiGlCopyTexSubImage2D"));
    glCreateProgramFunc = reinterpret_cast<decltype(glCreateProgramFunc)>(func("VmiGlCreateProgram"));
    glCreateShaderFunc = reinterpret_cast<decltype(glCreateShaderFunc)>(func("VmiGlCreateShader"));
    glCullFaceFunc = reinterpret_cast<decltype(glCullFaceFunc)>(func("VmiGlCullFace"));
    glDeleteBuffersFunc = reinterpret_cast<decltype(glDeleteBuffersFunc)>(func("VmiGlDeleteBuffers"));
    glDeleteFramebuffersFunc = reinterpret_cast<decltype(glDeleteFramebuffersFunc)>(func("VmiGlDeleteFramebuffers"));
    glDeleteProgramFunc = reinterpret_cast<decltype(glDeleteProgramFunc)>(func("VmiGlDeleteProgram"));
    glDeleteRenderbuffersFunc = reinterpret_cast<decltype(glDeleteRenderbuffersFunc)>(func("VmiGlDeleteRenderbuffers"));
    glDeleteShaderFunc = reinterpret_cast<decltype(glDeleteShaderFunc)>(func("VmiGlDeleteShader"));
    glDeleteTexturesFunc = reinterpret_cast<decltype(glDeleteTexturesFunc)>(func("VmiGlDeleteTextures"));
    glDepthFuncFunc = reinterpret_cast<decltype(glDepthFuncFunc)>(func("VmiGlDepthFunc"));
    glDepthMaskFunc = reinterpret_cast<decltype(glDepthMaskFunc)>(func("VmiGlDepthMask"));
    glDepthRangefFunc = reinterpret_cast<decltype(glDepthRangefFunc)>(func("VmiGlDepthRangef"));
    glDetachShaderFunc = reinterpret_cast<decltype(glDetachShaderFunc)>(func("VmiGlDetachShader"));
    glDisableFunc = reinterpret_cast<decltype(glDisableFunc)>(func("VmiGlDisable"));
    glDisableVertexAttribArrayFunc =
        reinterpret_cast<decltype(glDisableVertexAttribArrayFunc)>(func("VmiGlDisableVertexAttribArray"));
    glDrawArraysFunc = reinterpret_cast<decltype(glDrawArraysFunc)>(func("VmiGlDrawArrays"));
    glDrawElementsFunc = reinterpret_cast<decltype(glDrawElementsFunc)>(func("VmiGlDrawElements"));
    glEnableFunc = reinterpret_cast<decltype(glEnableFunc)>(func("VmiGlEnable"));
    glEnableVertexAttribArrayFunc =
        reinterpret_cast<decltype(glEnableVertexAttribArrayFunc)>(func("VmiGlEnableVertexAttribArray"));
    glFlushFunc = reinterpret_cast<decltype(glFlushFunc)>(func("VmiGlFlush"));
    glFramebufferRenderbufferFunc =
        reinterpret_cast<decltype(glFramebufferRenderbufferFunc)>(func("VmiGlFramebufferRenderbuffer"));
    glFramebufferTexture2DFunc =
        reinterpret_cast<decltype(glFramebufferTexture2DFunc)>(func("VmiGlFramebufferTexture2D"));
    glFrontFaceFunc = reinterpret_cast<decltype(glFrontFaceFunc)>(func("VmiGlFrontFace"));
    glGenBuffersFunc = reinterpret_cast<decltype(glGenBuffersFunc)>(func("VmiGlGenBuffers"));
    glGenerateMipmapFunc = reinterpret_cast<decltype(glGenerateMipmapFunc)>(func("VmiGlGenerateMipmap"));
    glGenFramebuffersFunc = reinterpret_cast<decltype(glGenFramebuffersFunc)>(func("VmiGlGenFramebuffers"));
    glGenRenderbuffersFunc = reinterpret_cast<decltype(glGenRenderbuffersFunc)>(func("VmiGlGenRenderbuffers"));
    glGenTexturesFunc = reinterpret_cast<decltype(glGenTexturesFunc)>(func("VmiGlGenTextures"));
    glGetActiveAttribFunc = reinterpret_cast<decltype(glGetActiveAttribFunc)>(func("VmiGlGetActiveAttrib"));
    glGetActiveUniformFunc = reinterpret_cast<decltype(glGetActiveUniformFunc)>(func("VmiGlGetActiveUniform"));
    glGetAttachedShadersFunc = reinterpret_cast<decltype(glGetAttachedShadersFunc)>(func("VmiGlGetAttachedShaders"));
    glGetAttribLocationFunc = reinterpret_cast<decltype(glGetAttribLocationFunc)>(func("VmiGlGetAttribLocation"));
    glGetBooleanvFunc = reinterpret_cast<decltype(glGetBooleanvFunc)>(func("VmiGlGetBooleanv"));
    glGetBufferParameterivFunc =
        reinterpret_cast<decltype(glGetBufferParameterivFunc)>(func("VmiGlGetBufferParameteriv"));
    glGetErrorFunc = reinterpret_cast<decltype(glGetErrorFunc)>(func("VmiGlGetError"));
    glGetFloatvFunc = reinterpret_cast<decltype(glGetFloatvFunc)>(func("VmiGlGetFloatv"));
    glGetFramebufferAttachmentParameterivFunc = reinterpret_cast<decltype(glGetFramebufferAttachmentParameterivFunc)>(
        func("VmiGlGetFramebufferAttachmentParameteriv"));
    glGetIntegervFunc = reinterpret_cast<decltype(glGetIntegervFunc)>(func("VmiGlGetIntegerv"));
    glGetProgramivFunc = reinterpret_cast<decltype(glGetProgramivFunc)>(func("VmiGlGetProgramiv"));
    glGetProgramInfoLogFunc = reinterpret_cast<decltype(glGetProgramInfoLogFunc)>(func("VmiGlGetProgramInfoLog"));
    glGetRenderbufferParameterivFunc =
        reinterpret_cast<decltype(glGetRenderbufferParameterivFunc)>(func("VmiGlGetRenderbufferParameteriv"));
    glGetShaderivFunc = reinterpret_cast<decltype(glGetShaderivFunc)>(func("VmiGlGetShaderiv"));
    glGetShaderInfoLogFunc = reinterpret_cast<decltype(glGetShaderInfoLogFunc)>(func("VmiGlGetShaderInfoLog"));
    glGetShaderPrecisionFormatFunc =
        reinterpret_cast<decltype(glGetShaderPrecisionFormatFunc)>(func("VmiGlGetShaderPrecisionFormat"));
    glGetShaderSourceFunc = reinterpret_cast<decltype(glGetShaderSourceFunc)>(func("VmiGlGetShaderSource"));
    glGetStringFunc = reinterpret_cast<decltype(glGetStringFunc)>(func("VmiGlGetString"));
    glGetTexParameterfvFunc = reinterpret_cast<decltype(glGetTexParameterfvFunc)>(func("VmiGlGetTexParameterfv"));
    glGetTexParameterivFunc = reinterpret_cast<decltype(glGetTexParameterivFunc)>(func("VmiGlGetTexParameteriv"));
    glGetUniformfvFunc = reinterpret_cast<decltype(glGetUniformfvFunc)>(func("VmiGlGetUniformfv"));
    glGetUniformivFunc = reinterpret_cast<decltype(glGetUniformivFunc)>(func("VmiGlGetUniformiv"));
    glGetUniformLocationFunc = reinterpret_cast<decltype(glGetUniformLocationFunc)>(func("VmiGlGetUniformLocation"));
    glGetVertexAttribfvFunc = reinterpret_cast<decltype(glGetVertexAttribfvFunc)>(func("VmiGlGetVertexAttribfv"));
    glGetVertexAttribivFunc = reinterpret_cast<decltype(glGetVertexAttribivFunc)>(func("VmiGlGetVertexAttribiv"));
    glGetVertexAttribPointervFunc =
        reinterpret_cast<decltype(glGetVertexAttribPointervFunc)>(func("VmiGlGetVertexAttribPointerv"));
    glHintFunc = reinterpret_cast<decltype(glHintFunc)>(func("VmiGlHint"));
    glIsBufferFunc = reinterpret_cast<decltype(glIsBufferFunc)>(func("VmiGlIsBuffer"));
    glIsEnabledFunc = reinterpret_cast<decltype(glIsEnabledFunc)>(func("VmiGlIsEnabled"));
    glIsFramebufferFunc = reinterpret_cast<decltype(glIsFramebufferFunc)>(func("VmiGlIsFramebuffer"));
    glIsProgramFunc = reinterpret_cast<decltype(glIsProgramFunc)>(func("VmiGlIsProgram"));
    glIsRenderbufferFunc = reinterpret_cast<decltype(glIsRenderbufferFunc)>(func("VmiGlIsRenderbuffer"));
    glIsShaderFunc = reinterpret_cast<decltype(glIsShaderFunc)>(func("VmiGlIsShader"));
    glIsTextureFunc = reinterpret_cast<decltype(glIsTextureFunc)>(func("VmiGlIsTexture"));
    glLineWidthFunc = reinterpret_cast<decltype(glLineWidthFunc)>(func("VmiGlLineWidth"));
    glLinkProgramFunc = reinterpret_cast<decltype(glLinkProgramFunc)>(func("VmiGlLinkProgram"));
    glPixelStoreiFunc = reinterpret_cast<decltype(glPixelStoreiFunc)>(func("VmiGlPixelStorei"));
    glPolygonOffsetFunc = reinterpret_cast<decltype(glPolygonOffsetFunc)>(func("VmiGlPolygonOffset"));
    glReadPixelsFunc = reinterpret_cast<decltype(glReadPixelsFunc)>(func("VmiGlReadPixels"));
    glReleaseShaderCompilerFunc =
        reinterpret_cast<decltype(glReleaseShaderCompilerFunc)>(func("VmiGlReleaseShaderCompiler"));
    glRenderbufferStorageFunc = reinterpret_cast<decltype(glRenderbufferStorageFunc)>(func("VmiGlRenderbufferStorage"));
    glSampleCoverageFunc = reinterpret_cast<decltype(glSampleCoverageFunc)>(func("VmiGlSampleCoverage"));
    glScissorFunc = reinterpret_cast<decltype(glScissorFunc)>(func("VmiGlScissor"));
    glShaderBinaryFunc = reinterpret_cast<decltype(glShaderBinaryFunc)>(func("VmiGlShaderBinary"));
    glShaderSourceFunc = reinterpret_cast<decltype(glShaderSourceFunc)>(func("VmiGlShaderSource"));
    glStencilFuncFunc = reinterpret_cast<decltype(glStencilFuncFunc)>(func("VmiGlStencilFunc"));
    glStencilFuncSeparateFunc = reinterpret_cast<decltype(glStencilFuncSeparateFunc)>(func("VmiGlStencilFuncSeparate"));
    glStencilMaskFunc = reinterpret_cast<decltype(glStencilMaskFunc)>(func("VmiGlStencilMask"));
    glStencilMaskSeparateFunc = reinterpret_cast<decltype(glStencilMaskSeparateFunc)>(func("VmiGlStencilMaskSeparate"));
    glStencilOpFunc = reinterpret_cast<decltype(glStencilOpFunc)>(func("VmiGlStencilOp"));
    glStencilOpSeparateFunc = reinterpret_cast<decltype(glStencilOpSeparateFunc)>(func("VmiGlStencilOpSeparate"));
    glTexImage2DFunc = reinterpret_cast<decltype(glTexImage2DFunc)>(func("VmiGlTexImage2D"));
    glTexParameterfFunc = reinterpret_cast<decltype(glTexParameterfFunc)>(func("VmiGlTexParameterf"));
    glTexParameterfvFunc = reinterpret_cast<decltype(glTexParameterfvFunc)>(func("VmiGlTexParameterfv"));
    glTexParameteriFunc = reinterpret_cast<decltype(glTexParameteriFunc)>(func("VmiGlTexParameteri"));
    glTexParameterivFunc = reinterpret_cast<decltype(glTexParameterivFunc)>(func("VmiGlTexParameteriv"));
    glTexSubImage2DFunc = reinterpret_cast<decltype(glTexSubImage2DFunc)>(func("VmiGlTexSubImage2D"));
    glUniform1fFunc = reinterpret_cast<decltype(glUniform1fFunc)>(func("VmiGlUniform1f"));
    glUniform1fvFunc = reinterpret_cast<decltype(glUniform1fvFunc)>(func("VmiGlUniform1fv"));
    glUniform1iFunc = reinterpret_cast<decltype(glUniform1iFunc)>(func("VmiGlUniform1i"));
    glUniform1ivFunc = reinterpret_cast<decltype(glUniform1ivFunc)>(func("VmiGlUniform1iv"));
    glUniform2fFunc = reinterpret_cast<decltype(glUniform2fFunc)>(func("VmiGlUniform2f"));
    glUniform2fvFunc = reinterpret_cast<decltype(glUniform2fvFunc)>(func("VmiGlUniform2fv"));
    glUniform2iFunc = reinterpret_cast<decltype(glUniform2iFunc)>(func("VmiGlUniform2i"));
    glUniform2ivFunc = reinterpret_cast<decltype(glUniform2ivFunc)>(func("VmiGlUniform2iv"));
    glUniform3fFunc = reinterpret_cast<decltype(glUniform3fFunc)>(func("VmiGlUniform3f"));
    glUniform3fvFunc = reinterpret_cast<decltype(glUniform3fvFunc)>(func("VmiGlUniform3fv"));
    glUniform3iFunc = reinterpret_cast<decltype(glUniform3iFunc)>(func("VmiGlUniform3i"));
    glUniform3ivFunc = reinterpret_cast<decltype(glUniform3ivFunc)>(func("VmiGlUniform3iv"));
    glUniform4fFunc = reinterpret_cast<decltype(glUniform4fFunc)>(func("VmiGlUniform4f"));
    glUniform4fvFunc = reinterpret_cast<decltype(glUniform4fvFunc)>(func("VmiGlUniform4fv"));
    glUniform4iFunc = reinterpret_cast<decltype(glUniform4iFunc)>(func("VmiGlUniform4i"));
    glUniform4ivFunc = reinterpret_cast<decltype(glUniform4ivFunc)>(func("VmiGlUniform4iv"));
    glUniformMatrix2fvFunc = reinterpret_cast<decltype(glUniformMatrix2fvFunc)>(func("VmiGlUniformMatrix2fv"));
    glUniformMatrix3fvFunc = reinterpret_cast<decltype(glUniformMatrix3fvFunc)>(func("VmiGlUniformMatrix3fv"));
    glUniformMatrix4fvFunc = reinterpret_cast<decltype(glUniformMatrix4fvFunc)>(func("VmiGlUniformMatrix4fv"));
    glUseProgramFunc = reinterpret_cast<decltype(glUseProgramFunc)>(func("VmiGlUseProgram"));
    glValidateProgramFunc = reinterpret_cast<decltype(glValidateProgramFunc)>(func("VmiGlValidateProgram"));
    glVertexAttrib1fFunc = reinterpret_cast<decltype(glVertexAttrib1fFunc)>(func("VmiGlVertexAttrib1f"));
    glVertexAttrib1fvFunc = reinterpret_cast<decltype(glVertexAttrib1fvFunc)>(func("VmiGlVertexAttrib1fv"));
    glVertexAttrib2fFunc = reinterpret_cast<decltype(glVertexAttrib2fFunc)>(func("VmiGlVertexAttrib2f"));
    glVertexAttrib2fvFunc = reinterpret_cast<decltype(glVertexAttrib2fvFunc)>(func("VmiGlVertexAttrib2fv"));
    glVertexAttrib3fFunc = reinterpret_cast<decltype(glVertexAttrib3fFunc)>(func("VmiGlVertexAttrib3f"));
    glVertexAttrib3fvFunc = reinterpret_cast<decltype(glVertexAttrib3fvFunc)>(func("VmiGlVertexAttrib3fv"));
    glVertexAttrib4fFunc = reinterpret_cast<decltype(glVertexAttrib4fFunc)>(func("VmiGlVertexAttrib4f"));
    glVertexAttrib4fvFunc = reinterpret_cast<decltype(glVertexAttrib4fvFunc)>(func("VmiGlVertexAttrib4fv"));
    glVertexAttribPointerFunc = reinterpret_cast<decltype(glVertexAttribPointerFunc)>(func("VmiGlVertexAttribPointer"));
    glViewportFunc = reinterpret_cast<decltype(glViewportFunc)>(func("VmiGlViewport"));
    glEGLImageTargetTexture2DOESFunc =
        reinterpret_cast<decltype(glEGLImageTargetTexture2DOESFunc)>(func("VmiGlEGLImageTargetTexture2DOES"));
    glEGLImageTargetRenderbufferStorageOESFunc = reinterpret_cast<decltype(glEGLImageTargetRenderbufferStorageOESFunc)>(
        func("VmiGlEGLImageTargetRenderbufferStorageOES"));
    glGetProgramBinaryOESFunc = reinterpret_cast<decltype(glGetProgramBinaryOESFunc)>(func("VmiGlGetProgramBinaryOES"));
    glProgramBinaryOESFunc = reinterpret_cast<decltype(glProgramBinaryOESFunc)>(func("VmiGlProgramBinaryOES"));
    glMapBufferOESFunc = reinterpret_cast<decltype(glMapBufferOESFunc)>(func("VmiGlMapBufferOES"));
    glUnmapBufferOESFunc = reinterpret_cast<decltype(glUnmapBufferOESFunc)>(func("VmiGlUnmapBufferOES"));
    glTexImage3DOESFunc = reinterpret_cast<decltype(glTexImage3DOESFunc)>(func("VmiGlTexImage3DOES"));
    glTexSubImage3DOESFunc = reinterpret_cast<decltype(glTexSubImage3DOESFunc)>(func("VmiGlTexSubImage3DOES"));
    glCopyTexSubImage3DOESFunc =
        reinterpret_cast<decltype(glCopyTexSubImage3DOESFunc)>(func("VmiGlCopyTexSubImage3DOES"));
    glCompressedTexImage3DOESFunc =
        reinterpret_cast<decltype(glCompressedTexImage3DOESFunc)>(func("VmiGlCompressedTexImage3DOES"));
    glCompressedTexSubImage3DOESFunc =
        reinterpret_cast<decltype(glCompressedTexSubImage3DOESFunc)>(func("VmiGlCompressedTexSubImage3DOES"));
    glFramebufferTexture3DOESFunc =
        reinterpret_cast<decltype(glFramebufferTexture3DOESFunc)>(func("VmiGlFramebufferTexture3DOES"));
    glBindVertexArrayOESFunc = reinterpret_cast<decltype(glBindVertexArrayOESFunc)>(func("VmiGlBindVertexArrayOES"));
    glDeleteVertexArraysOESFunc =
        reinterpret_cast<decltype(glDeleteVertexArraysOESFunc)>(func("VmiGlDeleteVertexArraysOES"));
    glGenVertexArraysOESFunc = reinterpret_cast<decltype(glGenVertexArraysOESFunc)>(func("VmiGlGenVertexArraysOES"));
    glIsVertexArrayOESFunc = reinterpret_cast<decltype(glIsVertexArrayOESFunc)>(func("VmiGlIsVertexArrayOES"));
    glDiscardFramebufferEXTFunc =
        reinterpret_cast<decltype(glDiscardFramebufferEXTFunc)>(func("VmiGlDiscardFramebufferEXT"));
    glMultiDrawArraysEXTFunc = reinterpret_cast<decltype(glMultiDrawArraysEXTFunc)>(func("VmiGlMultiDrawArraysEXT"));
    glMultiDrawElementsEXTFunc =
        reinterpret_cast<decltype(glMultiDrawElementsEXTFunc)>(func("VmiGlMultiDrawElementsEXT"));
    glGetPerfMonitorGroupsAMDFunc =
        reinterpret_cast<decltype(glGetPerfMonitorGroupsAMDFunc)>(func("VmiGlGetPerfMonitorGroupsAMD"));
    glGetPerfMonitorCountersAMDFunc =
        reinterpret_cast<decltype(glGetPerfMonitorCountersAMDFunc)>(func("VmiGlGetPerfMonitorCountersAMD"));
    glGetPerfMonitorGroupStringAMDFunc =
        reinterpret_cast<decltype(glGetPerfMonitorGroupStringAMDFunc)>(func("VmiGlGetPerfMonitorGroupStringAMD"));
    glGetPerfMonitorCounterStringAMDFunc =
        reinterpret_cast<decltype(glGetPerfMonitorCounterStringAMDFunc)>(func("VmiGlGetPerfMonitorCounterStringAMD"));
    glGetPerfMonitorCounterInfoAMDFunc =
        reinterpret_cast<decltype(glGetPerfMonitorCounterInfoAMDFunc)>(func("VmiGlGetPerfMonitorCounterInfoAMD"));
    glGenPerfMonitorsAMDFunc = reinterpret_cast<decltype(glGenPerfMonitorsAMDFunc)>(func("VmiGlGenPerfMonitorsAMD"));
    glDeletePerfMonitorsAMDFunc =
        reinterpret_cast<decltype(glDeletePerfMonitorsAMDFunc)>(func("VmiGlDeletePerfMonitorsAMD"));
    glSelectPerfMonitorCountersAMDFunc =
        reinterpret_cast<decltype(glSelectPerfMonitorCountersAMDFunc)>(func("VmiGlSelectPerfMonitorCountersAMD"));
    glBeginPerfMonitorAMDFunc = reinterpret_cast<decltype(glBeginPerfMonitorAMDFunc)>(func("VmiGlBeginPerfMonitorAMD"));
    glEndPerfMonitorAMDFunc = reinterpret_cast<decltype(glEndPerfMonitorAMDFunc)>(func("VmiGlEndPerfMonitorAMD"));
    glGetPerfMonitorCounterDataAMDFunc =
        reinterpret_cast<decltype(glGetPerfMonitorCounterDataAMDFunc)>(func("VmiGlGetPerfMonitorCounterDataAMD"));
    glRenderbufferStorageMultisampleIMGFunc = reinterpret_cast<decltype(glRenderbufferStorageMultisampleIMGFunc)>(
        func("VmiGlRenderbufferStorageMultisampleIMG"));
    glFramebufferTexture2DMultisampleIMGFunc = reinterpret_cast<decltype(glFramebufferTexture2DMultisampleIMGFunc)>(
        func("VmiGlFramebufferTexture2DMultisampleIMG"));
    glDeleteFencesNVFunc = reinterpret_cast<decltype(glDeleteFencesNVFunc)>(func("VmiGlDeleteFencesNV"));
    glGenFencesNVFunc = reinterpret_cast<decltype(glGenFencesNVFunc)>(func("VmiGlGenFencesNV"));
    glIsFenceNVFunc = reinterpret_cast<decltype(glIsFenceNVFunc)>(func("VmiGlIsFenceNV"));
    glTestFenceNVFunc = reinterpret_cast<decltype(glTestFenceNVFunc)>(func("VmiGlTestFenceNV"));
    glGetFenceivNVFunc = reinterpret_cast<decltype(glGetFenceivNVFunc)>(func("VmiGlGetFenceivNV"));
    glFinishFenceNVFunc = reinterpret_cast<decltype(glFinishFenceNVFunc)>(func("VmiGlFinishFenceNV"));
    glSetFenceNVFunc = reinterpret_cast<decltype(glSetFenceNVFunc)>(func("VmiGlSetFenceNV"));
    glCoverageMaskNVFunc = reinterpret_cast<decltype(glCoverageMaskNVFunc)>(func("VmiGlCoverageMaskNV"));
    glCoverageOperationNVFunc = reinterpret_cast<decltype(glCoverageOperationNVFunc)>(func("VmiGlCoverageOperationNV"));
    glGetDriverControlsQCOMFunc =
        reinterpret_cast<decltype(glGetDriverControlsQCOMFunc)>(func("VmiGlGetDriverControlsQCOM"));
    glGetDriverControlStringQCOMFunc =
        reinterpret_cast<decltype(glGetDriverControlStringQCOMFunc)>(func("VmiGlGetDriverControlStringQCOM"));
    glEnableDriverControlQCOMFunc =
        reinterpret_cast<decltype(glEnableDriverControlQCOMFunc)>(func("VmiGlEnableDriverControlQCOM"));
    glDisableDriverControlQCOMFunc =
        reinterpret_cast<decltype(glDisableDriverControlQCOMFunc)>(func("VmiGlDisableDriverControlQCOM"));
    glExtGetTexturesQCOMFunc = reinterpret_cast<decltype(glExtGetTexturesQCOMFunc)>(func("VmiGlExtGetTexturesQCOM"));
    glExtGetBuffersQCOMFunc = reinterpret_cast<decltype(glExtGetBuffersQCOMFunc)>(func("VmiGlExtGetBuffersQCOM"));
    glExtGetRenderbuffersQCOMFunc =
        reinterpret_cast<decltype(glExtGetRenderbuffersQCOMFunc)>(func("VmiGlExtGetRenderbuffersQCOM"));
    glExtGetFramebuffersQCOMFunc =
        reinterpret_cast<decltype(glExtGetFramebuffersQCOMFunc)>(func("VmiGlExtGetFramebuffersQCOM"));
    glExtGetTexLevelParameterivQCOMFunc =
        reinterpret_cast<decltype(glExtGetTexLevelParameterivQCOMFunc)>(func("VmiGlExtGetTexLevelParameterivQCOM"));
    glExtTexObjectStateOverrideiQCOMFunc =
        reinterpret_cast<decltype(glExtTexObjectStateOverrideiQCOMFunc)>(func("VmiGlExtTexObjectStateOverrideiQCOM"));
    glExtGetTexSubImageQCOMFunc =
        reinterpret_cast<decltype(glExtGetTexSubImageQCOMFunc)>(func("VmiGlExtGetTexSubImageQCOM"));
    glExtGetBufferPointervQCOMFunc =
        reinterpret_cast<decltype(glExtGetBufferPointervQCOMFunc)>(func("VmiGlExtGetBufferPointervQCOM"));
    glExtGetShadersQCOMFunc = reinterpret_cast<decltype(glExtGetShadersQCOMFunc)>(func("VmiGlExtGetShadersQCOM"));
    glExtGetProgramsQCOMFunc = reinterpret_cast<decltype(glExtGetProgramsQCOMFunc)>(func("VmiGlExtGetProgramsQCOM"));
    glExtIsProgramBinaryQCOMFunc =
        reinterpret_cast<decltype(glExtIsProgramBinaryQCOMFunc)>(func("VmiGlExtIsProgramBinaryQCOM"));
    glExtGetProgramBinarySourceQCOMFunc =
        reinterpret_cast<decltype(glExtGetProgramBinarySourceQCOMFunc)>(func("VmiGlExtGetProgramBinarySourceQCOM"));
    glStartTilingQCOMFunc = reinterpret_cast<decltype(glStartTilingQCOMFunc)>(func("VmiGlStartTilingQCOM"));
    glEndTilingQCOMFunc = reinterpret_cast<decltype(glEndTilingQCOMFunc)>(func("VmiGlEndTilingQCOM"));
    glGenVertexArraysFunc = reinterpret_cast<decltype(glGenVertexArraysFunc)>(func("VmiGlGenVertexArrays"));
    glBindVertexArrayFunc = reinterpret_cast<decltype(glBindVertexArrayFunc)>(func("VmiGlBindVertexArray"));
    glDeleteVertexArraysFunc = reinterpret_cast<decltype(glDeleteVertexArraysFunc)>(func("VmiGlDeleteVertexArrays"));
    glIsVertexArrayFunc = reinterpret_cast<decltype(glIsVertexArrayFunc)>(func("VmiGlIsVertexArray"));
    glMapBufferRangeFunc = reinterpret_cast<decltype(glMapBufferRangeFunc)>(func("VmiGlMapBufferRange"));
    glUnmapBufferFunc = reinterpret_cast<decltype(glUnmapBufferFunc)>(func("VmiGlUnmapBuffer"));
    glFlushMappedBufferRangeFunc =
        reinterpret_cast<decltype(glFlushMappedBufferRangeFunc)>(func("VmiGlFlushMappedBufferRange"));
    glBindBufferRangeFunc = reinterpret_cast<decltype(glBindBufferRangeFunc)>(func("VmiGlBindBufferRange"));
    glBindBufferBaseFunc = reinterpret_cast<decltype(glBindBufferBaseFunc)>(func("VmiGlBindBufferBase"));
    glCopyBufferSubDataFunc = reinterpret_cast<decltype(glCopyBufferSubDataFunc)>(func("VmiGlCopyBufferSubData"));
    glClearBufferivFunc = reinterpret_cast<decltype(glClearBufferivFunc)>(func("VmiGlClearBufferiv"));
    glClearBufferuivFunc = reinterpret_cast<decltype(glClearBufferuivFunc)>(func("VmiGlClearBufferuiv"));
    glClearBufferfvFunc = reinterpret_cast<decltype(glClearBufferfvFunc)>(func("VmiGlClearBufferfv"));
    glClearBufferfiFunc = reinterpret_cast<decltype(glClearBufferfiFunc)>(func("VmiGlClearBufferfi"));
    glGetBufferParameteri64vFunc =
        reinterpret_cast<decltype(glGetBufferParameteri64vFunc)>(func("VmiGlGetBufferParameteri64v"));
    glGetBufferPointervFunc = reinterpret_cast<decltype(glGetBufferPointervFunc)>(func("VmiGlGetBufferPointerv"));
    glUniformBlockBindingFunc = reinterpret_cast<decltype(glUniformBlockBindingFunc)>(func("VmiGlUniformBlockBinding"));
    glGetUniformBlockIndexFunc =
        reinterpret_cast<decltype(glGetUniformBlockIndexFunc)>(func("VmiGlGetUniformBlockIndex"));
    glGetUniformIndicesFunc = reinterpret_cast<decltype(glGetUniformIndicesFunc)>(func("VmiGlGetUniformIndices"));
    glGetActiveUniformBlockivFunc =
        reinterpret_cast<decltype(glGetActiveUniformBlockivFunc)>(func("VmiGlGetActiveUniformBlockiv"));
    glGetActiveUniformBlockNameFunc =
        reinterpret_cast<decltype(glGetActiveUniformBlockNameFunc)>(func("VmiGlGetActiveUniformBlockName"));
    glUniform1uiFunc = reinterpret_cast<decltype(glUniform1uiFunc)>(func("VmiGlUniform1ui"));
    glUniform2uiFunc = reinterpret_cast<decltype(glUniform2uiFunc)>(func("VmiGlUniform2ui"));
    glUniform3uiFunc = reinterpret_cast<decltype(glUniform3uiFunc)>(func("VmiGlUniform3ui"));
    glUniform4uiFunc = reinterpret_cast<decltype(glUniform4uiFunc)>(func("VmiGlUniform4ui"));
    glUniform1uivFunc = reinterpret_cast<decltype(glUniform1uivFunc)>(func("VmiGlUniform1uiv"));
    glUniform2uivFunc = reinterpret_cast<decltype(glUniform2uivFunc)>(func("VmiGlUniform2uiv"));
    glUniform3uivFunc = reinterpret_cast<decltype(glUniform3uivFunc)>(func("VmiGlUniform3uiv"));
    glUniform4uivFunc = reinterpret_cast<decltype(glUniform4uivFunc)>(func("VmiGlUniform4uiv"));
    glUniformMatrix2x3fvFunc = reinterpret_cast<decltype(glUniformMatrix2x3fvFunc)>(func("VmiGlUniformMatrix2x3fv"));
    glUniformMatrix3x2fvFunc = reinterpret_cast<decltype(glUniformMatrix3x2fvFunc)>(func("VmiGlUniformMatrix3x2fv"));
    glUniformMatrix2x4fvFunc = reinterpret_cast<decltype(glUniformMatrix2x4fvFunc)>(func("VmiGlUniformMatrix2x4fv"));
    glUniformMatrix4x2fvFunc = reinterpret_cast<decltype(glUniformMatrix4x2fvFunc)>(func("VmiGlUniformMatrix4x2fv"));
    glUniformMatrix3x4fvFunc = reinterpret_cast<decltype(glUniformMatrix3x4fvFunc)>(func("VmiGlUniformMatrix3x4fv"));
    glUniformMatrix4x3fvFunc = reinterpret_cast<decltype(glUniformMatrix4x3fvFunc)>(func("VmiGlUniformMatrix4x3fv"));
    glGetUniformuivFunc = reinterpret_cast<decltype(glGetUniformuivFunc)>(func("VmiGlGetUniformuiv"));
    glGetActiveUniformsivFunc = reinterpret_cast<decltype(glGetActiveUniformsivFunc)>(func("VmiGlGetActiveUniformsiv"));
    glVertexAttribI4iFunc = reinterpret_cast<decltype(glVertexAttribI4iFunc)>(func("VmiGlVertexAttribI4i"));
    glVertexAttribI4uiFunc = reinterpret_cast<decltype(glVertexAttribI4uiFunc)>(func("VmiGlVertexAttribI4ui"));
    glVertexAttribI4ivFunc = reinterpret_cast<decltype(glVertexAttribI4ivFunc)>(func("VmiGlVertexAttribI4iv"));
    glVertexAttribI4uivFunc = reinterpret_cast<decltype(glVertexAttribI4uivFunc)>(func("VmiGlVertexAttribI4uiv"));
    glVertexAttribIPointerFunc =
        reinterpret_cast<decltype(glVertexAttribIPointerFunc)>(func("VmiGlVertexAttribIPointer"));
    glGetVertexAttribIivFunc = reinterpret_cast<decltype(glGetVertexAttribIivFunc)>(func("VmiGlGetVertexAttribIiv"));
    glGetVertexAttribIuivFunc = reinterpret_cast<decltype(glGetVertexAttribIuivFunc)>(func("VmiGlGetVertexAttribIuiv"));
    glVertexAttribDivisorFunc = reinterpret_cast<decltype(glVertexAttribDivisorFunc)>(func("VmiGlVertexAttribDivisor"));
    glDrawArraysInstancedFunc = reinterpret_cast<decltype(glDrawArraysInstancedFunc)>(func("VmiGlDrawArraysInstanced"));
    glDrawElementsInstancedFunc =
        reinterpret_cast<decltype(glDrawElementsInstancedFunc)>(func("VmiGlDrawElementsInstanced"));
    glDrawRangeElementsFunc = reinterpret_cast<decltype(glDrawRangeElementsFunc)>(func("VmiGlDrawRangeElements"));
    glFenceSyncFunc = reinterpret_cast<decltype(glFenceSyncFunc)>(func("VmiGlFenceSync"));
    glClientWaitSyncFunc = reinterpret_cast<decltype(glClientWaitSyncFunc)>(func("VmiGlClientWaitSync"));
    glWaitSyncFunc = reinterpret_cast<decltype(glWaitSyncFunc)>(func("VmiGlWaitSync"));
    glDeleteSyncFunc = reinterpret_cast<decltype(glDeleteSyncFunc)>(func("VmiGlDeleteSync"));
    glIsSyncFunc = reinterpret_cast<decltype(glIsSyncFunc)>(func("VmiGlIsSync"));
    glGetSyncivFunc = reinterpret_cast<decltype(glGetSyncivFunc)>(func("VmiGlGetSynciv"));
    glDrawBuffersFunc = reinterpret_cast<decltype(glDrawBuffersFunc)>(func("VmiGlDrawBuffers"));
    glReadBufferFunc = reinterpret_cast<decltype(glReadBufferFunc)>(func("VmiGlReadBuffer"));
    glBlitFramebufferFunc = reinterpret_cast<decltype(glBlitFramebufferFunc)>(func("VmiGlBlitFramebuffer"));
    glInvalidateFramebufferFunc =
        reinterpret_cast<decltype(glInvalidateFramebufferFunc)>(func("VmiGlInvalidateFramebuffer"));
    glInvalidateSubFramebufferFunc =
        reinterpret_cast<decltype(glInvalidateSubFramebufferFunc)>(func("VmiGlInvalidateSubFramebuffer"));
    glFramebufferTextureLayerFunc =
        reinterpret_cast<decltype(glFramebufferTextureLayerFunc)>(func("VmiGlFramebufferTextureLayer"));
    glRenderbufferStorageMultisampleFunc =
        reinterpret_cast<decltype(glRenderbufferStorageMultisampleFunc)>(func("VmiGlRenderbufferStorageMultisample"));
    glTexStorage2DFunc = reinterpret_cast<decltype(glTexStorage2DFunc)>(func("VmiGlTexStorage2D"));
    glGetInternalformativFunc = reinterpret_cast<decltype(glGetInternalformativFunc)>(func("VmiGlGetInternalformativ"));
    glBeginTransformFeedbackFunc =
        reinterpret_cast<decltype(glBeginTransformFeedbackFunc)>(func("VmiGlBeginTransformFeedback"));
    glEndTransformFeedbackFunc =
        reinterpret_cast<decltype(glEndTransformFeedbackFunc)>(func("VmiGlEndTransformFeedback"));
    glGenTransformFeedbacksFunc =
        reinterpret_cast<decltype(glGenTransformFeedbacksFunc)>(func("VmiGlGenTransformFeedbacks"));
    glDeleteTransformFeedbacksFunc =
        reinterpret_cast<decltype(glDeleteTransformFeedbacksFunc)>(func("VmiGlDeleteTransformFeedbacks"));
    glBindTransformFeedbackFunc =
        reinterpret_cast<decltype(glBindTransformFeedbackFunc)>(func("VmiGlBindTransformFeedback"));
    glPauseTransformFeedbackFunc =
        reinterpret_cast<decltype(glPauseTransformFeedbackFunc)>(func("VmiGlPauseTransformFeedback"));
    glResumeTransformFeedbackFunc =
        reinterpret_cast<decltype(glResumeTransformFeedbackFunc)>(func("VmiGlResumeTransformFeedback"));
    glIsTransformFeedbackFunc = reinterpret_cast<decltype(glIsTransformFeedbackFunc)>(func("VmiGlIsTransformFeedback"));
    glTransformFeedbackVaryingsFunc =
        reinterpret_cast<decltype(glTransformFeedbackVaryingsFunc)>(func("VmiGlTransformFeedbackVaryings"));
    glGetTransformFeedbackVaryingFunc =
        reinterpret_cast<decltype(glGetTransformFeedbackVaryingFunc)>(func("VmiGlGetTransformFeedbackVarying"));
    glGenSamplersFunc = reinterpret_cast<decltype(glGenSamplersFunc)>(func("VmiGlGenSamplers"));
    glDeleteSamplersFunc = reinterpret_cast<decltype(glDeleteSamplersFunc)>(func("VmiGlDeleteSamplers"));
    glBindSamplerFunc = reinterpret_cast<decltype(glBindSamplerFunc)>(func("VmiGlBindSampler"));
    glSamplerParameterfFunc = reinterpret_cast<decltype(glSamplerParameterfFunc)>(func("VmiGlSamplerParameterf"));
    glSamplerParameteriFunc = reinterpret_cast<decltype(glSamplerParameteriFunc)>(func("VmiGlSamplerParameteri"));
    glSamplerParameterfvFunc = reinterpret_cast<decltype(glSamplerParameterfvFunc)>(func("VmiGlSamplerParameterfv"));
    glSamplerParameterivFunc = reinterpret_cast<decltype(glSamplerParameterivFunc)>(func("VmiGlSamplerParameteriv"));
    glGetSamplerParameterfvFunc =
        reinterpret_cast<decltype(glGetSamplerParameterfvFunc)>(func("VmiGlGetSamplerParameterfv"));
    glGetSamplerParameterivFunc =
        reinterpret_cast<decltype(glGetSamplerParameterivFunc)>(func("VmiGlGetSamplerParameteriv"));
    glIsSamplerFunc = reinterpret_cast<decltype(glIsSamplerFunc)>(func("VmiGlIsSampler"));
    glGenQueriesFunc = reinterpret_cast<decltype(glGenQueriesFunc)>(func("VmiGlGenQueries"));
    glDeleteQueriesFunc = reinterpret_cast<decltype(glDeleteQueriesFunc)>(func("VmiGlDeleteQueries"));
    glBeginQueryFunc = reinterpret_cast<decltype(glBeginQueryFunc)>(func("VmiGlBeginQuery"));
    glEndQueryFunc = reinterpret_cast<decltype(glEndQueryFunc)>(func("VmiGlEndQuery"));
    glGetQueryivFunc = reinterpret_cast<decltype(glGetQueryivFunc)>(func("VmiGlGetQueryiv"));
    glGetQueryObjectuivFunc = reinterpret_cast<decltype(glGetQueryObjectuivFunc)>(func("VmiGlGetQueryObjectuiv"));
    glIsQueryFunc = reinterpret_cast<decltype(glIsQueryFunc)>(func("VmiGlIsQuery"));
    glProgramParameteriFunc = reinterpret_cast<decltype(glProgramParameteriFunc)>(func("VmiGlProgramParameteri"));
    glProgramBinaryFunc = reinterpret_cast<decltype(glProgramBinaryFunc)>(func("VmiGlProgramBinary"));
    glGetProgramBinaryFunc = reinterpret_cast<decltype(glGetProgramBinaryFunc)>(func("VmiGlGetProgramBinary"));
    glGetFragDataLocationFunc = reinterpret_cast<decltype(glGetFragDataLocationFunc)>(func("VmiGlGetFragDataLocation"));
    glGetInteger64vFunc = reinterpret_cast<decltype(glGetInteger64vFunc)>(func("VmiGlGetInteger64v"));
    glGetIntegeri_vFunc = reinterpret_cast<decltype(glGetIntegeri_vFunc)>(func("VmiGlGetIntegeri_v"));
    glGetInteger64i_vFunc = reinterpret_cast<decltype(glGetInteger64i_vFunc)>(func("VmiGlGetInteger64i_v"));
    glTexImage3DFunc = reinterpret_cast<decltype(glTexImage3DFunc)>(func("VmiGlTexImage3D"));
    glTexStorage3DFunc = reinterpret_cast<decltype(glTexStorage3DFunc)>(func("VmiGlTexStorage3D"));
    glTexSubImage3DFunc = reinterpret_cast<decltype(glTexSubImage3DFunc)>(func("VmiGlTexSubImage3D"));
    glCompressedTexImage3DFunc =
        reinterpret_cast<decltype(glCompressedTexImage3DFunc)>(func("VmiGlCompressedTexImage3D"));
    glCompressedTexSubImage3DFunc =
        reinterpret_cast<decltype(glCompressedTexSubImage3DFunc)>(func("VmiGlCompressedTexSubImage3D"));
    glCopyTexSubImage3DFunc = reinterpret_cast<decltype(glCopyTexSubImage3DFunc)>(func("VmiGlCopyTexSubImage3D"));
    glGetStringiFunc = reinterpret_cast<decltype(glGetStringiFunc)>(func("VmiGlGetStringi"));
    glGetBooleani_vFunc = reinterpret_cast<decltype(glGetBooleani_vFunc)>(func("VmiGlGetBooleani_v"));
    glMemoryBarrierFunc = reinterpret_cast<decltype(glMemoryBarrierFunc)>(func("VmiGlMemoryBarrier"));
    glMemoryBarrierByRegionFunc =
        reinterpret_cast<decltype(glMemoryBarrierByRegionFunc)>(func("VmiGlMemoryBarrierByRegion"));
    glGenProgramPipelinesFunc = reinterpret_cast<decltype(glGenProgramPipelinesFunc)>(func("VmiGlGenProgramPipelines"));
    glDeleteProgramPipelinesFunc =
        reinterpret_cast<decltype(glDeleteProgramPipelinesFunc)>(func("VmiGlDeleteProgramPipelines"));
    glBindProgramPipelineFunc = reinterpret_cast<decltype(glBindProgramPipelineFunc)>(func("VmiGlBindProgramPipeline"));
    glGetProgramPipelineivFunc =
        reinterpret_cast<decltype(glGetProgramPipelineivFunc)>(func("VmiGlGetProgramPipelineiv"));
    glGetProgramPipelineInfoLogFunc =
        reinterpret_cast<decltype(glGetProgramPipelineInfoLogFunc)>(func("VmiGlGetProgramPipelineInfoLog"));
    glValidateProgramPipelineFunc =
        reinterpret_cast<decltype(glValidateProgramPipelineFunc)>(func("VmiGlValidateProgramPipeline"));
    glIsProgramPipelineFunc = reinterpret_cast<decltype(glIsProgramPipelineFunc)>(func("VmiGlIsProgramPipeline"));
    glUseProgramStagesFunc = reinterpret_cast<decltype(glUseProgramStagesFunc)>(func("VmiGlUseProgramStages"));
    glActiveShaderProgramFunc = reinterpret_cast<decltype(glActiveShaderProgramFunc)>(func("VmiGlActiveShaderProgram"));
    glCreateShaderProgramvFunc =
        reinterpret_cast<decltype(glCreateShaderProgramvFunc)>(func("VmiGlCreateShaderProgramv"));
    glProgramUniform1fFunc = reinterpret_cast<decltype(glProgramUniform1fFunc)>(func("VmiGlProgramUniform1f"));
    glProgramUniform2fFunc = reinterpret_cast<decltype(glProgramUniform2fFunc)>(func("VmiGlProgramUniform2f"));
    glProgramUniform3fFunc = reinterpret_cast<decltype(glProgramUniform3fFunc)>(func("VmiGlProgramUniform3f"));
    glProgramUniform4fFunc = reinterpret_cast<decltype(glProgramUniform4fFunc)>(func("VmiGlProgramUniform4f"));
    glProgramUniform1iFunc = reinterpret_cast<decltype(glProgramUniform1iFunc)>(func("VmiGlProgramUniform1i"));
    glProgramUniform2iFunc = reinterpret_cast<decltype(glProgramUniform2iFunc)>(func("VmiGlProgramUniform2i"));
    glProgramUniform3iFunc = reinterpret_cast<decltype(glProgramUniform3iFunc)>(func("VmiGlProgramUniform3i"));
    glProgramUniform4iFunc = reinterpret_cast<decltype(glProgramUniform4iFunc)>(func("VmiGlProgramUniform4i"));
    glProgramUniform1uiFunc = reinterpret_cast<decltype(glProgramUniform1uiFunc)>(func("VmiGlProgramUniform1ui"));
    glProgramUniform2uiFunc = reinterpret_cast<decltype(glProgramUniform2uiFunc)>(func("VmiGlProgramUniform2ui"));
    glProgramUniform3uiFunc = reinterpret_cast<decltype(glProgramUniform3uiFunc)>(func("VmiGlProgramUniform3ui"));
    glProgramUniform4uiFunc = reinterpret_cast<decltype(glProgramUniform4uiFunc)>(func("VmiGlProgramUniform4ui"));
    glProgramUniform1fvFunc = reinterpret_cast<decltype(glProgramUniform1fvFunc)>(func("VmiGlProgramUniform1fv"));
    glProgramUniform2fvFunc = reinterpret_cast<decltype(glProgramUniform2fvFunc)>(func("VmiGlProgramUniform2fv"));
    glProgramUniform3fvFunc = reinterpret_cast<decltype(glProgramUniform3fvFunc)>(func("VmiGlProgramUniform3fv"));
    glProgramUniform4fvFunc = reinterpret_cast<decltype(glProgramUniform4fvFunc)>(func("VmiGlProgramUniform4fv"));
    glProgramUniform1ivFunc = reinterpret_cast<decltype(glProgramUniform1ivFunc)>(func("VmiGlProgramUniform1iv"));
    glProgramUniform2ivFunc = reinterpret_cast<decltype(glProgramUniform2ivFunc)>(func("VmiGlProgramUniform2iv"));
    glProgramUniform3ivFunc = reinterpret_cast<decltype(glProgramUniform3ivFunc)>(func("VmiGlProgramUniform3iv"));
    glProgramUniform4ivFunc = reinterpret_cast<decltype(glProgramUniform4ivFunc)>(func("VmiGlProgramUniform4iv"));
    glProgramUniform1uivFunc = reinterpret_cast<decltype(glProgramUniform1uivFunc)>(func("VmiGlProgramUniform1uiv"));
    glProgramUniform2uivFunc = reinterpret_cast<decltype(glProgramUniform2uivFunc)>(func("VmiGlProgramUniform2uiv"));
    glProgramUniform3uivFunc = reinterpret_cast<decltype(glProgramUniform3uivFunc)>(func("VmiGlProgramUniform3uiv"));
    glProgramUniform4uivFunc = reinterpret_cast<decltype(glProgramUniform4uivFunc)>(func("VmiGlProgramUniform4uiv"));
    glProgramUniformMatrix2fvFunc =
        reinterpret_cast<decltype(glProgramUniformMatrix2fvFunc)>(func("VmiGlProgramUniformMatrix2fv"));
    glProgramUniformMatrix3fvFunc =
        reinterpret_cast<decltype(glProgramUniformMatrix3fvFunc)>(func("VmiGlProgramUniformMatrix3fv"));
    glProgramUniformMatrix4fvFunc =
        reinterpret_cast<decltype(glProgramUniformMatrix4fvFunc)>(func("VmiGlProgramUniformMatrix4fv"));
    glProgramUniformMatrix2x3fvFunc =
        reinterpret_cast<decltype(glProgramUniformMatrix2x3fvFunc)>(func("VmiGlProgramUniformMatrix2x3fv"));
    glProgramUniformMatrix3x2fvFunc =
        reinterpret_cast<decltype(glProgramUniformMatrix3x2fvFunc)>(func("VmiGlProgramUniformMatrix3x2fv"));
    glProgramUniformMatrix2x4fvFunc =
        reinterpret_cast<decltype(glProgramUniformMatrix2x4fvFunc)>(func("VmiGlProgramUniformMatrix2x4fv"));
    glProgramUniformMatrix4x2fvFunc =
        reinterpret_cast<decltype(glProgramUniformMatrix4x2fvFunc)>(func("VmiGlProgramUniformMatrix4x2fv"));
    glProgramUniformMatrix3x4fvFunc =
        reinterpret_cast<decltype(glProgramUniformMatrix3x4fvFunc)>(func("VmiGlProgramUniformMatrix3x4fv"));
    glProgramUniformMatrix4x3fvFunc =
        reinterpret_cast<decltype(glProgramUniformMatrix4x3fvFunc)>(func("VmiGlProgramUniformMatrix4x3fv"));
    glGetProgramInterfaceivFunc =
        reinterpret_cast<decltype(glGetProgramInterfaceivFunc)>(func("VmiGlGetProgramInterfaceiv"));
    glGetProgramResourceivFunc =
        reinterpret_cast<decltype(glGetProgramResourceivFunc)>(func("VmiGlGetProgramResourceiv"));
    glGetProgramResourceIndexFunc =
        reinterpret_cast<decltype(glGetProgramResourceIndexFunc)>(func("VmiGlGetProgramResourceIndex"));
    glGetProgramResourceLocationFunc =
        reinterpret_cast<decltype(glGetProgramResourceLocationFunc)>(func("VmiGlGetProgramResourceLocation"));
    glGetProgramResourceNameFunc =
        reinterpret_cast<decltype(glGetProgramResourceNameFunc)>(func("VmiGlGetProgramResourceName"));
    glBindImageTextureFunc = reinterpret_cast<decltype(glBindImageTextureFunc)>(func("VmiGlBindImageTexture"));
    glDispatchComputeFunc = reinterpret_cast<decltype(glDispatchComputeFunc)>(func("VmiGlDispatchCompute"));
    glDispatchComputeIndirectFunc =
        reinterpret_cast<decltype(glDispatchComputeIndirectFunc)>(func("VmiGlDispatchComputeIndirect"));
    glBindVertexBufferFunc = reinterpret_cast<decltype(glBindVertexBufferFunc)>(func("VmiGlBindVertexBuffer"));
    glVertexAttribBindingFunc = reinterpret_cast<decltype(glVertexAttribBindingFunc)>(func("VmiGlVertexAttribBinding"));
    glVertexAttribFormatFunc = reinterpret_cast<decltype(glVertexAttribFormatFunc)>(func("VmiGlVertexAttribFormat"));
    glVertexAttribIFormatFunc = reinterpret_cast<decltype(glVertexAttribIFormatFunc)>(func("VmiGlVertexAttribIFormat"));
    glVertexBindingDivisorFunc =
        reinterpret_cast<decltype(glVertexBindingDivisorFunc)>(func("VmiGlVertexBindingDivisor"));
    glDrawArraysIndirectFunc = reinterpret_cast<decltype(glDrawArraysIndirectFunc)>(func("VmiGlDrawArraysIndirect"));
    glDrawElementsIndirectFunc =
        reinterpret_cast<decltype(glDrawElementsIndirectFunc)>(func("VmiGlDrawElementsIndirect"));
    glTexStorage2DMultisampleFunc =
        reinterpret_cast<decltype(glTexStorage2DMultisampleFunc)>(func("VmiGlTexStorage2DMultisample"));
    glSampleMaskiFunc = reinterpret_cast<decltype(glSampleMaskiFunc)>(func("VmiGlSampleMaski"));
    glGetMultisamplefvFunc = reinterpret_cast<decltype(glGetMultisamplefvFunc)>(func("VmiGlGetMultisamplefv"));
    glFramebufferParameteriFunc =
        reinterpret_cast<decltype(glFramebufferParameteriFunc)>(func("VmiGlFramebufferParameteri"));
    glGetFramebufferParameterivFunc =
        reinterpret_cast<decltype(glGetFramebufferParameterivFunc)>(func("VmiGlGetFramebufferParameteriv"));
    glGetTexLevelParameterfvFunc =
        reinterpret_cast<decltype(glGetTexLevelParameterfvFunc)>(func("VmiGlGetTexLevelParameterfv"));
    glGetTexLevelParameterivFunc =
        reinterpret_cast<decltype(glGetTexLevelParameterivFunc)>(func("VmiGlGetTexLevelParameteriv"));
    glEnableiEXTFunc = reinterpret_cast<decltype(glEnableiEXTFunc)>(func("VmiGlEnableiEXT"));
    glDisableiEXTFunc = reinterpret_cast<decltype(glDisableiEXTFunc)>(func("VmiGlDisableiEXT"));
    glBlendEquationiEXTFunc = reinterpret_cast<decltype(glBlendEquationiEXTFunc)>(func("VmiGlBlendEquationiEXT"));
    glBlendEquationSeparateiEXTFunc =
        reinterpret_cast<decltype(glBlendEquationSeparateiEXTFunc)>(func("VmiGlBlendEquationSeparateiEXT"));
    glBlendFunciEXTFunc = reinterpret_cast<decltype(glBlendFunciEXTFunc)>(func("VmiGlBlendFunciEXT"));
    glBlendFuncSeparateiEXTFunc =
        reinterpret_cast<decltype(glBlendFuncSeparateiEXTFunc)>(func("VmiGlBlendFuncSeparateiEXT"));
    glColorMaskiEXTFunc = reinterpret_cast<decltype(glColorMaskiEXTFunc)>(func("VmiGlColorMaskiEXT"));
    glIsEnablediEXTFunc = reinterpret_cast<decltype(glIsEnablediEXTFunc)>(func("VmiGlIsEnablediEXT"));
    glCopyImageSubDataEXTFunc = reinterpret_cast<decltype(glCopyImageSubDataEXTFunc)>(func("VmiGlCopyImageSubDataEXT"));
    glBlendBarrierKHRFunc = reinterpret_cast<decltype(glBlendBarrierKHRFunc)>(func("VmiGlBlendBarrierKHR"));
    glTexParameterIivEXTFunc = reinterpret_cast<decltype(glTexParameterIivEXTFunc)>(func("VmiGlTexParameterIivEXT"));
    glTexParameterIuivEXTFunc = reinterpret_cast<decltype(glTexParameterIuivEXTFunc)>(func("VmiGlTexParameterIuivEXT"));
    glGetTexParameterIivEXTFunc =
        reinterpret_cast<decltype(glGetTexParameterIivEXTFunc)>(func("VmiGlGetTexParameterIivEXT"));
    glGetTexParameterIuivEXTFunc =
        reinterpret_cast<decltype(glGetTexParameterIuivEXTFunc)>(func("VmiGlGetTexParameterIuivEXT"));
    glSamplerParameterIivEXTFunc =
        reinterpret_cast<decltype(glSamplerParameterIivEXTFunc)>(func("VmiGlSamplerParameterIivEXT"));
    glSamplerParameterIuivEXTFunc =
        reinterpret_cast<decltype(glSamplerParameterIuivEXTFunc)>(func("VmiGlSamplerParameterIuivEXT"));
    glGetSamplerParameterIivEXTFunc =
        reinterpret_cast<decltype(glGetSamplerParameterIivEXTFunc)>(func("VmiGlGetSamplerParameterIivEXT"));
    glGetSamplerParameterIuivEXTFunc =
        reinterpret_cast<decltype(glGetSamplerParameterIuivEXTFunc)>(func("VmiGlGetSamplerParameterIuivEXT"));
    glVertexAttribPointerDataFunc =
        reinterpret_cast<decltype(glVertexAttribPointerDataFunc)>(func("VmiGlVertexAttribPointerData"));
    glVertexAttribPointerOffsetFunc =
        reinterpret_cast<decltype(glVertexAttribPointerOffsetFunc)>(func("VmiGlVertexAttribPointerOffset"));
    glDrawElementsOffsetFunc = reinterpret_cast<decltype(glDrawElementsOffsetFunc)>(func("VmiGlDrawElementsOffset"));
    glDrawElementsDataFunc = reinterpret_cast<decltype(glDrawElementsDataFunc)>(func("VmiGlDrawElementsData"));
    glGetCompressedTextureFormatsFunc =
        reinterpret_cast<decltype(glGetCompressedTextureFormatsFunc)>(func("VmiGlGetCompressedTextureFormats"));
    glShaderStringFunc = reinterpret_cast<decltype(glShaderStringFunc)>(func("VmiGlShaderString"));
    glFinishRoundTripFunc = reinterpret_cast<decltype(glFinishRoundTripFunc)>(func("VmiGlFinishRoundTrip"));
    glMapBufferRangeAEMUFunc = reinterpret_cast<decltype(glMapBufferRangeAEMUFunc)>(func("VmiGlMapBufferRangeAEMU"));
    glUnmapBufferAEMUFunc = reinterpret_cast<decltype(glUnmapBufferAEMUFunc)>(func("VmiGlUnmapBufferAEMU"));
    glFlushMappedBufferRangeAEMUFunc =
        reinterpret_cast<decltype(glFlushMappedBufferRangeAEMUFunc)>(func("VmiGlFlushMappedBufferRangeAEMU"));
    glReadPixelsOffsetAEMUFunc =
        reinterpret_cast<decltype(glReadPixelsOffsetAEMUFunc)>(func("VmiGlReadPixelsOffsetAEMU"));
    glCompressedTexImage2DOffsetAEMUFunc =
        reinterpret_cast<decltype(glCompressedTexImage2DOffsetAEMUFunc)>(func("VmiGlCompressedTexImage2DOffsetAEMU"));
    glCompressedTexSubImage2DOffsetAEMUFunc = reinterpret_cast<decltype(glCompressedTexSubImage2DOffsetAEMUFunc)>(
        func("VmiGlCompressedTexSubImage2DOffsetAEMU"));
    glTexImage2DOffsetAEMUFunc =
        reinterpret_cast<decltype(glTexImage2DOffsetAEMUFunc)>(func("VmiGlTexImage2DOffsetAEMU"));
    glTexSubImage2DOffsetAEMUFunc =
        reinterpret_cast<decltype(glTexSubImage2DOffsetAEMUFunc)>(func("VmiGlTexSubImage2DOffsetAEMU"));
    glGetUniformIndicesAEMUFunc =
        reinterpret_cast<decltype(glGetUniformIndicesAEMUFunc)>(func("VmiGlGetUniformIndicesAEMU"));
    glVertexAttribIPointerOffsetAEMUFunc =
        reinterpret_cast<decltype(glVertexAttribIPointerOffsetAEMUFunc)>(func("VmiGlVertexAttribIPointerOffsetAEMU"));
    glVertexAttribIPointerDataAEMUFunc =
        reinterpret_cast<decltype(glVertexAttribIPointerDataAEMUFunc)>(func("VmiGlVertexAttribIPointerDataAEMU"));
    glDrawElementsInstancedDataAEMUFunc =
        reinterpret_cast<decltype(glDrawElementsInstancedDataAEMUFunc)>(func("VmiGlDrawElementsInstancedDataAEMU"));
    glDrawElementsInstancedOffsetAEMUFunc =
        reinterpret_cast<decltype(glDrawElementsInstancedOffsetAEMUFunc)>(func("VmiGlDrawElementsInstancedOffsetAEMU"));
    glDrawRangeElementsDataAEMUFunc =
        reinterpret_cast<decltype(glDrawRangeElementsDataAEMUFunc)>(func("VmiGlDrawRangeElementsDataAEMU"));
    glDrawRangeElementsOffsetAEMUFunc =
        reinterpret_cast<decltype(glDrawRangeElementsOffsetAEMUFunc)>(func("VmiGlDrawRangeElementsOffsetAEMU"));
    glFenceSyncAEMUFunc = reinterpret_cast<decltype(glFenceSyncAEMUFunc)>(func("VmiGlFenceSyncAEMU"));
    glClientWaitSyncAEMUFunc = reinterpret_cast<decltype(glClientWaitSyncAEMUFunc)>(func("VmiGlClientWaitSyncAEMU"));
    glWaitSyncAEMUFunc = reinterpret_cast<decltype(glWaitSyncAEMUFunc)>(func("VmiGlWaitSyncAEMU"));
    glDeleteSyncAEMUFunc = reinterpret_cast<decltype(glDeleteSyncAEMUFunc)>(func("VmiGlDeleteSyncAEMU"));
    glIsSyncAEMUFunc = reinterpret_cast<decltype(glIsSyncAEMUFunc)>(func("VmiGlIsSyncAEMU"));
    glGetSyncivAEMUFunc = reinterpret_cast<decltype(glGetSyncivAEMUFunc)>(func("VmiGlGetSyncivAEMU"));
    glTransformFeedbackVaryingsAEMUFunc =
        reinterpret_cast<decltype(glTransformFeedbackVaryingsAEMUFunc)>(func("VmiGlTransformFeedbackVaryingsAEMU"));
    glTexImage3DOffsetAEMUFunc =
        reinterpret_cast<decltype(glTexImage3DOffsetAEMUFunc)>(func("VmiGlTexImage3DOffsetAEMU"));
    glTexSubImage3DOffsetAEMUFunc =
        reinterpret_cast<decltype(glTexSubImage3DOffsetAEMUFunc)>(func("VmiGlTexSubImage3DOffsetAEMU"));
    glCompressedTexImage3DOffsetAEMUFunc =
        reinterpret_cast<decltype(glCompressedTexImage3DOffsetAEMUFunc)>(func("VmiGlCompressedTexImage3DOffsetAEMU"));
    glCompressedTexSubImage3DOffsetAEMUFunc = reinterpret_cast<decltype(glCompressedTexSubImage3DOffsetAEMUFunc)>(
        func("VmiGlCompressedTexSubImage3DOffsetAEMU"));
    glCreateShaderProgramvAEMUFunc =
        reinterpret_cast<decltype(glCreateShaderProgramvAEMUFunc)>(func("VmiGlCreateShaderProgramvAEMU"));
    glDrawArraysIndirectDataAEMUFunc =
        reinterpret_cast<decltype(glDrawArraysIndirectDataAEMUFunc)>(func("VmiGlDrawArraysIndirectDataAEMU"));
    glDrawArraysIndirectOffsetAEMUFunc =
        reinterpret_cast<decltype(glDrawArraysIndirectOffsetAEMUFunc)>(func("VmiGlDrawArraysIndirectOffsetAEMU"));
    glDrawElementsIndirectDataAEMUFunc =
        reinterpret_cast<decltype(glDrawElementsIndirectDataAEMUFunc)>(func("VmiGlDrawElementsIndirectDataAEMU"));
    glDrawElementsIndirectOffsetAEMUFunc =
        reinterpret_cast<decltype(glDrawElementsIndirectOffsetAEMUFunc)>(func("VmiGlDrawElementsIndirectOffsetAEMU"));
    glUniformLayoutFunc = reinterpret_cast<decltype(glUniformLayoutFunc)>(func("VmiGlUniformLayout"));
    m_isInit = true;
    ALOGD("GL2EncoderBase::InitGLESv2Export success!");
    return true;
}

uint32_t GL2EncoderBase::GetGLESv2Encoder(void *self)
{
    GL2Encoder *ctx = static_cast<GL2Encoder *>(self);
    return ctx->m_GLESv2Encoder;
}

bool GL2EncoderBase::CreateVmiGLESv2Encoder(uint32_t streamHandle)
{
    if (createGLESv2EncoderFunc == nullptr) {
        return false;
    }
    m_GLESv2Encoder = createGLESv2EncoderFunc(streamHandle);
    if (m_GLESv2Encoder == 0) {
        return false;
    }
    return true;
}

void GL2EncoderBase::DeleteVmiGLESv2Encoder()
{
    if (deleteGLESv2EncoderFunc == nullptr) {
        ALOGE("delete glesv2 encoder is nullptr");
        return;
    }
    deleteGLESv2EncoderFunc(m_GLESv2Encoder);
}

void GL2EncoderBase::glActiveTexture_s(void *self, unsigned int texture)
{
    GET_CONTEXT;
    ctx->glActiveTextureFunc(ctx->GetGLESv2Encoder(self), texture);
}

void GL2EncoderBase::glAttachShader_s(void *self, GLuint program, GLuint shader)
{
    GET_CONTEXT;
    ctx->glAttachShaderFunc(ctx->GetGLESv2Encoder(self), program, shader);
}

void GL2EncoderBase::glBindAttribLocation_s(void *self, GLuint program, GLuint index, const GLchar *name)
{
    GET_CONTEXT;
    ctx->glBindAttribLocationFunc(ctx->GetGLESv2Encoder(self), program, index, name);
}

void GL2EncoderBase::glBindBuffer_s(void *self, GLenum target, GLuint buffer)
{
    GET_CONTEXT;
    ctx->glBindBufferFunc(ctx->GetGLESv2Encoder(self), target, buffer);
}

void GL2EncoderBase::glBindFramebuffer_s(void *self, GLenum target, GLuint framebuffer)
{
    GET_CONTEXT;
    ctx->glBindFramebufferFunc(ctx->GetGLESv2Encoder(self), target, framebuffer);
}

void GL2EncoderBase::glBindRenderbuffer_s(void *self, GLenum target, GLuint renderbuffer)
{
    GET_CONTEXT;
    ctx->glBindRenderbufferFunc(ctx->GetGLESv2Encoder(self), target, renderbuffer);
}

void GL2EncoderBase::glBindTexture_s(void *self, GLenum target, GLuint texture)
{
    GET_CONTEXT;
    ctx->glBindTextureFunc(ctx->GetGLESv2Encoder(self), target, texture);
}

void GL2EncoderBase::glBlendColor_s(void *self, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
    GET_CONTEXT;
    ctx->glBlendColorFunc(ctx->GetGLESv2Encoder(self), red, green, blue, alpha);
}

void GL2EncoderBase::glBlendEquation_s(void *self, GLenum mode)
{
    GET_CONTEXT;
    ctx->glBlendEquationFunc(ctx->GetGLESv2Encoder(self), mode);
}

void GL2EncoderBase::glBlendEquationSeparate_s(void *self, GLenum modeRGB, GLenum modeAlpha)
{
    GET_CONTEXT;
    ctx->glBlendEquationSeparateFunc(ctx->GetGLESv2Encoder(self), modeRGB, modeAlpha);
}

void GL2EncoderBase::glBlendFunc_s(void *self, GLenum sfactor, GLenum dfactor)
{
    GET_CONTEXT;
    ctx->glBlendFuncFunc(ctx->GetGLESv2Encoder(self), sfactor, dfactor);
}

void GL2EncoderBase::glBlendFuncSeparate_s(void *self, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
    GET_CONTEXT;
    ctx->glBlendFuncSeparateFunc(ctx->GetGLESv2Encoder(self), srcRGB, dstRGB, srcAlpha, dstAlpha);
}

void GL2EncoderBase::glBufferData_s(void *self, GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage)
{
    GET_CONTEXT;
    ctx->glBufferDataFunc(ctx->GetGLESv2Encoder(self), target, size, data, usage);
}

void GL2EncoderBase::glBufferSubData_s(void *self, GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data)
{
    GET_CONTEXT;
    ctx->glBufferSubDataFunc(ctx->GetGLESv2Encoder(self), target, offset, size, data);
}

GLenum GL2EncoderBase::glCheckFramebufferStatus_s(void *self, GLenum target)
{
    GET_CONTEXT;
    return ctx->glCheckFramebufferStatusFunc(ctx->GetGLESv2Encoder(self), target);
}

void GL2EncoderBase::glClear_s(void *self, GLbitfield mask)
{
    GET_CONTEXT;
    ctx->glClearFunc(ctx->GetGLESv2Encoder(self), mask);
}

void GL2EncoderBase::glClearColor_s(void *self, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
    GET_CONTEXT;
    ctx->glClearColorFunc(ctx->GetGLESv2Encoder(self), red, green, blue, alpha);
}

void GL2EncoderBase::glClearDepthf_s(void *self, GLfloat d)
{
    GET_CONTEXT;
    ctx->glClearDepthfFunc(ctx->GetGLESv2Encoder(self), d);
}

void GL2EncoderBase::glClearStencil_s(void *self, GLint s)
{
    GET_CONTEXT;
    ctx->glClearStencilFunc(ctx->GetGLESv2Encoder(self), s);
}

void GL2EncoderBase::glColorMask_s(void *self, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
    GET_CONTEXT;
    ctx->glColorMaskFunc(ctx->GetGLESv2Encoder(self), red, green, blue, alpha);
}

void GL2EncoderBase::glCompileShader_s(void *self, GLuint shader)
{
    GET_CONTEXT;
    ctx->glCompileShaderFunc(ctx->GetGLESv2Encoder(self), shader);
}

void GL2EncoderBase::glCompressedTexImage2D_s(void *self, GLenum target, GLint level, GLenum internalformat,
    GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data)
{
    GET_CONTEXT;
    ctx->glCompressedTexImage2DFunc(ctx->GetGLESv2Encoder(self), target, level, internalformat, width, height, border,
        imageSize, data);
}

void GL2EncoderBase::glCompressedTexSubImage2D_s(void *self, GLenum target, GLint level, GLint xoffset, GLint yoffset,
    GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data)
{
    GET_CONTEXT;
    ctx->glCompressedTexSubImage2DFunc(ctx->GetGLESv2Encoder(self), target, level, xoffset, yoffset, width, height,
        format, imageSize, data);
}

void GL2EncoderBase::glCopyTexImage2D_s(void *self, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y,
    GLsizei width, GLsizei height, GLint border)
{
    GET_CONTEXT;
    ctx->glCopyTexImage2DFunc(ctx->GetGLESv2Encoder(self), target, level, internalformat, x, y, width, height, border);
}

void GL2EncoderBase::glCopyTexSubImage2D_s(void *self, GLenum target, GLint level, GLint xoffset, GLint yoffset,
    GLint x, GLint y, GLsizei width, GLsizei height)
{
    GET_CONTEXT;
    ctx->glCopyTexSubImage2DFunc(ctx->GetGLESv2Encoder(self), target, level, xoffset, yoffset, x, y, width, height);
}

GLuint GL2EncoderBase::glCreateProgram_s(void *self)
{
    GET_CONTEXT;
    return ctx->glCreateProgramFunc(ctx->GetGLESv2Encoder(self));
}

GLuint GL2EncoderBase::glCreateShader_s(void *self, GLenum type)
{
    GET_CONTEXT;
    return ctx->glCreateShaderFunc(ctx->GetGLESv2Encoder(self), type);
}

void GL2EncoderBase::glCullFace_s(void *self, GLenum mode)
{
    GET_CONTEXT;
    ctx->glCullFaceFunc(ctx->GetGLESv2Encoder(self), mode);
}

void GL2EncoderBase::glDeleteBuffers_s(void *self, GLsizei n, const GLuint *buffers)
{
    GET_CONTEXT;
    ctx->glDeleteBuffersFunc(ctx->GetGLESv2Encoder(self), n, buffers);
}

void GL2EncoderBase::glDeleteFramebuffers_s(void *self, GLsizei n, const GLuint *framebuffers)
{
    GET_CONTEXT;
    ctx->glDeleteFramebuffersFunc(ctx->GetGLESv2Encoder(self), n, framebuffers);
}

void GL2EncoderBase::glDeleteProgram_s(void *self, GLuint program)
{
    GET_CONTEXT;
    ctx->glDeleteProgramFunc(ctx->GetGLESv2Encoder(self), program);
}

void GL2EncoderBase::glDeleteRenderbuffers_s(void *self, GLsizei n, const GLuint *renderbuffers)
{
    GET_CONTEXT;
    ctx->glDeleteRenderbuffersFunc(ctx->GetGLESv2Encoder(self), n, renderbuffers);
}

void GL2EncoderBase::glDeleteShader_s(void *self, GLuint shader)
{
    GET_CONTEXT;
    ctx->glDeleteShaderFunc(ctx->GetGLESv2Encoder(self), shader);
}

void GL2EncoderBase::glDeleteTextures_s(void *self, GLsizei n, const GLuint *textures)
{
    GET_CONTEXT;
    ctx->glDeleteTexturesFunc(ctx->GetGLESv2Encoder(self), n, textures);
}

void GL2EncoderBase::glDepthFunc_s(void *self, GLenum func)
{
    GET_CONTEXT;
    ctx->glDepthFuncFunc(ctx->GetGLESv2Encoder(self), func);
}

void GL2EncoderBase::glDepthMask_s(void *self, GLboolean flag)
{
    GET_CONTEXT;
    ctx->glDepthMaskFunc(ctx->GetGLESv2Encoder(self), flag);
}

void GL2EncoderBase::glDepthRangef_s(void *self, GLclampf zNear, GLclampf zFar)
{
    GET_CONTEXT;
    ctx->glDepthRangefFunc(ctx->GetGLESv2Encoder(self), zNear, zFar);
}

void GL2EncoderBase::glDetachShader_s(void *self, GLuint program, GLuint shader)
{
    GET_CONTEXT;
    ctx->glDetachShaderFunc(ctx->GetGLESv2Encoder(self), program, shader);
}

void GL2EncoderBase::glDisable_s(void *self, GLenum cap)
{
    GET_CONTEXT;
    ctx->glDisableFunc(ctx->GetGLESv2Encoder(self), cap);
}

void GL2EncoderBase::glDisableVertexAttribArray_s(void *self, GLuint index)
{
    GET_CONTEXT;
    ctx->glDisableVertexAttribArrayFunc(ctx->GetGLESv2Encoder(self), index);
}

void GL2EncoderBase::glDrawArrays_s(void *self, GLenum mode, GLint first, GLsizei count)
{
    GET_CONTEXT;
    ctx->glDrawArraysFunc(ctx->GetGLESv2Encoder(self), mode, first, count);
}

void GL2EncoderBase::glDrawElements_s(void *self, GLenum mode, GLsizei count, GLenum type, const GLvoid *indices)
{
    GET_CONTEXT;
    ctx->glDrawElementsFunc(ctx->GetGLESv2Encoder(self), mode, count, type, indices);
}

void GL2EncoderBase::glEnable_s(void *self, GLenum cap)
{
    GET_CONTEXT;
    ctx->glEnableFunc(ctx->GetGLESv2Encoder(self), cap);
}

void GL2EncoderBase::glEnableVertexAttribArray_s(void *self, GLuint index)
{
    GET_CONTEXT;
    ctx->glEnableVertexAttribArrayFunc(ctx->GetGLESv2Encoder(self), index);
}

void GL2EncoderBase::glFlush_s(void *self)
{
    GET_CONTEXT;
    ctx->glFlushFunc(ctx->GetGLESv2Encoder(self));
}

void GL2EncoderBase::glFramebufferRenderbuffer_s(void *self, GLenum target, GLenum attachment,
    GLenum renderbuffertarget, GLuint renderbuffer)
{
    GET_CONTEXT;
    ctx->glFramebufferRenderbufferFunc(ctx->GetGLESv2Encoder(self), target, attachment, renderbuffertarget,
        renderbuffer);
}

void GL2EncoderBase::glFramebufferTexture2D_s(void *self, GLenum target, GLenum attachment, GLenum textarget,
    GLuint texture, GLint level)
{
    GET_CONTEXT;
    ctx->glFramebufferTexture2DFunc(ctx->GetGLESv2Encoder(self), target, attachment, textarget, texture, level);
}

void GL2EncoderBase::glFrontFace_s(void *self, GLenum mode)
{
    GET_CONTEXT;
    ctx->glFrontFaceFunc(ctx->GetGLESv2Encoder(self), mode);
}

void GL2EncoderBase::glGenBuffers_s(void *self, GLsizei n, GLuint *buffers)
{
    GET_CONTEXT;
    ctx->glGenBuffersFunc(ctx->GetGLESv2Encoder(self), n, buffers);
}

void GL2EncoderBase::glGenerateMipmap_s(void *self, GLenum target)
{
    GET_CONTEXT;
    ctx->glGenerateMipmapFunc(ctx->GetGLESv2Encoder(self), target);
}

void GL2EncoderBase::glGenFramebuffers_s(void *self, GLsizei n, GLuint *framebuffers)
{
    GET_CONTEXT;
    ctx->glGenFramebuffersFunc(ctx->GetGLESv2Encoder(self), n, framebuffers);
}

void GL2EncoderBase::glGenRenderbuffers_s(void *self, GLsizei n, GLuint *renderbuffers)
{
    GET_CONTEXT;
    ctx->glGenRenderbuffersFunc(ctx->GetGLESv2Encoder(self), n, renderbuffers);
}

void GL2EncoderBase::glGenTextures_s(void *self, GLsizei n, GLuint *textures)
{
    GET_CONTEXT;
    ctx->glGenTexturesFunc(ctx->GetGLESv2Encoder(self), n, textures);
}

void GL2EncoderBase::glGetActiveAttrib_s(void *self, GLuint program, GLuint index, GLsizei bufsize, GLsizei *length,
    GLint *size, GLenum *type, GLchar *name)
{
    GET_CONTEXT;
    ctx->glGetActiveAttribFunc(ctx->GetGLESv2Encoder(self), program, index, bufsize, length, size, type, name);
}

void GL2EncoderBase::glGetActiveUniform_s(void *self, GLuint program, GLuint index, GLsizei bufsize, GLsizei *length,
    GLint *size, GLenum *type, GLchar *name)
{
    GET_CONTEXT;
    ctx->glGetActiveUniformFunc(ctx->GetGLESv2Encoder(self), program, index, bufsize, length, size, type, name);
}

void GL2EncoderBase::glGetAttachedShaders_s(void *self, GLuint program, GLsizei maxcount, GLsizei *count,
    GLuint *shaders)
{
    GET_CONTEXT;
    ctx->glGetAttachedShadersFunc(ctx->GetGLESv2Encoder(self), program, maxcount, count, shaders);
}

int GL2EncoderBase::glGetAttribLocation_s(void *self, GLuint program, const GLchar *name)
{
    GET_CONTEXT;
    return ctx->glGetAttribLocationFunc(ctx->GetGLESv2Encoder(self), program, name);
}

void GL2EncoderBase::glGetBooleanv_s(void *self, GLenum pname, GLboolean *params)
{
    GET_CONTEXT;
    ctx->glGetBooleanvFunc(ctx->GetGLESv2Encoder(self), pname, params);
}

void GL2EncoderBase::glGetBufferParameteriv_s(void *self, GLenum target, GLenum pname, GLint *params)
{
    GET_CONTEXT;
    ctx->glGetBufferParameterivFunc(ctx->GetGLESv2Encoder(self), target, pname, params);
}

GLenum GL2EncoderBase::glGetError_s(void *self)
{
    GET_CONTEXT;
    return ctx->glGetErrorFunc(ctx->GetGLESv2Encoder(self));
}

void GL2EncoderBase::glGetFloatv_s(void *self, GLenum pname, GLfloat *params)
{
    GET_CONTEXT;
    ctx->glGetFloatvFunc(ctx->GetGLESv2Encoder(self), pname, params);
}

void GL2EncoderBase::glGetFramebufferAttachmentParameteriv_s(void *self, GLenum target, GLenum attachment, GLenum pname,
    GLint *params)
{
    GET_CONTEXT;
    ctx->glGetFramebufferAttachmentParameterivFunc(ctx->GetGLESv2Encoder(self), target, attachment, pname, params);
}

void GL2EncoderBase::glGetIntegerv_s(void *self, GLenum pname, GLint *params)
{
    GET_CONTEXT;
    ctx->glGetIntegervFunc(ctx->GetGLESv2Encoder(self), pname, params);
}

void GL2EncoderBase::glGetProgramiv_s(void *self, GLuint program, GLenum pname, GLint *params)
{
    GET_CONTEXT;
    ctx->glGetProgramivFunc(ctx->GetGLESv2Encoder(self), program, pname, params);
}

void GL2EncoderBase::glGetProgramInfoLog_s(void *self, GLuint program, GLsizei bufsize, GLsizei *length,
    GLchar *infolog)
{
    GET_CONTEXT;
    ctx->glGetProgramInfoLogFunc(ctx->GetGLESv2Encoder(self), program, bufsize, length, infolog);
}

void GL2EncoderBase::glGetRenderbufferParameteriv_s(void *self, GLenum target, GLenum pname, GLint *params)
{
    GET_CONTEXT;
    ctx->glGetRenderbufferParameterivFunc(ctx->GetGLESv2Encoder(self), target, pname, params);
}

void GL2EncoderBase::glGetShaderiv_s(void *self, GLuint shader, GLenum pname, GLint *params)
{
    GET_CONTEXT;
    ctx->glGetShaderivFunc(ctx->GetGLESv2Encoder(self), shader, pname, params);
}

void GL2EncoderBase::glGetShaderInfoLog_s(void *self, GLuint shader, GLsizei bufsize, GLsizei *length, GLchar *infolog)
{
    GET_CONTEXT;
    ctx->glGetShaderInfoLogFunc(ctx->GetGLESv2Encoder(self), shader, bufsize, length, infolog);
}

void GL2EncoderBase::glGetShaderPrecisionFormat_s(void *self, GLenum shadertype, GLenum precisiontype, GLint *range,
    GLint *precision)
{
    GET_CONTEXT;
    ctx->glGetShaderPrecisionFormatFunc(ctx->GetGLESv2Encoder(self), shadertype, precisiontype, range, precision);
}

void GL2EncoderBase::glGetShaderSource_s(void *self, GLuint shader, GLsizei bufsize, GLsizei *length, GLchar *source)
{
    GET_CONTEXT;
    ctx->glGetShaderSourceFunc(ctx->GetGLESv2Encoder(self), shader, bufsize, length, source);
}

const GLubyte * GL2EncoderBase::glGetString_s(void *self, GLenum name)
{
    GET_CONTEXT;
    return ctx->glGetStringFunc(ctx->GetGLESv2Encoder(self), name);
}

void GL2EncoderBase::glGetTexParameterfv_s(void *self, GLenum target, GLenum pname, GLfloat *params)
{
    GET_CONTEXT;
    ctx->glGetTexParameterfvFunc(ctx->GetGLESv2Encoder(self), target, pname, params);
}

void GL2EncoderBase::glGetTexParameteriv_s(void *self, GLenum target, GLenum pname, GLint *params)
{
    GET_CONTEXT;
    ctx->glGetTexParameterivFunc(ctx->GetGLESv2Encoder(self), target, pname, params);
}

void GL2EncoderBase::glGetUniformfv_s(void *self, GLuint program, GLint location, GLfloat *params)
{
    GET_CONTEXT;
    ctx->glGetUniformfvFunc(ctx->GetGLESv2Encoder(self), program, location, params);
}

void GL2EncoderBase::glGetUniformiv_s(void *self, GLuint program, GLint location, GLint *params)
{
    GET_CONTEXT;
    ctx->glGetUniformivFunc(ctx->GetGLESv2Encoder(self), program, location, params);
}

GLint GL2EncoderBase::glGetUniformLocation_s(void *self, GLuint program, const GLchar *name)
{
    GET_CONTEXT;
    return ctx->glGetUniformLocationFunc(ctx->GetGLESv2Encoder(self), program, name);
}

void GL2EncoderBase::glGetVertexAttribfv_s(void *self, GLuint index, GLenum pname, GLfloat *params)
{
    GET_CONTEXT;
    ctx->glGetVertexAttribfvFunc(ctx->GetGLESv2Encoder(self), index, pname, params);
}

void GL2EncoderBase::glGetVertexAttribiv_s(void *self, GLuint index, GLenum pname, GLint *params)
{
    GET_CONTEXT;
    ctx->glGetVertexAttribivFunc(ctx->GetGLESv2Encoder(self), index, pname, params);
}

void GL2EncoderBase::glGetVertexAttribPointerv_s(void *self, GLuint index, GLenum pname, void **pointer)
{
    GET_CONTEXT;
    ctx->glGetVertexAttribPointervFunc(ctx->GetGLESv2Encoder(self), index, pname, pointer);
}

void GL2EncoderBase::glHint_s(void *self, GLenum target, GLenum mode)
{
    GET_CONTEXT;
    ctx->glHintFunc(ctx->GetGLESv2Encoder(self), target, mode);
}

GLboolean GL2EncoderBase::glIsBuffer_s(void *self, GLuint buffer)
{
    GET_CONTEXT;
    return ctx->glIsBufferFunc(ctx->GetGLESv2Encoder(self), buffer);
}

GLboolean GL2EncoderBase::glIsEnabled_s(void *self, GLenum cap)
{
    GET_CONTEXT;
    return ctx->glIsEnabledFunc(ctx->GetGLESv2Encoder(self), cap);
}

GLboolean GL2EncoderBase::glIsFramebuffer_s(void *self, GLuint framebuffer)
{
    GET_CONTEXT;
    return ctx->glIsFramebufferFunc(ctx->GetGLESv2Encoder(self), framebuffer);
}

GLboolean GL2EncoderBase::glIsProgram_s(void *self, GLuint program)
{
    GET_CONTEXT;
    return ctx->glIsProgramFunc(ctx->GetGLESv2Encoder(self), program);
}

GLboolean GL2EncoderBase::glIsRenderbuffer_s(void *self, GLuint renderbuffer)
{
    GET_CONTEXT;
    return ctx->glIsRenderbufferFunc(ctx->GetGLESv2Encoder(self), renderbuffer);
}

GLboolean GL2EncoderBase::glIsShader_s(void *self, GLuint shader)
{
    GET_CONTEXT;
    return ctx->glIsShaderFunc(ctx->GetGLESv2Encoder(self), shader);
}

GLboolean GL2EncoderBase::glIsTexture_s(void *self, GLuint texture)
{
    GET_CONTEXT;
    return ctx->glIsTextureFunc(ctx->GetGLESv2Encoder(self), texture);
}

void GL2EncoderBase::glLineWidth_s(void *self, GLfloat width)
{
    GET_CONTEXT;
    ctx->glLineWidthFunc(ctx->GetGLESv2Encoder(self), width);
}

void GL2EncoderBase::glLinkProgram_s(void *self, GLuint program)
{
    GET_CONTEXT;
    ctx->glLinkProgramFunc(ctx->GetGLESv2Encoder(self), program);
}

void GL2EncoderBase::glPixelStorei_s(void *self, GLenum pname, GLint param)
{
    GET_CONTEXT;
    ctx->glPixelStoreiFunc(ctx->GetGLESv2Encoder(self), pname, param);
}

void GL2EncoderBase::glPolygonOffset_s(void *self, GLfloat factor, GLfloat units)
{
    GET_CONTEXT;
    ctx->glPolygonOffsetFunc(ctx->GetGLESv2Encoder(self), factor, units);
}

void GL2EncoderBase::glReadPixels_s(void *self, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format,
    GLenum type, void *pixels)
{
    GET_CONTEXT;
    ctx->glReadPixelsFunc(ctx->GetGLESv2Encoder(self), x, y, width, height, format, type, pixels);
}

void GL2EncoderBase::glReleaseShaderCompiler_s(void *self)
{
    GET_CONTEXT;
    ctx->glReleaseShaderCompilerFunc(ctx->GetGLESv2Encoder(self));
}

void GL2EncoderBase::glRenderbufferStorage_s(void *self, GLenum target, GLenum internalformat, GLsizei width,
    GLsizei height)
{
    GET_CONTEXT;
    ctx->glRenderbufferStorageFunc(ctx->GetGLESv2Encoder(self), target, internalformat, width, height);
}

void GL2EncoderBase::glSampleCoverage_s(void *self, GLfloat value, GLboolean invert)
{
    GET_CONTEXT;
    ctx->glSampleCoverageFunc(ctx->GetGLESv2Encoder(self), value, invert);
}

void GL2EncoderBase::glScissor_s(void *self, GLint x, GLint y, GLsizei width, GLsizei height)
{
    GET_CONTEXT;
    ctx->glScissorFunc(ctx->GetGLESv2Encoder(self), x, y, width, height);
}

void GL2EncoderBase::glShaderBinary_s(void *self, GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length)
{
    GET_CONTEXT;
    ctx->glShaderBinaryFunc(ctx->GetGLESv2Encoder(self), count, shaders, binaryformat, binary, length);
}

void GL2EncoderBase::glShaderSource_s(void *self, GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length)
{
    GET_CONTEXT;
    ctx->glShaderSourceFunc(ctx->GetGLESv2Encoder(self), shader, count, string, length);
}

void GL2EncoderBase::glStencilFunc_s(void *self, GLenum func, GLint ref, GLuint mask)
{
    GET_CONTEXT;
    ctx->glStencilFuncFunc(ctx->GetGLESv2Encoder(self), func, ref, mask);
}

void GL2EncoderBase::glStencilFuncSeparate_s(void *self, GLenum face, GLenum func, GLint ref, GLuint mask)
{
    GET_CONTEXT;
    ctx->glStencilFuncSeparateFunc(ctx->GetGLESv2Encoder(self), face, func, ref, mask);
}

void GL2EncoderBase::glStencilMask_s(void *self, GLuint mask)
{
    GET_CONTEXT;
    ctx->glStencilMaskFunc(ctx->GetGLESv2Encoder(self), mask);
}

void GL2EncoderBase::glStencilMaskSeparate_s(void *self, GLenum face, GLuint mask)
{
    GET_CONTEXT;
    ctx->glStencilMaskSeparateFunc(ctx->GetGLESv2Encoder(self), face, mask);
}

void GL2EncoderBase::glStencilOp_s(void *self, GLenum fail, GLenum zfail, GLenum zpass)
{
    GET_CONTEXT;
    ctx->glStencilOpFunc(ctx->GetGLESv2Encoder(self), fail, zfail, zpass);
}

void GL2EncoderBase::glStencilOpSeparate_s(void *self, GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)
{
    GET_CONTEXT;
    ctx->glStencilOpSeparateFunc(ctx->GetGLESv2Encoder(self), face, sfail, dpfail, dppass);
}

void GL2EncoderBase::glTexImage2D_s(void *self, GLenum target, GLint level, GLint internalformat, GLsizei width,
    GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels)
{
    GET_CONTEXT;
    ctx->glTexImage2DFunc(ctx->GetGLESv2Encoder(self), target, level, internalformat, width, height, border, format,
        type, pixels);
}

void GL2EncoderBase::glTexParameterf_s(void *self, GLenum target, GLenum pname, GLfloat param)
{
    GET_CONTEXT;
    ctx->glTexParameterfFunc(ctx->GetGLESv2Encoder(self), target, pname, param);
}

void GL2EncoderBase::glTexParameterfv_s(void *self, GLenum target, GLenum pname, const GLfloat *params)
{
    GET_CONTEXT;
    ctx->glTexParameterfvFunc(ctx->GetGLESv2Encoder(self), target, pname, params);
}

void GL2EncoderBase::glTexParameteri_s(void *self, GLenum target, GLenum pname, GLint param)
{
    GET_CONTEXT;
    ctx->glTexParameteriFunc(ctx->GetGLESv2Encoder(self), target, pname, param);
}

void GL2EncoderBase::glTexParameteriv_s(void *self, GLenum target, GLenum pname, const GLint *params)
{
    GET_CONTEXT;
    ctx->glTexParameterivFunc(ctx->GetGLESv2Encoder(self), target, pname, params);
}

void GL2EncoderBase::glTexSubImage2D_s(void *self, GLenum target, GLint level, GLint xoffset, GLint yoffset,
    GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels)
{
    GET_CONTEXT;
    ctx->glTexSubImage2DFunc(ctx->GetGLESv2Encoder(self), target, level, xoffset, yoffset, width, height, format, type,
        pixels);
}

void GL2EncoderBase::glUniform1f_s(void *self, GLint location, GLfloat v0)
{
    GET_CONTEXT;
    ctx->glUniform1fFunc(ctx->GetGLESv2Encoder(self), location, v0);
}

void GL2EncoderBase::glUniform1fv_s(void *self, GLint location, GLsizei count, const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glUniform1fvFunc(ctx->GetGLESv2Encoder(self), location, count, value);
}

void GL2EncoderBase::glUniform1i_s(void *self, GLint location, GLint v0)
{
    GET_CONTEXT;
    ctx->glUniform1iFunc(ctx->GetGLESv2Encoder(self), location, v0);
}

void GL2EncoderBase::glUniform1iv_s(void *self, GLint location, GLsizei count, const GLint *value)
{
    GET_CONTEXT;
    ctx->glUniform1ivFunc(ctx->GetGLESv2Encoder(self), location, count, value);
}

void GL2EncoderBase::glUniform2f_s(void *self, GLint location, GLfloat v0, GLfloat v1)
{
    GET_CONTEXT;
    ctx->glUniform2fFunc(ctx->GetGLESv2Encoder(self), location, v0, v1);
}

void GL2EncoderBase::glUniform2fv_s(void *self, GLint location, GLsizei count, const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glUniform2fvFunc(ctx->GetGLESv2Encoder(self), location, count, value);
}

void GL2EncoderBase::glUniform2i_s(void *self, GLint location, GLint v0, GLint v1)
{
    GET_CONTEXT;
    ctx->glUniform2iFunc(ctx->GetGLESv2Encoder(self), location, v0, v1);
}

void GL2EncoderBase::glUniform2iv_s(void *self, GLint location, GLsizei count, const GLint *value)
{
    GET_CONTEXT;
    ctx->glUniform2ivFunc(ctx->GetGLESv2Encoder(self), location, count, value);
}

void GL2EncoderBase::glUniform3f_s(void *self, GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
    GET_CONTEXT;
    ctx->glUniform3fFunc(ctx->GetGLESv2Encoder(self), location, v0, v1, v2);
}

void GL2EncoderBase::glUniform3fv_s(void *self, GLint location, GLsizei count, const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glUniform3fvFunc(ctx->GetGLESv2Encoder(self), location, count, value);
}

void GL2EncoderBase::glUniform3i_s(void *self, GLint location, GLint v0, GLint v1, GLint v2)
{
    GET_CONTEXT;
    ctx->glUniform3iFunc(ctx->GetGLESv2Encoder(self), location, v0, v1, v2);
}

void GL2EncoderBase::glUniform3iv_s(void *self, GLint location, GLsizei count, const GLint *value)
{
    GET_CONTEXT;
    ctx->glUniform3ivFunc(ctx->GetGLESv2Encoder(self), location, count, value);
}

void GL2EncoderBase::glUniform4f_s(void *self, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    GET_CONTEXT;
    ctx->glUniform4fFunc(ctx->GetGLESv2Encoder(self), location, v0, v1, v2, v3);
}

void GL2EncoderBase::glUniform4fv_s(void *self, GLint location, GLsizei count, const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glUniform4fvFunc(ctx->GetGLESv2Encoder(self), location, count, value);
}

void GL2EncoderBase::glUniform4i_s(void *self, GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
    GET_CONTEXT;
    ctx->glUniform4iFunc(ctx->GetGLESv2Encoder(self), location, v0, v1, v2, v3);
}

void GL2EncoderBase::glUniform4iv_s(void *self, GLint location, GLsizei count, const GLint *value)
{
    GET_CONTEXT;
    ctx->glUniform4ivFunc(ctx->GetGLESv2Encoder(self), location, count, value);
}

void GL2EncoderBase::glUniformMatrix2fv_s(void *self, GLint location, GLsizei count, GLboolean transpose,
    const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glUniformMatrix2fvFunc(ctx->GetGLESv2Encoder(self), location, count, transpose, value);
}

void GL2EncoderBase::glUniformMatrix3fv_s(void *self, GLint location, GLsizei count, GLboolean transpose,
    const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glUniformMatrix3fvFunc(ctx->GetGLESv2Encoder(self), location, count, transpose, value);
}

void GL2EncoderBase::glUniformMatrix4fv_s(void *self, GLint location, GLsizei count, GLboolean transpose,
    const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glUniformMatrix4fvFunc(ctx->GetGLESv2Encoder(self), location, count, transpose, value);
}

void GL2EncoderBase::glUseProgram_s(void *self, GLuint program)
{
    GET_CONTEXT;
    ctx->glUseProgramFunc(ctx->GetGLESv2Encoder(self), program);
}

void GL2EncoderBase::glValidateProgram_s(void *self, GLuint program)
{
    GET_CONTEXT;
    ctx->glValidateProgramFunc(ctx->GetGLESv2Encoder(self), program);
}

void GL2EncoderBase::glVertexAttrib1f_s(void *self, GLuint index, GLfloat x)
{
    GET_CONTEXT;
    ctx->glVertexAttrib1fFunc(ctx->GetGLESv2Encoder(self), index, x);
}

void GL2EncoderBase::glVertexAttrib1fv_s(void *self, GLuint index, const GLfloat *v)
{
    GET_CONTEXT;
    ctx->glVertexAttrib1fvFunc(ctx->GetGLESv2Encoder(self), index, v);
}

void GL2EncoderBase::glVertexAttrib2f_s(void *self, GLuint index, GLfloat x, GLfloat y)
{
    GET_CONTEXT;
    ctx->glVertexAttrib2fFunc(ctx->GetGLESv2Encoder(self), index, x, y);
}

void GL2EncoderBase::glVertexAttrib2fv_s(void *self, GLuint index, const GLfloat *v)
{
    GET_CONTEXT;
    ctx->glVertexAttrib2fvFunc(ctx->GetGLESv2Encoder(self), index, v);
}

void GL2EncoderBase::glVertexAttrib3f_s(void *self, GLuint index, GLfloat x, GLfloat y, GLfloat z)
{
    GET_CONTEXT;
    ctx->glVertexAttrib3fFunc(ctx->GetGLESv2Encoder(self), index, x, y, z);
}

void GL2EncoderBase::glVertexAttrib3fv_s(void *self, GLuint index, const GLfloat *v)
{
    GET_CONTEXT;
    ctx->glVertexAttrib3fvFunc(ctx->GetGLESv2Encoder(self), index, v);
}

void GL2EncoderBase::glVertexAttrib4f_s(void *self, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    GET_CONTEXT;
    ctx->glVertexAttrib4fFunc(ctx->GetGLESv2Encoder(self), index, x, y, z, w);
}

void GL2EncoderBase::glVertexAttrib4fv_s(void *self, GLuint index, const GLfloat *v)
{
    GET_CONTEXT;
    ctx->glVertexAttrib4fvFunc(ctx->GetGLESv2Encoder(self), index, v);
}

void GL2EncoderBase::glVertexAttribPointer_s(void *self, GLuint index, GLint size, GLenum type, GLboolean normalized,
    GLsizei stride, const void *pointer)
{
    GET_CONTEXT;
    ctx->glVertexAttribPointerFunc(ctx->GetGLESv2Encoder(self), index, size, type, normalized, stride, pointer);
}

void GL2EncoderBase::glViewport_s(void *self, GLint x, GLint y, GLsizei width, GLsizei height)
{
    GET_CONTEXT;
    ctx->glViewportFunc(ctx->GetGLESv2Encoder(self), x, y, width, height);
}

void GL2EncoderBase::glEGLImageTargetTexture2DOES_s(void *self, GLenum target, GLeglImageOES image)
{
    GET_CONTEXT;
    ctx->glEGLImageTargetTexture2DOESFunc(ctx->GetGLESv2Encoder(self), target, image);
}

void GL2EncoderBase::glEGLImageTargetRenderbufferStorageOES_s(void *self, GLenum target, GLeglImageOES image)
{
    GET_CONTEXT;
    ctx->glEGLImageTargetRenderbufferStorageOESFunc(ctx->GetGLESv2Encoder(self), target, image);
}

void GL2EncoderBase::glGetProgramBinaryOES_s(void *self, GLuint program, GLsizei bufSize, GLsizei *length,
    GLenum *binaryFormat, void *binary)
{
    GET_CONTEXT;
    ctx->glGetProgramBinaryOESFunc(ctx->GetGLESv2Encoder(self), program, bufSize, length, binaryFormat, binary);
}

void GL2EncoderBase::glProgramBinaryOES_s(void *self, GLuint program, GLenum binaryFormat, const void *binary,
    GLint length)
{
    GET_CONTEXT;
    ctx->glProgramBinaryOESFunc(ctx->GetGLESv2Encoder(self), program, binaryFormat, binary, length);
}

void *GL2EncoderBase::glMapBufferOES_s(void *self, GLenum target, GLenum access)
{
    GET_CONTEXT;
    return ctx->glMapBufferOESFunc(ctx->GetGLESv2Encoder(self), target, access);
}

GLboolean GL2EncoderBase::glUnmapBufferOES_s(void *self, GLenum target)
{
    GET_CONTEXT;
    return ctx->glUnmapBufferOESFunc(ctx->GetGLESv2Encoder(self), target);
}

void GL2EncoderBase::glTexImage3DOES_s(void *self, GLenum target, GLint level, GLenum internalformat, GLsizei width,
    GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels)
{
    GET_CONTEXT;
    ctx->glTexImage3DOESFunc(ctx->GetGLESv2Encoder(self), target, level, internalformat, width, height, depth, border,
        format, type, pixels);
}

void GL2EncoderBase::glTexSubImage3DOES_s(void *self, GLenum target, GLint level, GLint xoffset, GLint yoffset,
    GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels)
{
    GET_CONTEXT;
    ctx->glTexSubImage3DOESFunc(ctx->GetGLESv2Encoder(self), target, level, xoffset, yoffset, zoffset, width, height,
        depth, format, type, pixels);
}

void GL2EncoderBase::glCopyTexSubImage3DOES_s(void *self, GLenum target, GLint level, GLint xoffset, GLint yoffset,
    GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
    GET_CONTEXT;
    ctx->glCopyTexSubImage3DOESFunc(ctx->GetGLESv2Encoder(self), target, level, xoffset, yoffset, zoffset, x, y, width,
        height);
}

void GL2EncoderBase::glCompressedTexImage3DOES_s(void *self, GLenum target, GLint level, GLenum internalformat,
    GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data)
{
    GET_CONTEXT;
    ctx->glCompressedTexImage3DOESFunc(ctx->GetGLESv2Encoder(self), target, level, internalformat, width, height, depth,
        border, imageSize, data);
}

void GL2EncoderBase::glCompressedTexSubImage3DOES_s(void *self, GLenum target, GLint level, GLint xoffset,
    GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize,
    const void *data)
{
    GET_CONTEXT;
    ctx->glCompressedTexSubImage3DOESFunc(ctx->GetGLESv2Encoder(self), target, level, xoffset, yoffset, zoffset, width,
        height, depth, format, imageSize, data);
}

void GL2EncoderBase::glFramebufferTexture3DOES_s(void *self, GLenum target, GLenum attachment, GLenum textarget,
    GLuint texture, GLint level, GLint zoffset)
{
    GET_CONTEXT;
    ctx->glFramebufferTexture3DOESFunc(ctx->GetGLESv2Encoder(self), target, attachment, textarget, texture, level,
        zoffset);
}

void GL2EncoderBase::glBindVertexArrayOES_s(void *self, GLuint array)
{
    GET_CONTEXT;
    ctx->glBindVertexArrayOESFunc(ctx->GetGLESv2Encoder(self), array);
}

void GL2EncoderBase::glDeleteVertexArraysOES_s(void *self, GLsizei n, const GLuint *arrays)
{
    GET_CONTEXT;
    ctx->glDeleteVertexArraysOESFunc(ctx->GetGLESv2Encoder(self), n, arrays);
}

void GL2EncoderBase::glGenVertexArraysOES_s(void *self, GLsizei n, GLuint *arrays)
{
    GET_CONTEXT;
    ctx->glGenVertexArraysOESFunc(ctx->GetGLESv2Encoder(self), n, arrays);
}

GLboolean GL2EncoderBase::glIsVertexArrayOES_s(void *self, GLuint array)
{
    GET_CONTEXT;
    return ctx->glIsVertexArrayOESFunc(ctx->GetGLESv2Encoder(self), array);
}

void GL2EncoderBase::glDiscardFramebufferEXT_s(void *self, GLenum target, GLsizei numAttachments,
    const GLenum *attachments)
{
    GET_CONTEXT;
    ctx->glDiscardFramebufferEXTFunc(ctx->GetGLESv2Encoder(self), target, numAttachments, attachments);
}

void GL2EncoderBase::glMultiDrawArraysEXT_s(void *self, GLenum mode, const GLint *first, const GLsizei *count,
    GLsizei primcount)
{
    GET_CONTEXT;
    ctx->glMultiDrawArraysEXTFunc(ctx->GetGLESv2Encoder(self), mode, first, count, primcount);
}

void GL2EncoderBase::glMultiDrawElementsEXT_s(void *self, GLenum mode, const GLsizei *count, GLenum type,
    const void * const * indices, GLsizei primcount)
{
    GET_CONTEXT;
    ctx->glMultiDrawElementsEXTFunc(ctx->GetGLESv2Encoder(self), mode, count, type, indices, primcount);
}

void GL2EncoderBase::glGetPerfMonitorGroupsAMD_s(void *self, GLint *numGroups, GLsizei groupsSize, GLuint *groups)
{
    GET_CONTEXT;
    ctx->glGetPerfMonitorGroupsAMDFunc(ctx->GetGLESv2Encoder(self), numGroups, groupsSize, groups);
}

void GL2EncoderBase::glGetPerfMonitorCountersAMD_s(void *self, GLuint group, GLint *numCounters,
    GLint *maxActiveCounters, GLsizei counterSize, GLuint *counters)
{
    GET_CONTEXT;
    ctx->glGetPerfMonitorCountersAMDFunc(ctx->GetGLESv2Encoder(self), group, numCounters, maxActiveCounters,
        counterSize, counters);
}

void GL2EncoderBase::glGetPerfMonitorGroupStringAMD_s(void *self, GLuint group, GLsizei bufSize, GLsizei *length,
    GLchar *groupString)
{
    GET_CONTEXT;
    ctx->glGetPerfMonitorGroupStringAMDFunc(ctx->GetGLESv2Encoder(self), group, bufSize, length, groupString);
}

void GL2EncoderBase::glGetPerfMonitorCounterStringAMD_s(void *self, GLuint group, GLuint counter, GLsizei bufSize,
    GLsizei *length, GLchar *counterString)
{
    GET_CONTEXT;
    ctx->glGetPerfMonitorCounterStringAMDFunc(ctx->GetGLESv2Encoder(self), group, counter, bufSize, length,
        counterString);
}

void GL2EncoderBase::glGetPerfMonitorCounterInfoAMD_s(void *self, GLuint group, GLuint counter, GLenum pname,
    void *data)
{
    GET_CONTEXT;
    ctx->glGetPerfMonitorCounterInfoAMDFunc(ctx->GetGLESv2Encoder(self), group, counter, pname, data);
}

void GL2EncoderBase::glGenPerfMonitorsAMD_s(void *self, GLsizei n, GLuint *monitors)
{
    GET_CONTEXT;
    ctx->glGenPerfMonitorsAMDFunc(ctx->GetGLESv2Encoder(self), n, monitors);
}

void GL2EncoderBase::glDeletePerfMonitorsAMD_s(void *self, GLsizei n, GLuint *monitors)
{
    GET_CONTEXT;
    ctx->glDeletePerfMonitorsAMDFunc(ctx->GetGLESv2Encoder(self), n, monitors);
}

void GL2EncoderBase::glSelectPerfMonitorCountersAMD_s(void *self, GLuint monitor, GLboolean enable, GLuint group,
    GLint numCounters, GLuint *counterList)
{
    GET_CONTEXT;
    ctx->glSelectPerfMonitorCountersAMDFunc(ctx->GetGLESv2Encoder(self), monitor, enable, group, numCounters,
        counterList);
}

void GL2EncoderBase::glBeginPerfMonitorAMD_s(void *self, GLuint monitor)
{
    GET_CONTEXT;
    ctx->glBeginPerfMonitorAMDFunc(ctx->GetGLESv2Encoder(self), monitor);
}

void GL2EncoderBase::glEndPerfMonitorAMD_s(void *self, GLuint monitor)
{
    GET_CONTEXT;
    ctx->glEndPerfMonitorAMDFunc(ctx->GetGLESv2Encoder(self), monitor);
}

void GL2EncoderBase::glGetPerfMonitorCounterDataAMD_s(void *self, GLuint monitor, GLenum pname, GLsizei dataSize,
    GLuint *data, GLint *bytesWritten)
{
    GET_CONTEXT;
    ctx->glGetPerfMonitorCounterDataAMDFunc(ctx->GetGLESv2Encoder(self), monitor, pname, dataSize, data, bytesWritten);
}

void GL2EncoderBase::glRenderbufferStorageMultisampleIMG_s(void *self, GLenum target, GLsizei samples,
    GLenum internalformat, GLsizei width, GLsizei height)
{
    GET_CONTEXT;
    ctx->glRenderbufferStorageMultisampleIMGFunc(ctx->GetGLESv2Encoder(self), target, samples, internalformat, width,
        height);
}

void GL2EncoderBase::glFramebufferTexture2DMultisampleIMG_s(void *self, GLenum target, GLenum attachment,
    GLenum textarget, GLuint texture, GLint level, GLsizei samples)
{
    GET_CONTEXT;
    ctx->glFramebufferTexture2DMultisampleIMGFunc(ctx->GetGLESv2Encoder(self), target, attachment, textarget, texture,
        level, samples);
}

void GL2EncoderBase::glDeleteFencesNV_s(void *self, GLsizei n, const GLuint *fences)
{
    GET_CONTEXT;
    ctx->glDeleteFencesNVFunc(ctx->GetGLESv2Encoder(self), n, fences);
}

void GL2EncoderBase::glGenFencesNV_s(void *self, GLsizei n, GLuint *fences)
{
    GET_CONTEXT;
    ctx->glGenFencesNVFunc(ctx->GetGLESv2Encoder(self), n, fences);
}

GLboolean GL2EncoderBase::glIsFenceNV_s(void *self, GLuint fence)
{
    GET_CONTEXT;
    return ctx->glIsFenceNVFunc(ctx->GetGLESv2Encoder(self), fence);
}

GLboolean GL2EncoderBase::glTestFenceNV_s(void *self, GLuint fence)
{
    GET_CONTEXT;
    return ctx->glTestFenceNVFunc(ctx->GetGLESv2Encoder(self), fence);
}

void GL2EncoderBase::glGetFenceivNV_s(void *self, GLuint fence, GLenum pname, GLint *params)
{
    GET_CONTEXT;
    ctx->glGetFenceivNVFunc(ctx->GetGLESv2Encoder(self), fence, pname, params);
}

void GL2EncoderBase::glFinishFenceNV_s(void *self, GLuint fence)
{
    GET_CONTEXT;
    ctx->glFinishFenceNVFunc(ctx->GetGLESv2Encoder(self), fence);
}

void GL2EncoderBase::glSetFenceNV_s(void *self, GLuint fence, GLenum condition)
{
    GET_CONTEXT;
    ctx->glSetFenceNVFunc(ctx->GetGLESv2Encoder(self), fence, condition);
}

void GL2EncoderBase::glCoverageMaskNV_s(void *self, GLboolean mask)
{
    GET_CONTEXT;
    ctx->glCoverageMaskNVFunc(ctx->GetGLESv2Encoder(self), mask);
}


void GL2EncoderBase::glCoverageOperationNV_s(void *self, GLenum operation)
{
    GET_CONTEXT;
    ctx->glCoverageOperationNVFunc(ctx->GetGLESv2Encoder(self), operation);
}

void GL2EncoderBase::glGetDriverControlsQCOM_s(void *self, GLint *num, GLsizei size, GLuint *driverControls)
{
    GET_CONTEXT;
    ctx->glGetDriverControlsQCOMFunc(ctx->GetGLESv2Encoder(self), num, size, driverControls);
}

void GL2EncoderBase::glGetDriverControlStringQCOM_s(void *self, GLuint driverControl, GLsizei bufSize, GLsizei *length,
    GLchar *driverControlString)
{
    GET_CONTEXT;
    ctx->glGetDriverControlStringQCOMFunc(ctx->GetGLESv2Encoder(self), driverControl, bufSize, length,
        driverControlString);
}

void GL2EncoderBase::glEnableDriverControlQCOM_s(void *self, GLuint driverControl)
{
    GET_CONTEXT;
    ctx->glEnableDriverControlQCOMFunc(ctx->GetGLESv2Encoder(self), driverControl);
}

void GL2EncoderBase::glDisableDriverControlQCOM_s(void *self, GLuint driverControl)
{
    GET_CONTEXT;
    ctx->glDisableDriverControlQCOMFunc(ctx->GetGLESv2Encoder(self), driverControl);
}

void GL2EncoderBase::glExtGetTexturesQCOM_s(void *self, GLuint *textures, GLint maxTextures, GLint *numTextures)
{
    GET_CONTEXT;
    ctx->glExtGetTexturesQCOMFunc(ctx->GetGLESv2Encoder(self), textures, maxTextures, numTextures);
}

void GL2EncoderBase::glExtGetBuffersQCOM_s(void *self, GLuint *buffers, GLint maxBuffers, GLint *numBuffers)
{
    GET_CONTEXT;
    ctx->glExtGetBuffersQCOMFunc(ctx->GetGLESv2Encoder(self), buffers, maxBuffers, numBuffers);
}

void GL2EncoderBase::glExtGetRenderbuffersQCOM_s(void *self, GLuint *renderbuffers, GLint maxRenderbuffers,
    GLint *numRenderbuffers)
{
    GET_CONTEXT;
    ctx->glExtGetRenderbuffersQCOMFunc(ctx->GetGLESv2Encoder(self), renderbuffers, maxRenderbuffers, numRenderbuffers);
}

void GL2EncoderBase::glExtGetFramebuffersQCOM_s(void *self, GLuint *framebuffers, GLint maxFramebuffers,
    GLint *numFramebuffers)
{
    GET_CONTEXT;
    ctx->glExtGetFramebuffersQCOMFunc(ctx->GetGLESv2Encoder(self), framebuffers, maxFramebuffers, numFramebuffers);
}

void GL2EncoderBase::glExtGetTexLevelParameterivQCOM_s(void *self, GLuint texture, GLenum face, GLint level,
    GLenum pname, GLint *params)
{
    GET_CONTEXT;
    ctx->glExtGetTexLevelParameterivQCOMFunc(ctx->GetGLESv2Encoder(self), texture, face, level, pname, params);
}

void GL2EncoderBase::glExtTexObjectStateOverrideiQCOM_s(void *self, GLenum target, GLenum pname, GLint param)
{
    GET_CONTEXT;
    ctx->glExtTexObjectStateOverrideiQCOMFunc(ctx->GetGLESv2Encoder(self), target, pname, param);
}

void GL2EncoderBase::glExtGetTexSubImageQCOM_s(void *self, GLenum target, GLint level, GLint xoffset, GLint yoffset,
    GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, void *texels)
{
    GET_CONTEXT;
    ctx->glExtGetTexSubImageQCOMFunc(ctx->GetGLESv2Encoder(self), target, level, xoffset, yoffset, zoffset, width,
        height, depth, format, type, texels);
}

void GL2EncoderBase::glExtGetBufferPointervQCOM_s(void *self, GLenum target, void **params)
{
    GET_CONTEXT;
    ctx->glExtGetBufferPointervQCOMFunc(ctx->GetGLESv2Encoder(self), target, params);
}

void GL2EncoderBase::glExtGetShadersQCOM_s(void *self, GLuint *shaders, GLint maxShaders, GLint *numShaders)
{
    GET_CONTEXT;
    ctx->glExtGetShadersQCOMFunc(ctx->GetGLESv2Encoder(self), shaders, maxShaders, numShaders);
}

void GL2EncoderBase::glExtGetProgramsQCOM_s(void *self, GLuint *programs, GLint maxPrograms, GLint *numPrograms)
{
    GET_CONTEXT;
    ctx->glExtGetProgramsQCOMFunc(ctx->GetGLESv2Encoder(self), programs, maxPrograms, numPrograms);
}

GLboolean GL2EncoderBase::glExtIsProgramBinaryQCOM_s(void *self, GLuint program)
{
    GET_CONTEXT;
    return ctx->glExtIsProgramBinaryQCOMFunc(ctx->GetGLESv2Encoder(self), program);
}

void GL2EncoderBase::glExtGetProgramBinarySourceQCOM_s(void *self, GLuint program, GLenum shadertype, GLchar *source,
    GLint *length)
{
    GET_CONTEXT;
    ctx->glExtGetProgramBinarySourceQCOMFunc(ctx->GetGLESv2Encoder(self), program, shadertype, source, length);
}

void GL2EncoderBase::glStartTilingQCOM_s(void *self, GLuint x, GLuint y, GLuint width, GLuint height,
    GLbitfield preserveMask)
{
    GET_CONTEXT;
    ctx->glStartTilingQCOMFunc(ctx->GetGLESv2Encoder(self), x, y, width, height, preserveMask);
}

void GL2EncoderBase::glEndTilingQCOM_s(void *self, GLbitfield preserveMask)
{
    GET_CONTEXT;
    ctx->glEndTilingQCOMFunc(ctx->GetGLESv2Encoder(self), preserveMask);
}

void GL2EncoderBase::glGenVertexArrays_s(void *self, GLsizei n, GLuint *arrays)
{
    GET_CONTEXT;
    ctx->glGenVertexArraysFunc(ctx->GetGLESv2Encoder(self), n, arrays);
}

void GL2EncoderBase::glBindVertexArray_s(void *self, GLuint array)
{
    GET_CONTEXT;
    ctx->glBindVertexArrayFunc(ctx->GetGLESv2Encoder(self), array);
}

void GL2EncoderBase::glDeleteVertexArrays_s(void *self, GLsizei n, const GLuint *arrays)
{
    GET_CONTEXT;
    ctx->glDeleteVertexArraysFunc(ctx->GetGLESv2Encoder(self), n, arrays);
}

GLboolean GL2EncoderBase::glIsVertexArray_s(void *self, GLuint array)
{
    GET_CONTEXT;
    return ctx->glIsVertexArrayFunc(ctx->GetGLESv2Encoder(self), array);
}

void *GL2EncoderBase::glMapBufferRange_s(void *self, GLenum target, GLintptr offset, GLsizeiptr length,
    GLbitfield access)
{
    GET_CONTEXT;
    return ctx->glMapBufferRangeFunc(ctx->GetGLESv2Encoder(self), target, offset, length, access);
}

GLboolean GL2EncoderBase::glUnmapBuffer_s(void *self, GLenum target)
{
    GET_CONTEXT;
    return ctx->glUnmapBufferFunc(ctx->GetGLESv2Encoder(self), target);
}

void GL2EncoderBase::glFlushMappedBufferRange_s(void *self, GLenum target, GLintptr offset, GLsizeiptr length)
{
    GET_CONTEXT;
    ctx->glFlushMappedBufferRangeFunc(ctx->GetGLESv2Encoder(self), target, offset, length);
}

void GL2EncoderBase::glBindBufferRange_s(void *self, GLenum target, GLuint index, GLuint buffer, GLintptr offset,
    GLsizeiptr size)
{
    GET_CONTEXT;
    ctx->glBindBufferRangeFunc(ctx->GetGLESv2Encoder(self), target, index, buffer, offset, size);
}

void GL2EncoderBase::glBindBufferBase_s(void *self, GLenum target, GLuint index, GLuint buffer)
{
    GET_CONTEXT;
    ctx->glBindBufferBaseFunc(ctx->GetGLESv2Encoder(self), target, index, buffer);
}

void GL2EncoderBase::glCopyBufferSubData_s(void *self, GLenum readTarget, GLenum writeTarget, GLintptr readOffset,
    GLintptr writeOffset, GLsizeiptr size)
{
    GET_CONTEXT;
    ctx->glCopyBufferSubDataFunc(ctx->GetGLESv2Encoder(self), readTarget, writeTarget, readOffset, writeOffset, size);
}

void GL2EncoderBase::glClearBufferiv_s(void *self, GLenum buffer, GLint drawbuffer, const GLint *value)
{
    GET_CONTEXT;
    ctx->glClearBufferivFunc(ctx->GetGLESv2Encoder(self), buffer, drawbuffer, value);
}

void GL2EncoderBase::glClearBufferuiv_s(void *self, GLenum buffer, GLint drawbuffer, const GLuint *value)
{
    GET_CONTEXT;
    ctx->glClearBufferuivFunc(ctx->GetGLESv2Encoder(self), buffer, drawbuffer, value);
}

void GL2EncoderBase::glClearBufferfv_s(void *self, GLenum buffer, GLint drawbuffer, const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glClearBufferfvFunc(ctx->GetGLESv2Encoder(self), buffer, drawbuffer, value);
}

void GL2EncoderBase::glClearBufferfi_s(void *self, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
{
    GET_CONTEXT;
    ctx->glClearBufferfiFunc(ctx->GetGLESv2Encoder(self), buffer, drawbuffer, depth, stencil);
}

void GL2EncoderBase::glGetBufferParameteri64v_s(void *self, GLenum target, GLenum pname, GLint64 *params)
{
    GET_CONTEXT;
    ctx->glGetBufferParameteri64vFunc(ctx->GetGLESv2Encoder(self), target, pname, params);
}

void GL2EncoderBase::glGetBufferPointerv_s(void *self, GLenum target, GLenum pname, void **params)
{
    GET_CONTEXT;
    ctx->glGetBufferPointervFunc(ctx->GetGLESv2Encoder(self), target, pname, params);
}

void GL2EncoderBase::glUniformBlockBinding_s(void *self, GLuint program, GLuint uniformBlockIndex,
    GLuint uniformBlockBinding)
{
    GET_CONTEXT;
    ctx->glUniformBlockBindingFunc(ctx->GetGLESv2Encoder(self), program, uniformBlockIndex, uniformBlockBinding);
}

GLuint GL2EncoderBase::glGetUniformBlockIndex_s(void *self, GLuint program, const GLchar *uniformBlockName)
{
    GET_CONTEXT;
    return ctx->glGetUniformBlockIndexFunc(ctx->GetGLESv2Encoder(self), program, uniformBlockName);
}

void GL2EncoderBase::glGetUniformIndices_s(void *self, GLuint program, GLsizei uniformCount,
    const GLchar * const * uniformNames, GLuint *uniformIndices)
{
    GET_CONTEXT;
    ctx->glGetUniformIndicesFunc(ctx->GetGLESv2Encoder(self), program, uniformCount, uniformNames, uniformIndices);
}

void GL2EncoderBase::glGetActiveUniformBlockiv_s(void *self, GLuint program, GLuint uniformBlockIndex, GLenum pname,
    GLint *params)
{
    GET_CONTEXT;
    ctx->glGetActiveUniformBlockivFunc(ctx->GetGLESv2Encoder(self), program, uniformBlockIndex, pname, params);
}

void GL2EncoderBase::glGetActiveUniformBlockName_s(void *self, GLuint program, GLuint uniformBlockIndex,
    GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName)
{
    GET_CONTEXT;
    ctx->glGetActiveUniformBlockNameFunc(ctx->GetGLESv2Encoder(self), program, uniformBlockIndex, bufSize, length,
        uniformBlockName);
}

void GL2EncoderBase::glUniform1ui_s(void *self, GLint location, GLuint v0)
{
    GET_CONTEXT;
    ctx->glUniform1uiFunc(ctx->GetGLESv2Encoder(self), location, v0);
}

void GL2EncoderBase::glUniform2ui_s(void *self, GLint location, GLuint v0, GLuint v1)
{
    GET_CONTEXT;
    ctx->glUniform2uiFunc(ctx->GetGLESv2Encoder(self), location, v0, v1);
}

void GL2EncoderBase::glUniform3ui_s(void *self, GLint location, GLuint v0, GLuint v1, GLuint v2)
{
    GET_CONTEXT;
    ctx->glUniform3uiFunc(ctx->GetGLESv2Encoder(self), location, v0, v1, v2);
}

void GL2EncoderBase::glUniform4ui_s(void *self, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
    GET_CONTEXT;
    ctx->glUniform4uiFunc(ctx->GetGLESv2Encoder(self), location, v0, v1, v2, v3);
}

void GL2EncoderBase::glUniform1uiv_s(void *self, GLint location, GLsizei count, const GLuint *value)
{
    GET_CONTEXT;
    ctx->glUniform1uivFunc(ctx->GetGLESv2Encoder(self), location, count, value);
}

void GL2EncoderBase::glUniform2uiv_s(void *self, GLint location, GLsizei count, const GLuint *value)
{
    GET_CONTEXT;
    ctx->glUniform2uivFunc(ctx->GetGLESv2Encoder(self), location, count, value);
}

void GL2EncoderBase::glUniform3uiv_s(void *self, GLint location, GLsizei count, const GLuint *value)
{
    GET_CONTEXT;
    ctx->glUniform3uivFunc(ctx->GetGLESv2Encoder(self), location, count, value);
}

void GL2EncoderBase::glUniform4uiv_s(void *self, GLint location, GLsizei count, const GLuint *value)
{
    GET_CONTEXT;
    ctx->glUniform4uivFunc(ctx->GetGLESv2Encoder(self), location, count, value);
}

void GL2EncoderBase::glUniformMatrix2x3fv_s(void *self, GLint location, GLsizei count, GLboolean transpose,
    const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glUniformMatrix2x3fvFunc(ctx->GetGLESv2Encoder(self), location, count, transpose, value);
}

void GL2EncoderBase::glUniformMatrix3x2fv_s(void *self, GLint location, GLsizei count, GLboolean transpose,
    const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glUniformMatrix3x2fvFunc(ctx->GetGLESv2Encoder(self), location, count, transpose, value);
}

void GL2EncoderBase::glUniformMatrix2x4fv_s(void *self, GLint location, GLsizei count, GLboolean transpose,
    const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glUniformMatrix2x4fvFunc(ctx->GetGLESv2Encoder(self), location, count, transpose, value);
}

void GL2EncoderBase::glUniformMatrix4x2fv_s(void *self, GLint location, GLsizei count, GLboolean transpose,
    const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glUniformMatrix4x2fvFunc(ctx->GetGLESv2Encoder(self), location, count, transpose, value);
}

void GL2EncoderBase::glUniformMatrix3x4fv_s(void *self, GLint location, GLsizei count, GLboolean transpose,
    const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glUniformMatrix3x4fvFunc(ctx->GetGLESv2Encoder(self), location, count, transpose, value);
}

void GL2EncoderBase::glUniformMatrix4x3fv_s(void *self, GLint location, GLsizei count, GLboolean transpose,
    const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glUniformMatrix4x3fvFunc(ctx->GetGLESv2Encoder(self), location, count, transpose, value);
}

void GL2EncoderBase::glGetUniformuiv_s(void *self, GLuint program, GLint location, GLuint *params)
{
    GET_CONTEXT;
    ctx->glGetUniformuivFunc(ctx->GetGLESv2Encoder(self), program, location, params);
}

void GL2EncoderBase::glGetActiveUniformsiv_s(void *self, GLuint program, GLsizei uniformCount,
    const GLuint *uniformIndices, GLenum pname, GLint *params)
{
    GET_CONTEXT;
    ctx->glGetActiveUniformsivFunc(ctx->GetGLESv2Encoder(self), program, uniformCount, uniformIndices, pname, params);
}

void GL2EncoderBase::glVertexAttribI4i_s(void *self, GLuint index, GLint x, GLint y, GLint z, GLint w)
{
    GET_CONTEXT;
    ctx->glVertexAttribI4iFunc(ctx->GetGLESv2Encoder(self), index, x, y, z, w);
}

void GL2EncoderBase::glVertexAttribI4ui_s(void *self, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
{
    GET_CONTEXT;
    ctx->glVertexAttribI4uiFunc(ctx->GetGLESv2Encoder(self), index, x, y, z, w);
}

void GL2EncoderBase::glVertexAttribI4iv_s(void *self, GLuint index, const GLint *v)
{
    GET_CONTEXT;
    ctx->glVertexAttribI4ivFunc(ctx->GetGLESv2Encoder(self), index, v);
}

void GL2EncoderBase::glVertexAttribI4uiv_s(void *self, GLuint index, const GLuint *v)
{
    GET_CONTEXT;
    ctx->glVertexAttribI4uivFunc(ctx->GetGLESv2Encoder(self), index, v);
}


void GL2EncoderBase::glVertexAttribIPointer_s(void *self, GLuint index, GLint size, GLenum type, GLsizei stride,
    const void *pointer)
{
    GET_CONTEXT;
    ctx->glVertexAttribIPointerFunc(ctx->GetGLESv2Encoder(self), index, size, type, stride, pointer);
}

void GL2EncoderBase::glGetVertexAttribIiv_s(void *self, GLuint index, GLenum pname, GLint *params)
{
    GET_CONTEXT;
    ctx->glGetVertexAttribIivFunc(ctx->GetGLESv2Encoder(self), index, pname, params);
}

void GL2EncoderBase::glGetVertexAttribIuiv_s(void *self, GLuint index, GLenum pname, GLuint *params)
{
    GET_CONTEXT;
    ctx->glGetVertexAttribIuivFunc(ctx->GetGLESv2Encoder(self), index, pname, params);
}

void GL2EncoderBase::glVertexAttribDivisor_s(void *self, GLuint index, GLuint divisor)
{
    GET_CONTEXT;
    ctx->glVertexAttribDivisorFunc(ctx->GetGLESv2Encoder(self), index, divisor);
}

void GL2EncoderBase::glDrawArraysInstanced_s(void *self, GLenum mode, GLint first, GLsizei count, GLsizei instancecount)
{
    GET_CONTEXT;
    ctx->glDrawArraysInstancedFunc(ctx->GetGLESv2Encoder(self), mode, first, count, instancecount);
}

void GL2EncoderBase::glDrawElementsInstanced_s(void *self, GLenum mode, GLsizei count, GLenum type, const void *indices,
    GLsizei instancecount)
{
    GET_CONTEXT;
    ctx->glDrawElementsInstancedFunc(ctx->GetGLESv2Encoder(self), mode, count, type, indices, instancecount);
}

void GL2EncoderBase::glDrawRangeElements_s(void *self, GLenum mode, GLuint start, GLuint end, GLsizei count,
    GLenum type, const void *indices)
{
    GET_CONTEXT;
    ctx->glDrawRangeElementsFunc(ctx->GetGLESv2Encoder(self), mode, start, end, count, type, indices);
}

GLsync GL2EncoderBase::glFenceSync_s(void *self, GLenum condition, GLbitfield flags)
{
    GET_CONTEXT;
    return ctx->glFenceSyncFunc(ctx->GetGLESv2Encoder(self), condition, flags);
}

GLenum GL2EncoderBase::glClientWaitSync_s(void *self, GLsync sync, GLbitfield flags, GLuint64 timeout)
{
    GET_CONTEXT;
    return ctx->glClientWaitSyncFunc(ctx->GetGLESv2Encoder(self), sync, flags, timeout);
}

void GL2EncoderBase::glWaitSync_s(void *self, GLsync sync, GLbitfield flags, GLuint64 timeout)
{
    GET_CONTEXT;
    ctx->glWaitSyncFunc(ctx->GetGLESv2Encoder(self), sync, flags, timeout);
}

void GL2EncoderBase::glDeleteSync_s(void *self, GLsync sync)
{
    GET_CONTEXT;
    ctx->glDeleteSyncFunc(ctx->GetGLESv2Encoder(self), sync);
}

GLboolean GL2EncoderBase::glIsSync_s(void *self, GLsync sync)
{
    GET_CONTEXT;
    return ctx->glIsSyncFunc(ctx->GetGLESv2Encoder(self), sync);
}

void GL2EncoderBase::glGetSynciv_s(void *self, GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length,
    GLint *values)
{
    GET_CONTEXT;
    ctx->glGetSyncivFunc(ctx->GetGLESv2Encoder(self), sync, pname, bufSize, length, values);
}

void GL2EncoderBase::glDrawBuffers_s(void *self, GLsizei n, const GLenum *bufs)
{
    GET_CONTEXT;
    ctx->glDrawBuffersFunc(ctx->GetGLESv2Encoder(self), n, bufs);
}

void GL2EncoderBase::glReadBuffer_s(void *self, GLenum src)
{
    GET_CONTEXT;
    ctx->glReadBufferFunc(ctx->GetGLESv2Encoder(self), src);
}

void GL2EncoderBase::glBlitFramebuffer_s(void *self, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0,
    GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
{
    GET_CONTEXT;
    ctx->glBlitFramebufferFunc(ctx->GetGLESv2Encoder(self), srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1,
        mask, filter);
}

void GL2EncoderBase::glInvalidateFramebuffer_s(void *self, GLenum target, GLsizei numAttachments,
    const GLenum *attachments)
{
    GET_CONTEXT;
    ctx->glInvalidateFramebufferFunc(ctx->GetGLESv2Encoder(self), target, numAttachments, attachments);
}

void GL2EncoderBase::glInvalidateSubFramebuffer_s(void *self, GLenum target, GLsizei numAttachments,
    const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height)
{
    GET_CONTEXT;
    ctx->glInvalidateSubFramebufferFunc(ctx->GetGLESv2Encoder(self), target, numAttachments, attachments, x, y, width,
        height);
}

void GL2EncoderBase::glFramebufferTextureLayer_s(void *self, GLenum target, GLenum attachment, GLuint texture,
    GLint level, GLint layer)
{
    GET_CONTEXT;
    ctx->glFramebufferTextureLayerFunc(ctx->GetGLESv2Encoder(self), target, attachment, texture, level, layer);
}

void GL2EncoderBase::glRenderbufferStorageMultisample_s(void *self, GLenum target, GLsizei samples,
    GLenum internalformat, GLsizei width, GLsizei height)
{
    GET_CONTEXT;
    ctx->glRenderbufferStorageMultisampleFunc(ctx->GetGLESv2Encoder(self), target, samples, internalformat, width,
        height);
}

void GL2EncoderBase::glTexStorage2D_s(void *self, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width,
    GLsizei height)
{
    GET_CONTEXT;
    ctx->glTexStorage2DFunc(ctx->GetGLESv2Encoder(self), target, levels, internalformat, width, height);
}

void GL2EncoderBase::glGetInternalformativ_s(void *self, GLenum target, GLenum internalformat, GLenum pname,
    GLsizei bufSize, GLint *params)
{
    GET_CONTEXT;
    ctx->glGetInternalformativFunc(ctx->GetGLESv2Encoder(self), target, internalformat, pname, bufSize, params);
}

void GL2EncoderBase::glBeginTransformFeedback_s(void *self, GLenum primitiveMode)
{
    GET_CONTEXT;
    ctx->glBeginTransformFeedbackFunc(ctx->GetGLESv2Encoder(self), primitiveMode);
}

void GL2EncoderBase::glEndTransformFeedback_s(void *self)
{
    GET_CONTEXT;
    ctx->glEndTransformFeedbackFunc(ctx->GetGLESv2Encoder(self));
}

void GL2EncoderBase::glGenTransformFeedbacks_s(void *self, GLsizei n, GLuint *ids)
{
    GET_CONTEXT;
    ctx->glGenTransformFeedbacksFunc(ctx->GetGLESv2Encoder(self), n, ids);
}

void GL2EncoderBase::glDeleteTransformFeedbacks_s(void *self, GLsizei n, const GLuint *ids)
{
    GET_CONTEXT;
    ctx->glDeleteTransformFeedbacksFunc(ctx->GetGLESv2Encoder(self), n, ids);
}

void GL2EncoderBase::glBindTransformFeedback_s(void *self, GLenum target, GLuint id)
{
    GET_CONTEXT;
    ctx->glBindTransformFeedbackFunc(ctx->GetGLESv2Encoder(self), target, id);
}

void GL2EncoderBase::glPauseTransformFeedback_s(void *self)
{
    GET_CONTEXT;
    ctx->glPauseTransformFeedbackFunc(ctx->GetGLESv2Encoder(self));
}

void GL2EncoderBase::glResumeTransformFeedback_s(void *self)
{
    GET_CONTEXT;
    ctx->glResumeTransformFeedbackFunc(ctx->GetGLESv2Encoder(self));
}

GLboolean GL2EncoderBase::glIsTransformFeedback_s(void *self, GLuint id)
{
    GET_CONTEXT;
    return ctx->glIsTransformFeedbackFunc(ctx->GetGLESv2Encoder(self), id);
}

void GL2EncoderBase::glTransformFeedbackVaryings_s(void *self, GLuint program, GLsizei count,
    const GLchar * const * varyings, GLenum bufferMode)
{
    GET_CONTEXT;
    ctx->glTransformFeedbackVaryingsFunc(ctx->GetGLESv2Encoder(self), program, count, varyings, bufferMode);
}

void GL2EncoderBase::glGetTransformFeedbackVarying_s(void *self, GLuint program, GLuint index, GLsizei bufSize,
    GLsizei *length, GLsizei *size, GLenum *type, GLchar *name)
{
    GET_CONTEXT;
    ctx->glGetTransformFeedbackVaryingFunc(ctx->GetGLESv2Encoder(self), program, index, bufSize, length, size, type,
        name);
}

void GL2EncoderBase::glGenSamplers_s(void *self, GLsizei count, GLuint *samplers)
{
    GET_CONTEXT;
    ctx->glGenSamplersFunc(ctx->GetGLESv2Encoder(self), count, samplers);
}

void GL2EncoderBase::glDeleteSamplers_s(void *self, GLsizei count, const GLuint *samplers)
{
    GET_CONTEXT;
    ctx->glDeleteSamplersFunc(ctx->GetGLESv2Encoder(self), count, samplers);
}

void GL2EncoderBase::glBindSampler_s(void *self, GLuint unit, GLuint sampler)
{
    GET_CONTEXT;
    ctx->glBindSamplerFunc(ctx->GetGLESv2Encoder(self), unit, sampler);
}

void GL2EncoderBase::glSamplerParameterf_s(void *self, GLuint sampler, GLenum pname, GLfloat param)
{
    GET_CONTEXT;
    ctx->glSamplerParameterfFunc(ctx->GetGLESv2Encoder(self), sampler, pname, param);
}

void GL2EncoderBase::glSamplerParameteri_s(void *self, GLuint sampler, GLenum pname, GLint param)
{
    GET_CONTEXT;
    ctx->glSamplerParameteriFunc(ctx->GetGLESv2Encoder(self), sampler, pname, param);
}

void GL2EncoderBase::glSamplerParameterfv_s(void *self, GLuint sampler, GLenum pname, const GLfloat *param)
{
    GET_CONTEXT;
    ctx->glSamplerParameterfvFunc(ctx->GetGLESv2Encoder(self), sampler, pname, param);
}

void GL2EncoderBase::glSamplerParameteriv_s(void *self, GLuint sampler, GLenum pname, const GLint *param)
{
    GET_CONTEXT;
    ctx->glSamplerParameterivFunc(ctx->GetGLESv2Encoder(self), sampler, pname, param);
}

void GL2EncoderBase::glGetSamplerParameterfv_s(void *self, GLuint sampler, GLenum pname, GLfloat *params)
{
    GET_CONTEXT;
    ctx->glGetSamplerParameterfvFunc(ctx->GetGLESv2Encoder(self), sampler, pname, params);
}


void GL2EncoderBase::glGetSamplerParameteriv_s(void *self, GLuint sampler, GLenum pname, GLint *params)
{
    GET_CONTEXT;
    ctx->glGetSamplerParameterivFunc(ctx->GetGLESv2Encoder(self), sampler, pname, params);
}

GLboolean GL2EncoderBase::glIsSampler_s(void *self, GLuint sampler)
{
    GET_CONTEXT;
    return ctx->glIsSamplerFunc(ctx->GetGLESv2Encoder(self), sampler);
}

void GL2EncoderBase::glGenQueries_s(void *self, GLsizei n, GLuint *ids)
{
    GET_CONTEXT;
    ctx->glGenQueriesFunc(ctx->GetGLESv2Encoder(self), n, ids);
}

void GL2EncoderBase::glDeleteQueries_s(void *self, GLsizei n, const GLuint *ids)
{
    GET_CONTEXT;
    ctx->glDeleteQueriesFunc(ctx->GetGLESv2Encoder(self), n, ids);
}

void GL2EncoderBase::glBeginQuery_s(void *self, GLenum target, GLuint id)
{
    GET_CONTEXT;
    ctx->glBeginQueryFunc(ctx->GetGLESv2Encoder(self), target, id);
}

void GL2EncoderBase::glEndQuery_s(void *self, GLenum target)
{
    GET_CONTEXT;
    ctx->glEndQueryFunc(ctx->GetGLESv2Encoder(self), target);
}

void GL2EncoderBase::glGetQueryiv_s(void *self, GLenum target, GLenum pname, GLint *params)
{
    GET_CONTEXT;
    ctx->glGetQueryivFunc(ctx->GetGLESv2Encoder(self), target, pname, params);
}

void GL2EncoderBase::glGetQueryObjectuiv_s(void *self, GLuint id, GLenum pname, GLuint *params)
{
    GET_CONTEXT;
    ctx->glGetQueryObjectuivFunc(ctx->GetGLESv2Encoder(self), id, pname, params);
}

GLboolean GL2EncoderBase::glIsQuery_s(void *self, GLuint id)
{
    GET_CONTEXT;
    return ctx->glIsQueryFunc(ctx->GetGLESv2Encoder(self), id);
}

void GL2EncoderBase::glProgramParameteri_s(void *self, GLuint program, GLenum pname, GLint value)
{
    GET_CONTEXT;
    ctx->glProgramParameteriFunc(ctx->GetGLESv2Encoder(self), program, pname, value);
}

void GL2EncoderBase::glProgramBinary_s(void *self, GLuint program, GLenum binaryFormat, const void *binary,
    GLsizei length)
{
    GET_CONTEXT;
    ctx->glProgramBinaryFunc(ctx->GetGLESv2Encoder(self), program, binaryFormat, binary, length);
}

void GL2EncoderBase::glGetProgramBinary_s(void *self, GLuint program, GLsizei bufSize, GLsizei *length,
    GLenum *binaryFormat, void *binary)
{
    GET_CONTEXT;
    ctx->glGetProgramBinaryFunc(ctx->GetGLESv2Encoder(self), program, bufSize, length, binaryFormat, binary);
}

GLint GL2EncoderBase::glGetFragDataLocation_s(void *self, GLuint program, const GLchar *name)
{
    GET_CONTEXT;
    return ctx->glGetFragDataLocationFunc(ctx->GetGLESv2Encoder(self), program, name);
}

void GL2EncoderBase::glGetInteger64v_s(void *self, GLenum pname, GLint64 *data)
{
    GET_CONTEXT;
    ctx->glGetInteger64vFunc(ctx->GetGLESv2Encoder(self), pname, data);
}

void GL2EncoderBase::glGetIntegeri_v_s(void *self, GLenum target, GLuint index, GLint *data)
{
    GET_CONTEXT;
    ctx->glGetIntegeri_vFunc(ctx->GetGLESv2Encoder(self), target, index, data);
}

void GL2EncoderBase::glGetInteger64i_v_s(void *self, GLenum target, GLuint index, GLint64 *data)
{
    GET_CONTEXT;
    ctx->glGetInteger64i_vFunc(ctx->GetGLESv2Encoder(self), target, index, data);
}

void GL2EncoderBase::glTexImage3D_s(void *self, GLenum target, GLint level, GLint internalformat, GLsizei width,
    GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels)
{
    GET_CONTEXT;
    ctx->glTexImage3DFunc(ctx->GetGLESv2Encoder(self), target, level, internalformat, width, height, depth, border,
        format, type, pixels);
}

void GL2EncoderBase::glTexStorage3D_s(void *self, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width,
    GLsizei height, GLsizei depth)
{
    GET_CONTEXT;
    ctx->glTexStorage3DFunc(ctx->GetGLESv2Encoder(self), target, levels, internalformat, width, height, depth);
}

void GL2EncoderBase::glTexSubImage3D_s(void *self, GLenum target, GLint level, GLint xoffset, GLint yoffset,
    GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels)
{
    GET_CONTEXT;
    ctx->glTexSubImage3DFunc(ctx->GetGLESv2Encoder(self), target, level, xoffset, yoffset, zoffset, width, height,
        depth, format, type, pixels);
}

void GL2EncoderBase::glCompressedTexImage3D_s(void *self, GLenum target, GLint level, GLenum internalformat,
    GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data)
{
    GET_CONTEXT;
    ctx->glCompressedTexImage3DFunc(ctx->GetGLESv2Encoder(self), target, level, internalformat, width, height, depth,
        border, imageSize, data);
}

void GL2EncoderBase::glCompressedTexSubImage3D_s(void *self, GLenum target, GLint level, GLint xoffset, GLint yoffset,
    GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data)
{
    GET_CONTEXT;
    ctx->glCompressedTexSubImage3DFunc(ctx->GetGLESv2Encoder(self), target, level, xoffset, yoffset, zoffset, width,
        height, depth, format, imageSize, data);
}

void GL2EncoderBase::glCopyTexSubImage3D_s(void *self, GLenum target, GLint level, GLint xoffset, GLint yoffset,
    GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
    GET_CONTEXT;
    ctx->glCopyTexSubImage3DFunc(ctx->GetGLESv2Encoder(self), target, level, xoffset, yoffset, zoffset, x, y, width,
        height);
}

const GLubyte *GL2EncoderBase::glGetStringi_s(void *self, GLenum name, GLuint index)
{
    GET_CONTEXT;
    return ctx->glGetStringiFunc(ctx->GetGLESv2Encoder(self), name, index);
}

void GL2EncoderBase::glGetBooleani_v_s(void *self, GLenum target, GLuint index, GLboolean *data)
{
    GET_CONTEXT;
    ctx->glGetBooleani_vFunc(ctx->GetGLESv2Encoder(self), target, index, data);
}

void GL2EncoderBase::glMemoryBarrier_s(void *self, GLbitfield barriers)
{
    GET_CONTEXT;
    ctx->glMemoryBarrierFunc(ctx->GetGLESv2Encoder(self), barriers);
}

void GL2EncoderBase::glMemoryBarrierByRegion_s(void *self, GLbitfield barriers)
{
    GET_CONTEXT;
    ctx->glMemoryBarrierByRegionFunc(ctx->GetGLESv2Encoder(self), barriers);
}

void GL2EncoderBase::glGenProgramPipelines_s(void *self, GLsizei n, GLuint *pipelines)
{
    GET_CONTEXT;
    ctx->glGenProgramPipelinesFunc(ctx->GetGLESv2Encoder(self), n, pipelines);
}

void GL2EncoderBase::glDeleteProgramPipelines_s(void *self, GLsizei n, const GLuint *pipelines)
{
    GET_CONTEXT;
    ctx->glDeleteProgramPipelinesFunc(ctx->GetGLESv2Encoder(self), n, pipelines);
}

void GL2EncoderBase::glBindProgramPipeline_s(void *self, GLuint pipeline)
{
    GET_CONTEXT;
    ctx->glBindProgramPipelineFunc(ctx->GetGLESv2Encoder(self), pipeline);
}

void GL2EncoderBase::glGetProgramPipelineiv_s(void *self, GLuint pipeline, GLenum pname, GLint *params)
{
    GET_CONTEXT;
    ctx->glGetProgramPipelineivFunc(ctx->GetGLESv2Encoder(self), pipeline, pname, params);
}

void GL2EncoderBase::glGetProgramPipelineInfoLog_s(void *self, GLuint pipeline, GLsizei bufSize, GLsizei *length,
    GLchar *infoLog)
{
    GET_CONTEXT;
    ctx->glGetProgramPipelineInfoLogFunc(ctx->GetGLESv2Encoder(self), pipeline, bufSize, length, infoLog);
}

void GL2EncoderBase::glValidateProgramPipeline_s(void *self, GLuint pipeline)
{
    GET_CONTEXT;
    ctx->glValidateProgramPipelineFunc(ctx->GetGLESv2Encoder(self), pipeline);
}

GLboolean GL2EncoderBase::glIsProgramPipeline_s(void *self, GLuint pipeline)
{
    GET_CONTEXT;
    return ctx->glIsProgramPipelineFunc(ctx->GetGLESv2Encoder(self), pipeline);
}

void GL2EncoderBase::glUseProgramStages_s(void *self, GLuint pipeline, GLbitfield stages, GLuint program)
{
    GET_CONTEXT;
    ctx->glUseProgramStagesFunc(ctx->GetGLESv2Encoder(self), pipeline, stages, program);
}

void GL2EncoderBase::glActiveShaderProgram_s(void *self, GLuint pipeline, GLuint program)
{
    GET_CONTEXT;
    ctx->glActiveShaderProgramFunc(ctx->GetGLESv2Encoder(self), pipeline, program);
}

GLuint GL2EncoderBase::glCreateShaderProgramv_s(void *self, GLenum type, GLsizei count, const GLchar * const * strings)
{
    GET_CONTEXT;
    return ctx->glCreateShaderProgramvFunc(ctx->GetGLESv2Encoder(self), type, count, strings);
}

void GL2EncoderBase::glProgramUniform1f_s(void *self, GLuint program, GLint location, GLfloat v0)
{
    GET_CONTEXT;
    ctx->glProgramUniform1fFunc(ctx->GetGLESv2Encoder(self), program, location, v0);
}

void GL2EncoderBase::glProgramUniform2f_s(void *self, GLuint program, GLint location, GLfloat v0, GLfloat v1)
{
    GET_CONTEXT;
    ctx->glProgramUniform2fFunc(ctx->GetGLESv2Encoder(self), program, location, v0, v1);
}

void GL2EncoderBase::glProgramUniform3f_s(void *self, GLuint program, GLint location, GLfloat v0, GLfloat v1,
    GLfloat v2)
{
    GET_CONTEXT;
    ctx->glProgramUniform3fFunc(ctx->GetGLESv2Encoder(self), program, location, v0, v1, v2);
}

void GL2EncoderBase::glProgramUniform4f_s(void *self, GLuint program, GLint location, GLfloat v0, GLfloat v1,
    GLfloat v2, GLfloat v3)
{
    GET_CONTEXT;
    ctx->glProgramUniform4fFunc(ctx->GetGLESv2Encoder(self), program, location, v0, v1, v2, v3);
}

void GL2EncoderBase::glProgramUniform1i_s(void *self, GLuint program, GLint location, GLint v0)
{
    GET_CONTEXT;
    ctx->glProgramUniform1iFunc(ctx->GetGLESv2Encoder(self), program, location, v0);
}

void GL2EncoderBase::glProgramUniform2i_s(void *self, GLuint program, GLint location, GLint v0, GLint v1)
{
    GET_CONTEXT;
    ctx->glProgramUniform2iFunc(ctx->GetGLESv2Encoder(self), program, location, v0, v1);
}

void GL2EncoderBase::glProgramUniform3i_s(void *self, GLuint program, GLint location, GLint v0, GLint v1, GLint v2)
{
    GET_CONTEXT;
    ctx->glProgramUniform3iFunc(ctx->GetGLESv2Encoder(self), program, location, v0, v1, v2);
}

void GL2EncoderBase::glProgramUniform4i_s(void *self, GLuint program, GLint location, GLint v0, GLint v1, GLint v2,
    GLint v3)
{
    GET_CONTEXT;
    ctx->glProgramUniform4iFunc(ctx->GetGLESv2Encoder(self), program, location, v0, v1, v2, v3);
}

void GL2EncoderBase::glProgramUniform1ui_s(void *self, GLuint program, GLint location, GLuint v0)
{
    GET_CONTEXT;
    ctx->glProgramUniform1uiFunc(ctx->GetGLESv2Encoder(self), program, location, v0);
}

void GL2EncoderBase::glProgramUniform2ui_s(void *self, GLuint program, GLint location, GLuint v0, GLuint v1)
{
    GET_CONTEXT;
    ctx->glProgramUniform2uiFunc(ctx->GetGLESv2Encoder(self), program, location, v0, v1);
}

void GL2EncoderBase::glProgramUniform3ui_s(void *self, GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2)
{
    GET_CONTEXT;
    ctx->glProgramUniform3uiFunc(ctx->GetGLESv2Encoder(self), program, location, v0, v1, v2);
}

void GL2EncoderBase::glProgramUniform4ui_s(void *self, GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2,
    GLuint v3)
{
    GET_CONTEXT;
    ctx->glProgramUniform4uiFunc(ctx->GetGLESv2Encoder(self), program, location, v0, v1, v2, v3);
}

void GL2EncoderBase::glProgramUniform1fv_s(void *self, GLuint program, GLint location, GLsizei count,
    const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glProgramUniform1fvFunc(ctx->GetGLESv2Encoder(self), program, location, count, value);
}

void GL2EncoderBase::glProgramUniform2fv_s(void *self, GLuint program, GLint location, GLsizei count,
    const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glProgramUniform2fvFunc(ctx->GetGLESv2Encoder(self), program, location, count, value);
}

void GL2EncoderBase::glProgramUniform3fv_s(void *self, GLuint program, GLint location, GLsizei count,
    const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glProgramUniform3fvFunc(ctx->GetGLESv2Encoder(self), program, location, count, value);
}

void GL2EncoderBase::glProgramUniform4fv_s(void *self, GLuint program, GLint location, GLsizei count,
    const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glProgramUniform4fvFunc(ctx->GetGLESv2Encoder(self), program, location, count, value);
}

void GL2EncoderBase::glProgramUniform1iv_s(void *self, GLuint program, GLint location, GLsizei count,
    const GLint *value)
{
    GET_CONTEXT;
    ctx->glProgramUniform1ivFunc(ctx->GetGLESv2Encoder(self), program, location, count, value);
}

void GL2EncoderBase::glProgramUniform2iv_s(void *self, GLuint program, GLint location, GLsizei count,
    const GLint *value)
{
    GET_CONTEXT;
    ctx->glProgramUniform2ivFunc(ctx->GetGLESv2Encoder(self), program, location, count, value);
}

void GL2EncoderBase::glProgramUniform3iv_s(void *self, GLuint program, GLint location, GLsizei count,
    const GLint *value)
{
    GET_CONTEXT;
    ctx->glProgramUniform3ivFunc(ctx->GetGLESv2Encoder(self), program, location, count, value);
}

void GL2EncoderBase::glProgramUniform4iv_s(void *self, GLuint program, GLint location, GLsizei count,
    const GLint *value)
{
    GET_CONTEXT;
    ctx->glProgramUniform4ivFunc(ctx->GetGLESv2Encoder(self), program, location, count, value);
}

void GL2EncoderBase::glProgramUniform1uiv_s(void *self, GLuint program, GLint location, GLsizei count,
    const GLuint *value)
{
    GET_CONTEXT;
    ctx->glProgramUniform1uivFunc(ctx->GetGLESv2Encoder(self), program, location, count, value);
}

void GL2EncoderBase::glProgramUniform2uiv_s(void *self, GLuint program, GLint location, GLsizei count,
    const GLuint *value)
{
    GET_CONTEXT;
    ctx->glProgramUniform2uivFunc(ctx->GetGLESv2Encoder(self), program, location, count, value);
}

void GL2EncoderBase::glProgramUniform3uiv_s(void *self, GLuint program, GLint location, GLsizei count,
    const GLuint *value)
{
    GET_CONTEXT;
    ctx->glProgramUniform3uivFunc(ctx->GetGLESv2Encoder(self), program, location, count, value);
}

void GL2EncoderBase::glProgramUniform4uiv_s(void *self, GLuint program, GLint location, GLsizei count,
    const GLuint *value)
{
    GET_CONTEXT;
    ctx->glProgramUniform4uivFunc(ctx->GetGLESv2Encoder(self), program, location, count, value);
}

void GL2EncoderBase::glProgramUniformMatrix2fv_s(void *self, GLuint program, GLint location, GLsizei count,
    GLboolean transpose, const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glProgramUniformMatrix2fvFunc(ctx->GetGLESv2Encoder(self), program, location, count, transpose, value);
}

void GL2EncoderBase::glProgramUniformMatrix3fv_s(void *self, GLuint program, GLint location, GLsizei count,
    GLboolean transpose, const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glProgramUniformMatrix3fvFunc(ctx->GetGLESv2Encoder(self), program, location, count, transpose, value);
}

void GL2EncoderBase::glProgramUniformMatrix4fv_s(void *self, GLuint program, GLint location, GLsizei count,
    GLboolean transpose, const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glProgramUniformMatrix4fvFunc(ctx->GetGLESv2Encoder(self), program, location, count, transpose, value);
}

void GL2EncoderBase::glProgramUniformMatrix2x3fv_s(void *self, GLuint program, GLint location, GLsizei count,
    GLboolean transpose, const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glProgramUniformMatrix2x3fvFunc(ctx->GetGLESv2Encoder(self), program, location, count, transpose, value);
}

void GL2EncoderBase::glProgramUniformMatrix3x2fv_s(void *self, GLuint program, GLint location, GLsizei count,
    GLboolean transpose, const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glProgramUniformMatrix3x2fvFunc(ctx->GetGLESv2Encoder(self), program, location, count, transpose, value);
}

void GL2EncoderBase::glProgramUniformMatrix2x4fv_s(void *self, GLuint program, GLint location, GLsizei count,
    GLboolean transpose, const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glProgramUniformMatrix2x4fvFunc(ctx->GetGLESv2Encoder(self), program, location, count, transpose, value);
}

void GL2EncoderBase::glProgramUniformMatrix4x2fv_s(void *self, GLuint program, GLint location, GLsizei count,
    GLboolean transpose, const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glProgramUniformMatrix4x2fvFunc(ctx->GetGLESv2Encoder(self), program, location, count, transpose, value);
}

void GL2EncoderBase::glProgramUniformMatrix3x4fv_s(void *self, GLuint program, GLint location, GLsizei count,
    GLboolean transpose, const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glProgramUniformMatrix3x4fvFunc(ctx->GetGLESv2Encoder(self), program, location, count, transpose, value);
}

void GL2EncoderBase::glProgramUniformMatrix4x3fv_s(void *self, GLuint program, GLint location, GLsizei count,
    GLboolean transpose, const GLfloat *value)
{
    GET_CONTEXT;
    ctx->glProgramUniformMatrix4x3fvFunc(ctx->GetGLESv2Encoder(self), program, location, count, transpose, value);
}

void GL2EncoderBase::glGetProgramInterfaceiv_s(void *self, GLuint program, GLenum programInterface, GLenum pname,
    GLint *params)
{
    GET_CONTEXT;
    ctx->glGetProgramInterfaceivFunc(ctx->GetGLESv2Encoder(self), program, programInterface, pname, params);
}

void GL2EncoderBase::glGetProgramResourceiv_s(void *self, GLuint program, GLenum programInterface, GLuint index,
    GLsizei propCount, const GLenum *props, GLsizei bufSize, GLsizei *length, GLint *params)
{
    GET_CONTEXT;
    ctx->glGetProgramResourceivFunc(ctx->GetGLESv2Encoder(self), program, programInterface, index, propCount, props,
        bufSize, length, params);
}

GLuint GL2EncoderBase::glGetProgramResourceIndex_s(void *self, GLuint program, GLenum programInterface,
    const GLchar *name)
{
    GET_CONTEXT;
    return ctx->glGetProgramResourceIndexFunc(ctx->GetGLESv2Encoder(self), program, programInterface, name);
}

GLint GL2EncoderBase::glGetProgramResourceLocation_s(void *self, GLuint program, GLenum programInterface,
    const GLchar *name)
{
    GET_CONTEXT;
    return ctx->glGetProgramResourceLocationFunc(ctx->GetGLESv2Encoder(self), program, programInterface, name);
}

void GL2EncoderBase::glGetProgramResourceName_s(void *self, GLuint program, GLenum programInterface, GLuint index,
    GLsizei bufSize, GLsizei *length, GLchar *name)
{
    GET_CONTEXT;
    ctx->glGetProgramResourceNameFunc(ctx->GetGLESv2Encoder(self), program, programInterface, index, bufSize, length,
        name);
}

void GL2EncoderBase::glBindImageTexture_s(void *self, GLuint unit, GLuint texture, GLint level, GLboolean layered,
    GLint layer, GLenum access, GLenum format)
{
    GET_CONTEXT;
    ctx->glBindImageTextureFunc(ctx->GetGLESv2Encoder(self), unit, texture, level, layered, layer, access, format);
}

void GL2EncoderBase::glDispatchCompute_s(void *self, GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z)
{
    GET_CONTEXT;
    ctx->glDispatchComputeFunc(ctx->GetGLESv2Encoder(self), num_groups_x, num_groups_y, num_groups_z);
}

void GL2EncoderBase::glDispatchComputeIndirect_s(void *self, GLintptr indirect)
{
    GET_CONTEXT;
    ctx->glDispatchComputeIndirectFunc(ctx->GetGLESv2Encoder(self), indirect);
}

void GL2EncoderBase::glBindVertexBuffer_s(void *self, GLuint bindingindex, GLuint buffer, GLintptr offset,
    GLsizei stride)
{
    GET_CONTEXT;
    ctx->glBindVertexBufferFunc(ctx->GetGLESv2Encoder(self), bindingindex, buffer, offset, stride);
}

void GL2EncoderBase::glVertexAttribBinding_s(void *self, GLuint attribindex, GLuint bindingindex)
{
    GET_CONTEXT;
    ctx->glVertexAttribBindingFunc(ctx->GetGLESv2Encoder(self), attribindex, bindingindex);
}

void GL2EncoderBase::glVertexAttribFormat_s(void *self, GLuint attribindex, GLint size, GLenum type,
    GLboolean normalized, GLuint relativeoffset)
{
    GET_CONTEXT;
    ctx->glVertexAttribFormatFunc(ctx->GetGLESv2Encoder(self), attribindex, size, type, normalized, relativeoffset);
}

void GL2EncoderBase::glVertexAttribIFormat_s(void *self, GLuint attribindex, GLint size, GLenum type,
    GLuint relativeoffset)
{
    GET_CONTEXT;
    ctx->glVertexAttribIFormatFunc(ctx->GetGLESv2Encoder(self), attribindex, size, type, relativeoffset);
}

void GL2EncoderBase::glVertexBindingDivisor_s(void *self, GLuint bindingindex, GLuint divisor)
{
    GET_CONTEXT;
    ctx->glVertexBindingDivisorFunc(ctx->GetGLESv2Encoder(self), bindingindex, divisor);
}

void GL2EncoderBase::glDrawArraysIndirect_s(void *self, GLenum mode, const void *indirect)
{
    GET_CONTEXT;
    ctx->glDrawArraysIndirectFunc(ctx->GetGLESv2Encoder(self), mode, indirect);
}

void GL2EncoderBase::glDrawElementsIndirect_s(void *self, GLenum mode, GLenum type, const void *indirect)
{
    GET_CONTEXT;
    ctx->glDrawElementsIndirectFunc(ctx->GetGLESv2Encoder(self), mode, type, indirect);
}

void GL2EncoderBase::glTexStorage2DMultisample_s(void *self, GLenum target, GLsizei samples, GLenum internalformat,
    GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
    GET_CONTEXT;
    ctx->glTexStorage2DMultisampleFunc(ctx->GetGLESv2Encoder(self), target, samples, internalformat, width, height,
        fixedsamplelocations);
}

void GL2EncoderBase::glSampleMaski_s(void *self, GLuint maskNumber, GLbitfield mask)
{
    GET_CONTEXT;
    ctx->glSampleMaskiFunc(ctx->GetGLESv2Encoder(self), maskNumber, mask);
}

void GL2EncoderBase::glGetMultisamplefv_s(void *self, GLenum pname, GLuint index, GLfloat *val)
{
    GET_CONTEXT;
    ctx->glGetMultisamplefvFunc(ctx->GetGLESv2Encoder(self), pname, index, val);
}

void GL2EncoderBase::glFramebufferParameteri_s(void *self, GLenum target, GLenum pname, GLint param)
{
    GET_CONTEXT;
    ctx->glFramebufferParameteriFunc(ctx->GetGLESv2Encoder(self), target, pname, param);
}

void GL2EncoderBase::glGetFramebufferParameteriv_s(void *self, GLenum target, GLenum pname, GLint *params)
{
    GET_CONTEXT;
    ctx->glGetFramebufferParameterivFunc(ctx->GetGLESv2Encoder(self), target, pname, params);
}

void GL2EncoderBase::glGetTexLevelParameterfv_s(void *self, GLenum target, GLint level, GLenum pname, GLfloat *params)
{
    GET_CONTEXT;
    ctx->glGetTexLevelParameterfvFunc(ctx->GetGLESv2Encoder(self), target, level, pname, params);
}

void GL2EncoderBase::glGetTexLevelParameteriv_s(void *self, GLenum target, GLint level, GLenum pname, GLint *params)
{
    GET_CONTEXT;
    ctx->glGetTexLevelParameterivFunc(ctx->GetGLESv2Encoder(self), target, level, pname, params);
}

void GL2EncoderBase::glEnableiEXT_s(void *self, GLenum target, GLuint index)
{
    GET_CONTEXT;
    ctx->glEnableiEXTFunc(ctx->GetGLESv2Encoder(self), target, index);
}

void GL2EncoderBase::glDisableiEXT_s(void *self, GLenum target, GLuint index)
{
    GET_CONTEXT;
    ctx->glDisableiEXTFunc(ctx->GetGLESv2Encoder(self), target, index);
}

void GL2EncoderBase::glBlendEquationiEXT_s(void *self, GLuint buf, GLenum mode)
{
    GET_CONTEXT;
    ctx->glBlendEquationiEXTFunc(ctx->GetGLESv2Encoder(self), buf, mode);
}

void GL2EncoderBase::glBlendEquationSeparateiEXT_s(void *self, GLuint buf, GLenum modeRGB, GLenum modeAlpha)
{
    GET_CONTEXT;
    ctx->glBlendEquationSeparateiEXTFunc(ctx->GetGLESv2Encoder(self), buf, modeRGB, modeAlpha);
}

void GL2EncoderBase::glBlendFunciEXT_s(void *self, GLuint buf, GLenum src, GLenum dst)
{
    GET_CONTEXT;
    ctx->glBlendFunciEXTFunc(ctx->GetGLESv2Encoder(self), buf, src, dst);
}

void GL2EncoderBase::glBlendFuncSeparateiEXT_s(void *self, GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha,
    GLenum dstAlpha)
{
    GET_CONTEXT;
    ctx->glBlendFuncSeparateiEXTFunc(ctx->GetGLESv2Encoder(self), buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
}

void GL2EncoderBase::glColorMaskiEXT_s(void *self, GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a)
{
    GET_CONTEXT;
    ctx->glColorMaskiEXTFunc(ctx->GetGLESv2Encoder(self), index, r, g, b, a);
}

GLboolean GL2EncoderBase::glIsEnablediEXT_s(void *self, GLenum target, GLuint index)
{
    GET_CONTEXT;
    return ctx->glIsEnablediEXTFunc(ctx->GetGLESv2Encoder(self), target, index);
}

void GL2EncoderBase::glCopyImageSubDataEXT_s(void *self, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX,
    GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ,
    GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth)
{
    GET_CONTEXT;
    ctx->glCopyImageSubDataEXTFunc(ctx->GetGLESv2Encoder(self), srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName,
        dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
}

void GL2EncoderBase::glBlendBarrierKHR_s(void *self)
{
    GET_CONTEXT;
    ctx->glBlendBarrierKHRFunc(ctx->GetGLESv2Encoder(self));
}

void GL2EncoderBase::glTexParameterIivEXT_s(void *self, GLenum target, GLenum pname, const GLint *params)
{
    GET_CONTEXT;
    ctx->glTexParameterIivEXTFunc(ctx->GetGLESv2Encoder(self), target, pname, params);
}

void GL2EncoderBase::glTexParameterIuivEXT_s(void *self, GLenum target, GLenum pname, const GLuint *params)
{
    GET_CONTEXT;
    ctx->glTexParameterIuivEXTFunc(ctx->GetGLESv2Encoder(self), target, pname, params);
}

void GL2EncoderBase::glGetTexParameterIivEXT_s(void *self, GLenum target, GLenum pname, GLint *params)
{
    GET_CONTEXT;
    ctx->glGetTexParameterIivEXTFunc(ctx->GetGLESv2Encoder(self), target, pname, params);
}

void GL2EncoderBase::glGetTexParameterIuivEXT_s(void *self, GLenum target, GLenum pname, GLuint *params)
{
    GET_CONTEXT;
    ctx->glGetTexParameterIuivEXTFunc(ctx->GetGLESv2Encoder(self), target, pname, params);
}

void GL2EncoderBase::glSamplerParameterIivEXT_s(void *self, GLuint sampler, GLenum pname, const GLint *param)
{
    GET_CONTEXT;
    ctx->glSamplerParameterIivEXTFunc(ctx->GetGLESv2Encoder(self), sampler, pname, param);
}

void GL2EncoderBase::glSamplerParameterIuivEXT_s(void *self, GLuint sampler, GLenum pname, const GLuint *param)
{
    GET_CONTEXT;
    ctx->glSamplerParameterIuivEXTFunc(ctx->GetGLESv2Encoder(self), sampler, pname, param);
}

void GL2EncoderBase::glGetSamplerParameterIivEXT_s(void *self, GLuint sampler, GLenum pname, GLint *params)
{
    GET_CONTEXT;
    ctx->glGetSamplerParameterIivEXTFunc(ctx->GetGLESv2Encoder(self), sampler, pname, params);
}

void GL2EncoderBase::glGetSamplerParameterIuivEXT_s(void *self, GLuint sampler, GLenum pname, GLuint *params)
{
    GET_CONTEXT;
    ctx->glGetSamplerParameterIuivEXTFunc(ctx->GetGLESv2Encoder(self), sampler, pname, params);
}


void GL2EncoderBase::glVertexAttribPointerData_s(void *self, GLuint indx, GLint size, GLenum type, GLboolean normalized,
    GLsizei stride, void *data, GLuint datalen)
{
    GET_CONTEXT;
    ctx->glVertexAttribPointerDataFunc(ctx->GetGLESv2Encoder(self), indx, size, type, normalized, stride, data,
        datalen);
}

void GL2EncoderBase::glVertexAttribPointerOffset_s(void *self, GLuint indx, GLint size, GLenum type,
    GLboolean normalized, GLsizei stride, GLuint offset)
{
    GET_CONTEXT;
    ctx->glVertexAttribPointerOffsetFunc(ctx->GetGLESv2Encoder(self), indx, size, type, normalized, stride, offset);
}

void GL2EncoderBase::glDrawElementsOffset_s(void *self, GLenum mode, GLsizei count, GLenum type, GLuint offset)
{
    GET_CONTEXT;
    ctx->glDrawElementsOffsetFunc(ctx->GetGLESv2Encoder(self), mode, count, type, offset);
}

void GL2EncoderBase::glDrawElementsData_s(void *self, GLenum mode, GLsizei count, GLenum type, void *data,
    GLuint datalen)
{
    GET_CONTEXT;
    ctx->glDrawElementsDataFunc(ctx->GetGLESv2Encoder(self), mode, count, type, data, datalen);
}

void GL2EncoderBase::glGetCompressedTextureFormats_s(void *self, int count, GLint *formats)
{
    GET_CONTEXT;
    ctx->glGetCompressedTextureFormatsFunc(ctx->GetGLESv2Encoder(self), count, formats);
}

void GL2EncoderBase::glShaderString_s(void *self, GLuint shader, const GLchar *string, GLsizei len)
{
    GET_CONTEXT;
    ctx->glShaderStringFunc(ctx->GetGLESv2Encoder(self), shader, string, len);
}

int GL2EncoderBase::glFinishRoundTrip_s(void *self)
{
    GET_CONTEXT;
    return ctx->glFinishRoundTripFunc(ctx->GetGLESv2Encoder(self));
}

void GL2EncoderBase::glMapBufferRangeAEMU_s(void *self, GLenum target, GLintptr offset, GLsizeiptr length,
    GLbitfield access, void *mapped)
{
    GET_CONTEXT;
    ctx->glMapBufferRangeAEMUFunc(ctx->GetGLESv2Encoder(self), target, offset, length, access, mapped);
}

void GL2EncoderBase::glUnmapBufferAEMU_s(void *self, GLenum target, GLintptr offset, GLsizeiptr length,
    GLbitfield access, void *guest_buffer, GLboolean *out_res)
{
    GET_CONTEXT;
    ctx->glUnmapBufferAEMUFunc(ctx->GetGLESv2Encoder(self), target, offset, length, access, guest_buffer, out_res);
}

void GL2EncoderBase::glFlushMappedBufferRangeAEMU_s(void *self, GLenum target, GLintptr offset, GLsizeiptr length,
    GLbitfield access, void *guest_buffer)
{
    GET_CONTEXT;
    ctx->glFlushMappedBufferRangeAEMUFunc(ctx->GetGLESv2Encoder(self), target, offset, length, access, guest_buffer);
}

void GL2EncoderBase::glReadPixelsOffsetAEMU_s(void *self, GLint x, GLint y, GLsizei width, GLsizei height,
    GLenum format, GLenum type, GLuint offset)
{
    GET_CONTEXT;
    ctx->glReadPixelsOffsetAEMUFunc(ctx->GetGLESv2Encoder(self), x, y, width, height, format, type, offset);
}

void GL2EncoderBase::glCompressedTexImage2DOffsetAEMU_s(void *self, GLenum target, GLint level, GLenum internalformat,
    GLsizei width, GLsizei height, GLint border, GLsizei imageSize, GLuint offset)
{
    GET_CONTEXT;
    ctx->glCompressedTexImage2DOffsetAEMUFunc(ctx->GetGLESv2Encoder(self), target, level, internalformat, width, height,
        border, imageSize, offset);
}

void GL2EncoderBase::glCompressedTexSubImage2DOffsetAEMU_s(void *self, GLenum target, GLint level, GLint xoffset,
    GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, GLuint offset)
{
    GET_CONTEXT;
    ctx->glCompressedTexSubImage2DOffsetAEMUFunc(ctx->GetGLESv2Encoder(self), target, level, xoffset, yoffset, width,
        height, format, imageSize, offset);
}

void GL2EncoderBase::glTexImage2DOffsetAEMU_s(void *self, GLenum target, GLint level, GLint internalformat,
    GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, GLuint offset)
{
    GET_CONTEXT;
    ctx->glTexImage2DOffsetAEMUFunc(ctx->GetGLESv2Encoder(self), target, level, internalformat, width, height, border,
        format, type, offset);
}

void GL2EncoderBase::glTexSubImage2DOffsetAEMU_s(void *self, GLenum target, GLint level, GLint xoffset, GLint yoffset,
    GLsizei width, GLsizei height, GLenum format, GLenum type, GLuint offset)
{
    GET_CONTEXT;
    ctx->glTexSubImage2DOffsetAEMUFunc(ctx->GetGLESv2Encoder(self), target, level, xoffset, yoffset, width, height,
        format, type, offset);
}

void GL2EncoderBase::glGetUniformIndicesAEMU_s(void *self, GLuint program, GLsizei uniformCount,
    const GLchar *packedUniformNames, GLsizei packedLen, GLuint *uniformIndices)
{
    GET_CONTEXT;
    ctx->glGetUniformIndicesAEMUFunc(ctx->GetGLESv2Encoder(self), program, uniformCount, packedUniformNames, packedLen,
        uniformIndices);
}

void GL2EncoderBase::glVertexAttribIPointerOffsetAEMU_s(void *self, GLuint index, GLint size, GLenum type,
    GLsizei stride, GLuint offset)
{
    GET_CONTEXT;
    ctx->glVertexAttribIPointerOffsetAEMUFunc(ctx->GetGLESv2Encoder(self), index, size, type, stride, offset);
}

void GL2EncoderBase::glVertexAttribIPointerDataAEMU_s(void *self, GLuint index, GLint size, GLenum type, GLsizei stride,
    void *data, GLuint datalen)
{
    GET_CONTEXT;
    ctx->glVertexAttribIPointerDataAEMUFunc(ctx->GetGLESv2Encoder(self), index, size, type, stride, data, datalen);
}

void GL2EncoderBase::glDrawElementsInstancedDataAEMU_s(void *self, GLenum mode, GLsizei count, GLenum type,
    const void *indices, GLsizei primcount, GLsizei datalen)
{
    GET_CONTEXT;
    ctx->glDrawElementsInstancedDataAEMUFunc(ctx->GetGLESv2Encoder(self), mode, count, type, indices, primcount,
        datalen);
}

void GL2EncoderBase::glDrawElementsInstancedOffsetAEMU_s(void *self, GLenum mode, GLsizei count, GLenum type,
    GLuint offset, GLsizei primcount)
{
    GET_CONTEXT;
    ctx->glDrawElementsInstancedOffsetAEMUFunc(ctx->GetGLESv2Encoder(self), mode, count, type, offset, primcount);
}

void GL2EncoderBase::glDrawRangeElementsDataAEMU_s(void *self, GLenum mode, GLuint start, GLuint end, GLsizei count,
    GLenum type, const GLvoid *indices, GLsizei datalen)
{
    GET_CONTEXT;
    ctx->glDrawRangeElementsDataAEMUFunc(ctx->GetGLESv2Encoder(self), mode, start, end, count, type, indices, datalen);
}

void GL2EncoderBase::glDrawRangeElementsOffsetAEMU_s(void *self, GLenum mode, GLuint start, GLuint end, GLsizei count,
    GLenum type, GLuint offset)
{
    GET_CONTEXT;
    ctx->glDrawRangeElementsOffsetAEMUFunc(ctx->GetGLESv2Encoder(self), mode, start, end, count, type, offset);
}

uint64_t GL2EncoderBase::glFenceSyncAEMU_s(void *self, GLenum condition, GLbitfield flags)
{
    GET_CONTEXT;
    return ctx->glFenceSyncAEMUFunc(ctx->GetGLESv2Encoder(self), condition, flags);
}

GLenum GL2EncoderBase::glClientWaitSyncAEMU_s(void *self, uint64_t wait_on, GLbitfield flags, GLuint64 timeout)
{
    GET_CONTEXT;
    return ctx->glClientWaitSyncAEMUFunc(ctx->GetGLESv2Encoder(self), wait_on, flags, timeout);
}

void GL2EncoderBase::glWaitSyncAEMU_s(void *self, uint64_t wait_on, GLbitfield flags, GLuint64 timeout)
{
    GET_CONTEXT;
    ctx->glWaitSyncAEMUFunc(ctx->GetGLESv2Encoder(self), wait_on, flags, timeout);
}

void GL2EncoderBase::glDeleteSyncAEMU_s(void *self, uint64_t to_delete)
{
    GET_CONTEXT;
    ctx->glDeleteSyncAEMUFunc(ctx->GetGLESv2Encoder(self), to_delete);
}

GLboolean GL2EncoderBase::glIsSyncAEMU_s(void *self, uint64_t sync)
{
    GET_CONTEXT;
    return ctx->glIsSyncAEMUFunc(ctx->GetGLESv2Encoder(self), sync);
}

void GL2EncoderBase::glGetSyncivAEMU_s(void *self, uint64_t sync, GLenum pname, GLsizei bufSize, GLsizei *length,
    GLint *values)
{
    GET_CONTEXT;
    ctx->glGetSyncivAEMUFunc(ctx->GetGLESv2Encoder(self), sync, pname, bufSize, length, values);
}

void GL2EncoderBase::glTransformFeedbackVaryingsAEMU_s(void *self, GLuint program, GLsizei count,
    const char *packedVaryings, GLuint packedVaryingsLen, GLenum bufferMode)
{
    GET_CONTEXT;
    ctx->glTransformFeedbackVaryingsAEMUFunc(ctx->GetGLESv2Encoder(self), program, count, packedVaryings,
        packedVaryingsLen, bufferMode);
}

void GL2EncoderBase::glTexImage3DOffsetAEMU_s(void *self, GLenum target, GLint level, GLint internalFormat,
    GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, GLuint offset)
{
    GET_CONTEXT;
    ctx->glTexImage3DOffsetAEMUFunc(ctx->GetGLESv2Encoder(self), target, level, internalFormat, width, height, depth,
        border, format, type, offset);
}

void GL2EncoderBase::glTexSubImage3DOffsetAEMU_s(void *self, GLenum target, GLint level, GLint xoffset, GLint yoffset,
    GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLuint offset)
{
    GET_CONTEXT;
    ctx->glTexSubImage3DOffsetAEMUFunc(ctx->GetGLESv2Encoder(self), target, level, xoffset, yoffset, zoffset, width,
        height, depth, format, type, offset);
}

void GL2EncoderBase::glCompressedTexImage3DOffsetAEMU_s(void *self, GLenum target, GLint level, GLenum internalformat,
    GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, GLuint offset)
{
    GET_CONTEXT;
    ctx->glCompressedTexImage3DOffsetAEMUFunc(ctx->GetGLESv2Encoder(self), target, level, internalformat, width, height,
        depth, border, imageSize, offset);
}

void GL2EncoderBase::glCompressedTexSubImage3DOffsetAEMU_s(void *self, GLenum target, GLint level, GLint xoffset,
    GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize,
    GLuint data)
{
    GET_CONTEXT;
    ctx->glCompressedTexSubImage3DOffsetAEMUFunc(ctx->GetGLESv2Encoder(self), target, level, xoffset, yoffset, zoffset,
        width, height, depth, format, imageSize, data);
}

GLuint GL2EncoderBase::glCreateShaderProgramvAEMU_s(void *self, GLenum type, GLsizei count, const char *packedStrings,
    GLuint packedLen)
{
    GET_CONTEXT;
    return ctx->glCreateShaderProgramvAEMUFunc(ctx->GetGLESv2Encoder(self), type, count, packedStrings, packedLen);
}

void GL2EncoderBase::glDrawArraysIndirectDataAEMU_s(void *self, GLenum mode, const void *indirect, GLuint datalen)
{
    GET_CONTEXT;
    ctx->glDrawArraysIndirectDataAEMUFunc(ctx->GetGLESv2Encoder(self), mode, indirect, datalen);
}

void GL2EncoderBase::glDrawArraysIndirectOffsetAEMU_s(void *self, GLenum mode, GLuint offset)
{
    GET_CONTEXT;
    ctx->glDrawArraysIndirectOffsetAEMUFunc(ctx->GetGLESv2Encoder(self), mode, offset);
}

void GL2EncoderBase::glDrawElementsIndirectDataAEMU_s(void *self, GLenum mode, GLenum type, const void *indirect,
    GLuint datalen)
{
    GET_CONTEXT;
    ctx->glDrawElementsIndirectDataAEMUFunc(ctx->GetGLESv2Encoder(self), mode, type, indirect, datalen);
}

void GL2EncoderBase::glDrawElementsIndirectOffsetAEMU_s(void *self, GLenum mode, GLenum type, GLuint offset)
{
    GET_CONTEXT;
    ctx->glDrawElementsIndirectOffsetAEMUFunc(ctx->GetGLESv2Encoder(self), mode, type, offset);
}

void GL2EncoderBase::glUniformLayout_s(void *self, GLuint program)
{
    GET_CONTEXT;
    ctx->glUniformLayoutFunc(ctx->GetGLESv2Encoder(self), program);
}
