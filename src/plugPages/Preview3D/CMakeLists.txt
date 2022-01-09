cmake_minimum_required(VERSION 3.16)
#-------------------------   PLUGIN   ----------------------------------------
project(Preview3D LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(FalconView)
add_library(ppPreview3D MODULE
    pweditor.cpp
    )
set(TS_FILES
    preview3D_de_DE.ts
    )
target_link_libraries(ppPreview3D
                      PRIVATE FVBaseLib
                      PRIVATE FVlcLib
                      )
use_interface_libraries(ppPreview3D
                        IFlinuxCNC
                        IFQt
                        IFOpenCASCADE
                        IFStandard
                        )
if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

