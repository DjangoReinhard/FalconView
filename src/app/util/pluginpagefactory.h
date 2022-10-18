/* 
 * **************************************************************************
 * 
 *  file:       pluginpagefactory.h
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    19.1.2022 by Django Reinhard
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
#ifndef PLUGINPAGEFACTORY_H
#define PLUGINPAGEFACTORY_H
class AbstractCenterWidget;
class GuiCore;
class AxisMask;
class Config;
class ValueManager;
class QString;


class PluginPageFactory
{
public:
  explicit PluginPageFactory();
  virtual ~PluginPageFactory();

  AbstractCenterWidget* createDockable(const   QString& name, bool flag = false);
  AbstractCenterWidget* createCenterPage(const QString& name);
  AbstractCenterWidget* createNotebookPage(const QString& name);

private:
  GuiCore*      core;
  Config*       cfg;
  ValueManager* vm;
  };
#endif // PLUGINPAGEFACTORY_H
