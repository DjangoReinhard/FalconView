/* 
 * **************************************************************************
 * 
 *  file:       geline.cpp
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
#include <geline.h>


GELine::GELine(GEType type, const gp_Pnt& from, const gp_Pnt& to, QObject *parent)
 : GraphicElement(type, from, parent)
 , end(to) {
  }


GELine::GELine(const gp_Pnt& from, const gp_Pnt& to, QObject *parent)
 : GraphicElement(GraphicElement::GELine, from, parent)
 , end(to) {
  }


GELine::GELine(const GELine& other)
 : GraphicElement(other)
 , end(other.end) {
  }


GELine& GELine::operator=(const GELine &other) {
  if (&other == this) return *this;

  GraphicElement::operator=(other);
  end = other.end;

  return *this;
  }


gp_Pnt GELine::to() const {
  return end;
  }


gp_Pnt GELine::to() {
  return end;
  }
