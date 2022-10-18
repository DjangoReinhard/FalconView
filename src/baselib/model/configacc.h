/* 
 * **************************************************************************
 * 
 *  file:       configacc.h
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
#ifndef CONFIG_H
#define CONFIG_H
#include <valuemanager.h>
#include <QString>
#include <QSettings>
class ConfigManager;
class AbstractCenterWidget;
class QColor;
class QFont;
class QFile;


class Config
{
public:
  // sync with ConfigManager::geToString(int i) !
  enum GuiElem {
    AppDefault
  , ActCodes
  , CurSeg
  , DroAbs
  , DroDtg
  , DroRel
  , DroTitle
  , EdLinNum
  , Feed
  , Filename
  , GCode
  , Speed
  , ToolDesc
  , ToolNum
  , ToolNext
  , LineHL
  , FixPrompt
  , FixTitle
  , FixDisabledTitle
  , FixEdit
  , RapidMove
  , WorkMove
  , OldSeg
  , WorkPiece
  , WorkLimit
  , LastKey
    };

  explicit Config();
  QColor   getBackground(GuiElem key) const;
  QColor   getForeground(GuiElem key) const;
  QFont    getFont(GuiElem key) const;
  void     beginGroup(const QString& name);
  void     endGroup();
  void     setBackground(GuiElem key, const QColor& color);
  void     setForeground(GuiElem key, const QColor& color);
  void     setFont(GuiElem key, const QFont& font);
  QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const;
  void     setValue(const QString& key, const QVariant& value);
  QString  nameOf(GuiElem key) const;
  int      numGuiElements() const { return LastKey; }

private:
  explicit Config(void* p);
  static ConfigManager* cfg;
  friend class AbstractCenterWidget;
  friend class PluginPageFactory;
  };
#endif // CONFIG_H
