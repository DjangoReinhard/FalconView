/* 
 * **************************************************************************
 * 
 *  file:       valuemodel.h
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
#ifndef VALUEMODEL_H
#define VALUEMODEL_H
#include <QObject>
#include <QVariant>


class ValueModel : public QObject
{
  Q_OBJECT
public:
  explicit ValueModel(const QString& name, const QVariant& value = 0);

  void     setValue(const QVariant& value);
  QVariant getValue() const { return v; };
  QString  getName()  const { return n; };
  void     dump() const;

signals:
  void valueChanged(const QVariant& newValue);

private:
  QVariant v;
  QString  n;
  };
#endif // VALUEMODEL_H
