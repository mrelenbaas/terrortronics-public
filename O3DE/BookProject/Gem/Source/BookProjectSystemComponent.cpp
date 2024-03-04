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

#include <AzCore/Serialization/SerializeContext.h>

#include "BookProjectSystemComponent.h"

#include <BookProject/BookProjectTypeIds.h>

namespace BookProject
{
    AZ_COMPONENT_IMPL(BookProjectSystemComponent, "BookProjectSystemComponent",
        BookProjectSystemComponentTypeId);

    void BookProjectSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<BookProjectSystemComponent, AZ::Component>()
                ->Version(0)
                ;
        }
    }

    void BookProjectSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("BookProjectService"));
    }

    void BookProjectSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("BookProjectService"));
    }

    void BookProjectSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void BookProjectSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    BookProjectSystemComponent::BookProjectSystemComponent()
    {
        if (BookProjectInterface::Get() == nullptr)
        {
            BookProjectInterface::Register(this);
        }
    }

    BookProjectSystemComponent::~BookProjectSystemComponent()
    {
        if (BookProjectInterface::Get() == this)
        {
            BookProjectInterface::Unregister(this);
        }
    }

    void BookProjectSystemComponent::Init()
    {
    }

    void BookProjectSystemComponent::Activate()
    {
        BookProjectRequestBus::Handler::BusConnect();
    }

    void BookProjectSystemComponent::Deactivate()
    {
        BookProjectRequestBus::Handler::BusDisconnect();
    }
}
