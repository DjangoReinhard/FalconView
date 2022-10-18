/* 
 * **************************************************************************
 * 
 *  file:       toolcategory.cpp
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
#include <toolcategory.h>
#include <QDebug>


ToolCategory::ToolCategory(int id, const QString& name, ToolCategory* parent)
 : QObject((QObject*)parent)
 , id(id)
 , name(name) {
  }


void ToolCategory::appendChild(ToolCategory* child) {
  children.append(child);
  }


int ToolCategory::columnCount() const {
  return 1;
  }


int ToolCategory::childCount() const {
  return children.count();
  }


QVariant ToolCategory::data(int column) const {
  if (column == 0) return name;
  if (column == 9) return id;
  return QVariant();
  }


ToolCategory* ToolCategory::child(int row) {
  if (row < 0 || row >= children.size()) return nullptr;
  return children.at(row);
  }


ToolCategory* ToolCategory::parent() {
  return static_cast<ToolCategory*>(QObject::parent());
  }


int ToolCategory::row() const {
  if (QObject::parent()) return static_cast<ToolCategory*>(QObject::parent())->children.indexOf(const_cast<ToolCategory*>(this));
  return 0;
  }


void ToolCategory::dump() {
  qDebug() << "toolCategory: #" << id << " / " << name << " (" << static_cast<ToolCategory*>(QObject::parent())->name << ")";
  }
