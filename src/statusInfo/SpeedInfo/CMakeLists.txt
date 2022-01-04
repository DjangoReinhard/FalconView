cmake_minimum_required(VERSION 3.16)
#------------------------------   PLUGIN   -----------------------------------
project(SpeedInfo LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(FalconView)
add_library(siSpeedInfo SHARED
    speedstatus.cpp
    )
set(TS_FILES
    speedinfo_de_DE.ts
    )
target_include_directories(siSpeedInfo
                           PRIVATE ${LinuxCNC_DIR}/include
                           PRIVATE ${LinuxCNC_DIR}/src
                           PRIVATE ${LinuxCNC_DIR}/src/emc/rs274ngc
                           PRIVATE ${LinuxCNC_DIR}/src/emc/tooldata
                           PRIVATE ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
                           PRIVATE ${OpenCASCADE_INCLUDE_DIR}
                           )
target_link_libraries(siSpeedInfo
                      PRIVATE FVBaseLib
                      PRIVATE FVlcLib
                      PRIVATE Qt${QT_VERSION_MAJOR}::Gui
                      PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                      PRIVATE Qt${QT_VERSION_MAJOR}::Core
                      PRIVATE Qt${QT_VERSION_MAJOR}::Sql
                      PRIVATE Qt${QT_VERSION_MAJOR}::UiTools
                      PRIVATE Qt${QT_VERSION_MAJOR}::Xml
                      PRIVATE ${LC_LibLC} ${LC_LibPM} ${LC_LibNML} ${LC_LibRS274}
                      PRIVATE ${LC_LibLCI} ${LC_LibPP} ${LC_LibHal} ${LC_LibTD}
                      PRIVATE m stdc++ boost_python39 python3.9 crypt pthread dl util
                      TKernel TKMath TKService TKV3d TKOpenGl
                      TKBRep TKIGES TKSTL TKVRML TKSTEP TKSTEPAttr TKSTEP209
                      TKSTEPBase TKGeomBase TKGeomAlgo TKG3d TKG2d
                      TKXSBase TKShHealing TKHLR TKTopAlgo TKMesh TKPrim
                      TKCDF TKBool TKBO TKFillet TKOffset TKLCAF TKCAF TKVCAF
                      TKBin TKXml
                      )
if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

