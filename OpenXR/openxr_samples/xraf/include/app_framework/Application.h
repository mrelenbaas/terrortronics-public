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

#include <memory>

#ifdef XR_USE_PLATFORM_ANDROID
#include <jni.h>
#endif

#include <string>

#include "Components/Controller.h"
#include "Components/Gui.h"
#include "Scene/HitTest.h"
#include "Scene/Node.h"
#include "XrCore.h"

namespace ml {

class SystemHelper;
class WebRequest;
class IntentHelper;

class Application {
 public:
  /*! Options that can be passed while initiating the application class. */
  typedef enum ApplicationFlags {
    NONE = 0,        /**< Specify no options */
    VULKAN = 1 << 1, /**< Use Vulkan backend */
    USE_HAND_INTERACTION =
        1 << 2 /**< Allow hand based interaction with the interface. */
  } ApplicationFlags;
  Application(android_app *app, std::vector<std::string> permissions = {},
              const std::vector<std::string> &extensions = {},
              const std::vector<std::string> &optional_extensions = {},
              uint32_t flags = VULKAN,  // ApplicationFlags bitflags.
              const std::vector<XrEnvironmentBlendMode>
                  &acceptable_blend_modes = {XR_ENVIRONMENT_BLEND_MODE_ADDITIVE,
                                             XR_ENVIRONMENT_BLEND_MODE_OPAQUE},
              bool enable_controller = true);
  virtual ~Application();

  /*!
    \brief Runs the application.
  */
  void RunApp();

  /*!
    \brief Returns the root Scene Graph Node.
  */
  Scene::Node *GetRoot() const {
    return root_;
  }

  /*! \brief Returns the Asset Manager */
  IAssetManagerPtr AssetManager() {
    return IAssetManager::Factory(app_);
  }

  /*! \brief Returns the XrCore object */
  XrCore *GetXRCore() {
    return xr_core.get();
  }

  /*! \brief Creates a GUI relative to the current head pose.
   *
   * @param width width in pixels.
   * @param height height in pixels.
   * @param pixels_per_meter pixels per meter
   * @param offset offset from the head pose where to place the gui.
   * @param on_draw on draw call
   * @return node to the gui.
   *
   * If the gui must appear in a fixed position not relative to the head pose
   * simply override the pose of the node after creation.
   *
   */
  Scene::Node *CreateGui(
      uint32_t width, uint32_t height, uint32_t pixels_per_meter = 500,
      const XrPosef &pose = XrPosef{XrQuaternionf{0.0f, 0.0f, 0.0f, 1.0f},
                                    XrVector3f{0.0f, 0.0f, -2.0f}},
      uint32_t gui_flags = Components::Gui::DefaultGuiFlags,
      Components::Gui::OnDrawFunction on_draw = {});

  /*! \brief Creates a GUI relative to the current head pose.
   *
   * @param width width in pixels.
   * @param height height in pixels.
   * @param pixels_per_meter pixels per meter
   * @param gui_flags flags used to create the Gui.
   * @param on_draw on draw call
   * @return node to the gui.
   *
   * If the gui must appear in a fixed position not relative to the head pose
   * simply override the pose of the node after creation.
   *
   */
  Scene::Node *CreateGui(uint32_t width, uint32_t height,
                         uint32_t pixels_per_meter = 500,
                         uint32_t gui_flags = Components::Gui::DefaultGuiFlags,
                         Components::Gui::OnDrawFunction on_draw = {}) {
    auto pose = XrPosef{XrQuaternionf{0.0f, 0.0f, 0.0f, 1.0f},
                        XrVector3f{0.0f, 0.0f, -2.0f}};
    return CreateGui(width, height, pixels_per_meter, pose, gui_flags, on_draw);
  }

  /*!
    Finishes the activity
  */
  void FinishActivity();

  /*! \brief System Helper Factory
   *
   * This will create a new System Helper every time you
   * call it so keep a copy of this pointer.
   *
   * */
  std::shared_ptr<SystemHelper> SystemHelperFactory();

  /*! \brief Intent Helper Factory
   *
   * This will create a new Intent Helper every time you
   * call it so keep a copy of this pointer.
   *
   * */
  std::shared_ptr<IntentHelper> IntentHelperFactory();

  /*! \brief WebRequest Factory
   *
   * This will create a new WebRequest object.
   *
   * */
  std::shared_ptr<WebRequest> WebRequestFactory();

 protected:
  Scene::HitTest hit_test_;

  /*! \brief OpenXR lifecycle callback.
   *
   * https://www.khronos.org/registry/OpenXR/specs/1.0/html/xrspec.html#session-lifecycle
   *
   * Note you must call base method when overriding.
   *
   * */
  virtual void OnReady();
  /*! \brief OpenXR lifecycle callback.
   *
   * https://www.khronos.org/registry/OpenXR/specs/1.0/html/xrspec.html#session-lifecycle
   * */
  virtual void OnSynchronized(XrSessionState previous_state){};
  /*! \brief OpenXR lifecycle callback.
   *
   * https://www.khronos.org/registry/OpenXR/specs/1.0/html/xrspec.html#session-lifecycle
   * */
  virtual void OnVisible(XrSessionState previous_state){};
  /*! \brief OpenXR lifecycle callback.
   *
   * https://www.khronos.org/registry/OpenXR/specs/1.0/html/xrspec.html#session-lifecycle
   * */
  virtual void OnFocussed(){};
  /*! \brief OpenXR lifecycle callback.
   *
   * https://www.khronos.org/registry/OpenXR/specs/1.0/html/xrspec.html#session-lifecycle
   *
   * Note you must call base method when overriding.
   *
   * */
  virtual void OnStopping();
  /*! \brief Pre-render state update callback.
   *
   * Render loop callback when the application is visible.
   *
   * @param delta_time_sec time between frames in seconds
   */
  virtual void OnUpdate(float delta_time_sec) {
    (void)delta_time_sec;
  }

  /*! \brief OnPreRender is called after OnUpdate, just before rendering starts.
   *
   * Anything display/time critical should go here and be FAST, as this method
   * synchronizes app with display (may block).
   * Prefer to use OnUpdate() if possible.
   *
   * @param state state of currently rendered frame
   */
  virtual void OnPreRender(const XrFrameState &state) {
    (void)state;
  }

  /*! \brief OnReferenceSpaceChangePending is called from the
   * XrEventDataReferenceSpaceChangePending event.
   * @param event is the XrEventDataReferenceSpaceChangePending event details.
   */
  virtual void OnReferenceSpaceChangePending(
      const XrEventDataReferenceSpaceChangePending &event) {
    (void)event;
  }

  /*! \brief OnHeadsetFitChanged is called from the
   * XrEventDataHeadsetFitChangedML.
   * @param event is the XrEventDataHeadsetFitChangedML event details.
   */
  virtual void OnHeadsetFitChanged(
      const XrEventDataHeadsetFitChangedML &event) {
    (void)event;
  }

  /*! \brief OnEyeCalibrationChanged is called from the
   * XrEventDataEyeCalibrationChangedML.
   * @param event is the XrEventDataEyeCalibrationChangedML event details.
   */
  virtual void OnEyeCalibrationChanged(
      const XrEventDataEyeCalibrationChangedML &event) {
    (void)event;
  }

  /*! \brief Disables the controller interactions and ray. */
  void DisableControllerInteractions() {
    controller_interactions_enabled_ = false;
  }

  /*! \brief Enables the controller interactions and ray. */
  void EnableControllerInteractions() {
    controller_interactions_enabled_ = true;
  }

 private:
  struct android_app *app_;
  Scene::Node *root_;
  std::unique_ptr<XrCore> xr_core;
  std::shared_ptr<Components::Controller> controller_;
  bool controller_interactions_enabled_;

  static std::unique_ptr<IXrMLGraphicsDevice> GetGraphics(
      IXrMLGraphicsDevice::DeviceType device_type, XrCore *core,
      Scene::Node *node);
  void UpdateController(const XrFrameState &state);
};

}  // namespace ml
