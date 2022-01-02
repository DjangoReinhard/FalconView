TEMPLATE = app
TARGET   = FalconView
CONFIG  += c++17
QT      += widgets gui-private uitools sql xml
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES *= QT_USE_QSTRINGBUILDER
LINUXCNC = /usr/local/src/linuxcnc-deb11
OCCT     = /usr/local

INCLUDEPATH += \
    /usr/include/python3.9 \    # only linuxcnc uses python
    $${LINUXCNC}/include \
    $${LINUXCNC}/src/emc/rs274ngc \
    $${LINUXCNC}/src/emc/tooldata \
    $${LINUXCNC}/src \
    $${OCCT}/include/opencascade \

INCLUDEPATH += \
    src/app/control \
    src/app/model \
    src/app/util \
    src/app/view \
    src/baselib/control \
    src/baselib/model \
    src/baselib/util \
    src/baselib/view \
    src/lcLib/control \
    src/lcLib/model \
    src/lcLib/util \
    src/lcLib/view \
    src/plugPages \
    src/statusInfo

SOURCES += \
    src/app/main.cpp \
    src/app/control/abstractcondition.cpp \
    src/app/control/andcondition.cpp \
    src/app/control/dynaaction.cpp \
    src/app/control/equalcondition.cpp \
    src/app/control/falsecondition.cpp \
    src/app/control/greatercondition.cpp \
    src/app/control/mainwindow.cpp \
    src/app/control/multistatetoolbutton.cpp \
    src/app/control/notcondition.cpp \
    src/app/control/orcondition.cpp \
    src/app/control/smallercondition.cpp \
    src/app/control/testmain.cpp \
    src/app/control/truecondition.cpp \
    src/app/model/falconviewdb.cpp \
    src/app/model/tool.cpp \
    src/app/model/toolcategory.cpp \
    src/app/util/multistateaction.cpp \
  src/app/view/dockable.cpp \
    src/app/view/micon.cpp \
    src/app/view/plugindialog.cpp \
    src/baselib/control/core.cpp \
    src/baselib/control/kernel.cpp \
    src/baselib/model/configacc.cpp \
    src/baselib/model/configmgr.cpp \
    src/baselib/model/direntry.cpp \
    src/baselib/model/dirmodel.cpp \
    src/baselib/model/filemodel.cpp \
    src/baselib/model/sysevent.cpp \
    src/baselib/model/syseventmodel.cpp \
    src/baselib/model/valuemanager.cpp \
    src/baselib/model/valuemodel.cpp \
    src/baselib/util/dbconnection.cpp \
    src/baselib/util/flowlayout.cpp \
    src/baselib/util/kernelcreator.cpp \
    src/baselib/util/timestamp.cpp \
    src/lcLib/control/LCInter.cpp \
    src/lcLib/control/axismask.cpp \
    src/lcLib/control/canonif.cpp \
    src/lcLib/control/canonifsettings.cpp \
    src/lcLib/control/commandwriter.cpp \
    src/lcLib/control/errorreader.cpp \
    src/lcLib/control/gcodehighlighter.cpp \
    src/lcLib/control/guicore.cpp \
    src/lcLib/control/guikernel.cpp \
    src/lcLib/control/helpengine.cpp \
    src/lcLib/control/positioncalculator.cpp \
    src/lcLib/control/statusreader.cpp \
    src/lcLib/model/lcproperties.cpp \
    src/lcLib/model/linecodes.cpp \
    src/lcLib/model/stupidtoolchangerif.cpp \
    src/lcLib/model/toolentry.cpp \
    src/lcLib/model/tooltable.cpp \
    src/lcLib/util/Geom_HelixData.cpp \
    src/lcLib/util/HHelixCurveAdaptor.cpp \
    src/lcLib/util/HelixCurveAdaptor.cpp \
    src/lcLib/util/HelixCurveAdaptor_CylinderEvaluator.cpp \
    src/lcLib/util/ally3d.cpp \
    src/lcLib/util/graphicfactory.cpp \
    src/lcLib/util/guikernelcreator.cpp \
    src/lcLib/util/pluginpagefactory.cpp \
    src/lcLib/view/abscenterwidget.cpp \
    src/lcLib/view/filemanager.cpp \
    src/lcLib/view/centerpage.cpp \
    src/lcLib/view/centerview.cpp \
    src/lcLib/view/gcodeeditor.cpp \
    src/lcLib/view/gcodeinfo.cpp \
    src/lcLib/view/helpcontentwidget.cpp \
    src/lcLib/view/helpkeywordwidget.cpp \
    src/lcLib/view/helpbrowser.cpp \
    src/lcLib/view/helpdockable.cpp \
    src/lcLib/view/helpview.cpp \
    src/lcLib/view/jogbutton.cpp \
    src/lcLib/view/numlabel.cpp \
    src/lcLib/view/occtviewer.cpp \
    src/lcLib/view/settingsnb.cpp \
    src/lcLib/view/testEdit.cpp \
    src/plugPages/FixtureManager/fixtureedit.cpp \
    src/plugPages/FixtureManager/fixturemanager.cpp \
    src/plugPages/JogView/jogview.cpp \
    src/plugPages/LCToolTable/lctooltable.cpp \
    src/plugPages/MDIEditor/mdieditor.cpp \
    src/plugPages/PathEditor/patheditor.cpp \
    src/plugPages/PrefsEditor/preferenceseditor.cpp \
    src/plugPages/Preview3D/pweditor.cpp \
    src/plugPages/SysEventView/syseventview.cpp \
    src/plugPages/ToolManager/CategoryTreeModel.cpp \
    src/plugPages/ToolManager/category.cpp \
    src/plugPages/ToolManager/toolcategorymodel.cpp \
    src/plugPages/ToolManager/tooleditor.cpp \
    src/plugPages/ToolManager/toolmanager.cpp \
    src/plugPages/ToolManager/toolmodel.cpp \
    src/statusInfo/CurCodes/curcodesstatus.cpp \
    src/statusInfo/Position/positionstatus.cpp \
    src/statusInfo/SpeedInfo/speedstatus.cpp \
    src/statusInfo/ToolInfo/toolstatus.cpp \

HEADERS += \
    src/app/control/abstractcondition.h \
    src/app/control/andcondition.h \
    src/app/control/dynaaction.h \
    src/app/control/equalcondition.h \
    src/app/control/falsecondition.h \
    src/app/control/greatercondition.h \
    src/app/control/mainwindow.h \
    src/app/control/multistatetoolbutton.h \
    src/app/control/notcondition.h \
    src/app/control/orcondition.h \
    src/app/control/smallercondition.h \
    src/app/control/testmain.h \
    src/app/control/truecondition.h \
    src/app/model/falconviewdb.h \
    src/app/model/toolcategory.h \
    src/app/model/tool.h \
    src/app/util/multistateaction.h \
    src/app/view/dockable.h \
    src/app/view/micon.h \
    src/app/view/plugindialog.h \
    src/baselib/control/applicationmode.h \
    src/baselib/control/core.h \
    src/baselib/control/filemanagerclient.h \
    src/baselib/control/kernel.h \
    src/baselib/model/configacc.h \
    src/baselib/model/configmgr.h \
    src/baselib/model/direntry.h \
    src/baselib/model/dirmodel.h \
    src/baselib/model/filemodel.h \
    src/baselib/model/sysevent.h \
    src/baselib/model/syseventmodel.h \
    src/baselib/model/valuemanager.h \
    src/baselib/model/valuemodel.h \
    src/baselib/util/dbconnection.h \
    src/baselib/util/dbhelper.h \
    src/baselib/util/flowlayout.h \
    src/baselib/util/kernelcreator.h \
    src/baselib/util/timestamp.h \
    src/baselib/view/PluginPageInterface.h \
    src/lcLib/control/axismask.h \
    src/lcLib/control/canonif.h \
    src/lcLib/control/canonifsettings.h \
    src/lcLib/control/commandwriter.h \
    src/lcLib/control/errorreader.h \
    src/lcLib/control/gcodehighlighter.h \
    src/lcLib/control/guicore.h \
    src/lcLib/control/guikernel.h \
    src/lcLib/control/helpengine.h \
    src/lcLib/control/LCInter.h \
    src/lcLib/control/positioncalculator.h \
    src/lcLib/control/statusreader.h \
    src/lcLib/model/lcproperties.h \
    src/lcLib/model/linecodes.h \
    src/lcLib/model/stupidtoolchangerif.h \
    src/lcLib/model/toolentry.h \
    src/lcLib/model/tooltable.h \
    src/lcLib/util/ally3d.h \
    src/lcLib/util/Geom_HelixData.h \
    src/lcLib/util/graphicfactory.h \
    src/lcLib/util/guikernelcreator.h \
    src/lcLib/util/HelixCurveAdaptor_CylinderEvaluator.h \
    src/lcLib/util/HelixCurveAdaptor.h \
    src/lcLib/util/HelixCurveAdaptor_p.h \
    src/lcLib/util/HHelixCurveAdaptor.h \
    src/lcLib/util/insulatePose.h \
    src/lcLib/util/pluginpagefactory.h \
    src/lcLib/view/abscenterwidget.h \
    src/lcLib/view/filemanager.h \
    src/lcLib/view/centerpage.h \
    src/lcLib/view/centerview.h \
    src/lcLib/view/gcodeeditor.h \
    src/lcLib/view/gcodeinfo.h \
    src/lcLib/view/helpcontentwidget.h \
    src/lcLib/view/helpkeywordwidget.h \
    src/lcLib/view/helpbrowser.h \
    src/lcLib/view/helpdockable.h \
    src/lcLib/view/helpview.h \
    src/lcLib/view/jogbutton.h \
    src/lcLib/view/numlabel.h \
    src/lcLib/view/occtviewer.h \
    src/lcLib/view/settingsnb.h \
    src/lcLib/view/testEdit.h \
    src/plugPages/FixtureManager/fixtureedit.h \
    src/plugPages/FixtureManager/fixturemanager.h \
    src/plugPages/JogView/jogview.h \
    src/plugPages/LCToolTable/lctooltable.h \
    src/plugPages/MDIEditor/mdieditor.h \
    src/plugPages/PathEditor/patheditor.h \
    src/plugPages/PrefsEditor/preferenceseditor.h \
    src/plugPages/Preview3D/pweditor.h \
    src/plugPages/SysEventView/syseventview.h \
    src/plugPages/ToolManager/category.h \
    src/plugPages/ToolManager/CategoryTreeModel.h \
    src/plugPages/ToolManager/toolcategorymodel.h \
    src/plugPages/ToolManager/tooleditor.h \
    src/plugPages/ToolManager/toolmanager.h \
    src/plugPages/ToolManager/toolmodel.h \
    src/statusInfo/CurCodes/curcodesstatus.h \
    src/statusInfo/Position/positionstatus.h \
    src/statusInfo/SpeedInfo/speedstatus.h \
    src/statusInfo/ToolInfo/toolstatus.h \

FORMS += \
    src/app/UI/mainwindow.ui \
    src/lcLib/UI/GCodeEditor.ui \
    src/lcLib/UI/HelpTitle.ui \
    src/plugPages/FixtureManager/Fixture.ui \
    src/plugPages/JogView/Jog.ui \
    src/plugPages/MDIEditor/MDIEditor.ui \
    src/plugPages/PrefsEditor/Settings.ui \
    src/plugPages/ToolManager/ToolEditor.ui \
    src/statusInfo/CurCodes/HCurCodes.ui \
    src/statusInfo/CurCodes/VCurCodes.ui \
    src/statusInfo/Position/PositionMain.ui \
    src/statusInfo/Position/Position.ui \
    src/statusInfo/SpeedInfo/HSpeedInfo.ui \
    src/statusInfo/SpeedInfo/VSpeedInfo.ui \
    src/statusInfo/ToolInfo/ToolInfo.ui \

TRANSLATIONS += \
    src/app/i18n/FalconView_de_DE.ts \
    src/baselib/baselib_de_DE.ts \
    src/lcLib/lcLib_de_DE.ts \
    src/plugPages/FixtureManager/fixture_de_DE.ts \
    src/plugPages/JogView/jogview_de_DE.ts \
    src/plugPages/LCToolTable/lctooltable_de_DE.ts \
    src/plugPages/MDIEditor/mdieditor_de_DE.ts \
    src/plugPages/PathEditor/patheditor_de_DE.ts \
    src/plugPages/PrefsEditor/prefseditor_DE.ts \
    src/plugPages/Preview3D/preview3D_de_DE.ts \
    src/plugPages/SysEventView/syseventview_de_DE.ts \
    src/plugPages/ToolManager/toolmanager_de_DE.ts \
    src/statusInfo/CurCodes/curcodes_de_DE.ts \
    src/statusInfo/Position/position_de_DE.ts \
    src/statusInfo/SpeedInfo/speedinfo_de_DE.ts \
    src/statusInfo/ToolInfo/toolinfo_de_DE.ts \

RESOURCES += \
    FalconView.qrc

unix:!mac {
  LIBS += -Wl,-rpath=$${LINUXCNC}/lib
  LIBS += -Wl,-rpath=$${OCCT}/lib
  QMAKE_CXXFLAGS += -std=gnu++11
}

LIBS += -L$${LINUXCNC}/lib
LIBS += -L/usr/lib
LIBS += \
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

LIBS += -L$${OCCT}/lib
LIBS += -lTKernel -lTKMath -lTKService -lTKV3d -lTKOpenGl \
        -lTKBRep -lTKIGES -lTKSTL -lTKVRML -lTKSTEP -lTKSTEPAttr -lTKSTEP209 \
        -lTKSTEPBase -lTKGeomBase -lTKGeomAlgo -lTKG3d -lTKG2d \
        -lTKXSBase -lTKShHealing -lTKHLR -lTKTopAlgo -lTKMesh -lTKPrim \
        -lTKCDF -lTKBool -lTKBO -lTKFillet -lTKOffset -lTKLCAF -lTKCAF -lTKVCAF \
        -lTKBin -lTKXml

