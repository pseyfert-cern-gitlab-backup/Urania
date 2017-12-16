// @(#)root/tmva $Id: TMVAClassification.C 38895 2011-04-18 11:59:54Z evt $
/**********************************************************************************
 * Project   : TMVA - a ROOT-integrated toolkit for multivariate data analysis    *
 * Package   : TMVA                                                               *
 * Root Macro: TMVAClassification                                                 *
 *                                                                                *
 * This macro provides examples for the training and testing of the               *
 * TMVA classifiers.                                                              *
 *                                                                                *
 * As input data is used a toy-MC sample consisting of four Gaussian-distributed  *
 * and linearly correlated input variables.                                       *
 *                                                                                *
 * The methods to be used can be switched on and off by means of booleans, or     *
 * via the prompt command, for example:                                           *
 *                                                                                *
 *    root -l ./TMVAClassification.C\(\"Fisher,Likelihood\"\)                     *
 *                                                                                *
 * (note that the backslashes are mandatory)                                      *
 * If no method given, a default set of classifiers is used.                      *
 *                                                                                *
 * The output file "TMVA.root" can be analysed with the use of dedicated          *
 * macros (simply say: root -l <macro.C>), which can be conveniently              *
 * invoked through a GUI that will appear at the end of the run of this macro.    *
 * Launch the GUI via the command:                                                *
 *                                                                                *
 *    root -l ./TMVAGui.C                                                         *
 *                                                                                *
 **********************************************************************************/

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include "TMath.h"

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"



int main(int argc, char** argv) {
  if (3!=argc) {
    std::cout << "USAGE newest <inname> <outname>" << std::endl;
    return 1;
  }

  {
    TTree* tree;
    TFile* ff = new TFile(argv[1],"read");
    std::map<std::string,int> done;
    for (int treeid = 0 ; treeid < ff->GetListOfKeys()->GetEntries() ; ++treeid) {
      done[ff->GetListOfKeys()->At(treeid)->GetName()] = 0;
    }
    ff->Close();
    delete ff;
    for (std::map<std::string,int>::iterator  it  = done.begin() ; it != done.end() ; ++it) {
      if (1==it->second) continue;
      TFile* ff = new TFile(argv[1],"read");
      ff->GetObject((((std::string)it->first).c_str()),tree);
      TFile* fout = new TFile(argv[2],"update");
      fout->WriteTObject(tree);
      fout->Close();
      delete fout;
      ff->Close();
      delete ff;
    }
  }

  std:: cout << " ============ GOOD BYE ==========" << std::endl;
  return 0;
}
