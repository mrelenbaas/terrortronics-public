#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET ImGui.Clients)
   ly_create_alias( NAME ImGui.Clients NAMESPACE Gem TARGETS Gem::ImGui)
endif()
if(NOT TARGET ImGui.Servers)
   ly_create_alias( NAME ImGui.Servers NAMESPACE Gem TARGETS Gem::ImGui)
endif()
if(NOT TARGET ImGui.Unified)
   ly_create_alias( NAME ImGui.Unified NAMESPACE Gem TARGETS Gem::ImGui)
endif()
if(NOT TARGET ImGui.Builders)
   ly_create_alias( NAME ImGui.Builders NAMESPACE Gem TARGETS Gem::ImGui.Editor)
endif()
if(NOT TARGET ImGui.Tools)
   ly_create_alias( NAME ImGui.Tools NAMESPACE Gem TARGETS Gem::ImGui.Editor)
endif()
