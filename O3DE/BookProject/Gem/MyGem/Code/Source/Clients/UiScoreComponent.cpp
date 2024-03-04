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

#include "UiScoreComponent.h"
#include <AzCore/Serialization/EditContext.h>
#include <LyShine/Bus/UiTextBus.h>

namespace MyGem
{
  void UiScoreComponent::Reflect(AZ::ReflectContext* rc)
  {
    if (auto sc = azrtti_cast<AZ::SerializeContext*>(rc))
    {
      sc->Class<UiScoreComponent, AZ::Component>()
        ->Version(1);
      
      if (AZ::EditContext* ec = sc->GetEditContext())
      {
        using namespace AZ::Edit;
        ec->Class<UiScoreComponent>(
          "Ui Score Component",
          "[Updates score text]")
          ->ClassElement(ClassElements::EditorData, "")
          ->Attribute(
              Attributes::AppearsInAddComponentMenu,
                  AZ_CRC_CE("UI"));
      }
    }
  }

  void UiScoreComponent::Activate()
  {
    UiScoreNotificationBus::Handler::BusConnect(GetEntityId());
  }

  void UiScoreComponent::Deactivate()
  {
    UiScoreNotificationBus::Handler::BusDisconnect();
  }

  void UiScoreComponent::OnTeamScored(int team)
  {
    //AZ_Printf("Chicken", "forward axis %f", 0.0f);
    if (team >= 0 && team <= 1)
    {
      m_teams[team]++;
      char buffer[10];
      azsnprintf(buffer, 10,
          "%d : %d", m_teams[0], m_teams[1]);
      UiTextBus::Event(GetEntityId(),
          &UiTextBus::Events::SetText, AZStd::string(buffer));
      //AZ_Printf("Chicken", "forward axis %f", 1.0f);
    }
  }
}