/* 
 * **************************************************************************
 * 
 *  file:       fixturemanager.h
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
#ifndef FIXTUREMANAGER_H
#define FIXTUREMANAGER_H
#include <abscenterwidget.h>

QT_BEGIN_NAMESPACE
class FixtureEdit;
class AxisMask;
QT_END_NAMESPACE


class FixtureManager : public AbstractCenterWidget
{
  Q_OBJECT
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "ViewPluginInterface_iid" FILE "fixtureManager.json")
#endif
public:
  FixtureManager(QWidget* parent = nullptr);

  virtual void connectSignals() override;
  virtual void updateStyles()   override;
  void activateEditor(int index);

protected:
  virtual void keyPressEvent(QKeyEvent* event) override;
  virtual void showEvent(QShowEvent *event) override;
  virtual QWidget* createContent() override;

private:
  QWidget*  client;
  QFont     cFonts[4];
  QString   cStyle[4];
  AxisMask* axisMask;
  };
#endif // FIXTUREMANAGER_H
