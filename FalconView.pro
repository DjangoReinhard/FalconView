QT_FOR_CONFIG += widgets
requires(qtConfig(inputdialog))

TEMPLATE = subdirs
SUBDIRS = \
  src/baselib \
  src/lcLib \
  src/plugPages \
  src/app

src.app.depends = src/baselib
src.lcLib.depends = src/baselib
src.plugPages.FixtureManager.depends = src/lcLib
src.plugPages.HelpView.depends = src/lcLib
src.plugPages.JogView.depends = src/lcLib
src.plugPages.LCToolTable.depends = src/lcLib
src.plugPages.MDIEditor.depends = src/lcLib
src.plugPages.PathEditor.depends = src/lcLib
src.plugPages.PrefsEditor.depends = src/baselib
src.plugPages.Preview3D.depends = src/lcLib
src.plugPages.SysEventView.depends = src/baselib
src.plugPages.ToolManager.depends = src/lcLib
