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

/*! \brief 2d Quad Geometry.
 *
 * 1x1 quad with its origin in its center.
 * */
namespace Quad {

inline std::shared_ptr<Components::Mesh> LineFactory() {
  auto mesh = std::make_shared<Components::Mesh>();
  mesh->ToVertexVector({{
                           // pos
                           {-0.5f, -0.5f, 0.0f},
                           {-0.5f, 0.5f, 0.0f},
                           {0.5f, 0.5f, 0.0f},
                           {0.5f, -0.5f, 0.0f},
                       }},
                       {{
                           // normals
                       }},
                       {{
                           // colors
                           {1.0f, 0.0f, 0.0f, 1.0f},
                           {0.0f, 1.0f, 0.0f, 1.0f},
                           {0.0f, 0.0f, 1.0f, 1.0f},
                           {0.0f, 1.0f, 1.0f, 1.0f},
                       }},
                       {{
                           // uv
                       }});
  mesh->indices = {{// indices
                    0, 1, 1, 2, 2, 3, 3, 0}};
  mesh->type = ml::Components::Mesh::LINES;
  mesh->material->use_material = false;
  return mesh;
}

static const std::vector<XrVector3f> TriangleVertices = {{
    {-0.5f, -0.5f, 0.0f},
    {-0.5f, 0.5f, 0.0f},
    {0.5f, 0.5f, 0.0f},
    {0.5f, -0.5f, 0.0f},
}};
static const std::vector<XrVector2f> TriangleUVs = {{
    {0.000000f, 1.000000f},
    {0.000000f, 0.000000f},
    {1.000000f, 0.000000f},
    {1.000000f, 1.000000f},
}};

static const std::vector<uint16_t> TriangleIndices = {{// indices
                                                       0, 3, 2, 0, 2, 1}};

inline std::shared_ptr<Components::Mesh> TriangleFactory() {
  auto mesh = std::make_shared<Components::Mesh>();
  mesh->ToVertexVector(TriangleVertices,
                       {{
                           // normals
                       }},
                       {{
                           // colors
                           {1.0f, 0.0f, 0.0f, 1.0f},
                           {0.0f, 1.0f, 0.0f, 1.0f},
                           {0.0f, 0.0f, 1.0f, 1.0f},
                           {0.0f, 1.0f, 1.0f, 1.0f},
                       }},
                       TriangleUVs);
  mesh->indices = TriangleIndices;
  mesh->type = ml::Components::Mesh::TRIANGLE;
  mesh->material->base_color = XrColor4f{1.0f, 1.0f, 1.0f, 1.0f};
  return mesh;
}

};  // namespace Quad
}  // namespace Geometry
}  // namespace ml
