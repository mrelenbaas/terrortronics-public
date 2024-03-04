// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
// Copyright (c) 2023 Magic Leap, Inc. All Rights Reserved.
// Use of this file is governed by the Software License Agreement,
// located here: https://www.magicleap.com/software-license-agreement-ml2
// Terms and conditions applicable to third-party materials accompanying
// this distribution may also be found in the top-level NOTICE file
// appearing herein.
// %COPYRIGHT_END%
// ---------------------------------------------------------------------
// %BANNER_END%

#include <app_framework/Application.h>
#include <app_framework/Extensions/ExtPlaneDetection.h>
#include <app_framework/Utils/PermissionHelper.h>

#include "PlaneProcessor.h"

//#include <stdio.h>
//#include <stdlib.h>

//#include <tchar.h>
//#include <string>
//#include "stdlib.h"

using namespace ml;

class App : public Application {
 public:
  explicit App(struct android_app *state) :
    Application(state,
                {},
                {},
                ml::Extensions::ExtPlaneDetection::RequiredExtensions()),
    gui_node_(nullptr) {
    std::vector<std::string> permissions = {
      {"com.magicleap.permission.SPATIAL_MAPPING"}};
    permission_helper_ = std::make_unique<PermissionHelper>(permissions, this);
  }

  void OnFocussed() override {
    if (!gui_node_) {
      if (!permission_helper_->RequestPermissions()) {
        return;
      }
    }

    if (gui_node_) {
      return;
    }

    plane_processor_ = std::make_unique<PlaneProcessor>(GetXRCore(), GetRoot());
    plane_processor_->Start();

    gui_node_ = CreateGui(500, 500, 500, Components::Gui::DefaultGuiFlags,
                          [&](IGui &gui, const XrFrameState &frame_state) {
                            OnDrawGui(gui, frame_state);
                          });
  }

  void OnPreRender(const XrFrameState &frame_state) override {
    if (plane_processor_) {
      plane_processor_->Process(frame_state, plane_filters_);
    }
  }

 private:
  Scene::Node *gui_node_;
  std::unique_ptr<PermissionHelper> permission_helper_;
  std::unique_ptr<PlaneProcessor> plane_processor_;
  PlaneFilters plane_filters_;

  void OnDrawGui(IGui &gui, const XrFrameState &frame_state) {
    bool continue_running = true;

      //std::string srcFilePath = "/sdcard/state.txt";
      //FILE* file = fopen(srcFilePath.c_str(), "r");
      //gui.BeginDialog("(HAM) OpenXR Plane Detection Demo", &continue_running);
      //if (file != nullptr) {
      //    ImGui::Text("(SUCCESS) XR_EXT_plane_detection runtime support: ");
      //} else {
      //    ImGui::Text("(FAILURE) XR_EXT_plane_detection runtime support: ");
      //}
      //fclose(file);
    ImGui::Text("XR_EXT_plane_detection runtime support: ");
    ImGui::SameLine();
    if (!plane_processor_->IsPlaneDetectionSupported()) {
      ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "Not available");
    } else {
      ImGui::TextColored(ImVec4(0.f, 1.f, 0.f, 1.f), "Available");

      if (ImGui::Button(plane_processor_->IsScanInProgress() ? "Stop"
                                                             : "Start")) {
        if (plane_processor_->IsScanInProgress()) {
          plane_processor_->Stop();
        } else {
          plane_processor_->Start();
        }
      }

      if (ImGui::Checkbox("Show Polygons", &plane_filters_.show_vertices)) {
        plane_filters_.show_bounding_boxes = !plane_filters_.show_vertices;
      }

      if (plane_processor_->IsPlaneDetectionCapSupported(
              XR_PLANE_DETECTION_CAPABILITY_PLANE_HOLES_BIT_EXT)) {
        ImGui::Checkbox("Show Holes", &plane_filters_.show_holes);
      }

      ImGui::Separator();
      ImGui::Text(
          "Select filter to activate. If none is selected, all will be "
          "activated");

      ImGui::Checkbox("Show Horizontal Upward Planes",
                      &plane_filters_.horizontal_upward);
      ImGui::Checkbox("Show Horizontal Downward Planes",
                      &plane_filters_.horizontal_downward);
      ImGui::Checkbox("Show Vertical Planes", &plane_filters_.vertical);
      ImGui::Checkbox("Show Arbitrary Planes", &plane_filters_.arbitrary);

      ImGui::Separator();

      if (plane_processor_->IsPlaneDetectionCapSupported(
              XR_PLANE_DETECTION_CAPABILITY_SEMANTIC_CEILING_BIT_EXT)) {
        ImGui::Checkbox("Show Ceilings", &plane_filters_.ceilings);
      }

      if (plane_processor_->IsPlaneDetectionCapSupported(
              XR_PLANE_DETECTION_CAPABILITY_SEMANTIC_FLOOR_BIT_EXT)) {
        ImGui::Checkbox("Show Floors", &plane_filters_.floors);
      }

      if (plane_processor_->IsPlaneDetectionCapSupported(
              XR_PLANE_DETECTION_CAPABILITY_SEMANTIC_WALL_BIT_EXT)) {
        ImGui::Checkbox("Show Walls", &plane_filters_.walls);
      }

      if (plane_processor_->IsPlaneDetectionCapSupported(
              XR_PLANE_DETECTION_CAPABILITY_SEMANTIC_PLATFORM_BIT_EXT)) {
        ImGui::Checkbox("Show Platforms", &plane_filters_.platforms);
      }
    }
    gui.EndDialog();

    if (!continue_running) {
      ALOGI("Exiting....");
      FinishActivity();
    }
  }
};

void android_main(struct android_app *state) {
  App app(state);
  app.RunApp();
  ALOGI("Exited");
}
