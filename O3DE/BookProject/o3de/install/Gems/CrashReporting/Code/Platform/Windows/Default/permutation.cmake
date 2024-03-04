#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET CrashReporting.Clients)
   ly_create_alias( NAME CrashReporting.Clients NAMESPACE Gem TARGETS Gem::CrashReporting)
endif()
if(NOT TARGET CrashReporting.Servers)
   ly_create_alias( NAME CrashReporting.Servers NAMESPACE Gem TARGETS Gem::CrashReporting)
endif()
if(NOT TARGET CrashReporting.Unified)
   ly_create_alias( NAME CrashReporting.Unified NAMESPACE Gem TARGETS Gem::CrashReporting)
endif()
