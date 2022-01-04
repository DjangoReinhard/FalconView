cmake_minimum_required(VERSION 3.16)
##################################   TOP   ###################################
project(FalconView     VERSION 0.1)
##############################################################################
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_MODULE_PATH /d/linux/cmake)
include(FalconView RESULT_VARIABLE ConfigBase)
set(CMAKE_PREFIX_PATH "/opt/qt5.15/5.15.2/gcc_64" CACHE PATH "CMake search-path")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/usr/local/lib/cmake/opencascade")
set(OpenCASCADE_DIR   "/usr/local/lib/cmake/opencascade" CACHE PATH "OpenCascade 7.6.0")
set(LinuxCNC_DIR      "/usr/local/src/linuxcnc-deb11" CACHE PATH "LinuxCNC")
set(DistDIR           ${PROJECT_BINARY_DIR}/dist CACHE PATH "build-result")
find_package(Qt5 REQUIRED COMPONENTS
             Gui
             Widgets
             Core
             Sql
             UiTools
             Xml
             LinguistTools
             )
find_package(OpenCASCADE COMPONENTS
             FoundationClasses
             ModelingData
             ModelingAlgorithms
             Visualization
             ApplicationFramework
             Draw
             PATHS ${OpenCASCADE_DIR} NO_DEFAULT_PATH
             )
find_library(LC_LibLC    linuxcnc REQUIRED PATHS ${LinuxCNC_DIR}/lib )
find_library(LC_LibPM    posemath REQUIRED PATHS ${LinuxCNC_DIR}/lib )
find_library(LC_LibNML   nml REQUIRED PATHS ${LinuxCNC_DIR}/lib )
find_library(LC_LibRS274 rs274 REQUIRED PATHS ${LinuxCNC_DIR}/lib )
find_library(LC_LibLCI   linuxcncini REQUIRED PATHS ${LinuxCNC_DIR}/lib )
find_library(LC_LibPP    pyplugin REQUIRED PATHS ${LinuxCNC_DIR}/lib )
find_library(LC_LibHal   linuxcnchal REQUIRED PATHS ${LinuxCNC_DIR}/lib )
find_library(LC_LibTD    tooldata REQUIRED PATHS ${LinuxCNC_DIR}/lib )

add_subdirectory(src)
add_subdirectory(docs)
add_custom_target(Dummy)
add_dependencies(FalconView HelpFile)
add_dependencies(FalconView Dummy)
add_custom_command(TARGET Dummy POST_BUILD
    COMMAND ${PROJECT_SOURCE_DIR}/buildFinish ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR}
    DEPENDS $<TARGET_FILE:FalconView>
    COMMENT "finish build"
    )

