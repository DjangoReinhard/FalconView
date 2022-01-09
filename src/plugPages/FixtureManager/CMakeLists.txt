cmake_minimum_required(VERSION 3.16)
#------------------------------   PLUGIN   -----------------------------------
project(FixtureManager LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(FalconView)
add_library(ppFixtureManager MODULE
    fixturemanager.cpp
    fixtureedit.cpp
    )
set(TS_FILES
    fixture_de_DE.ts
    )
target_link_libraries(ppFixtureManager
                      PRIVATE FVBaseLib
                      PRIVATE FVlcLib
                      )
use_interface_libraries(ppFixtureManager
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

