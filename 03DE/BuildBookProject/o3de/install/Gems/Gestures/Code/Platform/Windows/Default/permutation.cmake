#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET Gestures.Clients)
   ly_create_alias( NAME Gestures.Clients NAMESPACE Gem TARGETS Gestures)
endif()
if(NOT TARGET Gestures.Servers)
   ly_create_alias( NAME Gestures.Servers NAMESPACE Gem TARGETS Gestures)
endif()
if(NOT TARGET Gestures.Unified)
   ly_create_alias( NAME Gestures.Unified NAMESPACE Gem TARGETS Gestures)
endif()
if(NOT TARGET Gestures.Builders)
   ly_create_alias( NAME Gestures.Builders NAMESPACE Gem TARGETS Gestures)
endif()
if(NOT TARGET Gestures.Tools)
   ly_create_alias( NAME Gestures.Tools NAMESPACE Gem TARGETS Gestures)
endif()
