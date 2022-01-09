cmake_minimum_required(VERSION 3.16)
#---------------------------   PLUGIN   --------------------------------------
project(LCToolTable LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(FalconView)
add_library(nbLCToolTable MODULE
    lctooltable.cpp
    )
set(TS_FILES
    lctooltable_de_DE.ts
    )
target_link_libraries(nbLCToolTable
                      PRIVATE FVBaseLib
                      PRIVATE FVlcLib
                      )
use_interface_libraries(nbLCToolTable
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

