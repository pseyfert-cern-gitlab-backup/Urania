#include "Riostream.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h"
#include "TF1.h"
#include <stdexcept>
#include "RooMath.h"
#include "MCGenPHSP.h"

#define m_kaon 493.677
#define m_pion 139.57018
#define m_Bs 5366.77
#define gamma_Bs_freq 0.668

ClassImp(MCGenPHSP) 

// ---------------------------------------------------

 MCGenPHSP::MCGenPHSP(const char *name, const char *title,
                        RooAbsReal& _wide_window,
                        RooAbsReal& _m1,
                        RooAbsReal& _m2,
                        RooAbsReal& _t,
                        RooAbsReal& _option) :
   RooAbsReal(name,title),
   wide_window("wide_window","wide_window",this,_wide_window),
   m1("m1","m1",this,_m1),
   m2("m2","m2",this,_m2),
   t("t","t",this,_t),
   option("option","option",this,_option)
 { 
 } 

// ---------------------------------------------------

 MCGenPHSP::MCGenPHSP(const MCGenPHSP& other, const char* name) :  
   RooAbsReal(other,name),
   wide_window("wide_window",this,other.wide_window),
   m1("m1",this,other.m1),
   m2("m2",this,other.m2),
   t("t",this,other.t),
   option("option",this,other.option)
 { 
 } 

// ---------------------------------------------------
// Momentum Q associated to a mother particle of mass ma decaying
// to two daughters of masses mb and mc.

Double_t MCGenPHSP::GetQ(Double_t ma,Double_t mb,Double_t mc) const 
 {
  
  Double_t Q = sqrt((ma*ma - pow(mb+mc,2))*(ma*ma - pow(mb-mc,2)))/(2*ma);
  
  return Q;
  
 }

// ---------------------------------------------------
// Phase space factor.

Double_t MCGenPHSP::phasespace(Double_t ma, Double_t mb) const 
 { 
 
   Double_t Q1 = GetQ(ma,m_kaon,m_pion);
   Double_t Q2 = GetQ(mb,m_kaon,m_pion);
   Double_t QB = GetQ(m_Bs,ma,mb);
   Double_t phsp = Q1*Q2*QB;

   if (wide_window == 1) {return phsp/511488825382022.94;}
   else if (wide_window == 0) {return phsp/19250835243402.47;}

   return 0.;

 }

// ---------------------------------------------------
// Decay time dependence.

Double_t MCGenPHSP::timemodel(Double_t tau) const 
 { 

   return exp(-gamma_Bs_freq*tau)/1.4965117894579445;

 }

// ---------------------------------------------------

 Double_t MCGenPHSP::evaluate() const 
 { 

	if (option == 1) {return phasespace(m1,m2);}
	else if (option == 2) {return timemodel(t);}

	throw std::invalid_argument( "Invalid option value." );

}
