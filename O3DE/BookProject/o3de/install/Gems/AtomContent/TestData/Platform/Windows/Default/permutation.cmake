#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET Atom_TestData.Builders)
   ly_create_alias( NAME Atom_TestData.Builders NAMESPACE Gem TARGETS)
endif()
if(NOT TARGET Atom_TestData.Tools)
   ly_create_alias( NAME Atom_TestData.Tools NAMESPACE Gem TARGETS)
endif()
