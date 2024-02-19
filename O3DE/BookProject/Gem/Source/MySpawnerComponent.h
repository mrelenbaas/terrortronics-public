#pragma once
#include <AzCore/Component/Component.h>
#include <AzFramework/Spawnable/SpawnableEntitiesInterface.h>

namespace BookProject
{
  // An example of spawning prefab from C++.
  class MySpawnerComponent : public AZ::Component
  {
  public:
    AZ_COMPONENT(MySpawnerComponent, "{62F9D653-8A5D-47DF-B2CA-4F272AFBA688}");

    // AZ::Component overrides
    void Activate() override;
    void Deactivate() override {}

    // Provide runtime reflection, if any
    static void Reflect(AZ::ReflectContext* reflection);

  private:
    AZ::Data::Asset<AzFramework::Spawnable> m_spawnableAsset;
    AzFramework::EntitySpawnTicket m_ticket;
  };
}