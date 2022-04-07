cmake_minimum_required(VERSION 3.16)
#------------------------------   PLUGIN   -----------------------------------
project(Position LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(Interface)
add_library(siPosition MODULE
    positionstatus.cpp
    Position.qrc
    )
set(TS_FILES
    position_de_DE.ts
    )
target_link_libraries(siPosition
                      PRIVATE FVBaseLib
                      PRIVATE FVguiLib
                      )
use_interface_libraries(siPosition
                        IFQt
                        IFOpenCASCADE
                        IFStandard
                        )
if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

