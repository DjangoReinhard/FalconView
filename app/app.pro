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
    model \
    control \
    util \
    view \
    ../baselib/model \
    ../baselib/control \
    ../baselib/util \
    ../baselib/view \
    ../lcLib/model \
    ../lcLib/control \
    ../lcLib/util \
    ../lcLib/view \
    /usr/include/python3.9 \    # only linuxcnc uses python
    $${LINUXCNC}/include \
    $${LINUXCNC}/src/emc/rs274ngc \
    $${LINUXCNC}/src/emc/tooldata \
    $${LINUXCNC}/src \
    $${OCCT}/include/opencascade

TEST_SOURCES += \
    test/testDB.cpp \
    test/testengine.cpp \

SOURCES += \
    main.cpp \
    model/falconviewdb.cpp \
    model/tool.cpp \
    model/toolcategory.cpp \
    control/dynaaction.cpp \
    control/equalcondition.cpp \
    control/falsecondition.cpp \
    control/greatercondition.cpp \
    control/mainwindow.cpp \
    control/multistatetoolbutton.cpp \
    control/notcondition.cpp \
    control/orcondition.cpp \
    control/smallercondition.cpp \
    control/testmain.cpp \
    control/truecondition.cpp \
    control/abstractcondition.cpp \
    control/andcondition.cpp \
    util/multistateaction.cpp \
    view/dyndockable.cpp \
    view/micon.cpp \
    view/plugindialog.cpp

HEADERS += \
    model/falconviewdb.h \
    model/tool.h \
    model/toolcategory.h \
    control/dynaaction.h \
    control/equalcondition.h \
    control/falsecondition.h \
    control/greatercondition.h \
    control/mainwindow.h \
    control/multistatetoolbutton.h \
    control/notcondition.h \
    control/orcondition.h \
    control/smallercondition.h \
    control/testmain.h \
    control/truecondition.h \
    control/abstractcondition.h \
    control/andcondition.h \
    util/multistateaction.h \
    view/dyndockable.h \
    view/micon.h \
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

