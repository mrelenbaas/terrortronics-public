#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET Stars.Clients)
   ly_create_alias( NAME Stars.Clients NAMESPACE Gem TARGETS Gem::Stars)
endif()
if(NOT TARGET Stars.Tools)
   ly_create_alias( NAME Stars.Tools NAMESPACE Gem TARGETS Gem::Stars.Editor)
endif()
if(NOT TARGET Stars.Builders)
   ly_create_alias( NAME Stars.Builders NAMESPACE Gem TARGETS Gem::Stars.Editor)
endif()
