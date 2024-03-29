#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

# Generated by O3DE

ly_add_target(
    NAME BookProject.Private.Object IMPORTED STATIC
    NAMESPACE Gem
    COMPILE_DEFINITIONS
        INTERFACE

    INCLUDE_DIRECTORIES
        INTERFACE
            Include
    BUILD_DEPENDENCIES
        INTERFACE
            AZ::AzCore
            AZ::AzFramework
            Gem::StartingPointInput.Static
            Gem::Atom_AtomBridge.Static
    RUNTIME_DEPENDENCIES
        AZ::AzCore
        AZ::AzFramework
        Gem::StartingPointInput.Static
        Gem::Atom_AtomBridge.Static
    TARGET_PROPERTIES

)



set(configs profile)
foreach(config ${configs})
    include("Platform/Windows/Default/BookProject.Private.Object_${config}.cmake" OPTIONAL)
endforeach()

# Generated by O3DE

ly_add_target(
    NAME BookProject IMPORTED GEM_MODULE
    NAMESPACE Gem
    COMPILE_DEFINITIONS
        INTERFACE

    INCLUDE_DIRECTORIES
        INTERFACE
            Include
    BUILD_DEPENDENCIES
        INTERFACE

    RUNTIME_DEPENDENCIES
        Gem::BookProject.Private.Object
        AZ::AzCore
        AZ::AzFramework
        Gem::StartingPointInput.Static
    TARGET_PROPERTIES

)



set(configs profile)
foreach(config ${configs})
    include("Platform/Windows/Default/BookProject_${config}.cmake" OPTIONAL)
endforeach()

if(NOT TARGET BookProject.Builders)
   ly_create_alias( NAME BookProject.Builders NAMESPACE Gem TARGETS Gem::BookProject)
endif()
if(NOT TARGET BookProject.Tools)
   ly_create_alias( NAME BookProject.Tools NAMESPACE Gem TARGETS Gem::BookProject)
endif()
if(NOT TARGET BookProject.Clients)
   ly_create_alias( NAME BookProject.Clients NAMESPACE Gem TARGETS Gem::BookProject)
endif()
if(NOT TARGET BookProject.Servers)
   ly_create_alias( NAME BookProject.Servers NAMESPACE Gem TARGETS Gem::BookProject)
endif()
if(NOT TARGET BookProject.Unified)
   ly_create_alias( NAME BookProject.Unified NAMESPACE Gem TARGETS Gem::BookProject)
endif()
o3de_add_variant_dependencies_for_gem_dependencies(GEM_NAME BookProject VARIANTS Builders Tools Clients Servers Unified)
