#include <toolcategorymodel.h>
#include <toolcategory.h>
#include <dbconnection.h>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>


ToolCategoryModel::ToolCategoryModel(QObject *parent)
 : QAbstractItemModel(parent)
 , rootItem(new ToolCategory(0, tr("Tools"))) {
  if (!DBConnection("toolTable").connect()) {
     throw new QSqlError("failed to open database!");
     }
  setupModelData(rootItem);
  }


ToolCategoryModel::~ToolCategoryModel() {
  delete rootItem;
  }


int ToolCategoryModel::columnCount(const QModelIndex& parent) const {
  if (parent.isValid())
     return static_cast<ToolCategory*>(parent.internalPointer())->columnCount();
  return rootItem->columnCount();
  }


QVariant ToolCategoryModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid()) return QVariant();
  if (role != Qt::DisplayRole) return QVariant();
  ToolCategory* item = static_cast<ToolCategory*>(index.internalPointer());

  return item->data(index.column());
  }


Qt::ItemFlags ToolCategoryModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) return Qt::NoItemFlags;
  return QAbstractItemModel::flags(index);
  }


QVariant ToolCategoryModel::headerData(int section, Qt::Orientation orientation, int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
     return rootItem->data(section);
  return QVariant();
  }


QModelIndex ToolCategoryModel::index(int row, int column, const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent)) return QModelIndex();
  ToolCategory* parentItem;

  if (!parent.isValid()) parentItem = rootItem;
  else                   parentItem = static_cast<ToolCategory*>(parent.internalPointer());
  ToolCategory* childItem = parentItem->child(row);

  if (childItem) return createIndex(row, column, childItem);
  return QModelIndex();
  }


QModelIndex ToolCategoryModel::parent(const QModelIndex& index) const {
  if (!index.isValid()) return QModelIndex();
  ToolCategory* child = static_cast<ToolCategory*>(index.internalPointer());
  ToolCategory* parent = child->parent();

  if (parent == rootItem) return QModelIndex();

  return createIndex(parent->row(), 0, parent);
  }


int ToolCategoryModel::rowCount(const QModelIndex &parent) const {
  ToolCategory* parentItem;

  if (parent.column() > 0) return 0;
  if (!parent.isValid()) parentItem = rootItem;
  else                   parentItem = static_cast<ToolCategory*>(parent.internalPointer());
  return parentItem->childCount();
  }


void ToolCategoryModel::setupModelData(ToolCategory *root) {
  QSqlTableModel tm;
  ToolCategory*  parent = root;

  tm.setTable("Category");
  tm.select();
  int mx = tm.rowCount();

  for (int i=0; i < mx; ++i) {
      QSqlRecord rec = tm.record(i);

      int id        = rec.field("id").value().toInt();
      int parentIdx = rec.field("parent").value().toInt();

      if (parentIdx != id) parent = categories.at(parentIdx - 1);

      ToolCategory* tc = new ToolCategory(rec.field("id").value().toInt()
                                        , rec.field("name").value().toString()
                                        , parent);

      tc->dump();
      categories.append(tc);
      parent->appendChild(tc);
      }
  }


QVector<ToolCategory*> ToolCategoryModel::categories;
