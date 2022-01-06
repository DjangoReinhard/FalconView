cmake_minimum_required(VERSION 3.16)
#--------------------------------   LIB   ------------------------------------
project(BaseLib LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(FalconView)
add_library(FVBaseLib STATIC
    control/core.cpp
    control/kernel.cpp
    model/configacc.cpp
    model/configmgr.cpp
    model/direntry.cpp
    model/dirmodel.cpp
    model/filemodel.cpp
    model/sysevent.cpp
    model/syseventmodel.cpp
    model/valuemanager.cpp
    model/valuemodel.cpp
    util/dbconnection.cpp
    util/flowlayout.cpp
    util/kernelcreator.cpp
    util/timestamp.cpp
    )
set(TS_FILES
    i18n/baselib_de_DE.ts
    )
target_include_directories(FVBaseLib
                           PUBLIC control
                           PUBLIC model
                           PUBLIC util
                           PUBLIC view
                           PRIVATE ${LinuxCNC_DIR}/include
                           PRIVATE ${LinuxCNC_DIR}/src
                           PRIVATE ${LinuxCNC_DIR}/src/emc/rs274ngc
                           PRIVATE ${LinuxCNC_DIR}/src/emc/tooldata
                           PRIVATE ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
                           PRIVATE ${OpenCASCADE_INCLUDE_DIR}
                           )
target_link_libraries(FVBaseLib
                      PRIVATE Qt${QT_VERSION_MAJOR}::Gui
                      PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                      PRIVATE Qt${QT_VERSION_MAJOR}::Core
                      PRIVATE Qt${QT_VERSION_MAJOR}::Sql
                      PRIVATE Qt${QT_VERSION_MAJOR}::UiTools
                      PRIVATE Qt${QT_VERSION_MAJOR}::Xml
                      PRIVATE ${LC_LibLC}
                      PRIVATE ${LC_LibPM}
                      PRIVATE ${LC_LibNML}
                      PRIVATE ${LC_LibRS274}
                      PRIVATE ${LC_LibLCI}
                      PRIVATE ${LC_LibPP}
                      PRIVATE ${LC_LibHal}
                      PRIVATE ${LC_LibTD}
                      PRIVATE TKernel
                      PRIVATE TKMath
                      PRIVATE TKService
                      PRIVATE TKV3d
                      PRIVATE TKOpenGl
                      PRIVATE TKBRep
                      PRIVATE TKIGES
                      PRIVATE TKSTL
                      PRIVATE TKVRML
                      PRIVATE TKSTEP
                      PRIVATE TKSTEPAttr
                      PRIVATE TKSTEP209
                      PRIVATE TKSTEPBase
                      PRIVATE TKGeomBase
                      PRIVATE TKGeomAlgo
                      PRIVATE TKG3d
                      PRIVATE TKG2d
                      PRIVATE TKXSBase
                      PRIVATE TKShHealing
                      PRIVATE TKHLR
                      PRIVATE TKTopAlgo
                      PRIVATE TKMesh
                      PRIVATE TKPrim
                      PRIVATE TKCDF
                      PRIVATE TKBool
                      PRIVATE TKBO
                      PRIVATE TKFillet
                      PRIVATE TKOffset
                      PRIVATE TKLCAF
                      PRIVATE TKCAF
                      PRIVATE TKVCAF
                      PRIVATE TKBin
                      PRIVATE TKXml
                      PRIVATE m
                      PRIVATE stdc++
                      PRIVATE boost_python39
                      PRIVATE python3.9
                      PRIVATE crypt
                      PRIVATE pthread
                      PRIVATE dl
                      PRIVATE util
                      )
if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()


