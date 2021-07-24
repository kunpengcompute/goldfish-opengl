/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2017-2020. All rights reserved.
 * Description: OpenGL ES API entry list of Encoder
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the Apache License version 2
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * Apache License for more details.
 */
#ifndef GLES_API_ENTRY_LIST_H
#define GLES_API_ENTRY_LIST_H
#undef GL_ES_VERSION_2_0
#include "GLES3/gl32.h"
#include "GLES2/gl2ext.h"

// define extra OpenGLES API entries which don't include in "GLES3/gl32.h" and "GLES2/gl2ext.h"
using PFNGLVERTEXATTRIBPOINTERDATAPROC = void(*)(void*, GLuint, GLint, GLenum, GLboolean, GLsizei,
                                                            const void*, GLuint);
using PFNGLVERTEXATTRIBPOINTEROFFSETPROC = void(*)(void*, GLuint, GLint, GLenum, GLboolean, GLsizei, GLuint);
using PFNGLDRAWELEMENTSOFFSETPROC = void(*)(void*, GLenum, GLsizei, GLenum, GLuint);
using PFNGLDRAWELEMENTSDATAPROC = void(*)(void*, GLenum, GLsizei, GLenum, const void*, GLuint);
using PFNGLGETCOMPRESSEDTEXTUREFORMATSPROC = void(*)(void*, int, GLint*);
using PFNGLSHADERSTRINGPROC = void(*)(void*, GLuint, const GLchar*, GLsizei);
using PFNGLFINISHROUNDTRIPPROC = int(*)(void*);
using PFNGLMAPBUFFERRANGEAEMUPROC = void(*)(void*, GLenum, GLintptr, GLsizeiptr, GLbitfield, void*);
using PFNGLUNMAPBUFFERAEMUPROC = void(*)(void*, GLenum, GLintptr, GLsizeiptr, GLbitfield, void*, GLboolean*);
using PFNGLFLUSHMAPPEDBUFFERRANGEAEMUPROC = void(*)(void*, GLenum, GLintptr, GLsizeiptr, GLbitfield, void*);
using PFNGLREADPIXELSOFFSETAEMUPROC = void(*)(void*, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLuint);
using PFNGLCOMPRESSEDTEXIMAGE2DOFFSETAEMUPROC = void(*)(void*, GLenum, GLint, GLenum, GLsizei,
                                                        GLsizei, GLint, GLsizei, GLuint);
using PFNGLCOMPRESSEDTEXSUBIMAGE2DOFFSETAEMUPROC = void(*)(void*, GLenum, GLint, GLint, GLint,
                                                           GLsizei, GLsizei, GLenum, GLsizei, GLuint);
using PFNGLTEXIMAGE2DOFFSETAEMUPROC = void(*)(void*, GLenum, GLint, GLint, GLsizei,
                                              GLsizei, GLint, GLenum, GLenum, GLuint);
using PFNGLTEXSUBIMAGE2DOFFSETAEMUPROC = void(*)(void*, GLenum, GLint, GLint, GLint, GLsizei,
                                                 GLsizei, GLenum, GLenum, GLuint);
using PFNGLGETUNIFORMINDICESAEMUPROC = void(*)(void*, GLuint, GLsizei, const GLchar*, GLsizei, GLuint*);
using PFNGLVERTEXATTRIBIPOINTEROFFSETAEMUPROC = void(*)(void*, GLuint, GLint, GLenum, GLsizei, GLuint);
using PFNGLVERTEXATTRIBIPOINTERDATAAEMUPROC = void(*)(void*, GLuint, GLint, GLenum, GLsizei, void*, GLuint);
using PFNGLDRAWELEMENTSINSTANCEDDATAAEMUPROC = void(*)(void*, GLenum, GLsizei, GLenum,
                                                       const void*, GLsizei, GLsizei);
using PFNGLDRAWELEMENTSINSTANCEDOFFSETAEMUPROC = void(*)(void*, GLenum, GLsizei, GLenum, GLuint, GLsizei);
using PFNGLDRAWRANGEELEMENTSDATAAEMUPROC = void(*)(void*, GLenum, GLuint, GLuint, GLsizei,
                                                   GLenum, const GLvoid*, GLsizei);
using PFNGLDRAWRANGEELEMENTSOFFSETAEMUPROC = void(*)(void*, GLenum, GLuint, GLuint, GLsizei, GLenum, GLuint);
using PFNGLFENCESYNCAEMUPROC = uint64_t(*)(void*, GLenum, GLbitfield);
using PFNGLCLIENTWAITSYNCAEMUPROC = GLenum(*)(void*, uint64_t, GLbitfield, GLuint64);
using PFNGLWAITSYNCAEMUPROC = void(*)(void*, uint64_t, GLbitfield, GLuint64);
using PFNGLDELETESYNCAEMUPROC = void(*)(void*, uint64_t);
using PFNGLISSYNCAEMUPROC = GLboolean(*)(void*, uint64_t);
using PFNGLGETSYNCIVAEMUPROC = void(*)(void*, uint64_t, GLenum, GLsizei, GLsizei*, GLint*);
using PFNGLTRANSFORMFEEDBACKVARYINGSAEMUPROC = void(*)(void*, GLuint, GLsizei, const char*, GLuint, GLenum);
using PFNGLTEXIMAGE3DOFFSETAEMUPROC = void(*)(void*, GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei,
                                              GLint, GLenum, GLenum, GLuint);
using PFNGLTEXSUBIMAGE3DOFFSETAEMUPROC = void(*)(void*, GLenum, GLint, GLint, GLint, GLint,
                                                 GLsizei, GLsizei, GLsizei, GLenum, GLenum, GLuint);
using PFNGLCOMPRESSEDTEXIMAGE3DOFFSETAEMUPROC = void(*)(void*, GLenum, GLint, GLenum, GLsizei,
                                                        GLsizei, GLsizei, GLint, GLsizei, GLuint);
using PFNGLCOMPRESSEDTEXSUBIMAGE3DOFFSETAEMUPROC = void(*)(void*, GLenum, GLint, GLint, GLint, GLint,
                                                           GLsizei, GLsizei, GLsizei, GLenum, GLsizei, GLuint);
using PFNGLCREATESHADERPROGRAMVAEMUPROC = GLuint(*)(void*, GLenum, GLsizei, const char*, GLuint);
using PFNGLDRAWARRAYSINDIRECTDATAAEMUPROC = void(*)(void*, GLenum, const void*, GLuint);
using PFNGLDRAWARRAYSINDIRECTOFFSETAEMUPROC = void(*)(void*, GLenum, GLuint);
using PFNGLDRAWELEMENTSINDIRECTDATAAEMUPROC = void(*)(void*, GLenum, GLenum, const void*, GLuint);
using PFNGLDRAWELEMENTSINDIRECTOFFSETAEMUPROC = void(*)(void*, GLenum, GLenum, GLuint);
using PFNGLCREATEPROGRAMTRACEPROC = void(*)(void*, GLuint);
using PFNGLCREATESHADERTRACEPROC = void(*)(void*, GLenum, GLuint);
using PFNGLGENBUFFERSTRACEPROC = void(*)(void*, GLsizei, GLuint*);
using PFNGLGENFRAMEBUFFERSTRACEPROC = void(*)(void*, GLsizei, GLuint*);
using PFNGLGENRENDERBUFFERSTRACEPROC = void(*)(void*, GLsizei, GLuint*);
using PFNGLGENTEXTURESTRACEPROC = void(*)(void*, GLsizei, GLuint*);
using PFNGLGENVERTEXARRAYSTRACEPROC = void(*)(void*, GLsizei, GLuint*);
using PFNGLFENCESYNCTRACEPROC = void(*)(void*, GLenum, GLbitfield, GLsync);
using PFNGLGENTRANSFORMFEEDBACKSTRACEPROC = void(*)(void*, GLsizei, GLuint*);
using PFNGLGENSAMPLERSDECPROC = void(*)(void*, GLsizei, GLuint*);
using PFNGLGENQUERIESDECPROC = void(*)(void*, GLsizei, GLuint*);
using PFNGLGETUNIFORMLOCATIPNTRACEPROC = void(*)(void*, GLuint, const GLchar*, int);
using PFNGLGETUNIFORMBLOCKINDEXTRACEPROC = void(*)(void*, GLuint, const GLchar*, GLuint);
using PFNGLGETUNIFORMINDICESAEMUTRACEPROC = void(*)(void*, GLuint, GLsizei, const GLchar*, GLsizei, GLuint*);
using PFNGLGETATTRIBLOCATIONTRACEPROC = void(*)(void*, GLuint, const GLchar*, int);
using PFNGLBINDBUFFERDRACOPROC = void(*)(void*, GLenum, GLuint);
using PFNGLBUFFERDATADRACOPROC = void(*)(void*, GLenum, GLsizeiptr, const GLvoid*, GLenum);
using PFNGLBUFFERSUBDATADRACOPROC = void(*)(void*, GLenum, GLintptr, GLsizeiptr, const GLvoid*);
using PFNGLVERTEXATTRIBPOINTEROFFSETDRACOPROC = void(*)(void*, GLuint, GLint, GLenum, GLboolean, GLsizei, GLuint);
using PFNGLDRAWELEMENTSOFFSETDRACOPROC = void(*)(void*, GLenum, GLsizei, GLenum, GLuint);
using PFNGLUNIFORMLAYOUTPROC = void(*)(void*, GLuint);


// declare GLESEntryTypeGenerator is a template struct
template<typename T>
struct GLESEntryTypeGenerator;

// use template struct to generate encoder API signature with context automatically deducing from native GLES API
template<typename R, typename... Args>
struct GLESEntryTypeGenerator<R(*)(Args...)> {
    using GLESEntryType = R(*)(void* ctx, Args...);
};

/**
 * @brief: declare VmiGLESv2Encoder's function pointer member whose type deducing from native GLES API
 * @param [in]GLESNativeEntryAPI: native GLES API type
 * @param [in]memberName: memberName of function pointer
 */
#define GLES_DECLARE_MEMBER_DEDUCE(GLESNativeEntryAPI, memberName) \
    GLESEntryTypeGenerator<GLESNativeEntryAPI>::GLESEntryType memberName = nullptr;

/**
 * @brief: declare VmiGLESv2Encoder's function pointer member whose type defined manually
 * @param [in]GLESExtraEntryAPI: native GLES API type
 * @param [in]memberName: memberName of function pointer
 */
#define GLES_DECLARE_MEMBER_MANUAL(GLESExtraEntryAPI, memberName) \
    GLESExtraEntryAPI memberName = nullptr;

/**
 * @brief: apply "macro" operation on each function pointer member for all the native openGLES API type
 * @param [in]macro: the operation with each OpenGLES API type and function pointer member
 */
#define FOREACH_OPENGL_DEDUCE(macro) \
    macro(PFNGLACTIVETEXTUREPROC, glActiveTexture) \
    macro(PFNGLATTACHSHADERPROC, glAttachShader) \
    macro(PFNGLBINDATTRIBLOCATIONPROC, glBindAttribLocation) \
    macro(PFNGLBINDBUFFERPROC, glBindBuffer) \
    macro(PFNGLBINDFRAMEBUFFERPROC, glBindFramebuffer) \
    macro(PFNGLBINDRENDERBUFFERPROC, glBindRenderbuffer) \
    macro(PFNGLBINDTEXTUREPROC, glBindTexture) \
    macro(PFNGLBLENDCOLORPROC, glBlendColor) \
    macro(PFNGLBLENDEQUATIONPROC, glBlendEquation) \
    macro(PFNGLBLENDEQUATIONSEPARATEPROC, glBlendEquationSeparate) \
    macro(PFNGLBLENDFUNCPROC, glBlendFunc) \
    macro(PFNGLBLENDFUNCSEPARATEPROC, glBlendFuncSeparate) \
    macro(PFNGLBUFFERDATAPROC, glBufferData) \
    macro(PFNGLBUFFERSUBDATAPROC, glBufferSubData) \
    macro(PFNGLCHECKFRAMEBUFFERSTATUSPROC, glCheckFramebufferStatus) \
    macro(PFNGLCLEARPROC, glClear) \
    macro(PFNGLCLEARCOLORPROC, glClearColor) \
    macro(PFNGLCLEARDEPTHFPROC, glClearDepthf) \
    macro(PFNGLCLEARSTENCILPROC, glClearStencil) \
    macro(PFNGLCOLORMASKPROC, glColorMask) \
    macro(PFNGLCOMPILESHADERPROC, glCompileShader) \
    macro(PFNGLCOMPRESSEDTEXIMAGE2DPROC, glCompressedTexImage2D) \
    macro(PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC, glCompressedTexSubImage2D) \
    macro(PFNGLCOPYTEXIMAGE2DPROC, glCopyTexImage2D) \
    macro(PFNGLCOPYTEXSUBIMAGE2DPROC, glCopyTexSubImage2D) \
    macro(PFNGLCREATEPROGRAMPROC, glCreateProgram) \
    macro(PFNGLCREATESHADERPROC, glCreateShader) \
    macro(PFNGLCULLFACEPROC, glCullFace) \
    macro(PFNGLDELETEBUFFERSPROC, glDeleteBuffers) \
    macro(PFNGLDELETEFRAMEBUFFERSPROC, glDeleteFramebuffers) \
    macro(PFNGLDELETEPROGRAMPROC, glDeleteProgram) \
    macro(PFNGLDELETERENDERBUFFERSPROC, glDeleteRenderbuffers) \
    macro(PFNGLDELETESHADERPROC, glDeleteShader) \
    macro(PFNGLDELETETEXTURESPROC, glDeleteTextures) \
    macro(PFNGLDEPTHFUNCPROC, glDepthFunc) \
    macro(PFNGLDEPTHMASKPROC, glDepthMask) \
    macro(PFNGLDEPTHRANGEFPROC, glDepthRangef) \
    macro(PFNGLDETACHSHADERPROC, glDetachShader) \
    macro(PFNGLDISABLEPROC, glDisable) \
    macro(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray) \
    macro(PFNGLDRAWARRAYSPROC, glDrawArrays) \
    macro(PFNGLDRAWELEMENTSPROC, glDrawElements) \
    macro(PFNGLENABLEPROC, glEnable) \
    macro(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray) \
    macro(PFNGLFINISHPROC, glFinish) \
    macro(PFNGLFLUSHPROC, glFlush) \
    macro(PFNGLFRAMEBUFFERRENDERBUFFERPROC, glFramebufferRenderbuffer) \
    macro(PFNGLFRAMEBUFFERTEXTURE2DPROC, glFramebufferTexture2D) \
    macro(PFNGLFRONTFACEPROC, glFrontFace) \
    macro(PFNGLGENBUFFERSPROC, glGenBuffers) \
    macro(PFNGLGENERATEMIPMAPPROC, glGenerateMipmap) \
    macro(PFNGLGENFRAMEBUFFERSPROC, glGenFramebuffers) \
    macro(PFNGLGENRENDERBUFFERSPROC, glGenRenderbuffers) \
    macro(PFNGLGENTEXTURESPROC, glGenTextures) \
    macro(PFNGLGETACTIVEATTRIBPROC, glGetActiveAttrib) \
    macro(PFNGLGETACTIVEUNIFORMPROC, glGetActiveUniform) \
    macro(PFNGLGETATTACHEDSHADERSPROC, glGetAttachedShaders) \
    macro(PFNGLGETATTRIBLOCATIONPROC, glGetAttribLocation) \
    macro(PFNGLGETBOOLEANVPROC, glGetBooleanv) \
    macro(PFNGLGETBUFFERPARAMETERIVPROC, glGetBufferParameteriv) \
    macro(PFNGLGETERRORPROC, glGetError) \
    macro(PFNGLGETFLOATVPROC, glGetFloatv) \
    macro(PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC, glGetFramebufferAttachmentParameteriv) \
    macro(PFNGLGETINTEGERVPROC, glGetIntegerv) \
    macro(PFNGLGETPROGRAMIVPROC, glGetProgramiv) \
    macro(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog) \
    macro(PFNGLGETRENDERBUFFERPARAMETERIVPROC, glGetRenderbufferParameteriv) \
    macro(PFNGLGETSHADERIVPROC, glGetShaderiv) \
    macro(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog) \
    macro(PFNGLGETSHADERPRECISIONFORMATPROC, glGetShaderPrecisionFormat) \
    macro(PFNGLGETSHADERSOURCEPROC, glGetShaderSource) \
    macro(PFNGLGETSTRINGPROC, glGetString) \
    macro(PFNGLGETTEXPARAMETERFVPROC, glGetTexParameterfv) \
    macro(PFNGLGETTEXPARAMETERIVPROC, glGetTexParameteriv) \
    macro(PFNGLGETUNIFORMFVPROC, glGetUniformfv) \
    macro(PFNGLGETUNIFORMIVPROC, glGetUniformiv) \
    macro(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation) \
    macro(PFNGLGETVERTEXATTRIBFVPROC, glGetVertexAttribfv) \
    macro(PFNGLGETVERTEXATTRIBIVPROC, glGetVertexAttribiv) \
    macro(PFNGLGETVERTEXATTRIBPOINTERVPROC, glGetVertexAttribPointerv) \
    macro(PFNGLHINTPROC, glHint) \
    macro(PFNGLISBUFFERPROC, glIsBuffer) \
    macro(PFNGLISENABLEDPROC, glIsEnabled) \
    macro(PFNGLISFRAMEBUFFERPROC, glIsFramebuffer) \
    macro(PFNGLISPROGRAMPROC, glIsProgram) \
    macro(PFNGLISRENDERBUFFERPROC, glIsRenderbuffer) \
    macro(PFNGLISSHADERPROC, glIsShader) \
    macro(PFNGLISTEXTUREPROC, glIsTexture) \
    macro(PFNGLLINEWIDTHPROC, glLineWidth) \
    macro(PFNGLLINKPROGRAMPROC, glLinkProgram) \
    macro(PFNGLPIXELSTOREIPROC, glPixelStorei) \
    macro(PFNGLPOLYGONOFFSETPROC, glPolygonOffset) \
    macro(PFNGLREADPIXELSPROC, glReadPixels) \
    macro(PFNGLRELEASESHADERCOMPILERPROC, glReleaseShaderCompiler) \
    macro(PFNGLRENDERBUFFERSTORAGEPROC, glRenderbufferStorage) \
    macro(PFNGLSAMPLECOVERAGEPROC, glSampleCoverage) \
    macro(PFNGLSCISSORPROC, glScissor) \
    macro(PFNGLSHADERBINARYPROC, glShaderBinary) \
    macro(PFNGLSHADERSOURCEPROC, glShaderSource) \
    macro(PFNGLSTENCILFUNCPROC, glStencilFunc) \
    macro(PFNGLSTENCILFUNCSEPARATEPROC, glStencilFuncSeparate) \
    macro(PFNGLSTENCILMASKPROC, glStencilMask) \
    macro(PFNGLSTENCILMASKSEPARATEPROC, glStencilMaskSeparate) \
    macro(PFNGLSTENCILOPPROC, glStencilOp) \
    macro(PFNGLSTENCILOPSEPARATEPROC, glStencilOpSeparate) \
    macro(PFNGLTEXIMAGE2DPROC, glTexImage2D) \
    macro(PFNGLTEXPARAMETERFPROC, glTexParameterf) \
    macro(PFNGLTEXPARAMETERFVPROC, glTexParameterfv) \
    macro(PFNGLTEXPARAMETERIPROC, glTexParameteri) \
    macro(PFNGLTEXPARAMETERIVPROC, glTexParameteriv) \
    macro(PFNGLTEXSUBIMAGE2DPROC, glTexSubImage2D) \
    macro(PFNGLUNIFORM1FPROC, glUniform1f) \
    macro(PFNGLUNIFORM1FVPROC, glUniform1fv) \
    macro(PFNGLUNIFORM1IPROC, glUniform1i) \
    macro(PFNGLUNIFORM1IVPROC, glUniform1iv) \
    macro(PFNGLUNIFORM2FPROC, glUniform2f) \
    macro(PFNGLUNIFORM2FVPROC, glUniform2fv) \
    macro(PFNGLUNIFORM2IPROC, glUniform2i) \
    macro(PFNGLUNIFORM2IVPROC, glUniform2iv) \
    macro(PFNGLUNIFORM3FPROC, glUniform3f) \
    macro(PFNGLUNIFORM3FVPROC, glUniform3fv) \
    macro(PFNGLUNIFORM3IPROC, glUniform3i) \
    macro(PFNGLUNIFORM3IVPROC, glUniform3iv) \
    macro(PFNGLUNIFORM4FPROC, glUniform4f) \
    macro(PFNGLUNIFORM4FVPROC, glUniform4fv) \
    macro(PFNGLUNIFORM4IPROC, glUniform4i) \
    macro(PFNGLUNIFORM4IVPROC, glUniform4iv) \
    macro(PFNGLUNIFORMMATRIX2FVPROC, glUniformMatrix2fv) \
    macro(PFNGLUNIFORMMATRIX3FVPROC, glUniformMatrix3fv) \
    macro(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv) \
    macro(PFNGLUSEPROGRAMPROC, glUseProgram) \
    macro(PFNGLVALIDATEPROGRAMPROC, glValidateProgram) \
    macro(PFNGLVERTEXATTRIB1FPROC, glVertexAttrib1f) \
    macro(PFNGLVERTEXATTRIB1FVPROC, glVertexAttrib1fv) \
    macro(PFNGLVERTEXATTRIB2FPROC, glVertexAttrib2f) \
    macro(PFNGLVERTEXATTRIB2FVPROC, glVertexAttrib2fv) \
    macro(PFNGLVERTEXATTRIB3FPROC, glVertexAttrib3f) \
    macro(PFNGLVERTEXATTRIB3FVPROC, glVertexAttrib3fv) \
    macro(PFNGLVERTEXATTRIB4FPROC, glVertexAttrib4f) \
    macro(PFNGLVERTEXATTRIB4FVPROC, glVertexAttrib4fv) \
    macro(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer) \
    macro(PFNGLVIEWPORTPROC, glViewport) \
    macro(PFNGLEGLIMAGETARGETTEXTURE2DOESPROC, glEGLImageTargetTexture2DOES) \
    macro(PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC, glEGLImageTargetRenderbufferStorageOES) \
    macro(PFNGLGETPROGRAMBINARYOESPROC, glGetProgramBinaryOES) \
    macro(PFNGLPROGRAMBINARYOESPROC, glProgramBinaryOES) \
    macro(PFNGLMAPBUFFEROESPROC, glMapBufferOES) \
    macro(PFNGLUNMAPBUFFEROESPROC, glUnmapBufferOES) \
    macro(PFNGLTEXIMAGE3DOESPROC, glTexImage3DOES) \
    macro(PFNGLTEXSUBIMAGE3DOESPROC, glTexSubImage3DOES) \
    macro(PFNGLCOPYTEXSUBIMAGE3DOESPROC, glCopyTexSubImage3DOES) \
    macro(PFNGLCOMPRESSEDTEXIMAGE3DOESPROC, glCompressedTexImage3DOES) \
    macro(PFNGLCOMPRESSEDTEXSUBIMAGE3DOESPROC, glCompressedTexSubImage3DOES) \
    macro(PFNGLFRAMEBUFFERTEXTURE3DOESPROC, glFramebufferTexture3DOES) \
    macro(PFNGLBINDVERTEXARRAYOESPROC, glBindVertexArrayOES) \
    macro(PFNGLDELETEVERTEXARRAYSOESPROC, glDeleteVertexArraysOES) \
    macro(PFNGLGENVERTEXARRAYSOESPROC, glGenVertexArraysOES) \
    macro(PFNGLISVERTEXARRAYOESPROC, glIsVertexArrayOES) \
    macro(PFNGLDISCARDFRAMEBUFFEREXTPROC, glDiscardFramebufferEXT) \
    macro(PFNGLMULTIDRAWARRAYSEXTPROC, glMultiDrawArraysEXT) \
    macro(PFNGLMULTIDRAWELEMENTSEXTPROC, glMultiDrawElementsEXT) \
    macro(PFNGLGETPERFMONITORGROUPSAMDPROC, glGetPerfMonitorGroupsAMD) \
    macro(PFNGLGETPERFMONITORCOUNTERSAMDPROC, glGetPerfMonitorCountersAMD) \
    macro(PFNGLGETPERFMONITORGROUPSTRINGAMDPROC, glGetPerfMonitorGroupStringAMD) \
    macro(PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC, glGetPerfMonitorCounterStringAMD) \
    macro(PFNGLGETPERFMONITORCOUNTERINFOAMDPROC, glGetPerfMonitorCounterInfoAMD) \
    macro(PFNGLGENPERFMONITORSAMDPROC, glGenPerfMonitorsAMD) \
    macro(PFNGLDELETEPERFMONITORSAMDPROC, glDeletePerfMonitorsAMD) \
    macro(PFNGLSELECTPERFMONITORCOUNTERSAMDPROC, glSelectPerfMonitorCountersAMD) \
    macro(PFNGLBEGINPERFMONITORAMDPROC, glBeginPerfMonitorAMD) \
    macro(PFNGLENDPERFMONITORAMDPROC, glEndPerfMonitorAMD) \
    macro(PFNGLGETPERFMONITORCOUNTERDATAAMDPROC, glGetPerfMonitorCounterDataAMD) \
    macro(PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC, glRenderbufferStorageMultisampleIMG) \
    macro(PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC, glFramebufferTexture2DMultisampleIMG) \
    macro(PFNGLDELETEFENCESNVPROC, glDeleteFencesNV) \
    macro(PFNGLGENFENCESNVPROC, glGenFencesNV) \
    macro(PFNGLISFENCENVPROC, glIsFenceNV) \
    macro(PFNGLTESTFENCENVPROC, glTestFenceNV) \
    macro(PFNGLGETFENCEIVNVPROC, glGetFenceivNV) \
    macro(PFNGLFINISHFENCENVPROC, glFinishFenceNV) \
    macro(PFNGLSETFENCENVPROC, glSetFenceNV) \
    macro(PFNGLCOVERAGEMASKNVPROC, glCoverageMaskNV) \
    macro(PFNGLCOVERAGEOPERATIONNVPROC, glCoverageOperationNV) \
    macro(PFNGLGETDRIVERCONTROLSQCOMPROC, glGetDriverControlsQCOM) \
    macro(PFNGLGETDRIVERCONTROLSTRINGQCOMPROC, glGetDriverControlStringQCOM) \
    macro(PFNGLENABLEDRIVERCONTROLQCOMPROC, glEnableDriverControlQCOM) \
    macro(PFNGLDISABLEDRIVERCONTROLQCOMPROC, glDisableDriverControlQCOM) \
    macro(PFNGLEXTGETTEXTURESQCOMPROC, glExtGetTexturesQCOM) \
    macro(PFNGLEXTGETBUFFERSQCOMPROC, glExtGetBuffersQCOM) \
    macro(PFNGLEXTGETRENDERBUFFERSQCOMPROC, glExtGetRenderbuffersQCOM) \
    macro(PFNGLEXTGETFRAMEBUFFERSQCOMPROC, glExtGetFramebuffersQCOM) \
    macro(PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC, glExtGetTexLevelParameterivQCOM) \
    macro(PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC, glExtTexObjectStateOverrideiQCOM) \
    macro(PFNGLEXTGETTEXSUBIMAGEQCOMPROC, glExtGetTexSubImageQCOM) \
    macro(PFNGLEXTGETBUFFERPOINTERVQCOMPROC, glExtGetBufferPointervQCOM) \
    macro(PFNGLEXTGETSHADERSQCOMPROC, glExtGetShadersQCOM) \
    macro(PFNGLEXTGETPROGRAMSQCOMPROC, glExtGetProgramsQCOM) \
    macro(PFNGLEXTISPROGRAMBINARYQCOMPROC, glExtIsProgramBinaryQCOM) \
    macro(PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC, glExtGetProgramBinarySourceQCOM) \
    macro(PFNGLSTARTTILINGQCOMPROC, glStartTilingQCOM) \
    macro(PFNGLENDTILINGQCOMPROC, glEndTilingQCOM) \
    macro(PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays) \
    macro(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray) \
    macro(PFNGLDELETEVERTEXARRAYSPROC, glDeleteVertexArrays) \
    macro(PFNGLISVERTEXARRAYPROC, glIsVertexArray) \
    macro(PFNGLMAPBUFFERRANGEPROC, glMapBufferRange) \
    macro(PFNGLUNMAPBUFFERPROC, glUnmapBuffer) \
    macro(PFNGLFLUSHMAPPEDBUFFERRANGEPROC, glFlushMappedBufferRange) \
    macro(PFNGLBINDBUFFERRANGEPROC, glBindBufferRange) \
    macro(PFNGLBINDBUFFERBASEPROC, glBindBufferBase) \
    macro(PFNGLCOPYBUFFERSUBDATAPROC, glCopyBufferSubData) \
    macro(PFNGLCLEARBUFFERIVPROC, glClearBufferiv) \
    macro(PFNGLCLEARBUFFERUIVPROC, glClearBufferuiv) \
    macro(PFNGLCLEARBUFFERFVPROC, glClearBufferfv) \
    macro(PFNGLCLEARBUFFERFIPROC, glClearBufferfi) \
    macro(PFNGLGETBUFFERPARAMETERI64VPROC, glGetBufferParameteri64v) \
    macro(PFNGLGETBUFFERPOINTERVPROC, glGetBufferPointerv) \
    macro(PFNGLUNIFORMBLOCKBINDINGPROC, glUniformBlockBinding) \
    macro(PFNGLGETUNIFORMBLOCKINDEXPROC, glGetUniformBlockIndex) \
    macro(PFNGLGETUNIFORMINDICESPROC, glGetUniformIndices) \
    macro(PFNGLGETACTIVEUNIFORMBLOCKIVPROC, glGetActiveUniformBlockiv) \
    macro(PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC, glGetActiveUniformBlockName) \
    macro(PFNGLUNIFORM1UIPROC, glUniform1ui) \
    macro(PFNGLUNIFORM2UIPROC, glUniform2ui) \
    macro(PFNGLUNIFORM3UIPROC, glUniform3ui) \
    macro(PFNGLUNIFORM4UIPROC, glUniform4ui) \
    macro(PFNGLUNIFORM1UIVPROC, glUniform1uiv) \
    macro(PFNGLUNIFORM2UIVPROC, glUniform2uiv) \
    macro(PFNGLUNIFORM3UIVPROC, glUniform3uiv) \
    macro(PFNGLUNIFORM4UIVPROC, glUniform4uiv) \
    macro(PFNGLUNIFORMMATRIX2X3FVPROC, glUniformMatrix2x3fv) \
    macro(PFNGLUNIFORMMATRIX3X2FVPROC, glUniformMatrix3x2fv) \
    macro(PFNGLUNIFORMMATRIX2X4FVPROC, glUniformMatrix2x4fv) \
    macro(PFNGLUNIFORMMATRIX4X2FVPROC, glUniformMatrix4x2fv) \
    macro(PFNGLUNIFORMMATRIX3X4FVPROC, glUniformMatrix3x4fv) \
    macro(PFNGLUNIFORMMATRIX4X3FVPROC, glUniformMatrix4x3fv) \
    macro(PFNGLGETUNIFORMUIVPROC, glGetUniformuiv) \
    macro(PFNGLGETACTIVEUNIFORMSIVPROC, glGetActiveUniformsiv) \
    macro(PFNGLVERTEXATTRIBI4IPROC, glVertexAttribI4i) \
    macro(PFNGLVERTEXATTRIBI4UIPROC, glVertexAttribI4ui) \
    macro(PFNGLVERTEXATTRIBI4IVPROC, glVertexAttribI4iv) \
    macro(PFNGLVERTEXATTRIBI4UIVPROC, glVertexAttribI4uiv) \
    macro(PFNGLVERTEXATTRIBIPOINTERPROC, glVertexAttribIPointer) \
    macro(PFNGLGETVERTEXATTRIBIIVPROC, glGetVertexAttribIiv) \
    macro(PFNGLGETVERTEXATTRIBIUIVPROC, glGetVertexAttribIuiv) \
    macro(PFNGLVERTEXATTRIBDIVISORPROC, glVertexAttribDivisor) \
    macro(PFNGLDRAWARRAYSINSTANCEDPROC, glDrawArraysInstanced) \
    macro(PFNGLDRAWELEMENTSINSTANCEDPROC, glDrawElementsInstanced) \
    macro(PFNGLDRAWRANGEELEMENTSPROC, glDrawRangeElements) \
    macro(PFNGLFENCESYNCPROC, glFenceSync) \
    macro(PFNGLCLIENTWAITSYNCPROC, glClientWaitSync) \
    macro(PFNGLWAITSYNCPROC, glWaitSync) \
    macro(PFNGLDELETESYNCPROC, glDeleteSync) \
    macro(PFNGLISSYNCPROC, glIsSync) \
    macro(PFNGLGETSYNCIVPROC, glGetSynciv) \
    macro(PFNGLDRAWBUFFERSPROC, glDrawBuffers) \
    macro(PFNGLREADBUFFERPROC, glReadBuffer) \
    macro(PFNGLBLITFRAMEBUFFERPROC, glBlitFramebuffer) \
    macro(PFNGLINVALIDATEFRAMEBUFFERPROC, glInvalidateFramebuffer) \
    macro(PFNGLINVALIDATESUBFRAMEBUFFERPROC, glInvalidateSubFramebuffer) \
    macro(PFNGLFRAMEBUFFERTEXTURELAYERPROC, glFramebufferTextureLayer) \
    macro(PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC, glRenderbufferStorageMultisample) \
    macro(PFNGLTEXSTORAGE2DPROC, glTexStorage2D) \
    macro(PFNGLGETINTERNALFORMATIVPROC, glGetInternalformativ) \
    macro(PFNGLBEGINTRANSFORMFEEDBACKPROC, glBeginTransformFeedback) \
    macro(PFNGLENDTRANSFORMFEEDBACKPROC, glEndTransformFeedback) \
    macro(PFNGLGENTRANSFORMFEEDBACKSPROC, glGenTransformFeedbacks) \
    macro(PFNGLDELETETRANSFORMFEEDBACKSPROC, glDeleteTransformFeedbacks) \
    macro(PFNGLBINDTRANSFORMFEEDBACKPROC, glBindTransformFeedback) \
    macro(PFNGLPAUSETRANSFORMFEEDBACKPROC, glPauseTransformFeedback) \
    macro(PFNGLRESUMETRANSFORMFEEDBACKPROC, glResumeTransformFeedback) \
    macro(PFNGLISTRANSFORMFEEDBACKPROC, glIsTransformFeedback) \
    macro(PFNGLTRANSFORMFEEDBACKVARYINGSPROC, glTransformFeedbackVaryings) \
    macro(PFNGLGETTRANSFORMFEEDBACKVARYINGPROC, glGetTransformFeedbackVarying) \
    macro(PFNGLGENSAMPLERSPROC, glGenSamplers) \
    macro(PFNGLDELETESAMPLERSPROC, glDeleteSamplers) \
    macro(PFNGLBINDSAMPLERPROC, glBindSampler) \
    macro(PFNGLSAMPLERPARAMETERFPROC, glSamplerParameterf) \
    macro(PFNGLSAMPLERPARAMETERIPROC, glSamplerParameteri) \
    macro(PFNGLSAMPLERPARAMETERFVPROC, glSamplerParameterfv) \
    macro(PFNGLSAMPLERPARAMETERIVPROC, glSamplerParameteriv) \
    macro(PFNGLGETSAMPLERPARAMETERFVPROC, glGetSamplerParameterfv) \
    macro(PFNGLGETSAMPLERPARAMETERIVPROC, glGetSamplerParameteriv) \
    macro(PFNGLISSAMPLERPROC, glIsSampler) \
    macro(PFNGLGENQUERIESPROC, glGenQueries) \
    macro(PFNGLDELETEQUERIESPROC, glDeleteQueries) \
    macro(PFNGLBEGINQUERYPROC, glBeginQuery) \
    macro(PFNGLENDQUERYPROC, glEndQuery) \
    macro(PFNGLGETQUERYIVPROC, glGetQueryiv) \
    macro(PFNGLGETQUERYOBJECTUIVPROC, glGetQueryObjectuiv) \
    macro(PFNGLISQUERYPROC, glIsQuery) \
    macro(PFNGLPROGRAMPARAMETERIPROC, glProgramParameteri) \
    macro(PFNGLPROGRAMBINARYPROC, glProgramBinary) \
    macro(PFNGLGETPROGRAMBINARYPROC, glGetProgramBinary) \
    macro(PFNGLGETFRAGDATALOCATIONPROC, glGetFragDataLocation) \
    macro(PFNGLGETINTEGER64VPROC, glGetInteger64v) \
    macro(PFNGLGETINTEGERI_VPROC, glGetIntegeri_v) \
    macro(PFNGLGETINTEGER64I_VPROC, glGetInteger64i_v) \
    macro(PFNGLTEXIMAGE3DPROC, glTexImage3D) \
    macro(PFNGLTEXSTORAGE3DPROC, glTexStorage3D) \
    macro(PFNGLTEXSUBIMAGE3DPROC, glTexSubImage3D) \
    macro(PFNGLCOMPRESSEDTEXIMAGE3DPROC, glCompressedTexImage3D) \
    macro(PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC, glCompressedTexSubImage3D) \
    macro(PFNGLCOPYTEXSUBIMAGE3DPROC, glCopyTexSubImage3D) \
    macro(PFNGLGETSTRINGIPROC, glGetStringi) \
    macro(PFNGLGETBOOLEANI_VPROC, glGetBooleani_v) \
    macro(PFNGLMEMORYBARRIERPROC, glMemoryBarrier) \
    macro(PFNGLMEMORYBARRIERBYREGIONPROC, glMemoryBarrierByRegion) \
    macro(PFNGLGENPROGRAMPIPELINESPROC, glGenProgramPipelines) \
    macro(PFNGLDELETEPROGRAMPIPELINESPROC, glDeleteProgramPipelines) \
    macro(PFNGLBINDPROGRAMPIPELINEPROC, glBindProgramPipeline) \
    macro(PFNGLGETPROGRAMPIPELINEIVPROC, glGetProgramPipelineiv) \
    macro(PFNGLGETPROGRAMPIPELINEINFOLOGPROC, glGetProgramPipelineInfoLog) \
    macro(PFNGLVALIDATEPROGRAMPIPELINEPROC, glValidateProgramPipeline) \
    macro(PFNGLISPROGRAMPIPELINEPROC, glIsProgramPipeline) \
    macro(PFNGLUSEPROGRAMSTAGESPROC, glUseProgramStages) \
    macro(PFNGLACTIVESHADERPROGRAMPROC, glActiveShaderProgram) \
    macro(PFNGLCREATESHADERPROGRAMVPROC, glCreateShaderProgramv) \
    macro(PFNGLPROGRAMUNIFORM1FPROC, glProgramUniform1f) \
    macro(PFNGLPROGRAMUNIFORM2FPROC, glProgramUniform2f) \
    macro(PFNGLPROGRAMUNIFORM3FPROC, glProgramUniform3f) \
    macro(PFNGLPROGRAMUNIFORM4FPROC, glProgramUniform4f) \
    macro(PFNGLPROGRAMUNIFORM1IPROC, glProgramUniform1i) \
    macro(PFNGLPROGRAMUNIFORM2IPROC, glProgramUniform2i) \
    macro(PFNGLPROGRAMUNIFORM3IPROC, glProgramUniform3i) \
    macro(PFNGLPROGRAMUNIFORM4IPROC, glProgramUniform4i) \
    macro(PFNGLPROGRAMUNIFORM1UIPROC, glProgramUniform1ui) \
    macro(PFNGLPROGRAMUNIFORM2UIPROC, glProgramUniform2ui) \
    macro(PFNGLPROGRAMUNIFORM3UIPROC, glProgramUniform3ui) \
    macro(PFNGLPROGRAMUNIFORM4UIPROC, glProgramUniform4ui) \
    macro(PFNGLPROGRAMUNIFORM1FVPROC, glProgramUniform1fv) \
    macro(PFNGLPROGRAMUNIFORM2FVPROC, glProgramUniform2fv) \
    macro(PFNGLPROGRAMUNIFORM3FVPROC, glProgramUniform3fv) \
    macro(PFNGLPROGRAMUNIFORM4FVPROC, glProgramUniform4fv) \
    macro(PFNGLPROGRAMUNIFORM1IVPROC, glProgramUniform1iv) \
    macro(PFNGLPROGRAMUNIFORM2IVPROC, glProgramUniform2iv) \
    macro(PFNGLPROGRAMUNIFORM3IVPROC, glProgramUniform3iv) \
    macro(PFNGLPROGRAMUNIFORM4IVPROC, glProgramUniform4iv) \
    macro(PFNGLPROGRAMUNIFORM1UIVPROC, glProgramUniform1uiv) \
    macro(PFNGLPROGRAMUNIFORM2UIVPROC, glProgramUniform2uiv) \
    macro(PFNGLPROGRAMUNIFORM3UIVPROC, glProgramUniform3uiv) \
    macro(PFNGLPROGRAMUNIFORM4UIVPROC, glProgramUniform4uiv) \
    macro(PFNGLPROGRAMUNIFORMMATRIX2FVPROC, glProgramUniformMatrix2fv) \
    macro(PFNGLPROGRAMUNIFORMMATRIX3FVPROC, glProgramUniformMatrix3fv) \
    macro(PFNGLPROGRAMUNIFORMMATRIX4FVPROC, glProgramUniformMatrix4fv) \
    macro(PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC, glProgramUniformMatrix2x3fv) \
    macro(PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC, glProgramUniformMatrix3x2fv) \
    macro(PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC, glProgramUniformMatrix2x4fv) \
    macro(PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC, glProgramUniformMatrix4x2fv) \
    macro(PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC, glProgramUniformMatrix3x4fv) \
    macro(PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC, glProgramUniformMatrix4x3fv) \
    macro(PFNGLGETPROGRAMINTERFACEIVPROC, glGetProgramInterfaceiv) \
    macro(PFNGLGETPROGRAMRESOURCEIVPROC, glGetProgramResourceiv) \
    macro(PFNGLGETPROGRAMRESOURCEINDEXPROC, glGetProgramResourceIndex) \
    macro(PFNGLGETPROGRAMRESOURCELOCATIONPROC, glGetProgramResourceLocation) \
    macro(PFNGLGETPROGRAMRESOURCENAMEPROC, glGetProgramResourceName) \
    macro(PFNGLBINDIMAGETEXTUREPROC, glBindImageTexture) \
    macro(PFNGLDISPATCHCOMPUTEPROC, glDispatchCompute) \
    macro(PFNGLDISPATCHCOMPUTEINDIRECTPROC, glDispatchComputeIndirect) \
    macro(PFNGLBINDVERTEXBUFFERPROC, glBindVertexBuffer) \
    macro(PFNGLVERTEXATTRIBBINDINGPROC, glVertexAttribBinding) \
    macro(PFNGLVERTEXATTRIBFORMATPROC, glVertexAttribFormat) \
    macro(PFNGLVERTEXATTRIBIFORMATPROC, glVertexAttribIFormat) \
    macro(PFNGLVERTEXBINDINGDIVISORPROC, glVertexBindingDivisor) \
    macro(PFNGLDRAWARRAYSINDIRECTPROC, glDrawArraysIndirect) \
    macro(PFNGLDRAWELEMENTSINDIRECTPROC, glDrawElementsIndirect) \
    macro(PFNGLTEXSTORAGE2DMULTISAMPLEPROC, glTexStorage2DMultisample) \
    macro(PFNGLSAMPLEMASKIPROC, glSampleMaski) \
    macro(PFNGLGETMULTISAMPLEFVPROC, glGetMultisamplefv) \
    macro(PFNGLFRAMEBUFFERPARAMETERIPROC, glFramebufferParameteri) \
    macro(PFNGLGETFRAMEBUFFERPARAMETERIVPROC, glGetFramebufferParameteriv) \
    macro(PFNGLGETTEXLEVELPARAMETERFVPROC, glGetTexLevelParameterfv) \
    macro(PFNGLGETTEXLEVELPARAMETERIVPROC, glGetTexLevelParameteriv) \
    macro(PFNGLENABLEIEXTPROC, glEnableiEXT) \
    macro(PFNGLDISABLEIEXTPROC, glDisableiEXT) \
    macro(PFNGLBLENDEQUATIONIEXTPROC, glBlendEquationiEXT) \
    macro(PFNGLBLENDEQUATIONSEPARATEIEXTPROC, glBlendEquationSeparateiEXT) \
    macro(PFNGLBLENDFUNCIEXTPROC, glBlendFunciEXT) \
    macro(PFNGLBLENDFUNCSEPARATEIEXTPROC, glBlendFuncSeparateiEXT) \
    macro(PFNGLCOLORMASKIEXTPROC, glColorMaskiEXT) \
    macro(PFNGLISENABLEDIEXTPROC, glIsEnablediEXT) \
    macro(PFNGLCOPYIMAGESUBDATAEXTPROC, glCopyImageSubDataEXT) \
    macro(PFNGLBLENDBARRIERKHRPROC, glBlendBarrierKHR) \
    macro(PFNGLTEXPARAMETERIIVEXTPROC, glTexParameterIivEXT) \
    macro(PFNGLTEXPARAMETERIUIVEXTPROC, glTexParameterIuivEXT) \
    macro(PFNGLGETTEXPARAMETERIIVEXTPROC, glGetTexParameterIivEXT) \
    macro(PFNGLGETTEXPARAMETERIUIVEXTPROC, glGetTexParameterIuivEXT) \
    macro(PFNGLSAMPLERPARAMETERIIVEXTPROC, glSamplerParameterIivEXT) \
    macro(PFNGLSAMPLERPARAMETERIUIVEXTPROC, glSamplerParameterIuivEXT) \
    macro(PFNGLGETSAMPLERPARAMETERIIVEXTPROC, glGetSamplerParameterIivEXT) \
    macro(PFNGLGETSAMPLERPARAMETERIUIVEXTPROC, glGetSamplerParameterIuivEXT)

/**
 * @brief: apply "macro" operation on each function pointer member for all the extra openGLES API type
 * @param [in]macro: the operation with each OpenGLES API type and function pointer member
 */
#define FOREACH_OPENGL_MANUAL(macro) \
    macro(PFNGLVERTEXATTRIBPOINTERDATAPROC, glVertexAttribPointerData) \
    macro(PFNGLVERTEXATTRIBPOINTEROFFSETPROC, glVertexAttribPointerOffset) \
    macro(PFNGLDRAWELEMENTSOFFSETPROC, glDrawElementsOffset) \
    macro(PFNGLDRAWELEMENTSDATAPROC, glDrawElementsData) \
    macro(PFNGLGETCOMPRESSEDTEXTUREFORMATSPROC, glGetCompressedTextureFormats) \
    macro(PFNGLSHADERSTRINGPROC, glShaderString) \
    macro(PFNGLFINISHROUNDTRIPPROC, glFinishRoundTrip) \
    macro(PFNGLMAPBUFFERRANGEAEMUPROC, glMapBufferRangeAEMU) \
    macro(PFNGLUNMAPBUFFERAEMUPROC, glUnmapBufferAEMU) \
    macro(PFNGLUNMAPBUFFERAEMUPROC, glUnmapBufferTrace) \
    macro(PFNGLFLUSHMAPPEDBUFFERRANGEAEMUPROC, glFlushMappedBufferRangeAEMU) \
    macro(PFNGLREADPIXELSOFFSETAEMUPROC, glReadPixelsOffsetAEMU) \
    macro(PFNGLCOMPRESSEDTEXIMAGE2DOFFSETAEMUPROC, glCompressedTexImage2DOffsetAEMU) \
    macro(PFNGLCOMPRESSEDTEXSUBIMAGE2DOFFSETAEMUPROC, glCompressedTexSubImage2DOffsetAEMU) \
    macro(PFNGLTEXIMAGE2DOFFSETAEMUPROC, glTexImage2DOffsetAEMU) \
    macro(PFNGLTEXSUBIMAGE2DOFFSETAEMUPROC, glTexSubImage2DOffsetAEMU) \
    macro(PFNGLGETUNIFORMINDICESAEMUPROC, glGetUniformIndicesAEMU) \
    macro(PFNGLVERTEXATTRIBIPOINTEROFFSETAEMUPROC, glVertexAttribIPointerOffsetAEMU) \
    macro(PFNGLVERTEXATTRIBIPOINTERDATAAEMUPROC, glVertexAttribIPointerDataAEMU) \
    macro(PFNGLDRAWELEMENTSINSTANCEDDATAAEMUPROC, glDrawElementsInstancedDataAEMU) \
    macro(PFNGLDRAWELEMENTSINSTANCEDOFFSETAEMUPROC, glDrawElementsInstancedOffsetAEMU) \
    macro(PFNGLDRAWRANGEELEMENTSDATAAEMUPROC, glDrawRangeElementsDataAEMU) \
    macro(PFNGLDRAWRANGEELEMENTSOFFSETAEMUPROC, glDrawRangeElementsOffsetAEMU) \
    macro(PFNGLFENCESYNCAEMUPROC, glFenceSyncAEMU) \
    macro(PFNGLCLIENTWAITSYNCAEMUPROC, glClientWaitSyncAEMU) \
    macro(PFNGLWAITSYNCAEMUPROC, glWaitSyncAEMU) \
    macro(PFNGLDELETESYNCAEMUPROC, glDeleteSyncAEMU) \
    macro(PFNGLISSYNCAEMUPROC, glIsSyncAEMU) \
    macro(PFNGLGETSYNCIVAEMUPROC, glGetSyncivAEMU) \
    macro(PFNGLTRANSFORMFEEDBACKVARYINGSAEMUPROC, glTransformFeedbackVaryingsAEMU) \
    macro(PFNGLTEXIMAGE3DOFFSETAEMUPROC, glTexImage3DOffsetAEMU) \
    macro(PFNGLTEXSUBIMAGE3DOFFSETAEMUPROC, glTexSubImage3DOffsetAEMU) \
    macro(PFNGLCOMPRESSEDTEXIMAGE3DOFFSETAEMUPROC, glCompressedTexImage3DOffsetAEMU) \
    macro(PFNGLCOMPRESSEDTEXSUBIMAGE3DOFFSETAEMUPROC, glCompressedTexSubImage3DOffsetAEMU) \
    macro(PFNGLCREATESHADERPROGRAMVAEMUPROC, glCreateShaderProgramvAEMU) \
    macro(PFNGLDRAWARRAYSINDIRECTDATAAEMUPROC, glDrawArraysIndirectDataAEMU) \
    macro(PFNGLDRAWARRAYSINDIRECTOFFSETAEMUPROC, glDrawArraysIndirectOffsetAEMU) \
    macro(PFNGLDRAWELEMENTSINDIRECTDATAAEMUPROC, glDrawElementsIndirectDataAEMU) \
    macro(PFNGLDRAWELEMENTSINDIRECTOFFSETAEMUPROC, glDrawElementsIndirectOffsetAEMU) \
    macro(PFNGLCREATEPROGRAMTRACEPROC, glCreateProgramTrace) \
    macro(PFNGLCREATESHADERTRACEPROC, glCreateShaderTrace) \
    macro(PFNGLGENBUFFERSTRACEPROC, glGenBuffersTrace) \
    macro(PFNGLGENFRAMEBUFFERSTRACEPROC, glGenFramebuffersTrace) \
    macro(PFNGLGENRENDERBUFFERSTRACEPROC, glGenRenderbuffersTrace) \
    macro(PFNGLGENTEXTURESTRACEPROC, glGenTexturesTrace) \
    macro(PFNGLGENVERTEXARRAYSTRACEPROC, glGenVertexArraysTrace) \
    macro(PFNGLFENCESYNCTRACEPROC, glFenceSyncTrace) \
    macro(PFNGLGENTRANSFORMFEEDBACKSTRACEPROC, glGenTransformFeedbacksTrace) \
    macro(PFNGLGENSAMPLERSDECPROC, glGenSamplersTrace) \
    macro(PFNGLGENQUERIESDECPROC, glGenQueriesTrace) \
    macro(PFNGLGETUNIFORMLOCATIPNTRACEPROC, glGetUniformLocationTrace) \
    macro(PFNGLGETUNIFORMBLOCKINDEXTRACEPROC, glGetUniformBlockIndexTrace) \
    macro(PFNGLGETUNIFORMINDICESAEMUTRACEPROC, glGetUniformIndicesAEMUTrace) \
    macro(PFNGLGETATTRIBLOCATIONTRACEPROC, glGetAttribLocationTrace) \
    macro(PFNGLBINDBUFFERDRACOPROC, glBindBufferDraco) \
    macro(PFNGLBUFFERDATADRACOPROC, glBufferDataDraco) \
    macro(PFNGLBUFFERSUBDATADRACOPROC, glBufferSubDataDraco) \
    macro(PFNGLVERTEXATTRIBPOINTEROFFSETDRACOPROC, glVertexAttribPointerOffsetDraco) \
    macro(PFNGLDRAWELEMENTSOFFSETDRACOPROC, glDrawElementsOffsetDraco) \
    macro(PFNGLUNIFORMLAYOUTPROC, glUniformLayout)


#endif // GLES_API_ENTRY_LIST_H
