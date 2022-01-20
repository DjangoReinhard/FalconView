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
    ../baselib/control \
    ../baselib/model \
    ../baselib/util \
    ../baselib/view \
    ../guiLib/control \
    ../guiLib/util \
    ../guiLib/view \

SOURCES += \
    lcproperties.cpp \
    toolentry.cpp \
    tooltable.cpp \

HEADERS += \
    lcproperties.h \
    toolentry.h \
    tooltable.h \

TRANSLATIONS += \
    lcLib_de_DE.ts

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
    }
!isEmpty(target.path): INSTALLS += target

