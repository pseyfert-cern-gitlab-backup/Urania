// Include files 

#include "RooInterModel.h"
#include "TIterator.h"
#include "RooAbsArg.h"
#include "TF1.h"
#include "TPad.h"
#include "TMath.h"
#include "Math/WrappedTF1.h"
#include "Math/GSLIntegrator.h"
#include "PhaseSpace.h"
#include <cmath>
#include "TH1.h"
#include "TLatex.h"
#include "pdg.hpp"
#include "FF.cc"

ClassImp(RooInterModel)

//-----------------------------------------------------------------------------
// Implementation file for class : RooInterModel
//
// 2013-04-22 : Thomas Blake
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================

RooInterModel::RooInterModel( const char *name, 
                              const char *title,
                              RooAbsReal& q, 
                              RooAbsReal& p1,
                              RooAbsReal& frac_VA,
                              const RooArgList& mean, 
                              const RooArgList& width,
                              const RooArgList& phase,
                              const RooArgList& scale ) : 
  RooAbsPdf(name,title),
  citableFF(false),
  q_       ("q","m_{mumu}",this,q),
  p1_      ("p1","p1",this,p1),
  frac_VA_ ("frac_VA","frac_VA",this,frac_VA),
  mean_    ("meancoeff" ,"mean coeff" ,this),
  width_   ("widthcoeff","width coeff",this),
  phase_   ("phasecoeff","phase coeff",this),
  scale_   ("scalecoeff","scale coeff",this),
  psp_     ( 5279., 105.658, 105.658, 493.68, 1 ) {

  assert( ( mean_.getSize() == width_.getSize()) && 
          ( mean_.getSize() == phase_.getSize()) && 
          ( mean_.getSize() == scale_.getSize()) );
  
  TIterator* iterm =  mean.createIterator() ;
  TIterator* iterw = width.createIterator() ;
  TIterator* iterp = phase.createIterator() ;
  TIterator* iters = scale.createIterator() ;
    
  RooAbsArg* coef;
  
  while((coef = (RooAbsArg*) iterm->Next())) {  mean_.add( *coef ); };
  while((coef = (RooAbsArg*) iterw->Next())) { width_.add( *coef ); };
  while((coef = (RooAbsArg*) iterp->Next())) { phase_.add( *coef ); };
  while((coef = (RooAbsArg*) iters->Next())) { scale_.add( *coef ); };
 
  delete iterm;
  delete iterw;
  delete iterp;
  
} ;

RooInterModel::RooInterModel( const RooInterModel& other, 
                              const char* name ) : 
  RooAbsPdf(other,name), 
  citableFF (other.citableFF),
  q_       ("q",this,other.q_), 
  p1_      ("p1",this,other.p1_),
  frac_VA_ ("frac_VA",this,other.frac_VA_),
  mean_    ("mean",this,other.mean_),
  width_   ("width",this,other.width_),
  phase_   ("radius", this, other.phase_),
  scale_   ("radius", this, other.scale_),
  psp_     (other.psp_ ) {} ;

//=============================================================================
// Destructor
//=============================================================================

RooInterModel::~RooInterModel() {} 

//=============================================================================


std::complex<double> RooInterModel::bw( const Double_t q, const Double_t mean, const Double_t gamma ) const 
{
  Double_t cotphi =  ( mean * mean - q * q ) /  ( mean * gamma ) ;
   //std::cout << cotphi << std::endl;
  static const std::complex<double> i( 0 , 1 );

  std::complex<double> amp = 1./( cotphi - i ); 

  return amp;  
}

std::complex<double> RooInterModel::rotate( const Double_t arg ) const 
{
  return std::complex<double>( cos(arg), sin(arg));
}

std::complex<double> RooInterModel::nonres() const 
{


  if ( q_ < psp_.low() || q_ > psp_.upp() ) {
    return std::complex<double>(0.,0.);
  }
  


    FormFactor formfactor;
    if (citableFF)
  {
    formfactor.model(2);
  }
    double ff = formfactor(q_,p1_);



  Double_t tri  = psp_.triangle( q_*q_)/std::pow( psp_.MM() , 4 );
  
  return std::complex<double>( std::sqrt(q_/psp_.MM())*ff*std::pow( tri, 0.75 ), 0. );
}


Double_t RooInterModel::eff(Double_t q) const
{
  double kappa = 42.0;
  const double deltam = 5279-494;
  // std::cout << _kappa << std::endl;
  double denom = 1+ kappa*(deltam-q)/deltam;
  return (1.0-1.0/denom);  
}

Double_t RooInterModel::evaluate() const 
{
  std::complex< double > amp = nonres();
  std::complex< double > amp_axial = nonres();




  for ( int i = 0; i < mean_.getSize(); ++i ){
 
    Double_t mval = ((RooAbsReal&)mean_[i] ).getVal();
    Double_t wval = ((RooAbsReal&)width_[i]).getVal();
    Double_t pval = ((RooAbsReal&)phase_[i]).getVal();
    Double_t sval = ((RooAbsReal&)scale_[i]).getVal();
    
    std::complex< double > bwi = bw( q_,mval,wval );
    std::complex< double > phi = rotate( pval );
    
    amp = amp + ( sval*bwi*phi*nonres() ) ;
  }
  return eff(q_)*(std::norm( amp )+frac_VA_*std::norm(amp_axial));
}
