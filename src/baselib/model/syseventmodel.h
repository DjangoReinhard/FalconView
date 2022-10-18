/* 
 * **************************************************************************
 * 
 *  file:       syseventmodel.h
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
#ifndef SYSEVENTMODEL_H
#define SYSEVENTMODEL_H
#include <QSqlTableModel>
class DBConnection;
class FalconViewDB;
class SysEvent;


class SysEventModel : public QSqlTableModel
{
  Q_OBJECT
public:
  explicit SysEventModel(DBConnection& conn, QObject *parent = nullptr);

  virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  void append(const SysEvent* e);

protected:
  int nextId();

private:
  static bool  createTable();
  friend class FalconViewDB;
  };
#endif // SYSEVENTMODEL_H
