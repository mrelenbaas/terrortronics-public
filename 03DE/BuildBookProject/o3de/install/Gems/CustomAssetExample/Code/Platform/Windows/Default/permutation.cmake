#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET CustomAssetExample.Clients)
   ly_create_alias( NAME CustomAssetExample.Clients NAMESPACE Gem TARGETS CustomAssetExample)
endif()
if(NOT TARGET CustomAssetExample.Servers)
   ly_create_alias( NAME CustomAssetExample.Servers NAMESPACE Gem TARGETS CustomAssetExample)
endif()
if(NOT TARGET CustomAssetExample.Unified)
   ly_create_alias( NAME CustomAssetExample.Unified NAMESPACE Gem TARGETS CustomAssetExample)
endif()
if(NOT TARGET CustomAssetExample.Builders)
   ly_create_alias( NAME CustomAssetExample.Builders NAMESPACE Gem TARGETS CustomAssetExample.Editor)
endif()
if(NOT TARGET CustomAssetExample.Tools)
   ly_create_alias( NAME CustomAssetExample.Tools NAMESPACE Gem TARGETS CustomAssetExample.Editor)
endif()
