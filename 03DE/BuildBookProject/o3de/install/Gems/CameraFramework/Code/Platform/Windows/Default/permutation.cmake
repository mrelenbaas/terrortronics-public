#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET CameraFramework.Clients)
   ly_create_alias( NAME CameraFramework.Clients NAMESPACE Gem TARGETS Gem::CameraFramework)
endif()
if(NOT TARGET CameraFramework.Servers)
   ly_create_alias( NAME CameraFramework.Servers NAMESPACE Gem TARGETS Gem::CameraFramework)
endif()
if(NOT TARGET CameraFramework.Unified)
   ly_create_alias( NAME CameraFramework.Unified NAMESPACE Gem TARGETS Gem::CameraFramework)
endif()
if(NOT TARGET CameraFramework.Tools)
   ly_create_alias( NAME CameraFramework.Tools NAMESPACE Gem TARGETS Gem::CameraFramework)
endif()
if(NOT TARGET CameraFramework.Builders)
   ly_create_alias( NAME CameraFramework.Builders NAMESPACE Gem TARGETS Gem::CameraFramework)
endif()
