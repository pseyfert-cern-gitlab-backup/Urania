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

Double_t eff_forInt(Double_t q)
{
  double kappa = 42.0;
  const double deltam = 5279-494;
  // std::cout << _kappa << std::endl;
  double denom = 1+ kappa*(deltam-q)/deltam;
  return (1.0-1.0/denom);  
}

double phasespace_factorPhys(double m)
{
  PhaseSpace ps(pdg::Bplus_M,pdg::muon_M,pdg::muon_M,pdg::kaon_M,0);
  return ps.twobody(m);
}



std::complex<double> nonres_forInt(double x,double p1_) 
{

  PhaseSpace psp_( 5279., 105.658, 105.658, 493.68, 1 );


  if ( x < psp_.low() || x > psp_.upp() ) {
    return std::complex<double>(0.,0.);
  }
    FormFactor formfactor;
        formfactor.model(2);
    Double_t  ff = formfactor(x,p1_);


  Double_t tri  = psp_.triangle( x*x)/std::pow( psp_.MM() , 4 );
  
  return std::complex<double>( std::sqrt(x/psp_.MM())*ff*std::pow( tri, 0.75 ), 0. );
}

double nonres_forIntNorm( double *x, double* par )
{
  return eff_forInt(*x)*std::norm(nonres_forInt( *x,par[0]));
}

std::complex<double> bw_withPhys( const Double_t m, const Double_t mean, const Double_t gamma, const Double_t p0)
{
  Double_t cotphi =  ( mean * mean - m * m ) /  ( mean * gamma ) ;
  static const std::complex<double> i( 0 , 1 );
  std::complex<double> amp = 1./( cotphi - i );
  amp = amp*nonres_forInt(m,p0);

  return amp;
  
}

double bw_forIntPhys( double *x, double* par )
{
  return eff_forInt(*x)*std::norm(par[2]*bw_withPhys( *x,par[0],par[1],par[3]));
}

std::complex<double> rotate_forInt( const Double_t arg )
{
  return std::complex<double>( cos(arg), sin(arg) );
}


double inteferencePhys(double *x,double *par) 
 { 
  double mean_val = par[0];
  double width_val = par[1];
  double phase_val = par[2];
  double scale_val = par[3];
  double p_val = par[4];

    std::complex<double> a0 = nonres_forInt( *x,p_val ) ;
    std::complex<double> a1 = bw_withPhys( *x,mean_val,width_val,p_val);
    std::complex< double > phi = rotate_forInt( phase_val );
    return std::norm( a0 + phi*scale_val*a1) - std::norm(a1*scale_val) - std::norm(a0);
 }

double inteferenceTwoBWPhys(double *x,double *par) 
 { 
    const double mean_val = par[0];
    const double width_val = par[1];
    const double phase_val = par[2];
    const double scale_val = par[3];
    const double p_val = par[4];
    const double mean2_val = par[5];
    const double width2_val = par[6];
    const double phase2_val = par[7];
    const double scale2_val = par[8];
    std::complex<double> a0 = nonres_forInt( *x,p_val ) ;
    std::complex<double> a1 = bw_withPhys( *x,mean_val,width_val,p_val);
    std::complex<double> a2 = bw_withPhys( *x,mean2_val,width2_val,p_val);
    std::complex< double > phi = rotate_forInt( phase_val );
    std::complex< double > phi2 = rotate_forInt( phase2_val );
    return eff_forInt(*x)*(std::norm( a0 + phi*scale_val*a1 + phi2*scale2_val*a2) - std::norm(a1*scale_val) - std::norm(a2*scale2_val) - std::norm(a0));
 }

double inteferenceThreeBWPhys(double *x,double *par) 
 { 
    const double mean_val = par[0];
    const double width_val = par[1];
    const double phase_val = par[2];
    const double scale_val = par[3];
    const double p_val = par[4];
    const double mean2_val = par[5];
    const double width2_val = par[6];
    const double phase2_val = par[7];
    const double scale2_val = par[8];
    const double mean3_val = par[9];
    const double width3_val = par[10];
    const double phase3_val = par[11];
    const double scale3_val = par[12];
    std::complex<double> a0 = nonres_forInt( *x,p_val ) ;
    std::complex<double> a1 = bw_withPhys( *x,mean_val,width_val,p_val);
    std::complex<double> a2 = bw_withPhys( *x,mean2_val,width2_val,p_val);
    std::complex<double> a3 = bw_withPhys( *x,mean3_val,width3_val,p_val);
    std::complex< double > phi = rotate_forInt( phase_val );
    std::complex< double > phi2 = rotate_forInt( phase2_val );
    std::complex< double > phi3 = rotate_forInt( phase3_val );
    //std::cout << scale2_val << std::endl;
    return eff_forInt(*x)*(std::norm( a0 + phi*scale_val*a1 + phi2*scale2_val*a2 + phi3*scale3_val*a3) - std::norm(a1*scale_val) - std::norm(a2*scale2_val) - std::norm(a3*scale3_val) - std::norm(a0));
 }

double inteferenceFourBWPhys(double *x,double *par) 
 { 
    const double mean_val = par[0];
    const double width_val = par[1];
    const double phase_val = par[2];
    const double scale_val = par[3];
    const double p_val = par[4];
    const double mean2_val = par[5];
    const double width2_val = par[6];
    const double phase2_val = par[7];
    const double scale2_val = par[8];
    const double mean3_val = par[9];
    const double width3_val = par[10];
    const double phase3_val = par[11];
    const double scale3_val = par[12];
    const double mean4_val = par[13];
    const double width4_val = par[14];
    const double phase4_val = par[15];
    const double scale4_val = par[16];
    std::complex<double> a0 = nonres_forInt( *x,p_val ) ;
    std::complex<double> a1 = bw_withPhys( *x,mean_val,width_val,p_val);
    std::complex<double> a2 = bw_withPhys( *x,mean2_val,width2_val,p_val);
    std::complex<double> a3 = bw_withPhys( *x,mean3_val,width3_val,p_val);
    std::complex<double> a4 = bw_withPhys( *x,mean4_val,width4_val,p_val);
    std::complex< double > phi = rotate_forInt( phase_val );
    std::complex< double > phi2 = rotate_forInt( phase2_val );
    std::complex< double > phi3 = rotate_forInt( phase3_val );
    std::complex< double > phi4 = rotate_forInt( phase4_val );
    //std::cout << scale2_val << std::endl;
    return eff_forInt(*x)*(std::norm( a0 + phi*scale_val*a1 + phi2*scale2_val*a2 + phi3*scale3_val*a3 + phi4*scale4_val*a4) - std::norm(a1*scale_val) - std::norm(a2*scale2_val) - std::norm(a3*scale3_val) -std::norm(a4*scale4_val) - std::norm(a0));
 } 

double all(double *x,double *par) 
 { 
    const double mean_val = par[0];
    const double width_val = par[1];
    const double phase_val = par[2];
    const double scale_val = par[3];
    const double p_val = par[4];
    const double mean2_val = par[5];
    const double width2_val = par[6];
    const double phase2_val = par[7];
    const double scale2_val = par[8];
    const double mean3_val = par[9];
    const double width3_val = par[10];
    const double phase3_val = par[11];
    const double scale3_val = par[12];
    const double mean4_val = par[13];
    const double width4_val = par[14];
    const double phase4_val = par[15];
    const double scale4_val = par[16];
    std::complex<double> a0 = nonres_forInt( *x,p_val ) ;
    std::complex<double> a1 = bw_withPhys( *x,mean_val,width_val,p_val);
    std::complex<double> a2 = bw_withPhys( *x,mean2_val,width2_val,p_val);
    std::complex<double> a3 = bw_withPhys( *x,mean3_val,width3_val,p_val);
    std::complex<double> a4 = bw_withPhys( *x,mean4_val,width4_val,p_val);
    std::complex< double > phi = rotate_forInt( phase_val );
    std::complex< double > phi2 = rotate_forInt( phase2_val );
    std::complex< double > phi3 = rotate_forInt( phase3_val );
    std::complex< double > phi4 = rotate_forInt( phase4_val );
    //std::cout << scale2_val << std::endl;
    return eff_forInt(*x)*(std::norm( a0 + phi*scale_val*a1 + phi2*scale2_val*a2 + phi3*scale3_val*a3 + phi4*scale4_val*a4));
 } 



double RooInterModel::numIntegrateInterference(double min, double max,int whichBW)
{
    Double_t mval = ((RooAbsReal&)mean_[whichBW] ).getVal();
    Double_t wval = ((RooAbsReal&)width_[whichBW]).getVal();
    Double_t pval = ((RooAbsReal&)phase_[whichBW]).getVal();
    Double_t sval = ((RooAbsReal&)scale_[whichBW]).getVal();
    inter_comp = new TF1("myfunc_inter",inteferencePhys,min,max,5);
    inter_comp->SetParameters(mval,wval,pval,sval,p1_);
    ROOT::Math::WrappedTF1 wf1(*inter_comp);
    ROOT::Math::GSLIntegrator ig(ROOT::Math::IntegrationOneDim::kADAPTIVE);
    ig.SetFunction(wf1);
    // ig.SetF
    ig.SetRelTolerance(0.001);
    return ig.Integral(min, max);
}

double RooInterModel::numIntegrateInterferenceTwoBW(double min, double max)
{
    Double_t mval = ((RooAbsReal&)mean_[0] ).getVal();
    Double_t wval = ((RooAbsReal&)width_[0]).getVal();
    Double_t pval = ((RooAbsReal&)phase_[0]).getVal();
    Double_t sval = ((RooAbsReal&)scale_[0]).getVal();

    Double_t mval2 = ((RooAbsReal&)mean_[1] ).getVal();
    Double_t wval2 = ((RooAbsReal&)width_[1]).getVal();
    Double_t pval2 = ((RooAbsReal&)phase_[1]).getVal();
    Double_t sval2 = ((RooAbsReal&)scale_[1]).getVal();
  // Double_t arg= x - mean;  
  // return 1. / (arg*arg + 0.25*width*width);

  TF1 f("Inteference function", inteferenceTwoBWPhys, min, max);
      inter_comp = new TF1("myfunc_inter",inteferenceTwoBWPhys,min,max,9);
      inter_comp->SetParameters(mval,wval,pval,sval,p1_,mval2,wval2,pval2,sval2);
  // gPad->SaveAs("interference.pdf");
  ROOT::Math::WrappedTF1 wf1(*inter_comp);
  ROOT::Math::GSLIntegrator ig(ROOT::Math::IntegrationOneDim::kADAPTIVE);
  ig.SetFunction(wf1);
  // ig.SetF
  ig.SetRelTolerance(0.001);
  return ig.Integral(min, max);
}



double RooInterModel::numIntegrateInterferenceThreeBW(double min, double max)
{
    Double_t mval = ((RooAbsReal&)mean_[0] ).getVal();
    Double_t wval = ((RooAbsReal&)width_[0]).getVal();
    Double_t pval = ((RooAbsReal&)phase_[0]).getVal();
    Double_t sval = ((RooAbsReal&)scale_[0]).getVal();

    Double_t mval2 = ((RooAbsReal&)mean_[1] ).getVal();
    Double_t wval2 = ((RooAbsReal&)width_[1]).getVal();
    Double_t pval2 = ((RooAbsReal&)phase_[1]).getVal();
    Double_t sval2 = ((RooAbsReal&)scale_[1]).getVal();

    Double_t mval3 = ((RooAbsReal&)mean_[2] ).getVal();
    Double_t wval3 = ((RooAbsReal&)width_[2]).getVal();
    Double_t pval3 = ((RooAbsReal&)phase_[2]).getVal();
    Double_t sval3 = ((RooAbsReal&)scale_[2]).getVal();

    double pars[13];
    pars[0] = mval;
    pars[1] = wval;
    pars[2] = pval;
    pars[3] = sval;
    pars[4] = p1_;
    pars[5] = mval2;
    pars[6] = wval2;
    pars[7] = pval2;
    pars[8] = sval2;
    pars[9] = mval3;
    pars[10] = wval3;
    pars[11] = pval3;
    pars[12] = sval3;     
  // Double_t arg= x - mean;  
  // return 1. / (arg*arg + 0.25*width*width);

  TF1 f("Inteference function", inteferenceThreeBWPhys, min, max);
      inter_comp = new TF1("myfunc_inter",inteferenceThreeBWPhys,min,max,13);
      inter_comp->SetParameters(pars);
  // gPad->SaveAs("interference.pdf");
  ROOT::Math::WrappedTF1 wf1(*inter_comp);
  ROOT::Math::GSLIntegrator ig(ROOT::Math::IntegrationOneDim::kADAPTIVE);
  ig.SetFunction(wf1);
  // ig.SetF
  ig.SetRelTolerance(0.001);
  return ig.Integral(min, max);
  return 0;
}


double RooInterModel::numIntegrateInterferenceFourBW(double min, double max)
{
    Double_t mval = ((RooAbsReal&)mean_[0] ).getVal();
    Double_t wval = ((RooAbsReal&)width_[0]).getVal();
    Double_t pval = ((RooAbsReal&)phase_[0]).getVal();
    Double_t sval = ((RooAbsReal&)scale_[0]).getVal();

    Double_t mval2 = ((RooAbsReal&)mean_[1] ).getVal();
    Double_t wval2 = ((RooAbsReal&)width_[1]).getVal();
    Double_t pval2 = ((RooAbsReal&)phase_[1]).getVal();
    Double_t sval2 = ((RooAbsReal&)scale_[1]).getVal();

    Double_t mval3 = ((RooAbsReal&)mean_[2] ).getVal();
    Double_t wval3 = ((RooAbsReal&)width_[2]).getVal();
    Double_t pval3 = ((RooAbsReal&)phase_[2]).getVal();
    Double_t sval3 = ((RooAbsReal&)scale_[2]).getVal();

    Double_t mval4 = ((RooAbsReal&)mean_[3] ).getVal();
    Double_t wval4 = ((RooAbsReal&)width_[3]).getVal();
    Double_t pval4 = ((RooAbsReal&)phase_[3]).getVal();
    Double_t sval4 = ((RooAbsReal&)scale_[3]).getVal();

    double pars[17];
    pars[0] = mval;
    pars[1] = wval;
    pars[2] = pval;
    pars[3] = sval;
    pars[4] = p1_;
    pars[5] = mval2;
    pars[6] = wval2;
    pars[7] = pval2;
    pars[8] = sval2;
    pars[9] = mval3;
    pars[10] = wval3;
    pars[11] = pval3;
    pars[12] = sval3;
    pars[13] = mval4;
    pars[14] = wval4;
    pars[15] = pval4;
    pars[16] = sval4;      
  // Double_t arg= x - mean;  
  // return 1. / (arg*arg + 0.25*width*width);

  TF1 f("Inteference function", inteferenceFourBWPhys, min, max);
      inter_comp = new TF1("myfunc_inter",inteferenceFourBWPhys,min,max,17);
      inter_comp->SetParameters(pars);
  // gPad->SaveAs("interference.pdf");
  ROOT::Math::WrappedTF1 wf1(*inter_comp);
  ROOT::Math::GSLIntegrator ig(ROOT::Math::IntegrationOneDim::kADAPTIVE);
  ig.SetFunction(wf1);
  // ig.SetF
  ig.SetRelTolerance(0.001);
  return ig.Integral(min, max);
}

double RooInterModel::constNumIntegrateAll(double min, double max) const
{
    Double_t mval = ((RooAbsReal&)mean_[0] ).getVal();
    Double_t wval = ((RooAbsReal&)width_[0]).getVal();
    Double_t pval = ((RooAbsReal&)phase_[0]).getVal();
    Double_t sval = ((RooAbsReal&)scale_[0]).getVal();

    Double_t mval2 = ((RooAbsReal&)mean_[1] ).getVal();
    Double_t wval2 = ((RooAbsReal&)width_[1]).getVal();
    Double_t pval2 = ((RooAbsReal&)phase_[1]).getVal();
    Double_t sval2 = ((RooAbsReal&)scale_[1]).getVal();


    Double_t mval3;
    Double_t wval3;
    Double_t pval3;
    Double_t sval3;

    Double_t mval4;
    Double_t wval4;
    Double_t pval4;
    Double_t sval4;

    if (mean_.getSize() > 2)
    {
      mval3 = ((RooAbsReal&)mean_[2] ).getVal();
      wval3 = ((RooAbsReal&)width_[2]).getVal();
      pval3 = ((RooAbsReal&)phase_[2]).getVal();
      sval3 = ((RooAbsReal&)scale_[2]).getVal();
    }

    if (mean_.getSize() > 3)
    {
      mval4 = ((RooAbsReal&)mean_[3] ).getVal();
      wval4 = ((RooAbsReal&)width_[3]).getVal();
      pval4 = ((RooAbsReal&)phase_[3]).getVal();
      sval4 = ((RooAbsReal&)scale_[3]).getVal();
    }

    double pars[17];
    pars[0] = mval;
    pars[1] = wval;
    pars[2] = pval;
    pars[3] = sval;
    pars[4] = p1_;
    pars[5] = mval2;
    pars[6] = wval2;
    pars[7] = pval2;
    pars[8] = sval2;
    if (mean_.getSize() > 2)
    {
      pars[9] = mval3;
      pars[10] = wval3;
      pars[11] = pval3;
      pars[12] = sval3;
    }
    else
    {
      pars[9] = 4200;
      pars[10] = 10;
      pars[11] = 0.0;
      pars[12] = 0.0;      
    } 
    if (mean_.getSize() > 3)
    {
      pars[13] = mval4;
      pars[14] = wval4;
      pars[15] = pval4;
      pars[16] = sval4;
    }
    else
    {
      pars[13] = 4200;
      pars[14] = 10;
      pars[15] = 0.0;
      pars[16] = 0.0;      
    }   
  // Double_t arg= x - mean;  
  // return 1. / (arg*arg + 0.25*width*width);

  TF1* all_comp = new TF1("myfunc_inter",all,min,max,17);
      all_comp->SetParameters(pars);

  ROOT::Math::WrappedTF1 wf1(*all_comp);
  ROOT::Math::GSLIntegrator ig(ROOT::Math::IntegrationOneDim::kADAPTIVE);
  ig.SetFunction(wf1);
  // ig.SetF
  ig.SetRelTolerance(0.001);
  return ig.Integral(min, max);
}


double RooInterModel::numIntegrateBW(double min, double max,int whichBW) 
{
    Double_t mval = ((RooAbsReal&)mean_[whichBW] ).getVal();
    Double_t wval = ((RooAbsReal&)width_[whichBW]).getVal();
    Double_t sval = ((RooAbsReal&)scale_[whichBW]).getVal();
      BW_comp = new TF1("myfunc_BW",bw_forIntPhys,min,max,4);
      BW_comp->SetParameters(mval,wval,sval,p1_);
      BW_comp->SetParNames("constant","coefficient");
      BW_comp->Draw();
  // gPad->SaveAs("BW.pdf");
  ROOT::Math::WrappedTF1 wf1(*BW_comp);
  ROOT::Math::GSLIntegrator ig(ROOT::Math::IntegrationOneDim::kADAPTIVE);
  ig.SetFunction(wf1);
  // ig.SetF
  ig.SetRelTolerance(0.001);
  return ig.Integral(min, max);
}

double RooInterModel::numIntegrateNonres(double min, double max)
{
  nonres_comp = new TF1("nonresfunction", nonres_forIntNorm, min, max,2);
  nonres_comp->SetParameters(p1_,p1_);
  nonres_comp->Draw();
  // gPad->SaveAs("nonres.pdf");
  ROOT::Math::WrappedTF1 wf1(*nonres_comp);
  ROOT::Math::GSLIntegrator ig(ROOT::Math::IntegrationOneDim::kADAPTIVE);
  ig.SetFunction(wf1);
  // ig.SetF
  ig.SetRelTolerance(0.001);
  return ig.Integral(min, max);
  return 0;
}

double RooInterModel::constNumIntegrateNonres(double min, double max) const
{
  TF1* nonres_comp = new TF1("nonresfunction", nonres_forIntNorm, min, max,2);
  nonres_comp->SetParameters(p1_,p1_);
  // nonres_comp->Draw();
  // // gPad->SaveAs("nonres.pdf");
  ROOT::Math::WrappedTF1 wf1(*nonres_comp);
  ROOT::Math::GSLIntegrator ig(ROOT::Math::IntegrationOneDim::kADAPTIVE);
  ig.SetFunction(wf1);
  // ig.SetF
  ig.SetRelTolerance(0.001);
  return ig.Integral(min, max);
}

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


Double_t RooInterModel::FF_bus( const Double_t shat ) const 
{
  return 1.0/std::pow( 1. - p1_*shat, 2 ); //  - p2_*shat*shat );
  // return 1.0/( 1. - p1_*shat - p2_*shat*shat ); 
  // return 1./(1. - p1_*shat) + p2_/std::pow( 1. - p1_*shat , 2 );
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
