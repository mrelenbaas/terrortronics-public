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
#include <AzCore/Component/ComponentBus.h>
#include <AzCore/RTTI/BehaviorContext.h>

namespace MyGem
{
  class UiScoreNotifications
      : public AZ::ComponentBus
  {
  public:
    virtual void OnTeamScored(int team) = 0;
  };

  using UiScoreNotificationBus = AZ::EBus<UiScoreNotifications>;

  // NEW
  class ScoreNotificationHandler
      : public UiScoreNotificationBus::Handler
      , public AZ::BehaviorEBusHandler
  {
  public:
    AZ_EBUS_BEHAVIOR_BINDER(ScoreNotificationHandler,
        "{54172CAD-38FA-452B-9EE7-3DBB71181442}",
        AZ::SystemAllocator, OnTeamScored);
    
    void OnTeamScored(int team) override
    {
      Call(FN_OnTeamScored, team);
    }
  };
}