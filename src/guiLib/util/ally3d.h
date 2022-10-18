/* 
 * **************************************************************************
 * 
 *  file:       ally3d.h
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    29.1.2022 by Django Reinhard
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
#ifndef ALLY3D_H
#define ALLY3D_H
#include <QObject>
#include <QMap>
#include <AIS_ViewCube.hxx>
#include <AIS_Shape.hxx>
class OcctQtViewer;
class GraphicElement;
class GraphicFactory;
class ValueModel;


class Ally3D : public QObject
{
  Q_OBJECT
public:
  explicit Ally3D(QObject *parent = nullptr);

  void setOcctViewer(OcctQtViewer* view3D);
  void setTraverseColor(const QColor& c);
  void setFeedColor(const QColor& c);
  void setLimitsColor(const QColor& c);
  void setCurSegColor(const QColor& c);
  void setOldSegColor(const QColor& c);
  void setWorkPieceColor(const QColor& c);
  void showPos(GraphicElement* ge);

public slots:
  void showPath(const QMap<long, GraphicElement*>& path);
  void moveCone(double x, double y, double z);
  void showMachineLimits();
  void showWorkLimits();

protected slots:
  void update(const QVariant& line);
  void highlight(const QVariant& line);

private:
  Handle(AIS_Shape) cone;
  OcctQtViewer*     v3D;
  GraphicFactory*   facGraph;
  Bnd_Box           workPiece;
  Quantity_Color    colTraverse;
  Quantity_Color    colFeed;
  Quantity_Color    colLimits;
  Quantity_Color    colCurSeg;
  Quantity_Color    colOldSeg;
  Quantity_Color    colWorkPiece;
  QMap<long, GraphicElement*> workPath;
  QMap<long, GraphicElement*>::iterator lastSeg;
  };
#endif // ALLY3D_H
