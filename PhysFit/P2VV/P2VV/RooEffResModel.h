/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 *    File: $Id: RooGaussModel.h,v 1.21 2007/05/11 09:13:07 verkerke Exp $
 * Authors:                                                                  *
 *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/
#ifndef ROO_EFF_RES_MODEL
#define ROO_EFF_RES_MODEL

#include <RooRealProxy.h>
#include <RooObjCacheManager.h>
#include <RooSetProxy.h>

#include <P2VV/RooAbsEffResModel.h>

class RooCustomizer;
class RooResoluitionModel;
class RooAbsAnaConvPdf;

class RooEffResModel : public RooResolutionModel, public RooAbsEffResModel {
public:

   // Constructors, assignment etc
   inline RooEffResModel()  { }
   RooEffResModel(const char *name, const char *title, RooResolutionModel& , RooAbsReal& );
   RooEffResModel(const RooEffResModel& other, const char* name=0);
   RooEffResModel* clone(const char* newname) const override { return new RooEffResModel(*this,newname) ; }
   virtual ~RooEffResModel();

   Int_t basisCode(const char* name) const override;
   Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const override;
   Double_t analyticalIntegral(Int_t code, const char* rangeName) const override;
   Bool_t forceAnalyticalInt(const RooAbsArg& /*dep*/) const override;

   Int_t getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t staticInitOK=kTRUE) const override;
   void initGenerator(Int_t code) override;
   void generateEvent(Int_t code) override;

   RooAbsGenContext* modelGenContext(const RooAbsAnaConvPdf& convPdf, const RooArgSet &vars,
                                     const RooDataSet *prototype=0, const RooArgSet* auxProto=0,
                                     Bool_t verbose= kFALSE) const override;

   const RooAbsReal* efficiency() const override {
      // Return pointer to efficiency
      return &_eff.arg();
   }

   virtual RooResolutionModel& model() const {
      return dynamic_cast<RooResolutionModel&>(*_model.absArg());
   }

   const RooArgList& getIntegralRanges(const RooArgSet& iset, const char* rangeName = 0) const;

   RooArgSet* observables() const override {
      // Return pointer to pdf in product
      // (pointer because genreflex dictionaries can't handle value)
      return new RooArgSet(_observables);
   }

protected:

   friend class RooMultiEffResModel;

   Double_t evaluate() const override;
   RooEffResModel* convolution(RooFormulaVar* inBasis, RooAbsArg* owner) const override;

private:

   class CacheElem : public RooAbsCacheElement {
   public:
      CacheElem(const RooEffResModel& parent,const RooArgSet& iset, const TNamed *rangeName);
      virtual ~CacheElem();

      RooArgList containedArgs(Action) override;
      Double_t getVal() { return _I->getVal(); }

      const RooAbsReal* integral() const { return _I; }

   private:
      friend class RooEffResModel;
      // Payload
      RooAbsReal* _I;
   };

   CacheElem *getCache(const RooArgSet* iset, const TNamed* rangeName = 0 ) const;

   // Pointers to our underlying components
   RooSetProxy _observables;
   RooRealProxy _model;     // RooResolutionModel
   RooRealProxy _eff;       // RooAbsReal

   typedef std::map<std::string, RooArgList*> RangeMap;
   mutable RangeMap _ranges;

   mutable RooObjCacheManager _cacheMgr;

   ClassDef(RooEffResModel,1) // EffResian Resolution Model
};

#endif
