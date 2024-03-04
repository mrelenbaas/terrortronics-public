#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET ScriptCanvasPhysics.Clients)
   ly_create_alias( NAME ScriptCanvasPhysics.Clients NAMESPACE Gem TARGETS Gem::ScriptCanvasPhysics Gem::ScriptCanvas)
endif()
if(NOT TARGET ScriptCanvasPhysics.Servers)
   ly_create_alias( NAME ScriptCanvasPhysics.Servers NAMESPACE Gem TARGETS Gem::ScriptCanvasPhysics Gem::ScriptCanvas)
endif()
if(NOT TARGET ScriptCanvasPhysics.Unified)
   ly_create_alias( NAME ScriptCanvasPhysics.Unified NAMESPACE Gem TARGETS Gem::ScriptCanvasPhysics Gem::ScriptCanvas)
endif()
if(NOT TARGET ScriptCanvasPhysics.Tools)
   ly_create_alias( NAME ScriptCanvasPhysics.Tools NAMESPACE Gem TARGETS Gem::ScriptCanvasPhysics Gem::ScriptCanvas.Editor)
endif()
if(NOT TARGET ScriptCanvasPhysics.Builders)
   ly_create_alias( NAME ScriptCanvasPhysics.Builders NAMESPACE Gem TARGETS Gem::ScriptCanvasPhysics Gem::ScriptCanvas.Editor)
endif()
