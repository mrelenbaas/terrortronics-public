#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET SceneProcessing.Builders)
   ly_create_alias( NAME SceneProcessing.Builders NAMESPACE Gem TARGETS Gem::SceneProcessing.Editor)
endif()
if(NOT TARGET SceneProcessing.Tools)
   ly_create_alias( NAME SceneProcessing.Tools NAMESPACE Gem TARGETS Gem::SceneProcessing.Editor)
endif()
