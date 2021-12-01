/*
 * Description:  Load shared library.
 */

#ifndef __LOAD_SHARED_LIB_H
#define __LOAD_SHARED_LIB_H

#include <string>
#include <dlfcn.h>
#include <log/log.h>

typedef void (*notSupport_client_proc_t)();

namespace {
    void NotSupportEGL()
    {
        ALOGE("Failed to call EGL function, Not support");
    }
}

class ApiInitializer {
public:
    ApiInitializer(void *dso) :
        m_dso(dso), m_notSupportFunc(NotSupportEGL) {
    }
    static void *s_getProc(const char *name, void *userData) {
        ApiInitializer *self = (ApiInitializer *)userData;
        void *ptr = self->getProc(name);
        if (ptr == nullptr) {
            ALOGE("Failed to get func:%s", name);
            return reinterpret_cast<void *>(self->m_notSupportFunc);
        }
        return self->getProc(name);
    }
private:
    void *m_dso;
    notSupport_client_proc_t m_notSupportFunc;
    void *getProc(const char *name) {
        void *symbol = NULL;
        if (m_dso) {
            symbol = dlsym(m_dso, name);
        }
        return symbol;
    }
};

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