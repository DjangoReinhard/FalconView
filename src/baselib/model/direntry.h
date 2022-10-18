/* 
 * **************************************************************************
 * 
 *  file:       direntry.h
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
#ifndef DIRENTRY_H
#define DIRENTRY_H
#include <QVariant>


class DirEntry
{
public:
  DirEntry(const QString& name, const QString& path, DirEntry* parent = nullptr);
  ~DirEntry();

  void     appendChild(DirEntry* child);

  DirEntry* child(int row);
  int       childCount() const;
  int       childNumber() const;
  int       columnCount() const;
  QVariant  data(int column) const;
  QString   path() const;
  int       row() const;
  DirEntry* parent();
  void      setData(int column, const QVariant& value);

private:
  QVector<DirEntry*> children;
  QVariant           itemData;
  QString            filePath;
  DirEntry*          parentItem;
  };
#endif // DIRENTRY_H
