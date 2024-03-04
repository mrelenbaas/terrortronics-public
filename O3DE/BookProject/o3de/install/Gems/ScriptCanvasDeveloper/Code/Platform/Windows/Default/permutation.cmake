#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET ScriptCanvasDeveloper.Clients)
   ly_create_alias( NAME ScriptCanvasDeveloper.Clients NAMESPACE Gem TARGETS Gem::ScriptCanvasDeveloper)
endif()
if(NOT TARGET ScriptCanvasDeveloper.Servers)
   ly_create_alias( NAME ScriptCanvasDeveloper.Servers NAMESPACE Gem TARGETS Gem::ScriptCanvasDeveloper)
endif()
if(NOT TARGET ScriptCanvasDeveloper.Unified)
   ly_create_alias( NAME ScriptCanvasDeveloper.Unified NAMESPACE Gem TARGETS Gem::ScriptCanvasDeveloper)
endif()
if(NOT TARGET ScriptCanvasDeveloper.Builders)
   ly_create_alias( NAME ScriptCanvasDeveloper.Builders NAMESPACE Gem TARGETS Gem::ScriptCanvasDeveloper.Editor)
endif()
if(NOT TARGET ScriptCanvasDeveloper.Tools)
   ly_create_alias( NAME ScriptCanvasDeveloper.Tools NAMESPACE Gem TARGETS Gem::ScriptCanvasDeveloper.Editor)
endif()
