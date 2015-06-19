/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "MassAbsFunc.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 
#include "TComplex.h"
#include "RooRealProxy.h"
#include "RooArgList.h"


#define qr 197.3


ClassImp(MassAbsFunc) 


  MassAbsFunc::MassAbsFunc(const char *name, const char *title,
			  RooAbsReal& _m1,
			  RooAbsReal& _m2,
			  RooAbsReal& _m_kst,
			  RooAbsReal& _m_kst0,
			  RooAbsReal& _g_kst,
			  RooAbsReal& _g_kst0,
			   RooAbsReal& _m_Bs,
			  RooArgList& _acc_coefList,
			  RooAbsReal& _norm):
    RooAbsReal(name,title), 
    m1("m1","m1",this,_m1),
    m2("m2","m2",this,_m2),
    m_kst("m_kst","m_kst",this,_m_kst),
    m_kst0("m_kst0","m_kst0",this,_m_kst0),
    g_kst("g_kst","g_kst",this,_g_kst),
    g_kst0("g_kst0","g_kst0",this,_g_kst0),
    m_Bs("m_Bs","m_Bs",this,_m_Bs),
    acc_coefList("acc_coefList","List of acc coefficients",this),
    norm("norm","norm",this,_norm)
{

  TIterator* _coefIter = _acc_coefList.createIterator();
  coefIter = acc_coefList.createIterator();

  RooAbsArg* coef ;

  while((coef = (RooAbsArg*)_coefIter->Next())) {
    if (!dynamic_cast<RooAbsReal*>(coef)) {
      cout << "RooPolynomial::ctor(" << GetName() << ") ERROR: coefficient " << coef->GetName() 
	   << " is not of type RooAbsReal" << endl ;
      assert(0) ;
    }
    acc_coefList.add(*coef) ;
  }

  delete _coefIter ;

}


 MassAbsFunc::MassAbsFunc(const MassAbsFunc& other, const char* name) :  
   RooAbsReal(other,name), 
   m1("m1",this,other.m1),
   m2("m2",this,other.m2),
   m_kst("m_kst",this,other.m_kst),
   m_kst0("m_kst0",this,other.m_kst0),
   g_kst("g_kst",this,other.g_kst),
   g_kst0("g_kst0",this,other.g_kst0),
   m_Bs("m_Bs",this,other.m_Bs),
   acc_coefList("acc_coefList",this,other.acc_coefList),
   norm("norm",this,other.norm)
 { 

   coefIter = acc_coefList.createIterator();

 } 



Double_t MassAbsFunc::getAcc() const
{

  Double_t coefs[2];

  Int_t i = 0;
  
  RooAbsReal* coefreal;

  coefIter->Reset();

  while((coefreal = (RooAbsReal*)coefIter->Next())){
  
    coefs[i++]= coefreal->getVal();//nsetTH);

  }


  Double_t acc_m1 = coefs[0] + coefs[1]*m1;
  Double_t acc_m2 = coefs[0] + coefs[1]*m2;

  return acc_m1*acc_m2;

}

TComplex MassAbsFunc::PWaveMass_2(Int_t indx) const 
 { 
   
   Double_t m;

   if (indx==1) m=m1;
   else if (indx==2) m=m2;
   else {
     cout << "Not valid index, must be 1(K*mass) or 2(K*b mass)" << endl;
     return 0.;
       }

   Double_t m0 = 1414;
   Double_t G0 = 232.;
   


   Double_t Q_kst = sqrt((m0*m0 - pow(m_kaon+m_pion,2))*(m0*m0 - pow(m_kaon-m_pion,2)))/(2*m0);

   Double_t Q_m = sqrt((m*m - pow(m_kaon+m_pion,2))*(m*m - pow(m_kaon-m_pion,2)))/(2*m);

   Double_t g1_m = G0*(m0/m)*((1+pow(r_kst*Q_kst,2))/(1+pow(r_kst*Q_m,2)))*pow(Q_m/Q_kst,3);
   
   Double_t g1_m_num = G0*m0*((1+pow(r_kst*Q_kst,2))/(1+pow(r_kst*Q_m,2)))*pow(Q_m/Q_kst,2)/Q_kst;
   
   // WITH m/q
   TComplex num(pow(m0,2)*G0*((1+pow(r_kst*Q_kst,2))/(1+pow(r_kst*Q_m,2)))*pow(Q_m,2)/pow(Q_kst,3),0);
   TComplex denom(m0*m0 - m*m, -m0*g1_m);
   

//    //WITHOUT m/q
//    TComplex num(m0*g1_m,0);
//    TComplex denom(m0*m0 - m*m, -m0*g1_m);

   TComplex BW = num/denom;//(m/Q_m)*m0*g1_m/((m0*m0 - m*m) - i*m0*g1_m);//m0*g1_m/((m0*m0 - m*m) - i*m0*g1_m);

//    cout << "G0: "<<G0<<endl;
//    cout << "r_kst: "<<r_kst<<endl;

//   Double_t phasespace = sqrt(2*pow(Q_m/m,3));


   return BW/sqrt(72.2562757614);

 }


TComplex MassAbsFunc::PWaveMass(Int_t indx) const 
 { 
   
   Double_t m;

   if (indx==1) m=m1;
   else if (indx==2) m=m2;
   else {
     cout << "Not valid index, must be 1(K*mass) or 2(K*b mass)" << endl;
     return 0.;
       }

   
   Double_t Q_kst = sqrt((m_kst*m_kst - pow(m_kaon+m_pion,2))*(m_kst*m_kst - pow(m_kaon-m_pion,2)))/(2*m_kst);

   Double_t Q_m = sqrt((m*m - pow(m_kaon+m_pion,2))*(m*m - pow(m_kaon-m_pion,2)))/(2*m);

   Double_t g1_m = g_kst*(m_kst/m)*((1+pow(r_kst*Q_kst,2))/(1+pow(r_kst*Q_m,2)))*pow(Q_m/Q_kst,3);
   
   Double_t g1_m_num = g_kst*m_kst*((1+pow(r_kst*Q_kst,2))/(1+pow(r_kst*Q_m,2)))*pow(Q_m/Q_kst,2)/Q_kst;
   
   // WITH m/q
   TComplex num(pow(m_kst,2)*g_kst*((1+pow(r_kst*Q_kst,2))/(1+pow(r_kst*Q_m,2)))*pow(Q_m,2)/pow(Q_kst,3),0);
   TComplex denom(m_kst*m_kst - m*m, -m_kst*g1_m);
   

//    //WITHOUT m/q
//    TComplex num(m_kst*g1_m,0);
//    TComplex denom(m_kst*m_kst - m*m, -m_kst*g1_m);

   TComplex BW = num/denom;//(m/Q_m)*m_kst*g1_m/((m_kst*m_kst - m*m) - i*m_kst*g1_m);//m_kst*g1_m/((m_kst*m_kst - m*m) - i*m_kst*g1_m);

//    cout << "g_kst0: "<<g_kst0<<endl;
//    cout << "r_kst: "<<r_kst<<endl;

//   Double_t phasespace = sqrt(2*pow(Q_m/m,3));

//   Only one P-wave:
//   return BW/sqrt(72.2562757614);



//  Two P-waves:


   TComplex BW_2 = PWaveMass_2(indx);
   TComplex beta(0.20 , 5.31 , 1);
   
   TComplex TwoBW = BW + beta*BW_2;



//    return TwoBW/sqrt(70.0309039034);//68.533431075774885)/sqrt(sqrt(1.04224546179));
   return BW;



 } 



TComplex MassAbsFunc::SWaveMass(Int_t indx)const
{
   Double_t m;

   if (indx==1) m=m1;
   else if (indx==2) m=m2;
   else {
     cout << "Not valid index, must be 1(K*mass) or 2(K*b mass)" << endl;
     return 0.;
       }

   Double_t Q_kst = sqrt((m_kst0*m_kst0 - pow(m_kaon+m_pion,2))*(m_kst0*m_kst0 - pow(m_kaon-m_pion,2)))/(2*m_kst0);
   Double_t Q_m = sqrt((m*m - pow(m_kaon+m_pion,2))*(m*m - pow(m_kaon-m_pion,2)))/(2*m);

   Double_t g0_m = g_kst0*(m_kst0/m)*(Q_m/Q_kst);

   Double_t g0_m_num = g_kst0*m_kst0*(1/Q_kst);
   
   TComplex i(0,1);


   Double_t cotAB_m = 1./(a_dif*Q_m)+0.5*b_dif*Q_m;

   TComplex eAB_m(1,2*atan(1./cotAB_m),1);



   // WITH (m/q)
   TComplex BW_m = (pow(m_kst0,2)*g_kst0/Q_kst)/((m_kst0*m_kst0 - m*m) - i*m_kst0*g0_m);
   TComplex NR_m = m/(Q_m*cotAB_m - i*Q_m);


//    //WITHOUT (m/q)
//    TComplex BW_m = m_kst0*g0_m/((m_kst0*m_kst0 - m*m) - i*m_kst0*g0_m);//(m/Q_m)*m_kst0*g0_m/((m_kst0*m_kst0 - m*m) - i*m_kst0*g0_m);//
//    TComplex NR_m = 1./(cotAB_m - i);


//    Double_t phasespace = sqrt(2*(Q_m/m));


   TComplex SW_m = (NR_m + eAB_m*BW_m);//BW_m;

//    cout << "g_kst0: "<<g_kst0<<endl;
//    cout << "r_kst: "<<r_kst<<endl;

   return SW_m;



//    Double_t MBs = 5366.3;
//    Double_t p0 = sqrt((MBs*MBs - pow(m_kst+m,2))*(MBs*MBs - pow(m_kst-m,2)))/(2*MBs);;
//    Double_t phasespace = sqrt(pow(Q_m,1)*p0);

//    return SW_m*phasespace/sqrt(108523368.209);



//    Double_t g_kst0_b = 279.;


//    Double_t Q_kst = sqrt((m_kst0*m_kst0 - pow(m_kaon+m_pion,2))*(m_kst0*m_kst0 - pow(m_kaon-m_pion,2)))/(2*m_kst0);
//    Double_t Q_m = sqrt((m*m - pow(m_kaon+m_pion,2))*(m*m - pow(m_kaon-m_pion,2)))/(2*m);

//    Double_t g0_m = g_kst0_b*(m_kst0/m)*(Q_m/Q_kst);

//    Double_t g0_m_num = g_kst0_b*m_kst0*(1/Q_kst);
   
//    TComplex i(0,1);


//    Double_t cotAB_m = 1./(a_dif*Q_m)+0.5*b_dif*Q_m;

//    TComplex eAB_m(1,2*atan(1./cotAB_m),1);



//    // WITH (m/q)
//    TComplex BW_m = (pow(m_kst0,2)*g_kst0_b/Q_kst)/((m_kst0*m_kst0 - m*m) - i*m_kst0*g0_m);
//    TComplex NR_m = m/(Q_m*cotAB_m - i*Q_m);


// //    //WITHOUT (m/q)
// //    TComplex BW_m = m_kst0*g0_m/((m_kst0*m_kst0 - m*m) - i*m_kst0*g0_m);//(m/Q_m)*m_kst0*g0_m/((m_kst0*m_kst0 - m*m) - i*m_kst0*g0_m);//
// //    TComplex NR_m = 1./(cotAB_m - i);

//    cout << "g_kst0: "<<g_kst0<<endl;
//    cout << "r_kst: "<<r_kst<<endl;
//    cout << "g_kst0_b: "<<g_kst0_b<<endl;



//    TComplex SW_m = NR_m + eAB_m*BW_m;//BW_m;


//    return SW_m/sqrt(17.333149911);

}
