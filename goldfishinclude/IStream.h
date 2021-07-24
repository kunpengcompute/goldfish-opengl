/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2017-2021. All rights reserved.
 * Description:  IStream for goldfish-opengl
 */
#ifndef ISTREAM_H
#define ISTREAM_H

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <new>

class VmiRebuildStream;
class SnapshotRestore;

class IStream {
public:
    explicit IStream(size_t bufSize) : m_bufSize(bufSize)
    {
    }

    virtual ~IStream()
    {
        // NOTE: m_buf is 'owned' by the child class thus we expect it to be released by it
    }

    virtual const uint8_t* ReadOpcode(uint32_t opcode, uintptr_t &buf, size_t &len)
    {
        (void)opcode;
        (void)buf;
        (void)len;
        return nullptr;
    }

    virtual const uint8_t* ReadOpcode(uint32_t opcode, uintptr_t &buf, size_t &len, uint32_t maxReadTime)
    {
        (void)opcode;
        (void)buf;
        (void)len;
        (void)maxReadTime;
        return nullptr;
    }

    virtual uint8_t* AllocEncodeCache(size_t size)
    {
        (void)size;
        return nullptr;
    }

    virtual void* AllocBuffer(size_t size) = 0;
    virtual int CommitBuffer(size_t size) = 0;
    virtual const uint8_t* ReadFully(uint8_t* buf, size_t len) = 0;
    virtual const uint8_t* Read(uint8_t* buf, size_t* len) = 0;
    virtual int WriteFully(const uint8_t* buf, size_t len) = 0;

    uint8_t* Alloc(size_t len)
    {
        if (m_buf != nullptr && len > m_free) {
            Flush();
        }

        if (m_buf == nullptr || len > m_bufSize) {
            int allocLen = (m_bufSize < len) ? len : m_bufSize;
            m_buf = reinterpret_cast<uint8_t *>(AllocBuffer(allocLen));
            if (m_buf == nullptr) {
                return nullptr;
            }
            m_bufSize = allocLen;
            m_free = allocLen;
        }

        uint8_t *ptr = m_buf + (m_bufSize - m_free);
        m_free -= len;
        return ptr;
    }

    void Flush()
    {
        if (m_buf == nullptr || m_free == m_bufSize) {
            return;
        }
        m_state = CommitBuffer(m_bufSize - m_free);
        if (m_state < 0) {
            return;
        }
        m_buf = nullptr;
        m_free = 0;
        return;
    }

    const uint8_t* Readback(uint8_t *buf, size_t len)
    {
        Flush();
        return ReadFully(buf, len);
    }

    /**
     * @brief: initialize InstructionStream then return IStream* instance
     * @return: IStream*
     */
    static IStream* GetStream();

    virtual void WaitRebuildStateMachine()
    {
    }

    virtual void SetWaitRestore()
    {
    }

    virtual void NotifyRestoreFinished()
    {
    }

private:
    uint8_t* m_buf = nullptr;
    size_t m_bufSize = 0;
    size_t m_free = 0;
    int m_state = 0;

};

#endif
