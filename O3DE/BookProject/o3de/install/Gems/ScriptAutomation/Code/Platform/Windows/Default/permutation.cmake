#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET ScriptAutomation.Servers)
   ly_create_alias( NAME ScriptAutomation.Servers NAMESPACE Gem TARGETS Gem::ScriptAutomation)
endif()
if(NOT TARGET ScriptAutomation.Unified)
   ly_create_alias( NAME ScriptAutomation.Unified NAMESPACE Gem TARGETS Gem::ScriptAutomation)
endif()
if(NOT TARGET ScriptAutomation.Builders)
   ly_create_alias( NAME ScriptAutomation.Builders NAMESPACE Gem TARGETS Gem::ScriptAutomation)
endif()
if(NOT TARGET ScriptAutomation.Clients)
   ly_create_alias( NAME ScriptAutomation.Clients NAMESPACE Gem TARGETS Gem::ScriptAutomation)
endif()
if(NOT TARGET ScriptAutomation.Tools)
   ly_create_alias( NAME ScriptAutomation.Tools NAMESPACE Gem TARGETS Gem::ScriptAutomation)
endif()
