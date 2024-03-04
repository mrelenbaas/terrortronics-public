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

#include "../include/app_framework/GuiBackend.h"

#include <imgui.h>

#include <list>

#include "../include/app_framework/AssetManager.h"
#include "../include/app_framework/Components/Gui.h"
#include "../include/app_framework/Geometry/Cube.h"
#include "../include/app_framework/Scene/Node.h"

using namespace ml;

void GuiBackend::BeginUpdate() {
  ImGui::NewFrame();
  frame_started_ = true;
  draw_index_ = 0;
}

void GuiBackend::EndUpdate() {
  ImGui::EndFrame();
  frame_ended_ = true;
}

bool GuiBackend::BeginDialog(const char *name, bool *open,
                             ImGuiWindowFlags flags) {
  bool may_drag = false;
  if (draw_index_ < dialogs_.size()) {
    const auto &dialog = dialogs_[draw_index_];
    draw_index_++;
    may_drag = (dialog.dialog.gui_flags & Components::Gui::ALLOW_DRAG) != 0;

    ImGui::SetNextWindowPos(ImVec2(dialog.x, dialog.y), ImGuiCond_Always);
    ImGui::SetNextWindowSize(
        ImVec2(static_cast<float>(dialog.dialog.pixel_width),
               static_cast<float>(dialog.dialog.pixel_height)),
        ImGuiCond_Always);

  } else {
    ALOGE(
        "More Begin Dialog calls than Gui nodes in tree, GUI is likely not "
        "right.");
  }

  bool result = ImGui::Begin(name, open, flags);
  if (ImGui::IsItemClicked()) {
    if (may_drag) {
      StartDragging();
    }
  }
  return result;
}
void GuiBackend::EndDialog() {
  ImGui::End();
}

void GuiBackend::StartDragging() {
  if (!drag_info_.node || drag_info_.is_dragging) {
    return;
  }

  drag_info_.is_dragging = true;

  // TODO This should be using world transforms.
  drag_info_.gui_start.position = drag_info_.node->Translation();
  XrQuaternionf rot = drag_info_.node->Rotation();
  drag_info_.gui_start.orientation = rot;
  drag_info_.controller_start = controller_pose_;
  drag_info_.drag_begin = std::chrono::steady_clock::now();
}

void GuiBackend::ContinueDragging(const XrPosef &pose) {
  if (!drag_info_.node) {
    return;
  }
  const auto &di = drag_info_;

  XrQuaternionf inv_rot = di.controller_start.orientation;
  Linear::XrInvert(inv_rot);

  XrQuaternionf controller_rotation_difference;
  Linear::XrMultiply(controller_rotation_difference,
                     controller_pose_.orientation, inv_rot);

  XrQuaternionf rotation;
  Linear::XrMultiply(rotation, controller_rotation_difference,
                     di.gui_start.orientation);

  XrVector3f center_offset;
  Linear::XrSub(center_offset, di.global_ray_gui_intersect,
                di.gui_start.position);

  XrVector3f ray;
  Linear::XrSub(ray, di.global_ray_gui_intersect, di.controller_start.position);

  Linear::XrRotate(center_offset, controller_rotation_difference);

  Linear::XrRotate(ray, controller_rotation_difference);

  XrVector3f offset;
  Linear::XrSub(offset, controller_pose_.position, center_offset);
  Linear::XrAdd(offset, offset, ray);

  // TODO Really this should be setting world transform.
  di.node->SetRotation(rotation);
  di.node->SetTranslation(offset);
}

void GuiBackend::EndDragging() {
  drag_info_.is_dragging = false;
}

void GuiBackend::UpdateController(const XrPosef &controller_pose,
                                  Scene::Node *node, const XrVector3f &position,
                                  const XrVector3f &local_position,
                                  float trigger) {
  if (dialogs_.empty()) {
    return;
  }

  controller_pose_ = controller_pose;

  if (drag_info_.is_dragging) {
    if (trigger > 0.7f) {
      ContinueDragging(controller_pose);
    } else {
      EndDragging();
    }
    return;
  }

  if (node == nullptr) {
    return;
  }

  DialogInfo *dialog_info = nullptr;
  for (auto &check_dialog : dialogs_) {
    if (check_dialog.dialog.node == node) {
      dialog_info = &check_dialog;
      break;
    }
  }
  if (dialog_info == nullptr) {
    ALOGE("Unable to find GUI with this node.");
    return;
  }

  auto &io = ImGui::GetIO();
  io.MousePos.x =
      dialog_info->x + (local_position.x / dialog_info->dialog.width + 0.5f) *
                           dialog_info->dialog.pixel_width;
  io.MousePos.y =
      dialog_info->y + (-local_position.y / dialog_info->dialog.height + 0.5f) *
                           dialog_info->dialog.pixel_height;
  io.MouseDown[0] = trigger > 0.7f;

  ImGui::GetForegroundDrawList()->AddCircle(
      io.MousePos, 1.0f, IM_COL32(255, 255, 255, 100), 5, 2.0f);
  ImGui::GetForegroundDrawList()->AddCircle(
      io.MousePos, 7.5f, IM_COL32(255, 255, 255, 100), 20, 2.0f);

  drag_info_.node = node;
  drag_info_.global_ray_gui_intersect = position;
}

bool GuiBackend::Defragment() {
  // for now lay them out only horizontally.
  // ideally we try to tile them into the vertical open
  // space as well.

  uint32_t width, height;
  FrameBufferSize(width, height);

  uint32_t available_x = 0;
  const uint32_t padding = 10;

  for (size_t i = 0; i < dialogs_.size(); i++) {
    DialogInfo &dialog = dialogs_[i];

    if (available_x + dialog.dialog.pixel_width > width) {
      ALOGE("Too many ImGui dialogs for BackBuffer size.");
      continue;
    }

    dialog.x = available_x;
    available_x += dialog.dialog.pixel_width + padding;
    auto gui = dialog.dialog.gui.lock();
    if (gui) {
      gui->BackBufferChanged(dialog.x, dialog.y);
    }
  }
  return true;
}

bool GuiBackend::RegisterGui(Dialog dialog, uint32_t &x_pos, uint32_t &y_pos) {
  Defragment();

  x_pos = 0;
  y_pos = 0;
  if (!dialogs_.empty()) {
    auto &dialog = dialogs_.back();
    x_pos = dialog.x + dialog.dialog.pixel_width + 10;
  }

  dialogs_.push_back({dialog, x_pos, y_pos});

  uint32_t width, height;
  FrameBufferSize(width, height);
  if (dialog.pixel_height > height) {
    ALOGW("Warning dialog too tall for framebuffer");
  }

  auto gui = dialog.gui.lock();
  if (gui) {
    gui->BackBufferChanged(x_pos, y_pos);
  } else {
    ALOGE("Could not find Gui component.");
  }

  return x_pos + dialog.pixel_width < width;
}

void GuiBackend::UnregisterGui(Scene::Node *node) {
  auto it = std::find_if(
      dialogs_.begin(), dialogs_.end(),
      [node](const DialogInfo &info) { return info.dialog.node == node; });
  if (it != dialogs_.end()) {
    dialogs_.erase(it);
  }
}
bool GuiBackend::RenderImGui() {
  if (!frame_started_) {
    return false;
  }

  if (!frame_ended_) {
    ALOGE("You forgot to call Gui::EndUpdate");
    EndUpdate();
  }
  ImGui::Render();
  frame_started_ = false;
  frame_ended_ = false;
  return true;
}

void GuiBackend::OnDraw(const XrFrameState &frame_state) {
  if (dialogs_.empty()) {
    return;
  }
  std::list<Scene::Node *> marked_for_removal;

  BeginUpdate();
  for (auto &dialog : dialogs_) {
    auto gui = dialog.dialog.node->GetComponent<Components::Gui>();
    if (gui) {
      gui->OnDraw(*this, frame_state);
      if (gui->MarkedForRemoval()) {
        marked_for_removal.push_back(dialog.dialog.node);
      }
    }
  }
  EndUpdate();

  for (auto node : marked_for_removal) {
    node->Parent()->RemoveChild(node);
  }
}

ImFont *GuiBackend::LoadFont(void *font_buffer, size_t font_buffer_len,
                             const ImWchar *glyph_ranges, bool is_owned,
                             float font_size, bool merge) {
  if (font_buffer == nullptr || font_buffer_len <= 0) {
    ALOGE("Passed invalid font buffer or length!");
    return nullptr;
  }

  ImGuiIO &io = ImGui::GetIO();
  ImFontConfig cfg;
  cfg.FontDataOwnedByAtlas =
      is_owned;  // This can be used so that ImGui frees memory for the font
  cfg.MergeMode = merge;  // This will merge loaded glyph ranges into an already
                          // existing font
  return io.Fonts->AddFontFromMemoryTTF(font_buffer, font_buffer_len, font_size,
                                        &cfg, glyph_ranges);
}

ImFont *GuiBackend::LoadFont(std::shared_ptr<IAsset> font_asset,
                             const ImWchar *glyph_ranges, float font_size,
                             bool merge) {
  if (!font_asset) {
    ALOGE("Passed invalid font asset!");
    return nullptr;
  }

  try {
    const auto len = font_asset->Length();
    void *font_buffer = malloc(len);
    font_asset->Read(font_buffer, len);

    return LoadFont(font_buffer, len, glyph_ranges, true, font_size, merge);
  } catch (const std::runtime_error &ex) {
    ALOGE("Encountered runtime_error while accessing font asset!");
    return nullptr;
  }
}

const ImWchar *GuiBackend::GetGlyphRangesArabic() {
  // These are not ALL Arabic glyph ranges! Just some subset based on unicode
  // webpage
  static const ImWchar ranges[] = {
      0x0600, 0x06FF,  // Arabic
      0x0750, 0x077F,  // Arabic Supplement
      0x08A0, 0x08FF,  // Arabic Extended-A
      0x0870, 0x089F,  // Arabic Extended-B
      0,
  };
  return &ranges[0];
}
