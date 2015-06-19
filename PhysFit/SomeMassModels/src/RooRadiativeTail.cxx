/*****************************************************************************
 * Project: Erasmus                                                           *
 * Package: SomeMassModels                                                    *
 *    File: $Id: RooRadiativeTail.cxx,v 1.13 2007/07/12 20:30:49 asarti Exp $
 * Authors:                                                                  *
 *           Alessio Sarti          alessio.sarti@lnf.infn.it
 * Purpose:
 * Description of the B->hh exclusive peak
 *                                                                           *
 *****************************************************************************/



#include "RooFit.h"

#include <math.h>

#include "RooRadiativeTail.h"
#include "RooAbsReal.h"
#include "RooRealVar.h"
#include "RooRandom.h"
#include "RooMath.h"

ClassImp(RooRadiativeTail)


//_____________________________________________________________________________
RooRadiativeTail::RooRadiativeTail(const char *name, const char *title,
			 RooAbsReal& _mass, RooAbsReal& _slope,
			 RooAbsReal& _mean, RooAbsReal& _sigma) :
  RooAbsPdf(name,title),
  mass("mass","Observable",this,_mass),
  slope("slope","Slope",this,_slope),
  mean("mean","Mean",this,_mean),
  sigma("sigma","Sigma",this,_sigma)
{
}



//_____________________________________________________________________________
RooRadiativeTail::RooRadiativeTail(const RooRadiativeTail& other, const char* name) : 
  RooAbsPdf(other,name), mass("mass",this,other.mass), slope("slope",this,other.slope),
  mean("mean",this,other.mean), sigma("sigma",this,other.sigma)
{
}



//_____________________________________________________________________________
Double_t RooRadiativeTail::evaluate() const
{

  Double_t damp = 1/1.4142135623730951/sigma;
  Double_t ret = exp(slope*(mass-mean))*(1-RooMath::erf(damp*(mass-mean+slope*sigma*sigma))) ;

  return ret ;
}



//_____________________________________________________________________________
Int_t RooRadiativeTail::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const 
{
  if (matchArgs(allVars,analVars,mass)) return 1 ;
  return 0 ;
}



//_____________________________________________________________________________
Double_t RooRadiativeTail::analyticalIntegral(Int_t code, const char* rangeName) const 
{
  assert(code==1) ;

  Double_t damp = 1/1.4142135623730951/sigma;  
  Double_t fact = -1/slope;
  Double_t up = exp(-0.5*sigma*sigma*slope*slope)*RooMath::erf(damp*(mean-mass.max(rangeName)))+ exp(slope*(-mean+mass.max(rangeName)))*(RooMath::erf(damp*(slope*sigma*sigma-mean+mass.max(rangeName)))-1);
  Double_t down = exp(-0.5*sigma*sigma*slope*slope)*RooMath::erf(damp*(mean-mass.min(rangeName)))+ exp(slope*(-mean+mass.min(rangeName)))*(RooMath::erf(damp*(slope*sigma*sigma-mean+mass.min(rangeName)))-1);
  Double_t ret = fact*(up-down);

  return ret ;

}
