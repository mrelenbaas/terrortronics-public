#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

if(NOT TARGET ExpressionEvaluation.Clients)
   ly_create_alias( NAME ExpressionEvaluation.Clients NAMESPACE Gem TARGETS ExpressionEvaluation)
endif()
if(NOT TARGET ExpressionEvaluation.Servers)
   ly_create_alias( NAME ExpressionEvaluation.Servers NAMESPACE Gem TARGETS ExpressionEvaluation)
endif()
if(NOT TARGET ExpressionEvaluation.Unified)
   ly_create_alias( NAME ExpressionEvaluation.Unified NAMESPACE Gem TARGETS ExpressionEvaluation)
endif()
if(NOT TARGET ExpressionEvaluation.Builders)
   ly_create_alias( NAME ExpressionEvaluation.Builders NAMESPACE Gem TARGETS ExpressionEvaluation)
endif()
if(NOT TARGET ExpressionEvaluation.Tools)
   ly_create_alias( NAME ExpressionEvaluation.Tools NAMESPACE Gem TARGETS ExpressionEvaluation)
endif()
