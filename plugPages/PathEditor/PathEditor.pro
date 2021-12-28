TEMPLATE = lib
TARGET   = $$qtLibraryTarget(pp_PathEditor)
CONFIG  += plugin static c++17
QT      += widgets
DESTDIR  = ../../plugins

INCLUDEPATH  += \
    ../../baselib

HEADERS = \
    patheditor.h

SOURCES = \
    patheditor.cpp

uikit: CONFIG += debug_and_release
