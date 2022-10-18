/* 
 * **************************************************************************
 * 
 *  file:       axismask.h
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
#ifndef AXISMASK_H
#define AXISMASK_H
#include <QObject>
class QString;


class AxisMask : public QObject
{
  Q_OBJECT
public:
  explicit AxisMask(const AxisMask& other);
  explicit AxisMask(int mask);
  explicit AxisMask(const QString& iniValue);
  virtual ~AxisMask();

  AxisMask& operator =(const AxisMask& other);
  int  activeAxis() const { return cntActive; }
  bool hasXAxis()   const { return axisSeen[0]; }
  bool hasYAxis()   const { return axisSeen[1]; }
  bool hasZAxis()   const { return axisSeen[2]; }
  bool hasAAxis()   const { return axisSeen[3]; }
  bool hasBAxis()   const { return axisSeen[4]; }
  bool hasCAxis()   const { return axisSeen[5]; }
  bool hasUAxis()   const { return axisSeen[6]; }
  bool hasVAxis()   const { return axisSeen[7]; }
  bool hasWAxis()   const { return axisSeen[8]; }
  bool hasAxis(int axis) const;
  void setup(const QString& axisLetters);
  int  joint4Axis(int axis) const;
  int  mask() const { return axisMask; }
  void dump() const;

protected:
  void calcActive();
  void parseIni(const QString& iniValue);
  void checkHomed(int axis, QVariant value);

private:
  int  cntActive;
  int  axisMask;
  int  joint2Axis[9];
  bool axisSeen[9];
  bool axisHomed[9];
  static const char axisLetters[];
  };
#endif // AXISMASK_H
