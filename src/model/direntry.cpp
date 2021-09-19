#include <direntry.h>


DirEntry::DirEntry(const QString& name, const QString& path, DirEntry* parent)
 : itemData(name)
 , filePath(path)
 , parentItem(parent) {
  }


DirEntry::~DirEntry() {
  qDeleteAll(children);
  }


void DirEntry::appendChild(DirEntry *child) {
  children.append(child);
  }


DirEntry* DirEntry::child(int row) {
  if (row < 0 || row >= children.size())
     return nullptr;
  return children.at(row);
  }


int DirEntry::childCount() const {
  return children.count();
  }


int DirEntry::columnCount() const {
  return 1;
  }


QVariant DirEntry::data(int column) const {
  if (column == 0) return itemData;
  if (column == 9) return filePath;
  return QVariant();
  }


QString DirEntry::path() const {
  return filePath;
  }


DirEntry* DirEntry::parent() {
  return parentItem;
  }


int DirEntry::row() const {
  if (parentItem) return parentItem->children.indexOf(const_cast<DirEntry*>(this));
  return 0;
  }
