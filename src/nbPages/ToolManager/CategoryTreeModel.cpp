/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "CategoryTreeModel.h"
#include "category.h"
#include <dbconnection.h>
#include <QtWidgets>
#include <QSqlQuery>
#include <QSqlError>


CategoryTreeModel::CategoryTreeModel(DBConnection& conn, QObject *parent)
 : QAbstractItemModel(parent)
 , rootItem(new Category(0, "Cat-Root")) {
  rootItem->insertChildren(0, 1, rootItem->columnCount());
  Category* root = rootItem->child(0);

  root->setData(0, tr("Tool-Type"));
  root->setData(1, 0);
  root->setData(2, 0);

  assert(conn.connect());
  setupModelData(root);
  }


CategoryTreeModel::~CategoryTreeModel() {
  delete rootItem;
  }


int CategoryTreeModel::columnCount(const QModelIndex& parent) const  {
  Q_UNUSED(parent);
  return rootItem->columnCount();
  }


QVariant CategoryTreeModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();
  if (role != Qt::DisplayRole && role != Qt::EditRole)
     return QVariant();
  Category* item = getItem(index);

  return item->data(index.column());
  }


Qt::ItemFlags CategoryTreeModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) return Qt::NoItemFlags;
  return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
  }


Category* CategoryTreeModel::getItem(const QModelIndex &index) const {
  if (index.isValid()) {
     Category* item = static_cast<Category*>(index.internalPointer());

     if (item) return item;
     }
  return rootItem;
  }


QVariant CategoryTreeModel::headerData(int column, Qt::Orientation orientation, int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
     switch (column) {
       case 0: return "Name";
       case 1: return "Id";
       case 2: return "P";
       }
     }
  return QVariant();
  }


QModelIndex CategoryTreeModel::index(int row, int column, const QModelIndex &parent) const {
//  qDebug() << "ask for index: row" << row << "column" << column << "parent" << parent;
  if (parent.isValid() && parent.column() != 0)
     return QModelIndex();
  Category* parentItem = getItem(parent);

  if (!parentItem) return QModelIndex();
  Category* childItem = parentItem->child(row);

  if (childItem) return createIndex(row, column, childItem);
  return QModelIndex();
  }


bool CategoryTreeModel::insertColumns(int position, int columns, const QModelIndex &parent) {
  throw QString("model::insertColumns( ... ) unexpected!");
  beginInsertColumns(parent, position, position + columns - 1);
  const bool success = rootItem->insertColumns(position, columns);

  endInsertColumns();

  return success;
  }


bool CategoryTreeModel::insertRows(int position, int rows, const QModelIndex &parent) {
  Category* parentItem = getItem(parent);

  if (!parentItem) return false;
  beginInsertRows(parent, position, position + rows - 1);
  const bool success = parentItem->insertChildren(position, rows
                                                , rootItem->columnCount());
  endInsertRows();

  return success;
  }


QModelIndex CategoryTreeModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) return QModelIndex();
  Category* childItem  = getItem(index);
  Category* parentItem = childItem ? childItem->parent() : nullptr;


  if (parentItem == rootItem || !parentItem)
     return QModelIndex();
  return createIndex(parentItem->childNumber(), 0, parentItem);
  }


bool CategoryTreeModel::removeColumns(int position, int columns, const QModelIndex &parent) {
  beginRemoveColumns(parent, position, position + columns - 1);
  const bool success = rootItem->removeColumns(position, columns);
  endRemoveColumns();

  if (rootItem->columnCount() == 0) removeRows(0, rowCount());
  return success;
  }


bool CategoryTreeModel::removeRows(int position, int rows, const QModelIndex &parent) {
  Category* parentItem = getItem(parent);

  if (!parentItem) return false;
  beginRemoveRows(parent, position, position + rows - 1);
  const bool success = parentItem->removeChildren(position, rows);
  endRemoveRows();

  return success;
  }


Category* CategoryTreeModel::root() const {
  return rootItem->child(0);
  }


int CategoryTreeModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid() && parent.column() > 0)
     return 0;
  const Category* parentItem = getItem(parent);

  return parentItem ? parentItem->childCount() : 0;
  }


bool CategoryTreeModel::setData(const QModelIndex &index, const QVariant &value, int role) {
  if (role != Qt::EditRole) return false;
  Category* item   = getItem(index);
  bool      result = item->setData(index.column(), value);

  if (result) emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
  return result;
  }


bool CategoryTreeModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role) {
  if (role != Qt::EditRole || orientation != Qt::Horizontal)
     return false;
  const bool result = rootItem->setData(section, value);

  if (result) emit headerDataChanged(orientation, section, section);
  return result;
  }


void CategoryTreeModel::setupModelData(Category* parent) {
#ifdef REDNOSE
  QList<Category*> parents;
  QList<int>       indentations;

  parents << parent;
  indentations << 0;

  int number = 0;

  while (number < lines.count()) {
        int position = 0;

        while (position < lines[number].length()) {
              if (lines[number].at(position) != ' ')
                 break;
              ++position;
              }
        const QString lineData = lines[number].mid(position).trimmed();

        if (!lineData.isEmpty()) {
           // Read the column data from the rest of the line.
           const QStringList columnStrings = lineData.split(QLatin1Char('\t'), Qt::SkipEmptyParts);
           QList<QVariant>   columnData;

           columnData.reserve(columnStrings.size());
           for (const QString &columnString : columnStrings)
               columnData << columnString;

           if (position > indentations.last()) {
              // The last child of the current parent is now the new parent
              // unless the current parent has no children.

              if (parents.last()->childCount() > 0) {
                 parents << parents.last()->child(parents.last()->childCount()-1);
                 indentations << position;
                 }
              }
           else {
              while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                    }
              }
           // Append a new item to the current parent's list of children.
           Category* parent = parents.last();

           parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
           for (int column = 0; column < columnData.size(); ++column)
               parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
           }
        ++number;
        }
#else
  QSqlTableModel tm;

  tm.setTable("Category");
  tm.select();
  int mx = tm.rowCount();

  for (int i=0; i < mx; ++i) {
      QSqlRecord rec       = tm.record(i);
      int        id        = rec.value("id").toInt();
      int        parentIdx = rec.value("parent").toInt();

      if (parentIdx && parentIdx != id) parent = categories.at(parentIdx - 1);
      else                              parent = rootItem->child(0);

//      qDebug() << "id: " << id << "name:" << rec.value("name").toString() << "parent: " << parentIdx;

      parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
      Category* cat = parent->child(parent->childCount() - 1);

      cat->setData(0, rec.value("name"));
      cat->setData(1, id);
      cat->setData(2, parentIdx);
      categories.append(cat);
      }
#endif
  }


QVector<Category*> CategoryTreeModel::categories;
