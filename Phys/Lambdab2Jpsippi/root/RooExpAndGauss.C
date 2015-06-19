 /***************************************************************************** 
  * Project: RooFit                                                           * 
  *                                                                           * 
  * Copyright (c) 2000-2005, Regents of the University of California          * 
  *                          and Stanford University. All rights reserved.    * 
  *                                                                           * 
  * Redistribution and use in source and binary forms,                        * 
  * with or without modification, are permitted according to the terms        * 
  * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             * 
  *****************************************************************************/ 

 // -- CLASS DESCRIPTION [PDF] -- 
 // Your description goes here... 

 #include <iostream> 

 #include "RooExpAndGauss.h" 
 #include "RooAbsReal.h" 

// ClassImp(RooExpAndGauss)   /// Had to remove that ???

 RooExpAndGauss::RooExpAndGauss(const char *name, const char *title, 
                        RooAbsReal& _m,
                        RooAbsReal& _m0,
                        RooAbsReal& _sigma,
                        RooAbsReal& _m1) :
   RooAbsPdf(name,title), 
   m("m","m",this,_m),
   m0("m0","m0",this,_m0),
   sigma("sigma","sigma",this,_sigma),
   m1("m1","m1",this,_m1)
 { 
 } 


 RooExpAndGauss::RooExpAndGauss(const RooExpAndGauss& other, const char* name) :  
   RooAbsPdf(other,name), 
   m("m",this,other.m),
   m0("m0",this,other.m0),
   sigma("sigma",this,other.sigma),
   m1("m1",this,other.m1)
 { 
 } 



 Double_t RooExpAndGauss::evaluate() const 
 { 
  
  Double_t r      = (m-m0)/sigma ;             // exponent of gaussian
  Double_t gauss  = exp(-0.5*r*r) ;            // actual value of gaussian
  //
  if ( m > m1 ) return gauss ; // gaussian

  Double_t r1     = (m1-m0)/sigma ;             // exponent of gaussian at m1
  Double_t gauss1 = exp(-0.5*r1*r1) ;           // actual value of gaussian at m1  
  Double_t slope  = -gauss1 * r1/sigma ;        // actual derivative of gaussian at m1
  //  cout << "EAG:: m=" << m << " m0=" << m0 << " s=" << sigma << " m1=" << m1<< " g=" 
  //       << gauss1 << " sl=" << slope << endl ;
  
  // exp : A e^(Bm) = gauss1 ;   A B e^(Bm) = slope -> B = slope/gauss ; ; A = gauss1 / e^(Bm) 

  Double_t B = slope/gauss1 ;
  Double_t A = gauss1/exp(B*m1) ;

  return A*exp(B*m) ;                // 
 } 



