/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "Kstar_evtgen_2D.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

#include <vector>
using std::vector;

#include <iostream>
using std::ios;
#include <fstream>
#include <iomanip>
#include <sstream>

#include <complex>
#include "BWtools.C"

ClassImp(Kstar_evtgen_2D) 

 Kstar_evtgen_2D::Kstar_evtgen_2D(const char *name, const char *title, 
                        RooAbsReal& _m1,
                        RooAbsReal& _m2,
                        RooAbsReal& _m0,
                        RooAbsReal& _g0,
                        RooAbsReal& _mDa,
                        RooAbsReal& _mDb,
                        RooAbsReal& _J,
                        RooAbsReal& _MB,
                        RooAbsReal& _MV,
                        RooAbsReal& _l) :
   RooAbsPdf(name,title), 
   m1("m1","m1",this,_m1),
   m2("m2","m2",this,_m2),
   m0("m0","m0",this,_m0),
   g0("g0","g0",this,_g0),
   mDa("mDa","mDa",this,_mDa),
   mDb("mDb","mDb",this,_mDb),
   J("J","J",this,_J),
   MB("MB","MB",this,_MB),
   MV("MV","MV",this,_MV),
   l("l","l",this,_l)
 { 
 } 


 Kstar_evtgen_2D::Kstar_evtgen_2D(const Kstar_evtgen_2D& other, const char* name) :  
   RooAbsPdf(other,name), 
   m1("m1",this,other.m1),
   m2("m2",this,other.m2),
   m0("m0",this,other.m0),
   g0("g0",this,other.g0),
   mDa("mDa",this,other.mDa),
   mDb("mDb",this,other.mDb),
   J("J",this,other.J),
   MB("MB",this,other.MB),
   MV("MV",this,other.MV),
   l("l",this,other.l)
 { 
 } 


Double_t Kstar_evtgen_2D::calculatePDF_1D(Int_t indx)const
{


  Double_t m_kst=m0;
  Double_t m_kstb=m0;
  
  if (indx==1)
    {
      m_kst = m1;
      m_kstb = m2;
    }
  else
    {
      m_kst = m2;
      m_kstb = m1;
    }

   Double_t K0 = get_K(m_kst,m0,g0,mDa,mDb,J);
   Double_t K0h = get_K_hat(m_kst,m0,g0,mDa,mDb,J);

   Double_t q = get_q(m_kst,mDa,mDb);
   Double_t q0 = get_q(m0,mDa,mDb);
   if (q==0) return 0;
   Double_t rho_decay = pow(q,2*J+1)*Blatt_Weisskopf(q,q0,J);


   Double_t p = get_q(MB,m_kstb,m_kst);
   Double_t p0 = get_q(MB,m_kstb,m0);
   if (p==0) return 0;
   Double_t rho_birth = pow(p,2*l+1)*Blatt_Weisskopf(p,p0,l);

   std::complex<Double_t> num(K0h,0.); 
   std::complex<Double_t> den(1, -(K0)); 
   std::complex<Double_t> T = num/den;
   Double_t  kst1 = real(T*conj(T));

   return kst1 * rho_decay * rho_birth;



}


Double_t Kstar_evtgen_2D::getPDF_1D(Double_t m_kst, Double_t m_kstb)const
{
  
   Double_t K0 = get_K(m_kst,m0,g0,mDa,mDb,J);
   Double_t K0h = get_K_hat(m_kst,m0,g0,mDa,mDb,J);

   Double_t q = get_q(m_kst,mDa,mDb);
   Double_t q0 = get_q(m0,mDa,mDb);
   if (q==0) return 0;
   Double_t rho_decay = pow(q,2*J+1)*Blatt_Weisskopf(q,q0,J);


   Double_t p = get_q(MB,m_kstb,m_kst);
   Double_t p0 = get_q(MB,m_kstb,m0);
   if (p==0) return 0;
   Double_t rho_birth = pow(p,2*l+1)*Blatt_Weisskopf(p,p0,l);

   std::complex<Double_t> num(K0h,0.); 
   std::complex<Double_t> den(1, -(K0)); 
   std::complex<Double_t> T = num/den;
   Double_t  kst1 = real(T*conj(T));

   return kst1 * rho_decay * rho_birth;


}


Double_t Kstar_evtgen_2D::getPDF_2D(Double_t mkst, Double_t mkstb)const
{
  Double_t PDF_1 = getPDF_1D(mkst,mkstb);
  Double_t PDF_2 = getPDF_1D(mkstb,mkst);

   return PDF_1*PDF_2;

}



 Double_t Kstar_evtgen_2D::evaluate() const 
 { 


   Double_t PDF_1 = calculatePDF_1D(1);
   Double_t PDF_2 = calculatePDF_1D(2);

   return PDF_1*PDF_2;


 } 



Int_t Kstar_evtgen_2D::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const  
 { 
   // LIST HERE OVER WHICH VARIABLES ANALYTICAL INTEGRATION IS SUPPORTED, 
   // ASSIGN A NUMERIC CODE FOR EACH SUPPORTED (SET OF) PARAMETERS 
   // THE EXAMPLE BELOW ASSIGNS CODE 1 TO INTEGRATION OVER VARIABLE X
   // YOU CAN ALSO IMPLEMENT MORE THAN ONE ANALYTICAL INTEGRAL BY REPEATING THE matchArgs 
   // EXPRESSION MULTIPLE TIMES

   if (matchArgs(allVars,analVars,m1,m2)) return 0;
//      {
//        cout << "returning: 3"<<endl;
//        return 3 ;
//      }
   if (matchArgs(allVars,analVars,m1))
     {
       cout << "returning: 1"<<endl;
       return 1 ;
     } 
   if (matchArgs(allVars,analVars,m2))
     {
       cout << "returning: 2"<<endl;
       return 2 ;
     }
   

return 0 ; 
 } 




 Double_t Kstar_evtgen_2D::analyticalIntegral(Int_t code, const char* rangeName) const  
 { 
   // RETURN ANALYTICAL INTEGRAL DEFINED BY RETURN CODE ASSIGNED BY getAnalyticalIntegral
   // THE MEMBER FUNCTION x.min(rangeName) AND x.max(rangeName) WILL RETURN THE INTEGRATION
   // BOUNDARIES FOR EACH OBSERVABLE x

   // assert(code==1) ; 
   // return (x.max(rangeName)-x.min(rangeName)) ; 



   if (code==1){
     Int_t n;
     Double_t xmin,xmax,sum,f1,f2,f3,d1,d2,e,error,beta1,beta2,delta,beta,x1,x2;
     n=1000;
     n=3*n;

     xmin=m1.min(rangeName);
     xmax=MB-m2;


     delta=(xmax-xmin)/n;
     sum=0.0;
     error=0.0;
     for(Int_t i=0;i<n;i=i+1)
       {
	 x1=xmin+i*delta;
	 x2=xmin+(i+1)*delta;
	 beta1=(x2+x1)/2;
	 beta2=(x2-x1)/2;
	 f1=getPDF_2D(beta1-sqrt(3/5)*beta2,m2);
	 f2=getPDF_2D(beta1,m2);
	 f3=getPDF_2D(beta1+sqrt(3/5)*beta2,m2);
	 sum=sum+beta2*(5.0/9.0*(f1+f3)+8.0/9.0*f2);
         
       }
     return sum;

  
//      beta=(xmax-xmin)/(2*n);
//      sum=0.0;
//      error=0.0;
//      for(Int_t i=2;i<n;i=i+3)
//        {
// 	 f1=getPDF_2D(xmin+(i-1)*beta,m2);
// 	 f2=getPDF_2D(xmin+i*beta,m2);
// 	 f3=getPDF_2D(xmin+(i+1)*beta,m2);
// 	 sum=sum+beta*(5.0/9.0*(f1+f3)+8.0/9.0*f2);
// // 	 d1=abs(getPDF_2D(m1,m2-i*beta)-getPDF_2D(m1,m2-i*beta))/beta;
// // 	 d2=abs(getPDF_2D(m1,m2-i*beta)-getPDF_2D(m1,m2+i*beta))/beta;
// // 	 if(d1<d2) e=d2;
// // 	 else e=d1;
// // 	 error=error+e;
//        }
//      return sum;
   }

   else if (code==2){
     Int_t n;
     Double_t xmin,xmax,sum,f1,f2,f3,d1,d2,e,error,beta1,beta2,delta,beta,x1,x2;
     n=1000;
     n=3*n;

     xmin=m1.min(rangeName);
     xmax=MB-m1;
  
     delta=(xmax-xmin)/n;
     sum=0.0;
     error=0.0;
     for(Int_t i=0;i<n;i=i+1)
       {
	 x1=xmin+i*delta;
	 x2=xmin+(i+1)*delta;
	 beta1=(x2+x1)/2;
	 beta2=(x2-x1)/2;
	 f1=getPDF_2D(m1,beta1-sqrt(3/5)*beta2);
	 f2=getPDF_2D(m1,beta1);
	 f3=getPDF_2D(m1,beta1+sqrt(3/5)*beta2);
	 sum=sum+beta2*(5.0/9.0*(f1+f3)+8.0/9.0*f2);
         
       }
     return sum;

//      beta=(xmax-xmin)/(2*n);
//      sum=0.0;
//      error=0.0;
//      for(Int_t i=2;i<n;i=i+3)
//        {
// 	 f1=getPDF_2D(m1,xmin+(i-1)*beta);
// 	 f2=getPDF_2D(m1,xmin+i*beta);
// 	 f3=getPDF_2D(m1,xmin+(i+1)*beta);
// 	 sum=sum+beta*(5.0/9.0*(f1+f3)+8.0/9.0*f2);
// // 	 d1=abs(getPDF_2D(m1,m2-i*beta)-getPDF_2D(m1,m2-i*beta))/beta;
// // 	 d2=abs(getPDF_2D(m1,m2-i*beta)-getPDF_2D(m1,m2+i*beta))/beta;
// // 	 if(d1<d2) e=d2;
// // 	 else e=d1;
// // 	 error=error+e;
//        }
//      return sum;

   }

   else
     {

       return 1.1406*pow(10,19);
     }


   return 0 ; 
 } 

