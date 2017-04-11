/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef TAGEFFICIENCYWEIGHTNOCAT
#define TAGEFFICIENCYWEIGHTNOCAT

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooAbsReal.h"
 
class TagEfficiencyWeightNoCat : public RooAbsReal {
public:
  TagEfficiencyWeightNoCat(); 
  TagEfficiencyWeightNoCat(const char *name, const char *title,
          RooAbsReal& _tag,
          RooAbsReal& _eff);
  TagEfficiencyWeightNoCat(const TagEfficiencyWeightNoCat& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new TagEfficiencyWeightNoCat(*this,newname); }
  virtual ~TagEfficiencyWeightNoCat();

protected:

  RooRealProxy tag;
  RooRealProxy eff;
  
  Double_t evaluate() const;

private:
  ClassDef(TagEfficiencyWeightNoCat, 1);
};
 
#endif