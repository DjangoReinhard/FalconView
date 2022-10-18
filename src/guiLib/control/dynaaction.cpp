/* 
 * **************************************************************************
 * 
 *  file:       dynaaction.cpp
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
#include <dynaaction.h>
#include <abstractcondition.h>
#include <QDebug>


DynaAction::DynaAction(const QIcon& disIco, const QIcon& enIco, const QIcon& cIco, const QString& text, AbstractCondition* cEnabled, AbstractCondition* cChecked, QObject *parent)
 : QAction(disIco, text, parent)
 , cEnabled(cEnabled)
 , cChecked(cChecked)
 , disabledIcon(disIco)
 , enabledIcon(enIco)
 , checkedIcon(cIco) {
  setObjectName("DynaAction");
  if (cEnabled) {
     connect(cEnabled, &AbstractCondition::conditionChanged, this, &DynaAction::setEnabled);
     setEnabled(cEnabled->result());
     }
  if (cChecked) {
     connect(cChecked, &AbstractCondition::conditionChanged, this, &DynaAction::setChecked);
     setChecked(cChecked->result());
     }
  }


void DynaAction::setEnabled(bool enabled) {
//  qDebug() << "DA[" << text() << "]: setEnabled(" << (enabled ? "ON" : "OFF") << ")";
  if (enabled) {
//     setChecked(cChecked->result());
     QAction::setIcon(enabledIcon);
     QAction::setEnabled(enabled);
     }
  else {
     QAction::setIcon(disabledIcon);
     QAction::setEnabled(enabled);
     }
  }


void DynaAction::setChecked(bool checked) {
//  qDebug() << "DA[" << text() << "]: setChecked(" << (checked ? "YES" : "NO") << ")";
  if (checked) {
     QAction::setIcon(checkedIcon);
     QAction::setChecked(checked);
     }
  else {
     QAction::setIcon(enabledIcon);
     QAction::setChecked(checked);
     }
//  qDebug() << "DA[" << text() << "]: is checked(" << (checked ? "YES" : "NO") << ")";
  }
