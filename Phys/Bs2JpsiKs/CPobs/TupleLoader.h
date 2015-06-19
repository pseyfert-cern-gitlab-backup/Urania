// #############################################################################
// Phys/Bs2JpsiKs Package
// Analyise Arguments, Name Files, Load NTuples
// Authors: Patrick Koppenburg & Kristof De Bruyn
// #############################################################################

#ifndef TupleLoader_h
#define TupleLoader_h

// #############################################################################
// *** Load Useful Classes ***
class IB2JpsiX;
class B2JpsiKs;
class TString;

// General C++
#include <iostream>
#include <stdlib.h>

// Root
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <TTree.h>

// Bs2JpsiKs Package
#include "IB2JpsiX.h"
#include "B2JpsiKs.h"


// #############################################################################
// *** Namespace ***
namespace ErrorCodes{
  enum EC {
    Error      = -33,
    FailsCuts  = -9, // Fails loose cuts
    KstarNet   = -8, // Eliminated by B->JpsiK* Neural Net
    UnbiasNet  = -7, // Eliminated by Unbiased Neural Net
    KilledMuCa = -6, // killed multiple B candidate
    KilledMuPV = -5  // killed multiple PV
  };
}


// #############################################################################
// *** Declarations ***

// Call Arguments
int decodeArgs(const int argc, char** const argv, TString& module,
               TString& data, TString& step, TString& dir, TString& decay,
               TString& weightMethod, bool& hasOpt);
void help(const TString module);

// Name Files
TString makeFileName(const TString module, const TString data,
                     const TString step, const TString dir,
                     const TString decay, const TString weightMethod);
TString mvaFileName(const TString decay, const TString step,
                    const unsigned int tracktype, const TString ext);

// Load NTuples
IB2JpsiX* loadTuple(const TString module, const TString data,
                    const TString step, const TString dir,
                    const TString decay, const TString weightMethod);
B2JpsiKs* loadB2JpsiKsTuple(const TString module, const TString data,
                            const TString step, const TString dir,
                            const TString decay, const TString weightMethod);
TChain* loadChain(const TString file1, const TString file2, const TString line,
                  const TString module, const TString data, const TString step,
                  const TString dir, const TString decay,
                  const TString weightMethod);
// Other
Long64_t printFrac(const Long64_t nentries);
#endif 
// #############################################################################
