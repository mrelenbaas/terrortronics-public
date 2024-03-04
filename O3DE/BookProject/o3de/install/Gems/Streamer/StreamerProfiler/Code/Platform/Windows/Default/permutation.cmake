#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET StreamerProfiler.Clients)
   ly_create_alias( NAME StreamerProfiler.Clients NAMESPACE Gem TARGETS Gem::StreamerProfiler)
endif()
if(NOT TARGET StreamerProfiler.Servers)
   ly_create_alias( NAME StreamerProfiler.Servers NAMESPACE Gem TARGETS Gem::StreamerProfiler)
endif()
if(NOT TARGET StreamerProfiler.Unified)
   ly_create_alias( NAME StreamerProfiler.Unified NAMESPACE Gem TARGETS Gem::StreamerProfiler)
endif()
