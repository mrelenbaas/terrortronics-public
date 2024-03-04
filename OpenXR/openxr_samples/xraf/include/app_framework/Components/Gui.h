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

#include <functional>
#include <tuple>

#include "../Geometry/Quad.h"
#include "../IGuiBackend.h"
#include "../Scene/Node.h"
#include "../XrCore.h"
#include "Component.h"

namespace ml {

namespace Components {

class Gui;
/*! Shared Pointer type of the Gui Component. */
using GuiPtr = std::shared_ptr<Components::Gui>;

using GuiRemoved = std::function<void()>;

/*! \brief Gui Component.
 *
 * This component handles the ImGui
 * dialogs in the Scene Graph.
 *
 */
class Gui : public IComponent {
 public:
  Gui() = default;

  /*! \brief Use by the Application Framework. */
  void SetRemovedCallback(GuiRemoved removed) {
    removed_ = removed;
  }

  /*! \brief Use by the Application Framework. */
  void OnDraw(IGui &gui, const XrFrameState &frame_state) {
    if (on_draw_) {
      on_draw_(gui, frame_state);
    }
  }

  ~Gui() {
    auto gui_impl = core_->GraphicsDevice()->GetGui();
    gui_impl->UnregisterGui(dialog_.node);
    if (removed_) {
      removed_();
    }
  }

  /*! \brief Called with the position on the back buffer changes.
   *
   * All guis are drawn in one single back buffer. Sometimes
   * it will be necessary to move these around the back buffer.
   */
  void BackBufferChanged(uint32_t x, uint32_t y) {
    float fx, fy;
    fx = (float)x;
    fy = (float)y;
    float x0 = fx / fb_width_;
    float x1 = (fx + dialog_.pixel_width) / fb_width_;
    float y0 = fy / fb_height_;
    float y1 = (fy + dialog_.pixel_height) / fb_height_;
    auto quad = quad_.lock();
    if (!quad) {
      return;
    }

#ifdef DEBUG_GUI
    // if you want to see the layout of the
    // dialogs on the back buffer simply enable this code.
    x0 = 0.0f;
    y0 = 0.0f;
    x1 = 1.0f;
    y1 = 1.0f;
#endif

    for (size_t i = 0; i < quad->vertices.size(); i++) {
      auto &vertex = quad->vertices[i];
      // move the vertexes to the requested sizes.
      vertex.pos.x = ml::Geometry::Quad::TriangleVertices[i].x * dialog_.width;
      vertex.pos.y = ml::Geometry::Quad::TriangleVertices[i].y * dialog_.height;

      vertex.uv.x = ml::Geometry::Quad::TriangleUVs[i].x < 0.5f ? x0 : x1;
      vertex.uv.y = ml::Geometry::Quad::TriangleUVs[i].y < 0.5f ? y0 : y1;

      if ((gui_flags_ & DEBUG_BACK_BUFFER) != 0) {
        vertex.uv.x = ml::Geometry::Quad::TriangleUVs[i].x < 0.5f ? 0.0f : 1.0f;
        vertex.uv.y = ml::Geometry::Quad::TriangleUVs[i].y < 0.5f ? 0.0f : 1.0f;
      }
    }
    dialog_.node->BroadcastChange(Scene::Node::MESH_UPDATED);
  }

  using OnDrawFunction =
      std::function<void(IGui &gui, const XrFrameState &frame_state)>;

  enum GuiFlags { NONE = 0, ALLOW_DRAG = 1 << 0, DEBUG_BACK_BUFFER = 1 << 1 };
  static const uint32_t DefaultGuiFlags = ALLOW_DRAG;

  /*! \brief Gui Factory
   *
   * @param core the XrCore object
   * @param pixel_width is the width of the desired Gui dialog
   * @param pixel_height is the height of the desired Gui dialog
   * @param pixels_per_meter is the number of pixels per meter
   * @param on_draw the callback that handles the drawing of the ImGui elements.
   * @return
   *
   * Please use the #Application class "CreateGui" method to create GUI's so
   * that the GUI is registered with the controller collision logic.
   *
   */
  static std::tuple<GuiPtr, Scene::Node *> Factory(
      XrCore *core, uint32_t pixel_width = 500, uint32_t pixel_height = 500,
      float pixels_per_meter = 500, uint32_t gui_flags = DefaultGuiFlags,
      OnDrawFunction on_draw = {}) {
    // calculate the UV coordinates.
    uint32_t fb_width, fb_height;
    auto gui_impl = core->GraphicsDevice()->GetGui();
    gui_impl->FrameBufferSize(fb_width, fb_height);

    // early fail, might still fail in registration
    if (pixel_height > fb_height || pixel_width > fb_width) {
      ALOGE("requested pixel height exceed framebuffer: %d > %d", pixel_height,
            fb_height);
      return std::make_tuple(nullptr, nullptr);
    }

    auto node = new Scene::Node();
    auto quad = ml::Geometry::Quad::TriangleFactory();
    auto gui = std::make_shared<Gui>();
    gui->on_draw_ = on_draw;

    node->AddComponent(quad);
    node->AddComponent(gui);

    float width = pixel_width / pixels_per_meter;
    float height = pixel_height / pixels_per_meter;
    gui->core_ = core;
    gui->dialog_ = {pixel_width, pixel_height, width, height,
                    node,        gui_flags,    gui};
    gui->fb_width_ = fb_width;
    gui->fb_height_ = fb_height;
    gui->quad_ = quad;
    gui->gui_flags_ = gui_flags;
    gui->marked_for_removal_ = false;

    uint32_t x, y;
    gui_impl->RegisterGui(gui->dialog_, x, y);
    return std::make_tuple(gui, node);
  }

  /*! \brief Call this to remove the GUI.
   *
   * Note that this also removes the GUI from the scene graph once
   * all GUI update drawing is done.
   *
   * */
  void Remove() {
    marked_for_removal_ = true;
  }

  /*! \brief Returns true if marked for removal */
  bool MarkedForRemoval() const {
    return marked_for_removal_;
  }

 private:
  XrCore *core_;
  IGuiBackend::Dialog dialog_;
  uint32_t fb_width_;
  uint32_t fb_height_;
  std::weak_ptr<Components::Mesh> quad_;
  GuiRemoved removed_;
  uint32_t gui_flags_;
  OnDrawFunction on_draw_;
  bool marked_for_removal_;
};
}  // namespace Components
}  // namespace ml
