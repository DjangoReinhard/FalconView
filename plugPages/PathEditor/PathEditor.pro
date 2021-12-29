TEMPLATE = lib
TARGET   = $$qtLibraryTarget(pp_PathEditor)
CONFIG  += plugin c++17
QT      += widgets
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES *= QT_USE_QSTRINGBUILDER
DESTDIR  = ../../plugPages

INCLUDEPATH  += \
    ../../baselib \
    ../../lcLib

HEADERS = \
    patheditor.h

SOURCES = \
    patheditor.cpp

uikit: CONFIG += debug_and_release
