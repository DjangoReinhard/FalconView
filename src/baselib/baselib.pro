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
    control/core.cpp \
    control/kernel.cpp \
    model/configacc.cpp \
    model/configmgr.cpp \
    model/direntry.cpp \
    model/dirmodel.cpp \
    model/filemodel.cpp \
    model/pos9.cpp \
    model/sysevent.cpp \
    model/syseventmodel.cpp \
    model/valuemanager.cpp \
    model/valuemodel.cpp \
    util/axismask.cpp \
    util/dbconnection.cpp \
    util/flowlayout.cpp \
    util/kernelcreator.cpp \
    util/timestamp.cpp \

HEADERS += \
    control/applicationmode.h \
    control/core.h \
    control/filemanagerclient.h \
    control/kernel.h \
    control/KernelInterface.h \
    model/configacc.h \
    model/configmgr.h \
    model/direntry.h \
    model/dirmodel.h \
    model/filemodel.h \
    model/pos9.h \
    model/sysevent.h \
    model/syseventmodel.h \
    model/valuemanager.h \
    model/valuemodel.h \
    util/axismask.h \
    util/dbconnection.h \
    util/dbhelper.h \
    util/flowlayout.h \
    util/kernelcreator.h \
    util/timestamp.h \
    view/GCodeViewerInterface.h \
    view/mdieditorinterface.h \
    view/ViewPluginInterface.h \

TRANSLATIONS += \
    baselib_de_DE.ts

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
    }
!isEmpty(target.path): INSTALLS += target
