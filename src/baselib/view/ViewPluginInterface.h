/* 
 * **************************************************************************
 * 
 *  file:       ViewPluginInterface.h
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
#ifndef VIEWPLUGININTERFACE_H
#define VIEWPLUGININTERFACE_H
#include <QtPlugin>

class DBConnection;
class GuiCore;
QT_BEGIN_NAMESPACE
class QAction;
class QWidget;
class QCloseEvent;
class QShowEvent;
QT_END_NAMESPACE


class ViewPluginInterface
{
public:
  virtual ~ViewPluginInterface() = default;

  virtual void     closeEvent(QCloseEvent* e) = 0;  // a
  virtual void     showEvent(QShowEvent* e)   = 0;  // a

  virtual QWidget* createContent()  = 0;            // a
  virtual void     connectSignals() = 0;
  virtual void     updateStyles()   = 0;
  };

QT_BEGIN_NAMESPACE
#define ViewPluginInterface_iid "de.schwarzrot.FalconView.ViewPlugin/0.1"
Q_DECLARE_INTERFACE(ViewPluginInterface, ViewPluginInterface_iid)
QT_END_NAMESPACE

#endif // VIEWPLUGININTERFACE_H
