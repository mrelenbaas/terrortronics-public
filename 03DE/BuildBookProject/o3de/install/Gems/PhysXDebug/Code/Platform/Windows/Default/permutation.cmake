#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET PhysXDebug.Clients)
   ly_create_alias( NAME PhysXDebug.Clients NAMESPACE Gem TARGETS Gem::PhysXDebug)
endif()
if(NOT TARGET PhysXDebug.Servers)
   ly_create_alias( NAME PhysXDebug.Servers NAMESPACE Gem TARGETS Gem::PhysXDebug)
endif()
if(NOT TARGET PhysXDebug.Unified)
   ly_create_alias( NAME PhysXDebug.Unified NAMESPACE Gem TARGETS Gem::PhysXDebug)
endif()
if(NOT TARGET PhysXDebug.Builders)
   ly_create_alias( NAME PhysXDebug.Builders NAMESPACE Gem TARGETS Gem::PhysXDebug.Editor)
endif()
if(NOT TARGET PhysXDebug.Tools)
   ly_create_alias( NAME PhysXDebug.Tools NAMESPACE Gem TARGETS Gem::PhysXDebug.Editor)
endif()
