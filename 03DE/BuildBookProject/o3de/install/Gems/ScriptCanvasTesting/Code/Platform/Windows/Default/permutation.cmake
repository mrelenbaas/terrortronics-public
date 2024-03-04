#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET ScriptCanvasTesting.Tools)
   ly_create_alias( NAME ScriptCanvasTesting.Tools NAMESPACE Gem TARGETS Gem::ScriptCanvasTesting.Editor)
endif()
if(NOT TARGET ScriptCanvasTesting.Builders)
   ly_create_alias( NAME ScriptCanvasTesting.Builders NAMESPACE Gem TARGETS Gem::ScriptCanvasTesting.Editor)
endif()
