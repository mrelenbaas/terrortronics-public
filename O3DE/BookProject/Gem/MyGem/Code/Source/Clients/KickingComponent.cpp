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

#include "KickingComponent.h"
#include <AzCore/Component/Entity.h>
#include <AzCore/Component/TransformBus.h>
#include <AzCore/Interface/Interface.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzFramework/Physics/PhysicsScene.h>
#include <AzFramework/Physics/RigidBodyBus.h>

namespace MyGem
{
  void KickingComponent::Reflect(AZ::ReflectContext* rc)
  {
    if (auto sc = azrtti_cast<AZ::SerializeContext*>(rc))
    {
      sc->Class<KickingComponent, AZ::Component>()
        ->Field("Kick force", &KickingComponent::m_kickForce)
        ->Version(1);
      
      if (AZ::EditContext* ec = sc->GetEditContext())
      {
        using namespace AZ::Edit;
        ec->Class<KickingComponent>(
          "Kicking",
          "[Kicking the ball when it comes close]")
          ->ClassElement(ClassElements::EditorData, "")
          ->Attribute(
              Attributes::AppearsInAddComponentMenu,
                  AZ_CRC_CE("Game"))
          ->DataElement(0, &KickingComponent::m_kickForce,
              "Kick force", "impulse strength");
      }
    }
  }

  KickingComponent::KickingComponent()
      : m_trigger([this](
          AzPhysics::SceneHandle,
          const AzPhysics::TriggerEventList& tel)
      {
        OnTriggerEvents(tel);
      }) {}
  
  void KickingComponent::Activate()
  {
    auto* si = AZ::Interface<AzPhysics::SceneInterface>::Get();
    if (si != nullptr)
    {
      AzPhysics::SceneHandle sh = si->GetSceneHandle(
          AzPhysics::DefaultPhysicsSceneName);
      si->RegisterSceneTriggersEventHandler(sh, m_trigger);
    }
  }

  void KickingComponent::OnTriggerEvents(
      const AzPhysics::TriggerEventList& tel)
  {
    AZ_Printf("Chicken", "here %f", 0.0f);
    using namespace AzPhysics;
    for (const TriggerEvent& te : tel)
    {
      if (te.m_triggerBody &&
          te.m_triggerBody->GetEntityId() == GetEntityId())
      {
        AZ_Printf("Chicken", "here %f", 1.0f);
        if (te.m_type == TriggerEvent::Type::Enter)
        {
          AZ_Printf("Chicken", "here %f", 2.0f);
          KickBall(te.m_otherBody->GetEntityId());
        }
      }
    }
  }

  void KickingComponent::KickBall(AZ::EntityId b)
  {
    AZ::Vector3 impulse = GetBallPosition(b) - GetSelfPosition();
    impulse.Normalize();
    impulse *= m_kickForce;
    AddImpulseToBall(impulse, b);
  }

  AZ::Vector3 KickingComponent::GetBallPosition(AZ::EntityId ball)
  {
    AZ::Vector3 ballPosition = AZ::Vector3::CreateZero();
    AZ::TransformBus::EventResult(ballPosition, ball,
        &AZ::TransformBus::Events::GetWorldTranslation);
    return ballPosition;
  }

  AZ::Vector3 KickingComponent::GetSelfPosition()
  {
    return GetEntity()->GetTransform()->
        GetWorldTM().GetTranslation();
  }

  void KickingComponent::AddImpulseToBall(
      AZ::Vector3 v, AZ::EntityId ball)
  {
    Physics::RigidBodyRequestBus::Event(ball,
      &Physics::RigidBodyRequestBus::Events::ApplyLinearImpulse,
        v);
  }
} // namespace MyGem