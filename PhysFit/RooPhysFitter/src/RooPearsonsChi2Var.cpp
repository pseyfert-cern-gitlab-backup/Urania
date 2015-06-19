// $Id: $
// Include files
#include "RooFit.h"

#include "RooDataHist.h"
#include "RooAbsPdf.h"
#include "RooCmdConfig.h"
#include "RooMsgService.h"

#include "Riostream.h"

#include "RooRealVar.h"

#include "TMath.h"

// local
#include "RooPhysFitter/RooPearsonsChi2Var.h"

//ClassImp(RooPearsonsChi2Var);

RooArgSet RooPearsonsChi2Var::_emptySet ;

/*
//-----------------------------------------------------------------------------
// Implementation file for class : RooPearsonsChi2Var
//
// 2011-04-16 : Philip Hunt (LHCB)
//-----------------------------------------------------------------------------
 
//////////////////////////////////////////////////////////////////////////////
// 
// Class RooPearsonsChi2Var implements a the Pearson's chi^2 statistical test
// from a binned dataset  and a PDF. The chi^2 test statistic is calculated as 
//
//             / (f_PDF * N_tot/ V_bin) - N_bin \+2
//  Sum[bins] |  ------------------------------ |
//             \         N_bin                 /
//
// If no user-defined errors are defined for the dataset, poisson errors
// are used. In extended PDF mode, N_tot is substituted with N_expected.
//
// The number of degrees of freedom are returned by getNDOF, defined by
// nDOF = Nbins - nParams - 1, where Nbins is the number of bins in the dataset
// and nParams is the number of non-constant fit parameters.
 
//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
*/

RooPearsonsChi2Var::RooPearsonsChi2Var(const char *name, const char* title,
                                       RooAbsReal& func, RooDataHist& hdata,
                                       const RooCmdArg& arg1,
                                       const RooCmdArg& arg2,
                                       const RooCmdArg& arg3,
                                       const RooCmdArg& arg4,
                                       const RooCmdArg& arg5,
                                       const RooCmdArg& arg6,
                                       const RooCmdArg& arg7,
                                       const RooCmdArg& arg8,
                                       const RooCmdArg& arg9) :
        RooAbsOptTestStatistic(name,title,func,hdata,_emptySet,
                               RooCmdConfig::decodeStringOnTheFly("RooPearsonsChi2Var::RooPearsonsChi2Var",
                                                                  "RangeWithName",0,"",arg1,arg2,arg3,
                                                                  arg4,arg5,arg6,arg7,arg8,arg9),
                               0,
                               RooCmdConfig::decodeIntOnTheFly("RooPearsonsChi2Var::RooPearsonsChi2Var","NumCPU",0,1,
                                                               arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9),
                               RooCmdConfig::decodeIntOnTheFly("RooPearsonsChi2Var::RooPearsonsChi2Var","Verbose",
                                                               0,1,arg1,arg2,arg3,arg4,arg5,
                                                               arg6,arg7,arg8,arg9),
                               0)
{

    RooCmdConfig pc("RooPearsonsChi2Var::RooPearsonsChi2Var") ;
    pc.defineInt("etype","DataError",0,(Int_t)RooDataHist::SumW2) ;
    pc.allowUndefined() ;

    pc.process(arg1) ;
    pc.process(arg2) ;
    pc.process(arg3) ;
    pc.process(arg4) ;
    pc.process(arg5) ;
    pc.process(arg6) ;
    pc.process(arg7) ;
    pc.process(arg8) ;
    pc.process(arg9) ;

    _funcMode = Function ;
    _etype = (RooDataHist::ErrorType) pc.getInt("etype") ;
}


RooPearsonsChi2Var::RooPearsonsChi2Var(const char *name, const char* title,
                                       RooAbsPdf& pdf, RooDataHist& hdata,
                                       const RooCmdArg& arg1,const RooCmdArg& arg2,
                                       const RooCmdArg& arg3,
                                       const RooCmdArg& arg4,const RooCmdArg& arg5,
                                       const RooCmdArg& arg6,
                                       const RooCmdArg& arg7,const RooCmdArg& arg8,
                                       const RooCmdArg& arg9) :
        RooAbsOptTestStatistic(name,title,pdf,hdata,
                               *(const RooArgSet*)RooCmdConfig::decodeObjOnTheFly("RooPearsonsChi2Var::RooPearsonsChi2Var",
                                       "ProjectedObservables",
                                       0,&_emptySet
                                       ,arg1,arg2,arg3,arg4,
                                       arg5,arg6,arg7,arg8,arg9),
                               RooCmdConfig::decodeStringOnTheFly("RooPearsonsChi2Var::RooPearsonsChi2Var","RangeWithName",
                                                                  0,"",arg1,arg2,arg3,arg4,arg5,
                                                                  arg6,arg7,arg8,arg9),
                               RooCmdConfig::decodeStringOnTheFly("RooPearsonsChi2Var::RooPearsonsChi2Var","AddCoefRange",
                                                                  0,"",arg1,arg2,arg3,arg4,arg5,
                                                                  arg6,arg7,arg8,arg9),
                               RooCmdConfig::decodeIntOnTheFly("RooPearsonsChi2Var::RooPearsonsChi2Var","NumCPU",0,1,
                                                               arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9),
                               RooCmdConfig::decodeIntOnTheFly("RooPearsonsChi2Var::RooPearsonsChi2Var","Verbose",0,1,
                                                               arg1,arg2,arg3,arg4,arg5,arg6,arg7,
                                                               arg8,arg9),
                               RooCmdConfig::decodeIntOnTheFly("RooPearsonsChi2Var::RooPearsonsChi2Var","SplitRange",
                                                               0,0,arg1,arg2,arg3,arg4,arg5,arg6,arg7,
                                                               arg8,arg9))
        //  RooPearsonsChi2Var constructor. Optional arguments taken
        //
        //  Extended()   -- Include extended term in calculation
        //  DataError()  -- Choose between Poisson errors and Sum-of-weights errors
        //  NumCPU()     -- Activate parallel processing feature
        //  Range()      -- Fit only selected region
        //  SumCoefRange() -- Set the range in which to interpret the coefficients of RooAddPdf components
        //  SplitRange() -- Fit range is split by index catory of simultaneous PDF
        //  ConditionalObservables() -- Define projected observables
        //  Verbose()    -- Verbose output of GOF framework
{
    RooCmdConfig pc("RooPearsonsChi2Var::RooPearsonsChi2Var") ;
    pc.defineInt("extended","Extended",0,kFALSE) ;
    pc.defineInt("etype","DataError",0,(Int_t)RooDataHist::SumW2) ;
    pc.allowUndefined() ;

    pc.process(arg1) ;
    pc.process(arg2) ;
    pc.process(arg3) ;
    pc.process(arg4) ;
    pc.process(arg5) ;
    pc.process(arg6) ;
    pc.process(arg7) ;
    pc.process(arg8) ;
    pc.process(arg9) ;

    _funcMode = pc.getInt("extended") ? ExtendedPdf : Pdf ;
    _etype = (RooDataHist::ErrorType) pc.getInt("etype") ;
}


RooPearsonsChi2Var::RooPearsonsChi2Var(const char *name, const char *title,
                                       RooAbsPdf& pdf, RooDataHist& hdata,
                                       Bool_t extended, const char* cutRange,
                                       const char* addCoefRange,
                                       Int_t nCPU, Bool_t interleave,
                                       Bool_t verbose, Bool_t splitCutRange,
                                       RooDataHist::ErrorType etype) :
        RooAbsOptTestStatistic(name,title,pdf,hdata,RooArgSet(),cutRange,
                               addCoefRange,nCPU,interleave,verbose,splitCutRange),
        _etype(etype), _funcMode(extended?ExtendedPdf:Pdf)

{
    // Constructor of a chi2 for given p.d.f. with respect given binned
    // dataset. If cutRange is specified the calculation of the chi2 is
    // restricted to that named range. If addCoefRange is specified, the
    // interpretation of fractions for all component RooAddPdfs that do
    // not have a frozen range interpretation is set to chosen range
    // name. If nCPU is greater than one the chi^2 calculation is
    // paralellized over the specified number of processors. If
    // interleave is true the partitioning of event over processors
    // follows a (i % n == i_set) strategy rather than a bulk
    // partitioning strategy which may result in unequal load balancing
    // in binned datasets with many (adjacent) zero bins. If
    // splitCutRange is true the cutRange is used to construct an
    // individual cutRange for each RooSimultaneous index category state
    // name cutRange_{indexStateName}.
}


RooPearsonsChi2Var::RooPearsonsChi2Var(const char *name, const char *title,
                                       RooAbsReal& func, RooDataHist& hdata,
                                       const RooArgSet& projDeps,
                                       RooPearsonsChi2Var::FuncMode fmode,
                                       const char* cutRange,
                                       const char* addCoefRange,
                                       Int_t nCPU, Bool_t interleave,
                                       Bool_t verbose, Bool_t splitCutRange,
                                       RooDataHist::ErrorType etype) :
RooAbsOptTestStatistic(name,title,func,hdata,projDeps,cutRange,
                       addCoefRange,nCPU,interleave,verbose,splitCutRange),
_etype(etype), _funcMode(fmode)

{
    // Constructor of a chi2 for given p.d.f. with respect given binned
    // dataset taking the observables specified in projDeps as projected
    // observables. If cutRange is specified the calculation of the chi2
    // is restricted to that named range. If addCoefRange is specified,
    // the interpretation of fractions for all component RooAddPdfs that
    // do not have a frozen range interpretation is set to chosen range
    // name. If nCPU is greater than one the chi^2 calculation is
    // paralellized over the specified number of processors. If
    // interleave is true the partitioning of event over processors
    // follows a (i % n == i_set) strategy rather than a bulk
    // partitioning strategy which may result in unequal load balancing
    // in binned datasets with many (adjacent) zero bins. If
    // splitCutRange is true the cutRange is used to construct an
    // individual cutRange for each RooSimultaneous index category state
    // name cutRange_{indexStateName}.
}


RooPearsonsChi2Var::RooPearsonsChi2Var(const RooPearsonsChi2Var& other, const char* name) :
        RooAbsOptTestStatistic(other,name),
        _etype(other._etype),
        _funcMode(other._funcMode)
{
    /// Copy constructor
}

//=============================================================================
// Destructor
//=============================================================================
RooPearsonsChi2Var::~RooPearsonsChi2Var()
{}

//=============================================================================

Double_t RooPearsonsChi2Var::evaluatePartition(Int_t firstEvent,
        Int_t lastEvent,
        Int_t stepSize) const
{
    // Calculate chi^2 in partition from firstEvent to lastEvent using given stepSize
    Int_t i=0;
    Double_t result(0);

    // Determine normalization factor depending on type of input function
    Double_t normFactor(Function) ;
    switch (_funcMode)
    {
    case Function:
        normFactor=1 ;
        break ;
    case Pdf:
        normFactor = _dataClone->sumEntries() ;
        break ;
    case ExtendedPdf:
        normFactor = ((RooAbsPdf*)_funcClone)->expectedEvents(_dataClone->get()) ;
        break ;
    }


    // Loop over bins of dataset
    RooDataHist* hdata = (RooDataHist*) _dataClone ;
    for (i=firstEvent ; i<lastEvent ; i+=stepSize)
    {
        // get the data values for this event
        hdata->get(i);

        if (!hdata->valid())
        {
            continue ;
        }

        Double_t nData = hdata->weight() ;

        Double_t nPdf = _funcClone->getVal(_normSet) * normFactor * hdata->binVolume() ;

        Double_t eExt = nPdf-nData ;

        //    Double_t eIntLo,eIntHi ;
        //     hdata->weightError(eIntLo,eIntHi,_etype) ;
        //     Double_t eInt = (eExt>0) ? eIntHi : eIntLo ;


        // Skip cases where pdf=0 and there is no data
        if (nData==0. && nPdf==0)
        {
            continue ;
        }

        // Reject bins where nData=0
        if (nData==0.)
        {
            coutI(Eval) << "RooPearsonsChi2Var::RooPearsonsChi2Var(" << GetName()
            << ") : bin " << i
            << " has zero entries, but function is not zero (" << nPdf << "). "
            << "Will ignore this bin. " << endl ;
            continue;
        }

        ccoutD(Eval) << "PearsonsChi2Var[" << i << "]" << " nData = " << nData << " nPdf = " << nPdf << " errorExt = "
        << eExt << " errorInt = "  << " contrib = " << eExt*eExt/(nData) << endl ;

        result += eExt*eExt/(nData) ;
    }
    return result;
}
