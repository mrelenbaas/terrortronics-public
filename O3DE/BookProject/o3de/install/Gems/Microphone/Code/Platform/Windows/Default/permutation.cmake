#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET Microphone.Clients)
   ly_create_alias( NAME Microphone.Clients NAMESPACE Gem TARGETS Gem::Microphone Gem::AudioSystem)
endif()
if(NOT TARGET Microphone.Tools)
   ly_create_alias( NAME Microphone.Tools NAMESPACE Gem TARGETS Gem::Microphone Gem::AudioSystem.Editor)
endif()
