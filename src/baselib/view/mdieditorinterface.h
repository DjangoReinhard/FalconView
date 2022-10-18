/* 
 * **************************************************************************
 * 
 *  file:       mdieditorinterface.h
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
#ifndef MDIEDITORINTERFACE_H
#define MDIEDITORINTERFACE_H
#include <CenterPageInterface.h>


class MDIEditorInterface : public CenterPageInterface
{
public:
  virtual ~MDIEditorInterface() = default;

  virtual void    append(const QString& command) = 0;
  virtual QString command() const                = 0;
  };

QT_BEGIN_NAMESPACE
#define MDIEditorInterface_iid "de.schwarzrot.FalconView.MDIEditor/0.1"
Q_DECLARE_INTERFACE(MDIEditorInterface, MDIEditorInterface_iid)
QT_END_NAMESPACE

#endif // MDIEDITORINTERFACE_H
