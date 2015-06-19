/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 *    File: $Id: RooGaussModel.h,v 1.21 2007/05/11 09:13:07 verkerke Exp $
 * Authors:                                                                  *
 *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 * 2012-08-24 imported from G. Raven's p2vv git repository - M. Schiller     *
 * 2012-09-08 re-import from upstream, with some substantial modifications   *
 *	to ensure that the code does not leak memory (Manuel Schiller)       *
 * 2012-10-04 re-import from upstream, with some experimental changes, which *
 *	which are disabled by default for now...                             *
 *****************************************************************************/
#ifndef ROO_EFF_RES_MODEL
#define ROO_EFF_RES_MODEL

#include <string>

#include <RooRealProxy.h>
#include <RooObjCacheManager.h>
#include <RooSetProxy.h>
#include "RooAbsEffResModel.h"

// experimental code - do not define these for now...
#define _NEWCACHE

class RooCustomizer;
class RooResoluitionModel;
class RooAbsAnaConvPdf;

class RooEffResModel : public RooAbsEffResModel {
public:
   // Constructors, assignment etc
   inline RooEffResModel()  { }
   RooEffResModel(const char *name, const char *title, RooResolutionModel& , RooAbsReal& );
   RooEffResModel(const RooEffResModel& other, const char* name=0);
   virtual RooEffResModel* clone(const char* newname) const { return new RooEffResModel(*this,newname) ; }
   virtual ~RooEffResModel();
  
   virtual Int_t basisCode(const char* name) const ;
   virtual Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const ;
   virtual Double_t analyticalIntegral(Int_t code, const char* rangeName) const ;
   virtual Bool_t forceAnalyticalInt(const RooAbsArg& /*dep*/) const;

   virtual Int_t getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t staticInitOK=kTRUE) const;
   virtual void initGenerator(Int_t code);
   virtual void generateEvent(Int_t code);

   virtual RooAbsGenContext* modelGenContext(const RooAbsAnaConvPdf& convPdf, const RooArgSet &vars,
                                             const RooDataSet *prototype=0, const RooArgSet* auxProto=0,
                                             Bool_t verbose= kFALSE) const;
   
   virtual RooAbsReal* efficiency() const { 
      // Return pointer to pdf in product
      return static_cast<RooAbsReal*>(_eff.absArg());
   }

   virtual std::vector<RooAbsReal*> efficiencies() const { 
      // Return pointer to pdf in product
      return std::vector<RooAbsReal*>(1, efficiency());
   }   

   virtual RooResolutionModel& model() const {
      return dynamic_cast<RooResolutionModel&>(*_model.absArg());
   }

   const RooArgList& getIntegralRanges(const RooArgSet& iset, const char* rangeName = 0) const;

   const RooArgSet* observables() const { 
      // Return pointer to pdf in product
      return static_cast<const RooArgSet*>(&_observables);
   }

protected:

   virtual Double_t evaluate() const ;
   virtual RooEffResModel* convolution(RooFormulaVar* inBasis, RooAbsArg* owner) const;

private:

   class CacheElem : public RooAbsCacheElement {
   public:
      CacheElem(const RooEffResModel& parent,const RooArgSet& iset, const TNamed *rangeName);
      virtual ~CacheElem();

      virtual RooArgList containedArgs(Action) ;
      Double_t getVal(const RooArgSet* nset = 0) const;

   private:
      // Payload
#ifndef _NEWCACHE
      RooAbsReal *_I;
#else
      const RooArgList& _rangeNames; // range names
      RooRealVar* _x; // variable in which we parametrise
      RooAbsReal* _eff; // efficiency as function of _x
      RooAbsReal* _int; // integral over _x
      mutable Double_t _val; //! cached value
#endif
   };

   CacheElem *getCache(const RooArgSet* iset, const TNamed* rangeName = 0 ) const;

   // Pointers to our underlying components
   RooSetProxy _observables;
   RooRealProxy _model;     // RooResolutionModel
   RooRealProxy _eff;       // RooAbsReal 

   typedef std::map<std::string, RooArgList> RangeMap;
   mutable RangeMap _ranges; //!

   mutable RooObjCacheManager _cacheMgr; //!

   ClassDef(RooEffResModel,1) // EffResian Resolution Model
};

#endif
