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

#include "../include/app_framework/Extensions/ExtHandInteraction.h"
#include "../include/app_framework/Linear.h"
#include "../include/app_framework/Logging.h"

using namespace ml::Extensions;

std::vector<std::string> ExtHandInteraction::RequiredExtensions() {
  return std::vector<std::string>{XR_EXT_HAND_INTERACTION_EXTENSION_NAME};
}

ExtHandInteraction::ExtHandInteraction(ml::XrCore* core)
    : core_(core) {
  if (!core_->IsExtensionEnabled(XR_EXT_HAND_INTERACTION_EXTENSION_NAME)) {
    throw std::runtime_error(XR_EXT_HAND_INTERACTION_EXTENSION_NAME
                             " extension not enabled!");
  }
}

ExtHandInteraction::~ExtHandInteraction() {
  auto posture_count = static_cast<uint32_t>(HandPosture::HandPostureCount);
  auto type_count = static_cast<uint32_t>(HandActionType::HandActionTypeCount);
  for (uint32_t hand = 0; hand < HandCount; ++hand) { // Hand
    auto posture = static_cast<uint32_t>(HandPosture::Aim);
    for(; posture < posture_count; ++posture) { // Posture type
      auto type = static_cast<uint32_t>(HandActionType::Pose);
      const auto p = static_cast<HandPosture>(posture);
      for(; type < type_count; ++type) { // Action type
        const auto t = static_cast<HandActionType>(type);
        HandInteractionKey key = { .hand_side = static_cast<HandSide>(hand), .posture = p, .type = t };
        if (action_map_.count(key) != 0) {
          xrDestroyAction(action_map_[key]);
        }
        if (action_set_map_.count(key) != 0) {
          xrDestroyActionSet(action_set_map_[key]);
        }
        if (space_map_.count(key) != 0) {
          xrDestroySpace(space_map_[key]);
        }
      }
    }
  }
}

bool ExtHandInteraction::AddXrPath(HandSide hand_side, HandPosture posture, HandActionType type) {
  std::string result;
  switch(type) {
    case HandActionType::Pose:
      result = GetXrPoseString(hand_side, posture);
      break;
    case HandActionType::Value:
      result = GetXrValueString(hand_side, posture);
      break;
    case HandActionType::Ready:
      result = GetXrReadyString(hand_side, posture);
      break;
    default:
      break;
  }
  if (result.empty()) {
    return false;
  }
  HandInteractionKey key = { .hand_side = hand_side,
                             .posture = posture,
                             .type = type };
  return AddXrStringPath(key, result.c_str());
}

bool ExtHandInteraction::AddXrStringPath(const HandInteractionKey key, const char* string_path) {
  XrPath path;
  auto instance = core_->Instance();
  if (xrStringToPath(instance, string_path, &path) != XR_SUCCESS) {
    return false;
  }
  path_map_[key] = path;
  return true;
}

bool ExtHandInteraction::BindExtension(bool initialize_paths) {
  // Optionally, initialize all paths first
  const auto posture_count = static_cast<uint32_t>(HandPosture::HandPostureCount);
  const auto type_count = static_cast<uint32_t>(HandActionType::HandActionTypeCount);
  if (initialize_paths) {
    for (uint32_t hand = 0; hand < HandCount; ++hand) { // Hand
      auto posture = static_cast<uint32_t>(HandPosture::Aim);
      for (; posture < posture_count; ++posture) {
        auto type = static_cast<uint32_t>(HandActionType::Pose);
        for (; type < type_count; ++type) {
          AddXrPath(static_cast<HandSide>(hand),
                    static_cast<HandPosture>(posture),
                    static_cast<HandActionType>(type));
        }
      }
    }
  }
  // Check for configured paths
  if (path_map_.size() == 0) {
    ALOGE("Found no paths for Hand interaction extension");
    return false;
  }
  // Create Actions, iterate through potential interaction keys
  for (uint32_t hand = 0; hand < HandCount; ++hand) { // Hand
    auto hand_side = static_cast<HandSide>(hand);
    auto posture = static_cast<uint32_t>(HandPosture::Aim);
    for (; posture < posture_count; ++posture) {
      auto type = static_cast<uint32_t>(HandActionType::Pose);
      // Create action sets for hand and posture type
      HandInteractionKey key = { .hand_side = hand_side,
                                 .posture = static_cast<HandPosture>(posture),
                                 .type = static_cast<HandActionType>(type) };
      // Create action set
      if (!CreateActionSet(key)) {
        continue;
      }
      // Iterate through each action type
      for (; type < type_count; ++type) {
        // Update Key
        key.type = static_cast<HandActionType>(type);
        if (CreateAction(key)) {
          // Add to bindings for suggested bindings later
          interaction_bindings_.push_back({
            action_map_[key],
            path_map_[key]
          });
        }
      }
    }
  }
  if (interaction_bindings_.size() == 0) {
    ALOGE("Found no interaction bindings");
    return false;
  }
  auto instance = core_->Instance();
  XrPath hand_interaction;
  if (xrStringToPath(instance, HandInteractionExtensionPath, &hand_interaction) != XR_SUCCESS) {
    ALOGE("Failed to get xrpath for hand interaction profile");
    return false;
  }
  // Check suggested bindings from interaction bindings
  const XrInteractionProfileSuggestedBinding interaction_suggested_bindings{
      .type = XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING,
      .next = nullptr,
      .interactionProfile = hand_interaction,
      .countSuggestedBindings =
          static_cast<uint32_t>(interaction_bindings_.size()),
      .suggestedBindings = interaction_bindings_.data()};

  if (xrSuggestInteractionProfileBindings(
          core_->Instance(), &interaction_suggested_bindings) != XR_SUCCESS) {
    ALOGE("Failed to get suggested bindings");
    return false;
  }
  // Create spaces and register action sets
  for (uint32_t hand = 0; hand < HandCount; ++hand) { // Hand
    auto hand_side = static_cast<HandSide>(hand);
    auto posture = static_cast<uint32_t>(HandPosture::Aim);
    for (; posture < posture_count; ++posture) {
      // Create spaces
      XrActionSpaceCreateInfo space_info{XR_TYPE_ACTION_SPACE_CREATE_INFO};
      // Ensure pose action exists in posture and hand type
      HandInteractionKey key = { .hand_side = hand_side,
                                 .posture = static_cast<HandPosture>(posture),
                                 .type = HandActionType::Pose};
      if (action_map_.count(key) == 0) { continue; }
      space_info.action = action_map_[key];
      space_info.poseInActionSpace.orientation.w = 1.f;
      space_info.subactionPath = XR_NULL_PATH;
      space_map_[key] = {};
      if (xrCreateActionSpace(core_->Session(), &space_info, &space_map_[key]) != XR_SUCCESS) {
        ALOGE("xrCreateActionSpace failed for %s!", PostureToString(key.posture));
        return false;
      }
      // Register action set
      if (action_set_map_.count(key) == 0) {
        ALOGE("Failed to find action set for %s %s",
              (key.hand_side == HandSide::Left ? "Left" : "Right"),
              PostureToString(key.posture));
      }
      core_->RegisterActionSet(action_set_map_[key]);
      active_sets_.push_back({action_set_map_[key], XR_NULL_PATH});
    }
  }
  return true;
}

bool ExtHandInteraction::Sync(XrTime time) {
  time_ = time;
  XrActionsSyncInfo sync_info{XR_TYPE_ACTIONS_SYNC_INFO};
  sync_info.countActiveActionSets = static_cast<uint32_t>(active_sets_.size());
  sync_info.activeActionSets = active_sets_.data();
  if (XR_FAILED(xrSyncActions(core_->Session(), &sync_info))) {
    ALOGE("xrSyncActions failed");
    return false;
  }
  return true;
}

bool ExtHandInteraction::IsReadyExt(const HandPosture posture,
                                 HandSide hand_side,
                                 bool& ready) {
  if (core_->SessionState() != XR_SESSION_STATE_FOCUSED) {
    ALOGE("Not focused");
    return false;
  }
  if (posture == HandPosture::PokeEXT) {
    ready = false;
    return true;
  }
  HandInteractionKey key = { .hand_side = hand_side,
                             .posture = posture,
                             .type = HandActionType::Ready};
  if (action_map_.count(key) == 0) {
    return false;
  }
  XrAction action = action_map_[key];
  XrActionStateBoolean ready_state{XR_TYPE_ACTION_STATE_BOOLEAN};
  if (PollReady(action, ready_state)) {
    if (!ready_state.isActive) {
      ALOGE("Detected inactive ready action for %s", PostureToString(posture));
      return false;
    }
    ready = ready_state.currentState;
    return true;
  }
  return false;
}

bool ExtHandInteraction::GetPose(const HandPosture posture,
                                 HandSide hand_side,
                                 XrPosef& pose) {
  static const uint32_t track_flags = XR_SPACE_LOCATION_POSITION_VALID_BIT |
                                      XR_SPACE_LOCATION_ORIENTATION_VALID_BIT |
                                      XR_SPACE_LOCATION_POSITION_TRACKED_BIT;
  if (core_->SessionState() != XR_SESSION_STATE_FOCUSED) {
    ALOGE("Not focused");
    return false;
  }
  HandInteractionKey key = { .hand_side = hand_side,
                             .posture = posture,
                             .type = HandActionType::Pose};
  if (action_map_.count(key) == 0 ||
      space_map_.count(key) == 0) {
    return false;
  }
  XrAction action = action_map_[key];
  XrSpace space = space_map_[key];
  XrActionStatePose pose_state{XR_TYPE_ACTION_STATE_POSE};
  if (PollPose(action, pose_state)) {
    if (!pose_state.isActive) {
      ALOGE("Detected inactive pose action for %s", PostureToString(posture));
      return false;
    }
  } else {
    return false;
  }

  XrSpaceLocation location{XR_TYPE_SPACE_LOCATION};
  const XrResult result =
      xrLocateSpace(space, core_->WorldSpace(), time_, &location);
  if (XR_FAILED(result)) {
    ALOGE("xrLocateSpace failed: %d", result);
  } else {
    pose = location.pose;
  }
  return result == XR_SUCCESS &&
    (location.locationFlags & track_flags) == track_flags;
}

bool ExtHandInteraction::GetValue(const HandPosture posture,
                                  HandSide hand_side,
                                  float& value) {
  if (core_->SessionState() != XR_SESSION_STATE_FOCUSED) {
    ALOGE("Not focused");
    return false;
  }
  if (posture == HandPosture::PokeEXT) {
    value = 0.f;
    return true;
  }
  HandInteractionKey key = { .hand_side = hand_side,
                             .posture = posture,
                             .type = HandActionType::Value};
  if (action_map_.count(key) == 0) {
    return false;
  }
  XrAction action = action_map_[key];
  XrActionStateFloat action_value{XR_TYPE_ACTION_STATE_FLOAT};
  if (PollValue(action, action_value)) {
     if (!action_value.isActive) {
      ALOGE("Detected inactive value action for %s", PostureToString(posture));
      return false;
    }
    value = action_value.currentState;
    return true;
  }
  return false;
}

bool ExtHandInteraction::PollReady(XrAction& action,
                                    XrActionStateBoolean& state) {
  XrActionStateGetInfo get_info{XR_TYPE_ACTION_STATE_GET_INFO};
  get_info.action = action;
  if (xrGetActionStateBoolean(core_->Session(), &get_info, &state) !=
      XR_SUCCESS) {
    ALOGE("Failed to get action state: ready");
    return false;
  }
  return state.currentState;
}

bool ExtHandInteraction::PollValue(XrAction& action,
                                   XrActionStateFloat& state) {
  XrActionStateGetInfo get_info{XR_TYPE_ACTION_STATE_GET_INFO};
  get_info.action = action;
  if (xrGetActionStateFloat(core_->Session(), &get_info, &state) !=
      XR_SUCCESS) {
    ALOGE("Failed to get action state: value");
    return false;
  }
  return true;
}

bool ExtHandInteraction::PollPose(XrAction& action, XrActionStatePose& state) {
  XrActionStateGetInfo get_info{XR_TYPE_ACTION_STATE_GET_INFO};
  get_info.action = action;
  if (xrGetActionStatePose(core_->Session(), &get_info, &state) != XR_SUCCESS) {
    ALOGE("Failed to get action state: pose");
    return false;
  }
  return true;
}

bool ExtHandInteraction::CreateActionSet(const HandInteractionKey action_set_key) {
  static auto get_name = [this](const HandInteractionKey key, bool localized) {
    std::stringstream ss;
    char delimiter = localized ? ' ' : '_';
    ss << (key.hand_side == HandSide::Left ? "Left" : "Right") << delimiter <<
          PostureToString(key.posture);
    std::string result = ss.str();
    if (localized) {
      return result;
    } else {
      std::transform(result.begin(), result.end(), result.begin(), ::tolower);
      return result;
    }
  };
  XrActionSetCreateInfo action_set_info{
      .type = XR_TYPE_ACTION_SET_CREATE_INFO, .next = nullptr, .priority = 0};
  std::string name = get_name(action_set_key, false);
  std::string localized_name = get_name(action_set_key, true);
  strcpy(action_set_info.actionSetName, name.c_str());
  strcpy(action_set_info.localizedActionSetName, localized_name.c_str());
  XrActionSet set;
  ALOGD("Creating action set for: %s", localized_name.c_str());
  if (xrCreateActionSet(core_->Instance(), &action_set_info, &set) !=
      XR_SUCCESS) {
    ALOGE("Failed creating action set for: %s", localized_name.c_str());
    return false;
  }
  // Add set to map
  action_set_map_[action_set_key] = set;
  return true;
}

bool ExtHandInteraction::CreateAction(const HandInteractionKey action_key) {
  HandInteractionKey set_key = { .hand_side = action_key.hand_side,
                                 .posture = action_key.posture,
                                 .type = HandActionType::Pose };
  static auto get_name = [this](const HandInteractionKey key, bool localized) {
    std::stringstream ss;
    char delimiter = localized ? ' ' : '_';
    ss << PostureToString(key.posture) << delimiter << HandActionTypeToString(key.type);
    std::string result = ss.str();
    if (localized) {
      return result;
    } else {
      std::transform(result.begin(), result.end(), result.begin(), ::tolower);
      return result;
    }
  };
  if (action_set_map_.count(set_key) == 0) {
    ALOGE("Attempted to create action with no matching action set");
    return false;
  }
  // Poke does not have a ready or value action type supported
  if (action_key.posture == HandPosture:: PokeEXT &&
      (action_key.type == HandActionType::Ready || action_key.type == HandActionType::Value)) {
    return false;
  }
  XrActionCreateInfo action_info{XR_TYPE_ACTION_CREATE_INFO};
  XrActionType action_type = ActionTypeFromKey(action_key);
  std::string name = get_name(action_key, false);
  std::string localized_name = get_name(action_key, true);
  strcpy(action_info.actionName, name.c_str());
  ALOGD("Creating action for: %s", localized_name.c_str());
  action_info.actionType = action_type;
  strcpy(action_info.localizedActionName, localized_name.c_str());
  XrAction action;
  if (xrCreateAction(action_set_map_[set_key], &action_info, &action) != XR_SUCCESS) {
    ALOGE("Failed creating action for: %s", name.c_str());
    return false;
  }
  // Add action to map
  action_map_[action_key] = action;
  return true;
}
