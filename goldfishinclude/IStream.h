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
class VmiTransMatrix;
class VmiTexVideoEncode;

class IStream {
public:
    IStream() {}

    virtual ~IStream()
    {
        // NOTE: m_buf is 'owned' by the child class thus we expect it to be released by it
    }

    /**
     * @brief: initialize InstructionStream then return IStream* instance
     * @return: IStream*
     */
    static IStream* GetStream();

    virtual void WaitRebuildStateMachine() {}
};

#endif
