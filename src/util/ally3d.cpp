#include <ally3d.h>
#include <occtviewer.h>
#include <AIS_ColoredShape.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <valuemanager.h>
#include <canonif.h>
#include <core.h>


Ally3D::Ally3D(OcctQtViewer* view3D, QObject *parent)
 : QObject(parent)
 , v3D(view3D) {
  connect(ValueManager().getModel("curLine", 0), &ValueModel::valueChanged, this, &Ally3D::update);
  }


void Ally3D::moveCone(double x, double y, double z) {
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
  CanonIF ci;
  CANON_POSITION g5xO = ci.g5xOffset(ci.selectedOffset());
  CANON_POSITION g92O = ci.g92Offset();
  double         rot  = ci.xyRotation();  //TODO!
  LcProperties&  lcp  = Core().lcProperties();
  Handle(AIS_InteractiveContext) ctx = v3D->context();

  qDebug() << "showLimits() - g5x:" << g5xO.x << "/" << g5xO.y << "/" << g5xO.z
           << "\tg92: " << g92O.x << "/" << g92O.y << "/" << g92O.z
           << "\trot: " << rot;

  gp_Pnt cMin(lcp.value("AXIS_X", "MIN_LIMIT").toDouble() - g5xO.x - g92O.x
            , lcp.value("AXIS_Y", "MIN_LIMIT").toDouble() - g5xO.y - g92O.y
            , lcp.value("AXIS_Z", "MIN_LIMIT").toDouble() - g5xO.z - g92O.z);
  gp_Pnt cMax(lcp.value("AXIS_X", "MAX_LIMIT").toDouble() - g5xO.x - g92O.x
            , lcp.value("AXIS_Y", "MAX_LIMIT").toDouble() - g5xO.y - g92O.y
            , lcp.value("AXIS_Z", "MAX_LIMIT").toDouble() - g5xO.z - g92O.z);

  Handle(AIS_Shape) shape = ci.graphicFactory().createLine(gp_Pnt(cMin.X(), cMin.Y(), cMin.Z())
                                                         , gp_Pnt(cMax.X(), cMin.Y(), cMin.Z()));
  shape->SetColor(ci.limitColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMin.X(), cMin.Y(), cMin.Z())
                                       , gp_Pnt(cMin.X(), cMax.Y(), cMin.Z()));
  shape->SetColor(ci.limitColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMin.X(), cMin.Y(), cMin.Z())
                                       , gp_Pnt(cMin.X(), cMin.Y(), cMax.Z()));
  shape->SetColor(ci.limitColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMin.X(), cMax.Y(), cMin.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMin.Z()));
  shape->SetColor(ci.limitColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMin.X(), cMin.Y(), cMax.Z())
                                       , gp_Pnt(cMax.X(), cMin.Y(), cMax.Z()));
  shape->SetColor(ci.limitColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMax.X(), cMin.Y(), cMin.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMin.Z()));
  shape->SetColor(ci.limitColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMin.X(), cMax.Y(), cMin.Z())
                                       , gp_Pnt(cMin.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(ci.limitColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMax.X(), cMax.Y(), cMin.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(ci.limitColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMax.X(), cMax.Y(), cMin.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(ci.limitColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMin.X(), cMin.Y(), cMax.Z())
                                       , gp_Pnt(cMax.X(), cMin.Y(), cMax.Z()));
  shape->SetColor(ci.limitColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMax.X(), cMin.Y(), cMax.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(ci.limitColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMax.X(), cMin.Y(), cMin.Z())
                                       , gp_Pnt(cMax.X(), cMin.Y(), cMax.Z()));
  shape->SetColor(ci.limitColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMin.X(), cMin.Y(), cMax.Z())
                                       , gp_Pnt(cMin.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(ci.limitColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMin.X(), cMax.Y(), cMax.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(ci.limitColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  }


void Ally3D::showWorkLimits() {
  Handle(AIS_InteractiveContext) ctx = v3D->context();
  gp_Pnt  cMin = workPiece.CornerMin();
  gp_Pnt  cMax = workPiece.CornerMax();
  CanonIF ci;

  Handle(AIS_Shape) shape = ci.graphicFactory().createLine(gp_Pnt(cMin.X(), cMin.Y(), cMin.Z())
                                                         , gp_Pnt(cMax.X(), cMin.Y(), cMin.Z()));
  shape->SetColor(ci.workPieceColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMin.X(), cMin.Y(), cMin.Z())
                                       , gp_Pnt(cMin.X(), cMax.Y(), cMin.Z()));
  shape->SetColor(ci.workPieceColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMin.X(), cMin.Y(), cMin.Z())
                                       , gp_Pnt(cMin.X(), cMin.Y(), cMax.Z()));
  shape->SetColor(ci.workPieceColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMin.X(), cMax.Y(), cMin.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMin.Z()));
  shape->SetColor(ci.workPieceColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMin.X(), cMin.Y(), cMax.Z())
                                       , gp_Pnt(cMax.X(), cMin.Y(), cMax.Z()));
  shape->SetColor(ci.workPieceColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMax.X(), cMin.Y(), cMin.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMin.Z()));
  shape->SetColor(ci.workPieceColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMin.X(), cMax.Y(), cMin.Z())
                                       , gp_Pnt(cMin.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(ci.workPieceColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMax.X(), cMax.Y(), cMin.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(ci.workPieceColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMax.X(), cMax.Y(), cMin.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(ci.workPieceColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMin.X(), cMin.Y(), cMax.Z())
                                       , gp_Pnt(cMax.X(), cMin.Y(), cMax.Z()));
  shape->SetColor(ci.workPieceColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMax.X(), cMin.Y(), cMax.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(ci.workPieceColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMax.X(), cMin.Y(), cMin.Z())
                                       , gp_Pnt(cMax.X(), cMin.Y(), cMax.Z()));
  shape->SetColor(ci.workPieceColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMin.X(), cMin.Y(), cMax.Z())
                                       , gp_Pnt(cMin.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(ci.workPieceColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  shape = ci.graphicFactory().createLine(gp_Pnt(cMin.X(), cMax.Y(), cMax.Z())
                                       , gp_Pnt(cMax.X(), cMax.Y(), cMax.Z()));
  shape->SetColor(ci.workPieceColor());
  ctx->Display(shape, AIS_Shaded, 0, false);
  }


void Ally3D::showPath(const QMap<long, Handle(AIS_InteractiveObject)>& path) {
  Handle(AIS_InteractiveContext) ctx = v3D->context();  

  workPath.clear();
  workPath = path;
  ctx->RemoveAll(false);
  gp_Pnt  cMin, cMax, p;
  Bnd_Box bb;
  gp_Dir  axis = gp::DZ();
  gp_Ax2  aplace(gp_Pnt(0, 0, 0), axis);
  Quantity_Color    col;
  Quantity_Color    tc = CanonIF().feedColor();
  TopoDS_Shape      topo_cone = BRepPrimAPI_MakeCone(aplace, 0.001, 10, 20).Shape();


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
  if (workPath.size() < 1) return;
  int segNum = fmax(0, line.toInt() - 2);
  QMap<long, Handle(AIS_InteractiveObject)>::iterator curSeg = workPath.upperBound(segNum);
  Quantity_Color cCur = CanonIF().curSegColor();
  Quantity_Color cOld = CanonIF().oldSegColor();

  if (lastSeg.key() > segNum) lastSeg = curSeg;
//  qDebug() << "Ally3D::update(" << segNum << ")";
  while (lastSeg != curSeg) {
        lastSeg.value()->SetColor(cOld);
        lastSeg++;
        }
  lastSeg = curSeg;
  lastSeg.value()->SetColor(cCur);
  v3D->view()->Invalidate();
  v3D->update();
  }
