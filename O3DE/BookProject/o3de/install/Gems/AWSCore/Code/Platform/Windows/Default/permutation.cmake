#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET AWSCore.Servers)
   ly_create_alias( NAME AWSCore.Servers NAMESPACE Gem TARGETS Gem::AWSCore)
endif()
if(NOT TARGET AWSCore.Clients)
   ly_create_alias( NAME AWSCore.Clients NAMESPACE Gem TARGETS Gem::AWSCore)
endif()
if(NOT TARGET AWSCore.Unified)
   ly_create_alias( NAME AWSCore.Unified NAMESPACE Gem TARGETS Gem::AWSCore)
endif()
if(NOT TARGET AWSCore.Tools)
   ly_create_alias( NAME AWSCore.Tools NAMESPACE Gem TARGETS Gem::AWSCore Gem::AWSCore.Editor)
endif()
if(NOT TARGET AWSCore.Builders)
   ly_create_alias( NAME AWSCore.Builders NAMESPACE Gem TARGETS Gem::AWSCore Gem::AWSCore.Editor)
endif()
