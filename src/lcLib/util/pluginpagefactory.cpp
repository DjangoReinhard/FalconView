#include "pluginpagefactory.h"
#include <abscenterwidget.h>
#include <dbconnection.h>
#include <valuemanager.h>
#include <configacc.h>
#include <axismask.h>
#include <guicore.h>
#include <guikernel.h>
#include <lcproperties.h>
#include <filemanager.h>
#include <settingsnb.h>
#include <testEdit.h>
#include <helpview.h>
#ifndef USE_PLUGINS
# include <Position/positionstatus.h>
# include <ToolInfo/toolstatus.h>
# include <SpeedInfo/speedstatus.h>
# include <CurCodes/curcodesstatus.h>

# include <JogView/jogview.h>
# include <MDIEditor/mdieditor.h>
# include <SysEventView/syseventview.h>
# include <LCToolTable/lctooltable.h>
# include <Preview3D/pweditor.h>
# include <PathEditor/patheditor.h>
# include <PrefsEditor/preferenceseditor.h>
# include <FixtureManager/fixturemanager.h>
# include <ToolManager/toolmanager.h>
#endif

PluginPageFactory::PluginPageFactory()
 : core(nullptr)
 , cfg(nullptr)
 , vm(nullptr) {
  core     = new GuiCore();
  cfg      = new Config();
  vm       = new ValueManager();
  Kernel*       check  = GuiCore().kernel;
  OcctQtViewer* view3D = GuiCore().view3D();

  qDebug() << "kernel address in main-app: " << check
           << "view3D address in main-app: " << view3D;
  }


PluginPageFactory::~PluginPageFactory() {
  }


AbstractCenterWidget* PluginPageFactory::createCenterPage(const QString& name) {
  AbstractCenterWidget* rv = static_cast<AbstractCenterWidget*>(GuiCore().pluggablePage(name));

  if (rv) {
     qDebug() << "PPF: process loaded plugin for page named: " << name;
     }
  if (name == "FileManager") {
     rv = new FileManager(GuiCore().lcProperties().getPath("DISPLAY", "PROGRAM_PREFIX"));
     rv->patch(GuiCore::kernel, Config::cfg, ValueManager::instance);
     rv->initialize();
     }
  else if (name == "SettingsNotebook") {
     rv = new SettingsNotebook();
     rv->patch(GuiCore::kernel, Config::cfg, ValueManager::instance);
     rv->initialize();
     }
  else if (name == "TestEdit") {
     rv = new TestEdit();
     rv->patch(GuiCore::kernel, Config::cfg, ValueManager::instance);
     rv->initialize(":/src/lcLib/view/GCodeEditor.ui");
     }
  else if (name == "HelpView") {
     rv = new HelpView();
     rv->patch(GuiCore::kernel, Config::cfg, ValueManager::instance);
     rv->initialize();
     }
  else if (name == "Preview3D") {
#ifndef USE_PLUGINS
     rv = new PreViewEditor();
#else
     if (!rv) return rv;
     assert(rv);
#endif
     rv->patch(GuiCore::kernel, Config::cfg, ValueManager::instance, GuiCore().view3D());
     rv->initialize(":/src/lcLib/view/GCodeEditor.ui");
     }
  else if (name == "MDIEditor") {
#ifndef USE_PLUGINS
     rv = new MDIEditor();
#else
     if (!rv) return rv;
     assert(rv);
#endif
     rv->patch(GuiCore::kernel, Config::cfg, ValueManager::instance);
     rv->initialize(":/src/plugPages/MDIEditor/MDIEditor.ui");
     }
  else if (name == "SysEventView") {
#ifndef USE_PLUGINS
     rv = new SysEventView();
#else
     if (!rv) return rv;
     assert(rv);
#endif
     rv->patch(GuiCore::kernel, Config::cfg, ValueManager::instance);
     rv->initialize();
     }
  else if (name == "PathEditor") {
#ifndef USE_PLUGINS
     rv = new PathEditor();
#else
     if (!rv) return rv;
     assert(rv);
#endif
     rv->patch(GuiCore::kernel, Config::cfg, ValueManager::instance);
     rv->initialize(":/src/lcLib/view/GCodeEditor.ui");
     }
  else if (name == "ToolManager") {
#ifndef USE_PLUGINS
     rv = new ToolManager();
#else
     if (!rv) return rv;
     assert(rv);
#endif
     rv->patch(GuiCore::kernel, Config::cfg, ValueManager::instance);
     rv->initialize();
     }
  else if (name == "FixtureManager") {
#ifndef USE_PLUGINS
     rv = new FixtureManager();
#else
     if (!rv) return rv;
     assert(rv);
#endif
     rv->patch(GuiCore::kernel, Config::cfg, ValueManager::instance);
     rv->initialize();
     }
  else if (name == "PrefsEditor") {
#ifndef USE_PLUGINS
     rv = new PreferencesEditor();
#else
     if (!rv) return rv;
     assert(rv);
#endif
     rv->patch(GuiCore::kernel, Config::cfg, ValueManager::instance);
     rv->initialize(":/src/plugPages/PrefsEditor/Settings.ui", QString(), true);
     }
  else if (name == "LCToolTable") {
#ifndef USE_PLUGINS
     rv = new LCToolTable();
#else
     if (!rv) return rv;
     assert(rv);
#endif
     rv->patch(GuiCore::kernel, Config::cfg, ValueManager::instance);
     rv->initialize();
     }
  else if (name == "JogView") {
#ifndef USE_PLUGINS
     rv = new JogView();
#else
     if (!rv) return rv;
     assert(rv);
#endif
     rv->patch(GuiCore::kernel, Config::cfg, ValueManager::instance);
     rv->initialize();
     }
  return rv;
  }


AbstractCenterWidget* PluginPageFactory::createDockable(const QString& name, bool horizontal) {
  AbstractCenterWidget* rv = static_cast<AbstractCenterWidget*>(GuiCore().statusInfo(name));

  if (name == "Position") {
#ifndef USE_PLUGINS
     rv = new PositionStatus();
#else
     if (!rv) return rv;
     assert(rv);
#endif
     rv->patch(GuiCore::kernel, Config::cfg, ValueManager::instance);
     rv->initialize(":/src/statusInfo/Position/Position.ui");
     }
  else if (name == "ToolInfo") {
#ifndef USE_PLUGINS
     rv = new ToolStatus();
#else
     if (!rv) return rv;
     assert(rv);
#endif
     rv->patch(GuiCore::kernel, Config::cfg, ValueManager::instance);
     rv->initialize(":/src/statusInfo/ToolInfo/ToolInfo.ui");
     }
  else if (name == "SpeedInfo") {
#ifndef USE_PLUGINS
     rv = new SpeedStatus();
#else
     if (!rv) return rv;
     assert(rv);
#endif
     rv->patch(GuiCore::kernel, Config::cfg, ValueManager::instance);
     rv->initialize(horizontal ? ":/src/statusInfo/SpeedInfo/HSpeedInfo.ui"
                               : ":/src/statusInfo/SpeedInfo/VSpeedInfo.ui");
     }
  else if (name == "CurCodes") {
#ifndef USE_PLUGINS
     rv = new CurCodesStatus();
#else
     if (!rv) return rv;
     assert(rv);
#endif
     rv->patch(GuiCore::kernel, Config::cfg, ValueManager::instance);
     rv->initialize(horizontal ? ":/src/statusInfo/CurCodes/HCurCodes.ui"
                               : ":/src/statusInfo/CurCodes/VCurCodes.ui" );
     }
  return rv;
  }
