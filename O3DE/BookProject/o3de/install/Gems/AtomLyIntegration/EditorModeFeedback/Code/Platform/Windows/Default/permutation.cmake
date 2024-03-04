#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET EditorModeFeedback.Tools)
   ly_create_alias( NAME EditorModeFeedback.Tools NAMESPACE Gem TARGETS Gem::EditorModeFeedback.Editor)
endif()
if(NOT TARGET EditorModeFeedback.Builders)
   ly_create_alias( NAME EditorModeFeedback.Builders NAMESPACE Gem TARGETS Gem::EditorModeFeedback.Editor)
endif()
