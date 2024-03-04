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

#include <array>
#include <string>
#include <vector>

namespace ml {

class XrCore;

namespace Extensions {

/*! \brief the Palm Pose extension
 *
 * This class implements support for
 * XR_EXT_palm_pose
 *
 * Simply create and call Poll to check for which
 * hand the pose is available and query the pose via
 * GetPose.
 *
 * https://www.khronos.org/registry/OpenXR/specs/1.0/html/xrspec.html#XR_EXT_palm_pose
 *
 */
class ExtPalmPose {
 public:
  ExtPalmPose(XrCore *core);
  ~ExtPalmPose();
  static std::vector<std::string> RequiredExtensions();

  enum Hand { Left, Right, Count };

  /*! \brief Get Palm pose information.
   *
   * @param time time to predict the pose for.
   * @param hand which hand to return pose for
   * @param palm_pose returns the pose
   * @param is_nominal returns if the pose is nominal (has high accuracy)
   *
   * @return returns false if there was an error calling the underlying API.
   */
  bool GetPose(XrTime time, Hand hand, XrPosef &palm_pose, bool &is_nominal);

  /*! \brief Update the Palm pose information
   *
   * Use GetPose to get that information if specific is_active_* was set to
   * true.
   *
   * @param is_active_left returns if the pose information is active for left
   * hand
   * @param is_active_right returns if the pose information is active for right
   * hand
   *
   * @return returns false if there was an error calling the underlying API.
   */
  bool Poll(bool &is_active_left, bool &is_active_right);

 private:
  const char *GetHandStr(const Hand hand);

  XrCore *core_;
  XrActionSet action_set_;
  std::array<XrAction, Hand::Count> actions_;
  std::array<XrSpace, Hand::Count> action_spaces_;
};

}  // namespace Extensions

}  // namespace ml
