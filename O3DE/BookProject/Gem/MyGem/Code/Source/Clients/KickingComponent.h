#pragma once
#include <AzCore/Component/Component.h>
#include <AzFramework/Physics/Common/PhysicsEvents.h>

namespace MyGem
{
  class KickingComponent
      : public AZ::Component
  {
  public:
    AZ_COMPONENT(KickingComponent,
        "{F6EC4198-FE4B-4FCD-8554-1A576E517F8A}");
    
    static void Reflect(AZ::ReflectContext* rc);

    KickingComponent();

    // AZ::Component interface implementation
    void Activate() override;
    void Deactivate() override {}
  
  private:
    AzPhysics::SceneEvents::
        OnSceneTriggersEvent::Handler m_trigger;
    void OnTriggerEvents(
        const AzPhysics::TriggerEventList& tel);
    
    float m_kickForce = 1000.f;

    void KickBall(AZ::EntityId ball);

    AZ::Vector3 GetBallPosition(AZ::EntityId ball);
    AZ::Vector3 GetSelfPosition();
    void AddImpulseToBall(AZ::Vector3 v, AZ::EntityId ball);
  };
}