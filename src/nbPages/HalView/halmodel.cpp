/* 
 * **************************************************************************
 * 
 *  file:       halmodel.cpp
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
#include "halmodel.h"
#include "halelement.h"
#include "halcomponent.h"
#include "halpin.h"

#include <QDir>
#include <QDebug>

#include <sys/types.h>
#include <unistd.h>

#include <rtapi.h>
#include <hal.h>
#include <hal_priv.h>


HalModel::HalModel(QObject *parent)
 : QAbstractItemModel(parent)
 , root(new HalComponent(0))
 , name(QString("FalconView%1").arg(getpid()))
 , compID(-1) {
  compID = hal_init(name.toStdString().c_str());
  int rv;

  if (compID < 0) {
     qDebug() << "failed to initialize hal component ("
              << name.toStdString().c_str() << "): " << compID;
     }
  if ((rv = hal_ready(compID))) {
     qDebug() << "hal_ready failed with " << rv;
     }
  if (!hal_shmem_base) {
     qDebug() << "could not access hal-data region! #3";
     }
  if (!hal_data) {
     qDebug() << "could not access hal-data region! #4";
     }
  setupModelData(root);
  }


HalModel::~HalModel() {
  hal_exit(compID);
  delete root;
  }


int HalModel::columnCount(const QModelIndex &parent) const {
  return 5;
  }


QVariant HalModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid()) return QVariant();
  if (role != Qt::DisplayRole) return QVariant();
  HalElement* item = static_cast<HalElement*>(index.internalPointer());

  return item->data(index.column());
  }


Qt::ItemFlags HalModel::flags(const QModelIndex& index) const {
  if (!index.isValid()) return Qt::NoItemFlags;
  return QAbstractItemModel::flags(index);
  }


QVariant HalModel::headerData(int section, Qt::Orientation orientation, int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
     switch (section) {
       case 0: return "component/pin";
       case 1: return "type";
       case 2: return "dir";
       case 3: return "signal";
       case 4: return "value";
       }
     }
  return QVariant();
  }


HalElement* HalModel::getItem(const QModelIndex &index) const {
  if (index.isValid()) {
     HalElement* item = static_cast<HalElement*>(index.internalPointer());

     if (item) return item;
     }
  return root->child(0);
  }


QModelIndex HalModel::index(int row, int column, const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent)) return QModelIndex();
  HalElement* parentItem;

  if (!parent.isValid()) parentItem = root;
  else                   parentItem = static_cast<HalElement*>(parent.internalPointer());
  HalElement* childItem  = parentItem->child(row);

  if (childItem) return createIndex(row, column, childItem);
  return QModelIndex();
  }


//bool HalModel::insertDirectory(const QModelIndex &parentIdx, HalElement *entry) {
//  if (!parentIdx.isValid()) return false;
//  if (!entry) return false;
//  HalElement* parent = getItem(parentIdx);
//  QDir      newDir(entry->path());

//  if (parent == entry->parent() && newDir.mkpath(newDir.path())) {
//     beginInsertRows(parentIdx, parent->childCount(), parent->childCount());
//     parent->appendChild(entry);
//     endInsertRows();

//     return true;
//     }
//  return false;
//  }


//bool HalModel::setData(const QModelIndex &index, const QVariant &value, int role) {
//  if (!index.isValid()) return false;
//  if (!(role == Qt::EditRole || role == Qt::DisplayRole)) return false;
//  HalElement* item = getItem(index);

//  if (!item) return false;
//  QFileInfo fi(item->path());
//  QDir      oldDir(item->path());
//  QVariant  oldName = item->data(0);
//  QString   newPath(fi.dir().absolutePath() + "/" + value.toString());

//  if (oldDir.rename(item->path(), newPath)) {
//     item->setData(0, value);
//     item->setData(9, newPath);
//     emit dataChanged(index
//                    , index
//                    , { Qt::DisplayRole, Qt::EditRole });
//     return true;
//     }
//  return false;
//  }


QModelIndex HalModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) return QModelIndex();
  HalElement* childItem  = getItem(index);
  HalElement* parentItem = static_cast<HalElement*>(((QObject*)childItem)->parent());

  if (parentItem == root || !parentItem)
     return QModelIndex();
  return createIndex(parentItem->childNumber(), 0, parentItem);
  }


//HalElement* HalModel::root() const {
//  return rootItem;
//  }


int HalModel::rowCount(const QModelIndex &parent) const {
  HalElement* parentItem;

  if (parent.column() > 0) return 0;
  if (!parent.isValid()) parentItem = root;
  else                   parentItem = static_cast<HalElement*>(parent.internalPointer());
  return parentItem->childCount();
  }


void HalModel::processPins(int component, HalElement*  parent) {
  int        next = hal_data->pin_list_ptr;
  hal_pin_t* p;
  HalPin*    pin;

  if (component >= 0) {
     while (next) {
           p = static_cast<hal_pin_t*>((void*)(hal_shmem_base + next));
           if (p->owner_ptr == component) break;
           next = p->next_ptr;
           }
     }
  while (next) {
        pin = new HalPin(next);
        if (component >= 0 && component != pin->owner()) break;
        parent->appendChild(pin);
        next = pin->next();
        }
  }


void HalModel::setupModelData(HalElement *parent) {
  int           next = hal_data->comp_list_ptr;
  HalComponent* comp;

  while (next) {
        comp = new HalComponent(next);
        parent->appendChild(comp);
        processPins(next, comp);
        next = comp->next();
        }
  }
