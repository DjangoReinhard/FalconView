TEMPLATE      = lib
CONFIG       += plugin static
QT           += widgets
INCLUDEPATH  += ../../baselib
TARGET        = $$qtLibraryTarget(pp_ToolManager)
DESTDIR       = ../../plugins

HEADERS = \
    toolmanager.h

SOURCES = \
    toolmanager.cpp

uikit: CONFIG += debug_and_release
