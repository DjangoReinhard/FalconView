/* 
 * **************************************************************************
 * 
 *  file:       main.cpp
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    24.1.2022 by Django Reinhard
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
#include <mainwindow.h>
#include <testmain.h>
#include <falconviewdb.h>
#include <guicore.h>
#include <guikernelcreator.h>

#include <QCoreApplication>
#include <QApplication>
#include <QFileInfo>
#include <QStyleFactory>
#include <QTranslator>
#include <QKeySequence>
#include <QDebug>


int main(int argc, char *argv[]) {
  try {
      QApplication a(argc, argv);

      GuiCore::setKernelCreator(new GuiKernelCreator());
      FalconViewDB dbHelper;
      GuiCore      appCore(a, "FalconView", dbHelper);
#ifndef WANT_SHORT_TESTS
      MainWindow* mainWindow = new MainWindow();
#else
      TestMain*   mainWindow = new TestMain();
#endif

      appCore.setMainWindow(mainWindow);
      mainWindow->initialize();
      appCore.checkBE();
      mainWindow->show();
      int rv = a.exec();

      return rv;
      }
  catch (const QString& s) {
      qDebug() << s;
      }
  catch (const std::exception& e) {
      qDebug() << e.what();
      }
  }
