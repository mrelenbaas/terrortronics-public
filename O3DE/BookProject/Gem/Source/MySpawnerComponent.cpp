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

#include "MySpawnerComponent.h"
#include <AzCore/Asset/AssetSerializer.h>
#include <AzCore/Serialization/EditContext.h>

using namespace BookProject;

void MySpawnerComponent::Activate()
{
  using namespace AzFramework;
  AZ::Transform world = GetEntity()->GetTransform()->GetWorldTM();
  m_ticket = EntitySpawnTicket(m_spawnableAsset);

  auto cb = [world](
    EntitySpawnTicket::Id, // ticketId
    SpawnableEntityContainerView view)
  {
    const AZ::Entity* e = *view.begin();
    if (auto* tc = e->FindComponent<TransformComponent>())
    {
      tc->SetWorldTM(world);
    }
  };

  if (m_ticket.IsValid())
  {
    SpawnAllEntitiesOptionalArgs optionalArgs;
    optionalArgs.m_preInsertionCallback = AZStd::move(cb);
    SpawnableEntitiesInterface::Get()->SpawnAllEntities(
      m_ticket, AZStd::move(optionalArgs));
  }
}

void MySpawnerComponent::Reflect(AZ::ReflectContext* reflection)
{
  auto sc = azrtti_cast<AZ::SerializeContext*>(reflection);
  if (!sc) return;

  sc->Class<MySpawnerComponent, Component>()
    ->Field("Prefab", &MySpawnerComponent::m_spawnableAsset)
    ->Version(1);
  
  AZ::EditContext* ec = sc->GetEditContext();
  if (!ec) return;

  using namespace AZ::Edit::Attributes;
  ec->Class<MySpawnerComponent>("My Spawner Component",
    "[An example of spawning prefab from C++]")
    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
      ->Attribute(AppearsInAddComponentMenu, AZ_CRC("Game"))
      ->Attribute(Category, "My Project")
      ->DataElement(nullptr, &MySpawnerComponent::m_spawnableAsset,
        "Prefab",
        "Spawn this prefab once when this entity acticates")
  ;
}