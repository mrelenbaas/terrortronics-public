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

#include "../include/app_framework/Extensions/ExtPalmPose.h"

#include "../include/app_framework/Linear.h"
#include "../include/app_framework/Logging.h"
#include "../include/app_framework/XrCore.h"

using namespace ml::Extensions;

std::vector<std::string> ExtPalmPose::RequiredExtensions() {
  return std::vector<std::string>{XR_EXT_PALM_POSE_EXTENSION_NAME};
}

ExtPalmPose::ExtPalmPose(ml::XrCore *core)
    : core_(core), action_set_(XR_NULL_HANDLE) {
  if (!core_->IsExtensionEnabled(XR_EXT_PALM_POSE_EXTENSION_NAME)) {
    throw std::runtime_error(XR_EXT_PALM_POSE_EXTENSION_NAME
                             " extension not enabled!");
  }

  XrPosef pose_identity;
  Linear::XrCreateIdentity(pose_identity);

  // Create action set
  XrActionSetCreateInfo action_set_info{
      .type = XR_TYPE_ACTION_SET_CREATE_INFO, .next = nullptr, .priority = 0};
  strcpy(action_set_info.actionSetName, "palm_pose_set");
  strcpy(action_set_info.localizedActionSetName, "Palm Pose Set");
  if (xrCreateActionSet(core->Instance(), &action_set_info, &action_set_) !=
      XR_SUCCESS) {
    throw std::runtime_error("xrCreateActionSet failed!");
  }

  const char *component_path = "/input/palm_ext/pose";
  const std::string action_name_prefix = "palm_pose_";
  const std::string localized_action_name_prefix = "Palm Pose ";
  std::vector<XrActionSuggestedBinding> bindings;

  // Create action, path and bindings for each hand
  for (int hand = 0; hand < Hand::Count; hand++) {
    const std::string hand_str = GetHandStr(static_cast<Hand>(hand));
    const std::string action_name = action_name_prefix + hand_str;
    const std::string localized_action_name =
        localized_action_name_prefix + hand_str;
    XrActionCreateInfo action_info{.type = XR_TYPE_ACTION_CREATE_INFO,
                                   .next = nullptr,
                                   .actionType = XR_ACTION_TYPE_POSE_INPUT,
                                   .countSubactionPaths = 0,
                                   .subactionPaths = nullptr};
    strcpy(action_info.actionName, action_name.c_str());
    strcpy(action_info.localizedActionName, localized_action_name.c_str());
    if (xrCreateAction(action_set_, &action_info, &actions_[hand]) !=
        XR_SUCCESS) {
      throw std::runtime_error("xrCreateAction failed for " + action_name);
    }

    XrPath palm_pose_path;
    const std::string pose_path = "/user/hand/" + hand_str + component_path;
    if (xrStringToPath(core->Instance(), pose_path.c_str(), &palm_pose_path) !=
        XR_SUCCESS) {
      throw std::runtime_error("xrStringToPath failed for " + pose_path);
    }

    bindings.push_back(
        XrActionSuggestedBinding{actions_[hand], palm_pose_path});
  }

  const std::vector<const char *> interaction_profiles{
      "/interaction_profiles/ml/ml2_controller",
      "/interaction_profiles/khr/simple_controller"};
  // Suggest bindings for all interaction profiles
  for (const auto &interaction_profile : interaction_profiles) {
    XrPath interaction_profile_path;
    if (xrStringToPath(core->Instance(), interaction_profile,
                       &interaction_profile_path) != XR_SUCCESS) {
      throw std::runtime_error("xrStringToPath failed for " +
                               std::string(interaction_profile));
    }

    XrInteractionProfileSuggestedBinding suggested_bindings{
        .type = XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING,
        .next = nullptr,
        .interactionProfile = interaction_profile_path,
        .countSuggestedBindings = static_cast<uint32_t>(bindings.size()),
        .suggestedBindings = bindings.data()};

    if (xrSuggestInteractionProfileBindings(
            core->Instance(), &suggested_bindings) != XR_SUCCESS) {
      throw std::runtime_error(
          "xrSuggestInteractionProfileBindings failed for " +
          std::string(interaction_profile));
    }
  }

  // Register action set now that we've created and binded actions
  core_->RegisterActionSet(action_set_);

  // Create action space for each hand
  for (int hand = 0; hand < Hand::Count; hand++) {
    XrActionSpaceCreateInfo create_action_space_info{
        .type = XR_TYPE_ACTION_SPACE_CREATE_INFO,
        .next = nullptr,
        .action = actions_[hand],
        .subactionPath = {},
        .poseInActionSpace = pose_identity};
    if (xrCreateActionSpace(core->Session(), &create_action_space_info,
                            &action_spaces_[hand]) != XR_SUCCESS) {
      throw std::runtime_error("xrCreateActionSpace failed!");
    }
  }
}

const char *ExtPalmPose::GetHandStr(const Hand hand) {
  switch (hand) {
    case Hand::Left:
      return "left";
    case Hand::Right:
      return "right";
    default:
      throw std::runtime_error("Unkown Hand value passed to " +
                               std::string(__func__));
  }
}

ExtPalmPose::~ExtPalmPose() {
  for (auto &action_space : action_spaces_) {
    if (action_space != XR_NULL_HANDLE) {
      xrDestroySpace(action_space);
      action_space = XR_NULL_HANDLE;
    }
  }

  for (auto &action : actions_) {
    if (action != XR_NULL_HANDLE) {
      xrDestroyAction(action);
      action = XR_NULL_HANDLE;
    }
  }

  if (action_set_ != XR_NULL_HANDLE) {
    xrDestroyActionSet(action_set_);
    action_set_ = XR_NULL_HANDLE;
  }
}

bool ExtPalmPose::Poll(bool &is_active_left, bool &is_active_right) {
  if (core_->SessionState() != XR_SESSION_STATE_FOCUSED) {
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
  get_info.action = actions_[Hand::Left];
  if (XR_FAILED(xrGetActionStatePose(core_->Session(), &get_info,
                                     &action_state_pose))) {
    ALOGE("xrGetActionStatePoseL failed!");
    return false;
  }

  is_active_left = action_state_pose.isActive == XR_TRUE;

  action_state_pose = {XR_TYPE_ACTION_STATE_POSE};
  get_info.action = actions_[Hand::Right];
  if (XR_FAILED(xrGetActionStatePose(core_->Session(), &get_info,
                                     &action_state_pose))) {
    ALOGE("xrGetActionStatePoseR failed!");
    return false;
  }

  is_active_right = action_state_pose.isActive == XR_TRUE;
  return true;
}

bool ExtPalmPose::GetPose(XrTime time, Hand hand, XrPosef &palm_pose, bool &is_nominal) {
  if (hand != Left && hand != Right) {
    ALOGE("Unknown hand value given: %d", hand);
    return false;
  }
  XrSpaceLocation space_location{XR_TYPE_SPACE_LOCATION};
  const XrResult result = xrLocateSpace(
      action_spaces_[hand], core_->WorldSpace(), time, &space_location);
  if (XR_FAILED(result)) {
    ALOGE("xrLocateSpace failed: %d", result);
  } else {
    palm_pose = space_location.pose;
    is_nominal =
        space_location.locationFlags & XR_SPACE_LOCATION_POSITION_TRACKED_BIT;
  }
  return result == XR_SUCCESS;
}