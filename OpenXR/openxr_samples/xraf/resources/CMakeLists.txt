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

if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    set(PYTHON_CMD python)
else()
    set(PYTHON_CMD python3)
endif()


# Add any shader files you wish to include here
set(SHADER_FILES
        "shaders/shader.vert"
        "shaders/shader.frag"
        "shaders/pbr.vert"
        "shaders/pbr.frag"

        )

# Add any other files you wish to include here
set(BIN_FILES
        "textures/default.png"
        "textures/meteor.png"
        )


add_library(xr_app_framework_resources STATIC
        Resources.cpp
        )

# Shader resources
# ----------------

find_program(GLSL_VALIDATOR "glslangValidator")
if (GLSL_VALIDATOR)

    foreach (GLSL_PARTIAL ${SHADER_FILES})
        set(GLSL "${CMAKE_CURRENT_LIST_DIR}/${GLSL_PARTIAL}")
        get_filename_component(FILE_NAME ${GLSL} NAME)
        get_filename_component(DIR ${GLSL} DIRECTORY)
        set(OUT "${DIR}/../compiled/${FILE_NAME}.h")
        if((EXISTS "${OUT}") AND (NOT DEFINED ENV{XRAF_REBUILD_RESOURCES}))
          message("Reusing ${OUT} as it already exists, set XRAF_REBUILD_RESOURCES to enabling rebuilding")
          continue()
        endif()
        string(REPLACE "." "_" SPIRV_VAR ${FILE_NAME})
        add_custom_command(
                OUTPUT ${OUT}
                COMMAND glslangValidator --vn ${SPIRV_VAR} -V ${GLSL} -o ${OUT}
                DEPENDS ${GLSL})
        list(APPEND SPIRV_BINARY_FILES ${OUT})
        message("Built ${OUT}")
    endforeach (GLSL_PARTIAL)

    add_custom_target(
            vulkan_shaders
            DEPENDS ${SPIRV_BINARY_FILES}
    )
    add_dependencies(xr_app_framework_resources vulkan_shaders)
else ()
    message("Unable to find glslangValidator, not rebuilding shaders")
endif ()

# Binary resources
# ----------------

foreach (BIN_FILE_PARTIAL ${BIN_FILES})
    set(BIN_FILE "${CMAKE_CURRENT_LIST_DIR}/${BIN_FILE_PARTIAL}")
    get_filename_component(FILE_NAME "${BIN_FILE}" NAME)
    get_filename_component(DIR ${BIN_FILE} DIRECTORY)
    set(OUT "${DIR}/../compiled/${FILE_NAME}.h")
    if((EXISTS "${OUT}") AND (NOT DEFINED ENV{XRAF_REBUILD_RESOURCES}))
      message("Reusing ${OUT} as it already exists, set XRAF_REBUILD_RESOURCES to enabling rebuilding")
      continue()
    endif()
    string(REPLACE "." "_" BIN_VAR ${FILE_NAME})
    add_custom_command(
            OUTPUT ${OUT}
            COMMAND ${PYTHON_CMD} ${CMAKE_CURRENT_LIST_DIR}/bin2h.py "${BIN_FILE}" "${OUT}" "${BIN_VAR}"
            DEPENDS ${BIN_FILE})
    list(APPEND BIN_BINARY_FILES ${OUT})
    message("Built ${OUT}")
endforeach (BIN_FILE_PARTIAL)

add_custom_target(
        resources
        DEPENDS ${BIN_BINARY_FILES}
)

add_dependencies(xr_app_framework_resources resources)
