#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET GradientSignal.Clients)
   ly_create_alias( NAME GradientSignal.Clients NAMESPACE Gem TARGETS Gem::GradientSignal)
endif()
if(NOT TARGET GradientSignal.Servers)
   ly_create_alias( NAME GradientSignal.Servers NAMESPACE Gem TARGETS Gem::GradientSignal)
endif()
if(NOT TARGET GradientSignal.Unified)
   ly_create_alias( NAME GradientSignal.Unified NAMESPACE Gem TARGETS Gem::GradientSignal)
endif()
if(NOT TARGET GradientSignal.Builders)
   ly_create_alias( NAME GradientSignal.Builders NAMESPACE Gem TARGETS Gem::GradientSignal.Editor)
endif()
if(NOT TARGET GradientSignal.Tools)
   ly_create_alias( NAME GradientSignal.Tools NAMESPACE Gem TARGETS Gem::GradientSignal.Editor)
endif()
