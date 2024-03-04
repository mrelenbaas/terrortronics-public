#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET GraphCanvas.Builders)
   ly_create_alias( NAME GraphCanvas.Builders NAMESPACE Gem TARGETS Gem::GraphCanvas.Editor)
endif()
if(NOT TARGET GraphCanvas.Tools)
   ly_create_alias( NAME GraphCanvas.Tools NAMESPACE Gem TARGETS Gem::GraphCanvas.Editor)
endif()
