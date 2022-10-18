/* 
 * **************************************************************************
 * 
 *  file:       direntry.cpp
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
#include <direntry.h>


DirEntry::DirEntry(const QString& name, const QString& path, DirEntry* parent)
 : itemData(name)
 , filePath(path)
 , parentItem(parent) {
  }


DirEntry::~DirEntry() {
  qDeleteAll(children);
  }


void DirEntry::appendChild(DirEntry *child) {
  children.append(child);
  }


DirEntry* DirEntry::child(int row) {
  if (row < 0 || row >= children.size())
     return nullptr;
  return children.at(row);
  }


int DirEntry::childCount() const {
  return children.count();
  }


int DirEntry::childNumber() const {
  if (parentItem)
     return parentItem->children.indexOf(const_cast<DirEntry*>(this));
  return 0;
  }


int DirEntry::columnCount() const {
  return 1;
  }


QVariant DirEntry::data(int column) const {
  if (column == 0)      return itemData;
  else if (column == 9) return filePath;
  return QVariant();
  }


void DirEntry::setData(int column, const QVariant& value) {
  if (!column)          itemData = value;
  else if (column == 9) filePath = value.toString();
  }


QString DirEntry::path() const {
  return filePath;
  }


DirEntry* DirEntry::parent() {
  return parentItem;
  }


int DirEntry::row() const {
  if (parentItem) return parentItem->children.indexOf(const_cast<DirEntry*>(this));
  return 0;
  }
