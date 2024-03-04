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

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec4 inColor;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 3) out vec3 outPosition;
layout(location = 4) out vec3 outNormal;

void main() {
  mat4 mvp = ubo.view[ubuf.view_index].projection_matrix * ubo.view[ubuf.view_index].view_matrix * ubuf.model_matrix;
  gl_Position = mvp * vec4(inPosition, 1.0);
  fragColor = inColor;
  fragTexCoord = inTexCoord;
  outNormal = mat3(transpose(inverse(ubuf.model_matrix))) * inNormal;
  outPosition = inPosition;
}