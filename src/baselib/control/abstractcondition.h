/* 
 * **************************************************************************
 * 
 *  file:       abstractcondition.h
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
#ifndef ABSTRACTCONDITION_H
#define ABSTRACTCONDITION_H
#include <QObject>
#include <QVariant>
class ValueModel;


class AbstractCondition : public QObject
{
  Q_OBJECT
public:
  explicit AbstractCondition(ValueModel* model, const QVariant& value, QObject *parent = nullptr);
  virtual ~AbstractCondition();

  virtual bool result() const;
  QString name() const;

public slots:
  virtual bool eval() = 0;
  virtual void update();

signals:
  void conditionChanged(bool result);

protected:
  ValueModel* model() { return m; }
  QVariant    value() { return v; }

private:
  ValueModel* m;
  QVariant    v;
  bool        met;
  bool        initialized;
  };

#endif // ABSTRACTCONDITION_H
