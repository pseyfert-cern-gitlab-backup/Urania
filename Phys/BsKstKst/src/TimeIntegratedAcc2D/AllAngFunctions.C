#include <iostream>
#include <math.h>
#include "Math/SpecFunc.h"
#include "TMath.h"
using namespace std;

namespace {
inline double a(int p, int l, int m) {
        double r = TMath::Factorial(l+m)/TMath::Factorial(m+p)/TMath::Factorial(p)/TMath::Factorial(l-m-2*p);
        r /= pow(2.,m+2*p);
        return p%2==0 ? r : -r ;
    }
}


Double_t get_AngTerm_Coefficient(Int_t indx)
{

  if (indx==1)
    {
      return 4;
    }
  else if (indx==2)
    {
      return 1;
    }
  else if (indx==3)
    {
      return 1;
    }
  else if (indx==5)
    {
      return sqrt(2)*4;
    }
  else if (indx==7 || indx==71)
    {
      return 4/3.;
    }
  else if (indx==8 || indx==81)
    {
      return -8/sqrt(3);
    }
  else if (indx==9 || indx==91)
    {
      return -8/sqrt(6);
    }
  else if (indx==10 || indx==101)
    {
      return 8./sqrt(6);
    }
  else if (indx==11 || indx==111)
    {
      return 8/(3*sqrt(3));
    }
  else if (indx==12) //equivalent to AngF7_int
    {
      return -8/3.;
    }
  else if (indx==13)
    {
      return 4./9;
    }
  else if (indx==14)
    {
      return -8/3.;
    }
  else if (indx==15)
    {
      return -4*sqrt(2)/3.;
    }
  else
    {
      cout<<"No angular term selected. Return 0."<<endl;
      return 0;
    }

}


Double_t get_AngTerm_CosTheta1(Int_t indx, Double_t c1)
{

  Double_t c1_2 = c1*c1;
  Double_t s1_2 = 1.-c1_2;
  Double_t s1 = sqrt(s1_2);
  
  if (indx==1)
    {
      return c1*c1;
    }
  else if (indx==2)
    {
      return s1_2;
    }
  else if (indx==3)
    {
      return s1_2;
    }
  else if (indx==5)
    {
      return s1*c1;
    }
  else if (indx==7)
    {
      return c1*c1;
    }
  else if (indx==71)
    {
      return 1;
    }
  else if (indx==8)
    {
      return c1*c1;
    }
  else if (indx==81)
    {
      return c1;
    }
  else if (indx==9)
    {
      return s1*c1;
    }
  else if (indx==91)
    {
      return s1;
    }
  else if (indx==10)
    {
      return s1*c1;
    }
  else if (indx==101)
    {
      return s1;
    }
  else if (indx==11)
    {
      return c1;
    }
  else if (indx==111)
    {
      return 1;
    }
  else if (indx==12) //equivalent to AngF7_int
    {
      return c1;
    }
  else if (indx==13)
    {
      return 1;
    }
  else if (indx==14)
    {
      return c1;
    }
  else if (indx==15)
    {
      return s1;
    }
  else
    {
      cout<<"No angular term selected. Return 0."<<endl;
      return 0;
    }

}


Double_t get_AngTerm_CosTheta2(Int_t indx, Double_t c2)
{
  Double_t c2_2 = c2*c2;
  Double_t s2_2 = 1.-c2_2;
  Double_t s2 = sqrt(s2_2);
  
  if (indx==1)
    {
      return c2*c2;
    }
  else if (indx==2)
    {
      return s2_2;
    }
  else if (indx==3)
    {
      return s2_2;
    }
  else if (indx==5)
    {
      return s2*c2;
    }
  else if (indx==71)
    {
      return c2*c2;
    }
  else if (indx==7)
    {
      return 1;
    }
  else if (indx==81)
    {
      return c2*c2;
    }
  else if (indx==8)
    {
      return c2;
    }
  else if (indx==91)
    {
      return s2*c2;
    }
  else if (indx==9)
    {
      return s2;
    }
  else if (indx==101)
    {
      return s2*c2;
    }
  else if (indx==10)
    {
      return s2;
    }
  else if (indx==111)
    {
      return c2;
    }
  else if (indx==11)
    {
      return 1;
    }
  else if (indx==12) //equivalent to AngF7_int
    {
      return c2;
    }
  else if (indx==13)
    {
      return 1;
    }
  else if (indx==14)
    {
      return c2;
    }
  else if (indx==15)
    {
      return s2;
    }
  else
    {
      cout<<"No angular term selected. Return 0."<<endl;
      return 0;
    }
}


Double_t get_AngTerm_Phi(Int_t indx, Double_t ph)
{
  if (indx==1 || indx==7 || indx==71 || indx==8 || indx==81 || indx==11 || indx==111 || indx==12 || indx==13 || indx==14)
    {
      return 1;
    }
  else if (indx==2)
    {
      return (1+cos(2*ph));
    }
  else if (indx==3)
    {
      return (1-cos(2*ph));
    }
  else if (indx==5 || indx==9 || indx==91 || indx==15)
    {
      return cos(ph);
    }
  else if (indx==10 || indx==101)
    {
      return sin(ph);
    }
  else
    {
      cout<<"No angular term selected. Return 0."<<endl;
      return 0;
    }
}


Double_t get_AngTerm(Int_t indx, Double_t c1, Double_t c2, Double_t ph)
{
  Double_t coef = get_AngTerm_Coefficient(indx);
  Double_t termc1 = get_AngTerm_CosTheta1(indx, c1);
  Double_t termc2 = get_AngTerm_CosTheta2(indx, c2);
  Double_t termph = get_AngTerm_Phi(indx, ph);

  return coef*termc1*termc2*termph;
}
// Double_t get_AngTerm(Int_t indx, Double_t c1, Double_t c2, Double_t ph)
// {

//   Double_t c1_2 = c1*c1;
//   Double_t c2_2 = c2*c2;
//   Double_t s1_2 = 1.-c1_2;
//   Double_t s2_2 = 1.-c2_2;
//   Double_t s12s22 = s1_2*s2_2;
//   Double_t s1s2 = sqrt(s12s22);

  
//   if (indx==1)
//     {
//       return 4*c1*c1*c2*c2;
//     }
//   else if (indx==2)
//     {
//       return s1_2*s2_2*(1+cos(2*ph));
//     }
//   else if (indx==3)
//     {
//       return s1_2*s2_2*(1-cos(2*ph));
//     }
//   else if (indx==5)
//     {
//       return sqrt(2)*4*s1s2*c1*c2*cos(ph);
//     }
//   else if (indx==7)
//     {
//       return 4*c1*c1/3.;
//     }
//   else if (indx==71)
//     {
//       return 4*c2*c2/3.;
//     }
//   else if (indx==8)
//     {
//       return -8*c1*c1*c2/sqrt(3);
//     }
//   else if (indx==81)
//     {
//       return -8*c2*c2*c1/sqrt(3);
//     }
//   else if (indx==9)
//     {
//       return -8*s1s2*c1*cos(ph)/sqrt(6);
//     }
//   else if (indx==91)
//     {
//       return -8*s1s2*c2*cos(ph)/sqrt(6);
//     }
//   else if (indx==10)
//     {
//       return 8.*s1s2*c1*sin(ph)/sqrt(6);
//     }
//   else if (indx==101)
//     {
//       return 8.*s1s2*c2*sin(ph)/sqrt(6);
//     }
//   else if (indx==11)
//     {
//       return 8*c1/(3*sqrt(3));
//     }
//   else if (indx==111)
//     {
//       return 8*c2/(3*sqrt(3));
//     }
//   else if (indx==12) //equivalent to AngF7_int
//     {
//       return -8*c1*c2/3.;
//     }
//   else if (indx==13)
//     {
//       return 4./9;
//     }
//   else if (indx==14)
//     {
//       return -8*c1*c2/3.;
//     }
//   else if (indx==15)
//     {
//       return -4*sqrt(2)*s1s2*cos(ph)/3;
//     }
//   else
//     {
//       cout<<"No angular term selected. Return 0."<<endl;
//       return 0;
//     }

// }


double IntegrateLegendre(int _l1, int _m1, int _l2, int _m2)
{
  // this was verified to match mathematica for 
  // l1 in [0,2], m1 in [0,l1], l2 in [l1,4], m2 in [0,l2]
  if ( _m1==_m2 )                 return ( _l1 == _l2) ?  (TMath::Factorial(_l1+_m2)/TMath::Factorial(_l1-_m1)*double(2)/(2*_l1+1)) : 0.;
  if ( (_l1+_l2-_m1-_m2)%2 != 0 ) return 0; // these combinations are odd under x -> -x

  // from B.R. Wong, "On the overlap integral of associated Legendre Polynomials" 1998 J. Phys. A: Math. Gen. 31 1101
  // TODO: update to the result of 
  //       H. A. Mavromatis
  //       "A single-sum expression for the overlap integral of two associated Legendre polynomials"
  //       1999 J. Phys. A: Math. Gen. 32 2601
  //       http://iopscience.iop.org/0305-4470/32/13/011/pdf/0305-4470_32_13_011.pdf
  //       For that we need Wigner 3-j, which Lorenzo has added for Root 5.28... (note: check Condon-Shortly convention in this paper!)
  double r=0;
  for (int p1=0; 2*p1 <= _l1-_m1 ;++p1) {
    double a1 = a(p1,_l1,_m1);
    for (int p2=0; 2*p2 <= _l2-_m2 ; ++p2) {
       double a2 = a(p2,_l2,_m2);
       r+= a1*a2*TMath::Gamma( double(_l1+_l2-_m1-_m2-2*p1-2*p2+1)/2 )*TMath::Gamma( double(_m1+_m2+2*p1+2*p2+2)/2 );
    }
  }
  r /= TMath::Gamma( double(_l1+_l2+3)/2 );

  if ((_m1+_m2)%2==1) r = -r;
  return r;
}


double get_CosTheta1_Integral(Int_t indx, Int_t _l)
{

  double ang_int = 0;
 

  if (indx==1)
    {
      // (cos(th)^2) = (2 P20 + P00)/3
      ang_int = (2*IntegrateLegendre(2, 0, _l, 0) + IntegrateLegendre(0, 0, _l, 0))/3.;
    }

  else if (indx==2 || indx==3)
    {
      //(sin(th)^2) = 2/3(P00 - P20)
      ang_int = 2/3.*(IntegrateLegendre(0, 0, _l, 0)-IntegrateLegendre(2, 0, _l, 0));
    }
  else if (indx==5)
    {
      //sin(th)cos(th) = -1/3 P21
      ang_int = -1/3.*IntegrateLegendre(2, 1, _l, 0);
    }
  else if (indx==7)
    {
      //cos(th)^2 =  (2 P20 +P00)/3
      ang_int = (2*IntegrateLegendre(2, 0, _l, 0) + IntegrateLegendre(0, 0, _l, 0))/3.;
    }
  else if (indx==71)
    {
      //P00
      ang_int = IntegrateLegendre(0, 0, _l, 0);
    }
  else if (indx==12)
    {
      //cos(th) = P10
      ang_int = IntegrateLegendre(1, 0, _l, 0);
    }
  else if (indx==8)
    {
      //cos(th)^2 =  (2 P20 +P00)/3
      ang_int = (2*IntegrateLegendre(2, 0, _l, 0) + IntegrateLegendre(0, 0, _l, 0))/3.;
    }
  else if (indx==81)
    {
      //cos(th) = P10
      ang_int = IntegrateLegendre(1, 0, _l, 0);
    }
  else if (indx==9)
    {
      //sin(th)cos(th) = -1/3 P21
      ang_int = -1/3.*IntegrateLegendre(2, 1, _l, 0);
    }
  else if (indx==91)
    {
      //sin(th) = -P11
      ang_int = -IntegrateLegendre(1, 1, _l, 0);
    }
  else if (indx==10)
    {
      //sin(th)cos(th) = -1/3 P21
      ang_int = -1/3.*IntegrateLegendre(2, 1, _l, 0);
    }
  else if (indx==101)
    {
      //sin(th) = -P11
      ang_int = -IntegrateLegendre(1, 1, _l, 0);
    }
  else if (indx==11)
    {
      //cos(th) = P10
      ang_int = IntegrateLegendre(1, 0, _l, 0);
    }
  else if (indx==111)
    {
      //P00
      ang_int = IntegrateLegendre(0, 0, _l, 0);
    }
  else if (indx==13)
    {
      //P00
      ang_int = IntegrateLegendre(0, 0, _l, 0);
    }
  else if (indx==14)
    {
      //cos(th) = P10
      ang_int = IntegrateLegendre(1, 0, _l, 0);
    }
  else if (indx==15)
    {
      //sin(th) = -P11
      ang_int = -IntegrateLegendre(1, 1, _l, 0);
    }
  else
    {
      cout<<"No angular term selected for indx = "<<indx<<" . Return 0."<<endl;
      return 0;
    }
  return ang_int;
}


double get_CosTheta2_Integral(Int_t indx, Int_t _l)
{

  double ang_int = 0;
 

  if (indx==1)
    {
      // (cos(th)^2) = (2 P20 +P00)/3
      ang_int = (2*IntegrateLegendre(2, 0, _l, 0) + IntegrateLegendre(0, 0, _l, 0))/3.;
    }

  else if (indx==2 || indx==3)
    {
      //(sin(th)^2) = 2/3(P00 - P20)
      ang_int = 2/3.*(IntegrateLegendre(0, 0, _l, 0)-IntegrateLegendre(2, 0, _l, 0));
    }
  else if (indx==5)
    {
      //sin(th)cos(th) = -1/3 P21
      ang_int = -1/3.*IntegrateLegendre(2, 1, _l, 0);
    }
  else if (indx==71)
    {
      //cos(th)^2 =  (2 P20 +P00)/3
      ang_int = (2*IntegrateLegendre(2, 0, _l, 0) + IntegrateLegendre(0, 0, _l, 0))/3.;
    }
  else if (indx==7)
    {
      //P00
      ang_int = IntegrateLegendre(0, 0, _l, 0);
    }
  else if (indx==12)
    {
      //cos(th) = P10
      ang_int = IntegrateLegendre(1, 0, _l, 0);
    }
  else if (indx==81)
    {
      //cos(th)^2 =  (2 P20 +P00)/3
      ang_int = (2*IntegrateLegendre(2, 0, _l, 0) + IntegrateLegendre(0, 0, _l, 0))/3.;
    }
  else if (indx==8)
    {
      //cos(th) = P10
      ang_int = IntegrateLegendre(1, 0, _l, 0);
    }
  else if (indx==91)
    {
      //sin(th)cos(th) = -1/3 P21
      ang_int = -1/3.*IntegrateLegendre(2, 1, _l, 0);
    }
  else if (indx==9)
    {
      //sin(th) = -P11
      ang_int = -IntegrateLegendre(1, 1, _l, 0);
    }
  else if (indx==101)
    {
      //sin(th)cos(th) = -1/3 P21
      ang_int = -1/3.*IntegrateLegendre(2, 1, _l, 0);
    }
  else if (indx==10)
    {
      //sin(th) = -P11
      ang_int = -IntegrateLegendre(1, 1, _l, 0);
    }
  else if (indx==111)
    {
      //cos(th) = P10
      ang_int = IntegrateLegendre(1, 0, _l, 0);
    }
  else if (indx==11)
    {
      //P00
      ang_int = IntegrateLegendre(0, 0, _l, 0);
    }
  else if (indx==13)
    {
      //P00
      ang_int = IntegrateLegendre(0, 0, _l, 0);
    }
  else if (indx==14)
    {
      //cos(th) = P10
      ang_int = IntegrateLegendre(1, 0, _l, 0);
    }
  else if (indx==15)
    {
      //sin(th) = -P11
      ang_int = -IntegrateLegendre(1, 1, _l, 0);
    }
  else
    {
      cout<<"No angular term selected for indx = "<<indx<<" . Return 0."<<endl;
      return 0;
    }
  return ang_int;
}


double get_Phi_Integral(Int_t indx, Double_t phmin, Double_t phmax)
{

  Double_t Iph = 1;

  if (indx==1)
    {
      Iph = phmax - phmin;
    }
  else if (indx==2)
    {
      //(1+cos(2*ph))
      Double_t Ipha = phmax - phmin;
      Double_t Iphb =  (sin(2*phmax) - sin(2*phmin))/2.;
      Iph = Ipha+Iphb;
    }
  else if (indx==3)
    {
      //(1-cos(2*ph))
      Double_t Ipha = phmax - phmin;
      Double_t Iphb =  (sin(2*phmax) - sin(2*phmin))/2.;
      Iph = Ipha-Iphb;
    }
  else if (indx==5)
    {
      //cos(ph)
      Iph = sin(phmax)-sin(phmin);
    }
  else if (indx==7)
    {
      Iph = phmax - phmin;
    }
  else if (indx==71)
    {
      Iph = phmax - phmin;
    }
  else if (indx==8)
    {
      Iph = phmax - phmin;
    }
  else if (indx==81)
    {
      Iph = phmax - phmin;
    }
  else if (indx==9)
    {
      //cos(ph)
      Iph = sin(phmax)-sin(phmin);
    }
  else if (indx==91)
    {
      //cos(ph)
      Iph = sin(phmax)-sin(phmin);
    }
  else if (indx==10)
    {
      //sin(ph)
      Iph = cos(phmin)-cos(phmax);
    }
  else if (indx==101)
    {
      //sin(ph)
      Iph = cos(phmin)-cos(phmax);
    }
  else if (indx==11)
    {
      Iph = phmax - phmin;
    }
  else if (indx==111)
    {
      Iph = phmax - phmin;
    }
  else if (indx==12) //equivalent to AngF7_int
    {
      Iph = phmax - phmin;
    }
  else if (indx==13)
    {
      Iph = phmax - phmin;
    }
  else if (indx==14)
    {
      Iph = phmax - phmin;
    }
  else if (indx==15)
    {
      //cos(ph)
      Iph = sin(phmax)-sin(phmin);
    }
  else
    {
      cout<<"No angular term selected. Return 0."<<endl;
      return 0;
    }
  return Iph;
}


// Double_t get_AngTerm_Integral(Int_t indx, Int_t code, Double_t c1, Double_t c2, Double_t ph
// 			      , Double_t phmin=0, Double_t phmax=2*TMath::Pi()
// 			      , Int_t l_c1=0, Int_t l_c2=0 )
// {

//   Double_t c1_2 = c1*c1;
//   Double_t c2_2 = c2*c2;
//   Double_t s1_2 = 1.-c1_2;
//   Double_t s2_2 = 1.-c2_2;
//   Double_t s12s22 = s1_2*s2_2;
//   Double_t s1s2 = sqrt(s12s22);
//   Double_t s1 = sqrt(s1_2);
//   Double_t s2 = sqrt(s2_2);

//   Double_t Iph=1;
//   Double_t Ic1=1; 
//   Double_t Ic2=1;
  
//  if (indx==1)
//     {
//       Ic1 = c1*c1;
//       Ic2 = c2*c2;
//       Iph=1;
//       if (code==7 || code==17 || code==18 || code==27)  Ic1 = get_CosTheta1_Integral(indx, Int_t l_c1);
//       if (code==7 || code==17 || code==21 || code==28)  Ic2 = get_CosTheta1_Integral(indx, Int_t l_c2);
//       if (code==7 || code==18 || code==21 || code==29)  Iph = get_Phi_Integral(indx,phmin,phmax);
//       return 4*Ic1*Ic2*Iph;
//     }
//   else if (indx==2)
//     {
//       //
//       Ic1 = s1_2;
//       Ic2 = s2_2;
//       Iph = (1+cos(2*ph));
//       if (code==7 || code==17 || code==18 || code==27)  Ic1 = get_CosTheta1_Integral(indx, Int_t l_c1);
//       if (code==7 || code==17 || code==21 || code==28)  Ic2 = get_CosTheta1_Integral(indx, Int_t l_c2);
//       if (code==7 || code==18 || code==21 || code==29)  Iph = get_Phi_Integral(indx,phmin,phmax);
//       return Ic1*Ic2*Iph;
//     }
//   else if (indx==3)
//     {
//       Ic1 = s1_2;
//       Ic2 = s2_2;
//       Iph = (1-cos(2*ph));
//       if (code==7 || code==17 || code==18 || code==27)  Ic1 = get_CosTheta1_Integral(indx, Int_t l_c1);
//       if (code==7 || code==17 || code==21 || code==28)  Ic2 = get_CosTheta1_Integral(indx, Int_t l_c2);
//       if (code==7 || code==18 || code==21 || code==29)  Iph = get_Phi_Integral(indx,phmin,phmax);
//       return Ic1*Ic2*Iph;
//     }
//   else if (indx==5)
//     {
//       Ic1 = s1*c1;
//       Ic2 = s2*c2;
//       Iph = cos(ph);
//       if (code==7 || code==17 || code==18 || code==27)  Ic1 = get_CosTheta1_Integral(indx, Int_t l_c1);
//       if (code==7 || code==17 || code==21 || code==28)  Ic2 = get_CosTheta1_Integral(indx, Int_t l_c2);
//       if (code==7 || code==18 || code==21 || code==29)  Iph = get_Phi_Integral(indx,phmin,phmax);
//       return sqrt(2)*4*Ic1*Ic2*Iph;
//     }
//   else if (indx==7)
//     {
//       Ic1 = c1*c1;
//       Ic2 = 1;
//       Iph = 1;
//       if (code==7 || code==17 || code==18 || code==27)  Ic1 = get_CosTheta1_Integral(indx, Int_t l_c1);
//       if (code==7 || code==17 || code==21 || code==28)  Ic2 = get_CosTheta1_Integral(indx, Int_t l_c2);
//       if (code==7 || code==18 || code==21 || code==29)  Iph = get_Phi_Integral(indx,phmin,phmax);
//       return 4*Ic1*Ic2*Iph/3.;
//     }
//   else if (indx==71)
//     {
//       Ic1 = 1;
//       Ic2 = c2*c2;
//       Iph = 1;
//       if (code==7 || code==17 || code==18 || code==27)  Ic1 = get_CosTheta1_Integral(indx, Int_t l_c1);
//       if (code==7 || code==17 || code==21 || code==28)  Ic2 = get_CosTheta1_Integral(indx, Int_t l_c2);
//       if (code==7 || code==18 || code==21 || code==29)  Iph = get_Phi_Integral(indx,phmin,phmax);
//       return 4*Ic1*Ic2*Iph/3.;
//     }
//   else if (indx==8)
//     {
//       Ic1 = c1*c1;
//       Ic2 = c2;
//       Iph = 1;
//       if (code==7 || code==17 || code==18 || code==27)  Ic1 = get_CosTheta1_Integral(indx, Int_t l_c1);
//       if (code==7 || code==17 || code==21 || code==28)  Ic2 = get_CosTheta1_Integral(indx, Int_t l_c2);
//       if (code==7 || code==18 || code==21 || code==29)  Iph = get_Phi_Integral(indx,phmin,phmax);
//       return -8*Ic1*Ic2*Iph/sqrt(3);
//     }
//   else if (indx==81)
//     {
//       Ic1 = c1;
//       Ic2 = c2*c2;
//       Iph = 1;
//       if (code==7 || code==17 || code==18 || code==27)  Ic1 = get_CosTheta1_Integral(indx, Int_t l_c1);
//       if (code==7 || code==17 || code==21 || code==28)  Ic2 = get_CosTheta1_Integral(indx, Int_t l_c2);
//       if (code==7 || code==18 || code==21 || code==29)  Iph = get_Phi_Integral(indx,phmin,phmax);
//       return -8*Ic1*Ic2*Iph/sqrt(3);
//     }
//   else if (indx==9)
//     {
//       Ic1 = s1*c1;
//       Ic2 = s2;
//       Iph = cos(ph);
//       if (code==7 || code==17 || code==18 || code==27)  Ic1 = get_CosTheta1_Integral(indx, Int_t l_c1);
//       if (code==7 || code==17 || code==21 || code==28)  Ic2 = get_CosTheta1_Integral(indx, Int_t l_c2);
//       if (code==7 || code==18 || code==21 || code==29)  Iph = get_Phi_Integral(indx,phmin,phmax);
//       return -8*Ic1*Ic2*Iph/sqrt(6);
//     }
//   else if (indx==91)
//     {
//       Ic1 = s1;
//       Ic2 = s2*c2;
//       Iph = cos(ph);
//       if (code==7 || code==17 || code==18 || code==27)  Ic1 = get_CosTheta1_Integral(indx, Int_t l_c1);
//       if (code==7 || code==17 || code==21 || code==28)  Ic2 = get_CosTheta1_Integral(indx, Int_t l_c2);
//       if (code==7 || code==18 || code==21 || code==29)  Iph = get_Phi_Integral(indx,phmin,phmax);
//       return -8*Ic1*Ic2*Iph/sqrt(6);
//     }
//   else if (indx==10)
//     {
//       Ic1 = s1*c1;
//       Ic2 = s2;
//       Iph = sin(ph);
//       if (code==7 || code==17 || code==18 || code==27)  Ic1 = get_CosTheta1_Integral(indx, Int_t l_c1);
//       if (code==7 || code==17 || code==21 || code==28)  Ic2 = get_CosTheta1_Integral(indx, Int_t l_c2);
//       if (code==7 || code==18 || code==21 || code==29)  Iph = get_Phi_Integral(indx,phmin,phmax);
//       return 8.*Ic1*Ic2*Iph/sqrt(6);
//     }
//   else if (indx==101)
//     {
//       Ic1 = s1;
//       Ic2 = s2*c2;
//       Iph = sin(ph);
//       if (code==7 || code==17 || code==18 || code==27)  Ic1 = get_CosTheta1_Integral(indx, Int_t l_c1);
//       if (code==7 || code==17 || code==21 || code==28)  Ic2 = get_CosTheta1_Integral(indx, Int_t l_c2);
//       if (code==7 || code==18 || code==21 || code==29)  Iph = get_Phi_Integral(indx,phmin,phmax);
//       return 8.*Ic1*Ic2*Iph/sqrt(6);
//     }
//   else if (indx==11)
//     {
//       Ic1 = c1;
//       Ic2 = 1;
//       Iph = 1;
//       if (code==7 || code==17 || code==18 || code==27)  Ic1 = get_CosTheta1_Integral(indx, Int_t l_c1);
//       if (code==7 || code==17 || code==21 || code==28)  Ic2 = get_CosTheta1_Integral(indx, Int_t l_c2);
//       if (code==7 || code==18 || code==21 || code==29)  Iph = get_Phi_Integral(indx,phmin,phmax);
//       return 8*Ic1*Ic2*Iph/(3*sqrt(3));
//     }
//   else if (indx==111)
//     {
//       Ic1 = 1;
//       Ic2 = c2;
//       Iph = 1;
//       if (code==7 || code==17 || code==18 || code==27)  Ic1 = get_CosTheta1_Integral(indx, Int_t l_c1);
//       if (code==7 || code==17 || code==21 || code==28)  Ic2 = get_CosTheta1_Integral(indx, Int_t l_c2);
//       if (code==7 || code==18 || code==21 || code==29)  Iph = get_Phi_Integral(indx,phmin,phmax);
//       return 8*Ic1*Ic2*Iph/(3*sqrt(3));
//     }
//   else if (indx==12) //equivalent to AngF7_int
//     {
//       Ic1 = c1;
//       Ic2 = c2;
//       Iph = 1;
//       if (code==7 || code==17 || code==18 || code==27)  Ic1 = get_CosTheta1_Integral(indx, Int_t l_c1);
//       if (code==7 || code==17 || code==21 || code==28)  Ic2 = get_CosTheta1_Integral(indx, Int_t l_c2);
//       if (code==7 || code==18 || code==21 || code==29)  Iph = get_Phi_Integral(indx,phmin,phmax);
//       return -8*Ic1*Ic2*Iph/3.;
//     }
//   else if (indx==13)
//     {
//       Ic1 = 1;
//       Ic2 = 1;
//       Iph = 1;
//       if (code==7 || code==17 || code==18 || code==27)  Ic1 = get_CosTheta1_Integral(indx, Int_t l_c1);
//       if (code==7 || code==17 || code==21 || code==28)  Ic2 = get_CosTheta1_Integral(indx, Int_t l_c2);
//       if (code==7 || code==18 || code==21 || code==29)  Iph = get_Phi_Integral(indx,phmin,phmax);
//       return 4./9*Ic1*Ic2*Iph;
//     }
//   else if (indx==14)
//     {
//       Ic1 = c1;
//       Ic2 = c2;
//       Iph = 1;
//       if (code==7 || code==17 || code==18 || code==27)  Ic1 = get_CosTheta1_Integral(indx, Int_t l_c1);
//       if (code==7 || code==17 || code==21 || code==28)  Ic2 = get_CosTheta1_Integral(indx, Int_t l_c2);
//       if (code==7 || code==18 || code==21 || code==29)  Iph = get_Phi_Integral(indx,phmin,phmax);
//       return -8/3.*Ic1*Ic2*Iph;
//     }
//   else if (indx==15)
//     {
//       Ic1 = s1;
//       Ic2 = s2;
//       Iph = cos(ph);
//       if (code==7 || code==17 || code==18 || code==27)  Ic1 = get_CosTheta1_Integral(indx, Int_t l_c1);
//       if (code==7 || code==17 || code==21 || code==28)  Ic2 = get_CosTheta1_Integral(indx, Int_t l_c2);
//       if (code==7 || code==18 || code==21 || code==29)  Iph = get_Phi_Integral(indx,phmin,phmax);
//       return -4*sqrt(2)*Ic1*Ic2*Iph/3;
//     }
//   else
//     {
//       cout<<"No angular term selected. Return 0."<<endl;
// 	return 0;
//     }

// }


Double_t get_AngTerm_PhiIntegral(Int_t indx, Double_t c1, Double_t c2, Double_t phmin, Double_t phmax)
{
  Double_t coef = get_AngTerm_Coefficient(indx);
  Double_t termc1 = get_AngTerm_CosTheta1(indx, c1);
  Double_t termc2 = get_AngTerm_CosTheta1(indx, c2);
  Double_t termph = get_Phi_Integral(indx, phmin, phmax);

  return coef*termc1*termc2*termph;
}
