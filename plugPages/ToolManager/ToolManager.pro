TEMPLATE = lib
TARGET   = $$qtLibraryTarget(pp_ToolManager)
CONFIG  += plugin c++17
QT      += widgets sql xml
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES *= QT_USE_QSTRINGBUILDER
DESTDIR  = ../../plugPages
LINUXCNC = /usr/local/src/linuxcnc-deb11

INCLUDEPATH += \
    ../../baselib \
    ../../lcLib \
    /usr/include/python3.9 \    # only linuxcnc uses python
    $${LINUXCNC}/include \
    $${LINUXCNC}/src/emc/rs274ngc \
    $${LINUXCNC}/src/emc/tooldata \
    $${LINUXCNC}/src \

HEADERS = \
    CategoryTreeModel.h \
    category.h \
    toolcategorymodel.h \
    tooleditor.h \
    toolmanager.h \
    toolmodel.h

SOURCES = \
    CategoryTreeModel.cpp \
    category.cpp \
    toolcategorymodel.cpp \
    tooleditor.cpp \
    toolmanager.cpp \
    toolmodel.cpp

uikit: CONFIG += debug_and_release

FORMS += \
  ToolEditor.ui
