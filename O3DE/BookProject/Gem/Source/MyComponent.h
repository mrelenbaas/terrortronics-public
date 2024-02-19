#pragma once
#include <AzCore/Component/Component.h>
namespace BookProject
{
 // An example of the simplest O3DE component
 class MyComponent : public AZ::Component
 {
   public:
     AZ_COMPONENT(MyComponent, "{40BDC18F-E52F-45A8-AB9B-9D6C31E5F887}");
     // AZ::Component overrides
     void Activate() override {}
     void Deactivate() override {}
     // Provide runtime reflection, if any
     static void Reflect(AZ::ReflectContext* reflection);
 };
}
