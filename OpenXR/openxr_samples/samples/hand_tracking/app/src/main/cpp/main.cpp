// Copyright 2024 Bradley Elenbaas
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <app_framework/Application.h>
#include <app_framework/Components/GLTF.h>
#include <app_framework/Components/Gui.h>
#include <app_framework/Components/Light.h>
#include <app_framework/Components/Sound.h>
#include <app_framework/Components/Text.h>
#include <app_framework/Extensions/ExtHandTracking.h>
#include <app_framework/Geometry/Axis.h>
#include <app_framework/Geometry/Cube.h>
#include <app_framework/Utils/IntentHelper.h>

#include <chrono>
#include <cstdlib>
#include <string>

#include "bubble.h"

using namespace ml;

#define BUBBLES_IN_GAME 10

class App : public Application {
 public:
  App(struct android_app *state)
      : Application(state, {},
                    Extensions::ExtHandTracking::RequiredExtensions()),
        score_(0),
        missed_(0),
        sound_node_(nullptr) {
    try {
      left_.hand_ = std::make_unique<Extensions::ExtHandTracking>(
          GetXRCore(), XR_HAND_LEFT_EXT);
      right_.hand_ = std::make_unique<Extensions::ExtHandTracking>(
          GetXRCore(), XR_HAND_RIGHT_EXT);
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
  }

  void OnSynchronized(XrSessionState previous_state) override {
    // Check if we've been here before!
    if (previous_state != XR_SESSION_STATE_READY) {
      return;
    }

    auto root = GetRoot();
    if (root->ChildCount() > 1) {
      ALOGE("Already created.");
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

    /* Create the hand joint nodes */
    for (auto hand : std::vector<Hand *>{&left_, &right_}) {
      for (uint32_t i = 0; i < XR_HAND_JOINT_COUNT_EXT; i++) {
        auto node = new Scene::Node();
        root->AddChild(node);
        node->SetScale(0.01f);
        auto gfx = ml::Geometry::Cube::LineFactory();
        node->AddComponent(gfx);
        hand->joints_.push_back(node);
#ifdef LABEL_JOINTS
        std::string n = std::to_string(i);
        Scene::Node *text;
        std::tie(std::ignore, text) = ml::Components::Text::Factory(n);
        node->AddChild(text);
        text->SetScale(10.0f);
        node->SetVisible(false);
#endif
      }
    }

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

  // On Pre-render runs right before the graphics
  // renders.
  void OnPreRender(const XrFrameState &state) override {
    UpdateHand(state.predictedDisplayTime, left_);
    UpdateHand(state.predictedDisplayTime, right_);
    XrVector3f wind{-0.001f, 0.0f, 0.0f};
    for (auto &bubble : bubbles_) {
      if (bubble->Update(state.predictedDisplayTime, wind)) {
        missed_++;
      }
    }
  }

 private:
  struct Hand {
    std::unique_ptr<Extensions::ExtHandTracking> hand_;
    std::vector<Scene::Node *> joints_;
  };
  Hand left_;
  Hand right_;
  int score_;
  int missed_;
  std::vector<std::shared_ptr<Bubble>> bubbles_;
  std::vector<uint8_t> pop_sound_;
  Scene::Node *sound_node_;

  void UpdateHand(XrTime time, Hand &hand) {
    if (!hand.hand_ || hand.joints_.empty()) {
      SetHandVisibility(hand, false);
      return;
    }

    bool is_active;
    if (!hand.hand_->Locate(time, is_active)) {
      SetHandVisibility(hand, false);
      ALOGE("Locate failed");
      return;
    }
    if (!is_active) {
      SetHandVisibility(hand, false);
      return;
    }

    for (uint32_t i = 0; i < XR_HAND_JOINT_COUNT_EXT; i++) {
      auto finger = hand.joints_[i];
      auto &info = hand.hand_->Locations()[i];
      const uint32_t track_flags = XR_SPACE_LOCATION_POSITION_VALID_BIT |
                                   XR_SPACE_LOCATION_ORIENTATION_VALID_BIT |
                                   XR_SPACE_LOCATION_POSITION_TRACKED_BIT;
      if ((info.locationFlags & track_flags) == track_flags) {
        finger->SetPose(info.pose);
        finger->SetScale(info.radius);
        finger->SetVisible(true);
        CheckCollision(finger);
      } else {
        finger->SetVisible(false);
      }
    }
  }

  void CheckCollision(Scene::Node *node) {
    auto transform = node->WorldTransform();
    XrVector3f position;
    XrGetTranslation(position, transform);
    for (auto &bubble : bubbles_) {
      if (bubble->TestHit(position)) {
        score_++;
        auto snd = sound_node_->GetComponent<Components::Sound>();
        if (snd) {
          sound_node_->SetTranslation(position);
          snd->Play();
        } else {
          ALOGE("Hmm no sound component");
        }
      }
    }
  }

  void SetHandVisibility(Hand &hand, bool visible) {
    for (auto *joint : hand.joints_) {
      joint->SetVisible(visible);
    }
  }

  void OnDrawGui(IGui &gui, const XrFrameState &frame_state) {
    bool continue_running = true;

    gui.BeginDialog("OpenXR Hand Tracking Demo", &continue_running);
    float accuracy = 0.0f;
    if (score_ + missed_ > 0) {
      accuracy = 100.0 * (float)score_ / (float)(score_ + missed_);
    }
    ImGui::Text(
        "Pop the bubbles around you using your hands!\nScore: %d\nMissed: "
        "%d\nAccuracy: %.0f%%\n",
        score_, missed_, accuracy);

    ImGui::Separator();
    ImGui::Text(
        "\nThis application was built with the SDK Team's render engine.\n"
        "It uses OpenXR as the mixed reality API and Vulkan as \nthe graphics "
        "API.");

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
