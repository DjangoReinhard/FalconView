/* 
 * **************************************************************************
 * 
 *  file:       settingsnb.h
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
#ifndef SETTINGSNB_H
#define SETTINGSNB_H
#include <abscenterwidget.h>
#include <CenterPageInterface.h>
#include <QTabWidget>
class QCloseEvent;
class QVariant;


class SettingsNotebook : public AbstractCenterWidget, public CenterPageInterface
{
  Q_OBJECT
  Q_INTERFACES(CenterPageInterface)
public:
  explicit SettingsNotebook(QWidget *parent = nullptr);
  virtual ~SettingsNotebook();

  void addPage(AbstractCenterWidget* page);
  void dump();

protected:
  virtual bool eventFilter(QObject *obj, QEvent *event) override;
  virtual void resizeEvent(QResizeEvent *event) override;
  QString loadStyles(QTabWidget::TabPosition tp);
  virtual QWidget* createContent() override;
  void pageChanged(AbstractCenterWidget* page, const QVariant& dirty);
  bool switchTabPage(int pageIndex);
  void currentChanged(int index);

  virtual void     connectSignals() override;
  virtual void     updateStyles() override;
  virtual void     keyPressEvent(QKeyEvent* e) override;
  virtual void     closeEvent(QCloseEvent*) override;
  virtual void     showEvent(QShowEvent* e) override;
  virtual QAction* viewAction() override;

protected slots:
  void enableTabs(const QVariant& enable);

private:
  QTabWidget* tw;
  QAction*    action;
  };
#endif // SETTINGSNB_H
