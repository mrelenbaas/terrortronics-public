
#include "WindowPositionModuleInterface.h"
#include <AzCore/Memory/Memory.h>

#include <WindowPosition/WindowPositionTypeIds.h>

#include <Clients/WindowPositionSystemComponent.h>

namespace WindowPosition
{
    AZ_TYPE_INFO_WITH_NAME_IMPL(WindowPositionModuleInterface,
        "WindowPositionModuleInterface", WindowPositionModuleInterfaceTypeId);
    AZ_RTTI_NO_TYPE_INFO_IMPL(WindowPositionModuleInterface, AZ::Module);
    AZ_CLASS_ALLOCATOR_IMPL(WindowPositionModuleInterface, AZ::SystemAllocator);

    WindowPositionModuleInterface::WindowPositionModuleInterface()
    {
        // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
        // Add ALL components descriptors associated with this gem to m_descriptors.
        // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
        // This happens through the [MyComponent]::Reflect() function.
        m_descriptors.insert(m_descriptors.end(), {
            WindowPositionSystemComponent::CreateDescriptor(),
            });
    }

    AZ::ComponentTypeList WindowPositionModuleInterface::GetRequiredSystemComponents() const
    {
        return AZ::ComponentTypeList{
            azrtti_typeid<WindowPositionSystemComponent>(),
        };
    }
} // namespace WindowPosition