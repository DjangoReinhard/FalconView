/* 
 * **************************************************************************
 * 
 *  file:       positioncalculator.cpp
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    19.1.2022 by Django Reinhard
 *  copyright:  (c) 2022 Django Reinhard -  all rights reserved
 * 
 *  This program is free software: you can redistribute it and/or modify 
 *  it under the terms of the GNU General Public License as published by 
 *  the Free Software Foundation, either version 2 of the License, or 
 *  (at your option) any later version. 
 *   
 *  This program is distributed in the hope that it will be useful, 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *  GNU General Public License for more details. 
 *   
 *  You should have received a copy of the GNU General Public License 
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * **************************************************************************
 */
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


double PositionCalculator::convertUnit(double value, int unit) {
  switch (unit) {
    case CANON_UNITS_INCHES: return value * 25.40;
    case CANON_UNITS_CM:     return value * 10;
    default:                 break;
    }
  return value;
  }


void PositionCalculator::update(volatile const double* actPos, volatile const double*, volatile const double* dtg, int units, volatile const double* g5x, volatile const double* g92, volatile double rotXY, volatile const double* toolOffset) {
  double x = actPos[0] - g5x[0] - toolOffset[0];
  double y = actPos[1] - g5x[1] - toolOffset[1];
  double z = actPos[2] - g5x[2] - toolOffset[2];
  double a = actPos[3] - g5x[3] - toolOffset[3];
  double b = actPos[4] - g5x[4] - toolOffset[4];
  double c = actPos[5] - g5x[5] - toolOffset[5];
  double u = actPos[6] - g5x[6] - toolOffset[6];
  double v = actPos[7] - g5x[7] - toolOffset[7];
  double w = actPos[8] - g5x[8] - toolOffset[8];

//  qDebug() << "act. Pos: " << actPos[0] << "/" << actPos[1] << "/" << actPos[2]
//           << "rel. Pos: " << relPos[0] << "/" << relPos[1] << "/" << relPos[2]
//           << "dtg.: " << dtg[0] << "/" << dtg[1] << "/" << dtg[2];

  if (rotXY != 0) {
     double ang = rotXY * M_PI / 180.0;
     double xr  = x * cos(ang) - sin(ang);
     double yr  = y * sin(ang) + acos(ang);

     x = xr;
     y = yr;
     }
  x = convertUnit(x - g92[0], units);
  y = convertUnit(y - g92[1], units);
  z = convertUnit(z - g92[2], units);
  a = convertUnit(a - g92[3], units);
  b = convertUnit(b - g92[4], units);
  c = convertUnit(c - g92[5], units);
  u = convertUnit(u - g92[6], units);
  v = convertUnit(v - g92[7], units);
  w = convertUnit(w - g92[8], units);
  QVector3D cp(x, y, z);

  //  qDebug() << "posCalc: " << x << "/" << y << "/" << z;
  vm.setValue("conePos", cp);
  vm.setValue("absX", convertUnit(actPos[0], units));
  vm.setValue("absY", convertUnit(actPos[1], units));
  vm.setValue("absZ", convertUnit(actPos[2], units));
  vm.setValue("absA", convertUnit(actPos[3], units));
  vm.setValue("absB", convertUnit(actPos[4], units));
  vm.setValue("absC", convertUnit(actPos[5], units));
  vm.setValue("absU", convertUnit(actPos[6], units));
  vm.setValue("absV", convertUnit(actPos[7], units));
  vm.setValue("absW", convertUnit(actPos[8], units));
  vm.setValue("relX", x);
  vm.setValue("relY", y);
  vm.setValue("relZ", z);
  vm.setValue("relA", a);
  vm.setValue("relB", b);
  vm.setValue("relC", c);
  vm.setValue("relU", u);
  vm.setValue("relV", v);
  vm.setValue("relW", w);
  vm.setValue("dtgX", convertUnit(dtg[0], units));
  vm.setValue("dtgY", convertUnit(dtg[1], units));
  vm.setValue("dtgZ", convertUnit(dtg[2], units));
  vm.setValue("dtgA", convertUnit(dtg[3], units));
  vm.setValue("dtgB", convertUnit(dtg[4], units));
  vm.setValue("dtgC", convertUnit(dtg[5], units));
  vm.setValue("dtgU", convertUnit(dtg[6], units));
  vm.setValue("dtgV", convertUnit(dtg[7], units));
  vm.setValue("dtgW", convertUnit(dtg[8], units));
  }
