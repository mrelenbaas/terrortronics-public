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

#include "../../include/app_framework/Utils/PermissionHelper.h"

#include "../../include/app_framework/Application.h"
#include "../../include/app_framework/Components/ViewFollower.h"
#include "../../include/app_framework/IGui.h"
#include "../../include/app_framework/Scene/Node.h"
#include "../../include/app_framework/Utils/SystemHelper.h"

using namespace ml;

PermissionHelper::PermissionHelper(const std::vector<std::string> &permissions,
                                   Application *application)
    : application_(application),
      first_request_(true),
      permissions_(permissions),
      gui_(nullptr) {
  system_helper_ = application->SystemHelperFactory();
}

bool PermissionHelper::RequestPermissions() {
  std::vector<std::string> remaining = GetUngrantedPermissions();
  if (remaining.empty()) {
    if (gui_) {
      gui_->Parent()->RemoveChild(gui_);
      gui_ = nullptr;
    }
    return true;
  }

  // first time round, just request the permissions.
  if (first_request_) {
    first_request_ = false;
    system_helper_->RequestApplicationPermissions(remaining);
    return false;
  }

  // We've already requested permissions, but didn't
  // get them all, now popup a dialog instructing the
  // user to re-request the permissions.
  if (gui_) {
    gui_->SetVisible(true);
    return false;
  }

  auto pose = XrPosef{{0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -2.0f}};

  std::tie(std::ignore, gui_) = Components::ViewFollower::Factory(
      Components::ViewFollower::SMOOTH | Components::ViewFollower::UPRIGHT,
      pose, application_->GetXRCore());

  auto *dialog = application_->CreateGui(
      500, 250, 500, Components::Gui::NONE,
      [this](IGui &gui, const XrFrameState &frame_state) {
        bool continue_running = true;
        gui.BeginDialog("Permissions", &continue_running);
        ImGui::Text(
            "Not all permissions were granted. The following\npermissions are "
            "required to run this application");

        ImGui::Separator();
        for (const auto &permission : permissions_) {
          ImGui::Text("%s", permission.c_str());
        }
        if (ImGui::Button("Request Permission")) {
          std::vector<std::string> remaining = GetUngrantedPermissions();
          system_helper_->RequestApplicationPermissions(remaining);
        }

        gui.EndDialog();

        if (!continue_running) {
          application_->FinishActivity();
        }
      });

  gui_->AddChild(dialog);
  application_->GetRoot()->AddChild(gui_);
  Linear::XrCreateIdentity(pose);
  dialog->SetPose(pose);
  return false;
}

std::vector<std::string> PermissionHelper::GetUngrantedPermissions() const {
  std::vector<std::string> remaining;
  for (auto &permission : permissions_) {
    if (!system_helper_->CheckApplicationPermission(permission)) {
      remaining.push_back(permission);
    }
  }
  return remaining;
}

bool PermissionHelper::PermissionGranted() {
  bool all_granted = GetUngrantedPermissions().empty();
  if (all_granted) {
    if (gui_) {
      gui_->Parent()->RemoveChild(gui_);
      gui_ = nullptr;
    }
  }
  return all_granted;
}
