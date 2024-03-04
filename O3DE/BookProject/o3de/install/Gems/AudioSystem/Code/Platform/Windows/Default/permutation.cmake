#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET AudioSystem.Clients)
   ly_create_alias( NAME AudioSystem.Clients NAMESPACE Gem TARGETS Gem::AudioSystem)
endif()
if(NOT TARGET AudioSystem.Clients.API)
   ly_create_alias( NAME AudioSystem.Clients.API NAMESPACE Gem TARGETS Gem::AudioSystem.API)
endif()
if(NOT TARGET AudioSystem.Unified)
   ly_create_alias( NAME AudioSystem.Unified NAMESPACE Gem TARGETS Gem::AudioSystem)
endif()
if(NOT TARGET AudioSystem.Unified.API)
   ly_create_alias( NAME AudioSystem.Unified.API NAMESPACE Gem TARGETS Gem::AudioSystem.API)
endif()
if(NOT TARGET AudioSystem.Tools)
   ly_create_alias( NAME AudioSystem.Tools NAMESPACE Gem TARGETS Gem::AudioSystem.Editor)
endif()
if(NOT TARGET AudioSystem.Builders)
   ly_create_alias( NAME AudioSystem.Builders NAMESPACE Gem TARGETS Gem::AudioSystem.Editor)
endif()
