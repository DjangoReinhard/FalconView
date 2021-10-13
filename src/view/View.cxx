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

#if !defined _WIN32
#define QT_CLEAN_NAMESPACE         /* avoid definition of INT32 and INT8 */
#endif

#include "View.h"
#include "OcctWindow.h"

#include <Standard_WarningsDisable.hxx>
#include <QApplication>
#include <QBoxLayout>
#include <QFileInfo>
#include <QFileDialog>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QMdiSubWindow>
#include <QColorDialog>
#include <QActionGroup>
#include <QCursor>
#include <QDebug>
#include <QPainter>
#include <QStyleFactory>
#include <Standard_WarningsRestore.hxx>

#if !defined(_WIN32) && (!defined(__APPLE__) || defined(MACOSX_USE_GLX)) && QT_VERSION < 0x050000
#include <QX11Info>
#endif

#include <Aspect_DisplayConnection.hxx>
#include <Graphic3d_GraphicDriver.hxx>
#include <Graphic3d_TextureEnv.hxx>


namespace
{
//! Map Qt buttons bitmask to virtual keys.
static Aspect_VKeyMouse qtMouseButtons2VKeys(Qt::MouseButtons theButtons) {
  Aspect_VKeyMouse aButtons = Aspect_VKeyMouse_NONE;

  if ((theButtons & Qt::LeftButton)   != 0) aButtons |= Aspect_VKeyMouse_LeftButton;
  if ((theButtons & Qt::MiddleButton) != 0) aButtons |= Aspect_VKeyMouse_MiddleButton;
  if ((theButtons & Qt::RightButton)  != 0) aButtons |= Aspect_VKeyMouse_RightButton;
  return aButtons;
  }


//! Map Qt mouse modifiers bitmask to virtual keys.
static Aspect_VKeyFlags qtMouseModifiers2VKeys(Qt::KeyboardModifiers theModifiers) {
  Aspect_VKeyFlags aFlags = Aspect_VKeyFlags_NONE;

  if ((theModifiers & Qt::ShiftModifier)   != 0) aFlags |= Aspect_VKeyFlags_SHIFT;
  if ((theModifiers & Qt::ControlModifier) != 0) aFlags |= Aspect_VKeyFlags_CTRL;
  if ((theModifiers & Qt::AltModifier)     != 0) aFlags |= Aspect_VKeyFlags_ALT;
  return aFlags;
  }

static QCursor* defCursor     = nullptr;
static QCursor* handCursor    = nullptr;
static QCursor* panCursor     = nullptr;
static QCursor* globPanCursor = nullptr;
static QCursor* zoomCursor    = nullptr;
static QCursor* rotCursor     = nullptr;
}


View::View (const Handle(AIS_InteractiveContext)& theContext, QWidget* theParent)
 : QWidget(theParent)
 , myIsRaytracing(false)
 , myIsShadowsEnabled(true)
 , myIsReflectionsEnabled(false)
 , myIsAntialiasingEnabled(false)
 , myBackMenu(nullptr) {
#if !defined(_WIN32) && (!defined(__APPLE__) || defined(MACOSX_USE_GLX)) && QT_VERSION < 0x050000
  XSynchronize(x11Info().display(), true);
#endif
  myContext = theContext;
  myCurZoom = 0;

  setAttribute(Qt::WA_PaintOnScreen);
  setAttribute(Qt::WA_NoSystemBackground);
  setAttribute(Qt::WA_NativeWindow);

  myDefaultGestures = myMouseGestureMap;
  myCurrentMode = CurrentAction3d::Nothing;
  setMouseTracking(true);
  initViewActions();
  initCursors();
  setBackgroundRole(QPalette::NoRole);
  setFocusPolicy(Qt::StrongFocus);
  setAttribute(Qt::WA_PaintOnScreen);
  setAttribute(Qt::WA_NoSystemBackground);
  init();
  timer.start(200, this);
  }


void View::init() {
  if (myV3dView.IsNull()) myV3dView = myContext->CurrentViewer()->CreateView();
  Handle(OcctWindow) hWnd = new OcctWindow(this);

  myV3dView->SetWindow(hWnd);
  if (!hWnd->IsMapped()) {
     hWnd->Map();
     }
  Quantity_Color cola,colb;

  cola.SetValues(0.95, 0.95, 0.95, Quantity_TOC_RGB);
  colb.SetValues(0.5, 0.5, 0.5, Quantity_TOC_RGB);
  myV3dView->SetBgGradientColors(cola
                               , colb
                               , Aspect_GFM_CORNER2
                               , false);
  myContext->SetDisplayMode(AIS_Shaded, Standard_False);
  Handle(Prs3d_Drawer) t_hilight_style = myContext->HighlightStyle();
  Handle(Prs3d_Drawer) t_select_style = myContext->SelectionStyle();

  t_hilight_style->SetColor(Quantity_NOC_BLUE1);
  t_select_style->SetColor(Quantity_NOC_RED);
  myV3dView->MustBeResized();
  if (myIsRaytracing) myV3dView->ChangeRenderingParams().Method = Graphic3d_RM_RAYTRACING;
  }


void View::paintEvent(QPaintEvent *) {
  myV3dView->InvalidateImmediate();
  FlushViewEvents(myContext, myV3dView, true);
  }


void View::resizeEvent(QResizeEvent *) {
  if (!myV3dView.IsNull()) myV3dView->MustBeResized();
  }


void View::timerEvent(QTimerEvent *e) {
//  qDebug() << "start of timerEvent ...";
  if (e->timerId() == timer.timerId() && this->isVisible())  {
     qDebug() << "redraw 3D-View ...";
     myV3dView->Redraw();
     }
  }


void View::OnSelectionChanged(const Handle(AIS_InteractiveContext)& theCtx, const Handle(V3d_View)& theView) {
  Q_UNUSED(theCtx)
  Q_UNUSED(theView)
  }


void View::fitAll() {
  myV3dView->FitAll(myLimits);
  myV3dView->ZFitAll();
  myV3dView->Redraw();
  }


void View::axo() {
  myV3dView->SetProj(V3d_XposYnegZpos);
  }


void View::initCursors() {
  if (!defCursor)     defCursor     = new QCursor(Qt::ArrowCursor);
  if (!handCursor)    handCursor    = new QCursor(Qt::PointingHandCursor);
  if (!panCursor)     panCursor     = new QCursor(Qt::SizeAllCursor);
  if (!globPanCursor) globPanCursor = new QCursor(Qt::CrossCursor);
  if (!zoomCursor)    zoomCursor    = new QCursor(QPixmap(":/res/cursor_zoom.png"));
  if (!rotCursor)     rotCursor     = new QCursor(QPixmap(":/res/cursor_rotate.png"));
  }


QList<QAction*> View::getViewActions() {
  initViewActions();
  return myViewActions.values();
  }


QAction* View::getViewAction(ViewAction theAction) {
  return myViewActions.value(theAction);
  }


/*!
  Get paint engine for the OpenGL viewer. [ virtual public ]
*/
QPaintEngine* View::paintEngine() const {
  return 0;
  }


QAction* View::RegisterAction(QString theIconPath, QString thePromt, void (View::*theSlot)(void)) {
  QAction* anAction = new QAction(QPixmap(theIconPath), thePromt, this);

  anAction->setToolTip(thePromt);
  anAction->setStatusTip(thePromt);
  connect(anAction, &QAction::triggered, this, theSlot);

  return anAction;
  }


void View::initViewActions() {
  if (!myViewActions.empty()) return;
  myViewActions[ViewAction::FitAll] = RegisterAction(":/res/view_fitall.png", tr("Fit all"), &View::fitAll);
  myViewActions[ViewAction::Axo]    = RegisterAction(":/res/view_axo.png", tr("Isometric"), &View::axo);
  }


void View::activateCursor(const CurrentAction3d theMode) {
  QCursor* aCursor = defCursor;

  switch (theMode) {
    case CurrentAction3d::DynamicPanning:  aCursor = panCursor; break;
    case CurrentAction3d::DynamicZooming:  aCursor = zoomCursor; break;
    case CurrentAction3d::DynamicRotation: aCursor = rotCursor; break;
    case CurrentAction3d::GlobalPanning:   aCursor = globPanCursor; break;
    case CurrentAction3d::WindowZooming:   aCursor = handCursor; break;
    case CurrentAction3d::Nothing:         aCursor = defCursor; break;
    default: break;
    }
  setCursor(*aCursor);
  }


void View::updateX(double x) {
  myPos.SetX(x);
  }


void View::moveCone() {
  gp_Trsf move;

  qDebug() << "move cone to " << myPos.X() << "/" << myPos.Y() << "/" << myPos.Z();
  move.SetValues(1, 0, 0, myPos.X(),
                 0, 1, 0, myPos.Y(),
                 0, 0, 1, myPos.Z());
  myContext->SetLocation(myCone, move);
  myContext->Update(myCone, true);
  }


void View::updateY(double y) {
  myPos.SetY(y);
  moveCone();
  }


void View::updateZ(double z) {
  myPos.SetZ(z);
  moveCone();
  }


void View::mousePressEvent(QMouseEvent* theEvent) {
  Qt::MouseButtons       aMouseButtons = theEvent->buttons();
  const Graphic3d_Vec2i  aPnt(theEvent->pos().x(), theEvent->pos().y());
  const Aspect_VKeyFlags aFlags = qtMouseModifiers2VKeys(theEvent->modifiers());

  if (!myV3dView.IsNull()
   && UpdateMouseButtons(aPnt, qtMouseButtons2VKeys(aMouseButtons), aFlags, false)) {
     updateView();
     }
  myClickPos = aPnt;
  }


void View::mouseReleaseEvent(QMouseEvent* theEvent) {
  Qt::MouseButtons       aMouseButtons = theEvent->buttons();
  const Graphic3d_Vec2i  aPnt(theEvent->pos().x(), theEvent->pos().y());
  const Aspect_VKeyFlags aFlags = qtMouseModifiers2VKeys(theEvent->modifiers());

  if (!myV3dView.IsNull()
   && UpdateMouseButtons(aPnt, qtMouseButtons2VKeys(aMouseButtons), aFlags, false)) {
     updateView();
     }
  if (myCurrentMode == CurrentAction3d::GlobalPanning) myV3dView->Place(aPnt.x(), aPnt.y(), myCurZoom);
  if (myCurrentMode != CurrentAction3d::Nothing)       setCurrentAction(CurrentAction3d::Nothing);
  }


void View::mouseMoveEvent(QMouseEvent* theEvent) {
  Qt::MouseButtons      aMouseButtons = theEvent->buttons();
  const Graphic3d_Vec2i aNewPos(theEvent->pos().x(), theEvent->pos().y());

  if (!myV3dView.IsNull()
   && UpdateMousePosition(aNewPos, qtMouseButtons2VKeys(aMouseButtons), qtMouseModifiers2VKeys(theEvent->modifiers()), false)) {
     updateView();
     }
  }


void View::wheelEvent(QWheelEvent* e) {
  myV3dView->StartZoomAtPoint(e->position().x(), e->position().y());
  myV3dView->ZoomAtPoint(0, 0, e->angleDelta().y() / 12, 0);
  }


void View::updateView() {
  update();
  }


void View::defineMouseGestures() {
  myMouseGestureMap.Clear();
  AIS_MouseGesture aRot = AIS_MouseGesture_RotateOrbit;

  activateCursor(myCurrentMode);
  switch (myCurrentMode) {
    case CurrentAction3d::Nothing:
         myMouseGestureMap = myDefaultGestures;
         break;
    case CurrentAction3d::DynamicZooming: {
         myMouseGestureMap.Bind(Aspect_VKeyMouse_LeftButton, AIS_MouseGesture_Zoom);
         } break;
    case CurrentAction3d::GlobalPanning:
         break;
    case CurrentAction3d::WindowZooming: {
         myMouseGestureMap.Bind(Aspect_VKeyMouse_LeftButton, AIS_MouseGesture_ZoomWindow);
         } break;
    case CurrentAction3d::DynamicPanning: {
         myMouseGestureMap.Bind(Aspect_VKeyMouse_LeftButton, AIS_MouseGesture_Pan);
         } break;
    case CurrentAction3d::DynamicRotation: {
         myMouseGestureMap.Bind(Aspect_VKeyMouse_LeftButton, aRot);
         } break;
    default:
      break;    
    }
  }


void View::addItemInPopup(QMenu* theMenu) {
  Q_UNUSED(theMenu)
  }


void View::setLimits(const gp_Pnt &minCorner, const gp_Pnt &maxCorner) {
  myLimits = Bnd_Box(minCorner, maxCorner);
  }
