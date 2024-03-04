#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET Compression.Clients)
   ly_create_alias( NAME Compression.Clients NAMESPACE Gem TARGETS Gem::Compression)
endif()
if(NOT TARGET Compression.Servers)
   ly_create_alias( NAME Compression.Servers NAMESPACE Gem TARGETS Gem::Compression)
endif()
if(NOT TARGET Compression.Unified)
   ly_create_alias( NAME Compression.Unified NAMESPACE Gem TARGETS Gem::Compression)
endif()
if(NOT TARGET Compression.Clients.API)
   ly_create_alias( NAME Compression.Clients.API NAMESPACE Gem TARGETS Gem::Compression.API)
endif()
if(NOT TARGET Compression.Servers.API)
   ly_create_alias( NAME Compression.Servers.API NAMESPACE Gem TARGETS Gem::Compression.API)
endif()
if(NOT TARGET Compression.Unified.API)
   ly_create_alias( NAME Compression.Unified.API NAMESPACE Gem TARGETS Gem::Compression.API)
endif()
if(NOT TARGET Compression.Tools)
   ly_create_alias( NAME Compression.Tools NAMESPACE Gem TARGETS Gem::Compression.Editor)
endif()
if(NOT TARGET Compression.Builders)
   ly_create_alias( NAME Compression.Builders NAMESPACE Gem TARGETS Gem::Compression.Editor)
endif()
if(NOT TARGET Compression.Tools.API)
   ly_create_alias( NAME Compression.Tools.API NAMESPACE Gem TARGETS Gem::Compression.Editor.API)
endif()
if(NOT TARGET Compression.Builders.API)
   ly_create_alias( NAME Compression.Builders.API NAMESPACE Gem TARGETS Gem::Compression.Editor.API)
endif()
