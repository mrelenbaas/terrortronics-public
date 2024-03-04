# %BANNER_BEGIN%
# ---------------------------------------------------------------------
# %COPYRIGHT_BEGIN%
# Copyright (c) 2022 Magic Leap, Inc. All Rights Reserved.
# Use of this file is governed by the Software License Agreement,
# located here: https://www.magicleap.com/software-license-agreement-ml2
# Terms and conditions applicable to third-party materials accompanying
# this distribution may also be found in the top-level NOTICE file
# appearing herein.
# %COPYRIGHT_END%
# ---------------------------------------------------------------------
# %BANNER_END%
cmake_minimum_required(VERSION 3.22.1)

include("../../../../../../cmake/common.cmake")

project(${APP_NAME})

######################
# APPLICATION
######################

add_application(${APP_NAME} main.cpp)

target_link_libraries(${APP_NAME} PRIVATE
    xr_app_framework
    $<$<BOOL:${USE_OPENXR_LAYERS}>:XrApiLayer_core_validation>
)
