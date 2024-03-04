#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET DiffuseProbeGrid.Servers)
   ly_create_alias( NAME DiffuseProbeGrid.Servers NAMESPACE Gem TARGETS Gem::DiffuseProbeGrid)
endif()
if(NOT TARGET DiffuseProbeGrid.Clients)
   ly_create_alias( NAME DiffuseProbeGrid.Clients NAMESPACE Gem TARGETS Gem::DiffuseProbeGrid)
endif()
if(NOT TARGET DiffuseProbeGrid.Unified)
   ly_create_alias( NAME DiffuseProbeGrid.Unified NAMESPACE Gem TARGETS Gem::DiffuseProbeGrid)
endif()
if(NOT TARGET DiffuseProbeGrid.Builders)
   ly_create_alias( NAME DiffuseProbeGrid.Builders NAMESPACE Gem TARGETS Gem::DiffuseProbeGrid.Editor)
endif()
if(NOT TARGET DiffuseProbeGrid.Tools)
   ly_create_alias( NAME DiffuseProbeGrid.Tools NAMESPACE Gem TARGETS Gem::DiffuseProbeGrid.Editor)
endif()
