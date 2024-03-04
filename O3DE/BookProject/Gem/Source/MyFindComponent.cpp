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

#include "MyFindComponent.h"
#include <AZCore/Component/Entity.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzFramework/Components/TransformComponent.h>

using namespace BookProject;

void MyFindComponent::Activate()
{
  AZ::Entity* e = GetEntity();

  using namespace AzFramework;
  TransformComponent* tc = e->FindComponent<TransformComponent>();
  if (tc)
  {
    AZ::Transform t = tc->GetWorldTM();
    AZ::Vector3 p = t.GetTranslation();
    AZ_Printf("MyFind", "activated at %f %f %f", p.GetX(), p.GetY(), p.GetZ());
  }
}

void MyFindComponent::Reflect(AZ::ReflectContext* rc)
{
  auto sc = azrtti_cast<AZ::SerializeContext*>(rc);
  if (!sc) return;

  sc->Class<MyFindComponent, Component>()->Version(1);

  AZ::EditContext* ec = sc->GetEditContext();
  if (!ec) return;

  using namespace AZ::Edit::Attributes;
  // reflection of this component for O3DE Editor
  ec->Class<MyFindComponent>("Find Component Example", "[Communicates using FindComponent]")
    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
      ->Attribute(AppearsInAddComponentMenu, AZ_CRC("Game"))
      ->Attribute(Category, "My Project");
}