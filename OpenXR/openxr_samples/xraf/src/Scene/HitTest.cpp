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

#include "../../include/app_framework/Scene/HitTest.h"

#include <algorithm>

#include "../../include/app_framework/Linear.h"
#include "../../include/app_framework/Scene/Node.h"

using namespace ml::Scene;
using namespace ml::Linear;

void HitTest::Register(const Registration &info) {
  hit_registrations_.push_back(info);
}

void HitTest::Unregister(Node *node) {
  assert(node != nullptr);
  auto it = std::find_if(
      hit_registrations_.begin(), hit_registrations_.end(),
      [node](const Registration &info) { return info.node == node; });
  if (it == hit_registrations_.end()) {
    return;
  }
  hit_registrations_.erase(it);
}

// TODO this can be optimized
bool HitTest::Test(const Request &hit_test_info, Result &hit_result) {
  bool have_hit = false;
  hit_result.node = nullptr;
  hit_result.distance = hit_test_info.max_distance;

  for (const auto &reg : hit_registrations_) {
    // are we part of a hit group?
    if ((hit_test_info.hit_group & reg.hit_group) == 0) {
      continue;
    }

    if (!reg.node->Visible()) {
      continue;
    }

    XrMatrix4x4f node_T_world = reg.node->WorldTransform();

    for (size_t i = 0; i < reg.hit_quads.size(); i++) {
      const auto &quad = reg.hit_quads[i];
      XrVector3f plane_normal;
      XrVector4f plane_normal_4;
      XrVector4f quad_normal{quad.normal.x, quad.normal.y, quad.normal.z, 1.0f};
      XrVector3f plane_center;

      XrMatrix4x4f invert, invert_transpose;
      XrInvert(invert, node_T_world);
      XrTranspose(invert_transpose, invert);
      XrTransform(plane_normal_4, invert_transpose, quad_normal);
      plane_normal.x = plane_normal_4.x;
      plane_normal.y = plane_normal_4.y;
      plane_normal.z = plane_normal_4.z;

      XrTransform(plane_center, node_T_world, quad.center);

      float distance;
      bool has_intersected = ml::Linear::XrIntersect(
          hit_test_info.ray_center, hit_test_info.ray_direction, plane_center,
          plane_normal, distance);

      if (!has_intersected) {
        continue;
      }

      if (distance > hit_result.distance) {
        continue;
      }

      XrVector3f intersect;
      XrScale(intersect, hit_test_info.ray_direction, distance);
      XrAdd(intersect, intersect, hit_test_info.ray_center);

      XrVector3f local;
      XrMatrix4x4f world_T_node;
      XrInvert(world_T_node, node_T_world);
      XrTransform(local, world_T_node, intersect);

      if (fabs(local.x) <= reg.bounding_box.x * 0.5f &&
          fabs(local.y) <= reg.bounding_box.y * 0.5f &&
          fabs(local.z) <= reg.bounding_box.z * 0.5f) {
        hit_result.distance = distance;
        hit_result.node = reg.node;
        hit_result.position = intersect;
        hit_result.quad_index = i;
        hit_result.node_position = local;
        have_hit = true;
      }
    }
  }
  return have_hit;
}
