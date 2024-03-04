#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET LmbrCentral.Clients)
   ly_create_alias( NAME LmbrCentral.Clients NAMESPACE Gem TARGETS Gem::LmbrCentral)
endif()
if(NOT TARGET LmbrCentral.Servers)
   ly_create_alias( NAME LmbrCentral.Servers NAMESPACE Gem TARGETS Gem::LmbrCentral)
endif()
if(NOT TARGET LmbrCentral.Unified)
   ly_create_alias( NAME LmbrCentral.Unified NAMESPACE Gem TARGETS Gem::LmbrCentral)
endif()
if(NOT TARGET LmbrCentral.Builders)
   ly_create_alias( NAME LmbrCentral.Builders NAMESPACE Gem TARGETS Gem::LmbrCentral.Editor)
endif()
if(NOT TARGET LmbrCentral.Tools)
   ly_create_alias( NAME LmbrCentral.Tools NAMESPACE Gem TARGETS Gem::LmbrCentral.Editor)
endif()
