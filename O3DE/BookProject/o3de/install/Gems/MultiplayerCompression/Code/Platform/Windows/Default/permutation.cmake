#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET MultiplayerCompression.Clients)
   ly_create_alias( NAME MultiplayerCompression.Clients NAMESPACE Gem TARGETS Gem::MultiplayerCompression)
endif()
if(NOT TARGET MultiplayerCompression.Servers)
   ly_create_alias( NAME MultiplayerCompression.Servers NAMESPACE Gem TARGETS Gem::MultiplayerCompression)
endif()
if(NOT TARGET MultiplayerCompression.Unified)
   ly_create_alias( NAME MultiplayerCompression.Unified NAMESPACE Gem TARGETS Gem::MultiplayerCompression)
endif()
if(NOT TARGET MultiplayerCompression.Tools)
   ly_create_alias( NAME MultiplayerCompression.Tools NAMESPACE Gem TARGETS Gem::MultiplayerCompression)
endif()
