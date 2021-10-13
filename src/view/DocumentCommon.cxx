// Copyright (c) 2020 OPEN CASCADE SAS
//
// This file is part of the examples of the Open CASCADE Technology software library.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE

#include <DocumentCommon.h>
#include <mainwindow.h>
#include <View.h>
#include <lcproperties.h>
#include <cmath>

#include <Standard_WarningsDisable.hxx>
#include <QApplication>
#include <QColor>
#include <QColorDialog>
#include <QStatusBar>
#include <Standard_WarningsRestore.hxx>

#include <AIS_InteractiveObject.hxx>
#include <AIS_ViewCube.hxx>
#include <AIS_ColoredShape.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <Graphic3d_NameOfMaterial.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <OSD_Environment.hxx>

#include <TCollection_AsciiString.hxx>


// =======================================================================
// function : Viewer
// purpose  :
// =======================================================================
Handle(V3d_Viewer) DocumentCommon::Viewer(const Standard_ExtString,
                                          const Standard_CString,
                                          const Standard_Real theViewSize,
                                          const V3d_TypeOfOrientation theViewProj,
                                          const Standard_Boolean theComputedMode,
                                          const Standard_Boolean theDefaultComputedMode) {
  static Handle(OpenGl_GraphicDriver) aGraphicDriver;

  if (aGraphicDriver.IsNull()) {
     Handle(Aspect_DisplayConnection) aDisplayConnection;

#if !defined(_WIN32) && !defined(__WIN32__) && (!defined(__APPLE__) || defined(MACOSX_USE_GLX))
     aDisplayConnection = new Aspect_DisplayConnection();
#endif
     aGraphicDriver = new OpenGl_GraphicDriver(aDisplayConnection);
     }
  Handle(V3d_Viewer) aViewer = new V3d_Viewer(aGraphicDriver);

  aViewer->SetDefaultViewSize(theViewSize);
  aViewer->SetDefaultViewProj(theViewProj);
  aViewer->SetComputedMode(theComputedMode);
  aViewer->SetDefaultComputedMode(theDefaultComputedMode);

  return aViewer;
  }


DocumentCommon::DocumentCommon(MainWindow* theApp)
 : QObject(theApp)
 , myContextIsEmpty(true) {
  TCollection_ExtendedString a3DName("Visu3D");

  myViewer = Viewer(a3DName.ToExtString(), "", 1000.0, V3d_XposYnegZpos, Standard_True, Standard_True);
  myViewer->SetDefaultLights();
  myViewer->SetLightOn();
  myContext = new AIS_InteractiveContext(myViewer);
  }


void DocumentCommon::setLimits(LcProperties &cfg) {
  gp_Pnt cMin(cfg.value("AXIS_X", "MIN_LIMIT").toDouble()
            , cfg.value("AXIS_Y", "MIN_LIMIT").toDouble()
            , cfg.value("AXIS_Z", "MIN_LIMIT").toDouble());
  gp_Pnt cMax(cfg.value("AXIS_X", "MAX_LIMIT").toDouble()
            , cfg.value("AXIS_Y", "MAX_LIMIT").toDouble()
            , cfg.value("AXIS_Z", "MAX_LIMIT").toDouble());

  myWorkSpace = Bnd_Box(cMin, cMax);
  }


void DocumentCommon::setObjects(const QList<Handle(AIS_InteractiveObject)>& toolPath, bool shaded) {
  myContext->RemoveAll(Standard_False);
  myContextIsEmpty = toolPath.isEmpty();
  QList<Handle(AIS_InteractiveObject)> graphicElements(toolPath);
  Handle(AIS_ViewCube) aViewCube = new AIS_ViewCube();
  gp_Pnt  cMin, cMax, p;
  Bnd_Box bb;
  Quantity_Color col;
  gp_Dir axis = gp::DZ();
  gp_Ax2 aplace(gp_Pnt(0, 0, 0), axis);
  TopoDS_Shape      topo_cone = BRepPrimAPI_MakeCone(aplace, 0.001, 10, 20).Shape();
  Handle(AIS_Shape) cone      = new AIS_Shape(topo_cone);

  graphicElements.append(aViewCube);
  graphicElements.append(cone);

  for (const Handle(AIS_InteractiveObject)& anObject : graphicElements) {
      if (!shaded) myContext->Display(anObject, Standard_False);
      else         myContext->Display(anObject, AIS_Shaded, 0, Standard_False);
      const Handle(AIS_ColoredShape) shape = Handle(AIS_ColoredShape)::DownCast(anObject);

      if (!shape.IsNull()) {
         shape->Color(col);
         if (col == Quantity_Color(Quantity_NOC_CYAN1)) continue;
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

  myView3d->setLimits(cMin, cMax);
  myView3d->setCone(cone);
  myView3d->fitAll();
  }


void DocumentCommon::Clear() {
  myContext->RemoveAll(Standard_True);
  myContextIsEmpty = true;
  }
