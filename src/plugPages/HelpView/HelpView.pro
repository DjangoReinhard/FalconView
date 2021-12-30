TEMPLATE = lib
TARGET   = $$qtLibraryTarget(pp_HelpView)
CONFIG  += plugin c++17
QT      += widgets gui-private
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES *= QT_USE_QSTRINGBUILDER
DESTDIR  = ../../plugins

INCLUDEPATH  += \
    ../../baselib/model \
    ../../baselib/control \
    ../../baselib/util \
    ../../baselib/view \
    ../../lcLib/model \
    ../../lcLib/control \
    ../../lcLib/util \
    ../../lcLib/view

HEADERS = \
    helpbrowser.h \
    helpdockable.h \
    helpview.h

SOURCES = \
    helpbrowser.cpp \
    helpdockable.cpp \
    helpview.cpp

FORMS += \
    HelpTitle.ui

TRANSLATIONS += \
    helptitle_de_DE.ts

unix:!mac {
  LIBS += -Wl,-rpath=$${LINUXCNC}/lib
  QMAKE_CXXFLAGS += -std=gnu++11
}

LIBS += \
  -L../.. \
  -llcLib \
  -lbaselib \
