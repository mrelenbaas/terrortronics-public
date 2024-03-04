#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET CertificateManager.Clients)
   ly_create_alias( NAME CertificateManager.Clients NAMESPACE Gem TARGETS Gem::CertificateManager)
endif()
if(NOT TARGET CertificateManager.Servers)
   ly_create_alias( NAME CertificateManager.Servers NAMESPACE Gem TARGETS Gem::CertificateManager)
endif()
if(NOT TARGET CertificateManager.Unified)
   ly_create_alias( NAME CertificateManager.Unified NAMESPACE Gem TARGETS Gem::CertificateManager)
endif()
