#ifndef COMMANDNMLWRITER_H
#define COMMANDNMLWRITER_H
#include "abstractcommandwriter.h"
class RCS_CMD_CHANNEL;
class RCS_STAT_CHANNEL;
class RCS_CMD_MSG;
class EMC_STAT;


class CommandNMLWriter : public AbstractCommandWriter
{
  Q_OBJECT
public:
  explicit CommandNMLWriter(QObject *parent = nullptr);

  bool isActive() const override;
  int  sendCommand(RCS_CMD_MSG& msg) override;

protected:
  void sleep(double seconds);

private:
  RCS_CMD_CHANNEL*  cCmd;
  RCS_STAT_CHANNEL* cStat;
  EMC_STAT*         status;

  static const int    EMC_COMMAND_TIMEOUT;  // how long to wait until timeout
  static const double EMC_COMMAND_DELAY;    // seconds to sleep between checks
  };
#endif // COMMANDNMLWRITER_H
