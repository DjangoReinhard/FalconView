/* 
 * **************************************************************************
 * 
 *  file:       numlabel.cpp
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    19.1.2022 by Django Reinhard
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
#include <numlabel.h>
#include <QLocale>
#include <QResizeEvent>
#include <QDebug>
#include <guicore.h>


NumLabel::NumLabel(QWidget* parent, int digits)
 : QLabel(parent)
 , digits(digits) {
  }


NumLabel::~NumLabel() {
  }


void NumLabel::setDigits(int digits) {
  this->digits = digits;
  }


void NumLabel::setValue(const QVariant &v) {
  setText(GuiCore().locale().toString(v.toDouble(), 'f', digits));
  }
