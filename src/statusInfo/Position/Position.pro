TEMPLATE = lib
TARGET   = $$qtLibraryTarget(si_Position)
CONFIG  += plugin link_prl c++17
QT      += widgets
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES *= QT_USE_QSTRINGBUILDER
DEFINES *= USE_PLUGINS
DESTDIR  = ../../plugins
LINUXCNC = /usr/local/src/linuxcnc-deb11

INCLUDEPATH += \
    ../../baselib/model \
    ../../baselib/control \
    ../../baselib/util \
    ../../baselib/view \
    ../../lcLib/model \
    ../../lcLib/control \
    ../../lcLib/util \
    ../../lcLib/view \
    /usr/include/python3.9 \    # only linuxcnc uses python
    $${LINUXCNC}/include \
    $${LINUXCNC}/src/emc/rs274ngc \
    $${LINUXCNC}/src/emc/tooldata \
    $${LINUXCNC}/src \

HEADERS = \
    positionstatus.h

SOURCES = \
    positionstatus.cpp

FORMS +=  \
    Position.ui \
    PositionMain.ui

TRANSLATIONS += \
    position_de_DE.ts

unix:!mac {
  LIBS += -Wl,-rpath=$${LINUXCNC}/lib
  QMAKE_CXXFLAGS += -std=gnu++11
}

LIBS += \
  -L../.. \
  -llcLib \
  -lbaselib \

LIBS += \
  -L$${LINUXCNC}/lib \
  -L/usr/lib \
  -lm \
  -llinuxcnc \
  -lposemath \
  -lnml \
  -lrs274 \
  -llinuxcncini \
  -lpyplugin \
  -llinuxcnchal \
  -ltooldata \
  -lstdc++ \
  -lboost_python39 \
  -lpython3.9 \
  -lcrypt \
  -lpthread \
  -ldl \
  -lutil
