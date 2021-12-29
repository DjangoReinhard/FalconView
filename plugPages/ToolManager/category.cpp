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
#include <category.h>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlError>
#include <QDebug>


Category::Category(int id, const QString& name)
 : parentItem(nullptr) {
  append(QSqlField("id", QVariant::Int, "Category"));
  append(QSqlField("name", QVariant::String, "Category"));
  append(QSqlField("parent", QVariant::Int, "Category"));
  setValue("id", id);
  setValue("name", name);
  setValue("parent", id);
  }


Category::Category(Category* parent)
 : parentItem(parent) {
  append(QSqlField("id", QVariant::Int, "Category"));
  append(QSqlField("name", QVariant::String, "Category"));
  append(QSqlField("parent", QVariant::Int, "Category"));
  }


Category::Category(const QSqlRecord& other)
 : QSqlRecord(other)
 , parentItem(nullptr) {
  }


Category::~Category() {
  qDeleteAll(childItems);
  }


Category* Category::child(int number) {
  if (number < 0 || number >= childItems.size()) return nullptr;
  return childItems.at(number);
  }


int Category::childCount() const {
  return childItems.count();
  }


int Category::childNumber() const {
  if (parentItem)
     return parentItem->childItems.indexOf(const_cast<Category*>(this));
  return 0;
  }


int Category::columnCount() const {
  return 3;
  }


QVariant Category::data(int column) const {
  switch (column) {
    case 0: return value("name");
    case 1: return value("id");
    case 2: return value("parent");
    }
  return QVariant();
  }


bool Category::insertChildren(int position, int count, int) {
  if (position < 0 || position > childItems.size())
     return false;

  for (int row = 0; row < count; ++row) {
      childItems.insert(position, new Category(this));
      }
  return true;
  }


bool Category::insertColumns(int, int) {
  throw QString("unsupported function insertColumns!");
//  if (position < 0 || position > itemData.size())
//     return false;

//  for (int column = 0; column < columns; ++column)
//      itemData.insert(position, QVariant());

//  for (Category* child : qAsConst(childItems))
//      child->insertColumns(position, columns);
  return false;
  }


Category* Category::parent() {
  return parentItem;
  }


bool Category::removeChildren(int position, int count) {
  if (position < 0 || position + count > childItems.size())
     return false;

  for (int row = 0; row < count; ++row)
      delete childItems.takeAt(position);

  return true;
  }


bool Category::removeColumns(int, int) {
  throw QString("unsupported function removeColumns!");
//  if (position < 0 || position + columns > itemData.size())
//     return false;

//  for (int column = 0; column < columns; ++column)
//      itemData.remove(position);

//  for (Category* child : qAsConst(childItems))
//      child->removeColumns(position, columns);
  return false;
  }


bool Category::setData(int column, const QVariant &value) {
  switch (column) {
    case 0:  setValue("name", value); break;
    case 1:  setValue("id", value); break;
    case 2:  setValue("parent", value); break;
    default: return false;
    }
  return true;
  }


bool Category::updateName(const QString &name) {
  QString qs = QString("UPDATE Category SET name='%1' WHERE id=%2").arg(name).arg(value("id").toInt());
  QSqlQuery q(qs);

  if (!q.exec()) {
     qDebug() << "failed to query tools 4 cat" << value(0) << q.lastError().text();
     return false;
     }
  return true;
  }


bool Category::remove() {
  QString qs = QString("DELETE FROM Category WHERE id=%2").arg(value("id").toInt());
  QSqlQuery q(qs);

  if (!q.exec()) {
     qDebug() << "failed to query tools 4 cat" << value(0) << q.lastError().text();
     return false;
     }
  return true;
  }

