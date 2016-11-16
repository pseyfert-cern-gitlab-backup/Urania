#include <iostream>
#include <math.h>
#include "Math/SpecFunc.h"
using namespace std;

namespace {
inline double a(int p, int l, int m) {
        double r = TMath::Factorial(l+m)/TMath::Factorial(m+p)/TMath::Factorial(p)/TMath::Factorial(l-m-2*p);
        r /= pow(2.,m+2*p);
        return p%2==0 ? r : -r ;
    }
}


Double_t get_AngTerm(Int_t indx, Double_t c1, Double_t c2, Double_t ph)
{

  Double_t c1_2 = c1*c1;
  Double_t c2_2 = c2*c2;
  Double_t s1_2 = 1.-c1_2;
  Double_t s2_2 = 1.-c2_2;
  Double_t s12s22 = s1_2*s2_2;
  Double_t s1s2 = sqrt(s12s22);

  
  if (indx==1)
    {
      return 4*c1*c1*c2*c2;
    }
  else if (indx==2)
    {
      return s1_2*s2_2*(1+cos(2*ph));
    }
  else if (indx==3)
    {
      return s1_2*s2_2*(1-cos(2*ph));
    }
  else if (indx==5)
    {
      return sqrt(2)*4*s1s2*c1*c2*cos(ph);
    }
  else if (indx==7)
    {
      return 4*c1*c1/3.;
    }
  else if (indx==8)
    {
      return -8*c1*c1*c2/sqrt(3);
    }
  else if (indx==9)
    {
      return -8*s1s2*c1*cos(ph)/sqrt(6);
    }
  else if (indx==10)
    {
      return 8.*s1s2*c1*sin(ph)/sqrt(6);
    }
  else if (indx==11)
    {
      return 8*c1/(3*sqrt(3));
    }
  else if (indx==12) //equivalent to AngF7_int
    {
      return -8*c1*c2/3.;
    }
  else if (indx==13)
    {
      return 4./9;
    }
  else if (indx==14)
    {
      return -8*c1*c2/3.;
    }
  else if (indx==15)
    {
      return -4*sqrt(2)*s1s2*cos(ph)/3;
    }
  else
    {
      cout<<"No angular term selected. Return 0."<<endl;
      return 0;
    }

}


double IntegrateLegendre(int _l1, int _m1, int _l2, int _m2)
{
  // this was verified to match mathematica for 
  // l1 in [0,2], m1 in [0,l1], l2 in [l1,4], m2 in [0,l2]
  if ( _m1==_m2 )                 return ( _l1 == _l2) ?  TMath::Factorial(_l1+_m2)/TMath::Factorial(_l1-_m1)*double(2)/(2*_l1+1) : 0.;
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


double get_AngTerm_Integral(Int_t indx, Int_t _l, Int_t _n, Int_t _m )
{

  double ang_int = 0;
  double N =sqrt(TMath::Pi())/9.;
  

  if (indx==1)
    {
      // 4*N*(2 P00 Y00 + 4/sqrt(5) P00 Y20 + 4 P20 Y00 + 8/sqrt(5) P20 Y20)
      if (_n==0 && _m==0) return 4*N*(2*IntegrateLegendre(0, 0, _l, 0) + 4*IntegrateLegendre(2, 0, _l, 0));
      else if (_n==2 && _m==0 ) return 4*N*(4/sqrt(5)*IntegrateLegendre(0, 0, _l, 0) + 8/sqrt(5)*IntegrateLegendre(2, 0, _l, 0));
      else return 0;

    }

  else if (indx==2)
    {
      //4*N*(2 P00 Y00 - 2/sqrt(5) P00 Y20 +2sqrt(3)/sqrt(5) P00Y22 - 2 P20 Y00 + 2/sqrt(5) P20 Y20 - 2sqrt(3)/sqrt(5) P20 Y22)
      if (_n==0 && _m==0) return 4*N*(2*IntegrateLegendre(0, 0, _l, 0) - 2*IntegrateLegendre(2, 0, _l, 0));
      else if (_n==2 && _m==0) return 4*N*(-2/sqrt(5)*IntegrateLegendre(0, 0, _l, 0) + 2/sqrt(5)*IntegrateLegendre(2, 0, _l, 0));
      else if (_n==2 && _m==2) return 4*N*2*sqrt(3)/sqrt(5)*(IntegrateLegendre(0, 0, _l, 0) - IntegrateLegendre(2, 0, _l, 0));
      else return 0;

    }
  else if (indx==3)
    {
      //4*N*(2 P00 Y00 - 2/sqrt(5) P00 Y20 -2sqrt(3)/sqrt(5) P00Y22 - 2 P20 Y00 + 2/sqrt(5) P20 Y20 + 2sqrt(3)/sqrt(5) P20 Y22)
      if (_n==0 && _m==0) return 4*N*(2*IntegrateLegendre(0, 0, _l, 0) - 2*IntegrateLegendre(2, 0, _l, 0));
      else if (_n==2 && _m==0) return 4*N*(-2/sqrt(5)*IntegrateLegendre(0, 0, _l, 0) + 2/sqrt(5)*IntegrateLegendre(2, 0, _l, 0));
      else if (_n==2 && _m==2) return 4*N*2*sqrt(3)/sqrt(5)*(-1*IntegrateLegendre(0, 0, _l, 0) + IntegrateLegendre(2, 0, _l, 0));
      else return 0;
    }
  else if (indx==5)
    {
      //4N*2 sqrt(6)/sqrt(5) P21 Y21
      if (_n==2 && _m==1) return 4*N*2*sqrt(6/5)*IntegrateLegendre(2, 1, _l, 0);
      else return 0;
    }



  else if (indx==7)
    {
      //4*N*(2*P00 Y00 + 4*P20 Y00)
      if (_n==0 && _m==0) return 4*N*(2*IntegrateLegendre(0, 0, _l, 0) + 4*IntegrateLegendre(2, 0, _l, 0) );
      else return 0;
			    
    }
  else if (indx==8)
    {
      //-4*N*(4*P00 Y10 + 8*P20 Y10)
      if (_n==1 && _m==0) return -4*N*(4*IntegrateLegendre(0, 0, _l, 0) + 8*IntegrateLegendre(2, 0, _l, 0));
      else return 0;
    }
  else if (indx==9)
    {
      //-4*N*2sqrt(2) P21 Y11
      if (_n==1 && _m==1) return -4*N*2*sqrt(2)*IntegrateLegendre(2,1,_l,0);
      else return 0;
    }
  else if (indx==10)
    {
      //4*N*2sqrt(2) P21 Y1-1
      if (_n==1 && _m==-1) return 4*N*2*sqrt(2)*IntegrateLegendre(2,1,_l,0);
      else return 0;
    }
  else if (indx==11)
    {
      //4*N*4*sqrt(3) P10 Y00
      if (_n==0 && _m==0) return 4*N*4*sqrt(3)*IntegrateLegendre(1, 0, _l, 0);
      else return 0;
    }


  //Revisar los signos!!!!!
  else if (indx==71)
    {
      //4*N*(2*P00 Y00 + 4/sqrt(5)*P00 Y20)
      if (_n==0 && _m==0) return 4*N*2*IntegrateLegendre(0, 0, _l, 0);
      else if (_n==2 && _m==0) return 4*N*4/sqrt(5)*IntegrateLegendre(0, 0, _l, 0);
      else return 0;
			    
    }
  else if (indx==81)
    {
      //-4*N*(4*sqrt(3) P10 Y00 + 8*sqrt(3)/sqrt(5) P10 Y20)
      if (_n==0 && _m==0) return -4*N*4*sqrt(3)*IntegrateLegendre(1, 0, _l, 0);
      else if (_n==2 && _m==0) return -8*sqrt(3/5)*IntegrateLegendre(1, 0, _l, 0);
      else return 0;
    }
  else if (indx==91)
    {
      //-4*N*6 sqrt(2/5) P11 Y21
      if (_n==2 && _m==1) return -4*N*6*sqrt(2/5)*IntegrateLegendre(1,1,_l,0);
      else return 0;
    }
  else if (indx==101)
    {
      //4*N*6 sqrt(2/5) P11 Y2-1
      if (_n==2 && _m==-1) return 4*N*6*sqrt(2/5)*IntegrateLegendre(1,1,_l,0);
      else return 0;
    }
  else if (indx==111)
    {
      //4*N*4 P00 Y10
      if (_n==1 && _m==0) return 4*N*4*IntegrateLegendre(0, 0, _l, 0);
      else return 0;
    }





  else if (indx==12) //equivalent to AngF7_int
    {
      //4*N*2 sqrt(3) P10 Y10
      if (_n==1 && _m==0) return 4*N*2*sqrt(3)*IntegrateLegendre(1, 0, _l, 0);
      else return 0;
    }


  else if (indx==13)
    {
      //4*N*2 P00 Y00
      if (_n==0 && _m==0) return 4*N*2*IntegrateLegendre(0, 0, _l, 0);
      else return 0;
    }
  else if (indx==14)
    {
      //4*N*4*sqrt(3)* P10 Y10
      if (_n==1 && _m==0) return 4*N*4*sqrt(3)*IntegrateLegendre(1, 0, _l, 0);
      else return 0;
    }
  else if (indx==15)
    {
      //-4*N*2*sqrt(6) P11 Y11
      if (_n==1 && _m==1) return -4*N*2*sqrt(6)*IntegrateLegendre(1,1,_l,0);
      else return 0;
    }
  cout<<"No angular term selected for indx = "<<indx<<" . Return 0."<<endl;
  return 0;
}





double get_AngTerm_Integral_c2_ph(Int_t indx, Double_t c1,Int_t _n, Int_t _m )
{

  double ang_int = 0;
  double N =sqrt(TMath::Pi())/9.;
  

  if (indx==1)
    {
      // 4*N*(2 P00 Y00 + 4/sqrt(5) P00 Y20 + 4 P20 Y00 + 8/sqrt(5) P20 Y20)
      if (_n==0 && _m==0) return 4*N*(2*ROOT::Math::assoc_legendre(0, 0, c1) + 4*ROOT::Math::assoc_legendre(2, 0, c1));
      else if (_n==2 && _m==0 ) return 4*N*(4/sqrt(5)*ROOT::Math::assoc_legendre(0, 0, c1) + 8/sqrt(5)*ROOT::Math::assoc_legendre(2, 0, c1));
      else return 0;
    }

  else if (indx==2)
    {
      //4*N*(2 P00 Y00 - 2/sqrt(5) P00 Y20 +2sqrt(3)/sqrt(5) P00Y22 - 2 P20 Y00 + 2/sqrt(5) P20 Y20 - 2sqrt(3)/sqrt(5) P20 Y22)
      if (_n==0 && _m==0) return 4*N*(2*ROOT::Math::assoc_legendre(0, 0, c1) - 2*ROOT::Math::assoc_legendre(2, 0, c1));
      else if (_n==2 && _m==0) return 4*N*(-2/sqrt(5)*ROOT::Math::assoc_legendre(0, 0, c1) + 2/sqrt(5)*ROOT::Math::assoc_legendre(2, 0, c1));
      else if (_n==2 && _m==2) return 4*N*2*sqrt(3)/sqrt(5)*(ROOT::Math::assoc_legendre(0, 0, c1) - ROOT::Math::assoc_legendre(2, 0, c1));
      else return 0;

    }
  else if (indx==3)
    {
      //4*N*(2 P00 Y00 - 2/sqrt(5) P00 Y20 -2sqrt(3)/sqrt(5) P00Y22 - 2 P20 Y00 + 2/sqrt(5) P20 Y20 + 2sqrt(3)/sqrt(5) P20 Y22)
      if (_n==0 && _m==0) return 4*N*(2*ROOT::Math::assoc_legendre(0, 0, c1) - 2*ROOT::Math::assoc_legendre(2, 0, c1));
      else if (_n==2 && _m==0) return 4*N*(-2/sqrt(5)*ROOT::Math::assoc_legendre(0, 0, c1) + 2/sqrt(5)*ROOT::Math::assoc_legendre(2, 0, c1));
      else if (_n==2 && _m==2) return 4*N*2*sqrt(3)/sqrt(5)*(-1*ROOT::Math::assoc_legendre(0, 0, c1) + ROOT::Math::assoc_legendre(2, 0, c1));
      else return 0;
    }
  else if (indx==5)
    {
      //4N*2 sqrt(6)/sqrt(5) P21 Y21
      if (_n==2 && _m==1) return 4*N*2*sqrt(6/5)*ROOT::Math::assoc_legendre(2, 1, c1);
      else return 0;
    }



  else if (indx==7)
    {
      //4*N*(2*P00 Y00 + 4*P20 Y00)
      if (_n==0 && _m==0) return 4*N*(2*ROOT::Math::assoc_legendre(0, 0, c1) + 4*ROOT::Math::assoc_legendre(2, 0, c1) );
      else return 0;
			    
    }
  else if (indx==8)
    {
      //-4*N*(4*P00 Y10 + 8*P20 Y10)
      if (_n==1 && _m==0) return -4*N*(4*ROOT::Math::assoc_legendre(0, 0, c1) + 8*ROOT::Math::assoc_legendre(2, 0, c1));
      else return 0;
    }
  else if (indx==9)
    {
      //-4*N*2sqrt(2) P21 Y11
      if (_n==1 && _m==1) return -4*N*2*sqrt(2)*ROOT::Math::assoc_legendre(2,1,c1);
      else return 0;
    }
  else if (indx==10)
    {
      //4*N*2sqrt(2) P21 Y1-1
      if (_n==1 && _m==-1) return 4*N*2*sqrt(2)*ROOT::Math::assoc_legendre(2,1,c1);
      else return 0;
    }
  else if (indx==11)
    {
      //4*N*4*sqrt(3) P10 Y00
      if (_n==0 && _m==0) return 4*N*4*sqrt(3)*ROOT::Math::assoc_legendre(1, 0, c1);
      else return 0;
    }


  //Revisar los signos!!!!!
  else if (indx==71)
    {
      //4*N*(2*P00 Y00 + 4/sqrt(5)*P00 Y20)
      if (_n==0 && _m==0) return 4*N*2*ROOT::Math::assoc_legendre(0, 0, c1);
      else if (_n==2 && _m==0) return 4*N*4/sqrt(5)*ROOT::Math::assoc_legendre(0, 0, c1);
      else return 0;
			    
    }
  else if (indx==81)
    {
      //-4*N*(4*sqrt(3) P10 Y00 + 8*sqrt(3)/sqrt(5) P10 Y20)
      if (_n==0 && _m==0) return -4*N*4*sqrt(3)*ROOT::Math::assoc_legendre(1, 0, c1);
      else if (_n==2 && _m==0) return -8*sqrt(3/5)*ROOT::Math::assoc_legendre(1, 0, c1);
      else return 0;
    }
  else if (indx==91)
    {
      //-4*N*6 sqrt(2/5) P11 Y21
      if (_n==2 && _m==1) return -4*N*6*sqrt(2/5)*ROOT::Math::assoc_legendre(1,1,c1);
      else return 0;
    }
  else if (indx==101)
    {
      //4*N*6 sqrt(2/5) P11 Y2-1
      if (_n==2 && _m==-1) return 4*N*6*sqrt(2/5)*ROOT::Math::assoc_legendre(1,1,c1);
      else return 0;
    }
  else if (indx==111)
    {
      //4*N*4 P00 Y10
      if (_n==1 && _m==0) return 4*N*4*ROOT::Math::assoc_legendre(0, 0, c1);
      else return 0;
    }





  else if (indx==12) //equivalent to AngF7_int
    {
      //4*N*2 sqrt(3) P10 Y10
      if (_n==1 && _m==0) return 4*N*2*sqrt(3)*ROOT::Math::assoc_legendre(1, 0, c1);
      else return 0;
    }


  else if (indx==13)
    {
      //4*N*2 P00 Y00
      if (_n==0 && _m==0) return 4*N*2*ROOT::Math::assoc_legendre(0, 0, c1);
      else return 0;
    }
  else if (indx==14)
    {
      //4*N*4*sqrt(3)* P10 Y10
      if (_n==1 && _m==0) return 4*N*4*sqrt(3)*ROOT::Math::assoc_legendre(1, 0, c1);
      else return 0;
    }
  else if (indx==15)
    {
      //-4*N*2*sqrt(6) P11 Y11
      if (_n==1 && _m==1) return -4*N*2*sqrt(6)*ROOT::Math::assoc_legendre(1,1,c1);
      else return 0;
    }
  cout<<"No angular term selected for indx = "<<indx<<" . Return 0."<<endl;
  return 0;
}

