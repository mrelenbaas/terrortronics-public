#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET Twitch.Servers)
   ly_create_alias( NAME Twitch.Servers NAMESPACE Gem TARGETS Gem::Twitch)
endif()
if(NOT TARGET Twitch.Clients)
   ly_create_alias( NAME Twitch.Clients NAMESPACE Gem TARGETS Gem::Twitch)
endif()
if(NOT TARGET Twitch.Unified)
   ly_create_alias( NAME Twitch.Unified NAMESPACE Gem TARGETS Gem::Twitch)
endif()
if(NOT TARGET Twitch.Tools)
   ly_create_alias( NAME Twitch.Tools NAMESPACE Gem TARGETS Gem::Twitch)
endif()
