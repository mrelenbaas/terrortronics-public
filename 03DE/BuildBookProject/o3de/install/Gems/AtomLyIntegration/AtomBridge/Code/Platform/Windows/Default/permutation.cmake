#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET Atom_AtomBridge.Clients)
   ly_create_alias( NAME Atom_AtomBridge.Clients NAMESPACE Gem TARGETS Gem::Atom_AtomBridge)
endif()
if(NOT TARGET Atom_AtomBridge.Servers)
   ly_create_alias( NAME Atom_AtomBridge.Servers NAMESPACE Gem TARGETS Gem::Atom_AtomBridge)
endif()
if(NOT TARGET Atom_AtomBridge.Unified)
   ly_create_alias( NAME Atom_AtomBridge.Unified NAMESPACE Gem TARGETS Gem::Atom_AtomBridge)
endif()
if(NOT TARGET Atom_AtomBridge.Builders)
   ly_create_alias( NAME Atom_AtomBridge.Builders NAMESPACE Gem TARGETS Gem::Atom_AtomBridge.Editor)
endif()
if(NOT TARGET Atom_AtomBridge.Tools)
   ly_create_alias( NAME Atom_AtomBridge.Tools NAMESPACE Gem TARGETS Gem::Atom_AtomBridge.Editor)
endif()
