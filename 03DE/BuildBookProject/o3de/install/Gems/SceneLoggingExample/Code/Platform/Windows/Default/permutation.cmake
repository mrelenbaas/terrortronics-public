#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET SceneLoggingExample.Builders)
   ly_create_alias( NAME SceneLoggingExample.Builders NAMESPACE Gem TARGETS Gem::SceneLoggingExample)
endif()
if(NOT TARGET SceneLoggingExample.Tools)
   ly_create_alias( NAME SceneLoggingExample.Tools NAMESPACE Gem TARGETS Gem::SceneLoggingExample)
endif()
