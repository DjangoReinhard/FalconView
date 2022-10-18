/* 
 * **************************************************************************
 * 
 *  file:       configacc.cpp
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
#include <configacc.h>
#include <configmgr.h>
#include <core.h>
#include <KernelInterface.h>
#include <QColor>
#include <QFont>

Config::Config() {
  if (!Config::cfg) Config::cfg = Core().kernel->config();
  assert(Config::cfg);
  }


Config::Config(void* pFromOuterAddressSpace) {
  if (!Config::cfg) Config::cfg = (ConfigManager*)pFromOuterAddressSpace;
  }


QColor Config::getBackground(GuiElem key) const {
  return cfg->getBackground(key);
  }


QColor Config::getForeground(GuiElem key) const {
  return cfg->getForeground(key);
  }


QFont Config::getFont(GuiElem key) const {
  return cfg->getFont(key);
  }


void Config::beginGroup(const QString &name) {
  cfg->settings.beginGroup(name);
  }


void Config::endGroup() {
  cfg->settings.endGroup();
  }


QVariant Config::value(const QString& key, const QVariant& defaultValue) const {
  return cfg->value(key, defaultValue);
  }


void Config::setBackground(GuiElem key, const QColor& color) {
  cfg->setBackground(key, color);
  }


void Config::setForeground(GuiElem key, const QColor& color) {
  cfg->setForeground(key, color);
  }


void Config::setFont(GuiElem key, const QFont& font) {
  cfg->setFont(key, font);
  }


void Config::setValue(const QString& key, const QVariant& value) {
  cfg->setValue(key, value);
  }


QString Config::nameOf(GuiElem key) const {
  return cfg->geToString(key);
  }

ConfigManager* Config::cfg = nullptr;
