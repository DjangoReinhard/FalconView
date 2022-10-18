/* 
 * **************************************************************************
 * 
 *  file:       syseventview.h
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
#ifndef SYSEVENTVIEW_H
#define SYSEVENTVIEW_H
#include <abscenterwidget.h>
#include <CenterPageInterface.h>

QT_BEGIN_NAMESPACE
class QTableView;
class QAction;
class SysEventModel;
class DBConnection;
class QSortFilterProxyModel;
QT_END_NAMESPACE


class SysEventView : public AbstractCenterWidget, public CenterPageInterface
{
  Q_OBJECT
  Q_INTERFACES(CenterPageInterface)
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "CenterPageInterface_iid" FILE "sysEventView.json")
#endif
public:
  explicit SysEventView(QWidget* parent = nullptr);
  virtual ~SysEventView();

protected:
  virtual void closeEvent(QCloseEvent* e) override;
  virtual void connectSignals() override;
  virtual void updateStyles() override;
  virtual bool eventFilter(QObject* o, QEvent* e) override;
  virtual void showEvent(QShowEvent *event) override;
  virtual QWidget* createContent() override;
  virtual QAction* viewAction() override;

private:
  QTableView*            table;
  SysEventModel*         model;
  QSortFilterProxyModel* px;
  };
#endif // SYSEVENTVIEW_H
