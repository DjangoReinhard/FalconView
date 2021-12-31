#include <abscenterwidget.h>
#include <configacc.h>
#include <core.h>
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
AbstractCenterWidget::AbstractCenterWidget(QWidget* parent)
 : QWidget(parent)
 , vAction(nullptr)
 , addScrollArea(false) {
  }


void AbstractCenterWidget::closeEvent(QCloseEvent* e) {
  QWidget::closeEvent(e);
  }


QWidget* AbstractCenterWidget::createContent() {
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


void AbstractCenterWidget::dbSetup(DBConnection *) {
  }


// offline initialization
void AbstractCenterWidget::initialize(const QString& fileName, const QString& name, DBConnection* conn, bool addScrollArea) {
  this->fileName = fileName;
  this->addScrollArea = addScrollArea;
  if (!name.isEmpty()) {
     setObjectName(name);
     setWindowTitle(tr(name.toStdString().c_str()));
     }
  if (conn) dbSetup(conn);
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


QAction* AbstractCenterWidget::viewAction() {
  if (!vAction) {
     vAction = new QAction(this);

     vAction->setMenuRole(QAction::NoRole);
     vAction->setText(windowTitle());
     }
  return vAction;
  }


void AbstractCenterWidget::showEvent(QShowEvent* e) {
  QWidget::showEvent(e);
  if (e->type() == QEvent::Show) {
     if (Config().value("showHelpAtPageChange").toBool())
        Core().help4Keyword(objectName());
     }
  }
