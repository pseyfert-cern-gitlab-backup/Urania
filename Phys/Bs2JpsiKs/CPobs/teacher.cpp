// #############################################################################
// Phys/Bs2JpsiKs Package
// Neural Net Teacher
// Authors: Patrick Koppenburg & Kristof De Bruyn
// #############################################################################

// #############################################################################
// *** Load Useful Classes ***
// General C++
#include <iostream>
#include <string>

// Root
#include <TString.h>

// Bs2JpsiKs Package
#include "IB2JpsiX.h"
#include "TupleLoader.h"

// NeuroBayes
#include <NeuroBayesTeacher.hh>

using namespace std;

// #############################################################################
// *** Declarations ***
void analysis(string FileName = "teacherHistos.root",
              const char* PSFileName = "analysis.ps", int sort = 0, 
              const char* correlSigniFile = "correl_signi.txt");

int trainOnce(const TString module, const TString data, const TString step,
              const TString dir, const TString decay,
              const TString weightMethod, const unsigned int tracktype,
              const int prepFlag);
int runTeacher(const TString module, const TString data, const TString step,
               const TString dir, const TString decay,
               const TString weightMethod, const unsigned int tracktype,
               const int prepFlag);
int prepareTrainingSample(IB2JpsiX* trainTuple, NeuroBayesTeacher* nb,
                          const TString step, const unsigned int tracktype,
                          const unsigned int target);

// #############################################################################
// *** Teacher ***
int runTeacher(const TString module, const TString data, const TString step,
               const TString dir, const TString decay,
               const TString weightMethod,
               const unsigned int tracktype, const int prepFlag) {

  // Guard Clause
  if (step==m_NNKstar && tracktype==5) {
    std::cout << "WARNING: Step " << m_NNKstar << " is for Long tracks only."
              << std::endl;
  }

// ***** PART 0: Initialise Data ***** //
/////////////////////////////////////////

  // *** Load Data ***
  IB2JpsiX* trainTuple = loadTuple(module, (step==m_NNKstar ? "SigBd" : data),
                                   step, dir, decay, weightMethod);
  // Guard Clause
  if (!trainTuple) return -1;

// ***** PART I: Initialise NeuroBayes ***** //
///////////////////////////////////////////////
  
  std::cout << "\n PROGRESS: Initialising NeuroBayes Teacher \n" << std::endl;

  // *** NeuroBayes ***
  // NOTE: Teacher must run on lxplus! (due to Licence)
  // Initialise
  std::cout << "TEACH: Creating new Instance: "
            << " NeuroBayes is an Singleton" << std::endl;
  NeuroBayesTeacher* nb = NeuroBayesTeacher::Instance();

  // Output: expertise file
  TString trainingFile = mvaFileName(decay, step, tracktype, "nb");
  std::cout << "TEACH: Will put the training in " << trainingFile << std::endl;
  nb->SetOutputFile(trainingFile);

  // *** Settings ***
  unsigned int nvar = trainTuple->nVar(step, tracktype);
  unsigned int nhidden = nvar;
  if (step==m_NNUnbiased) {
    if (TMath::Abs(prepFlag)==1012) {
      nhidden = (tracktype==m_LL ? 17 : 28);
    } else if (TMath::Abs(prepFlag)==1022) {
      nhidden = (tracktype==m_LL ? 37 : 40);
    } else if (TMath::Abs(prepFlag)==612) {
      if (trainset!="Full") {
        nhidden = (tracktype==m_LL ? 18 : 32);
      } else {
        nhidden = (tracktype==m_LL ? 21 : 32);
      }
    } else if (TMath::Abs(prepFlag)==212) {
      nhidden = (tracktype==m_LL ? 29 : 34);
    }
  } else if (step==m_NNKstar) {
    if (TMath::Abs(prepFlag)==1012) {
      nhidden = 7;
    } else if (TMath::Abs(prepFlag)==622) {
      nhidden = 14;
    } else if (TMath::Abs(prepFlag)==612) {
      nhidden = 7;
    } else if (TMath::Abs(prepFlag)==212) {
      nhidden = 11;
    }
  }

  // Task
  nb->NB_DEF_TASK("CLA");     // Classification
  // NeuroBayes topology
  nb->NB_DEF_NODE1(nvar+1);   // Nodes in input layer  (Def: # used var + 1)
  nb->NB_DEF_NODE2(nhidden);  // Nodes in hidden layer (Def: # used var)
  nb->NB_DEF_NODE3(1);        // Nodes in output layer (Def: 1)
  // Setup
  // ... setting does not work with sPlot
  //if (step==m_NNKstar || (step==m_NNUnbiased && prepFlag==1022)) {
  if (step==m_NNKstar) {
    nb->NB_DEF_SHAPE("DIAG"); // Force training to diagonal
  }
  nb->NB_DEF_REG("ALL");      // Regularisation (prevent overfitting to example)
  nb->NB_DEF_LOSS("ENTROPY"); // Type of Loss function: ENTROPY or QUADRATIC
  nb->NB_DEF_ITER(1000);      // Number of training iteration
  nb->NB_DEF_METHOD("BFGS");  // Use BFGS algorith for optimisation
  nb->NB_DEF_LEARNDIAG(1);
  if (prepFlag>0) {
    nb->NB_DEF_MOM(0.5);      // Boost: Helps NB out of local minima
  }
  // General preprocessing
  nb->NB_DEF_PRE(TMath::Abs(prepFlag));

  // Individual preprocessing flags
  for (unsigned int i = 0; i!=nvar; i++) {
    nb->SetIndividualPreproFlag(i,
        trainTuple->individualPreproFlag(i,tracktype, step));
  }

  // *** Load Training Array ***
  prepareTrainingSample(trainTuple, nb, step, tracktype, 1);

  // Also load "background" for training on Simulation
  if (step==m_NNKstar) {
    trainTuple = loadTuple(module, "SigKstar", step, dir, decay, weightMethod);
    prepareTrainingSample(trainTuple, nb, step, tracktype, 0);
  }

// ***** PART II: Train NeuroBayes ***** //
///////////////////////////////////////////
  
  std::cout << "\n PROGRESS: Training NeuroBayes Teacher \n" << std::endl;
  nb->TrainNet();
  std::cout << "\n PROGRESS: Teaching Finished! \n" << std::endl;
  return 0;
}

// #############################################################################
// *** Fill Array ***
int prepareTrainingSample(IB2JpsiX* trainTuple, NeuroBayesTeacher* nb,
                          const TString step, const unsigned int tracktype,
                          const unsigned int target) {
  std::cout << "\n PROGRESS: Feeding examples to Teacher \n" << std::endl;

  // *** Initialise ***
  unsigned int nvar = trainTuple->nVar(step, tracktype);
  float* InputArray = new float[nvar];
  trainTuple->firstFill = true;
  
  Double_t sweight = -999;
  //Int_t unbiased = 0;
  bool inset = false;
  Long64_t trainLimit = (tracktype==m_LL ? 23000 : 81000);
  
  Long64_t nentries = trainTuple->nEntries();
  Long64_t printMod = printFrac(nentries);
  Long64_t nFailed = 0;
  Long64_t nKillMuCa = 0;
  Long64_t nKillMuPV = 0;
  Long64_t nGood = 0;
  Long64_t nTeach = 0;
  Long64_t nNonTeach = 0;

  std::cout << "TEACH: Will loop over " << nentries << " entries." << std::endl;
  for (Long64_t i=0; i<nentries; i++) {
    trainTuple->GetChain()->GetEntry(i);
    
    // Progress
    if (i%printMod==0) {
      std::cout << " |-> " << i << " / " << nentries
                << " (" << 100*i/nentries << "%)" << std::endl;
    }

    inset = (trainset=="Full" || (nTeach<trainLimit && (trainset=="All" ||
            (trainset=="2011" && trainTuple->getInputFile()==0) ||
            (trainset=="2012" && trainTuple->getInputFile()==1))));
    if (!inset) continue;

    // Get Data
    unsigned int npv = trainTuple->primaries();
    for (unsigned int pv=0; pv!=npv; pv++) {
      sweight = trainTuple->weightVal(pv);
      //unbiased = (step==m_NNUnbiased ? trainTuple->isUnbiased() : 1);
      // For training on subsamples
      // Select Teaching Sample
      if (sweight<=-7 || trainTuple->TrackType()!=tracktype) { 
        nFailed++;
        continue;
      } else if (sweight==ErrorCodes::KilledMuCa) {
        nKillMuCa++;
        continue;
      } else if (sweight==ErrorCodes::KilledMuPV) {
        nKillMuPV++;
        continue;
      } else if (sweight>=-1) {
        nGood++;
        if ((trainTuple->teacherSample() && trainTuple->teachingRegion(pv)) ||
            step==m_NNKstar) {
          nTeach++;

          // Feed Teacher
          trainTuple->prepareNBArray(InputArray, pv, step, tracktype);
          nb->SetTarget((step==m_NNKstar ? target : sweight));
          nb->SetNextInput(nvar, InputArray);
        } else {
          nNonTeach++;
          continue;
        }
      } else {
        // Error Handling
        std::cout << "WARNING: read sweight " << sweight
                  << " Will treat it as Failed Cuts." << std::endl;
        nFailed++;
      }
    } // End of pv-loop
  }

  // *** Results ***
  std::cout << "########################################" << std::endl;
  std::cout << "  RESULTS" << std::endl;
  std::cout << "  # Events failing previous cuts: " << nFailed   << std::endl;
  std::cout << "  # Multiple Candidates Killed  : " << nKillMuCa << std::endl;
  std::cout << "  # Multiple (B,PV) pairs Killed: " << nKillMuPV << std::endl;
  std::cout << "  # Good training candidates    : " << nGood     << std::endl;
  std::cout << "########################################" << std::endl;
  std::cout << "  # Events excluded from training: " << nNonTeach << std::endl;
  std::cout << "  # Events used for training     : " << nTeach    << std::endl;
  std::cout << "########################################" << std::endl;
}

// #############################################################################
// *** Training Procedure ***
int trainOnce(const TString module, const TString data, const TString step,
              const TString dir, const TString decay,
              const TString weightMethod, const unsigned int tracktype,
              const int prepFlag) {

  // *** Teach ***
  int out = runTeacher(module, data, step, dir, decay, weightMethod,
                       tracktype, prepFlag);
  // Error Analysis
  if (out!=0) return out;

  // *** Process Results ***
  std::cout << "\n PROGRESS: Processing Results \n" << std::endl;

  TString pdfString = mvaFileName(decay, step, tracktype, "pdf");
  analysis("ahist.txt", pdfString);
  
  std::cout << "\n PROGRESS: Finished! \n" << std::endl;
  return 0;
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
  int prepFlag = 1012;
  if (hasOpt) {
    tracktype = (argc>3 ? atoi(argv[3]) : 3);
    prepFlag  = (argc>4 ? atoi(argv[4]) : 1012);
    std::cout << "Extra Arguments for " << module << std::endl;
    std::cout << "          Track Type: " << tracktype << std::endl;
    std::cout << "  Preprocessing Flag: " << TMath::Abs(prepFlag)  << std::endl;
    std::cout << "      Momentum boost: " <<
                                         (prepFlag>0 ? "0.5" : "No") << std::endl;
    std::cout << "########################################" << std::endl;
  }
  if (tracktype==0) {
    std::cout << "ERROR: Did not specify which set to train:"
              << " long or downstream Ks sample." << std::endl;
    return -1;
  }

  // *** Main Function ***
  // NeuroBayes is a singleton, so it's difficult to run it twice in the same
  // piece of code + not convenient for tuning
  return trainOnce(module, data, step, dir, decay, weightMethod, tracktype,
                   prepFlag);
}

// #############################################################################