#ifndef CORE_P_H
#define CORE_P_H
#include <configmgr.h>
#include <lcproperties.h>
#include <tooltable.h>
#include <LCInter.h>
#include <mainview.h>
class OcctQtViewer;
class QString;
class QFile;

class Kernel
{
private:
  Kernel(const QString& iniFilename, const QString& appName, const QString& group = "SRD");

  void parseGCode(QFile& file);

  ConfigManager cfg;
  LcProperties  lcProps;
  ToolTable     tt;
  LCInterface   lcIF;
  OcctQtViewer* view3D;
  MainView*     mainView;

  friend class Core;
  friend class Config;
  };

#endif // CORE_P_H
