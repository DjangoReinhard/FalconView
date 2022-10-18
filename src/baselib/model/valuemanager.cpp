/* 
 * **************************************************************************
 * 
 *  file:       valuemanager.cpp
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    29.1.2022 by Django Reinhard
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
#include <valuemanager.h>
#include <iostream>
#include <QDebug>


ValueManager::ValueManager() {
  if (!instance) instance = new ValueHolder();
  assert(instance);
  }


ValueManager::ValueManager(void* pFromOuterAddressSpace) {
  if (!instance) instance = (ValueHolder*)pFromOuterAddressSpace;
  assert(instance);
  }


ValueModel* ValueManager::getModel(const QString& name, const QVariant& defaultValue) {
  ValueModel* vm = nullptr;

  if (!instance->models.contains(name)) {
     vm = new ValueModel(name, defaultValue);

     instance->models[name] = vm;
     }
  else vm = instance->models.value(name, nullptr);

  return vm;
  }


void ValueManager::setValue(const QString& name, const QVariant& value) {
  if (!instance->models.contains(name)) {
     ValueModel* vm = new ValueModel(name, value);

     qDebug() << "VM: new model created for >" << name << "<";

     instance->models[name] = vm;
     }
  else {
     ValueModel* vm = instance->models.value(name);

     vm->setValue(value);
     }
  }


QVariant ValueManager::getValue(const QString& name) {
  if (instance->models.contains(name)) {
     ValueModel* vm = instance->models.value(name);

     return vm->getValue();
     }
  return QVariant();
  }


void ValueManager::dump() {
  instance->dump();
  }


ValueManager::ValueHolder::ValueHolder() {
  }


void ValueManager::ValueHolder::dump() {
  QMap<QString, ValueModel*>::const_iterator i = models.constBegin();

  std::cout << "known ValueModels are:" << std::endl;
  while (i != models.constEnd()) {
        std::cout << i.key().toStdString().c_str()
                  << ": " << i.value()->getName().toStdString().c_str()
                  << "\t with value: " << i.value()->getValue().toString().toStdString().c_str()
                  << std::endl;
        ++i;
        }
  std::cout << std::endl;
  }


ValueManager::ValueHolder* ValueManager::instance = nullptr;
