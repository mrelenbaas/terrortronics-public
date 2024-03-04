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

#include "../Linear.h"

namespace ml {

namespace Geometry {

/*! \brief The basic Vertex building block */
struct Vertex {
  XrVector3f pos;     //! \brief position in space.
  XrVector3f normal;  //! \brief normal.
  XrVector2f uv;      //! \brief texture coordinate.
  union {
    //! \brief color of the vertex ( used only in certain
    //! shaders see Material settings.
    XrColor4f color;
    //! \brief PBR shaders need tangets, reuse this one.
    XrVector4f tangent;
  };
};

}  // namespace Geometry
}  // namespace ml
