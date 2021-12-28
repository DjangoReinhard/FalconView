TEMPLATE = lib
TARGET   = $$qtLibraryTarget(pp_FixtureManager)
CONFIG  += plugin static c++17
QT      += widgets
DESTDIR  = ../../plugins
LINUXCNC = /usr/local/src/linuxcnc-deb11
OCCT     = /usr/local/src/build-occt-Desktop_5_15_opt-Debug

INCLUDEPATH += \
    ../../baselib \
    /usr/include/python3.9 \    # only linuxcnc uses python
    $${LINUXCNC}/include \
    $${LINUXCNC}/src/emc/rs274ngc \
    $${LINUXCNC}/src/emc/tooldata \
    $${LINUXCNC}/src \
    $${OCCT}/include/opencascade

HEADERS = \
    fixtureedit.h \
    fixturemanager.h

SOURCES = \
    fixtureedit.cpp \
    fixturemanager.cpp

uikit: CONFIG += debug_and_release

FORMS += \
  Fixture.ui
