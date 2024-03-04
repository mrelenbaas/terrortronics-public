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

#include <imgui.h>
#include <openxr/openxr.h>

#include <memory>

#include "IGui.h"

namespace ml {

namespace Components {
class Gui;
}

namespace Scene {
class Node;
}

class IGuiBackend : public IGui {
 public:
  struct Dialog {
    uint32_t pixel_width;
    uint32_t pixel_height;
    float width;
    float height;
    Scene::Node *node;
    uint32_t gui_flags;
    std::weak_ptr<ml::Components::Gui> gui;
  };

  virtual ~IGuiBackend(){};

  virtual bool RegisterGui(Dialog dialog, uint32_t &x_pos, uint32_t &y_pos) = 0;
  virtual void UnregisterGui(Scene::Node *node) = 0;
  virtual void FrameBufferSize(uint32_t &width, uint32_t &height) const = 0;
  virtual void OnDraw(const XrFrameState &frame_state) = 0;

  // renders imgui internally
  virtual bool RenderImGui() = 0;
  virtual void UpdateController(const XrPosef &controller_pose,
                                Scene::Node *node, const XrVector3f &position,
                                const XrVector3f &local_position,
                                float trigger) = 0;
};

}  // namespace ml