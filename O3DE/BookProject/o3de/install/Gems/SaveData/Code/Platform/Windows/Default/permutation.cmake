#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET SaveData.Clients)
   ly_create_alias( NAME SaveData.Clients NAMESPACE Gem TARGETS Gem::SaveData)
endif()
