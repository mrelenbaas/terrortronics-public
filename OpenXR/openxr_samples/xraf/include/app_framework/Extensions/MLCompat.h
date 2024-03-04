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

#ifdef XR_USE_PLATFORM_ML

#include <algorithm>
#include <string>
#include <vector>

#include "../OpenXRCommon.h"

namespace ml {

class XrCore;

namespace Extensions {

/*! \brief ML Compat Extension
 *
 * This class implements support for
 * XR_ML_compat
 *
 * https://www.khronos.org/registry/OpenXR/specs/1.0/html/xrspec.html#XR_ML_compat
 *
 */
class MLCompat {
 public:
  MLCompat(XrCore* core);
  static std::vector<std::string> RequiredExtensions();

  /*! \brief Creates an XrSpace from a Magic Leap CFUID object.
   *
   * @param session the session to attach the space to.
   * @param createInfo the information used to create the space.
   * @param space the resulting space.
   * @return returns the result code.
   */
  XrResult xrCreateSpaceFromCoordinateFrameUIDML(
      XrSession session, const XrCoordinateSpaceCreateInfoML* createInfo,
      XrSpace* space) {
    if (!xrCreateSpaceFromCoordinateFrameUIDML_) {
      return XR_ERROR_FUNCTION_UNSUPPORTED;
    }
    return xrCreateSpaceFromCoordinateFrameUIDML_(session, createInfo, space);
  }

 private:
  XrCore* core_;
  PFN_xrCreateSpaceFromCoordinateFrameUIDML
      xrCreateSpaceFromCoordinateFrameUIDML_;
};

}  // namespace Extensions

}  // namespace ml
#endif /* XR_USE_PLATFORM_ML */