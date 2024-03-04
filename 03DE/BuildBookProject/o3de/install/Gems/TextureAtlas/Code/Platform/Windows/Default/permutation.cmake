#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET TextureAtlas.Builders)
   ly_create_alias( NAME TextureAtlas.Builders NAMESPACE Gem TARGETS Gem::TextureAtlas.Editor)
endif()
if(NOT TARGET TextureAtlas.Tools)
   ly_create_alias( NAME TextureAtlas.Tools NAMESPACE Gem TARGETS Gem::TextureAtlas.Editor)
endif()
if(NOT TARGET TextureAtlas.Servers)
   ly_create_alias( NAME TextureAtlas.Servers NAMESPACE Gem TARGETS Gem::TextureAtlas)
endif()
if(NOT TARGET TextureAtlas.Clients)
   ly_create_alias( NAME TextureAtlas.Clients NAMESPACE Gem TARGETS Gem::TextureAtlas)
endif()
if(NOT TARGET TextureAtlas.Unified)
   ly_create_alias( NAME TextureAtlas.Unified NAMESPACE Gem TARGETS Gem::TextureAtlas)
endif()
