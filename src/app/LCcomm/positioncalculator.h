#ifndef POSITIONCALCULATOR_H
#define POSITIONCALCULATOR_H
#include <QObject>
#include <valuemanager.h>
//#include <canon.hh>
class EmcPose;


class PositionCalculator : public QObject
{
  Q_OBJECT
public:
  explicit PositionCalculator(QObject* parent = nullptr);

  void update(EmcPose* absPos
            , EmcPose* relPos
            , EmcPose* dtg
            , int units
            , EmcPose* g5x
            , EmcPose* g92
            , double rotXY
            , EmcPose* toolOffset);

protected:
  double convertUnit(double value, int unit);
  void   createModels();

private:
  ValueManager vm;
  };
#endif // POSITIONCALCULATOR_H
