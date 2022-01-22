#include <centerpage.h>
#include <abscenterwidget.h>
#include <CenterPageInterface.h>
#include <core.h>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QAction>
#include <QFrame>
#include <QDebug>


CenterPage::CenterPage(AbstractCenterWidget* cw, bool visualFrame, QWidget *parent)
 : QWidget(parent)
 , frame(nullptr)
 , dcw(cw) {
  setObjectName(QString("%1Frame").arg(dcw->objectName()));
  setWindowTitle(dcw->windowTitle());
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


QString CenterPage::name() const {
  if (dcw) return dcw->windowTitle();
  return objectName();
  }


QString CenterPage::id() const {
  if (dcw) return dcw->objectName();
  return objectName();
  }


QAction* CenterPage::viewAction() {
//  CenterPageInterface* cpi = reinterpret_cast<CenterPageInterface*>(dcw);
  CenterPageInterface* cpi = qobject_cast<CenterPageInterface*>(dcw);

  if (cpi) return cpi->viewAction();
  return new QAction();
  }


void CenterPage::closeEvent(QCloseEvent *e) {
  if (dcw) dcw->closeEvent(e);
  }
