cmake_minimum_required(VERSION 3.16)
#--------------------------------   LIB   ------------------------------------
project(guiLib LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(FalconView)
add_library(FVguiLib STATIC
    control/dynaaction.cpp
    control/gcodehighlighter.cpp
    control/guicore.cpp
    control/helpengine.cpp
    util/Geom_HelixData.cpp
    util/graphicelement.cpp
    util/gehelix.cpp
    util/geline.cpp
    util/gerapidmove.cpp
    util/HHelixCurveAdaptor.cpp
    util/HelixCurveAdaptor.cpp
    util/HelixCurveAdaptor_CylinderEvaluator.cpp
    util/ally3d.cpp
    util/graphicfactory.cpp
    view/abscenterwidget.cpp
    view/centerpage.cpp
    view/filemanager.cpp
    view/gcodeeditor.cpp
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
    guiLib_de_DE.ts
    )
target_include_directories(FVguiLib
                           PUBLIC control
                           PUBLIC util
                           PUBLIC view
                           )
target_link_libraries(FVguiLib
                      PRIVATE FVBaseLib
                      )
use_interface_libraries(FVguiLib
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

