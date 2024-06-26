#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#
cmake_minimum_required(VERSION 3.22)

cmake_policy(SET CMP0012 NEW) # new policy for the if that evaluates a boolean out of "if(NOT ${same_location})"

cmake_path(SET target_file_dir "C:/O3DE/23.10.0/bin/Windows/profile/Default/.")

set(target_copy_files "C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysX_64.dll;C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysXCooking_64.dll;C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysXFoundation_64.dll;C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysXCommon_64.dll;C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysXDevice64.dll;C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysXGpu_64.dll")
set(target_target_files "C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.imguilib.dll;;C:/O3DE/23.10.0/bin/Windows/profile/Default/./LmbrCentral.dll;C:/Users/mrele/.o3de/3rdParty/packages/AWSGameLiftServerSDK-5.0.0-rev2-windows/AWSGameLiftServerSDK/bin/Release/aws-cpp-sdk-gamelift-server.dll;")
set(target_link_files "C:/O3DE/23.10.0/bin/Windows/profile/Default/./O3DEKernel.dll;C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.imguilib.dll")
set(target_imported_files "C:/O3DE/23.10.0/bin/Windows/profile/Default/O3DEKernel.dll;C:/O3DE/23.10.0/bin/Windows/profile/Default/ImGui.imguilib.dll;C:/O3DE/23.10.0/bin/Windows/profile/Default/LmbrCentral.dll;C:/O3DE/23.10.0/bin/Windows/profile/Default/AWSGameLift.Servers.dll")

function(ly_copy source_files relative_target_directory)
    set(options)
    set(oneValueArgs TARGET_FILE_DIR SOURCE_TYPE SOURCE_GEM_MODULE)
    set(multiValueArgs)
    cmake_parse_arguments("${CMAKE_CURRENT_FUNCTION}" "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    set(target_file_dir "${${CMAKE_CURRENT_FUNCTION}_TARGET_FILE_DIR}")
    set(source_type "${${CMAKE_CURRENT_FUNCTION}_SOURCE_TYPE}")
    set(source_is_gem "${${CMAKE_CURRENT_FUNCTION}_SOURCE_GEM_MODULE}")

    # Create the full path to the target directory
    cmake_path(APPEND target_directory "${target_file_dir}" "${relative_target_directory}")

    foreach(source_file IN LISTS source_files)
        cmake_path(GET source_file FILENAME target_filename)
        cmake_path(APPEND target_file "${target_directory}" "${target_filename}")
        cmake_path(COMPARE "${source_file}" EQUAL "${target_file}" same_location)
        if(NOT ${same_location})
            file(LOCK "${target_file}.lock" GUARD FUNCTION TIMEOUT 300)
            file(SIZE "${source_file}" source_file_size)
            if(EXISTS "${target_file}")
                file(SIZE "${target_file}" target_file_size)
            else()
                set(target_file_size 0)
            endif()
            if((NOT source_file_size EQUAL target_file_size) OR "${source_file}" IS_NEWER_THAN "${target_file}")
                message(STATUS "Copying \"${source_file}\" to \"${target_directory}\"...")
                file(MAKE_DIRECTORY "${full_target_directory}")
                file(COPY "${source_file}" DESTINATION "${target_directory}" FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE FOLLOW_SYMLINK_CHAIN)
                file(TOUCH_NOCREATE "${target_file}")
            endif()
        endif()
    endforeach()
endfunction()

ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysX_64.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysXCooking_64.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysXFoundation_64.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysXCommon_64.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysXDevice64.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysXGpu_64.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./O3DEKernel.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.imguilib.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.imguilib.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LmbrCentral.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSGameLiftServerSDK-5.0.0-rev2-windows/AWSGameLiftServerSDK/bin/Release/aws-cpp-sdk-gamelift-server.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./O3DEKernel.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.imguilib.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LmbrCentral.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AWSGameLift.Servers.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")


file(TOUCH "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/runtime_dependencies/profile/AWSGameLift.Servers.stamp")
