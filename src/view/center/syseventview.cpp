#include <syseventview.h>
#include <syseventmodel.h>
#include <QSortFilterProxyModel>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QTableView>


SysEventView::SysEventView(DBConnection& conn, QWidget* parent)
 : DynWidget(QString(), false, parent)
 , table(new QTableView)
 , model(new SysEventModel(conn))
 , px(new QSortFilterProxyModel(this)) {
  setObjectName(tr("SysEventView"));
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
