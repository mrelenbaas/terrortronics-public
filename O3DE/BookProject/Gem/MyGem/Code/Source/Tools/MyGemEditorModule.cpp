
#include <MyGem/MyGemTypeIds.h>
#include <MyGemModuleInterface.h>
#include "MyGemEditorSystemComponent.h"

namespace MyGem
{
    class MyGemEditorModule
        : public MyGemModuleInterface
    {
    public:
        AZ_RTTI(MyGemEditorModule, MyGemEditorModuleTypeId, MyGemModuleInterface);
        AZ_CLASS_ALLOCATOR(MyGemEditorModule, AZ::SystemAllocator);

        MyGemEditorModule()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            // Add ALL components descriptors associated with this gem to m_descriptors.
            // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
            // This happens through the [MyComponent]::Reflect() function.
            m_descriptors.insert(m_descriptors.end(), {
                MyGemEditorSystemComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         * Non-SystemComponents should not be added here
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList {
                azrtti_typeid<MyGemEditorSystemComponent>(),
            };
        }
    };
}// namespace MyGem

AZ_DECLARE_MODULE_CLASS(Gem_MyGem, MyGem::MyGemEditorModule)
