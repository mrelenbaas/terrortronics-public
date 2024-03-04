#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET PythonAssetBuilder.Tools)
   ly_create_alias( NAME PythonAssetBuilder.Tools NAMESPACE Gem TARGETS Gem::PythonAssetBuilder.Editor)
endif()
if(NOT TARGET PythonAssetBuilder.Builders)
   ly_create_alias( NAME PythonAssetBuilder.Builders NAMESPACE Gem TARGETS Gem::PythonAssetBuilder.Editor)
endif()
