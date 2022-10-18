/* 
 * **************************************************************************
 * 
 *  file:       Geom_HelixData.cpp
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
#include <Geom_HelixData.h>
#include <HHelixCurveAdaptor.h>
#include <GeomAbs_Shape.hxx>
#include <GeomConvert_ApproxCurve.hxx>


/*!
 * Uses adaptor classes and invokes GeomConvert_ApproxCurve
 * to approximate with a B-Spline.
 * Created B-Spline is polynomial and is of C2-continuity.
 * Returns true if the B-Spline has been successfully created
 * and false otherwise.
 */
bool Geom_HelixData::MakeHelix(const Geom_HelixData& theSource, Handle(Geom_BSplineCurve)& theTarget) {
  Handle(HHelixCurveAdaptor) anAdaptor = new HHelixCurveAdaptor(theSource);
  double           aTol        = Precision::Confusion();
  GeomAbs_Shape    aContinuity = GeomAbs_C2;   /* highest supported continuity */
  int              aMaxSeg     = 10000,        /* max number of spans */
                   aMaxDeg     = 9;            /* max degree, consistent with settings in Algo */

  GeomConvert_ApproxCurve anApprox(anAdaptor
                                 , aTol
                                 , aContinuity
                                 , aMaxSeg
                                 , aMaxDeg);
  if (anApprox.HasResult()) theTarget = anApprox.Curve();
  return !theTarget.IsNull();
  }
