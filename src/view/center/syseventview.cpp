#include <syseventview.h>
#include <syseventmodel.h>
#include <valuemanager.h>
#include <QSortFilterProxyModel>
#include <QShowEvent>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QTableView>
#include <QDebug>


SysEventView::SysEventView(DBConnection& conn, QWidget* parent)
 : DynWidget(QString(), false, parent)
 , table(new QTableView)
 , model(new SysEventModel(conn))
 , px(new QSortFilterProxyModel(this)) {
  setObjectName(SysEventView::className);
  setLayout(new QVBoxLayout(this));
  px->setSourceModel(model);
  table->setModel(px);
  table->setSelectionMode(QAbstractItemView::SingleSelection);
  table->setTabKeyNavigation(false);
  table->setSortingEnabled(true);
  table->horizontalHeader()->setStretchLastSection(true);
  table->horizontalHeader()->setSortIndicator(1, Qt::AscendingOrder);
  table->setAlternatingRowColors(true);
  layout()->addWidget(table);
  }


SysEventView::~SysEventView() {
  }


void SysEventView::connectSignals() {
  }


void SysEventView::updateStyles() {
  }


void SysEventView::showEvent(QShowEvent* e) {
  if (e->type() == QEvent::Show) {
     qDebug() << ">>>   SysEventView::showEvent - SHOW";
     ValueManager().setValue("errorActive", true);
     }
  }


void SysEventView::hideEvent(QHideEvent* e) {
  if (e->type() == QEvent::Hide) {
     qDebug() << "<<<   SysEventView::showEvent - HIDE";
     ValueManager().setValue("errorActive", false);
     }
  }


const QString SysEventView::className = "SysEventView";
