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

#include "MyInterfaceComponent.h"
#include <AzCore/Serialization/EditContext.h>
#include <BookProject/MyInterface.h>

using namespace BookProject;

void MyInterfaceComponent::Activate()
{
  if (MyInterface* myInterface = AZ::Interface<MyInterface>::Get())
  {
    AZ_Printf("Example", "%d", myInterface->GetMyInteger());
  }
}

void MyInterfaceComponent::Reflect(AZ::ReflectContext* rc)
{
  auto sc = azrtti_cast<AZ::SerializeContext*>(rc);
  if (!sc) return;

  sc->Class<MyInterfaceComponent, Component>()->Version(1);

  AZ::EditContext* ec = sc->GetEditContext();
  if (!ec) return;

  using namespace AZ::Edit::Attributes;
  // reflection of this component for the O3DE Editor
  ec->Class<MyInterfaceComponent>("Using Interface Example", "[Communicates using AZ::Interface]")
    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
      ->Attribute(AppearsInAddComponentMenu, AZ_CRC("Game"))
      ->Attribute(Category, "MyProject");
}