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
                           PRIVATE linuxCNC
#                           SYSTEM  /usr/include/python3.9
#                           PRIVATE ${LinuxCNC_DIR}/include
#                           PRIVATE ${LinuxCNC_DIR}/src
#                           PRIVATE ${LinuxCNC_DIR}/src/emc/rs274ngc
#                           PRIVATE ${LinuxCNC_DIR}/src/emc/tooldata
#                           PRIVATE ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
#                           PRIVATE ${OpenCASCADE_INCLUDE_DIR}
                           )
target_link_libraries(FVlcLib
                      PRIVATE FVBaseLib
                      PRIVATE linuxCNC
#                      PRIVATE Qt${QT_VERSION_MAJOR}::Gui
#                      PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
#                      PRIVATE Qt${QT_VERSION_MAJOR}::Core
#                      PRIVATE Qt${QT_VERSION_MAJOR}::Sql
#                      PRIVATE Qt${QT_VERSION_MAJOR}::UiTools
#                      PRIVATE Qt${QT_VERSION_MAJOR}::Xml
#                      PRIVATE ${LC_LibLC}
#                      PRIVATE ${LC_LibPM}
#                      PRIVATE ${LC_LibNML}
#                      PRIVATE ${LC_LibRS274}
#                      PRIVATE ${LC_LibLCI}
#                      PRIVATE ${LC_LibPP}
#                      PRIVATE ${LC_LibHal}
#                      PRIVATE ${LC_LibTD}
#                      PRIVATE TKernel
#                      PRIVATE TKMath
#                      PRIVATE TKService
#                      PRIVATE TKV3d
#                      PRIVATE TKOpenGl
#                      PRIVATE TKBRep
#                      PRIVATE TKIGES
#                      PRIVATE TKSTL
#                      PRIVATE TKVRML
#                      PRIVATE TKSTEP
#                      PRIVATE TKSTEPAttr
#                      PRIVATE TKSTEP209
#                      PRIVATE TKSTEPBase
#                      PRIVATE TKGeomBase
#                      PRIVATE TKGeomAlgo
#                      PRIVATE TKG3d
#                      PRIVATE TKG2d
#                      PRIVATE TKXSBase
#                      PRIVATE TKShHealing
#                      PRIVATE TKHLR
#                      PRIVATE TKTopAlgo
#                      PRIVATE TKMesh
#                      PRIVATE TKPrim
#                      PRIVATE TKCDF
#                      PRIVATE TKBool
#                      PRIVATE TKBO
#                      PRIVATE TKFillet
#                      PRIVATE TKOffset
#                      PRIVATE TKLCAF
#                      PRIVATE TKCAF
#                      PRIVATE TKVCAF
#                      PRIVATE TKBin
#                      PRIVATE TKXml
#                      PRIVATE m
#                      PRIVATE stdc++
#                      PRIVATE boost_python39
#                      PRIVATE python3.9
#                      PRIVATE crypt
#                      PRIVATE pthread
#                      PRIVATE dl
#                      PRIVATE util
                      )
                  get_target_property(XX FVlcLib INCLUDE_DIRECTORIES)
                  get_target_property(YY FVlcLib SOURCES)
                  get_target_property(ZZ FVlcLib INTERFACE_LINK_LIBRARIES)
                  get_target_property(AA linuxCNC INCLUDE_DIRECTORIES)
message("target: ${XX}")
message("tarsrc: ${YY}")
message("tar_LL: ${ZZ}")
message("lc_inc: ${ZZ}")

if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()


