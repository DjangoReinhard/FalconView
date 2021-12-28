TEMPLATE = lib
TARGET   = $$qtLibraryTarget(pp_PrefsEditor)
CONFIG  += plugin static c++17
QT      += widgets
DESTDIR  = ../../plugins

INCLUDEPATH  += \
    ../../baselib

HEADERS = \
    preferenceseditor.h

SOURCES = \
    preferenceseditor.cpp

uikit: CONFIG += debug_and_release

FORMS += \
  Settings.ui
