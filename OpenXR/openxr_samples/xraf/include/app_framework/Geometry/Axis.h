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

/*! \brief 3d Axis Geometry.
 *
 * 1x1x1 axis with it's origin at the intersection of the 3 axis.
 *
 * */

namespace Axis {

// x = RED (right)
// y = GREEN (up)
// z = BLUE (forward)
inline std::shared_ptr<Components::Mesh> LineFactory() {
  auto mesh = std::make_shared<Components::Mesh>();
  mesh->ToVertexVector({{
                           // pos
                           {0.0f, 0.0f, 0.0f},
                           {0.0f, 0.0f, 0.0f},
                           {0.0f, 0.0f, 0.0f},
                           {1.0f, 0.0f, 0.0f},
                           {0.0f, 1.0f, 0.0f},
                           {0.0f, 0.0f, 1.0f},
                       }},
                       {{
                           // normals
                       }},
                       {{
                           // colors
                           {1.0f, 0.0f, 0.0f, 1.0f},
                           {0.0f, 1.0f, 0.0f, 1.0f},
                           {0.0f, 0.0f, 1.0f, 1.0f},
                           {1.0f, 0.0f, 0.0f, 1.0f},
                           {0.0f, 1.0f, 0.0f, 1.0f},
                           {0.0f, 0.0f, 1.0f, 1.0f},
                       }},
                       {{
                           // uv
                       }});
  mesh->indices = {{// indices
                    0, 3, 1, 4, 2, 5, 0}};
  mesh->type = ml::Components::Mesh::LINES;
  mesh->material->use_material = false;
  return mesh;
}

};  // namespace Axis

}  // namespace Geometry

}  // namespace ml
