/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "AngAbsFunc.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 
#include "RooRealVar.h"
#include "RooArgList.h"


ClassImp(AngAbsFunc) 


AngAbsFunc::AngAbsFunc(const char *name, const char *title,
			       RooAbsReal& _c1,
			       RooAbsReal& _c2,
			       RooAbsReal& _ph,
			       RooArgList& _accTH_coefList,
			       RooArgList& _accPH_coefList):
    RooAbsReal(name,title), 
    c1("c1","c1",this,_c1),
    c2("c2","c2",this,_c2),
    ph("ph","ph",this,_ph),
    accTH_coefList("accTH_coefList","List of accTH coefficients",this),
    accPH_coefList("accPH_coefList","List of accPH coefficients",this)
{ 

  
  TIterator* _coefIterTH = _accTH_coefList.createIterator();
  TIterator* _coefIterPH = _accPH_coefList.createIterator();
  
  coefIterTH = accTH_coefList.createIterator();
  coefIterPH = accPH_coefList.createIterator();


  RooAbsArg* coef ;

  while((coef = (RooAbsArg*)_coefIterTH->Next())) {
    if (!dynamic_cast<RooAbsReal*>(coef)) {
      cout << "RooPolynomial::ctor(" << GetName() << ") ERROR: coefficient " << coef->GetName() 
	   << " is not of type RooAbsReal" << endl ;
      assert(0) ;
    }
    accTH_coefList.add(*coef) ;
  }

  

  while((coef = (RooAbsArg*)_coefIterPH->Next())) {
    if (!dynamic_cast<RooAbsReal*>(coef)) {
      cout << "RooPolynomial::ctor(" << GetName() << ") ERROR: coefficient " << coef->GetName() 
	   << " is not of type RooAbsReal" << endl ;
      assert(0) ;
    }

    accPH_coefList.add(*coef) ;
  }

  delete _coefIterTH ;
  delete _coefIterPH ;
}


AngAbsFunc::AngAbsFunc(const AngAbsFunc& other, const char* name):
  RooAbsReal(other,name), 
  c1("c1",this,other.c1),
  c2("c2",this,other.c2),
  ph("ph",this,other.ph),
  accTH_coefList("accTH_coefList",this,other.accTH_coefList),
  accPH_coefList("accPH_coefList",this,other.accPH_coefList)
	{ 

	  //cout << "Clonando"<< endl;
	  coefIterTH = accTH_coefList.createIterator();
	  coefIterPH = accPH_coefList.createIterator();


	} 







Double_t AngAbsFunc::getAccTHCoefs(Double_t* coefsTH)const
{
  Int_t i = 0;
  
  RooAbsReal* coefreal;

  coefIterTH->Reset();

  while((coefreal = (RooAbsReal*)coefIterTH->Next())){
  
    coefsTH[i++]= coefreal->getVal();//nsetTH);

  }

  return 1.;

}


Double_t AngAbsFunc::getAccPHCoefs(Double_t* coefsPH)const 
{
  Int_t i = 0;
  
  RooAbsReal* coefreal;

  coefIterPH->Reset();
  //const RooArgSet* nsetPH = accPH_coefList.nset() ;

  while((coefreal = (RooAbsReal*)coefIterPH->Next())){
    coefsPH[i++]= coefreal->getVal();//nsetTH);
    
  }

  return 1;

} 








 Int_t AngAbsFunc::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const  
 { 
   // LIST HERE OVER WHICH VARIABLES ANALYTICAL INTEGRATION IS SUPPORTED, 
   // ASSIGN A NUMERIC CODE FOR EACH SUPPORTED (SET OF) PARAMETERS 
   // THE EXAMPLE BELOW ASSIGNS CODE 1 TO INTEGRATION OVER VARIABLE X
   // YOU CAN ALSO IMPLEMENT MORE THAN ONE ANALYTICAL INTEGRAL BY REPEATING THE matchArgs 
   // EXPRESSION MULTIPLE TIMES

   // if (matchArgs(allVars,analVars,x)) return 1 ; 

   if (matchArgs(allVars,analVars,c1,c2,ph)) return 1 ; 
   if (matchArgs(allVars,analVars,c1,c2   )) return 2 ;
   if (matchArgs(allVars,analVars,c1   ,ph)) return 3 ;
   if (matchArgs(allVars,analVars,   c2,ph)) return 4 ;
   if (matchArgs(allVars,analVars,c1      )) return 5 ;
   if (matchArgs(allVars,analVars,   c2   )) return 6 ;
   if (matchArgs(allVars,analVars,      ph)) return 7 ;


   return 0 ; 
 } 



// Double_t AngAbsFunc::analyticalIntegral(Int_t code, const char* rangeName) const 
// {
//   Double_t integral = 0.;

//   return integral;
//   }
