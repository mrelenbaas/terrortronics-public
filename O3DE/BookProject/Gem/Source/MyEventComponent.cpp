#include "MyEventComponent.h"
#include <AzCore/Component/Entity.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzFramework/Components/TransformComponent.h>

using namespace BookProject;

//char stateBuffer[5];
//std::ofstream myfile;
//std::string someString;
char charArray[4];
std::string str;

MyEventComponent::MyEventComponent()
    : m_movementHandler(
        [this](
            const AZ::Transform& /*local*/,
            const AZ::Transform& world)
        {
          OnWorldTransformChanged(world);
        })
{
}

void MyEventComponent::OnWorldTransformChanged(const AZ::Transform&/*const AZ::Transform& world*/)
{
  //std::ifstream file("C:\\Users\\mrele\\Documents\\terrortronics-public\\CPP\\state.txt");
  //std::getline(file, str);
  //strcpy_s(charArray, str.c_str());

  //AZ_Printf("MyEvent", "now at %d,%d,%d,%d", charArray[0], charArray[1], charArray[2], charArray[3]);

  //AZ_Printf("MyEvent", "now at %f %f %f",
  //    world.GetTranslation().GetX(),
  //    world.GetTranslation().GetY(),
  //    world.GetTranslation().GetZ());
}

void MyEventComponent::Activate()
{
  AZ::Entity* e = GetEntity();

  using namespace AzFramework;
  TransformComponent* tc = e->FindComponent<TransformComponent>();
  // Track the movement of the entity
  tc->BindTransformChangedEventHandler(m_movementHandler);
}

void MyEventComponent::Reflect(AZ::ReflectContext* rc)
{
  auto sc = azrtti_cast<AZ::SerializeContext*>(rc);
  if (!sc) return;

  sc->Class<MyEventComponent, Component>()->Version(1);

  AZ::EditContext* ec = sc->GetEditContext();
  if (!ec) return;

  using namespace AZ::Edit::Attributes;
  ec->Class<MyEventComponent>("My Event Component Example", "[Communicates using AZ::Event]")
    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
      ->Attribute(AppearsInAddComponentMenu, AZ_CRC("Game"))
      ->Attribute(Category, "My Project");
}