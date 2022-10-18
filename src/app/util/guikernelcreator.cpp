/* 
 * **************************************************************************
 * 
 *  file:       guikernelcreator.cpp
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
#include <guikernelcreator.h>
#include <GuiKernelInterface.h>
#include <guikernel.h>
#include "rs274ngc.hh"


KernelInterface* GuiKernelCreator::kernel(QApplication& app, const QString& appName, const QString& groupID) {
  return new GuiKernel(ACTIVE_G_CODES, ACTIVE_M_CODES, app, appName, groupID);
  }
