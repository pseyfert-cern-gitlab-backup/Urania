/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "B2DXFitters/TagEfficiencyWeightNoCat.h" 
#include "RooAbsReal.h" 
#include <math.h> 
#include "TMath.h" 
#include <cmath>
#include <limits>

TagEfficiencyWeightNoCat::TagEfficiencyWeightNoCat(const char *name, const char *title, 
    RooAbsReal& _tag,
    RooAbsReal& _eff) :
    RooAbsReal(name,title), 
    tag("tag","tag",this,_tag),
    eff("eff","eff",this,_eff)
{ } 

TagEfficiencyWeightNoCat::TagEfficiencyWeightNoCat(const TagEfficiencyWeightNoCat& other, const char* name) :  
    RooAbsReal(other,name), 
    tag("tag",this,other.tag),
    eff("eff",this,other.eff)
{ } 

TagEfficiencyWeightNoCat::TagEfficiencyWeightNoCat() { }
TagEfficiencyWeightNoCat::~TagEfficiencyWeightNoCat() { }


Double_t TagEfficiencyWeightNoCat::evaluate() const 
{
    double t = (double) tag;
    if (fabs(t) > double(std::numeric_limits<float>::epsilon())) return double(eff);
    else return 1. - double(eff);
}
