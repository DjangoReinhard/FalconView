/* 
 * **************************************************************************
 * 
 *  file:       pos9.h
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
#ifndef POS9_H
#define POS9_H
#include <QObject>
class CANON_POSITION;


class Pos9 : public QObject
{
  Q_OBJECT
public:
  Pos9(QObject *parent = nullptr);
  Pos9(const CANON_POSITION& p);
  Pos9(double x, double y, double z, double a=0, double b=0, double c=0, double u=0, double v=0, double w=0);
  Pos9(const Pos9& other);

  Pos9& operator=(const Pos9& other);

  CANON_POSITION* toCanon();

  double x, y, z, a, b, c, u, v, w;
  };
#endif // POS9_H
