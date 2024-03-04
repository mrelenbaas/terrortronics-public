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

#include <functional>
#include <vector>

namespace ml {
namespace Scene {

class Node;

/*! \brief HitTest facilites easy hit testing of planes with rays */
class HitTest {
 public:
  HitTest() = default;
  ~HitTest() = default;

  /*! \brief Objects are registered by type to improve performance. */
  enum class HitGroups { GUI = 1 << 0 };

  /*! \brief The quad describing a surface to test a hit against. */
  struct HitQuad {
    XrVector3f center;  // Node Space
    XrVector3f normal;  // must be normalized.
  };

  /*! \brief The structure used to register a set of quads as a hit target. */
  struct Registration {
    Scene::Node *node;
    std::vector<HitQuad> hit_quads;
    XrVector3f bounding_box;  // centered on node space
    uint64_t hit_group;       // bitmask, bit 1 reserved for GUI.
  };

  /*! \brief The structure used to perform a hit test. */
  struct Request {
    uint64_t hit_group;
    XrVector3f ray_center;     // in world coordinates
    XrVector3f ray_direction;  // normalized in world coordinates
    float max_distance;
  };

  /*! \brief The Hit Results */
  struct Result {
    Scene::Node *node;
    XrVector3f position;       // world coordinates
    XrVector3f node_position;  // intersect in node coordinates.
    float distance;            // distance along ray
    size_t quad_index;         // index of the quad that was hit.
  };

  /*! \brief Used to register an object as a hit target. */
  void Register(const Registration &info);

  /*! \brief Used to unregister an object as a hit target. */
  void Unregister(Scene::Node *node);

  /*! \brief Clear all registrations. */
  void Clear() {
    hit_registrations_.clear();
  }

  /*! \brief Find which object is hit by the ray in hit_test_info.
   *
   * @returns false if no hit was found.
   * */
  bool Test(const Request &hit_test_info, Result &hit_info);

 private:
  std::vector<Registration> hit_registrations_;
};
}  // namespace Scene
}  // namespace ml
