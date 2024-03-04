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

set(target_copy_files "")
set(target_target_files "C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-auth.dll;C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-cal.dll;C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-common.dll;C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-compression.dll;C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-event-stream.dll;C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-http.dll;C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-io.dll;C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-mqtt.dll;C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-s3.dll;C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-checksums.dll;C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-core.dll;C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-crt-cpp.dll;C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-cognito-identity.dll;C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-cognito-idp.dll;C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-sts.dll;C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-identity-management.dll;;C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-dynamodb.dll;C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-lambda.dll;C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-s3.dll;C:/O3DE/23.10.0/bin/Windows/profile/Default/./AWSCore.dll;C:/O3DE/23.10.0/bin/Windows/profile/Default/./HttpRequestor.dll")
set(target_link_files "C:/O3DE/23.10.0/bin/Windows/profile/Default/./O3DEKernel.dll")
set(target_imported_files "C:/O3DE/23.10.0/bin/Windows/profile/Default/O3DEKernel.dll;C:/O3DE/23.10.0/bin/Windows/profile/Default/AWSCore.dll;C:/O3DE/23.10.0/bin/Windows/profile/Default/HttpRequestor.dll;C:/O3DE/23.10.0/bin/Windows/profile/Default/AWSClientAuth.dll")

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

ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./O3DEKernel.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-auth.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-cal.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-common.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-compression.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-event-stream.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-http.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-io.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-mqtt.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-s3.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-checksums.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-core.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-crt-cpp.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-cognito-identity.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-cognito-idp.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-sts.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-identity-management.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-dynamodb.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-lambda.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-s3.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AWSCore.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./HttpRequestor.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./O3DEKernel.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AWSCore.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./HttpRequestor.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AWSClientAuth.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")


file(TOUCH "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/runtime_dependencies/profile/AWSClientAuth.stamp")
