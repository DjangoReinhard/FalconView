TEMPLATE      = lib
CONFIG       += plugin static
QT           += widgets
INCLUDEPATH  += ../../baselib
TARGET        = $$qtLibraryTarget(pp_Preview3D)
DESTDIR       = ../../plugins

HEADERS = \
    pweditor.h

SOURCES = \
    pweditor.cpp

uikit: CONFIG += debug_and_release
