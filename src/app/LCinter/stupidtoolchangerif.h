/* 
 * **************************************************************************
 * 
 *  file:       stupidtoolchangerif.h
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
#ifndef STUPIDTOOLCHANGERIF_H
#define STUPIDTOOLCHANGERIF_H
#include <QDebug>


/**
 * @brief The StupidToolChangerIF class - dumb model of a tool changer as required by lc
 */
class StupidToolChangerIF
{
public:
  StupidToolChangerIF();

  int  slot4ToolInSpindle() const  {
//       qDebug() << "CHANGER: return slot of tool in spindle #" << actualSlot;

       return actualSlot;
       }
  int  nextTool() const      {
//       qDebug() << "CHANGER: return tool number of next tool #" << nextToolNum;

       return nextToolNum;
       }
  void selectNextTool(int toolNum) {
//       qDebug() << "CHANGER: SET tool number of next tool #" << toolNum;
       nextToolNum = toolNum;
       }
  void setCurrentTool(int slot)    {
//       qDebug() << "CHANGER: SET slot for tool in spindle #" << slot;
       actualSlot = slot;
       }

private:
  int   actualSlot;
  int   nextToolNum;
  };
#endif // STUPIDTOOLCHANGERIF_H
