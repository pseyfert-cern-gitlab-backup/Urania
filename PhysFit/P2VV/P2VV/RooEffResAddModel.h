// $Id: $
#ifndef ROOEFFRESADDMODEL_H
#define ROOEFFRESADDMODEL_H 1

// Include files
#include <RooAddModel.h>

#include <P2VV/RooAbsEffResModel.h>

/** @class RooEffResAddModel RooEffResAddModel.h P2VV/RooEffResAddModel.h
 *
 *
 *  @author Roel Aaij
 *  @date   2013-05-11
 */
class RooEffResAddModel : public RooAddModel, public RooAbsEffResModel {
public:
   /// Standard constructor
   RooEffResAddModel();
   RooEffResAddModel(const char *name, const char *title, const RooArgList& modelList,
                     const RooArgList& coefList, Bool_t ownPdfList=kFALSE);
   /// Copy constructor
   RooEffResAddModel(const RooEffResAddModel& other, const char* newName = 0);
   RooEffResAddModel(const RooAddModel& other, const char* newName = 0);

   /// Destructor
   virtual ~RooEffResAddModel( );

   /// Virtual constructor
   TObject* clone(const char* name) const override {
      return new RooEffResAddModel(*this, name);
   }

   RooAbsGenContext* modelGenContext(const RooAbsAnaConvPdf& convPdf, const RooArgSet &vars,
                                     const RooDataSet *prototype=0, const RooArgSet* auxProto=0,
                                     Bool_t verbose= kFALSE) const override;

   /**
    * Get a RooArgSet of all observables, caller takes ownership.
    * (pointer because genreflex dictionaries can't handle value)
    *
    * @return RooArgSet of observables
    */
   RooArgSet* observables() const override;

   const RooAbsReal* efficiency() const override;

protected:

   RooResolutionModel* convolution(RooFormulaVar* inBasis, RooAbsArg* owner) const override;

private:

   mutable RooAddModel* _addModel;

   ClassDef(RooEffResAddModel, 1)

};
#endif // P2VV_ROOEFFRESADDMODEL_H
