cmake_minimum_required(VERSION 3.16)
#--------------------------------   LIB   ------------------------------------
project(lcLib LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(FalconView)
add_library(FVlcLib STATIC
    lcproperties.cpp
    toolentry.cpp
    tooltable.cpp
    )
set(TS_FILES
    lcLib_de_DE.ts
    )
target_include_directories(FVlcLib
                           PUBLIC ${CMAKE_SOURCE_DIR}
                           )
target_link_libraries(FVlcLib
                      PRIVATE FVguiLib
                      PRIVATE FVBaseLib
                      )
use_interface_libraries(FVlcLib
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

