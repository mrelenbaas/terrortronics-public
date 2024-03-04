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

if("$ENV{CI_BUILD}" STREQUAL "1")
    message("Using CI mirror")
    file(READ "${CMAKE_CURRENT_LIST_DIR}/external_deps_ci.csv" data)
elseif(USE_LOCAL_DEPS)
    if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/external_deps_local.csv")
        message(FATAL_ERROR "Trying to use local dependencies without proper config files. Please first run ${CMAKE_CURRENT_LIST_DIR}/../scripts/fetch_externals.py script!")
    endif()
    file(READ "${CMAKE_CURRENT_LIST_DIR}/external_deps_local.csv" data)
else()
    file(READ "${CMAKE_CURRENT_LIST_DIR}/external_deps.csv" data)
endif()

string(REPLACE "\n" ";" data "${data}")
foreach(line IN LISTS data)
    string(REPLACE "," ";" line "${line}")
    list(LENGTH line length)
    if("${length}" EQUAL "3")
        list(GET line 0 name)
        list(GET line 1 url)
        list(GET line 2 hash)
        set(EXTERNAL_${name} ${url})
        set(EXTERNAL_HASH_${name} ${hash})
    endif()
endforeach()
