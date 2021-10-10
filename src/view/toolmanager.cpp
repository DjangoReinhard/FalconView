#include <toolmanager.h>
#include <toolcategorymodel.h>
#include <toolcategory.h>
#include <toolmodel.h>
#include <filemodel.h>
#include <KeyCodes.h>
#include <QTreeView>
#include <QTableView>
#include <QSplitter>
#include <QFileSystemModel>
#include <QSortFilterProxyModel>
#include <QItemSelection>
#include <QPlainTextEdit>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QShortcut>
#include <QKeyEvent>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>


ToolManager::ToolManager(QWidget *parent)
 : QWidget(parent)
 , spH(new QSplitter(Qt::Horizontal, this))
 , spV(new QSplitter(Qt::Vertical, this))
 , categories(new QTreeView(spV))
 , tools(new QTableView(spH))
 , preView(new QPlainTextEdit(spH))
 , categoryModel(new ToolCategoryModel())
 , toolModel(new ToolModel())
 , pxCat(new QSortFilterProxyModel(this))
 , pxTools(new QSortFilterProxyModel(this)) {
  setObjectName("ToolManager");
  pxCat->setSourceModel(categoryModel);
  categories->setModel(pxCat);
  categories->setTabKeyNavigation(false);
  categories->setSortingEnabled(true);
  categories->header()->setSortIndicator(0, Qt::AscendingOrder);

  pxTools->setSourceModel(toolModel);
  tools->setModel(pxTools);
  tools->setSelectionBehavior(QAbstractItemView::SelectRows);
  tools->horizontalHeader()->setStretchLastSection(true);
  tools->verticalHeader()->hide();
  tools->setEditTriggers(QAbstractItemView::NoEditTriggers);
  tools->setSelectionMode(QAbstractItemView::SingleSelection);
  tools->setTabKeyNavigation(false);
  tools->setSortingEnabled(true);
  tools->setColumnHidden(0, true);
  tools->setColumnHidden(4, true);
  tools->horizontalHeader()->setSortIndicator(3, Qt::AscendingOrder);

  preView->setFocusPolicy(Qt::FocusPolicy::NoFocus);
  preView->setReadOnly(true);

  this->setLayout(new QVBoxLayout(this));
  spH->addWidget(categories);
  spH->addWidget(spV);
  spV->addWidget(tools);
  spV->addWidget(preView);
  layout()->addWidget(spH);

  connect(categories->selectionModel(), &QItemSelectionModel::currentChanged
        , this, &ToolManager::currentChanged);
  connect(tools->selectionModel(), &QItemSelectionModel::selectionChanged
        , this, &ToolManager::selectionChanged);
  }


void ToolManager::toggleView() {
  qDebug() << "Hi, toggleView triggered ...";
  if (categories->hasFocus()) {
     tools->setFocus();
     }
  else {
     categories->setFocus();
     }
  }


void ToolManager::currentChanged(const QModelIndex& index) {
  qDebug() << "currentChanged - " << index;
  const QModelIndex& srcIndex = pxCat->mapToSource(index);
  ToolCategory* item = static_cast<ToolCategory*>(srcIndex.internalPointer());

  if (item) {
     qDebug() << "selected tool category: #" << item->data(9) << " " << item->data(0);
     toolModel->setFilter("type = " + item->data(9).toString());
//     tools->resizeColumnToContents(3);
     tools->resizeColumnsToContents();
//     tools->selectRow(0);
     }
  }


void ToolManager::keyReleaseEvent(QKeyEvent *event) {
  qDebug() << "released key: " << event->key();
  qDebug() << "\tmodifiers: "  << event->modifiers();

  switch (event->key()) {
    case KeyCodes::Enter:
         qDebug() << "hit ENTER?";
         break;
    case KeyCodes::F10_Key:
         qDebug() << "blub";
         if (categories->isVisible()) {
            categories->hide();
            tools->hide();
            }
         else {
            categories->show();
            tools->show();
            }
         break;
    }
  event->setAccepted(true);
  }


void ToolManager::selectionChanged(const QItemSelection& selected, const QItemSelection&) {
  QModelIndexList    mi       = selected.indexes();
  const QModelIndex& index    = mi.at(0);
  const QModelIndex& srcIndex = pxTools->mapToSource(index);

  qDebug() << "selected: " << selected;
  qDebug() << "     row: " << srcIndex.row();

  QSqlRecord rec = toolModel->record(srcIndex.row());

  qDebug() << "tool #" << rec.value("num") << " " << rec.value("name");
  }
