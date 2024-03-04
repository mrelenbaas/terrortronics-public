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

#include "../../addon_headers/XR_ML_system_notifications.h"

namespace ml {

class XrCore;

namespace Extensions {

/*! \brief The System Notifications extension
 *
 * This class implements support for
 * XR_ML_system_notifications
 *
 * Suppress/Unsuppress system notifications
 *
 * https://www.khronos.org/registry/OpenXR/specs/1.0/html/xrspec.html#XR_ML_system_notifications
 *
 */
class MLSystemNotifications {
 public:
  MLSystemNotifications(XrCore* core);
  ~MLSystemNotifications();
  static std::vector<std::string> RequiredExtensions();

  /*! \brief Sets whether system notifications are suppressed.
   *
   * @param is_suppressed flag whether to suppress system notifications.
   **/
  XrResult SetIsSuppressed(bool is_suppressed);

  /*! \brief Returns true if given system notifications flag is supported, false
   * otherwise. */
  bool IsSupported(uint64_t flag) const;

 private:
  XrCore* core_;
  PFN_xrSetSystemNotificationsML xrSetSystemNotificationsML_;
  XrFlags64 supported_features_;
};

}  // namespace Extensions

}  // namespace ml
