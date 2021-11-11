#ifndef COMMANDWRITER_H
#define COMMANDWRITER_H
#include <QObject>
class RCS_CMD_CHANNEL;
class RCS_STAT_CHANNEL;
class RCS_CMD_MSG;
class EMC_STAT;


class CommandWriter : public QObject
{
  Q_OBJECT
public:
  explicit CommandWriter(QObject *parent = nullptr);

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
