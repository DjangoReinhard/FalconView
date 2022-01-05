cmake_minimum_required(VERSION 3.16)
#---------------------------   PLUGIN   --------------------------------------
project(PrefsEditor LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(FalconView)
add_library(ppPrefsEditor SHARED
    preferenceseditor.cpp
    )
set(TS_FILES
    prefseditor_DE.ts
    )
target_link_libraries(ppPrefsEditor
                      PRIVATE FVBaseLib
                      PRIVATE FVlcLib
                      PRIVATE IFQt
                      PRIVATE IFLinuxCNC
                      PRIVATE IFOpenCASCADE
                      PRIVATE IFStandard
                      )
if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

