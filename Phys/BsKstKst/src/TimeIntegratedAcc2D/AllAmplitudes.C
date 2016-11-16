#include <iostream>
#include <math.h>
#include "Math/SpecFunc.h"
using namespace std;


Double_t get_Amplitude(Int_t indx, 
		       Double_t fL, Double_t fpa, Double_t Asp2, Double_t Asm2, Double_t Ass2,
		       Double_t dpa, Double_t dpe, Double_t dsp, Double_t dsm, Double_t dss,
		       Double_t Gs, Double_t DGs, Double_t norm)
{

 
   Double_t Ap2 = 1-Asp2-Asm2-Ass2;
   Double_t A02 = fL*Ap2;
   Double_t Apa2 = fpa*Ap2;
   Double_t fpe = 1-fL-fpa;
   Double_t Ape2 = fpe*Ap2;

   if (A02*Apa2*Ape2*Asp2*Asm2*Ass2<0) return 0;

   Double_t A0 = sqrt(A02);
   Double_t Apa = sqrt(Apa2);
   Double_t Ape = sqrt(Ape2);
   Double_t Asp = sqrt(Asp2);
   Double_t Asm = sqrt(Asm2);
   Double_t Ass = sqrt(Ass2);

   Double_t d0 = 0;

   Double_t GL = Gs + DGs/2.;
   Double_t GH = Gs - DGs/2.;


  if (indx==1)
    {
      return A02*norm;
    }
  else if (indx==2)
    {
      return Apa2*norm;
    }
  else if (indx==3)
    {
      return Ape2*GL/GH*norm;
    }
  else if (indx==5)
    {
      return A0*Apa*cos(dpa)*norm;
    }
  else if (indx==7 || indx==71 || indx==12)
    {
      return GL*norm;
    }
  else if (indx==8 || indx==81 || indx==9 || indx==91 || indx==11 || indx==111 || indx==14 || indx==15)
    {
      return 1*norm;
    }
  else if (indx==10)
    {
      return GL/GH*norm;
    }
  else if (indx==101)
    {
      return -1*GL/GH*norm;
    }
  else if (indx==13)
    {
      return Ass2*norm;
    }
  else
    {
      cout<<"No angular term selected. Return 0."<<endl;
      return 0;
    }

  return 1;
}

