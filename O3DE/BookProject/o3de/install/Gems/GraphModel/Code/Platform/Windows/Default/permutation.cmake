#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET GraphModel.Builders)
   ly_create_alias( NAME GraphModel.Builders NAMESPACE Gem TARGETS Gem::GraphModel.Editor)
endif()
if(NOT TARGET GraphModel.Tools)
   ly_create_alias( NAME GraphModel.Tools NAMESPACE Gem TARGETS Gem::GraphModel.Editor)
endif()
