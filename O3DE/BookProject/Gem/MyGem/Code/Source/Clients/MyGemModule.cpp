
#include <MyGem/MyGemTypeIds.h>
#include <MyGemModuleInterface.h>
#include "MyGemSystemComponent.h"

namespace MyGem
{
    class MyGemModule
        : public MyGemModuleInterface
    {
    public:
        AZ_RTTI(MyGemModule, MyGemModuleTypeId, MyGemModuleInterface);
        AZ_CLASS_ALLOCATOR(MyGemModule, AZ::SystemAllocator);
    };
}// namespace MyGem

AZ_DECLARE_MODULE_CLASS(Gem_MyGem, MyGem::MyGemModule)
