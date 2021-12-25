#include <dynframe.h>
#include <dyncenterwidget.h>
#include <core.h>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QAction>
#include <QFrame>
#include <QDebug>


DynFrame::DynFrame(DynCenterWidget* cw, bool visualFrame, QWidget *parent)
 : QWidget(parent)
 , frame(nullptr)
 , dcw(cw) {
  setObjectName(QString("%1Frame").arg(cw->objectName()));
  setWindowTitle(cw->windowTitle());
  setLayout(new QVBoxLayout);
  layout()->setContentsMargins(0, 0, 0, 0);
  if (visualFrame) {
     frame = new QFrame(this);
     frame->setFrameShape(QFrame::Box);
     frame->setFrameShadow(QFrame::Raised);
     frame->setLineWidth(2);
     frame->setAutoFillBackground(false);
     layout()->addWidget(frame);
     frame->setLayout(new QVBoxLayout);
     frame->layout()->addWidget(dcw);
     frame->layout()->setContentsMargins(0, 0, 0, 0);
     }
  else layout()->addWidget(dcw);
  }


void DynFrame::init() {
  if (dcw) dcw->initialize();
  }


QString DynFrame::name() const {
  if (dcw) return dcw->windowTitle();
  return objectName();
  }


QString DynFrame::id() const {
  if (dcw) return dcw->objectName();
  return objectName();
  }


QAction* DynFrame::viewAction() {
  if (dcw) return dcw->viewAction();
  return new QAction();
  }


void DynFrame::closeEvent(QCloseEvent *e) {
  if (dcw) dcw->closeEvent(e);
  }


void DynFrame::keyPressEvent(QKeyEvent *e) {
//  qDebug() << "DynFrame::keyPressEvent() of" << objectName() << "ts: " << e->timestamp();
  if (dcw) dcw->keyPressEvent(e);
  }


void DynFrame::keyReleaseEvent(QKeyEvent *e) {
//  qDebug() << "DynFrame::keyReleaseEvent() of" << objectName() << "ts: " << e->timestamp();
  if (dcw) dcw->keyReleaseEvent(e);
  }
