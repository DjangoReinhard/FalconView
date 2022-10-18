/* 
 * **************************************************************************
 * 
 *  file:       pos9.cpp
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
#include <pos9.h>
//#include <canon.hh>


Pos9::Pos9(QObject *parent)
 : QObject(parent)
 , x(0)
 , y(0)
 , z(0)
 , a(0)
 , b(0)
 , c(0)
 , u(0)
 , v(0)
 , w(0) {
  }


Pos9::Pos9(double x, double y, double z, double a, double b, double c, double u, double v, double w)
 : QObject(nullptr)
 , x(x)
 , y(y)
 , z(z)
 , a(a)
 , b(b)
 , c(c)
 , u(u)
 , v(v)
 , w(w) {
  }


Pos9::Pos9(const CANON_POSITION& other)
 : QObject(nullptr)
// , x(other.x)
// , y(other.y)
// , z(other.z)
// , a(other.a)
// , b(other.b)
// , c(other.c)
// , u(other.u)
// , v(other.v)
// , w(other.w)
  {
  }


Pos9::Pos9(const Pos9& other)
 : QObject(other.parent())
 , x(other.x)
 , y(other.y)
 , z(other.z)
 , a(other.a)
 , b(other.b)
 , c(other.c)
 , u(other.u)
 , v(other.v)
 , w(other.w) {
  }


Pos9& Pos9::operator=(const Pos9 &other) {
  setParent(other.parent());
  x = other.x;
  y = other.y;
  z = other.z;
  a = other.a;
  b = other.b;
  c = other.c;
  u = other.u;
  v = other.v;
  w = other.w;

  return *this;
  }


CANON_POSITION* Pos9::toCanon() {
  CANON_POSITION* rv = nullptr; //new CANON_POSITION();

//  rv->x = x;
//  rv->y = y;
//  rv->z = z;
//  rv->a = a;
//  rv->b = b;
//  rv->c = c;
//  rv->u = u;
//  rv->v = v;
//  rv->w = w;

  return rv;
  }
