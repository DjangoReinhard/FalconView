/* 
 * **************************************************************************
 * 
 *  file:       HHelixCurveAdaptor.cpp
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
#include <HHelixCurveAdaptor.h>


HHelixCurveAdaptor::HHelixCurveAdaptor(const Geom_HelixData& d)
 : myAdaptor(d) {
  }


HHelixCurveAdaptor::HHelixCurveAdaptor(const std::shared_ptr<HelixCurveAdaptor::Evaluator>& theEvaluator
                                                       , Standard_Real theMin
                                                       , Standard_Real theMax)
 : myAdaptor(theEvaluator, theMin, theMax) {
  }

double HHelixCurveAdaptor::FirstParameter() const { return myAdaptor.FirstParameter(); }
double HHelixCurveAdaptor::LastParameter()  const { return myAdaptor.LastParameter(); }

GeomAbs_Shape HHelixCurveAdaptor::Continuity() const { return myAdaptor.Continuity(); }
Standard_Integer HHelixCurveAdaptor::NbIntervals(const GeomAbs_Shape S) __CADEX_ADAPTOR3D_CURVE_CONST { return myAdaptor.NbIntervals(S); }
void HHelixCurveAdaptor::Intervals(TColStd_Array1OfReal& T, const GeomAbs_Shape S) __CADEX_ADAPTOR3D_CURVE_CONST { return myAdaptor.Intervals(T, S); }
Handle(Adaptor3d_Curve) HHelixCurveAdaptor::Trim(const double First
                                   , const double Last
                                   , const double Tol) const { return myAdaptor.Trim(First, Last, Tol); }

Standard_Boolean HHelixCurveAdaptor::IsClosed() const { return myAdaptor.IsClosed(); }
Standard_Boolean HHelixCurveAdaptor::IsPeriodic() const { return myAdaptor.IsPeriodic(); }

gp_Pnt HHelixCurveAdaptor::Value(const double U)const { return myAdaptor.Value(U); }
void HHelixCurveAdaptor::D0(const double U, gp_Pnt& P)const { return myAdaptor.D0(U, P); }
void HHelixCurveAdaptor::D1(const double U, gp_Pnt& P, gp_Vec& V)const { return myAdaptor.D1(U, P, V); }
void HHelixCurveAdaptor::D2(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2)const { return myAdaptor.D2(U, P, V1, V2); }
void HHelixCurveAdaptor::D3(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2, gp_Vec& V3)const { return myAdaptor.D3(U, P, V1, V2, V3); }
gp_Vec HHelixCurveAdaptor::DN(const double U, const Standard_Integer N)const { return myAdaptor.DN(U, N); }
double HHelixCurveAdaptor::Resolution(const double R3d)const { return myAdaptor.Resolution(R3d); }
GeomAbs_CurveType HHelixCurveAdaptor::GetType()const { return myAdaptor.GetType(); }



IMPLEMENT_STANDARD_HANDLE(HHelixCurveAdaptor, Adaptor3d_Curve)
IMPLEMENT_STANDARD_RTTIEXT(HHelixCurveAdaptor, Adaptor3d_Curve)
