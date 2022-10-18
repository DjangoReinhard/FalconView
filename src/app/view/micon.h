/* 
 * **************************************************************************
 * 
 *  file:       micon.h
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
#ifndef MICON_H
#define MICON_H
#include <QIcon>


class MIcon : public QIcon
{
public:
  MIcon(const QString& stdFileName, const QString& selFileName);
  MIcon(const QString& normalFile, const QString& activeFile, const QString& selectedFile);
  static void setDisabledFileName(const QString& fileName);

protected:
  static QString disabledFileName;
  };
#endif // MICON_H
