/* 
 * **************************************************************************
 * 
 *  file:       graphicfactory.cpp
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
#include "graphicfactory.h"
#include <cassert>
#include <QVector3D>
#include <QDebug>
#include <graphicelement.h>
#include <gerapidmove.h>
#include <geline.h>
#include <gehelix.h>
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


GERapidMove* GraphicFactory::createRapidMove(const gp_Pnt& from, const gp_Pnt& to) {
  gp_Pnt end = gp_Pnt(to);

  if (from.Distance(to) <= gp::Resolution()) end.SetX(end.X() + 0.001);
  TopoDS_Edge  edge = BRepBuilderAPI_MakeEdge(from, end);
  GERapidMove* rv   = new GERapidMove(from, end);

  rv->setShape(new AIS_Shape(edge));

  return rv;
  }


GELine* GraphicFactory::createLine(const gp_Pnt& from, const gp_Pnt& to) {
  gp_Pnt end = gp_Pnt(to);

  if (from.Distance(to) <= gp::Resolution()) end.SetX(end.X() + 0.001);
  TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(from, end);
//  Handle(AIS_Shape) rv   = new AIS_ColoredShape(edge);
  GELine*     rv   = new GELine(from, end);

  rv->setShape(new AIS_Shape(edge));
//  rv->SetMaterial(Graphic3d_NOM_PLASTIC);
//  rv->SetTransparency(0);
//  rv->SetWidth(2);

  return rv;
  }


//GraphicElement* GraphicFactory::createArc(const gp_Pnt& from, const gp_Pnt& to, const gp_Pnt& center, bool ccw) {
//  double r0 =center.Distance(from);
//  double r1 =center.Distance(to);

//  qDebug() << "createArc: r1 - r0" << (r1 - r0);
//  assert(abs(r0 - r1) < MIN_DELTA);
//  gp_Dir       dir(0, 0, 1);
//  gp_Circ      rawCircle(gp_Ax2(center, dir), r0);
//  TopoDS_Edge  edge;

//  if (from.Distance(to) <= gp::Resolution()) {
//     edge = BRepBuilderAPI_MakeEdge(rawCircle);
//     }
//  else {
//     Handle(Geom_TrimmedCurve) arc = GC_MakeArcOfCircle(rawCircle, from, to, ccw);
//     edge = BRepBuilderAPI_MakeEdge(arc);
//     }
//  Handle(AIS_Shape)         rv = new AIS_Shape(edge);

//  rv->SetMaterial(Graphic3d_NOM_PLASTIC);
//  rv->SetTransparency(0);
//  rv->SetWidth(2);

//  return rv;
//  }


GEHelix* GraphicFactory::createHelix(const gp_Pnt& from
                                   , const gp_Pnt& to
                                   , const gp_Pnt& center
                                   , const gp_Dir& axis
                                   , bool          ccw
                                   , int           fullTurns) {
  QVector3D start(from.X(), from.Y(), from.Z());
  QVector3D end(to.X(), to.Y(), from.Z());
  QVector3D c(center.X(), center.Y(), from.Z());
  gp_Dir    hAxis(axis);
  QVector3D s = start - c;
  QVector3D e = end - c;

  double r0 = s.length();
//  double r1 = e.length();
  double a0 = atan2(s.y(), s.x());
  double a1 = atan2(e.y(), e.x());

//  qDebug() << "> PRE(0) - a0:" << a0 << "a1:" << a1;
  if (a0 < 0) a0 += 2 * M_PI;
  if (a1 < 0) a1 += 2 * M_PI;
//  qDebug() << "> PRE(1) - a0:" << a0 << "a1:" << a1;
  double arc = a1 - a0;

//  qDebug() << "> PRE(2) - arc:" << arc;
  if (ccw && a0 > a1 && arc < 0)       arc += 2 * M_PI;
  else if (!ccw) {
     if (a0 < a1 && arc > 0) arc -= 2 * M_PI;
     arc = fabs(arc);
     hAxis.SetZ(-hAxis.Z());
     }
  arc += fullTurns * 2 * M_PI;
//  qDebug() << "> PRE(3) - r0:" << r0 << "r1:" << r1 << "a0 >" << a0 << "< - a1:" << a1 << "arc:" << arc << "\n\n";
  Handle(Geom_BSplineCurve) aHelix;
  Geom_HelixData helDat;
  GEHelix*       rv = nullptr;
  gp_Ax3 pos(gp_Pnt(center.X(), center.Y(), from.Z()), hAxis);
  double height     = to.Z() - from.Z();
  double turnFactor = arc / (2.0 * M_PI);
  double pitch      = height / turnFactor;

  helDat.setPosition(pos);
  helDat.setRadius(r0);
  helDat.setPitch(pitch);
  helDat.setRangeMax(arc);
  Handle(AIS_Shape) shape;

  if (helDat.MakeHelix(helDat, aHelix)) {
     TopoDS_Shape ts = BRepBuilderAPI_MakeEdge(aHelix);
     gp_Trsf rot;
     gp_Trsf trans;

     rot.SetRotation(pos.Axis(), ccw ? a0 : -(a0 + M_PI));
     trans.SetTranslation(gp_Vec(0, 0, 0));
     TopoDS_Shape rts = BRepBuilderAPI_Transform(ts, rot);

     rts = BRepBuilderAPI_Transform(rts, trans);
     rv = new GEHelix(from, to, center, axis, ccw, fullTurns);
     rv->setShape(new AIS_Shape(rts));
     }
  return rv;
  }
