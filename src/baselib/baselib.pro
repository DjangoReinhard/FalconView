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
    model \
    control \
    util \
    view \
    /usr/include/python3.9 \    # only linuxcnc uses python
    $${LINUXCNC}/include \
    $${LINUXCNC}/src/emc/rs274ngc \
    $${LINUXCNC}/src/emc/tooldata \
    $${LINUXCNC}/src \
    $${OCCT}/include/opencascade

SOURCES += \
    model/configacc.cpp \
    model/configmgr.cpp \
    model/direntry.cpp \
    model/dirmodel.cpp \
    model/filemodel.cpp \
    model/sysevent.cpp \
    model/syseventmodel.cpp \
    model/valuemanager.cpp \
    model/valuemodel.cpp \
    control/core.cpp \
    control/kernel.cpp \
    util/dbconnection.cpp \
    util/flowlayout.cpp \
    util/kernelcreator.cpp \
    util/timestamp.cpp

HEADERS += \
    model/configacc.h \
    model/configmgr.h \
    model/direntry.h \
    model/dirmodel.h \
    model/filemodel.h \
    model/sysevent.h \
    model/syseventmodel.h \
    model/valuemanager.h \
    model/valuemodel.h \
    control/applicationmode.h \
    control/core.h \
    control/filemanagerclient.h \
    control/kernel.h \
    util/dbconnection.h \
    util/dbhelper.h \
    util/flowlayout.h \
    util/kernelcreator.h \
    util/timestamp.h \
    view/PluginPageInterface.h

TRANSLATIONS += \
    baselib_de_DE.ts

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
    }
!isEmpty(target.path): INSTALLS += target
