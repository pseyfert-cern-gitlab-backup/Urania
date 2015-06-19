// $Id: $
#ifndef CALIBDATASCRIPTS_DSTFIT_MUONUNBIASED_H 
#define CALIBDATASCRIPTS_DSTFIT_MUONUNBIASED_H 1

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

// Type Definitions
typedef void (*fptr)(RooPhysFit::RooDMassFitter&, 
                     const char*,
                     const char*);

/** Perform a 2D invariant mass fit to D0 mass and delta mass
    for "right-sign" D*->D0(Kpi)pi events, and construct a
    signal sWeighted dataset.
    This function is used to create MuonUnBiased kaon and pion
    calibration samples.

    @param ch A pointer a TChain of D*->D0(Kpi)pi events.
    @param charge A string indicating the track charge to fit 
    ("Positive" or "Negative").
    @param pName The name of the track e.g. "K" or "Pi".
    @param wsName The name of the output RooWorkspace.
    @param fName The name of the output file.
    @param dsName The name to use for the (unweighted) RooDataSet.
    @param d0Name The name to use for the D0 mass RooRealVar.
    @param delmName The name to use for the delta mass RooRealVar.
    @param fun_vec A vector of functors used to set the spectator
    variables (variables used by PIDCalib that are not used in
    the mass fitting).
    @param index A string corresponding to the file index (default:
    "0").
    @param verbose A flag indicating whether the RooDstD0MassFitter
    should print verbose information (default: false).
*/
void DStFit_MuonUnBiased(TChain* ch, 
                         const char* charge,
                         const char* pName,                         
                         const char* wsName,
                         const char* fName,
                         const char* dsName,
                         const char* d0Name,
                         const char* delmName,
                         std::vector<fptr>& fun_vec,
                         const char* index="0",
                         Bool_t verbose=kFALSE);

#endif // CALIBDATASCRIPTS_DSTFIT_MUONUNBIASED_H
