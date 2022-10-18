/* 
 * **************************************************************************
 * 
 *  file:       abstractcondition.cpp
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
#include <abstractcondition.h>
#include <valuemodel.h>
#include <QDebug>


AbstractCondition::AbstractCondition(ValueModel* model, const QVariant& value, QObject *parent)
 : QObject(parent)
 , m(model)
 , v(value)
 , met(false)
 , initialized(false) {
  if (m) connect(m, &ValueModel::valueChanged, this, &AbstractCondition::update);
  }


AbstractCondition::~AbstractCondition() {
  }


QString AbstractCondition::name() const {
  return m ? m->getName() : QString();
  }


bool AbstractCondition::result() const {
//  qDebug() << "Condition [" << (m ? m->getName() : "unnamed") << "] has result:" << met;
  return met;
  }


void AbstractCondition::update() {
//  qDebug() << "AbstractCondition::update() ...";
  bool rv = eval();

//  qDebug() << "\teval returned: " << (rv ? "true" : "false");
  if (!initialized || rv != met) {
     met = rv;
//     qDebug() << "\tgonna fire condition changed event ...";
     emit  conditionChanged(met);
     initialized = true;
     }
  }
