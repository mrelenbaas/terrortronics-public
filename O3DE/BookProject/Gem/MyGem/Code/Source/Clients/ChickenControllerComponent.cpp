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

#include "ChickenControllerComponent.h"
#include "ChickenBus.h"
#include <AzCore/Component/Entity.h>
#include <AzCore/Component/TransformBus.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzFramework/Physics/CharacterBus.h>

namespace MyGem
{
  using namespace StartingPointInput;

  void ChickenControllerComponent::Reflect(AZ::ReflectContext* rc)
  {
    if (auto sc = azrtti_cast<AZ::SerializeContext*>(rc))
    {
      sc->Class<ChickenControllerComponent, AZ::Component>()
          ->Field("Speed", &ChickenControllerComponent::m_speed)
          ->Field("Turn Speed", &ChickenControllerComponent::m_turnSpeed)
          ->Field("Gravity Speed", &ChickenControllerComponent::m_gravity)
          ->Version(2);

      if (AZ::EditContext* ec = sc->GetEditContext())
      {
        using namespace AZ::Edit;
        ec->Class<ChickenControllerComponent>(
          "Chicken Controller",
          "[Player controlled chicken]")
          ->ClassElement(ClassElements::EditorData, "")
          ->Attribute(
              Attributes::AppearsInAddComponentMenu,
                AZ_CRC_CE("Game"))
          ->DataElement(nullptr,
              &ChickenControllerComponent::m_turnSpeed,
              "Turn Speed", "Chicken's turning speed")
          ->DataElement(nullptr,
              &ChickenControllerComponent::m_speed,
              "Speed", "Chicken's speed")
          ->DataElement(nullptr,
              &ChickenControllerComponent::m_gravity,
              "Gravity", "Chicken's gravity");
      }
    }
  }

  void ChickenControllerComponent::Activate()
  {
    InputEventNotificationBus::MultiHandler::BusConnect(
      MoveFwdEventId);
    InputEventNotificationBus::MultiHandler::BusConnect(
      MoveRightEventId);
    InputEventNotificationBus::MultiHandler::BusConnect(
      RotateYawEventId);
    AZ::TickBus::Handler::BusConnect();
  }

  void ChickenControllerComponent::Deactivate()
  {
    AZ::TickBus::Handler::BusDisconnect();
    InputEventNotificationBus::MultiHandler::BusDisconnect();
  }

  void ChickenControllerComponent::OnPressed(float value)
  {
    const InputEventNotificationId* inputId =
        InputEventNotificationBus::GetCurrentBusId();
    if (inputId == nullptr)
    {
      return;
    }

    if (*inputId == MoveFwdEventId)
    {
      //AZ_Printf("Chicken", "forward axis %f", value);
      m_forward = value;
    }
    else if (*inputId == MoveRightEventId)
    {
      m_strafe = value;
    }
  }

  void ChickenControllerComponent::OnReleased(float value)
  {
    const InputEventNotificationId* inputId =
        InputEventNotificationBus::GetCurrentBusId();
    if (inputId == nullptr)
    {
      return;
    }
    if (*inputId == MoveFwdEventId)
    {
      m_forward = value;
    }
    else if (*inputId == MoveRightEventId)
    {
      m_strafe = value;
    }
  }

  void ChickenControllerComponent::OnHeld(float value)
  {
    const InputEventNotificationId* inputId =
        InputEventNotificationBus::GetCurrentBusId();
    if (inputId == nullptr)
    {
      return;
    }

    if (*inputId == RotateYawEventId)
    {
      m_yaw = value;
    }
  }

  void ChickenControllerComponent::OnTick(float,
      AZ::ScriptTimePoint)
  {
    const ChickenInput input = CreateInput();
    ProcessInput(input);
  }

  ChickenInput ChickenControllerComponent::CreateInput()
  {
    ChickenInput input;
    input.m_forwardAxis = m_forward;
    input.m_strafeAxis = m_strafe;
    input.m_viewYaw = m_yaw;

    return input;
  }

  void ChickenControllerComponent::UpdateRotation(
      const ChickenInput& input)
  {
    AZ::TransformInterface* t = GetEntity()->GetTransform();

    float currentHeading = t->GetWorldRotationQuaternion().
        GetEulerRadians().GetZ();
    currentHeading += (input.m_viewYaw * m_turnSpeed);// * -0.001f;
    /*
    if (currentHeading <= -5.0f)
    {
      currentHeading = -5.0f;
    }
    if (currentHeading >= 5.0f)
    {
      currentHeading = 5.0f;
    }
    */
    AZ::Quaternion q =
        AZ::Quaternion::CreateRotationZ(currentHeading);
    
    //AZ_Printf("Chicken", "currentHeading %f, %f", input.m_viewYaw, input.m_viewYaw * m_turnSpeed);
    
    t->SetWorldRotationQuaternion(q);
  }

  void ChickenControllerComponent::UpdateVelocity(
      const ChickenInput& input)
  {
    const float currentHeading = GetEntity()->GetTransform()->
        GetWorldRotationQuaternion().GetEulerRadians().GetZ();
    const AZ::Vector3 fwd = AZ::Vector3::CreateAxisY(input.m_forwardAxis);
    const AZ::Vector3 strafe = AZ::Vector3::CreateAxisX(input.m_strafeAxis);
    const AZ::Vector3 combined = (fwd + strafe).GetNormalized();
    m_velocity = AZ::Quaternion::CreateRotationZ(currentHeading).
        TransformVector(combined) * m_speed;
    ChickenNotificationBus::Event(GetEntityId(),
        &ChickenNotificationBus::Events::OnChickenSpeedChanged,
        m_velocity.GetLength());
  }

  void ChickenControllerComponent::ProcessInput(
      const ChickenInput& input)
  {
    UpdateRotation(input);
    UpdateVelocity(input);

    Physics::CharacterRequestBus::Event(GetEntityId(),
        &Physics::CharacterRequestBus::Events::AddVelocity,
            m_velocity);
    Physics::CharacterRequestBus::Event(GetEntityId(),
        &Physics::CharacterRequestBus::Events::AddVelocity,
            AZ::Vector3::CreateAxisZ(m_gravity));
  }
} // namespace MyGem