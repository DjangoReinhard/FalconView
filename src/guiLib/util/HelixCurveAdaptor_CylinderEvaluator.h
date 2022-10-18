/* 
 * **************************************************************************
 * 
 *  file:       HelixCurveAdaptor_CylinderEvaluator.h
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
#ifndef HELIXCURVEADAPTOR_CYLINDEREVALUATOR_H
#define HELIXCURVEADAPTOR_CYLINDEREVALUATOR_H
#include <HelixCurveAdaptor.h>
#include <HelixCurveAdaptor_p.h>
#include <gp_Pnt.hxx>
#include <Geom_HelixData.h>


/*!
 * \class ACISAlgo_HelixCurveAdaptor_CylinderEvaluator
 * \brief Evaluates a helix lying on a cylinder.
 */
class HelixCurveAdaptor_CylinderEvaluator : public HelixCurveAdaptor::Evaluator
{
public:
  HelixCurveAdaptor_CylinderEvaluator(const Geom_HelixData& theData);

  virtual void D0(double U, gp_Pnt& P) const override;
  virtual void D1(double U, gp_Pnt& P, gp_Vec& V) const override;
  virtual void D2(double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const override;
  virtual void D3(double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2, gp_Vec& V3) const override;
  virtual gp_Vec DN(double U, int N) const override;
  };

#endif
