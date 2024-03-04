#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET Multiplayer_ScriptCanvas.Unified)
   ly_create_alias( NAME Multiplayer_ScriptCanvas.Unified NAMESPACE Gem TARGETS Gem::Multiplayer_ScriptCanvas Gem::ScriptCanvas)
endif()
if(NOT TARGET Multiplayer_ScriptCanvas.Clients)
   ly_create_alias( NAME Multiplayer_ScriptCanvas.Clients NAMESPACE Gem TARGETS Gem::Multiplayer_ScriptCanvas Gem::ScriptCanvas)
endif()
if(NOT TARGET Multiplayer_ScriptCanvas.Servers)
   ly_create_alias( NAME Multiplayer_ScriptCanvas.Servers NAMESPACE Gem TARGETS Gem::Multiplayer_ScriptCanvas Gem::ScriptCanvas)
endif()
if(NOT TARGET Multiplayer_ScriptCanvas.Tools)
   ly_create_alias( NAME Multiplayer_ScriptCanvas.Tools NAMESPACE Gem TARGETS Gem::Multiplayer_ScriptCanvas Gem::ScriptCanvas.Editor)
endif()
if(NOT TARGET Multiplayer_ScriptCanvas.Builders)
   ly_create_alias( NAME Multiplayer_ScriptCanvas.Builders NAMESPACE Gem TARGETS Gem::Multiplayer_ScriptCanvas Gem::ScriptCanvas.Editor)
endif()
