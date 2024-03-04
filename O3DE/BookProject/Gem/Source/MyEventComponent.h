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
#include <AzCore/Component/TransformBus.h>

#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <windows.h>

namespace BookProject
{
  // An example of listening to movement events
  // of TransformComponent using an AZ::Event
  class MyEventComponent : public AZ::Component
  {
  public:
    AZ_COMPONENT(MyEventComponent, "{D9738A27-ED20-4528-A1C8-E4CB9779C951}");

    static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
    {
      required.push_back(AZ_CRC_CE("TransformService"));
    }

    MyEventComponent();

    //AZ::Component overrides
    void Activate() override;
    void Deactivate() override {}

    // Provide runtime reflection, if any
    static void Reflect(AZ::ReflectContext* rc);
  
  private:
    AZ::TransformChangedEvent::Handler m_movementHandler;
    void OnWorldTransformChanged(const AZ::Transform& world);
  };
}