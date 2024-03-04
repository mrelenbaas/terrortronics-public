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

#include <cstdint>

// shaders
#include "compiled/pbr.frag.h"
#include "compiled/pbr.vert.h"
#include "compiled/shader.frag.h"
#include "compiled/shader.vert.h"
// binary files
#include "../include/app_framework/Resources.h"
#include "compiled/default.png.h"
#include "compiled/meteor.png.h"

bool ml::Resources::Get(Resource resource, const unsigned char *&data,
                        size_t &size) {
  switch (resource) {
    case SHADER_VERT:
      data = reinterpret_cast<const unsigned char *>(shader_vert);
      size = sizeof(shader_vert);
      return true;
    case SHADER_FRAG:
      data = reinterpret_cast<const unsigned char *>(shader_frag);
      size = sizeof(shader_frag);
      return true;
    case PBR_VERT:
      data = reinterpret_cast<const unsigned char *>(pbr_vert);
      size = sizeof(pbr_vert);
      return true;
    case PBR_FRAG:
      data = reinterpret_cast<const unsigned char *>(pbr_frag);
      size = sizeof(pbr_frag);
      return true;
    case TEXTURE_DEFAULT:
      data = default_png;
      size = sizeof(default_png);
      return true;

    case TEXTURE_METEOR:
      data = meteor_png;
      size = sizeof(meteor_png);
      return true;
  }
  return false;
}
