#pragma once
#include <AzCore/Component/Component.h>
#include "ChickenBus.h"

namespace MyGem
{
  class ChickenAnimationComponent
      : public AZ::Component
      , public ChickenNotificationBus::Handler
  {
  public:
    AZ_COMPONENT(ChickenAnimationComponent,
        "{1BDB8DAA-C9A8-474C-90F7-B9A7709783CC}");
    
    static void Reflect(AZ::ReflectContext* rc);

    // AZ::Component interface implementation
    void Activate() override;
    void Deactivate() override;

    // ChickenNotificationBus interface
    void OnChickenSpeedChanged(float s) override;
  
  private:
    AZ::EntityId m_actor;
  };
} // namespace MyGem