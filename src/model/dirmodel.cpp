#include <filesystem>
#include <dirmodel.h>
#include <direntry.h>
#include <QDebug>


DirModel::DirModel(const QString& baseDir, QObject *parent)
 : QAbstractItemModel(parent) {
  rootItem = new DirEntry(tr("Name"), baseDir);
  setupModelData(baseDir, rootItem);
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


Qt::ItemFlags DirModel::flags(const QModelIndex& index) const {
  if (!index.isValid()) return Qt::NoItemFlags;
  return QAbstractItemModel::flags(index);
  }


QVariant DirModel::headerData(int section, Qt::Orientation orientation, int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
     return rootItem->data(section);
  return QVariant();
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
  DirEntry* child  = static_cast<DirEntry*>(index.internalPointer());
  DirEntry* parent = child->parent();
  if (parent == rootItem) return QModelIndex();

  return createIndex(parent->row(), 0, parent);
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

//      qDebug() << "entry: " << path;
      for (const QString& s : parts) {
          if (!parents.contains(s)) {
//             qDebug() << "add new parent: " << s;
             parents[s] = new DirEntry(s, baseDir + "/" + path, last);
             last->appendChild(parents[s]);
             last = parents[s];
             }
          else last = parents[s];
          }
      }
  }
