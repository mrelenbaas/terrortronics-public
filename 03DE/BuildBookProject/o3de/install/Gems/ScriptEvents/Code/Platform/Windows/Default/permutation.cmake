#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET ScriptEvents.Clients)
   ly_create_alias( NAME ScriptEvents.Clients NAMESPACE Gem TARGETS Gem::ScriptEvents)
endif()
if(NOT TARGET ScriptEvents.Servers)
   ly_create_alias( NAME ScriptEvents.Servers NAMESPACE Gem TARGETS Gem::ScriptEvents)
endif()
if(NOT TARGET ScriptEvents.Unified)
   ly_create_alias( NAME ScriptEvents.Unified NAMESPACE Gem TARGETS Gem::ScriptEvents)
endif()
if(NOT TARGET ScriptEvents.Tools)
   ly_create_alias( NAME ScriptEvents.Tools NAMESPACE Gem TARGETS Gem::ScriptEvents.Editor)
endif()
if(NOT TARGET ScriptEvents.Builders)
   ly_create_alias( NAME ScriptEvents.Builders NAMESPACE Gem TARGETS Gem::ScriptEvents.Editor)
endif()
