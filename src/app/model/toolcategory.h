/* 
 * **************************************************************************
 * 
 *  file:       toolcategory.h
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
#ifndef TOOLCATEGORY_H
#define TOOLCATEGORY_H
#include <QObject>
#include <QVariant>
#include <QVector>
//#include <tool.h>
class ToolCategory;


class ToolCategory : public QObject
{
  Q_OBJECT
public:
  ToolCategory(int id, const QString& name, ToolCategory* parent = nullptr);

  void          appendChild(ToolCategory* child);
  ToolCategory* child(int row);
  ToolCategory* parent();
  int           columnCount()    const;
  int           childCount()     const;
  QVariant      data(int column) const;
  int           row()            const;
  void          dump();

private:
//  QMap<QString, int> pool;
  QVector<ToolCategory*> children;
//  QMap<int, Tool>        tools;
  int     id;
  QString name;
  };

#endif // TOOLCATEGORY_H
