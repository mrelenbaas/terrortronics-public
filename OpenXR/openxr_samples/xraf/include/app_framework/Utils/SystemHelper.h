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

#include <string>
#include <unordered_map>
#include <vector>

#ifdef XR_USE_PLATFORM_ANDROID
#include <jni.h>
#endif

namespace ml {

class SystemHelper {
 public:
  SystemHelper(struct android_app *app);
  ~SystemHelper();

  // make sure the public getter methods below are called from the
  // android_main() thread
  int GetVersionCode() const;
  const std::string &GetPackageName() const;
  const std::string &GetVersionName() const;
  const std::string &GetApplicationInstallDir() const;
  const std::string &GetApplicationWritableDir() const;
  const std::string &GetExternalFilesDir() const;
  const std::string &GetISO3Language() const;
  bool CheckApplicationPermission(const std::string &permission_name) const;
  void RequestApplicationPermission(const std::string &permission_name) const;
  void RequestApplicationPermissions(
      const std::vector<std::string> &permissions) const;
  std::unordered_map<std::string, std::string> &GetIntentExtras() const;
  bool IsInteractive() const;
  int GetComputePackBatteryLevel() const;
  int GetComputePackBatteryStatus() const;
  long GetComputePackChargeTimeRemaining() const;
  bool IsControllerPresent() const;
  int GetControllerBatteryLevel() const;
  int GetControllerBatteryStatus() const;
  int GetUnicodeChar(int event_type, int key_code, int meta_state) const;
  bool IsWifiOn() const;
  bool IsNetworkConnected() const;
  bool IsInternetAvailable() const;
  bool IsVoiceCommandsEnabled() const;
  bool HasSystemFeature(const std::string &system_feature_name) const;

 private:
  mutable int version_code_;
  mutable std::string package_name_;
  mutable std::string app_writable_dir_;
  mutable std::string external_files_dir_;
  mutable std::string app_install_dir_;
  mutable std::string version_name_;
  mutable std::string language_;
  mutable std::unordered_map<std::string, std::string> intent_extras_;
  void CreateAndCacheJNI();

#ifdef XR_USE_PLATFORM_ANDROID
  JavaVM *vm_;
  jclass context_;
  jclass pkg_mng_cls_;
  jclass network_cls_;
  jclass system_settings_cls_;

  jobject batt_mng_obj_;
  jobject content_resolver_obj_;
  jobject intent_filter_obj_;
  jobject native_activity_;

  jmethodID get_batt_property_mid_;
  jmethodID get_batt_charge_time_mid_;
  jmethodID sys_sett_get_int_mid_;
  jmethodID registerReceiver_mid_;

  mutable jobject pwr_mgr_;
  mutable jmethodID is_interactive_mid_;
  mutable jobject pkg_info_obj_;
  mutable jobject app_info_obj_;

  jobject GetPackageInfo() const;
  jobject GetAppInfo() const;
#else
  mutable std::vector<std::string> host_args_;
#endif
};

}  // namespace ml
