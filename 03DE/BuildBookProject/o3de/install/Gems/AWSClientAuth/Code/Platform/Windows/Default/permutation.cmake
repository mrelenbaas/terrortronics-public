#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET AWSClientAuth.Servers)
   ly_create_alias( NAME AWSClientAuth.Servers NAMESPACE Gem TARGETS Gem::AWSClientAuth Gem::AWSCore.Servers Gem::HttpRequestor.Servers)
endif()
if(NOT TARGET AWSClientAuth.Clients)
   ly_create_alias( NAME AWSClientAuth.Clients NAMESPACE Gem TARGETS Gem::AWSClientAuth Gem::AWSCore.Clients Gem::HttpRequestor.Clients)
endif()
if(NOT TARGET AWSClientAuth.Unified)
   ly_create_alias( NAME AWSClientAuth.Unified NAMESPACE Gem TARGETS Gem::AWSClientAuth Gem::AWSCore.Unified Gem::HttpRequestor.Unified)
endif()
if(NOT TARGET AWSClientAuth.Tools)
   ly_create_alias( NAME AWSClientAuth.Tools NAMESPACE Gem TARGETS Gem::AWSClientAuth.Editor Gem::AWSCore.Tools Gem::HttpRequestor.Tools)
endif()
if(NOT TARGET AWSClientAuth.Builders)
   ly_create_alias( NAME AWSClientAuth.Builders NAMESPACE Gem TARGETS Gem::AWSClientAuth Gem::AWSCore.Builders Gem::HttpRequestor.Builders)
endif()
