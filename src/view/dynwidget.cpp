#include <dynwidget.h>
#include <configacc.h>
#include <QString>
#include <QFrame>
#include <QAction>
#include <QFile>
#include <QDebug>
#include <QUiLoader>
#include <QScrollArea>
#include <QStackedLayout>


/*! loads widgets from uiFile and allows late initialization at page usage
 */
DynWidget::DynWidget(const QString& fileName, bool addScrollArea, QWidget* parent)
 : QFrame(parent)
 , vAction(nullptr) {
  QFile     uiDesc(fileName);

  if (uiDesc.exists()) {
     setLayout(new QVBoxLayout);
     w = loadFromUI(uiDesc);
     layout()->setContentsMargins(0, 0, 0, 0);
     if (w) {
        if (addScrollArea) {
           QScrollArea* sa = new QScrollArea(this);

           sa->setWidget(w);
           sa->setWidgetResizable(true);
           layout()->addWidget(sa);
           }
        else layout()->addWidget(w);
        }
     }
  }


// called by MainView::addPage
void DynWidget::init() {
  connectSignals();
  updateStyles();
  }


void DynWidget::closeEvent(QCloseEvent*) {
  qDebug() << "DynWidget::closeEvent() on widget " << objectName();
//  Config cfg;

//  cfg.setValue("widgetState", this->saveState());
  }


QAction* DynWidget::viewAction() {
  if (!vAction) {
     vAction = new QAction(this);

     vAction->setMenuRole(QAction::NoRole);
     vAction->setText(objectName());
     }
  return vAction;
  }


QWidget* DynWidget::loadFromUI(QFile& uiFile) {
  QWidget*  rv = nullptr;

  if (uiFile.exists()) {
     QUiLoader loader;
     rv = loader.load(&uiFile, this);

     uiFile.close();
     }
  return rv;
  }
