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

include(FetchContent)

if (NOT NO_APPSIM AND NO_ML_CAPI)
    message(FATAL_ERROR "Cannot compile for AppSim without using Magic Leap C-API")
endif()

project(xr_application_framework)

cmake_minimum_required(VERSION 3.22.1)

# Based on this var we will load different deps in LoadDependencies.cmake
if (USE_LOCAL_DEPS)
    message("Using local dependencies")
else()
    message("Using fresh dependencies")
endif()
include(../cmake/LoadDependencies.cmake)

# First setup the Vulkan headers.
# We like to use 1.3.x version so make sure those are used.
find_package(Vulkan REQUIRED)

# Add the Offical Vulkan Headers
FetchContent_Declare(
        VulkanHeaders
        URL_HASH MD5=${EXTERNAL_HASH_vulkan_headers}
        URL ${EXTERNAL_vulkan_headers})
FetchContent_MakeAvailable(VulkanHeaders)
set(Vulkan_INCLUDE_DIRS "${vulkanheaders_SOURCE_DIR}/include" CACHE INTERNAL "vulkan headers directory")
set(Vulkan_INCLUDE_DIR "${vulkanheaders_SOURCE_DIR}/include" CACHE INTERNAL "vulkan headers directory")

# Add OpenXR SDK
OPTION(USE_OPENXR_LAYERS "Use OpenXR layers" ON)
set(BUILD_ALL_EXTENSIONS ON CACHE INTERNAL "Build loader and layers with all extensions")
set(BUILD_TESTS OFF CACHE INTERNAL "Build tests")
set(BUILD_CONFORMANCE_TESTS OFF CACHE INTERNAL "Build conformance tests")
set(BUILD_API_LAYERS ${USE_OPENXR_LAYERS} CACHE INTERNAL "Use OpenXR layers")
FetchContent_Declare(
        oxr
        URL_HASH MD5=${EXTERNAL_HASH_openxr_source_sdk}
        URL ${EXTERNAL_openxr_source_sdk})

set(VMA_STATIC_VULKAN_FUNCTIONS OFF CACHE INTERNAL "Link statically with Vulkan API")
set(VMA_DYNAMIC_VULKAN_FUNCTIONS ON CACHE INTERNAL "Link statically with Vulkan API")

# Add the Vulkan Memory Manager
FetchContent_Declare(
        vmalib
        URL_HASH MD5=${EXTERNAL_HASH_vma}
        URL ${EXTERNAL_vma})

# Add STB library
FetchContent_Declare(
        stb_lib
        GIT_REPOSITORY ${EXTERNAL_stb}
        GIT_TAG ${EXTERNAL_HASH_stb}
        GIT_SHALLOW)

# Add gltf
FetchContent_Declare(
        gltf_lib
        URL_HASH MD5=${EXTERNAL_HASH_tinygltf}
        URL ${EXTERNAL_tinygltf})

set(TINYGLTF_BUILD_LOADER_EXAMPLE OFF CACHE INTERNAL "Build loader_example")

# Add im_gui
FetchContent_Declare(
        imgui_lib
        URL_HASH MD5=${EXTERNAL_HASH_imgui}
        URL ${EXTERNAL_imgui}
        PATCH_COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/patches/imgui_CMakeLists.txt CMakeLists.txt)

# Add mio_lib
FetchContent_Declare(
        mio_lib
        GIT_TAG ${EXTERNAL_HASH_mio}
        GIT_REPOSITORY ${EXTERNAL_mio}
        GIT_SHALLOW)

# MikkTSpace
FetchContent_Declare(
        mks_lib
        GIT_TAG ${EXTERNAL_HASH_MikkTSpace}
        GIT_REPOSITORY ${EXTERNAL_MikkTSpace}
        GIT_SHALLOW
        PATCH_COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/patches/mikktspace_CMakeLists.txt CMakeLists.txt)

FetchContent_MakeAvailable(oxr vmalib stb_lib gltf_lib imgui_lib mio_lib mks_lib)


add_subdirectory(resources)
set (PLATFORM_LIBRARIES)

if (NO_ML_CAPI)
    if (WIN32)
        set (ML_TARGET "win")
    endif()
    if (UNIX)
        if (APPLE)
          set (ML_TARGET "osx")
        else()
          set (ML_TARGET "linux")
        endif()
    endif()
    set(XRAF_PLATFORM NO_ML_CAPI)
else()
    file(TO_CMAKE_PATH "$ENV{MLSDK}" MLSDK)
    file(TO_CMAKE_PATH "${ANDROID_NDK}" ANDROID_NDK)
    list(APPEND CMAKE_MODULE_PATH "${MLSDK}/cmake" "${ANDROID_NDK}/../../mlsdk/cmake")

    find_package(MagicLeap REQUIRED)
    find_package(MagicLeapNativeAppGlue REQUIRED)
    find_package(MagicLeapOpenGL REQUIRED)
    set(XRAF_PLATFORM XR_USE_PLATFORM_ML)
    list(APPEND PLATFORM_LIBRARIES
        ML::audio
        ML::native_surface)
endif()


# Core Selection.
if (NO_APPSIM)
    set(XR_CORE_FILES
        src/host/XrHostCore.cpp
    )
    if (NOT ML_TARGET STREQUAL "win")
        list(APPEND PLATFORM_LIBRARIES
            dl
        )
    endif()
    set(XRAF_CORE XRAF_USE_HOST_CORE)
else()
    set(XR_CORE_FILES
        src/device/XrAndroidCore.cpp
    )
    list(APPEND PLATFORM_LIBRARIES
        native_app_glue
        gl.magicleap
    )

    if (ML_TARGET STREQUAL ml2)
        set(XRAF_CORE XRAF_USE_ANDROID_CORE)
    else()
        set(XRAF_CORE XRAF_USE_APPSIM_CORE)
        list(APPEND PLATFORM_LIBRARIES
            zi.magicleap
        )
        list(APPEND XR_CORE_FILES
            src/host/XrAppSimCore.cpp
        )
    endif()
endif()


# Target dependent functionality selection
if (ML_TARGET STREQUAL ml2)
    set(XR_DEFINES XR_USE_PLATFORM_ANDROID XR_USE_GRAPHICS_API_OPENGL_ES XR_USE_TIMESPEC)
    set(PLATFORM_SOURCES
            src/Extensions/KhrConvertTimeSpec.cpp
            src/device/AndroidAssetManager.cpp
            src/device/IntentHelper.cpp
            src/device/SystemHelper.cpp
            src/device/WebRequest.cpp
            )
elseif (ML_TARGET STREQUAL win)
    set(XR_DEFINES XR_USE_PLATFORM_WIN32 XR_USE_GRAPHICS_API_VULKAN)
    set(PLATFORM_SOURCES
            src/host/HostAssetManager.cpp
            src/host/IntentHelper.cpp
            src/host/SystemHelper.cpp
            src/host/WebRequest.cpp
            )

else ()
    set(XR_DEFINES XR_USE_PLATFORM_XCB XR_USE_GRAPHICS_API_OPENGL)
    set(PLATFORM_SOURCES
            src/host/HostAssetManager.cpp
            src/host/IntentHelper.cpp
            src/host/SystemHelper.cpp
            src/host/WebRequest.cpp
    )
endif ()

add_library(xr_app_framework STATIC
        src/Application.cpp
        src/GuiBackend.cpp
        src/Implementation.cpp
        src/IXrMLGraphicsDevice.cpp
        src/Linear.cpp
        src/XrCore.cpp
        src/XrMLGraphicsDeviceOpenGLES.cpp
        src/XrMLGraphicsDeviceVulkan.cpp
        src/XrMLSceneGraphGraphicsDeviceVulkan.cpp
        src/XrMLSwapChain.cpp
        src/XrReflection.cpp
        src/Components/Console.cpp
        src/Components/GLTF.cpp
        src/Components/GLTFAnimation.cpp
        src/Components/Mesh.cpp
        src/Components/NativeSurfaceTexture.cpp
        src/Components/Sound.cpp
        src/Extensions/ExtEyeGaze.cpp
        src/Extensions/ExtHandInteraction.cpp
        src/Extensions/ExtHandTracking.cpp
        src/Extensions/ExtPalmPose.cpp
        src/Extensions/ExtPlaneDetection.cpp
        src/Extensions/MLCompat.cpp
        src/Extensions/MLFrameEndInfoExt.cpp
        src/Extensions/MLGlobalDimmer.cpp
        src/Extensions/MLMarkerTracking.cpp
        src/Extensions/MLSystemNotifications.cpp
        src/Extensions/MLUserCalibration.cpp
        src/Extensions/XrKHRVulkanEnable.cpp
        src/Extensions/XrKHRVulkanEnable2.cpp
        src/Scene/HitTest.cpp
        src/Scene/Node.cpp
        src/Utils/PermissionHelper.cpp
        src/Utils/StructNextChain.cpp
        ${PLATFORM_SOURCES}
        ${XR_CORE_FILES}
        src/vulkan/AndroidHwBufferHelper.cpp
        src/vulkan/Buffer.cpp
        src/vulkan/CommandBuffers.cpp
        src/vulkan/ImageBuffer.cpp
        src/vulkan/ImmutableYcbcrSampler.cpp
        src/vulkan/MaterialDescriptorSet.cpp
        src/vulkan/NativeImageBuffer.cpp
        src/vulkan/RenderPass.cpp
        src/vulkan/RenderTarget.cpp
        src/vulkan/ShaderModule.cpp
        src/vulkan/SwapChain.cpp
        src/vulkan/TextureDescriptorPool.cpp
        src/vulkan/UBO.cpp
        src/vulkan/VulkanGui.cpp
        )


target_link_libraries(xr_app_framework PUBLIC
        openxr_loader
        xr_app_framework_resources
        ${Vulkan_LIBRARIES}
        Vulkan::Headers
        mikktspace
        imgui
        ${PLATFORM_LIBRARIES}
        )

if (NOT CMAKE_BUILD_TYPE)
    SET(XR_APP_FRAMEWORK_BUILD_TYPE Debug)
else()
    if (CMAKE_BUILD_TYPE STREQUAL Release)
        SET(XR_APP_FRAMEWORK_BUILD_TYPE Release)
    else()
        SET(XR_APP_FRAMEWORK_BUILD_TYPE Debug)
    endif()
endif()

if (ML_TARGET STREQUAL ml2)
    target_compile_options(xr_app_framework PUBLIC -Wno-pragmas -fPIC)
elseif (ML_TARGET STREQUAL win)
    target_compile_options(xr_app_framework PUBLIC -fPIC)
else ()
    target_compile_options(xr_app_framework PUBLIC -Wno-pragmas -fPIC)
endif ()

if (XR_APP_FRAMEWORK_BUILD_TYPE STREQUAL Release)
    target_compile_options(xr_app_framework PUBLIC -O3)
else()
    target_compile_options(xr_app_framework PUBLIC -g)
endif()

target_compile_options(xr_app_framework PRIVATE -Wall)

if (ML_TARGET STREQUAL win)
    target_compile_features(xr_app_framework PRIVATE cxx_std_20)
else ()
    target_compile_features(xr_app_framework PRIVATE cxx_std_17)
endif ()

if (ML_TARGET STREQUAL ml2)
    target_compile_definitions(xr_app_framework PUBLIC ${XR_DEFINES} XR_USE_GRAPHICS_API_VULKAN VULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1 VK_USE_PLATFORM_ANDROID_KHR=1 ${XRAF_CORE} ${XRAF_PLATFORM})
else ()
    target_compile_definitions(xr_app_framework PUBLIC ${XR_DEFINES} XR_USE_GRAPHICS_API_VULKAN VULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1 ${XRAF_CORE} ${XRAF_PLATFORM})
endif()
target_include_directories(xr_app_framework PUBLIC include "${Vulkan_INCLUDE_DIR}" "${vmalib_SOURCE_DIR}/include" "${stb_lib_SOURCE_DIR}" "${gltf_lib_SOURCE_DIR}" "${mio_lib_SOURCE_DIR}/single_include/")
