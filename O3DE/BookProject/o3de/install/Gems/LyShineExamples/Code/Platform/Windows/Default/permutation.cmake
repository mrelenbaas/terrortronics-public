#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET LyShineExamples.Builders)
   ly_create_alias( NAME LyShineExamples.Builders NAMESPACE Gem TARGETS Gem::LyShineExamples Gem::UiBasics.Builders Gem::LmbrCentral.Editor)
endif()
if(NOT TARGET LyShineExamples.Tools)
   ly_create_alias( NAME LyShineExamples.Tools NAMESPACE Gem TARGETS Gem::LyShineExamples Gem::LmbrCentral.Editor)
endif()
if(NOT TARGET LyShineExamples.Clients)
   ly_create_alias( NAME LyShineExamples.Clients NAMESPACE Gem TARGETS Gem::LyShineExamples Gem::LmbrCentral)
endif()
if(NOT TARGET LyShineExamples.Servers)
   ly_create_alias( NAME LyShineExamples.Servers NAMESPACE Gem TARGETS Gem::LyShineExamples Gem::LmbrCentral)
endif()
if(NOT TARGET LyShineExamples.Unified)
   ly_create_alias( NAME LyShineExamples.Unified NAMESPACE Gem TARGETS Gem::LyShineExamples Gem::LmbrCentral)
endif()
