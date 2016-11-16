#include "Riostream.h" 
#include "RooAbsPdf.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h"
#include "TF1.h"
#include <stdexcept>
#include "RooMath.h"
#include "SplineTAcc.h"


ClassImp(SplineTAcc) 

// ---------------------------------------------------

 SplineTAcc::SplineTAcc(const char *name, const char *title,
                        RooAbsReal& _t,
                        RooAbsReal& _x0,
                        RooAbsReal& _x1,
                        RooAbsReal& _x2,
                        RooAbsReal& _x3,
                        RooAbsReal& _x4,
                        RooAbsReal& _x5,
                        RooAbsReal& _c0,
                        RooAbsReal& _c1,
                        RooAbsReal& _c2,
                        RooAbsReal& _c3,
                        RooAbsReal& _c4,
                        RooAbsReal& _c5,
                        RooAbsReal& _c6,
                        RooAbsReal& _c7) :
   RooAbsPdf(name,title),
   t("t","t",this,_t),
   x0("x0","x0",this,_x0),
   x1("x1","x1",this,_x1),
   x2("x2","x2",this,_x2),
   x3("x3","x3",this,_x3),
   x4("x4","x4",this,_x4),
   x5("x5","x5",this,_x5),
   c0("c0","c0",this,_c0),
   c1("c1","c1",this,_c1),
   c2("c2","c2",this,_c2),
   c3("c3","c3",this,_c3),
   c4("c4","c4",this,_c4),
   c5("c5","c5",this,_c5),
   c6("c6","c6",this,_c6),
   c7("c7","c7",this,_c7)
 { 
   knot[0] = x0;
   knot[1] = x0;
   knot[2] = x0;
   knot[3] = x0;
   knot[4] = x1;
   knot[5] = x2;
   knot[6] = x3;
   knot[7] = x4;
   knot[8] = x5;
   knot[9] = x5;
   knot[10] = x5;
   knot[11] = x5;
 } 

// ---------------------------------------------------

 SplineTAcc::SplineTAcc(const SplineTAcc& other, const char* name) :  
   RooAbsPdf(other,name),
   t("t",this,other.t),
   x0("x0",this,other.x0),
   x1("x1",this,other.x1),
   x2("x2",this,other.x2),
   x3("x3",this,other.x3),
   x4("x4",this,other.x4),
   x5("x5",this,other.x5),
   c0("c0",this,other.c0),
   c1("c1",this,other.c1),
   c2("c2",this,other.c2),
   c3("c3",this,other.c3),
   c4("c4",this,other.c4),
   c5("c5",this,other.c5),
   c6("c6",this,other.c6),
   c7("c7",this,other.c7)
 { 
   knot[0] = x0;
   knot[1] = x0;
   knot[2] = x0;
   knot[3] = x0;
   knot[4] = x1;
   knot[5] = x2;
   knot[6] = x3;
   knot[7] = x4;
   knot[8] = x5;
   knot[9] = x5;
   knot[10] = x5;
   knot[11] = x5;
 } 

// ---------------------------------------------------

Double_t SplineTAcc::ci(Int_t i) const 
 { 

	if (i==0) {return c0;}
	else if (i==1) {return c1;}
	else if (i==2) {return c2;}
	else if (i==3) {return c3;}
	else if (i==4) {return c4;}
	else if (i==5) {return c5;}
	else if (i==6) {return c6;}
	else if (i==7) {return c7;}

	return 0.;

}

// ---------------------------------------------------

Double_t SplineTAcc::Bid(Int_t i, Int_t d, Double_t x) const 
 { 

	if (d==0) {
		if (knot[i] <= x and x < knot[i+1]) {return 1.;}
		else {return 0.;}
	}
	else {
		Double_t Bidsum = 0;
		Double_t term1 = Bid(i,d-1,x);
		Double_t term2 = Bid(i+1,d-1,x);
		if (term1 > 0) {Bidsum += (x-knot[i])/(knot[i+d]-knot[i])*term1;}
		if (term2 > 0) {Bidsum += (knot[i+1+d]-x)/(knot[i+1+d]-knot[i+1])*term2;}
		return Bidsum;
	}

}

// ---------------------------------------------------

Double_t SplineTAcc::polynomial(Double_t x) const 
 { 

	Double_t polsum = 0;
	for (Int_t i=0;i<8;i++) {polsum += ci(i)*Bid(i,3,x);}
	return polsum;

}

// ---------------------------------------------------

Double_t SplineTAcc::a_bin_deg(Int_t ibin, Int_t deg) const 
 { 

	if (ibin == 0) {

		if (deg == 0) {return -c0*pow(x1,3)/(pow(x0,3) - 3*pow(x0,2)*x1 + 3*x0*pow(x1,2) - pow(x1,3)) + c1*x0*pow(x1,2)/(pow(x0,3) - 3*pow(x0,2)*x1 + 3*x0*pow(x1,2) - pow(x1,3)) + c1*x0*x1*x2/(pow(x0,3) - 2*pow(x0,2)*x1 - pow(x0,2)*x2 + x0*pow(x1,2) + 2*x0*x1*x2 - pow(x1,2)*x2) + c1*x0*pow(x2,2)/(pow(x0,3) - pow(x0,2)*x1 - 2*pow(x0,2)*x2 + 2*x0*x1*x2 + x0*pow(x2,2) - x1*pow(x2,2)) - c2*pow(x0,2)*x1/(pow(x0,3) - 2*pow(x0,2)*x1 - pow(x0,2)*x2 + x0*pow(x1,2) + 2*x0*x1*x2 - pow(x1,2)*x2) - c2*pow(x0,2)*x2/(pow(x0,3) - pow(x0,2)*x1 - 2*pow(x0,2)*x2 + 2*x0*x1*x2 + x0*pow(x2,2) - x1*pow(x2,2)) - c2*pow(x0,2)*x3/(pow(x0,3) - pow(x0,2)*x1 - pow(x0,2)*x2 - pow(x0,2)*x3 + x0*x1*x2 + x0*x1*x3 + x0*x2*x3 - x1*x2*x3) + c3*pow(x0,3)/(pow(x0,3) - pow(x0,2)*x1 - pow(x0,2)*x2 - pow(x0,2)*x3 + x0*x1*x2 + x0*x1*x3 + x0*x2*x3 - x1*x2*x3);}

		else if (deg == 1) {return 3*(c0*pow(x0,3)*pow(x1,2) - 2*c0*pow(x0,2)*pow(x1,2)*x2 - c0*pow(x0,2)*pow(x1,2)*x3 + c0*x0*pow(x1,2)*pow(x2,2) + 2*c0*x0*pow(x1,2)*x2*x3 - c0*pow(x1,2)*pow(x2,2)*x3 - c1*pow(x0,4)*x1 - c1*pow(x0,4)*x2 + 3*c1*pow(x0,3)*x1*x2 + c1*pow(x0,3)*x1*x3 + c1*pow(x0,3)*x2*x3 - 3*c1*pow(x0,2)*x1*x2*x3 - c1*x0*pow(x1,2)*pow(x2,2) + c1*pow(x1,2)*pow(x2,2)*x3 + c2*pow(x0,5) - c2*pow(x0,4)*x1 - c2*pow(x0,3)*x1*x2 - c2*pow(x0,3)*x1*x3 - c2*pow(x0,3)*x2*x3 + c2*pow(x0,2)*pow(x1,2)*x2 + c2*pow(x0,2)*pow(x1,2)*x3 + 3*c2*pow(x0,2)*x1*x2*x3 - 2*c2*x0*pow(x1,2)*x2*x3 - c3*pow(x0,5) + 2*c3*pow(x0,4)*x1 + c3*pow(x0,4)*x2 - c3*pow(x0,3)*pow(x1,2) - 2*c3*pow(x0,3)*x1*x2 + c3*pow(x0,2)*pow(x1,2)*x2)/(pow(x0,6) - 3*pow(x0,5)*x1 - 2*pow(x0,5)*x2 - pow(x0,5)*x3 + 3*pow(x0,4)*pow(x1,2) + 6*pow(x0,4)*x1*x2 + 3*pow(x0,4)*x1*x3 + pow(x0,4)*pow(x2,2) + 2*pow(x0,4)*x2*x3 - pow(x0,3)*pow(x1,3) - 6*pow(x0,3)*pow(x1,2)*x2 - 3*pow(x0,3)*pow(x1,2)*x3 - 3*pow(x0,3)*x1*pow(x2,2) - 6*pow(x0,3)*x1*x2*x3 - pow(x0,3)*pow(x2,2)*x3 + 2*pow(x0,2)*pow(x1,3)*x2 + pow(x0,2)*pow(x1,3)*x3 + 3*pow(x0,2)*pow(x1,2)*pow(x2,2) + 6*pow(x0,2)*pow(x1,2)*x2*x3 + 3*pow(x0,2)*x1*pow(x2,2)*x3 - x0*pow(x1,3)*pow(x2,2) - 2*x0*pow(x1,3)*x2*x3 - 3*x0*pow(x1,2)*pow(x2,2)*x3 + pow(x1,3)*pow(x2,2)*x3);}

		else if (deg == 2) {return 3*(-c0*pow(x0,3)*x1 + 2*c0*pow(x0,2)*x1*x2 + c0*pow(x0,2)*x1*x3 - c0*x0*x1*pow(x2,2) - 2*c0*x0*x1*x2*x3 + c0*x1*pow(x2,2)*x3 + c1*pow(x0,4) - c1*pow(x0,3)*x3 - 3*c1*pow(x0,2)*x1*x2 + c1*x0*pow(x1,2)*x2 + c1*x0*x1*pow(x2,2) + 3*c1*x0*x1*x2*x3 - c1*pow(x1,2)*x2*x3 - c1*x1*pow(x2,2)*x3 - 2*c2*pow(x0,4) + 3*c2*pow(x0,3)*x1 + c2*pow(x0,3)*x2 + c2*pow(x0,3)*x3 - c2*pow(x0,2)*pow(x1,2) - c2*pow(x0,2)*x1*x2 - c2*pow(x0,2)*x1*x3 - c2*x0*x1*x2*x3 + c2*pow(x1,2)*x2*x3 + c3*pow(x0,4) - 2*c3*pow(x0,3)*x1 - c3*pow(x0,3)*x2 + c3*pow(x0,2)*pow(x1,2) + 2*c3*pow(x0,2)*x1*x2 - c3*x0*pow(x1,2)*x2)/(pow(x0,6) - 3*pow(x0,5)*x1 - 2*pow(x0,5)*x2 - pow(x0,5)*x3 + 3*pow(x0,4)*pow(x1,2) + 6*pow(x0,4)*x1*x2 + 3*pow(x0,4)*x1*x3 + pow(x0,4)*pow(x2,2) + 2*pow(x0,4)*x2*x3 - pow(x0,3)*pow(x1,3) - 6*pow(x0,3)*pow(x1,2)*x2 - 3*pow(x0,3)*pow(x1,2)*x3 - 3*pow(x0,3)*x1*pow(x2,2) - 6*pow(x0,3)*x1*x2*x3 - pow(x0,3)*pow(x2,2)*x3 + 2*pow(x0,2)*pow(x1,3)*x2 + pow(x0,2)*pow(x1,3)*x3 + 3*pow(x0,2)*pow(x1,2)*pow(x2,2) + 6*pow(x0,2)*pow(x1,2)*x2*x3 + 3*pow(x0,2)*x1*pow(x2,2)*x3 - x0*pow(x1,3)*pow(x2,2) - 2*x0*pow(x1,3)*x2*x3 - 3*x0*pow(x1,2)*pow(x2,2)*x3 + pow(x1,3)*pow(x2,2)*x3);}

		else if (deg == 3) {return c0/(pow(x0,3) - 3*pow(x0,2)*x1 + 3*x0*pow(x1,2) - pow(x1,3)) - c1/(pow(x0,3) - pow(x0,2)*x1 - 2*pow(x0,2)*x2 + 2*x0*x1*x2 + x0*pow(x2,2) - x1*pow(x2,2)) - c1/(pow(x0,3) - 2*pow(x0,2)*x1 - pow(x0,2)*x2 + x0*pow(x1,2) + 2*x0*x1*x2 - pow(x1,2)*x2) - c1/(pow(x0,3) - 3*pow(x0,2)*x1 + 3*x0*pow(x1,2) - pow(x1,3)) + c2/(pow(x0,3) - pow(x0,2)*x1 - pow(x0,2)*x2 - pow(x0,2)*x3 + x0*x1*x2 + x0*x1*x3 + x0*x2*x3 - x1*x2*x3) + c2/(pow(x0,3) - pow(x0,2)*x1 - 2*pow(x0,2)*x2 + 2*x0*x1*x2 + x0*pow(x2,2) - x1*pow(x2,2)) + c2/(pow(x0,3) - 2*pow(x0,2)*x1 - pow(x0,2)*x2 + x0*pow(x1,2) + 2*x0*x1*x2 - pow(x1,2)*x2) - c3/(pow(x0,3) - pow(x0,2)*x1 - pow(x0,2)*x2 - pow(x0,2)*x3 + x0*x1*x2 + x0*x1*x3 + x0*x2*x3 - x1*x2*x3);}
	}
	else if (ibin == 1) {

		if (deg == 0) {return -c1*pow(x2,3)/(pow(x0,2)*x1 - pow(x0,2)*x2 - 2*x0*x1*x2 + 2*x0*pow(x2,2) + x1*pow(x2,2) - pow(x2,3)) + c2*x0*pow(x2,2)/(pow(x0,2)*x1 - pow(x0,2)*x2 - 2*x0*x1*x2 + 2*x0*pow(x2,2) + x1*pow(x2,2) - pow(x2,3)) + c2*x0*x2*x3/(pow(x0,2)*x1 - pow(x0,2)*x2 - x0*x1*x2 - x0*x1*x3 + x0*pow(x2,2) + x0*x2*x3 + x1*x2*x3 - pow(x2,2)*x3) + c2*x1*pow(x3,2)/(x0*pow(x1,2) - x0*x1*x2 - x0*x1*x3 + x0*x2*x3 - pow(x1,2)*x3 + x1*x2*x3 + x1*pow(x3,2) - x2*pow(x3,2)) - c3*pow(x0,2)*x2/(pow(x0,2)*x1 - pow(x0,2)*x2 - x0*x1*x2 - x0*x1*x3 + x0*pow(x2,2) + x0*x2*x3 + x1*x2*x3 - pow(x2,2)*x3) - c3*x0*x1*x3/(x0*pow(x1,2) - x0*x1*x2 - x0*x1*x3 + x0*x2*x3 - pow(x1,2)*x3 + x1*x2*x3 + x1*pow(x3,2) - x2*pow(x3,2)) - c3*pow(x1,2)*x4/(pow(x1,3) - pow(x1,2)*x2 - pow(x1,2)*x3 - pow(x1,2)*x4 + x1*x2*x3 + x1*x2*x4 + x1*x3*x4 - x2*x3*x4) + c4*pow(x1,3)/(pow(x1,3) - pow(x1,2)*x2 - pow(x1,2)*x3 - pow(x1,2)*x4 + x1*x2*x3 + x1*x2*x4 + x1*x3*x4 - x2*x3*x4);}

		else if (deg == 1) {return (x1*(c3*x1 + 2*c3*x4 - 3*c4*x1)*(pow(x0,2)*x1 - pow(x0,2)*x2 - 2*x0*x1*x2 + 2*x0*pow(x2,2) + x1*pow(x2,2) - pow(x2,3))*(x0*pow(x1,2) - x0*x1*x2 - x0*x1*x3 + x0*x2*x3 - pow(x1,2)*x3 + x1*x2*x3 + x1*pow(x3,2) - x2*pow(x3,2))*(pow(x0,2)*x1 - pow(x0,2)*x2 - x0*x1*x2 - x0*x1*x3 + x0*pow(x2,2) + x0*x2*x3 + x1*x2*x3 - pow(x2,2)*x3) + x2*(3*c1*x2 - 2*c2*x0 - c2*x2)*(pow(x1,3) - pow(x1,2)*x2 - pow(x1,2)*x3 - pow(x1,2)*x4 + x1*x2*x3 + x1*x2*x4 + x1*x3*x4 - x2*x3*x4)*(x0*pow(x1,2) - x0*x1*x2 - x0*x1*x3 + x0*x2*x3 - pow(x1,2)*x3 + x1*x2*x3 + x1*pow(x3,2) - x2*pow(x3,2))*(pow(x0,2)*x1 - pow(x0,2)*x2 - x0*x1*x2 - x0*x1*x3 + x0*pow(x2,2) + x0*x2*x3 + x1*x2*x3 - pow(x2,2)*x3) + (-c2*x0*x2 - c2*x0*x3 - c2*x2*x3 + c3*pow(x0,2) + 2*c3*x0*x2)*(pow(x0,2)*x1 - pow(x0,2)*x2 - 2*x0*x1*x2 + 2*x0*pow(x2,2) + x1*pow(x2,2) - pow(x2,3))*(pow(x1,3) - pow(x1,2)*x2 - pow(x1,2)*x3 - pow(x1,2)*x4 + x1*x2*x3 + x1*x2*x4 + x1*x3*x4 - x2*x3*x4)*(x0*pow(x1,2) - x0*x1*x2 - x0*x1*x3 + x0*x2*x3 - pow(x1,2)*x3 + x1*x2*x3 + x1*pow(x3,2) - x2*pow(x3,2)) + (-2*c2*x1*x3 - c2*pow(x3,2) + c3*x0*x1 + c3*x0*x3 + c3*x1*x3)*(pow(x0,2)*x1 - pow(x0,2)*x2 - 2*x0*x1*x2 + 2*x0*pow(x2,2) + x1*pow(x2,2) - pow(x2,3))*(pow(x1,3) - pow(x1,2)*x2 - pow(x1,2)*x3 - pow(x1,2)*x4 + x1*x2*x3 + x1*x2*x4 + x1*x3*x4 - x2*x3*x4)*(pow(x0,2)*x1 - pow(x0,2)*x2 - x0*x1*x2 - x0*x1*x3 + x0*pow(x2,2) + x0*x2*x3 + x1*x2*x3 - pow(x2,2)*x3))/((pow(x0,2)*x1 - pow(x0,2)*x2 - 2*x0*x1*x2 + 2*x0*pow(x2,2) + x1*pow(x2,2) - pow(x2,3))*(pow(x1,3) - pow(x1,2)*x2 - pow(x1,2)*x3 - pow(x1,2)*x4 + x1*x2*x3 + x1*x2*x4 + x1*x3*x4 - x2*x3*x4)*(x0*pow(x1,2) - x0*x1*x2 - x0*x1*x3 + x0*x2*x3 - pow(x1,2)*x3 + x1*x2*x3 + x1*pow(x3,2) - x2*pow(x3,2))*(pow(x0,2)*x1 - pow(x0,2)*x2 - x0*x1*x2 - x0*x1*x3 + x0*pow(x2,2) + x0*x2*x3 + x1*x2*x3 - pow(x2,2)*x3));}

		else if (deg == 2) {return ((-3*c1*x2 + c2*x0 + 2*c2*x2)*(pow(x1,3) - pow(x1,2)*x2 - pow(x1,2)*x3 - pow(x1,2)*x4 + x1*x2*x3 + x1*x2*x4 + x1*x3*x4 - x2*x3*x4)*(x0*pow(x1,2) - x0*x1*x2 - x0*x1*x3 + x0*x2*x3 - pow(x1,2)*x3 + x1*x2*x3 + x1*pow(x3,2) - x2*pow(x3,2))*(pow(x0,2)*x1 - pow(x0,2)*x2 - x0*x1*x2 - x0*x1*x3 + x0*pow(x2,2) + x0*x2*x3 + x1*x2*x3 - pow(x2,2)*x3) + (-2*c3*x1 - c3*x4 + 3*c4*x1)*(pow(x0,2)*x1 - pow(x0,2)*x2 - 2*x0*x1*x2 + 2*x0*pow(x2,2) + x1*pow(x2,2) - pow(x2,3))*(x0*pow(x1,2) - x0*x1*x2 - x0*x1*x3 + x0*x2*x3 - pow(x1,2)*x3 + x1*x2*x3 + x1*pow(x3,2) - x2*pow(x3,2))*(pow(x0,2)*x1 - pow(x0,2)*x2 - x0*x1*x2 - x0*x1*x3 + x0*pow(x2,2) + x0*x2*x3 + x1*x2*x3 - pow(x2,2)*x3) + (c2*x0 + c2*x2 + c2*x3 - 2*c3*x0 - c3*x2)*(pow(x0,2)*x1 - pow(x0,2)*x2 - 2*x0*x1*x2 + 2*x0*pow(x2,2) + x1*pow(x2,2) - pow(x2,3))*(pow(x1,3) - pow(x1,2)*x2 - pow(x1,2)*x3 - pow(x1,2)*x4 + x1*x2*x3 + x1*x2*x4 + x1*x3*x4 - x2*x3*x4)*(x0*pow(x1,2) - x0*x1*x2 - x0*x1*x3 + x0*x2*x3 - pow(x1,2)*x3 + x1*x2*x3 + x1*pow(x3,2) - x2*pow(x3,2)) + (c2*x1 + 2*c2*x3 - c3*x0 - c3*x1 - c3*x3)*(pow(x0,2)*x1 - pow(x0,2)*x2 - 2*x0*x1*x2 + 2*x0*pow(x2,2) + x1*pow(x2,2) - pow(x2,3))*(pow(x1,3) - pow(x1,2)*x2 - pow(x1,2)*x3 - pow(x1,2)*x4 + x1*x2*x3 + x1*x2*x4 + x1*x3*x4 - x2*x3*x4)*(pow(x0,2)*x1 - pow(x0,2)*x2 - x0*x1*x2 - x0*x1*x3 + x0*pow(x2,2) + x0*x2*x3 + x1*x2*x3 - pow(x2,2)*x3))/((pow(x0,2)*x1 - pow(x0,2)*x2 - 2*x0*x1*x2 + 2*x0*pow(x2,2) + x1*pow(x2,2) - pow(x2,3))*(pow(x1,3) - pow(x1,2)*x2 - pow(x1,2)*x3 - pow(x1,2)*x4 + x1*x2*x3 + x1*x2*x4 + x1*x3*x4 - x2*x3*x4)*(x0*pow(x1,2) - x0*x1*x2 - x0*x1*x3 + x0*x2*x3 - pow(x1,2)*x3 + x1*x2*x3 + x1*pow(x3,2) - x2*pow(x3,2))*(pow(x0,2)*x1 - pow(x0,2)*x2 - x0*x1*x2 - x0*x1*x3 + x0*pow(x2,2) + x0*x2*x3 + x1*x2*x3 - pow(x2,2)*x3));}

		else if (deg == 3) {return c1/(pow(x0,2)*x1 - pow(x0,2)*x2 - 2*x0*x1*x2 + 2*x0*pow(x2,2) + x1*pow(x2,2) - pow(x2,3)) - c2/(pow(x0,2)*x1 - pow(x0,2)*x2 - x0*x1*x2 - x0*x1*x3 + x0*pow(x2,2) + x0*x2*x3 + x1*x2*x3 - pow(x2,2)*x3) - c2/(x0*pow(x1,2) - x0*x1*x2 - x0*x1*x3 + x0*x2*x3 - pow(x1,2)*x3 + x1*x2*x3 + x1*pow(x3,2) - x2*pow(x3,2)) - c2/(pow(x0,2)*x1 - pow(x0,2)*x2 - 2*x0*x1*x2 + 2*x0*pow(x2,2) + x1*pow(x2,2) - pow(x2,3)) + c3/(pow(x0,2)*x1 - pow(x0,2)*x2 - x0*x1*x2 - x0*x1*x3 + x0*pow(x2,2) + x0*x2*x3 + x1*x2*x3 - pow(x2,2)*x3) + c3/(x0*pow(x1,2) - x0*x1*x2 - x0*x1*x3 + x0*x2*x3 - pow(x1,2)*x3 + x1*x2*x3 + x1*pow(x3,2) - x2*pow(x3,2)) + c3/(pow(x1,3) - pow(x1,2)*x2 - pow(x1,2)*x3 - pow(x1,2)*x4 + x1*x2*x3 + x1*x2*x4 + x1*x3*x4 - x2*x3*x4) - c4/(pow(x1,3) - pow(x1,2)*x2 - pow(x1,2)*x3 - pow(x1,2)*x4 + x1*x2*x3 + x1*x2*x4 + x1*x3*x4 - x2*x3*x4);}
	}
	else if (ibin == 2) {

		if (deg == 0) {return -c2*pow(x3,3)/(x0*x1*x2 - x0*x1*x3 - x0*x2*x3 + x0*pow(x3,2) - x1*x2*x3 + x1*pow(x3,2) + x2*pow(x3,2) - pow(x3,3)) + c3*x0*pow(x3,2)/(x0*x1*x2 - x0*x1*x3 - x0*x2*x3 + x0*pow(x3,2) - x1*x2*x3 + x1*pow(x3,2) + x2*pow(x3,2) - pow(x3,3)) + c3*x1*x3*x4/(pow(x1,2)*x2 - pow(x1,2)*x3 - x1*x2*x3 - x1*x2*x4 + x1*pow(x3,2) + x1*x3*x4 + x2*x3*x4 - pow(x3,2)*x4) + c3*x2*pow(x4,2)/(x1*pow(x2,2) - x1*x2*x3 - x1*x2*x4 + x1*x3*x4 - pow(x2,2)*x4 + x2*x3*x4 + x2*pow(x4,2) - x3*pow(x4,2)) - c4*pow(x1,2)*x3/(pow(x1,2)*x2 - pow(x1,2)*x3 - x1*x2*x3 - x1*x2*x4 + x1*pow(x3,2) + x1*x3*x4 + x2*x3*x4 - pow(x3,2)*x4) - c4*x1*x2*x4/(x1*pow(x2,2) - x1*x2*x3 - x1*x2*x4 + x1*x3*x4 - pow(x2,2)*x4 + x2*x3*x4 + x2*pow(x4,2) - x3*pow(x4,2)) - c4*pow(x2,2)*x5/(pow(x2,3) - pow(x2,2)*x3 - pow(x2,2)*x4 - pow(x2,2)*x5 + x2*x3*x4 + x2*x3*x5 + x2*x4*x5 - x3*x4*x5) + c5*pow(x2,3)/(pow(x2,3) - pow(x2,2)*x3 - pow(x2,2)*x4 - pow(x2,2)*x5 + x2*x3*x4 + x2*x3*x5 + x2*x4*x5 - x3*x4*x5);}

		else if (deg == 1) {return (x2*(c4*x2 + 2*c4*x5 - 3*c5*x2)*(x1*pow(x2,2) - x1*x2*x3 - x1*x2*x4 + x1*x3*x4 - pow(x2,2)*x4 + x2*x3*x4 + x2*pow(x4,2) - x3*pow(x4,2))*(pow(x1,2)*x2 - pow(x1,2)*x3 - x1*x2*x3 - x1*x2*x4 + x1*pow(x3,2) + x1*x3*x4 + x2*x3*x4 - pow(x3,2)*x4)*(x0*x1*x2 - x0*x1*x3 - x0*x2*x3 + x0*pow(x3,2) - x1*x2*x3 + x1*pow(x3,2) + x2*pow(x3,2) - pow(x3,3)) + x3*(3*c2*x3 - 2*c3*x0 - c3*x3)*(pow(x2,3) - pow(x2,2)*x3 - pow(x2,2)*x4 - pow(x2,2)*x5 + x2*x3*x4 + x2*x3*x5 + x2*x4*x5 - x3*x4*x5)*(x1*pow(x2,2) - x1*x2*x3 - x1*x2*x4 + x1*x3*x4 - pow(x2,2)*x4 + x2*x3*x4 + x2*pow(x4,2) - x3*pow(x4,2))*(pow(x1,2)*x2 - pow(x1,2)*x3 - x1*x2*x3 - x1*x2*x4 + x1*pow(x3,2) + x1*x3*x4 + x2*x3*x4 - pow(x3,2)*x4) + (-c3*x1*x3 - c3*x1*x4 - c3*x3*x4 + c4*pow(x1,2) + 2*c4*x1*x3)*(pow(x2,3) - pow(x2,2)*x3 - pow(x2,2)*x4 - pow(x2,2)*x5 + x2*x3*x4 + x2*x3*x5 + x2*x4*x5 - x3*x4*x5)*(x1*pow(x2,2) - x1*x2*x3 - x1*x2*x4 + x1*x3*x4 - pow(x2,2)*x4 + x2*x3*x4 + x2*pow(x4,2) - x3*pow(x4,2))*(x0*x1*x2 - x0*x1*x3 - x0*x2*x3 + x0*pow(x3,2) - x1*x2*x3 + x1*pow(x3,2) + x2*pow(x3,2) - pow(x3,3)) + (-2*c3*x2*x4 - c3*pow(x4,2) + c4*x1*x2 + c4*x1*x4 + c4*x2*x4)*(pow(x2,3) - pow(x2,2)*x3 - pow(x2,2)*x4 - pow(x2,2)*x5 + x2*x3*x4 + x2*x3*x5 + x2*x4*x5 - x3*x4*x5)*(pow(x1,2)*x2 - pow(x1,2)*x3 - x1*x2*x3 - x1*x2*x4 + x1*pow(x3,2) + x1*x3*x4 + x2*x3*x4 - pow(x3,2)*x4)*(x0*x1*x2 - x0*x1*x3 - x0*x2*x3 + x0*pow(x3,2) - x1*x2*x3 + x1*pow(x3,2) + x2*pow(x3,2) - pow(x3,3)))/((pow(x2,3) - pow(x2,2)*x3 - pow(x2,2)*x4 - pow(x2,2)*x5 + x2*x3*x4 + x2*x3*x5 + x2*x4*x5 - x3*x4*x5)*(x1*pow(x2,2) - x1*x2*x3 - x1*x2*x4 + x1*x3*x4 - pow(x2,2)*x4 + x2*x3*x4 + x2*pow(x4,2) - x3*pow(x4,2))*(pow(x1,2)*x2 - pow(x1,2)*x3 - x1*x2*x3 - x1*x2*x4 + x1*pow(x3,2) + x1*x3*x4 + x2*x3*x4 - pow(x3,2)*x4)*(x0*x1*x2 - x0*x1*x3 - x0*x2*x3 + x0*pow(x3,2) - x1*x2*x3 + x1*pow(x3,2) + x2*pow(x3,2) - pow(x3,3)));}

		else if (deg == 2) {return ((-3*c2*x3 + c3*x0 + 2*c3*x3)*(pow(x2,3) - pow(x2,2)*x3 - pow(x2,2)*x4 - pow(x2,2)*x5 + x2*x3*x4 + x2*x3*x5 + x2*x4*x5 - x3*x4*x5)*(x1*pow(x2,2) - x1*x2*x3 - x1*x2*x4 + x1*x3*x4 - pow(x2,2)*x4 + x2*x3*x4 + x2*pow(x4,2) - x3*pow(x4,2))*(pow(x1,2)*x2 - pow(x1,2)*x3 - x1*x2*x3 - x1*x2*x4 + x1*pow(x3,2) + x1*x3*x4 + x2*x3*x4 - pow(x3,2)*x4) + (-2*c4*x2 - c4*x5 + 3*c5*x2)*(x1*pow(x2,2) - x1*x2*x3 - x1*x2*x4 + x1*x3*x4 - pow(x2,2)*x4 + x2*x3*x4 + x2*pow(x4,2) - x3*pow(x4,2))*(pow(x1,2)*x2 - pow(x1,2)*x3 - x1*x2*x3 - x1*x2*x4 + x1*pow(x3,2) + x1*x3*x4 + x2*x3*x4 - pow(x3,2)*x4)*(x0*x1*x2 - x0*x1*x3 - x0*x2*x3 + x0*pow(x3,2) - x1*x2*x3 + x1*pow(x3,2) + x2*pow(x3,2) - pow(x3,3)) + (c3*x1 + c3*x3 + c3*x4 - 2*c4*x1 - c4*x3)*(pow(x2,3) - pow(x2,2)*x3 - pow(x2,2)*x4 - pow(x2,2)*x5 + x2*x3*x4 + x2*x3*x5 + x2*x4*x5 - x3*x4*x5)*(x1*pow(x2,2) - x1*x2*x3 - x1*x2*x4 + x1*x3*x4 - pow(x2,2)*x4 + x2*x3*x4 + x2*pow(x4,2) - x3*pow(x4,2))*(x0*x1*x2 - x0*x1*x3 - x0*x2*x3 + x0*pow(x3,2) - x1*x2*x3 + x1*pow(x3,2) + x2*pow(x3,2) - pow(x3,3)) + (c3*x2 + 2*c3*x4 - c4*x1 - c4*x2 - c4*x4)*(pow(x2,3) - pow(x2,2)*x3 - pow(x2,2)*x4 - pow(x2,2)*x5 + x2*x3*x4 + x2*x3*x5 + x2*x4*x5 - x3*x4*x5)*(pow(x1,2)*x2 - pow(x1,2)*x3 - x1*x2*x3 - x1*x2*x4 + x1*pow(x3,2) + x1*x3*x4 + x2*x3*x4 - pow(x3,2)*x4)*(x0*x1*x2 - x0*x1*x3 - x0*x2*x3 + x0*pow(x3,2) - x1*x2*x3 + x1*pow(x3,2) + x2*pow(x3,2) - pow(x3,3)))/((pow(x2,3) - pow(x2,2)*x3 - pow(x2,2)*x4 - pow(x2,2)*x5 + x2*x3*x4 + x2*x3*x5 + x2*x4*x5 - x3*x4*x5)*(x1*pow(x2,2) - x1*x2*x3 - x1*x2*x4 + x1*x3*x4 - pow(x2,2)*x4 + x2*x3*x4 + x2*pow(x4,2) - x3*pow(x4,2))*(pow(x1,2)*x2 - pow(x1,2)*x3 - x1*x2*x3 - x1*x2*x4 + x1*pow(x3,2) + x1*x3*x4 + x2*x3*x4 - pow(x3,2)*x4)*(x0*x1*x2 - x0*x1*x3 - x0*x2*x3 + x0*pow(x3,2) - x1*x2*x3 + x1*pow(x3,2) + x2*pow(x3,2) - pow(x3,3)));}

		else if (deg == 3) {return c2/(x0*x1*x2 - x0*x1*x3 - x0*x2*x3 + x0*pow(x3,2) - x1*x2*x3 + x1*pow(x3,2) + x2*pow(x3,2) - pow(x3,3)) - c3/(x0*x1*x2 - x0*x1*x3 - x0*x2*x3 + x0*pow(x3,2) - x1*x2*x3 + x1*pow(x3,2) + x2*pow(x3,2) - pow(x3,3)) - c3/(pow(x1,2)*x2 - pow(x1,2)*x3 - x1*x2*x3 - x1*x2*x4 + x1*pow(x3,2) + x1*x3*x4 + x2*x3*x4 - pow(x3,2)*x4) - c3/(x1*pow(x2,2) - x1*x2*x3 - x1*x2*x4 + x1*x3*x4 - pow(x2,2)*x4 + x2*x3*x4 + x2*pow(x4,2) - x3*pow(x4,2)) + c4/(pow(x1,2)*x2 - pow(x1,2)*x3 - x1*x2*x3 - x1*x2*x4 + x1*pow(x3,2) + x1*x3*x4 + x2*x3*x4 - pow(x3,2)*x4) + c4/(x1*pow(x2,2) - x1*x2*x3 - x1*x2*x4 + x1*x3*x4 - pow(x2,2)*x4 + x2*x3*x4 + x2*pow(x4,2) - x3*pow(x4,2)) + c4/(pow(x2,3) - pow(x2,2)*x3 - pow(x2,2)*x4 - pow(x2,2)*x5 + x2*x3*x4 + x2*x3*x5 + x2*x4*x5 - x3*x4*x5) - c5/(pow(x2,3) - pow(x2,2)*x3 - pow(x2,2)*x4 - pow(x2,2)*x5 + x2*x3*x4 + x2*x3*x5 + x2*x4*x5 - x3*x4*x5);}
	}
	else if (ibin == 3) {

		if (deg == 0) {return -c3*pow(x4,3)/(x1*x2*x3 - x1*x2*x4 - x1*x3*x4 + x1*pow(x4,2) - x2*x3*x4 + x2*pow(x4,2) + x3*pow(x4,2) - pow(x4,3)) + c4*x1*pow(x4,2)/(x1*x2*x3 - x1*x2*x4 - x1*x3*x4 + x1*pow(x4,2) - x2*x3*x4 + x2*pow(x4,2) + x3*pow(x4,2) - pow(x4,3)) + c4*x2*x4*x5/(pow(x2,2)*x3 - pow(x2,2)*x4 - x2*x3*x4 - x2*x3*x5 + x2*pow(x4,2) + x2*x4*x5 + x3*x4*x5 - pow(x4,2)*x5) + c4*x3*pow(x5,2)/(x2*pow(x3,2) - x2*x3*x4 - x2*x3*x5 + x2*x4*x5 - pow(x3,2)*x5 + x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2)) - c5*pow(x2,2)*x4/(pow(x2,2)*x3 - pow(x2,2)*x4 - x2*x3*x4 - x2*x3*x5 + x2*pow(x4,2) + x2*x4*x5 + x3*x4*x5 - pow(x4,2)*x5) - c5*x2*x3*x5/(x2*pow(x3,2) - x2*x3*x4 - x2*x3*x5 + x2*x4*x5 - pow(x3,2)*x5 + x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2)) - c5*pow(x3,2)*x5/(pow(x3,3) - pow(x3,2)*x4 - 2*pow(x3,2)*x5 + 2*x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2)) + c6*pow(x3,3)/(pow(x3,3) - pow(x3,2)*x4 - 2*pow(x3,2)*x5 + 2*x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2));}

		else if (deg == 1) {return (x3*(c5*x3 + 2*c5*x5 - 3*c6*x3)*(x2*pow(x3,2) - x2*x3*x4 - x2*x3*x5 + x2*x4*x5 - pow(x3,2)*x5 + x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2))*(pow(x2,2)*x3 - pow(x2,2)*x4 - x2*x3*x4 - x2*x3*x5 + x2*pow(x4,2) + x2*x4*x5 + x3*x4*x5 - pow(x4,2)*x5)*(x1*x2*x3 - x1*x2*x4 - x1*x3*x4 + x1*pow(x4,2) - x2*x3*x4 + x2*pow(x4,2) + x3*pow(x4,2) - pow(x4,3)) + x4*(3*c3*x4 - 2*c4*x1 - c4*x4)*(pow(x3,3) - pow(x3,2)*x4 - 2*pow(x3,2)*x5 + 2*x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2))*(x2*pow(x3,2) - x2*x3*x4 - x2*x3*x5 + x2*x4*x5 - pow(x3,2)*x5 + x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2))*(pow(x2,2)*x3 - pow(x2,2)*x4 - x2*x3*x4 - x2*x3*x5 + x2*pow(x4,2) + x2*x4*x5 + x3*x4*x5 - pow(x4,2)*x5) + (-c4*x2*x4 - c4*x2*x5 - c4*x4*x5 + c5*pow(x2,2) + 2*c5*x2*x4)*(pow(x3,3) - pow(x3,2)*x4 - 2*pow(x3,2)*x5 + 2*x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2))*(x2*pow(x3,2) - x2*x3*x4 - x2*x3*x5 + x2*x4*x5 - pow(x3,2)*x5 + x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2))*(x1*x2*x3 - x1*x2*x4 - x1*x3*x4 + x1*pow(x4,2) - x2*x3*x4 + x2*pow(x4,2) + x3*pow(x4,2) - pow(x4,3)) + (-2*c4*x3*x5 - c4*pow(x5,2) + c5*x2*x3 + c5*x2*x5 + c5*x3*x5)*(pow(x3,3) - pow(x3,2)*x4 - 2*pow(x3,2)*x5 + 2*x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2))*(pow(x2,2)*x3 - pow(x2,2)*x4 - x2*x3*x4 - x2*x3*x5 + x2*pow(x4,2) + x2*x4*x5 + x3*x4*x5 - pow(x4,2)*x5)*(x1*x2*x3 - x1*x2*x4 - x1*x3*x4 + x1*pow(x4,2) - x2*x3*x4 + x2*pow(x4,2) + x3*pow(x4,2) - pow(x4,3)))/((pow(x3,3) - pow(x3,2)*x4 - 2*pow(x3,2)*x5 + 2*x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2))*(x2*pow(x3,2) - x2*x3*x4 - x2*x3*x5 + x2*x4*x5 - pow(x3,2)*x5 + x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2))*(pow(x2,2)*x3 - pow(x2,2)*x4 - x2*x3*x4 - x2*x3*x5 + x2*pow(x4,2) + x2*x4*x5 + x3*x4*x5 - pow(x4,2)*x5)*(x1*x2*x3 - x1*x2*x4 - x1*x3*x4 + x1*pow(x4,2) - x2*x3*x4 + x2*pow(x4,2) + x3*pow(x4,2) - pow(x4,3)));}

		else if (deg == 2) {return ((-3*c3*x4 + c4*x1 + 2*c4*x4)*(pow(x3,3) - pow(x3,2)*x4 - 2*pow(x3,2)*x5 + 2*x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2))*(x2*pow(x3,2) - x2*x3*x4 - x2*x3*x5 + x2*x4*x5 - pow(x3,2)*x5 + x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2))*(pow(x2,2)*x3 - pow(x2,2)*x4 - x2*x3*x4 - x2*x3*x5 + x2*pow(x4,2) + x2*x4*x5 + x3*x4*x5 - pow(x4,2)*x5) + (-2*c5*x3 - c5*x5 + 3*c6*x3)*(x2*pow(x3,2) - x2*x3*x4 - x2*x3*x5 + x2*x4*x5 - pow(x3,2)*x5 + x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2))*(pow(x2,2)*x3 - pow(x2,2)*x4 - x2*x3*x4 - x2*x3*x5 + x2*pow(x4,2) + x2*x4*x5 + x3*x4*x5 - pow(x4,2)*x5)*(x1*x2*x3 - x1*x2*x4 - x1*x3*x4 + x1*pow(x4,2) - x2*x3*x4 + x2*pow(x4,2) + x3*pow(x4,2) - pow(x4,3)) + (c4*x2 + c4*x4 + c4*x5 - 2*c5*x2 - c5*x4)*(pow(x3,3) - pow(x3,2)*x4 - 2*pow(x3,2)*x5 + 2*x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2))*(x2*pow(x3,2) - x2*x3*x4 - x2*x3*x5 + x2*x4*x5 - pow(x3,2)*x5 + x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2))*(x1*x2*x3 - x1*x2*x4 - x1*x3*x4 + x1*pow(x4,2) - x2*x3*x4 + x2*pow(x4,2) + x3*pow(x4,2) - pow(x4,3)) + (c4*x3 + 2*c4*x5 - c5*x2 - c5*x3 - c5*x5)*(pow(x3,3) - pow(x3,2)*x4 - 2*pow(x3,2)*x5 + 2*x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2))*(pow(x2,2)*x3 - pow(x2,2)*x4 - x2*x3*x4 - x2*x3*x5 + x2*pow(x4,2) + x2*x4*x5 + x3*x4*x5 - pow(x4,2)*x5)*(x1*x2*x3 - x1*x2*x4 - x1*x3*x4 + x1*pow(x4,2) - x2*x3*x4 + x2*pow(x4,2) + x3*pow(x4,2) - pow(x4,3)))/((pow(x3,3) - pow(x3,2)*x4 - 2*pow(x3,2)*x5 + 2*x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2))*(x2*pow(x3,2) - x2*x3*x4 - x2*x3*x5 + x2*x4*x5 - pow(x3,2)*x5 + x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2))*(pow(x2,2)*x3 - pow(x2,2)*x4 - x2*x3*x4 - x2*x3*x5 + x2*pow(x4,2) + x2*x4*x5 + x3*x4*x5 - pow(x4,2)*x5)*(x1*x2*x3 - x1*x2*x4 - x1*x3*x4 + x1*pow(x4,2) - x2*x3*x4 + x2*pow(x4,2) + x3*pow(x4,2) - pow(x4,3)));}

		else if (deg == 3) {return c3/(x1*x2*x3 - x1*x2*x4 - x1*x3*x4 + x1*pow(x4,2) - x2*x3*x4 + x2*pow(x4,2) + x3*pow(x4,2) - pow(x4,3)) - c4/(x1*x2*x3 - x1*x2*x4 - x1*x3*x4 + x1*pow(x4,2) - x2*x3*x4 + x2*pow(x4,2) + x3*pow(x4,2) - pow(x4,3)) - c4/(pow(x2,2)*x3 - pow(x2,2)*x4 - x2*x3*x4 - x2*x3*x5 + x2*pow(x4,2) + x2*x4*x5 + x3*x4*x5 - pow(x4,2)*x5) - c4/(x2*pow(x3,2) - x2*x3*x4 - x2*x3*x5 + x2*x4*x5 - pow(x3,2)*x5 + x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2)) + c5/(pow(x2,2)*x3 - pow(x2,2)*x4 - x2*x3*x4 - x2*x3*x5 + x2*pow(x4,2) + x2*x4*x5 + x3*x4*x5 - pow(x4,2)*x5) + c5/(x2*pow(x3,2) - x2*x3*x4 - x2*x3*x5 + x2*x4*x5 - pow(x3,2)*x5 + x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2)) + c5/(pow(x3,3) - pow(x3,2)*x4 - 2*pow(x3,2)*x5 + 2*x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2)) - c6/(pow(x3,3) - pow(x3,2)*x4 - 2*pow(x3,2)*x5 + 2*x3*x4*x5 + x3*pow(x5,2) - x4*pow(x5,2));}
	}
	else if (ibin == 4) {

		if (deg == 0) {return -c4*pow(x5,3)/(x2*x3*x4 - x2*x3*x5 - x2*x4*x5 + x2*pow(x5,2) - x3*x4*x5 + x3*pow(x5,2) + x4*pow(x5,2) - pow(x5,3)) + c5*x2*pow(x5,2)/(x2*x3*x4 - x2*x3*x5 - x2*x4*x5 + x2*pow(x5,2) - x3*x4*x5 + x3*pow(x5,2) + x4*pow(x5,2) - pow(x5,3)) + c5*x3*pow(x5,2)/(pow(x3,2)*x4 - pow(x3,2)*x5 - 2*x3*x4*x5 + 2*x3*pow(x5,2) + x4*pow(x5,2) - pow(x5,3)) + c5*x4*pow(x5,2)/(x3*pow(x4,2) - 2*x3*x4*x5 + x3*pow(x5,2) - pow(x4,2)*x5 + 2*x4*pow(x5,2) - pow(x5,3)) - c6*pow(x3,2)*x5/(pow(x3,2)*x4 - pow(x3,2)*x5 - 2*x3*x4*x5 + 2*x3*pow(x5,2) + x4*pow(x5,2) - pow(x5,3)) - c6*x3*x4*x5/(x3*pow(x4,2) - 2*x3*x4*x5 + x3*pow(x5,2) - pow(x4,2)*x5 + 2*x4*pow(x5,2) - pow(x5,3)) - c6*pow(x4,2)*x5/(pow(x4,3) - 3*pow(x4,2)*x5 + 3*x4*pow(x5,2) - pow(x5,3)) + c7*pow(x4,3)/(pow(x4,3) - 3*pow(x4,2)*x5 + 3*x4*pow(x5,2) - pow(x5,3));}

		else if (deg == 1) {return 3*(c4*x3*pow(x4,2)*pow(x5,2) - 2*c4*x3*x4*pow(x5,3) + c4*x3*pow(x5,4) - c4*pow(x4,2)*pow(x5,3) + 2*c4*x4*pow(x5,4) - c4*pow(x5,5) - 2*c5*x2*x3*pow(x4,2)*x5 + 3*c5*x2*x3*x4*pow(x5,2) - c5*x2*x3*pow(x5,3) + c5*x2*pow(x4,2)*pow(x5,2) - c5*x2*x4*pow(x5,3) + c5*x3*pow(x4,2)*pow(x5,2) - c5*x3*x4*pow(x5,3) - c5*x4*pow(x5,4) + c5*pow(x5,5) + c6*x2*pow(x3,2)*pow(x4,2) - 3*c6*x2*x3*x4*pow(x5,2) + c6*x2*x3*pow(x5,3) + c6*x2*x4*pow(x5,3) - c6*pow(x3,2)*pow(x4,2)*x5 + 3*c6*x3*x4*pow(x5,3) - c6*x3*pow(x5,4) - c6*x4*pow(x5,4) - c7*x2*pow(x3,2)*pow(x4,2) + 2*c7*x2*x3*pow(x4,2)*x5 - c7*x2*pow(x4,2)*pow(x5,2) + c7*pow(x3,2)*pow(x4,2)*x5 - 2*c7*x3*pow(x4,2)*pow(x5,2) + c7*pow(x4,2)*pow(x5,3))/(x2*pow(x3,2)*pow(x4,3) - 3*x2*pow(x3,2)*pow(x4,2)*x5 + 3*x2*pow(x3,2)*x4*pow(x5,2) - x2*pow(x3,2)*pow(x5,3) - 2*x2*x3*pow(x4,3)*x5 + 6*x2*x3*pow(x4,2)*pow(x5,2) - 6*x2*x3*x4*pow(x5,3) + 2*x2*x3*pow(x5,4) + x2*pow(x4,3)*pow(x5,2) - 3*x2*pow(x4,2)*pow(x5,3) + 3*x2*x4*pow(x5,4) - x2*pow(x5,5) - pow(x3,2)*pow(x4,3)*x5 + 3*pow(x3,2)*pow(x4,2)*pow(x5,2) - 3*pow(x3,2)*x4*pow(x5,3) + pow(x3,2)*pow(x5,4) + 2*x3*pow(x4,3)*pow(x5,2) - 6*x3*pow(x4,2)*pow(x5,3) + 6*x3*x4*pow(x5,4) - 2*x3*pow(x5,5) - pow(x4,3)*pow(x5,3) + 3*pow(x4,2)*pow(x5,4) - 3*x4*pow(x5,5) + pow(x5,6));}

		else if (deg == 2) {return (-3*c4*x3*pow(x4,2)*x5 + 6*c4*x3*x4*pow(x5,2) - 3*c4*x3*pow(x5,3) + 3*c4*pow(x4,2)*pow(x5,2) - 6*c4*x4*pow(x5,3) + 3*c4*pow(x5,4) + 3*c5*x2*x3*pow(x4,2) - 3*c5*x2*x3*x4*x5 - 3*c5*x2*x4*pow(x5,2) + 3*c5*x2*pow(x5,3) - 3*c5*x3*x4*pow(x5,2) + 3*c5*x3*pow(x5,3) - 3*c5*pow(x4,2)*pow(x5,2) + 9*c5*x4*pow(x5,3) - 6*c5*pow(x5,4) - 3*c6*x2*pow(x3,2)*x4 - 3*c6*x2*x3*pow(x4,2) + 9*c6*x2*x3*x4*x5 - 3*c6*x2*pow(x5,3) + 3*c6*pow(x3,2)*x4*x5 + 3*c6*x3*pow(x4,2)*x5 - 9*c6*x3*x4*pow(x5,2) + 3*c6*pow(x5,4) + 3*c7*x2*pow(x3,2)*x4 - 6*c7*x2*x3*x4*x5 + 3*c7*x2*x4*pow(x5,2) - 3*c7*pow(x3,2)*x4*x5 + 6*c7*x3*x4*pow(x5,2) - 3*c7*x4*pow(x5,3))/(x2*pow(x3,2)*pow(x4,3) - 3*x2*pow(x3,2)*pow(x4,2)*x5 + 3*x2*pow(x3,2)*x4*pow(x5,2) - x2*pow(x3,2)*pow(x5,3) - 2*x2*x3*pow(x4,3)*x5 + 6*x2*x3*pow(x4,2)*pow(x5,2) - 6*x2*x3*x4*pow(x5,3) + 2*x2*x3*pow(x5,4) + x2*pow(x4,3)*pow(x5,2) - 3*x2*pow(x4,2)*pow(x5,3) + 3*x2*x4*pow(x5,4) - x2*pow(x5,5) - pow(x3,2)*pow(x4,3)*x5 + 3*pow(x3,2)*pow(x4,2)*pow(x5,2) - 3*pow(x3,2)*x4*pow(x5,3) + pow(x3,2)*pow(x5,4) + 2*x3*pow(x4,3)*pow(x5,2) - 6*x3*pow(x4,2)*pow(x5,3) + 6*x3*x4*pow(x5,4) - 2*x3*pow(x5,5) - pow(x4,3)*pow(x5,3) + 3*pow(x4,2)*pow(x5,4) - 3*x4*pow(x5,5) + pow(x5,6));}

		else if (deg == 3) {return c4/(x2*x3*x4 - x2*x3*x5 - x2*x4*x5 + x2*pow(x5,2) - x3*x4*x5 + x3*pow(x5,2) + x4*pow(x5,2) - pow(x5,3)) - c5/(x2*x3*x4 - x2*x3*x5 - x2*x4*x5 + x2*pow(x5,2) - x3*x4*x5 + x3*pow(x5,2) + x4*pow(x5,2) - pow(x5,3)) - c5/(pow(x3,2)*x4 - pow(x3,2)*x5 - 2*x3*x4*x5 + 2*x3*pow(x5,2) + x4*pow(x5,2) - pow(x5,3)) - c5/(x3*pow(x4,2) - 2*x3*x4*x5 + x3*pow(x5,2) - pow(x4,2)*x5 + 2*x4*pow(x5,2) - pow(x5,3)) + c6/(pow(x3,2)*x4 - pow(x3,2)*x5 - 2*x3*x4*x5 + 2*x3*pow(x5,2) + x4*pow(x5,2) - pow(x5,3)) + c6/(x3*pow(x4,2) - 2*x3*x4*x5 + x3*pow(x5,2) - pow(x4,2)*x5 + 2*x4*pow(x5,2) - pow(x5,3)) + c6/(pow(x4,3) - 3*pow(x4,2)*x5 + 3*x4*pow(x5,2) - pow(x5,3)) - c7/(pow(x4,3) - 3*pow(x4,2)*x5 + 3*x4*pow(x5,2) - pow(x5,3));}
	}

	return 0.;

}

// ---------------------------------------------------

Double_t SplineTAcc::evaluate() const 
 { 

	return polynomial(t);

}
