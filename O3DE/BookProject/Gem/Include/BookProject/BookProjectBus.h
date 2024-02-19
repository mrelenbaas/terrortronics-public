
#pragma once

#include <BookProject/BookProjectTypeIds.h>

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace BookProject
{
    class BookProjectRequests
    {
    public:
        AZ_RTTI(BookProjectRequests, BookProjectRequestsTypeId);
        virtual ~BookProjectRequests() = default;
        // Put your public methods here
    };

    class BookProjectBusTraits
        : public AZ::EBusTraits
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////
    };

    using BookProjectRequestBus = AZ::EBus<BookProjectRequests, BookProjectBusTraits>;
    using BookProjectInterface = AZ::Interface<BookProjectRequests>;

} // namespace BookProject
