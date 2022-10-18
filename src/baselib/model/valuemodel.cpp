/* 
 * **************************************************************************
 * 
 *  file:       valuemodel.cpp
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
#include <valuemodel.h>
#include <QDebug>


ValueModel::ValueModel(const QString& name, const QVariant& value)
 : QObject(nullptr)
 , v(value)
 , n(name) {
  }


void ValueModel::setValue(const QVariant& value) {
//  qDebug() << "ValueModel[" <<  n << "] got new value:" << value;
  if (v != value) {
//     qDebug() << "ValueModel[" <<  n << "] value WILL change:" << v << " -> " << value;
     v = value;
     emit valueChanged(v);
     }
  }


void ValueModel::dump() const {
  qDebug() << "ValueModel[" << n  << "] has value:" << v;
  }
