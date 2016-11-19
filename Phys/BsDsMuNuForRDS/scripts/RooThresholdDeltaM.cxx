#include "RooThresholdDeltaM.h"
#include <math.h>
#include "TMath.h"
#include "Riostream.h"

 RooThresholdDeltaM::RooThresholdDeltaM(const char *name, const char *title,
                        RooAbsReal& _x,
                        RooAbsReal& _dm0,
                        RooAbsReal& _c) :
   RooAbsPdf(name,title),
   x("x","x",this,_x),
   dm0("dm0","dm0",this,_dm0),
   c("c","c",this,_c)
 {
 }


 RooThresholdDeltaM::RooThresholdDeltaM(const RooThresholdDeltaM& other, const char* name) :
   RooAbsPdf(other,name),
   x("x",this,other.x),
   dm0("dm0",this,other.dm0),
   c("c",this,other.c)
 {
 }



 Double_t RooThresholdDeltaM::evaluate() const
 {
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
   if (x/dm0<1) return 0;
   else return sqrt(x/dm0-1)*TMath::Exp(-c*(x/dm0));
 }
