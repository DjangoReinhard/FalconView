#include "syseventview.h"
#include <configacc.h>
#include <valuemanager.h>
#include <dynaaction.h>
#include <andcondition.h>
#include <equalcondition.h>
#include <truecondition.h>
#include <guicore.h>
#include <syseventmodel.h>
#include <QSortFilterProxyModel>
#include <QShowEvent>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QTableView>
#include <QDebug>


SysEventView::SysEventView(QWidget* parent)
 : AbstractCenterWidget(QString(), parent)
 , table(new QTableView)
 , model(nullptr)
 , px(new QSortFilterProxyModel(this)) {
  setObjectName("SysEventView");
  setWindowTitle(tr("SysEventView"));
  }


QWidget* SysEventView::createContent() {
  model = new SysEventModel(*core->databaseConnection());
  px->setSourceModel(model);
  table->setModel(px);
  table->setSelectionMode(QAbstractItemView::SingleSelection);
  table->setTabKeyNavigation(false);
  table->setSortingEnabled(true);
  table->horizontalHeader()->setStretchLastSection(true);
  table->horizontalHeader()->setSortIndicator(1, Qt::AscendingOrder);
  table->setAlternatingRowColors(true);
  table->installEventFilter(this);
  cfg->beginGroup("SysEventView");
  table->horizontalHeader()->restoreState(cfg->value("State").toByteArray());
  cfg->endGroup();

  return table;
  }


SysEventView::~SysEventView() {
  }


void SysEventView::showEvent(QShowEvent* e) {
  if (e->type() == QEvent::Show) {
     model->select();
     }
  }


void SysEventView::closeEvent(QCloseEvent* e) {
  }


void SysEventView::connectSignals() {
  }


void SysEventView::updateStyles() {
  }


bool SysEventView::eventFilter(QObject*, QEvent* event) {
  if (event->type() == QEvent::KeyPress) {
     QKeyEvent* e = static_cast<QKeyEvent*>(event);

     switch (e->key()) {
       case Qt::Key_Escape: {
            qDebug() << "SEV: hit ESC ... (old page:" << vm->getValue("lastPage").toString() << ")";
            vm->setValue("errorActive", false);
            vm->setValue("showAllButCenter", true);
            cfg->beginGroup("SysEventView");
            cfg->setValue("State", table->horizontalHeader()->saveState());
            cfg->endGroup();
            core->setAppMode4PageID(vm->getValue("lastPage").toString());
            } break;
       }
     }
  return false;
  }


QAction* SysEventView::viewAction() {
  if (!action) {
     action = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                           , QIcon(":SK_Messages.png")
                           , QIcon(":SK_Messages_active.png")
                           , tr("SysEvents")
                           , new TrueCondition()
                           , new EqualCondition(vm->getModel("errorActive"), true)
                           , this);
     }
  return action;
  }
