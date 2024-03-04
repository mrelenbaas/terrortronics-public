#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET AtomTressFX.Clients)
   ly_create_alias( NAME AtomTressFX.Clients NAMESPACE Gem TARGETS Gem::AtomTressFX)
endif()
if(NOT TARGET AtomTressFX.Servers)
   ly_create_alias( NAME AtomTressFX.Servers NAMESPACE Gem TARGETS Gem::AtomTressFX)
endif()
if(NOT TARGET AtomTressFX.Unified)
   ly_create_alias( NAME AtomTressFX.Unified NAMESPACE Gem TARGETS Gem::AtomTressFX)
endif()
if(NOT TARGET AtomTressFX.Tools)
   ly_create_alias( NAME AtomTressFX.Tools NAMESPACE Gem TARGETS Gem::AtomTressFX Gem::AtomTressFX.Builders)
endif()
