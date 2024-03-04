#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET ScriptCanvasDebugger.Builders)
   ly_create_alias( NAME ScriptCanvasDebugger.Builders NAMESPACE Gem TARGETS Gem::ScriptCanvasDebugger)
endif()
if(NOT TARGET ScriptCanvasDebugger.Tools)
   ly_create_alias( NAME ScriptCanvasDebugger.Tools NAMESPACE Gem TARGETS Gem::ScriptCanvasDebugger)
endif()
if(NOT TARGET ScriptCanvasDebugger.Clients)
   ly_create_alias( NAME ScriptCanvasDebugger.Clients NAMESPACE Gem TARGETS Gem::ScriptCanvasDebugger)
endif()
if(NOT TARGET ScriptCanvasDebugger.Servers)
   ly_create_alias( NAME ScriptCanvasDebugger.Servers NAMESPACE Gem TARGETS Gem::ScriptCanvasDebugger)
endif()
if(NOT TARGET ScriptCanvasDebugger.Unified)
   ly_create_alias( NAME ScriptCanvasDebugger.Unified NAMESPACE Gem TARGETS Gem::ScriptCanvasDebugger)
endif()
if(NOT TARGET ScriptCanvas.Clients)
   ly_create_alias( NAME ScriptCanvas.Clients NAMESPACE Gem TARGETS Gem::ScriptCanvas)
endif()
if(NOT TARGET ScriptCanvas.Servers)
   ly_create_alias( NAME ScriptCanvas.Servers NAMESPACE Gem TARGETS Gem::ScriptCanvas)
endif()
if(NOT TARGET ScriptCanvas.Unified)
   ly_create_alias( NAME ScriptCanvas.Unified NAMESPACE Gem TARGETS Gem::ScriptCanvas)
endif()
if(NOT TARGET ScriptCanvas.Builders)
   ly_create_alias( NAME ScriptCanvas.Builders NAMESPACE Gem TARGETS Gem::ScriptCanvas.Editor)
endif()
if(NOT TARGET ScriptCanvas.Tools)
   ly_create_alias( NAME ScriptCanvas.Tools NAMESPACE Gem TARGETS Gem::ScriptCanvas.Editor)
endif()
