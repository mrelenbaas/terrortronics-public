// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
// Copyright (c) 2022 Magic Leap, Inc. All Rights Reserved.
// Use of this file is governed by the Software License Agreement,
// located here: https://www.magicleap.com/software-license-agreement-ml2
// Terms and conditions applicable to third-party materials accompanying
// this distribution may also be found in the top-level NOTICE file
// appearing herein.
// %COPYRIGHT_END%
// ---------------------------------------------------------------------
// %BANNER_END%

#pragma once

#ifndef LOCAL_LOGGING
#include <android/log.h>

#define ALOG_VERBOSE ANDROID_LOG_VERBOSE
#define ALOG_FATAL ANDROID_LOG_FATAL
#define ALOG_ERROR ANDROID_LOG_ERROR
#define ALOG_DEBUG ANDROID_LOG_DEBUG
#define ALOG_WARN ANDROID_LOG_WARN
#define ALOG_INFO ANDROID_LOG_INFO
#else
#include <cstdarg>
#define ALOG_VERBOSE 0
#define ALOG_FATAL 1
#define ALOG_ERROR 2
#define ALOG_DEBUG 3
#define ALOG_WARN 4
#define ALOG_INFO 5
#endif

#ifndef ALOG_TAG
#define ALOG_TAG "com.magicleap.capi.xr_app_framework"
#endif

#ifndef ALOG
#ifdef LOCAL_LOGGING
#include <cstring>
#include <iostream>
inline void __local_log_print(int prio, const char *tag, const char *fmt, ...) {
  const int len = 1024;
  char tempBuff[len + 1];
  memset(tempBuff, 0, len);
  va_list arg;
  va_start(arg, fmt);
  size_t done = vsnprintf(tempBuff, len, fmt, arg);
  tempBuff[done] = '\0';
  va_end(arg);

#ifndef _WIN32
  const char *RED = "\033[;31m";
  const char *YELLOW = "\033[;33m";
  const char *RESET = "\033[0m";
  switch (prio) {
    case 6:
      std::cout << RED;
      break;
    case 5:
      std::cout << YELLOW;
      break;
  };
#endif
  std::cout << tag << " : level = " << prio << " : " << tempBuff << std::endl;
#ifndef _WIN32
  if (prio >= 5) {
    std::cout << RESET;
  }
#endif
}

#define ALOG(priority, tag, ...) __local_log_print(priority, tag, __VA_ARGS__)
#else
#define ALOG(priority, tag, ...) __android_log_print(priority, tag, __VA_ARGS__)
#endif
#endif

#ifndef ALOGV
#if LOG_NDEBUG
#define ALOGV(...) ((void)0)
#else
#define ALOGV(...) ((void)ALOG(ALOG_VERBOSE, ALOG_TAG, __VA_ARGS__))
#endif
#endif

#ifndef ALOGD
#define ALOGD(...) ((void)ALOG(ALOG_DEBUG, ALOG_TAG, __VA_ARGS__))
#endif

#ifndef ALOGI
#define ALOGI(...) ((void)ALOG(ALOG_INFO, ALOG_TAG, __VA_ARGS__))
#endif

#ifndef ALOGW
#define ALOGW(...) ((void)ALOG(ALOG_WARN, ALOG_TAG, __VA_ARGS__))
#endif

#ifndef ALOGE
#define ALOGE(...) ((void)ALOG(ALOG_ERROR, ALOG_TAG, __VA_ARGS__))
#endif

#ifndef ALOGA
#define ALOGA(...) ((void)ALOG(ALOG_FATAL, ALOG_TAG, __VA_ARGS__))
#endif

#ifndef ALOGF
#ifdef LOCAL_LOGGING
#define ALOGF(...)                                   \
  {                                                  \
    ((void)ALOG(ALOG_FATAL, ALOG_TAG, __VA_ARGS__)); \
    abort();                                         \
  }
#else
#define ALOGF(...) __android_log_assert("assert", ALOG_TAG, __VA_ARGS__)
#endif
#endif

#define ALOG_IF(priority, output_log, ...) \
  if (output_log) {                        \
    ALOG(priority, ALOG_TAG, __VA_ARGS__); \
  }
