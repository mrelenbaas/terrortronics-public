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

#include <string>
#include <vector>

namespace ml {

class XrCore;

namespace Extensions {

/*! \brief the Eye Gaze extension
 *
 * This class implements support for
 * XR_EXT_eye_gaze_interaction
 *
 * Simply create instance and call Poll in OnUpdate
 * to check if Eye Gaze pose is available in current frame,
 * then retrieve the data using GetPose (possibly called in OnPreRender.
 *
 * https://www.khronos.org/registry/OpenXR/specs/1.0/html/xrspec.html#XR_EXT_eye_gaze_interaction
 *
 */
class ExtEyeGaze {
 public:
  ExtEyeGaze(XrCore *core);
  ~ExtEyeGaze();
  static std::vector<std::string> RequiredExtensions();

  /*! \brief Get Eye Gaze pose information.
   *
   * @param time time to predict the pose for.
   * @param eye_gaze_pose returns the pose
   * @param is_nominal returns if the pose is nominal (has high accuracy)
   *
   * @return returns false if there was an error calling the underlying API.
   */
  bool GetPose(XrTime time, XrPosef &eye_gaze_pose, bool &is_nominal);

  /*! \brief Update the Eye Gaze pose information
   *
   * Use GetPose to get that information if is_active was set to true.
   *
   * @param is_active returns if the pose information is active
   *
   * @return returns false if there was an error calling the underlying API.
   */
  bool Poll(bool &is_active);

 private:
  XrCore *core_;
  XrActionSet action_set_;
  XrAction eye_gaze_intent_action_;
  XrSpace action_space_;
};

}  // namespace Extensions

}  // namespace ml
