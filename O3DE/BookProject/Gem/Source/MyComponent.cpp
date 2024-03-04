// Copyright 2024 Bradley Elenbaas
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "MyComponent.h"
#include <AzCore/Serialization/EditContext.h>

using namespace BookProject;

void MyComponent::Reflect(AZ::ReflectContext* reflection)
{
	 auto sc = azrtti_cast<AZ::SerializeContext*>(reflection);
	 if (!sc) return;
	 sc->Class<MyComponent, Component>()->Version(1);
	 AZ::EditContext* ec = sc->GetEditContext();
	 if (!ec) return;
	
	 using namespace AZ::Edit::Attributes;
	 // reflection of this component for O3DE Editor
	 ec->Class<MyComponent>("My Component", "[my description]")
		 ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
		 ->Attribute(AppearsInAddComponentMenu, AZ_CRC("Game"))
		 ->Attribute(Category, "My Project");
}
