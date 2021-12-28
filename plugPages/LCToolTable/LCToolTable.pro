TEMPLATE = lib
TARGET   = $$qtLibraryTarget(pp_LCToolTable)
CONFIG  += plugin static c++17
QT      += widgets
DESTDIR  = ../../plugins

LINUXCNC = /usr/local/src/linuxcnc-deb11

INCLUDEPATH += \
    /usr/include/python3.9 \    # only linuxcnc uses python
    $${LINUXCNC}/include \
    $${LINUXCNC}/src/emc/rs274ngc \
    $${LINUXCNC}/src/emc/tooldata \
    $${LINUXCNC}/src \
    ../../baselib \

HEADERS = \
    lctooltable.h

SOURCES = \
    lctooltable.cpp

uikit: CONFIG += debug_and_release
