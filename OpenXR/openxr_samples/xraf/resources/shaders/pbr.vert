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
  View views[2];
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
layout(location = 3) in vec4 inTangent;

layout(location = 0) out vec2 outTextCoord;
layout(location = 1) out vec3 outPosition;
layout(location = 2) out mat3 outTBN;

vec4 getPosition()
{
  vec4 pos = vec4(inPosition, 1.0);
  return pos;
}

vec3 getTangent()
{
  vec3 tangent = inTangent.xyz;
  return normalize(tangent);
}

vec3 getNormal()
{
  return normalize(inNormal);
}

void main() {
  mat4 mvp = ubo.views[ubuf.view_index].projection_matrix * ubo.views[ubuf.view_index].view_matrix * ubuf.model_matrix;
  gl_Position = mvp * vec4(inPosition, 1.0);
  outTextCoord = inTexCoord;

  mat4 normalMatrix = (transpose(inverse(ubuf.model_matrix)));

  vec4 pos = ubuf.model_matrix * getPosition();
  outPosition = vec3(pos.xyz) / pos.w;

  vec3 tangent = getTangent();
  vec3 normalW = normalize(vec3(normalMatrix * vec4(getNormal(), 0.0)));
  vec3 tangentW = normalize(vec3(ubuf.model_matrix * vec4(tangent, 0.0)));
  vec3 bitangentW = cross(normalW, tangentW) * inTangent.w;
  outTBN = mat3(tangentW, bitangentW, normalW);
}
