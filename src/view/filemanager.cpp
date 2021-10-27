#include <filemanager.h>
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
#include <QDebug>


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
 , pxFiles(new QSortFilterProxyModel(this)) {
  setObjectName("FileManager");
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
  }



void FileManager::connectSignals() {
  connect(dirs->selectionModel(), &QItemSelectionModel::currentChanged
        , this, &FileManager::currentChanged);
  connect(files->selectionModel(), &QItemSelectionModel::selectionChanged
        , this, &FileManager::selectionChanged);
  }


void FileManager::updateStyles() {
  }


void FileManager::toggleView() {
//  qDebug() << "Hi, toggleView triggered ...";
  if (dirs->hasFocus()) files->setFocus();
  else                  dirs->setFocus();
  }


void FileManager::currentChanged(const QModelIndex& index) {
  qDebug() << "currentChanged - " << index;
  const QModelIndex& srcIndex = pxDirs->mapToSource(index);
  DirEntry* item = static_cast<DirEntry*>(srcIndex.internalPointer());

  if (item) {
     qDebug() << "path for detail-view: " << item->path();
     fileModel->setupModel(item->path());
     files->resizeColumnsToContents();
//     for (int i=1; i < fileModel->columnCount(QModelIndex()); ++i)
//         files->resizeColumnToContents(i);
     }
  }


void FileManager::keyReleaseEvent(QKeyEvent *event) {
  qDebug() << "released key: " << event->key();

  if (event->key() == KeyCodes::Enter) {
     qDebug() << "hit ENTER?";
     QModelIndexList    mi       = files->selectionModel()->selection().indexes();

     if (!mi.size()) {
        event->accept();

        return;
        }
     const QModelIndex& index    = mi.at(0);
     const QModelIndex& srcIndex = pxFiles->mapToSource(index);
     const QFileInfo&   fi       = fileModel->fileInfo(srcIndex.row());
     const QString      path     = fi.absoluteFilePath();
     QFile file(path);

     qDebug() << "selected file: " << file.fileName();

     //TODO: change view-stack to caller page!
     emit fileSelected(file.fileName());
     }
  event->accept();
  }


void FileManager::selectionChanged(const QItemSelection& selected, const QItemSelection&) {
  qDebug() << "selected: "     << selected;
  QModelIndexList    mi       = selected.indexes();

  if (!mi.size()) return;
  const QModelIndex& index    = mi.at(0);
  const QModelIndex& srcIndex = pxFiles->mapToSource(index);
  const QFileInfo&   fi       = fileModel->fileInfo(srcIndex.row());
  const QString      path     = fi.absoluteFilePath();
  QFile file(path);

  qDebug() << "preview path: " << path;
  if (file.open(QFile::ReadOnly | QFile::Text)) {
     preView->setPlainText(file.read(1024));
     file.close();
     }
  else {
     preView->setPlainText(tr("<p>no textfile</p>"));
     }
  }
