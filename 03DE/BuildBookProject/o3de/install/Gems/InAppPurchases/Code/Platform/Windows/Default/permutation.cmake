#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET InAppPurchases.Clients)
   ly_create_alias( NAME InAppPurchases.Clients NAMESPACE Gem TARGETS Gem::InAppPurchases)
endif()
if(NOT TARGET InAppPurchases.Servers)
   ly_create_alias( NAME InAppPurchases.Servers NAMESPACE Gem TARGETS Gem::InAppPurchases)
endif()
if(NOT TARGET InAppPurchases.Unified)
   ly_create_alias( NAME InAppPurchases.Unified NAMESPACE Gem TARGETS Gem::InAppPurchases)
endif()
if(NOT TARGET InAppPurchases.Builders)
   ly_create_alias( NAME InAppPurchases.Builders NAMESPACE Gem TARGETS Gem::InAppPurchases)
endif()
if(NOT TARGET InAppPurchases.Tools)
   ly_create_alias( NAME InAppPurchases.Tools NAMESPACE Gem TARGETS Gem::InAppPurchases)
endif()
