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
                           )
target_link_libraries(FVBaseLib
                      PRIVATE IFQt
                      PRIVATE IFLinuxCNC
                      PRIVATE IFOpenCASCADE
                      PRIVATE IFStandard
                      )
if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()


