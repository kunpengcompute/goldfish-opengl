
#ifndef __SIPC_STREAM_H__
#define __SIPC_STREAM_H__

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <pthread.h>

#ifdef _GNU_SOURCE
#undef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <unistd.h>
#include <sys/syscall.h>

#include "ErrorLog.h"
#include "IOStream.h"

enum VmiStreamErrorCode : uint32_t {
    VMI_STREAM_SUCCESS = 0,
    VMI_STREAM_INVALID_PARAMS = 0x0A0A0001,
    VMI_STREAM_CREATE_FAILURE,
    VMI_STREAM_INVALID_INSTANCE,
    VMI_STREAM_INVALID_DATA,
    VMI_STREAM_FULL,
    VMI_STREAM_SEND_FAILED,
    VMI_STREAM_OOM,
    VMI_STREAM_RECV_FAILED,
    VMI_STREAM_PIPE_CLOSE,
    VMI_STREAM_NOT_READY
};

enum VMIMsgType : uint8_t {
    INVALID = 0,
    HEARTBEAT,
    GL,
    AUDIO,
    TOUCH_INPUT,
    NAVBAR_INPUT,
    VULKAN,
    END
};

using VmiStreamCreateFn = VmiStreamErrorCode (*)(uint32_t &instance, VMIMsgType type);
using VmiStreamDestroyFn = void (*)(uint32_t instance);
using VmiStreamSendFn = VmiStreamErrorCode (*)(uint32_t instance, std::pair<uint8_t *, uint32_t> data);
using VmiStreamRecvFn = VmiStreamErrorCode (*)(uint32_t instance, std::pair<uint8_t *, uint32_t &> data);
using VmiStreamGetNextMsgSizeFn = VmiStreamErrorCode (*)(uint32_t instance, uint32_t &size);

class SipcStream : public IOStream {
public:
    SipcStream(size_t bufSize) : IOStream(bufSize)
    {
        LoadSipcLib();
        CreateSipcStream();
    }
    ~SipcStream()
    {
        DestroySipcStream();
    }

    void *allocBuffer(size_t minSize)    { return malloc(minSize); }
    int flush();
    int commitBuffer(size_t size);
    const unsigned char *readFully( void *buf, size_t len);

    const unsigned char *read( void *buf, size_t *inout_len) { return nullptr; }
    int writeFully(const void* buf, size_t len) { return -1; }


private:
    void LoadSipcLib();
    static void *m_libVmiStream;
    static VmiStreamCreateFn m_pfVmiStreamCreate;
    static VmiStreamDestroyFn m_pfVmiStreamDestroy;
    static VmiStreamSendFn m_pfVmiStreamSend;
    static VmiStreamRecvFn m_pfVmiStreamRecv;
    static VmiStreamGetNextMsgSizeFn m_pfVmiStreamGetNextMsgSize;

    void CreateSipcStream();
    void DestroySipcStream();
    uint32_t m_instance = 0;

    int m_pid = getpid();
    int m_tid = syscall(SYS_gettid);
};

#endif

