#ifndef CORE_P_H
#define CORE_P_H
#include <configmgr.h>
#include <lcproperties.h>
#include <axismask.h>
#include <tooltable.h>
#include <LCInter.h>
#include <mainview.h>
class OcctQtViewer;
class MainWindow;
class QString;
class QFile;

class Kernel : public QObject
{
  Q_OBJECT
private:
  Kernel(const QString& iniFilename, const QString& appName, const QString& group = "SRD");
  virtual ~Kernel();

  void parseGCode(QFile& file);
  void updateView(const QVariant& v);

  ConfigManager cfg;
  LcProperties  lcProps;
  ToolTable     tt;
  LCInterface   lcIF;
  AxisMask      mAxis;
  OcctQtViewer* view3D;
  MainView*     mainView;
  MainWindow*   mainWindow;

  friend class Core;
  friend class Config;
  };

#endif // CORE_P_H
