#include <testmain.h>
#include <plugindialog.h>
#include <PluginPageInterface.h>
#include <guicore.h>
#include <centerpage.h>
#include <abscenterwidget.h>
#include <configacc.h>
#include <valuemanager.h>
#include <valuemodel.h>
#include <ui_mainwindow.h>
#include <QPluginLoader>
#include <QDir>
#include <QDebug>


TestMain::TestMain(QWidget *parent)
 : QMainWindow(parent)
 , ui(new Ui::MainWindow) {
  }


void TestMain::initialize() {
  ui->setupUi(this);
  pluginsDir = QDir(GuiCore().fileName4("plugins"));

  qDebug() << "app-dir:" << pluginsDir.absolutePath();
  bool   statusInPreview = Config().value("statusInPreview").toBool();
  bool   showHelpAtPageChange = Config().value("showHelpAtPageChange").toBool();
  ValueManager().setValue("statusInPreview", statusInPreview);
  ValueManager().setValue("showHelpAtPageChange", showHelpAtPageChange);
  QColor bgHLLine = ValueManager().getValue("cfgBg" + Config().nameOf(Config::GuiElem::LineHL)).value<QColor>();
  QColor fgHLLine = ValueManager().getValue("cfgFg" + Config().nameOf(Config::GuiElem::LineHL)).value<QColor>();

  qDebug() << "highlight colors: " << bgHLLine << fgHLLine;

  checkPlugins();

  aboutPlugins = new QAction(tr("About &Plugins"), this);
  connect(aboutPlugins, &QAction::triggered, this, &TestMain::pluginsAbout);
  ui->menuHelp->addAction(aboutPlugins);

  testPlugin();
  }


void TestMain::checkPlugins() {
  for (const QString& s : GuiCore().pluggablePages()) {
      AbstractCenterWidget* cw = static_cast<AbstractCenterWidget*>(GuiCore().pluggablePage(s));

//      check page:  "FixtureManager"
//      check page:  "HelpView"
//      check page:  "JogView"
//      check page:  "LCToolTable"
//      check page:  "MDIEditor"
//      check page:  "PathEditor"
//      check page:  "PreferencesEditor"
//      check page:  "PreViewEditor"
//      check page:  "SysEventView"
//      check page:  "ToolManager"
      qDebug() << "check page: " << cw->objectName();
      }
  }


void TestMain::loadPlugins() {
  const auto staticInstances = QPluginLoader::staticInstances();

  for (QObject *plugin : staticInstances) {
      qDebug() << "static plugin: " << plugin->objectName();
      }

#if defined(Q_OS_WIN)
  if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
      pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
  if (pluginsDir.dirName() == "MacOS") {
      pluginsDir.cdUp();
      pluginsDir.cdUp();
      pluginsDir.cdUp();
  }
#endif
  const auto entryList = pluginsDir.entryList(QDir::Files);

  for (const QString &fileName : entryList) {
      QString path = pluginsDir.absoluteFilePath(fileName);

      qDebug() << "try to load plugin:" << path;
      QPluginLoader loader(path);
      QObject *plugin = loader.instance();

      qDebug() << "plugin loaded:" << (loader.isLoaded() ? "YES" : "NO");
      if (plugin) {
         auto iPage = qobject_cast<PluginPageInterface*>(plugin);

         if (iPage) {
            pluginFileNames += fileName;

            qDebug() << "\nloadable page:" << fileName << "\n";
            }
         else {
            qDebug() << "plugin:" << fileName << " - but NOT a loadable page!";
            }
         }
      else qDebug() << "plugin" << fileName << "is not accepted as plugin! --->>>" << loader.errorString();
      }
  }


void TestMain::pluginsAbout() {
  PluginDialog dialog(pluginsDir.path(), pluginFileNames, this);

  dialog.exec();
  }


void TestMain::testPlugin() {
  QString pluginName("PathEditor");
  PluginPageInterface*  iP = GuiCore().pluggablePage(pluginName);
  AbstractCenterWidget* cw = static_cast<AbstractCenterWidget*>(iP);

  cw->initialize(":/src/lcLib/UI/GCodeEditor.ui");
  layout()->replaceWidget(ui->tbd, new CenterPage(cw, true, this));
  }
