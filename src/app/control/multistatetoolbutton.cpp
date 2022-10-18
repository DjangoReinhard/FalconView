/* 
 * **************************************************************************
 * 
 *  file:       multistatetoolbutton.cpp
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
#include <multistatetoolbutton.h>
#include <valuemanager.h>
#include <valuemodel.h>
#include <QDebug>


MultiStateToolButton::MultiStateToolButton(ValueModel* vm, const QIcon& s0Icon, const QIcon& s1Icon, const QIcon& s2Icon, QWidget* parent)
 : QToolButton(parent)
 , model(vm)
 , s0Icon(s0Icon)
 , s1Icon(s1Icon)
 , s2Icon(s2Icon) {
  setIcon(this->s0Icon);
  connect(model, &ValueModel::valueChanged, this, &MultiStateToolButton::stateChanged);
  }


void MultiStateToolButton::stateChanged(const QVariant& state) {
  ValueManager vm;

  qDebug() << "\t<<<< ==========   MultiStateButton::stateChanged ... " << state;
  vm.getModel("allHomed")->dump();
  vm.getModel("taskState")->dump();
  vm.getModel("execState")->dump();
  vm.getModel("errorActive")->dump();

  switch (state.toInt()) {
    case 2:
    case 3:   setIcon(s1Icon); break;
    case 4:   setIcon(s2Icon); break;
    default:  setIcon(s0Icon); break;
    }
  }
