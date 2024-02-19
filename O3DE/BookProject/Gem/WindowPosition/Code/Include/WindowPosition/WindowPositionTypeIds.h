
#pragma once

namespace WindowPosition
{
    // System Component TypeIds
    inline constexpr const char* WindowPositionSystemComponentTypeId = "{652FAD46-C825-48D2-8534-4867106A3011}";
    inline constexpr const char* WindowPositionEditorSystemComponentTypeId = "{A34D251F-09DB-42B7-B98F-C795956A3998}";

    // Module derived classes TypeIds
    inline constexpr const char* WindowPositionModuleInterfaceTypeId = "{E21D55A4-00F5-42C6-9416-19A5CA87E09C}";
    inline constexpr const char* WindowPositionModuleTypeId = "{10493DF3-321C-42AE-920D-4124F1AE1C4F}";
    // The Editor Module by default is mutually exclusive with the Client Module
    // so they use the Same TypeId
    inline constexpr const char* WindowPositionEditorModuleTypeId = WindowPositionModuleTypeId;

    // Interface TypeIds
    inline constexpr const char* WindowPositionRequestsTypeId = "{3886BD3F-5A87-478E-B7FC-EC05BD2472B3}";
} // namespace WindowPosition
