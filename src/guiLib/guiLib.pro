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

SOURCES += \
    control/gcodehighlighter.cpp \
    control/guicore.cpp \
    control/guikernel.cpp \
    control/helpengine.cpp \
    util/Geom_HelixData.cpp \
    util/HHelixCurveAdaptor.cpp \
    util/HelixCurveAdaptor.cpp \
    util/HelixCurveAdaptor_CylinderEvaluator.cpp \
    util/ally3d.cpp \
    util/graphicfactory.cpp \
    util/guikernelcreator.cpp \
    util/pluginpagefactory.cpp \
    view/abscenterwidget.cpp \
    view/centerpage.cpp \
    view/filemanager.cpp \
    view/gcodeeditor.cpp \
    view/gcodeinfo.cpp \
    view/helpbrowser.cpp \
    view/helpcontentwidget.cpp \
    view/helpdockable.cpp \
    view/helpkeywordwidget.cpp \
    view/helpview.cpp \
    view/jogbutton.cpp \
    view/numlabel.cpp \
    view/occtviewer.cpp \
    view/pagestack.cpp \
    view/settingsnb.cpp \
    view/testEdit.cpp \

HEADERS += \
    control/gcodehighlighter.h \
    control/guicore.h \
    control/guikernel.h \
    control/helpengine.h \
    util/Geom_HelixData.h \
    util/HHelixCurveAdaptor.h \
    util/HelixCurveAdaptor.h \
    util/HelixCurveAdaptor_CylinderEvaluator.h \
    util/HelixCurveAdaptor_p.h \
    util/ally3d.h \
    util/graphicfactory.h \
    util/guikernelcreator.h \
    util/insulatePose.h \
    util/pluginpagefactory.h \
    view/abscenterwidget.h \
    view/centerpage.h \
    view/filemanager.h \
    view/gcodeeditor.h \
    view/gcodeinfo.h \
    view/helpbrowser.h \
    view/helpcontentwidget.h \
    view/helpdockable.h \
    view/helpkeywordwidget.h \
    view/helpview.h \
    view/jogbutton.h \
    view/numlabel.h \
    view/occtviewer.h \
    view/pagestack.h \
    view/settingsnb.h \
    view/testEdit.h \

TRANSLATIONS += \
    guiLib_de_DE.ts

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
    }
!isEmpty(target.path): INSTALLS += target

FORMS += \
    UI/HelpTitle.ui \
    UI/GCodeEditor.ui
