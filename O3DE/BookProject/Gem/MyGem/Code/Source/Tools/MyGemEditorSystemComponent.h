
#pragma once

#include <AzToolsFramework/API/ToolsApplicationAPI.h>

#include <Clients/MyGemSystemComponent.h>

namespace MyGem
{
    /// System component for MyGem editor
    class MyGemEditorSystemComponent
        : public MyGemSystemComponent
        , protected AzToolsFramework::EditorEvents::Bus::Handler
    {
        using BaseSystemComponent = MyGemSystemComponent;
    public:
        AZ_COMPONENT_DECL(MyGemEditorSystemComponent);

        static void Reflect(AZ::ReflectContext* context);

        MyGemEditorSystemComponent();
        ~MyGemEditorSystemComponent();

    private:
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        // AZ::Component
        void Activate() override;
        void Deactivate() override;
    };
} // namespace MyGem
