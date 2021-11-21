#ifndef COMMANDWRITER_H
#define COMMANDWRITER_H
#include <QObject>
#include <QTime>
class RCS_CMD_CHANNEL;
class RCS_STAT_CHANNEL;
class RCS_CMD_MSG;
class EMC_STAT;


class CommandWriter : public QObject
{
  Q_OBJECT
public:
  explicit CommandWriter(QObject *parent = nullptr);

  bool isActive();

signals:
  void systemEvent(int type, const QString& msg, const QTime& when = QTime::currentTime());

public slots:
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

protected:
  int sendCommand(RCS_CMD_MSG& msg);
  void sleep(double seconds);

private:
  RCS_CMD_CHANNEL*  cCmd;
  RCS_STAT_CHANNEL* cStat;
  EMC_STAT*         status;

  static const int    EMC_COMMAND_TIMEOUT;  // how long to wait until timeout
  static const double EMC_COMMAND_DELAY;    // seconds to sleep between checks
  };
#endif // COMMANDWRITER_H
