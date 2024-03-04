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
#include "ChickenBus.h"

namespace MyGem
{
  class ChickenAnimationComponent
      : public AZ::Component
      , public ChickenNotificationBus::Handler
  {
  public:
    AZ_COMPONENT(ChickenAnimationComponent,
        "{1BDB8DAA-C9A8-474C-90F7-B9A7709783CC}");
    
    static void Reflect(AZ::ReflectContext* rc);

    // AZ::Component interface implementation
    void Activate() override;
    void Deactivate() override;

    // ChickenNotificationBus interface
    void OnChickenSpeedChanged(float s) override;
  
  private:
    AZ::EntityId m_actor;
  };
} // namespace MyGem