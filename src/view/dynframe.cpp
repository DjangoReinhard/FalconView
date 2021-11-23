#include <dynframe.h>
#include <dyncenterwidget.h>
#include <QVBoxLayout>
#include <QFrame>


DynFrame::DynFrame(DynCenterWidget* cw, QWidget *parent)
 : QWidget(parent)
 , frame(new QFrame(this))
 , dcw(cw) {
  setObjectName(cw->windowTitle());
  setLayout(new QVBoxLayout);
  frame->setFrameShape(QFrame::Box);
  frame->setFrameShadow(QFrame::Raised);
  frame->setLineWidth(2);
  frame->setAutoFillBackground(false);
  layout()->addWidget(frame);
  frame->setLayout(new QVBoxLayout);
  frame->layout()->addWidget(dcw);
  }


void DynFrame::init() {
  dcw->initialize();
  }


QAction* DynFrame::viewAction() {
  return dcw->viewAction();
  }


void DynFrame::closeEvent(QCloseEvent *e) {
  dcw->closeEvent(e);
  }
