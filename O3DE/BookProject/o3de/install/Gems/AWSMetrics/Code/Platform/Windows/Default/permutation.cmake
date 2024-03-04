#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET AWSMetrics.Servers)
   ly_create_alias( NAME AWSMetrics.Servers NAMESPACE Gem TARGETS Gem::AWSCore.Servers Gem::AWSMetrics)
endif()
if(NOT TARGET AWSMetrics.Clients)
   ly_create_alias( NAME AWSMetrics.Clients NAMESPACE Gem TARGETS Gem::AWSCore.Clients Gem::AWSMetrics)
endif()
if(NOT TARGET AWSMetrics.Unified)
   ly_create_alias( NAME AWSMetrics.Unified NAMESPACE Gem TARGETS Gem::AWSCore.Unified Gem::AWSMetrics)
endif()
if(NOT TARGET AWSMetrics.Tools)
   ly_create_alias( NAME AWSMetrics.Tools NAMESPACE Gem TARGETS Gem::AWSCore.Tools Gem::AWSMetrics.Editor)
endif()
if(NOT TARGET AWSMetrics.Builders)
   ly_create_alias( NAME AWSMetrics.Builders NAMESPACE Gem TARGETS Gem::AWSCore.Builders Gem::AWSMetrics)
endif()
