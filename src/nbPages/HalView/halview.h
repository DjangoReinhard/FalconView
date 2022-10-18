/* 
 * **************************************************************************
 * 
 *  file:       halview.h
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    23.1.2022 by Django Reinhard
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
#ifndef HALVIEW_H
#define HALVIEW_H
#include <abscenterwidget.h>

class HalModel;
QT_BEGIN_NAMESPACE
class QAction;
class QLineEdit;
class QTreeView;
QT_END_NAMESPACE


class HalView : public AbstractCenterWidget
{
  Q_OBJECT
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "ViewCenterPage_iid" FILE "halView.json")
#endif
public:
  explicit HalView(QWidget* parent = nullptr);
  virtual ~HalView();

  virtual QWidget* createContent() override;
  virtual void     connectSignals() override;
  virtual void     updateStyles() override;

protected slots:
  void currentChanged(const QModelIndex &current, const QModelIndex &previous);
//  virtual bool eventFilter(QObject* o, QEvent* e) override;
  virtual void showEvent(QShowEvent *event) override;
  virtual void closeEvent(QCloseEvent*) override;

private:
  QTreeView* tree;
  HalModel*  model;
  };
#endif // HALVIEW_H
