#include "Riostream.h" 
#include "RooAbsPdf.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h"
#include "TF1.h"
#include <stdexcept>
#include "RooMath.h"
#include "PolTAcc.h"
#include "Splineclass.h"

Splineclass spl;

ClassImp(PolTAcc) 

// ---------------------------------------------------

 PolTAcc::PolTAcc(const char *name, const char *title,
                        RooAbsReal& _t,
                        RooAbsReal& _year_opt,
                        RooAbsReal& _trig_opt,
                        RooAbsReal& _wide_window) :
   RooAbsPdf(name,title),
   t("t","t",this,_t),
   year_opt("year_opt","year_opt",this,_year_opt),
   trig_opt("trig_opt","trig_opt",this,_trig_opt),
   wide_window("wide_window","wide_window",this,_wide_window)
 { 
 } 

// ---------------------------------------------------

 PolTAcc::PolTAcc(const PolTAcc& other, const char* name) :  
   RooAbsPdf(other,name),
   t("t",this,other.t),
   year_opt("year_opt",this,other.year_opt),
   trig_opt("trig_opt",this,other.trig_opt),
   wide_window("wide_window",this,other.wide_window)
 { 
 } 

// ---------------------------------------------------

Int_t PolTAcc::iBin(Double_t x) const 
 { 

	if (x < spl.knot(wide_window,1)) {return 0;}
	else if ((x >= spl.knot(wide_window,1)) and (x < spl.knot(wide_window,2))) {return 1;}
	else if ((x >= spl.knot(wide_window,2)) and (x < spl.knot(wide_window,3))) {return 2;}
	else if ((x >= spl.knot(wide_window,3)) and (x < spl.knot(wide_window,4))) {return 3;}
	else {return 4;}

}

// ---------------------------------------------------

Double_t PolTAcc::evaluate() const 
 { 

	return spl.coef(year_opt,trig_opt,wide_window,iBin(t),0)+t*spl.coef(year_opt,trig_opt,wide_window,iBin(t),1)+t*t*spl.coef(year_opt,trig_opt,wide_window,iBin(t),2)+t*t*t*spl.coef(year_opt,trig_opt,wide_window,iBin(t),3);

}
