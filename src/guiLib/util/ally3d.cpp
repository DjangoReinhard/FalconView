#include <ally3d.h>
#include <graphicfactory.h>
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


//void Ally3D::setTraverseColor(const QColor &c) {
//  colTraverse = convertColor(c);
//  }


void Ally3D::setFeedColor(const QColor &c) {
  colFeed = convertColor(c);
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
  Handle(AIS_InteractiveContext) ctx   = v3D->context();
  Handle(AIS_Shape)              shape = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMin.Z())
                                                            , gp_Pnt(cMax.X(), cMin.Y(), cMin.Z()));
  shape->SetColor(colLimits);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMin.Z())
                                       , gp_Pnt(cMin.X(), cMax.Y(), cMin.Z()));
  shape->SetColor(colLimits);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMin.Z())
                                       , gp_Pnt(cMin.X(), cMin.Y(), cMax.Z()));
  shape->SetColor(colLimits);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMin.X(), cMax.Y(), cMin.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMin.Z()));
  shape->SetColor(colLimits);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMax.Z())
                                       , gp_Pnt(cMax.X(), cMin.Y(), cMax.Z()));
  shape->SetColor(colLimits);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMax.X(), cMin.Y(), cMin.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMin.Z()));
  shape->SetColor(colLimits);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMin.X(), cMax.Y(), cMin.Z())
                                       , gp_Pnt(cMin.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(colLimits);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMax.X(), cMax.Y(), cMin.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(colLimits);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMax.X(), cMax.Y(), cMin.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(colLimits);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMax.Z())
                                       , gp_Pnt(cMax.X(), cMin.Y(), cMax.Z()));
  shape->SetColor(colLimits);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMax.X(), cMin.Y(), cMax.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(colLimits);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMax.X(), cMin.Y(), cMin.Z())
                                       , gp_Pnt(cMax.X(), cMin.Y(), cMax.Z()));
  shape->SetColor(colLimits);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMax.Z())
                                       , gp_Pnt(cMin.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(colLimits);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMin.X(), cMax.Y(), cMax.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(colLimits);
  ctx->Display(shape, AIS_Shaded, 0, false);
  }


void Ally3D::showWorkLimits() {
  if (!v3D) return;
  Handle(AIS_InteractiveContext) ctx = v3D->context();
  gp_Pnt  cMin = workPiece.CornerMin();
  gp_Pnt  cMax = workPiece.CornerMax();

  Handle(AIS_Shape) shape = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMin.Z())
                                                         , gp_Pnt(cMax.X(), cMin.Y(), cMin.Z()));
  shape->SetColor(colWorkPiece);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMin.Z())
                                       , gp_Pnt(cMin.X(), cMax.Y(), cMin.Z()));
  shape->SetColor(colWorkPiece);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMin.Z())
                                       , gp_Pnt(cMin.X(), cMin.Y(), cMax.Z()));
  shape->SetColor(colWorkPiece);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMin.X(), cMax.Y(), cMin.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMin.Z()));
  shape->SetColor(colWorkPiece);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMax.Z())
                                       , gp_Pnt(cMax.X(), cMin.Y(), cMax.Z()));
  shape->SetColor(colWorkPiece);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMax.X(), cMin.Y(), cMin.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMin.Z()));
  shape->SetColor(colWorkPiece);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMin.X(), cMax.Y(), cMin.Z())
                                       , gp_Pnt(cMin.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(colWorkPiece);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMax.X(), cMax.Y(), cMin.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(colWorkPiece);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMax.X(), cMax.Y(), cMin.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(colWorkPiece);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMax.Z())
                                       , gp_Pnt(cMax.X(), cMin.Y(), cMax.Z()));
  shape->SetColor(colWorkPiece);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMax.X(), cMin.Y(), cMax.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(colWorkPiece);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMax.X(), cMin.Y(), cMin.Z())
                                       , gp_Pnt(cMax.X(), cMin.Y(), cMax.Z()));
  shape->SetColor(colWorkPiece);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMin.X(), cMin.Y(), cMax.Z())
                                       , gp_Pnt(cMin.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(colWorkPiece);
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = facGraph->createLine(gp_Pnt(cMin.X(), cMax.Y(), cMax.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(colWorkPiece);
  ctx->Display(shape, AIS_Shaded, 0, false);
  }


void Ally3D::showPath(const QMap<long, Handle(AIS_InteractiveObject)>& path) {
  if (!v3D) return;
  Handle(AIS_InteractiveContext) ctx = v3D->context();

//  if (workPath.size()) workPath.clear();
  workPath = path;
  ctx->RemoveAll(false);
  gp_Pnt         cMin, cMax, p;
  Bnd_Box        bb;
  gp_Dir         axis = gp::DZ();
  gp_Ax2         aplace(gp_Pnt(0, 0, 0), axis);
  Quantity_Color col;
  Quantity_Color tc        = colFeed;
  TopoDS_Shape   topo_cone = BRepPrimAPI_MakeCone(aplace, 0.001, 10, 20).Shape();

  cone = new AIS_Shape(topo_cone);
  for (const Handle(AIS_InteractiveObject)& anObject : qAsConst(workPath)) {
      ctx->Display(anObject, AIS_Shaded, 0, false);
      const Handle(AIS_ColoredShape) shape = Handle(AIS_ColoredShape)::DownCast(anObject);

      if (!shape.IsNull()) {
         shape->Color(col);
         if (col != tc) continue;
         bb = shape->BoundingBox();
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


void Ally3D::update(const QVariant& line) {
  if (!v3D) return;
  if (workPath.size() < 1) return;
  int segNum = fmax(0, line.toInt() - 2);
  QMap<long, Handle(AIS_InteractiveObject)>::iterator curSeg = workPath.upperBound(segNum);

  if (lastSeg.key() > segNum) lastSeg = curSeg;
//  qDebug() << "Ally3D::update(" << segNum << ")";
  while (lastSeg != curSeg) {
        lastSeg.value()->SetColor(colOldSeg);
        lastSeg++;
        }
  lastSeg = curSeg;
  lastSeg.value()->SetColor(colCurSeg);
  v3D->view()->Invalidate();
  v3D->update();
  }


void Ally3D::highlight(const QVariant& line) {
  if (!v3D) return;
  if (workPath.size() < 1) return;
  int segNum = fmax(0, line.toInt());
  QMap<long, Handle(AIS_InteractiveObject)>::iterator curSeg = workPath.upperBound(segNum);

  if (lastSeg.key() > segNum) lastSeg = curSeg;
//  qDebug() << "Ally3D::highlight(" << segNum << ")";
  while (lastSeg != curSeg) {
        lastSeg.value()->SetColor(colOldSeg);
        lastSeg++;
        }
  lastSeg = curSeg;
  if (!lastSeg->IsNull()) lastSeg.value()->SetColor(colCurSeg);
  }
