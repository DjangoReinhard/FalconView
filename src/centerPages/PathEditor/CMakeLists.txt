cmake_minimum_required(VERSION 3.16)
#--------------------------   PLUGIN   ---------------------------------------
project(PathEditor LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(Interface)
add_library(ppPathEditor MODULE
    patheditor.cpp
    PathEditor.qrc
    )
set(TS_FILES
    patheditor_de_DE.ts
    )
target_link_libraries(ppPathEditor
                      PRIVATE FVBaseLib
                      PRIVATE FVguiLib
                      )
use_interface_libraries(ppPathEditor
                        IFQt
                        IFOpenCASCADE
                        IFStandard
                        )
if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

