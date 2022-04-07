cmake_minimum_required(VERSION 3.16)
#=================================   APP   ===================================
project(FalconView LANGUAGES CXX)
#=============================================================================
include(Interface)
add_executable(FalconView
    main.cpp
    control/guikernel.cpp
    control/mainwindow.cpp
    control/multistatetoolbutton.cpp
    LCcomm/commandwriter.cpp
    LCcomm/errorreader.cpp
    LCcomm/gcodeinfo.cpp
    LCcomm/positioncalculator.cpp
    LCcomm/statusreader.cpp
    LCinter/canonif.cpp
    LCinter/canonifsettings.cpp
    LCinter/LCInter.cpp
    LCinter/stupidtoolchangerif.cpp
    model/falconviewdb.cpp
    model/toolcategory.cpp
    model/tool.cpp
    util/multistateaction.cpp
    util/guikernelcreator.cpp
    util/pluginpagefactory.cpp
    view/aboutdialog.cpp
    view/dockable.cpp
    view/micon.cpp
    ../../FalconView.qrc
    )
set(TS_FILES
    i18n/FalconView_de_DE.ts
    )
target_include_directories(FalconView
                           PUBLIC control
                           PUBLIC LCcomm
                           PUBLIC LCinter
                           PUBLIC model
                           PUBLIC util
                           PUBLIC view
                           PRIVATE ../nbPages
                           PRIVATE ../centerPages
                           )
target_link_libraries(FalconView
                      PRIVATE FVBaseLib
                      PRIVATE FVguiLib
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

