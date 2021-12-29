TEMPLATE = lib
TARGET   = $$qtLibraryTarget(pp_HelpView)
CONFIG  += plugin c++17
QT      += widgets gui-private
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES *= QT_USE_QSTRINGBUILDER
DESTDIR  = ../../plugPages

INCLUDEPATH  += \
    ../../baselib/model \
    ../../baselib/control \
    ../../baselib/util \
    ../../baselib/view \
    ../../lcLib

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

unix:!mac {
  LIBS += -Wl,-rpath=$${LINUXCNC}/lib
  QMAKE_CXXFLAGS += -std=gnu++11
}

LIBS += \
  -L../../lcLib \
  -L../../baselib \
  -llcLib \
  -lbaselib \
