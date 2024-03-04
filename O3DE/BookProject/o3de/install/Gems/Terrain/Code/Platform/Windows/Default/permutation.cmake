#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET Terrain.Servers)
   ly_create_alias( NAME Terrain.Servers NAMESPACE Gem TARGETS Gem::Terrain Gem::SurfaceData.Servers Gem::GradientSignal.Servers)
endif()
if(NOT TARGET Terrain.Clients)
   ly_create_alias( NAME Terrain.Clients NAMESPACE Gem TARGETS Gem::Terrain Gem::SurfaceData.Clients Gem::GradientSignal.Clients)
endif()
if(NOT TARGET Terrain.Unified)
   ly_create_alias( NAME Terrain.Unified NAMESPACE Gem TARGETS Gem::Terrain Gem::SurfaceData.Unified Gem::GradientSignal.Unified)
endif()
if(NOT TARGET Terrain.Builders)
   ly_create_alias( NAME Terrain.Builders NAMESPACE Gem TARGETS Gem::Terrain.Editor Gem::SurfaceData.Builders Gem::GradientSignal.Builders)
endif()
if(NOT TARGET Terrain.Tools)
   ly_create_alias( NAME Terrain.Tools NAMESPACE Gem TARGETS Gem::Terrain.Editor Gem::SurfaceData.Tools Gem::GradientSignal.Tools)
endif()
