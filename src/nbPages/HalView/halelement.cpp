/* 
 * **************************************************************************
 * 
 *  file:       halelement.cpp
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    23.1.2022 by Django Reinhard
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
#include "halelement.h"
#include <QVariant>


HalElement::HalElement(HalElement* parent)
 : QObject(parent)
 , p(nullptr) {
  }


HalElement::~HalElement() {
  qDeleteAll(children);
  }


void HalElement::appendChild(HalElement *child) {
  children.append(child);
  child->setParent(this);
  }


HalElement* HalElement::child(int row) {
  if (row < 0 || row >= children.size())
     return nullptr;
  return children.at(row);
  }


int HalElement::childCount() const {
  return children.count();
  }


int HalElement::childNumber() {
  HalElement* p = static_cast<HalElement*>(QObject::parent());

  if (p) return p->children.indexOf(const_cast<HalElement*>(this));
  return 0;
  }


//int HalElement::columnCount() const {
//  return 1;
//  }


QVariant HalElement::data(int column) const {
  if (column == 0) return name;
  return QVariant();
  }


void HalElement::setData(int column, const QVariant& value) {
  if (!column) name = value.toString();
  }


//int HalElement::row() const {
//  if (parentItem) return parentItem->children.indexOf(const_cast<HalElement*>(this));
//  return 0;
//  }
