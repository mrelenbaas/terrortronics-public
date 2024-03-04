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

/*! \brief Ray pointing in the -Z direction. */
namespace Ray {

inline std::shared_ptr<Components::Mesh> LineFactory() {
  auto mesh = std::make_shared<Components::Mesh>();
  mesh->ToVertexVector({{
                           // pos
                           {0.0f, 0.0f, 0.0f},
                           {0.0f, 0.0f, -0.75f},
                           {0.0f, 0.0f, -0.85f},
                           {0.0f, 0.0f, -1.0f},
                       }},
                       {{
                           // normals
                       }},
                       {{
                           // colors
                           {0.0f, 0.0f, 0.9f, 0.0f},
                           {0.0f, 0.9f, 0.9f, 1.0f},
                           {1.0f, 1.0f, 1.0f, 1.0f},
                           {1.0f, 1.0f, 1.0f, 1.0f},
                       }},
                       {{
                           // uv
                       }});
  mesh->indices = {{// indices
                    0, 1, 1, 2, 2, 3}};
  mesh->type = ml::Components::Mesh::LINES;
  mesh->material->use_material = false;
  return mesh;
}

};  // namespace Ray

}  // namespace Geometry

}  // namespace ml
