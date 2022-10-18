/* 
 * **************************************************************************
 * 
 *  file:       graphicelement.cpp
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
#include <graphicelement.h>


GraphicElement::GraphicElement(GEType type, const gp_Pnt& from, QObject *parent)
 : QObject(parent)
 , gtype(type)
 , start(from) {
  }


GraphicElement::GraphicElement(const GraphicElement& other)
 : QObject(other.parent())
 , gtype(other.gtype)
 , start(other.start) {
  }


gp_Pnt GraphicElement::from() const {
  return start;
  }


gp_Pnt GraphicElement::from() {
  return start;
  }


bool GraphicElement::isNull() const {
  return elem.IsNull();
  }


GraphicElement& GraphicElement::operator=(const GraphicElement &other) {
  if (&other == this) return *this;

  gtype = other.type();
  setParent(other.parent());
  start = other.start;

  return *this;
  }


void GraphicElement::setColor(Quantity_Color c) {
  if (!elem.IsNull()) elem->SetColor(c);
  }


void GraphicElement::setShape(Handle(AIS_Shape) shape) {
  elem = shape;
  elem->SetWidth(2);
  }


Handle(AIS_Shape) GraphicElement::shape() const {
  return elem;
  }


Handle(AIS_Shape) GraphicElement::shape() {
  return elem;
  }


GraphicElement::GEType GraphicElement::type() const {
  return gtype;
  }
