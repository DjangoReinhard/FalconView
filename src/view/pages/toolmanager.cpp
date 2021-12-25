#include <toolmanager.h>
#include <CategoryTreeModel.h>
#include <toolcategorymodel.h>
#include <tooleditor.h>
#include <toolmodel.h>
#include <timestamp.h>
#include <core.h>
#include <configacc.h>
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
 : DynCenterWidget(QString(), "ToolManager", false, parent)
 , conn(conn)
 , spH(new QSplitter(Qt::Horizontal, this))
 , categories(new QTreeView(spH))
 , spV(new QSplitter(Qt::Vertical, spH))
 , tools(new QTableView(spV))
 , categoryTreeModel(new CategoryTreeModel(conn))
 , categoryTableModel(new ToolCategoryModel(conn))
 , toolModel(new ToolModel(conn))
 , tEdit(new ToolEditor())
 , tsMsgBox(TimeStamp::rtSequence())
 , pxCat(new QSortFilterProxyModel(this))
 , pxTools(new QSortFilterProxyModel(this)) {
  setObjectName(ToolManager::className);
  setWindowTitle(ToolManager::className);
  categories->installEventFilter(this);
  tools->installEventFilter(this);
  tEdit->installEventFilter(this);
  }


QWidget* ToolManager::createContent() {
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
  tools->setMinimumHeight(300);
  QScrollArea* sa = new QScrollArea();

  tEdit->setFocusPolicy(Qt::FocusPolicy::NoFocus);
  tEdit->setEnabled(false);  
  sa->setFocusPolicy(Qt::FocusPolicy::NoFocus);
  sa->setWidget(tEdit);
  spV->addWidget(tools);
  spV->addWidget(sa);
  Config cfg;

  cfg.beginGroup(ToolManager::className);
  spH->restoreState(cfg.value("hState").toByteArray());
  spV->restoreState(cfg.value("vState").toByteArray());
  int cc = tools->horizontalHeader()->count();
  QList<QVariant> cwl = cfg.value("cw").toList();

  if (cc > cwl.size()) cc = cwl.size();
  for (int i=0; i < cc; ++i) {
      tools->setColumnWidth(i, cwl.at(i).toInt());
      }
  cfg.endGroup();
  categories->expandAll();

  return spH;
  }


void ToolManager::connectSignals() {
  connect(categories->selectionModel(), &QItemSelectionModel::currentChanged
        , this, &ToolManager::currentChanged);
  connect(tools->selectionModel(), &QItemSelectionModel::selectionChanged
        , this, &ToolManager::selectionChanged);
  }


ToolManager::~ToolManager() {
  }


void ToolManager::updateStyles() {
  }


bool ToolManager::eventFilter(QObject* o, QEvent* event) {
  if (event->type() == QEvent::KeyPress) {
     QKeyEvent* e = static_cast<QKeyEvent*>(event);

     switch (e->key()) {
       case Qt::Key_Return:
       case Qt::Key_Enter:
            if (o == tools) {
               qDebug() << "TM: enter (" << e->key() << ") has ts: " << e->timestamp();
               long now = TimeStamp::rtSequence();

               qDebug() << "TM: time-delta" << (now - tsMsgBox);
               if ((now - tsMsgBox) > 400) {
                  editTool();
                  return true;
                  }
               }
            break;
       case Qt::Key_Escape:
            if (o == tEdit && tEdit->isEnabled()) {  // abort editing
               //TODO: sync changes with start editing
               tEdit->setEnabled(false);
               Core().showAllButCenter(true);
               categories->show();
               tools->show();
               tools->setFocus();
               return true;
               }
            break;
       case Qt::Key_Space:
            if (o == categories) {
               QItemSelection  is  = categories->selectionModel()->selection();
               QModelIndexList ml  = is.indexes();
               QModelIndex     cur = ml.size() ? ml.at(0) : QModelIndex();

               if (categories->isExpanded(cur)) categories->setExpanded(cur, false);
               else                             categories->setExpanded(cur, true);
               return true;
               }
            else if (o == tools) {
               qDebug() << "space at tableView hit ...";
               toolModel->toggleSelection(tool2Edit);
               return true;
               }
            break;
       case Qt::Key_Tab:
       case Qt::Key_Backtab:
            if (o == categories) {
               tools->setFocus();
               return true;
               }
            else if (o == tools) {
               categories->setFocus();
               return true;
               }
            break;
       case Qt::Key_Insert:
            if (o == categories) {
               createCategory();
               return true;
               }
            else if (o == tools) {
               createTool();
               return true;
               }
            break;
       case Qt::Key_Delete:
            if (o == categories) {
               deleteCategory();
               return true;
               }
            else if (o == tools) {
               deleteTool();
               return true;
               }
            break;
       case Qt::Key_F6:
            if (o == categories) {
               renameCategory();
               return true;
               }
            break;
       case Qt::Key_F9:
            if (o == categories || o == tools)
               toolModel->exportTools();
            return true;
       case Qt::Key_S:
            if (e->modifiers() != Qt::CTRL) break;
            [[fallthrough]];
       case Qt::Key_F10:
            if (o == tEdit && tEdit->isEnabled()) {
               saveToolChanges();
               return true;
               }
            break;
       }
     }
  return false;
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


void ToolManager::deleteTool() {
  qDebug() << "delete tool: " << toolModel->record(tool2Edit).value("num");
  QMessageBox::StandardButton reply;

  reply = QMessageBox::question(this
                              , tr("QMessageBox::question()")
                              , tr("Should this tool be deleted?")
                              , QMessageBox::Yes | QMessageBox::No);
  tsMsgBox = TimeStamp::rtSequence();

  if (reply == QMessageBox::No) return;
  if (!toolModel->removeRows(tool2Edit, 1))
     Core().riseError(toolModel->lastError().text());
  if (!toolModel->submitAll())
     Core().riseError(toolModel->lastError().text());
  }


void ToolManager::setSize(int w, int h) {
  if (tEdit->isEnabled()) tEdit->resize(w, h);
  else                    resize(w, h);
  }


void ToolManager::editTool() {
  categories->hide();
  tools->hide();
  Core().showAllButCenter(false);
  tEdit->setEnabled(true);

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
  if (!toolModel->submitAll()) {
     Core().riseError(tr("saving of tool-data failed!")
                      + toolModel->lastError().text());
     }
  tEdit->setEnabled(false);
  tEdit->resize(edSize);
  Core().showAllButCenter(true);
  categories->show();
  tools->show();  
  tools->setFocus();
  }


void ToolManager::closeEvent(QCloseEvent*) {
  Config cfg;

  cfg.beginGroup(ToolManager::className);
  cfg.setValue("hState", spH->saveState());
  cfg.setValue("vState", spV->saveState());
  int cc = tools->horizontalHeader()->count();
  QList<QVariant> cwl;

  for (int i=0; i < cc; ++i) {
      cwl.append(tools->columnWidth(i));
      }
  cfg.setValue("cw", cwl);
  cfg.endGroup();
  }


void ToolManager::showEvent(QShowEvent* e) {
  DynCenterWidget::showEvent(e);
  if (e->type() == QEvent::Show) categories->setFocus();
  }


void ToolManager::selectionChanged(const QItemSelection& selected, const QItemSelection&) {
  QModelIndexList    mi       = selected.indexes();
  const QModelIndex& index    = mi.at(0);
  const QModelIndex& srcIndex = pxTools->mapToSource(index);

  tool2Edit = srcIndex.row();
  tEdit->setModel(toolModel->record(tool2Edit));
  }


const QString& ToolManager::className = "ToolManager";
