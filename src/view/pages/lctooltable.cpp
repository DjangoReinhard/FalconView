#include <lctooltable.h>
#include <tooltable.h>
#include <configacc.h>
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
 : DynCenterWidget(QString(), "LCToolTable", false, parent)
 , table(new QTableView)
 , model(Core().toolTableModel())
 , px(new QSortFilterProxyModel(this)) {
  setObjectName(LCToolTable::className);
  setWindowTitle(LCToolTable::className);
  }


QWidget* LCToolTable::createContent() {
  px->setSourceModel(model);
  table->setModel(px);
  table->setSelectionMode(QAbstractItemView::SingleSelection);
  table->setTabKeyNavigation(false);
  table->setSortingEnabled(true);
  table->horizontalHeader()->setStretchLastSection(true);
  table->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);
  table->setAlternatingRowColors(true);
  Config cfg;

  cfg.beginGroup(LCToolTable::className);
  table->horizontalHeader()->restoreState(cfg.value("state").toByteArray());
  cfg.endGroup();

  return table;
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
  DynCenterWidget::keyReleaseEvent(e);
  }


void LCToolTable::closeEvent(QCloseEvent*) {
  Config cfg;

  cfg.beginGroup(LCToolTable::className);
  cfg.setValue("state", table->horizontalHeader()->saveState());
  cfg.endGroup();
  }


const QString LCToolTable::className = "LCToolTable";
