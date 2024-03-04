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

#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/Module/Module.h>

#include "BookProjectSystemComponent.h"

#include <BookProject/BookProjectTypeIds.h>

#include "MyComponent.h"
#include "MyFindComponent.h"
//#include "MyInterface.h"
#include "MyLevelComponent.h"
#include "MyInterfaceComponent.h"
#include "MyEventComponent.h"
#include "OscillatorComponent.h"
#include "MySpawnerComponent.h"
//#include "ChickenControllerComponent.h"

namespace BookProject
{
    class BookProjectModule
        : public AZ::Module
    {
    public:
        AZ_RTTI(BookProjectModule, BookProjectModuleTypeId, AZ::Module);
        AZ_CLASS_ALLOCATOR(BookProjectModule, AZ::SystemAllocator);

        BookProjectModule()
            : AZ::Module()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), {
                BookProjectSystemComponent::CreateDescriptor(),
				MyComponent::CreateDescriptor(),
                MyFindComponent::CreateDescriptor(),
                //MyInterface::CreateDescriptor(),
                MyLevelComponent::CreateDescriptor(),
                MyInterfaceComponent::CreateDescriptor(),
                MyEventComponent::CreateDescriptor(),
                OscillatorComponent::CreateDescriptor(),
                MySpawnerComponent::CreateDescriptor(),
                //ChickenControllerComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<BookProjectSystemComponent>(),
            };
        }
    };
} // namespace BookProject

AZ_DECLARE_MODULE_CLASS(Gem_BookProject, BookProject::BookProjectModule)
