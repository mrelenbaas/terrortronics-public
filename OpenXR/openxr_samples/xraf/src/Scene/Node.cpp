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

#include "../include/app_framework/Scene/Node.h"

#include "../include/app_framework/Components/GLTF.h"
#include "../include/app_framework/Components/Sound.h"
using namespace ml::Scene;

void Node::SetWorldTransformsDirty() {
  RecurseNoTransforms(this, [](Node *node) -> bool {
    node->world_transform_dirty_ = true;
    return true;  // keep going.
  });
}

void Node::UpdateTransform() {
  local_transform_dirty_ = false;
  ml::Linear::XrCreateTranslationRotationScale(transform_, translation_,
                                               rotation_, scale_);
}
void Node::RemoveFirst(std::vector<Node *> &nodes, const Node *child) {
  bool first_occurrence = true;
  auto it = std::remove_if(nodes.begin(), nodes.end(),
                           [&first_occurrence, child](const Node *node) {
                             if (first_occurrence && node == child) {
                               first_occurrence = false;
                               return true;
                             }
                             return false;
                           });
  if (it == nodes.end()) {
    throw std::runtime_error("Not found.");
  }
  nodes.erase(it, nodes.end());
}

void Node::RecurseNoTransforms(Node *parent,
                               const std::function<bool(Node *)> &visitor) {
  if (!visitor(parent)) {
    return;
  }
  for (auto node : parent->children_) {
    RecurseNoTransforms(node, visitor);
  }
}

void Node::Recurse(
    Node *parent, bool visible_only, const XrMatrix4x4f &transform,
    const std::function<bool(Node *, const XrMatrix4x4f &)> &visitor) {
  if (visible_only && !parent->Visible()) {
    return;
  }

  XrMatrix4x4f node_transform;
  if (parent->world_transform_dirty_) {
    ml::Linear::XrMultiply(node_transform, transform, parent->Transform());
    parent->world_transform_ = node_transform;
    parent->world_transform_dirty_ = false;
  } else {
    node_transform = parent->world_transform_;
  }

  if (!visitor(parent, node_transform)) {
    return;
  }

  for (auto node : parent->children_) {
    Recurse(node, visible_only, node_transform, visitor);
  }
}

const XrMatrix4x4f &Node::WorldTransform() {
  if (!world_transform_dirty_ && !local_transform_dirty_) {
    return world_transform_;
  }

  std::vector<XrMatrix4x4f> transforms;
  Node *parent = this;
  while (parent) {
    transforms.push_back(parent->Transform());
    parent = parent->parent_;
  }
  XrMatrix4x4f transform;
  ml::Linear::XrCreateIdentity(transform);
  for (int32_t i = (int32_t)transforms.size() - 1; i >= 0; i--) {
    auto node = transforms[i];
    XrMatrix4x4f node_transform;
    ml::Linear::XrMultiply(node_transform, node, transform);
    transform = node_transform;
  }
  world_transform_dirty_ = false;
  world_transform_ = transform;
  return world_transform_;
}

Node *Node::DeepCopy() {
  Scene::Node *node = new Scene::Node();
  node->translation_ = translation_;
  node->scale_ = scale_;
  node->rotation_ = rotation_;
  node->transform_ = transform_;
  node->local_transform_dirty_ = local_transform_dirty_;
  node->world_transform_ = world_transform_;
  node->world_transform_dirty_ = world_transform_dirty_;
  node->visible_ = visible_;

  for (auto child : children_) {
    node->AddChild(child->DeepCopy());
  }

  node->ShareComponents(this, node);

  return node;
}
