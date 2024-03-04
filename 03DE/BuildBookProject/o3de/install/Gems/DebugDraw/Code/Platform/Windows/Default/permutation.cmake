#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET DebugDraw.Clients)
   ly_create_alias( NAME DebugDraw.Clients NAMESPACE Gem TARGETS DebugDraw)
endif()
if(NOT TARGET DebugDraw.Unified)
   ly_create_alias( NAME DebugDraw.Unified NAMESPACE Gem TARGETS DebugDraw)
endif()
if(NOT TARGET DebugDraw.Builders)
   ly_create_alias( NAME DebugDraw.Builders NAMESPACE Gem TARGETS DebugDraw.Editor)
endif()
if(NOT TARGET DebugDraw.Tools)
   ly_create_alias( NAME DebugDraw.Tools NAMESPACE Gem TARGETS DebugDraw.Editor)
endif()
