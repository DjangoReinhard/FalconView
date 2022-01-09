cmake_minimum_required(VERSION 3.16)
#=================================   APP   ===================================
project(FalconView LANGUAGES CXX)
#=============================================================================
include(FalconView)
add_executable(FalconView
    main.cpp
    control/abstractcondition.cpp
    control/andcondition.cpp
    control/dynaaction.cpp
    control/equalcondition.cpp
    control/falsecondition.cpp
    control/greatercondition.cpp
    control/mainwindow.cpp
    control/multistatetoolbutton.cpp
    control/notcondition.cpp
    control/orcondition.cpp
    control/smallercondition.cpp
    control/testmain.cpp
    control/truecondition.cpp
    model/falconviewdb.cpp
    model/tool.cpp
    model/toolcategory.cpp
    util/multistateaction.cpp
    view/dockable.cpp
    view/micon.cpp
    view/plugindialog.cpp
    ../../FalconView.qrc
    )
set(TS_FILES
    i18n/FalconView_de_DE.ts
    )
target_include_directories(FalconView
                           PUBLIC control
                           PUBLIC model
                           PUBLIC util
                           PUBLIC view
                           PRIVATE ../plugPages
                           )
target_link_libraries(FalconView
                      PRIVATE FVBaseLib
                      PRIVATE FVlcLib
                      )
use_interface_libraries(FalconView
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

