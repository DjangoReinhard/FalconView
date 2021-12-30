#include <dyndockable.h>
#include <abscenterwidget.h>
#include <QLayout>
#include <QAction>


DynDockable::DynDockable(AbstractCenterWidget* cw, QWidget* parent)
 : QDockWidget(cw->windowTitle(), parent)
 , dcw(cw) {
  setObjectName(QString("%1Dockable").arg(cw->objectName()));
//  titleBarWidget()->setWindowTitle(dcw->windowTitle());
  setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
  layout()->setContentsMargins(0, 0, 0, 0);
  setWidget(cw);
  }


void DynDockable::init(const QString& fileName, const QString& name, bool addScrollArea) {
  dcw->initialize(fileName, name, addScrollArea);
  }


QString DynDockable::name() const {
  if (dcw) return dcw->windowTitle();
  return objectName();
  }


QString DynDockable::id() const {
  if (dcw) return dcw->objectName();
  return objectName();
  }


void DynDockable::closeEvent(QCloseEvent* e) {
  if (dcw) dcw->closeEvent(e);
  }


QAction* DynDockable::viewAction() {
  if (dcw) return dcw->viewAction();
  return new QAction();
  }


//void DynDockable::keyPressEvent(QKeyEvent* e) {
//  if (dcw) dcw->keyPressEvent(e);
//  }


//void DynDockable::keyReleaseEvent(QKeyEvent* e) {
//  if (dcw) dcw->keyReleaseEvent(e);
//  }
