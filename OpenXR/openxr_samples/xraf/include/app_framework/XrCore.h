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

#include <atomic>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "AssetManager.h"
#include "Extensions/MLUserCalibration.h"
#include "IXrMLGraphicsDevice.h"
#include "Utils/StructNextChain.h"
#include "XrMLSwapChain.h"

namespace ml {

struct XrCoreCallbacks {
  // Life Cycle
  std::function<void()> OnReady;
  std::function<void(XrSessionState)> OnSynchronized;
  std::function<void(XrSessionState)> OnVisible;
  std::function<void()> OnFocussed;
  std::function<void()> OnStopping;

  // Render Loop
  std::function<void(float)> OnUpdate;
  std::function<void(const XrFrameState &)> OnPreRender;

  // Events
  std::function<void(const XrEventDataReferenceSpaceChangePending &)>
      OnReferenceSpaceChangePending;
  std::function<void(const XrEventDataHeadsetFitChangedML &)>
      OnHeadsetFitChanged;
  std::function<void(const XrEventDataEyeCalibrationChangedML &)>
      OnEyeCalibrationChanged;
};

class XrCore {
 public:
  /*! creates the OpenXR session with one of the graphics_devices
   * in order of preference.
   */
  XrCore(const std::string &app_name);
  virtual ~XrCore();

  bool Initialize(
      std::unique_ptr<IXrMLGraphicsDevice> &graphics_device,
      XrCoreCallbacks &callbacks, const std::vector<std::string> &extensions,
      const std::vector<std::string> &optional_extensions,
      const std::vector<XrEnvironmentBlendMode> &acceptable_blend_modes =
          {XR_ENVIRONMENT_BLEND_MODE_ADDITIVE,
           XR_ENVIRONMENT_BLEND_MODE_OPAQUE},
      bool enable_controller = true,
      bool allow_hand_interaction_dynamic_rebinding = false);

  void RenderFrame();
  bool IsSessionRunning() const;
  void PollActions();
  void PollEvents(bool *exit_render_loop, bool *request_restart);
  std::vector<XrExtensionProperties> ListExtensions() const;
  std::vector<XrApiLayerProperties> ListLayers() const;

  XrInstance Instance() {
    return instance_;
  }
  XrSession Session() {
    return session_;
  }
  XrSystemId SystemId() {
    return system_id_;
  }

  const std::string &AppName() const {
    return app_name_;
  }

  virtual void RenderLoop() = 0;

  /*! \brief Call this to exit out of the application. */
  virtual void FinishActivity() = 0;

  IXrMLGraphicsDevice *GraphicsDevice() {
    return graphics_device_.get();
  }

  /*! \brief Returns the Controller Pose at requested time. */
  bool GetControllerPose(XrTime time, XrPosef &pose);
  /*! \brief Returns the trigger value. */
  bool GetControllerTrigger(float &trigger) const;

  /*! \brief Set Haptic output on currently active controller. */
  bool ApplyHaptic(XrDuration duration, float frequency, float amplitude) const;

  /*! \brief Returns true if the runtime supports hand tracking. */
  inline bool SupportsHandTracking() const {
    return supports_hand_tracking_;
  }

  /*! \brief Returns true if the runtime has enabled the requested extension. */
  inline bool IsExtensionEnabled(const char *name) const {
    return HasExtension(enabled_extensions_, name);
  }

  /*! \brief The World Space XrSpace. */
  XrSpace WorldSpace() const {
    return current_space_;
  }

  /*! \brief The View Space XrSpace. */
  XrSpace ViewSpace() const {
    return view_space_;
  }

  /*! \brief Returns the list of supported environment blend modes. */
  const std::vector<XrEnvironmentBlendMode> &EnvironmentBlendModes() const {
    return environment_blend_modes_;
  }

  /*! \brief Sets the current environment blend mode. */
  bool SetEnvironmentBlendMode(XrEnvironmentBlendMode mode);

  /*! \brief Returns the current environment blend mode. */
  XrEnvironmentBlendMode EnvironmentBlendMode() const {
    return environment_blend_mode_;
  }

  /*! \brief HeadPoseOrigin returns the vertically aligned head pose at startup.
   */
  XrPosef HeadPoseOrigin() const {
    return head_pose_origin_;
  }

  /*! \brief HeadPoseOriginSet returns true if the head pose was set. */
  bool HeadPoseOriginSet() const {
    return head_pose_origin_set_;
  }

  using ViewPoseUpdateCallback = std::function<void(const XrPosef &view_pose)>;
  uint32_t RegisterForViewPoseUpdates(ViewPoseUpdateCallback callback) {
    int id = next_view_pose_id_.fetch_add(1);
    view_pose_callbacks_[id] = callback;
    return id;
  }
  void UnregisterFromViewPoseUpdates(uint32_t id) {
    view_pose_callbacks_.erase(id);
  }

  /*! \brief Register the action set with the runtime. */
  void RegisterActionSet(XrActionSet action_set);

  /*! \brief The current XrSessionState. */
  inline XrSessionState SessionState() const {
    return session_state_;
  }

  /*! \brief Sets the default values for Near Z and Far Z clipping distance.
   *
   * Default values are taken from #GetRecommendedClippingPlanes, if unavailable
   * no clipping plane is set.
   *
   * see
   * https://registry.khronos.org/OpenXR/specs/1.0/html/xrspec.html#XrViewConfigurationDepthRangeEXT
   * */
  void SetDefaultClippingPlanes();

  /*! \brief Get recommended near Z and far Z values if they are available and
   * return true. If the extension is not available return false.
   *
   * see
   * https://registry.khronos.org/OpenXR/specs/1.0/html/xrspec.html#XrViewConfigurationDepthRangeEXT
   * */
  bool GetRecommendedClippingPlanes(float &nearZ, float &farZ);

  /*! \brief Sets the Near Z clipping distance.
   *
   * see
   * https://registry.khronos.org/OpenXR/specs/1.0/html/xrspec.html#XR_KHR_composition_layer_depth
   * */
  void SetNearZ(float value) {
    near_z_ = value;
  }

  /*! \brief Gets the Near Z clipping distance.
   *
   * see
   * https://registry.khronos.org/OpenXR/specs/1.0/html/xrspec.html#XrViewConfigurationDepthRangeEXT
   * */
  float GetNearZ() const {
    return near_z_;
  }

  /*! \brief Sets the Far Z clipping distance.
   *
   * see
   * https://registry.khronos.org/OpenXR/specs/1.0/html/xrspec.html#XR_KHR_composition_layer_depth
   * */
  void SetFarZ(float value) {
    far_z_ = value;
  }

  /*! \brief Gets the Far Z clipping distance.
   *
   * see
   * https://registry.khronos.org/OpenXR/specs/1.0/html/xrspec.html#XrViewConfigurationDepthRangeEXT
   * */
  float GetFarZ() const {
    return far_z_;
  }

  /*! \brief Returns helper struct related to XrFrameEndInfo next chain. */
  StructNextChain &GetFrameEndInfoNextChain() {
    return frame_end_info_next_chain_;
  }

  /*! \brief Sets the world origin space for the render graph.
   *
   * returns the translation from old to new space.
   * */
  bool SetCurrentWorldSpace(XrReferenceSpaceType type, XrTime time,
                            XrSpaceLocation *space_location,
                            const XrPosef &pose = XrPosef{
                                {0.0f, 0.0f, 0.0f, 1.0f}});

  /*! \brief Sets the world origin space for the render graph. */
  bool SetCurrentWorldSpace(XrReferenceSpaceType type) {
    return SetCurrentWorldSpace(type, XrTime(0), nullptr);
  }

  std::vector<XrReferenceSpaceType> EnumerateReferenceSpaces();

 protected:
  bool FinalizeActionsSets();
  void Destroy();
  virtual bool CreateInstance(
      const std::vector<std::string> &extensions,
      const std::vector<std::string> &optional_extensions,
      const std::vector<XrEnvironmentBlendMode> &acceptable_blend_modes);
  void DestroyInstance();
  bool CreateSession();
  void DestroySession();
  bool CreateReferenceSpaces();
  void DestroyReferenceSpaces();
  std::vector<XrViewConfigurationView> EnumerateViewConfigurationViews(
      XrViewConfigurationDepthRangeEXT *depth_range = nullptr) const;
  std::vector<int64_t> EnumerateSwapChainFormats() const;

  bool CreateSwapChains();
  void DestroySwapChains();
  bool CreateActions();
  void DestroyActions();
  bool GetSystemId();
  bool RenderLayer(
      XrTime predicted_display_time,
      std::vector<XrCompositionLayerProjectionView> &projection_layer_views,
      std::vector<XrCompositionLayerDepthInfoKHR> &depth_info,
      XrCompositionLayerProjection &layer);
  const XrEventDataBaseHeader *ReadNextEvent();
  void SessionStateChangedEvent(
      const XrEventDataSessionStateChanged &state_changed_event,
      bool *exit_render_loop, bool *request_restart);
  static XrBool32 DebugUtilsMessengerCallbackEXT(
      XrDebugUtilsMessageSeverityFlagsEXT messageSeverity,
      XrDebugUtilsMessageTypeFlagsEXT messageTypes,
      const XrDebugUtilsMessengerCallbackDataEXT *callbackData, void *userData);

  std::vector<XrEnvironmentBlendMode> GetEnvironmentBlendModes();

  std::unique_ptr<IXrMLGraphicsDevice> graphics_device_;
  std::string app_name_;
  XrCoreCallbacks callbacks_;
  XrInstance instance_;
  XrSystemId system_id_;
  XrSession session_;
  XrSpace local_space_;
  XrSpace view_space_;
  XrSpace current_space_;
  std::vector<XrView> views_;
  std::vector<std::shared_ptr<XrMLSwapChain>> color_swap_chains_;
  std::vector<std::shared_ptr<XrMLSwapChain>> depth_swap_chains_;
  XrEventDataBuffer event_data_buffer_;
  XrSessionState session_state_;
  bool session_running_;
  bool enable_debug_ext_;
  XrDebugUtilsMessengerEXT messenger_;

  XrActionSet action_set_;
  XrSpace grip_space_;
  XrAction trigger_action_;
  XrAction pose_action_;
  XrAction haptic_action_;

  bool enable_controller_;
  bool trigger_active_;
  float trigger_;
  bool grip_active_;
  XrTime memorized_controller_pose_time_;
  XrSpaceLocation memorized_controller_pose_;
  bool supports_hand_tracking_;
  std::vector<XrEnvironmentBlendMode> environment_blend_modes_;
  XrEnvironmentBlendMode environment_blend_mode_;
  XrPosef head_pose_origin_;
  bool head_pose_origin_set_;
  std::atomic_uint32_t next_view_pose_id_;
  std::map<uint32_t, ViewPoseUpdateCallback> view_pose_callbacks_;
  std::vector<XrActionSet> action_sets_;
  bool action_sets_finalized_;
  float near_z_;  // in meters
  float far_z_;   // in meters
  StructNextChain frame_end_info_next_chain_;
  std::vector<std::string> enabled_extensions_;
  bool allow_hand_interaction_dynamic_rebinding_;

  static bool HasExtension(const std::vector<XrExtensionProperties> &extensions,
                           const char *extension_name);
  static bool HasExtension(const std::vector<const char *> &extensions,
                           const char *extension_name);
  static bool HasExtension(const std::vector<std::string> &extensions,
                           const char *extension_name);
  bool IsInitialized() const {
    return instance_ != XR_NULL_HANDLE && session_ != XR_NULL_HANDLE &&
           !color_swap_chains_.empty();
  }
};

}  // namespace ml
