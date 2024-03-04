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

#include <cstring>
#include <string>
#include <vector>

#include "../AssetManager.h"
#include "../Resources.h"
#include "ITexture.h"

namespace ml {

namespace Components {

/*! \brief TextureData class.
 *
 * Stores texture data from an asset. Texture may be shared between different
 * meshes.
 */
class TextureData : public ITexture {
 public:
  TextureData(IAssetManagerPtr asset_manager, const std::string &filename)
      : asset_manager_(asset_manager),
        filename_(filename),
        encoding_type_(ENCODED) {
  }

  /*! \brief Create Texture data from memory file encoded as an image file
   * JPG/PNG/etc. */
  TextureData(const char *data, size_t size)
      : asset_manager_(nullptr), encoding_type_(ENCODED) {
    data_.resize(size);
    memcpy(data_.data(), data, size);
  }

  /*! \brief Create Texture data from a compiled in Resource File */
  TextureData(ml::Resources::Resource resource)
      : asset_manager_(nullptr), encoding_type_(ENCODED) {
    const unsigned char *data;
    size_t size;
    if (!ml::Resources::Get(resource, data, size)) {
      throw std::runtime_error("Unable to load resource");
    }
    data_.resize(size);
    memcpy(data_.data(), data, size);
  }

  /*! \brief Create Texture data from RGBA encoded memory */
  TextureData(const char *data, size_t size, uint32_t width, uint32_t height)
      : asset_manager_(nullptr),
        encoding_type_(RAW),
        width_(width),
        height_(height) {
    data_.resize(size);
    memcpy(data_.data(), data, size);
  }

  bool Open() override {
    if (data_.size() > 0) {
      return true;
    }
    if (!asset_manager_) {
      return false;
    }
    asset_ptr_ = asset_manager_->Open(filename_.c_str());
    if (!asset_ptr_) {
      return false;
    }
    return true;
  }

  bool Close() override {
    asset_ptr_.reset();
    return true;
  }

  const char *Data() override {
    if (asset_ptr_) {
      return (const char *)asset_ptr_->GetBuffer();
    }
    return data_.data();
  }

  size_t Size() override {
    if (asset_ptr_) {
      return asset_ptr_->Length();
    }
    return data_.size();
  }

  EncodingType Encoding() override {
    return encoding_type_;
  }

  TextureType Type() const override {
    return TextureType::STATIC;
  }

  uint32_t Width() override {
    return width_;
  }

  uint32_t Height() override {
    return height_;
  }

  const ShaderSettings &Shader() const override {
    return shader_settings_;
  }

  void UpdateShader(const ShaderSettings &settings) {
    shader_settings_ = settings;
  }

 private:
  IAssetManagerPtr asset_manager_;
  std::string filename_;
  std::vector<char> data_;
  IAssetPtr asset_ptr_;
  EncodingType encoding_type_;
  uint32_t width_;
  uint32_t height_;
  ShaderSettings shader_settings_;
};

}  // namespace Components

}  // namespace ml