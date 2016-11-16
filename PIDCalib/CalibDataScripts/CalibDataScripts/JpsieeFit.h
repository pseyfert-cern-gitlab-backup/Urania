// $Id: $
#ifndef CALIBDATASCRIPTS_JPSIEEFIT_H 
#define CALIBDATASCRIPTS_JPSIEEFIT_H 1

/*
 *  @author Thomas Bird
 *  @date   2014-02-07
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
    for J/psi->ee events, and construct a
    signal sWeighted dataset.
    This function is used to create electron calibration
    samples.

    @param ch A pointer a TChain of J/psi->ee events.
    @param charge A string indicating the track charge to fit 
    ("Positive" or "Negative").
    @param pName The name of the probe electron e.g. "e0".
    @param otherPName The name of the tag electron e.g. "e1".
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
void JpsieeFit(TChain* ch,
      const char* charge,
      int bremAdded,
      const char* pName,
      const char* otherPName,
      const char* wsName,
      const char* fName,
      const char* dsName,
      const char* jpsiName,
      std::vector<fptr>& fun_vec,
      const char* index,
      float &bkgSlope,
      Bool_t isVerbose=kFALSE,
      Bool_t exitOnBadFit=kTRUE
              );

#endif // CALIBDATASCRIPTS_JPSIEEFIT_H
