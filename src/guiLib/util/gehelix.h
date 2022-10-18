/* 
 * **************************************************************************
 * 
 *  file:       gehelix.h
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    26.1.2022 by Django Reinhard
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
#ifndef GEHELIX_H
#define GEHELIX_H
#include <graphicelement.h>


class GEHelix : public GraphicElement
{
public:
  explicit GEHelix(const gp_Pnt& from, const gp_Pnt& to, const gp_Pnt& center, const gp_Dir& axis, bool ccw, int fullTurns=0, QObject *parent = nullptr);
  explicit GEHelix(const GEHelix& other);
  virtual ~GEHelix() = default;

  GEHelix& operator=(const GEHelix& other);

private:
  gp_Pnt end;
  gp_Pnt c;
  gp_Dir ca;
  bool   ccw;
  int    turns;
  };
#endif // GEHELIX_H
