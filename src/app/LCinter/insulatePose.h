/* 
 * **************************************************************************
 * 
 *  file:       insulatePose.h
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
#ifndef INSULATEPOSE_H
#define INSULATEPOSE_H

#ifdef toCart
#  undef toCart
#endif
#ifdef toCyl
#  undef toCyl
#endif
#ifdef toSph
#  undef toSph
#endif
#ifdef toQuat
#  undef toQuat
#endif
#ifdef toRot
#  undef toRot
#endif
#ifdef toMat
#  undef toMat
#endif
#ifdef toEulerZyz
#  undef toEulerZyz
#endif
#ifdef toEulerZyx
#  undef toEulerZyx
#endif
#ifdef toRpy
#  undef toRpy
#endif
#ifdef toPose
#  undef toPose
#endif
#ifdef toHom
#  undef toHom
#endif
#ifdef toLine
#  undef toLine
#endif
#ifdef toCircle
#  undef toCircle
#endif

#endif // INSULATEPOSE_H
