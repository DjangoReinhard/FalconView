#include <dyncenterwidget.h>
#include <dyndockable.h>
#include <configacc.h>
#include <QString>
#include <QFrame>
#include <QAction>
#include <QFile>
#include <QDebug>
#include <QKeyEvent>
#include <QUiLoader>
#include <QScrollArea>
#include <QStackedLayout>


/*! loads widgets from uiFile and allows late initialization at page usage
 */
DynCenterWidget::DynCenterWidget(const QString& fileName, const QString& name, bool addScrollArea, QWidget* parent)
 : QWidget(parent)
 , vAction(nullptr)
 , fileName(fileName)
 , addScrollArea(addScrollArea) {
  setWindowTitle(name);
  }


QWidget* DynCenterWidget::createContent() {
  QFile     uiDesc(fileName);
  QWidget*  rv = nullptr;

  if (uiDesc.exists()) {
     QUiLoader loader;
     QWidget*  w = loader.load(&uiDesc, this);

     uiDesc.close();
     if (w) {
        if (addScrollArea) {
           QScrollArea* sa = new QScrollArea(this);

           sa->setWidget(w);
           sa->setWidgetResizable(true);
           rv = sa;
           }
        else rv = w;
        }
     }
  return rv;
  }


// offline initialization (i.e. called by MainView::addPage)
void DynCenterWidget::initialize() {
  QWidget* w = createContent();

  if (w) {
     setLayout(new QVBoxLayout);
     layout()->setContentsMargins(0, 0, 0, 0);
     layout()->addWidget(w);
     }
  connectSignals();
  updateStyles();
  layout()->invalidate();
  }


QAction* DynCenterWidget::viewAction() {
  if (!vAction) {
     vAction = new QAction(this);

     vAction->setMenuRole(QAction::NoRole);
     vAction->setText(windowTitle());
     }
  return vAction;
  }


void DynCenterWidget::closeEvent(QCloseEvent* e) {
  QWidget::closeEvent(e);
  }


void DynCenterWidget::keyPressEvent(QKeyEvent* e) {
  qDebug() << "DynCenterWidget::keyPressEvent of " << objectName() << "ts:" << e->timestamp();
  QWidget::keyPressEvent(e);
  }


void DynCenterWidget::keyReleaseEvent(QKeyEvent* e) {
  qDebug() << "DynCenterWidget::keyReleaseEvent of " << objectName() << "ts:" << e->timestamp();
  QWidget::keyPressEvent(e);
  }
