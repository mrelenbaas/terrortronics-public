#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET RemoteTools.Clients)
   ly_create_alias( NAME RemoteTools.Clients NAMESPACE Gem TARGETS Gem::RemoteTools)
endif()
if(NOT TARGET RemoteTools.Servers)
   ly_create_alias( NAME RemoteTools.Servers NAMESPACE Gem TARGETS Gem::RemoteTools)
endif()
if(NOT TARGET RemoteTools.Unified)
   ly_create_alias( NAME RemoteTools.Unified NAMESPACE Gem TARGETS Gem::RemoteTools)
endif()
if(NOT TARGET RemoteTools.Tools)
   ly_create_alias( NAME RemoteTools.Tools NAMESPACE Gem TARGETS Gem::RemoteTools)
endif()
if(NOT TARGET RemoteTools.LuaTools)
   ly_create_alias( NAME RemoteTools.LuaTools NAMESPACE Gem TARGETS Gem::RemoteTools)
endif()
