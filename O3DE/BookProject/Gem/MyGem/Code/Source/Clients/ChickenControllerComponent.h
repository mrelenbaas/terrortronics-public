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

#pragma once

#include <AzCore/Component/Component.h>
#include <AzCore/Component/TickBus.h>
#include <AzCore/Math/Vector3.h>
#include <StartingPointInput/InputEventNotificationBus.h>

namespace MyGem
{
  const StartingPointInput::InputEventNotificationId
      MoveFwdEventId("move forward");
  const StartingPointInput::InputEventNotificationId
      MoveRightEventId("move right");
  const StartingPointInput::InputEventNotificationId
      RotateYawEventId("rotate yaw");
  
  class ChickenInput
  {
  public:
    float m_forwardAxis = 0;
    float m_strafeAxis = 0;
    float m_viewYaw = 0;
  };

  class ChickenControllerComponent
      : public AZ::Component
      , public AZ::TickBus::Handler
      , public StartingPointInput::
          InputEventNotificationBus::MultiHandler
  {
  public:
    AZ_COMPONENT(ChickenControllerComponent,
        "{36AE830B-24AF-4B01-9BB6-95C5AFDF2B74}");

    static void Reflect(AZ::ReflectContext* rc);

    // AZ::Component interface implementation
    void Activate() override;
    void Deactivate() override;

    // AZ::InputEventNotificationBus interface
    void OnPressed(float value) override;
    void OnReleased(float value) override;
    void OnHeld(float value) override;

    // TickBus interface
    void OnTick(float deltaTime, AZ::ScriptTimePoint) override;
  
  private:
    ChickenInput CreateInput();
    void ProcessInput(const ChickenInput& input);

    void UpdateRotation(const ChickenInput& input);
    void UpdateVelocity(const ChickenInput& input);
    AZ::Vector3 m_velocity = AZ::Vector3::CreateZero();

    float m_speed = 1.f;
    float m_turnSpeed = 1.f;
    float m_gravity = 1.f;

    float m_forward = 0.f;
    float m_strafe = 0.f;
    float m_yaw = 0.f;
  };
} // namespace MyGem