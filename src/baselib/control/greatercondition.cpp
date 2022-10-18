/* 
 * **************************************************************************
 * 
 *  file:       greatercondition.cpp
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    22.1.2022 by Django Reinhard
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
#include <greatercondition.h>
#include <valuemodel.h>
#include <QDebug>


GreaterCondition::GreaterCondition(ValueModel* model, const QVariant& value, QObject *parent)
 : AbstractCondition(model, value, parent) {
  update();
  }


GreaterCondition::~GreaterCondition() {
  }


bool GreaterCondition::eval() {
//  qDebug() << "GreaterCondition::eval() ...";
  switch (model()->getValue().type()) {
    case QVariant::Type::Char:
    case QVariant::Type::Int:
//         qDebug() << "compare signed integers (>): " << model()->getValue().toInt()
//                  << "\tvalue: " << value().toInt();
         return model()->getValue().toInt() > value().toInt();
    case QVariant::Type::LongLong:
//         qDebug() << "compare signed integers (>): " << model()->getValue().toLongLong()
//                  << "\tvalue: " << value().toLongLong();
         return model()->getValue().toLongLong() > value().toLongLong();
    case QVariant::Type::UInt:
    case QVariant::Type::ULongLong:
//         qDebug() << "compare unsigned integers (>): " << model()->getValue().toLongLong()
//                  << "\tvalue: " << value().toLongLong();
         return model()->getValue().toULongLong() > value().toULongLong();
    case QVariant::Type::Double:
//         qDebug() << "compare decimals (>): " << model()->getValue().toDouble()
//                  << "\tvalue: " << value().toDouble();
         return model()->getValue().toDouble() > value().toDouble();
    default:
         return false;
    }
  return false;
  }
