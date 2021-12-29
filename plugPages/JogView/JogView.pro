TEMPLATE = lib
TARGET   = $$qtLibraryTarget(pp_JogView)
CONFIG  += plugin c++17
QT      += widgets
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES *= QT_USE_QSTRINGBUILDER
DESTDIR  = ../../plugPages

INCLUDEPATH  += \
    ../../baselib \
    ../../lcLib

HEADERS = \
    jogbutton.h \
    jogview.h

SOURCES = \
    jogbutton.cpp \
    jogview.cpp

uikit: CONFIG += debug_and_release

FORMS += \
  Jog.ui
