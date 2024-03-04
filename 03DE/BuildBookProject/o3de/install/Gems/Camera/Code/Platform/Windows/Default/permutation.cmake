#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET Camera.Clients)
   ly_create_alias( NAME Camera.Clients NAMESPACE Gem TARGETS Gem::Camera)
endif()
if(NOT TARGET Camera.Servers)
   ly_create_alias( NAME Camera.Servers NAMESPACE Gem TARGETS Gem::Camera)
endif()
if(NOT TARGET Camera.Unified)
   ly_create_alias( NAME Camera.Unified NAMESPACE Gem TARGETS Gem::Camera)
endif()
if(NOT TARGET Camera.Tools)
   ly_create_alias( NAME Camera.Tools NAMESPACE Gem TARGETS Gem::Camera.Editor)
endif()
if(NOT TARGET Camera.Builders)
   ly_create_alias( NAME Camera.Builders NAMESPACE Gem TARGETS Gem::Camera.Editor)
endif()
