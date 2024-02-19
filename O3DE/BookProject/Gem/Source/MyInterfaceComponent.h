#pragma once
#include <AzCore/Component/Component.h>

namespace BookProject
{
  // An example of using AZ::Interface
  class MyInterfaceComponent : public AZ::Component
  {
  public:
    AZ_COMPONENT(MyInterfaceComponent, "{DF9CCC6B-28C7-4052-AD6F-6595F6BC8395}");

    // AZ::Component overrides
    void Activate() override;
    void Deactivate() override {}

    // Provide runtime reflection, if any
    static void Reflect(AZ::ReflectContext* rc);
  };
}