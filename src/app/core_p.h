#ifndef CORE_P_H
#define CORE_P_H
#include <configmgr.h>
#include <lcproperties.h>
#include <positioncalculator.h>
#include <gcodeinfo.h>
#include <statusreader.h>
#include <axismask.h>
#include <tooltable.h>
#include <LCInter.h>
#include <mainview.h>
#include <QBasicTimer>
class OcctQtViewer;
class DBConnection;
class DBHelper;
class MainWindow;
class QString;
class QFile;


class Kernel : public QObject
{
  Q_OBJECT
protected:
  void timerEvent(QTimerEvent* event) override;

private:
  Kernel(const QString& iniFilename, const QString& appName, const QString& group, DBHelper& dbAssist);
  virtual ~Kernel();

  void parseGCode(QFile& file);
  void updateView(const QVariant& v);
  DBConnection* createDatabase(const QString& path, DBHelper& dbAssist);

  ConfigManager       cfg;
  LcProperties        lcProps;
  ToolTable           tt;
  LCInterface         lcIF;
  AxisMask            mAxis;
  OcctQtViewer*       view3D;
  MainView*           mainView;
  MainWindow*         mainWindow;
  DBConnection*       conn;
  GCodeInfo           gcodeInfo;
  PositionCalculator  positionCalculator;
  StatusReader        statusReader;
  QBasicTimer         timer;

  friend class Core;
  friend class Config;
  };

#endif // CORE_P_H
