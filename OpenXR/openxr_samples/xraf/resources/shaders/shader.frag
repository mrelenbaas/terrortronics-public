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

#version 450

struct LightSource {
  vec4 pos;
  vec4 color;
  uint flags;
};

#define MAX_LIGHTS 4
#define LIGHT_ENABLED 1

struct View {
  mat4 projection_matrix;
  mat4 view_matrix;
  vec4 camera_pos;
};

layout(std140, set = 0, binding = 0) uniform UniformBufferObject {
  View view[2];
  LightSource light_sources[MAX_LIGHTS];
} ubo;

#define USE_TEXTURE 1
#define USE_MATERIAL 2
#define USE_NORMAL_MAP 4
#define USE_AO_MAP 8
#define USE_EMISSIVE_MAP 16

layout (std140, push_constant) uniform buf
{
  mat4 model_matrix;
  vec4 base_color;
  vec4 material; // x = roughness, y = metallic
  vec4 emissive_factor;
  float ao_strength;
  uint flags;
  uint view_index;
} ubuf;

layout(location = 0) in vec4 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 3) in vec3 inPos;
layout(location = 4) in vec3 inNormal;

layout(location = 0) out vec4 outColor;

layout(set = 1, binding = 0) uniform sampler2D texSampler;

void main() {
  if ((ubuf.flags & USE_TEXTURE)!=0) {
    outColor = texture(texSampler, fragTexCoord);
  } else {
    if ((ubuf.flags & USE_MATERIAL) !=0) {
      outColor = ubuf.base_color;
    } else {
      outColor = fragColor;
    }
  }
}
