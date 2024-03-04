#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET EMotionFX.Clients)
   ly_create_alias( NAME EMotionFX.Clients NAMESPACE Gem TARGETS EMotionFX)
endif()
if(NOT TARGET EMotionFX.Servers)
   ly_create_alias( NAME EMotionFX.Servers NAMESPACE Gem TARGETS EMotionFX)
endif()
if(NOT TARGET EMotionFX.Unified)
   ly_create_alias( NAME EMotionFX.Unified NAMESPACE Gem TARGETS EMotionFX)
endif()
if(NOT TARGET EMotionFX.Builders)
   ly_create_alias( NAME EMotionFX.Builders NAMESPACE Gem TARGETS EMotionFX.Editor)
endif()
if(NOT TARGET EMotionFX.Tools)
   ly_create_alias( NAME EMotionFX.Tools NAMESPACE Gem TARGETS EMotionFX.Editor)
endif()
