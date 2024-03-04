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

#include "../include/app_framework/XrCore.h"

#include <iostream>
#include <string>

#include "../include/app_framework/IGuiBackend.h"
#include "../include/app_framework/IXrMLGraphicsDevice.h"
#include "../include/app_framework/Linear.h"
#include "../include/app_framework/Logging.h"
#include "../include/app_framework/XrAndroidCore.h"
#include "../include/app_framework/XrReflection.h"

constexpr float kNoClippingNearZ = 0.05f;
constexpr float kNoClippingFarZ = 100.f;

using namespace ml;

XrCore::XrCore(const std::string &app_name)
    : app_name_(app_name),
      instance_(XR_NULL_HANDLE),
      session_(XR_NULL_HANDLE),
      local_space_(XR_NULL_HANDLE),
      view_space_(XR_NULL_HANDLE),
      session_state_(XR_SESSION_STATE_IDLE),
      session_running_(false),
      enable_debug_ext_(false),
      messenger_(XR_NULL_HANDLE),
      enable_controller_(true),
      grip_active_(false),
      supports_hand_tracking_(false),
      head_pose_origin_{{0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}},
      head_pose_origin_set_(false),
      next_view_pose_id_(0),
      action_sets_finalized_(false),
      near_z_(kNoClippingNearZ),
      far_z_(kNoClippingFarZ),
      allow_hand_interaction_dynamic_rebinding_(false) {
#ifndef NDEBUG
  enable_debug_ext_ = false;
#endif
}

XrCore::~XrCore() {
  Destroy();
}

bool XrCore::Initialize(
    std::unique_ptr<IXrMLGraphicsDevice> &graphics_device,
    XrCoreCallbacks &callbacks, const std::vector<std::string> &extensions,
    const std::vector<std::string> &optional_extensions,
    const std::vector<XrEnvironmentBlendMode> &acceptable_blend_modes,
    bool enable_controller, bool allow_hand_interaction_dynamic_rebinding) {
  if (graphics_device_ != nullptr) {
    return false;
  }

  callbacks_ = callbacks;
  enable_controller_ = enable_controller;
  allow_hand_interaction_dynamic_rebinding_ =
      allow_hand_interaction_dynamic_rebinding;

  if (!callbacks_.OnReady) {
    callbacks_.OnReady = []() {};
  }
  if (!callbacks_.OnFocussed) {
    callbacks_.OnFocussed = []() {};
  }
  if (!callbacks_.OnSynchronized) {
    callbacks_.OnSynchronized = [](XrSessionState) {};
  }
  if (!callbacks_.OnStopping) {
    callbacks_.OnStopping = []() {};
  }
  if (!callbacks_.OnUpdate) {
    callbacks_.OnUpdate = [](float) {};
  }
  if (!callbacks_.OnVisible) {
    callbacks_.OnVisible = [](XrSessionState) {};
  }
  if (!callbacks_.OnPreRender) {
    callbacks_.OnPreRender = [](const XrFrameState &) {};
  }

  graphics_device_ = std::move(graphics_device);

  if (!CreateInstance(extensions, optional_extensions,
                      acceptable_blend_modes)) {
    return false;
  }

  if (!graphics_device_->Initialize()) {
    return false;
  }

  if (!CreateSession()) {
    return false;
  }

  if (!CreateReferenceSpaces()) {
    return false;
  }

  if (!CreateSwapChains()) {
    return false;
  }

  if (enable_controller_) {
    if (!CreateActions()) {
      return false;
    }
  }

  SetDefaultClippingPlanes();

  return true;
}

void XrCore::Destroy() {
  DestroySwapChains();
  DestroyReferenceSpaces();
  DestroySession();
  graphics_device_ = nullptr;
  DestroyInstance();
}

bool XrCore::GetSystemId() {
  XrSystemGetInfo system_info{
      .type = XR_TYPE_SYSTEM_GET_INFO,
      .next = nullptr,
      .formFactor = XR_FORM_FACTOR_HEAD_MOUNTED_DISPLAY};
  if (xrGetSystem(instance_, &system_info, &system_id_) != XR_SUCCESS) {
    ALOGE("xrGetSystem failed.");
    return false;
  }
  return true;
}

XrBool32 XrCore::DebugUtilsMessengerCallbackEXT(
    XrDebugUtilsMessageSeverityFlagsEXT messageSeverity,
    XrDebugUtilsMessageTypeFlagsEXT messageTypes,
    const XrDebugUtilsMessengerCallbackDataEXT *callbackData, void *userData) {
  XrCore *self = static_cast<XrCore *>(userData);
  (void)self;

  if (callbackData && callbackData->functionName && callbackData->message) {
    switch (messageSeverity) {
      case XR_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
        ALOGV("OpenXR Debug: function=%s, message=%s",
              callbackData->functionName, callbackData->message);
        break;
      case XR_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
        ALOGI("OpenXR Debug: function=%s, message=%s",
              callbackData->functionName, callbackData->message);
        break;
      case XR_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
        ALOGW("OpenXR Debug: function=%s, message=%s",
              callbackData->functionName, callbackData->message);
        break;
      case XR_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
      default:
        ALOGE("OpenXR Debug: function=%s, message=%s",
              callbackData->functionName, callbackData->message);
        break;
    }
  }
  return XR_FALSE;
}

bool XrCore::CreateInstance(
    const std::vector<std::string> &extensions,
    const std::vector<std::string> &optional_extensions,
    const std::vector<XrEnvironmentBlendMode> &acceptable_blend_modes) {
  std::vector<const char *> enabled_layers;
  auto layers = ListLayers();
  for (const auto &layer : layers) {
    ALOGI("Layer: %s", layer.layerName);
    if (enable_debug_ext_ &&
        strcmp(layer.layerName, "XR_APILAYER_LUNARG_core_validation") == 0) {
      ALOGI("Enabling Layer: %s", layer.layerName);
      enabled_layers.push_back("XR_APILAYER_LUNARG_core_validation");
    }
  }

  auto available_extensions = ListExtensions();

  for (const auto &extension : available_extensions) {
    ALOGI("Extension: %s", extension.extensionName);
  }

  graphics_device_->PreInstanceInitialize(available_extensions);

  std::vector<const char *> enabled_extensions = {
      XR_KHR_COMPOSITION_LAYER_DEPTH_EXTENSION_NAME};
  for (const auto &name : graphics_device_->RequiredExtensions()) {
    if (!HasExtension(available_extensions, name)) {
      ALOGE("Missing Extension %s", name);
      return false;
    }
    if (!HasExtension(enabled_extensions, name)) {
      enabled_extensions.push_back(name);
    }
  }
  for (const auto &name : extensions) {
    if (!HasExtension(available_extensions, name.c_str())) {
      ALOGE("Missing Extension %s", name.c_str());
      return false;
    }
    if (!HasExtension(enabled_extensions, name.c_str())) {
      enabled_extensions.push_back(name.c_str());
    }
  }

  for (const auto &name : optional_extensions) {
    if (HasExtension(available_extensions, name.c_str())) {
      enabled_extensions.push_back(name.c_str());
    }
  }

  // Enable the Magic Leap 2 Controller profile if available.
  if (HasExtension(available_extensions,
                   XR_ML_ML2_CONTROLLER_INTERACTION_EXTENSION_NAME) &&
      !HasExtension(enabled_extensions,
                    XR_ML_ML2_CONTROLLER_INTERACTION_EXTENSION_NAME)) {
    enabled_extensions.push_back(
        XR_ML_ML2_CONTROLLER_INTERACTION_EXTENSION_NAME);
  }

  if (allow_hand_interaction_dynamic_rebinding_) {
    if (HasExtension(available_extensions,
                     XR_EXT_HAND_INTERACTION_EXTENSION_NAME) &&
        !HasExtension(enabled_extensions,
                      XR_EXT_HAND_INTERACTION_EXTENSION_NAME)) {
      enabled_extensions.push_back(XR_EXT_HAND_INTERACTION_EXTENSION_NAME);
    }
  }

  if (enable_debug_ext_ &&
      HasExtension(available_extensions, XR_EXT_DEBUG_UTILS_EXTENSION_NAME)) {
    if (!HasExtension(enabled_extensions, XR_EXT_DEBUG_UTILS_EXTENSION_NAME)) {
      enabled_extensions.push_back(XR_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
  }

  if (HasExtension(available_extensions,
                   XR_EXT_VIEW_CONFIGURATION_DEPTH_RANGE_EXTENSION_NAME) &&
      !HasExtension(enabled_extensions,
                    XR_EXT_VIEW_CONFIGURATION_DEPTH_RANGE_EXTENSION_NAME)) {
    enabled_extensions.push_back(
        XR_EXT_VIEW_CONFIGURATION_DEPTH_RANGE_EXTENSION_NAME);
  }

  for (auto name : enabled_extensions) {
    ALOGI("Enabling Extension: %s", name);
    enabled_extensions_.push_back(name);
  }

  XrInstanceCreateInfo info{
      .type = XR_TYPE_INSTANCE_CREATE_INFO,
      .next = nullptr,
      .createFlags = 0,
      .enabledApiLayerCount = static_cast<uint32_t>(enabled_layers.size()),
      .enabledApiLayerNames = enabled_layers.data(),
      .enabledExtensionCount = static_cast<uint32_t>(enabled_extensions.size()),
      .enabledExtensionNames = enabled_extensions.data()};
  info.applicationInfo.apiVersion = XR_CURRENT_API_VERSION;
  info.applicationInfo.applicationVersion = 1.0;
  strncpy(info.applicationInfo.applicationName, app_name_.c_str(),
          XR_MAX_APPLICATION_NAME_SIZE);
  info.applicationInfo.applicationName[XR_MAX_APPLICATION_NAME_SIZE - 1] = '\0';
  if (xrCreateInstance(&info, &instance_) != XR_SUCCESS) {
    ALOGE("Failed to create instance");
    return false;
  }

  if (!GetSystemId()) {
    return false;
  }

  if (enable_debug_ext_) {
    XrDebugUtilsMessengerCreateInfoEXT create_info{
        XR_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        nullptr,
        XR_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
            XR_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
            XR_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            XR_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
        XR_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            XR_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            XR_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT |
            XR_DEBUG_UTILS_MESSAGE_TYPE_CONFORMANCE_BIT_EXT,
        &DebugUtilsMessengerCallbackEXT,
        this};
    PFN_xrCreateDebugUtilsMessengerEXT xrCreateDebugUtilsMessengerEXT = nullptr;
    if (xrGetInstanceProcAddr(
            instance_, "xrCreateDebugUtilsMessengerEXT",
            (PFN_xrVoidFunction *)&xrCreateDebugUtilsMessengerEXT) !=
        XR_SUCCESS) {
      ALOGW("Unable to enable XR_EXT_DEBUG_UTILS");
    }
    xrCreateDebugUtilsMessengerEXT(instance_, &create_info, &messenger_);
  }

  XrSystemHandTrackingPropertiesEXT hand_tracking_properties{
      .type = XR_TYPE_SYSTEM_HAND_TRACKING_PROPERTIES_EXT, .next = nullptr};
  XrSystemProperties properties{.type = XR_TYPE_SYSTEM_PROPERTIES,
                                .next = &hand_tracking_properties};
  if (xrGetSystemProperties(instance_, system_id_, &properties) != XR_SUCCESS) {
    ALOGE("Unable to get system properties");
  } else {
    ALOGI("Vendor ID: %d", properties.vendorId);
    ALOGI("Supports Hand Tracking: %d",
          hand_tracking_properties.supportsHandTracking);
    supports_hand_tracking_ =
        hand_tracking_properties.supportsHandTracking == XR_TRUE;
  }

  environment_blend_modes_ = GetEnvironmentBlendModes();
  if (environment_blend_modes_.empty()) {
    ALOGE("No blend modes available.");
    return false;
  }

  for (const auto available_mode : environment_blend_modes_) {
    if (std::find(acceptable_blend_modes.begin(), acceptable_blend_modes.end(),
                  available_mode) != acceptable_blend_modes.end()) {
      environment_blend_mode_ = available_mode;
      return true;
    }
  }
  ALOGE("Unable to find acceptable environmental blend mode");
  return false;
}

void XrCore::DestroyInstance() {
  if (messenger_ != XR_NULL_HANDLE) {
    PFN_xrDestroyDebugUtilsMessengerEXT xrDestroyDebugUtilsMessengerEXT =
        nullptr;
    if (xrGetInstanceProcAddr(
            instance_, "xrDestroyDebugUtilsMessengerEXT",
            (PFN_xrVoidFunction *)&xrDestroyDebugUtilsMessengerEXT) ==
        XR_SUCCESS) {
      xrDestroyDebugUtilsMessengerEXT(messenger_);
      messenger_ = XR_NULL_HANDLE;
    }
  }
  if (instance_ != XR_NULL_HANDLE) {
    xrDestroyInstance(instance_);
    instance_ = XR_NULL_HANDLE;
  }
}

bool XrCore::CreateSession() {
  XrSessionCreateInfo create_info{
      .type = XR_TYPE_SESSION_CREATE_INFO,
      .next = graphics_device_->GetGraphicsBindings(),
      .createFlags = 0,
      .systemId = system_id_,
  };

  if (xrCreateSession(instance_, &create_info, &session_) != XR_SUCCESS) {
    ALOGE("Failed to call xrCreateSession");
    return false;
  }

  return true;
}

void XrCore::DestroySession() {
  if (session_ != XR_NULL_HANDLE) {
    xrDestroySession(session_);
    session_ = XR_NULL_HANDLE;
  }
}

bool XrCore::CreateReferenceSpaces() {
  XrPosef pose = {};
  pose.orientation.w = 1;
  XrReferenceSpaceCreateInfo reference_space_create_info{
      .type = XR_TYPE_REFERENCE_SPACE_CREATE_INFO,
      .next = nullptr,
      .referenceSpaceType = XR_REFERENCE_SPACE_TYPE_VIEW,
      .poseInReferenceSpace = pose,
  };

  if (xrCreateReferenceSpace(session_, &reference_space_create_info,
                             &view_space_) != XR_SUCCESS) {
    ALOGE("Unable to create view space");
    return false;
  }

  SetCurrentWorldSpace(XR_REFERENCE_SPACE_TYPE_LOCAL);
  return true;
}

void XrCore::DestroyReferenceSpaces() {
  if (current_space_ != XR_NULL_HANDLE) {
    xrDestroySpace(current_space_);
    current_space_ = XR_NULL_HANDLE;
  }
  if (view_space_ != XR_NULL_HANDLE) {
    xrDestroySpace(view_space_);
    view_space_ = XR_NULL_HANDLE;
  }
}

void XrCore::SetDefaultClippingPlanes() {
  float nearZ = kNoClippingNearZ;
  float farZ = kNoClippingFarZ;
  if (!GetRecommendedClippingPlanes(nearZ, farZ)) {
    ALOGW("No recommended clipping planes! Setting no clipping planes.");
  }
  SetNearZ(nearZ);
  SetFarZ(farZ);
}

bool XrCore::GetRecommendedClippingPlanes(float &nearZ, float &farZ) {
  if (!HasExtension(ListExtensions(),
                    XR_EXT_VIEW_CONFIGURATION_DEPTH_RANGE_EXTENSION_NAME)) {
    return false;
  }
  auto config_depth_range = std::make_unique<XrViewConfigurationDepthRangeEXT>(
      XrViewConfigurationDepthRangeEXT{
          XR_TYPE_VIEW_CONFIGURATION_DEPTH_RANGE_EXT});
  EnumerateViewConfigurationViews(config_depth_range.get());
  nearZ = config_depth_range->recommendedNearZ;
  farZ = config_depth_range->recommendedFarZ;
  return true;
}

std::vector<XrViewConfigurationView> XrCore::EnumerateViewConfigurationViews(
    XrViewConfigurationDepthRangeEXT *depth_range) const {
  std::vector<XrViewConfigurationView> config_views;
  uint32_t view_count = 0;
  if (xrEnumerateViewConfigurationViews(
          instance_, system_id_, XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO, 0,
          &view_count, nullptr) != XR_SUCCESS) {
    ALOGE(
        "xrEnumerateViewConfigurationViews failed to list number of "
        "configuration views.");
    return config_views;
  }

  config_views.resize(view_count,
                      {XR_TYPE_VIEW_CONFIGURATION_VIEW, depth_range});
  if (xrEnumerateViewConfigurationViews(
          instance_, system_id_, XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO,
          view_count, &view_count, config_views.data()) != XR_SUCCESS) {
    ALOGE("xrEnumerateViewConfigurationViews failed to fill the view list.");
    return config_views;
  }
  return config_views;
}

std::vector<int64_t> XrCore::EnumerateSwapChainFormats() const {
  std::vector<int64_t> formats;

  uint32_t swap_chain_format_count;
  if (xrEnumerateSwapchainFormats(session_, 0, &swap_chain_format_count,
                                  nullptr) != XR_SUCCESS) {
    ALOGE(
        "xrEnumerateSwapchainFormats failed to return number of supported "
        "formats.");
    return formats;
  }

  formats.resize(swap_chain_format_count);

  if (xrEnumerateSwapchainFormats(session_, (uint32_t)formats.size(),
                                  &swap_chain_format_count,
                                  formats.data()) != XR_SUCCESS) {
    ALOGE("xrEnumerateSwapchainFormats failed to fill list of formats.");
    return formats;
  }

  return formats;
}

bool XrCore::CreateSwapChains() {
  auto config_views = EnumerateViewConfigurationViews();
  if (config_views.empty()) {
    return false;
  }

  const auto swap_chain_formats = EnumerateSwapChainFormats();
  if (swap_chain_formats.empty()) {
    return false;
  }

  views_.resize(config_views.size(), {XR_TYPE_VIEW});

  const int64_t color_format =
      graphics_device_->SelectSwapChainGraphicsFormat(swap_chain_formats);
  const int64_t depth_format =
      graphics_device_->SelectDepthSwapChainGraphicsFormat(swap_chain_formats);

  if (color_format < 0 || depth_format < 0) {
    return false;
  }

  uint32_t swap_chain_image_count = 0;

  for (uint32_t i = 0; i < config_views.size(); i++) {
    const XrViewConfigurationView &view_configuration_view = config_views[i];
    ALOGI("Creating swapchain for view %d with dimensions Width=%d Height=%d ",
          i, view_configuration_view.recommendedImageRectWidth,
          view_configuration_view.recommendedImageRectHeight);

    auto color_swap_chain =
        std::make_shared<XrMLSwapChain>(this, graphics_device_.get());

    if (!color_swap_chain->Create(view_configuration_view, false, color_format,
                                  i)) {
      return false;
    }
    color_swap_chains_.push_back(color_swap_chain);
    swap_chain_image_count =
        std::max(swap_chain_image_count, color_swap_chain->ImageCount());

    auto depth_swap_chain =
        std::make_shared<XrMLSwapChain>(this, graphics_device_.get());

    if (!depth_swap_chain->Create(view_configuration_view, true, depth_format,
                                  i)) {
      return false;
    }
    depth_swap_chains_.push_back(depth_swap_chain);
    swap_chain_image_count =
        std::max(swap_chain_image_count, depth_swap_chain->ImageCount());
  }

  graphics_device_->SetupViews(config_views, color_format, depth_format,
                               swap_chain_image_count);

  return true;
}

void XrCore::DestroySwapChains() {
  color_swap_chains_.clear();
  depth_swap_chains_.clear();
}

void XrCore::RenderFrame() {
  if (session_ == XR_NULL_HANDLE) {
    return;
  }

  XrFrameWaitInfo frame_wait_info{XR_TYPE_FRAME_WAIT_INFO};
  XrFrameState frame_state{XR_TYPE_FRAME_STATE};
  xrWaitFrame(session_, &frame_wait_info, &frame_state);

  if (!head_pose_origin_set_ || !view_pose_callbacks_.empty()) {
    XrSpaceLocation view_pose{XR_TYPE_SPACE_LOCATION, nullptr};
    xrLocateSpace(view_space_, current_space_, frame_state.predictedDisplayTime,
                  &view_pose);

    if ((view_pose.locationFlags & XR_SPACE_LOCATION_POSITION_VALID_BIT) != 0) {
      if (!head_pose_origin_set_) {
        head_pose_origin_ = view_pose.pose;
        head_pose_origin_.orientation.x = 0.0f;
        head_pose_origin_.orientation.z = 0.0f;
        Linear::XrNormalize(head_pose_origin_.orientation);
        head_pose_origin_set_ = true;
      }
      for (auto &callback : view_pose_callbacks_) {
        callback.second(view_pose.pose);
      }
    }
  }

  callbacks_.OnPreRender(frame_state);

  XrFrameBeginInfo frame_begin_info{XR_TYPE_FRAME_BEGIN_INFO};
  xrBeginFrame(session_, &frame_begin_info);

  std::vector<XrCompositionLayerBaseHeader *> layers;
  XrCompositionLayerProjection layer{XR_TYPE_COMPOSITION_LAYER_PROJECTION};

  std::vector<XrCompositionLayerProjectionView> projection_layer_views(
      views_.size());
  std::vector<XrCompositionLayerDepthInfoKHR> depth_info(views_.size());

  if (frame_state.shouldRender == XR_TRUE) {
    graphics_device_->RenderFrame();

    if (RenderLayer(frame_state.predictedDisplayTime, projection_layer_views,
                    depth_info, layer)) {
      layers.push_back(
          reinterpret_cast<XrCompositionLayerBaseHeader *>(&layer));
    }
  }

  XrFrameEndInfo frame_end_info{
      .type = XR_TYPE_FRAME_END_INFO,
      .next = frame_end_info_next_chain_.GetChainRoot(),
      .displayTime = frame_state.predictedDisplayTime,
      .environmentBlendMode = environment_blend_mode_,
      .layerCount = (uint32_t)layers.size(),
      .layers = layers.data(),
  };

  xrEndFrame(session_, &frame_end_info);
}

bool XrCore::RenderLayer(
    XrTime predicted_display_time,
    std::vector<XrCompositionLayerProjectionView> &projection_layer_views,
    std::vector<XrCompositionLayerDepthInfoKHR> &depth_info,
    XrCompositionLayerProjection &layer) {
  bool success = true;
  XrResult res;

  XrViewState view_state{XR_TYPE_VIEW_STATE};
  const uint32_t view_capacity_input = (uint32_t)views_.size();
  uint32_t view_count_output = view_capacity_input;

  XrViewLocateInfo view_locate_info{
      .type = XR_TYPE_VIEW_LOCATE_INFO,
      .viewConfigurationType = XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO,
      .displayTime = predicted_display_time,
      .space = current_space_,
  };

  res = xrLocateViews(session_, &view_locate_info, &view_state,
                      view_capacity_input, &view_count_output, views_.data());
  if (res != XR_SUCCESS) {
    ALOGE("Failed to locate views");
    return false;
  }

  if ((view_state.viewStateFlags & XR_VIEW_STATE_POSITION_VALID_BIT) == 0 ||
      (view_state.viewStateFlags & XR_VIEW_STATE_ORIENTATION_VALID_BIT) == 0) {
    // no head pose available, nothing we can do to render now.
    return false;
  }
  graphics_device_->UpdateViewMatrix(views_);

  // Render view to the appropriate part of the swapchain image.
  for (uint32_t i = 0; i < view_count_output; i++) {
    // Each view has a separate swapchain which is acquired, rendered to, and
    // released.
    const auto &color_swap_chain = color_swap_chains_[i];
    const auto &depth_swap_chain = depth_swap_chains_[i];

    if (!color_swap_chain->AcquireImage()) {
      continue;
    }

    if (!depth_swap_chain->AcquireImage()) {
      color_swap_chain->ReleaseImage();
      continue;
    }

    depth_info[i] = {
        .type = XR_TYPE_COMPOSITION_LAYER_DEPTH_INFO_KHR,
        .next = nullptr,
        .subImage =
            {
                .swapchain = depth_swap_chain->Swapchain(),
                .imageRect = {.offset = {0, 0},
                              .extent = {.width = static_cast<int32_t>(
                                             depth_swap_chain->Width()),
                                         .height = static_cast<int32_t>(
                                             depth_swap_chain->Height())}},
                .imageArrayIndex = 0,

            },
        .minDepth = 0.0f,
        .maxDepth = 1.0f,
        .nearZ = near_z_,
        .farZ = far_z_,
    };

    projection_layer_views[i] = {
        .type = XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW,
        .next = &depth_info[i],
        .pose = views_[i].pose,
        .fov = views_[i].fov,
        .subImage =
            {
                .swapchain = color_swap_chain->Swapchain(),
                .imageRect = {.offset = {0, 0},
                              .extent = {.width = static_cast<int32_t>(
                                             color_swap_chain->Width()),
                                         .height = static_cast<int32_t>(
                                             color_swap_chain->Height())}},
                .imageArrayIndex = 0,
            },
    };

    graphics_device_->RenderView(projection_layer_views[i],
                                 color_swap_chain.get(), depth_swap_chain.get(),
                                 i);

    depth_swap_chain->ReleaseImage();
    color_swap_chain->ReleaseImage();
  }

  layer.space = current_space_;
  layer.layerFlags = XR_COMPOSITION_LAYER_BLEND_TEXTURE_SOURCE_ALPHA_BIT;
  layer.viewCount = (uint32_t)projection_layer_views.size();
  layer.views = projection_layer_views.data();
  return success;
}

void XrCore::SessionStateChangedEvent(
    const XrEventDataSessionStateChanged &state_changed_event,
    bool *exit_render_loop, bool *request_restart) {
  const XrSessionState old_state = session_state_;
  session_state_ = state_changed_event.state;

  ALOGI("XrEventDataSessionStateChanged: state %s->%s time=%ld",
        XrEnumStr(old_state), XrEnumStr(session_state_),
        state_changed_event.time);

  if ((state_changed_event.session != XR_NULL_HANDLE) &&
      (state_changed_event.session != session_)) {
    ALOGE("XrEventDataSessionStateChanged for unknown session");
    return;
  }

  switch (session_state_) {
    case XR_SESSION_STATE_READY: {
      if (session_ == XR_NULL_HANDLE) {
        return;
      }

      callbacks_.OnReady();

      XrSessionBeginInfo session_begin_info{
          .type = XR_TYPE_SESSION_BEGIN_INFO,
          .primaryViewConfigurationType =
              XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO};
      if (xrBeginSession(session_, &session_begin_info) != XR_SUCCESS) {
        ALOGE("xrBeginSession failed");
        return;
      }
      session_running_ = true;
      break;
    }
    case XR_SESSION_STATE_STOPPING: {
      if (session_ == XR_NULL_HANDLE) {
        return;
      }

      callbacks_.OnStopping();

      session_running_ = false;
      if (xrEndSession(session_) != XR_SUCCESS) {
        ALOGE("xrEndSession failed");
        return;
      }
      break;
    }
    case XR_SESSION_STATE_EXITING: {
      *exit_render_loop = true;
      // Do not attempt to restart because user closed this session.
      *request_restart = false;
      break;
    }
    case XR_SESSION_STATE_LOSS_PENDING: {
      *exit_render_loop = true;
      // Poll for a new instance.
      *request_restart = true;
      break;
    }
    case XR_SESSION_STATE_SYNCHRONIZED:
      callbacks_.OnSynchronized(old_state);
      break;
    case XR_SESSION_STATE_FOCUSED:
      callbacks_.OnFocussed();
      break;
    case XR_SESSION_STATE_VISIBLE:
      callbacks_.OnVisible(old_state);
      break;
    default:
      break;
  }
}

// Return event if one is available, otherwise return null.
const XrEventDataBaseHeader *XrCore::ReadNextEvent() {
  XrEventDataBaseHeader *base_header =
      reinterpret_cast<XrEventDataBaseHeader *>(&event_data_buffer_);
  *base_header = {XR_TYPE_EVENT_DATA_BUFFER};
  const XrResult xr = xrPollEvent(instance_, &event_data_buffer_);
  if (xr == XR_SUCCESS) {
    if (base_header->type == XR_TYPE_EVENT_DATA_EVENTS_LOST) {
      const XrEventDataEventsLost *const events_lost =
          reinterpret_cast<const XrEventDataEventsLost *>(base_header);
      ALOGW("%d events lost", events_lost->lostEventCount);
    }

    return base_header;
  }
  if (xr == XR_EVENT_UNAVAILABLE) {
    return nullptr;
  }
  ALOGE("xrPollEvent error");
  return nullptr;
}

void XrCore::PollEvents(bool *exit_render_loop, bool *request_restart) {
  if (session_ == XR_NULL_HANDLE) {
    return;
  }

  *exit_render_loop = *request_restart = false;

  // Process all pending messages.
  while (const XrEventDataBaseHeader *event = ReadNextEvent()) {
    switch (event->type) {
      case XR_TYPE_EVENT_DATA_INSTANCE_LOSS_PENDING: {
        const auto &instance_loss_pending =
            *reinterpret_cast<const XrEventDataInstanceLossPending *>(event);
        ALOGW("XrEventDataInstanceLossPending by %ld",
              instance_loss_pending.lossTime);
        *exit_render_loop = true;
        *request_restart = true;
        return;
      }
      case XR_TYPE_EVENT_DATA_SESSION_STATE_CHANGED: {
        auto session_state_changed_event =
            *reinterpret_cast<const XrEventDataSessionStateChanged *>(event);
        SessionStateChangedEvent(session_state_changed_event, exit_render_loop,
                                 request_restart);
        break;
      }
      case XR_TYPE_EVENT_DATA_REFERENCE_SPACE_CHANGE_PENDING: {
        if (callbacks_.OnReferenceSpaceChangePending) {
          auto reference_space_change_pending =
              *reinterpret_cast<const XrEventDataReferenceSpaceChangePending *>(
                  event);
          callbacks_.OnReferenceSpaceChangePending(
              reference_space_change_pending);
        }
        break;
      }
      case XR_TYPE_EVENT_DATA_HEADSET_FIT_CHANGED_ML: {
        if (callbacks_.OnHeadsetFitChanged) {
          auto headset_fit_changed =
              *reinterpret_cast<const XrEventDataHeadsetFitChangedML *>(event);
          callbacks_.OnHeadsetFitChanged(headset_fit_changed);
        }
        break;
      }
      case XR_TYPE_EVENT_DATA_EYE_CALIBRATION_CHANGED_ML: {
        if (callbacks_.OnEyeCalibrationChanged) {
          auto eye_calibration_changed =
              *reinterpret_cast<const XrEventDataEyeCalibrationChangedML *>(
                  event);
          callbacks_.OnEyeCalibrationChanged(eye_calibration_changed);
        }
        break;
      }
      default: {
        ALOGV("Ignoring event type %d", event->type);
        break;
      }
    }
  }
}

bool XrCore::IsSessionRunning() const {
  return session_running_;
}

std::vector<XrExtensionProperties> XrCore::ListExtensions() const {
  std::vector<XrExtensionProperties> extensions;
  uint32_t count = 0;
  if (xrEnumerateInstanceExtensionProperties(nullptr, 0, &count, nullptr) !=
      XR_SUCCESS) {
    ALOGE("Failed to call xrEnumerateInstanceExtensionProperties");
    return extensions;
  }
  extensions.resize(count);
  for (XrExtensionProperties &extension : extensions) {
    extension.type = XR_TYPE_EXTENSION_PROPERTIES;
  }
  if (xrEnumerateInstanceExtensionProperties(nullptr, count, &count,
                                             extensions.data()) != XR_SUCCESS) {
    ALOGE("Failed to call xrEnumerateInstanceExtensionProperties");
    return extensions;
  }
  return extensions;
}

std::vector<XrApiLayerProperties> XrCore::ListLayers() const {
  std::vector<XrApiLayerProperties> layers;
  uint32_t count = 0;
  if (xrEnumerateApiLayerProperties(0, &count, nullptr) != XR_SUCCESS) {
    ALOGE("Failed to call xrEnumerateApiLayerProperties");
    return layers;
  }
  layers.resize(count);
  for (XrApiLayerProperties &layer : layers) {
    layer.type = XR_TYPE_API_LAYER_PROPERTIES;
  }

  if (xrEnumerateApiLayerProperties(count, &count, layers.data()) !=
      XR_SUCCESS) {
    ALOGE("Failed to call xrEnumerateApiLayerProperties");
    return layers;
  }
  return layers;
}

bool XrCore::HasExtension(const std::vector<XrExtensionProperties> &extensions,
                          const char *extension_name) {
  for (const auto &extension : extensions) {
    if (strcmp(extension.extensionName, extension_name) == 0) {
      return true;
    }
  }
  return false;
}

bool XrCore::HasExtension(const std::vector<const char *> &extensions,
                          const char *extension_name) {
  for (const auto &extension : extensions) {
    if (strcmp(extension, extension_name) == 0) {
      return true;
    }
  }
  return false;
}

bool XrCore::HasExtension(const std::vector<std::string> &extensions,
                          const char *extension_name) {
  for (const auto &extension : extensions) {
    if (strcmp(extension.c_str(), extension_name) == 0) {
      return true;
    }
  }
  return false;
}

bool XrCore::CreateActions() {
  XrActionSetCreateInfo action_set_info{XR_TYPE_ACTION_SET_CREATE_INFO};
  strcpy(action_set_info.actionSetName, "xr_core");
  strcpy(action_set_info.localizedActionSetName, "XR Core");
  action_set_info.priority = 0;
  if (xrCreateActionSet(instance_, &action_set_info, &action_set_) !=
      XR_SUCCESS) {
    ALOGE("Unable to create action set");
    return false;
  }

  // shared action info
  XrActionCreateInfo action_info{XR_TYPE_ACTION_CREATE_INFO};
  action_info.countSubactionPaths = 0;
  action_info.subactionPaths = nullptr;

  // grip pose
  action_info.actionType = XR_ACTION_TYPE_POSE_INPUT;
  strcpy(action_info.actionName, "grip_pose");
  strcpy(action_info.localizedActionName, "Grip Pose");
  xrCreateAction(action_set_, &action_info, &pose_action_);

  action_info.actionType = XR_ACTION_TYPE_FLOAT_INPUT;
  strcpy(action_info.actionName, "trigger");
  strcpy(action_info.localizedActionName, "Trigger");
  xrCreateAction(action_set_, &action_info, &trigger_action_);

  action_info.actionType = XR_ACTION_TYPE_VIBRATION_OUTPUT;
  strcpy(action_info.actionName, "haptic");
  strcpy(action_info.localizedActionName, "Haptic");
  xrCreateAction(action_set_, &action_info, &haptic_action_);

  XrPath ml2_controller, simple_controller, ml2_trigger_left, ml2_trigger_right,
      simple_trigger_left, simple_trigger_right, grip_path_left, haptic_left,
      haptic_right, grip_path_right;
  xrStringToPath(instance_, "/interaction_profiles/ml/ml2_controller",
                 &ml2_controller);

  xrStringToPath(instance_, "/interaction_profiles/khr/simple_controller",
                 &simple_controller);

  xrStringToPath(instance_, "/user/hand/right/input/aim/pose",
                 &grip_path_right);
  xrStringToPath(instance_, "/user/hand/left/input/aim/pose", &grip_path_left);

  xrStringToPath(instance_, "/user/hand/right/input/trigger/value",
                 &ml2_trigger_right);
  xrStringToPath(instance_, "/user/hand/left/input/trigger/value",
                 &ml2_trigger_left);

  xrStringToPath(instance_, "/user/hand/right/input/select/click",
                 &simple_trigger_right);
  xrStringToPath(instance_, "/user/hand/left/input/select/click",
                 &simple_trigger_left);
  xrStringToPath(instance_, "/user/hand/left/output/haptic", &haptic_left);
  xrStringToPath(instance_, "/user/hand/right/output/haptic", &haptic_right);

  /* ML2 Based Bindings */
  std::vector<XrActionSuggestedBinding> ml2_bindings{
      {{trigger_action_, ml2_trigger_right},
       {trigger_action_, ml2_trigger_left},
       {pose_action_, grip_path_right},
       {pose_action_, grip_path_left},
       {haptic_action_, haptic_right},
       {haptic_action_, haptic_left}}};
  XrInteractionProfileSuggestedBinding ml2_suggested_bindings{
      XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING};
  ml2_suggested_bindings.interactionProfile = ml2_controller;
  ml2_suggested_bindings.suggestedBindings = ml2_bindings.data();
  ml2_suggested_bindings.countSuggestedBindings = (uint32_t)ml2_bindings.size();

  /* Simple Controller Based Bindings */
  std::vector<XrActionSuggestedBinding> simple_bindings{
      {{trigger_action_, simple_trigger_right},
       {trigger_action_, simple_trigger_left},
       {pose_action_, grip_path_right},
       {pose_action_, grip_path_left},
       {haptic_action_, haptic_right},
       {haptic_action_, haptic_left}}};

  XrInteractionProfileSuggestedBinding simple_suggested_bindings{
      XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING};
  simple_suggested_bindings.interactionProfile = simple_controller;
  simple_suggested_bindings.suggestedBindings = simple_bindings.data();
  simple_suggested_bindings.countSuggestedBindings =
      (uint32_t)simple_bindings.size();

  struct Bindings {
    XrInteractionProfileSuggestedBinding &binding;
    const char *name;
  };

  std::vector<Bindings> bindings = {
      {ml2_suggested_bindings, "ml/ml2_controller"},
      {simple_suggested_bindings, "khr/simple_controller"},
  };

  bool binding_found = false;
  for (auto &binding : bindings) {
    ALOGI("Trying %s interaction profile.", binding.name);
    if (xrSuggestInteractionProfileBindings(instance_, &binding.binding) ==
        XR_SUCCESS) {
      binding_found = true;
    }
  }

  if (!binding_found) {
    ALOGE("Unable to find controller binding.");
    return false;
  }

  if (allow_hand_interaction_dynamic_rebinding_ &&
      this->IsExtensionEnabled(XR_EXT_HAND_INTERACTION_EXTENSION_NAME)) {
    XrPath hand_interaction_profile, aim_activate_right, aim_activate_left;

    if (xrStringToPath(instance_,
                       "/interaction_profiles/ext/hand_interaction_ext",
                       &hand_interaction_profile) != XR_SUCCESS) {
      ALOGE("Failed to get interaction profile");
    }

    if (xrStringToPath(instance_,
                       "/user/hand/right/input/aim_activate_ext/value",
                       &aim_activate_right) != XR_SUCCESS) {
      ALOGE("Failed to get right aim activate");
    }

    if (xrStringToPath(instance_,
                       "/user/hand/left/input/aim_activate_ext/value",
                       &aim_activate_left) != XR_SUCCESS) {
      ALOGE("Failed to get left aim activate");
    }

    /* Hand Interaction Based Bindings */
    std::vector<XrActionSuggestedBinding> hand_interaction_bindings{
        {trigger_action_, aim_activate_right},
        {trigger_action_, aim_activate_left},
        {pose_action_, grip_path_right},
        {pose_action_, grip_path_left}};

    XrInteractionProfileSuggestedBinding hand_interaction_suggested_bindings{
        XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING};
    hand_interaction_suggested_bindings.interactionProfile =
        hand_interaction_profile;
    hand_interaction_suggested_bindings.suggestedBindings =
        hand_interaction_bindings.data();
    hand_interaction_suggested_bindings.countSuggestedBindings =
        (uint32_t)hand_interaction_bindings.size();

    xrSuggestInteractionProfileBindings(instance_,
                                        &hand_interaction_suggested_bindings);
  }

  XrActionSpaceCreateInfo action_space_info{XR_TYPE_ACTION_SPACE_CREATE_INFO};
  action_space_info.action = pose_action_;
  action_space_info.poseInActionSpace.orientation.w = 1.f;
  action_space_info.subactionPath = XR_NULL_PATH;
  if (xrCreateActionSpace(session_, &action_space_info, &grip_space_) !=
      XR_SUCCESS) {
    ALOGE("xrCreateActionSpace failed");
    return false;
  }

  RegisterActionSet(action_set_);
  return true;
}

void XrCore::RegisterActionSet(XrActionSet action_set) {
  if (action_sets_finalized_) {
    ALOGE("Actionsets already finalized");
    return;
  }
  action_sets_.push_back(action_set);
}

bool XrCore::FinalizeActionsSets() {
  if (action_sets_finalized_) {
    ALOGE("Action Sets already finalized.");
    return false;
  }
  XrSessionActionSetsAttachInfo attach_info{
      XR_TYPE_SESSION_ACTION_SETS_ATTACH_INFO};
  attach_info.countActionSets = action_sets_.size();
  attach_info.actionSets = action_sets_.data();
  if (xrAttachSessionActionSets(session_, &attach_info) != XR_SUCCESS) {
    ALOGE("xrAttachSessionActionSets failed");
    return false;
  }
  action_sets_finalized_ = true;
  return true;
}

void XrCore::DestroyActions() {
  if (pose_action_ != XR_NULL_HANDLE) {
    xrDestroyAction(pose_action_);
  }
  if (trigger_action_ != XR_NULL_HANDLE) {
    xrDestroyAction(trigger_action_);
  }
  if (grip_space_ != XR_NULL_HANDLE) {
    xrDestroySpace(grip_space_);
  }
  if (action_set_ != XR_NULL_HANDLE) {
    xrDestroyActionSet(action_set_);
  }
  pose_action_ = XR_NULL_HANDLE;
  trigger_action_ = XR_NULL_HANDLE;
  action_set_ = XR_NULL_HANDLE;
  grip_space_ = XR_NULL_HANDLE;
}

void XrCore::PollActions() {
  if (session_ == XR_NULL_HANDLE) {
    return;
  }

  if (session_state_ != XR_SESSION_STATE_FOCUSED) {
    return;
  }

  if (!action_sets_finalized_) {
    FinalizeActionsSets();
  }
  if (!enable_controller_) {
    return;
  }

  // Sync actions
  const XrActiveActionSet active_action_set{action_set_, XR_NULL_PATH};
  XrActionsSyncInfo sync_info{XR_TYPE_ACTIONS_SYNC_INFO};
  sync_info.countActiveActionSets = 1;
  sync_info.activeActionSets = &active_action_set;
  if (xrSyncActions(session_, &sync_info) != XR_SUCCESS) {
    ALOGE("xrSyncActions Failed");
    return;
  }

  XrActionStateGetInfo get_info{XR_TYPE_ACTION_STATE_GET_INFO};
  get_info.action = trigger_action_;
  get_info.subactionPath = XR_NULL_PATH;
  XrActionStateFloat grab_value{XR_TYPE_ACTION_STATE_FLOAT};
  if (xrGetActionStateFloat(session_, &get_info, &grab_value) != XR_SUCCESS) {
    ALOGE("xrGetActionStateFloat Failed");
    return;
  }

  trigger_active_ = grab_value.isActive == XR_TRUE;
  if (trigger_active_) {
    trigger_ = grab_value.currentState;
  }

  get_info.action = pose_action_;
  XrActionStatePose poseState{XR_TYPE_ACTION_STATE_POSE};
  if (xrGetActionStatePose(session_, &get_info, &poseState) != XR_SUCCESS) {
    ALOGE("xrGetActionStatePose Failed");
    return;
  }

  grip_active_ = poseState.isActive;
}

bool XrCore::GetControllerPose(XrTime time, XrPosef &pose) {
  if (!enable_controller_) {
    return true;
  }
  if (!grip_active_) {
    return false;
  }
  if (time != memorized_controller_pose_time_) {
    memorized_controller_pose_.type = XR_TYPE_SPACE_LOCATION;
    memorized_controller_pose_.next = nullptr;
    memorized_controller_pose_time_ = time;
    if (xrLocateSpace(grip_space_, current_space_, time,
                      &memorized_controller_pose_) != XR_SUCCESS) {
      ALOGE("xrLocateSpace Failed");
      return false;
    }
  }
  pose = memorized_controller_pose_.pose;
  return (memorized_controller_pose_.locationFlags &
          XR_SPACE_LOCATION_POSITION_VALID_BIT) != 0 &&
         (memorized_controller_pose_.locationFlags &
          XR_SPACE_LOCATION_ORIENTATION_VALID_BIT) != 0;
}

bool XrCore::GetControllerTrigger(float &trigger) const {
  if (!trigger_active_) {
    return false;
  }
  trigger = trigger_;
  return true;
}

std::vector<XrEnvironmentBlendMode> XrCore::GetEnvironmentBlendModes() {
  std::vector<XrEnvironmentBlendMode> modes;
  uint32_t count = 0;
  if (xrEnumerateEnvironmentBlendModes(
          instance_, system_id_, XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO, 0,
          &count, nullptr) != XR_SUCCESS) {
    return modes;
  }
  if (count == 0) {
    return modes;
  }
  modes.resize(count);
  if (xrEnumerateEnvironmentBlendModes(
          instance_, system_id_, XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO,
          (uint32_t)modes.size(), &count, modes.data()) != XR_SUCCESS) {
    modes.clear();
    return modes;
  }
  return modes;
}

bool XrCore::SetEnvironmentBlendMode(XrEnvironmentBlendMode mode) {
  if (std::find(environment_blend_modes_.begin(),
                environment_blend_modes_.end(),
                mode) == environment_blend_modes_.end()) {
    ALOGE(
        "Environmental Blend Mode %d is not an acceptable blend mode on this "
        "runtime.",
        mode);
    return false;
  }
  environment_blend_mode_ = mode;
  return true;
}

bool XrCore::SetCurrentWorldSpace(XrReferenceSpaceType type, XrTime time,
                                  XrSpaceLocation *space_location,
                                  const XrPosef &pose) {
  XrReferenceSpaceCreateInfo reference_space_create_info{
      .type = XR_TYPE_REFERENCE_SPACE_CREATE_INFO,
      .next = nullptr,
      .referenceSpaceType = type,
      .poseInReferenceSpace = pose,
  };

  XrSpace space;
  if (xrCreateReferenceSpace(session_, &reference_space_create_info, &space) !=
      XR_SUCCESS) {
    ALOGE("Unable to create reference space");
    return false;
  }

  if (space_location != nullptr) {
    xrLocateSpace(current_space_, space, time, space_location);
  }

  if (current_space_ != XR_NULL_HANDLE) {
    xrDestroySpace(current_space_);
  }
  current_space_ = space;
  return true;
}

std::vector<XrReferenceSpaceType> XrCore::EnumerateReferenceSpaces() {
  std::vector<XrReferenceSpaceType> types;
  uint32_t count;
  if (xrEnumerateReferenceSpaces(session_, 0, &count, nullptr) != XR_SUCCESS) {
    ALOGE("Unable to xrEnumerateReferenceSpaces");
    return types;
  }
  if (count == 0) {
    ALOGV("xrEnumerateReferenceSpaces returned 0.");
    return types;
  }
  types.resize(count);
  if (xrEnumerateReferenceSpaces(session_, count, &count, types.data()) !=
      XR_SUCCESS) {
    ALOGE("Unable to xrEnumerateReferenceSpaces");
    types.clear();
  }
  return types;
}

bool XrCore::ApplyHaptic(XrDuration duration, float frequency,
                         float amplitude) const {
  XrHapticActionInfo info{XR_TYPE_HAPTIC_ACTION_INFO};
  info.subactionPath = XR_NULL_PATH;
  info.action = haptic_action_;
  XrHapticVibration vibration{XR_TYPE_HAPTIC_VIBRATION};
  vibration.duration = duration;
  vibration.frequency = frequency;
  vibration.amplitude = amplitude;
  return xrApplyHapticFeedback(
             session_, &info,
             reinterpret_cast<XrHapticBaseHeader *>(&vibration)) == XR_SUCCESS;
}
