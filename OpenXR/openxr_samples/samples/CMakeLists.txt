cmake_minimum_required(VERSION 3.22.1)
project(samples)

string(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE_LOWERCASE)
set(OUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/out/openxr_host_samples/${BUILD_TYPE_LOWERCASE}")

macro(copy_artifacts target)
set_target_properties(${target} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUT_DIR}/${target}"
  LIBRARY_OUTPUT_DIRECTORY_DEBUG "${OUT_DIR}/${target}"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUT_DIR}/${target}"
  LIBRARY_OUTPUT_DIRECTORY_RELEASE "${OUT_DIR}/${target}"
)

add_custom_command(TARGET ${target} POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/../AndroidManifest.xml"
    "${OUT_DIR}/${target}/AndroidManifest.xml"
)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../assets")
  add_custom_command(TARGET ${target} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/../assets"
        "${OUT_DIR}/${target}/assets"
  )
endif()
endmacro()

macro(add_subdir target)
set(APP_ID "com.magicleap.capi.xr.sample.${target}")
set(APP_NAME ${target})
set(APP_ID "com.magicleap.capi.xr.sample.${target}")
add_subdirectory(${target}/app/src/main/cpp)
unset(APP_ID)
unset(APP_NAME)
unset(APP_ID)
endmacro()

add_subdir(eye_gaze) # -> Unable to create tracker: XR_EXT_eye_gaze_interaction extension not enabled!
add_subdir(hand_tracking) # -> XR_ERROR_PATH_UNSUPPORTED: xrSuggestInteractionProfileBindings(...)
add_subdir(simple)