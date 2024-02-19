
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
