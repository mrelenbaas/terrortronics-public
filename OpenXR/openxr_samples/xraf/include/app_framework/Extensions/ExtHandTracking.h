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

/*! \brief the Hand Tracking extension
 *
 * This class implements support for
 * XR_EXT_hand_tracking
 *
 * Simple Create using left or right hand and call
 * Locate to get the pose information for all the
 * key points.
 *
 * https://www.khronos.org/registry/OpenXR/specs/1.0/html/xrspec.html#XR_EXT_hand_tracking
 *
 */
class ExtHandTracking {
 public:
  ExtHandTracking(XrCore *core, XrHandEXT hand);
  ~ExtHandTracking();
  static std::vector<std::string> RequiredExtensions();

  /*! \brief Update the hand pose information.
   *
   * @param time time to predict the pose for.
   * @param is_active returns if the pose information is active
   * @return returns false if there was an error calling the underlying API.
   *
   * Use Locations or Velocities to get that information.
   *
   */
  bool Locate(XrTime time, bool &is_active);

  /*! \brief Returns the keypoint pose information. (if available)
   *
   * check the locationFlags for each keypoint for validity.
   * */
  const std::vector<XrHandJointLocationEXT> &Locations() const {
    return locations_;
  }
  /*! \brief Returns the keypoint velocty information. (if available)
   *
   * check the velocityFlags for each keypoint for validity.
   * */
  const std::vector<XrHandJointVelocityEXT> &Velocities() const {
    return velocities_;
  }

 private:
  XrCore *core_;
  XrHandTrackerEXT tracker_;
  PFN_xrCreateHandTrackerEXT xrCreateHandTrackerEXT;
  PFN_xrDestroyHandTrackerEXT xrDestroyHandTrackerEXT;
  PFN_xrLocateHandJointsEXT xrLocateHandJointsEXT;

  std::vector<XrHandJointLocationEXT> locations_;
  std::vector<XrHandJointVelocityEXT> velocities_;
  XrHandJointLocationsEXT location_info_;
  XrHandJointVelocitiesEXT velocity_info_;
  XrHandJointsLocateInfoEXT locate_info_;
};

}  // namespace Extensions

}  // namespace ml
