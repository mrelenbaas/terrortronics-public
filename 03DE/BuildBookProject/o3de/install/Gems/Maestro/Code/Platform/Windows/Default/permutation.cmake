#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET Maestro.Clients)
   ly_create_alias( NAME Maestro.Clients NAMESPACE Gem TARGETS Gem::Maestro)
endif()
if(NOT TARGET Maestro.Servers)
   ly_create_alias( NAME Maestro.Servers NAMESPACE Gem TARGETS Gem::Maestro)
endif()
if(NOT TARGET Maestro.Unified)
   ly_create_alias( NAME Maestro.Unified NAMESPACE Gem TARGETS Gem::Maestro)
endif()
if(NOT TARGET Maestro.Tools)
   ly_create_alias( NAME Maestro.Tools NAMESPACE Gem TARGETS Gem::Maestro.Editor)
endif()
if(NOT TARGET Maestro.Builders)
   ly_create_alias( NAME Maestro.Builders NAMESPACE Gem TARGETS Gem::Maestro.Editor)
endif()
