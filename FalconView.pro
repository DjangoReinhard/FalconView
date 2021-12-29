QT_FOR_CONFIG += widgets
requires(qtConfig(inputdialog))

TEMPLATE = subdirs
SUBDIRS = \
  baselib \
  lcLib \
  plugPages \
  app

app.depends = baselib
lcLib.depends = baselib
plugPages.FixtureManager.depends = lcLib
plugPages.HelpView.depends = lcLib
plugPages.JogView.depends = lcLib
plugPages.LCToolTable.depends = lcLib
plugPages.MDIEditor.depends = lcLib
plugPages.PathEditor.depends = lcLib
plugPages.PrefsEditor.depends = baselib
plugPages.Preview3D.depends = lcLib
plugPages.SysEventView.depends = baselib
plugPages.ToolManager.depends = lcLib
