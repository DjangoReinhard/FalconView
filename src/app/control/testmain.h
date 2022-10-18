/* 
 * **************************************************************************
 * 
 *  file:       testmain.h
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
#ifndef TESTMAIN_H
#define TESTMAIN_H
#include <QMainWindow>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class TestMain : public QMainWindow
{
  Q_OBJECT
public:
  explicit TestMain(QWidget *parent = nullptr);
  virtual ~TestMain() = default;

  void initialize();
  void checkPlugins();
  void loadPlugins();
  void testPlugin();
  void pluginsAbout();

private:
  Ui::MainWindow* ui           = nullptr;
  QAction*        aboutPlugins = nullptr;
  QStringList     pluginFileNames;
  QDir            pluginsDir;
  };
#endif // TESTMAIN_H
