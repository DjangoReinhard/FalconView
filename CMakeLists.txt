cmake_minimum_required(VERSION 3.16)
##################################   TOP   ###################################
project(FalconView     VERSION 0.1)
##############################################################################
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_MODULE_PATH /d/linux/cmake)
include(FalconView RESULT_VARIABLE ConfigBase)
set(CMAKE_PREFIX_PATH "/opt/qt5.15/5.15.2/gcc_64" CACHE PATH "CMake search-path")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ";/usr/local/lib/cmake/opencascade")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ";/usr/local/src/linuxcnc-deb11")
set(OpenCASCADE_DIR "/usr/local/lib/cmake/opencascade" CACHE PATH "OpenCascade 7.6.0")
set(ENV{EMC2_HOME} "/usr/local/src/linuxcnc-deb11")
### ------ don't change settings below this line ---- ###
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
find_package(linuxCNC MODULE REQUIRED)
add_library(IFQt          INTERFACE)
add_library(IFOpenCASCADE INTERFACE)
add_library(IFStandard    INTERFACE)
target_link_libraries(IFQt
                      INTERFACE Qt${QT_VERSION_MAJOR}::Gui
                      INTERFACE Qt${QT_VERSION_MAJOR}::GuiPrivate
                      INTERFACE Qt${QT_VERSION_MAJOR}::Widgets
                      INTERFACE Qt${QT_VERSION_MAJOR}::Core
                      INTERFACE Qt${QT_VERSION_MAJOR}::Sql
                      INTERFACE Qt${QT_VERSION_MAJOR}::UiTools
                      INTERFACE Qt${QT_VERSION_MAJOR}::Xml
                      )
target_include_directories(IFOpenCASCADE
                           INTERFACE ${OpenCASCADE_INCLUDE_DIR}
                           )
target_link_libraries(IFOpenCASCADE
                      INTERFACE TKernel
                      INTERFACE TKMath
                      INTERFACE TKService
                      INTERFACE TKV3d
                      INTERFACE TKOpenGl
                      INTERFACE TKBRep
                      INTERFACE TKIGES
                      INTERFACE TKSTL
                      INTERFACE TKVRML
                      INTERFACE TKSTEP
                      INTERFACE TKSTEPAttr
                      INTERFACE TKSTEP209
                      INTERFACE TKSTEPBase
                      INTERFACE TKGeomBase
                      INTERFACE TKGeomAlgo
                      INTERFACE TKG3d
                      INTERFACE TKG2d
                      INTERFACE TKXSBase
                      INTERFACE TKShHealing
                      INTERFACE TKHLR
                      INTERFACE TKTopAlgo
                      INTERFACE TKMesh
                      INTERFACE TKPrim
                      INTERFACE TKCDF
                      INTERFACE TKBool
                      INTERFACE TKBO
                      INTERFACE TKFillet
                      INTERFACE TKOffset
                      INTERFACE TKLCAF
                      INTERFACE TKCAF
                      INTERFACE TKVCAF
                      INTERFACE TKBin
                      INTERFACE TKXml
                      )
target_link_libraries(IFStandard
                      INTERFACE m
                      INTERFACE stdc++
                      INTERFACE boost_python39
                      INTERFACE python3.9
                      INTERFACE crypt
                      INTERFACE pthread
                      INTERFACE dl
                      INTERFACE util
                      )
add_subdirectory(src)
add_subdirectory(docs)
add_custom_target(build_Finish ALL
                  COMMAND ${PROJECT_SOURCE_DIR}/scripts/buildFinish ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR}
                  DEPENDS FalconView
                          nbFixtureManager
                          nbPrefsEditor
                          nbToolManager
                          ppJogView
                          ppMDIEditor
                          ppPathEditor
                          ppPreview3D
                          ppSysEventView
                          siCurCodes
                          siPosition
                          siSpeedInfo
                          siToolInfo
                  )
add_dependencies(FalconView HelpFile)

