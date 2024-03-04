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

/*! \brief The End Frame Info extension
 *
 * This class implements support for
 * XR_ML_frame_end_info
 *
 * Enable/disable vignette and protected surfaces, as well as set focus
 * distance.
 *
 * The default value of focus_distance is set to 0 meters. The system interprets
 * this as "the application has not set a focus_distance" and uses the far_clip
 * distance for processing (see ml_graphics.h).
 *
 * While far_clip is a fair initial approximation, ideally the application
 * provides real world focus distance of objects that the user is interacting
 * with. The system expects that focus distance may change with each frame.
 */
class MLFrameEndInfo {
 public:
  MLFrameEndInfo(XrCore* core);
  ~MLFrameEndInfo();
  static std::vector<std::string> RequiredExtensions();

  /*! \brief Returns true if vignette is enabled. False otherwise. */
  bool IsVignetteEnabled() const;

  /*! \brief Sets whether vignette is enabled.
   *
   * @param is_enabled flag to enable or disable vignette.
   **/
  void SetIsVignetteEnabled(bool is_enabled);

  /*! \brief Returns true if protected surface is enabled. False otherwise. */
  bool IsProtectedEnabled() const;

  /*! \brief Sets whether protected surface is enabled.
   *
   * @param is_enabled flag to enable or disable protected surface.
   **/
  void SetIsProtectedEnabled(bool is_enabled);

  /*! \brief Returns current focus distance in meters. */
  float GetFocusDistance() const;

  /*! \brief Sets current focus distance (meters).
   *
   * @param focus_distance value in meters (clamped between 0 and 1000 meters)
   **/
  void SetFocusDistance(float focus_distance);

 private:
  XrCore* core_;
  XrFrameEndInfoML xr_end_frame_info_ext_;
};

}  // namespace Extensions

}  // namespace ml
