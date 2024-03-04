#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET Multiplayer.Clients)
   ly_create_alias( NAME Multiplayer.Clients NAMESPACE Gem TARGETS Gem::Multiplayer.Client Gem::Multiplayer.Debug.Client)
endif()
if(NOT TARGET Multiplayer.Servers)
   ly_create_alias( NAME Multiplayer.Servers NAMESPACE Gem TARGETS Gem::Multiplayer.Server)
endif()
if(NOT TARGET Multiplayer.Unified)
   ly_create_alias( NAME Multiplayer.Unified NAMESPACE Gem TARGETS Gem::Multiplayer Gem::Multiplayer.Debug)
endif()
if(NOT TARGET Multiplayer.Builders)
   ly_create_alias( NAME Multiplayer.Builders NAMESPACE Gem TARGETS Gem::Multiplayer.Editor)
endif()
if(NOT TARGET Multiplayer.Tools)
   ly_create_alias( NAME Multiplayer.Tools NAMESPACE Gem TARGETS Gem::Multiplayer.Debug Gem::Multiplayer.Builders)
endif()
