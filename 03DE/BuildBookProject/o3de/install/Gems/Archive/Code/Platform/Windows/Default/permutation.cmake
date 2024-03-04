#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET Archive.Clients)
   ly_create_alias( NAME Archive.Clients NAMESPACE Gem TARGETS Gem::Archive)
endif()
if(NOT TARGET Archive.Servers)
   ly_create_alias( NAME Archive.Servers NAMESPACE Gem TARGETS Gem::Archive)
endif()
if(NOT TARGET Archive.Unified)
   ly_create_alias( NAME Archive.Unified NAMESPACE Gem TARGETS Gem::Archive)
endif()
if(NOT TARGET Archive.Clients.API)
   ly_create_alias( NAME Archive.Clients.API NAMESPACE Gem TARGETS Gem::Archive.API)
endif()
if(NOT TARGET Archive.Servers.API)
   ly_create_alias( NAME Archive.Servers.API NAMESPACE Gem TARGETS Gem::Archive.API)
endif()
if(NOT TARGET Archive.Unified.API)
   ly_create_alias( NAME Archive.Unified.API NAMESPACE Gem TARGETS Gem::Archive.API)
endif()
if(NOT TARGET Archive.Tools)
   ly_create_alias( NAME Archive.Tools NAMESPACE Gem TARGETS Gem::Archive.Editor)
endif()
if(NOT TARGET Archive.Builders)
   ly_create_alias( NAME Archive.Builders NAMESPACE Gem TARGETS Gem::Archive.Editor)
endif()
if(NOT TARGET Archive.Tools.API)
   ly_create_alias( NAME Archive.Tools.API NAMESPACE Gem TARGETS Gem::Archive.Editor.API)
endif()
if(NOT TARGET Archive.Builders.API)
   ly_create_alias( NAME Archive.Builders.API NAMESPACE Gem TARGETS Gem::Archive.Editor.API)
endif()
