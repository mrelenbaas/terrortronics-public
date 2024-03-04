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

#include <tuple>

#include "../Geometry/Ray.h"
#include "../Scene/Node.h"
#include "Component.h"

namespace ml {

namespace Components {

class Controller;
/*! Shared Pointer type of the Controller Component. */
using ControllerPtr = std::shared_ptr<Components::Controller>;

/*! \brief Component that has a ray for interaction with Scene::HitTest or
 * ImGui's */
class Controller : public IComponent {
 public:
  /*! \brief Create a new controller component. */
  static std::tuple<ControllerPtr, Scene::Node *> Factory() {
    auto node = new ml::Scene::Node();
    auto ray_mesh_node_ = new Scene::Node();
    node->AddChild(ray_mesh_node_);
    auto ray = ml::Geometry::Ray::LineFactory();
    ray_mesh_node_->AddComponent(ray);

    auto controller = std::make_shared<Controller>();
    controller->ray_mesh_node_ = ray_mesh_node_;
    node->AddComponent(controller);
    return std::make_tuple(controller, node);
  }

  /*! \brief Change the ray length.
   *
   * @param length in meters
   *
   * Great for terminating the ray when it intersects with a GUI.
   */
  void SetRayLength(float length) {
    ray_mesh_node_->SetScale(length);
  }

  /*! \brief Sets the Pose of the Ray */
  void SetPose(const XrPosef &pose) {
    auto parent = ray_mesh_node_->Parent();
    if (parent) {
      parent->SetPose(pose);
    }
  }

  /*! \brief Hide the ray. */
  void Hide() {
    ray_mesh_node_->SetVisible(false);
  }

  /*! \brief Show the ray. */
  void Show() {
    ray_mesh_node_->SetVisible(true);
  }

  /*! \brief Returns the node this Gui is attached to. */
  Scene::Node *Node() const {
    return ray_mesh_node_->Parent();
  }

 private:
  Scene::Node *ray_mesh_node_;
};

}  // namespace Components

}  // namespace ml
