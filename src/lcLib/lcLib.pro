TEMPLATE = lib
CONFIG  += staticlib create_prl c++17
QT      += widgets gui-private uitools sql xml
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES *= QT_USE_QSTRINGBUILDER
DEFINES *= USE_PLUGINS
DESTDIR  = ..
LINUXCNC = /usr/local/src/linuxcnc-deb11
OCCT     = /usr/local

INCLUDEPATH += \
    /usr/include/python3.9 \    # only linuxcnc uses python
    $${LINUXCNC}/include \
    $${LINUXCNC}/src/emc/rs274ngc \
    $${LINUXCNC}/src/emc/tooldata \
    $${LINUXCNC}/src \
    $${OCCT}/include/opencascade \
    ../baselib/model \
    ../baselib/control \
    ../baselib/util \
    ../baselib/view \
    model \
    control \
    util \
    view \
    ../plugPages \
    ../statusInfo \

SOURCES += \
    control/canonifsettings.cpp \
    model/tooltable.cpp \
    model/toolentry.cpp \
    model/linecodes.cpp \
    model/lcproperties.cpp \
    model/stupidtoolchangerif.cpp \
    control/positioncalculator.cpp \
    control/guikernel.cpp \
    control/errorreader.cpp \
    control/canonif.cpp \
    control/axismask.cpp \
    control/LCInter.cpp \
    control/commandwriter.cpp \
    control/guicore.cpp \
    control/helpengine.cpp \
    control/statusreader.cpp \
    control/gcodehighlighter.cpp \
    util/HelixCurveAdaptor.cpp \
    util/guikernelcreator.cpp \
    util/graphicfactory.cpp \
    util/HHelixCurveAdaptor.cpp \
    util/HelixCurveAdaptor_CylinderEvaluator.cpp \
    util/ally3d.cpp \
    util/Geom_HelixData.cpp \
    util/pluginpagefactory.cpp \
    view/abscenterwidget.cpp \
    view/filemanager.cpp \
    view/gcodeeditor.cpp \
    view/testEdit.cpp \
    view/gcodeinfo.cpp \
    view/jogbutton.cpp \
    view/numlabel.cpp \
    view/centerview.cpp \
    view/settingsnb.cpp \
    view/helpkeywordwidget.cpp \
    view/helpcontentwidget.cpp \
    view/occtviewer.cpp \
    view/centerpage.cpp \

HEADERS += \
    control/canonifsettings.h \
    model/stupidtoolchangerif.h \
    model/lcproperties.h \
    model/toolentry.h \
    model/tooltable.h \
    model/linecodes.h \
    control/canonif.h \
    control/helpengine.h \
    control/guicore.h \
    control/LCInter.h \
    control/gcodehighlighter.h \
    control/statusreader.h \
    control/commandwriter.h \
    control/positioncalculator.h \
    control/axismask.h \
    control/guikernel.h \
    control/errorreader.h \
    util/HHelixCurveAdaptor.h \
    util/ally3d.h \
    util/HelixCurveAdaptor_CylinderEvaluator.h \
    util/Geom_HelixData.h \
    util/HelixCurveAdaptor_p.h \
    util/HelixCurveAdaptor.h \
    util/insulatePose.h \
    util/guikernelcreator.h \
    util/graphicfactory.h \
    util/pluginpagefactory.h \
    view/abscenterwidget.h \
    view/centerpage.h \
    view/filemanager.h \
    view/gcodeeditor.h \
    view/helpcontentwidget.h \
    view/centerview.h \
    view/occtviewer.h \
    view/jogbutton.h \
    view/settingsnb.h \
    view/testEdit.h \
    view/helpkeywordwidget.h \
    view/gcodeinfo.h \
    view/numlabel.h \

TRANSLATIONS += \
    lcLib_de_DE.ts

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
    }
!isEmpty(target.path): INSTALLS += target

FORMS += \
    UI/GCodeEditor.ui
