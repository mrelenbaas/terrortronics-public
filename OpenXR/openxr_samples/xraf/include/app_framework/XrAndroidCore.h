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

#include "Utils/AndroidHelper.h"
#include "XrCore.h"

namespace ml {
class XrAndroidCore : public XrCore {
 public:
  XrAndroidCore(const std::string &app_name, struct android_app *app);
  // IAssetManagerPtr AssetManager() override;
  void RenderLoop() override;
  void FinishActivity() override;

  // workaround for platform hang in xrWaitSwapchainImage
  bool ProcessSingle(int milli_seconds);
  bool HasNativeWindow() const {
    return has_native_window_;
  }

 private:
  struct android_app *app_;
  bool resumed_;
  bool has_native_window_;
  bool CreateInstance(const std::vector<std::string> &extensions,
                      const std::vector<std::string> &optional_extensions,
                      const std::vector<XrEnvironmentBlendMode>
                          &acceptable_blend_modes) override;
  static void HandleCmd(struct android_app *app, int32_t cmd);
  static int32_t HandleInput(struct android_app *app, AInputEvent *event);
};

}  // namespace ml
