#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET WhiteBox.Clients)
   ly_create_alias( NAME WhiteBox.Clients NAMESPACE Gem TARGETS Gem::WhiteBox)
endif()
if(NOT TARGET WhiteBox.Servers)
   ly_create_alias( NAME WhiteBox.Servers NAMESPACE Gem TARGETS Gem::WhiteBox)
endif()
if(NOT TARGET WhiteBox.Unified)
   ly_create_alias( NAME WhiteBox.Unified NAMESPACE Gem TARGETS Gem::WhiteBox)
endif()
if(NOT TARGET WhiteBox.Tools)
   ly_create_alias( NAME WhiteBox.Tools NAMESPACE Gem TARGETS Gem::WhiteBox.Editor)
endif()
if(NOT TARGET WhiteBox.Builders)
   ly_create_alias( NAME WhiteBox.Builders NAMESPACE Gem TARGETS Gem::WhiteBox.Editor)
endif()
