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
    configacc.cpp \
    configmgr.cpp \
    core.cpp \
    dbconnection.cpp \
    direntry.cpp \
    dirmodel.cpp \
    filemanager.cpp \
    filemodel.cpp \
    flowlayout.cpp \
    kernel.cpp \
    kernelcreator.cpp \
    sysevent.cpp \
    syseventmodel.cpp \
    timestamp.cpp \
    valuemanager.cpp \
    valuemanager.cpp \
    valuemodel.cpp \
    valuemodel.cpp

HEADERS += \
    PluginPageInterface.h \
    abscenterwidget.h \
    applicationmode.h \
    configacc.h \
    configmgr.h \
    core.h \
    dbconnection.h \
    dbhelper.h \
    direntry.h \
    dirmodel.h \
    filemanager.h \
    filemanagerclient.h \
    filemodel.h \
    flowlayout.h \
    kernel.h \
    kernelcreator.h \
    sysevent.h \
    syseventmodel.h \
    timestamp.h \
    valuemanager.h \
    valuemanager.h \
    valuemodel.h \
    valuemodel.h

TRANSLATIONS += \
    baselib_de_DE.ts

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
    }
!isEmpty(target.path): INSTALLS += target
