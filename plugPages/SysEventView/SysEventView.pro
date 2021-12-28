TEMPLATE = lib
TARGET   = $$qtLibraryTarget(pp_SysEventView)
CONFIG  += plugin static c++17
QT      += widgets sql
DESTDIR  = ../../plugins

INCLUDEPATH  += \
    ../../baselib

HEADERS = \
    syseventview.h

SOURCES = \
    syseventview.cpp

uikit: CONFIG += debug_and_release
