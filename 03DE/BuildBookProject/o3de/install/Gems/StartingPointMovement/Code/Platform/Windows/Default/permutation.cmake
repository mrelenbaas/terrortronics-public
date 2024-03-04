#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET StartingPointMovement.Servers)
   ly_create_alias( NAME StartingPointMovement.Servers NAMESPACE Gem TARGETS Gem::StartingPointMovement)
endif()
if(NOT TARGET StartingPointMovement.Clients)
   ly_create_alias( NAME StartingPointMovement.Clients NAMESPACE Gem TARGETS Gem::StartingPointMovement)
endif()
if(NOT TARGET StartingPointMovement.Unified)
   ly_create_alias( NAME StartingPointMovement.Unified NAMESPACE Gem TARGETS Gem::StartingPointMovement)
endif()
if(NOT TARGET StartingPointMovement.Builders)
   ly_create_alias( NAME StartingPointMovement.Builders NAMESPACE Gem TARGETS Gem::StartingPointMovement)
endif()
if(NOT TARGET StartingPointMovement.Tools)
   ly_create_alias( NAME StartingPointMovement.Tools NAMESPACE Gem TARGETS Gem::StartingPointMovement)
endif()
