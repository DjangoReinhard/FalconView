/* 
 * **************************************************************************
 * 
 *  file:       ally3d.cpp
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
#include <ally3d.h>
#include <graphicfactory.h>
#include <graphicelement.h>
#include <geline.h>
#include <occtviewer.h>
#include <valuemanager.h>
#include <guicore.h>

#include <AIS_ColoredShape.hxx>
#include <BRepPrimAPI_MakeCone.hxx>


Ally3D::Ally3D(QObject *parent)
 : QObject(parent)
 , v3D(nullptr)
 , facGraph(new GraphicFactory()) {
  }


static Quantity_Color convertColor(const QColor& c) {
  return Quantity_Color((double)(c.red()   / 255.0)
                      , (double)(c.green() / 255.0)
                      , (double)(c.blue()  / 255.0), Quantity_TOC_RGB);
  }


void Ally3D::setFeedColor(const QColor &c) {
  colFeed = convertColor(c);
  }


void Ally3D::setTraverseColor(const QColor &c) {
  colTraverse = convertColor(c);
  }


void Ally3D::setLimitsColor(const QColor &c) {
  colLimits = convertColor(c);
  }


void Ally3D::setCurSegColor(const QColor &c) {
  colCurSeg = convertColor(c);
  }


void Ally3D::setOldSegColor(const QColor &c) {
  colOldSeg = convertColor(c);
  }


void Ally3D::setWorkPieceColor(const QColor &c) {
  colWorkPiece = convertColor(c);
  }


void Ally3D::setOcctViewer(OcctQtViewer *view3D) {
  v3D = view3D;
  connect(ValueManager().getModel("curLine", 0), &ValueModel::valueChanged, this, &Ally3D::update);
  connect(ValueManager().getModel("edLine", 0), &ValueModel::valueChanged, this, &Ally3D::highlight);
  }


void Ally3D::moveCone(double x, double y, double z) {
  if (!v3D) return;
  gp_Trsf   move;

//  qDebug() << "moveCone: " << x << "/" << y << "/" << z;
  move.SetValues (1, 0, 0, x
                , 0, 1, 0, y
                , 0, 0, 1, z);
  v3D->context()->SetLocation(cone, move);
  v3D->view()->Invalidate();
  v3D->update();
  }


void Ally3D::showMachineLimits() {
  if (!v3D) return;
  std::pair<QVector3D, QVector3D> ml = GuiCore().machineLimits();
  gp_Pnt cMin(ml.first.x(), ml.first.y(), ml.first.z());
  gp_Pnt cMax(ml.second.x(), ml.second.y(), ml.second.z());
  Handle(AIS_InteractiveContext) ctx  = v3D->context();
  GraphicElement*                line = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMin.Z())
                                                           , gp_Pnt(cMax.X(), cMin.Y(), cMin.Z()));
  line->setColor(colLimits);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMin.Z())
                            , gp_Pnt(cMin.X(), cMax.Y(), cMin.Z()));
  line->setColor(colLimits);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMin.Z())
                            , gp_Pnt(cMin.X(), cMin.Y(), cMax.Z()));
  line->setColor(colLimits);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMin.X(), cMax.Y(), cMin.Z())
                            , gp_Pnt(cMax.X(), cMax.Y(), cMin.Z()));
  line->setColor(colLimits);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMax.Z())
                            , gp_Pnt(cMax.X(), cMin.Y(), cMax.Z()));
  line->setColor(colLimits);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMax.X(), cMin.Y(), cMin.Z())
                            , gp_Pnt(cMax.X(), cMax.Y(), cMin.Z()));
  line->setColor(colLimits);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMin.X(), cMax.Y(), cMin.Z())
                            , gp_Pnt(cMin.X(), cMax.Y(), cMax.Z()));
  line->setColor(colLimits);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMax.X(), cMax.Y(), cMin.Z())
                            , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  line->setColor(colLimits);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMax.X(), cMax.Y(), cMin.Z())
                            , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  line->setColor(colLimits);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMax.Z())
                            , gp_Pnt(cMax.X(), cMin.Y(), cMax.Z()));
  line->setColor(colLimits);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMax.X(), cMin.Y(), cMax.Z())
                            , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  line->setColor(colLimits);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMax.X(), cMin.Y(), cMin.Z())
                            , gp_Pnt(cMax.X(), cMin.Y(), cMax.Z()));
  line->setColor(colLimits);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMax.Z())
                            , gp_Pnt(cMin.X(), cMax.Y(), cMax.Z()));
  line->setColor(colLimits);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMin.X(), cMax.Y(), cMax.Z())
                            , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  line->setColor(colLimits);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  }


void Ally3D::showWorkLimits() {
  if (!v3D) return;
  Handle(AIS_InteractiveContext) ctx = v3D->context();
  gp_Pnt  cMin = workPiece.CornerMin();
  gp_Pnt  cMax = workPiece.CornerMax();

  GELine* line = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMin.Z())
                                    , gp_Pnt(cMax.X(), cMin.Y(), cMin.Z()));
  line->setColor(colWorkPiece);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMin.Z())
                            , gp_Pnt(cMin.X(), cMax.Y(), cMin.Z()));
  line->setColor(colWorkPiece);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMin.Z())
                            , gp_Pnt(cMin.X(), cMin.Y(), cMax.Z()));
  line->setColor(colWorkPiece);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMin.X(), cMax.Y(), cMin.Z())
                            , gp_Pnt(cMax.X(), cMax.Y(), cMin.Z()));
  line->setColor(colWorkPiece);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMax.Z())
                            , gp_Pnt(cMax.X(), cMin.Y(), cMax.Z()));
  line->setColor(colWorkPiece);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMax.X(), cMin.Y(), cMin.Z())
                            , gp_Pnt(cMax.X(), cMax.Y(), cMin.Z()));
  line->setColor(colWorkPiece);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMin.X(), cMax.Y(), cMin.Z())
                            , gp_Pnt(cMin.X(), cMax.Y(), cMax.Z()));
  line->setColor(colWorkPiece);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMax.X(), cMax.Y(), cMin.Z())
                            , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  line->setColor(colWorkPiece);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMax.X(), cMax.Y(), cMin.Z())
                            , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  line->setColor(colWorkPiece);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMax.Z())
                            , gp_Pnt(cMax.X(), cMin.Y(), cMax.Z()));
  line->setColor(colWorkPiece);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMax.X(), cMin.Y(), cMax.Z())
                            , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  line->setColor(colWorkPiece);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMax.X(), cMin.Y(), cMin.Z())
                            , gp_Pnt(cMax.X(), cMin.Y(), cMax.Z()));
  line->setColor(colWorkPiece);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMax.Z())
                            , gp_Pnt(cMin.X(), cMax.Y(), cMax.Z()));
  line->setColor(colWorkPiece);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  line = facGraph->createLine(gp_Pnt(cMin.X(), cMax.Y(), cMax.Z())
                            , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  line->setColor(colWorkPiece);
  ctx->Display(line->shape(), AIS_Shaded, 0, false);
  }


void Ally3D::showPath(const QMap<long, GraphicElement*>& path) {
  if (!v3D) return;
  Handle(AIS_InteractiveContext) ctx = v3D->context();

  workPath = path;
  ctx->RemoveAll(false);
  gp_Pnt         cMin, cMax, p;
  Bnd_Box        bb;
  gp_Dir         axis = gp::DZ();
  gp_Ax2         aplace(gp_Pnt(0, 0, 0), axis);
  TopoDS_Shape   topo_cone = BRepPrimAPI_MakeCone(aplace, 0.001, 10, 20).Shape();

  cone = new AIS_Shape(topo_cone);
  for (GraphicElement* ge : workPath) {
      if (!ge->shape().IsNull())
         ctx->Display(ge->shape(), AIS_Shaded, 0, false);

      if (ge->type() == GraphicElement::GELine
       || ge->type() == GraphicElement::GEHelix) {
         bb = ge->shape()->BoundingBox();
         p = bb.CornerMin();
         cMin.SetX(fmin(cMin.X(), p.X()));
         cMin.SetY(fmin(cMin.Y(), p.Y()));
         cMin.SetZ(fmin(cMin.Z(), p.Z()));
         p = bb.CornerMax();
         cMax.SetX(fmax(cMax.X(), p.X()));
         cMax.SetY(fmax(cMax.Y(), p.Y()));
         cMax.SetZ(fmax(cMax.Z(), p.Z()));
         }
      }
  ctx->Display(v3D->cube(), 0, 0, false);
  ctx->Display(cone, AIS_Shaded, 0, false);
  workPiece = Bnd_Box(cMin, cMax);
  showWorkLimits();
  showMachineLimits();
  v3D->setBounds(workPiece);
  v3D->fitAll();
  lastSeg = workPath.lowerBound(0);
  }


void Ally3D::showPos(GraphicElement *ge) {
  if (!ge) return;
  ValueManager vm;

  vm.setValue("relX", ge->from().X());
  vm.setValue("relY", ge->from().Y());
  vm.setValue("relZ", ge->from().Z());

  switch (ge->type()) {
    case GraphicElement::GELine:
    case GraphicElement::GERapid: {
         GELine* l = static_cast<GELine*>(ge);

         vm.setValue("dtgX", l->to().X() - l->from().X());
         vm.setValue("dtgY", l->to().Y() - l->from().Y());
         vm.setValue("dtgZ", l->to().Z() - l->from().Z());
         } break;
    default:
         vm.setValue("dtgX", 0);
         vm.setValue("dtgY", 0);
         vm.setValue("dtgZ", 0);
         break;
    }
  }


void Ally3D::update(const QVariant& line) {
  if (!v3D) return;
  if (workPath.size() < 1) return;
  int segNum = fmax(0, line.toInt() - 2);
  QMap<long, GraphicElement*>::iterator curSeg = workPath.upperBound(segNum);

  if (lastSeg.key() > segNum) lastSeg = curSeg;
//  qDebug() << "Ally3D::update(" << segNum << ")";
  while (lastSeg != curSeg) {
        lastSeg.value()->setColor(colOldSeg);
        lastSeg++;
        }
  lastSeg = curSeg;
  lastSeg.value()->setColor(colCurSeg);
  v3D->view()->Invalidate();
  v3D->update();
  }


void Ally3D::highlight(const QVariant& line) {
  if (!v3D) return;
  if (workPath.size() < 1) return;
  if (!lastSeg.value()->isNull()) {
     GraphicElement* ge = lastSeg.value();

     switch (ge->type()) {
       case GraphicElement::GELine:
       case GraphicElement::GEHelix:
            ge->setColor(colFeed);
            break;
       case GraphicElement::GERapid:
            ge->setColor(colTraverse);
            break;
       default:
            break;
       }
     }
  int segNum = fmax(0, line.toInt());
  QMap<long, GraphicElement*>::iterator curSeg = workPath.upperBound(segNum);
  GraphicElement* ge = nullptr;

  if (lastSeg.key() > segNum) lastSeg = curSeg;
//  qDebug() << "Ally3D::highlight(" << segNum << ")";
  while (lastSeg != curSeg) {
        GraphicElement* ge = lastSeg.value();

        switch (ge->type()) {
          case GraphicElement::GELine:
          case GraphicElement::GEHelix:
               ge->setColor(colFeed);
               break;
          case GraphicElement::GERapid:
               ge->setColor(colTraverse);
               break;
          default:
               break;
          }
        lastSeg++;
        }
  lastSeg = curSeg;
  if (!lastSeg.value()->isNull()) {
     GraphicElement* ge = lastSeg.value();

     ge->setColor(colCurSeg);
     showPos(ge);
     moveCone(ge->from().X(), ge->from().Y(), ge->from().Z());
     }
  }
