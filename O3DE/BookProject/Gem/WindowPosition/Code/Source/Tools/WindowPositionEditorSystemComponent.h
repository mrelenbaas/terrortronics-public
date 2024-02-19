
#pragma once

#include <AzToolsFramework/API/ToolsApplicationAPI.h>

#include <Clients/WindowPositionSystemComponent.h>

namespace WindowPosition
{
    /// System component for WindowPosition editor
    class WindowPositionEditorSystemComponent
        : public WindowPositionSystemComponent
        , protected AzToolsFramework::EditorEvents::Bus::Handler
    {
        using BaseSystemComponent = WindowPositionSystemComponent;
    public:
        AZ_COMPONENT_DECL(WindowPositionEditorSystemComponent);

        static void Reflect(AZ::ReflectContext* context);

        WindowPositionEditorSystemComponent();
        ~WindowPositionEditorSystemComponent();

    private:
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        // AZ::Component
        void Activate() override;
        void Deactivate() override;
    };
} // namespace WindowPosition
