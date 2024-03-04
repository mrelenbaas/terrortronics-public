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

namespace MyGem
{
    // System Component TypeIds
    inline constexpr const char* MyGemSystemComponentTypeId = "{4B811CCA-1C9E-40BA-9520-546D5E77EA51}";
    inline constexpr const char* MyGemEditorSystemComponentTypeId = "{C1E92FCF-4C22-4779-AD48-9637840BCAA6}";

    // Module derived classes TypeIds
    inline constexpr const char* MyGemModuleInterfaceTypeId = "{5456F4F5-785A-4F76-996C-8C947F2358D4}";
    inline constexpr const char* MyGemModuleTypeId = "{5CA98C54-C580-4E9A-8CED-9A8019912941}";
    // The Editor Module by default is mutually exclusive with the Client Module
    // so they use the Same TypeId
    inline constexpr const char* MyGemEditorModuleTypeId = MyGemModuleTypeId;

    // Interface TypeIds
    inline constexpr const char* MyGemRequestsTypeId = "{E83402A6-1F3A-41F0-8C96-BA65268710A9}";
} // namespace MyGem
