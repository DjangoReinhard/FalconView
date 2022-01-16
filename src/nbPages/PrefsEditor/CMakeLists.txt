cmake_minimum_required(VERSION 3.16)
#---------------------------   PLUGIN   --------------------------------------
project(PrefsEditor LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(FalconView)
add_library(nbPrefsEditor MODULE
    preferenceseditor.cpp
    )
set(TS_FILES
    prefseditor_DE.ts
    )
target_link_libraries(nbPrefsEditor
                      PRIVATE FVBaseLib
                      PRIVATE FVguiLib
                      )
use_interface_libraries(nbPrefsEditor
                        IFQt
                        IFOpenCASCADE
                        IFStandard
                        )
if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

