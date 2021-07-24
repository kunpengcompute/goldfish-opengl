/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description:  GL2Encoder base class.
 */
#define LOG_TAG "GL2EncoderBase"
#include "GL2EncoderBase.h"
#include "GL2Encoder.h"
#include <functional>
#include <string>
#include <climits>
#include <cstdlib>
#include <dlfcn.h>

createGLESv2Encoder_proc_t GL2EncoderBase::createGLESv2EncoderFunc = nullptr;
glActiveTexture_client_proc_t GL2EncoderBase::glActiveTextureFunc = nullptr;
bool GL2EncoderBase::m_isInit = false;
void* GL2EncoderBase::m_libHandle = nullptr;

void* LoadLibrary(const std::string& path)
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
        const char* reason = dlerror();
        if (reason == nullptr) {
            reason = "Unknow";
        }
        ALOGE("Failed to open library, path:%s, reason:%s", path.c_str(), reason);
    }
    return library;
}

void* GetProcAddress(void* library, const std::string& name)
{
    if (library == nullptr || name.empty()) {
        ALOGE("Failed to get function:%s, library == nullptr", name.c_str());
        return nullptr;
    }
    void* symbol = dlsym(library, name.c_str());
    if (symbol == nullptr) {
        const char* reason = dlerror();
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
    InitGLESv2Export();
}

GL2EncoderBase::~GL2EncoderBase()
{
    if (m_libHandle == nullptr) {
        return;
    }
    if (dlclose(m_libHandle) != 0) {
        const char* reason = dlerror();
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
    std::function<void *(const char *)> func = std::bind(&GetProcAddress,
        m_libHandle, std::placeholders::_1);
    if (func == nullptr) {
        return false;
    }

    createGLESv2EncoderFunc = reinterpret_cast<decltype(createGLESv2EncoderFunc)>(func("CreateVmiGLESv2Encoder"));
    glActiveTextureFunc = reinterpret_cast<decltype(glActiveTextureFunc)>(func("VmiGlActiveTexture"));
   
    m_isInit = true;
    ALOGD("GL2EncoderBase::InitGLESv2Export success!");
    return true;
}

void * GL2EncoderBase::GetGLESv2Encoder(void * self)
{
    GL2Encoder * ctx = static_cast<GL2Encoder*>(self);
    return dynamic_cast<VmiGLESv2Encoder*>(ctx);
}

bool GL2EncoderBase::CreateVmiGLESv2Encoder(void * stream)
{
    if(createGLESv2EncoderFunc == nullptr) {
        return false;
    }
    m_GLESv2Encoder = createGLESv2EncoderFunc(stream);
    if (m_GLESv2Encoder == nullptr) {
        return false;
    }
    return true;
}

void GL2EncoderBase::glActiveTexture_s(void * self, unsigned int texture)
{
    ALOGD("GL2EncoderBase::glActiveTexture_s begin");
    GL2EncoderBase * ctx = static_cast<GL2EncoderBase*>(self);
    if (ctx == nullptr){
        ALOGE("glActiveTexture_s: parameters error. ctx==nullptr");
        return;
    }
    ctx->glActiveTextureFunc(ctx->GetGLESv2Encoder(self), texture);
}