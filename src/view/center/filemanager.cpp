#include <filemanager.h>
#include <filemanagerclient.h>
#include <testEdit.h>
#include <mainview.h>
#include <core.h>
#include <configacc.h>
#include <KeyCodes.h>
#include <dirmodel.h>
#include <direntry.h>
#include <filemodel.h>
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
//#include <QDebug>


FileManager::FileManager(const QDir& baseDir, QWidget *parent)
 : DynWidget(parent)
 , spH(new QSplitter(Qt::Horizontal, this))
 , spV(new QSplitter(Qt::Vertical, this))
 , dirs(new QTreeView(spV))
 , files(new QTableView(spH))
 , preView(new QPlainTextEdit(spH))
 , dirModel(new DirModel(baseDir.absolutePath()))
 , fileModel(new FileModel())
 , pxDirs(new QSortFilterProxyModel(this))
 , pxFiles(new QSortFilterProxyModel(this))
 , client(nullptr) {
  setObjectName(FileManager::className);
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

  this->setLayout(new QVBoxLayout(this));
  spH->addWidget(dirs);
  spH->addWidget(spV);
  spV->addWidget(files);
  spV->addWidget(preView);
  layout()->addWidget(spH);
  layout()->setContentsMargins(0, 0, 0, 0);
  Config cfg;

  cfg.beginGroup(FileManager::className);
  spH->restoreState(cfg.value("hState").toByteArray());
  spV->restoreState(cfg.value("vState").toByteArray());
  cfg.endGroup();
  }


void FileManager::connectSignals() {
  connect(dirs->selectionModel(), &QItemSelectionModel::currentChanged
        , this, &FileManager::currentChanged);
  connect(files->selectionModel(), &QItemSelectionModel::selectionChanged
        , this, &FileManager::selectionChanged);
  }


void FileManager::updateStyles() {
  }


void FileManager::showEvent(QShowEvent* e) {
  if (e->type() == QEvent::Show) dirs->setFocus();
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


void FileManager::keyReleaseEvent(QKeyEvent* e) {
//  qDebug() << "released key: " << event->key();

  if (e->key() == Qt::Key_Enter
   || e->key() == Qt::Key_Return) {
     QModelIndexList    mi       = files->selectionModel()->selection().indexes();

     e->accept();
     if (!mi.size()) return;
     const QModelIndex& index    = mi.at(0);
     const QModelIndex& srcIndex = pxFiles->mapToSource(index);
     const QFileInfo&   fi       = fileModel->fileInfo(srcIndex.row());
     const QString      path     = fi.absoluteFilePath();
     QFile file(path);

     if (client) {
        client->fileSelected(file.fileName());
        client = nullptr;
        }
     }
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
