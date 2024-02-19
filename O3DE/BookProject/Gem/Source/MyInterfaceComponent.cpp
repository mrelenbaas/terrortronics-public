#include "MyInterfaceComponent.h"
#include <AzCore/Serialization/EditContext.h>
#include <BookProject/MyInterface.h>

using namespace BookProject;

void MyInterfaceComponent::Activate()
{
  if (MyInterface* myInterface = AZ::Interface<MyInterface>::Get())
  {
    AZ_Printf("Example", "%d", myInterface->GetMyInteger());
  }
}

void MyInterfaceComponent::Reflect(AZ::ReflectContext* rc)
{
  auto sc = azrtti_cast<AZ::SerializeContext*>(rc);
  if (!sc) return;

  sc->Class<MyInterfaceComponent, Component>()->Version(1);

  AZ::EditContext* ec = sc->GetEditContext();
  if (!ec) return;

  using namespace AZ::Edit::Attributes;
  // reflection of this component for the O3DE Editor
  ec->Class<MyInterfaceComponent>("Using Interface Example", "[Communicates using AZ::Interface]")
    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
      ->Attribute(AppearsInAddComponentMenu, AZ_CRC("Game"))
      ->Attribute(Category, "MyProject");
}