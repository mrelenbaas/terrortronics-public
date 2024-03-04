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

#include "XrCore.h"

namespace ml {
class XrHostCore : public XrCore {
 public:
  XrHostCore(const std::string &app_name);
  void RenderLoop() override;
  void FinishActivity() override;

 private:
  bool finish_;
};

}  // namespace ml
