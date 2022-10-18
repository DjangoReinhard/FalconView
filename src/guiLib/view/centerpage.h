/* 
 * **************************************************************************
 * 
 *  file:       centerpage.h
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
#ifndef CENTERPAGE_H
#define CENTERPAGE_H
#include <QWidget>
//class CenterPageInterface;
class AbstractCenterWidget;
class QFrame;


class CenterPage : public QWidget
{
  Q_OBJECT
public:
  explicit CenterPage(AbstractCenterWidget* cp, bool visualFrame = false, QWidget *parent = nullptr);

  QString  name() const;
  QString  id() const;
  QAction* viewAction();
  inline AbstractCenterWidget* centerWidget() { return dcw; }
  inline AbstractCenterWidget* centerWidget() const { return dcw; }
  virtual void closeEvent(QCloseEvent* e) override;

private:
  QFrame*               frame;
  AbstractCenterWidget* dcw;
//  CenterPageInterface* cpi;
  };

#endif // CENTERPAGE_H
