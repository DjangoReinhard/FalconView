cmake_minimum_required(VERSION 3.16)
#------------------------------   PLUGIN   -----------------------------------
project(ToolInfo LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(FalconView)
add_library(siToolInfo MODULE
    toolstatus.cpp
    )
set(TS_FILES
    toolinfo_de_DE.ts
    )
target_link_libraries(siToolInfo
                      PRIVATE FVBaseLib
                      PRIVATE FVlcLib
                      )
use_interface_libraries(siToolInfo
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

