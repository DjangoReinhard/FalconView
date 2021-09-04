#ifndef STATUSREADER_H
#define STATUSREADER_H
#include <QObject>
#include <valuemanager.h>
class RCS_STAT_CHANNEL;
class EMC_STAT;
class PositionCalculator;
class GCodeInfo;


class StatusReader : public QObject
{
  Q_OBJECT
public:
  StatusReader(PositionCalculator& pc, GCodeInfo& gi);

public slots:
  void update();

private:
  void createModels();

  RCS_STAT_CHANNEL*   cStatus;
  EMC_STAT*           status;
  ValueManager        vm;
  PositionCalculator& pc;
  GCodeInfo&          gi;
  };

#endif // STATUSREADER_H
