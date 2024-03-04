#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET PhysX.Clients)
   ly_create_alias( NAME PhysX.Clients NAMESPACE Gem TARGETS Gem::PhysX)
endif()
if(NOT TARGET PhysX.Servers)
   ly_create_alias( NAME PhysX.Servers NAMESPACE Gem TARGETS Gem::PhysX)
endif()
if(NOT TARGET PhysX.Unified)
   ly_create_alias( NAME PhysX.Unified NAMESPACE Gem TARGETS Gem::PhysX)
endif()
if(NOT TARGET PhysX.Builders)
   ly_create_alias( NAME PhysX.Builders NAMESPACE Gem TARGETS Gem::PhysX.Editor)
endif()
if(NOT TARGET PhysX.Tools)
   ly_create_alias( NAME PhysX.Tools NAMESPACE Gem TARGETS Gem::PhysX.Editor)
endif()
