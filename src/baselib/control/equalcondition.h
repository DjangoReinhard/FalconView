/* 
 * **************************************************************************
 * 
 *  file:       equalcondition.h
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
#ifndef EQUALCONDITION_H
#define EQUALCONDITION_H
#include <abstractcondition.h>


class EqualCondition : public AbstractCondition
{
  Q_OBJECT
public:
  explicit EqualCondition(ValueModel* model, const QVariant& value, QObject *parent = nullptr);

public slots:
  virtual bool eval() override;
  };
#endif // EQUALCONDITION_H
