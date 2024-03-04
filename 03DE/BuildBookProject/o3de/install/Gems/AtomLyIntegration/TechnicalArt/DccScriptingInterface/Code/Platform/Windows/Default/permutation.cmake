#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET DccScriptingInterface.Tools)
   ly_create_alias( NAME DccScriptingInterface.Tools NAMESPACE Gem TARGETS Gem::DccScriptingInterface.Editor)
endif()
if(NOT TARGET DccScriptingInterface.Builders)
   ly_create_alias( NAME DccScriptingInterface.Builders NAMESPACE Gem TARGETS Gem::DccScriptingInterface.Editor)
endif()
if(NOT TARGET DccScriptingInterface.Tools.API)
   ly_create_alias( NAME DccScriptingInterface.Tools.API NAMESPACE Gem TARGETS Gem::DccScriptingInterface.Editor.API)
endif()
if(NOT TARGET DccScriptingInterface.Builders.API)
   ly_create_alias( NAME DccScriptingInterface.Builders.API NAMESPACE Gem TARGETS Gem::DccScriptingInterface.Editor.API)
endif()
