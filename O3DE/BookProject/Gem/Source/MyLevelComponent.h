#pragma once
#include <AzCore/Component/Component.h>
#include <AzCore/Interface/Interface.h>
#include <BookProject/MyInterface.h>

namespace BookProject
{
  // An example of a level component with AZ::Interface
  class MyLevelComponent
      : public AZ::Component
      , public AZ::Interface<MyInterface>::Registrar
  {
    public:
      AZ_COMPONENT(MyLevelComponent, "{D0E746EF-2861-4DC4-A35B-4EB0558FB847}");

      // AZ::Component overrides
      void Activate() override {}
      void Deactivate() override {}

      // Provide runtime reflection, if any
      static void Reflect(AZ::ReflectContext* rc);

      // MyInterface
      int GetMyInteger() override { return 42; }
  };
}