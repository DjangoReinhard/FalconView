/* 
 * **************************************************************************
 * 
 *  file:       configmgr.cpp
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
#include <configmgr.h>
#include <configacc.h>
#include <core.h>
#include <QVariant>
#include <QColor>
#include <QFont>
#include <QFile>
#include <QDir>
#include <QDebug>


ConfigManager::ConfigManager(const QString& appName, const QString& group)
 : settings(QSettings::UserScope, group, appName)
 , lastIndex(static_cast<Config::GuiElem>(Config::GuiElem::LastKey)) {
  initialize();
  }


void ConfigManager::initialize() {
  for (int i=0; i < lastIndex; ++i) {
      QString  k = QString("cfgBg") + geToString(i);
      QVariant v = settings.value(k, QColor(Qt::white));

      vm.setValue(k, v);
      k = QString("cfgFg") + geToString(i);
      v = settings.value(k, QColor(Qt::black));
      vm.setValue(k, v);
      k = QString("cfgF") + geToString(i);
      v = settings.value(k, QFont("Hack", 12));
      vm.setValue(k, v);
      }
  }


QColor ConfigManager::getBackground(int index) {
  if (index < 0 || index >= lastIndex)  return QColor(Qt::white);
  return vm.getValue("cfgBg" + geToString(index)).value<QColor>();
  }


QColor ConfigManager::getForeground(int index) {
  if (index < 0 || index >= lastIndex)  return QColor(Qt::black);
  return vm.getValue("cfgFg" + geToString(index)).value<QColor>();
  }


QFont ConfigManager::getFont(int index) {
  if (index < 0 || index >= lastIndex)  return QFont();
  return vm.getValue("cfgF" + geToString(index)).value<QFont>();
  }


QVariant ConfigManager::value(const QString& key, const QVariant& defaultValue) const {
//  qDebug() << "CfgMgr::value(" << key << "\tdefault:" << defaultValue;
  return settings.value(key, defaultValue);
  }


void ConfigManager::setBackground(int index, const QColor& color) {
  if (index < 0 || index >= lastIndex)  return;
  QString key = QString("cfgBg") + geToString(index);

  vm.setValue(key, color);
  settings.setValue(key, color);
  }


void ConfigManager::setForeground(int index, const QColor& color) {
  if (index < 0 || index >= lastIndex)  return;
  QString key = QString("cfgFg") + geToString(index);

  vm.setValue(key, color);
  settings.setValue(key, color);
  }


void ConfigManager::setFont(int index, const QFont& font) {
  if (index < 0 || index >= lastIndex)  return;
  QString key = QString("cfgF") + geToString(index);

  vm.setValue(key, font);
  settings.setValue(key, font);
  }


void ConfigManager::setValue(const QString& key, const QVariant& value) {
  settings.setValue(key, value);
  }

#define asString( name ) # name
// sync with Config::GuiElem
QString ConfigManager::geToString(int i) {
  switch (static_cast<Config::GuiElem>(i)) {
    case Config::GuiElem::AppDefault: return asString(AppDefault);
    case Config::GuiElem::ActCodes:   return asString(ActCodes);
    case Config::GuiElem::CurSeg:     return asString(CurSeg);
    case Config::GuiElem::DroAbs:     return asString(DroAbs);
    case Config::GuiElem::DroDtg:     return asString(DroDtg);
    case Config::GuiElem::DroRel:     return asString(DroRel);
    case Config::GuiElem::DroTitle:   return asString(DroTitle);
    case Config::GuiElem::EdLinNum:   return asString(EdLinNum);
    case Config::GuiElem::Feed:       return asString(Feed);
    case Config::GuiElem::Filename:   return asString(Filename);
    case Config::GuiElem::FixEdit:    return asString(FixEdit);
    case Config::GuiElem::FixPrompt:  return asString(FixPrompt);
    case Config::GuiElem::FixTitle:   return asString(FixTitle);
    case Config::GuiElem::GCode:      return asString(GCode);
    case Config::GuiElem::LineHL:     return asString(LineHL);
    case Config::GuiElem::OldSeg:     return asString(OldSeg);
    case Config::GuiElem::RapidMove:  return asString(RapidMove);
    case Config::GuiElem::Speed:      return asString(Speed);
    case Config::GuiElem::ToolDesc:   return asString(ToolDesc);
    case Config::GuiElem::ToolNext:   return asString(ToolNext);
    case Config::GuiElem::ToolNum:    return asString(ToolNum);
    case Config::GuiElem::WorkLimit:  return asString(WorkLimit);
    case Config::GuiElem::WorkMove:   return asString(WorkMove);
    case Config::GuiElem::WorkPiece:  return asString(WorkPiece);
    case Config::GuiElem::FixDisabledTitle: return asString(FixDisabledTitle);
    default: break;
    }
  return QString();
  }
