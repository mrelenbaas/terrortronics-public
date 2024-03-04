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
#include "UiScoreBus.h"

namespace MyGem
{
  class UiScoreComponent
      : public AZ::Component
      , public UiScoreNotificationBus::Handler
  {
  public:
    AZ_COMPONENT(UiScoreComponent,
        "{3B0F416B-FC49-42A1-9809-2866C035BA81}");
    
    static void Reflect(AZ::ReflectContext* rc);

    // AZ::Component interface implementation
    void Activate() override;
    void Deactivate() override;

    // UiScoreNotificanBus interface
    void OnTeamScored(int team) override;
  
  private:
    int m_teams[2] = { 0, 0 };
  };
} // namespace MyGem