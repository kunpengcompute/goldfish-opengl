/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description:  Load shared library.
 */
#include "LoadSharedLib.h"
#include <dlfcn.h>
#include <climits>
#include <cstdlib>
#include <log/log.h>

LoadSharedLib::LoadSharedLib(const std::string &path) : m_path(path), isInit(false)
{
}

LoadSharedLib::~LoadSharedLib()
{
    CloseHandle();
}

bool LoadSharedLib::OpenHandle()
{
    if (isInit) {
        return true;
    }
    if (m_path.empty()) {
        ALOGE("path is empty!");
        return false;
    }
    auto realPath = realpath(m_path.c_str(), nullptr);
    if (realPath == nullptr) {
        ALOGE("invalid path!");
        return false;
    }
    m_handle = dlopen(realPath, RTLD_LAZY | RTLD_LOCAL);
    free(realPath);
    realPath = nullptr;
    if (m_handle == nullptr) {
        const char* reason = dlerror();
        if (reason == nullptr) {
            reason = "Unkown";
        }
        ALOGE("Failed to open library, path:%s, reason:%s", m_path.c_str(), reason);
        return false;
    }
    isInit = true;
    return true;
}

void LoadSharedLib::CloseHandle()
{
    if (m_handle != nullptr) {
        dlclose(m_handle);
        m_handle = nullptr;
    }
    isInit = false;
}

void* LoadSharedLib::GetProcAddress(const std::string &funcName)
{
    if (!OpenHandle()) {
        ALOGE("Failed to open dlHandle");
        return nullptr;
    }
    void* symbol = dlsym(m_handle, funcName.c_str());
    if (symbol == nullptr) {
        const char *reason = dlerror();
        if (reason == nullptr) {
            reason = "Unknow";
        }
        ALOGE("Failed to get function:%s, reason:%s", funcName.c_str(), reason);
    }
    return symbol;
}