TEMPLATE = lib
TARGET   = $$qtLibraryTarget(pp_JogView)
CONFIG  += plugin static c++17
QT      += widgets
DESTDIR  = ../../plugins

INCLUDEPATH  += \
    ../../baselib

HEADERS = \
    jogbutton.h \
    jogview.h

SOURCES = \
    jogbutton.cpp \
    jogview.cpp

uikit: CONFIG += debug_and_release

FORMS += \
  Jog.ui
