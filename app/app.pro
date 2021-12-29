TEMPLATE = app
TARGET   = FalconView
CONFIG  += c++17
QT      += widgets uitools sql xml
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES *= QT_USE_QSTRINGBUILDER
DESTDIR  = ..
LINUXCNC = /usr/local/src/linuxcnc-deb11
OCCT     = /usr/local/src/build-occt-Desktop_5_15_opt-Debug

INCLUDEPATH += \
    app \
    model \
    model/db \
    nml  \
    rs274 \
    util \
    view \
    view/pages \
    view/status \
    ../baselib \
    ../lcLib \
    /usr/include/python3.9 \    # only linuxcnc uses python
    $${LINUXCNC}/include \
    $${LINUXCNC}/src/emc/rs274ngc \
    $${LINUXCNC}/src/emc/tooldata \
    $${LINUXCNC}/src \
    $${OCCT}/include/opencascade

SOURCES += \
    app/main.cpp \
    app/mainwindow.cpp \
    app/testmain.cpp \
    model/db/falconviewdb.cpp \
    model/toolcategory.cpp \
    model/tool.cpp \
    util/abstractcondition.cpp \
    util/andcondition.cpp \
    util/dynaaction.cpp \
    util/equalcondition.cpp \
    util/falsecondition.cpp \
    util/greatercondition.cpp \
    util/micon.cpp \
    util/multistateaction.cpp \
    util/multistatetoolbutton.cpp \
    util/notcondition.cpp \
    util/orcondition.cpp \
    util/smallercondition.cpp \
    util/truecondition.cpp \
    view/dyndockable.cpp \
  view/plugindialog.cpp

HEADERS += \
    app/mainwindow.h \
    app/testmain.h \
    model/db/falconviewdb.h \
    model/toolcategory.h \
    model/tool.h \
    util/abstractcondition.h \
    util/andcondition.h \
    util/dynaaction.h \
    util/equalcondition.h \
    util/falsecondition.h \
    util/greatercondition.h \
    util/micon.h \
    util/multistateaction.h \
    util/multistatetoolbutton.h \
    util/notcondition.h \
    util/orcondition.h \
    util/smallercondition.h \
    util/truecondition.h \
    view/dyndockable.h \
  view/plugindialog.h

FORMS += \
    UI/mainwindow.ui

unix:!mac {
  LIBS += -Wl,-rpath=$${LINUXCNC}/lib
  QMAKE_CXXFLAGS += -std=gnu++11
}

LIBS += \
  -L../lcLib \
  -L../baselib \
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

LIBS += -Wl,-rpath=$${OCCT}/lin64/gcc/libd \
        -L$${OCCT}/lin64/gcc/libd
LIBS += -lTKernel -lTKMath -lTKService -lTKV3d -lTKOpenGl \
        -lTKBRep -lTKIGES -lTKSTL -lTKVRML -lTKSTEP -lTKSTEPAttr -lTKSTEP209 \
        -lTKSTEPBase -lTKGeomBase -lTKGeomAlgo -lTKG3d -lTKG2d \
        -lTKXSBase -lTKShHealing -lTKHLR -lTKTopAlgo -lTKMesh -lTKPrim \
        -lTKCDF -lTKBool -lTKBO -lTKFillet -lTKOffset -lTKLCAF -lTKCAF -lTKVCAF \
        -lTKBin -lTKXml

TRANSLATIONS += \
    i18n/FalconView_de_DE.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#DISTFILES += \
#    docs/FalconView.qdocconf \
#    docs/FalconView.qhp \
#    docs/genHelp \
#    docs/src/FixtureManager.qdoc \
#    docs/src/JogView.qdoc \
#    docs/src/LCToolTable.qdoc \
#    docs/src/MDIedit.qdoc \
#    docs/src/PreferencesEditor.qdoc \
#    docs/src/Preview.qdoc \
#    docs/src/SettingsNotebook.qdoc \
#    docs/src/TestEdit.qdoc \
#    docs/src/ToolEditor.qdoc \
#    docs/src/ToolManager.qdoc \
#    docs/src/fileManager.qdoc \
#    docs/src/index.qdoc \
#    docs/src/pathEdit.qdoc \
#    docs/src/reference.qdoc \
#    docs/src/startup.qdoc \
#    docs/src/usage.qdoc \
#    docs/src.de/index.qdoc \
#    docs/html/FalconView.qhcp \
#    i18n/FalconView_de_DE.ts

#QMAKE_SPEC - the shortname of the host mkspec that is resolved and stored in the QMAKESPEC variable during a host build
#QMAKE_VERSION - the current version of qmake
#QMAKE_XSPEC - the shortname of the target mkspec that is resolved and stored in the QMAKESPEC variable during a target build
#QT_HOST_BINS - location of host executables
#QT_HOST_DATA - location of data for host executables used by qmake
#QT_HOST_PREFIX - default prefix for all host paths
#QT_INSTALL_ARCHDATA - location of general architecture-dependent Qt data
#QT_INSTALL_BINS - location of Qt binaries (tools and applications)
#QT_INSTALL_CONFIGURATION - location for Qt settings. Not applicable on Windows
#QT_INSTALL_DATA - location of general architecture-independent Qt data
#QT_INSTALL_DOCS - location of documentation
#QT_INSTALL_EXAMPLES - location of examples
#QT_INSTALL_HEADERS - location for all header files
#QT_INSTALL_IMPORTS - location of QML 1.x extensions
#QT_INSTALL_LIBEXECS - location of executables required by libraries at runtime
#QT_INSTALL_LIBS - location of libraries
#QT_INSTALL_PLUGINS - location of Qt plugins
#QT_INSTALL_PREFIX - default prefix for all paths
#QT_INSTALL_QML - location of QML 2.x extensions
#QT_INSTALL_TESTS - location of Qt test cases
#QT_INSTALL_TRANSLATIONS - location of translation information for Qt strings
#QT_SYSROOT - the sysroot used by the target build environment
#QT_VERSION - the Qt version. We recommend that you query Qt module specific version numbers 
#for (var, $$list($$enumerate_vars())) {
#    message($$var)
#    message($$eval($$var))
#    }


RESOURCES += ../FalconView.qrc

INSTALLS += target docs
