/* 
 * **************************************************************************
 * 
 *  file:       HelixCurveAdaptor_CylinderEvaluator.cpp
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
#include <HelixCurveAdaptor_CylinderEvaluator.h>


HelixCurveAdaptor_CylinderEvaluator::HelixCurveAdaptor_CylinderEvaluator(const Geom_HelixData& theData)
 : HelixCurveAdaptor::Evaluator(theData) {
  myVCoef = theData.Pitch() * theData.ScaleFactor() / (2 * M_PI);
  }


void HelixCurveAdaptor_CylinderEvaluator::D0(double U, gp_Pnt& P) const {
  double v    = VParameter(U);
  double Rx   = myData.XRadius();
  double Ry   = myData.YRadius();
  double sinU = sin(U);
  double cosU = cos(U);

  P = Rx * cosU * XDir() + Ry * sinU * YDir() + v * ZDir() + Loc();
  }


void HelixCurveAdaptor_CylinderEvaluator::D1(double U, gp_Pnt& P, gp_Vec& V) const {
  double v    = VParameter (U);
  double Rx   = myData.XRadius();
  double Ry   = myData.YRadius();
  double sinU = sin (U);
  double cosU = cos (U);

  P = Rx * cosU * XDir() + Ry * sinU * YDir() + v * ZDir() + Loc();

  double k = myVCoef;

  V = -Rx * sinU * XDir() + Ry * cosU * YDir() + k * ZDir();
  }


void HelixCurveAdaptor_CylinderEvaluator::D2(double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const {
  double v    = VParameter (U);
  double Rx   = myData.XRadius();
  double Ry   = myData.YRadius();
  double sinU = sin (U);
  double cosU = cos (U);

  P = Rx * cosU * XDir() + Ry * sinU * YDir() + v * ZDir() + Loc();

  double k = myVCoef;

  V1 = -Rx * sinU * XDir() + Ry * cosU * YDir() + k * ZDir();
  V2 = -Rx * cosU * XDir() - Ry * sinU * YDir();
  }


void HelixCurveAdaptor_CylinderEvaluator::D3(double , gp_Pnt& , gp_Vec& , gp_Vec& , gp_Vec& ) const {
  Standard_ASSERT_RAISE(0 != 1, "invalid call! - D3 unsupported on Helix");
  }


gp_Vec HelixCurveAdaptor_CylinderEvaluator::DN(double , const Standard_Integer ) const {
  Standard_ASSERT_RAISE(0 != 1, "invalid call! - DN unsupported on Helix");
  return gp_Vec();
  }
