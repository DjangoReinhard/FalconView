cmake_minimum_required(VERSION 3.16)
#----------------------------   PLUGIN   -------------------------------------
project(SysEventView LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(Interface)
add_library(ppSysEventView MODULE
    syseventview.cpp
    SysEventView.qrc
    )
set(TS_FILES
    sysevenview_de_DE.ts
    )
target_link_libraries(ppSysEventView
                      PRIVATE FVBaseLib
                      PRIVATE FVguiLib
                      )
use_interface_libraries(ppSysEventView
                        IFQt
                        IFOpenCASCADE
                        IFStandard
                        )
if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

