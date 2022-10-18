/* 
 * **************************************************************************
 * 
 *  file:       dockable.h
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
#ifndef DOCKABLE_H
#define DOCKABLE_H
#include <QDockWidget>
class QString;
class QWidget;
class AbstractCenterWidget;


class Dockable : public QDockWidget
{    
public:
  Dockable(AbstractCenterWidget* cw, QWidget* parent = nullptr);

  QString  name() const;
  QString  id() const;
  QAction* viewAction();
  AbstractCenterWidget* centerWidget() { return dcw; }
  AbstractCenterWidget* centerWidget() const { return dcw; }

protected:
  static const int DockingTitleHeight = 39;
  virtual void closeEvent(QCloseEvent* e) override;
//  virtual void keyPressEvent(QKeyEvent* e) override;
//  virtual void keyReleaseEvent(QKeyEvent* e) override;

private:
  AbstractCenterWidget* dcw;
  };
#endif // DOCKABLE_H
