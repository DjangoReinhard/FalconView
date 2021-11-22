#include <dyndockable.h>
#include <dyncenterwidget.h>
#include <QString>
#include <QWidget>
#include <QFile>
#include <QUiLoader>


DynDockable::DynDockable(DynCenterWidget* cw, QWidget* parent)
 : QDockWidget(cw->windowTitle(), parent)
 , centerWidget(cw) {
  setObjectName(cw->windowTitle());
  setWidget(cw);
  setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
  }


void DynDockable::initialize() {
  centerWidget->initialize();
  }
