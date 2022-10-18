/* 
 * **************************************************************************
 * 
 *  file:       gehelix.cpp
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
#include <gehelix.h>

GEHelix::GEHelix(const gp_Pnt& from, const gp_Pnt& to, const gp_Pnt& center, const gp_Dir& axis, bool ccw, int fullTurns, QObject *parent)
 : GraphicElement(GraphicElement::GEHelix, from, parent)
 , end(to)
 , c(center)
 , ca(axis)
 , ccw(ccw)
 , turns(fullTurns) {
  }


GEHelix::GEHelix(const GEHelix& other)
 : GraphicElement(other)
 , end(other.end)
 , c(other.c)
 , ca(other.ca)
 , ccw(other.ccw)
 , turns(other.turns) {
  }


GEHelix& GEHelix::operator=(const GEHelix &other) {
  if (&other == this) return *this;

  end   = other.end;
  c     = other.c;
  ca    = other.ca;
  ccw   = other.ccw;
  turns = other.turns;

  return *this;
  }

