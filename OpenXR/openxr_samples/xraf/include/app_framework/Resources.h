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

#include <cstddef>

namespace ml {

namespace Resources {

/** Adding new resources.
 *
 * 1. Edit the resources/CmakeLists.txt and add the resource there.
 * 2. Add the resource to the list below.
 * 3. Edit Resource.cpp to return the correct data.
 */
enum Resource {
  // Shaders
  SHADER_VERT,
  SHADER_FRAG,
  PBR_VERT,
  PBR_FRAG,

  // Textures
  TEXTURE_DEFAULT,  // just white.
  TEXTURE_METEOR,   // white with Meteor.
};

bool Get(Resource resource, const unsigned char *&data, size_t &size);
}  // namespace Resources

}  // namespace ml