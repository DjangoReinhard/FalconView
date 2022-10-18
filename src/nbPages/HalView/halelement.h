/* 
 * **************************************************************************
 * 
 *  file:       halelement.h
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    23.1.2022 by Django Reinhard
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
#ifndef HALELEMENT_H
#define HALELEMENT_H
#include <QObject>


class HalElement : public QObject
{
  Q_OBJECT
public:
  explicit HalElement(HalElement* parent = nullptr);
  virtual ~HalElement();

  void             appendChild(HalElement* child);
  HalElement*      child(int row);
  int              childCount() const;
  int              childNumber();
//  int              columnCount() const;
  virtual QVariant data(int column) const;
  virtual int      next() const = 0;
  void             setData(int column, const QVariant& value);

protected:
  QVector<HalElement*> children;
  QString              name;
  void*                p;
  };
#endif // HALELEMENT_H
