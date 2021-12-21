#include <syseventview.h>
#include <syseventmodel.h>
#include <configacc.h>
#include <valuemanager.h>
#include <core.h>
#include <QSortFilterProxyModel>
#include <QShowEvent>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QTableView>
#include <QDebug>


SysEventView::SysEventView(DBConnection& conn, QWidget* parent)
 : DynCenterWidget(QString(), "SysEventView", false, parent)
 , table(new QTableView)
 , model(new SysEventModel(conn))
 , px(new QSortFilterProxyModel(this)) {
  setObjectName(SysEventView::className);
  setWindowTitle(SysEventView::className);
  }


QWidget* SysEventView::createContent() {
  px->setSourceModel(model);
  table->setModel(px);
  table->setSelectionMode(QAbstractItemView::SingleSelection);
  table->setTabKeyNavigation(false);
  table->setSortingEnabled(true);
  table->horizontalHeader()->setStretchLastSection(true);
  table->horizontalHeader()->setSortIndicator(1, Qt::AscendingOrder);
  table->setAlternatingRowColors(true);
  table->installEventFilter(this);
  Config cfg;

  cfg.beginGroup(SysEventView::className);
  table->horizontalHeader()->restoreState(cfg.value("State").toByteArray());
  cfg.endGroup();

  return table;
  }


SysEventView::~SysEventView() {
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
            qDebug() << "SEV: hit ESC ... (old page:" << ValueManager().getValue("lastPage").toString() << ")";
            Core().activatePage(ValueManager().getValue("lastPage").toString());
            ValueManager().setValue("errorActive", false);
            ValueManager().setValue("showAllButCenter", true);
            Config cfg;

            cfg.beginGroup(SysEventView::className);
            cfg.setValue("State", table->horizontalHeader()->saveState());
            cfg.endGroup();
            } break;
       }
     }
  return false;
  }


const QString SysEventView::className = "SysEventView";
