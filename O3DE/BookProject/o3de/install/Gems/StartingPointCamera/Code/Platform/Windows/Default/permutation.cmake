#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET StartingPointCamera.Servers)
   ly_create_alias( NAME StartingPointCamera.Servers NAMESPACE Gem TARGETS Gem::StartingPointCamera)
endif()
if(NOT TARGET StartingPointCamera.Unified)
   ly_create_alias( NAME StartingPointCamera.Unified NAMESPACE Gem TARGETS Gem::StartingPointCamera)
endif()
if(NOT TARGET StartingPointCamera.Clients)
   ly_create_alias( NAME StartingPointCamera.Clients NAMESPACE Gem TARGETS Gem::StartingPointCamera)
endif()
if(NOT TARGET StartingPointCamera.Builders)
   ly_create_alias( NAME StartingPointCamera.Builders NAMESPACE Gem TARGETS Gem::StartingPointCamera)
endif()
if(NOT TARGET StartingPointCamera.Tools)
   ly_create_alias( NAME StartingPointCamera.Tools NAMESPACE Gem TARGETS Gem::StartingPointCamera)
endif()
