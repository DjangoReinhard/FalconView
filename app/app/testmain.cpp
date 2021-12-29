#include <testmain.h>
#include <plugindialog.h>
#include <PluginPageInterface.h>
#include <ui_mainwindow.h>
#include <QPluginLoader>
#include <QDebug>


TestMain::TestMain(const QDir& dir, QWidget *parent)
 : QMainWindow(parent)
 , ui(new Ui::MainWindow)
 , pluginsDir(dir) {
  ui->setupUi(this);
  qDebug() << "app-dir:" << dir.absolutePath();
  pluginsDir.cd("plugPages");
  loadPlugins();

  aboutPlugins = new QAction(tr("About &Plugins"), this);
  connect(aboutPlugins, &QAction::triggered, this, &TestMain::pluginsAbout);
  ui->menuHelp->addAction(aboutPlugins);
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
//  pluginsDir.cd("plugins");
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
