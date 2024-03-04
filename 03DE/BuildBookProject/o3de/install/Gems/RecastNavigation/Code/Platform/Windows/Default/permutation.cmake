#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET RecastNavigation.Clients)
   ly_create_alias( NAME RecastNavigation.Clients NAMESPACE Gem TARGETS Gem::RecastNavigation)
endif()
if(NOT TARGET RecastNavigation.Servers)
   ly_create_alias( NAME RecastNavigation.Servers NAMESPACE Gem TARGETS Gem::RecastNavigation)
endif()
if(NOT TARGET RecastNavigation.Unified)
   ly_create_alias( NAME RecastNavigation.Unified NAMESPACE Gem TARGETS Gem::RecastNavigation)
endif()
if(NOT TARGET RecastNavigation.Clients.API)
   ly_create_alias( NAME RecastNavigation.Clients.API NAMESPACE Gem TARGETS Gem::RecastNavigation.API)
endif()
if(NOT TARGET RecastNavigation.Servers.API)
   ly_create_alias( NAME RecastNavigation.Servers.API NAMESPACE Gem TARGETS Gem::RecastNavigation.API)
endif()
if(NOT TARGET RecastNavigation.Unified.API)
   ly_create_alias( NAME RecastNavigation.Unified.API NAMESPACE Gem TARGETS Gem::RecastNavigation.API)
endif()
if(NOT TARGET RecastNavigation.Tools)
   ly_create_alias( NAME RecastNavigation.Tools NAMESPACE Gem TARGETS Gem::RecastNavigation.Editor)
endif()
if(NOT TARGET RecastNavigation.Builders)
   ly_create_alias( NAME RecastNavigation.Builders NAMESPACE Gem TARGETS Gem::RecastNavigation.Editor)
endif()
if(NOT TARGET RecastNavigation.Tools.API)
   ly_create_alias( NAME RecastNavigation.Tools.API NAMESPACE Gem TARGETS Gem::RecastNavigation.Editor.API)
endif()
if(NOT TARGET RecastNavigation.Builders.API)
   ly_create_alias( NAME RecastNavigation.Builders.API NAMESPACE Gem TARGETS Gem::RecastNavigation.Editor.API)
endif()
