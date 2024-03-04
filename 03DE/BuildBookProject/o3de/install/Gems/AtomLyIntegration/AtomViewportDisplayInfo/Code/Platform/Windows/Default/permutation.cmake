#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET AtomViewportDisplayInfo.Clients)
   ly_create_alias( NAME AtomViewportDisplayInfo.Clients NAMESPACE Gem TARGETS Gem::AtomViewportDisplayInfo)
endif()
if(NOT TARGET AtomViewportDisplayInfo.Tools)
   ly_create_alias( NAME AtomViewportDisplayInfo.Tools NAMESPACE Gem TARGETS Gem::AtomViewportDisplayInfo)
endif()
if(NOT TARGET AtomViewportDisplayInfo.Servers)
   ly_create_alias( NAME AtomViewportDisplayInfo.Servers NAMESPACE Gem TARGETS Gem::AtomViewportDisplayInfo)
endif()
if(NOT TARGET AtomViewportDisplayInfo.Unified)
   ly_create_alias( NAME AtomViewportDisplayInfo.Unified NAMESPACE Gem TARGETS Gem::AtomViewportDisplayInfo)
endif()
