// ####################################################################################################
// Phys/Bs2JpsiKs Package
// Analyise Arguments, Name Files, Load NTuples
// Authors: Patrick Koppenburg & Kristof De Bruyn
// ####################################################################################################

#ifndef TupleLoader_h
#define TupleLoader_h

// ####################################################################################################
// *** Load Useful Classes ***
class TString ;
#include "IB2JpsiX.h"
#include "B2JpsiKs_2011.h"
#include "Bu2JpsiK_2011.h"
#include "B2JpsiPhi_2011.h"
#include "Lb2JpsiL_2012.h"
#include "TFriendElement.h"
#include "TString.h"
#include "TParameter.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
// Namespace
namespace ErrorCodes{
  enum EC{ Error = -33 ,
           FailsCuts = -9 ,
           KilledMuCa = -8, // killed multiple B candidate
           KilledMuPV = -7, // killed multiple PV
           DiffTrack = -6 // different track type
         };
}


// ####################################################################################################
// *** Declarations ***

// Analyse Arguments
int decodeArgs(TString& module, TString& decay, unsigned int& NNtype, TString& dir, TString& weightMethod,
               unsigned int& ttype,TString& what,int argc, char** argv);

// Name Files
TString makeFileName(TString module, TString decay, unsigned int  NNType, TString weightMethod, 
                     TString what, int ttype, TString dir);
void expertiseFile(char* ExpertiseFile, TString decay, unsigned int ttype, unsigned int NNtype);

// Load NTuples
IB2JpsiX* loadTuple(TString module, TString decay, TString dir, TString what,
                    unsigned int NNtype, TString weightMethod, unsigned int ttype);
B2JpsiKs_2011* loadB2JpsiKsTuple(TString module, TString decay, TString dir, TString what,
                                 unsigned int NNtype,TString weightMethod, unsigned int ttype);
B2JpsiPhi_2011* loadB2JpsiPhiTuple(TString module, TString decay, TString dir, TString what, 
                                   unsigned int NNtype, TString weightMethod, unsigned int ttype);
Bu2JpsiK_2011* loadBu2JpsiKTuple(TString module, TString decay, TString dir, TString what,
                                 unsigned int NNtype, TString weightMethod, unsigned int ttype);
Lb2JpsiL_2012* loadLb2JpsiLTuple(TString module, TString decay, TString dir, TString what,
                                 unsigned int NNtype, TString weightMethod, unsigned int ttype);
TChain* loadChain(TString file1, TString file2, TString line,
                  TString module, TString decay, TString dir, TString what,
                  unsigned int NNtype, TString weightMethod, unsigned int ttype);
void help(std::string);
double printFrac(Long64_t n) ;
#endif 
// ####################################################################################################
