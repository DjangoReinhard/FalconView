cmake_minimum_required(VERSION 3.16)
#---------------------------   PLUGIN   --------------------------------------
project(ToolManager LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(FalconView)
add_library(ppToolManager MODULE
    toolmanager.cpp
    toolmodel.cpp
    tooleditor.cpp
    category.cpp
    CategoryTreeModel.cpp
    toolcategorymodel.cpp
    )
set(TS_FILES
    toolmanager_de_DE.ts
    )
target_link_libraries(ppToolManager
                      PRIVATE FVBaseLib
                      PRIVATE FVlcLib
                      )
use_interface_libraries(ppToolManager
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

