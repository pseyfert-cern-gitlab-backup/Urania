// #############################################################################
// Phys/Bs2JpsiKs Package
// Base Class
// Authors: Patrick Koppenburg & Kristof De Bruyn
// #############################################################################

#ifndef IB2JPSIX_H 
#define IB2JPSIX_H 1

// #############################################################################
// *** Load Useful Classes ***
#include <TROOT.h>
#include <TChain.h>
#include "TTree.h"
#include <TFile.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <iostream>
#include <TH2.h>
#include "cmath"
#include <list>
#include "TRandom2.h"

// #############################################################################
// *** Settings ***

// Testing
static const bool testrun = false; // For testing/debugging
static const Long64_t maxEntries = 10000;
static const int maxLeafs = 25;

// Training (sample will contain parts/frac of the events)
static const TString trainset = "Full"; // Options: 2011/2012/All/Full
static const double parts_in_teaching = 3;
static const double frac_in_teaching = 4;
// For comparing 2011 vs. 2012 vs. All use
// 2011 (3/4) - 2012 (3/8) - All (3/12)

// #############################################################################
// *** Initialize Constants ***

// Supported Modules (in run order)
static const TString m_slimtuple    = "./slimtuple.exe";
static const TString m_weighting    = "./weighting.exe";
static const TString m_teacher      = "./teacher.exe";
static const TString m_TMVA_teacher = "./TMVA_teacher.exe";
static const TString m_expert       = "./expert.exe";
static const TString m_TMVA_expert  = "./TMVA_expert.exe";
static const TString m_optimisation = "optimisationTag";

// Supported Data Types
static const TString m_LHCb2011          = "LHCb2011";
static const TString m_LHCb2011Prescaled = "LHCb2011Prescaled";
static const TString m_LHCb2012          = "LHCb2012";
static const TString m_LHCb2012Prescaled = "LHCb2012Prescaled";
static const TString m_LHCbAll           = "LHCbAll";
static const TString m_LHCbAllPrescaled  = "LHCbAllPrescaled";
static const TString m_SigBd             = "SigBd";
static const TString m_SigBdPrescaled    = "SigBdPrescaled";
static const TString m_SigBs             = "SigBs";
static const TString m_SigBsPrescaled    = "SigBsPrescaled";
static const TString m_SigKstar          = "SigKstar";
static const TString m_SigKstarWM        = "SigKstarWM";
static const TString m_IncJpsi           = "IncJpsi";

static bool isSigMC (TString data) {
  return (data==m_SigBd || data==m_SigBdPrescaled ||
          data==m_SigBs || data==m_SigBsPrescaled ||
          data==m_SigKstar || data==m_SigKstarWM);
};
static bool isLHCb (TString data) {
  return (data==m_LHCb2011 || data==m_LHCb2011Prescaled ||
          data==m_LHCb2012 || data==m_LHCb2012Prescaled ||
          data==m_LHCbAll || data==m_LHCbAllPrescaled);
};
static bool isPrescaled (TString data) {
  return (data==m_LHCb2011Prescaled || data==m_LHCb2012Prescaled ||
          data==m_LHCbAllPrescaled || data==m_IncJpsi ||
          data==m_SigBdPrescaled || data==m_SigBsPrescaled);
};

// Supported Steps in Selection
static const TString m_NNInitialise = "Initialise";
static const TString m_NNKstar      = "Kstar";
static const TString m_NNUnbiased   = "Unbiased";
static const TString m_NNSecond     = "Second";
static const TString m_NNAnalyse    = "Analyse";

// Supported Decays
static const TString m_B2JpsiKs = "B2JpsiKs";

// Supported Directories
static const TString m_castor = "castor";
static const TString m_local  = "local";

// Supported Weight Methods
static const TString m_downscaled = "downscaled";
static const TString m_random     = "random";
static const TString m_weighted   = "weighted";
static const TString m_noweight   = "no-weight";

// Supported Track Types
static const unsigned int m_ANY = 0;
static const unsigned int m_DD  = 5;
static const unsigned int m_LL  = 3;


// Constants
static const double m_Kplus = 493.677;
static const double m_Kzero = 497.614;
static const double m_JpsiPDG = 3096.916;
static const double m_JpsiFittedMass = 3099.0;
static const double m_BdPDG = 5279.58;
static const double m_BsPDG = 5366.77;
static const double numberofseconds = 60.;
static const double clight = 299.792458; // Units: mm/ns

// Selection Cuts
static const double tauErrcut = 0.2; // Units: ps
static const double taucut = 0.2; // Units: ps
static const double m_OWNPVZ_range = 250; // Units: cm
static const int ipcut_LL = 28;
static const int ipcut_DD = 44;

// Mass Ranges
static const double BdBox_min = 5230;
static const double BdBox_max = 5320;
static const double BsBox_min = 5340;
static const double BsBox_max = 5390;

// Plotting Colours
static const unsigned int m_BsCol = 12;
static const unsigned int m_BdCol = 14;
static const unsigned int m_KstarCol = 17;


// #############################################################################
//
// Class Content
//
// #############################################################################
class IB2JpsiX {
public: 

// #############################################################################
// *** Declarations ***

  // Initialize
  virtual void defineConstants(const TString step, const unsigned int track) = 0;
  virtual void Init(TTree *tree, const TString module, const TString data,
                    const TString step, const TString dir) = 0;
  
  // Accessors
  virtual double mass(const unsigned int pv) = 0;
  virtual double massErr(const unsigned int pv) = 0;
  virtual double time(const unsigned int pv) = 0;
  virtual double timeErr(const unsigned int pv) = 0;
  virtual double jpsiIPchi2(const unsigned int pv) = 0;
  virtual unsigned int primaries() = 0;
  virtual int TrackType() = 0;
  virtual UInt_t getRunNumber() = 0;
  virtual ULong64_t getEventNumber() = 0;
  virtual float getGpsSecond() = 0;
  virtual int getInputFile() = 0;
  virtual double weightVal(const unsigned int pv) = 0;
  virtual float neuralnet(const unsigned int pv) = 0;
  virtual int isUnbiased() = 0;
  virtual int nVar(const TString step, const unsigned int track) = 0;
  virtual Long64_t nEntries() = 0;

  // Selection Cuts
  virtual bool applyDecayCuts(const unsigned int pv) = 0;
  virtual bool applyCommonCuts(const TString data, const unsigned int pv) = 0;
  virtual bool fullTrigger() = 0;
  virtual bool unbiasedTrigger() = 0;
  virtual bool MCTruth(const TString data) = 0;

  virtual bool teachingRegion(const unsigned int pv) = 0;

  // Mass regions
  virtual double sideband_low_min() = 0;
  virtual double sideband_high_min() = 0;
  virtual double sideband_high_max(const TString data) = 0;

  // Teacher Interaction
  std::map<TString, int> *mvaVars;
  bool firstFill;
  virtual TTree* GetChain() = 0;
  virtual Int_t GetEntry(const Long64_t entry) = 0;
  virtual void prepareNBArray(float* InputArray, const unsigned int pv,
                              const TString step, const unsigned int tracktype) = 0;
  virtual void fillNBArray(const TString ID, const unsigned int pv,
                           float* InputArray) = 0;
  virtual void fillVar(const TString ID, const unsigned int pv,
                       TString& varName, float& varVal) = 0;
  virtual unsigned int individualPreproFlag(const unsigned int i,
                              const unsigned int track, const TString step) = 0;

  
// #############################################################################
// *** Data Selection ***
  
  // Selection Cuts
  bool applyAllCuts(const TString data, const unsigned int pv) {
    if (isLHCb(data)) {
      return (applyCommonCuts(data,pv) && applyDecayCuts(pv) && fullTrigger());
    } else if (isSigMC(data)) {
      return (applyCommonCuts(data,pv) && applyDecayCuts(pv) && MCTruth(data));
    } else if (data==m_IncJpsi) {
      return (applyCommonCuts(data,pv) && applyDecayCuts(pv));
    } else {
      std::cout << "ERROR: No Loose cuts defined for data sample "
                << data << std::endl;
      return false;
    }
  }
  
  // Training
  bool teacherSample() {
    return (getGpsSecond() > numberofseconds *
            (frac_in_teaching - parts_in_teaching)/frac_in_teaching);
  }
  bool expertSample() {
    return (!teacherSample());
  }
 
 protected:
  
 private:

};
#endif // IB2JPSIX_H
