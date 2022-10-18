/* 
 * **************************************************************************
 * 
 *  file:       dynaaction.h
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
#ifndef DYNAACTION_H
#define DYNAACTION_H
#include <QAction>
class AbstractCondition;


class DynaAction : public QAction
{
  Q_OBJECT
public:
  explicit DynaAction(const QIcon& disabledIcon, const QIcon& enabledIcon, const QIcon& checkedIcon, const QString& text, AbstractCondition* cEnabled, AbstractCondition* cChecked, QObject *parent = nullptr);

public slots:
  void setEnabled(bool enabled);
  void setChecked(bool checked);

private:
  AbstractCondition* cEnabled;
  AbstractCondition* cChecked;
  QIcon disabledIcon;
  QIcon enabledIcon;
  QIcon checkedIcon;
  };
#endif // DYNAACTION_H
