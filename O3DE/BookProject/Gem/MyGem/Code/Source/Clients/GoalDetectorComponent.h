#pragma once
#include <AzCore/Component/Component.h>
#include <AzFramework/Physics/Common/PhysicsEvents.h>

namespace MyGem
{
  class GoalDetectorComponent
      : public AZ::Component
  {
  public:
    AZ_COMPONENT(GoalDetectorComponent,
        "{77269E49-D4D8-4BFC-853F-7BAC0E5B92A1}");
    
    static void Reflect(AZ::ReflectContext* rc);

    GoalDetectorComponent();

    // AZ::Component interface implementation.
    void Activate() override;
    void Deactivate() override {}
  
  private:
    AzPhysics::SceneEvents::
        OnSceneTriggersEvent::Handler m_trigger;
    void OnTriggerEvents(
        const AzPhysics::TriggerEventList& tel);
    
    AZ::EntityId m_ball;
    AZ::EntityId m_reset;
    int m_team = 0;

    AZ::Vector3 GetRespawnPoint() const;
    void RespawnBall(const AZ::Vector3& v);
    void UpdateUi();
  };
} // namespace MyGem