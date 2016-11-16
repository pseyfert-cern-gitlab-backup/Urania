#include "Riostream.h" 
#include "accpdf.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h"
#include "TF1.h"

#define pi 3.14159265358979323846264

ClassImp(accpdf) 

// ---------------------------------------------------
// First constructor.

 accpdf::accpdf(const char *name, const char *title, 
                        RooAbsReal& _m1,
                        RooAbsReal& _m2,
                        RooAbsReal& _cos1,
			RooAbsReal& _cos2,
                        RooAbsReal& _phi,
                        RooAbsReal& _t,
                        RooAbsReal& _k1,
                        RooAbsReal& _k2,
                        RooAbsReal& _k3,
                        RooAbsReal& _k4,
                        RooAbsReal& _k5,
                        RooAbsReal& _p1,
			RooAbsReal& _a_acc,
			RooAbsReal& _b_acc,
			RooAbsReal& _c_acc,
			RooAbsReal& _kpipair,
			RooAbsReal& _option) :
   RooAbsReal(name,title), 
   m1("m1","m1",this,_m1),
   m2("m2","m2",this,_m2),
   cos1("cos1","cos1",this,_cos1),
   cos2("cos2","cos2",this,_cos2),
   phi("phi","phi",this,_phi),
   t("t","t",this,_t),
   k1("k1","k1",this,_k1),
   k2("k2","k2",this,_k2),
   k3("k3","k3",this,_k3),
   k4("k4","k4",this,_k4),
   k5("k5","k5",this,_k5),
   p1("p1","p1",this,_p1),
   a_acc("a_acc","a_acc",this,_a_acc),
   b_acc("b_acc","b_acc",this,_b_acc),
   c_acc("c_acc","c_acc",this,_c_acc),
   kpipair("kpipair","kpipair",this,_kpipair),
   option("option","option",this,_option)
 { 
 } 

// ---------------------------------------------------
// Second constructor.
						
 accpdf::accpdf(const accpdf& other, const char* name) :  
   RooAbsReal(other,name), 
   m1("m1",this,other.m1),
   m2("m2",this,other.m2),
   cos1("cos1",this,other.cos1),
   cos2("cos2",this,other.cos2),
   phi("phi",this,other.phi),
   t("t",this,other.t),
   k1("k1",this,other.k1),
   k2("k2",this,other.k2),
   k3("k3",this,other.k3),
   k4("k4",this,other.k4),
   k5("k5",this,other.k5),
   p1("p1",this,other.p1),
   a_acc("a_acc",this,other.a_acc),
   b_acc("b_acc",this,other.b_acc),
   c_acc("c_acc",this,other.c_acc),
   kpipair("kpipair",this,other.kpipair),
   option("option",this,other.option)
 { 
 } 
						
// ---------------------------------------------------
// Angular acceptance in cos(theta).

Double_t accpdf::accCos(Double_t x) const
 { 

	return 1.+k1*x+k2*(2.*x*x-1.)+k3*(4.*x*x*x-3.*x)+k4*(8.*x*x*x*x-8.*x*x+1.)+k5*(16.*x*x*x*x*x-20.*x*x*x+5.*x);

 }

// ---------------------------------------------------
// Angular acceptance in phi.

Double_t accpdf::accPhi(Double_t x) const 
 { 
   
	return 1. + 0.*x;

 }

// ---------------------------------------------------
// Invariant mass dependent acceptance.

Double_t accpdf::accMass(Double_t x) const 
 { 
   
	return 1. + p1*x;

 }
 
// ---------------------------------------------------
// Time dependent acceptance.

Double_t accpdf::accTime(Double_t x) const 
 { 
   
	return x*x*x/(a_acc+x*x*x)*(1.+b_acc*x+c_acc*x*x);

 }
 
// ---------------------------------------------------
// Total factorized acceptance.

Double_t accpdf::evaluate() const 
 {
 
	if (option == 0) {return accCos(cos1)*accCos(cos2)*accPhi(phi)*accMass(m1)*accMass(m2)*accTime(t);}
	if (option == 1 and kpipair == 1) {return accMass(m1);}
	if (option == 1 and kpipair == 2) {return accMass(m2);}
	if (option == 2 and kpipair == 1) {return accCos(cos1);}
	if (option == 2 and kpipair == 2) {return accCos(cos2);}
	if (option == 3) {return accPhi(phi);}
	if (option == 4) {return accTime(t);}

	throw std::invalid_argument( "Invalid option value" );
	
 }
