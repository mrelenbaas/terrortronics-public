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

#include "Component.h"

namespace ml {

namespace Components {

class ITexture : public ComponentHolder {
 public:
  struct ShaderSettings {
    enum Wrap { CLAMP_TO_EDGE, MIRRORED_REPEAT, REPEAT };
    enum Filter {
      NEAREST,
      LINEAR,
      NEAREST_MIPMAP_NEAREST,
      LINEAR_MIPMAP_NEAREST,
      NEAREST_MIPMAP_LINEAR,
      LINEAR_MIPMAP_LINEAR
    };
    Wrap u_wrap{REPEAT};
    Wrap v_wrap{REPEAT};
    Wrap w_wrap{REPEAT};
    Filter magnification{LINEAR};  // LINEAR and NEAREST ONLY.
    Filter minification{LINEAR};
    float lod_bias = 0.0f;

    bool UsesMipmapping() const {
      return minification >= NEAREST_MIPMAP_NEAREST;
    }

    static Wrap GLToWrap(int gl) {
      switch (gl) {
        case 33071:
          return CLAMP_TO_EDGE;
        case 33648:
          return MIRRORED_REPEAT;
        case 10497:
          return REPEAT;
        default:
          return REPEAT;
      }
    }
    static Filter GLToFilter(int gl) {
      switch (gl) {
        case 9728:
          return NEAREST;
        case 9729:
          return LINEAR;
        case 9984:
          return NEAREST_MIPMAP_NEAREST;
        case 9985:
          return LINEAR_MIPMAP_NEAREST;
        case 9986:
          return NEAREST_MIPMAP_LINEAR;
        case 9987:
          return LINEAR_MIPMAP_LINEAR;
        default:
          return NEAREST;
      }
    }
  };

  virtual ~ITexture() {
  }

  // RAW = RGBA
  // Encoded = PNG/JPG/etc...
  enum EncodingType { RAW, ENCODED };

  enum class TextureType { STATIC, NATIVE_SURFACE };

  /*! \brief opens the underlying data
   *
   * Note that Data and Size are only defined
   * if Open was successful.
   *
   * @return true if successful.
   */
  virtual bool Open() = 0;
  virtual bool Close() = 0;
  virtual const char *Data() = 0;
  virtual size_t Size() = 0;

  virtual EncodingType Encoding() = 0;
  virtual TextureType Type() const = 0;

  /*! \brief width and height only valid when encoding type is RAW */
  virtual uint32_t Width() = 0;
  virtual uint32_t Height() = 0;
  virtual const ShaderSettings &Shader() const = 0;
};

using ITexturePtr = std::shared_ptr<ITexture>;
}  // namespace Components
}  // namespace ml