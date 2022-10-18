/* 
 * **************************************************************************
 * 
 *  file:       abscenterwidget.h
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
#ifndef ABSCENTERWIDGET_H
#define ABSCENTERWIDGET_H
#include <QWidget>
#include <ViewPluginInterface.h>

QT_BEGIN_NAMESPACE
class PageStack;
class DBConnection;
class SettingsNotebook;
class PluginPageFactory;
class ValueManager;
class GuiCore;
class Config;
class QString;
class QAction;
class QFile;
QT_END_NAMESPACE


/*! loads widgets from uiFile and allows late initialization at page usage
 */
class AbstractCenterWidget : public QWidget, public ViewPluginInterface
{
  Q_OBJECT
  Q_INTERFACES(ViewPluginInterface)
public:
  virtual void     closeEvent(QCloseEvent* e) override;
  virtual void     showEvent(QShowEvent* e) override;
  virtual QAction* viewAction();

signals:
  void dataChanged(AbstractCenterWidget* w, const QVariant& changed);

protected:
  explicit AbstractCenterWidget(const QString& fileName, QWidget* parent = nullptr);
  explicit AbstractCenterWidget(const QString& fileName, bool addScroolArea, QWidget* parent = nullptr);
  virtual ~AbstractCenterWidget() = default;

  virtual void     initialize(const QString& name = QString());
  virtual QString  fileName() const;
  virtual void     patch(void* pk, void* pc, void* pv, void* pu = nullptr, bool flag = false);
  virtual QWidget* createContent() override;

  GuiCore*      core;
  Config*       cfg;
  ValueManager* vm;
  QAction*      action;

private:
  QString       uiFileName;
  bool          addScrollArea;
  friend class PluginPageFactory;
  };
#endif // ABSCENTERWIDGET_H
