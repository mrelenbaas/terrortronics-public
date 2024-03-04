#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET SurfaceData.Servers)
   ly_create_alias( NAME SurfaceData.Servers NAMESPACE Gem TARGETS Gem::SurfaceData)
endif()
if(NOT TARGET SurfaceData.Clients)
   ly_create_alias( NAME SurfaceData.Clients NAMESPACE Gem TARGETS Gem::SurfaceData)
endif()
if(NOT TARGET SurfaceData.Unified)
   ly_create_alias( NAME SurfaceData.Unified NAMESPACE Gem TARGETS Gem::SurfaceData)
endif()
if(NOT TARGET SurfaceData.Builders)
   ly_create_alias( NAME SurfaceData.Builders NAMESPACE Gem TARGETS Gem::SurfaceData.Editor)
endif()
if(NOT TARGET SurfaceData.Tools)
   ly_create_alias( NAME SurfaceData.Tools NAMESPACE Gem TARGETS Gem::SurfaceData.Editor)
endif()
