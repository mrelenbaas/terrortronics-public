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

#include <memory>

#include "../Scene/Node.h"
#include "../XrCore.h"
#include "Component.h"

namespace ml {

namespace Components {

class ViewFollower;
using ViewFollowerPtr = std::shared_ptr<ViewFollower>;

/*! \brief Component that makes a node follow the view. */
class ViewFollower : public IComponent {
 public:
  enum Flags { NONE = 0, SMOOTH = 1 << 0, UPRIGHT = 1 << 1 };

  ViewFollower(uint32_t flags, Scene::Node *node, XrPosef target_pose,
               XrCore *core)
      : smooth_((flags & SMOOTH) != 0),
        upright_((flags & UPRIGHT) != 0),
        node_(node),
        target_pose_(target_pose),
        core_(core),
        moving_(false) {
    {
      auto target = Linear::XrCreatePose(core->HeadPoseOrigin(), target_pose_);
      node_->SetPose(target);
    }

    view_callback_registration_id_ =
        core->RegisterForViewPoseUpdates([this](const XrPosef &pose) {
          auto target = Linear::XrCreatePose(pose, target_pose_);
          if (smooth_) {
            XrVector3f direction;
            Linear::XrSub(direction, target.position, node_->Translation());
            float distance = Linear::XrMagnitude(direction);
            if (!moving_ && distance < 0.50f) {  // 10 cm threshold.
              return;
            }
            moving_ = true;
            Linear::XrScale(direction, direction, distance);
            distance *= distance;
            const double speed = fmin(0.1f, distance);
            XrVector3f d_p;
            Linear::XrScale(d_p, direction, speed);
            Linear::XrAdd(target.position, node_->Translation(), d_p);
            if (distance < 0.05f) {
              moving_ = false;
            }
          }
          if (upright_) {
            target.orientation.x = 0.0f;
            target.orientation.z = 0.0f;
            Linear::XrNormalize(target.orientation);
          }
          node_->SetPose(target);
        });
  }

  ~ViewFollower() {
    core_->UnregisterFromViewPoseUpdates(view_callback_registration_id_);
  }

  static std::tuple<ViewFollowerPtr, Scene::Node *> Factory(uint32_t flags,
                                                            XrPosef target_pose,
                                                            XrCore *core) {
    auto *node = new Scene::Node();
    auto follower =
        std::make_shared<ViewFollower>(flags, node, target_pose, core);
    node->AddComponent(follower);
    return std::make_tuple(follower, node);
  }

 private:
  bool smooth_;
  bool upright_;
  Scene::Node *node_;
  XrPosef target_pose_;
  XrCore *core_;
  bool moving_;
  uint32_t view_callback_registration_id_;
};

}  // namespace Components
}  // namespace ml
