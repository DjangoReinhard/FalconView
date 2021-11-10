#include <toolmanager.h>
#include <CategoryTreeModel.h>
#include <toolcategorymodel.h>
#include <tooleditor.h>
#include <toolmodel.h>
#include <KeyCodes.h>
#include <QAbstractButton>
#include <QTreeView>
#include <QTableView>
#include <QSplitter>
#include <QMessageBox>
#include <QFileSystemModel>
#include <QSortFilterProxyModel>
#include <QItemSelection>
#include <QDateTime>
#include <QScrollArea>
#include <QInputDialog>
#include <QPlainTextEdit>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QShortcut>
#include <QKeyEvent>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlField>
#include <QThread>
#include <QDebug>


ToolManager::ToolManager(DBConnection& conn, QWidget *parent)
 : DynWidget(parent)
 , conn(conn)
 , spH(new QSplitter(Qt::Horizontal, this))
 , spV(new QSplitter(Qt::Vertical, this))
 , categories(new QTreeView(spV))
 , tools(new QTableView(spH))
 , categoryTreeModel(new CategoryTreeModel(conn))
 , categoryTableModel(new ToolCategoryModel(conn))
 , toolModel(new ToolModel(conn))
 , tEdit(new ToolEditor(this))
 , tsMsgBox(timeStamp())
 , pxCat(new QSortFilterProxyModel(this))
 , pxTools(new QSortFilterProxyModel(this)) {
  setObjectName(tr("ToolManager"));
  pxCat->setSourceModel(categoryTreeModel);
  categories->setModel(pxCat);
  categories->setTabKeyNavigation(false);
  categories->setSortingEnabled(true);
  categories->header()->setSortIndicator(0, Qt::AscendingOrder);
  categories->hideColumn(1);
  categories->hideColumn(2);
  categories->setMaximumWidth(250);

  pxTools->setSourceModel(toolModel);
  tools->setModel(pxTools);
  tools->setSelectionBehavior(QAbstractItemView::SelectRows);
  tools->horizontalHeader()->setStretchLastSection(true);
  tools->verticalHeader()->hide();
  tools->setEditTriggers(QAbstractItemView::NoEditTriggers);
  tools->setSelectionMode(QAbstractItemView::SingleSelection);
  tools->setAlternatingRowColors(true);
  tools->setTabKeyNavigation(false);
  tools->setSortingEnabled(true);
  tools->setColumnHidden(0, true);
  tools->setColumnHidden(4, true);
  tools->horizontalHeader()->setSortIndicator(3, Qt::AscendingOrder);
  tools->setMinimumHeight(400);
  QScrollArea* sa = new QScrollArea;

  tEdit->setFocusPolicy(Qt::FocusPolicy::NoFocus);
  tEdit->setEnabled(false);  

  sa->setFocusPolicy(Qt::FocusPolicy::NoFocus);
  sa->setWidget(tEdit);

  this->setLayout(new QVBoxLayout(this));
  spH->addWidget(categories);
  spH->addWidget(spV);
  spV->addWidget(tools);
  spV->addWidget(sa);
  layout()->addWidget(spH);
  layout()->setContentsMargins(0, 0, 0, 0);
  }


void ToolManager::connectSignals() {
  connect(categories->selectionModel(), &QItemSelectionModel::currentChanged
        , this, &ToolManager::currentChanged);
  connect(tools->selectionModel(), &QItemSelectionModel::selectionChanged
        , this, &ToolManager::selectionChanged);
  }


void ToolManager::updateStyles() {
  }


void ToolManager::createCategory() {
  bool ok;
  QString text = QInputDialog::getText(this
                                     , tr("QInputDialog::getText()")
                                     , tr("Category name:")
                                     , QLineEdit::Normal
                                     , "what ever"
                                     , &ok);
  if (ok && !text.isEmpty()) {
     QItemSelection  is     = categories->selectionModel()->selection();
     QModelIndexList ml     = is.indexes();
     QModelIndex     cur    = ml.size() ? ml.at(0) : QModelIndex();
     QModelIndex     srcIdx = pxCat->mapToSource(cur);
     int             nextId = categoryTableModel->nextId();
     Category*       parent = static_cast<Category*>(srcIdx.internalPointer());

     if (!parent) parent = categoryTreeModel->root();
     int   parentId = parent->data(1).toInt();

     if (!categoryTreeModel->insertRow(0, srcIdx)) return;
     for (int column = 0; column < categoryTreeModel->columnCount(srcIdx); ++column) {
         const QModelIndex child = categoryTreeModel->index(0, column, srcIdx);

         switch (column) {
           case 0: categoryTreeModel->setData(child, text, Qt::EditRole); break;
           case 1: categoryTreeModel->setData(child, nextId, Qt::EditRole); break;
           case 2: categoryTreeModel->setData(child, parentId != nextId ? parentId : nextId, Qt::EditRole); break;
           }
         }
     Category* newCat = parent->child(0);

     categoryTableModel->insertRecord(-1, *newCat);
     categoryTableModel->submitAll();
     }
  }


void ToolManager::createTool() {
  bool ok;
  int toolNum  = toolModel->maxToolNum() + 1;

  while (true) {
        QString text = QInputDialog::getText(this
                                           , tr("QInputDialog::getText()")
                                           , tr("Tool number:")
                                           , QLineEdit::Normal
                                           , QString::number(toolNum)
                                           , &ok);
        if (ok && !text.isEmpty()) {
           //TODO: validate new tool number
           int newNum = text.toInt(&ok);

           if (!ok) {
              //invalid user input - ?!?
              qDebug() << "invalid tool-number:" << text;
              continue;
              }
           if (toolModel->existsToolNum(newNum)) {
              qDebug() << "toolnumber #" << newNum << "already exists in database!";
              continue;
              }
           QSqlRecord rec = toolModel->record();

           rec.setValue("num", newNum);
           tEdit->setModel(rec);
           editTool();
           break;
           }
        else break;
        }
  }


void ToolManager::currentChanged(const QModelIndex& index) {
  const QModelIndex& srcIndex = pxCat->mapToSource(index);
  int cid = categoryTreeModel->data(categoryTreeModel->index(srcIndex.row(), 1
                                                           , srcIndex.parent())
                                  , Qt::DisplayRole).toInt();

  if (cid > 0) toolModel->setFilter("type = " + QString::number(cid));
  else         toolModel->setFilter("type > 0");
  tools->resizeColumnsToContents();
  }


void ToolManager::deleteCategory() {
  QItemSelection  is     = categories->selectionModel()->selection();
  QModelIndexList ml     = is.indexes();
  QModelIndex     cur    = ml.size() ? ml.at(0) : QModelIndex();
  QModelIndex     srcIdx = pxCat->mapToSource(cur);
  Category*       cat    = static_cast<Category*>(srcIdx.internalPointer());

  if (!cat) return;      // don't delete root entry!
  int count = toolModel->tools4Category(cat->data(1).toInt());

  if (count || cat->childCount()) {
     QMessageBox::information(this
                            , tr("QMessageBox::information()")
                            , tr("This category has attached tools "
                                 "or sub-categories and cannot be removed."));
     }
  else {
     if (cat->remove())
        categoryTreeModel->removeRows(srcIdx.row(), 1, srcIdx.parent());
     }
  }


long ToolManager::timeStamp() {
  QFile sysTime("/proc/uptime");

  if (sysTime.open(QIODevice::ReadOnly | QIODevice::Text)) {
     QTextStream in(&sysTime);
     QStringList parts = in.readLine().split(" ");
     bool   ok = false;
     double ts = 0;

     sysTime.close();
     if (parts.size()) ts = parts[0].toDouble(&ok);
     if (ok) return ts * 1000;
     }
  return 0;
  }


void ToolManager::deleteTool() {
  qDebug() << "delete tool: " << toolModel->record(tool2Edit).value("num");
  QMessageBox::StandardButton reply;

  reply = QMessageBox::question(this
                              , tr("QMessageBox::question()")
                              , tr("Should this tool be deleted?")
                              , QMessageBox::Yes | QMessageBox::No);
  tsMsgBox = timeStamp();

  if (reply == QMessageBox::No) return;
  if (!toolModel->removeRows(tool2Edit, 1)) qDebug() << toolModel->lastError().text();
  if (!toolModel->submitAll())              qDebug() << toolModel->lastError().text();
  }


void ToolManager::editTool() {
  categories->hide();
  tools->hide();
  //TODO: hide all others!
  tEdit->setEnabled(true);

  qDebug() << "default size: " << edSize;
  qDebug() << "self size:" << size();
  qDebug() << "edit size:" << tEdit->size();

  if (edSize.width() == -1 && edSize.height() == -1) edSize = tEdit->size();
  tEdit->resize(size().width() - 20, size().height() - 20);

  // data record is already loaded into editor,
  // so just inform about how to finish editing
  QMessageBox::information(this
                         , tr("QMessageBox::information()")
                         , tr("To finish tool editing press F10 "
                              "to save changes or ESC to abort."));
  }


void ToolManager::renameCategory() {
  QItemSelection  is     = categories->selectionModel()->selection();
  QModelIndexList ml     = is.indexes();
  QModelIndex     cur    = ml.size() ? ml.at(0) : QModelIndex();
  QModelIndex     srcIdx = pxCat->mapToSource(cur);
  QString         oName  = categoryTreeModel->data(srcIdx, Qt::EditRole).toString();
  bool ok;

  QString text = QInputDialog::getText(this
                                     , tr("QInputDialog::getText()")
                                     , tr("new Category name:")
                                     , QLineEdit::Normal
                                     , oName
                                     , &ok);
  if (ok && !text.isEmpty()) {
     Category*      cat = static_cast<Category*>(srcIdx.internalPointer());

     if (cat->updateName(text))
        categoryTreeModel->setData(srcIdx, text, Qt::EditRole);
     }
  }


void ToolManager::saveToolChanges() {
  QSqlRecord tool = toolModel->record();

  tEdit->getChanges(tool);
  if (tool.value("id").isNull()) {     // may be new record to insert ...
     tool.setValue("id", toolModel->nextId());
     toolModel->insertRecord(-1, tool);
     }
  else toolModel->setRecord(tool2Edit, tool);
  if (!toolModel->submitAll()) qDebug() << "saving of tool-data failed!" << toolModel->lastError().text();
  tEdit->setEnabled(false);
  tEdit->resize(edSize);
  categories->show();
  tools->show();
  tools->setFocus();
  }


void ToolManager::keyReleaseEvent(QKeyEvent *event) {
//  qDebug() << "released key: " << event->key();
//  qDebug() << "\tmodifiers: "  << event->modifiers();

  switch (event->key()) {    
    case Qt::Key_Return:
    case Qt::Key_Enter: {
         qDebug() << "TM: enter (" << event->key() << ") has ts: " << event->timestamp();
         long now = timeStamp();

         qDebug() << "TM: time-delta" << (now - tsMsgBox);
         if (tools->hasFocus() && (now - tsMsgBox) > 400) {
            editTool();
            }
         } break;
    case Qt::Key_Escape:
         if (tEdit->isEnabled()) {  // abort editing
            //TODO: sync changes with start editing
            tEdit->setEnabled(false);
            categories->show();
            tools->show();
            tools->setFocus();
            }
         break;
    case Qt::Key_Space:
         if (categories->hasFocus()) {
            QItemSelection  is  = categories->selectionModel()->selection();
            QModelIndexList ml  = is.indexes();
            QModelIndex     cur = ml.size() ? ml.at(0) : QModelIndex();

            if (categories->isExpanded(cur)) categories->setExpanded(cur, false);
            else                             categories->setExpanded(cur, true);
            }
         break;
    case Qt::Key_Insert: {
         if (categories->hasFocus()) createCategory();
         else if (tools->hasFocus()) createTool();
         } break;
    case Qt::Key_Delete: {
         if (categories->hasFocus()) deleteCategory();
         else if (tools->hasFocus()) deleteTool();
         } break;
    case Qt::Key_F6: {
         if (categories->hasFocus()) renameCategory();
         } break;
    case Qt::Key_F10:
         if (tEdit->isEnabled()) saveToolChanges();
         break;
    }
  event->setAccepted(true);
  }


void ToolManager::showEvent(QShowEvent* e) {
  if (e->type() == QEvent::Show) categories->setFocus();
  }


void ToolManager::selectionChanged(const QItemSelection& selected, const QItemSelection&) {
  QModelIndexList    mi       = selected.indexes();
  const QModelIndex& index    = mi.at(0);
  const QModelIndex& srcIndex = pxTools->mapToSource(index);

  tool2Edit = srcIndex.row();
  tEdit->setModel(toolModel->record(tool2Edit));
  }
