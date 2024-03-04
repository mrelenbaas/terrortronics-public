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

#include <app_framework/Application.h>
#include <app_framework/Components/GLTF.h>
#include <app_framework/Components/Gui.h>
#include <app_framework/Components/Light.h>
#include <app_framework/Components/Sound.h>
#include <app_framework/Extensions/ExtEyeGaze.h>
#include <app_framework/Geometry/Cube.h>
#include <app_framework/Utils/PermissionHelper.h>

#include <chrono>
#include <cstdlib>
#include <string>

#include "bubble.h"

#include <iostream>
#include <fstream>
using namespace std;

using namespace ml;

#define BUBBLES_IN_GAME 10

class App : public Application {
 public:
  App(struct android_app *state)
      : Application(state, {}, Extensions::ExtEyeGaze::RequiredExtensions()),
        gaze_node_(nullptr),
        score_(0),
        missed_(0),
        sound_node_(nullptr) {
    std::vector<std::string> permissions = {
        {"com.magicleap.permission.EYE_TRACKING",
         "android.permission.READ_EXTERNAL_STORAGE"}};
    permission_helper_ = std::make_unique<PermissionHelper>(permissions, this);

    try {
      eye_tracker_ = std::make_unique<Extensions::ExtEyeGaze>(GetXRCore());
    } catch (std::runtime_error &e) {
      ALOGE("Unable to create tracker: %s", e.what());
      FinishActivity();
    }

    auto asset = AssetManager()->Open("pop.raw");
    if (asset) {
      int64_t len = asset->Length();
      pop_sound_.resize(len);
      memcpy(pop_sound_.data(), asset->GetBuffer(), len);
    } else {
      ALOGE("Unable to read pop.raw");
    }

    GetXRCore()->RegisterForViewPoseUpdates(
        [this](const XrPosef &view_pose) { head_pose_ = view_pose; });
  }

  void OnFocussed() override {
    if (!permission_helper_->RequestPermissions()) {
      // If the permission was not granted, don't even try to use the
      // restricted resources.
      return;
    }

    auto root = GetRoot();
    if (gaze_node_) {
      // Return if app was already initialized
      return;
    }

    /* Create the GUI */
    {
      CreateGui(500, 250, 500, Components::Gui::DefaultGuiFlags,
                std::bind(&App::OnDrawGui, this, std::placeholders::_1,
                          std::placeholders::_2));
    }

    Scene::Node *light_node = nullptr;
    std::tie(std::ignore, light_node) =
        Components::Light::Factory(XrColor4f{0.7f, 0.7f, 1.0f, 1.0f});
    light_node->SetTranslation(XrVector3f{0.0f, 2.0f, 1.0f});
    root->AddChild(light_node);

    gaze_node_ = new Scene::Node();
    root->AddChild(gaze_node_);
    gaze_node_->SetVisible(false);

    target_node_ = new Scene::Node();
    root->AddChild(target_node_);
    target_node_->SetScale(0.02f);
    auto gfx = ml::Geometry::Cube::LineFactory();
    target_node_->AddComponent(gfx);

    /* Create the bubble game objects */
    for (int i = 0; i < BUBBLES_IN_GAME; i++) {
      bubbles_.push_back(std::make_shared<Bubble>(GetXRCore(), root, i));
    }

    /* Create a sound Node */
    {
      std::tie(std::ignore, sound_node_) =
          Components::Sound::Factory(pop_sound_, 1, 44100, 16);
      root->AddChild(sound_node_);
    }
  }

  void OnPreRender(const XrFrameState &state) override {
    UpdateGaze(state.predictedDisplayTime);
    XrVector3f wind{-0.001f, 0.0f, 0.0f};
    for (auto &bubble : bubbles_) {
      if (bubble->Update(state.predictedDisplayTime, wind)) {
        missed_++;
      }
    }
  }

 private:
  static constexpr XrVector3f FORWARD{0, 0, -1};
  std::unique_ptr<PermissionHelper> permission_helper_;
  Scene::Node *gaze_node_;
  Scene::Node *target_node_;
  std::unique_ptr<Extensions::ExtEyeGaze> eye_tracker_;
  int score_;
  int missed_;
  std::vector<std::shared_ptr<Bubble>> bubbles_;
  std::vector<uint8_t> pop_sound_;
  Scene::Node *sound_node_;
  XrPosef head_pose_;

  bool PollGaze() {
    if (GetXRCore()->SessionState() != XR_SESSION_STATE_FOCUSED) {
      return false;
    }

    bool is_active;
    if (!eye_tracker_->Poll(is_active)) {
      target_node_->SetVisible(false);
      ALOGE("Poll failed");
      return false;
    }
    if (!is_active) {
      target_node_->SetVisible(false);
    }
    return true;
  }

  void UpdateGaze(XrTime time) {
    if (!gaze_node_ || !target_node_) {
      return;
    }

    if (!PollGaze()) {
      return;
    }

    XrPosef gaze_pose;
    bool is_nominal = false;
    if (!eye_tracker_->GetPose(time, gaze_pose, is_nominal)) {
      ALOGE("GetPose failed");
      return;
    }

    if (!is_nominal) {
      ALOGW("GetPose returned subnominal pose! Results may vary!");
    }

    gaze_node_->SetPose(gaze_pose);

    // Create direction by rotating forward vector using eye_gaze rotation
    XrVector3f gaze_dir;
    XrRotate(gaze_dir, gaze_node_->Pose().orientation, FORWARD);

    // Create offset from face ~1m forward
    const float offset_from_face_fwd = target_node_->Scale().z / 2 + 1.f;

    // Set initial pose from eye_gaze
    target_node_->SetPose(gaze_pose);

    // Reposition our target node by previously created offset in the direction of eye_gaze
    target_node_->SetTranslation(XrVector3f{
        gaze_pose.position.x + offset_from_face_fwd * gaze_dir.x,
        gaze_pose.position.y + offset_from_face_fwd * gaze_dir.y,
        gaze_pose.position.z + offset_from_face_fwd * gaze_dir.z});
    target_node_->SetVisible(true);

    CheckCollision(gaze_dir);
  }

  void CheckCollision(const XrVector3f& gaze_dir) {
    for (auto &bubble : bubbles_) {
      if (bubble->TestHitRay(head_pose_.position, gaze_dir)) {
        score_++;
        auto snd = sound_node_->GetComponent<Components::Sound>();
        if (snd) {
          sound_node_->SetTranslation(bubble->Node()->Translation());
          snd->Play();
        } else {
          ALOGE("Hmm no sound component");
        }
      }
    }
  }

  void OnDrawGui(IGui &gui, const XrFrameState &frame_state) {
    bool continue_running = true;

    gui.BeginDialog("OpenXR Eye Gaze Demo", &continue_running);
    float accuracy = 0.0f;
    if (score_ + missed_ > 0) {
      accuracy = 100.0 * (float)score_ / (float)(score_ + missed_);
    }
    int newScore;
    if (filesystem::exists("/sdcard/state.txt")) {
        newScore = 0;
    }
    if (filesystem::exists("/sdcard/state1.txt")) {
        newScore = 1;
    }
    if (filesystem::exists("/sdcard/state2.txt")) {
        newScore = 2;
    }
    if (filesystem::exists("/sdcard/state3.txt")) {
        newScore = 3;
    }
    if (filesystem::exists("/sdcard/state4.txt")) {
        newScore = 4;
    }
    if (filesystem::exists("/sdcard/state5.txt")) {
        newScore = 5;
    }
    if (filesystem::exists("/sdcard/state6.txt")) {
        newScore = 6;
    }
    if (filesystem::exists("/sdcard/state7.txt")) {
        newScore = 7;
    }
    if (filesystem::exists("/sdcard/state8.txt")) {
        newScore = 8;
    }
    if (filesystem::exists("/sdcard/state9.txt")) {
        newScore = 9;
    }

    /*
    ifstream MyFile("/sdcard/state.txt");
    //std::string srcFilePath = "/sdcard/state.txt";
    std::string line;
    std::string otherLine;
    //FILE* file = fopen(srcFilePath.c_str(), "r");
    bool isFirst = true;
    while (getline(MyFile, line)) {
      //Log.d("HAM", "here");
      if (isFirst) {
          otherLine = line;
          isFirst = false;
      }
    }
    MyFile.close();
     */
    //gui.BeginDialog("OpenXR Plane Detection Demo", &continue_running);
    //if (file != nullptr) {
    //    ImGui::Text("(SUCCESS) XR_EXT_plane_detection runtime support: ");
    //} else {
    //    ImGui::Text("(FAILURE) XR_EXT_plane_detection runtime support: ");
    //}
    //fclose(file);

    //gui.BeginDialog("OpenXR Eye Gaze Demo", &continue_running);
    /*
    float accuracy = 0.0f;
    if (score_ + missed_ > 0) {
      accuracy = 100.0 * (float)score_ / (float)(score_ + missed_);
    }
    ImGui::Text(
        "Pop the bubbles around you using your eyes (by looking at them)!"
        "\nScore: %d\nMissed: %d\nAccuracy: %.0f%%\n: HERE: %s\n",
        score_, missed_, accuracy, otherLine.c_str());
    */
    ImGui::Text(
      "Pop the bubbles around you using your eyes (by looking at them)!"
      "\nScore: %d\nMissed: %d\nAccuracy: %.0f%%\n: NEW SCORE: %d\n",
      score_, missed_, accuracy, newScore);

    ImGui::Separator();
    ImGui::Text(
        "\nThis application was built with the SDK Team's render engine.\n"
        "It uses OpenXR as the mixed reality API and Vulkan as \n"
        "the graphics API.");

    gui.EndDialog();

    if (!continue_running) {
      ALOGE("Exiting....");
      FinishActivity();
    }
  }
};

void android_main(struct android_app *state) {
  App app(state);
  app.RunApp();
}
