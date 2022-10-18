/* 
 * **************************************************************************
 * 
 *  file:       dbconnection.cpp
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
#include <dbconnection.h>
#include <QSqlDatabase>
#include <QFileInfo>


DBConnection::DBConnection(const QString& dbName, const QString& dbType)
 : name(dbName)
 , type(dbType) {
  if (!dbName.contains('/')) {
     QFileInfo dbPath(QString("../FalconView/db/") + dbName);

     name = dbPath.absoluteFilePath();
     }
  }


DBConnection::DBConnection(const DBConnection& other)
 : name(other.name)
 , type(other.type) {
  }


bool DBConnection::connect() {
  if (QSqlDatabase::database().isValid()) {
     if (QSqlDatabase::database().isOpen()) return true;
     else                                   return QSqlDatabase::database().open();
     }
  QSqlDatabase db = QSqlDatabase::addDatabase(type);

  db.setDatabaseName(name);
  db.setHostName("localhost");

  return db.open();
  }
