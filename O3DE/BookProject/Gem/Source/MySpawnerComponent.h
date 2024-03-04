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
#include <AzFramework/Spawnable/SpawnableEntitiesInterface.h>

namespace BookProject
{
  // An example of spawning prefab from C++.
  class MySpawnerComponent : public AZ::Component
  {
  public:
    AZ_COMPONENT(MySpawnerComponent, "{62F9D653-8A5D-47DF-B2CA-4F272AFBA688}");

    // AZ::Component overrides
    void Activate() override;
    void Deactivate() override {}

    // Provide runtime reflection, if any
    static void Reflect(AZ::ReflectContext* reflection);

  private:
    AZ::Data::Asset<AzFramework::Spawnable> m_spawnableAsset;
    AzFramework::EntitySpawnTicket m_ticket;
  };
}