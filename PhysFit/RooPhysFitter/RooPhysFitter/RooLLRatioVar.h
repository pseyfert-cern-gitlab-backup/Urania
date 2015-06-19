// $Id: $
#ifndef ROOPHYSFITTER_ROOLLRATIOVAR_H
#define ROOPHYSFITTER_ROOLLRATIOVAR_H 1

// Include files
#include "RooAbsOptTestStatistic.h"
#include "RooAbsPdf.h"
#include "RooDataHist.h"
#include "RooCmdArg.h"

/** @class RooLLRatioVar RooLLRatioVar.h RooPhysFitter/RooLLRatioVar.h
 *  
 *
 *  @author Philip Hunt (LHCB)
 *  @date   2011-04-16
 */

class RooLLRatioVar : public RooAbsOptTestStatistic
{
public:
    enum FuncMode { Function, Pdf, ExtendedPdf };

    /// constructors
    RooLLRatioVar( const char* name, const char* title,
                   RooAbsPdf& pdf, RooDataHist& data,
                   Bool_t extended = kFALSE, const char* rangeName = 0,
                   const char* addCoefRangeName = 0, Int_t nCPU = 1,
                   RooFit::MPSplit interleave = RooFit::BulkPartition,
                   Bool_t verbose = kTRUE,
                   Bool_t splitCutRange = kTRUE,
                   RooAbsData::ErrorType = RooDataHist::SumW2);

    RooLLRatioVar(const char* name, const char* title,
                  RooAbsReal& func, RooDataHist& data,
                  const RooCmdArg& arg1,
                  const RooCmdArg& arg2 = RooCmdArg::none(),
                  const RooCmdArg& arg3 = RooCmdArg::none(),
                  const RooCmdArg& arg4 = RooCmdArg::none(),
                  const RooCmdArg& arg5 = RooCmdArg::none(),
                  const RooCmdArg& arg6 = RooCmdArg::none(),
                  const RooCmdArg& arg7 = RooCmdArg::none(),
                  const RooCmdArg& arg8 = RooCmdArg::none(),
                  const RooCmdArg& arg9 = RooCmdArg::none());

    RooLLRatioVar(const char* name, const char* title,
                  RooAbsPdf& pdf, RooDataHist& data,
                  const RooCmdArg& arg1,
                  const RooCmdArg& arg2 = RooCmdArg::none(),
                  const RooCmdArg& arg3 = RooCmdArg::none(),
                  const RooCmdArg& arg4 = RooCmdArg::none(),
                  const RooCmdArg& arg5 = RooCmdArg::none(),
                  const RooCmdArg& arg6 = RooCmdArg::none(),
                  const RooCmdArg& arg7 = RooCmdArg::none(),
                  const RooCmdArg& arg8 = RooCmdArg::none(),
                  const RooCmdArg& arg9 = RooCmdArg::none());
    RooLLRatioVar(const char* name, const char* title,
                  RooAbsReal& func, RooDataHist& data,
                  const RooArgSet& projDeps,
                  RooLLRatioVar::FuncMode funcMode,
                  const char* rangeName = 0, const char* addCoefRangeName = 0,
                  Int_t nCPU = 1,
                  RooFit::MPSplit interleave = RooFit::BulkPartition,
                  Bool_t verbose = kTRUE, Bool_t splitCutRange = kTRUE,
                  RooAbsData::ErrorType = RooDataHist::SumW2);

    /// copy constructor
    RooLLRatioVar(const RooLLRatioVar& other, const char* name=0);

    /// virtual constructor
    virtual RooAbsTestStatistic* create(const char* name, const char* title,
                                        RooAbsReal& pdf, RooAbsData& dhist,
                                        const RooArgSet& projDeps,
                                        const char* rangeName = 0,
                                        const char* addCoefRangeName = 0,
                                        Int_t nCPU = 1,
                                        RooFit::MPSplit interleave = RooFit::BulkPartition,
                                        Bool_t verbose = kTRUE,
                                        Bool_t splitCutRange = kTRUE)
    {
      // Virtual constructor
      return new RooLLRatioVar(name,title,(RooAbsPdf&)pdf,
                               (RooDataHist&)dhist,
                               projDeps,_funcMode,rangeName,
                               addCoefRangeName,nCPU,interleave,
                               verbose, splitCutRange,_etype) ;
    }

    virtual ~RooLLRatioVar( ); ///< Destructor

    /// virtual clone method
    virtual TObject* clone(const char* newname) const
    {
        return new RooLLRatioVar(*this,newname);
    }

    virtual Double_t defaultErrorLevel() const
    {
        // The default error level for MINUIT error analysis for a chi^2 is 1.0
        return 1.0 ;
    }

protected:

    static RooArgSet _emptySet; // supports named argument constructor
    RooAbsData::ErrorType _etype; // Error type stored in associated RooDataHist
    RooLLRatioVar::FuncMode _funcMode; // Function, p.d.f. or extended p.d.f.

    virtual Double_t evaluatePartition(Int_t firstEvent, Int_t lastEvent,
                                       Int_t stepSize) const;
    ClassDef(RooLLRatioVar,1);

private:

};
#endif // ROOPHYSFITTER_ROOLLRATIOVAR_H
