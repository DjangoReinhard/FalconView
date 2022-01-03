cmake_minimum_required(VERSION 3.16)
project(FalconView     VERSION 0.1)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

set(CMAKE_PREFIX_PATH "/opt/qt5.15/5.15.2/gcc_64" CACHE PATH "Qt5 Toolkit")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/usr/local/lib/cmake/opencascade")
set(OpenCASCADE_DIR   "/usr/local/lib/cmake/opencascade" CACHE PATH "OpenCascade 7.6.0")
set(LinuxCNC_DIR      "/usr/local/src/linuxcnc-deb11" CACHE PATH "LinuxCNC")
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
find_library(LIB_LC  linuxcnc REQUIRED PATHS ${LinuxCNC_DIR}/lib )
find_library(LIB_PM  posemath REQUIRED PATHS ${LinuxCNC_DIR}/lib )
find_library(LIB_NML nml REQUIRED PATHS ${LinuxCNC_DIR}/lib )
find_library(LIB_RS  rs274 REQUIRED PATHS ${LinuxCNC_DIR}/lib )
find_library(LIB_LCI linuxcncini REQUIRED PATHS ${LinuxCNC_DIR}/lib )
find_library(LIB_PP  pyplugin REQUIRED PATHS ${LinuxCNC_DIR}/lib )
find_library(LIB_LH  linuxcnchal REQUIRED PATHS ${LinuxCNC_DIR}/lib )
find_library(LIB_TD  tooldata REQUIRED PATHS ${LinuxCNC_DIR}/lib )

add_subdirectory(src)
#add_subdirectory(docs)
