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
    $${OCCT}/include/opencascade

SOURCES += \
    abscenterwidget.cpp \
    axismask.cpp \
    canonif.cpp \
    configacc.cpp \
    configmgr.cpp \
    core.cpp \
    dbconnection.cpp \
    direntry.cpp \
    dirmodel.cpp \
    dynframe.cpp \
    filemanager.cpp \
    filemodel.cpp \
    flowlayout.cpp \
    gcodeeditor.cpp \
    gcodehighlighter.cpp \
    gcodeinfo.cpp \
    graphicfactory.cpp \
    helpcontentwidget.cpp \
    helpengine.cpp \
    helpkeywordwidget.cpp \
    kernel.cpp \
    kernelcreator.cpp \
    lcproperties.cpp \
    positioncalculator.cpp \
    stupidtoolchangerif.cpp \
    sysevent.cpp \
    syseventmodel.cpp \
    testEdit.cpp \
    toolentry.cpp \
    tooltable.cpp \
    valuemanager.cpp \
    valuemodel.cpp

HEADERS += \
    PluginPageInterface.h \
    abscenterwidget.h \
    applicationmode.h \
    axismask.h \
    canonif.h \
    configacc.h \
    configmgr.h \
    core.h \
    core_p.h \
    dbconnection.h \
    dbhelper.h \
    direntry.h \
    dirmodel.h \
    dynframe.h \
    filemanager.h \
    filemanagerclient.h \
    filemodel.h \
    flowlayout.h \
    gcodeeditor.h \
    gcodehighlighter.h \
    gcodeinfo.h \
    graphicfactory.h \
    helpcontentwidget.h \
    helpengine.h \
    helpkeywordwidget.h \
    kernel.h \
    kernelcreator.h \
    lcproperties.h \
    positioncalculator.h \
    stupidtoolchangerif.h \
    sysevent.h \
    syseventmodel.h \
    testEdit.h \
    toolentry.h \
    tooltable.h \
    valuemanager.h \
    valuemodel.h

TRANSLATIONS += \
    baselib_de_DE.ts

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
    }
!isEmpty(target.path): INSTALLS += target
