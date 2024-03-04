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

find_program(CCACHE_EXECUTABLE ccache)
if (CCACHE_EXECUTABLE)
    message("Using ccache")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_EXECUTABLE}")
    set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_EXECUTABLE}")
endif()

if (NO_XRAF)
    message("Not including XRAF")
    if (NOT NO_ML_CAPI)
        file(TO_CMAKE_PATH "$ENV{MLSDK}" MLSDK)
        file(TO_CMAKE_PATH "${ANDROID_NDK}" ANDROID_NDK)
        list(APPEND CMAKE_MODULE_PATH "${MLSDK}/cmake" "${ANDROID_NDK}/../../mlsdk/cmake")
        find_package(MagicLeap REQUIRED)
        find_package(MagicLeapNativeAppGlue REQUIRED)
        find_package(MagicLeapOpenGL REQUIRED)
    endif()
else()
    include(FetchContent)
    FetchContent_Declare(
        xraf
        SOURCE_DIR   "${CMAKE_CURRENT_LIST_DIR}/../xraf"
    )
    FetchContent_MakeAvailable(xraf)
endif()

function(target_common APP_NAME)
    target_compile_options(${APP_NAME} PRIVATE -Wall)
    target_compile_features(${APP_NAME} PRIVATE cxx_std_17)
    target_compile_definitions(${APP_NAME} PRIVATE ALOG_TAG="${APP_ID}" APP_NAME="${APP_NAME}")

    if (ML_TARGET STREQUAL ml2)
        # nothing yet.
    else()
        target_compile_options(${APP_NAME} PRIVATE -fPIC)
        # Instead of using android log use a printf based  log output.
        if (NO_APPSIM)
            target_compile_definitions(xr_app_framework PUBLIC LOCAL_LOGGING)
        endif()
    endif()

    if (COMMAND copy_artifacts)
        copy_artifacts(${APP_NAME})
    endif()
endfunction()


# This functions replaced add_library so that any
# of the samples/tests can be built as an executable
# as well.
function(add_application APP_NAME sources)
    # All samples have the APP_NAME as their first
    # argument, this however needs to be split for
    # add library from the source files.
    list(REMOVE_AT ARGV 0)
    if (NO_APPSIM)
        add_executable(${APP_NAME} ${ARGV})
    else()
        add_library(${APP_NAME} SHARED ${ARGV})
    endif()
    target_common(${APP_NAME})
endfunction()
