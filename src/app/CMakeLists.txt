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
    control/lckernel.cpp
    control/mainwindow.cpp
    control/multistatetoolbutton.cpp
    control/notcondition.cpp
    control/orcondition.cpp
    control/smallercondition.cpp
    control/testmain.cpp
    control/truecondition.cpp
    LC/axismask.cpp
    LC/canonif.cpp
    LC/canonifsettings.cpp
    LC/commandwriter.cpp
    LC/errorreader.cpp
    LC/LCInter.cpp
    LC/lcproperties.cpp
    LC/positioncalculator.cpp
    LC/statusreader.cpp
    LC/stupidtoolchangerif.cpp
    LC/toolentry.cpp
    LC/tooltable.cpp
    main.cpp
    model/falconviewdb.cpp
    model/toolcategory.cpp
    model/tool.cpp
    test/testDB.cpp
    test/testengine.cpp
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
                           PUBLIC LC
                           PUBLIC model
                           PUBLIC util
                           PUBLIC view
                           PRIVATE ../nbPages
                           PRIVATE ../plugPages
                           )
target_link_libraries(FalconView
                      PRIVATE FVBaseLib
                      PRIVATE FVguiLib
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

