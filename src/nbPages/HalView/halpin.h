/* 
 * **************************************************************************
 * 
 *  file:       halpin.h
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
#ifndef HALPIN_H
#define HALPIN_H
#include "halelement.h"

class HalSignal;


class HalPin : public HalElement
{
public:
  explicit HalPin(int pin, HalElement*  parent = nullptr);
  virtual ~HalPin();

  virtual QVariant data(int column) const override;
  virtual int next() const override;
  virtual int owner() const;

protected:
  QString typeName(int type) const;
  QString dirName(int dir) const;
  double  value() const;

private:
  HalSignal* sig;
  };
#endif // HALPIN_H
