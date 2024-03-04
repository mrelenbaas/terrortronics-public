// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
// Copyright (c) 2023 Magic Leap, Inc. All Rights Reserved.
// Use of this file is governed by the Software License Agreement,
// located here: https://www.magicleap.com/software-license-agreement-ml2
// Terms and conditions applicable to third-party materials accompanying
// this distribution may also be found in the top-level NOTICE file
// appearing herein.
// %COPYRIGHT_END%
// ---------------------------------------------------------------------
// %BANNER_END%

#include "app_framework/XrAppSimCore.h"

using namespace ml;

static std::function<void()> g_terminate_notifier;

#ifndef XR_USE_PLATFORM_WIN32
#include <signal.h>
#include <unistd.h>

void signal_handler(int s) {
  if (g_terminate_notifier) {
    g_terminate_notifier();
  }
}

void register_signal_handler() {
  signal(SIGINT, signal_handler);
}
#else
#include <stdio.h>
BOOL WINAPI signal_handler(DWORD fdwCtrlType) {
  switch (fdwCtrlType) {
    // Handle the CTRL-C signal.
    case CTRL_C_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_LOGOFF_EVENT:
    case CTRL_SHUTDOWN_EVENT:
      if (g_terminate_notifier) {
        g_terminate_notifier();
      }
      return TRUE;
    default:
      return FALSE;
  }
}
void register_signal_handler() {
  SetConsoleCtrlHandler(signal_handler, TRUE);
}
#endif

XrAppSimCore::XrAppSimCore(const std::string &app_name, struct android_app *app)
    : XrAndroidCore(app_name, app) {
  register_signal_handler();
  g_terminate_notifier = [this]() { FinishActivity(); };
}
