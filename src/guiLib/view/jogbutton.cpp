/* 
 * **************************************************************************
 * 
 *  file:       jogbutton.cpp
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
#include "jogbutton.h"
#include <QStylePainter>
#include <QStyleOptionFocusRect>
#include <QDebug>


/*
 * ugly coding around - as QIcon does not provide a combination for a pressed (unchecked)
 * button and QButtonGroup does not support unchecked buttons and QAbstractButton::setIcon
 * is not virtual ...
 * What a mess!
 */
JogButton::JogButton(QWidget* parent)
 : QToolButton(parent)
 , counterPart(nullptr) {
  connect(this, &QToolButton::pressed, this, &JogButton::pressed);
  connect(this, &QToolButton::released, this, &JogButton::released);
  connect(this, &QToolButton::toggled, this, &JogButton::toggled);
  }


JogButton::~JogButton() {
  }


/*
 * replacement for setIcon being not virtual
 */
void JogButton::init(JogButton* other) {
  counterPart = other;
  icoDefault = icon();
  icoActive  = icon().pixmap(128, 128, QIcon::Normal, QIcon::On);
  }


/*
 * replacement for button-group to allow unchecked buttons
 */
void JogButton::pressed() {
  if (!isCheckable()) setIcon(icoActive);
  else {
     if (counterPart->isChecked()) counterPart->setChecked(false);
     }
  }


/*
 * replacement for QIcon not having state for pressed but unchecked button
 */
void JogButton::released() {
  setIcon(icoDefault);
  }


/*
 * replacement for button::click not releasing buttons, that are checkable and checked
 */
void JogButton::toggled(bool checked) {
  if (checked) {
     if (counterPart->isChecked()) counterPart->setChecked(false);
     }
  }
