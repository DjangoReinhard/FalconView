QT += core gui uitools sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES *= QT_USE_QSTRINGBUILDER

TARGET = FalconView

INCLUDEPATH += \
    src/app \
    src/model \
    src/nml  \
    src/rs274 \
    src/util \
    src/view \
    src/view/dockable \
    /usr/include/python3.9 \
    lc/include \
    lc/src/emc/rs274ngc \
    lc/src/emc/tooldata \
    lc/src \
    /usr/local/src/build-occt-Desktop_5_15_opt-Debug/include/opencascade


SOURCES += \
    src/app/main.cpp \
    src/app/mainwindow.cpp \
    src/app/core.cpp \
    src/model/configacc.cpp \
    src/model/configmgr.cpp \
    src/model/category.cpp \
    src/model/CategoryTreeModel.cpp \
    src/model/dbconnection.cpp \
    src/model/direntry.cpp \
    src/model/dirmodel.cpp \
    src/model/filemodel.cpp \
    src/model/gcodeinfo.cpp \
    src/model/lcproperties.cpp \
    src/model/positioncalculator.cpp \
    src/model/toolcategory.cpp \
    src/model/toolcategorymodel.cpp \
    src/model/tool.cpp \
    src/model/toolentry.cpp \
    src/model/toolmodel.cpp \
    src/model/tooltable.cpp \
    src/model/valuemanager.cpp \
    src/model/valuemodel.cpp \
    src/nml/statusreader.cpp \
    src/rs274/canonif.cpp \
    src/rs274/linecodes.cpp \
    src/rs274/stupidtoolchangerif.cpp \
    src/util/abstractcondition.cpp \
    src/util/axismask.cpp \
    src/util/equalcondition.cpp \
    src/util/gcodehighlighter.cpp \
    src/util/greatercondition.cpp \
    src/util/LCInter.cpp \
    src/util/flowlayout.cpp \
    src/util/smallercondition.cpp \
    src/view/dockable/curcodesdockable.cpp \
    src/view/dockable/dockable.cpp \
    src/view/dockable/editordockable.cpp \
    src/view/dockable/maindockable.cpp \
    src/view/dockable/positiondockable.cpp \
    src/view/dockable/speedinfodockable.cpp \
    src/view/dockable/toolinfodockable.cpp \
    src/view/DocumentCommon.cxx \
    src/view/dynwidget.cpp \
    src/view/filemanager.cpp \
    src/view/fixturemanager.cpp \
    src/view/gcodeeditor.cpp \
    src/view/gcodeviewer.cpp \
    src/view/graphicfactory.cpp \
    src/view/labeladapter.cpp \
    src/view/mainview.cpp \
    src/view/micon.cpp \
    src/view/occtviewer.cpp \
    src/view/overlay.cpp \
    src/view/pweditor.cpp \
    src/view/patheditor.cpp \
    src/view/fixtureedit.cpp \
    src/view/settingseditor.cpp \
    src/view/splitwidget.cpp \
    src/view/testEdit.cpp \
    src/view/tooleditor.cpp \
    src/view/toolmanager.cpp \

HEADERS += \
    src/app/core_p.h \
    src/app/mainwindow.h \
    src/app/core.h \
    src/model/configacc.h \
    src/model/configmgr.h \
    src/model/category.h \
    src/model/CategoryTreeModel.h \
    src/model/dbconnection.h \
    src/model/direntry.h \
    src/model/dirmodel.h \
    src/model/filemodel.h \
    src/model/gcodeinfo.h \
    src/model/lcproperties.h \
    src/model/positioncalculator.h \
    src/model/toolcategory.h \
    src/model/toolcategorymodel.h \
    src/model/toolentry.h \
    src/model/tool.h \
    src/model/toolmodel.h \
    src/model/tooltable.h \
    src/model/valuemanager.h \
    src/model/valuemodel.h \
    src/nml/insulatePose.h \
    src/nml/statusreader.h \
    src/rs274/canonif.h \
    src/rs274/linecodes.h \
    src/rs274/stupidtoolchangerif.h \
    src/util/abstractcondition.h \
    src/util/axismask.h \
    src/util/equalcondition.h \
    src/util/filemanagerclient.h \
    src/util/gcodehighlighter.h \
    src/util/greatercondition.h \
    src/util/KeyCodes.h \
    src/util/LCInter.h \
    src/util/flowlayout.h \
    src/util/smallercondition.h \
    src/view/dockable/curcodesdockable.h \
    src/view/dockable/dockable.h \
    src/view/dockable/editordockable.h \
    src/view/dockable/maindockable.h \
    src/view/dockable/positiondockable.h \
    src/view/dockable/speedinfodockable.h \
    src/view/dockable/toolinfodockable.h \
    src/view/DocumentCommon.h \
    src/view/dynwidget.h \
    src/view/filemanager.h \
    src/view/fixturemanager.h \
    src/view/gcodeeditor.h \
    src/view/gcodeviewer.h \
    src/view/graphicfactory.h \
    src/view/labeladapter.h \
    src/view/mainview.h \
    src/view/micon.h \
    src/view/overlay.h \
    src/view/occtviewer.h \
    src/view/pweditor.h \
    src/view/patheditor.h \
    src/view/fixtureedit.h \
    src/view/settingseditor.h \
    src/view/splitwidget.h \
    src/view/testEdit.h \
    src/view/tooleditor.h \
    src/view/toolmanager.h \


FORMS += \
    src/UI/CurCodes.ui \
    src/UI/GCodeEditor.ui \
    src/UI/mainwindow.old.ui \
    src/UI/mainwindow.ui \
    src/UI/Fixture.ui \
    src/UI/Overlay.ui \
    src/UI/Position.ui \
    src/UI/Settings.ui \
    src/UI/SpeedInfo.ui \
    src/UI/ToolEditor.ui \
    src/UI/ToolInfo.ui \

unix:!mac {
  LIBS += -Wl,-rpath=$${_PRO_FILE_PWD_}/lc/lib
  QMAKE_CXXFLAGS += -std=gnu++11
}

LIBS += \
  -L$${_PRO_FILE_PWD_}/lc/lib \
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

LIBS += -L/usr/local/src/build-occt-Desktop_5_15_opt-Debug/lin64/gcc/libd
LIBS += -lTKernel -lTKMath -lTKService -lTKV3d -lTKOpenGl \
        -lTKBRep -lTKIGES -lTKSTL -lTKVRML -lTKSTEP -lTKSTEPAttr -lTKSTEP209 \
        -lTKSTEPBase -lTKGeomBase -lTKGeomAlgo -lTKG3d -lTKG2d \
        -lTKXSBase -lTKShHealing -lTKHLR -lTKTopAlgo -lTKMesh -lTKPrim \
        -lTKCDF -lTKBool -lTKBO -lTKFillet -lTKOffset -lTKLCAF -lTKCAF -lTKVCAF \
        -lTKBin -lTKXml

TRANSLATIONS += \
    src/i18n/FalconView_de_DE.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    src/i18n/FalconView_de_DE.ts

RESOURCES += FalconView.qrc
