#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET ScriptedEntityTweener.Tools)
   ly_create_alias( NAME ScriptedEntityTweener.Tools NAMESPACE Gem TARGETS Gem::ScriptedEntityTweener)
endif()
if(NOT TARGET ScriptedEntityTweener.Clients)
   ly_create_alias( NAME ScriptedEntityTweener.Clients NAMESPACE Gem TARGETS Gem::ScriptedEntityTweener)
endif()
if(NOT TARGET ScriptedEntityTweener.Builders)
   ly_create_alias( NAME ScriptedEntityTweener.Builders NAMESPACE Gem TARGETS Gem::ScriptedEntityTweener)
endif()
if(NOT TARGET ScriptedEntityTweener.Servers)
   ly_create_alias( NAME ScriptedEntityTweener.Servers NAMESPACE Gem TARGETS Gem::ScriptedEntityTweener)
endif()
if(NOT TARGET ScriptedEntityTweener.Unified)
   ly_create_alias( NAME ScriptedEntityTweener.Unified NAMESPACE Gem TARGETS Gem::ScriptedEntityTweener)
endif()
