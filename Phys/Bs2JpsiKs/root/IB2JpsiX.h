// ####################################################################################################
// Phys/Bs2JpsiKs Package
// Base Class
// Authors: Patrick Koppenburg & Kristof De Bruyn
// ####################################################################################################

#ifndef IB2JPSIX_H 
#define IB2JPSIX_H 1

// ####################################################################################################
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

// ####################################################################################################
// *** Initialize Constants ***
// SETUP - Modify to your desires
static const bool twoNets = true; // Do you want to run coarse + fine neural net? Or everything in one go?
static const bool testrun = false ; // For testing/debugging
static const Long64_t maxEntries = 10;
// Training sample contains parts/frac of sample
static const double parts_in_teaching = 3;
static const double frac_in_teaching = 4;

// Supported Decays
static const TString m_B2JpsiKs = "B2JpsiKs" ;
static const TString m_B2JpsiPhi = "B2JpsiPhi" ;
static const TString m_Bu2JpsiK = "Bu2JpsiK" ;
static const TString m_Lb2JpsiL = "Lb2JpsiL" ;

// Supported Neural Net Settings
static const unsigned int m_NNtype_one = 1;
static const unsigned int m_NNtype_two = 2;
static const unsigned int m_NNtype_ANA = 0; 
static const double numberofseconds = 60. ;

// Supported Modules
static const TString m_slimtuple = "./slimtuple.exe"; 
static const TString m_weighting = "./weighting.exe"; 
static const TString m_teacher = "./teacher.exe"; 
static const TString m_expert = "./expert.exe"; 
static const TString m_branching = "./branching.exe"; 
static const TString m_branchingSim = "./branchingSim.exe"; 
static const TString m_lifetime = "lifetime"; // Call as extra option 'Tau' in ./branching.exe
static const TString m_systematics = "systematics"; // Call as extra option 'Syst' in ./branching.exe
static const TString m_punzi = "punzi"; // Call as extra option 'Punzi' in ./branching.exe
static const TString m_mod = "mod"; // Call as extra option 'Mod' in ./branching.exe
static const TString m_systematicsTau = "systtau"; // Call as extra option 'SystTau' in ./branching.exe

// Supported Directories
static const TString m_castor = "castor";
static const TString m_local = "local";

// Supported Weight Methods
static const TString m_downscaled = "downscaled";
static const TString m_random = "random";
static const TString m_weighted = "weighted";
static const TString m_noweight = "no-weight";

// Supported Track Types
static const unsigned int m_DD = 5;
static const unsigned int m_LL = 3;
static const unsigned int m_ANY = 0;

// Supported Data Types
static const TString m_2011 = "LHCb2011";
static const TString m_2012 = "LHCb2012";
static const TString m_2011LD = "LHCb2011LD";
static const TString m_2012LD = "LHCb2012LD";
static const TString m_2012_25 = "LHCb2012_25";
static const TString m_SigBd = "SigBd";
static const TString m_SigBs = "SigBs";
static const TString m_SigBdPrescaled = "SigBdPrescaled";
static const TString m_SigBsPrescaled = "SigBsPrescaled";
static const TString m_SigBu = "SigBu";
static const TString m_SigKstar = "SigKstar";
static const TString m_SigKstarWM = "SigKstarWM";
static const TString m_IncJpsi = "IncJpsi";
static const TString m_Prescaled = "Prescaled";
static const TString m_Test = "Test";
static bool isSigMC(TString what){
  return (what==m_SigBd || what==m_SigBs || what==m_SigBdPrescaled || what==m_SigBsPrescaled || 
          what==m_SigKstar || what==m_SigKstarWM);};

// Selection Cuts
static const double m_NNICut = 0 ; 
static const double taucut = 0.0002;
static const double m_OWNPVZ_range = 250 ; // cm
static const double m_Kplus = 493.677;
static const double m_Kzero = 497.614;
static const double KstarVeto = 20;
static const double m_JpsiPDG = 3096.916;
static const double m_BdPDG = 5279.58;
static const double m_BsPDG = 5366.77;
static const double m_JpsiFittedMass = 3099.0 ; // a bit on the high side
static const double clight = 299.792458; // mm/ns

// Mass Ranges
static const double BdBox_min = 5230 ; // does Bu as well
static const double BdBox_max = 5320 ; // does Bu as well
static const double BsBox_min = 5340 ; 
static const double BsBox_max = 5390 ; 

// Constants for Branching Ratio
static const double syst = 0.962353366404;
static const double esyst = 0.0527386727569;
static const double fsfd  = 0.267 ;
static const double fsfde = 0.021 ;
static const double jpk0bf  =  0.5*0.000871 ; // 8.71 +/- 0.32 10^-4   ! THIS IS K0
static const double jpk0bfe =  0.5*0.000032 ; // 8.71 10^-4
static const double fsBr = 0.0117 ; // Result of 0.41 fb-1 analysis


// Plotting Colours
static const unsigned int m_BsCol = 12;
static const unsigned int m_BdCol = 17;
static const unsigned int m_KstarCol = 14;

// ####################################################################################################
//
// Class Content
//
// ####################################################################################################
class IB2JpsiX {
public: 

// ####################################################################################################
// *** Declarations ***

  // Initialize
  virtual void defineConstants() = 0;

  // Accessors
  virtual double mass(unsigned int pv) = 0 ;
  virtual double massErr(unsigned int pv) = 0 ;
  virtual double time(unsigned int pv) = 0 ;
  virtual Double_t weightVal(unsigned int pv) = 0;
  virtual Float_t neuralnet(unsigned int pv) = 0;
  virtual UInt_t getRunNumber() = 0 ;
  virtual ULong64_t getEventNumber() = 0 ;
  virtual Float_t getGpsSecond() = 0  ;
  virtual Int_t TrackType() = 0 ;

  // Selection Cuts
  virtual bool applyDecayCuts(unsigned int pv,unsigned int ttype) = 0 ;
  virtual bool applyCommonCuts(TString what, unsigned int pv) = 0 ;  
  virtual bool trigger() = 0 ;
  virtual bool MCTruth(TString what) = 0 ;

  virtual bool teachingRegion(unsigned int pv) = 0 ;
  virtual bool noSigRegion(unsigned int pv) = 0 ;  

  // Mass regions
  virtual double sideband_low_min() = 0 ;
  virtual double sideband_high_min() = 0 ;
  virtual double sideband_high_max() = 0 ;

  // Teacher Interaction
  virtual Long64_t nEntries() = 0;
  virtual unsigned int nVar(TString decay, unsigned int NNtype, unsigned int ttype) = 0 ;
  virtual unsigned int individualPreproFlag(unsigned int i) = 0 ;
  virtual void prepareArray(const unsigned int nvar, float* InputArray, unsigned int pv, unsigned int ttype ) = 0;
  virtual void fillArray(const int var, const float value, TString name, float* InputArray) = 0;
  
  // Tree Interaction
  bool firstFill;
  virtual TTree* GetChain() = 0;
  virtual Int_t GetEntry(Long64_t entry) = 0;
  virtual void Init(TTree *tree, TString module, TString dir, TString what, unsigned int NNtype) = 0;
  virtual double DTFchi2(unsigned int pv) = 0;
  virtual bool getPsiHlt1TrackMuonDecision_TOS() = 0;
  virtual bool getPsiHlt1DiMuonHighMassDecision_TOS() = 0;
  virtual bool getPsiHlt1TrackAllL0Decision_TOS() = 0;
  virtual bool getPsiHlt2DiMuonDetachedJPsiDecision_TOS() = 0;
  virtual bool getPsiHlt2DiMuonJPsiHighPTDecision_TOS() = 0;
  virtual bool getPsiHlt2DiMuonJPsiDecision_TOS() = 0;
  virtual bool getPsiHlt2TopoMu2BodyBBDTDecision_TOS() = 0;
  virtual bool getPsiL0Global_Dec() = 0;
  virtual bool getPsiHlt1Global_Dec() = 0;
  virtual bool getPsiHlt2Global_Dec() = 0;
  virtual bool getPsiL0Global_TIS() = 0;
  virtual bool getPsiHlt1Global_TIS() = 0;
  virtual bool getPsiHlt2Global_TIS() = 0;
  virtual unsigned int primaries() = 0;
  
  // Best Primary Vertex
  virtual void printCandidates(std::list<unsigned int>& passPVs ) = 0 ;
  virtual void printCandidate(unsigned int ) = 0 ;

  
  // ####################################################################################################
  // *** Data Selection ***
  
  // Selection Cuts
  bool applyAllCuts(unsigned int NNtype,TString what, unsigned int pv, unsigned int ttype){
    if(m_NNtype_one==NNtype){
      if (m_2011==what || m_2012==what || m_Prescaled==what || what ==m_2011LD ||  what==m_2012LD 
          ||  what==m_2012_25  || what==m_Test ){
        return (applyDecayCuts(pv,ttype) && applyCommonCuts(what,pv) && trigger());
      }
      else if ((what==m_SigBd || what==m_SigBs || what==m_SigBdPrescaled || what==m_SigBsPrescaled || 
                what==m_SigKstar || what==m_SigKstarWM) || what==m_SigBu ){
        return (applyDecayCuts(pv,ttype) && applyCommonCuts(what,pv) && MCTruth(what));}
      else if (what==m_IncJpsi){ return (applyDecayCuts(pv,ttype) && applyCommonCuts(what,pv));}
      else {
        std::cout << "Unknown Sample Specification ``" << what << "''" << std::endl ;
        return false ;
      }
    }
    else {
      std::cout << "applyAllCuts should only be used with the first NN, you gave ``" << NNtype << "''" << std::endl ;
      return false ;
    }
  }
  
  // Training
  inline bool teacherSample(){
    return (getGpsSecond()>numberofseconds*(frac_in_teaching-parts_in_teaching)/frac_in_teaching);}
  inline bool expertSample(){return !teacherSample();}
 
 protected:
  
 private:

};
#endif // IB2JPSIX_H
