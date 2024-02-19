#pragma once
#include <AzCore/Component/Component.h>

namespace MyGem
{
  class ChickenNotifications
      : public AZ::ComponentBus
  {
  public:
      virtual void OnChickenSpeedChanged(float speed) = 0;
  };

  using ChickenNotificationBus = AZ::EBus<ChickenNotifications>;
}