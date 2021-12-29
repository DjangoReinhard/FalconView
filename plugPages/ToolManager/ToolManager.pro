TEMPLATE = lib
TARGET   = $$qtLibraryTarget(pp_ToolManager)
CONFIG  += plugin c++17
QT      += widgets sql xml
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES *= QT_USE_QSTRINGBUILDER
DESTDIR  = ../../plugPages
LINUXCNC = /usr/local/src/linuxcnc-deb11

INCLUDEPATH += \
    ../../baselib/model \
    ../../baselib/control \
    ../../baselib/util \
    ../../baselib/view \
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

FORMS += \
  ToolEditor.ui

unix:!mac {
  LIBS += -Wl,-rpath=$${LINUXCNC}/lib
  QMAKE_CXXFLAGS += -std=gnu++11
}

LIBS += \
  -L../../lcLib \
  -L../../baselib \
  -llcLib \
  -lbaselib \

LIBS += \
  -L$${LINUXCNC}/lib \
  -L/usr/lib \
  -lm \
  -llinuxcnc \
  -lposemath \
  -lnml \
  -lrs274 \
  -llinuxcncini \
  -lpyplugin \
  -llinuxcnchal \
  -ltooldata \
  -lstdc++ \
  -lboost_python39 \
  -lpython3.9 \
  -lcrypt \
  -lpthread \
  -ldl \
  -lutil
