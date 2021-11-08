// Copyright (c) 2021 OPEN CASCADE SAS
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
#ifndef _OcctQtViewer_HeaderFile
#define _OcctQtViewer_HeaderFile

#include <Standard_WarningsDisable.hxx>
#include <QOpenGLWidget>
#include <QVariant>
#include <Standard_WarningsRestore.hxx>

#include <AIS_InteractiveContext.hxx>
#include <AIS_ViewController.hxx>
#include <AIS_InteractiveObject.hxx>
#include <AIS_Shape.hxx>
#include <V3d_View.hxx>

class AIS_ViewCube;
class Ally3D;


//! OCCT 3D View.
class OcctQtViewer : public QOpenGLWidget, public AIS_ViewController
{
  Q_OBJECT

public:
  OcctQtViewer(bool verbose = false, QWidget* theParent = nullptr);
  virtual ~OcctQtViewer();

  const QString& getGlInfo() const                { return myGlInfo; }
  virtual QSize  minimumSizeHint() const override { return QSize(200, 200); }
  virtual QSize  sizeHint()        const override { return QSize(720, 480); }
  void fitAll();

protected:
  // OpenGL events
  virtual void initializeGL() override;
  virtual void paintGL() override;  

  // user input events
  virtual void closeEvent(QCloseEvent* e) override;
  virtual void keyPressEvent(QKeyEvent* e) override;
  virtual void mousePressEvent(QMouseEvent* e) override;
  virtual void mouseReleaseEvent(QMouseEvent* e) override;
  virtual void mouseMoveEvent(QMouseEvent* e) override;
  virtual void wheelEvent(QWheelEvent* e) override;

  const Handle(V3d_Viewer)&             viewer() const  { return myViewer; }
  const Handle(V3d_View)&               view() const    { return myView; }
  const Handle(AIS_InteractiveContext)& context() const { return myContext; }
  Handle(AIS_ViewCube)                  cube() const    { return myViewCube; }
  Handle(AIS_Shape)                     cone()          { return myCone; }

private:
  void dumpGlInfo(bool theIsBasic);
  void updateView();            //! Request widget paintGL() event.

  virtual void handleViewRedraw(const Handle(AIS_InteractiveContext)& theCtx
                              , const Handle(V3d_View)& theView) override;

private:
  Handle(V3d_Viewer)             myViewer;
  Handle(V3d_View)               myView;
  Handle(AIS_InteractiveContext) myContext;
  Handle(AIS_Shape)              myCone;
  Handle(AIS_ViewCube)           myViewCube;
  Bnd_Box                        myBounds;
  QString                        myGlInfo;
  bool                           myIsCoreProfile;
  bool                           verbose;
  friend class                   Ally3D;
  };
#endif // _OcctQtViewer_HeaderFile
