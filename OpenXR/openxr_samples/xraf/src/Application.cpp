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

#include "../include/app_framework/Application.h"

#include <exception>

#include "../include/app_framework/Components/GLTF.h"
#include "../include/app_framework/Components/Gui.h"
#include "../include/app_framework/Linear.h"
#include "../include/app_framework/Scene/Node.h"
#include "../include/app_framework/Utils/IntentHelper.h"
#include "../include/app_framework/Utils/SystemHelper.h"
#include "../include/app_framework/Utils/WebRequest.h"
#include "../include/app_framework/XrAndroidCore.h"
#include "../include/app_framework/XrAppSimCore.h"
#include "../include/app_framework/XrHostCore.h"
#include "../include/app_framework/XrMLSceneGraphGraphicsDeviceVulkan.h"

using namespace ml;
using namespace ml::Linear;

std::unique_ptr<ml::IXrMLGraphicsDevice> Application::GetGraphics(
    IXrMLGraphicsDevice::DeviceType device_type, XrCore *core,
    Scene::Node *node) {
  switch (device_type) {
    case ml::IXrMLGraphicsDevice::Vulkan:
      return std::make_unique<XrMLSceneGraphGraphicsDeviceVulkan>(core, node);
    case ml::IXrMLGraphicsDevice::OpenGLES:
    // Unsupported by Scene Graph at this point.
    // return std::make_unique<BasicOpenGLESGraphicsDevice>(core);
    default:
      return nullptr;
  }
}

Application::Application(
    android_app *app, std::vector<std::string> permissions,
    const std::vector<std::string> &extensions,
    const std::vector<std::string> &optional_extensions, uint32_t flags,
    const std::vector<XrEnvironmentBlendMode> &acceptable_blend_modes,
    bool enable_controller)
    : app_(app), controller_interactions_enabled_(enable_controller) {
#ifdef XR_USE_PLATFORM_ANDROID
  Components::GLTF::SetAssetManager(app->activity->assetManager);
#endif

  try {
#ifdef XR_USE_PLATFORM_ANDROID
    xr_core = std::make_unique<XrAndroidCore>(ALOG_TAG, app);
#elif defined XRAF_USE_HOST_CORE
    xr_core = std::make_unique<XrHostCore>(ALOG_TAG);
#else
    xr_core = std::make_unique<XrAppSimCore>(ALOG_TAG, app);
#endif
    root_ = new Scene::Node();
    root_->Acquire();

    std::unique_ptr<ml::IXrMLGraphicsDevice> graphics_device;

    if (flags & ApplicationFlags::VULKAN) {
      graphics_device =
          GetGraphics(IXrMLGraphicsDevice::Vulkan, xr_core.get(), root_);
    }

    if (!graphics_device) {
      ALOGE("Unable to create graphics device");
      throw std::runtime_error("Unable to create graphics device");
    }

    XrCoreCallbacks callbacks{
        [this]() { this->OnReady(); },
        [this](XrSessionState previous_state) {
          this->OnSynchronized(previous_state);
        },
        [this](XrSessionState previous_state) {
          this->OnVisible(previous_state);
        },
        [this]() { this->OnFocussed(); },
        [this]() { this->OnStopping(); },
        [this](float delta_time_s) { this->OnUpdate(delta_time_s); },
        [this](const XrFrameState &frame_state) {
          UpdateController(frame_state);
          this->OnPreRender(frame_state);
          xr_core->GraphicsDevice()->GetGui()->OnDraw(frame_state);
        },
        [this](const XrEventDataReferenceSpaceChangePending &event) {
          this->OnReferenceSpaceChangePending(event);
        },
        [this](const XrEventDataHeadsetFitChangedML &event) {
          this->OnHeadsetFitChanged(event);
        },
        [this](const XrEventDataEyeCalibrationChangedML &event) {
          this->OnEyeCalibrationChanged(event);
        }};

    // takes ownership of graphics device.
    if (!xr_core->Initialize(graphics_device, callbacks, extensions,
                             optional_extensions, acceptable_blend_modes,
                             enable_controller,
                             flags & ApplicationFlags::USE_HAND_INTERACTION)) {
      ALOGE("Ending Activity, failed to initialize core.");
      FinishActivity();
      return;
    }

  } catch (std::runtime_error &e) {
    ALOGE("Failed to create XrCore: %s", e.what());
    throw e;
  }
}

void Application::UpdateController(const XrFrameState &state) {
  if (!controller_) {
    return;
  }

  if (!controller_interactions_enabled_) {
    controller_->Hide();
    return;
  }

  XrPosef pose;
  auto core = GetXRCore();
  if (!core->GetControllerPose(state.predictedDisplayTime, pose)) {
    controller_->Hide();
    return;
  }
  controller_->Show();
  controller_->SetPose(pose);

  float trigger = 0.0f;
  core->GetControllerTrigger(trigger);

  Scene::HitTest::Result result{};

  XrMatrix4x4f controller_T_world;
  XrVector3f identity{1.0f, 1.0f, 1.0f};
  XrCreateTranslationRotationScale(controller_T_world, pose.position,
                                   pose.orientation, identity);

  XrVector3f ray_normal{0.0f, 0.0f, -1.f};
  XrVector3f ray_direction;
  XrVector3f ray_center;
  XrVector3f zero{0.0f, 0.0f, 0.0f};

  ml::Linear::XrRotate(ray_direction, pose.orientation, ray_normal);
  XrTransform(ray_center, controller_T_world, zero);
  XrNormalize(ray_direction);

  if (hit_test_.Test({(uint32_t)Scene::HitTest::HitGroups::GUI, pose.position,
                      ray_direction, 1000.0f},
                     result)) {
    controller_->SetRayLength(result.distance);
  } else {
    controller_->SetRayLength(1.0f);
  }
  core->GraphicsDevice()->GetGui()->UpdateController(
      pose, result.node, result.position, result.node_position, trigger);
}

Application::~Application() {
  // finish the last render cycle before destroying things.
  xr_core->GraphicsDevice()->Finish();
  root_->Release();
  controller_.reset();
  xr_core.reset();
}

void Application::RunApp() {
  if (xr_core) {
    xr_core->RenderLoop();
  }
}
void Application::FinishActivity() {
  xr_core->FinishActivity();
}

Scene::Node *Application::CreateGui(uint32_t width, uint32_t height,
                                    uint32_t pixels_per_meter,
                                    const XrPosef &pose, uint32_t gui_flags,
                                    Components::Gui::OnDrawFunction on_draw) {
  Scene::Node *node = nullptr;
  std::shared_ptr<Components::Gui> gui;

  std::tie(gui, node) = Components::Gui::Factory(
      GetXRCore(), width, height, (float)pixels_per_meter, gui_flags, on_draw);
  float width_meters = 1.05f * (float)width / (float)pixels_per_meter;
  float height_meters = 1.05f * (float)height / (float)pixels_per_meter;
  root_->AddChild(node);
  Scene::HitTest::Registration r;
  r.bounding_box = XrVector3f{width_meters, height_meters, 1.0f};
  r.node = node;
  r.hit_group = (uint32_t)Scene::HitTest::HitGroups::GUI;
  r.hit_quads = {{XrVector3f{0.0f, 0.0f, 0.0f}, XrVector3f{0.0f, 0.0f, -1.0}}};
  hit_test_.Register(r);
  gui->SetRemovedCallback([this, node]() { hit_test_.Unregister(node); });

  auto reference = xr_core->HeadPoseOrigin();
  node->SetPose(XrCreatePose(reference, pose));
  return node;
}

void Application::OnReady() {
  if (controller_ == nullptr) {
    Scene::Node *node = nullptr;
    std::tie(controller_, node) = Components::Controller::Factory();
    GetRoot()->AddChild(node);
  }
}

void Application::OnStopping() {
  root_->Clear();
  controller_.reset();
}

std::shared_ptr<SystemHelper> Application::SystemHelperFactory() {
  return std::make_shared<ml::SystemHelper>(app_);
}

std::shared_ptr<IntentHelper> Application::IntentHelperFactory() {
  return std::make_shared<ml::IntentHelper>(app_);
}

std::shared_ptr<WebRequest> Application::WebRequestFactory() {
  return std::make_shared<ml::WebRequest>(app_);
}
