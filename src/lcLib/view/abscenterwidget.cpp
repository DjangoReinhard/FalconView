#include <abscenterwidget.h>
#include <configacc.h>
#include <guicore.h>
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
 , core(nullptr)
 , cfg(nullptr)
 , vm(nullptr)
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


// offline initialization
void AbstractCenterWidget::initialize(const QString& fileName, const QString& name, bool addScrollArea) {
  if (!core) {
     core = new GuiCore();
     cfg  = new Config();
     vm   = new ValueManager();
     }
  this->fileName = fileName;
  this->addScrollArea = addScrollArea;
  if (!name.isEmpty()) {
     setObjectName(name);
     setWindowTitle(tr(name.toStdString().c_str()));
     }
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


void AbstractCenterWidget::patch(void *pk, void *pc, void *pv, void*) {
  core = new GuiCore(pk);
  cfg  = new Config(pc);
  vm   = new ValueManager(pv);

  qDebug() << "ACW - core:" << core->kernel << "\tgiven:" << pk;
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
