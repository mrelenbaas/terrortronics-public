#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET FastNoise.Clients)
   ly_create_alias( NAME FastNoise.Clients NAMESPACE Gem TARGETS FastNoise)
endif()
if(NOT TARGET FastNoise.Servers)
   ly_create_alias( NAME FastNoise.Servers NAMESPACE Gem TARGETS FastNoise)
endif()
if(NOT TARGET FastNoise.Unified)
   ly_create_alias( NAME FastNoise.Unified NAMESPACE Gem TARGETS FastNoise)
endif()
if(NOT TARGET FastNoise.Builders)
   ly_create_alias( NAME FastNoise.Builders NAMESPACE Gem TARGETS FastNoise.Editor)
endif()
if(NOT TARGET FastNoise.Tools)
   ly_create_alias( NAME FastNoise.Tools NAMESPACE Gem TARGETS FastNoise.Editor)
endif()
