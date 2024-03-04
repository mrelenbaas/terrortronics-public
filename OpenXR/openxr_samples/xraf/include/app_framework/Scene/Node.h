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

#include <any>
#include <atomic>
#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "../Components/Component.h"
#include "../Components/Mesh.h"
#include "../Linear.h"
#include "../Logging.h"
#include "../RefCount.h"

namespace ml {

namespace Scene {

/*!\brief Node class
 *
 * This is the class that builds the scene graph. Each node can contain other
 * nodes as children.
 *
 * Each node also can attached "Components" for example Vulkan Buffers.
 *
 * */
class Node : public RefCount, public Components::ComponentHolder {
 public:
  Node()
      : translation_{0.0f, 0.0f, 0.0f},
        scale_{1.0f, 1.0f, 1.0f},
        rotation_{0.0f, 0.0f, 0.0f, 1.0f},
        local_transform_dirty_{false},
        world_transform_dirty_{true},
        visible_{true},
        parent_{nullptr} {
    ml::Linear::XrCreateIdentity(transform_);
  }

  virtual ~Node() {
    Clear();
    ClearComponents();
    parent_ = nullptr;
  }

  // no copying please.
  Node(const Node &) = delete;
  Node &operator=(Node &) = delete;

  /*!\brief Add Child node */
  void AddChild(Node *child) {
    assert(child != nullptr);
    if (child->parent_ == this) {
      // already a child, nothing to do.
      return;
    }

    auto *parent = this;
    while (parent != nullptr) {
      if (child == parent) {
        throw std::runtime_error(
            "Circular reference, a child can not a parent to itself.");
      }
      parent = parent->parent_;
    }
    child->Acquire();
    child->SetOnSceneGraphChanged(scene_graph_changed_);
    if (child->parent_) {
      child->parent_->RemoveChild(child);
    }
    child->parent_ = this;
    children_.push_back(child);
    BroadcastChange(ADD);
  }

  /*!\brief Removes a Child node */
  void RemoveChild(Node *child) {
    assert(child != nullptr);

    RemoveFirst(children_, child);
    child->parent_ = nullptr;
    child->Release();
    BroadcastChange(REMOVE);
  }

  /*!\brief Set the visibility of a Child node */
  inline void SetVisible(bool visible) {
    visible_ = visible;
  }

  /*!\brief Visibility of a Child node */
  inline bool Visible() const {
    return visible_;
  }

  /*!\brief Local Transform */
  inline XrMatrix4x4f const &Transform() {
    if (local_transform_dirty_) {
      UpdateTransform();
    }
    return transform_;
  }

  /*!\brief Set Local Translation */
  inline void SetTranslation(const XrVector3f &translation) {
    translation_ = translation;
    local_transform_dirty_ = true;
    SetWorldTransformsDirty();
  }

  /*!\brief Set Local Translation */
  inline void SetTranslation(float x, float y, float z) {
    SetTranslation(XrVector3f{x, y, z});
  }
  /*!\brief Local Translation */
  inline XrVector3f const &Translation() const {
    return translation_;
  }
  /*!\brief Set Local Rotation */
  inline void SetRotation(const XrQuaternionf &rotation) {
    rotation_ = rotation;
    local_transform_dirty_ = true;
    SetWorldTransformsDirty();
  }

  /*!\brief Set Local Rotation */
  inline void SetRotation(float x, float y, float z, float w) {
    SetRotation(XrQuaternionf{x, y, z, w});
  }
  /*!\brief Local Rotation */
  inline XrQuaternionf const &Rotation() const {
    return rotation_;
  }
  /*!\brief Set Local Scale */
  inline void SetScale(const XrVector3f &scale) {
    scale_ = scale;
    local_transform_dirty_ = true;
    SetWorldTransformsDirty();
  }
  /*!\brief Set Local Scale */
  inline void SetScale(float scale) {
    SetScale(XrVector3f{scale, scale, scale});
  }
  /*!\brief Set Local Scale */
  inline void SetScale(float x, float y, float z) {
    SetScale(XrVector3f{x, y, z});
  }
  /*!\brief Local Scale */
  inline XrVector3f const &Scale() const {
    return scale_;
  }
  /*! \brief sets the combined translation and rotation */
  inline void SetPose(const XrPosef &pose) {
    SetTranslation(pose.position);
    SetRotation(pose.orientation);
  }
  /*! \brief Gets the combined translation and rotation */
  inline XrPosef Pose() const {
    return XrPosef{rotation_, translation_};
  }
  /*!\brief calls the visitor on each node in the tree
   *
   * return false from the visitor to abandon traversing
   * the current leg of the tree.
   *
   * */
  void VisitNodes(bool visible_only,
                  std::function<bool(Node *, const XrMatrix4x4f &)> visitor) {
    XrMatrix4x4f transform;
    ml::Linear::XrCreateIdentity(transform);
    Recurse(this, visible_only, transform, visitor);
  }

  /*!\brief Returns the child at index.
   *
   * returns nullptr if requested index is larger
   * or equal to the number of children. aka 0-based indexing.
   *
   * */
  Node *Child(size_t index) {
    if (index >= children_.size()) {
      return nullptr;
    }
    return children_[index];
  }

  /*! \brief Returns the child count. */
  size_t ChildCount() const {
    return children_.size();
  }

  /*! \brief Returns a const vector of children. */
  const std::vector<Node *> &Children() const {
    return children_;
  }

  /*! \brief Returns the parent node. */
  Node *Parent() const {
    return parent_;
  }

  /*! \brief Clears all children. */
  void Clear() {
    for (auto node : children_) {
      node->Release();
    }
    children_.clear();
  }

  enum SceneGraphChangeOperation { ADD, REMOVE, MESH_UPDATED };
  using OnSceneGraphChanged =
      std::function<void(Node *, SceneGraphChangeOperation operation)>;

  /*! \brief One listener can register for updates from each node.
   *
   * IMPORTANT
   *
   * Note that the scene graph implementation likely relies on this
   * to work, so please don't register a new change notifier unless
   * you call the old handler as well.
   *
   * */
  OnSceneGraphChanged SetOnSceneGraphChanged(
      OnSceneGraphChanged scene_graph_changed) {
    auto result = scene_graph_changed_;
    scene_graph_changed_ = scene_graph_changed;
    for (auto &child : children_) {
      child->SetOnSceneGraphChanged(scene_graph_changed);
    }
    return result;
  }

  /*! \brief Returns the world transform for the node. */
  XrMatrix4x4f const &WorldTransform();

  /*! \brief Broadcasts a chance like update mesh. */
  void BroadcastChange(SceneGraphChangeOperation reason) {
    if (scene_graph_changed_) {
      scene_graph_changed_(this, reason);
    }
  }

  /*! \brief Get the node name */
  const std::string &Name() {
    return name_;
  }

  /*! \brief Set the node name. */
  void SetName(const std::string &name) {
    name_ = name;
  }

  /*! \brief Deepcopy */
  Scene::Node *DeepCopy();

 private:
  XrVector3f translation_;
  XrVector3f scale_;
  XrQuaternionf rotation_;
  XrMatrix4x4f transform_;
  bool local_transform_dirty_;
  XrMatrix4x4f world_transform_;
  bool world_transform_dirty_;
  bool visible_;
  std::vector<Node *> children_;
  Node *parent_;
  OnSceneGraphChanged scene_graph_changed_;
  std::string name_;

  static void Recurse(
      Node *parent, bool visible_only, const XrMatrix4x4f &transform,
      const std::function<bool(Node *, const XrMatrix4x4f &)> &visitor);

  static void RecurseNoTransforms(Node *parent,
                                  const std::function<bool(Node *)> &visitor);
  ;

  static void RemoveFirst(std::vector<Node *> &nodes, const Node *child);

  void UpdateTransform();

  void SetWorldTransformsDirty();
};

}  // namespace Scene
}  // namespace ml