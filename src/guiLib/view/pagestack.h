/* 
 * **************************************************************************
 * 
 *  file:       pagestack.h
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
#ifndef PAGESTACK_H
#define PAGESTACK_H
#include <abscenterwidget.h>
#include <QMap>
class CenterPage;
class QKeyEvent;
class QCloseEvent;
class Kernel;


class PageStack : public AbstractCenterWidget
{
  Q_OBJECT
public:
  PageStack(QWidget* parent = nullptr);

  CenterPage*      activatePage(const QString& name);
  QString          activePage() const;
  CenterPage*      page(const QString& name);
  QList<QString>   pages() const;
  void             addPage(CenterPage* page, const QString& name = QString());
  void             dump() const;
  void             windowClosing(QCloseEvent* e);
  virtual QAction* viewAction();

protected:
  virtual QWidget* createContent() override;
  virtual void connectSignals() override;
  virtual void updateStyles() override;

private:
  QMap<QString, CenterPage*> pagePool;
  QString                    curPage;
  QAction*                   action;
  friend class Kernel;
  };
#endif // PAGESTACK_H
