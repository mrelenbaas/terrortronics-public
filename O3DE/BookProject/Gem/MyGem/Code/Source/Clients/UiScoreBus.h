#pragma once
#include <AzCore/Component/ComponentBus.h>
#include <AzCore/RTTI/BehaviorContext.h>

namespace MyGem
{
  class UiScoreNotifications
      : public AZ::ComponentBus
  {
  public:
    virtual void OnTeamScored(int team) = 0;
  };

  using UiScoreNotificationBus = AZ::EBus<UiScoreNotifications>;

  // NEW
  class ScoreNotificationHandler
      : public UiScoreNotificationBus::Handler
      , public AZ::BehaviorEBusHandler
  {
  public:
    AZ_EBUS_BEHAVIOR_BINDER(ScoreNotificationHandler,
        "{54172CAD-38FA-452B-9EE7-3DBB71181442}",
        AZ::SystemAllocator, OnTeamScored);
    
    void OnTeamScored(int team) override
    {
      Call(FN_OnTeamScored, team);
    }
  };
}