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

#include <openxr/openxr.h>

#include <algorithm>
#include <string>
#include <vector>

#include "../../addon_headers/XR_ML_user_calibration.h"

namespace ml {

class XrCore;

namespace Extensions {

/*! \brief Plane Detection
 *
 * This class implements support XR_ML_user_calibration extension.
 *
 * ToDo: Add public url once extension is published.
 *
 */
class MLUserCalibration {
 public:
  MLUserCalibration(XrCore* core);
  ~MLUserCalibration();
  static std::vector<std::string> RequiredExtensions();

  /*!
   * \brief Enable/disable the user calibration events.
   *
   * @param instance Previously created XrInstance.
   * @param enable_info Strucutre containing the enable/disable information.
   * @return Returns true if operation successful, false otherwise.
   */
  bool xrEnableUserCalibrationEventsML(
      XrInstance instance, XrUserCalibrationEnableEventsInfoML* enable_info) {
    return xrEnableUserCalibrationEventsML_(instance, enable_info);
  }

 private:
  XrCore* core_;
  PFN_xrEnableUserCalibrationEventsML xrEnableUserCalibrationEventsML_;
};

}  // namespace Extensions

}  // namespace ml
