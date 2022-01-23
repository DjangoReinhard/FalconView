#include "halview.h"
#include <applicationmode.h>
#include <configacc.h>
#include <guicore.h>
#include <QTreeView>
#include <QHeaderView>
#include <QKeyEvent>
#include <QDebug>
#include "halmodel.h"


HalView::HalView(QWidget* parent)
 : AbstractCenterWidget(":HalView.ui", parent) {
  setObjectName("HalView");
  setWindowTitle(tr("HalView"));
  }


HalView::~HalView() {
  delete tree;
  delete model;
  }


void HalView::closeEvent(QCloseEvent*) {
  cfg->beginGroup("HalView");
  cfg->setValue("tree", tree->header()->saveState());
  cfg->setValue("geometry", saveGeometry());
  cfg->endGroup();
  }


QWidget* HalView::createContent() {
//  QWidget* rv = AbstractCenterWidget::createContent();
  tree  = new QTreeView();
  model = new HalModel();
  tree->setAlternatingRowColors(true);
  tree->setModel(model);

  cfg->beginGroup("HalView");
  tree->header()->restoreState(cfg->value("tree").toByteArray());
  restoreGeometry(cfg->value("geometry").toByteArray());
  cfg->endGroup();

  return tree;
  }


void HalView::connectSignals() {
//  connect(history->selectionModel(), &QItemSelectionModel::currentChanged, this, &HalView::currentChanged);
  }


//void HalView::currentChanged(const QModelIndex& current, const QModelIndex&) {
////  qDebug() << "currentChanged" << current;
//  cmd->setText(history->item(current.row())->text());
//  }


//bool HalView::eventFilter(QObject*, QEvent* event) {
//  if (event->type() == QEvent::KeyPress) {
//     QKeyEvent* e = static_cast<QKeyEvent*>(event);

//     switch (e->key()) {
//       case Qt::Key_Up:
//            history->setCurrentRow(history->currentRow() > 0
//                                 ? history->currentRow() - 1 : 0);
//            return true;
//       case Qt::Key_Down:
//            history->setCurrentRow(history->currentRow() < (history->count() - 1)
//                                 ? history->currentRow() + 1 : history->count() - 1);
//            return true;
//       case Qt::Key_Tab:
//       case Qt::Key_Backtab:
//            return true;
//       }
//     }
//  return false;
//  }


void HalView::showEvent(QShowEvent* e) {
  if (e->type() == QEvent::Show) {
     tree->setFocus();
     }
  AbstractCenterWidget::showEvent(e);
  }


void HalView::updateStyles() {
  }
