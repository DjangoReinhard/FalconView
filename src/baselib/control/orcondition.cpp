/* 
 * **************************************************************************
 * 
 *  file:       orcondition.cpp
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
#include <orcondition.h>
#include <QDebug>


OrCondition::OrCondition(AbstractCondition* c0, AbstractCondition* c1, QObject *parent)
 : AbstractCondition(nullptr, QVariant(), parent) {
  addCondition(c0);
  addCondition(c1);
  }


OrCondition::~OrCondition() {
  }


OrCondition& OrCondition::addCondition(AbstractCondition* c) {
  connect(c, &AbstractCondition::conditionChanged, this, &AbstractCondition::update);
  cl.append(c);

  return *this;
  }


bool OrCondition::eval() {
  for (auto c : qAsConst(cl)) {
//      qDebug() << "OrCondition::eval() ..." << c->result();
      if (c->result()) return true;
      }
  return false;
  }
