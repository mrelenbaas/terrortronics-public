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

#include <string>
#include <vector>
#include <sstream>
#include <functional>
#include <unordered_map>

#include "../XrCore.h"

static constexpr const char* HandInteractionExtensionPath =
  "/interaction_profiles/ext/hand_interaction_ext";
namespace ml {

namespace Extensions {

enum class HandSide : uint8_t { Left = 0, Right };
enum class HandActionType : uint8_t { Pose = 0, Ready, Value, HandActionTypeCount};
enum class HandPosture : uint8_t { Aim = 0, Grip, PinchEXT, PokeEXT, HandPostureCount};
constexpr uint32_t HandCount = 2;
struct HandInteractionKey {
  HandSide hand_side = HandSide::Left;
  HandPosture posture = HandPosture::Aim;
  HandActionType type = HandActionType::Pose;
  bool operator==(const HandInteractionKey &other) const {
    return hand_side == other.hand_side &&
           posture == other.posture &&
           type == other.type;
  }
};

struct HandInteractionHash {
  std::size_t operator()(const HandInteractionKey& key) const {
    std::size_t hash = 0;
    std::hash<HandSide> side_hash;
    std::hash<HandPosture> posture_hash;
    std::hash<HandActionType> type_hash;
    hash ^= side_hash(key.hand_side) +
            0x9e3779b9 + (hash << 6) + (hash >> 2);
    hash ^= posture_hash(key.posture) +
            0x9e3779b9 + (hash << 6) + (hash >> 2);
    hash ^= type_hash(key.type) +
            0x9e3779b9 + (hash << 6) + (hash >> 2);
    return hash;
  }
};

using XrActionSetMap = std::unordered_map<HandInteractionKey, XrActionSet, HandInteractionHash>;
using XrActionMap = std::unordered_map<HandInteractionKey, XrAction, HandInteractionHash>;
using XrSpaceMap = std::unordered_map<HandInteractionKey, XrSpace, HandInteractionHash>;
using XrPathMap = std::unordered_map<HandInteractionKey, XrPath, HandInteractionHash>;

/*! \brief the Hand Interaction extension
 *
 * This class implements support for
 * XR_EXT_hand_interaction
 *
 * Create an instance
 * Call BindExention, or add paths one by one
 * And then call BindExtension(false)
 * Update by calling Sync
 * Use IsReadyExt, GetValue, GetPose
 * To get extension data
 *
 */
class ExtHandInteraction {
 public:
  ExtHandInteraction(XrCore* core);
  ~ExtHandInteraction();
  static std::vector<std::string> RequiredExtensions();
  bool BindExtension(bool initialize_paths = true);
  bool Sync(XrTime time);
  bool IsReadyExt(const HandPosture posture, HandSide hand_side, bool& ready);
  bool GetValue(const HandPosture posture, HandSide hand_side, float& value);
  bool GetPose(const HandPosture posture, HandSide hand_side, XrPosef& pose);

  const char* PostureToString(HandPosture posture) {
    switch (posture) {
      case HandPosture::Aim:
        return "Aim";
      case HandPosture::Grip:
        return "Grip";
      case HandPosture::PinchEXT:
        return "Pinch";
      case HandPosture::PokeEXT:
        return "Poke";
      default:
        return "";
    }
  }
  const char* HandActionTypeToString(HandActionType type) {
    switch (type) {
      case HandActionType::Pose:
        return "Pose";
      case HandActionType::Ready:
        return "Ready";
      case HandActionType::Value:
        return "Value";
      default:
        return "";
    }
  }

  const char* GetHandPath(HandSide hand) {
    return hand == HandSide::Left ? "/user/hand/left/input/" :
      "/user/hand/right/input/";
  }

  const char* GetPosePath(HandPosture posture) {
    switch (posture) {
      case HandPosture::Aim:
        return "aim/pose";
      case HandPosture::Grip:
        return "grip/pose";
      case HandPosture::PinchEXT:
        return "pinch_ext/pose";
      case HandPosture::PokeEXT:
        return "poke_ext/pose";
      default:
        throw std::runtime_error("Given bad posture type for pose path!");
        return "";
    }
  }

  const char* GetValuePath(HandPosture posture) {
    switch (posture) {
      case HandPosture::Aim:
        return "aim_activate_ext/value";
      case HandPosture::Grip:
        return "grasp_ext/value";
      case HandPosture::PinchEXT:
        return "pinch_ext/value";
      default:
        throw std::runtime_error("Given bad posture type for value path!");
        return "";
    }
  }

  const char* GetReadyPath(HandPosture posture) {
    switch (posture) {
      case HandPosture::Aim:
        return "aim_activate_ext/ready_ext";
      case HandPosture::Grip:
        return "grasp_ext/ready_ext";
      case HandPosture::PinchEXT:
        return "pinch_ext/pose";
      default:
        throw std::runtime_error("Given bad posture type for ready path!");
        return "";
    }
  }

  std::string GetXrPoseString(const HandSide hand_side,
                              const HandPosture posture) {
    try {
      return std::string(GetHandPath(hand_side)) +
                         std::string(GetPosePath(posture));
    } catch(std::exception _) {
      return std::string();
    }
  }

  std::string GetXrValueString(const HandSide hand_side,
                               const HandPosture posture) {
    try {
      return std::string(GetHandPath(hand_side)) +
                         std::string(GetValuePath(posture));
    } catch(std::exception _) {
      return std::string();
    }
  }

  std::string GetXrReadyString(const HandSide hand_side,
                               const HandPosture posture) {
    try {
      return std::string(GetHandPath(hand_side)) +
                         std::string(GetReadyPath(posture));

    } catch(std::exception _) {
      return std::string();
    }
  }
  bool AddXrPath(HandSide hand_side, HandPosture posture, HandActionType type);
  bool AddXrStringPath(const HandInteractionKey key, const char* string_path);

 private:
  XrCore* core_;
  XrTime time_;
  XrActionSetMap action_set_map_{};
  XrActionMap action_map_{};
  XrSpaceMap space_map_{};
  XrPathMap path_map_{};
  std::vector<XrActiveActionSet> active_sets_{};
  std::vector<XrActionSuggestedBinding> interaction_bindings_{};
  bool SetupHandActions(const std::string& hand, uint32_t hand_index);
  bool CreateActionSet(const HandInteractionKey action_set_key);
  bool CreateAction(const HandInteractionKey action_key);
  bool PollReady(XrAction& action, XrActionStateBoolean& state);
  bool PollValue(XrAction& action, XrActionStateFloat& state);
  bool PollPose(XrAction& action, XrActionStatePose& state);

  XrActionType ActionTypeFromKey(const HandInteractionKey key) {
    switch(key.type) {
      case HandActionType::Pose:
        return XR_ACTION_TYPE_POSE_INPUT;
      case HandActionType::Value:
        return XR_ACTION_TYPE_FLOAT_INPUT;
      case HandActionType::Ready:
        return XR_ACTION_TYPE_BOOLEAN_INPUT;
      default:
        throw std::runtime_error("Failed to get action type from hand action type");
    }
  }
};

}  // namespace Extensions

}  // namespace ml
