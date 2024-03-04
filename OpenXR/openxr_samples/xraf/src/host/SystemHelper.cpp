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

#include <app_framework/Logging.h>
#include <app_framework/Utils/AndroidHelper.h>
#include <app_framework/Utils/SystemHelper.h>
#ifdef XRAF_USE_APPSIM_CORE
#include <ml_zi_permissions.h>
#endif

static const std::string kEmptyStr = "";

namespace ml {

SystemHelper::SystemHelper(struct android_app *app) {
  version_code_ = -1;
  package_name_ = "com.magicleap.zi";
  // Make a copy of the command line arguments
  if (app->argc > 0 && app->argv != nullptr) {
    host_args_.insert(host_args_.end(), &app->argv[0], &app->argv[app->argc]);
  }
#ifdef XRAF_USE_APPSIM_CORE
  MLZIPermissionsStart();
#endif
}

SystemHelper::~SystemHelper() {
#ifdef XRAF_USE_APPSIM_CORE
  MLZIPermissionsStop();
#endif
}

const std::string &SystemHelper::GetPackageName() const {
  return package_name_;
}

int SystemHelper::GetVersionCode() const {
  return 0;
}

const std::string &SystemHelper::GetVersionName() const {
  // App Sim code goes here
  return kEmptyStr;
}

const std::string &SystemHelper::GetApplicationInstallDir() const {
  // App Sim code goes here
  return kEmptyStr;
}

const std::string &SystemHelper::GetApplicationWritableDir() const {
  // App Sim code goes here
  return kEmptyStr;
}

const std::string &SystemHelper::GetExternalFilesDir() const {
  // App Sim code goes here
  return kEmptyStr;
}

const std::string &SystemHelper::GetISO3Language() const {
  // App Sim code goes here
  return kEmptyStr;
}

bool SystemHelper::IsInteractive() const {
  // App Sim code goes here
  return true;
}

bool SystemHelper::CheckApplicationPermission(
    const std::string &permission_name) const {
#ifdef XRAF_USE_APPSIM_CORE
  MLResult result = MLZIPermissionsIsGranted(permission_name.c_str());
  return result == MLResult_Ok;
#else
  return true;
#endif
}

void SystemHelper::RequestApplicationPermission(
    const std::string &permission_name) const {
#ifdef XRAF_USE_APPSIM_CORE
  MLZIPermissionsRequest(permission_name.c_str());
#endif
}

void SystemHelper::RequestApplicationPermissions(
    const std::vector<std::string> &permissions) const {
  for (auto &permission : permissions) {
    RequestApplicationPermission(permission);
  }
}

std::unordered_map<std::string, std::string> &SystemHelper::GetIntentExtras()
    const {
  // Process as key/ value pairs
  intent_extras_.clear();
  for (size_t i = 0; i < host_args_.size(); i += 2) {
    intent_extras_[host_args_[i]] = {};
    if ((i + 1) < host_args_.size()) {
      intent_extras_[host_args_[i]] = host_args_[i + 1];
    }
  }

  return intent_extras_;
}

int SystemHelper::GetComputePackBatteryLevel() const {
  // App Sim code goes here
  return 0;
}

int SystemHelper::GetComputePackBatteryStatus() const {
  // App Sim code goes here
  return 0;
}

long SystemHelper::GetComputePackChargeTimeRemaining() const {
  // App Sim code goes here
  return -1;
}

bool SystemHelper::IsControllerPresent() const {
  // App Sim code goes here
  return false;
}

int SystemHelper::GetControllerBatteryLevel() const {
  // App Sim code goes here
  return 0;
}

int SystemHelper::GetControllerBatteryStatus() const {
  // App Sim code goes here
  return 0;
}

int SystemHelper::GetUnicodeChar(int event_type, int key_code,
                                 int meta_state) const {
  // App Sim code goes here
  (void)event_type;
  (void)key_code;
  (void)meta_state;
  return 0;
}

bool SystemHelper::IsWifiOn() const {
  return false;
}

bool SystemHelper::IsNetworkConnected() const {
  return false;
}

bool SystemHelper::IsInternetAvailable() const {
  return false;
}

bool SystemHelper::HasSystemFeature(
    const std::string &system_feature_name) const {
  return false;
}

bool SystemHelper::IsVoiceCommandsEnabled() const {
  return false;
}

}  // namespace ml
