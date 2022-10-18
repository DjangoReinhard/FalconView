/* 
 * **************************************************************************
 * 
 *  file:       toolcategorymodel.h
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
#ifndef TOOLCATEGORYMODEL_H
#define TOOLCATEGORYMODEL_H
#include <QSqlTableModel>
class DBConnection;
class FalconViewDB;


class ToolCategoryModel : public QSqlTableModel
{
  Q_OBJECT
public:
  explicit ToolCategoryModel(DBConnection& conn, QObject *parent = nullptr);

  int      nextId() const;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
  static bool  createTable();
  friend class FalconViewDB;
  friend class ToolManager;
  };
#endif // TOOLCATEGORYMODEL_H
