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
#include "ExtendedRCEncoderContext.h"

std::mutex ExtendedRCEncoderContext::m_lock {};
void *ExtendedRCEncoderContext::m_implLib = nullptr;

ExtendedRCEncoderContext::ExtendedRCEncoderContext()
{
}

ExtendedRCEncoderContext::~ExtendedRCEncoderContext()
{
    DeleteVmiRenderControlEncoder();
}

int ExtendedRCEncoderContext::initDispatchByName(void *(*getProc)(const char *, void *userData), void *userData)
{
    rcGetRendererVersion = (rcGetRendererVersion_proc_t)getProc("GetRendererVersion", userData);
    rcGetEGLVersion = (rcGetEGLVersion_proc_t)getProc("GetEGLVersion", userData);
    rcQueryEGLString = (rcQueryEGLString_proc_t)getProc("QueryEGLString", userData);
    rcGetGLString = (rcGetGLString_proc_t)getProc("GetGLString", userData);
    rcGetNumConfigs = (rcGetNumConfigs_proc_t)getProc("GetNumConfigs", userData);
    rcGetConfigs = (rcGetConfigs_proc_t)getProc("GetConfigs", userData);
    rcChooseConfig = (rcChooseConfig_proc_t)getProc("ChooseConfig", userData);
    rcGetFBParam = (rcGetFBParam_proc_t)getProc("GetFBParam", userData);
    rcCreateContext = (rcCreateContext_proc_t)getProc("CreateContext", userData);
    rcDestroyContext = (rcDestroyContext_proc_t)getProc("DestroyContext", userData);
    rcCreateWindowSurface = (rcCreateWindowSurface_proc_t)getProc("CreateWindowSurface", userData);
    rcDestroyWindowSurface = (rcDestroyWindowSurface_proc_t)getProc("DestroyWindowSurface", userData);
    rcCreateColorBuffer = (rcCreateColorBuffer_proc_t)getProc("CreateColorBuffer", userData);
    rcOpenColorBuffer = (rcOpenColorBuffer_proc_t)getProc("OpenColorBuffer", userData);
    rcCloseColorBuffer = (rcCloseColorBuffer_proc_t)getProc("CloseColorBuffer", userData);
    rcSetWindowColorBuffer = (rcSetWindowColorBuffer_proc_t)getProc("SetWindowColorBuffer", userData);
    rcFlushWindowColorBuffer = (rcFlushWindowColorBuffer_proc_t)getProc("FlushWindowColorBuffer", userData);
    rcMakeCurrent = (rcMakeCurrent_proc_t)getProc("MakeCurrent", userData);
    rcFBPost = (rcFBPost_proc_t)getProc("FBPost", userData);
    rcFBSetSwapInterval = (rcFBSetSwapInterval_proc_t)getProc("FBSetSwapInterval", userData);
    rcBindTexture = (rcBindTexture_proc_t)getProc("BindTexture", userData);
    rcBindRenderbuffer = (rcBindRenderbuffer_proc_t)getProc("BindRenderbuffer", userData);
    rcColorBufferCacheFlush = (rcColorBufferCacheFlush_proc_t)getProc("ColorBufferCacheFlush", userData);
    rcReadColorBuffer = (rcReadColorBuffer_proc_t)getProc("ReadColorBuffer", userData);
    rcUpdateColorBuffer = (rcUpdateColorBuffer_proc_t)getProc("UpdateColorBuffer", userData);
    rcOpenColorBuffer2 = (rcOpenColorBuffer2_proc_t)getProc("OpenColorBuffer2", userData);
    rcCreateClientImage = (rcCreateClientImage_proc_t)getProc("CreateClientImage", userData);
    rcDestroyClientImage = (rcDestroyClientImage_proc_t)getProc("DestroyClientImage", userData);
    rcSelectChecksumHelper = (rcSelectChecksumHelper_proc_t)getProc("SelectChecksumHelper", userData);
    rcCreateSyncKHR = (rcCreateSyncKHR_proc_t)getProc("CreateSyncKHR", userData);
    rcClientWaitSyncKHR = (rcClientWaitSyncKHR_proc_t)getProc("ClientWaitSyncKHR", userData);
    rcFlushWindowColorBufferAsync =
        (rcFlushWindowColorBufferAsync_proc_t)getProc("FlushWindowColorBufferAsync", userData);
    rcDestroySyncKHR = (rcDestroySyncKHR_proc_t)getProc("DestroySyncKHR", userData);
    rcSetPuid = (rcSetPuid_proc_t)getProc("SetPuid", userData);
    rcUpdateColorBufferDMA = (rcUpdateColorBufferDMA_proc_t)getProc("UpdateColorBufferDMA", userData);
    rcCreateColorBufferDMA = (rcCreateColorBufferDMA_proc_t)getProc("CreateColorBufferDMA", userData);
    rcWaitSyncKHR = (rcWaitSyncKHR_proc_t)getProc("WaitSyncKHR", userData);
    setSyncImpl = (setSyncImpl_proc_t)getProc("SetSyncImpl", userData);
    hasNativeSync = (hasNativeSync_proc_t)getProc("HasNativeSync", userData);
    hasNativeSyncV3 = (hasNativeSyncV3_proc_t)getProc("HasNativeSyncV3", userData);
    setGLESMaxVersion = (setGLESMaxVersion_proc_t)getProc("SetGLESMaxVersion", userData);
    getGLESMaxVersion = (getGLESMaxVersion_proc_t)getProc("GetGLESMaxVersion", userData);
    createVmiRenderControlEncoderFunc =
        (createVmiRenderControlEncoder_proc_t)getProc("CreateVmiRenderControlEncoder", userData);
    deleteVmiRenderControlEncoderFunc =
        (deleteVmiRenderControlEncoder_proc_t)getProc("DeleteVmiRenderControlEncoder", userData);
    return 0;
}

bool ExtendedRCEncoderContext::InitRenderControlExport()
{
    std::lock_guard<std::mutex> lock(m_lock);
    ALOGD("ExtendedRCEncoderContext::InitRenderControlExport begin");
#if defined(__LP64__)
        const std::string libName = "/vendor/lib64/libVmiInstructionEngine.so";
#else
        const std::string libName = "/vendor/lib/libVmiInstructionEngine.so";
#endif
    if (m_implLib == nullptr) {
        m_implLib = dlopen(libName.c_str(), RTLD_NOW | RTLD_LOCAL);
        if (m_implLib == nullptr) {
            ALOGE("error: Failed to open shared library:%s", libName.c_str());
            return false;
        }
    }
    std::unique_ptr<ApiInitializer> initializer = std::make_unique<ApiInitializer>(m_implLib);
    if (initializer == nullptr) {
        ALOGE("Failed to create ApiInitializer");
        return false;
    }
    initDispatchByName(ApiInitializer::s_getProc, initializer.get());
    ALOGD("ExtendedRCEncoderContext::InitRenderControlExport end");
    return true;
}

uint32_t ExtendedRCEncoderContext::GetRenderControlEncoder(void *self)
{
    ExtendedRCEncoderContext *ctx = static_cast<ExtendedRCEncoderContext *>(self);
    return ctx->m_renderControlWrap;
}

bool ExtendedRCEncoderContext::CreateVmiRenderControlEncoder(uint32_t stream)
{
    if (createVmiRenderControlEncoderFunc == nullptr) {
        return false;
    }
    m_renderControlWrap = createVmiRenderControlEncoderFunc(stream);
    if (m_renderControlWrap == 0) {
        return false;
    }
    return true;
}

void ExtendedRCEncoderContext::DeleteVmiRenderControlEncoder()
{
    if (deleteVmiRenderControlEncoderFunc == nullptr) {
        return;
    }
    deleteVmiRenderControlEncoderFunc(m_renderControlWrap);
}