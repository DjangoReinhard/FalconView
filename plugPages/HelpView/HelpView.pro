TEMPLATE = lib
TARGET   = $$qtLibraryTarget(pp_HelpView)
CONFIG  += plugin static c++17
QT      += widgets gui-private
DESTDIR  = ../../plugins

INCLUDEPATH  += \
    ../../baselib

HEADERS = \
    helpbrowser.h \
    helpdockable.h \
    helpview.h

SOURCES = \
    helpbrowser.cpp \
    helpdockable.cpp \
    helpview.cpp

uikit: CONFIG += debug_and_release

FORMS += \
  HelpTitle.ui
