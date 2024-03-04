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

#include "../include/app_framework/Extensions/ExtEyeGaze.h"

#include "../include/app_framework/Linear.h"
#include "../include/app_framework/Logging.h"
#include "../include/app_framework/XrCore.h"

using namespace ml::Extensions;

std::vector<std::string> ExtEyeGaze::RequiredExtensions() {
  return std::vector<std::string>{XR_EXT_EYE_GAZE_INTERACTION_EXTENSION_NAME};
}

ExtEyeGaze::ExtEyeGaze(ml::XrCore *core)
    : core_(core),
      action_set_(XR_NULL_HANDLE),
      eye_gaze_intent_action_(XR_NULL_HANDLE),
      action_space_(XR_NULL_HANDLE) {
  if (!core_->IsExtensionEnabled(XR_EXT_EYE_GAZE_INTERACTION_EXTENSION_NAME)) {
    throw std::runtime_error(XR_EXT_EYE_GAZE_INTERACTION_EXTENSION_NAME
                             " extension not enabled!");
  }

  XrPosef pose_identity;
  Linear::XrCreateIdentity(pose_identity);

  // Create action set
  XrActionSetCreateInfo action_set_info{
      .type = XR_TYPE_ACTION_SET_CREATE_INFO, .next = nullptr, .priority = 0};
  strcpy(action_set_info.actionSetName, "eye_gaze_set");
  strcpy(action_set_info.localizedActionSetName, "EyeGazeSet");
  if (xrCreateActionSet(core->Instance(), &action_set_info, &action_set_) !=
      XR_SUCCESS) {
    throw std::runtime_error("xrCreateActionSet failed!");
  }

  // Create user intent action
  XrActionCreateInfo action_info{.type = XR_TYPE_ACTION_CREATE_INFO,
                                 .next = nullptr,
                                 .actionType = XR_ACTION_TYPE_POSE_INPUT,
                                 .countSubactionPaths = 0,
                                 .subactionPaths = nullptr};
  strcpy(action_info.actionName, "eye_gaze_intent");
  strcpy(action_info.localizedActionName, "Eye Gaze");
  if (xrCreateAction(action_set_, &action_info, &eye_gaze_intent_action_) !=
      XR_SUCCESS) {
    throw std::runtime_error("xrCreateAction failed!");
  }

  // Create suggested bindings
  XrPath eye_gaze_interaction_profile_path;
  if (xrStringToPath(core->Instance(),
                     "/interaction_profiles/ext/eye_gaze_interaction",
                     &eye_gaze_interaction_profile_path) != XR_SUCCESS) {
    throw std::runtime_error("xrStringToPath failed!");
  }

  XrPath gaze_pose_path;
  if (xrStringToPath(core->Instance(), "/user/eyes_ext/input/gaze_ext/pose",
                     &gaze_pose_path) != XR_SUCCESS) {
    throw std::runtime_error("xrStringToPath failed!");
  }

  const XrActionSuggestedBinding bindings{.action = eye_gaze_intent_action_,
                                          .binding = gaze_pose_path};

  const XrInteractionProfileSuggestedBinding suggested_bindings{
      .type = XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING,
      .next = nullptr,
      .interactionProfile = eye_gaze_interaction_profile_path,
      .countSuggestedBindings = 1,
      .suggestedBindings = &bindings};
  if (xrSuggestInteractionProfileBindings(core->Instance(),
                                          &suggested_bindings) != XR_SUCCESS) {
    throw std::runtime_error("xrSuggestInteractionProfileBindings failed!");
  }

  core_->RegisterActionSet(action_set_);

  const XrActionSpaceCreateInfo create_action_space_info{
      .type = XR_TYPE_ACTION_SPACE_CREATE_INFO,
      .next = nullptr,
      .action = eye_gaze_intent_action_,
      .subactionPath = {},
      .poseInActionSpace = pose_identity};
  if (xrCreateActionSpace(core->Session(), &create_action_space_info,
                          &action_space_) != XR_SUCCESS) {
    throw std::runtime_error("xrCreateActionSpace failed!");
  }
}

ExtEyeGaze::~ExtEyeGaze() {
  if (action_space_ != XR_NULL_HANDLE) {
    xrDestroySpace(action_space_);
    action_space_ = XR_NULL_HANDLE;
  }

  if (eye_gaze_intent_action_ != XR_NULL_HANDLE) {
    xrDestroyAction(eye_gaze_intent_action_);
    eye_gaze_intent_action_ = XR_NULL_HANDLE;
  }

  if (action_set_ != XR_NULL_HANDLE) {
    xrDestroyActionSet(action_set_);
    action_set_ = XR_NULL_HANDLE;
  }
}

bool ExtEyeGaze::Poll(bool &is_active) {
  if (core_->SessionState() != XR_SESSION_STATE_FOCUSED) {
    ALOGW("Poll called when session state is not XR_SESSION_STATE_FOCUSED.");
    return false;
  }

  const XrActiveActionSet active_action_set{action_set_, XR_NULL_PATH};
  XrActionsSyncInfo sync_info{XR_TYPE_ACTIONS_SYNC_INFO};
  sync_info.countActiveActionSets = 1;
  sync_info.activeActionSets = &active_action_set;
  if (XR_FAILED(xrSyncActions(core_->Session(), &sync_info))) {
    ALOGE("xrSyncActions failed");
    return false;
  }

  XrActionStatePose action_state_pose{XR_TYPE_ACTION_STATE_POSE};
  XrActionStateGetInfo get_info{XR_TYPE_ACTION_STATE_GET_INFO};
  get_info.action = eye_gaze_intent_action_;
  if (XR_FAILED(xrGetActionStatePose(core_->Session(), &get_info,
                                     &action_state_pose))) {
    ALOGE("xrGetActionStatePose failed!");
    return false;
  }

  is_active = action_state_pose.isActive == XR_TRUE;
  return true;
}

bool ExtEyeGaze::GetPose(XrTime time, XrPosef &eye_gaze_pose,
                         bool &is_nominal) {
  XrEyeGazeSampleTimeEXT eyeGazeSampleTime{XR_TYPE_EYE_GAZE_SAMPLE_TIME_EXT};
  XrSpaceLocation gazeLocation{XR_TYPE_SPACE_LOCATION, &eyeGazeSampleTime};
  const XrResult result =
      xrLocateSpace(action_space_, core_->WorldSpace(), time, &gazeLocation);
  if (XR_FAILED(result)) {
    ALOGE("xrLocateSpace failed: %d", result);
  } else {
    eye_gaze_pose = gazeLocation.pose;
    is_nominal =
        gazeLocation.locationFlags & XR_SPACE_LOCATION_POSITION_TRACKED_BIT;
  }
  return result == XR_SUCCESS;
}
