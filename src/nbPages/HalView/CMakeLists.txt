cmake_minimum_required(VERSION 3.16)
#---------------------------   PLUGIN   --------------------------------------
project(HalView LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(FalconView)
add_library(nbHalView MODULE
    halview.cpp
    halcomponent.cpp
    halelement.cpp
    halmodel.cpp
    halpin.cpp
    halsignal.cpp
    )
set(TS_FILES
    halview_de_DE.ts
    )
target_link_libraries(nbHalView
                      PRIVATE FVBaseLib
                      PRIVATE FVguiLib
                      )
use_interface_libraries(nbHalView
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

