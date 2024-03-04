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
  class GoalDetectorComponent
      : public AZ::Component
  {
  public:
    AZ_COMPONENT(GoalDetectorComponent,
        "{77269E49-D4D8-4BFC-853F-7BAC0E5B92A1}");
    
    static void Reflect(AZ::ReflectContext* rc);

    GoalDetectorComponent();

    // AZ::Component interface implementation.
    void Activate() override;
    void Deactivate() override {}
  
  private:
    AzPhysics::SceneEvents::
        OnSceneTriggersEvent::Handler m_trigger;
    void OnTriggerEvents(
        const AzPhysics::TriggerEventList& tel);
    
    AZ::EntityId m_ball;
    AZ::EntityId m_reset;
    int m_team = 0;

    AZ::Vector3 GetRespawnPoint() const;
    void RespawnBall(const AZ::Vector3& v);
    void UpdateUi();
  };
} // namespace MyGem