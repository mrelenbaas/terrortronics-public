
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
