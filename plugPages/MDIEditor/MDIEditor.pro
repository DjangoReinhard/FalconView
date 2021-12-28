TEMPLATE      = lib
CONFIG       += plugin static
QT           += widgets
INCLUDEPATH  += ../../baselib
TARGET        = $$qtLibraryTarget(pp_MDIEditor)
DESTDIR       = ../../plugins

HEADERS = \
    mdieditor.h

SOURCES = \
    mdieditor.cpp

uikit: CONFIG += debug_and_release
