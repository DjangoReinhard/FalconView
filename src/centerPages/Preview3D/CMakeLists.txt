cmake_minimum_required(VERSION 3.16)
#-------------------------   PLUGIN   ----------------------------------------
project(Preview3D LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(Interface)
add_library(ppPreview3D MODULE
    pweditor.cpp
    Preview3D.qrc
    )
set(TS_FILES
    preview3D_de_DE.ts
    )
target_link_libraries(ppPreview3D
                      PRIVATE FVBaseLib
                      PRIVATE FVguiLib
                      )
use_interface_libraries(ppPreview3D
                        IFQt
                        IFOpenCASCADE
                        IFStandard
                        )
if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

