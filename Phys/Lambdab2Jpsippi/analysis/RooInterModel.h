#ifndef ROOINTERMODEL_H 
#define ROOINTERMODEL_H 1

// Include files

#include "RooAbsPdf.h"
#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooArgList.h"
#include "RooListProxy.h"

#include "PhaseSpace.h"
#include <complex>


class RooInterModel : public RooAbsPdf {

public: 
  /// Standard constructor
  RooInterModel( const char *name, 
                 const char *title,
                 RooAbsReal& q, 
                 RooAbsReal& p1, 
                 RooAbsReal& frac_VA,
                 const RooArgList& mean, 
                 const RooArgList& width,
                 const RooArgList& phase,
                 const RooArgList& scale ); 
  
  RooInterModel(const RooInterModel& other, const char* name=0) ;

  virtual TObject* clone(const char* newname) const { 
     return new RooInterModel(*this,newname); 
  }
  
  virtual ~RooInterModel( ); ///< Destructor
  

  
  double numIntegrateInterference(double,double,int);
  double numIntegrateInterferenceTwoBW(double,double);
  double numIntegrateInterferenceThreeBW(double,double);
  double numIntegrateInterferenceFourBW(double,double);
  double numIntegrateNonres(double,double);
  double constNumIntegrateNonres(double,double) const;
  double constNumIntegrateAll(double,double) const;
  double numIntegrateBW(double,double,int);
  bool citableFF;
  TF1* nonres_comp;
  TF1* BW_comp;
  TF1* im_inter_comp;
  TF1* real_inter_comp;
  TF1* inter_comp;
  TF1* all_comp;
protected:
  
  std::complex< double > rotate( const Double_t arg ) const  ;

  std::complex< double > nonres() const ;
  
  
  std::complex< double > bw( const Double_t q, 
                             const Double_t mean, 
                             const Double_t gamma ) const ;
  Double_t FF_bus(const Double_t) const;
  Double_t eff(const Double_t) const;
  Double_t evaluate() const ;

  // double inteference(double);


private:

  RooRealProxy q_;
  RooRealProxy p1_ ;
  RooRealProxy frac_VA_;
  RooListProxy mean_;
  RooListProxy width_;
  RooListProxy phase_;
  RooListProxy scale_;
  


  
protected: 
 PhaseSpace psp_;

private:
  

  ClassDef(RooInterModel,1)
  
};
#endif // ROOINTERMODEL_H
