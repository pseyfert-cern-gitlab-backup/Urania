/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef TRANSF5
#define TRANSF5

#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "RooRealVar.h"
 
class TransF5 : public RooAbsReal {
public:
  TransF5() {} ; 
  // Constructor with weights
  TransF5(const char *name, const char *title,
	      RooAbsReal& _CPsi,
	      RooAbsReal& _CTheta,
	      RooAbsReal& _Phi,
	      RooAbsReal& _X):
    RooAbsReal(name,title), 
    m_useX(1),
    CPsi("CPsi","CPsi",this,_CPsi),
    CTheta("CTheta","CTheta",this,_CTheta),
    Phi("Phi","Phi",this,_Phi),
    X("X","X",this,_X)
      {
      }

  // Constructor without weights
  TransF5(const char *name, const char *title,
	      RooAbsReal& _CPsi,
	      RooAbsReal& _CTheta,
	  RooAbsReal& _Phi):
      RooAbsReal(name,title), 
      m_useX(false),
      CPsi("CPsi","CPsi",this,_CPsi),
      CTheta("CTheta","CTheta",this,_CTheta),
      Phi("Phi","Phi",this,_Phi),
      X("X", "X", this, *new RooRealVar( (std::string(name)+"_dummyX").c_str(),
					 (std::string(name)+"_dummyX").c_str(),
					 0.) )
	{ 
	} 

  TransF5(const TransF5& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new TransF5(*this,newname); }
  inline virtual ~TransF5() { }

  Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const ;
  Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ;

  inline bool  useX() const { return m_useX; }
  
  inline void  useX(bool useIt) { m_useX = useIt; }

protected:

  bool m_useX;
  RooRealProxy CPsi ;
  RooRealProxy CTheta ;
  RooRealProxy Phi ;
  RooRealProxy X;

  Double_t evaluate() const ;

private:

  ClassDef(TransF5,1) // Your description goes here...
};
 
#endif