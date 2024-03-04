#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET Metastream.Clients)
   ly_create_alias( NAME Metastream.Clients NAMESPACE Gem TARGETS Gem::Metastream)
endif()
if(NOT TARGET Metastream.Servers)
   ly_create_alias( NAME Metastream.Servers NAMESPACE Gem TARGETS Gem::Metastream)
endif()
if(NOT TARGET Metastream.Unified)
   ly_create_alias( NAME Metastream.Unified NAMESPACE Gem TARGETS Gem::Metastream)
endif()
if(NOT TARGET Metastream.Builders)
   ly_create_alias( NAME Metastream.Builders NAMESPACE Gem TARGETS Gem::Metastream)
endif()
if(NOT TARGET Metastream.Tools)
   ly_create_alias( NAME Metastream.Tools NAMESPACE Gem TARGETS Gem::Metastream)
endif()
