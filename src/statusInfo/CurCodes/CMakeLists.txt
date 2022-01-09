cmake_minimum_required(VERSION 3.16)
#------------------------------   PLUGIN   -----------------------------------
project(CurCodes LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(FalconView)
add_library(siCurCodes MODULE
    curcodesstatus.cpp
    )
set(TS_FILES
    curcodes_de_DE.ts
    )
target_link_libraries(siCurCodes
                      PRIVATE FVBaseLib
                      PRIVATE FVlcLib
                      )
use_interface_libraries(siCurCodes
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

