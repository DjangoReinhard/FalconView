/* 
 * **************************************************************************
 * 
 *  file:       positioncalculator.h
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
#ifndef POSITIONCALCULATOR_H
#define POSITIONCALCULATOR_H
#include <QObject>
#include <valuemanager.h>


class PositionCalculator : public QObject
{
  Q_OBJECT
public:
  explicit PositionCalculator(QObject* parent = nullptr);

  void update(volatile const double* absPos
            , volatile const double* relPos
            , volatile const double* dtg
            , int units
            , volatile const double* g5x
            , volatile const double* g92
            , volatile double rotXY
            , volatile const double* toolOffset);

protected:
  double convertUnit(double value, int unit);
  void   createModels();

private:
  ValueManager vm;
  };
#endif // POSITIONCALCULATOR_H
