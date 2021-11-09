#include <lctooltable.h>
#include <tooltable.h>
#include <QWidget>
#include <QVBoxLayout>
#include <QVariant>
#include <QTableView>
#include <QScrollArea>
#include <QHeaderView>
#include <QSortFilterProxyModel>
#include <QKeyEvent>
#include <core.h>


LCToolTable::LCToolTable(QWidget* parent)
 : DynWidget(QString(), false, parent)
 , table(new QTableView)
 , model(Core().toolTableModel())
 , px(new QSortFilterProxyModel(this)) {
  setObjectName(tr("LC-Tools"));
  setLayout(new QVBoxLayout(this));
  px->setSourceModel(model);
  table->setModel(px);
  table->setSelectionMode(QAbstractItemView::SingleSelection);
  table->setTabKeyNavigation(false);
  table->setSortingEnabled(true);
  table->horizontalHeader()->setStretchLastSection(true);
  table->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);
  table->setAlternatingRowColors(true);
  layout()->addWidget(table);
  }


LCToolTable::~LCToolTable() {
  }


void LCToolTable::connectSignals() {
  }


void LCToolTable::updateStyles() {
  }


void LCToolTable::keyReleaseEvent(QKeyEvent *e) {
  switch (e->key()) {
    case Qt::Key_F10:
         //TODO: save tooltable changes ...
         model->save();
         e->accept();
         break;
    default: break;
    }
  DynWidget::keyReleaseEvent(e);
  }

