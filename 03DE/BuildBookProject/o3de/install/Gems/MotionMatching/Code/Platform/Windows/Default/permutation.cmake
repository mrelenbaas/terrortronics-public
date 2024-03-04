#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET MotionMatching.Clients)
   ly_create_alias( NAME MotionMatching.Clients NAMESPACE Gem TARGETS Gem::MotionMatching)
endif()
if(NOT TARGET MotionMatching.Servers)
   ly_create_alias( NAME MotionMatching.Servers NAMESPACE Gem TARGETS Gem::MotionMatching)
endif()
if(NOT TARGET MotionMatching.Unified)
   ly_create_alias( NAME MotionMatching.Unified NAMESPACE Gem TARGETS Gem::MotionMatching)
endif()
if(NOT TARGET MotionMatching.Tools)
   ly_create_alias( NAME MotionMatching.Tools NAMESPACE Gem TARGETS Gem::MotionMatching.Editor)
endif()
if(NOT TARGET MotionMatching.Builders)
   ly_create_alias( NAME MotionMatching.Builders NAMESPACE Gem TARGETS Gem::MotionMatching.Editor)
endif()
