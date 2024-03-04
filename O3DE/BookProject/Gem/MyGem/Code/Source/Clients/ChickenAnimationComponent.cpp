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

#include "ChickenAnimationComponent.h"
#include <AzCore/Serialization/EditContext.h>
#include <Integration/AnimGraphComponentBus.h>
//#include <EMotionFX/Code/Source/Integration/AnimGraphComponentBus.h>

namespace MyGem
{
  void ChickenAnimationComponent::Reflect(AZ::ReflectContext* rc)
  {
    if (auto sc = azrtti_cast<AZ::SerializeContext*>(rc))
    {
      sc->Class<ChickenAnimationComponent, AZ::Component>()
        ->Field("Actor", &ChickenAnimationComponent::m_actor)
        ->Version(1);
      
      if (AZ::EditContext* ec = sc->GetEditContext())
      {
        using namespace AZ::Edit;
        ec->Class<ChickenAnimationComponent>(
          "Chicken Animation",
          "[Player controlled chicken]")
          ->ClassElement(ClassElements::EditorData, "")
          ->Attribute(
              Attributes::AppearsInAddComponentMenu,
              AZ_CRC_CE("Game"))
          ->DataElement(nullptr,
              &ChickenAnimationComponent::m_actor,
              "Actor", "Entity with chicken actor.");
      }
    }
  }

  void ChickenAnimationComponent::Activate()
  {
    ChickenNotificationBus::Handler::BusDisconnect();
  }

  void ChickenAnimationComponent::Deactivate()
  {
    ChickenNotificationBus::Handler::BusDisconnect();
  }

  void ChickenAnimationComponent::OnChickenSpeedChanged(float s)
  {
    using namespace EMotionFX::Integration;
    AnimGraphComponentRequestBus::Event(m_actor,
        &AnimGraphComponentRequests::SetNamedParameterFloat,
            "Speed", s);
  }
} // namespace MyGem