#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET VirtualGamepad.Clients)
   ly_create_alias( NAME VirtualGamepad.Clients NAMESPACE Gem TARGETS Gem::VirtualGamepad Gem::LyShine.Clients)
endif()
if(NOT TARGET VirtualGamepad.Tools)
   ly_create_alias( NAME VirtualGamepad.Tools NAMESPACE Gem TARGETS Gem::VirtualGamepad Gem::LyShine.Tools)
endif()
if(NOT TARGET VirtualGamepad.Builders)
   ly_create_alias( NAME VirtualGamepad.Builders NAMESPACE Gem TARGETS Gem::VirtualGamepad Gem::UiBasics.Builders Gem::LyShine.Builders)
endif()
