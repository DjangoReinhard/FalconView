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

#ifndef VIEW_H
#define VIEW_H

#include <functional>

#include <Standard_WarningsDisable.hxx>
#include <QAction>
#include <QList>
#include <QMenu>
#include <QToolBar>
#include <QWidget>
#include <QBasicTimer>
#include <Standard_WarningsRestore.hxx>

#include <AIS_InteractiveContext.hxx>
#include <AIS_ViewController.hxx>
#include <AIS_Shape.hxx>
#include <V3d_View.hxx>

class TopoDS_Shape;

enum CurrentAction3d { Nothing, DynamicZooming, WindowZooming,
                       DynamicPanning, GlobalPanning, DynamicRotation, ObjectDececting };
enum ViewAction { FitAll
                , FitArea
                , Zoom
                , Pan
                , GlobalPan
                , Front
                , Back
                , Top
                , Bottom
                , Left
                , Right
                , Axo
                , Rotation
                , Reset
                , HlrOff
                , HlrOn
                , Shading
                , Wireframe
                , Transparency };


//! Qt widget containing V3d_View and toolbar with view manipulation buttons.
//! Also use AIS_ViewController for redirecting user input (mouse, keyboard)
//! into 3D viewer events (rotation, panning, zooming)
class View: public QWidget, protected AIS_ViewController
{
  Q_OBJECT
public:
  View (const Handle(AIS_InteractiveContext)& theContext, QWidget* theParent);
 ~View() {
    delete myBackMenu;
    }

  virtual void    init();
  QList<QAction*> getViewActions();
  QAction*        getViewAction(ViewAction theAction);
  void setLimits(const gp_Pnt& minCorner, const gp_Pnt& maxCorner);
  bool IsRaytracingMode() const      { return myIsRaytracing; }
  bool IsShadowsEnabled() const      { return myIsShadowsEnabled; }
  bool IsReflectionsEnabled() const  { return myIsReflectionsEnabled; }
  bool IsAntialiasingEnabled() const { return myIsAntialiasingEnabled; }

  static QString GetMessages(int type,TopAbs_ShapeEnum aSubShapeType, TopAbs_ShapeEnum aShapeType);
  static QString GetShapeType(TopAbs_ShapeEnum aShapeType);

  Standard_EXPORT static void OnButtonuseraction(int ExerciceSTEP, Handle(AIS_InteractiveContext)& );
  Standard_EXPORT static void DoSelection(int Id, Handle(AIS_InteractiveContext)& );
  Standard_EXPORT static void OnSetSelectionMode(Handle(AIS_InteractiveContext)&,
                                                 Standard_Integer&,
                                                 TopAbs_ShapeEnum& SelectionMode,
                                                 Standard_Boolean& );
  virtual QPaintEngine* paintEngine() const override;
  const Handle(V3d_View)& getView() const { return myV3dView; }
  void setCone(Handle(AIS_Shape) cone)    { myCone = cone; }

signals:
  void selectionChanged();

public slots:
  void fitAll();
  void axo();
  void updateX(double x);
  void updateY(double y);
  void updateZ(double z);
//  void updateToggled(bool);

protected:
  virtual void paintEvent(QPaintEvent*) Standard_OVERRIDE;
  virtual void resizeEvent(QResizeEvent*) Standard_OVERRIDE;
  virtual void mousePressEvent(QMouseEvent*) Standard_OVERRIDE;
  virtual void mouseReleaseEvent(QMouseEvent*) Standard_OVERRIDE;
  virtual void mouseMoveEvent(QMouseEvent*) Standard_OVERRIDE;
  virtual void wheelEvent(QWheelEvent*) Standard_OVERRIDE;  
  virtual void timerEvent(QTimerEvent *e) Standard_OVERRIDE;

  virtual void moveCone();
  virtual void addItemInPopup(QMenu*);
  void         activateCursor(const CurrentAction3d);
  Handle(AIS_InteractiveContext)& getContext()           { return myContext; }
  CurrentAction3d                 getCurrentMode() const { return myCurrentMode; }

private:
  void     initCursors();
  void     initViewActions();
  QAction* RegisterAction(QString theIconPath, QString thePromt, void (View::*theSlot)(void));

private:
  bool myIsRaytracing;
  bool myIsShadowsEnabled;
  bool myIsReflectionsEnabled;
  bool myIsAntialiasingEnabled;

  Handle(V3d_View)                myV3dView;
  Handle(AIS_InteractiveContext)  myContext;
  AIS_MouseGestureMap             myDefaultGestures;
  Graphic3d_Vec2i                 myClickPos;

  void updateView();
//  void repaint();

  //! Setup mouse gestures.
  void defineMouseGestures();

  //! Set current action.
  void setCurrentAction (CurrentAction3d theAction) {
    myCurrentMode = theAction;
    defineMouseGestures();
    }

  //! Handle selection changed event.
  void OnSelectionChanged(const Handle(AIS_InteractiveContext)& theCtx,
                          const Handle(V3d_View)& theView) Standard_OVERRIDE;
  CurrentAction3d                 myCurrentMode;
  Standard_Real                   myCurZoom;
  QMap<ViewAction, QAction*>      myViewActions;
  QMenu*                          myBackMenu;
  QToolBar*                       myViewBar;
  Bnd_Box                         myLimits;
  Handle(AIS_Shape)               myCone;
  gp_Pnt                          myPos;
  QBasicTimer                     timer;
  };
#endif
