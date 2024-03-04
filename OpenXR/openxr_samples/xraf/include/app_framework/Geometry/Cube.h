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

#include <cstdint>
#include <string>

#include "../Components/Mesh.h"

namespace ml {

namespace Geometry {

/*! \brief 3d Cube Geometry.
 *
 * 1x1x1 cube with origin in it's center.
 * */
namespace Cube {

inline std::shared_ptr<Components::Mesh> LineFactory() {
  auto mesh = std::make_shared<Components::Mesh>();
  mesh->ToVertexVector({{
                           // pos
                           {-0.5f, -0.5f, -0.5f},
                           {-0.5f, -0.5f, +0.5f},
                           {-0.5f, +0.5f, -0.5f},
                           {-0.5f, +0.5f, +0.5f},
                           {+0.5f, -0.5f, -0.5f},
                           {+0.5f, -0.5f, +0.5f},
                           {+0.5f, +0.5f, -0.5f},
                           {+0.5f, +0.5f, +0.5f},
                       }},
                       {{}},
                       {{
                           // colors
                           {0.0f, 0.0f, 0.0f, 1.0f},
                           {0.0f, 0.0f, 1.0f, 1.0f},
                           {0.0f, 1.0f, 0.0f, 1.0f},
                           {0.0f, 1.0f, 1.0f, 1.0f},
                           {1.0f, 0.0f, 0.0f, 1.0f},
                           {1.0f, 0.0f, 1.0f, 1.0f},
                           {1.0f, 1.0f, 0.0f, 1.0f},
                           {1.0f, 1.0f, 1.0f, 1.0f},
                       }},
                       {{
                           // uv
                       }});
  mesh->indices = {{
      // indices
      // front
      0,
      4,
      4,
      6,
      6,
      2,
      2,
      0,
      // Back
      1,
      5,
      5,
      7,
      7,
      3,
      3,
      1,
      // Left
      5,
      4,
      7,
      6,
      // Right
      1,
      0,
      3,
      2,
  }};
  mesh->type = ml::Components::Mesh::LINES;
  mesh->material->use_material = false;
  return mesh;
}

inline std::shared_ptr<Components::Mesh> TriangleFactory() {
  auto mesh = std::make_shared<Components::Mesh>();
  mesh->ToVertexVector({{
                           // pos
                           // front
                           {-0.5f, -0.5f, 0.50f},
                           {-0.5f, 0.5f, 0.5f},
                           {0.5f, 0.5f, 0.5f},
                           {0.5f, -0.5f, 0.5f},
                           // back
                           {0.5f, -0.5f, -0.50f},
                           {0.5f, 0.5f, -0.5f},
                           {-0.5f, 0.5f, -0.5f},
                           {-0.5f, -0.5f, -0.5f},
                           // left
                           {-0.5f, -0.5f, -0.50f},
                           {-0.5f, 0.5f, -0.5f},
                           {-0.5f, 0.5f, 0.5f},
                           {-0.5f, -0.5f, 0.5f},
                           // right
                           {0.5f, -0.5f, 0.50f},
                           {0.5f, 0.5f, 0.5f},
                           {0.5f, 0.5f, -0.5f},
                           {0.5f, -0.5f, -0.5f},
                           // top
                           {-0.5f, 0.5f, 0.50f},
                           {-0.5f, 0.5f, -0.5f},
                           {0.5f, 0.5f, -0.5f},
                           {0.5f, 0.5f, 0.5f},
                           // bottom
                           {0.5f, -0.5f, -0.50f},
                           {-0.5f, -0.5f, -0.5f},
                           {-0.5f, -0.5f, 0.5f},
                           {0.5f, -0.5f, 0.5f},
                       }},
                       {{
                           // normals
                           // front
                           {0.0, 0.0f, -1.0f},
                           {0.0, 0.0f, -1.0f},
                           {0.0, 0.0f, -1.0f},
                           {0.0, 0.0f, -1.0f},

                           // back
                           {0.0, 0.0f, 1.0f},
                           {0.0, 0.0f, 1.0f},
                           {0.0, 0.0f, 1.0f},
                           {0.0, 0.0f, 1.0f},

                           // left
                           {-1.0, 0.0f, 0.0f},
                           {-1.0, 0.0f, 0.0f},
                           {-1.0, 0.0f, 0.0f},
                           {-1.0, 0.0f, 0.0f},

                           // right
                           {1.0, 0.0f, 0.0f},
                           {1.0, 0.0f, 0.0f},
                           {1.0, 0.0f, 0.0f},
                           {1.0, 0.0f, 0.0f},

                           // top
                           {0.0, 1.0f, 0.0f},
                           {0.0, 1.0f, 0.0f},
                           {0.0, 1.0f, 0.0f},
                           {0.0, 1.0f, 0.0f},

                           // bottom
                           {0.0, -1.0f, 0.0f},
                           {0.0, -1.0f, 0.0f},
                           {0.0, -1.0f, 0.0f},
                           {0.0, -1.0f, 0.0f},

                       }},
                       {{
                           // colors
                           {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},
                           {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},

                           {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},
                           {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},

                           {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},
                           {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},

                           {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},
                           {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},

                           {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},
                           {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},

                           {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},
                           {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},
                       }},
                       {{
                           // uv
                           // front
                           {0.000000f, 1.000000f},
                           {0.000000f, 0.000000f},
                           {1.000000f, 0.000000f},
                           {1.000000f, 1.000000f},
                           // back
                           {0.000000f, 1.000000f},
                           {0.000000f, 0.000000f},
                           {1.000000f, 0.000000f},
                           {1.000000f, 1.000000f},
                           // left
                           {0.000000f, 1.000000f},
                           {0.000000f, 0.000000f},
                           {1.000000f, 0.000000f},
                           {1.000000f, 1.000000f},
                           // right
                           {0.000000f, 1.000000f},
                           {0.000000f, 0.000000f},
                           {1.000000f, 0.000000f},
                           {1.000000f, 1.000000f},
                           // top
                           {0.000000f, 1.000000f},
                           {0.000000f, 0.000000f},
                           {1.000000f, 0.000000f},
                           {1.000000f, 1.000000f},
                           // bottom
                           {0.000000f, 1.000000f},
                           {0.000000f, 0.000000f},
                           {1.000000f, 0.000000f},
                           {1.000000f, 1.000000f},
                       }});
  mesh->indices = {{
      // indices
      // front
      0,
      3,
      2,
      0,
      2,
      1,
      // back
      4,
      7,
      6,
      4,
      6,
      5,
      // left
      8,
      11,
      10,
      8,
      10,
      9,
      // right
      12,
      15,
      14,
      12,
      14,
      13,
      // top
      16,
      19,
      18,
      16,
      18,
      17,
      // bottom
      20,
      23,
      22,
      20,
      22,
      21,
  }};
  mesh->type = ml::Components::Mesh::TRIANGLE;
  mesh->material->base_color = XrColor4f{1.0f, 1.0f, 1.0f, 1.0f};
  return mesh;
}
};  // namespace Cube
}  // namespace Geometry
}  // namespace ml
