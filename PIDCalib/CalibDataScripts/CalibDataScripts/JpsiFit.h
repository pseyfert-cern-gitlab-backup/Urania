// $Id: $
#ifndef CALIBDATASCRIPTS_JPSIFIT_H 
#define CALIBDATASCRIPTS_JPSIFIT_H 1

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

    @param ch A pointer a TChain of J/psi->mumu events.
    @param charge A string indicating the track charge to fit 
    ("Positive" or "Negative").
    @param pName The name of the probe muon e.g. "Mu0".
    @param otherPName The name of the tag muon e.g. "Mu1".
    @param wsName The name of the output RooWorkspace.
    @param fName The name of the output file.
    @param dsName The name to use for the (unweighted) RooDataSet.
    @param jpsiName The name to use for the J/psi mass RooRealVar.
    @param fun_vec A vector of functors used to set the spectator
    variables (variables used by PIDCalib that are not used in
    the mass fitting).
    @param index A string corresponding to the file index (default:
    "0").
    @param verbose A flag indicating whether the RooDMassFitter
    should print verbose information (default: false).
*/
void JpsiFit(TChain* ch, 
             const char* charge,
             const char* pName,
             const char* otherPName,
             const char* wsName,
             const char* fName,
             const char* dsName,
             const char* jpsiName,
             std::vector<fptr>& fun_vec,
             const char* index="0",
             Bool_t isVerbose=kFALSE);

#endif // CALIBDATASCRIPTS_JPSIFIT_H
