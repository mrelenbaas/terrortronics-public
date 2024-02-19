
#include "WindowPositionSystemComponent.h"

#include <WindowPosition/WindowPositionTypeIds.h>

#include <AzCore/Serialization/SerializeContext.h>

namespace WindowPosition
{
    AZ_COMPONENT_IMPL(WindowPositionSystemComponent, "WindowPositionSystemComponent",
        WindowPositionSystemComponentTypeId);

    void WindowPositionSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<WindowPositionSystemComponent, AZ::Component>()
                ->Version(0)
                ;
        }
    }

    void WindowPositionSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("WindowPositionService"));
    }

    void WindowPositionSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("WindowPositionService"));
    }

    void WindowPositionSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void WindowPositionSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    WindowPositionSystemComponent::WindowPositionSystemComponent()
    {
        if (WindowPositionInterface::Get() == nullptr)
        {
            WindowPositionInterface::Register(this);
        }
    }

    WindowPositionSystemComponent::~WindowPositionSystemComponent()
    {
        if (WindowPositionInterface::Get() == this)
        {
            WindowPositionInterface::Unregister(this);
        }
    }

    void WindowPositionSystemComponent::Init()
    {
    }

    void WindowPositionSystemComponent::Activate()
    {
        WindowPositionRequestBus::Handler::BusConnect();
        AZ::TickBus::Handler::BusConnect();
    }

    void WindowPositionSystemComponent::Deactivate()
    {
        AZ::TickBus::Handler::BusDisconnect();
        WindowPositionRequestBus::Handler::BusDisconnect();
    }

    void WindowPositionSystemComponent::OnTick([[maybe_unused]] float deltaTime, [[maybe_unused]] AZ::ScriptTimePoint time)
    {
    }

} // namespace WindowPosition
