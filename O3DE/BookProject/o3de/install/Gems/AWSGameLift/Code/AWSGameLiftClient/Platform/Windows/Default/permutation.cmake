#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET AWSGameLift.Tools)
   ly_create_alias( NAME AWSGameLift.Tools NAMESPACE Gem TARGETS Gem::AWSGameLift.Editor Gem::AWSCore.Tools)
endif()
if(NOT TARGET AWSGameLift.Builders)
   ly_create_alias( NAME AWSGameLift.Builders NAMESPACE Gem TARGETS Gem::AWSCore.Builders Gem::AWSGameLift.Clients)
endif()
