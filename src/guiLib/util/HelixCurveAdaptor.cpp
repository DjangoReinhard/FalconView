/* 
 * **************************************************************************
 * 
 *  file:       HelixCurveAdaptor.cpp
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
#include <HelixCurveAdaptor.h>
#include <HelixCurveAdaptor_CylinderEvaluator.h>
#include <Standard_Assert.hxx>
/*********************************************************************************************/


HelixCurveAdaptor::HelixCurveAdaptor(const Geom_HelixData& theData)
 : myMin(theData.RangeMin())
 , myMax(theData.RangeMax()) {
  if (std::fabs(theData.Taper()) < Precision::Confusion()) {
     //cylinder
     myEvaluator.reset(new HelixCurveAdaptor_CylinderEvaluator(theData));
     }
  }


/*! Used when trimming*/
HelixCurveAdaptor::HelixCurveAdaptor(const std::shared_ptr<Evaluator>& theEvaluator, double theMin, double theMax)
 : myEvaluator(theEvaluator)
 , myMin(theMin)
 , myMax(theMax) {
  Standard_ASSERT_RAISE(myEvaluator->Data().RangeMin() <= theMin, "invalid value >theMin<");
  Standard_ASSERT_RAISE(myEvaluator->Data().RangeMax() >= theMax, "invalid value >theMax<");
  }


double HelixCurveAdaptor::FirstParameter() const {
  return myMin;
  }


double HelixCurveAdaptor::LastParameter() const {
  return myMax;
  }


GeomAbs_Shape HelixCurveAdaptor::Continuity() const {
  return GeomAbs_CN;
  }


Standard_Integer HelixCurveAdaptor::NbIntervals (const GeomAbs_Shape /*S*/) __CADEX_ADAPTOR3D_CURVE_CONST {
  return 1;
  }


void HelixCurveAdaptor::Intervals (TColStd_Array1OfReal& T, const GeomAbs_Shape /*S*/) __CADEX_ADAPTOR3D_CURVE_CONST {
  T (T.Lower()) = FirstParameter();
  T (T.Upper()) = LastParameter();
  }


Handle(Adaptor3d_Curve) HelixCurveAdaptor::Trim(const double First, const double Last, const double /*Tol*/) const {
  return new HHelixCurveAdaptor(myEvaluator, First, Last);
  }


Standard_Boolean HelixCurveAdaptor::IsClosed() const {
  return Standard_False;
  }


Standard_Boolean HelixCurveAdaptor::IsPeriodic() const {
  return Standard_False;
  }


gp_Pnt HelixCurveAdaptor::Value(const double U) const {
  gp_Pnt aP;

  D0(U, aP);

  return aP;
  }


void HelixCurveAdaptor::D0(const double U, gp_Pnt& P) const {
  myEvaluator->D0(U, P);
  }


void HelixCurveAdaptor::D1(const double U, gp_Pnt& P, gp_Vec& V) const {
  myEvaluator->D1(U, P, V);
  }


void HelixCurveAdaptor::D2(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const {
  myEvaluator->D2(U, P, V1, V2);
  }


void HelixCurveAdaptor::D3(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2, gp_Vec& V3) const {
  myEvaluator->D3(U, P, V1, V2, V3);
  }


gp_Vec HelixCurveAdaptor::DN(const double U, const Standard_Integer N) const {
  return myEvaluator->DN(U, N);
  }


double HelixCurveAdaptor::Resolution(const double R3d) const {
  //see GeomAdaptor_Curve::Resolution()
  const auto& aData = myEvaluator->Data();
  double      R     = std::max(aData.XRadius(), aData.YRadius());

  if (R3d < 2 * R) return 2 * ASin(R3d / (2 * R));
  return 2 * M_PI;
  }


GeomAbs_CurveType HelixCurveAdaptor::GetType() const {
  return GeomAbs_OtherCurve;
  }
