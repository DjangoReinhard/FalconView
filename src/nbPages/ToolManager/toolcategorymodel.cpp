/* 
 * **************************************************************************
 * 
 *  file:       toolcategorymodel.cpp
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    3.1.2022 by Django Reinhard
 *  copyright:  (c) 2022 Django Reinhard -  all rights reserved
 * 
 *  This program is free software: you can redistribute it and/or modify 
 *  it under the terms of the GNU General Public License as published by 
 *  the Free Software Foundation, either version 2 of the License, or 
 *  (at your option) any later version. 
 *   
 *  This program is distributed in the hope that it will be useful, 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *  GNU General Public License for more details. 
 *   
 *  You should have received a copy of the GNU General Public License 
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * **************************************************************************
 */
#include "toolcategorymodel.h"
#include <dbconnection.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


ToolCategoryModel::ToolCategoryModel(DBConnection& conn, QObject *parent)
 : QSqlTableModel(parent) {
  if (!conn.connect()) {
     throw new QSqlError("failed to open database!");
     }
  setTable("Category");
  this->setEditStrategy(QSqlTableModel::OnManualSubmit);
  select();

//  qDebug() << "cat-columns" << columnCount();
//  qDebug() << "cat-rows" << rowCount();
  }


bool ToolCategoryModel::createTable() {
  QSqlQuery sql;
  bool      rv;

  rv = sql.exec("CREATE TABLE \"Category\" (id      INT NOT NULL"
                                         ", parent  INT NOT NULL"
                                         ", name    VARCHAR(50) NOT NULL"
                                         ", PRIMARY KEY(id) )");
  return rv;
  }


QVariant ToolCategoryModel::headerData(int column, Qt::Orientation orientation, int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
     switch (column) {
       case 0: return tr("id");
       case 1: return tr("name");
       case 2: return tr("parent");
       }
     }
  return QVariant();
  }


int ToolCategoryModel::nextId() const {
  QString   qs = QString("SELECT max(id) FROM Category");
  QSqlQuery q(qs);

  if (!q.exec()) {
     qDebug() << "failed to query next id" << q.lastError().text();
     }
  int nid = 0;

  if (q.next()) nid = q.value(0).toInt();

  return nid + 1;
  }
