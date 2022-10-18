/* 
 * **************************************************************************
 * 
 *  file:       gcodeinfo.h
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
#ifndef GCODEINFO_H
#define GCODEINFO_H
#include <valuemanager.h>
class QString;


class GCodeInfo
{
public:
  GCodeInfo();

  void update(volatile const int* activeGCodes
            , volatile const int* activeMCodes
            , volatile const char* fileName
            , int  curLine);

protected:
  ValueManager vm;
  };
#endif // GCODEINFO_H
