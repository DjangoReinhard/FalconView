/* 
 * **************************************************************************
 * 
 *  file:       GCodeViewerInterface.h
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
#ifndef GCODEVIEWERINTERFACE_H
#define GCODEVIEWERINTERFACE_H
#include <CenterPageInterface.h>


class GCodeViewerInterface
{
public:
  virtual ~GCodeViewerInterface() = default;

  virtual QString currentRow() const = 0;
  virtual long    curLine() const    = 0;
  };

QT_BEGIN_NAMESPACE
#define GCodeViewerInterface_iid "de.schwarzrot.FalconView.GCodeViewer/0.1"
Q_DECLARE_INTERFACE(GCodeViewerInterface, GCodeViewerInterface_iid)
QT_END_NAMESPACE

#endif // GCODEVIEWERINTERFACE_H
