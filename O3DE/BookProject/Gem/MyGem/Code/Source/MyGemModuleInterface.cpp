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

#include "MyGemModuleInterface.h"
#include <AzCore/Memory/Memory.h>

#include <MyGem/MyGemTypeIds.h>

#include <Clients/MyGemSystemComponent.h>
#include <Clients/ChickenControllerComponent.h>
#include <Clients/UiScoreComponent.h>
#include <Clients/GoalDetectorComponent.h>
#include <Clients/KickingComponent.h>
#include <Clients/ChickenAnimationComponent.h>

namespace MyGem
{
    AZ_TYPE_INFO_WITH_NAME_IMPL(MyGemModuleInterface,
        "MyGemModuleInterface", MyGemModuleInterfaceTypeId);
    AZ_RTTI_NO_TYPE_INFO_IMPL(MyGemModuleInterface, AZ::Module);
    AZ_CLASS_ALLOCATOR_IMPL(MyGemModuleInterface, AZ::SystemAllocator);

    MyGemModuleInterface::MyGemModuleInterface()
    {
        // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
        // Add ALL components descriptors associated with this gem to m_descriptors.
        // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
        // This happens through the [MyComponent]::Reflect() function.
        m_descriptors.insert(m_descriptors.end(), {
            MyGemSystemComponent::CreateDescriptor(),
            ChickenControllerComponent::CreateDescriptor(),
            UiScoreComponent::CreateDescriptor(),
            GoalDetectorComponent::CreateDescriptor(),
            KickingComponent::CreateDescriptor(),
            ChickenAnimationComponent::CreateDescriptor()
            });
    }

    AZ::ComponentTypeList MyGemModuleInterface::GetRequiredSystemComponents() const
    {
        return AZ::ComponentTypeList{
            azrtti_typeid<MyGemSystemComponent>(),
        };
    }
} // namespace MyGem
