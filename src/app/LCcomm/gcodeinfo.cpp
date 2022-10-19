/* 
 * **************************************************************************
 * 
 *  file:       gcodeinfo.cpp
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    30.1.2022 by Django Reinhard
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
#include <gcodeinfo.h>
#include <guicore.h>
#include <QString>
#include <QDebug>


GCodeInfo::GCodeInfo() {
  vm.setValue("fileName", " ");
  vm.setValue("curLine", -1);
  }


void GCodeInfo::update(volatile const int* activeGCodes
                     , volatile const int* activeMCodes
                     , volatile const char* fileName
                     , volatile int curLine) {
  int mx = GuiCore().activeGCodes();

  for (int i=1; i < mx; ++i) {
      QString k = QString("GC%1").arg(i);
      QString v = " ";

      if (activeGCodes[i] >= 0) {
         double dv = (double)activeGCodes[i] / 10.0;

         v = QString("G%1").arg(dv, 0, 'F', activeGCodes[i] % 10 ? 1 : 0);
         }
//      qDebug() << "< active GCode(" << i << "):" << k << "\t" << v << "\traw:" << activeGCodes[i];
      vm.setValue(k, v);
      }
  mx = GuiCore().activeMCodes();

  for (int i=1; i < mx; ++i) {
      QString k = QString("MC%1").arg(i);
      QString v = " ";

      if (activeMCodes[i] >= 0) {
         double dv = (double)activeMCodes[i];

         v = QString("M%1").arg(dv, 0, 'F', 0);
         }
//      qDebug() << "> active MCode(" << i << "):" << k << "\t" << v << "\traw:" << activeMCodes[i];
      vm.setValue(k, v);
      }
  vm.setValue("fileName", QString((const char*)fileName));
  vm.setValue("curLine", curLine + 1);
  }
