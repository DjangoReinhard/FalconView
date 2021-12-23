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
#include <QDebug>
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
  table->horizontalHeader()->restoreState(cfg.value(Core().isLatheMode() ? "latheState": "millState").toByteArray());
  cfg.endGroup();
  int mx = table->model()->rowCount();

  for (int i=0; i < mx; ++i) table->setRowHeight(i, 60);

  return table;
  }


LCToolTable::~LCToolTable() {
  }


void LCToolTable::connectSignals() {
  connect(Core().toolTableModel(), &QAbstractTableModel::dataChanged, this, &LCToolTable::modelChanged);
  }


void LCToolTable::modelChanged() {
  model->setDirty();
  Core().showAllButCenter(false);
  emit dataChanged(this, true);
  }


void LCToolTable::updateStyles() {
  }


void LCToolTable::keyReleaseEvent(QKeyEvent *e) {
  switch (e->key()) {
    // just cut our keys out of default processing
    case Qt::Key_F10: break;
    case Qt::Key_S:
         if (e->modifiers() == Qt::CTRL) break;
         [[fallthrough]];
    default:
         DynCenterWidget::keyReleaseEvent(e);
         break;
    }
  }

void LCToolTable::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
      case Qt::Key_F10:
         qDebug() << "LCToolTable::keyPressEvent (F10)";

         if (model->save()) {
            model->setDirty(false);
            Core().showAllButCenter(true);
            emit dataChanged(this, false);
            }
         e->accept();
         break;
    case Qt::Key_S:
         if (e->modifiers() == Qt::CTRL) {
            qDebug() << "LCToolTable::keyPressEvent (CTRL+S)";

            if (model->save()) {
               model->setDirty(false);
               Core().showAllButCenter(true);
               emit dataChanged(this, false);
               }
            e->accept();
            break;
            }
         [[fallthrough]];
    default:
         DynCenterWidget::keyPressEvent(e);
         break;
    }
  }


void LCToolTable::closeEvent(QCloseEvent*) {
  Config cfg;

  cfg.beginGroup(LCToolTable::className);
  cfg.setValue(Core().isLatheMode() ? "latheState" : "millState", table->horizontalHeader()->saveState());
  cfg.endGroup();
  }


const QString LCToolTable::className = "LCToolTable";
