#pragma once
#include <AzCore/Component/Component.h>
#include "UiScoreBus.h"

namespace MyGem
{
  class UiScoreComponent
      : public AZ::Component
      , public UiScoreNotificationBus::Handler
  {
  public:
    AZ_COMPONENT(UiScoreComponent,
        "{3B0F416B-FC49-42A1-9809-2866C035BA81}");
    
    static void Reflect(AZ::ReflectContext* rc);

    // AZ::Component interface implementation
    void Activate() override;
    void Deactivate() override;

    // UiScoreNotificanBus interface
    void OnTeamScored(int team) override;
  
  private:
    int m_teams[2] = { 0, 0 };
  };
} // namespace MyGem