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

#include <openxr/openxr.h>

#include <algorithm>
#include <string>
#include <vector>

namespace ml {

class XrCore;

namespace Extensions {

/*! \brief The Global Dimmer extension
 *
 * This class implements support for
 * XR_ML_global_dimmer
 *
 * Enable/disable global dimming and set appropriate dimming values.
 *
 * https://www.khronos.org/registry/OpenXR/specs/1.0/html/xrspec.html#XR_ML_global_dimmer
 *
 */
class MLGlobalDimmer {
 public:
  MLGlobalDimmer(XrCore* core);
  ~MLGlobalDimmer();
  static std::vector<std::string> RequiredExtensions();

  /*! \brief Returns true if global dimmer is enabled. False otherwise. */
  bool IsEnabled() const;

  /*! \brief Returns current dimmer value. */
  float Value() const;

  /*! \brief Sets current dimmer value.
   *
   * @param dimmer_value dimming value, will be clamped to 0.f-1.f.
   *
   * This value will not be used, unless global dimmer is enabled.
   **/
  void SetValue(float dimmer_value);

  /*! \brief Sets whether global dimmer is enabled.
   *
   * @param is_enabled flag whether to use dimmer_value for dimming.
   **/
  void SetIsEnabled(bool is_enabled);

 private:
  XrCore* core_;
  XrGlobalDimmerFrameEndInfoML xr_global_dimmer_frame_end_info_;
};

}  // namespace Extensions

}  // namespace ml
