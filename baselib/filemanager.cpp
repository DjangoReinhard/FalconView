#include <filemanager.h>
#include <filemanagerclient.h>
#include <core.h>
#include <configacc.h>
#include <dirmodel.h>
#include <direntry.h>
#include <filemodel.h>

#include <QTreeView>
#include <QTableView>
#include <QSplitter>
#include <QFileSystemModel>
#include <QInputDialog>
#include <QSortFilterProxyModel>
#include <QMessageBox>
#include <QItemSelection>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QShortcut>
#include <QKeyEvent>
#include <QDebug>


FileManager::FileManager(const QDir& baseDir, QWidget *parent)
 : AbstractCenterWidget(QString(), "FileManager", false, parent)
 , spH(new QSplitter(Qt::Horizontal, this))
 , spV(new QSplitter(Qt::Vertical, this))
 , dirs(new QTreeView(spV))
 , files(new QTableView(spH))
 , preView(new QPlainTextEdit(spH))
 , dirModel(new DirModel(baseDir.absolutePath()))
 , fileModel(new FileModel())
 , pxDirs(new QSortFilterProxyModel(this))
 , pxFiles(new QSortFilterProxyModel(this))
 , client(nullptr)
 , file2Copy(nullptr)
 , file2Move(nullptr) {
  setObjectName(FileManager::className);
  setWindowTitle(FileManager::className);
  pxDirs->setSourceModel(dirModel);
  dirs->setModel(pxDirs);
  dirs->setTabKeyNavigation(false);
  dirs->setSortingEnabled(true);
  dirs->header()->setSortIndicator(0, Qt::AscendingOrder);

  pxFiles->setSourceModel(fileModel);
  files->setModel(pxFiles);
  files->setSelectionBehavior(QAbstractItemView::SelectRows);
  files->verticalHeader()->hide();
  files->setEditTriggers(QAbstractItemView::NoEditTriggers);
  files->setSelectionMode(QAbstractItemView::SingleSelection);
  files->setAlternatingRowColors(true);
  files->setTabKeyNavigation(false);
  files->setSortingEnabled(true);
  files->horizontalHeader()->setStretchLastSection(true);
  files->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);

  preView->setFocusPolicy(Qt::FocusPolicy::NoFocus);
  preView->setReadOnly(true);
  preView->setWordWrapMode(QTextOption::NoWrap);

  dirs->installEventFilter(this);
  files->installEventFilter(this);
  preView->installEventFilter(this);
  }


QWidget* FileManager::createContent() {
  spH->addWidget(dirs);
  spH->addWidget(spV);
  spV->addWidget(files);
  spV->addWidget(preView);
  Config cfg;

  cfg.beginGroup(FileManager::className);
  spH->restoreState(cfg.value("hState").toByteArray());
  spV->restoreState(cfg.value("vState").toByteArray());
  cfg.endGroup();
  dirs->expandAll();

  return spH;
  }


void FileManager::connectSignals() {
  connect(dirs->selectionModel(), &QItemSelectionModel::currentChanged
        , this, &FileManager::currentChanged);
  connect(files->selectionModel(), &QItemSelectionModel::selectionChanged
        , this, &FileManager::selectionChanged);
  }


void FileManager::createDirectory() {
  bool ok;
  QString text = QInputDialog::getText(this
                                     , tr("QInputDialog::getText()")
                                     , tr("name of Directory: ")
                                     , QLineEdit::Normal
                                     , QDir::home().dirName()
                                     , &ok);
  if (ok && !text.isEmpty()) {
     qDebug() << "new directory name: >" << text << "<";
     QItemSelection  is     = dirs->selectionModel()->selection();
     QModelIndexList ml     = is.indexes();
     QModelIndex     cur    = ml.size() ? ml.at(0) : QModelIndex();
     QModelIndex     srcIdx = pxDirs->mapToSource(cur);
     DirEntry*       parent = dirModel->getItem(srcIdx);
     QDir            newDir((parent ? parent->path() : dirModel->root()->path()) + "/" + text);

     dirModel->insertDirectory(srcIdx, new DirEntry(text, newDir.path(), parent));
     }
  }


void FileManager::renameDirectory() {
  bool ok;
  QString text = QInputDialog::getText(this
                                     , tr("QInputDialog::getText()")
                                     , tr("name of Directory: ")
                                     , QLineEdit::Normal
                                     , QDir::home().dirName()
                                     , &ok);
  if (ok && !text.isEmpty()) {
     qDebug() << "new directory name: >" << text << "<";
     QItemSelection  is     = dirs->selectionModel()->selection();
     QModelIndexList ml     = is.indexes();
     QModelIndex     cur    = ml.size() ? ml.at(0) : QModelIndex();
     QModelIndex     srcIdx = pxDirs->mapToSource(cur);

     dirModel->setData(srcIdx, text, Qt::DisplayRole);
     }
  }


void FileManager::updateStyles() {
  }


void FileManager::showEvent(QShowEvent* e) {
  AbstractCenterWidget::showEvent(e);
  if (e->type() == QEvent::Show) {
     dirs->setFocus();
//     QMessageBox::information(this
//                            , tr("QMessageBox::information()")
//                            , tr("<p>File-Manager helps you to select and organize your "
//                                 "gcode files.</p><p>TAB-key toggles between directory tree "
//                                 "and file list. Cursor up/down shows active file in preview. "
//                                 "ENTER loads the selected file into editor.</p><p>"
//                                 "Insert can be used to create files or directories.</p><p>"
//                                 "F5 can be used to select a file for copy transaction. After "
//                                 "hitting F5 you can use Cursor keys to select the target "
//                                 "directory. When the desired directory is selected, press "
//                                 "Enter.</p><p>Same procedure using F6 for move file.</p><p>"
//                                 "ENTER loads a file into editor, whereas ESC closes the "
//                                 "filemanager without any action.</p>"));
//     if (ValueManager().getValue("showHelpOnNewPage").toBool()) Core().mainWindow()->showHelp();
     }
  }


void FileManager::setClient(FileManagerClient* c) {
  client = c;
  }


void FileManager::currentChanged(const QModelIndex& index) {
//  qDebug() << "currentChanged - " << index;
  const QModelIndex& srcIndex = pxDirs->mapToSource(index);
  DirEntry* item = static_cast<DirEntry*>(srcIndex.internalPointer());

  if (item) {
//     qDebug() << "path for detail-view: " << item->path();
     fileModel->setupModel(item->path());
     files->resizeColumnsToContents();
     }
  }


bool FileManager::eventFilter(QObject* src, QEvent* event) {
  if (event->type() == QEvent::KeyPress) {
     QKeyEvent* e = static_cast<QKeyEvent*>(event);

     switch (e->key()) {
       case Qt::Key_Enter:
       case Qt::Key_Return:
            if (src == files) {
               QModelIndexList    mi       = files->selectionModel()->selection().indexes();

               if (!mi.size()) return false;
               const QModelIndex& index    = mi.at(0);
               const QModelIndex& srcIndex = pxFiles->mapToSource(index);
               const QFileInfo&   fi       = fileModel->fileInfo(srcIndex.row());
               const QString      path     = fi.absoluteFilePath();
               QFile file(path);

               if (client) {
                  client->fileSelected(file.fileName());
                  client = nullptr;

                  return true;
                  }
               }
            else if (src == dirs) {
               // finish copy or move
               if (file2Copy || file2Move) {
                  QItemSelection  is     = dirs->selectionModel()->selection();
                  QModelIndexList ml     = is.indexes();
                  QModelIndex     cur    = ml.size() ? ml.at(0) : QModelIndex();
                  QModelIndex     srcIdx = pxDirs->mapToSource(cur);
                  DirEntry*       item   = static_cast<DirEntry*>(srcIdx.internalPointer());

                  qDebug() << "target for copy/move is" << item->path();

                  if (file2Copy) {
                     qDebug() << "finish copy action of" << file2Copy->fileName() << "(" << file2Copy->absoluteFilePath() << ")";
                     QFile::copy(file2Copy->absoluteFilePath(), item->path() + "/" + file2Copy->fileName());
                     currentChanged(cur);
                     delete file2Copy;
                     file2Copy = nullptr;

                     return true;
                     }
                  else {
                     qDebug() << "finish move action of" << file2Move->fileName() << "(" << file2Move->absoluteFilePath() << ")";
                     if (QFile::copy(file2Move->absoluteFilePath(), item->path() + "/" + file2Move->fileName()))
                        QFile::remove(file2Move->absoluteFilePath());
                     currentChanged(cur);
                     delete file2Move;
                     file2Move = nullptr;

                     return true;
                     }
                  }
               } break;
       case Qt::Key_Insert:
            if (src == dirs) {
               createDirectory();

               return true;
               }
            else if (src == files) {
               //TODO: create new file and open gcode editor
               qDebug() << "TODO: TableView ?!? => should create file!";

               return true;
               } break;
       case Qt::Key_Delete:
            if (src == dirs) {
               //TODO: remove directory - but only empty ones!
               qDebug() << "TODO: remove directory? (TreeView)";

               return true;
               }
            else if (src == files) {
               //TODO: remove file ...
               qDebug() << "TODO: remove file? (TableView)";

               return true;
               } break;
       case Qt::Key_F5:
            if (src == files) {   // start copy file
               QModelIndexList  mil    = files->selectionModel()->selectedRows();
               QModelIndex      cur    = mil.size() ? mil.at(0) : QModelIndex();
               QModelIndex      srcIdx = pxFiles->mapToSource(cur);
               const QFileInfo& fi     = fileModel->fileInfo(srcIdx.row());

               if (file2Copy) {
                  QMessageBox::StandardButton reply = QMessageBox::critical(this
                                                                          , tr("QMessageBox::critical()")
                                                                          , QString(tr("There is already file %1 "
                                                                                       "marked for copy. Do you "
                                                                                       "want to abort that copy "
                                                                                       "operation and start a new copy?"))
                                                                                   .arg(file2Copy->absoluteFilePath())
                                                                          , QMessageBox::Yes | QMessageBox::No);

                  if (reply == QMessageBox::Yes) {
                     delete file2Copy;
                     file2Copy = new QFileInfo(fi.absoluteFilePath());

                     QMessageBox::information(this
                                            , tr("QMessageBox::information()")
                                            , QString(tr("file %1 has been marked for copy. "
                                                         "To finish copy operation goto "
                                                         "desired destination directory "
                                                         "and press [Enter].")).arg(file2Copy->absoluteFilePath()));
                     }
                  }
               else {
                  file2Copy = new QFileInfo(fi.absoluteFilePath());

                  QMessageBox::information(this
                                         , tr("QMessageBox::information()")
                                         , QString(tr("file %1 has been marked for copy. To "
                                                      "finish copy operation goto desired "
                                                      "destination directory and press [Enter]."))
                                                  .arg(file2Copy->absoluteFilePath()));
                  }
               dirs->setFocus();

               return true;
               } break;
       case Qt::Key_F6: {
            if (src == files) {   // start move file
               QModelIndexList  mil    = files->selectionModel()->selectedRows();
               QModelIndex      cur    = mil.size() ? mil.at(0) : QModelIndex();
               QModelIndex      srcIdx = pxFiles->mapToSource(cur);
               const QFileInfo& fi     = fileModel->fileInfo(srcIdx.row());

               if (file2Move) {
                  QMessageBox::StandardButton reply = QMessageBox::critical(this
                                                                          , tr("QMessageBox::critical()")
                                                                          , QString(tr("There is already file %1 "
                                                                                       "marked for move. Do you "
                                                                                       "want to abort that move "
                                                                                       "operation and start a "
                                                                                       "new move?"))
                                                                                   .arg(file2Move->absoluteFilePath())
                                                                          , QMessageBox::Yes | QMessageBox::No);

                  if (reply == QMessageBox::Yes) {
                     delete file2Move;
                     file2Move = new QFileInfo(fi.absoluteFilePath());
                     QMessageBox::information(this
                                            , tr("QMessageBox::information()")
                                            , QString(tr("file %1 has been marked for move. To "
                                                         "finish move operation goto desired "
                                                         "destination directory and press [Enter]."))
                                                     .arg(file2Move->absoluteFilePath()));
                     }
                  }
               else {
                  file2Move = new QFileInfo(fi.absoluteFilePath());

                  QMessageBox::information(this
                                         , tr("QMessageBox::information()")
                                         , QString(tr("file %1 has been marked for move. To "
                                                      "finish move operation goto desired "
                                                      "destination directory and press Enter"))
                                                  .arg(file2Move->absoluteFilePath()));
                  }
               dirs->setFocus();
               return true;
               }
            else if (src == dirs) {
               renameDirectory();

               return true;
               }
            } break;
       default: break;
       }
     }
  return false;
  }


void FileManager::closeEvent(QCloseEvent*) {
  Config cfg;

  cfg.beginGroup(FileManager::className);
  cfg.setValue("hState", spH->saveState());
  cfg.setValue("vState", spV->saveState());
  cfg.endGroup();
  }


void FileManager::selectionChanged(const QItemSelection& selected, const QItemSelection&) {
//  qDebug() << "selected: "     << selected;
  QModelIndexList    mi       = selected.indexes();

  if (!mi.size()) return;
  const QModelIndex& index    = mi.at(0);
  const QModelIndex& srcIndex = pxFiles->mapToSource(index);
  const QFileInfo&   fi       = fileModel->fileInfo(srcIndex.row());
  const QString      path     = fi.absoluteFilePath();
  QFile file(path);

//  qDebug() << "preview path: " << path;
  if (file.open(QFile::ReadOnly | QFile::Text)) {
     preView->setPlainText(file.read(1024));
     file.close();
     }
  else {
     preView->setPlainText(tr("<p>no textfile</p>"));
     }
  }

const QString FileManager::className = "FileManager";
