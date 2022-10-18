/* 
 * **************************************************************************
 * 
 *  file:       graphicelement.h
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
#ifndef GRAPHICELEMENT_H
#define GRAPHICELEMENT_H
#include <QObject>
#include <gp_Pnt.hxx>
#include <AIS_Shape.hxx>
class Quantity_Color;


class GraphicElement : public QObject
{
  Q_OBJECT
public:
  enum GEType {
    GELine
  , GEHelix
  , GERapid
  , GEBorder
    };
  GraphicElement& operator =(const GraphicElement& other);

  gp_Pnt from() const;
  gp_Pnt from();
  bool isNull() const;
  GEType type() const;
  void setColor(Quantity_Color c);
  void setShape(Handle(AIS_Shape) shape);
  Handle(AIS_Shape) shape() const;
  Handle(AIS_Shape) shape();


protected:
  explicit GraphicElement(GEType type, const gp_Pnt& from, QObject *parent = nullptr);
  explicit GraphicElement(const GraphicElement& other);
  virtual ~GraphicElement() = default;

private:
  GEType            gtype;
  Handle(AIS_Shape) elem;
  gp_Pnt            start;
  };
#endif // GRAPHICELEMENT_H
