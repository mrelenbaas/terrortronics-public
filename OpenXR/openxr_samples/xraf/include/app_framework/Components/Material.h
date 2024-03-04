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
#include "Component.h"
#include "ITexture.h"

namespace ml {

namespace Components {

/*! \brief Material settings for shaders.
 *
 * Properties here follow the GLTF material standard.
 * https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html#materials
 */
class Material : public Components::ComponentHolder {
 public:
  /*! \brief Texture Type. */
  enum TextureType {
    COLOR = 0,
    METALLIC_ROUGHNESS = 1,
    NORMAL = 2,
    AO = 3,
    EMISSIVE = 4,
    TEXTURE_TYPE_COUNT = 5
  };

  /*! \brief The base color of the object. */
  XrColor4f base_color;
  /*! \brief roughness a value between 0.0 and 1.0 describing the PBR roughness
   * value. */
  float roughness;
  /*! \brief metallic a value between 0.0 and 1.0 describing the PBR metallic
   * value. */
  float metallic;
  /*! \brief the image texture to be used with an object.
   *
   * If no image texture is specified the base_color is used.
   *
   */
  Components::ITexturePtr color_texture;
  /*! \brief the metallic roughness texture to be used with an object.
   *
   * If no texture is specified the roughness and metallic values are
   * used.
   *
   * The roughness is packed in the green channel.
   * The metallic value is packed in the blue channel.
   *
   */
  Components::ITexturePtr metallic_roughness_texture;

  /*! \brief the normal texture to use for the mesh.
   *
   * Note that tangents should be loaded in to the "color" vertex
   * attribute.
   *
   */
  Components::ITexturePtr normal_texture;

  /*! \brief the multiplier for the occlusion texture.
   * occlusion = 1.0 + occlusion_strength * (<sampled occlusion texture value>
   * - 1.0)
   * */
  float occlusion_strength;

  /*! \brief the occlusion texture to use for the mesh. (R)
   */
  Components::ITexturePtr occlusion_texture;

  /*! \brief the multiplier for the emissive texture. */
  XrColor4f emissive_factor;

  /*! \brief the emissive texture to use for the mesh. (RGB)
   */
  Components::ITexturePtr emissive_texture;

  /*! \brief use_material
   *
   * Each vertex has per vertex color available, this will
   * be used if use_material is set to false. Otherwise the shaders
   * will use the properties defined in this object.
   *
   * Material settings are not used in the LINE based renderers, only
   * the mesh color points.
   */
  bool use_material{true};
};

}  // namespace Components
}  // namespace ml