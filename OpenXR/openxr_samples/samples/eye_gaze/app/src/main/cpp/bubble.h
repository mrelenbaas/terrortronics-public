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

#include <app_framework/Components/GLTF.h>
#include <app_framework/XrCore.h>

using namespace ml::Linear;

namespace ml {

class Bubble {
 public:
  Bubble(XrCore *core, Scene::Node *root, int index)
      : state_(IDLE), core_(core) {
    std::string filename = "bubble_red.glb";
    switch (index % 3) {
      case 0:
        filename = "bubble_red.glb";
        break;
      case 1:
        filename = "bubble_green.glb";
        break;
      case 2:
        filename = "bubble_blue.glb";
        break;
    }
    std::tie(std::ignore, node_) = Components::GLTF::Factory(filename.c_str());
    root->AddChild(node_);
    node_->SetScale(0.05f);
    SetState(WAITING, 0);
  }

  enum State { IDLE, WAITING, FLOATING };

  void SetState(State state, XrTime time) {
    if (state == state_) {
      return;
    }
    state_ = state;
    switch (state) {
      case WAITING:
        time_left_ = std::rand() % 200;
        node_->SetVisible(false);
        break;
      case FLOATING: {
        time_left_ = 1600;
        XrSpaceLocation loc;
        loc.type = XR_TYPE_SPACE_LOCATION;
        loc.next = nullptr;
        float x, z;
        if (xrLocateSpace(core_->ViewSpace(), core_->WorldSpace(), time,
                          &loc) == XR_SUCCESS) {
          double angle = std::rand() % 360;
          double len = 0.5 + (float)std::rand() / ((float)RAND_MAX) * 0.50;
          x = loc.pose.position.x + cos(DegreeToRad(angle)) * len;
          z = loc.pose.position.z + sin(DegreeToRad(angle)) * len;
        } else {
          x = (float)std::rand() / (float)RAND_MAX;
          z = (float)std::rand() / (float)RAND_MAX;
        }

        node_->SetTranslation(x, -1.0f, z);
        node_->SetVisible(true);
        break;
      }
      case IDLE:
        time_left_ = 0;
        node_->SetVisible(false);
        break;
    }
  }

  bool Update(XrTime time, const XrVector3f &wind) {
    bool bubble_popped = false;
    time_left_--;

    switch (state_) {
      case WAITING:
        if (time_left_ <= 0) {
          SetState(FLOATING, time);
        }
        return bubble_popped;

      case IDLE:
        return bubble_popped;

      case FLOATING:
        auto pos = node_->Translation();
        // pop at the ceiling!
        if (time_left_ <= 0 || pos.y > 1.5f) {
          SetState(WAITING, time);
          bubble_popped = true;
        }
        break;
    }

    auto pos = node_->Translation();
    XrVector3f move{0.0f, 0.005f, 0.0f};
    XrAdd(pos, pos, move);
    XrAdd(pos, pos, wind);
    node_->SetTranslation(pos);
    return bubble_popped;
  }

  bool TestHit(const XrVector3f &pos) {
    if (!node_->Visible()) {
      return false;
    }
    auto bubble = node_->Translation();
    XrSub(bubble, bubble, pos);
    if (XrMagnitude(bubble) < 0.1f) {
      SetState(WAITING, 0);
      return true;
    }
    return false;
  }
  bool TestHitRay(const XrVector3f &ray_origin, const XrVector3f &ray_dir) {
    if (!node_->Visible()) {
      return false;
    }
    const XrVector3f bubble_center = node_->Translation();

    // Handpicked value based on tests, ideally should match sphere's radius
    const float bubble_radius = 0.025f;

    // Vector from the sphere's center to the ray's origin
    XrVector3f delta;
    XrSub(delta, ray_origin, bubble_center);

    // distance from the ray origin to the sphere center projected on the ray
    const float dist_to_center = XrDot(delta, ray_dir);

    // according to Pythagoras a^2 + b^2 - c^2 == 0
    // 'a' is dist from ray orig to a point on the ray that is sphere center
    // projected onto ray
    // 'b' is sphere radius here, NOT real dist from sphere
    // center to 'a'
    // 'c' is dist from ray orig to sphere center in straight line
    //
    // if we get result == 0,
    //      this means that dist from sphere center to 'a' is equal to sphere
    //      radius so exactly 1 collision point
    // if we get result < 0,
    //      this means that dist from sphere center to 'a' is bigger than the
    //      radius so 0 collision points
    // if we get result > 0,
    //      this means that dist from sphere center to 'a' is lower than the
    //      radius so 2 collision points
    //
    // tip: XrDot(vec1, vec1) == pow(XrMagnitude(vec1), 2)
    const float diff =
        pow(dist_to_center, 2) + pow(bubble_radius, 2) - XrDot(delta, delta);
    if (diff < 0.0) {
      return false;
    }

    // If we'd like to know exact intersection points:
    // const float diff_sqrt = sqrt(diff);
    // XrVector3f intersect1 = ray_origin + (-delta - diff_sqrt) * ray_dir;
    // XrVector3f intersect2 = ray_origin + (-delta + diff_sqrt) * ray_dir;

    SetState(WAITING, 0);
    return true;
  }

  Scene::Node *Node() const {
    return node_;
  }

 protected:
  Scene::Node *node_;
  int32_t time_left_;
  State state_;
  XrCore *core_;
};

}  // namespace ml