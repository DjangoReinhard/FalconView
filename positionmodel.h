#ifndef POSITIONMODEL_H
#define POSITIONMODEL_H

#include <QObject>
#include "valuemodel.h"


class PositionModel : public QObject
{
  Q_OBJECT
public:
  PositionModel();

  ValueModel& getXAbs() { return absX; }
  ValueModel& getYAbs() { return absY; }
  ValueModel& getZAbs() { return absZ; }
  ValueModel& getAAbs() { return absA; }
  ValueModel& getBAbs() { return absB; }
  ValueModel& getCAbs() { return absC; }
  ValueModel& getUAbs() { return absU; }
  ValueModel& getVAbs() { return absV; }
  ValueModel& getWAbs() { return absW; }

  ValueModel& getXRel() { return relX; }
  ValueModel& getYRel() { return relY; }
  ValueModel& getZRel() { return relZ; }
  ValueModel& getARel() { return relA; }
  ValueModel& getBRel() { return relB; }
  ValueModel& getCRel() { return relC; }
  ValueModel& getURel() { return relU; }
  ValueModel& getVRel() { return relV; }
  ValueModel& getWRel() { return relW; }

  ValueModel& getXDtg() { return dtgX; }
  ValueModel& getYDtg() { return dtgY; }
  ValueModel& getZDtg() { return dtgZ; }
  ValueModel& getADtg() { return dtgA; }
  ValueModel& getBDtg() { return dtgB; }
  ValueModel& getCDtg() { return dtgC; }
  ValueModel& getUDtg() { return dtgU; }
  ValueModel& getVDtg() { return dtgV; }
  ValueModel& getWDtg() { return dtgW; }

private:
  ValueModel absX;
  ValueModel absY;
  ValueModel absZ;
  ValueModel absA;
  ValueModel absB;
  ValueModel absC;
  ValueModel absU;
  ValueModel absV;
  ValueModel absW;
  ValueModel relX;
  ValueModel relY;
  ValueModel relZ;
  ValueModel relA;
  ValueModel relB;
  ValueModel relC;
  ValueModel relU;
  ValueModel relV;
  ValueModel relW;
  ValueModel dtgX;
  ValueModel dtgY;
  ValueModel dtgZ;
  ValueModel dtgA;
  ValueModel dtgB;
  ValueModel dtgC;
  ValueModel dtgU;
  ValueModel dtgV;
  ValueModel dtgW;
  };

#endif // POSITIONMODEL_H
