/* 
 * **************************************************************************
 * 
 *  file:       graphicfactory.h
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
#ifndef GRAPHICFACTORY_H
#define GRAPHICFACTORY_H
class gp_Pnt;
class gp_Dir;
class GELine;
class GEHelix;
class GERapidMove;


class GraphicFactory
{
public:
//  GraphicElement* createArc(const gp_Pnt& from, const gp_Pnt& to, const gp_Pnt& center, bool ccw);
  GEHelix*     createHelix(const gp_Pnt& from, const gp_Pnt& to, const gp_Pnt& center, const gp_Dir& axis, bool ccw, int fullTurns = 0);
  GELine*      createLine(const gp_Pnt& from, const gp_Pnt& to);
  GERapidMove* createRapidMove(const gp_Pnt& from, const gp_Pnt& to);
  };
#endif // GRAPHICFACTORY_H
