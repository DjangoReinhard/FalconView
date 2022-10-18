/* 
 * **************************************************************************
 * 
 *  file:       valuemanager.h
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    9.1.2022 by Django Reinhard
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
#ifndef VALUEMANAGER_H
#define VALUEMANAGER_H
#include <valuemodel.h>
#include <QString>
class AbstractCenterWidget;


class ValueManager
{
public:
  ValueManager();

  ValueModel* getModel(const QString& name, const QVariant& defaultValue = QVariant());
  QVariant    getValue(const QString& name);
  void        setValue(const QString& name, const QVariant& value);
  void        dump();

protected:
  class ValueHolder
  {
    friend class ValueManager;

    ValueHolder();

    void dump();

    QMap<QString, ValueModel*> models;
    };

private:
  ValueManager(void* p);
  static ValueHolder* instance;
  friend class AbstractCenterWidget;
  friend class PluginPageFactory;
  };

#endif // VALUEMANAGER_H
