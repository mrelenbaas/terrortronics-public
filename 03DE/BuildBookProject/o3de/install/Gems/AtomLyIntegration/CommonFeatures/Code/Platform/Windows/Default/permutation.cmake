#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET AtomLyIntegration_CommonFeatures.Clients)
   ly_create_alias( NAME AtomLyIntegration_CommonFeatures.Clients NAMESPACE Gem TARGETS Gem::AtomLyIntegration_CommonFeatures Gem::GradientSignal.Clients)
endif()
if(NOT TARGET AtomLyIntegration_CommonFeatures.Servers)
   ly_create_alias( NAME AtomLyIntegration_CommonFeatures.Servers NAMESPACE Gem TARGETS Gem::AtomLyIntegration_CommonFeatures Gem::GradientSignal.Servers)
endif()
if(NOT TARGET AtomLyIntegration_CommonFeatures.Unified)
   ly_create_alias( NAME AtomLyIntegration_CommonFeatures.Unified NAMESPACE Gem TARGETS Gem::AtomLyIntegration_CommonFeatures Gem::GradientSignal.Unified)
endif()
if(NOT TARGET CommonFeaturesAtom.Clients)
   ly_create_alias( NAME CommonFeaturesAtom.Clients NAMESPACE Gem TARGETS Gem::AtomLyIntegration_CommonFeatures.Clients)
endif()
if(NOT TARGET CommonFeaturesAtom.Servers)
   ly_create_alias( NAME CommonFeaturesAtom.Servers NAMESPACE Gem TARGETS Gem::AtomLyIntegration_CommonFeatures.Servers)
endif()
if(NOT TARGET CommonFeaturesAtom.Unified)
   ly_create_alias( NAME CommonFeaturesAtom.Unified NAMESPACE Gem TARGETS Gem::AtomLyIntegration_CommonFeatures.Unified)
endif()
if(NOT TARGET AtomLyIntegration_CommonFeatures.Builders)
   ly_create_alias( NAME AtomLyIntegration_CommonFeatures.Builders NAMESPACE Gem TARGETS Gem::AtomLyIntegration_CommonFeatures.Editor Gem::Atom_Feature_Common.Builders Gem::Atom_RPI.Builders Gem::GradientSignal.Builders)
endif()
if(NOT TARGET AtomLyIntegration_CommonFeatures.Tools)
   ly_create_alias( NAME AtomLyIntegration_CommonFeatures.Tools NAMESPACE Gem TARGETS Gem::AtomLyIntegration_CommonFeatures.Editor Gem::GradientSignal.Tools)
endif()
if(NOT TARGET CommonFeaturesAtom.Builders)
   ly_create_alias( NAME CommonFeaturesAtom.Builders NAMESPACE Gem TARGETS Gem::AtomLyIntegration_CommonFeatures.Builders)
endif()
if(NOT TARGET CommonFeaturesAtom.Tools)
   ly_create_alias( NAME CommonFeaturesAtom.Tools NAMESPACE Gem TARGETS Gem::AtomLyIntegration_CommonFeatures.Tools)
endif()
