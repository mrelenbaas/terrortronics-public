#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET Atom_Bootstrap.Clients)
   ly_create_alias( NAME Atom_Bootstrap.Clients NAMESPACE Gem TARGETS Gem::Atom_Bootstrap)
endif()
if(NOT TARGET Atom_Bootstrap.Servers)
   ly_create_alias( NAME Atom_Bootstrap.Servers NAMESPACE Gem TARGETS Gem::Atom_Bootstrap)
endif()
if(NOT TARGET Atom_Bootstrap.Unified)
   ly_create_alias( NAME Atom_Bootstrap.Unified NAMESPACE Gem TARGETS Gem::Atom_Bootstrap)
endif()
