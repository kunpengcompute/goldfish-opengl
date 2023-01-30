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
#ifndef __SMART_PTR_H
#define __SMART_PTR_H

#if PLATFORM_SDK_VERSION > 28
#include  <sys/types.h>

#if !defined(_WIN32)
#include <pthread.h>
#else
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_WIN32)

typedef pthread_mutex_t mutex_t;

static __inline__ void mutex_lock(mutex_t* lock) {
    pthread_mutex_lock(lock);
}

static __inline__ void mutex_unlock(mutex_t* lock) {
    pthread_mutex_unlock(lock);
}

static __inline__ int mutex_init(mutex_t* lock) {
    return pthread_mutex_init(lock, NULL);
}

static __inline__ void mutex_destroy(mutex_t* lock) {
    pthread_mutex_destroy(lock);
}

#else // !defined(_WIN32)

typedef struct {
    int init;
    CRITICAL_SECTION lock[1];
} mutex_t;

#define MUTEX_INITIALIZER  { 0, {{ NULL, 0, 0, NULL, NULL, 0 }} }

static __inline__ void mutex_lock(mutex_t* lock) {
    if (!lock->init) {
        lock->init = 1;
        InitializeCriticalSection( lock->lock );
        lock->init = 2;
    } else while (lock->init != 2) {
        Sleep(10);
    }
    EnterCriticalSection(lock->lock);
}

static __inline__ void mutex_unlock(mutex_t* lock) {
    LeaveCriticalSection(lock->lock);
}

static __inline__ int mutex_init(mutex_t* lock) {
    InitializeCriticalSection(lock->lock);
    lock->init = 2;
    return 0;
}

static __inline__ void mutex_destroy(mutex_t* lock) {
    if (lock->init) {
        lock->init = 0;
        DeleteCriticalSection(lock->lock);
    }
}

#endif // !defined(_WIN32)

#ifdef __cplusplus
}
#endif
#endif

#include <cutils/threads.h>
#include <cutils/atomic.h>

template <class T, bool threadSafe = false>
class SmartPtr
{
public:
    explicit SmartPtr(T* ptr = (T*)NULL) {
        if (threadSafe) {
            m_lock = new mutex_t;
            mutex_init(m_lock);
        }
        else m_lock = NULL;

        m_ptr = ptr;
        if (ptr)
           m_pRefCount = new int32_t(1);
        else
           m_pRefCount = NULL;
    }

    SmartPtr<T,threadSafe>(const SmartPtr<T,false>& rhs) {
        if (threadSafe) {
            m_lock = new mutex_t;
            mutex_init(m_lock);
        }
        else m_lock = NULL;

        m_pRefCount = rhs.m_pRefCount;
        m_ptr       = rhs.m_ptr;
        use();
    }

    SmartPtr<T,threadSafe>(SmartPtr<T,true>& rhs) {
        if (threadSafe) {
            m_lock = new mutex_t;
            mutex_init(m_lock);
        }
        else m_lock = NULL;

        if (rhs.m_lock) mutex_lock(rhs.m_lock);
        m_pRefCount = rhs.m_pRefCount;
        m_ptr       = rhs.m_ptr;
        use();
        if (rhs.m_lock) mutex_unlock(rhs.m_lock);
    }

    ~SmartPtr() {
        if (m_lock) mutex_lock(m_lock);
        release();
        if (m_lock)
        {
            mutex_unlock(m_lock);
            mutex_destroy(m_lock);
            delete m_lock;
        }
    }

    T* Ptr() const {
        return m_ptr;
    }

    const T* constPtr() const
    {
        return m_ptr;
    }

    T* operator->() const {
        return m_ptr;
    }

    T& operator*() const {
        return *m_ptr;
    }

    operator void*() const {
        return (void *)m_ptr;
    }

    // This gives STL lists something to compare.
    bool operator <(const SmartPtr<T>& t1) const {
        return m_ptr < t1.m_ptr;
    }

    SmartPtr<T,threadSafe>& operator=(const SmartPtr<T,false>& rhs)
    {
        if (m_ptr == rhs.m_ptr)
            return *this;

        if (m_lock) mutex_lock(m_lock);
        release();
        m_pRefCount = rhs.m_pRefCount;
        m_ptr       = rhs.m_ptr;
        use();
        if (m_lock) mutex_unlock(m_lock);

        return *this;
    }

    SmartPtr<T,threadSafe>& operator=(SmartPtr<T,true>& rhs)
    {
        if (m_ptr == rhs.m_ptr)
            return *this;

        if (m_lock) mutex_lock(m_lock);
        release();
        if (rhs.m_lock) mutex_lock(rhs.m_lock);
        m_pRefCount = rhs.m_pRefCount;
        m_ptr       = rhs.m_ptr;
        use();
        if (rhs.m_lock) mutex_unlock(rhs.m_lock);
        if (m_lock) mutex_unlock(m_lock);

        return *this;
    }

private:
    int32_t  *m_pRefCount;
    mutex_t  *m_lock;
    T* m_ptr;

    // Increment the reference count on this pointer by 1.
    int use() {
        if (!m_pRefCount) return 0;
        return android_atomic_inc(m_pRefCount) + 1;
    }

    // Decrement the reference count on the pointer by 1.
    // If the reference count goes to (or below) 0, the pointer is deleted.
    int release() {
        if (!m_pRefCount) return 0;

        int iVal = android_atomic_dec(m_pRefCount);
        if (iVal > 1)
            return iVal - 1;

        delete m_pRefCount;
        m_pRefCount = NULL;

        if (m_ptr) {
            delete m_ptr;
            m_ptr = NULL;
        }
        return 0;
    }

};

#endif // of  __SMART_PTR_H
