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
#include <vector>

#include "../Geometry/Vertex.h"
#include "Component.h"
#include "Material.h"

namespace ml {

namespace Components {

/*! \brief Mesh class.
 *
 * Holds the vertexes, index buffers and material settings for an object.
 */
class Mesh : public IComponent {
 public:
  Mesh() {
    // by default create a material but we support shared materials.
    material = std::make_shared<Components::Material>();
  }
  Mesh(std::shared_ptr<Components::Material> &materialptr)
      : material(materialptr) {
  }

  /*! \brief Type dictates render pipeline settings. */
  enum Type {
    NONE,                //! \brief Used.
    TRIANGLE,            //! \brief Triangle mesh, with filled surface
    TRIANGLE_WIREFRAME,  //! \brief Triangle mesh with the surface not filled.
    LINES,               //! \brief Line mesh, not filled.
    LINE_STRIP,          //! \brief Line mesh, not filled.
    PBR,  //! \brief Triangle Mesh that is filled and rendered by PBR shader.
    NATIVE_BUFFER  //! \brief Triangle Mesh that is filled and used with
                   //! NativeSurfaceTexture.
  };

  /*! \brief the vertex list. */
  std::vector<Geometry::Vertex> vertices;
  /*! \brief the index list.
   *
   * We always must supply an index list.
   * */
  std::vector<uint16_t> indices;
  /*! \brief The material. */
  std::shared_ptr<Material> material;
  /*! \brief the type of mesh */
  Type type{TRIANGLE};

  /*! \brief Generates Tangent vectors from normals, UV and positions.
   *
   * Note that this completely changes the vertices and indices.
   *
   * @return true if succeeded.
   */
  bool GenerateTangents();

  // convenience func.
  std::vector<Geometry::Vertex> &ToVertexVector(std::vector<XrVector3f> pos,
                                                std::vector<XrVector3f> normals,
                                                std::vector<XrColor4f> colors,
                                                std::vector<XrVector2f> uv) {
    vertices.resize(pos.size());
    for (size_t i = 0; i < pos.size(); i++) {
      auto &e = vertices[i];
      e.pos = pos[i];
      if (i < colors.size()) {
        e.color = colors[i];
      }
      if (i < uv.size()) {
        e.uv = uv[i];
      }
      if (i < normals.size()) {
        e.normal = normals[i];
      }
    }
    // TODO this looks unnecessary.
    pos.clear();
    normals.clear();
    colors.clear();
    uv.clear();
    return vertices;
  }
};
}  // namespace Components
}  // namespace ml
