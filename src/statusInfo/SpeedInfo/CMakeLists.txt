cmake_minimum_required(VERSION 3.16)
#------------------------------   PLUGIN   -----------------------------------
project(SpeedInfo LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(Interface)
add_library(siSpeedInfo MODULE
    speedstatus.cpp
    SpeedInfo.qrc
    )
set(TS_FILES
    speedinfo_de_DE.ts
    )
target_link_libraries(siSpeedInfo
                      PRIVATE FVBaseLib
                      PRIVATE FVguiLib
                      )
use_interface_libraries(siSpeedInfo
                        IFQt
                        IFOpenCASCADE
                        IFStandard
                        )
if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

