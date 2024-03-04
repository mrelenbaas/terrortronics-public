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

/*
 * written with inspriation from:
 *  https://github.com/SaschaWillems/Vulkan/blob/master/data/shaders/glsl/pbrtexture/pbrtexture.frag
 *  https://learnopengl.com/PBR/Lighting
 *  https://github.khronos.org/glTF-Sample-Viewer-Release/
 *
*/

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

layout(location = 0) in vec2 inTexCoord;
layout(location = 1) in vec3 inPos;
layout(location = 2) in mat3 inTBN;

layout(location = 0) out vec4 outColor;

layout(set = 1, binding = 0) uniform sampler2D texSampler;
layout(set = 1, binding = 1) uniform sampler2D metallicRoughnessSampler;
layout(set = 1, binding = 2) uniform sampler2D normalSampler;
layout(set = 1, binding = 3) uniform sampler2D aoSampler;
layout(set = 1, binding = 4) uniform sampler2D emissiveSampler;

const float PI = 3.14159265359;

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
  return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
  float a      = roughness*roughness;
  float a2     = a*a;
  float NdotH  = max(dot(N, H), 0.0);
  float NdotH2 = NdotH*NdotH;

  float num   = a2;
  float denom = (NdotH2 * (a2 - 1.0) + 1.0);
  denom = PI * denom * denom;

  return num / denom;
}

float G_SchlicksmithGGX(float dotNL, float dotNV, float roughness)
{
  float r = (roughness + 1.0);
  float k = (r*r) / 8.0;
  float GL = dotNL / (dotNL * (1.0 - k) + k);
  float GV = dotNV / (dotNV * (1.0 - k) + k);
  return GL * GV;
}


vec3 Uncharted2Tonemap(vec3 x)
{
  float A = 0.15;
  float B = 0.50;
  float C = 0.10;
  float D = 0.20;
  float E = 0.02;
  float F = 0.30;
  return ((x*(A*x+C*B)+D*E)/(x*(A*x+B)+D*F))-E/F;
}

vec4 materialcolor()
{
  vec4 color = texture(texSampler, inTexCoord) * ubuf.base_color;
  return vec4(pow(color.xyz, vec3(2.2)), color.w); // maybe load as linear instead...
}

vec3 emissive_color()
{
  if ((ubuf.flags & USE_EMISSIVE_MAP )== 0 ) {
    return vec3(0);
  }
  vec4 color = texture(emissiveSampler, inTexCoord) * ubuf.emissive_factor;
  return pow(color.rgb, vec3(2.2));
}

vec3 calculateNormal()
{
  if ((ubuf.flags & USE_NORMAL_MAP )== 0 ) {
    vec3 ng = normalize(inTBN[2]);
    if (gl_FrontFacing == false) {
      ng *= -1.0;
    }
    return ng;
  }

  vec3 t = inTBN[0];
  vec3 b = inTBN[1];
  vec3 ng = inTBN[2];

  if (gl_FrontFacing == false)
  {
    t *= -1.0;
    b *= -1.0;
    ng *= -1.0;
  }
  vec3 ntex = texture(normalSampler, inTexCoord).rgb * 2.0 - vec3(1.0);
  return normalize(ntex.x * t + ntex.y * b + ntex.z * ng);
}

void main()
{
	// DEBUG texture coordinates
	// outColor = vec4(inTexCoord, 0,1);
	// return;

	// DEBUG Normal Texture
	// outColor = vec4( (texture(normalSampler, inTexCoord).rgb), 1.0);
	// return;

	// DEBUG Normal Texture
	// outColor = vec4(( ((inNormal) + 1.0) / 2.0) , 1.0);
	// return;

	// // DEBUG Tangents
	// outColor = vec4(( (normalize(inTBN[0]) + 1.0) / 2.0) , 1.0);
	// return;

	// // DEBUG biTangents
	// outColor = vec4(( (normalize(inTBN[1]) + 1.0) / 2.0) , 1.0);
	// return;

	// DEBUG geometry normal
	// outColor = vec4(( (normalize(inTBN[2]) + 1.0) / 2.0) , 1.0);
	// return;

	// DEBUG Shading normal
	// outColor = vec4( ((calculateNormal()) + 1.0) / 2.0, 1.0);
	// return;

  vec3 camPos = ubo.view[ubuf.view_index].camera_pos.xyz;
  vec3 N = calculateNormal();
  vec3 V = normalize(camPos - inPos);
  vec4 albedo_rgba = materialcolor();
  vec3 albedo = albedo_rgba.xyz;
  vec4 metallic_roughness = texture(metallicRoughnessSampler, inTexCoord);
  float metallic =  metallic_roughness.z * ubuf.material.y;
  float roughness = max(0.05, metallic_roughness.y * ubuf.material.x );

  float dotNV = clamp(dot(N, V), 0.0, 1.0);
  vec3 F0 = vec3(0.04);
  F0 = mix(F0, albedo, metallic);

  vec3 Lo = vec3(0.0);
  for(int i = 0; i < 4; ++i)
  {
    if ((ubo.light_sources[i].flags & LIGHT_ENABLED ) != 0) {
      // calculate per-light radiance
      vec3 light_vector = ubo.light_sources[i].pos.xyz - inPos;
      vec3 L = normalize(light_vector);
      vec3 H = normalize(V + L);
      float distance    = length(light_vector);
      float attenuation = 1.0 / (distance);
      vec3 radiance     = ubo.light_sources[i].color.xyz * attenuation;
      float dotNL = clamp(dot(N, L), 0.0, 1.0);

      float NDF = DistributionGGX(N, H, roughness);
      float rroughness = max(0.05, roughness);
      float G = G_SchlicksmithGGX(dotNL, dotNV, rroughness);
      vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);

      vec3 kS = F;
      vec3 kD = vec3(1.0) - kS;
      kD *= 1.0 - metallic;

      vec3 numerator    = NDF * G * F;
      float denominator = 4.0 * max(dotNV, 0.0) * max(dotNL, 0.0) + 0.0001;
      vec3 specular     = numerator / denominator;

      vec3 diffuse = albedo / PI;
      float NdotL = max(dotNL, 0.0);
      Lo += (kD * diffuse + specular) * radiance * NdotL;
    }
  }

  // three percent 'fake' ambient white light.
  const float ambient_lighting = 0.03;

  vec3 ao = vec3(1.0);
  vec3 ambient = vec3(ambient_lighting) * albedo * ao;
  vec3 color = ambient + Lo;

  // mix in the emissive texture.
  color += emissive_color();

  if ((ubuf.flags & USE_AO_MAP )!= 0 ) {
    float ao = texture(aoSampler, inTexCoord).r;
    color = mix(color, color * ao, ubuf.ao_strength);
  }

  const float exposure = 4.5;
  color = Uncharted2Tonemap(color * exposure);
  color = color * (1.0f / Uncharted2Tonemap(vec3(11.2f)));
  // too bright
  // const float gamma = 2.2;
  // color = pow(color, vec3(1.0f / gamma));
  outColor = vec4(color, albedo_rgba.w);
}
