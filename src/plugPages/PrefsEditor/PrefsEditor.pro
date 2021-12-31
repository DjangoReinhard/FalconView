TEMPLATE = lib
TARGET   = $$qtLibraryTarget(pp_PrefsEditor)
CONFIG  += plugin c++17
QT      += widgets
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES *= QT_USE_QSTRINGBUILDER
DEFINES *= USE_PLUGINS
DESTDIR  = ../../plugins

INCLUDEPATH  += \
    ../../baselib/model \
    ../../baselib/control \
    ../../baselib/util \
    ../../baselib/view \

HEADERS = \
    preferenceseditor.h

SOURCES = \
    preferenceseditor.cpp

FORMS += \
    Settings.ui

TRANSLATIONS += \
    prefseditor_DE.ts

unix:!mac {
  LIBS += -Wl,-rpath=$${LINUXCNC}/lib
  QMAKE_CXXFLAGS += -std=gnu++11
}

LIBS += \
  -L../.. \
  -lbaselib \

