#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET StartingPointInput.Servers)
   ly_create_alias( NAME StartingPointInput.Servers NAMESPACE Gem TARGETS Gem::StartingPointInput)
endif()
if(NOT TARGET StartingPointInput.Unified)
   ly_create_alias( NAME StartingPointInput.Unified NAMESPACE Gem TARGETS Gem::StartingPointInput)
endif()
if(NOT TARGET StartingPointInput.Clients)
   ly_create_alias( NAME StartingPointInput.Clients NAMESPACE Gem TARGETS Gem::StartingPointInput)
endif()
if(NOT TARGET StartingPointInput.Builders)
   ly_create_alias( NAME StartingPointInput.Builders NAMESPACE Gem TARGETS Gem::StartingPointInput.Editor)
endif()
if(NOT TARGET StartingPointInput.Tools)
   ly_create_alias( NAME StartingPointInput.Tools NAMESPACE Gem TARGETS Gem::StartingPointInput.Editor)
endif()
