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

#ifdef _WIN32
  #include <windows.h>
#endif
#include <OpenGl_Context.hxx>
#include <occtviewer.h>

#include <Standard_WarningsDisable.hxx>
#include <QApplication>
#include <QMessageBox>
#include <QMouseEvent>
#include <QDebug>
#include <Standard_WarningsRestore.hxx>

#include <AIS_Shape.hxx>
#include <AIS_ViewCube.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <Aspect_NeutralWindow.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <Message.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <OpenGl_FrameBuffer.hxx>


namespace
{
//! Map Qt buttons bitmask to virtual keys.
Aspect_VKeyMouse qtMouseButtons2VKeys(Qt::MouseButtons theButtons) {
  Aspect_VKeyMouse aButtons = Aspect_VKeyMouse_NONE;

  if ((theButtons & Qt::LeftButton) != 0)   aButtons |= Aspect_VKeyMouse_LeftButton;
  if ((theButtons & Qt::MiddleButton) != 0) aButtons |= Aspect_VKeyMouse_MiddleButton;
  if ((theButtons & Qt::RightButton) != 0)  aButtons |= Aspect_VKeyMouse_RightButton;

  return aButtons;
  }


//! Map Qt mouse modifiers bitmask to virtual keys.
Aspect_VKeyFlags qtMouseModifiers2VKeys(Qt::KeyboardModifiers theModifiers) {
  Aspect_VKeyFlags aFlags = Aspect_VKeyFlags_NONE;

  if ((theModifiers & Qt::ShiftModifier) != 0)   aFlags |= Aspect_VKeyFlags_SHIFT;
  if ((theModifiers & Qt::ControlModifier) != 0) aFlags |= Aspect_VKeyFlags_CTRL;
  if ((theModifiers & Qt::AltModifier) != 0)     aFlags |= Aspect_VKeyFlags_ALT;

  return aFlags;
  }
}   // end unnamed namespace


OcctQtViewer::OcctQtViewer(bool verbose, QWidget* theParent)
 : QOpenGLWidget(theParent)
 , myIsCoreProfile(false)
 , verbose(verbose) {
  Handle(Aspect_DisplayConnection) aDisp   = new Aspect_DisplayConnection();
  Handle(OpenGl_GraphicDriver)     aDriver = new OpenGl_GraphicDriver(aDisp, false);

  aDriver->ChangeOptions().buffersNoSwap      = true;  // lets QOpenGLWidget to manage buffer swap
  aDriver->ChangeOptions().buffersOpaqueAlpha = true;  // don't write into alpha channel
  aDriver->ChangeOptions().useSystemBuffer    = false; // offscreen FBOs should be always used

  // create viewer
  myViewer = new V3d_Viewer(aDriver);
  myViewer->SetDefaultBackgroundColor(Quantity_NOC_GRAY);
  myViewer->SetDefaultLights();
  myViewer->SetLightOn();
  myViewer->ActivateGrid(Aspect_GT_Rectangular, Aspect_GDM_Lines);

  // create AIS context
  myContext  = new AIS_InteractiveContext(myViewer);
  myViewCube = new AIS_ViewCube();
  myViewCube->SetViewAnimation(myViewAnimation);
  myViewCube->SetFixedAnimationLoop(false);
  myViewCube->SetAutoStartAnimation(true);
  myViewCube->TransformPersistence()->SetOffset2d(Graphic3d_Vec2i(100, 150));

  // note - window will be created later within initializeGL() callback!
  myView = myViewer->CreateView();
  myView->SetImmediateUpdate(false);
  myView->ChangeRenderingParams().NbMsaaSamples  = 4; // warning - affects performance
  myView->ChangeRenderingParams().ToShowStats    = false;
  myView->ChangeRenderingParams().CollectedStats = (Graphic3d_RenderingParams::PerfCounters)
                                                   (Graphic3d_RenderingParams::PerfCounters_FrameRate
                                                  | Graphic3d_RenderingParams::PerfCounters_Triangles);
  // Qt widget setup
  setMouseTracking(true);
  setBackgroundRole(QPalette::NoRole);  // or NoBackground
  setFocusPolicy(Qt::StrongFocus);      // set focus policy to threat
                                        // QContextMenuEvent from keyboard
  setUpdatesEnabled(true);
  setUpdateBehavior(QOpenGLWidget::NoPartialUpdate);

  // OpenGL setup managed by Qt
  QSurfaceFormat aGlFormat;

  aGlFormat.setDepthBufferSize(24);
  aGlFormat.setStencilBufferSize(8);
  //aGlFormat.setOption (QSurfaceFormat::DebugContext, true);
  //aGlFormat.setOption (QSurfaceFormat::DeprecatedFunctions, true);
  aGlFormat.setVersion(4, 5);
  aGlFormat.setProfile(myIsCoreProfile ? QSurfaceFormat::CoreProfile
                                       : QSurfaceFormat::CompatibilityProfile);
#if (QT_VERSION_MAJOR > 5) || (QT_VERSION_MAJOR == 5 && QT_VERSION_MINOR >= 10)
  aGlFormat.setColorSpace(QSurfaceFormat::sRGBColorSpace);
  setTextureFormat(GL_SRGB8_ALPHA8);
#else
  Message::SendWarning("Warning! Qt 5.10+ is required for sRGB setup.\n"
                       "Colors in 3D Viewer might look incorrect (Qt " QT_VERSION_STR " is used).\n");
  aDriver->ChangeOptions().sRGBDisable = true;
#endif
  setFormat (aGlFormat);

#if defined(_WIN32)
  // never use ANGLE on Windows, since OCCT 3D Viewer does not expect this
  QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
  //QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
#endif
  Handle(Prs3d_Drawer) hlStyle = myContext->HighlightStyle();

  hlStyle->SetMethod(Aspect_TOHM_COLOR);
  hlStyle->SetColor(Quantity_NOC_BLUE);
  hlStyle->SetDisplayMode(1);
  hlStyle->SetTransparency(0.2f);
  myContext->SetHighlightStyle(hlStyle);
  }


OcctQtViewer::~OcctQtViewer() {
  }


void OcctQtViewer::dumpGlInfo(bool theIsBasic) {
  TColStd_IndexedDataMapOfStringString aGlCapsDict;

  myView->DiagnosticInformation(aGlCapsDict
                              , theIsBasic ? Graphic3d_DiagnosticInfo_Basic
                                           : Graphic3d_DiagnosticInfo_Complete);
  TCollection_AsciiString anInfo;

  for (TColStd_IndexedDataMapOfStringString::Iterator aValueIter (aGlCapsDict)
     ; aValueIter.More()
     ; aValueIter.Next()) {
      if (!aValueIter.Value().IsEmpty()) {
         if (!anInfo.IsEmpty()) {
            anInfo += "\n";
            }
         anInfo += aValueIter.Key() + ": " + aValueIter.Value();
         }
      }
  Message::SendInfo(anInfo);
  myGlInfo = QString::fromUtf8(anInfo.ToCString());
  }


void OcctQtViewer::initializeGL() {
  const QRect            aRect = rect();
  const Graphic3d_Vec2i  aViewSize(aRect.right()  - aRect.left()
                                 , aRect.bottom() - aRect.top());
  Handle(OpenGl_Context) aGlCtx = new OpenGl_Context();

  if (!aGlCtx->Init(myIsCoreProfile)) {
     Message::SendFail() << "Error: OpenGl_Context is unable to wrap OpenGL context";
     QMessageBox::critical(0, "Failure", "OpenGl_Context is unable to wrap OpenGL context");
     QApplication::exit(1);

     return;
     }
  Handle(Aspect_NeutralWindow) aWindow = Handle(Aspect_NeutralWindow)::DownCast(myView->Window());

  if (!aWindow.IsNull()) {
     aWindow->SetSize(aViewSize.x(), aViewSize.y());
     myView->SetWindow(aWindow, aGlCtx->RenderingContext());
     if (verbose) dumpGlInfo(true);
     }
  else {
     aWindow = new Aspect_NeutralWindow();

     Aspect_Drawable aNativeWin = (Aspect_Drawable )winId();
#ifdef _WIN32
     //HGLRC aWglCtx    = wglGetCurrentContext();
     HDC   aWglDevCtx = wglGetCurrentDC();
     HWND  aWglWin    = WindowFromDC(aWglDevCtx);

     aNativeWin       = (Aspect_Drawable)aWglWin;
#endif
     aWindow->SetNativeHandle(aNativeWin);
     aWindow->SetSize(aViewSize.x(), aViewSize.y());
     myView->SetWindow(aWindow, aGlCtx->RenderingContext());
     if (verbose) dumpGlInfo(true);
     }
  }


void OcctQtViewer::closeEvent(QCloseEvent* e) {
  qDebug() << "OcctQtViewer::closeEvent?!?";
  e->accept();
  }


void OcctQtViewer::setBounds(const Bnd_Box &bounds) {
  myBounds = bounds;
  }


void OcctQtViewer::keyPressEvent(QKeyEvent* e) {
  switch (e->key()) {
    case Qt::Key_F:
         if (e->modifiers() == Qt::KeyboardModifier::ControlModifier)
            frontView();
         else fitAll();
         e->accept();
         break;
    case Qt::Key_T:
         if (e->modifiers() == Qt::KeyboardModifier::ControlModifier) {
            topView();
            e->accept();
            }
         break;
    case Qt::Key_R:
         if (e->modifiers() == Qt::KeyboardModifier::ControlModifier) {
            rightView();
            e->accept();
            }
         break;
    case Qt::Key_L:
         if (e->modifiers() == Qt::KeyboardModifier::ControlModifier) {
            leftView();
            e->accept();
            }
         break;
    case Qt::Key_B:
         if (e->modifiers() == Qt::KeyboardModifier::ControlModifier) {
            backView();
            e->accept();
            }
         break;
    case Qt::Key_3:
         if (e->modifiers() == Qt::KeyboardModifier::ControlModifier) {
            isoView();
            e->accept();
            }
         break;
    default:
         QOpenGLWidget::keyPressEvent(e);
         break;
    }
  }


void OcctQtViewer::fitAll() {
  myView->FitAll(myBounds, false);
  myView->Invalidate();
  update();
  }


void OcctQtViewer::mousePressEvent(QMouseEvent* e) {
  QOpenGLWidget::mousePressEvent(e);
  const Graphic3d_Vec2i  aPnt(e->pos().x(), e->pos().y());
  const Aspect_VKeyFlags aFlags = qtMouseModifiers2VKeys(e->modifiers());

  if (!myView.IsNull()
    && UpdateMouseButtons(aPnt
                        , qtMouseButtons2VKeys(e->buttons())
                        , aFlags
                        , false)) {
     updateView();
     }
  }


void OcctQtViewer::mouseReleaseEvent(QMouseEvent* e) {
  QOpenGLWidget::mouseReleaseEvent(e);
  const Graphic3d_Vec2i  aPnt(e->pos().x(), e->pos().y());
  const Aspect_VKeyFlags aFlags = qtMouseModifiers2VKeys(e->modifiers());

  if (!myView.IsNull()
    && UpdateMouseButtons(aPnt
                        , qtMouseButtons2VKeys(e->buttons())
                        , aFlags
                        , false)) {
     updateView();
     }
  }


void OcctQtViewer::mouseMoveEvent(QMouseEvent* e) {
  QOpenGLWidget::mouseMoveEvent(e);
  const Graphic3d_Vec2i aNewPos (e->pos().x(), e->pos().y());

  if (!myView.IsNull()
    && UpdateMousePosition(aNewPos
                         , qtMouseButtons2VKeys(e->buttons())
                         , qtMouseModifiers2VKeys(e->modifiers())
                         , false)) {
     updateView();
     }
  }


void OcctQtViewer::wheelEvent(QWheelEvent* e) {
  QOpenGLWidget::wheelEvent(e);
  const Graphic3d_Vec2i aPos(e->position().x(), e->position().y());

  if (!myView.IsNull()
    && UpdateZoom(Aspect_ScrollDelta(aPos, e->angleDelta().y() / 8))) {
     updateView();
     }
  }


void OcctQtViewer::updateView() {
  update();
  }


void OcctQtViewer::paintGL() {
  if (myView->Window().IsNull()) return;

  // wrap FBO created by QOpenGLWidget
  Handle(OpenGl_GraphicDriver)  aDriver     = Handle(OpenGl_GraphicDriver)::DownCast(myContext->CurrentViewer()->Driver());
  const Handle(OpenGl_Context)& aGlCtx      = aDriver->GetSharedContext();
  Handle(OpenGl_FrameBuffer)    aDefaultFbo = aGlCtx->DefaultFrameBuffer();

  if (aDefaultFbo.IsNull()) {
     aDefaultFbo = new OpenGl_FrameBuffer();
     aGlCtx->SetDefaultFrameBuffer(aDefaultFbo);
     }
  if (!aDefaultFbo->InitWrapper(aGlCtx)) {
     aDefaultFbo.Nullify();
     Message::DefaultMessenger()->Send("Default FBO wrapper creation failed", Message_Fail);
     QMessageBox::critical(0, "Failure", "Default FBO wrapper creation failed");
     QApplication::exit(1);
     return;
     }
  Graphic3d_Vec2i              aViewSizeOld;
  Graphic3d_Vec2i              aViewSizeNew = aDefaultFbo->GetVPSize();
  Handle(Aspect_NeutralWindow) aWindow      = Handle(Aspect_NeutralWindow)::DownCast(myView->Window());

  aWindow->Size(aViewSizeOld.x(), aViewSizeOld.y());
  if (aViewSizeNew != aViewSizeOld) {
     aWindow->SetSize(aViewSizeNew.x(), aViewSizeNew.y());
     myView->MustBeResized();
     myView->Invalidate();
     }
  // flush pending input events and redraw the viewer
  myView->InvalidateImmediate();
  FlushViewEvents(myContext, myView, true);
  }


void OcctQtViewer::handleViewRedraw(const Handle(AIS_InteractiveContext)& theCtx
                                  , const Handle(V3d_View)& theView) {
  AIS_ViewController::handleViewRedraw(theCtx, theView);

  if (myToAskNextFrame) {
     updateView();      // ask more frames for animation
     }
  }


void OcctQtViewer::frontView() {
  myView->SetProj(V3d_Yneg);
  fitAll();
  }


void OcctQtViewer::backView() {
  myView->SetProj(V3d_Ypos);
  fitAll();
  }


void OcctQtViewer::topView() {
  myView->SetProj(V3d_Zpos);
  fitAll();
  }


void OcctQtViewer::leftView() {
  myView->SetProj(V3d_Xneg);
  fitAll();
  }


void OcctQtViewer::rightView() {
  myView->SetProj(V3d_Xpos);
  fitAll();
  }


void OcctQtViewer::isoView() {
  myView->SetProj(V3d_XposYnegZpos);
  fitAll();
  }
