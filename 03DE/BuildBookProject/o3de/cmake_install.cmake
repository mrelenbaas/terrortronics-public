# Install script for directory: C:/O3DE/23.10.0

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "profile")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    set(install_output_folder "${CMAKE_INSTALL_PREFIX}/bin/Windows/${CMAKE_INSTALL_CONFIG_NAME}/Default")
    set(install_pak_output_folder "${install_output_folder}/Cache/pc")
    set(runtime_output_directory_RELEASE )
    if(NOT DEFINED LY_ASSET_DEPLOY_ASSET_TYPE)
        set(LY_ASSET_DEPLOY_ASSET_TYPE pc)
    endif()
    message(STATUS "Generating ${install_pak_output_folder}/engine.pak from C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Cache/${LY_ASSET_DEPLOY_ASSET_TYPE}")
    file(MAKE_DIRECTORY "${install_pak_output_folder}")
    cmake_path(SET cache_product_path "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Cache/${LY_ASSET_DEPLOY_ASSET_TYPE}")
    # Copy the generated cmake_dependencies.*.setreg files for loading gems in non-monolithic to the cache
    file(GLOB gem_source_paths_setreg "${runtime_output_directory_RELEASE}/Registry/*.setreg")
    # The MergeSettingsToRegistry_TargetBuildDependencyRegistry function looks for lowercase "registry" directory
    file(MAKE_DIRECTORY "${cache_product_path}/registry")
    file(COPY ${gem_source_paths_setreg} DESTINATION "${cache_product_path}/registry")

    file(GLOB product_assets "${cache_product_path}/*")
    list(APPEND pak_artifacts ${product_assets})
    if(pak_artifacts)
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E tar "cf" "${install_pak_output_folder}/engine.pak" --format=zip -- ${pak_artifacts}
            WORKING_DIRECTORY "${cache_product_path}"
            RESULT_VARIABLE archive_creation_result
        )
        if(archive_creation_result EQUAL 0)
            message(STATUS "${install_output_folder}/engine.pak generated")
        endif()
    endif()

    # Remove copied .setreg files from the Cache directory
    unset(artifacts_to_remove)
    foreach(gem_source_path_setreg IN LISTS gem_source_paths_setreg)
        cmake_path(GET gem_source_path_setreg FILENAME setreg_filename)
        list(APPEND artifacts_to_remove "${cache_product_path}/registry/${setreg_filename}")
    endforeach()
    if (artifacts_to_remove)
        file(REMOVE ${artifacts_to_remove})
    endif()
endif()

endif()

endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Framework/AtomCore/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Framework/AzCore/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Framework/AzQtComponents/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Framework/AzFramework/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Framework/AzGameFramework/AzGameFramework/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Framework/AzTest/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Framework/AzToolsFramework/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Framework/AzNetworking/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/LauncherUnified/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Legacy/CryCommon/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Legacy/CrySystem/XML/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Legacy/CrySystem/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Editor/Plugins/EditorCommon/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Editor/Plugins/ComponentEntityEditorPlugin/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Editor/Plugins/FFMPEGPlugin/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Editor/Plugins/ProjectSettingsTool/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Editor/Plugins/PerforcePlugin/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Editor/Plugins/EditorAssetImporter/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Editor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Tools/SceneAPI/SceneBuilder/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Tools/SceneAPI/SceneCore/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Tools/SceneAPI/SceneData/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Tools/SceneAPI/SceneUI/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Tools/SceneAPI/SDKWrapper/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Tools/AssetProcessor/AssetBuilderSDK/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Tools/AssetProcessor/AssetBuilder/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Tools/AssetProcessor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Tools/AWSNativeSDKInit/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Tools/AzTestRunner/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Tools/CrashHandler/Support/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Tools/CrashHandler/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Tools/CrashHandler/Tools/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Tools/PythonBindingsExample/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Tools/RemoteConsole/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Tools/DeltaCataloger/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Tools/SerializeContextTools/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Tools/AssetBundler/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Tools/LuaIDE/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Code/Tools/ProjectManager/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Atom/RHI/DX12/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Atom/RHI/Metal/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Atom/RHI/Vulkan/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Atom/RHI/Null/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Atom/RHI/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Atom/RPI/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Atom/Bootstrap/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Atom/Asset/Shader/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/AtomLyIntegration/AtomViewportDisplayInfo/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Camera/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/LmbrCentral/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/ImGui/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Atom/Feature/Common/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/SurfaceData/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Atom/Asset/ImageProcessingAtom/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/GradientSignal/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/GraphCanvas/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/GraphModel/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Atom/Tools/AtomToolsFramework/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/AtomLyIntegration/CommonFeatures/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/AtomLyIntegration/EditorModeFeedback/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Maestro/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/SceneProcessing/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Achievements/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Compression/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Archive/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/AssetValidation/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Atom/Component/DebugCamera/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Atom/Tools/MaterialCanvas/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Atom/Tools/MaterialEditor/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Atom/Tools/PassCanvas/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Atom/Tools/ShaderManagementConsole/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/AtomLyIntegration/ImguiAtom/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/AtomLyIntegration/AtomImGuiTools/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/EMotionFX/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/AtomLyIntegration/EMotionFXAtom/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/AtomLyIntegration/AtomFont/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/AtomLyIntegration/AtomViewportDisplayIcons/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/AtomLyIntegration/AtomBridge/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Atom/Utils/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/EditorPythonBindings/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/QtForPython/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/AudioSystem/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/AWSCore/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/HttpRequestor/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/AWSClientAuth/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/AWSGameLift/Code/AWSGameLiftClient/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/AWSGameLift/Code/AWSGameLiftServer/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/AWSMetrics/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/BarrierInput/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/CameraFramework/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/CertificateManager/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/CrashReporting/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/CustomAssetExample/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/DebugDraw/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/DiffuseProbeGrid/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/ExpressionEvaluation/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/FastNoise/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/GameState/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/LocalUser/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/TextureAtlas/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/LyShine/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/SaveData/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/MessagePopup/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/LyShineExamples/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/GameStateSamples/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Gestures/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/InAppPurchases/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/LandscapeCanvas/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Metastream/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Microphone/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/MotionMatching/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Multiplayer/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/ScriptEvents/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/ScriptCanvas/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Multiplayer/Multiplayer_ScriptCanvas/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/MultiplayerCompression/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/NvCloth/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/PhysX/Code/NumericalMethods/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/PhysX/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/PhysXDebug/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Presence/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Profiler/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/PythonAssetBuilder/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/RecastNavigation/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/RemoteTools/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/SceneLoggingExample/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/ScriptAutomation/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/ScriptCanvasDeveloper/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/ScriptCanvasPhysics/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/ScriptCanvasTesting/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/ScriptedEntityTweener/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/SliceFavorites/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Stars/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/StartingPointCamera/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/StartingPointInput/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/StartingPointMovement/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Streamer/StreamerProfiler/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Terrain/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/TestAssetBuilder/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/TickBusOrderViewer/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Twitch/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/Vegetation/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/VideoPlaybackFramework/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/VirtualGamepad/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/Gems/WhiteBox/Code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/DX12-e750182c/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Metal-6545c5f9/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Vulkan-d8dd7abf/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Null-3dfa7e40/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/RHI-76a22ad2/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/RPI-63d498e4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Bootstrap-6eca9b85/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Shader-a293eb3a/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/AtomViewportDisplayInfo-708c9402/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Camera-13d17e63/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/LmbrCentral-44cddad6/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/ImGui-00ca01a4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Common-fa950a7d/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/SurfaceData-1619ea4b/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/ImageProcessingAtom-ba2c1ce8/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/GradientSignal-cca9f827/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/GraphCanvas-2ecd3b13/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/GraphModel-f8a17b5e/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/AtomToolsFramework-a636e8fa/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/CommonFeatures-75772729/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/EditorModeFeedback-4343b472/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Maestro-22276045/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/PrefabBuilder-39d8b875/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/SceneProcessing-c72397c2/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Achievements-9f4a0fe0/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Compression-a56cc1b8/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Archive-2f894dde/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/AssetValidation-79878db3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/DebugCamera-7001b38b/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/MaterialCanvas-1de068c0/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/MaterialEditor-e50e397b/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/PassCanvas-da6173d5/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/ShaderManagementConsole-17c9ff95/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/ImguiAtom-17d56c81/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/AtomImGuiTools-ae119da0/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/EMotionFX-f9272c96/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/EMotionFXAtom-f6b16c74/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/AtomFont-536c68e5/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/AtomViewportDisplayIcons-fa4b3b43/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/AtomBridge-7a283318/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Atom-3e57dccd/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Sponza-22efb8c8/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/ReferenceMaterials-7d95bcdd/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/AtomContent-c97c9f3d/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/TestData-3a7003c5/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/AtomLyIntegration-d96d9f24/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/EditorPythonBindings-0f791cec/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/QtForPython-77c0f22f/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/DccScriptingInterface-493693f4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/AtomTressFX-525b143f/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/AudioSystem-864c30e4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/AudioEngineWwise-f2ddb3a8/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/AWSCore-b1a2fb9d/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/HttpRequestor-cc1aa552/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/AWSClientAuth-4555e3c9/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/AWSGameLift-ffa06df1/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/AWSMetrics-e95b1365/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/BarrierInput-f9a44ed0/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/CameraFramework-1f181aa9/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/CertificateManager-356a8ea9/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/CrashReporting-06bd7a23/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/CustomAssetExample-13bf8a10/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/DebugDraw-1f2c2e47/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/DevTextures-00fa9d1a/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/DiffuseProbeGrid-c9c65032/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/ExpressionEvaluation-85e9b8d6/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/FastNoise-6f45dfc6/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/GameState-4aed26ab/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/LocalUser-dfe8c871/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/TextureAtlas-0aadf95a/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/UiBasics-2ec503ed/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/LyShine-b7a3e19d/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/SaveData-33659190/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/MessagePopup-b91d52e7/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/LyShineExamples-f376ecf3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/GameStateSamples-554f2157/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Gestures-a0e7b96f/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/InAppPurchases-4be3c57b/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/LandscapeCanvas-449b1aab/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Metastream-119dca8e/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Microphone-cc6f408d/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/MotionMatching-7d8dbc58/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Multiplayer-ea78d252/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/ScriptEvents-da33bfde/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/ScriptCanvas-edafb2c3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Multiplayer_ScriptCanvas-97afcaa7/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/MultiplayerCompression-42464e05/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/NvCloth-599d590f/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/PhysX-560586c4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/PhysXDebug-48c04950/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Presence-7ec60339/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/PrimitiveAssets-db789af3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Profiler-ff39a628/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/PythonAssetBuilder-2797988d/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/RecastNavigation-fa8532bb/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/RemoteTools-1460b2d6/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/SceneLoggingExample-31639178/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/ScriptAutomation-b35ac4ca/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/ScriptCanvasDeveloper-3166a1c1/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/ScriptCanvasPhysics-210a43bc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/ScriptCanvasTesting-352cd43f/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/ScriptedEntityTweener-12049373/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/SliceFavorites-bf5ad279/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Stars-fbbf660a/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/StartingPointCamera-8c7663ae/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/StartingPointInput-dd9c33aa/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/StartingPointMovement-3c70e206/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Streamer-af536474/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/StreamerProfiler-27baf197/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Terrain-f58d84fd/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/TestAssetBuilder-ce739dec/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/TickBusOrderViewer-8c81575f/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Twitch-40abe477/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Vegetation-a1c6f1ad/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/VideoPlaybackFramework-fc51379e/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/VirtualGamepad-bec8bd97/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/WhiteBox-780e5b81/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/BookProject-433ee658/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/Gem-34bae4f8/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/External/MyGem-c19403bc/cmake_install.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Bootstrap/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Bootstrap/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Bootstrap/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Bootstrap/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Bootstrap/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Bootstrap/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomViewportDisplayInfo/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/AtomViewportDisplayInfo/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomViewportDisplayInfo/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/AtomViewportDisplayInfo/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomViewportDisplayInfo/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/AtomViewportDisplayInfo/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Camera/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Camera/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Camera/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Camera/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Camera/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Camera/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LmbrCentral/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/LmbrCentral/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LmbrCentral/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/LmbrCentral/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LmbrCentral/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/LmbrCentral/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ImGui/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ImGui/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ImGui/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ImGui/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ImGui/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ImGui/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SurfaceData/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/SurfaceData/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SurfaceData/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/SurfaceData/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SurfaceData/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/SurfaceData/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GradientSignal/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/GradientSignal/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GradientSignal/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/GradientSignal/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GradientSignal/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/GradientSignal/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GraphCanvas/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/GraphCanvas/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GraphCanvas/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/GraphCanvas/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GraphCanvas/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/GraphCanvas/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GraphModel/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/GraphModel/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GraphModel/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/GraphModel/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GraphModel/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/GraphModel/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/AtomToolsFramework/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Tools/AtomToolsFramework/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/AtomToolsFramework/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Tools/AtomToolsFramework/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/AtomToolsFramework/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Tools/AtomToolsFramework/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/CommonFeatures/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/CommonFeatures/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/CommonFeatures/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/CommonFeatures/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/CommonFeatures/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/CommonFeatures/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/EditorModeFeedback/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/EditorModeFeedback/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/EditorModeFeedback/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/EditorModeFeedback/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/EditorModeFeedback/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/EditorModeFeedback/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Maestro/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Maestro/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Maestro/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Maestro/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Maestro/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Maestro/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SceneProcessing/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/SceneProcessing/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SceneProcessing/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/SceneProcessing/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SceneProcessing/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/SceneProcessing/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Achievements/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Achievements/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Achievements/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Achievements/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Achievements/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Achievements/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Compression/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Compression/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Compression/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Compression/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Compression/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Compression/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Archive/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Archive/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Archive/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Archive/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Archive/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Archive/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AssetValidation/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AssetValidation/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AssetValidation/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AssetValidation/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AssetValidation/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AssetValidation/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialCanvas/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Tools/MaterialCanvas/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialCanvas/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Tools/MaterialCanvas/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialCanvas/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Tools/MaterialCanvas/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialEditor/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Tools/MaterialEditor/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialEditor/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Tools/MaterialEditor/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialEditor/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Tools/MaterialEditor/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/PassCanvas/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Tools/PassCanvas/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/PassCanvas/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Tools/PassCanvas/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/PassCanvas/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Tools/PassCanvas/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/ShaderManagementConsole/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Tools/ShaderManagementConsole/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/ShaderManagementConsole/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Tools/ShaderManagementConsole/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/ShaderManagementConsole/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Tools/ShaderManagementConsole/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/EMotionFX/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/EMotionFX/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/EMotionFX/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/EMotionFX/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/EMotionFX/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/EMotionFX/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomBridge/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/AtomBridge/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomBridge/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/AtomBridge/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomBridge/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/AtomBridge/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/EditorPythonBindings/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/EditorPythonBindings/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/EditorPythonBindings/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/EditorPythonBindings/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/EditorPythonBindings/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/EditorPythonBindings/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/QtForPython/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/QtForPython/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/QtForPython/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/QtForPython/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/QtForPython/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/QtForPython/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AudioSystem/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AudioSystem/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AudioSystem/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AudioSystem/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AudioSystem/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AudioSystem/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSCore/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AWSCore/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSCore/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AWSCore/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSCore/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AWSCore/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/HttpRequestor/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/HttpRequestor/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/HttpRequestor/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/HttpRequestor/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/HttpRequestor/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/HttpRequestor/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSClientAuth/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AWSClientAuth/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSClientAuth/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AWSClientAuth/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSClientAuth/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AWSClientAuth/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSGameLift/Code/AWSGameLiftClient" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AWSGameLift/Code/AWSGameLiftClient/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSGameLift/Code/AWSGameLiftClient/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AWSGameLift/Code/AWSGameLiftClient/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSGameLift/Code/AWSGameLiftClient/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AWSGameLift/Code/AWSGameLiftClient/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSMetrics/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AWSMetrics/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSMetrics/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AWSMetrics/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSMetrics/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AWSMetrics/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/BarrierInput/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/BarrierInput/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/BarrierInput/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/BarrierInput/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/BarrierInput/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/BarrierInput/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CameraFramework/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/CameraFramework/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CameraFramework/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/CameraFramework/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CameraFramework/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/CameraFramework/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CertificateManager/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/CertificateManager/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CertificateManager/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/CertificateManager/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CertificateManager/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/CertificateManager/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CrashReporting/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/CrashReporting/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CrashReporting/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/CrashReporting/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CrashReporting/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/CrashReporting/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CustomAssetExample/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/CustomAssetExample/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CustomAssetExample/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/CustomAssetExample/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CustomAssetExample/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/CustomAssetExample/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/DebugDraw/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/DebugDraw/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/DebugDraw/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/DebugDraw/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/DebugDraw/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/DebugDraw/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/DiffuseProbeGrid/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/DiffuseProbeGrid/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/DiffuseProbeGrid/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/DiffuseProbeGrid/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/DiffuseProbeGrid/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/DiffuseProbeGrid/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ExpressionEvaluation/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ExpressionEvaluation/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ExpressionEvaluation/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ExpressionEvaluation/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ExpressionEvaluation/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ExpressionEvaluation/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/FastNoise/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/FastNoise/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/FastNoise/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/FastNoise/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/FastNoise/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/FastNoise/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GameState/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/GameState/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GameState/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/GameState/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GameState/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/GameState/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LocalUser/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/LocalUser/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LocalUser/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/LocalUser/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LocalUser/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/LocalUser/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/TextureAtlas/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/TextureAtlas/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/TextureAtlas/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/TextureAtlas/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/TextureAtlas/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/TextureAtlas/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LyShine/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/LyShine/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LyShine/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/LyShine/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LyShine/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/LyShine/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SaveData/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/SaveData/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SaveData/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/SaveData/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SaveData/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/SaveData/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/MessagePopup/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/MessagePopup/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/MessagePopup/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/MessagePopup/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/MessagePopup/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/MessagePopup/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LyShineExamples/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/LyShineExamples/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LyShineExamples/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/LyShineExamples/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LyShineExamples/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/LyShineExamples/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GameStateSamples/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/GameStateSamples/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GameStateSamples/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/GameStateSamples/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GameStateSamples/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/GameStateSamples/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Gestures/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Gestures/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Gestures/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Gestures/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Gestures/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Gestures/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/InAppPurchases/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/InAppPurchases/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/InAppPurchases/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/InAppPurchases/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/InAppPurchases/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/InAppPurchases/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LandscapeCanvas/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/LandscapeCanvas/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LandscapeCanvas/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/LandscapeCanvas/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LandscapeCanvas/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/LandscapeCanvas/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Metastream/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Metastream/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Metastream/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Metastream/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Metastream/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Metastream/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Microphone/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Microphone/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Microphone/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Microphone/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Microphone/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Microphone/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/MotionMatching/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/MotionMatching/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/MotionMatching/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/MotionMatching/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/MotionMatching/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/MotionMatching/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Multiplayer/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Multiplayer/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Multiplayer/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Multiplayer/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Multiplayer/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Multiplayer/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptEvents/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptEvents/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptEvents/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptEvents/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptEvents/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptEvents/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvas/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptCanvas/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvas/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptCanvas/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvas/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptCanvas/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Multiplayer/Multiplayer_ScriptCanvas/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Multiplayer/Multiplayer_ScriptCanvas/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Multiplayer/Multiplayer_ScriptCanvas/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Multiplayer/Multiplayer_ScriptCanvas/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Multiplayer/Multiplayer_ScriptCanvas/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Multiplayer/Multiplayer_ScriptCanvas/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/MultiplayerCompression/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/MultiplayerCompression/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/MultiplayerCompression/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/MultiplayerCompression/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/MultiplayerCompression/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/MultiplayerCompression/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/NvCloth/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/NvCloth/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/NvCloth/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/NvCloth/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/NvCloth/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/NvCloth/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PhysX/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/PhysX/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PhysX/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/PhysX/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PhysX/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/PhysX/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PhysXDebug/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/PhysXDebug/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PhysXDebug/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/PhysXDebug/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PhysXDebug/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/PhysXDebug/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Presence/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Presence/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Presence/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Presence/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Presence/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Presence/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Profiler/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Profiler/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Profiler/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Profiler/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Profiler/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Profiler/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PythonAssetBuilder/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/PythonAssetBuilder/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PythonAssetBuilder/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/PythonAssetBuilder/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PythonAssetBuilder/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/PythonAssetBuilder/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/RecastNavigation/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/RecastNavigation/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/RecastNavigation/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/RecastNavigation/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/RecastNavigation/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/RecastNavigation/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/RemoteTools/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/RemoteTools/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/RemoteTools/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/RemoteTools/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/RemoteTools/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/RemoteTools/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SceneLoggingExample/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/SceneLoggingExample/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SceneLoggingExample/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/SceneLoggingExample/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SceneLoggingExample/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/SceneLoggingExample/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptAutomation/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptAutomation/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptAutomation/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptAutomation/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptAutomation/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptAutomation/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvasDeveloper/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptCanvasDeveloper/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvasDeveloper/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptCanvasDeveloper/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvasDeveloper/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptCanvasDeveloper/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvasPhysics/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptCanvasPhysics/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvasPhysics/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptCanvasPhysics/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvasPhysics/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptCanvasPhysics/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvasTesting/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptCanvasTesting/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvasTesting/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptCanvasTesting/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvasTesting/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptCanvasTesting/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptedEntityTweener/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptedEntityTweener/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptedEntityTweener/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptedEntityTweener/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptedEntityTweener/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptedEntityTweener/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SliceFavorites/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/SliceFavorites/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SliceFavorites/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/SliceFavorites/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SliceFavorites/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/SliceFavorites/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Stars/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Stars/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Stars/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Stars/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Stars/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Stars/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/StartingPointCamera/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/StartingPointCamera/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/StartingPointCamera/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/StartingPointCamera/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/StartingPointCamera/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/StartingPointCamera/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/StartingPointInput/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/StartingPointInput/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/StartingPointInput/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/StartingPointInput/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/StartingPointInput/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/StartingPointInput/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/StartingPointMovement/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/StartingPointMovement/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/StartingPointMovement/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/StartingPointMovement/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/StartingPointMovement/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/StartingPointMovement/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Streamer/StreamerProfiler/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Streamer/StreamerProfiler/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Streamer/StreamerProfiler/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Streamer/StreamerProfiler/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Streamer/StreamerProfiler/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Streamer/StreamerProfiler/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Terrain/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Terrain/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Terrain/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Terrain/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Terrain/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Terrain/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/TestAssetBuilder/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/TestAssetBuilder/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/TestAssetBuilder/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/TestAssetBuilder/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/TestAssetBuilder/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/TestAssetBuilder/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/TickBusOrderViewer/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/TickBusOrderViewer/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/TickBusOrderViewer/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/TickBusOrderViewer/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/TickBusOrderViewer/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/TickBusOrderViewer/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Twitch/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Twitch/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Twitch/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Twitch/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Twitch/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Twitch/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Vegetation/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Vegetation/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Vegetation/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Vegetation/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Vegetation/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Vegetation/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/VideoPlaybackFramework/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/VideoPlaybackFramework/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/VideoPlaybackFramework/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/VideoPlaybackFramework/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/VideoPlaybackFramework/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/VideoPlaybackFramework/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/VirtualGamepad/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/VirtualGamepad/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/VirtualGamepad/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/VirtualGamepad/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/VirtualGamepad/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/VirtualGamepad/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/WhiteBox/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/WhiteBox/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/WhiteBox/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/WhiteBox/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/WhiteBox/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/WhiteBox/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT_PROFILE" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Pp][Rr][Oo][Ff][Ii][Ll][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/Windows/profile/Default/." TYPE EXECUTABLE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/BookProject.GameLauncher.exe")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT_PROFILE" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Pp][Rr][Oo][Ff][Ii][Ll][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/./Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/./Platform/Windows/Default/BookProject.GameLauncher_profile.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT_PROFILE" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Pp][Rr][Oo][Ff][Ii][Ll][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/Windows/profile/Default/." TYPE EXECUTABLE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/BookProject.ServerLauncher.exe")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT_PROFILE" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Pp][Rr][Oo][Ff][Ii][Ll][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/./Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/./Platform/Windows/Default/BookProject.ServerLauncher_profile.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT_PROFILE" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Pp][Rr][Oo][Ff][Ii][Ll][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/Windows/profile/Default/." TYPE EXECUTABLE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/BookProject.UnifiedLauncher.exe")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT_PROFILE" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Pp][Rr][Oo][Ff][Ii][Ll][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/./Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/./Platform/Windows/Default/BookProject.UnifiedLauncher_profile.cmake")
  endif()
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/./CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/./Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/./Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/./Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/./Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Prefab/PrefabBuilder" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Prefab/PrefabBuilder/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Prefab/PrefabBuilder/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Prefab/PrefabBuilder/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Prefab/PrefabBuilder/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Prefab/PrefabBuilder/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/Sponza" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomContent/Sponza/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/Sponza/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomContent/Sponza/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/Sponza/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomContent/Sponza/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/ReferenceMaterials" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomContent/ReferenceMaterials/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/ReferenceMaterials/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomContent/ReferenceMaterials/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/ReferenceMaterials/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomContent/ReferenceMaterials/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomContent/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomContent/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomContent/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/TestData" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomContent/TestData/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/TestData/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomContent/TestData/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/TestData/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomContent/TestData/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomTressFX" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomTressFX/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomTressFX/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomTressFX/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomTressFX/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomTressFX/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/DevTextures" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/DevTextures/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/DevTextures/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/DevTextures/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/DevTextures/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/DevTextures/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/UiBasics" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/UiBasics/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/UiBasics/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/UiBasics/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/UiBasics/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/UiBasics/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PrimitiveAssets" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/PrimitiveAssets/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PrimitiveAssets/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/PrimitiveAssets/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PrimitiveAssets/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/PrimitiveAssets/Platform/Windows/Default/permutation.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT_PROFILE" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Pp][Rr][Oo][Ff][Ii][Ll][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Windows/profile/Default" TYPE STATIC_LIBRARY MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/lib/profile/BookProject.Private.Object.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT_PROFILE" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Pp][Rr][Oo][Ff][Ii][Ll][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/Gem/./Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/External/Gem/./Platform/Windows/Default/BookProject.Private.Object_profile.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT_PROFILE" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Pp][Rr][Oo][Ff][Ii][Ll][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/Windows/profile/Default/." TYPE MODULE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/BookProject.dll")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT_PROFILE" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Pp][Rr][Oo][Ff][Ii][Ll][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/Gem/./Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/External/Gem/./Platform/Windows/Default/BookProject_profile.cmake")
  endif()
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/Gem/." TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/External/Gem/./CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/Gem/./Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/External/Gem/./Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/Gem/./Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/External/Gem/./Platform/Windows/Default/permutation.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT_PROFILE" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Pp][Rr][Oo][Ff][Ii][Ll][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/MyGem/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/External/MyGem/Code/Platform/Windows/Default/MyGem.API_profile.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT_PROFILE" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Pp][Rr][Oo][Ff][Ii][Ll][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Windows/profile/Default" TYPE STATIC_LIBRARY MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/lib/profile/MyGem.Private.Object.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT_PROFILE" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Pp][Rr][Oo][Ff][Ii][Ll][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/MyGem/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/External/MyGem/Code/Platform/Windows/Default/MyGem.Private.Object_profile.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT_PROFILE" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Pp][Rr][Oo][Ff][Ii][Ll][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/Windows/profile/Default/." TYPE MODULE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/MyGem.dll")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT_PROFILE" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Pp][Rr][Oo][Ff][Ii][Ll][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/MyGem/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/External/MyGem/Code/Platform/Windows/Default/MyGem_profile.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT_PROFILE" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Pp][Rr][Oo][Ff][Ii][Ll][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/MyGem/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/External/MyGem/Code/Platform/Windows/Default/MyGem.Editor.API_profile.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT_PROFILE" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Pp][Rr][Oo][Ff][Ii][Ll][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Windows/profile/Default" TYPE STATIC_LIBRARY MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/lib/profile/MyGem.Editor.Private.Object.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT_PROFILE" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Pp][Rr][Oo][Ff][Ii][Ll][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/MyGem/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/External/MyGem/Code/Platform/Windows/Default/MyGem.Editor.Private.Object_profile.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT_PROFILE" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Pp][Rr][Oo][Ff][Ii][Ll][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/Windows/profile/Default/." TYPE MODULE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/MyGem.Editor.dll")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT_PROFILE" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Pp][Rr][Oo][Ff][Ii][Ll][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/MyGem/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/External/MyGem/Code/Platform/Windows/Default/MyGem.Editor_profile.cmake")
  endif()
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/MyGem/Code" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/External/MyGem/Code/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/MyGem/Code/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/External/MyGem/Code/Platform/Windows/platform_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/MyGem/Code/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/External/MyGem/Code/Platform/Windows/Default/permutation.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/cmake" REGEX "/\\_\\_pycache\\_\\_$" EXCLUDE REGEX "/findo3de\\.cmake$" EXCLUDE REGEX "/cmake\\/configurationtypes\\.cmake$" EXCLUDE REGEX "3rdparty/platform/.*/builtinpackages_.*.cmake" EXCLUDE)
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/cmake/install/ConfigurationTypes.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT_PROFILE" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Pp][Rr][Oo][Ff][Ii][Ll][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/cmake/Platform/Windows/Default/ConfigurationTypes_profile.cmake")
  endif()
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE MESSAGE_NEVER FILES
    "C:/O3DE/23.10.0/CMakeLists.txt"
    "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/cmake/engine.json"
    )
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/cmake/Findo3de.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/cmake/Platform/Windows/Default/o3de_subdirectories_windows.cmake")
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake/3rdParty/Platform/Windows" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/cmake/3rdParty/Platform/Windows/BuiltInPackages_windows.cmake")
endif()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake/3rdParty/Platform/Windows/Default" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/cmake/3rdParty/Platform/Windows/Default/BuiltInPackages_windows.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT_PROFILE" OR NOT CMAKE_INSTALL_COMPONENT)
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
                cmake_path(APPEND full_target_directory "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}" "${target_directory}")
                cmake_path(APPEND target_file "${full_target_directory}" "${target_filename}")
                if("${source_file}" IS_NEWER_THAN "${target_file}")
                    message(STATUS "Copying ${source_file} to ${full_target_directory}...")
                    file(COPY "${source_file}" DESTINATION "${full_target_directory}" FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE FOLLOW_SYMLINK_CHAIN)
                    file(TOUCH_NOCREATE "${target_file}")
                endif()
            endforeach()
        endfunction()

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEFAULT_PROFILE" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Pp][Rr][Oo][Ff][Ii][Ll][Ee])$")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./O3DEKernel.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/iconengines/qsvgicon.dll" "iconengines" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qgif.dll" "imageformats" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qicns.dll" "imageformats" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qico.dll" "imageformats" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qjpeg.dll" "imageformats" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qsvg.dll" "imageformats" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qtga.dll" "imageformats" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qtiff.dll" "imageformats" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qwbmp.dll" "imageformats" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qwebp.dll" "imageformats" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/platforms/qminimal.dll" "platforms" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/platforms/qwindows.dll" "platforms" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/styles/qwindowsvistastyle.dll" "styles" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Core.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Gui.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Widgets.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Gui.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Core.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Svg.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Xml.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./O3DEKernel.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Core.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Gui.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Widgets.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Svg.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Xml.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AzQtComponents.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Svg.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Widgets.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AzQtComponents.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AzQtComponents.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./O3DEQtControlGallery.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ReflectedPropertyEditorStandalone.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./DPEDebugViewStandalone.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./CrySystem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EditorCore.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EditorCore.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EditorCommon.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/bearer/qgenericbearer.dll" "bearer" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.imguilib.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LmbrCentral.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Concurrent.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomViewportDisplayInfo.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LmbrCentral.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EditorCommon.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EditorLib.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Network.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.imguilib.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EditorCore.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/python/runtime/python-3.10.5-rev1-windows/python/python310.dll;C:/O3DE/23.10.0/python/runtime/python-3.10.5-rev1-windows/python/python3.dll;C:/O3DE/23.10.0/python/runtime/python-3.10.5-rev1-windows/python/python310.pdb;C:/O3DE/23.10.0/python/runtime/python-3.10.5-rev1-windows/python/python3.pdb" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Network.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.imguilib.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LmbrCentral.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Concurrent.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomViewportDisplayInfo.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LmbrCentral.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EditorLib.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/EditorPlugins/ComponentEntityEditorPlugin.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/EditorPlugins/FFMPEGPlugin.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/EditorPlugins/ProjectSettingsTool.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/EditorPlugins/PerforcePlugin.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SceneCore.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SceneData.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SceneUI.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SceneCore.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SceneData.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SceneUI.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/EditorPlugins/EditorAssetImporter.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/openimageio-opencolorio-2.3.17-rev4-windows/OpenImageIO/bin/iconvert.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/openimageio-opencolorio-2.3.17-rev4-windows/OpenImageIO/bin/idiff.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/openimageio-opencolorio-2.3.17-rev4-windows/OpenImageIO/bin/igrep.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/openimageio-opencolorio-2.3.17-rev4-windows/OpenImageIO/bin/iinfo.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/openimageio-opencolorio-2.3.17-rev4-windows/OpenImageIO/bin/maketx.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/openimageio-opencolorio-2.3.17-rev4-windows/OpenImageIO/bin/oiiotool.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/openimageio-opencolorio-2.3.17-rev4-windows/OpenImageIO/lib/python3.10/site-packages/OpenImageIO.cp310-win_amd64.pyd" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/vulkan-validationlayers-1.3.261-rev1-windows/vulkan-validationlayers/lib/release/VkLayer_khronos_validation.json" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/vulkan-validationlayers-1.3.261-rev1-windows/vulkan-validationlayers/lib/release/VkLayer_khronos_validation.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/squish-ccr-deb557d-rev1-windows/squish-ccr/bin/squish-ccr.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/ISPCTexComp-36b80aa-rev1-windows/ISPCTexComp/bin/ispc_texcomp.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/DirectXShaderCompilerDxc-1.6.2112-o3de-rev1-windows/DirectXShaderCompilerDxc/bin/Release/dxc.exe" "Builders/DirectXShaderCompiler" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/DirectXShaderCompilerDxc-1.6.2112-o3de-rev1-windows/DirectXShaderCompilerDxc/bin/Release/dxil.dll" "Builders/DirectXShaderCompiler" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/DirectXShaderCompilerDxc-1.6.2112-o3de-rev1-windows/DirectXShaderCompilerDxc/bin/Release/dxcompiler.dll" "Builders/DirectXShaderCompiler" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/SPIRVCross-2021.04.29-rev1-windows/SPIRVCross/bin/Release/spirv-cross.exe" "Builders/SPIRVCross" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/azslc-1.8.15-rev2-windows/azslc/bin/Release/azslc.exe" "Builders/AZSLc" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/mcpp-2.7.2_az.2-rev1-windows/mcpp/lib/mcpp0.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysX_64.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysXCooking_64.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysXFoundation_64.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysXCommon_64.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysXDevice64.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysXGpu_64.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.assetbuilder.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.bookproject.assetbuilder.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.assetprocessor.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.bookproject.assetprocessor.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/pyside2-5.15.2.1-py3.10-rev6-windows/pyside2/bin/pyside2-lupdate.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/pyside2-5.15.2.1-py3.10-rev6-windows/pyside2/bin/shiboken2.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/pyside2-5.15.2.1-py3.10-rev6-windows/pyside2/bin/libclang.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/pyside2-5.15.2.1-py3.10-rev6-windows/pyside2/bin/pyside_tool.py" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/pyside2-5.15.2.1-py3.10-rev6-windows/pyside2/bin/shiboken_tool.py" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.materialcanvas.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.bookproject.materialcanvas.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.materialeditor.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.bookproject.materialeditor.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.passcanvas.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.bookproject.passcanvas.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.shadermanagementconsole.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.bookproject.shadermanagementconsole.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-auth.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-cal.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-common.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-compression.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-event-stream.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-http.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-io.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-mqtt.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-s3.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-checksums.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-core.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-crt-cpp.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-dynamodb.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-lambda.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-s3.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AWSCore.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/pyside2-5.15.2.1-py3.10-rev6-windows/pyside2/lib/site-packages/PySide2/pyside2.abi3.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/AWSCoreEditorQtBin/AWSCore.ResourceMappingTool.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AWSCore.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Network.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SceneBuilder.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomFont.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomImGuiTools.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomLyIntegration_CommonFeatures.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_Bootstrap.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_Component_DebugCamera.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI_DX12.Private.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI_Metal.Private.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI_Vulkan.Private.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_Feature_Common.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI.Private.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI_Null.Private.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RPI.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EditorPythonBindings.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Xml.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./GraphCanvas.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./GraphModel.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImageProcessingAtom.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomToolsFramework.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomViewportDisplayIcons.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_Asset_Shader.Builders.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI_DX12.Builders.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI_Metal.Builders.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI_Vulkan.Builders.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_Feature_Common.Builders.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI_Null.Builders.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RPI.Builders.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EMotionFX.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_Feature_Common.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EMotionFX_Atom.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImguiAtom.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_AtomBridge.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AudioSystem.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/BookProject.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Camera.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./CameraFramework.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/openimageio-opencolorio-2.3.17-rev4-windows/OpenImageIO/bin/OpenImageIO.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./GradientSignal.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomLyIntegration_CommonFeatures.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_Feature_Common.Builders.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RPI.Builders.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Compression.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./DebugDraw.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./DiffuseProbeGrid.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EMotionFX.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EditorModeFeedback.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EditorPythonBindings.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./GradientSignal.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SurfaceData.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LandscapeCanvas.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./TextureAtlas.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LyShine.Builders.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LmbrCentral.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./TextureAtlas.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LyShine.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LyShineExamples.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Maestro.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/MyGem.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./NvCloth.Editor.Gem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./PhysX.Editor.Gem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./PrefabBuilder.Builders.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SceneProcessing.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ExpressionEvaluation.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptEvents.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptCanvas.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptEvents.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptCanvas.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptCanvasPhysics.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptEvents.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./StartingPointInput.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./TextureAtlas.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./WhiteBox.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AssetBuilder.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "EXECUTABLE" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AssetProcessor.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "EXECUTABLE" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomViewportDisplayInfo.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/EditorPlugins/ComponentEntityEditorPlugin.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/EditorPlugins/EditorAssetImporter.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/EditorPlugins/FFMPEGPlugin.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/pyside2-5.15.2.1-py3.10-rev6-windows/pyside2/lib/site-packages/shiboken2/shiboken2.abi3.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Test.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./QtForPython.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LyShine.Tools.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./MaterialCanvas.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "EXECUTABLE" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./MaterialEditor.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "EXECUTABLE" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./PassCanvas.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "EXECUTABLE" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ShaderManagementConsole.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "EXECUTABLE" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./CrySystem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LuaIDE.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "EXECUTABLE" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/EditorPlugins/PerforcePlugin.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./o3de.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "EXECUTABLE" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/EditorPlugins/ProjectSettingsTool.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SceneCore.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SceneData.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EditorCommon.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/openimageio-opencolorio-2.3.17-rev4-windows/OpenColorIO/bin/OpenColorIO_2_1.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/openimageio-opencolorio-2.3.17-rev4-windows/OpenColorIO/bin/OpenColorIO_2_1.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/openimageio-opencolorio-2.3.17-rev4-windows/OpenImageIO/bin/OpenImageIO.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/openimageio-opencolorio-2.3.17-rev4-windows/OpenImageIO/bin/OpenImageIO_Util.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5OpenGL.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SceneUI.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/openimageio-opencolorio-2.3.17-rev4-windows/OpenImageIO/bin/OpenImageIO.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/openimageio-opencolorio-2.3.17-rev4-windows/OpenImageIO/bin/OpenImageIO_Util.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Concurrent.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AWSCore.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/pyside2-5.15.2.1-py3.10-rev6-windows/pyside2/lib/site-packages/PySide2/pyside2.abi3.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/AWSCoreEditorQtBin/AWSCore.ResourceMappingTool.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AWSCore.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/assimp-5.2.5-rev1-windows/assimp/bin/release/assimp-vc143-mt.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SceneBuilder.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomFont.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomImGuiTools.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/openimageio-opencolorio-2.3.17-rev4-windows/OpenColorIO/bin/OpenColorIO_2_1.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/openimageio-opencolorio-2.3.17-rev4-windows/OpenImageIO/bin/OpenImageIO.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/openimageio-opencolorio-2.3.17-rev4-windows/OpenImageIO/bin/OpenImageIO_Util.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomLyIntegration_CommonFeatures.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_Bootstrap.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_Component_DebugCamera.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI_DX12.Private.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI_Metal.Private.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI_Vulkan.Private.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_Feature_Common.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI.Private.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI_Null.Private.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RPI.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EditorPythonBindings.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./GraphCanvas.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./GraphModel.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImageProcessingAtom.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomToolsFramework.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomViewportDisplayIcons.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_Asset_Shader.Builders.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI_DX12.Builders.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI_Metal.Builders.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI_Vulkan.Builders.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_Feature_Common.Builders.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI_Null.Builders.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RPI.Builders.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5OpenGL.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EMotionFX.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_Feature_Common.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EMotionFX_Atom.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImguiAtom.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_AtomBridge.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AudioSystem.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Camera.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./CameraFramework.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./GradientSignal.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Compression.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./DebugDraw.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./DiffuseProbeGrid.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EditorModeFeedback.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SurfaceData.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LandscapeCanvas.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./TextureAtlas.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LyShine.Builders.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./TextureAtlas.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LyShine.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LyShineExamples.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Maestro.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./NvCloth.Editor.Gem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./PhysX.Editor.Gem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./PrefabBuilder.Builders.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SceneProcessing.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ExpressionEvaluation.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptEvents.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptCanvas.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptEvents.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptCanvas.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptCanvasPhysics.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./StartingPointInput.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./WhiteBox.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AssetBuilder.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AssetProcessor.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/pyside2-5.15.2.1-py3.10-rev6-windows/pyside2/lib/site-packages/shiboken2/shiboken2.abi3.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Test.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./QtForPython.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LyShine.Tools.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./MaterialCanvas.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./MaterialEditor.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./PassCanvas.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ShaderManagementConsole.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LuaIDE.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./o3de.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Editor.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.bookproject_serverlauncher.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.bookproject.bookproject_serverlauncher.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.editor.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.bookproject.editor.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RPI.Private.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomLyIntegration_CommonFeatures.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EMotionFX.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EMotionFX_Atom.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_AtomBridge.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_Bootstrap.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Camera.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./GradientSignal.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomLyIntegration_CommonFeatures.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Compression.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./DiffuseProbeGrid.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EMotionFX.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./GameState.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LmbrCentral.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Maestro.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/MyGem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./NvCloth.Gem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./PhysX.Gem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptCanvas.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptEvents.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./StartingPointInput.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./TextureAtlas.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./WhiteBox.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/BookProject.ServerLauncher.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "EXECUTABLE" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RPI.Private.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomLyIntegration_CommonFeatures.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EMotionFX.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EMotionFX_Atom.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_AtomBridge.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Camera.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./GradientSignal.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Compression.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./DiffuseProbeGrid.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./GameState.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Maestro.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./NvCloth.Gem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./PhysX.Gem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./StartingPointInput.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./WhiteBox.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.assetprocessorbatch.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.bookproject.assetprocessorbatch.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AssetProcessorBatch.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AzTestRunner.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ToolsCrashUploader.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./PythonBindingsExample.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./DeltaCataloger.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SerializeContextTools.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.assetbundlerbatch.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.bookproject.assetbundlerbatch.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AssetBundlerBatch.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.assetbundler.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.bookproject.assetbundler.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AssetBundler.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SurfaceData.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./GraphCanvas.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SceneProcessing.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Achievements.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Archive.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Archive.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AssetValidation.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./DccScriptingInterface.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AudioSystem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./HttpRequestor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-cognito-identity.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-cognito-idp.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-sts.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-identity-management.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AWSCore.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./HttpRequestor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AWSClientAuth.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AWSClientAuth.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AWSClientAuth.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-gamelift.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AWSGameLift.Clients.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AWSGameLift.Clients.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AWSGameLift.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSGameLiftServerSDK-5.0.0-rev2-windows/AWSGameLiftServerSDK/bin/Release/aws-cpp-sdk-gamelift-server.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AWSGameLift.Servers.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AWSMetrics.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AWSMetrics.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AWSMetrics.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./BarrierInput.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./CertificateManager.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./CrashReporting.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./CrashReporting.Uploader.exe" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./CustomAssetExample.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./CustomAssetExample.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./DebugDraw.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./GradientSignal.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./FastNoise.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./FastNoise.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LocalUser.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SaveData.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./MessagePopup.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./GameState.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LocalUser.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./GameStateSamples.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Gestures.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./InAppPurchases.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Metastream.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Microphone.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./MotionMatching.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Gem.MotionMatching.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./CertificateManager.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Multiplayer.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Multiplayer.Client.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Multiplayer.Server.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Multiplayer.Debug.Client.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Multiplayer.Debug.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Multiplayer.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Multiplayer_ScriptCanvas.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./MultiplayerCompression.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./PhysX.Gem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./PhysXDebug.Gem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./PhysX.Editor.Gem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./PhysXDebug.Editor.Gem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Presence.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Profiler.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ProfilerImGui.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./PythonAssetBuilder.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./RecastNavigation.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./RecastNavigation.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./RemoteTools.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SceneLoggingExample.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptAutomation.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptCanvasDeveloper.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptCanvas.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptCanvasDeveloper.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptCanvasTesting.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptedEntityTweener.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SliceFavorites.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Stars.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Stars.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./CameraFramework.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./StartingPointCamera.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./StartingPointMovement.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./StreamerProfiler.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Terrain.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Terrain.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./TestAssetBuilder.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./TickBusOrderViewer.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Twitch.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SurfaceData.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Vegetation.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Vegetation.Editor.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./VideoPlaybackFramework.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./VirtualGamepad.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/" SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/vulkan-validationlayers-1.3.261-rev1-windows/vulkan-validationlayers/lib/release/VkLayer_khronos_validation.json" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/vulkan-validationlayers-1.3.261-rev1-windows/vulkan-validationlayers/lib/release/VkLayer_khronos_validation.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysX_64.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysXCooking_64.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysXFoundation_64.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysXCommon_64.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysXDevice64.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/PhysX-4.1.2.29882248-rev5-windows/PhysX/shared/profile/bin/PhysXGpu_64.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.bookproject_gamelauncher.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.bookproject.bookproject_gamelauncher.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-auth.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-cal.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-common.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-compression.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-event-stream.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-http.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-io.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-mqtt.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-c-s3.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-checksums.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-core.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-crt-cpp.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-dynamodb.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-lambda.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/AWSNativeSDK-1.9.50-rev2-windows/AWSNativeSDK/bin/Release/aws-cpp-sdk-s3.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AWSCore.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Achievements.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomFont.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.imguilib.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LmbrCentral.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomImGuiTools.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI.Private.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RPI.Private.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomLyIntegration_CommonFeatures.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomViewportDisplayInfo.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_Bootstrap.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_Component_DebugCamera.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI_DX12.Private.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI_Null.Private.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI_Vulkan.Private.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_Feature_Common.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EMotionFX.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EMotionFX_Atom.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImguiAtom.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_AtomBridge.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomViewportDisplayInfo.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_Bootstrap.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AudioSystem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/BookProject.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Camera.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./CameraFramework.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./GradientSignal.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomLyIntegration_CommonFeatures.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Compression.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./DebugDraw.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./DiffuseProbeGrid.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EMotionFX.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./GameState.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./CrySystem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./TextureAtlas.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LyShine.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LmbrCentral.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LyShineExamples.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Maestro.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/MyGem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./NvCloth.Gem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./PhysX.Gem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SaveData.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ExpressionEvaluation.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptEvents.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptCanvas.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptCanvasPhysics.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptEvents.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./StartingPointInput.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./TextureAtlas.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./WhiteBox.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "MODULE_LIBRARY" SOURCE_GEM_MODULE "TRUE")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./O3DEKernel.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.imguilib.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./O3DEKernel.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AWSCore.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Achievements.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomFont.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.imguilib.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LmbrCentral.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomImGuiTools.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI.Private.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RPI.Private.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomLyIntegration_CommonFeatures.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomViewportDisplayInfo.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_Bootstrap.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_Component_DebugCamera.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI_DX12.Private.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI_Null.Private.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_RHI_Vulkan.Private.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_Feature_Common.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EMotionFX.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./EMotionFX_Atom.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImguiAtom.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Atom_AtomBridge.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AudioSystem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Camera.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./CameraFramework.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./GradientSignal.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Compression.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./DebugDraw.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./DiffuseProbeGrid.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./GameState.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ImGui.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./CrySystem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./TextureAtlas.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LyShine.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./LyShineExamples.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./Maestro.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./NvCloth.Gem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./PhysX.Gem.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SaveData.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ExpressionEvaluation.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptEvents.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptCanvas.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./ScriptCanvasPhysics.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./StartingPointInput.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./WhiteBox.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.bookproject_serverlauncher.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.bookproject.bookproject_serverlauncher.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.bookproject_unifiedlauncher.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/bin/profile/Registry/cmake_dependencies.bookproject.bookproject_unifiedlauncher.setreg" "Registry" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/iconengines/qsvgicon.dll" "iconengines" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qgif.dll" "imageformats" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qicns.dll" "imageformats" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qico.dll" "imageformats" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qjpeg.dll" "imageformats" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qsvg.dll" "imageformats" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qtga.dll" "imageformats" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qtiff.dll" "imageformats" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qwbmp.dll" "imageformats" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/imageformats/qwebp.dll" "imageformats" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/platforms/qminimal.dll" "platforms" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/platforms/qwindows.dll" "platforms" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/plugins/styles/qwindowsvistastyle.dll" "styles" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Core.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Gui.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SceneCore.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Core.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Gui.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Widgets.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AzQtComponents.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Svg.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Xml.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SceneCore.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SceneData.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "SHARED_LIBRARY" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Core.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Gui.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Widgets.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Svg.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/Users/mrele/.o3de/3rdParty/packages/qt-5.15.2-rev7-windows/qt/bin/Qt5Xml.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AzQtComponents.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SceneCore.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./SceneData.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./PrefabBuilder.Builders.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomTressFX.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")
    ly_copy("C:/O3DE/23.10.0/bin/Windows/profile/Default/./AtomTressFX.Builders.dll" "" TARGET_FILE_DIR "bin/Windows/profile/Default/." SOURCE_TYPE "" SOURCE_GEM_MODULE "")

  endif()
endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/DX12" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/RHI/DX12/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/DX12" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/DX12/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/DX12" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/DX12/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Metal" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/RHI/Metal/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Metal" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/Metal/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Metal" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/Metal/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Vulkan" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/RHI/Vulkan/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Vulkan" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/Vulkan/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Vulkan" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/Vulkan/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Null" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/RHI/Null/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Null" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/Null/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Null" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/Null/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/DX12" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/RHI/DX12/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/DX12" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/DX12/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/DX12" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/DX12/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Metal" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/RHI/Metal/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Metal" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/Metal/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Metal" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/Metal/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Null" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/RHI/Null/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Null" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/Null/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Null" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/Null/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Vulkan" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/RHI/Vulkan/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Vulkan" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/Vulkan/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Vulkan" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/Vulkan/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/RHI/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RPI" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RPI/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RPI" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RPI/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RPI" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/RPI/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RPI" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RPI/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RPI" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RPI/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Bootstrap" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Bootstrap/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Bootstrap" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Bootstrap/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Bootstrap" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Bootstrap/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Bootstrap" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Bootstrap/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Asset/Shader" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Asset/Shader/Config")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Asset/Shader" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Asset/Shader/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Asset/Shader" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Asset/Shader/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Asset/Shader" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Asset/Shader/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Asset/Shader" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Asset/Shader/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomViewportDisplayInfo" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/AtomViewportDisplayInfo/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomViewportDisplayInfo" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomViewportDisplayInfo/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomViewportDisplayInfo" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomViewportDisplayInfo/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Camera" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Camera/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Camera" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Camera/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Camera" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Camera/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Camera" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Camera/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LmbrCentral" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/LmbrCentral/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LmbrCentral" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/LmbrCentral/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LmbrCentral" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/LmbrCentral/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LmbrCentral" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/LmbrCentral/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ImGui" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ImGui/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ImGui" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ImGui/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ImGui" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ImGui/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Feature/Common" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Feature/Common/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Feature/Common/Assets" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Feature/Common/Assets/Config")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Feature/Common/Editor" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Feature/Common/Editor/Scripts")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Feature/Common" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Feature/Common/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Feature/Common" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Feature/Common/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Feature/Common" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Feature/Common/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Feature/Common" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Feature/Common/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SurfaceData" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/SurfaceData/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SurfaceData" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/SurfaceData/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SurfaceData" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/SurfaceData/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SurfaceData" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/SurfaceData/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Asset/ImageProcessingAtom" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Asset/ImageProcessingAtom/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Asset/ImageProcessingAtom/Assets" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Asset/ImageProcessingAtom/Assets/Config")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Asset/ImageProcessingAtom" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Asset/ImageProcessingAtom/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Asset/ImageProcessingAtom" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Asset/ImageProcessingAtom/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Asset/ImageProcessingAtom" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Asset/ImageProcessingAtom/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Asset/ImageProcessingAtom" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Asset/ImageProcessingAtom/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GradientSignal" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/GradientSignal/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GradientSignal" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/GradientSignal/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GradientSignal" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/GradientSignal/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GradientSignal" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/GradientSignal/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GraphCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/GraphCanvas/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GraphCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/GraphCanvas/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GraphCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/GraphCanvas/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GraphModel" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/GraphModel/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GraphModel" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/GraphModel/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GraphModel" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/GraphModel/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/AtomToolsFramework" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Tools/AtomToolsFramework/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/AtomToolsFramework" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/AtomToolsFramework/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/AtomToolsFramework" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/AtomToolsFramework/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/CommonFeatures" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/CommonFeatures/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/CommonFeatures/Assets/Editor" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/CommonFeatures/Assets/Editor/Scripts")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/CommonFeatures/Editor" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/CommonFeatures/Editor/Scripts")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/CommonFeatures" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/CommonFeatures/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/CommonFeatures" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/CommonFeatures/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/CommonFeatures" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/CommonFeatures/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/CommonFeatures" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/CommonFeatures/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/EditorModeFeedback" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/EditorModeFeedback/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/EditorModeFeedback" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/EditorModeFeedback/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/EditorModeFeedback" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/EditorModeFeedback/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/EditorModeFeedback" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/EditorModeFeedback/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Maestro" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Maestro/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Maestro" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Maestro/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Maestro" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Maestro/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Prefab/PrefabBuilder" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Prefab/PrefabBuilder/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Prefab/PrefabBuilder" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Prefab/PrefabBuilder/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SceneProcessing/Code/Include" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/SceneProcessing/Code/Include/Config")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SceneProcessing/Code/Source" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/SceneProcessing/Code/Source/Config")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SceneProcessing" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/SceneProcessing/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SceneProcessing" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/SceneProcessing/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SceneProcessing" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/SceneProcessing/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SceneProcessing" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/SceneProcessing/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Achievements" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Achievements/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Achievements" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Achievements/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Achievements" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Achievements/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Compression" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Compression/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Compression" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Compression/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Compression" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Compression/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Compression" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Compression/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Archive" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Archive/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Archive" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Archive/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Archive" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Archive/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Archive" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Archive/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AssetValidation" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AssetValidation/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AssetValidation" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AssetValidation/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AssetValidation" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AssetValidation/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Component/DebugCamera" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Component/DebugCamera/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Component/DebugCamera" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Component/DebugCamera/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Component/DebugCamera" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Component/DebugCamera/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialCanvas" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/MaterialCanvas/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialCanvas" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/MaterialCanvas/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Tools/MaterialCanvas/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/MaterialCanvas/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/MaterialCanvas/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialEditor" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/MaterialEditor/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialEditor" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/MaterialEditor/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialEditor" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Tools/MaterialEditor/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialEditor" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/MaterialEditor/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialEditor" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/MaterialEditor/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/PassCanvas" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/PassCanvas/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/PassCanvas" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/PassCanvas/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/PassCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Tools/PassCanvas/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/PassCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/PassCanvas/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/PassCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/PassCanvas/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/ShaderManagementConsole" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/ShaderManagementConsole/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/ShaderManagementConsole" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Atom/Tools/ShaderManagementConsole/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/ShaderManagementConsole" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/ShaderManagementConsole/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/ShaderManagementConsole" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/ShaderManagementConsole/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/ImguiAtom" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/ImguiAtom/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/ImguiAtom" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/ImguiAtom/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/ImguiAtom" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/ImguiAtom/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/ImguiAtom" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/ImguiAtom/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomImGuiTools" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/AtomImGuiTools/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomImGuiTools" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomImGuiTools/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomImGuiTools" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomImGuiTools/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/EMotionFX" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/EMotionFX/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/EMotionFX/Code/Source/Integration" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/EMotionFX/Code/Source/Integration/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/EMotionFX" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/EMotionFX/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/EMotionFX" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/EMotionFX/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/EMotionFX" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/EMotionFX/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/EMotionFX" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/EMotionFX/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/EMotionFXAtom" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/EMotionFXAtom/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/EMotionFXAtom" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/EMotionFXAtom/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/EMotionFXAtom" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/EMotionFXAtom/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/EMotionFXAtom" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/EMotionFXAtom/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/EMotionFXAtom" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/EMotionFXAtom/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomFont" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomFont/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomFont" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/AtomFont/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomFont" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomFont/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomFont" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomFont/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomViewportDisplayIcons" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomViewportDisplayIcons/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomViewportDisplayIcons" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/AtomViewportDisplayIcons/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomViewportDisplayIcons" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomViewportDisplayIcons/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomViewportDisplayIcons" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomViewportDisplayIcons/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomBridge" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomBridge/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomBridge" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/AtomBridge/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomBridge" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomBridge/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomBridge" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomBridge/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Asset/ImageProcessingAtom" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Asset/ImageProcessingAtom/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Asset/ImageProcessingAtom/Assets" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Asset/ImageProcessingAtom/Assets/Config")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Asset/ImageProcessingAtom" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Asset/ImageProcessingAtom/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Asset/Shader" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Asset/Shader/Config")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Asset/Shader" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Asset/Shader/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Asset/ImageProcessingAtom" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Asset/ImageProcessingAtom/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Asset/ImageProcessingAtom" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Asset/ImageProcessingAtom/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Asset/Shader" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Asset/Shader/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Asset/Shader" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Asset/Shader/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Bootstrap" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Bootstrap/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Bootstrap" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Bootstrap/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Bootstrap" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Bootstrap/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Component/DebugCamera" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Component/DebugCamera/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Component/DebugCamera" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Component/DebugCamera/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Feature/Common" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Feature/Common/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Feature/Common/Assets" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Feature/Common/Assets/Config")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Feature/Common/Editor" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Feature/Common/Editor/Scripts")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Feature/Common" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Feature/Common/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Feature/Common" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Feature/Common/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Feature/Common" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Feature/Common/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/DX12" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/DX12/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/DX12" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/DX12/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Metal" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/Metal/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Metal" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/Metal/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Null" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/Null/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Null" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/Null/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Vulkan" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/Vulkan/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI/Vulkan" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/Vulkan/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RHI" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RHI/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RPI" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RPI/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RPI" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RPI/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RPI" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RPI/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/RPI" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/RPI/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialCanvas" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/MaterialCanvas/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialCanvas" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/MaterialCanvas/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialEditor" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/MaterialEditor/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialEditor" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/MaterialEditor/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/PassCanvas" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/PassCanvas/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/PassCanvas" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/PassCanvas/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/ShaderManagementConsole" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/ShaderManagementConsole/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/AtomToolsFramework" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/AtomToolsFramework/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/AtomToolsFramework" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/AtomToolsFramework/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/MaterialCanvas/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/MaterialCanvas/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialEditor" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/MaterialEditor/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/MaterialEditor" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/MaterialEditor/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/PassCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/PassCanvas/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/PassCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/PassCanvas/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/ShaderManagementConsole" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/ShaderManagementConsole/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom/Tools/ShaderManagementConsole" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/Tools/ShaderManagementConsole/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Atom" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Atom/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/Sponza" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/Sponza/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/Sponza" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/Sponza/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/Sponza" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/Sponza/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/Sponza" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/Sponza/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/ReferenceMaterials" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/ReferenceMaterials/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/ReferenceMaterials" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/ReferenceMaterials/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/ReferenceMaterials" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/ReferenceMaterials/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/ReferenceMaterials" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/ReferenceMaterials/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/ReferenceMaterials" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/ReferenceMaterials/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/ReferenceMaterials" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/ReferenceMaterials/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/Sponza" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/Sponza/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/Sponza" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/Sponza/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/Sponza" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/Sponza/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/Sponza" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/Sponza/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/TestData" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/TestData/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/TestData" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/TestData/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/TestData" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/TestData/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/TestData" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/TestData/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/TestData" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/TestData/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/TestData" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/TestData/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/TestData" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/TestData/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomContent/TestData" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomContent/TestData/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomBridge" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomBridge/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomBridge" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomBridge/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomBridge" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomBridge/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomFont" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomFont/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomFont" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomFont/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomFont" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomFont/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomImGuiTools" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomImGuiTools/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomImGuiTools" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomImGuiTools/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomViewportDisplayIcons" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomViewportDisplayIcons/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomViewportDisplayIcons" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomViewportDisplayIcons/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomViewportDisplayIcons" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomViewportDisplayIcons/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomViewportDisplayInfo" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomViewportDisplayInfo/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/AtomViewportDisplayInfo" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/AtomViewportDisplayInfo/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/CommonFeatures" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/CommonFeatures/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/CommonFeatures/Assets/Editor" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/CommonFeatures/Assets/Editor/Scripts")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/CommonFeatures/Editor" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/CommonFeatures/Editor/Scripts")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/CommonFeatures" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/CommonFeatures/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/CommonFeatures" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/CommonFeatures/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/CommonFeatures" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/CommonFeatures/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/EMotionFXAtom" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/EMotionFXAtom/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/EMotionFXAtom" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/EMotionFXAtom/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/EMotionFXAtom" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/EMotionFXAtom/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/EMotionFXAtom" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/EMotionFXAtom/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/EditorModeFeedback" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/EditorModeFeedback/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/EditorModeFeedback" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/EditorModeFeedback/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/EditorModeFeedback" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/EditorModeFeedback/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/ImguiAtom" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/ImguiAtom/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/ImguiAtom" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/ImguiAtom/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/ImguiAtom" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/ImguiAtom/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface/Editor" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface/Editor/Scripts")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/EditorPythonBindings" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/EditorPythonBindings/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/EditorPythonBindings/Editor" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/EditorPythonBindings/Editor/Scripts")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/EditorPythonBindings" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/EditorPythonBindings/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/EditorPythonBindings" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/EditorPythonBindings/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/EditorPythonBindings" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/EditorPythonBindings/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/QtForPython/Editor" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/QtForPython/Editor/Scripts")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/QtForPython" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/QtForPython/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/QtForPython" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/QtForPython/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/QtForPython" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/QtForPython/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface/Editor" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface/Editor/Scripts")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomLyIntegration/TechnicalArt/DccScriptingInterface/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomTressFX" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomTressFX/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomTressFX/Code" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomTressFX/Code/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomTressFX/External" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomTressFX/External/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomTressFX" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomTressFX/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AtomTressFX" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AtomTressFX/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AudioSystem" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AudioSystem/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AudioSystem" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AudioSystem/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AudioSystem" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AudioSystem/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AudioEngineWwise" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AudioEngineWwise/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AudioEngineWwise" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AudioEngineWwise/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AudioEngineWwise" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AudioEngineWwise/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AudioEngineWwise" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AudioEngineWwise/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSCore" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AWSCore/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSCore" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AWSCore/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSCore" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AWSCore/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSCore" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AWSCore/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/HttpRequestor" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/HttpRequestor/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/HttpRequestor" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/HttpRequestor/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/HttpRequestor" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/HttpRequestor/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSClientAuth" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AWSClientAuth/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSClientAuth" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AWSClientAuth/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSClientAuth" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AWSClientAuth/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSGameLift" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AWSGameLift/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSGameLift" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AWSGameLift/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSGameLift" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AWSGameLift/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSMetrics" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AWSMetrics/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSMetrics" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/AWSMetrics/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSMetrics" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AWSMetrics/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/AWSMetrics" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/AWSMetrics/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/BarrierInput" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/BarrierInput/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/BarrierInput" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/BarrierInput/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/BarrierInput" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/BarrierInput/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CameraFramework" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/CameraFramework/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CameraFramework" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/CameraFramework/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CameraFramework" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/CameraFramework/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CameraFramework" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/CameraFramework/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CertificateManager" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/CertificateManager/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CertificateManager" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/CertificateManager/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CertificateManager" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/CertificateManager/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CertificateManager" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/CertificateManager/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CrashReporting" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/CrashReporting/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CrashReporting" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/CrashReporting/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CrashReporting" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/CrashReporting/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CustomAssetExample" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/CustomAssetExample/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CustomAssetExample" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/CustomAssetExample/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/CustomAssetExample" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/CustomAssetExample/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/DebugDraw" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/DebugDraw/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/DebugDraw" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/DebugDraw/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/DebugDraw" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/DebugDraw/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/DevTextures" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/DevTextures/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/DevTextures" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/DevTextures/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/DevTextures" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/DevTextures/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/DiffuseProbeGrid" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/DiffuseProbeGrid/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/DiffuseProbeGrid" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/DiffuseProbeGrid/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/DiffuseProbeGrid" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/DiffuseProbeGrid/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/DiffuseProbeGrid" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/DiffuseProbeGrid/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ExpressionEvaluation" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ExpressionEvaluation/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ExpressionEvaluation" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ExpressionEvaluation/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ExpressionEvaluation" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ExpressionEvaluation/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/FastNoise" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/FastNoise/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/FastNoise" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/FastNoise/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/FastNoise" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/FastNoise/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GameState" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/GameState/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GameState" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/GameState/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GameState" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/GameState/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LocalUser" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/LocalUser/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LocalUser" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/LocalUser/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LocalUser" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/LocalUser/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/TextureAtlas" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/TextureAtlas/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/TextureAtlas" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/TextureAtlas/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/TextureAtlas" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/TextureAtlas/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/UiBasics" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/UiBasics/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/UiBasics" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/UiBasics/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/UiBasics" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/UiBasics/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LyShine" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/LyShine/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LyShine" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/LyShine/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LyShine" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/LyShine/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LyShine" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/LyShine/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LyShine" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/LyShine/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SaveData" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/SaveData/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SaveData" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/SaveData/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SaveData" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/SaveData/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/MessagePopup" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/MessagePopup/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/MessagePopup" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/MessagePopup/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/MessagePopup" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/MessagePopup/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/MessagePopup" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/MessagePopup/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LyShineExamples" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/LyShineExamples/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LyShineExamples" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/LyShineExamples/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LyShineExamples" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/LyShineExamples/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LyShineExamples" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/LyShineExamples/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GameStateSamples" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/GameStateSamples/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GameStateSamples" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/GameStateSamples/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GameStateSamples" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/GameStateSamples/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/GameStateSamples" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/GameStateSamples/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Gestures" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Gestures/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Gestures" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Gestures/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Gestures" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Gestures/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/InAppPurchases" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/InAppPurchases/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/InAppPurchases" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/InAppPurchases/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/InAppPurchases" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/InAppPurchases/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LandscapeCanvas" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/LandscapeCanvas/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LandscapeCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/LandscapeCanvas/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LandscapeCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/LandscapeCanvas/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/LandscapeCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/LandscapeCanvas/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Metastream" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Metastream/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Metastream" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Metastream/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Metastream" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Metastream/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Microphone" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Microphone/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Microphone" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Microphone/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Microphone" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Microphone/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/MotionMatching" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/MotionMatching/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/MotionMatching" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/MotionMatching/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/MotionMatching" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/MotionMatching/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/MotionMatching" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/MotionMatching/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Multiplayer" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Multiplayer/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Multiplayer/Multiplayer_ScriptCanvas" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Multiplayer/Multiplayer_ScriptCanvas/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Multiplayer/Multiplayer_ScriptCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Multiplayer/Multiplayer_ScriptCanvas/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Multiplayer/Multiplayer_ScriptCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Multiplayer/Multiplayer_ScriptCanvas/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Multiplayer/Multiplayer_ScriptCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Multiplayer/Multiplayer_ScriptCanvas/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Multiplayer" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Multiplayer/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Multiplayer" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Multiplayer/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Multiplayer" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Multiplayer/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Multiplayer" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Multiplayer/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptEvents" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ScriptEvents/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptEvents" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptEvents/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptEvents" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ScriptEvents/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptEvents" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ScriptEvents/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvas" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ScriptCanvas/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvas/Code/Editor" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ScriptCanvas/Code/Editor/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvas/Code/Editor/Include/ScriptCanvas" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ScriptCanvas/Code/Editor/Include/ScriptCanvas/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvas" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ScriptCanvas/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptCanvas/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ScriptCanvas/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ScriptCanvas/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Multiplayer/Multiplayer_ScriptCanvas" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Multiplayer/Multiplayer_ScriptCanvas/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Multiplayer/Multiplayer_ScriptCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Multiplayer/Multiplayer_ScriptCanvas/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Multiplayer/Multiplayer_ScriptCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Multiplayer/Multiplayer_ScriptCanvas/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Multiplayer/Multiplayer_ScriptCanvas" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Multiplayer/Multiplayer_ScriptCanvas/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/MultiplayerCompression" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/MultiplayerCompression/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/MultiplayerCompression" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/MultiplayerCompression/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/MultiplayerCompression" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/MultiplayerCompression/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/NvCloth" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/NvCloth/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/NvCloth" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/NvCloth/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/NvCloth" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/NvCloth/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/NvCloth" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/NvCloth/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PhysX" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/PhysX/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PhysX" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/PhysX/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PhysX" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/PhysX/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PhysX" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/PhysX/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PhysX" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/PhysX/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PhysXDebug" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/PhysXDebug/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PhysXDebug" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/PhysXDebug/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PhysXDebug" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/PhysXDebug/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Presence" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Presence/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Presence" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Presence/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Presence" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Presence/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PrimitiveAssets" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/PrimitiveAssets/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PrimitiveAssets" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/PrimitiveAssets/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PrimitiveAssets" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/PrimitiveAssets/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Profiler" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Profiler/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Profiler" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Profiler/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Profiler" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Profiler/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PythonAssetBuilder" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/PythonAssetBuilder/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PythonAssetBuilder/Editor" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/PythonAssetBuilder/Editor/Scripts")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PythonAssetBuilder" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/PythonAssetBuilder/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PythonAssetBuilder" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/PythonAssetBuilder/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/PythonAssetBuilder" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/PythonAssetBuilder/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/RecastNavigation" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/RecastNavigation/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/RecastNavigation" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/RecastNavigation/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/RecastNavigation" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/RecastNavigation/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/RecastNavigation" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/RecastNavigation/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/RemoteTools" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/RemoteTools/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/RemoteTools" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/RemoteTools/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/RemoteTools" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/RemoteTools/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/RemoteTools" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/RemoteTools/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SceneLoggingExample" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/SceneLoggingExample/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SceneLoggingExample" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/SceneLoggingExample/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SceneLoggingExample" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/SceneLoggingExample/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptAutomation" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ScriptAutomation/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptAutomation" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ScriptAutomation/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptAutomation" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptAutomation/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptAutomation" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ScriptAutomation/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptAutomation" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ScriptAutomation/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvasDeveloper" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptCanvasDeveloper/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvasDeveloper" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ScriptCanvasDeveloper/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvasDeveloper" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ScriptCanvasDeveloper/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvasPhysics" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptCanvasPhysics/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvasPhysics" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ScriptCanvasPhysics/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvasPhysics" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ScriptCanvasPhysics/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvasTesting" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ScriptCanvasTesting/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvasTesting" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptCanvasTesting/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvasTesting" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ScriptCanvasTesting/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptCanvasTesting" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ScriptCanvasTesting/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptedEntityTweener" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ScriptedEntityTweener/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptedEntityTweener" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/ScriptedEntityTweener/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptedEntityTweener" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ScriptedEntityTweener/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/ScriptedEntityTweener" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/ScriptedEntityTweener/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SliceFavorites" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/SliceFavorites/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SliceFavorites" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/SliceFavorites/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/SliceFavorites" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/SliceFavorites/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Stars" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Stars/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Stars" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Stars/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Stars" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Stars/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Stars" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Stars/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Stars" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Stars/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/StartingPointCamera" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/StartingPointCamera/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/StartingPointCamera" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/StartingPointCamera/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/StartingPointCamera" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/StartingPointCamera/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/StartingPointCamera" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/StartingPointCamera/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/StartingPointInput" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/StartingPointInput/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/StartingPointInput" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/StartingPointInput/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/StartingPointInput" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/StartingPointInput/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/StartingPointInput" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/StartingPointInput/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/StartingPointInput" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/StartingPointInput/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/StartingPointMovement" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/StartingPointMovement/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/StartingPointMovement" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/StartingPointMovement/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/StartingPointMovement" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/StartingPointMovement/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/StartingPointMovement" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/StartingPointMovement/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Streamer/StreamerProfiler" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Streamer/StreamerProfiler/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Streamer/StreamerProfiler" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Streamer/StreamerProfiler/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Streamer/StreamerProfiler" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Streamer/StreamerProfiler/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Streamer/StreamerProfiler" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Streamer/StreamerProfiler/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Streamer" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Streamer/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Streamer" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Streamer/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Streamer" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Streamer/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Streamer/StreamerProfiler" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Streamer/StreamerProfiler/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Streamer/StreamerProfiler" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Streamer/StreamerProfiler/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Streamer/StreamerProfiler" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Streamer/StreamerProfiler/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Streamer/StreamerProfiler" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Streamer/StreamerProfiler/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Terrain" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Terrain/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Terrain" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Terrain/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Terrain" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Terrain/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Terrain" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Terrain/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Terrain" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Terrain/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/TestAssetBuilder" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/TestAssetBuilder/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/TestAssetBuilder" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/TestAssetBuilder/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/TestAssetBuilder" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/TestAssetBuilder/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/TestAssetBuilder" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/TestAssetBuilder/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/TickBusOrderViewer" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/TickBusOrderViewer/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/TickBusOrderViewer" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/TickBusOrderViewer/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/TickBusOrderViewer" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/TickBusOrderViewer/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Twitch" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Twitch/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Twitch" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Twitch/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Twitch" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Twitch/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Twitch" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Twitch/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Vegetation" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Vegetation/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Vegetation" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/Vegetation/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Vegetation" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Vegetation/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/Vegetation" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/Vegetation/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/VideoPlaybackFramework" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/VideoPlaybackFramework/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/VideoPlaybackFramework" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/VideoPlaybackFramework/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/VideoPlaybackFramework" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/VideoPlaybackFramework/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/VirtualGamepad" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/VirtualGamepad/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/VirtualGamepad" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/VirtualGamepad/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/VirtualGamepad" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/VirtualGamepad/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/VirtualGamepad" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/VirtualGamepad/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/WhiteBox" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/WhiteBox/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/WhiteBox" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/WhiteBox/Config")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/WhiteBox/Editor" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/WhiteBox/Editor/Scripts")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/WhiteBox" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/WhiteBox/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/WhiteBox" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/Gems/WhiteBox/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/WhiteBox" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/WhiteBox/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Gems/WhiteBox" TYPE FILE MESSAGE_NEVER FILES "C:/O3DE/23.10.0/Gems/WhiteBox/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/BookProject" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/BookProject" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Config")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/BookProject/Gem/MyGem" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/MyGem/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/BookProject/Gem/MyGem" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/MyGem/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/BookProject/Gem" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/BookProject/Gem/WindowPosition" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/WindowPosition/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/BookProject/Gem/WindowPosition" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/WindowPosition/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/BookProject/Gem/MyGem" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/External/BookProject/Gem/MyGem/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/BookProject/Gem/MyGem" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/MyGem/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/BookProject/Gem/MyGem" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/MyGem/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/BookProject/Gem/WindowPosition" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/External/BookProject/Gem/WindowPosition/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/BookProject/Gem/WindowPosition" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/WindowPosition/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/BookProject/Gem/WindowPosition" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/WindowPosition/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/BookProject/Gem" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/External/BookProject/Gem/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/BookProject/Gem" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/BookProject" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/BookProject" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/Gem/MyGem" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/MyGem/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/Gem/MyGem" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/MyGem/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/Gem/MyGem" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/MyGem/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/Gem/MyGem" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/MyGem/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/Gem" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/Gem/WindowPosition" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/WindowPosition/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/Gem/WindowPosition" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/WindowPosition/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/Gem/WindowPosition" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/WindowPosition/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/Gem/WindowPosition" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/WindowPosition/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/Gem" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/MyGem" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/MyGem/Assets")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/MyGem" TYPE DIRECTORY MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/MyGem/Registry")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/MyGem" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/03DE/BuildBookProject/o3de/install/External/MyGem/CMakeLists.txt")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/MyGem" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/MyGem/gem.json")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/External/MyGem" TYPE FILE MESSAGE_NEVER FILES "C:/Users/mrele/Documents/terrortronics-public/O3DE/BookProject/Gem/MyGem/preview.png")
endif()

endif()

if(NOT LY_CORE_COMPONENT_ALREADY_INCLUDED)
if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE MESSAGE_NEVER FILES
    "C:/O3DE/23.10.0/pytest.ini"
    "C:/O3DE/23.10.0/LICENSE.txt"
    "C:/O3DE/23.10.0/README.md"
    )
endif()

endif()

