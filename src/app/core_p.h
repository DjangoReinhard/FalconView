#ifndef CORE_P_H
#define CORE_P_H
#include <configmgr.h>
#include <lcproperties.h>
#include <positioncalculator.h>
#include <gcodeinfo.h>
#include <syseventmodel.h>
#include <statusreader.h>
#include <commandwriter.h>
#include <axismask.h>
#include <ally3d.h>
#include <tooltable.h>
#include <LCInter.h>
#include <centerview.h>
#include <QLocale>
#include <QThread>
#include <QBasicTimer>
class OcctQtViewer;
class DBConnection;
class DBHelper;
class MainWindow;
class SysEvent;
class QString;
class QFile;


class Kernel : public QObject
{
  Q_OBJECT
protected:
  void timerEvent(QTimerEvent* event) override;

protected slots:
  void logSysEvent(int type, const QString& msg, const QTime& when);

signals:
  void abortTask();
  void enableBlockDelete(bool enable);
  void enableFlood(bool enable);
  void enableMist(bool enable);
  void enableOptionalStop(bool enable);
  void setSpindleOverride(double rate);
  void jogStep(int axis, double stepSize, double speed);
  void jogStart(int axis, double speed);
  void jogStop(int axis);
  void homeAxis(int jointNum);
  void loadTaskPlan(const QString& gcodeFile);
  void loadToolTable(const QString& toolTableFile);
  void sendMDICommand(const QString& command);
  void setAuto(int autoMode, int line);
  void setFeedOverride(double rate);
  void setRapidOverride(double rate);
  void setSpindle(bool enable, int speed, int direction);
  void setTaskMode(int mode);
  void setTaskState(int state);
  void taskPlanSynch();

private:
  Kernel(const QString& iniFilename, const QString& appName, const QString& group);
  virtual ~Kernel();

  void nop();
  void checkTools();
  bool isLatheMode() const;
  void initialize(DBHelper& dbAssist);
  void parseGCode(QFile& file);
  void setupBackend();
  void updateView(const QVariant& v);
  void windowClosing(QCloseEvent* e);
  DBConnection* createDatabase(DBHelper& dbAssist);

  ConfigManager       cfg;
  LcProperties        lcProps;
  ToolTable           tt;
  LCInterface         lcIF;
  AxisMask            mAxis;
  OcctQtViewer*       view3D;
  CenterView*         centerView;
  MainWindow*         mainWindow;
  DBConnection*       conn;
  Ally3D              ally3D;
  GCodeInfo           gcodeInfo;
  PositionCalculator  positionCalculator;
  StatusReader        statusReader;
  CommandWriter*      commandWriter;
  QBasicTimer         timer;
  QLocale             curLocale;
  QThread             backendCommThread;
  SysEventModel*      tmSysEvents;
  bool                simulator;

  friend class Core;
  friend class Config;
  };

#endif // CORE_P_H
