#ifndef STATUSUPDATER_H
#define STATUSUPDATER_H
#include <QObject>
#include <valuemanager.h>
class PositionCalculator;
class GCodeInfo;
class LCStatus;


class StatusUpdater : public QObject
{
  Q_OBJECT
public:
  explicit StatusUpdater(PositionCalculator& pc, GCodeInfo& gi, QObject *parent = nullptr);

  void update(const LCStatus& status);

private:
  void createModels();

  ValueManager        vm;
  PositionCalculator& pc;
  GCodeInfo&          gi;
  };

#endif // STATUSUPDATER_H
