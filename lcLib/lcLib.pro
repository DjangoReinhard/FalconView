TEMPLATE = lib
CONFIG  += staticlib c++17
QT      += widgets gui-private uitools sql xml
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES *= QT_USE_QSTRINGBUILDER
LINUXCNC = /usr/local/src/linuxcnc-deb11
OCCT     = /usr/local/src/build-occt-Desktop_5_15_opt-Debug

INCLUDEPATH += \
    /usr/include/python3.9 \    # only linuxcnc uses python
    $${LINUXCNC}/include \
    $${LINUXCNC}/src/emc/rs274ngc \
    $${LINUXCNC}/src/emc/tooldata \
    $${LINUXCNC}/src \
    $${OCCT}/include/opencascade \
    ../baselib

SOURCES += \
    Geom_HelixData.cpp \
    HHelixCurveAdaptor.cpp \
    HelixCurveAdaptor.cpp \
    HelixCurveAdaptor_CylinderEvaluator.cpp \
    LCInter.cpp \
    ally3d.cpp \
    axismask.cpp \
    canonif.cpp \
    centerview.cpp \
    commandwriter.cpp \
    curcodesstatus.cpp \
    dynframe.cpp \
    errorreader.cpp \
    gcodeeditor.cpp \
    gcodehighlighter.cpp \
    gcodeinfo.cpp \
    graphicfactory.cpp \
    guicore.cpp \
    guikernel.cpp \
    guikernelcreator.cpp \
    helpcontentwidget.cpp \
    helpengine.cpp \
    helpkeywordwidget.cpp \
    lcproperties.cpp \
    linecodes.cpp \
    numlabel.cpp \
    occtviewer.cpp \
    positioncalculator.cpp \
    positionstatus.cpp \
    settingsnb.cpp \
    speedstatus.cpp \
    statusreader.cpp \
    stupidtoolchangerif.cpp \
    testEdit.cpp \
    toolentry.cpp \
    toolstatus.cpp \
    tooltable.cpp

HEADERS += \
    Geom_HelixData.h \
    HHelixCurveAdaptor.h \
    HelixCurveAdaptor.h \
    HelixCurveAdaptor_CylinderEvaluator.h \
    HelixCurveAdaptor_p.h \
    LCInter.h \
    ally3d.h \
    axismask.h \
    canonif.h \
    centerview.h \
    commandwriter.h \
    core_p.h \
    curcodesstatus.h \
    dynframe.h \
    errorreader.h \
    gcodeeditor.h \
    gcodehighlighter.h \
    gcodeinfo.h \
    graphicfactory.h \
    guicore.h \
    guikernel.h \
    guikernelcreator.h \
    helpcontentwidget.h \
    helpengine.h \
    helpkeywordwidget.h \
    insulatePose.h \
    lcproperties.h \
    linecodes.h \
    numlabel.h \
    occtviewer.h \
    positioncalculator.h \
    positionstatus.h \
    settingsnb.h \
    speedstatus.h \
    statusreader.h \
    stupidtoolchangerif.h \
    testEdit.h \
    toolentry.h \
    toolstatus.h \
    tooltable.h

TRANSLATIONS += \
    lcLib_de_DE.ts

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
    }
!isEmpty(target.path): INSTALLS += target

FORMS += \
  GCodeEditor.ui \
  HCurCodes.ui \
  HSpeedInfo.ui \
  Position.ui \
  PositionMain.ui \
  ToolInfo.ui \
  VCurCodes.ui \
  VSpeedInfo.ui
