#include <emc_nml.hh>
#include <insulatePose.h>
#include <positioncalculator.h>
#include <cmath>
#include <QVector3D>
#include <QVariant>
#include <QDebug>

PositionCalculator::PositionCalculator(QObject *parent)
 : QObject(parent) {
  createModels();
  }


void PositionCalculator::createModels() {
  vm.setValue("absX", 0);
  vm.setValue("absY", 0);
  vm.setValue("absZ", 0);
  vm.setValue("absA", 0);
  vm.setValue("absB", 0);
  vm.setValue("absC", 0);
  vm.setValue("absU", 0);
  vm.setValue("absV", 0);
  vm.setValue("absW", 0);
  vm.setValue("relX", 0);
  vm.setValue("relY", 0);
  vm.setValue("relZ", 0);
  vm.setValue("relA", 0);
  vm.setValue("relB", 0);
  vm.setValue("relC", 0);
  vm.setValue("relU", 0);
  vm.setValue("relV", 0);
  vm.setValue("relW", 0);
  vm.setValue("dtgX", 0);
  vm.setValue("dtgY", 0);
  vm.setValue("dtgZ", 0);
  vm.setValue("dtgA", 0);
  vm.setValue("dtgB", 0);
  vm.setValue("dtgC", 0);
  vm.setValue("dtgU", 0);
  vm.setValue("dtgV", 0);
  vm.setValue("dtgW", 0);
  }


double PositionCalculator::convertUnit(double value, CANON_UNITS unit) {
  switch (unit) {
    case CANON_UNITS_INCHES: return value * 25.40;
    case CANON_UNITS_CM:     return value * 10;
    default:                 break;
    }
  return value;
  }


void PositionCalculator::update(EmcPose* actPos, EmcPose* /* relPos */, EmcPose* dtg, CANON_UNITS units, EmcPose* g5x, EmcPose* g92, double rotXY, EmcPose* toolOffset) {
  double x = actPos->tran.x - g5x->tran.x - toolOffset->tran.x;
  double y = actPos->tran.y - g5x->tran.y - toolOffset->tran.y;
  double z = actPos->tran.z - g5x->tran.z - toolOffset->tran.z;
  double a = actPos->a      - g5x->a      - toolOffset->a;
  double b = actPos->b      - g5x->b      - toolOffset->b;
  double c = actPos->c      - g5x->c      - toolOffset->c;
  double u = actPos->u      - g5x->u      - toolOffset->u;
  double v = actPos->v      - g5x->v      - toolOffset->v;
  double w = actPos->w      - g5x->w      - toolOffset->w;

  if (rotXY != 0) {
     double ang = rotXY * M_PI / 180.0;
     double xr  = x * cos(ang) - sin(ang);
     double yr  = y * sin(ang) + acos(ang);

     x = xr;
     y = yr;
     }
  x = convertUnit(x - g92->tran.x, units);
  y = convertUnit(y - g92->tran.y, units);
  z = convertUnit(z - g92->tran.z, units);
  a = convertUnit(a - g92->a, units);
  b = convertUnit(b - g92->b, units);
  c = convertUnit(c - g92->c, units);
  u = convertUnit(u - g92->u, units);
  v = convertUnit(v - g92->v, units);
  w = convertUnit(w - g92->w, units);

  QVector3D cp(x, y, z);
//  qDebug() << "posCalc: " << x << "/" << y << "/" << z;

  vm.setValue("absX", convertUnit(actPos->tran.x, units));
  vm.setValue("absY", convertUnit(actPos->tran.y, units));
  vm.setValue("absZ", convertUnit(actPos->tran.z, units));
  vm.setValue("absA", convertUnit(actPos->a, units));
  vm.setValue("absB", convertUnit(actPos->b, units));
  vm.setValue("absC", convertUnit(actPos->c, units));
  vm.setValue("absU", convertUnit(actPos->u, units));
  vm.setValue("absV", convertUnit(actPos->v, units));
  vm.setValue("absW", convertUnit(actPos->w, units));
  vm.setValue("conePos", cp);
  vm.setValue("relX", x);
  vm.setValue("relY", y);
  vm.setValue("relZ", z);
  vm.setValue("relA", a);
  vm.setValue("relB", b);
  vm.setValue("relC", c);
  vm.setValue("relU", u);
  vm.setValue("relV", v);
  vm.setValue("relW", w);
  vm.setValue("dtgX", convertUnit(dtg->tran.x, units));
  vm.setValue("dtgY", convertUnit(dtg->tran.y, units));
  vm.setValue("dtgZ", convertUnit(dtg->tran.z, units));
  vm.setValue("dtgA", convertUnit(dtg->a, units));
  vm.setValue("dtgB", convertUnit(dtg->b, units));
  vm.setValue("dtgC", convertUnit(dtg->c, units));
  vm.setValue("dtgU", convertUnit(dtg->u, units));
  vm.setValue("dtgV", convertUnit(dtg->v, units));
  vm.setValue("dtgW", convertUnit(dtg->w, units));
  }
