#include "lctooltable.h"
#include <tooltable.h>
#include <configacc.h>
#include <guicore.h>
#include <QWidget>
#include <QVBoxLayout>
#include <QVariant>
#include <QTableView>
#include <QScrollArea>
#include <QHeaderView>
#include <QSortFilterProxyModel>
#include <QKeyEvent>
#include <QDebug>


LCToolTable::LCToolTable(QWidget* parent)
 : AbstractCenterWidget(parent)
 , table(nullptr)
 , model(nullptr)
 , px(nullptr) {
  setObjectName("LCToolTable");
  setWindowTitle(tr("LCToolTable"));
  }


QWidget* LCToolTable::createContent() {
  table = new QTableView();
  model = core->toolTableModel();
  px    = new QSortFilterProxyModel(this);
  px->setSourceModel(model);
  table->setModel(px);
  table->setSelectionMode(QAbstractItemView::SingleSelection);
  table->setTabKeyNavigation(false);
  table->setSortingEnabled(true);
  table->horizontalHeader()->setStretchLastSection(true);
  table->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);
  table->setAlternatingRowColors(true);
  cfg->beginGroup("LCToolTable");
  table->horizontalHeader()->restoreState(cfg->value(core->isLatheMode() ? "latheState": "millState").toByteArray());
  cfg->endGroup();
  int mx = table->model()->rowCount();

  for (int i=0; i < mx; ++i) table->setRowHeight(i, 60);

  return table;
  }


LCToolTable::~LCToolTable() {
  }


void LCToolTable::connectSignals() {
  connect(core->toolTableModel(), &QAbstractTableModel::dataChanged, this, &LCToolTable::modelChanged);
  }


void LCToolTable::modelChanged() {
  model->setDirty();
  core->showAllButCenter(false);
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
         AbstractCenterWidget::keyReleaseEvent(e);
         break;
    }
  }

void LCToolTable::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
      case Qt::Key_F10:
         qDebug() << "LCToolTable::keyPressEvent (F10)";

         if (model->save()) {
            model->setDirty(false);
            core->showAllButCenter(true);
            emit dataChanged(this, false);
            }
         e->accept();
         break;
    case Qt::Key_S:
         if (e->modifiers() == Qt::CTRL) {
            qDebug() << "LCToolTable::keyPressEvent (CTRL+S)";

            if (model->save()) {
               model->setDirty(false);
               core->showAllButCenter(true);
               emit dataChanged(this, false);
               }
            e->accept();
            break;
            }
         [[fallthrough]];
    default:
         AbstractCenterWidget::keyPressEvent(e);
         break;
    }
  }


void LCToolTable::closeEvent(QCloseEvent*) {
  cfg->beginGroup("LCToolTable");
  cfg->setValue(core->isLatheMode() ? "latheState" : "millState", table->horizontalHeader()->saveState());
  cfg->endGroup();
  }
