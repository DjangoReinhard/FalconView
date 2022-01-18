QT_FOR_CONFIG += widgets
requires(qtConfig(inputdialog))

TEMPLATE = subdirs
POST_TARGETDEPS = copy
SUBDIRS = \
  src/app \
  src/baselib \
  src/guiLib \
  src/nbPages \
  src/plugPages \
  src/statusInfo \
  docs

#QMAKE_EXTRA_TARGETS = copy
#
#copy.commands = cd ../FalconView && for i in $( find . -name *.qm ); do cp $i i18n; done

#src.app.depends = src/baselib
#src.lcLib.depends = src/baselib
#src.statusInfo.CurCodes.depends = src/baselib
#src.statusInfo.Position.depends = src/baselib
#src.statusInfo.SpeedInfo.depends = src/baselib
#src.statusInfo.ToolInfo.depends = src/baselib
#src.plugPages.FixtureManager.depends = src/lcLib
#src.plugPages.HelpView.depends = src/lcLib
#src.plugPages.JogView.depends = src/lcLib
#src.plugPages.LCToolTable.depends = src/lcLib
#src.plugPages.MDIEditor.depends = src/lcLib
#src.plugPages.PathEditor.depends = src/lcLib
#src.plugPages.PrefsEditor.depends = src/baselib
#src.plugPages.Preview3D.depends = src/lcLib
#src.plugPages.SysEventView.depends = src/baselib
#src.plugPages.ToolManager.depends = src/lcLib
