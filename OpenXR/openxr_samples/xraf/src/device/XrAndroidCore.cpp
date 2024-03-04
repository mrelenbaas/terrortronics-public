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

#include "../include/app_framework/XrAndroidCore.h"

#include <chrono>

#include "../include/app_framework/IGuiBackend.h"
#include "../include/app_framework/Logging.h"
#include "../include/app_framework/OpenXRCommon.h"

using namespace ml;

XrAndroidCore::XrAndroidCore(const std::string &app_name,
                             struct android_app *app)
    : XrCore(app_name), app_(app), resumed_(false), has_native_window_(false) {
}

int32_t XrAndroidCore::HandleInput(struct android_app *app,
                                   AInputEvent *event) {
  ALOGI("Event received");
  return 0;
}

// Life Cycle handling
void XrAndroidCore::HandleCmd(struct android_app *app, int32_t cmd) {
  auto self = reinterpret_cast<XrAndroidCore *>(app->userData);
  switch (cmd) {
    case APP_CMD_START:
      ALOGI("APP_CMD_START");
      break;
    case APP_CMD_INIT_WINDOW:
      ALOGI("APP_CMD_INIT_WINDOW");
      self->has_native_window_ = true;
      break;
    case APP_CMD_TERM_WINDOW:
      ALOGI("APP_CMD_TERM_WINDOW");
      self->has_native_window_ = false;
      break;
    case APP_CMD_RESUME:
      ALOGI("APP_CMD_RESUME");
      self->resumed_ = true;
      break;
    case APP_CMD_GAINED_FOCUS:
      ALOGI("APP_CMD_GAINED_FOCUS");
      break;
    case APP_CMD_LOST_FOCUS:
      ALOGI("APP_CMD_LOST_FOCUS");
      break;
    case APP_CMD_PAUSE:
      ALOGI("APP_CMD_PAUSE");
      self->resumed_ = false;
      break;
    case APP_CMD_STOP:
      ALOGI("APP_CMD_STOP");
      break;
    case APP_CMD_SAVE_STATE:
      ALOGI("APP_CMD_SAVE_STATE");
      break;
    case APP_CMD_DESTROY:
      ALOGI("APP_CMD_DESTROY");
      break;
    case APP_CMD_LOW_MEMORY:
      ALOGI("APP_CMD_LOW_MEMORY");
      break;
    default:
      ALOGI("Unhandled APP_CMD: %d", cmd);
      break;
  }
}

void XrAndroidCore::RenderLoop() {
  // it is possible we had a startup error and are just cleaning up.
  if (IsInitialized()) {
    graphics_device_->StartOfRenderLoop();
  }

  ALOGV("RenderLoop Begin");
  // Register the callbacks.
  app_->userData = this;
  app_->onAppCmd = HandleCmd;
  app_->onInputEvent = HandleInput;

  // Start delta_time timer
  using namespace std::chrono;
  high_resolution_clock timer;
  auto start = timer.now();
  while (app_->destroyRequested == 0) {
    auto stop = high_resolution_clock::now();
    float delta_time_s = duration_cast<duration<float>>(stop - start).count();
    start = stop;

    bool exit_render_loop;
    bool request_restart;
    int events;
    struct android_poll_source *source = nullptr;

    // process all events from the Android system.
    while ((ALooper_pollAll(resumed_ ? 0 : -1, nullptr, &events,
                            (void **)&source)) >= 0) {
      // Process this event.
      if (source != nullptr) {
        source->process(app_, source);
      }

      if (app_->destroyRequested) {
        break;
      }

      // we need to poll here as well to make sure we
      // get the state change when dropping back to home
      // menu.
      PollEvents(&exit_render_loop, &request_restart);
    }

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

bool XrAndroidCore::CreateInstance(
    const std::vector<std::string> &extensions,
    const std::vector<std::string> &optional_extensions,
    const std::vector<XrEnvironmentBlendMode> &acceptable_blend_modes) {
#ifdef XR_USE_PLATFORM_ANDROID
  PFN_xrInitializeLoaderKHR xrInitializeLoaderKHR = nullptr;
  xrGetInstanceProcAddr(
      nullptr, "xrInitializeLoaderKHR",
      reinterpret_cast<PFN_xrVoidFunction *>(&xrInitializeLoaderKHR));
  XrLoaderInitInfoAndroidKHR init_loader{
      .type = XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR,
      .next = nullptr,
      .applicationVM = app_->activity->vm,
      .applicationContext = app_->activity->clazz};
  if ((xrInitializeLoaderKHR == nullptr) ||
      xrInitializeLoaderKHR(reinterpret_cast<XrLoaderInitInfoBaseHeaderKHR *>(
          &init_loader)) != XR_SUCCESS) {
    ALOGE("xrInitializeLoaderKHR failed");
    return false;
  }
#endif
  return XrCore::CreateInstance(extensions, optional_extensions,
                                acceptable_blend_modes);
}

void XrAndroidCore::FinishActivity() {
  ANativeActivity_finish(app_->activity);
}

bool XrAndroidCore::ProcessSingle(int milli_seconds) {
  int events;
  struct android_poll_source *source = nullptr;
  if ((ALooper_pollAll(milli_seconds, nullptr, &events, (void **)&source)) >=
      0) {
    // Process this event.
    if (source != nullptr) {
      source->process(app_, source);
    }
    bool exit_render_loop;
    bool request_restart;
    PollEvents(&exit_render_loop, &request_restart);
    return true;
  }
  return false;
}
