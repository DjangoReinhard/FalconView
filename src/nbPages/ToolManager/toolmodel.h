/* 
 * **************************************************************************
 * 
 *  file:       toolmodel.h
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
#ifndef TOOLMODEL_H
#define TOOLMODEL_H
#include <QSqlTableModel>
#include <QIcon>
class FalconViewDB;
class DBConnection;
class GuiCore;


class ToolModel : public QSqlTableModel
{
  Q_OBJECT
public:
  explicit ToolModel(DBConnection& conn, QObject *parent = nullptr);

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  QVariant promptData(int section, int role = Qt::DisplayRole) const;
  int      tools4Category(int categoryId);
  int      exportTools();
  int      maxToolNum();
  int      nextId();
  bool     existsToolNum(int toolNum);
  void     toggleSelection(int row);
  void     setCore(GuiCore* core);

private:
  static bool  createTable();
  QIcon    ui;
  QIcon    ci;
  GuiCore* core;
  friend class FalconViewDB;
  friend class ToolManager;
  };
#endif // TOOLMODEL_H
