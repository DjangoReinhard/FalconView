#include <filesystem>
#include <dirmodel.h>
#include <direntry.h>
#include <QDir>
#include <QDebug>


DirModel::DirModel(const QString& baseDir, QObject *parent)
 : QAbstractItemModel(parent)
 , rootItem(new DirEntry(tr("Root"), baseDir)) {
  DirEntry* pD = new DirEntry(tr("BaseDir"), baseDir);

  rootItem->appendChild(pD);
  setupModelData(baseDir, pD);
  }


DirModel::~DirModel() {
  delete rootItem;
  }


int DirModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid())
     return static_cast<DirEntry*>(parent.internalPointer())->columnCount();
  return rootItem->columnCount();
  }


QVariant DirModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid()) return QVariant();
  if (role != Qt::DisplayRole) return QVariant();
  DirEntry* item = static_cast<DirEntry*>(index.internalPointer());

  return item->data(index.column());
  }


bool DirModel::setData(const QModelIndex &index, const QVariant &value, int role) {
  if (!index.isValid()) return false;
  if (!(role == Qt::EditRole || role == Qt::DisplayRole)) return false;
  DirEntry* item = getItem(index);

  if (!item) return false;
  QFileInfo fi(item->path());
  QDir      oldDir(item->path());
  QVariant  oldName = item->data(0);
  QString   newPath(fi.dir().absolutePath() + "/" + value.toString());

  if (oldDir.rename(item->path(), newPath)) {
     item->setData(0, value);
     item->setData(9, newPath);
     emit dataChanged(index
                    , index
                    , { Qt::DisplayRole, Qt::EditRole });
     return true;
     }
  return false;
  }


Qt::ItemFlags DirModel::flags(const QModelIndex& index) const {
  if (!index.isValid()) return Qt::NoItemFlags;
  return QAbstractItemModel::flags(index);
  }


QVariant DirModel::headerData(int section, Qt::Orientation orientation, int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
     return rootItem->data(section);
  return QVariant();
  }


DirEntry* DirModel::getItem(const QModelIndex &index) const {
  if (index.isValid()) {
     DirEntry* item = static_cast<DirEntry*>(index.internalPointer());

     if (item) return item;
     }
  return rootItem->child(0);
  }


bool DirModel::insertDirectory(const QModelIndex &parentIdx, DirEntry *entry) {
  if (!parentIdx.isValid()) return false;
  if (!entry) return false;
  DirEntry* parent = getItem(parentIdx);
  QDir      newDir(entry->path());

  if (parent == entry->parent() && newDir.mkpath(newDir.path())) {
     beginInsertRows(parentIdx, parent->childCount(), parent->childCount());
     parent->appendChild(entry);
     endInsertRows();

     return true;
     }
  return false;
  }


QModelIndex DirModel::index(int row, int column, const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent)) return QModelIndex();
  DirEntry* parentItem;

  if (!parent.isValid()) parentItem = rootItem;
  else                   parentItem = static_cast<DirEntry*>(parent.internalPointer());
  DirEntry* childItem  = parentItem->child(row);

  if (childItem) return createIndex(row, column, childItem);
  return QModelIndex();
  }


QModelIndex DirModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) return QModelIndex();
  DirEntry* childItem  = getItem(index);
  DirEntry* parentItem = childItem ? childItem->parent() : nullptr;

  if (parentItem == rootItem || !parentItem)
     return QModelIndex();
  return createIndex(parentItem->childNumber(), 0, parentItem);
  }


DirEntry* DirModel::root() const {
  return rootItem->child(0);
  }


int DirModel::rowCount(const QModelIndex &parent) const {
  DirEntry* parentItem;

  if (parent.column() > 0) return 0;
  if (!parent.isValid()) parentItem = rootItem;
  else                   parentItem = static_cast<DirEntry*>(parent.internalPointer());
  return parentItem->childCount();
  }


void DirModel::setupModelData(const QString &baseDir, DirEntry *parent) {
  int len = baseDir.length() + 1;
  QMap<QString, DirEntry*> parents;

  for (auto& dirEntry : std::filesystem::recursive_directory_iterator{baseDir.toStdString().c_str()}) {
      if (!dirEntry.is_directory()) continue;
      QString path        = QString(dirEntry.path().string().c_str()).mid(len);
      QStringList parts   = path.split("/");
      QString     curPath = baseDir;
      DirEntry*   last    = parent;

      qDebug() << "entry: " << path;
      for (const QString& s : parts) {
          if (!parents.contains(s)) {
             qDebug() << "add new parent: " << s;
             parents[s] = new DirEntry(s, baseDir + "/" + path, last);
             last->appendChild(parents[s]);
             last = parents[s];
             }
          else last = parents[s];
          }
      }
  }
