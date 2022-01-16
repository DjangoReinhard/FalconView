#include "pluginpagefactory.h"
#include <abscenterwidget.h>
#include <dbconnection.h>
#include <valuemanager.h>
#include <configacc.h>
//#include <axismask.h>
#include <guicore.h>
//#include <guikernel.h>
//#include <lcproperties.h>
#include <filemanager.h>
#include <settingsnb.h>
#include <testEdit.h>
#include <helpview.h>
#include <QDir>
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
  KernelInterface* check  = GuiCore().kernel;
  OcctQtViewer*    view3D = GuiCore().view3D();

  qDebug() << "kernel address in main-app: " << check
           << "view3D address in main-app: " << view3D;
  }


PluginPageFactory::~PluginPageFactory() {
  delete core;
  delete cfg;
  delete vm;
  }


AbstractCenterWidget* PluginPageFactory::createCenterPage(const QString& name) {
  AbstractCenterWidget* rv = static_cast<AbstractCenterWidget*>(GuiCore().pluggableMainPage(name));

  if (rv) {
     qDebug() << "PPF: process loaded plugin for center page named: " << name;
     }
  if (name == "FileManager")           rv = new FileManager(QDir(GuiCore().fileName4("nc_files")));
  else if (name == "SettingsNotebook") rv = new SettingsNotebook();
  else if (name == "TestEdit")         rv = new TestEdit();
  else if (name == "HelpView")         rv = new HelpView();
  else if (name == "Preview3D") {
#ifndef USE_PLUGINS
     rv = new PreViewEditor();
#endif
     if (!rv) return rv;
     assert(rv);
     rv->patch(GuiCore::kernel, Config::cfg, ValueManager::instance, GuiCore().view3D());
     rv->initialize();

     return rv;
     }
  else {
#ifndef USE_PLUGINS
     if (name == "MDIEditor") rv = new MDIEditor();
     else if (name = "SysEventView") rv = SysEventView();
     else if (name = "PathEditor") rv = PathEditor();
     else if (name = "JogView") rv = JogView();
#endif
     }
  if (!rv) return rv;
  assert(rv);
  rv->patch(GuiCore::kernel, Config::cfg, ValueManager::instance);
  rv->initialize();

  return rv;
  }


AbstractCenterWidget* PluginPageFactory::createNotebookPage(const QString& name) {
  AbstractCenterWidget* rv = static_cast<AbstractCenterWidget*>(GuiCore().pluggableNotebookPage(name));

  if (rv) {
     qDebug() << "PPF: process loaded plugin for notebook page named: " << name;
     }
#ifndef USE_PLUGINS
  if (name == "ToolManager")         rv = new ToolManager();
  else if (name == "FixtureManager") rv = new FixtureManager();
  else if (name == "PrefsEditor")    rv = new PreferencesEditor();
  else if (name == "LCToolTable")    rv = new LCToolTable();
#else
  if (!rv) return rv;
  assert(rv);
#endif
  rv->patch(GuiCore::kernel, Config::cfg, ValueManager::instance);
  rv->initialize();

  return rv;
  }


AbstractCenterWidget* PluginPageFactory::createDockable(const QString& name, bool horizontal) {
  AbstractCenterWidget* rv = static_cast<AbstractCenterWidget*>(GuiCore().statusInfo(name));

  if (rv) {
     qDebug() << "PPF: process loaded plugin for dockable named: " << name;
     }
#ifndef USE_PLUGINS
  if (name == "Position")       rv = new PositionStatus();
  else if (name == "ToolInfo")  rv = new ToolStatus();
  else if (name == "SpeedInfo") rv = new SpeedStatus();
  else if (name == "CurCodes")  rv = new CurCodesStatus();
#else
  if (!rv) return rv;
  assert(rv);
#endif
  rv->patch(GuiCore::kernel, Config::cfg, ValueManager::instance);
  rv->initialize();

  return rv;
  }
