cmake_minimum_required(VERSION 3.16)
project(lcLib LANGUAGES CXX)
set(CMAKE_BUILD_TYPE  Debug)
add_compile_definitions(USE_PLUGINS)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
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
set(FORMS
    UI/GCodeEditor.ui
    UI/HelpTitle.ui
    )
set(TS_FILES
    lcLib_de_DE.ts
    )
add_library(FVlcLib STATIC ${SOURCES} ${FORMS})
target_include_directories(FVlcLib
                           PUBLIC UI
                           PUBLIC control
                           PUBLIC model
                           PUBLIC util
                           PUBLIC view
                           SYSTEM  /usr/include/python3.9
                           PRIVATE ../plugPages
                           PRIVATE ${LinuxCNC_DIR}/include
                           PRIVATE ${LinuxCNC_DIR}/src
                           PRIVATE ${LinuxCNC_DIR}/src/emc/rs274ngc
                           PRIVATE ${LinuxCNC_DIR}/src/emc/tooldata
                           PRIVATE ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
                           PRIVATE ${OpenCASCADE_INCLUDE_DIR}
                           )
target_link_libraries(FVlcLib
                      PRIVATE FVBaseLib
                      PRIVATE Qt${QT_VERSION_MAJOR}::Gui
                      PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                      PRIVATE Qt${QT_VERSION_MAJOR}::Core
                      PRIVATE Qt${QT_VERSION_MAJOR}::Sql
                      PRIVATE Qt${QT_VERSION_MAJOR}::UiTools
                      PRIVATE Qt${QT_VERSION_MAJOR}::Xml
                      PRIVATE ${LinuxCNC_DIR}/lib/linuxcnc
                      PRIVATE ${LinuxCNC_DIR}/lib/posemath
                      PRIVATE ${LinuxCNC_DIR}/lib/nml
                      PRIVATE ${LinuxCNC_DIR}/lib/rs274
                      PRIVATE ${LinuxCNC_DIR}/lib/linuxcncini
                      PRIVATE ${LinuxCNC_DIR}/lib/pyplugin
                      PRIVATE ${LinuxCNC_DIR}/lib/linuxcnchal
                      PRIVATE ${LinuxCNC_DIR}/lib/tooldata
                      PRIVATE m stdc++ boost_python39 python3.9 crypt pthread dl util
                      TKernel TKMath TKService TKV3d TKOpenGl
                      TKBRep TKIGES TKSTL TKVRML TKSTEP TKSTEPAttr TKSTEP209
                      TKSTEPBase TKGeomBase TKGeomAlgo TKG3d TKG2d
                      TKXSBase TKShHealing TKHLR TKTopAlgo TKMesh TKPrim
                      TKCDF TKBool TKBO TKFillet TKOffset TKLCAF TKCAF TKVCAF
                      TKBin TKXml
                      )
if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()


