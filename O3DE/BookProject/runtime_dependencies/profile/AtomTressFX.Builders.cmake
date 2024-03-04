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

set(target_copy_files "C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/iconengines/qsvgicon.dll;C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qgif.dll;C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qicns.dll;C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qico.dll;C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qjpeg.dll;C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qsvg.dll;C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qtga.dll;C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qtiff.dll;C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qwbmp.dll;C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qwebp.dll;C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/platforms/qminimal.dll;C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/platforms/qwindows.dll;C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/styles/qwindowsvistastyle.dll")
set(target_target_files "C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Core.dll;C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Gui.dll;;C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.imguilib.dll;C:/O3DE/23.10.0/bin/Windows/profile/Default/./LmbrCentral.dll;")
set(target_link_files "C:/O3DE/23.10.0/bin/Windows/profile/Default/./O3DEKernel.dll;C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Core.dll;C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Gui.dll;C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Widgets.dll;C:/O3DE/23.10.0/bin/Windows/profile/Default/./AzQtComponents.dll;C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Svg.dll;C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Xml.dll;C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.imguilib.dll")
set(target_imported_files "C:/O3DE/23.10.0/bin/Windows/profile/Default/O3DEKernel.dll;C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Core.dll;C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Gui.dll;C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Widgets.dll;C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Svg.dll;C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Xml.dll;C:/O3DE/23.10.0/bin/Windows/profile/Default/AzQtComponents.dll;C:/O3DE/23.10.0/bin/Windows/profile/Default/ImGui.imguilib.dll;C:/O3DE/23.10.0/bin/Windows/profile/Default/LmbrCentral.dll;C:/O3DE/23.10.0/bin/Windows/profile/Default/AtomTressFX.Builders.dll")

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

ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/iconengines/qsvgicon.dll" "iconengines" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qgif.dll" "imageformats" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qicns.dll" "imageformats" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qico.dll" "imageformats" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qjpeg.dll" "imageformats" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qsvg.dll" "imageformats" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qtga.dll" "imageformats" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qtiff.dll" "imageformats" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qwbmp.dll" "imageformats" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qwebp.dll" "imageformats" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/platforms/qminimal.dll" "platforms" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/platforms/qwindows.dll" "platforms" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/styles/qwindowsvistastyle.dll" "styles" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./O3DEKernel.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Core.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Gui.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Widgets.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AzQtComponents.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Svg.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Xml.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.imguilib.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Core.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Gui.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.imguilib.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LmbrCentral.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./O3DEKernel.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Core.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Gui.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Widgets.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Svg.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Xml.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AzQtComponents.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.imguilib.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LmbrCentral.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomTressFX.Builders.dll" "" TARGET_FILE_DIR "C:/O3DE/23.10.0/bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")


file(TOUCH "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/runtime_dependencies/profile/AtomTressFX.Builders.stamp")
