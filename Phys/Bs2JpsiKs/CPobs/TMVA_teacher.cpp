// #############################################################################
// Phys/Bs2JpsiKs Package
// Boosted Decsion Tree Teacher
// Authors: Patrick Koppenburg & Kristof De Bruyn
// #############################################################################

// #############################################################################
// *** Load Useful Classes ***
// General C++
#include <iostream>

// Root
#include <TChain.h>
#include <TFile.h>
#include <TString.h>

#include <TMVA/Config.h>
#include <TMVA/Factory.h>
#include <TMVA/MethodCuts.h>
#include <TMVA/Reader.h>
#include <TMVA/Tools.h>

// Bs2JpsiKs Package
#include "IB2JpsiX.h"
#include "TupleLoader.h"

using namespace std;

// #############################################################################
// *** Declarations ***
void fillBDTTeacher(const TString ID, IB2JpsiX* trainTuple,
                    TMVA::Factory *factory);

// #############################################################################
// *** Teacher ***
int runTeacher(const TString module, const TString data, const TString step,
               const TString dir, const TString decay,
               const TString weightMethod, const unsigned int tracktype,
               const TString BDTtraining) {

  // Guard Clause
  if (step==m_NNKstar && tracktype==5) {
    std::cout << "WARNING: Step " << m_NNKstar << " is for Long tracks only."
              << std::endl;
  }

// ***** PART 0: Initialise Data ***** //
/////////////////////////////////////////

  // *** Load Data ***
  IB2JpsiX* trainTuple = loadTuple(module, data, step, dir, decay, weightMethod);
  // Guard Clause
  if (!trainTuple) return -1;

// ***** PART I: Initialise TMVA ***** //
///////////////////////////////////////////////

  TString outfileName("TMVA.root");
  TFile *outputFile = TFile::Open(outfileName, "RECREATE");
  TMVA::Factory *factory = new TMVA::Factory("TMVA", outputFile,
    "V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification");

  // *** Array for TMVA ***
  trainTuple->defineConstants(step, tracktype);

  fillBDTTeacher("dtfc", trainTuple, factory);
  fillBDTTeacher("otcl", trainTuple, factory);
  fillBDTTeacher("prim", trainTuple, factory);
  fillBDTTeacher("spdm", trainTuple, factory);
  fillBDTTeacher("b0me", trainTuple, factory);
  fillBDTTeacher("b0pt", trainTuple, factory);
  fillBDTTeacher("bch2", trainTuple, factory);
  fillBDTTeacher("bmom", trainTuple, factory);
  fillBDTTeacher("dira", trainTuple, factory);
  fillBDTTeacher("jchi", trainTuple, factory);
  fillBDTTeacher("jipc", trainTuple, factory);
  fillBDTTeacher("jmas", trainTuple, factory);
  fillBDTTeacher("jmme", trainTuple, factory);
  fillBDTTeacher("jmom", trainTuple, factory);
  fillBDTTeacher("jppt", trainTuple, factory);
  fillBDTTeacher("kipc", trainTuple, factory);
  fillBDTTeacher("ksch", trainTuple, factory);
  fillBDTTeacher("ksez", trainTuple, factory);
  fillBDTTeacher("ksfd", trainTuple, factory);
  fillBDTTeacher("ksme", trainTuple, factory);
  fillBDTTeacher("ksmm", trainTuple, factory);
  fillBDTTeacher("ksmo", trainTuple, factory);
  fillBDTTeacher("kspt", trainTuple, factory);
  fillBDTTeacher("ksta", trainTuple, factory);
  fillBDTTeacher("muic", trainTuple, factory);
  fillBDTTeacher("muid", trainTuple, factory);
  fillBDTTeacher("muip", trainTuple, factory);
  fillBDTTeacher("mumo", trainTuple, factory);
  fillBDTTeacher("mupt", trainTuple, factory);
  fillBDTTeacher("mutk", trainTuple, factory);
  fillBDTTeacher("pidk", trainTuple, factory);
  fillBDTTeacher("pigp", trainTuple, factory);
  fillBDTTeacher("piic", trainTuple, factory);
  fillBDTTeacher("piip", trainTuple, factory);
  fillBDTTeacher("pimo", trainTuple, factory);
  fillBDTTeacher("pipt", trainTuple, factory);
  fillBDTTeacher("pitk", trainTuple, factory);

  // *** Assign Targets ***
  Double_t weight = 1.0;
  factory->AddSignalTree(trainTuple->GetChain(), weight);
  factory->AddBackgroundTree(trainTuple->GetChain(), weight);

  // *** Assign sWeights
  factory->SetSignalWeightExpression("sweight[0]");
  factory->SetBackgroundWeightExpression("1-sweight[0]");
  
  // *** Prepare Training ***
  TString trackString = (tracktype==3 ? "3" : "5");
  TString trackName = (tracktype==3 ? "LL" : "DD");
  // Loose Cuts
  TString cutString = "piplus_TRACK_Type==" + trackString + " && sweight[0]>-3";
  // Exclude Bs from Training
  char buffer[100];
  std::sprintf(buffer,
    " && (B0_FitDaughtersPVConst_M[0]<%f || B0_FitDaughtersPVConst_M[0]>%f)",
    BsBox_min, BsBox_max);
  // Training fraction
  TString trainFrac = " && BCID%60>15"; // Replace with GpsSecond
  // Extra regularisation Cuts
  TString regCuts = " && B0_FitPVConst_KS0_MERR[0]>0 && B0_FitPVConst_KS0_MERR[0]<50 && B0_FitPVConst_J_psi_1S_MERR[0]<50";
  // Compose
  cutString.Append(buffer);
  cutString.Append(trainFrac);
  cutString.Append(regCuts);

  TCut mycuts = (TCut) cutString;
  factory->PrepareTrainingAndTestTree(mycuts,
    "!V:SplitMode=Random:SplitSeed=123:NormMode=None" );

  // ***** Setup Training ***** //
  ////////////////////////////////

  // Default setup
  TString defSetup = "!H:!V:NTrees=850:nEventsMin=150:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex";
  if (BDTtraining=="Def_Dep3" || BDTtraining=="All") {
    factory->BookMethod (TMVA::Types::kBDT, "BDT_Def_Dep3_"+trackName,
      ""+defSetup+":MaxDepth=3:nCuts=20:VarTransform=None:PruneMethod=NoPruning");
  }
  // Gaussian-ate variables
  if (BDTtraining=="Gau_Dep3" || BDTtraining=="All") {
    factory->BookMethod (TMVA::Types::kBDT, "BDT_Gau_Dep3_"+trackName,
      ""+defSetup+":MaxDepth=3:nCuts=20:VarTransform=Gauss:PruneMethod=NoPruning");
  }
  // Decorrelate variables
  if (BDTtraining=="Dec_Dep3" || BDTtraining=="All") {
    factory->BookMethod (TMVA::Types::kBDT, "BDT_Dec_Dep3_"+trackName,
      ""+defSetup+":MaxDepth=3:nCuts=20:VarTransform=G,D,G:PruneMethod=NoPruning");
  }
  // Decorrelate variables + extra depth
  if (BDTtraining=="Dec_Dep5" || BDTtraining=="All") {
    factory->BookMethod (TMVA::Types::kBDT, "BDT_Dec_Dep5_"+trackName,
      ""+defSetup+":MaxDepth=5:nCuts=20:VarTransform=G,D,G:PruneMethod=NoPruning");
  }
  // Decorrelate variables + extra steps in Node cut optimisation
  if (BDTtraining=="Dec_Dep3_Cuts50" || BDTtraining=="All") {
    factory->BookMethod (TMVA::Types::kBDT, "BDT_Dec_Dep3_Cuts50_"+trackName,
      ""+defSetup+":MaxDepth=3:nCuts=50:VarTransform=G,D,G:PruneMethod=NoPruning");
  }
  // Decorrelate variables + pruning
  if (BDTtraining=="Dec_Dep3_Prune" || BDTtraining=="All") {
    factory->BookMethod( TMVA::Types::kBDT, "BDT_Dec_Dep3_Prune_"+trackName,
      ""+defSetup+":MaxDepth=3:nCuts=20:VarTransform=G,D,G:PruneMethod=CostComplexity:PruneStrength=-1");
  }
  // ***** Run ***** //
  /////////////////////

  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();

  // ***** Finalise ***** //
  //////////////////////////

  outputFile->Close();

  // Clean up
  delete factory;

}

// #############################################################################
void fillBDTTeacher(const TString ID, IB2JpsiX* trainTuple,
                    TMVA::Factory *factory) {
  int varID = (trainTuple->mvaVars->find(ID)->second);
  if (varID>=0) {
    TString name = "";
    float value = -999.;
    trainTuple->fillVar(ID, 0, name, value);
    factory->AddVariable(name, 'F');
  }
}

// #############################################################################
// *** Main ***
int main(int argc, char** argv) {

  // *** Decode Arguments ***
  TString module, data, step, dir, decay, weightMethod;
  bool hasOpt;
  int out = decodeArgs(argc, argv,
                       module, data, step, dir, decay, weightMethod, hasOpt);
  if (out!=0) return out;

  // Extra argument
  unsigned int tracktype = 0;
  TString BDTtraining = "Def_Dep3";
  if (hasOpt) {
      tracktype = (argc>3 ? (double) atoi(argv[3]) : 3);
    BDTtraining = (argc>4 ? argv[4] : "Def_Dep3");
    std::cout << "Extra Arguments for " << module << std::endl;
    std::cout << "  Track Type: " << tracktype << std::endl;
    std::cout << "    Training: " << BDTtraining << std::endl;
    std::cout << "########################################" << std::endl;
  }
  if (tracktype==0) {
    std::cout << "ERROR: Did not specify which set to train:"
              << " long or downstream Ks sample." << std::endl;
    return -1;
  }

  // *** Main Function ***
  return runTeacher(module, data, step, dir, decay, weightMethod,
                    tracktype, BDTtraining);
}

// #############################################################################