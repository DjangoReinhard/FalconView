cmake_minimum_required(VERSION 3.16)
#-------------------------   PLUGIN   ----------------------------------------
project(MDIEditor LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(Interface)
add_library(ppMDIEditor MODULE
    mdieditor.cpp
    MDIEditor.qrc
    )
set(TS_FILES
    mdieditor_de_DE.ts
    )
target_link_libraries(ppMDIEditor
                      PRIVATE FVBaseLib
                      PRIVATE FVguiLib
                      )
use_interface_libraries(ppMDIEditor
                        IFQt
                        IFOpenCASCADE
                        IFStandard
                        )
if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

