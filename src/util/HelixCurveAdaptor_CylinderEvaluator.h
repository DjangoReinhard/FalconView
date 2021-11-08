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
