// $Id: $
#ifndef ROOPHYSFITTER_ROOPEARSONSCHI2VAR_H
#define ROOPHYSFITTER_ROOPEARSONSCHI2VAR_H 1

// Include files
#include "RooAbsOptTestStatistic.h"
#include "RooAbsPdf.h"
#include "RooDataHist.h"
#include "RooCmdArg.h"

/** @class RooPearsonsChi2Var RooPearsonsChi2Var.h RooPhysFitter/RooPearsonsChi2Var.h
 *  
 *
 *  @author Philip Hunt (LHCB)
 *  @date   2011-04-16
 */

class RooPearsonsChi2Var : public RooAbsOptTestStatistic
{
public:
    enum FuncMode { Function, Pdf, ExtendedPdf };

    /// constructors
    RooPearsonsChi2Var( const char* name, const char* title,
                        RooAbsPdf& pdf, RooDataHist& data,
                        Bool_t extended = kFALSE, const char* rangeName = 0,
                        const char* addCoefRangeName = 0,
                        Int_t nCPU = 1,
                        Bool_t interleave = kFALSE, Bool_t verbose = kTRUE,
                        Bool_t splitCutRange = kTRUE,
                        RooAbsData::ErrorType = RooDataHist::SumW2);

    RooPearsonsChi2Var(const char* name, const char* title,
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

    RooPearsonsChi2Var(const char* name, const char* title,
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
    RooPearsonsChi2Var(const char* name, const char* title,
                       RooAbsReal& func, RooDataHist& data,
                       const RooArgSet& projDeps,
                       RooPearsonsChi2Var::FuncMode funcMode,
                       const char* rangeName = 0, const char* addCoefRangeName = 0,
                       Int_t nCPU = 1, Bool_t interleave = kFALSE,
                       Bool_t verbose = kTRUE, Bool_t splitCutRange = kTRUE,
                       RooAbsData::ErrorType = RooDataHist::SumW2);

    /// copy constructor
    RooPearsonsChi2Var(const RooPearsonsChi2Var& other, const char* name=0);

    /// virtual constructor
    virtual RooAbsTestStatistic* create(const char* name, const char* title,
                                        RooAbsReal& pdf, RooAbsData& dhist,
                                        const RooArgSet& projDeps,
                                        const char* rangeName = 0,
                                        const char* addCoefRangeName = 0,
                                        Int_t nCPU = 1,
                                        Bool_t interleave = kFALSE,
                                        Bool_t verbose = kTRUE,
                                        Bool_t splitCutRange = kTRUE)
    {
        // Virtual constructor
        return new RooPearsonsChi2Var(name,title,(RooAbsPdf&)pdf,
                                      (RooDataHist&)dhist,
                                      projDeps,_funcMode,rangeName,
                                      addCoefRangeName,nCPU,interleave,
                                      verbose, splitCutRange,_etype) ;
    }

    virtual ~RooPearsonsChi2Var( ); ///< Destructor

    /// virtual clone method
    virtual TObject* clone(const char* newname) const
    {
        return new RooPearsonsChi2Var(*this,newname);
    }

    virtual Double_t defaultErrorLevel() const
    {
        // The default error level for MINUIT error analysis for a chi^2 is 1.0
        return 1.0 ;
    }

protected:

    static RooArgSet _emptySet; // supports named argument constructor
    RooAbsData::ErrorType _etype; // Error type stored in associated RooDataHist
    RooPearsonsChi2Var::FuncMode _funcMode; // Function, p.d.f. or extended p.d.f.
    virtual Double_t evaluatePartition(Int_t firstEvent, Int_t lastEvent,
                                       Int_t stepSize) const;
    ClassDef(RooPearsonsChi2Var,1);

private:

};
#endif // ROOPHYSFITTER_ROOPEARSONSCHI2VAR_H
