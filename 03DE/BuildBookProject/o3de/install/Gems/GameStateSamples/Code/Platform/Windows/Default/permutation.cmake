#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET GameStateSamples.Clients)
   ly_create_alias( NAME GameStateSamples.Clients NAMESPACE Gem TARGETS Gem::GameStateSamples)
endif()
if(NOT TARGET GameStateSamples.Servers)
   ly_create_alias( NAME GameStateSamples.Servers NAMESPACE Gem TARGETS Gem::GameStateSamples)
endif()
if(NOT TARGET GameStateSamples.Unified)
   ly_create_alias( NAME GameStateSamples.Unified NAMESPACE Gem TARGETS Gem::GameStateSamples)
endif()
if(NOT TARGET GameStateSamples.Builders)
   ly_create_alias( NAME GameStateSamples.Builders NAMESPACE Gem TARGETS Gem::UiBasics.Builders Gem::LyShineExamples.Builders)
endif()
