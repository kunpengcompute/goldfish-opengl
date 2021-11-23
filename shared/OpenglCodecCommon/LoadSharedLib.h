/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description:  Load shared library.
 */

#ifndef __LOAD_SHARED_LIB_H
#define __LOAD_SHARED_LIB_H

#include <string>

class LoadSharedLib {
public:
    LoadSharedLib(const std::string &path);
    ~LoadSharedLib();
    void* GetProcAddress(const std::string &funcStr);
private:
    bool OpenHandle();
    void CloseHandle();
    std::string m_path = "";
    void* m_handle = nullptr;
    bool isInit = false;
};

#endif