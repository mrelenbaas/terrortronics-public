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

#include "MyGemSystemComponent.h"

#include <MyGem/MyGemTypeIds.h>

#include <AzCore/Serialization/SerializeContext.h>

namespace MyGem
{
    AZ_COMPONENT_IMPL(MyGemSystemComponent, "MyGemSystemComponent",
        MyGemSystemComponentTypeId);

    void MyGemSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<MyGemSystemComponent, AZ::Component>()
                ->Version(0)
                ;
        }
    }

    void MyGemSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("MyGemService"));
    }

    void MyGemSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("MyGemService"));
    }

    void MyGemSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void MyGemSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    MyGemSystemComponent::MyGemSystemComponent()
    {
        if (MyGemInterface::Get() == nullptr)
        {
            MyGemInterface::Register(this);
        }
    }

    MyGemSystemComponent::~MyGemSystemComponent()
    {
        if (MyGemInterface::Get() == this)
        {
            MyGemInterface::Unregister(this);
        }
    }

    void MyGemSystemComponent::Init()
    {
    }

    void MyGemSystemComponent::Activate()
    {
        MyGemRequestBus::Handler::BusConnect();
        AZ::TickBus::Handler::BusConnect();
    }

    void MyGemSystemComponent::Deactivate()
    {
        AZ::TickBus::Handler::BusDisconnect();
        MyGemRequestBus::Handler::BusDisconnect();
    }

    void MyGemSystemComponent::OnTick([[maybe_unused]] float deltaTime, [[maybe_unused]] AZ::ScriptTimePoint time)
    {
    }

} // namespace MyGem
