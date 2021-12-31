#include <dockable.h>
#include <abscenterwidget.h>
#include <QLayout>
#include <QAction>


Dockable::Dockable(AbstractCenterWidget* cw, QWidget* parent)
 : QDockWidget(cw->windowTitle(), parent)
 , dcw(cw) {
  dcw->setParent(this);
  setObjectName(QString("%1Dockable").arg(cw->objectName()));
  setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
  layout()->setContentsMargins(0, 0, 0, 0);
  setWidget(cw);
  }


QString Dockable::name() const {
  if (dcw) return dcw->windowTitle();
  return objectName();
  }


QString Dockable::id() const {
  if (dcw) return dcw->objectName();
  return objectName();
  }


void Dockable::closeEvent(QCloseEvent* e) {
  if (dcw) dcw->closeEvent(e);
  }


QAction* Dockable::viewAction() {
  if (dcw) return dcw->viewAction();
  return new QAction();
  }


//void DynDockable::keyPressEvent(QKeyEvent* e) {
//  if (dcw) dcw->keyPressEvent(e);
//  }


//void DynDockable::keyReleaseEvent(QKeyEvent* e) {
//  if (dcw) dcw->keyReleaseEvent(e);
//  }
