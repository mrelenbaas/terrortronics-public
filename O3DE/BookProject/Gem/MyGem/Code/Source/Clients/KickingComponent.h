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
#include <AzFramework/Physics/Common/PhysicsEvents.h>

namespace MyGem
{
  class KickingComponent
      : public AZ::Component
  {
  public:
    AZ_COMPONENT(KickingComponent,
        "{F6EC4198-FE4B-4FCD-8554-1A576E517F8A}");
    
    static void Reflect(AZ::ReflectContext* rc);

    KickingComponent();

    // AZ::Component interface implementation
    void Activate() override;
    void Deactivate() override {}
  
  private:
    AzPhysics::SceneEvents::
        OnSceneTriggersEvent::Handler m_trigger;
    void OnTriggerEvents(
        const AzPhysics::TriggerEventList& tel);
    
    float m_kickForce = 1000.f;

    void KickBall(AZ::EntityId ball);

    AZ::Vector3 GetBallPosition(AZ::EntityId ball);
    AZ::Vector3 GetSelfPosition();
    void AddImpulseToBall(AZ::Vector3 v, AZ::EntityId ball);
  };
}