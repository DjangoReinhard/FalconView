cmake_minimum_required(VERSION 3.16)
#--------------------------------   LIB   ------------------------------------
project(lcLib LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(FalconView)
add_library(FVlcLib STATIC
    control/LCInter.cpp
    control/axismask.cpp
    control/canonif.cpp
    control/canonifsettings.cpp
    control/commandwriter.cpp
    control/errorreader.cpp
    control/gcodehighlighter.cpp
    control/guicore.cpp
    control/guikernel.cpp
    control/helpengine.cpp
    control/positioncalculator.cpp
    control/statusreader.cpp
    model/lcproperties.cpp
    model/linecodes.cpp
    model/stupidtoolchangerif.cpp
    model/toolentry.cpp
    model/tooltable.cpp
    util/Geom_HelixData.cpp
    util/HHelixCurveAdaptor.cpp
    util/HelixCurveAdaptor.cpp
    util/HelixCurveAdaptor_CylinderEvaluator.cpp
    util/ally3d.cpp
    util/graphicfactory.cpp
    util/guikernelcreator.cpp
    util/pluginpagefactory.cpp
    view/abscenterwidget.cpp
    view/centerpage.cpp
    view/filemanager.cpp
    view/gcodeeditor.cpp
    view/gcodeinfo.cpp
    view/helpbrowser.cpp
    view/helpcontentwidget.cpp
    view/helpdockable.cpp
    view/helpkeywordwidget.cpp
    view/helpview.cpp
    view/jogbutton.cpp
    view/numlabel.cpp
    view/occtviewer.cpp
    view/pagestack.cpp
    view/settingsnb.cpp
    view/testEdit.cpp
    )
set(TS_FILES
    lcLib_de_DE.ts
    )
target_include_directories(FVlcLib
                           PUBLIC control
                           PUBLIC model
                           PUBLIC util
                           PUBLIC view
                           PRIVATE ../plugPages
                           )
target_link_libraries(FVlcLib
                      PRIVATE FVBaseLib
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


