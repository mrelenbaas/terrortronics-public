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

#include <map>
#include <memory>

#include "../Components/Component.h"
#include "CommandBuffers.h"
#include "TextureDescriptorPool.h"

namespace ml {

namespace Vulkan {

class MaterialDescriptorSet : public ml::Components::IComponent {
 public:
  using TextureMap =
      std::map<ml::Components::Material::TextureType, Vulkan::ImageBufferPtr>;

  MaterialDescriptorSet(Vulkan::TextureDescriptorPool* pool,
                        const TextureMap& default_images)
      : descriptor_pool_(pool), default_images_(default_images) {
  }

  // Start material setup
  void StartSetup();
  // Add image during the setup
  void AddImage(Material::TextureType texture_type, ImageBufferPtr& image);
  // Finish material setup, this creates the descriptor set.
  void FinishSetup(vk::Device device);

  inline const vk::DescriptorSet& DescriptorSet() const {
    return descriptor_set_;
  }

  inline bool HasImage(Material::TextureType texture_type) const {
    return has_image_.count(texture_type);
  }

  inline bool HasImages() const {
    for (const auto& kvp : images_) {
      if (kvp.second) {
        return true;
      }
    }
    return false;
  }

  // Update descriptor set, if material uses NativeSurfaceTexture and it has
  // frames to consume
  void UpdateIfNative(vk::Device device,
                      ml::Vulkan::CommandBuffer& command_buffer,
                      vk::Queue& queue);
  bool IsNative() const {
    return descriptor_pool_->Type() == TextureDescriptorPool::NATIVE_BUFFER;
  }

 protected:
  Vulkan::TextureDescriptorPool* descriptor_pool_;
  const TextureMap& default_images_;
  TextureMap images_;
  vk::DescriptorSet descriptor_set_;
  std::map<ml::Components::Material::TextureType, bool> has_image_;

  void UpdateDescriptorSet(vk::Device device);
};

}  // namespace Vulkan
}  // namespace ml