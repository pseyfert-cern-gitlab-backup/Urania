// $Id: $
#ifndef CALIBDATASCRIPTS_LAM0FIT_MUONUNBIASED_H 
#define CALIBDATASCRIPTS_LAM0FIT_MUONUNBIASED_H 1

/*
 *  @author Juan Martin Otalora Goicochea
 *  @date   2012-09-26
 */

// Include files
#include <vector>
#include "Rtypes.h"
#include "RooPhysFitter/RooDMassFitter.h"

// forward declarations
class TChain;

// typedefs
typedef void (*fptr)(RooPhysFit::RooDMassFitter&, 
                     const char*,
                     const char*);

/** Perform an invariant mass fit to Lambda0 mass
    for Lam0->ppi events, and construct a
    signal sWeighted dataset.
    This function is used to create MuonUnBiased proton calibration
    samples.

    @param ch A pointer a TChain of Lam0->ppi events.
    @param charge A string indicating the track charge to fit 
    ("Positive" or "Negative").
    @param MomRange A string indicating the momentum range
    of the protons ("LoP": <40GeV/c, "HiP" >40GeV/c)
    @param pName The name of the track e.g. "P".
    @param wsName The name of the output RooWorkspace.
    @param fName The name of the output file.
    @param dsName The name to use for the (unweighted) RooDataSet.
    @param lam0Name The name to use for the Lambda0 mass RooRealVar.
    @param fun_vec A vector of functors used to set the spectator
    variables (variables used by PIDCalib that are not used in
    the mass fitting).
    @param index A string corresponding to the file index (default:
    "0").
    @param verbose A flag indicating whether the RooDMassFitter
    should print verbose information (default: false).
*/
void Lam0Fit_MuonUnBiased(TChain* ch, 
                          const char* charge,
                          const char* MomRange,
                          const char* pName,
                          const char* wsName,
                          const char* fName,
                          const char* dsName,
                          const char* lam0Name,
                          std::vector<fptr>& fun_vec,
                          const char* index="0",
                          Bool_t isVerbose=kFALSE);

#endif // CALIBDATASCRIPTS_LAM0FIT_MUONUNBIASED_H
