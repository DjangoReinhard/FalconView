/* 
 * **************************************************************************
 * 
 *  file:       dockable.cpp
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
#include <dockable.h>
#include <abscenterwidget.h>
#include <QLayout>
#include <QAction>


Dockable::Dockable(AbstractCenterWidget* cw, QWidget* parent)
 : QDockWidget(cw->windowTitle(), parent)
 , dcw(cw) {
  dcw->setParent(this);
  setObjectName(QString("%1Dockable").arg(cw->objectName()));
  setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
  layout()->setContentsMargins(0, 0, 0, 0);
  setWidget(cw);
  }


QString Dockable::name() const {
  if (dcw) return dcw->windowTitle();
  return objectName();
  }


QString Dockable::id() const {
  if (dcw) return dcw->objectName();
  return objectName();
  }


void Dockable::closeEvent(QCloseEvent* e) {
  if (dcw) dcw->closeEvent(e);
  }


QAction* Dockable::viewAction() {
  if (dcw) return dcw->viewAction();
  return new QAction();
  }


//void DynDockable::keyPressEvent(QKeyEvent* e) {
//  if (dcw) dcw->keyPressEvent(e);
//  }


//void DynDockable::keyReleaseEvent(QKeyEvent* e) {
//  if (dcw) dcw->keyReleaseEvent(e);
//  }
