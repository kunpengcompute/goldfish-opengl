// Copyright 2018 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdlib.h>

#include <atomic>
#include <cassert>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <thread>

#include "cutils/log.h"
#include "cutils/properties.h"
#include "cutils/threads.h"

extern "C" {

int property_get(const char* key, char* value, const char* default_value) {
  return 0;
}

int __android_log_print(int priority, const char* tag, const char* format,
                        ...) {
  if (priority == ANDROID_LOG_VERBOSE || priority == ANDROID_LOG_DEBUG) {
    return 1;
  }
  const char* local_tag = tag;
  if (!local_tag) {
    local_tag = "<NO_TAG>";
  }
  printf("%d %s ", priority, local_tag);
  va_list ap;
  va_start(ap, format);
  vprintf(format, ap);
  va_end(ap);
  printf("\n");
  return 1;
}

void __android_log_assert(const char* condition, const char* tag,
                          const char* format, ...) {
  const char* local_tag = tag;
  if (!local_tag) {
    local_tag = "<NO_TAG>";
  }
  printf("__android_log_assert: condition: %s tag: %s ", condition, local_tag);
  if (format) {
    va_list ap;
    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);
  }
  printf("\n");

  assert(0);
  exit(-1);
}

int sync_wait(int fd, int timeout) {
  return -1;
}

void* thread_store_get(thread_store_t* store) {
  return store->has_tls ? pthread_getspecific(store->tls) : nullptr;
}

void thread_store_set(thread_store_t* store,
                      void* value,
                      thread_store_destruct_t destroy) {
    pthread_mutex_lock(&store->lock);
    if (!store->has_tls) {
        if (pthread_key_create(&store->tls, destroy) != 0) {
            pthread_mutex_unlock(&store->lock);
            return;
        }
        store->has_tls = 1;
    }
    pthread_mutex_unlock(&store->lock);
    pthread_setspecific(store->tls, value);
}

pid_t gettid() {
  static thread_local pid_t id = 0;
  if (!id) {
    static std::atomic<pid_t> next_thread_id{1};
    id = next_thread_id++;
  }
  return id;
}

}
