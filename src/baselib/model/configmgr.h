/* 
 * **************************************************************************
 * 
 *  file:       configmgr.h
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
#ifndef CONFIGMGR_H
#define CONFIGMGR_H
#include <QSettings>
#include <QString>
#include <QColor>
#include <QFont>
#include <valuemanager.h>
class ToolEntry;

class ConfigManager
{
public:
  ConfigManager(const QString& appName = "Config-Manager", const QString& group = "SRD");

  QColor       getBackground(int index);
  QColor       getForeground(int index);
  QFont        getFont(int index);
  void         setBackground(int index, const QColor& color);
  void         setForeground(int index, const QColor& color);
  void         setFont(int index, const QFont& font);
  QVariant     value(const QString& key, const QVariant& defaultValue = QVariant()) const;
  void         setValue(const QString& key, const QVariant& value);
  QString      geToString(int i);
  void         initialize();

  QString      iniFileName;
  ValueManager vm;
  QSettings    settings;

private:
  const int          lastIndex;
//  static const char* guiElemNames[];
  };

#endif // CONFIGMGR_H
