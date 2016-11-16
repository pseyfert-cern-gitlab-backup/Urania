// $Id: $
#ifndef CALIBDATASCRIPTS_INCLCFIT_H 
#define CALIBDATASCRIPTS_INCLCFIT_H 1

/*
 *  @author Juan Martin Otalora Goicochea
 *  @date   2012-09-26
 */

// Include file
#include <vector>
#include "Rtypes.h"
#include "RooPhysFitter/RooDMassFitter.h"

// forward declarations
class TChain;

// typedefs
typedef void (*fptr)(RooPhysFit::RooDMassFitter&, 
                     const char*,
                     const char*);

/** Perform an invariant mass fit to J/psi mass
    for J/psi->mumu events, and construct a
    signal sWeighted dataset.
    This function is used to create muon calibration
    samples.

And now is rehashed to make LC fits for protons

    @param ch A pointer a TChain of Lc -> pkpi events.
    @param charge A string indicating the track charge to fit 
    ("Positive" or "Negative").
    @param pName The name of the probe proton.

    @param wsName The name of the output RooWorkspace.
    @param fName The name of the output file.
    @param dsName The name to use for the (unweighted) RooDataSet.
    @param IncLcName The name to use for the Lc mass RooRealVar.
    @param fun_vec A vector of functors used to set the spectator
    variables (variables used by PIDCalib that are not used in
    the mass fitting).
    @param index A string corresponding to the file index (default:
    "0").
    @param verbose A flag indicating whether the RooDMassFitter
    should print verbose information (default: false).
*/
void IncLcFit(TChain* ch, 
             const char* charge,
             const char* pName,
             const char* wsName,
             const char* fName,
             const char* dsName,
             const char* IncLcName,
             std::vector<fptr>& fun_vec,
             const char* index="0",
             Bool_t isVerbose=kFALSE);

#endif // CALIBDATASCRIPTS_INCLCFIT_H
