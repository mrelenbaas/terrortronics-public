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

#include <openxr/openxr.h>

#include <array>
#include <tuple>

#include "../Scene/Node.h"
#include "Component.h"

namespace ml {

namespace Components {

class Light;
/*! Shared Pointer type of the Light Component. */
using LightPtr = std::shared_ptr<Components::Light>;

/*! \brief A Light component.
 *
 * A Scene graph will only support a limited number of lights
 * in a scene. (Vulkan currently supports up to 3). Also the
 * lights will only be used with the PBR shader.
 *
 * If no lights are provided in the scene tree, defaults lights
 * will be used.
 *
 */
class Light : public IComponent {
 public:
  Light() : color_{1.0f, 1.0f, 1.0f, 1.0f} {
  }

  /*! \brief Light Factory.
   *
   *
   * @param r color channel
   * @param b color channel
   * @param g color channel
   * @return Light Component and Node created.
   */
  static std::tuple<LightPtr, Scene::Node *> Factory(const XrColor4f &color) {
    auto node = new Scene::Node();
    std::shared_ptr<Light> component = std::make_shared<Light>();
    node->AddComponent(component);
    component->SetColor(color);
    return std::make_tuple(component, node);
  }

  /*! \brief Sets the color of the light. */
  void SetColor(float r, float g, float b) {
    color_.r = r;
    color_.g = g;
    color_.b = b;
    color_.a = 1.0f;  // lights are not transparent.
  }

  /*! \brief Sets the color of the light. */
  void SetColor(const XrColor4f &color) {
    color_ = color;
  }

  /*! \brief Returns the color of the light.
   *
   * RGBA order.
   *
   * */
  const XrColor4f &Color() const {
    return color_;
  }

 protected:
  XrColor4f color_;
};
}  // namespace Components
}  // namespace ml
