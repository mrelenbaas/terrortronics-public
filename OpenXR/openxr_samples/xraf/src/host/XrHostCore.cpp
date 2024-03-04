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

#include "../include/app_framework/XrHostCore.h"

#include <app_framework/Utils/AndroidHelper.h>

#include <chrono>

#include "../include/app_framework/IGuiBackend.h"
#include "../include/app_framework/Logging.h"
#include "../include/app_framework/OpenXRCommon.h"

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

XrHostCore::XrHostCore(const std::string &app_name)
    : XrCore(app_name), finish_(false) {
  register_signal_handler();
  g_terminate_notifier = [this]() { FinishActivity(); };
}

void XrHostCore::RenderLoop() {
  if (IsInitialized()) {
    graphics_device_->StartOfRenderLoop();
  }

  // Start delta_time timer
  using namespace std::chrono;
  high_resolution_clock timer;
  auto start = timer.now();
  while (!finish_) {
    auto stop = timer.now();
    float delta_time_s = duration_cast<duration<float>>(stop - start).count();
    start = stop;

    bool exit_render_loop;
    bool request_restart;
    PollEvents(&exit_render_loop, &request_restart);
    if (exit_render_loop) {
      FinishActivity();
    }
    if (IsInitialized()) {
      PollActions();
      callbacks_.OnUpdate(delta_time_s);
      RenderFrame();
    }
  }
  ALOGV("RenderLoop Finish");
}

void XrHostCore::FinishActivity() {
  finish_ = true;
}

extern void android_main(struct android_app *state);

int main(int argc, char *argv[]) {
  android_app app{argc, argv, 0};
  android_main(&app);
  return app.result;
}
