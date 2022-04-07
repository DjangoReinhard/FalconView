cmake_minimum_required(VERSION 3.16)
#---------------------------   PLUGIN   --------------------------------------
project(ToolManager LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(Interface)
add_library(nbToolManager MODULE
    toolmanager.cpp
    toolmodel.cpp
    tooleditor.cpp
    category.cpp
    CategoryTreeModel.cpp
    toolcategorymodel.cpp
    ToolManager.qrc
    )
set(TS_FILES
    toolmanager_de_DE.ts
    )
target_link_libraries(nbToolManager
                      PRIVATE FVBaseLib
                      PRIVATE FVguiLib
                      )
use_interface_libraries(nbToolManager
                        IFQt
                        IFOpenCASCADE
                        IFStandard
                        )
if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

