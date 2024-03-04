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

#pragma once
#include <AzCore/Component/Component.h>
#include <AzCore/Interface/Interface.h>
#include <BookProject/MyInterface.h>

namespace BookProject
{
  // An example of a level component with AZ::Interface
  class MyLevelComponent
      : public AZ::Component
      , public AZ::Interface<MyInterface>::Registrar
  {
    public:
      AZ_COMPONENT(MyLevelComponent, "{D0E746EF-2861-4DC4-A35B-4EB0558FB847}");

      // AZ::Component overrides
      void Activate() override {}
      void Deactivate() override {}

      // Provide runtime reflection, if any
      static void Reflect(AZ::ReflectContext* rc);

      // MyInterface
      int GetMyInteger() override { return 42; }
  };
}