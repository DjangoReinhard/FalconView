#include "graphicfactory.h"
#include <cassert>
#include <QDebug>
#include <AIS_ColoredShape.hxx>
#include <gp_Circ.hxx>
#include <Geom_Line.hxx>
#include <Geom_Circle.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_HelixData.h>
#include <Geom2d_TrimmedCurve.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <GC_MakeArcOfEllipse.hxx>
#include <GC_MakeCircle.hxx>
#include <gce_MakeDir.hxx>
#include <gce_MakeElips.hxx>
#include <TopoDS_Edge.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_Transform.hxx>

double const MIN_DELTA = 0.001;


Handle(AIS_Shape) GraphicFactory::createLine(const gp_Pnt& from, const gp_Pnt& to) {
  gp_Pnt end = gp_Pnt(to);

  if (from.Distance(to) <= gp::Resolution()) end.SetX(end.X() + 0.001);
  TopoDS_Edge       edge = BRepBuilderAPI_MakeEdge(from, end);
  Handle(AIS_Shape) rv   = new AIS_ColoredShape(edge);

  rv->SetMaterial(Graphic3d_NOM_PLASTIC);
  rv->SetTransparency(0);
  rv->SetWidth(2);

  return rv;
  }


Handle(AIS_Shape) GraphicFactory::createArc(const gp_Pnt& from, const gp_Pnt& to, const gp_Pnt& center, bool ccw) {
  double r0 =center.Distance(from);
  double r1 =center.Distance(to);

  qDebug() << "createArc: r1 - r0" << (r1 - r0);
  assert(abs(r0 - r1) < MIN_DELTA);
  gp_Dir       dir(0, 0, 1);
  gp_Circ      rawCircle(gp_Ax2(center, dir), r0);
  TopoDS_Edge  edge;

  if (from.Distance(to) <= gp::Resolution()) {
     edge = BRepBuilderAPI_MakeEdge(rawCircle);
     }
  else {
     Handle(Geom_TrimmedCurve) arc = GC_MakeArcOfCircle(rawCircle, from, to, ccw);
     edge = BRepBuilderAPI_MakeEdge(arc);
     }
  Handle(AIS_Shape)         rv = new AIS_ColoredShape(edge);

  rv->SetMaterial(Graphic3d_NOM_PLASTIC);
  rv->SetTransparency(0);
  rv->SetWidth(2);

  return rv;
  }


Handle(AIS_Shape) GraphicFactory::createHelix(const gp_Pnt& from
                                            , const gp_Pnt& to
                                            , const gp_Pnt& center
                                            , const gp_Dir& axis
                                            , bool          ccw
                                            , int           fullTurns) {
  Handle(Geom_BSplineCurve) aHelix;
  Geom_HelixData helDat;
  gp_Ax3 pos(center, axis);
  gp_Lin centerAxis(center, axis);
  gp_Ax2 cylAxis(center, axis);
  gp_Lin normStart  = centerAxis.Normal(from);
  gp_Lin normEnd    = centerAxis.Normal(to);
  double r0         = centerAxis.Distance(from);
  double r1         = centerAxis.Distance(to);
  double angStart   = pos.XDirection().Angle(normStart.Direction());
  double angEnd     = pos.XDirection().Angle(normEnd.Direction());
  double angle      = 2 * M_PI - normStart.Angle(normEnd);
  double height     = normStart.Distance(normEnd);
  double turnFactor = (angle + (fullTurns * 2.0 * M_PI)) / (2.0 * M_PI);
  double pitch      = height / turnFactor;

  qDebug() << "angle of start point:" << angStart
           << "angle of end point:" << angEnd;
  qDebug() << "makeHelix: r0=" << r0 << "r1=" << r1
           << "height=" << height << "angle=" << angle
           << "pitch=" << pitch << "turnFactor=" << turnFactor;
  qDebug() << "pitch * turnFactor = " << (pitch * turnFactor);

  if (ccw) pos.XReverse();
  helDat.setPosition(pos);
  helDat.setRadius(r0);
  helDat.setPitch(pitch);
  helDat.setRangeMax(angle);
  Handle(AIS_Shape) rv;

  if (helDat.MakeHelix(helDat, aHelix)) {
     TopoDS_Shape ts = BRepBuilderAPI_MakeEdge(aHelix);
     gp_Trsf rot;

     rot.SetRotation(pos.Axis(), -angStart);
     TopoDS_Shape rts = BRepBuilderAPI_Transform(ts, rot);

     rv = new AIS_Shape(rts);
     rv->SetWidth(2);
     }
  return rv;
  }
