#ifndef TESTMAIN_H
#define TESTMAIN_H
#include <QMainWindow>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class TestMain : public QMainWindow
{
  Q_OBJECT
public:
  explicit TestMain(const QDir& dir, QWidget *parent = nullptr);

  void loadPlugins();
  void pluginsAbout();

private:
  Ui::MainWindow* ui           = nullptr;
  QAction*        aboutPlugins = nullptr;
  QStringList     pluginFileNames;
  QDir            pluginsDir;
  };
#endif // TESTMAIN_H
