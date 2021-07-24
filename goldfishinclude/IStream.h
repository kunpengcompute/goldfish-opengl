/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2017-2021. All rights reserved.
 * Description:  IStream for goldfish-opengl
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the Apache License version 2
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * Apache License for more details.
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
