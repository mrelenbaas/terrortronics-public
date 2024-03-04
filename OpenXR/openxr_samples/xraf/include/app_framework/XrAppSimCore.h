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
#pragma once

#include "XrAndroidCore.h"

// XrAppSimCore extends XrAndroidCore and allows for signal handling on host
// platforms.

namespace ml {
class XrAppSimCore : public XrAndroidCore {
 public:
  XrAppSimCore(const std::string &app_name, struct android_app *app);
};

}  // namespace ml
