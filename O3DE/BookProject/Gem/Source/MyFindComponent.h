#pragma once
#include <AzCore/Component/Component.h>

namespace BookProject
{
  class MyFindComponent : public AZ::Component
  {
  public:
    AZ_COMPONENT(MyFindComponent, "{255F72BA-F3FA-483A-84BE-C51B5E943909}");

    static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
    {
      required.push_back(AZ_CRC_CE("TransformService"));
    }

    // AZ::Component overrides
    void Activate() override;
    void Deactivate() override {}

    // Provide runtime reflection, if any
    static void Reflect(AZ::ReflectContext* rc);
  };
}