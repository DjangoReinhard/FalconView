cmake_minimum_required(VERSION 3.16)
#--------------------------------   LIB   ------------------------------------
project(BaseLib LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(Interface)
add_library(FVBaseLib STATIC
    control/core.cpp
    control/abstractcondition.cpp
    control/andcondition.cpp
    control/equalcondition.cpp
    control/falsecondition.cpp
    control/greatercondition.cpp
    control/notcondition.cpp
    control/orcondition.cpp
    control/smallercondition.cpp
    control/truecondition.cpp
    model/configacc.cpp
    model/configmgr.cpp
    model/direntry.cpp
    model/dirmodel.cpp
    model/filemodel.cpp
    model/pos9.cpp
    model/sysevent.cpp
    model/syseventmodel.cpp
    model/valuemanager.cpp
    model/valuemodel.cpp
    util/axismask.cpp
    util/dbconnection.cpp
    util/flowlayout.cpp
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
use_interface_libraries(FVBaseLib
                        IFQt
                        IFOpenCASCADE
                        IFStandard
                        )
if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()


