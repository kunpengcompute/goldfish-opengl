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

class IStream {
public:
    IStream() {}

    virtual ~IStream() {}

    static IStream* GetStream();

    virtual void WaitRebuildStateMachine() {}
};

#endif
