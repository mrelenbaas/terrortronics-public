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
#include <AzCore/Component/TickBus.h>
//#include <AzFramework/Spawnable/SpawnableEntitiesInterface.h>

namespace BookProject
{
  // An example of singing up to an Ebus, TickBus, in this case
  class OscillatorComponent
      : public AZ::Component
      , public AZ::TickBus::Handler // for ticking events
  {
  public:
      // be sure this quid is unique, avoid copy-paste errors!
      AZ_COMPONENT(OscillatorComponent, "{5BDCFB5A-3D60-49F1-B051-0BF160898647}");
    
  protected:
    // AZ::Component overrides
    void Activate() override;
    void Deactivate() override;

    // AZ::TickBus overrides
    void OnTick(float dt, AZ::ScriptTimePoint) override;

    // Provide runtime reflection, if any
    static void Reflect(AZ::ReflectContext* reflection);

    // what other components does this component require?
    static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& req);
  
  private:
    float m_period = 3.f;
    float m_currentTime = 0.f;
    float m_amplitude = 10.f;
  };
}