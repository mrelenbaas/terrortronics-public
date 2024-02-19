
#pragma once

#include <AzCore/Component/Component.h>

#include <BookProject/BookProjectBus.h>

namespace BookProject
{
    class BookProjectSystemComponent
        : public AZ::Component
        , protected BookProjectRequestBus::Handler
    {
    public:
        AZ_COMPONENT_DECL(BookProjectSystemComponent);

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        BookProjectSystemComponent();
        ~BookProjectSystemComponent();

    protected:
        ////////////////////////////////////////////////////////////////////////
        // BookProjectRequestBus interface implementation

        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////
    };
}
