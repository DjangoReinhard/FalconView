cmake_minimum_required(VERSION 3.16)
##################################   TOP   ###################################
project(FalconView     VERSION 0.1)
##############################################################################
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_MODULE_PATH /d/linux/cmake)
include(FalconView RESULT_VARIABLE ConfigBase)
set(CMAKE_PREFIX_PATH "/opt/qt5.15/5.15.2/gcc_64" CACHE PATH "CMake search-path")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/usr/local/lib/cmake/opencascade")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/usr/local/src/linuxcnc-deb11")
set(OpenCASCADE_DIR "/usr/local/lib/cmake/opencascade" CACHE PATH "OpenCascade 7.6.0")
set(ENV{EMC2_HOME} "/usr/local/src/linuxcnc-deb11")
set(CMAKE_INSTALL_MESSAGE ALWAYS)
set(CMAKE_INSTALL_PREFIX "/d/linux/QtI" CACHE PATH "test installation" FORCE)
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
target_include_directories(IFQt
                           INTERFACE ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
                           )
target_link_libraries(IFQt
                      INTERFACE Qt${QT_VERSION_MAJOR}::Gui
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

add_library(IFlinuxCNC    INTERFACE)
add_library(IFQt          INTERFACE)
add_library(IFOpenCASCADE INTERFACE)
add_library(IFStandard    INTERFACE)
target_include_directories(IFlinuxCNC
                           INTERFACE /usr/include/python3.9
                           INTERFACE ${LinuxCNC_DIR}/include
                           INTERFACE ${LinuxCNC_DIR}/src
                           INTERFACE ${LinuxCNC_DIR}/src/emc/rs274ngc
                           INTERFACE ${LinuxCNC_DIR}/src/emc/tooldata
                           )
target_link_libraries(IFlinuxCNC
                      INTERFACE ${LC_LibLC}
                      INTERFACE ${LC_LibPM}
                      INTERFACE ${LC_LibNML}
                      INTERFACE ${LC_LibRS274}
                      INTERFACE ${LC_LibLCI}
                      INTERFACE ${LC_LibPP}
                      INTERFACE ${LC_LibHal}
                      INTERFACE ${LC_LibTD}
                      )
target_include_directories(IFQt
                           INTERFACE ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
                           )
target_link_libraries(IFQt
                      INTERFACE Qt${QT_VERSION_MAJOR}::Gui
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
                          ppFixtureManager
                          ppJogView
                          ppLCToolTable
                          ppMDIEditor
                          ppPathEditor
                          ppPrefsEditor
                          ppPreview3D
                          ppSysEventView
                          ppToolManager
                          siCurCodes
                          siPosition
                          siSpeedInfo
                          siToolInfo
                  )
add_dependencies(FalconView HelpFile)

