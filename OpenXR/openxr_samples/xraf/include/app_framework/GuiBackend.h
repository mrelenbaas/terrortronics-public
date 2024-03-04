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

#include <chrono>
#include <vector>

#include "IGuiBackend.h"
#include "Linear.h"
#include "Scene/Node.h"

namespace ml {

class GuiBackend : public IGuiBackend {
 public:
  GuiBackend() : frame_started_(false), frame_ended_(false), draw_index_(0) {
  }

  // IGui
  bool BeginDialog(const char *name, bool *open = nullptr,
                   ImGuiWindowFlags flags =
                       ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                       ImGuiWindowFlags_NoCollapse) override;
  void EndDialog() override;
  ImFont *LoadFont(void *font_buffer, size_t font_buffer_len,
                   const ImWchar *glyph_ranges = nullptr, bool is_owned = false,
                   float font_size = 20.f, bool merge = true) override;

  ImFont *LoadFont(std::shared_ptr<IAsset> font_asset,
                   const ImWchar *glyph_ranges = nullptr,
                   float font_size = 20.f, bool merge = true) override;

  // IGuiBackend
  void OnDraw(const XrFrameState &frame_state) override;
  bool RenderImGui() override;
  void UpdateController(const XrPosef &controller_pose, Scene::Node *node,
                        const XrVector3f &position,
                        const XrVector3f &local_position,
                        float trigger) override;
  bool RegisterGui(Dialog dialog, uint32_t &x_pos, uint32_t &y_pos) override;
  void UnregisterGui(Scene::Node *node) override;

  static const ImWchar *GetGlyphRangesArabic();

 protected:
  struct DialogInfo {
    IGuiBackend::Dialog dialog;
    uint32_t x;
    uint32_t y;
  };
  std::vector<DialogInfo> dialogs_;
  bool frame_started_;
  bool frame_ended_;
  size_t draw_index_;

  XrPosef controller_pose_;

  typedef struct DragInfo {
    bool is_dragging;
    XrVector3f global_ray_gui_intersect;
    XrPosef gui_start;
    XrPosef controller_start;
    std::chrono::steady_clock::time_point drag_begin;
    Scene::Node *node;
    DragInfo()
        : is_dragging(false),
          drag_begin(std::chrono::steady_clock::time_point()),
          node(nullptr) {
    }
  } DragInfo;
  DragInfo drag_info_;

  void BeginUpdate();
  void EndUpdate();

  void StartDragging();
  void ContinueDragging(const XrPosef &pose);
  void EndDragging();
  bool Intersect(DialogInfo &info, const XrVector3f &ray_center,
                 const XrVector3f &ray_dir, float &distance, XrVector2f &pos,
                 XrVector3f &global_pos);
  bool Defragment();
};

}  // namespace ml
