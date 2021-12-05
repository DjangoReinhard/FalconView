TEMPLATE = app
QT += core gui gui-private uitools sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES *= QT_USE_QSTRINGBUILDER

TARGET = FalconView

LINUXCNC = /usr/local/src/linuxcnc-deb11
OCCT     = /usr/local/src/build-occt-Desktop_5_15_opt-Debug

INCLUDEPATH += \
    src/app \
    src/model \
    src/model/db \
    src/nml  \
    src/rs274 \
    src/util \
    src/view \
    src/view/pages \
    src/view/status \
    /usr/include/python3.9 \    # only linuxcnc uses python
    $${LINUXCNC}/include \
    $${LINUXCNC}/src/emc/rs274ngc \
    $${LINUXCNC}/src/emc/tooldata \
    $${LINUXCNC}/src \
    $${OCCT}/include/opencascade


SOURCES += \
    src/app/main.cpp \
    src/app/mainwindow.cpp \
    src/app/core.cpp \
    src/model/configacc.cpp \
    src/model/configmgr.cpp \
    src/model/db/category.cpp \
    src/model/db/CategoryTreeModel.cpp \
    src/model/db/dbconnection.cpp \
    src/model/db/falconviewdb.cpp \
    src/model/db/sysevent.cpp \
    src/model/db/syseventmodel.cpp \
    src/model/db/toolcategorymodel.cpp \
    src/model/db/toolmodel.cpp \
    src/model/direntry.cpp \
    src/model/dirmodel.cpp \
    src/model/filemodel.cpp \
    src/model/gcodeinfo.cpp \
    src/model/lcproperties.cpp \
    src/model/positioncalculator.cpp \
    src/model/toolcategory.cpp \
    src/model/tool.cpp \
    src/model/toolentry.cpp \
    src/model/tooltable.cpp \
    src/model/valuemanager.cpp \
    src/model/valuemodel.cpp \
    src/nml/commandwriter.cpp \
    src/nml/errorreader.cpp \
    src/nml/statusreader.cpp \
    src/rs274/canonif.cpp \
    src/rs274/linecodes.cpp \
    src/rs274/stupidtoolchangerif.cpp \
    src/util/abstractcondition.cpp \
    src/util/ally3d.cpp \
    src/util/andcondition.cpp \
    src/util/axismask.cpp \
    src/util/dynaaction.cpp \
    src/util/equalcondition.cpp \
    src/util/falsecondition.cpp \
    src/util/flowlayout.cpp \
    src/util/gcodehighlighter.cpp \
    src/util/Geom_HelixData.cpp \
    src/util/graphicfactory.cpp \
    src/util/greatercondition.cpp \
    src/util/helpengine.cpp \
    src/util/HelixCurveAdaptor_CylinderEvaluator.cpp \
    src/util/HelixCurveAdaptor.cpp \
    src/util/HHelixCurveAdaptor.cpp \
    src/util/LCInter.cpp \
    src/util/labeladapter.cpp \
    src/util/micon.cpp \
    src/util/multistateaction.cpp \
    src/util/multistatetoolbutton.cpp \
    src/util/notcondition.cpp \
    src/util/orcondition.cpp \
    src/util/smallercondition.cpp \
    src/util/timestamp.cpp \
    src/util/truecondition.cpp \
    src/view/helpcontentwidget.cpp \
    src/view/helpdialog.cpp \
    src/view/helpkeywordwidget.cpp \
    src/view/pages/filemanager.cpp \
    src/view/pages/fixturemanager.cpp \
    src/view/pages/jogview.cpp \
    src/view/pages/lctooltable.cpp \
    src/view/pages/patheditor.cpp \
    src/view/pages/preferenceseditor.cpp \
    src/view/pages/pweditor.cpp \
    src/view/pages/syseventview.cpp \
    src/view/pages/testEdit.cpp \
    src/view/pages/toolmanager.cpp \
    src/view/status/curcodesstatus.cpp \
    src/view/status/positionstatus.cpp \
    src/view/status/speedstatus.cpp \
    src/view/status/toolstatus.cpp \
    src/view/centerview.cpp \
    src/view/dyncenterwidget.cpp \
    src/view/dyndockable.cpp \
    src/view/dynframe.cpp \
    src/view/fixtureedit.cpp \
    src/view/gcodeeditor.cpp \
    src/view/htmlbrowser.cpp \
    src/view/occtviewer.cpp \
    src/view/settingsnb.cpp \
    src/view/tooleditor.cpp \

HEADERS += \
    src/app/applicationmode.h \
    src/app/core_p.h \
    src/app/mainwindow.h \
    src/app/core.h \
    src/model/configacc.h \
    src/model/configmgr.h \
    src/model/db/category.h \
    src/model/db/CategoryTreeModel.h \
    src/model/db/dbconnection.h \
    src/model/db/dbhelper.h \
    src/model/db/falconviewdb.h \
    src/model/db/sysevent.h \
    src/model/db/syseventmodel.h \
    src/model/db/toolcategorymodel.h \
    src/model/db/toolmodel.h \
    src/model/direntry.h \
    src/model/dirmodel.h \
    src/model/filemodel.h \
    src/model/gcodeinfo.h \
    src/model/lcproperties.h \
    src/model/positioncalculator.h \
    src/model/toolcategory.h \
    src/model/toolentry.h \
    src/model/tool.h \
    src/model/tooltable.h \
    src/model/valuemanager.h \
    src/model/valuemodel.h \
    src/nml/commandwriter.h \
    src/nml/errorreader.h \
    src/nml/insulatePose.h \
    src/nml/statusreader.h \
    src/rs274/canonif.h \
    src/rs274/linecodes.h \
    src/rs274/stupidtoolchangerif.h \
    src/util/abstractcondition.h \
    src/util/ally3d.h \
    src/util/andcondition.h \
    src/util/axismask.h \
    src/util/dynaaction.h \
    src/util/equalcondition.h \
    src/util/falsecondition.h \
    src/util/filemanagerclient.h \
    src/util/flowlayout.h \
    src/util/gcodehighlighter.h \
    src/util/Geom_HelixData.h \
    src/util/graphicfactory.h \
    src/util/greatercondition.h \
    src/util/helpengine.h \
    src/util/HelixCurveAdaptor_CylinderEvaluator.h \
    src/util/HelixCurveAdaptor_p.h \
    src/util/HelixCurveAdaptor.h \
    src/util/HHelixCurveAdaptor.h \
    src/util/labeladapter.h \
    src/util/LCInter.h \
    src/util/micon.h \
    src/util/multistateaction.h \
    src/util/multistatetoolbutton.h \
    src/util/notcondition.h \
    src/util/orcondition.h \
    src/util/smallercondition.h \
    src/util/timestamp.h \
    src/util/truecondition.h \
    src/view/helpcontentwidget.h \
    src/view/helpdialog.h \
    src/view/helpkeywordwidget.h \
    src/view/pages/filemanager.h \
    src/view/pages/fixturemanager.h \
    src/view/pages/jogview.h \
    src/view/pages/lctooltable.h \
    src/view/pages/patheditor.h \
    src/view/pages/preferenceseditor.h \
    src/view/pages/pweditor.h \
    src/view/pages/syseventview.h \
    src/view/pages/testEdit.h \
    src/view/pages/toolmanager.h \
    src/view/status/curcodesstatus.h \
    src/view/status/positionstatus.h \
    src/view/status/speedstatus.h \
    src/view/status/toolstatus.h \
    src/view/centerview.h \
    src/view/dyncenterwidget.h \
    src/view/dyndockable.h \
    src/view/dynframe.h \
    src/view/fixtureedit.h \
    src/view/gcodeeditor.h \
    src/view/htmlbrowser.h \
    src/view/occtviewer.h \
    src/view/settingsnb.h \
    src/view/tooleditor.h \

FORMS += \
    src/UI/HCurCodes.ui \
    src/UI/HelpTitle.ui \
    src/UI/Jog.ui \
    src/UI/Jog2.ui \
    src/UI/VCurCodes.ui \
    src/UI/GCodeEditor.ui \
    src/UI/mainwindow.ui \
    src/UI/Fixture.ui \
    src/UI/Position.ui \
    src/UI/Settings.ui \
    src/UI/HSpeedInfo.ui \
    src/UI/VSpeedInfo.ui \
    src/UI/ToolEditor.ui \
    src/UI/ToolInfo.ui

unix:!mac {
  LIBS += -Wl,-rpath=$${LINUXCNC}/lib
  QMAKE_CXXFLAGS += -std=gnu++11
}

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
    src/i18n/FalconView_de_DE.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    docs/FalconView.qdocconf \
    docs/FalconView.qhp \
    docs/genHelp \
    docs/src/fileManager.qdoc \
    docs/src/index.qdoc \
    docs/src/reference.qdoc \
    docs/src/startup.qdoc \
    docs/src/usage.qdoc \
    docs/html/FalconView.qhcp \
    i18n/FalconView_de_DE.ts

RESOURCES += FalconView.qrc

INSTALLS += target docs
