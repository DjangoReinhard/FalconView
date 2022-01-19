cmake_minimum_required(VERSION 3.16)
#------------------------   PLUGIN   -----------------------------------------
project(JogView LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(FalconView)
add_library(ppJogView MODULE
    jogview.cpp
    )
set(TS_FILES
    jogview_de_DE.ts
    )
target_link_libraries(ppJogView
                      PRIVATE FVBaseLib
                      PRIVATE FVguiLib
                      )
use_interface_libraries(ppJogView
                        IFQt
                        IFOpenCASCADE
                        IFStandard
                        )
if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

