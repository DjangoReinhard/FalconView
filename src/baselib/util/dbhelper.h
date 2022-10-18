/* 
 * **************************************************************************
 * 
 *  file:       dbhelper.h
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
#ifndef DBHELPERINTERFACE_H
#define DBHELPERINTERFACE_H
#include <QtPlugin>
#include <QString>
class DBConnection;


class DBHelperInterface
{
public:
  virtual ~DBHelperInterface() = default;

  virtual bool          connect(const QString& path)         = 0;
  virtual DBConnection* createDatabase(const QString& path)  = 0;
  virtual void          createSampleData(DBConnection& conn) = 0;
  DBConnection*         dbConnection() { return conn; }

protected:
  DBConnection* conn;
  };

QT_BEGIN_NAMESPACE
#define DBHelperInterface_iid "de.schwarzrot.FalconView.DBHelper/0.1"
Q_DECLARE_INTERFACE(DBHelperInterface, DBHelperInterface_iid)
QT_END_NAMESPACE

#endif // DBHELPERINTERFACE_H
