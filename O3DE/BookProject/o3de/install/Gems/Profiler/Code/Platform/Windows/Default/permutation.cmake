#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET Profiler.Servers)
   ly_create_alias( NAME Profiler.Servers NAMESPACE Gem TARGETS Gem::Profiler)
endif()
if(NOT TARGET Profiler.Builders)
   ly_create_alias( NAME Profiler.Builders NAMESPACE Gem TARGETS Gem::Profiler)
endif()
if(NOT TARGET Profiler.Clients)
   ly_create_alias( NAME Profiler.Clients NAMESPACE Gem TARGETS Gem::ProfilerImGui)
endif()
if(NOT TARGET Profiler.Unified)
   ly_create_alias( NAME Profiler.Unified NAMESPACE Gem TARGETS Gem::ProfilerImGui)
endif()
if(NOT TARGET Profiler.Tools)
   ly_create_alias( NAME Profiler.Tools NAMESPACE Gem TARGETS Gem::ProfilerImGui)
endif()
