#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET HttpRequestor.Clients)
   ly_create_alias( NAME HttpRequestor.Clients NAMESPACE Gem TARGETS Gem::HttpRequestor)
endif()
if(NOT TARGET HttpRequestor.Servers)
   ly_create_alias( NAME HttpRequestor.Servers NAMESPACE Gem TARGETS Gem::HttpRequestor)
endif()
if(NOT TARGET HttpRequestor.Unified)
   ly_create_alias( NAME HttpRequestor.Unified NAMESPACE Gem TARGETS Gem::HttpRequestor)
endif()
if(NOT TARGET HttpRequestor.Builders)
   ly_create_alias( NAME HttpRequestor.Builders NAMESPACE Gem TARGETS Gem::HttpRequestor)
endif()
if(NOT TARGET HttpRequestor.Tools)
   ly_create_alias( NAME HttpRequestor.Tools NAMESPACE Gem TARGETS Gem::HttpRequestor)
endif()
