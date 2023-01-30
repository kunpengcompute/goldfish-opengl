
#include "SipcStream.h"
#include <chrono>
#include <cstdint>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "log/log_main.h"

using namespace std;

void *SipcStream::m_libVmiStream = nullptr;
VmiStreamCreateFn SipcStream::m_pfVmiStreamCreate = nullptr;
VmiStreamDestroyFn SipcStream::m_pfVmiStreamDestroy = nullptr;
VmiStreamSendFn SipcStream::m_pfVmiStreamSend = nullptr;
VmiStreamRecvFn SipcStream::m_pfVmiStreamRecv = nullptr;
VmiStreamGetNextMsgSizeFn SipcStream::m_pfVmiStreamGetNextMsgSize = nullptr;

// 需保持与指令流引擎的 VMI::GLHead 定义一致
enum CompressType : int32_t {
    COMPRESS_INVALID = -1,
    COMPRESS_NONE = 0,
    COMPRESS_ZSTD = 1,
};

struct GLHead {
public:
    void SetHeader(CompressType compressType, uint32_t length, uint32_t pid, uint32_t tid, int64_t timeStamp)
    {
        m_decompressLength = length;
        m_pid = pid;
        m_tid = tid;
        m_compressType = compressType;
        m_timeStamp = timeStamp;
    }
private:
    uint32_t m_decompressLength = 0;
    CompressType m_compressType = COMPRESS_NONE;
    uint32_t m_pid = 0;
    uint32_t m_tid = 0;
    int64_t m_timeStamp = 0;
} __attribute__((packed));

void SipcStream::LoadSipcLib()
{
#if defined(__LP64__)
    const std::string libName = "/vendor/lib64/libVmiStream.so";
#else
    const std::string libName = "/vendor/lib/libVmiStream.so";
#endif
    if (m_libVmiStream == nullptr) {
        m_libVmiStream = dlopen(libName.c_str(), RTLD_NOW | RTLD_LOCAL);
        if (m_libVmiStream == nullptr) {
            ALOGE("Failed to open shared library:%s", libName.c_str());
            return;
        }
        ALOGI("Success to open shared library:%s", libName.c_str());
    }

    if (m_pfVmiStreamCreate == nullptr) {
        string func("VmiStreamCreate");
        m_pfVmiStreamCreate = (VmiStreamCreateFn)dlsym(m_libVmiStream, func.c_str());
        if (m_pfVmiStreamCreate == nullptr) {
            ALOGE("Failed to get function %s", func.c_str());
        } else {
            ALOGI("Success to get function %s", func.c_str());
        }
    }

    if (m_pfVmiStreamDestroy == nullptr) {
        string func("VmiStreamDestroy");
        m_pfVmiStreamDestroy = (VmiStreamDestroyFn)dlsym(m_libVmiStream, func.c_str());
        if (m_pfVmiStreamDestroy == nullptr) {
            ALOGE("Failed to get function %s", func.c_str());
        } else {
            ALOGI("Success to get function %s", func.c_str());
        }
    }

    if (m_pfVmiStreamSend == nullptr) {
        string func("VmiStreamSend");
        m_pfVmiStreamSend = (VmiStreamSendFn)dlsym(m_libVmiStream, func.c_str());
        if (m_pfVmiStreamSend == nullptr) {
            ALOGE("Failed to get function %s", func.c_str());
        } else {
            ALOGI("Success to get function %s", func.c_str());
        }
    }

    if (m_pfVmiStreamRecv == nullptr) {
        string func("VmiStreamRecv");
        m_pfVmiStreamRecv = (VmiStreamRecvFn)dlsym(m_libVmiStream, func.c_str());
        if (m_pfVmiStreamRecv == nullptr) {
            ALOGE("Failed to get function %s", func.c_str());
        } else {
            ALOGI("Success to get function %s", func.c_str());
        }
    }

    if (m_pfVmiStreamGetNextMsgSize == nullptr) {
        string func("VmiStreamGetNextMsgSize");
        m_pfVmiStreamGetNextMsgSize = (VmiStreamGetNextMsgSizeFn)dlsym(m_libVmiStream, func.c_str());
        if (m_pfVmiStreamGetNextMsgSize == nullptr) {
            ALOGE("Failed to get function %s", func.c_str());
        } else {
            ALOGI("Success to get function %s", func.c_str());
        }
    }
}

void SipcStream::CreateSipcStream()
{
    if (m_pfVmiStreamCreate == nullptr) {
        ALOGE("pfVmiStreamCreate is null");
        return;
    }

    uint32_t instance;
    VmiStreamErrorCode ret = m_pfVmiStreamCreate(instance, GL);
    if (ret != VMI_STREAM_SUCCESS) {
        ALOGE("pfVmiStreamCreate return %u", ret);
        return;
    }

    m_instance = instance;
}

void SipcStream::DestroySipcStream()
{
    if (m_pfVmiStreamDestroy == nullptr) {
        ALOGE("pfVmiStreamDestroy is null");
        return;
    }

    if (m_instance == 0) {
        ALOGE("m_instance is 0");
        return;
    }

    m_pfVmiStreamDestroy(m_instance);
    m_instance = 0;
}

int SipcStream::flush()
{
    return commitBuffer(m_bufsize - m_free);
}

int SipcStream::commitBuffer(size_t size)
{
    if (m_pfVmiStreamSend == nullptr) {
        ALOGE("pfVmiStreamSend is null");
        return -1;
    }

    if (m_buf == nullptr) {
        ALOGE("m_buf is null");
        return -1;
    }

    if (m_bufsize != size + m_free) {
        ALOGE("m_bufsize:%zu, m_free:%zu, size:%zu", m_bufsize, m_free, size);
        return -1;
    }

    if (m_instance == 0) {
        ALOGE("m_instance is 0");
        return -1;
    }

    const uint32_t sendBufLen = 8 * 1024 *1024;
    static uint8_t sendBuf[sendBufLen];

    if (size + sizeof(GLHead) > sendBufLen) {
        ALOGE("commit buffer size:%zu too large", size);
        return -1;
    }

    int64_t time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    GLHead* glHead = (GLHead*)sendBuf;
    glHead->SetHeader(CompressType::COMPRESS_NONE, (uint32_t)size, (uint32_t)m_pid, (uint32_t)m_tid, time);
    (void)memcpy(&sendBuf[sizeof(GLHead)], m_buf, size);
    VmiStreamErrorCode ret = m_pfVmiStreamSend(m_instance,
        std::make_pair<uint8_t *, uint32_t>((uint8_t *)sendBuf, (uint32_t)size + sizeof(GLHead)));
    if (ret != VMI_STREAM_SUCCESS) {
        ALOGE("pfVmiStreamSend return %u", ret);
        return -1;
    }

    m_free = m_bufsize;
    return size;
}

const unsigned char *SipcStream::readFully(void *buf, size_t len)
{
    if (m_pfVmiStreamRecv == nullptr) {
        ALOGE("pfVmiStreamRecv is null");
        return nullptr;
    }

    if (m_pfVmiStreamGetNextMsgSize == nullptr) {
        ALOGE("pfVmiStreamGetNextMsgSize is null");
        return nullptr;
    }

    if (m_instance == 0) {
        ALOGE("m_instance is 0");
        return nullptr;
    }

    // 客户端会把多个字段组成一个包回送给服务端，而服务端每次只会读取一个字段（或者一个包的部分内容）
    // 因此在此函数中需要做简单的拆分操作，只返回服务端想要的部分内容
    // SIPC 每个包最大 1M；如果单次读取数据超过 1M，需要多次读取 SIPC，自行组装
    static uint8_t cacheData[8 * 1024 * 1024];
    static uint32_t cacheBegin = 0;  // 有效数据的起始位置
    static uint32_t cacheNotRead = 0;// 剩余有效数据的长度

    if (len > sizeof(cacheData)) {
        ALOGE("pkg need to read(%zu) is too large", len);
        return nullptr;
    }

    VmiStreamErrorCode ret;
    while (cacheNotRead < len) {
        uint32_t nextPktSize = 0;
        ret = m_pfVmiStreamGetNextMsgSize(m_instance, nextPktSize);
        if (ret != VMI_STREAM_SUCCESS) {
            ALOGE("pfVmiStreamGetNextMsgSize return %u", ret);
            return nullptr;
        }

        if (nextPktSize == 0) {
            usleep(1);
            continue;
        }

        if (nextPktSize > sizeof(cacheData) - cacheBegin - cacheNotRead) {
            ALOGE("Next pkg size:%u is larger than left cache:%zu", nextPktSize,
                sizeof(cacheData) - cacheBegin - cacheNotRead);
            return nullptr;
        }

        std::pair<uint8_t *, uint32_t &> pairData =
            { static_cast<uint8_t *>(cacheData) + cacheBegin + cacheNotRead, nextPktSize };
        ret = m_pfVmiStreamRecv(m_instance, pairData);
        if (ret != VMI_STREAM_SUCCESS) {
            ALOGE("pfVmiStreamRecv return %u", ret);
            return nullptr;
        }

        cacheNotRead = nextPktSize;
    }

    (void)memcpy(buf, cacheData + cacheBegin, len);
    cacheBegin += (uint32_t)len;
    cacheNotRead -= (uint32_t)len;

    // 每次完整读完一个包，缓冲区指针重置
    if (cacheNotRead == 0) {
        cacheBegin = 0;
    }

    return (unsigned char *)buf;
}


