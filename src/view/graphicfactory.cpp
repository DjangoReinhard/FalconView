#include "graphicfactory.h"
#include <cassert>
#include <AIS_ColoredShape.hxx>
#include <gp_Circ.hxx>
#include <Geom_Line.hxx>
#include <Geom_Circle.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <GC_MakeArcOfEllipse.hxx>
#include <GC_MakeCircle.hxx>
#include <gce_MakeDir.hxx>
#include <gce_MakeElips.hxx>
#include <TopoDS_Edge.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>

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
