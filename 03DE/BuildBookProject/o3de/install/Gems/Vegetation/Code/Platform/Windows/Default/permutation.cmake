#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET Vegetation.Servers)
   ly_create_alias( NAME Vegetation.Servers NAMESPACE Gem TARGETS Gem::Vegetation)
endif()
if(NOT TARGET Vegetation.Clients)
   ly_create_alias( NAME Vegetation.Clients NAMESPACE Gem TARGETS Gem::Vegetation)
endif()
if(NOT TARGET Vegetation.Unified)
   ly_create_alias( NAME Vegetation.Unified NAMESPACE Gem TARGETS Gem::Vegetation)
endif()
if(NOT TARGET Vegetation.Builders)
   ly_create_alias( NAME Vegetation.Builders NAMESPACE Gem TARGETS Gem::Vegetation.Editor)
endif()
if(NOT TARGET Vegetation.Tools)
   ly_create_alias( NAME Vegetation.Tools NAMESPACE Gem TARGETS Gem::Vegetation.Editor)
endif()
