cmake_minimum_required(VERSION 3.16)
#------------------------------   PLUGIN   -----------------------------------
project(FixtureManager LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(FalconView)
add_library(nbFixtureManager MODULE
    fixturemanager.cpp
    fixtureedit.cpp
    )
set(TS_FILES
    fixture_de_DE.ts
    )
target_link_libraries(nbFixtureManager
                      PRIVATE FVBaseLib
                      PRIVATE FVguiLib
                      )
use_interface_libraries(nbFixtureManager
                        IFQt
                        IFOpenCASCADE
                        IFStandard
                        )
if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

