#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET LyShine.Clients)
   ly_create_alias( NAME LyShine.Clients NAMESPACE Gem TARGETS Gem::LyShine)
endif()
if(NOT TARGET LyShine.Servers)
   ly_create_alias( NAME LyShine.Servers NAMESPACE Gem TARGETS Gem::LyShine)
endif()
if(NOT TARGET LyShine.Unified)
   ly_create_alias( NAME LyShine.Unified NAMESPACE Gem TARGETS Gem::LyShine)
endif()
if(NOT TARGET LyShine.Clients.API)
   ly_create_alias( NAME LyShine.Clients.API NAMESPACE Gem TARGETS Gem::LyShine.Clients)
endif()
if(NOT TARGET LyShine.Servers.API)
   ly_create_alias( NAME LyShine.Servers.API NAMESPACE Gem TARGETS Gem::LyShine.Servers)
endif()
if(NOT TARGET LyShine.Unified.API)
   ly_create_alias( NAME LyShine.Unified.API NAMESPACE Gem TARGETS Gem::LyShine.Unified)
endif()
