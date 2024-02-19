
#pragma once

#include <MyGem/MyGemTypeIds.h>

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace MyGem
{
    class MyGemRequests
    {
    public:
        AZ_RTTI(MyGemRequests, MyGemRequestsTypeId);
        virtual ~MyGemRequests() = default;
        // Put your public methods here
    };

    class MyGemBusTraits
        : public AZ::EBusTraits
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////
    };

    using MyGemRequestBus = AZ::EBus<MyGemRequests, MyGemBusTraits>;
    using MyGemInterface = AZ::Interface<MyGemRequests>;

} // namespace MyGem
