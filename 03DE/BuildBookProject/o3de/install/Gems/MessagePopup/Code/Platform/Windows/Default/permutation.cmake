#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET MessagePopup.Clients)
   ly_create_alias( NAME MessagePopup.Clients NAMESPACE Gem TARGETS Gem::MessagePopup)
endif()
if(NOT TARGET MessagePopup.Builders)
   ly_create_alias( NAME MessagePopup.Builders NAMESPACE Gem TARGETS Gem::UiBasics.Builders)
endif()
