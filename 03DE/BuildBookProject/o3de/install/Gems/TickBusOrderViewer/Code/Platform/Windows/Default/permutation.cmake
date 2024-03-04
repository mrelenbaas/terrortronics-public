#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET TickBusOrderViewer.Servers)
   ly_create_alias( NAME TickBusOrderViewer.Servers NAMESPACE Gem TARGETS Gem::TickBusOrderViewer)
endif()
if(NOT TARGET TickBusOrderViewer.Clients)
   ly_create_alias( NAME TickBusOrderViewer.Clients NAMESPACE Gem TARGETS Gem::TickBusOrderViewer)
endif()
if(NOT TARGET TickBusOrderViewer.Unified)
   ly_create_alias( NAME TickBusOrderViewer.Unified NAMESPACE Gem TARGETS Gem::TickBusOrderViewer)
endif()
if(NOT TARGET TickBusOrderViewer.Tools)
   ly_create_alias( NAME TickBusOrderViewer.Tools NAMESPACE Gem TARGETS Gem::TickBusOrderViewer)
endif()
