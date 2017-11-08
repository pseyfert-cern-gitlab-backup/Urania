#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooStats/SPlot.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooCBShape.h"
#include "RooArgusBG.h"
#include "RooGaussian.h"
#include "RooPolynomial.h"
#include "RooExponential.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooAddition.h"
#include "RooProduct.h"
#include "TCanvas.h"
#include "RooAbsPdf.h"
#include "RooFit.h"
#include "RooFitResult.h"
#include "RooWorkspace.h"
#include "RooConstVar.h"
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TCut.h"
#include "SemiDec.h"
#include "TLorentzVector.h"
#include "TVector3.h" 

// #################
// ##### INFO ######  
// This code does the splots of the Ds*gamma mass to make the fit of the exclusive R(Ds*)
// ################# 

// use this order for safety on library loading
using namespace RooFit ;
using namespace RooStats ;

// see below for implementation
void AddModel(RooWorkspace*, float, TString);
void AddData(RooWorkspace*, float, TString, TString);
void DoSPlot(RooWorkspace*, float, TString, TString);
void MakePlots(RooWorkspace*, TString, TString);
void ComputeBMom2Fold(Double_t, TLorentzVector, TVector3, Double_t &, Double_t &, Double_t &);
//double hel(TLorentzVector, TLorentzVector, TLorentzVector, TLorentzVector);
float getEntries(TString);

void splotDs0(TString resonance, TString sample){

  // Create a new workspace to manage the project.
  RooWorkspace* wspace = new RooWorkspace("myWS");

  // add the signal and background models to the workspace.
  // Inside this function you will find a discription our model.
  float nentries = getEntries(sample); 
  //float nentries = 100000;
  AddModel(wspace, nentries, resonance);

  // add data to the workspace
  AddData(wspace, nentries, resonance, sample);

  // inspect the workspace if you wish
  wspace->Print();

  // do sPlot.  
  // This wil make a new dataset with sWeights added for every event.
  DoSPlot(wspace, nentries, resonance, sample);

  // Make some plots showing the discriminating variable and 
  // the control variable after unfolding.
  MakePlots(wspace, resonance, sample);

  // cleanup
  delete wspace;

}

//____________________________________
void AddModel(RooWorkspace* ws, float nentries, TString resonance){

  // Make models for signal and background 

  Double_t lowRange, highRange, massLow, massHigh, massCentral;
  // set range of observable
  if(resonance == "Dsst"){
    massLow = 2109.1;
    massHigh = 2115.1;
    massCentral = 2112.1;
    lowRange = 2050.;
    highRange = 2220.;
  }
  if(resonance == "Ds0"){
    massLow = 2312.7;
    massHigh = 2322.7;
    massCentral = 2317.7;
    lowRange = 2050.;
    highRange = 2600.;
  }

  // make a RooRealVar for the observables
  RooRealVar invMass("resMass", "resMass", lowRange, highRange,"MeV");
 
  /////////////////////////////////////////////
  // make 1-d model for signal including the invariant mass 
  std::cout << "make signal model" << std::endl;
  // mass model for signal Gaussian
  RooRealVar mean("mean", "signal mass", massCentral, massLow, massHigh);
  RooRealVar sigma("sigma", "Width of signal", 10.0, 5.0, 15.0);
  RooRealVar alpha1("alpha1", "alpha1", 0.8, 0., 3.0);
  RooRealVar alpha2("alpha2", "alpha2", -0.8, -1.5, 0.);
  RooRealVar n1 = RooRealVar("n1", "n1", 10., 0.2, 60.);
  RooRealVar n2 = RooRealVar("n2", "n2", 10., 1.2, 60.);
  RooCBShape *sig1 = new RooCBShape("sig1", "signal CB", invMass, mean, sigma, alpha1, n1);
  RooCBShape *sig2 = new RooCBShape("sig2", "signal CB", invMass, mean, sigma, alpha2, n2);
  RooRealVar frac = RooRealVar("frac","frac",0.5,0.,1.);
  RooCBShape *SigModel = new RooCBShape("sig", "signal CB", invMass, mean, sigma, alpha2, n2);

  // make background model for 0.4 apperture
  
  std::cout << "make background model" << std::endl;
  RooRealVar a1("a1","a1",0.3,-1,1) ;
  RooRealVar a2("a2","a2",-0.1,-1,1) ;
  RooRealVar a3("a3","a3",-0.01,-1,1) ;
  RooChebychev *BkgModel = new RooChebychev("bkg","background", invMass, RooArgSet(a1,a2,a3));
/*
  RooRealVar c = RooRealVar("c", "c", -0.0006, -0.01, 0.);
  RooExponential *BkgModel = new RooExponential("bkg", "exponential 1", invMass, c);
  RooRealVar *thMass;
  if(resonance == "Dsst"){
    thMass = new RooRealVar("thMass", "thMass", 2000, 1900, 2150, "MeV/c^{2}");
  }
  if(resonance == "Ds0"){
    thMass = new RooRealVar("thMass", "thMass", 2190, 2100, 2220, "MeV/c^{2}");
  }
  RooRealVar thSigma = RooRealVar("thSigma", "thSigma", 80, 10, 120, "MeV/c^{2}");
  RooFormulaVar *thres = new RooFormulaVar("eff","0.5*(TMath::Erf((resMass-thMass)/thSigma)+1)",RooArgList(invMass,*thMass,thSigma)) ;
*/
  //RooEffProd *BkgModel = new RooEffProd("bkg", "background", *expo, *thres);
 
  /* 
  // make background model for 1.0 apperture
  std::cout << "make background model" << std::endl;
  RooRealVar a1 = RooRealVar("a1", "a1", -1.0, -100.0, 100.0);
  RooRealVar a2 = RooRealVar("a2", "a2", -1.0, -100.0, 100.0);
  RooPolynomial *BkgModel = new RooPolynomial("bkg", "polynomial 1", invMass, RooArgList(a1, a2));
  */
  //////////////////////////////////////////////
  // combined model
  // These variables represent the number of signal or background events
  // They will be fitted.
  RooRealVar SigYield("SigYield","fitted yield for Signal", nentries*0.2, 0., 0.4*nentries) ; 
  RooRealVar BkgYield("BkgYield","fitted yield for Background", nentries*0.8, 0., 0.6*nentries) ; 
  SigYield.setError(sqrt(nentries));
  BkgYield.setError(sqrt(nentries));

  // now make the combined model
  std::cout << "make full model" << std::endl;
  RooAddPdf model("model","signal+background models", RooArgList(*SigModel,*BkgModel), RooArgList(SigYield,BkgYield));

  // interesting for debugging and visualizing the model
  model.graphVizTree("fullModel.dot");

  std::cout << "import model" << std::endl;
  ws->import(model);

  delete SigModel;
  delete BkgModel; 
}

//____________________________________
void AddData(RooWorkspace* ws, float nentries, TString resonance, TString sample){
  // Add data from nutples
  
  TChain *fChain; 
  // use the ntuples that are cleaned in Ds
  if (sample == "data"){ 
    fChain = new TChain("B2DsMuNuTuple/DecayTree");
    fChain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/s/sogilvy/RDs/WithVetoes/TupleRDS_DataDown_allNeutrals_iso.root");
    fChain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/s/sogilvy/RDs/WithVetoes/TupleRDS_DataUp_allNeutrals_iso.root");
  } else if (sample == "SS"){
    fChain = new TChain("B2DsMuNuSSTuple/DecayTree");
    fChain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/s/sogilvy/RDs/WithVetoes/TupleRDS_DataDown_allNeutrals_iso.root");
    fChain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/s/sogilvy/RDs/WithVetoes/TupleRDS_DataUp_allNeutrals_iso.root");  
  } else if (sample == "BdDD"){
    fChain = new TChain("B2DsMuNuTuple/DecayTree");    
    fChain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/WithVetoes/TupleRDS_Sim09b_BdDstDs.root");
  } else if (sample == "BuDD"){
    fChain = new TChain("B2DsMuNuTuple/DecayTree");
    fChain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/WithVetoes/TupleRDS_Sim09b_BuD0Ds.root");
  } else if (sample == "BsDD"){
    fChain = new TChain("B2DsMuNuTuple/DecayTree");
    fChain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/WithVetoes/TupleRDS_Sim09b_BsDsDs.root");
  } else if (sample == "LbDD"){
    fChain = new TChain("B2DsMuNuTuple/DecayTree");
    fChain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/WithVetoes/TupleRDS_Sim09b_LbLcDs.root");
  } else if (sample == "sigmu"){
    fChain = new TChain("B2DsMuNuTuple/DecayTree");
    fChain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/WithVetoes/TupleRDS_Sim09b_DsMuNu.root");
  } else if (sample == "sigtau"){
    fChain = new TChain("B2DsMuNuTuple/DecayTree");
    fChain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/WithVetoes/TupleRDS_Sim09b_DsTauNu.root");
  }

  
  Bool_t          Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS;
  Double_t        Kpl_P;
  Double_t        Kmi_P;
  Double_t        pi_P;
  Double_t        Kpl_PT;
  Double_t        Kmi_PT;
  Double_t        pi_PT;
  Double_t        Ds_PT;
//  Float_t         Bs_0_BDTS_DOCA;
  Double_t        Bs_0_FDCHI2_TOPPV;
  Double_t        Ds_MM;
  Double_t        Bs_0_MM;
  Double_t        Bs_0_MCORR;
  Double_t        q2;
  Double_t        Emu;
  Double_t        mu_PT;
  Double_t        mu_PX;
  Double_t        mu_PY;
  Double_t        mu_PZ;
  Double_t        mu_PE;
  Double_t        mu_PIDmu;
  Double_t        mu_iso_MinBDT_Long;
  Int_t           Ds_0_40_nc_mult;
  Double_t        Ds_0_40_nc_maxPt_PX;
  Double_t        Ds_0_40_nc_maxPt_PY;
  Double_t        Ds_0_40_nc_maxPt_PZ;
  Double_t        Ds_0_40_nc_maxPt_PE;
  Double_t        Ds_0_40_nc_CL;
  Int_t           Ds_0_40_pi0_mult;
  Double_t        Ds_0_40_pi0_maxPt_PX;
  Double_t        Ds_0_40_pi0_maxPt_PY;
  Double_t        Ds_0_40_pi0_maxPt_PZ;
  Double_t        Ds_0_40_pi0_maxPt_MM;
  Double_t        Ds_0_40_g1_CL;
  Double_t        Ds_0_40_g2_CL;
  Double_t        Ds_0_40_pi0_maxPt_PE;
  Double_t        Ds_PE;
  Double_t        Ds_PX;
  Double_t        Ds_PY;
  Double_t        Ds_PZ;
  Double_t        Bs_0_PX;
  Double_t        Bs_0_PY;
  Double_t        Bs_0_PZ;
  Double_t        Bs_0_PE;
  Double_t        Bs_0_OWNPV_X;
  Double_t        Bs_0_OWNPV_Y;
  Double_t        Bs_0_OWNPV_Z;
  Double_t        Bs_0_ENDVERTEX_X;
  Double_t        Bs_0_ENDVERTEX_Y;
  Double_t        Bs_0_ENDVERTEX_Z; 
  Double_t        Bs_0_ENDVERTEX_CHI2;
  Double_t        resFlag;
  // true variables for sigmu
  Double_t        Bs_0_TRUEP_X;
  Double_t        Bs_0_TRUEP_Y;
  Double_t        Bs_0_TRUEP_Z;
  Double_t        Bs_0_TRUEP_E;
  Double_t        mu_TRUEP_X;
  Double_t        mu_TRUEP_Y;
  Double_t        mu_TRUEP_Z;
  Double_t        mu_TRUEP_E;
  Double_t        Ds_TRUEP_E;
  Double_t        Ds_TRUEP_X;
  Double_t        Ds_TRUEP_Y;
  Double_t        Ds_TRUEP_Z;
  Double_t        Ds_0_40_nc_MCmaxPt_PX;
  Double_t        Ds_0_40_nc_MCmaxPt_PY;
  Double_t        Ds_0_40_nc_MCmaxPt_PZ;
  Double_t        Ds_0_40_nc_MCmaxPt_PE;
  Int_t           Ds_0_40_nc_MCmax_ID;
  Int_t           Ds_MC_MOTHER_ID;
  Int_t           Ds_MC_GD_MOTHER_ID;
  Int_t           mu_MC_MOTHER_ID;
  Double_t        Ds_1_00_nc_maxPt_PX;
  Double_t        Ds_1_00_nc_maxPt_PY;
  Double_t        Ds_1_00_nc_maxPt_PZ;
  Double_t        Ds_1_00_nc_maxPt_PE;
  Int_t           Ds_1_00_nc_mult;
  Double_t        Ds_1_00_nc_CL;
  Double_t        Ds_1_00_nc_radius;
  Int_t           nLongTracks;

  TBranch        *b_Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS;   //!
  TBranch        *b_Kpl_P;   //!
  TBranch        *b_Kmi_P;   //!
  TBranch        *b_pi_P;   //!
  TBranch        *b_Kpl_PT;   //!
  TBranch        *b_Kmi_PT;   //!
  TBranch        *b_pi_PT;   //!
  TBranch        *b_Ds_PT;   //!
//  TBranch        *b_Bs_0_BDTS_DOCA;   //!
  TBranch        *b_Bs_0_FDCHI2_TOPPV;   //!
  TBranch        *b_Bs_0_MM;
  TBranch        *b_Ds_MM;   //!
  TBranch        *b_Bs_0_MCORR;   //!
  TBranch        *b_q2;    //!
  TBranch        *b_Emu;     //!
  TBranch        *b_mu_PT;   //!
  TBranch        *b_mu_PX;   //!
  TBranch        *b_mu_PY;   //!
  TBranch        *b_mu_PZ;   //!
  TBranch        *b_mu_PE;   //!
  TBranch        *b_mu_PIDmu;   //!
  TBranch        *b_mu_iso_MinBDT_Long;   //!
  TBranch        *b_Ds_0_40_nc_mult;   //!
  TBranch        *b_Ds_0_40_nc_maxPt_PX;   //!
  TBranch        *b_Ds_0_40_nc_maxPt_PY;   //!
  TBranch        *b_Ds_0_40_nc_maxPt_PZ;   //!
  TBranch        *b_Ds_0_40_nc_maxPt_PE;   //!
  TBranch        *b_Ds_0_40_nc_CL;   //!
  TBranch        *b_Ds_0_40_pi0_mult;   //!
  TBranch        *b_Ds_0_40_pi0_maxPt_PX;   //!
  TBranch        *b_Ds_0_40_pi0_maxPt_PY;   //!
  TBranch        *b_Ds_0_40_pi0_maxPt_PZ;   //!
  TBranch        *b_Ds_0_40_pi0_maxPt_MM;   //!
  TBranch        *b_Ds_0_40_g1_CL;   //!
  TBranch        *b_Ds_0_40_g2_CL;   //!
  TBranch        *b_Ds_0_40_pi0_maxPt_PE;   //!
  TBranch        *b_Ds_PE;   //!
  TBranch        *b_Ds_PX;   //!
  TBranch        *b_Ds_PY;   //!
  TBranch        *b_Ds_PZ;   //!
  TBranch        *b_Bs_0_PE;   //!
  TBranch        *b_Bs_0_PX;   //!
  TBranch        *b_Bs_0_PY;   //!
  TBranch        *b_Bs_0_PZ;   //! 
  TBranch        *b_Bs_0_OWNPV_X;
  TBranch        *b_Bs_0_OWNPV_Y;
  TBranch        *b_Bs_0_OWNPV_Z;
  TBranch        *b_Bs_0_ENDVERTEX_X;
  TBranch        *b_Bs_0_ENDVERTEX_Y;
  TBranch        *b_Bs_0_ENDVERTEX_Z;
  TBranch        *b_Bs_0_ENDVERTEX_CHI2;
  TBranch        *b_resFlag;
  // true variables for sigmu
  TBranch        *b_Bs_0_TRUEP_X;
  TBranch        *b_Bs_0_TRUEP_Y;
  TBranch        *b_Bs_0_TRUEP_Z;
  TBranch        *b_Bs_0_TRUEP_E;
  TBranch        *b_mu_TRUEP_X;
  TBranch        *b_mu_TRUEP_Y;
  TBranch        *b_mu_TRUEP_Z;
  TBranch        *b_mu_TRUEP_E;
  TBranch        *b_Ds_TRUEP_E;
  TBranch        *b_Ds_TRUEP_X;
  TBranch        *b_Ds_TRUEP_Y;
  TBranch        *b_Ds_TRUEP_Z;
  TBranch        *b_Ds_0_40_nc_MCmaxPt_PX;
  TBranch        *b_Ds_0_40_nc_MCmaxPt_PY;
  TBranch        *b_Ds_0_40_nc_MCmaxPt_PZ;
  TBranch        *b_Ds_0_40_nc_MCmaxPt_PE;
  TBranch        *b_Ds_0_40_nc_MCmax_ID;
  TBranch        *b_Ds_MC_MOTHER_ID;
  TBranch        *b_Ds_MC_GD_MOTHER_ID;
  TBranch        *b_mu_MC_MOTHER_ID; 
  TBranch        *b_Ds_1_00_nc_maxPt_PX;
  TBranch        *b_Ds_1_00_nc_maxPt_PY;
  TBranch        *b_Ds_1_00_nc_maxPt_PZ;
  TBranch        *b_Ds_1_00_nc_maxPt_PE;
  TBranch        *b_Ds_1_00_nc_mult;   //!
  TBranch        *b_Ds_1_00_nc_CL;   //!
  TBranch        *b_Ds_1_00_nc_radius;
  TBranch        *b_nLongTracks;

  fChain->SetBranchStatus("*",1);
  fChain->SetBranchAddress("Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS", &Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS, &b_Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS);
  fChain->SetBranchAddress("Kpl_P", &Kpl_P, &b_Kpl_P);
  fChain->SetBranchAddress("Kmi_P", &Kmi_P, &b_Kmi_P);
  fChain->SetBranchAddress("pi_P", &pi_P, &b_pi_P);
  fChain->SetBranchAddress("Kpl_PT", &Kpl_PT, &b_Kpl_PT);
  fChain->SetBranchAddress("Kmi_PT", &Kmi_PT, &b_Kmi_PT);
  fChain->SetBranchAddress("pi_PT", &pi_PT, &b_pi_PT);
  fChain->SetBranchAddress("Ds_PT", &Ds_PT, &b_Ds_PT);
//  fChain->SetBranchAddress("Bs_0_BDTS_DOCA", &Bs_0_BDTS_DOCA, &b_Bs_0_BDTS_DOCA);
  fChain->SetBranchAddress("Bs_0_FDCHI2_TOPPV", &Bs_0_FDCHI2_TOPPV, &b_Bs_0_FDCHI2_TOPPV);
  fChain->SetBranchAddress("Ds_MM", &Ds_MM, &b_Ds_MM);
  fChain->SetBranchAddress("Bs_0_MM", &Bs_0_MM, &b_Bs_0_MM);
  fChain->SetBranchAddress("Bs_0_MCORR", &Bs_0_MCORR, &b_Bs_0_MCORR);
  fChain->SetBranchAddress("q2", &q2, &b_q2);
  fChain->SetBranchAddress("Emu", &Emu, &b_Emu);
  fChain->SetBranchAddress("mu_PT", &mu_PT, &b_mu_PT);
  fChain->SetBranchAddress("mu_PX", &mu_PX, &b_mu_PX);
  fChain->SetBranchAddress("mu_PY", &mu_PY, &b_mu_PY);
  fChain->SetBranchAddress("mu_PZ", &mu_PZ, &b_mu_PZ);
  fChain->SetBranchAddress("mu_PE", &mu_PE, &b_mu_PE);
  fChain->SetBranchAddress("mu_PIDmu", &mu_PIDmu, &b_mu_PIDmu);
  fChain->SetBranchAddress("mu_iso_MinBDT_Long", &mu_iso_MinBDT_Long, &b_mu_iso_MinBDT_Long);
  fChain->SetBranchAddress("Ds_0.40_nc_mult", &Ds_0_40_nc_mult, &b_Ds_0_40_nc_mult);
  fChain->SetBranchAddress("Ds_0.40_nc_maxPt_PX", &Ds_0_40_nc_maxPt_PX, &b_Ds_0_40_nc_maxPt_PX);
  fChain->SetBranchAddress("Ds_0.40_nc_maxPt_PY", &Ds_0_40_nc_maxPt_PY, &b_Ds_0_40_nc_maxPt_PY);
  fChain->SetBranchAddress("Ds_0.40_nc_maxPt_PZ", &Ds_0_40_nc_maxPt_PZ, &b_Ds_0_40_nc_maxPt_PZ);
  fChain->SetBranchAddress("Ds_0.40_nc_maxPt_PE", &Ds_0_40_nc_maxPt_PE, &b_Ds_0_40_nc_maxPt_PE);
  fChain->SetBranchAddress("Ds_0.40_nc_CL", &Ds_0_40_nc_CL, &b_Ds_0_40_nc_CL);
  fChain->SetBranchAddress("Ds_0.40_pi0_mult", &Ds_0_40_pi0_mult, &b_Ds_0_40_pi0_mult);
  fChain->SetBranchAddress("Ds_0.40_pi0_maxPt_PX", &Ds_0_40_pi0_maxPt_PX, &b_Ds_0_40_pi0_maxPt_PX);
  fChain->SetBranchAddress("Ds_0.40_pi0_maxPt_PY", &Ds_0_40_pi0_maxPt_PY, &b_Ds_0_40_pi0_maxPt_PY);
  fChain->SetBranchAddress("Ds_0.40_pi0_maxPt_PZ", &Ds_0_40_pi0_maxPt_PZ, &b_Ds_0_40_pi0_maxPt_PZ);
  fChain->SetBranchAddress("Ds_0.40_pi0_maxPt_MM", &Ds_0_40_pi0_maxPt_MM, &b_Ds_0_40_pi0_maxPt_MM);
  fChain->SetBranchAddress("Ds_0.40_g1_CL", &Ds_0_40_g1_CL, &b_Ds_0_40_g1_CL);
  fChain->SetBranchAddress("Ds_0.40_g2_CL", &Ds_0_40_g2_CL, &b_Ds_0_40_g2_CL);
  fChain->SetBranchAddress("Ds_0.40_pi0_maxPt_PE", &Ds_0_40_pi0_maxPt_PE, &b_Ds_0_40_pi0_maxPt_PE);
  fChain->SetBranchAddress("Ds_PE", &Ds_PE, &b_Ds_PE);
  fChain->SetBranchAddress("Ds_PX", &Ds_PX, &b_Ds_PX);
  fChain->SetBranchAddress("Ds_PY", &Ds_PY, &b_Ds_PY);
  fChain->SetBranchAddress("Ds_PZ", &Ds_PZ, &b_Ds_PZ);
  fChain->SetBranchAddress("Bs_0_PE", &Bs_0_PE, &b_Bs_0_PE);
  fChain->SetBranchAddress("Bs_0_PX", &Bs_0_PX, &b_Bs_0_PX);
  fChain->SetBranchAddress("Bs_0_PY", &Bs_0_PY, &b_Bs_0_PY);
  fChain->SetBranchAddress("Bs_0_PZ", &Bs_0_PZ, &b_Bs_0_PZ);
  fChain->SetBranchAddress("Bs_0_OWNPV_X", &Bs_0_OWNPV_X, &b_Bs_0_OWNPV_X);
  fChain->SetBranchAddress("Bs_0_OWNPV_Y", &Bs_0_OWNPV_Y, &b_Bs_0_OWNPV_Y);
  fChain->SetBranchAddress("Bs_0_OWNPV_Z", &Bs_0_OWNPV_Z, &b_Bs_0_OWNPV_Z);
  fChain->SetBranchAddress("Bs_0_ENDVERTEX_X", &Bs_0_ENDVERTEX_X, &b_Bs_0_ENDVERTEX_X);
  fChain->SetBranchAddress("Bs_0_ENDVERTEX_Y", &Bs_0_ENDVERTEX_Y, &b_Bs_0_ENDVERTEX_Y);
  fChain->SetBranchAddress("Bs_0_ENDVERTEX_Z", &Bs_0_ENDVERTEX_Z, &b_Bs_0_ENDVERTEX_Z);
  fChain->SetBranchAddress("Bs_0_ENDVERTEX_CHI2", &Bs_0_ENDVERTEX_CHI2, &b_Bs_0_ENDVERTEX_CHI2);
  fChain->SetBranchAddress("resFlag", &resFlag, &b_resFlag);
  fChain->SetBranchAddress("nLongTracks", &nLongTracks, &b_nLongTracks);
  if(sample=="sigmu" || sample == "sigtau"){
    fChain->SetBranchAddress("Ds_0.40_nc_MCmaxPt_PX", &Ds_0_40_nc_MCmaxPt_PX, &b_Ds_0_40_nc_MCmaxPt_PX);
    fChain->SetBranchAddress("Ds_0.40_nc_MCmaxPt_PY", &Ds_0_40_nc_MCmaxPt_PY, &b_Ds_0_40_nc_MCmaxPt_PY);
    fChain->SetBranchAddress("Ds_0.40_nc_MCmaxPt_PZ", &Ds_0_40_nc_MCmaxPt_PZ, &b_Ds_0_40_nc_MCmaxPt_PZ);
    fChain->SetBranchAddress("Ds_0.40_nc_MCmaxPt_PE", &Ds_0_40_nc_MCmaxPt_PE, &b_Ds_0_40_nc_MCmaxPt_PE); 
    fChain->SetBranchAddress("Ds_0.40_nc_MCmax_ID", &Ds_0_40_nc_MCmax_ID, &b_Ds_0_40_nc_MCmax_ID);
    fChain->SetBranchAddress("Ds_MC_MOTHER_ID", &Ds_MC_MOTHER_ID, &b_Ds_MC_MOTHER_ID);
    fChain->SetBranchAddress("Ds_MC_GD_MOTHER_ID", &Ds_MC_GD_MOTHER_ID, &b_Ds_MC_GD_MOTHER_ID);
    fChain->SetBranchAddress("mu_MC_MOTHER_ID", &mu_MC_MOTHER_ID, &b_mu_MC_MOTHER_ID); 
    fChain->SetBranchAddress("mu_TRUEP_X", &mu_TRUEP_X, &b_mu_TRUEP_X);
    fChain->SetBranchAddress("mu_TRUEP_Y", &mu_TRUEP_Y, &b_mu_TRUEP_Y);
    fChain->SetBranchAddress("mu_TRUEP_Z", &mu_TRUEP_Z, &b_mu_TRUEP_Z);
    fChain->SetBranchAddress("mu_TRUEP_E", &mu_TRUEP_E, &b_mu_TRUEP_E);
    fChain->SetBranchAddress("Ds_TRUEP_E", &Ds_TRUEP_E, &b_Ds_TRUEP_E);
    fChain->SetBranchAddress("Ds_TRUEP_X", &Ds_TRUEP_X, &b_Ds_TRUEP_X);
    fChain->SetBranchAddress("Ds_TRUEP_Y", &Ds_TRUEP_Y, &b_Ds_TRUEP_Y);
    fChain->SetBranchAddress("Ds_TRUEP_Z", &Ds_TRUEP_Z, &b_Ds_TRUEP_Z);
    fChain->SetBranchAddress("Bs_0_TRUEP_E", &Bs_0_TRUEP_E, &b_Bs_0_TRUEP_E);
    fChain->SetBranchAddress("Bs_0_TRUEP_X", &Bs_0_TRUEP_X, &b_Bs_0_TRUEP_X);
    fChain->SetBranchAddress("Bs_0_TRUEP_Y", &Bs_0_TRUEP_Y, &b_Bs_0_TRUEP_Y);
    fChain->SetBranchAddress("Bs_0_TRUEP_Z", &Bs_0_TRUEP_Z, &b_Bs_0_TRUEP_Z);
  }

  RooRealVar *fitMass;
  if(resonance == "Dsst"){
    fitMass = new RooRealVar("resMass", "resMass", 2050., 2220.);
  }
  if(resonance == "Ds0"){
    fitMass = new RooRealVar("resMass", "resMass", 2050., 2600.);
  }  
  RooRealVar *triggerTOS = new RooRealVar("triggerTOS", "triggerTOS", 0,1);
  RooRealVar *kplp = new RooRealVar("kplp", "kplp", 0., 10000000.);
  RooRealVar *kmip = new RooRealVar("kmip", "kmip", 0., 10000000.);
  RooRealVar *pip = new RooRealVar("pip", "pip", 0., 10000000.);
  RooRealVar *kplpt = new RooRealVar("kplpt", "kplpt", 0.,10000000.);
  RooRealVar *kmipt = new RooRealVar("kmipt", "kmipt", 0.,10000000.);
  RooRealVar *pipt = new RooRealVar("pipt", "pipt", 0.,10000000.);
  RooRealVar *dspt = new RooRealVar("dspt", "dspt", 0.,10000000.);
  RooRealVar *bsdoca = new RooRealVar("bsdoca", "bsdoca", 0., 1.);
  RooRealVar *bsfdchi2 = new RooRealVar("bsfdchi2", "bsfdchi2", 0., 100000.);
  RooRealVar *dsmm = new RooRealVar("dsmm", "dsmm", 1940., 2000.);
  RooRealVar *bsmm = new RooRealVar("bsmm", "bsmm", 2000., 8000.);
  RooRealVar *mcorr = new RooRealVar("mcorr", "mcorr", 0., 10000.);
  RooRealVar *Q2 = new RooRealVar("Q2", "Q2", -15000000., 15000000.);
  RooRealVar *emu = new RooRealVar("emu", "emu", 0., 4000.);
  RooRealVar *mupt = new RooRealVar("mupt", "mupt", 0., 10000000.);
  //RooRealVar *mupx = new RooRealVar("mupx", "mupx", -10000000., 10000000.);
  //RooRealVar *mupy = new RooRealVar("mupy", "mupy", -10000000., 10000000.);
  //RooRealVar *mupz = new RooRealVar("mupz", "mupz", -10000000., 10000000.);
  //RooRealVar *mupe = new RooRealVar("mupe", "mupe", 0., 10000000.);
  RooRealVar *mupidmu = new RooRealVar("mupidmu", "mupidmu", -50., 50.);
  RooRealVar *muiso = new RooRealVar("muiso", "muiso", -1., 1.);
  RooRealVar *ncmult = new RooRealVar("ncmult", "ncmult", 0., 20.);
  RooRealVar *ncpx = new RooRealVar("ncpx", "ncpx", -10000000., 10000000.);
  RooRealVar *ncpy = new RooRealVar("ncpy", "ncpy", -10000000., 10000000.);
  RooRealVar *ncpz = new RooRealVar("ncpz", "ncpz", -10000000., 10000000.);
  RooRealVar *ncpe = new RooRealVar("ncpe", "ncpe", 0., 10000000.);
  RooRealVar *ncCL = new RooRealVar("ncCL", "ncCL", 0., 1.);
  RooRealVar *pi0mult = new RooRealVar("pi0mult", "pi0mult", 0., 20.);
  RooRealVar *pi0px = new RooRealVar("pi0px", "pi0px", -10000000., 10000000.);
  RooRealVar *pi0py = new RooRealVar("pi0py", "pi0py", -10000000., 10000000.); 
  RooRealVar *pi0pz = new RooRealVar("pi0pz", "pi0pz", -10000000., 10000000.);
  RooRealVar *pi0mm = new RooRealVar("pi0mm", "pi0mm", 80., 200.);  
  RooRealVar *g1CL = new RooRealVar("g1CL", "g1CL", 0., 1.); 
  RooRealVar *g2CL = new RooRealVar("g2CL", "g2CL", 0., 1.); 
  RooRealVar *pi0pe = new RooRealVar("pi0pe", "pi0pe", 0., 10000000.);
  RooRealVar *dspe = new RooRealVar("dspe", "dspe", 0., 10000000.);
  RooRealVar *dspx = new RooRealVar("dspx", "dspx", -10000000., 10000000.);
  RooRealVar *dspy = new RooRealVar("dspy", "dspy", -10000000., 10000000.);
  RooRealVar *dspz = new RooRealVar("dspz", "dspz", -10000000., 10000000.);
  RooRealVar *bspe = new RooRealVar("bspe", "bspe", 0., 10000000.);
  RooRealVar *bspx = new RooRealVar("bspx", "bspx", -10000000., 10000000.);
  RooRealVar *bspy = new RooRealVar("bspy", "bspy", -10000000., 10000000.);
  RooRealVar *bspz = new RooRealVar("bspz", "bspz", -10000000., 10000000.);
  RooRealVar *bsorigx = new RooRealVar("bsorigx", "bsorigx", -10000000., 10000000.);
  RooRealVar *bsorigy = new RooRealVar("bsorigy", "bsorigy", -10000000., 10000000.);
  RooRealVar *bsorigz = new RooRealVar("bsorigz", "bsorigz", -10000000., 10000000.);
  RooRealVar *bsendx = new RooRealVar("bsendx", "bsendx", -10000000., 10000000.);
  RooRealVar *bsendy = new RooRealVar("bsendy", "bsendy", -10000000., 10000000.);
  RooRealVar *bsendz = new RooRealVar("bsendz", "bsendz", -10000000., 10000000.);
  RooRealVar *bsvchi2 = new RooRealVar("bsvchi2", "bsvchi2", 0., 8.);
  RooRealVar *MassDsG = new RooRealVar("MassDsG", "MassDsG", -10000000., 10000000.);
  RooRealVar *aDsG = new RooRealVar("aDsG", "aDsG", -10000000., 10000000.);
  RooRealVar *pBsY = new RooRealVar("pBsY", "pBsY", -10000000., 10000000.);
  RooRealVar *q2Y = new RooRealVar("q2Y", "q2Y", -15000000., 15000000.);
  RooRealVar *mm2Y = new RooRealVar("mm2Y", "mm2Y", -10000000., 10000000.);
  RooRealVar *thlY = new RooRealVar("thlY", "thlY", -10000000., 10000000.);
  RooRealVar *elcmY = new RooRealVar("elcmY", "elcmY", -10000000., 10000000.);
  RooRealVar *wY = new RooRealVar("wY", "wY", -10000000., 10000000.);
  RooRealVar *pBsP1 = new RooRealVar("pBsP1", "pBsP1", -10000000., 10000000.);
  RooRealVar *q2P1 = new RooRealVar("q2P1", "q2P1", -15000000., 15000000.);
  RooRealVar *mm2P1 = new RooRealVar("mm2P1", "mm2P1", -10000000., 10000000.);
  RooRealVar *thlP1 = new RooRealVar("thlP1", "thlP1", -10000000., 10000000.);
  RooRealVar *elcmP1 = new RooRealVar("elcmP1", "elcmP1", -10000000., 10000000.);
  RooRealVar *wP1 = new RooRealVar("wP1", "wP1", -10000000., 10000000.);
  RooRealVar *pBsP2 = new RooRealVar("pBsP2", "pBsP2", -10000000., 10000000.);
  RooRealVar *q2P2 = new RooRealVar("q2P2", "q2P2", -15000000., 15000000.);
  RooRealVar *mm2P2 = new RooRealVar("mm2P2", "mm2P2", -10000000., 10000000.);
  RooRealVar *thlP2 = new RooRealVar("thlP2", "thlP2", -10000000., 10000000.);
  RooRealVar *elcmP2 = new RooRealVar("elcmP2", "elcmP2", -10000000., 10000000.);
  RooRealVar *wP2 = new RooRealVar("wP2", "wP2", -10000000., 10000000.);
  RooRealVar *pBsTrue = new RooRealVar("pBsTrue", "pBsTrue", -10000000., 10000000.);
  RooRealVar *q2True = new RooRealVar("q2True", "q2True", -15000000., 15000000.);
  RooRealVar *mm2True = new RooRealVar("mm2True", "mm2True", -10000000., 10000000.);
  RooRealVar *thlTrue = new RooRealVar("thlTrue", "thlTrue", -10000000., 10000000.);
  RooRealVar *elcmTrue = new RooRealVar("elcmTrue", "elcmTrue", -10000000., 10000000.);
  RooRealVar *wTrue = new RooRealVar("wTrue", "wTrue", -10000000., 10000000.);
  RooRealVar *sq = new RooRealVar("sq", "sq", -10000000., 10000000.);
  RooRealVar *McorrDsst = new RooRealVar("McorrDsst", "McorrDsst", 0., 10000000.);
  RooRealVar *McorrDs = new RooRealVar("McorrDs", "McorrDs", 0., 10000000.);
  RooRealVar *bSinFlightAng = new RooRealVar("bSinFlightAng", "bSinFlightAng", -10000000., 10000000.);
  RooRealVar *bFlightLen = new RooRealVar("bFlightLen", "bFlightLen", -10000000., 10000000.);
  RooRealVar *truemupx = new RooRealVar("truemupx", "truemupx", -10000000., 10000000.);
  RooRealVar *truemupy = new RooRealVar("truemupy", "truemupy", -10000000., 10000000.);
  RooRealVar *truemupz = new RooRealVar("truemupz", "truemupz", -10000000., 10000000.);
  RooRealVar *truemupe = new RooRealVar("truemupe", "truemupe", 0., 10000000.);
  RooRealVar *truedspe = new RooRealVar("truedspe", "truedspe", 0., 10000000.);
  RooRealVar *truedspx = new RooRealVar("truedspx", "truedspx", -10000000., 10000000.);
  RooRealVar *truedspy = new RooRealVar("truedspy", "truedspy", -10000000., 10000000.);
  RooRealVar *truedspz = new RooRealVar("truedspz", "truedspz", -10000000., 10000000.);
  RooRealVar *truebspe = new RooRealVar("truebspe", "truebspe", 0., 10000000.);
  RooRealVar *truebspx = new RooRealVar("truebspx", "truebspx", -10000000., 10000000.);
  RooRealVar *truebspy = new RooRealVar("truebspy", "truebspy", -10000000., 10000000.);
  RooRealVar *truebspz = new RooRealVar("truebspz", "truebspz", -10000000., 10000000.);
  RooRealVar *truencpx = new RooRealVar("truencpx", "truencpx", -10000000., 10000000.);
  RooRealVar *truencpy = new RooRealVar("truencpy", "truencpy", -10000000., 10000000.);
  RooRealVar *truencpz = new RooRealVar("truencpz", "truencpz", -10000000., 10000000.);
  RooRealVar *truencpe = new RooRealVar("truencpe", "truencpe", 0., 10000000.);
  RooRealVar *gID = new RooRealVar("gID", "gID", -100000.,100000.);
  RooRealVar *DsMomID = new RooRealVar("DsMomID", "DsMomID", -100000.,100000.);
  RooRealVar *DsGMID = new RooRealVar("DsGMID", "DsGMID", -100000.,100000.);
  RooRealVar *muMomID = new RooRealVar("muMomID", "muMomID", -100000.,100000.);
  RooRealVar *nLongT = new RooRealVar("nLongT", "nLongT", 0., 140.);
  RooRealVar *rad = new RooRealVar("rad","rad",0.,1.);
  RooRealVar *helicity = new RooRealVar("helicity", "helicity", -1., 1.);

  RooArgSet vars;
  vars.add(RooArgSet(*fitMass, *triggerTOS, *kplp, *kmip, *pip, *kplpt, *kmipt, *pipt, *dspt));
  vars.add(RooArgSet(*bsdoca,*bsfdchi2,*dsmm,*mcorr,*Q2,*emu,*mupt,*mupidmu,*muiso));
  vars.add(RooArgSet(*bsmm));
  vars.add(RooArgSet(*ncmult,*ncpx,*ncpy,*ncpz,*ncpe,*ncCL));
  vars.add(RooArgSet(*pi0mult,*pi0px,*pi0py,*pi0pz,*pi0mm,*pi0pe,*g1CL,*g2CL));
  vars.add(RooArgSet(*dspe,*dspx,*dspy,*dspz)); 
  vars.add(RooArgSet(*bspe,*bspx,*bspy,*bspz));
  vars.add(RooArgSet(*bsorigx,*bsorigy,*bsorigz,*bsendx,*bsendy,*bsendz,*bsvchi2));
  vars.add(RooArgSet(*MassDsG,*aDsG));
  vars.add(RooArgSet(*pBsY,*q2Y,*mm2Y,*thlY,*elcmY,*wY));
  vars.add(RooArgSet(*pBsP1,*q2P1,*mm2P1,*thlP1,*elcmP1,*wP1));
  vars.add(RooArgSet(*pBsP2,*q2P2,*mm2P2,*thlP2,*elcmP2,*wP2));
  vars.add(RooArgSet(*sq,*McorrDsst,*bSinFlightAng,*bFlightLen,*nLongT));
  if(sample=="sigmu" || sample == "sigtau"){
    vars.add(RooArgSet(*truedspe,*truedspx,*truedspy,*truedspz));
    vars.add(RooArgSet(*truebspe,*truebspx,*truebspy,*truebspz));
    vars.add(RooArgSet(*truemupe,*truemupx,*truemupy,*truemupz));
    vars.add(RooArgSet(*truencpx,*truencpy,*truencpz,*truencpe));
    vars.add(RooArgSet(*pBsTrue,*q2True,*mm2True,*thlTrue,*elcmTrue,*wTrue));
    vars.add(RooArgSet(*gID,*DsMomID,*DsGMID,*muMomID,*helicity));
  }
  RooDataSet *data = new RooDataSet("dataset", "dataset", vars);

  Double_t DsMassPDG(1.96827);
  Double_t BsMassPDG(5366.82);
  Double_t DsstMassPDG(2112.1);
  Double_t GeV=1000;
  Double_t GeV2= GeV*GeV;
  std::cout << "Imported vars" << std::endl;
  // Fill for Dsst
  if(resonance == "Dsst"){
    for(int i = 0; i!=nentries; ++i){
      if (i%1000000 == 0) std::cout << "--- ... Processing event: " << i << std::endl;
      fChain->GetEntry(i);
      // apply the cuts to add only good data
      // remove mu_pT> 1000
      // all the MC samples from Sim09b have already the right trigger applied
      bool cuts;
      //if (sample == "data" || sample == "SS" || sample == "sigmu" || sample == "sigtau" || sample == "sigmuSim09b"){
        //cuts = resFlag<2 && Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS==1 && Bs_0_MCORR<8000 && Bs_0_MCORR>3000 && mu_PIDmu>0.0 && Ds_MM>1940 && Ds_MM<2000 && mu_iso_MinBDT_Long>-0.5 && Ds_0_40_nc_mult>0 && sqrt(pow(Ds_0_40_nc_maxPt_PX,2)+pow(Ds_0_40_nc_maxPt_PY,2))>0 && Ds_0_40_nc_CL > 0.6;
      cuts = resFlag<2 && Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS==1 && Bs_0_MCORR<8000 && Bs_0_MCORR>3000 && mu_PIDmu>0.0 && Ds_MM>1940 && Ds_MM<2000 && mu_iso_MinBDT_Long>-0.5 && Ds_0_40_nc_mult>0 && sqrt(pow(Ds_0_40_nc_maxPt_PX,2)+pow(Ds_0_40_nc_maxPt_PY,2))>0;
      //}
      //else cuts = Bs_0_MCORR<8000 && Bs_0_MCORR>3000 && mu_PIDmu>0.0 && Ds_MM>1940 && Ds_MM<2000 && mu_iso_MinBDT_Long>-0.5 && Ds_0_40_nc_mult>0 && sqrt(pow(Ds_0_40_nc_maxPt_PX,2)+pow(Ds_0_40_nc_maxPt_PY,2))>0 && Ds_0_40_nc_CL > 0.6; 
      //else cuts = Bs_0_MCORR<8000 && Bs_0_MCORR>3000 && mu_PIDmu>0.0 && Ds_MM>1940 && Ds_MM<2000 && mu_iso_MinBDT_Long>-0.5 && Ds_0_40_nc_mult>0 && sqrt(pow(Ds_0_40_nc_maxPt_PX,2)+pow(Ds_0_40_nc_maxPt_PY,2))>0; 
      if (cuts) {
        float mass = sqrt( pow((Ds_0_40_nc_maxPt_PE+Ds_PE),2) - ( pow(Ds_0_40_nc_maxPt_PX+Ds_PX,2)+pow(Ds_0_40_nc_maxPt_PY+Ds_PY,2)+pow(Ds_0_40_nc_maxPt_PZ+Ds_PZ,2) ) )-Ds_MM+1968.30;
        if(mass < 2050. || mass > 2220.) continue;
        *fitMass = sqrt( pow((Ds_0_40_nc_maxPt_PE+Ds_PE),2) - ( pow(Ds_0_40_nc_maxPt_PX+Ds_PX,2)+pow(Ds_0_40_nc_maxPt_PY+Ds_PY,2)+pow(Ds_0_40_nc_maxPt_PZ+Ds_PZ,2) ) )-Ds_MM+1968.30;
        *triggerTOS = Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS;
        *kplp = Kpl_P;
        *kmip = Kmi_P;
        *pip = pi_P;
        *kplpt = Kpl_PT;
        *kmipt = Kmi_PT;
        *pipt = pi_PT;
        *dspt = Ds_PT;
//        *bsdoca = Bs_0_BDTS_DOCA;
        *bsfdchi2 = Bs_0_FDCHI2_TOPPV;
        *dsmm = Ds_MM;
        *bsmm = Bs_0_MM;
        *mcorr = Bs_0_MCORR;
        *Q2 = q2;
        *emu = Emu;
        *mupt = mu_PT;
        //*mupx = mu_PX;
        //*mupy = mu_PY;
        //*mupz = mu_PZ;
        //*mupe = mu_PE;
        *mupidmu = mu_PIDmu;
        *muiso = mu_iso_MinBDT_Long;
        *ncmult = Ds_0_40_nc_mult;
        *ncpx = Ds_0_40_nc_maxPt_PX;
        *ncpy = Ds_0_40_nc_maxPt_PY;
        *ncpz = Ds_0_40_nc_maxPt_PZ; 
        *ncpe = Ds_0_40_nc_maxPt_PE;
        *ncCL = Ds_0_40_nc_CL;
        *pi0mult = Ds_0_40_pi0_mult;
        *pi0px = Ds_0_40_pi0_maxPt_PX;
        *pi0py = Ds_0_40_pi0_maxPt_PY;
        *pi0pz = Ds_0_40_pi0_maxPt_PZ;
        *pi0mm = Ds_0_40_pi0_maxPt_MM;
        *pi0pe = Ds_0_40_pi0_maxPt_PE;
        *g1CL = Ds_0_40_g1_CL;
        *g2CL = Ds_0_40_g2_CL;
        *dspe = Ds_PE;
        *dspx = Ds_PX;
        *dspy = Ds_PY;
        *dspz = Ds_PZ;
        *bspe = Bs_0_PE;
        *bspx = Bs_0_PX;
        *bspy = Bs_0_PY;
        *bspz = Bs_0_PZ;
        *nLongT = nLongTracks;
        if(sample=="sigmu" || sample == "sigtau"){
          *truemupx = mu_TRUEP_X;
          *truemupy = mu_TRUEP_Y;
          *truemupz = mu_TRUEP_Z;
          *truemupe = mu_TRUEP_E;
          *truedspe = Ds_TRUEP_E;
          *truedspx = Ds_TRUEP_X;
          *truedspy = Ds_TRUEP_Y;
          *truedspz = Ds_TRUEP_Z;
          *truebspe = Bs_0_TRUEP_E;
          *truebspx = Bs_0_TRUEP_X;
          *truebspy = Bs_0_TRUEP_Y;
          *truebspz = Bs_0_TRUEP_Z;
          *truencpx = Ds_0_40_nc_MCmaxPt_PX;
          *truencpy = Ds_0_40_nc_MCmaxPt_PY;
          *truencpz = Ds_0_40_nc_MCmaxPt_PZ;
          *truencpe = Ds_0_40_nc_MCmaxPt_PE; 
          *gID = Ds_0_40_nc_MCmax_ID;
          *DsMomID = Ds_MC_MOTHER_ID;
          *DsGMID = Ds_MC_GD_MOTHER_ID;
          *muMomID = mu_MC_MOTHER_ID;
        }
        *rad = Ds_1_00_nc_radius;
        *bsorigx = Bs_0_OWNPV_X;
        *bsorigy = Bs_0_OWNPV_Y;
        *bsorigz = Bs_0_OWNPV_Z;
        *bsendx = Bs_0_ENDVERTEX_X;
        *bsendy = Bs_0_ENDVERTEX_Y;
        *bsendz = Bs_0_ENDVERTEX_Z;
        *bsvchi2 = Bs_0_ENDVERTEX_CHI2;
        // compute the helicity angle
        TLorentzVector gamma(Ds_0_40_nc_maxPt_PX,Ds_0_40_nc_maxPt_PY,Ds_0_40_nc_maxPt_PZ,Ds_0_40_nc_maxPt_PE);
        TLorentzVector Dsst(Ds_PX+Ds_0_40_nc_maxPt_PX,Ds_PY+Ds_0_40_nc_maxPt_PY,Ds_PZ+Ds_0_40_nc_maxPt_PZ,Ds_PE+Ds_0_40_nc_maxPt_PE);
        gamma.Boost(-Dsst.BoostVector());
        Double_t angle = cos(gamma.Vect().Angle(Dsst.BoostVector()));
        *helicity = angle;
        // stuff from Marcello
        *MassDsG = sqrt(((Ds_PE+Ds_0_40_nc_maxPt_PE)*(Ds_PE+Ds_0_40_nc_maxPt_PE)-
                       (Ds_PX+Ds_0_40_nc_maxPt_PX)*(Ds_PX+Ds_0_40_nc_maxPt_PX)-
                       (Ds_PY+Ds_0_40_nc_maxPt_PY)*(Ds_PY+Ds_0_40_nc_maxPt_PY)-
                       (Ds_PZ+Ds_0_40_nc_maxPt_PZ)*(Ds_PZ+Ds_0_40_nc_maxPt_PZ))/1000000)-
                       Ds_MM/1000+DsMassPDG;
        TLorentzVector Bs4V(Bs_0_PX,Bs_0_PY,Bs_0_PZ,Bs_0_PE);
        TLorentzVector Mu4V(mu_PX,mu_PY,mu_PZ,mu_PE);
        TLorentzVector Dsst4V(Ds_PX+Ds_0_40_nc_maxPt_PX,Ds_PY+Ds_0_40_nc_maxPt_PY,Ds_PZ+Ds_0_40_nc_maxPt_PZ,Ds_PE+Ds_0_40_nc_maxPt_PE);
        TLorentzVector Ds4V(Ds_PX,Ds_PY,Ds_PZ,Ds_PE);   
        TLorentzVector DsstMu4V = Dsst4V + Mu4V;
        TLorentzVector DsMu4V = Ds4V + Mu4V;
        //*helicity = hel(Bs4V,Ds4V,gamma,Mu4V);
        TVector3 DsstMu3V = DsstMu4V.Vect();
        TVector3 DsMu3V = DsMu4V.Vect();
        TVector3 Bs4V3 = Bs4V.Vect();
        TVector3 Bs_dir(Bs_0_ENDVERTEX_X - Bs_0_OWNPV_X,
                        Bs_0_ENDVERTEX_Y - Bs_0_OWNPV_Y,
                        Bs_0_ENDVERTEX_Z - Bs_0_OWNPV_Z);
        Double_t Bs_dir_phi = Bs_dir.Phi();
        Double_t Bs_dir_eta = Bs_dir.Eta();
        Double_t Bs_dir_theta = Bs_dir.Theta();
        Double_t Bs_dir_mag = Bs_dir.Mag();
        //Double_t ang = Bs_dir.Angle(Bs4V3);
        Double_t ang = Bs_dir.Angle(DsstMu3V);
        *bSinFlightAng = sin(Bs_dir_theta);
        *bFlightLen = Bs_dir_mag;
        Double_t pHigh(0.), pLow(0.), det(0.);
        //ComputeBMom2Fold(BsMassPDG,Bs4V,Bs_dir,pLow,pHigh,det);
        ComputeBMom2Fold(BsMassPDG,DsstMu4V,Bs_dir,pLow,pHigh,det);
        TVector3 B3vHigh = (Bs_dir.Unit())*pHigh;
        TVector3 B3vLow = (Bs_dir.Unit())*pLow;
        TLorentzVector Bs4vHigh( B3vHigh,sqrt( BsMassPDG*BsMassPDG+B3vHigh.Mag2() ) );
        TLorentzVector Bs4vLow( B3vLow,sqrt( BsMassPDG*BsMassPDG+B3vLow.Mag2() ) );
        *pBsP1 = pHigh;
        *pBsP2 = pLow;
        *sq = det;
        SemiDec slHigh(Bs4vHigh, Dsst4V, Mu4V);
        *q2P1 = slHigh.GetQ2();
        *mm2P1 = slHigh.GetMM2();
        *thlP1 = slHigh.GetThetaL();
        *elcmP1 = slHigh.GetElCM();
        *wP1 = slHigh.GetW();
        SemiDec slLow(Bs4vLow, Dsst4V, Mu4V);
        *q2P2 = slLow.GetQ2();
        *mm2P2 = slLow.GetMM2();
        *thlP2 = slLow.GetThetaL();
        *elcmP2 = slLow.GetElCM();
        *wP2 = slLow.GetW();
        // ========================================================================
        // Boost Approx. Kinematics
        // ========================================================================
        *pBsY = (BsMassPDG/DsstMu4V.M())*(DsstMu4V.Pz())*sqrt(1+tan(Bs_dir_theta)*tan(Bs_dir_theta));
        TVector3 BsFromY3=(Bs_dir.Unit())*(pBsY->getValV());
        Double_t EBsFromY= sqrt(pBsY->getValV()*pBsY->getValV()+BsMassPDG*BsMassPDG);
        TLorentzVector BsFromY(BsFromY3.X(),BsFromY3.Y(),BsFromY3.Z(),EBsFromY );
        SemiDec slY(BsFromY, Dsst4V, Mu4V);
        *q2Y = slY.GetQ2();
        *mm2Y = slY.GetMM2();
        *thlY = slY.GetThetaL();
        *elcmY = slY.GetElCM();
        *wY = slY.GetW();
        if(sample=="sigmu" || sample == "sigtau"){
          // MC =============
          // True quantities
          // ================
          TLorentzVector BsTrue4V(Bs_0_TRUEP_X, Bs_0_TRUEP_Y, Bs_0_TRUEP_Z, Bs_0_TRUEP_E);
          TLorentzVector MuTrue4V(mu_TRUEP_X,mu_TRUEP_Y,mu_TRUEP_Z,mu_TRUEP_E);
          TLorentzVector DsTrue4V(Ds_TRUEP_X, Ds_TRUEP_Y, Ds_TRUEP_Z, Ds_TRUEP_E);
          TLorentzVector GammaTrue4V(Ds_0_40_nc_MCmaxPt_PX, Ds_0_40_nc_MCmaxPt_PY, Ds_0_40_nc_MCmaxPt_PZ, Ds_0_40_nc_MCmaxPt_PE);
          TLorentzVector DssTrue4Va = DsTrue4V+GammaTrue4V;

          TLorentzVector DssTrue4V; DssTrue4V.SetXYZM(DssTrue4Va.X(), DssTrue4Va.Y(), DssTrue4Va.Z(), DsstMassPDG);

          SemiDec slTrue(BsTrue4V, DssTrue4V, MuTrue4V);
          *q2True=slTrue.GetQ2();
          *mm2True=slTrue.GetMM2();
          *thlTrue = slTrue.GetThetaL();
          *elcmTrue=slTrue.GetElCM();
          *wTrue=slTrue.GetW();
          *pBsTrue=BsTrue4V.P();
        }
        // ==========================
        // compute corrected mass
        // ==========================
        // Ds corrected mass
        TVector3 Ds3V = Ds4V.Vect();
        Double_t pTcorrDs = DsMu3V.Perp(Bs_dir);
        *McorrDs = sqrt( DsMu4V.M2()+pow(pTcorrDs,2) ) + pTcorrDs;
        // Dsst corrected mass
        TVector3 Dsst3V = Dsst4V.Vect();
        Double_t pTcorrDsst = DsstMu3V.Perp(Bs_dir);
        *McorrDsst = sqrt( DsstMu4V.M2()+pow(pTcorrDsst,2) ) + pTcorrDsst; 
        TVector3 Mu3V = Mu4V.Vect();
        Double_t pTcorr =  Mu3V.Perp(Bs_dir);
        //Double_t McorrMu = (sqrt( pow(Bs_0_MM,2)+pow(pTcorr,2) ) + pTcorr);
        RooArgSet upvars;
        upvars.add(RooArgSet(*fitMass, *kplp, *kmip, *pip, *kplpt, *kmipt, *pipt, *dspt));
        upvars.add(RooArgSet(*bsdoca,*bsfdchi2,*dsmm,*mcorr,*Q2,*emu,*mupt,*mupidmu,*muiso));
        upvars.add(RooArgSet(*ncmult,*ncpx,*ncpy,*ncpz,*ncpe,*ncCL));
        upvars.add(RooArgSet(*pi0mult,*pi0px,*pi0py,*pi0pz,*pi0mm,*pi0pe,*g1CL,*g2CL));
        upvars.add(RooArgSet(*bsmm,*triggerTOS));
        upvars.add(RooArgSet(*dspe,*dspx,*dspy,*dspz));
        upvars.add(RooArgSet(*bspe,*bspx,*bspy,*bspz));
        upvars.add(RooArgSet(*bsorigx,*bsorigy,*bsorigz,*bsendx,*bsendy,*bsendz,*bsvchi2));
        upvars.add(RooArgSet(*MassDsG,*aDsG));
        upvars.add(RooArgSet(*pBsY,*q2Y,*mm2Y,*thlY,*elcmY,*wY));
        upvars.add(RooArgSet(*pBsP1,*q2P1,*mm2P1,*thlP1,*elcmP1,*wP1));
        upvars.add(RooArgSet(*pBsP2,*q2P2,*mm2P2,*thlP2,*elcmP2,*wP2));
        upvars.add(RooArgSet(*sq,*McorrDsst,*bSinFlightAng,*bFlightLen,*nLongT));
        if(sample=="sigmu" || sample == "sigtau"){
          upvars.add(RooArgSet(*truemupe,*truemupx,*truemupy,*truemupz));
          upvars.add(RooArgSet(*truedspe,*truedspx,*truedspy,*truedspz));
          upvars.add(RooArgSet(*truebspe,*truebspx,*truebspy,*truebspz));
          upvars.add(RooArgSet(*truencpx,*truencpy,*truencpz,*truencpe));
          upvars.add(RooArgSet(*pBsTrue,*q2True,*mm2True,*thlTrue,*elcmTrue,*wTrue));
          upvars.add(RooArgSet(*gID,*DsMomID,*DsGMID,*muMomID,*helicity));
        }
        data->add(upvars);     
      } 
    }
  }

  // Fill for Ds0
  if(resonance == "Ds0"){
    for(int i = 0; i!=nentries; ++i){
      if (i%1000000 == 0) std::cout << "--- ... Processing event: " << i << std::endl;
      fChain->GetEntry(i);
      // apply the cuts to add only good data
      // remove mu_PT>1000
      if(Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS==1 && Bs_0_MCORR<8000 && Bs_0_MCORR>3000 && mu_PIDmu>0.0 && Ds_MM>1940 && Ds_MM<2000 && mu_iso_MinBDT_Long>-0.5 && Ds_0_40_pi0_mult>0 && sqrt(pow(Ds_0_40_pi0_maxPt_PX,2)+pow(Ds_0_40_pi0_maxPt_PY,2))>0 && abs(Ds_0_40_pi0_maxPt_MM-134.9766)<20 && Ds_0_40_g1_CL>0.6 && Ds_0_40_g2_CL>0.6){
        *fitMass = sqrt( pow((Ds_0_40_pi0_maxPt_PE+Ds_PE),2) - ( pow(Ds_0_40_pi0_maxPt_PX+Ds_PX,2)+pow(Ds_0_40_pi0_maxPt_PY+Ds_PY,2)+pow(Ds_0_40_pi0_maxPt_PZ+Ds_PZ,2) ) )-Ds_MM+1968.30;
        *triggerTOS = Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS;
        *kplp = Kpl_P;
        *kmip = Kmi_P;
        *pip = pi_P;
        *kplpt = Kpl_PT;
        *kmipt = Kmi_PT;
        *pipt = pi_PT;
        *dspt = Ds_PT;
//        *bsdoca = Bs_0_BDTS_DOCA;
        *bsfdchi2 = Bs_0_FDCHI2_TOPPV;
        *dsmm = Ds_MM;
        *bsmm = Bs_0_MM;
        *mcorr = Bs_0_MCORR;
        *Q2 = q2;
        *emu = Emu;
        *mupt = mu_PT;
        *mupidmu = mu_PIDmu;
        *muiso = mu_iso_MinBDT_Long;
        *ncmult = Ds_0_40_nc_mult;
        *ncpx = Ds_0_40_nc_maxPt_PX;
        *ncpy = Ds_0_40_nc_maxPt_PY;
        *ncpz = Ds_0_40_nc_maxPt_PZ;
        *ncpe = Ds_0_40_nc_maxPt_PE;
        *ncCL = Ds_0_40_nc_CL;
        *pi0mult = Ds_0_40_pi0_mult;
        *pi0px = Ds_0_40_pi0_maxPt_PX;
        *pi0py = Ds_0_40_pi0_maxPt_PY;
        *pi0pz = Ds_0_40_pi0_maxPt_PZ;
        *pi0mm = Ds_0_40_pi0_maxPt_MM;
        *pi0pe = Ds_0_40_pi0_maxPt_PE;
        *g1CL = Ds_0_40_g1_CL;
        *g2CL = Ds_0_40_g2_CL;
        *dspe = Ds_PE;
        *dspx = Ds_PX;
        *dspy = Ds_PY;
        *dspz = Ds_PZ;
        *bspe = Bs_0_PE;
        *bspx = Bs_0_PX;
        *bspy = Bs_0_PY;
        *bspz = Bs_0_PZ;
        *bsorigx = Bs_0_OWNPV_X;
        *bsorigy = Bs_0_OWNPV_Y;
        *bsorigz = Bs_0_OWNPV_Z;
        *bsendx = Bs_0_ENDVERTEX_X;
        *bsendy = Bs_0_ENDVERTEX_Y;
        *bsendz = Bs_0_ENDVERTEX_Z; 

        RooArgSet upvars(*fitMass, *triggerTOS, *kplp, *kmip, *pip, *kplpt, *kmipt, *pipt, *dspt);
        upvars.add(RooArgSet(*bsdoca,*bsfdchi2,*dsmm,*mcorr,*Q2,*emu,*mupt,*mupidmu,*muiso));
        upvars.add(RooArgSet(*ncmult,*ncpx,*ncpy,*ncpz,*ncpe,*ncCL));
        upvars.add(RooArgSet(*pi0mult,*pi0px,*pi0py,*pi0pz,*pi0mm,*pi0pe,*g1CL,*g2CL));
        upvars.add(RooArgSet(*dspe,*dspx,*dspy,*dspz));
        upvars.add(RooArgSet(*bspe,*bspx,*bspy,*bspz));
        upvars.add(RooArgSet(*bsmm));
        upvars.add(RooArgSet(*bsorigx,*bsorigy,*bsorigz,*bsendx,*bsendy,*bsendz));
        data->add(upvars);
      }
    }
  }

  data->Print("v");
  ws->import(*data); 
  
  delete data;
}

//____________________________________
void DoSPlot(RooWorkspace* ws, float nentries, TString resonance, TString sample){
  std::cout << "Calculate sWeights" << std::endl;

  // get what we need out of the workspace to do the fit
  RooAbsPdf* model = ws->pdf("model");
  RooRealVar* SigYield = ws->var("SigYield");
  RooRealVar* BkgYield = ws->var("BkgYield");
  RooDataSet* data = (RooDataSet*) ws->data("dataset");
 
  Double_t nen = data->sumEntries();
  std::cout << "The dataset has " << nen << " entries" << std::endl; 

  // fit the model to the data.
  model->fitTo(*data, Extended(true), SumW2Error(kTRUE), Minos(true), Strategy(2), Timer(kTRUE), NumCPU(4)); 
   
  std::cout << "The fit is done" << std::endl;
  // The sPlot technique requires that we fix the parameters
  // of the model that are not yields after doing the fit.
  RooRealVar* sig = ws->var("sigma");
  RooRealVar* masa = ws->var("mean");
  //RooRealVar* al1 = ws->var("alpha1");
  RooRealVar* al2 = ws->var("alpha2");
  //RooRealVar* N1 = ws->var("n1");
  RooRealVar* N2 = ws->var("n2");
  sig->setConstant();
  masa->setConstant();
  //al1->setConstant();
  al2->setConstant();
  //N1->setConstant();
  N2->setConstant();
  //RooRealVar* bkgc = ws->var("c");
  RooRealVar* bkga1 = ws->var("a1");
  RooRealVar* bkga2 = ws->var("a2");
  RooRealVar* bkga3 = ws->var("a3");
  //RooRealVar* thM = ws->var("thMass");
  //RooRealVar* thSig = ws->var("thSigma");
  //bkgc->setConstant();
  bkga1->setConstant();
  bkga2->setConstant();
  bkga3->setConstant();
  //thM->setConstant();
  //thSig->setConstant(); 
  RooMsgService::instance().setSilentMode(false);

  // Now we use the SPlot class to add SWeights to our data set
  // based on our model and our yield variables
  std::cout << "Start the splot" << std::endl;
  RooStats::SPlot* sData = new RooStats::SPlot("sData","An SPlot", *data, model, RooArgList(*SigYield,*BkgYield));

  // Check that our weights have the desired properties

  std::cout << "Check SWeights:" << std::endl;

  std::cout << "Yield of signal is " 
	    << SigYield->getVal() << ". From sWeights it is "
	    << sData->GetYieldFromSWeight("SigYield") << std::endl;

  std::cout << "Yield of background is " 
	    << BkgYield->getVal() << ". From sWeights it is "
	    << sData->GetYieldFromSWeight("BkgYield") << std::endl;

  for(Int_t i=0; i != 10; ++i)
    {
      std::cout << "sig Weight " << sData->GetSWeight(i,"SigYield") 
		<< ", bkg Weight " << sData->GetSWeight(i,"BkgYield") 
		<< ", Total Weight " << sData->GetSumOfEventSWeight(i) 
		<< std::endl;
    }

  std::cout << std::endl;

  // import this new dataset with sWeights
  std::cout << "import new dataset with sWeights" << std::endl;
  ws->import(*data, Rename("dataWithSWeights"));
  data->Print("v");

  // here will unraved the WS to write an ntuple with weights
  TFile *file = new TFile("DsMass_WithSWeighted_"+resonance+"_"+sample+"_NoCL_CB_Sim09b.root","RECREATE");
  TTree *finalTree = new TTree("DecayTree","tree with weights");
  
  Bool_t triggerTOS;
  Int_t muiso;
  Double_t kplp, kmip, pip, kplpt, kmipt, pipt, dspt;
  Double_t bsdoca, bsfdchi2, dsmm, bsmm, mcorr, Q2, emu, mupt, mupidmu;
  Double_t ncmult, ncpx, ncpy, ncpz, ncpe, ncCL;
  Double_t pi0mult, pi0px, pi0py, pi0pz, pi0mm, pi0pe, g1CL, g2CL;
  Double_t dspe, dspx, dspy, dspz;
  Double_t bspe, bspx, bspy, bspz;
  Double_t bsorigx, bsorigy, bsorigz, bsendx, bsendy, bsendz, bsvchi2;
  Double_t sigw, bkgw;
  Double_t pBsY, q2Y, mm2Y, thlY, elcmY, wY;
  Double_t pBsP1, q2P1, mm2P1,thlP1, elcmP1, wP1;
  Double_t pBsP2, q2P2, mm2P2,thlP2, elcmP2, wP2;
  Double_t pBsTrue, q2True, mm2True, thlTrue, elcmTrue, wTrue;
  Double_t MassDsG, aDsG;
  Double_t sq, rad; 
  Double_t McorrDsst, bSinFlightAng, bFlightLen;
  Int_t gID, DsMomID, DsGMID, muMomID;
  Int_t nLongT;
  Double_t helicity;

  finalTree->Branch("sigw",&sigw,"sigw/D");
  finalTree->Branch("bkgw",&bkgw,"bkgw/D");
  finalTree->Branch("MassDsG",&MassDsG,"MassDsG/D");
  finalTree->Branch("Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS", &triggerTOS, "Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS/B");
  finalTree->Branch("Kpl_P", &kplp, "Kpl_P/D");
  finalTree->Branch("Kmi_P", &kmip, "Kmi_P/D");
  finalTree->Branch("pi_P", &pip, "pi_P/D");
  finalTree->Branch("Kpl_PT", &kplpt, "Kpl_PT/D");
  finalTree->Branch("Kmi_PT", &kmipt, "Kmi_PT/D");
  finalTree->Branch("pi_PT", &pipt, "pi_PT/D");
  finalTree->Branch("Ds_PT", &dspt, "Ds_PT/D");
//  finalTree->Branch("Bs_0_BDTS_DOCA", &bsdoca, "Bs_0_BDTS_DOCA/D");
  finalTree->Branch("Bs_0_FDCHI2_TOPPV", &bsfdchi2, "Bs_0_FDCHI2_TOPPV/D");
  finalTree->Branch("Ds_MM", &dsmm, "Ds_MM/D");
  finalTree->Branch("Bs_MM", &bsmm, "Bs_MM/D");
  finalTree->Branch("Bs_0_MCORR", &mcorr, "Bs_0_MCORR/D");
  finalTree->Branch("q2", &Q2, "q2/D");
  finalTree->Branch("Emu", &emu, "Emu/D");
  finalTree->Branch("mu_PT", &mupt, "mu_PT/D");
  finalTree->Branch("mu_PIDmu", &mupidmu, "mu_PIDmu/D");
  finalTree->Branch("mu_iso_MinBDT_Long", &muiso, "mu_iso_MinBDT_Long/D");
  finalTree->Branch("Ds_0.40_nc_mult", &ncmult, "Ds_0.40_nc_mult/I");
  finalTree->Branch("Ds_0.40_nc_maxPt_PX", &ncpx, "Ds_0.40_nc_maxPt_PX/D");
  finalTree->Branch("Ds_0.40_nc_maxPt_PY", &ncpy, "Ds_0.40_nc_maxPt_PY/D");
  finalTree->Branch("Ds_0.40_nc_maxPt_PZ", &ncpz, "Ds_0.40_nc_maxPt_PZ/D");
  finalTree->Branch("Ds_0.40_nc_maxPt_PE", &ncpe, "Ds_0.40_nc_maxPt_PE/D");
  finalTree->Branch("Ds_0.40_nc_CL", &ncCL, "Ds_0.40_nc_CL/D");
  finalTree->Branch("Ds_0.40_pi0_mult", &pi0mult, "Ds_0.40_pi0_mult/I");
  finalTree->Branch("Ds_0.40_pi0_maxPt_PX", &pi0px, "Ds_0.40_pi0_maxPt_PX/D");
  finalTree->Branch("Ds_0.40_pi0_maxPt_PY", &pi0py, "Ds_0.40_pi0_maxPt_PY/D");
  finalTree->Branch("Ds_0.40_pi0_maxPt_PZ", &pi0pz, "Ds_0.40_pi0_maxPt_PZ/D");
  finalTree->Branch("Ds_0.40_pi0_maxPt_MM", &pi0mm, "Ds_0.40_pi0_maxPt_MM/D");
  finalTree->Branch("Ds_0.40_g1_CL", &g1CL, "Ds_0.40_g1_CL/D");
  finalTree->Branch("Ds_0.40_g2_CL", &g2CL, "Ds_0.40_g2_CL/D");
  finalTree->Branch("Ds_0.40_pi0_maxPt_PE", &pi0pe, "Ds_0.40_pi0_maxPt_PE/D");
  finalTree->Branch("Ds_PE", &dspe, "Ds_PE/D");
  finalTree->Branch("Ds_PX", &dspx, "Ds_PX/D");
  finalTree->Branch("Ds_PY", &dspy, "Ds_PY/D");
  finalTree->Branch("Ds_PZ", &dspz, "Ds_PZ/D");
  finalTree->Branch("Bs_PE", &bspe, "Bs_PE/D");
  finalTree->Branch("Bs_PX", &bspx, "Bs_PX/D");
  finalTree->Branch("Bs_PY", &bspy, "Bs_PY/D");
  finalTree->Branch("Bs_PZ", &bspz, "Bs_PZ/D");
  finalTree->Branch("Bs_ORIGX", &bsorigx, "Bs_ORIGX/D");
  finalTree->Branch("Bs_ORIGY", &bsorigy, "Bs_ORIGY/D");
  finalTree->Branch("Bs_ORIGZ", &bsorigz, "Bs_ORIGZ/D");
  finalTree->Branch("Bs_ENDX", &bsendx, "Bs_ENDX/D");
  finalTree->Branch("Bs_ENDY", &bsendy, "Bs_ENDY/D");
  finalTree->Branch("Bs_ENDZ", &bsendz, "Bs_ENDZ/D");
  finalTree->Branch("Bs_VCHI2", &bsvchi2, "Bs_VCHI2/D");
  finalTree->Branch("aDsG",&aDsG,"aDsG/D");
  finalTree->Branch("pBsY",&pBsY,"pBsY/D");
  finalTree->Branch("q2Y",&q2Y,"q2Y/D");
  finalTree->Branch("mm2Y",&mm2Y,"mm2Y/D");
  finalTree->Branch("thlY",&thlY,"thlY/D");
  finalTree->Branch("elcmY",&elcmY,"elcmY/D");
  finalTree->Branch("wY",&wY,"wY/D");
  finalTree->Branch("pBsP1",&pBsP1,"pBsP1/D");
  finalTree->Branch("q2P1",&q2P1,"q2P1/D");
  finalTree->Branch("mm2P1",&mm2P1,"mm2P1/D");
  finalTree->Branch("thlP1",&thlP1,"thlP1/D");
  finalTree->Branch("elcmP1",&elcmP1,"elcmP1/D");
  finalTree->Branch("wP1",&wP1,"wP1/D");
  finalTree->Branch("pBsP2",&pBsP2,"pBsP2/D");
  finalTree->Branch("q2P2",&q2P2,"q2P2/D");
  finalTree->Branch("mm2P2",&mm2P2,"mm2P2/D");
  finalTree->Branch("thlP2",&thlP2,"thlP2/D");
  finalTree->Branch("elcmP2",&elcmP2,"elcmP2/D");
  finalTree->Branch("wP2",&wP2,"wP2/D"); 
  finalTree->Branch("pBsTrue",&pBsTrue,"pBsTrue/D");
  finalTree->Branch("q2True",&q2True,"q2True/D");
  finalTree->Branch("mm2True",&mm2True,"mm2True/D");
  finalTree->Branch("thlTrue",&thlTrue,"thlTrue/D");
  finalTree->Branch("elcmTrue",&elcmTrue,"elcmTrue/D");
  finalTree->Branch("wTrue",&wTrue,"wTrue/D");
  finalTree->Branch("sq",&sq,"sq/D");
  finalTree->Branch("McorrDsst",&McorrDsst,"McorrDsst/D");
  finalTree->Branch("bSinFlightAng",&bSinFlightAng,"bSinFlightAng/D");
  finalTree->Branch("bFlightLen",&bFlightLen,"bFlightLen/D");
  finalTree->Branch("nLongT",&nLongT,"nLongT/I");
  finalTree->Branch("helicity",&helicity,"helicity/D");
  if(sample=="sigmu" || sample == "sigtau"){
    finalTree->Branch("gID",&gID,"gID/I");
    finalTree->Branch("DsMomID",&DsMomID,"DsMomID/I");
    finalTree->Branch("DsGMID",&DsGMID,"DsGMID/I");
    finalTree->Branch("muMomID",&muMomID,"muMomID/I");
  }
  for (int i = 0; i!=nen; ++i){
    const RooArgSet *Dset = data->get(i);  // get the row
    triggerTOS = Dset->getRealValue("triggerTOS");
    kplp = Dset->getRealValue("kplp");
    kmip = Dset->getRealValue("kmip");
    pip = Dset->getRealValue("pip");
    kplpt = Dset->getRealValue("kplpt");
    kmipt = Dset->getRealValue("kmipt");
    pipt = Dset->getRealValue("pipt");
    dspt = Dset->getRealValue("dspt");
    bsdoca = Dset->getRealValue("bsdoca");
    bsfdchi2 = Dset->getRealValue("bsfdchi2");
    dsmm = Dset->getRealValue("dsmm");
    bsmm = Dset->getRealValue("bsmm");
    mcorr = Dset->getRealValue("mcorr");
    Q2 = Dset->getRealValue("Q2");
    emu =  Dset->getRealValue("emu");
    mupt = Dset->getRealValue("mupt");
    mupidmu = Dset->getRealValue("mupidmu");
    muiso = Dset->getRealValue("muiso");
    ncmult = Dset->getRealValue("ncmult");
    ncpx = Dset->getRealValue("ncpx");
    ncpy = Dset->getRealValue("ncpy");
    ncpz = Dset->getRealValue("ncpz");
    ncpe = Dset->getRealValue("ncpe");
    ncCL = Dset->getRealValue("ncCL");
    pi0mult = Dset->getRealValue("pi0mult");
    pi0px = Dset->getRealValue("pi0px");
    pi0py = Dset->getRealValue("pi0py");
    pi0pz = Dset->getRealValue("pi0pz");
    pi0mm = Dset->getRealValue("pi0mm");
    pi0pe = Dset->getRealValue("pi0pe");
    g1CL = Dset->getRealValue("g1CL");
    g2CL = Dset->getRealValue("g2CL");
    dspe = Dset->getRealValue("dspe");
    dspx = Dset->getRealValue("dspx");
    dspy = Dset->getRealValue("dspy");
    dspz = Dset->getRealValue("dspz");
    bspe = Dset->getRealValue("bspe");
    bspx = Dset->getRealValue("bspx");
    bspy = Dset->getRealValue("bspy");
    bspz = Dset->getRealValue("bspz");
    bsorigx = Dset->getRealValue("bsorigx");
    bsorigy = Dset->getRealValue("bsorigy");
    bsorigz = Dset->getRealValue("bsorigz");
    bsendx = Dset->getRealValue("bsendx");
    bsendy = Dset->getRealValue("bsendy");
    bsendz = Dset->getRealValue("bsendz");
    bsvchi2 = Dset->getRealValue("bsvchi2");
    sigw = Dset->getRealValue("SigYield_sw");
    bkgw = Dset->getRealValue("BkgYield_sw");  
    MassDsG = Dset->getRealValue("MassDsG");
    aDsG = Dset->getRealValue("aDsG");
    pBsY = Dset->getRealValue("pBsY");
    q2Y = Dset->getRealValue("q2Y");
    mm2Y = Dset->getRealValue("mm2Y");
    thlY = Dset->getRealValue("thlY");
    elcmY = Dset->getRealValue("elcmY");
    wY = Dset->getRealValue("wY");
    pBsP1 = Dset->getRealValue("pBsP1");
    q2P1 = Dset->getRealValue("q2P1");
    mm2P1 = Dset->getRealValue("mm2P1");
    thlP1 = Dset->getRealValue("thlP1");
    elcmP1 = Dset->getRealValue("elcmP1");
    wP1 = Dset->getRealValue("wP1");
    pBsP2 = Dset->getRealValue("pBsP2");
    q2P2 = Dset->getRealValue("q2P2");
    mm2P2 = Dset->getRealValue("mm2P2");
    thlP2 = Dset->getRealValue("thlP2");
    elcmP2 = Dset->getRealValue("elcmP2");
    wP2 = Dset->getRealValue("wP2");
    pBsTrue = Dset->getRealValue("pBsTrue");
    q2True = Dset->getRealValue("q2True");
    mm2True = Dset->getRealValue("mm2True");
    thlTrue = Dset->getRealValue("thlTrue");
    elcmTrue = Dset->getRealValue("elcmTrue");
    wTrue = Dset->getRealValue("wTrue");
    sq = Dset->getRealValue("sq");
    McorrDsst = Dset->getRealValue("McorrDsst");
    bSinFlightAng = Dset->getRealValue("bSinFlightAng");
    bFlightLen = Dset->getRealValue("bFlightLen");   
    nLongT = Dset->getRealValue("nLongT");
    helicity = Dset->getRealValue("helicity");
    if(sample=="sigmu" || sample == "sigtau"){
      gID = Dset->getRealValue("gID");
      DsMomID = Dset->getRealValue("DsMomID");
      DsGMID = Dset->getRealValue("DsGMID");
      muMomID = Dset->getRealValue("muMomID");
    }
    finalTree->Fill();
  }
  finalTree->Write();
}

void MakePlots(RooWorkspace* ws, TString resonance, TString sample){

  // Here we make plots of the discriminating variable (mass) after the fit
  // and of the control variable (isolation) after unfolding with sPlot.
  std::cout << "make plots" << std::endl;

  // get what we need out of the workspace
  RooAbsPdf* model = ws->pdf("model");
  RooAbsPdf* SigModel = ws->pdf("sig");
  RooAbsPdf* BkgModel = ws->pdf("bkg");

  // get the variables
  RooRealVar* invMass = ws->var("resMass");
  RooRealVar* q2 = ws->var("Q2");
  RooRealVar* mcorr = ws->var("mcorr");
  RooRealVar* emu = ws->var("emu");
  RooRealVar* rad;
  RooRealVar* helicity;
  if(sample=="sigmu"){
    helicity = ws->var("helicity");
  }

  // note, we get the dataset with sWeights
  RooDataSet* data = (RooDataSet*) ws->data("dataWithSWeights");

  // this shouldn't be necessary, need to fix something with workspace
  // do this to set parameters back to their fitted values.
  model->fitTo(*data, Extended(true), SumW2Error(kTRUE), Minos(true), Strategy(2), Timer(kTRUE), NumCPU(4));
  // make our canvases and plot
  TCanvas* cdata1 = new TCanvas("sPlotMCORR","sPlot MCORR", 400, 400);
  cdata1->Divide(1,3);

  //plot invMass for data with full model and individual componenets overlayed
  cdata1->cd(1);
  RooPlot *frame_1;
  if(resonance=="Dsst"){
    frame_1 = invMass->frame(2050.,2220.,100); 
  }
  if(resonance=="Ds0"){
    frame_1 = invMass->frame(2050.,2600.,80);         
  }
  data->plotOn(frame_1,MarkerStyle(1)) ; 
  model->plotOn(frame_1,LineColor(kBlue),LineWidth(1));//,NormRange("FitRange")) ;   
  model->plotOn(frame_1,Components(*SigModel),LineStyle(kDashed),LineColor(kRed)) ;   
  model->plotOn(frame_1,Components(*BkgModel),LineStyle(kDashed),LineColor(kGreen)) ;   
  frame_1->SetTitle("Fit of model to discriminating variable");
  frame_1->Draw() ;
  std::cout << "drawn" << std::endl;  
  // Plot Ds_MM for signal component.  
  // Do this by plotting all events weighted by the sWeight for the signal component.
  // The SPlot class adds a new variable that has the name of the corresponding
  // yield + "_sw".
  cdata1->cd(2);
  RooDataSet *dataw_sig_1 = new RooDataSet(data->GetName(),data->GetTitle(),data,*data->get(),0,"SigYield_sw") ;
  std::cout << "-1" << std::endl;
  RooPlot* frame2_1;
  std::cout << "0" << std::endl;
  if(sample=="sigmu"){
    frame2_1 = helicity->frame(-1.,1.,100);
  }
  else {
    frame2_1 = mcorr->frame(3000.,8000.,80);
  }
  std::cout << "1" << std::endl;
  dataw_sig_1->plotOn(frame2_1, DataError(RooAbsData::SumW2), MarkerStyle(1) ) ; 
  frame2_1->SetTitle("Corrected mass distribution for signal");
  frame2_1->Draw() ;

  // Plot Ds_MM for backgournd component.  
  // Eg. plot all events weighted by the sWeight for the background component.
  // The SPlot class adds a new variable that has the name of the corresponding
  // yield + "_sw".
  cdata1->cd(3);
  RooDataSet *dataw_bkg_1 = new RooDataSet(data->GetName(),data->GetTitle(),data,*data->get(),0,"BkgYield_sw") ;
  RooPlot* frame3_1;
  if(sample=="sigmu"){
    frame3_1 = helicity->frame(-1.,1.,100);
  }
  else {
    frame3_1 = mcorr->frame(3000.,8000.,80);
  }
  dataw_bkg_1->plotOn(frame3_1,DataError(RooAbsData::SumW2), MarkerStyle(1) ) ; 
  frame3_1->SetTitle("Corrected mass distribution for background");
  frame3_1->Draw() ;
  cdata1->SaveAs("SPlot_MCORR_"+resonance+"_"+sample+".pdf");

  if(sample!="sigmu"){
  // Q2
  TCanvas* cdata2 = new TCanvas("sPlotQ2","sPlot Q2", 400, 400);
  cdata2->Divide(1,3);
  cdata2->cd(1);
  RooPlot *frame_2;
  if(resonance=="Dsst"){
    frame_2 = invMass->frame(2050.,2220.,80);
  }
  if(resonance=="Ds0"){
    frame_2 = invMass->frame(2050.,2600.,80);
  } 
  data->plotOn(frame_2,MarkerStyle(1)) ;
  model->plotOn(frame_2,LineColor(kBlue),LineWidth(1));//,NormRange("FitRange")) ;   
  model->plotOn(frame_2,Components(*SigModel),LineStyle(kDashed),LineColor(kRed)) ;
  model->plotOn(frame_2,Components(*BkgModel),LineStyle(kDashed),LineColor(kGreen)) ;
  frame_2->SetTitle("Fit of model to discriminating variable");
  frame_2->Draw() ;
 
  cdata2->cd(2);
  RooDataSet *dataw_sig_2 = new RooDataSet(data->GetName(),data->GetTitle(),data,*data->get(),0,"SigYield_sw") ;
  RooPlot* frame2_2 = q2->frame(0.,14000000.,80);
  dataw_sig_2->plotOn(frame2_2, DataError(RooAbsData::SumW2), MarkerStyle(1) ) ;
  frame2_2->SetTitle("Q2 distribution for signal");
  frame2_2->Draw() ; 

  cdata2->cd(3);
  RooDataSet *dataw_bkg_2 = new RooDataSet(data->GetName(),data->GetTitle(),data,*data->get(),0,"BkgYield_sw") ;
  RooPlot* frame3_2 = q2->frame(0.,14000000.,80);
  dataw_bkg_2->plotOn(frame3_2,DataError(RooAbsData::SumW2), MarkerStyle(1) ) ;
  frame3_2->SetTitle("Q2 distribution for background");
  frame3_2->Draw() ;
  cdata2->SaveAs("SPlot_Q2_"+resonance+"_"+sample+".pdf"); 
 
  // Emu

  TCanvas* cdata3 = new TCanvas("sPlotEmu","sPlot Emu", 400, 400);
  cdata3->Divide(1,3);  
  cdata3->cd(1);
  RooPlot *frame_3;
  if(resonance=="Dsst"){
    frame_3 = invMass->frame(2050.,2220.,80);
  }
  if(resonance=="Ds0"){
    frame_3 = invMass->frame(2050.,2600.,80);
  }  
  data->plotOn(frame_3,MarkerStyle(1)) ;
  model->plotOn(frame_3,LineColor(kBlue),LineWidth(1));//,NormRange("FitRange")) ;   
  model->plotOn(frame_3,Components(*SigModel),LineStyle(kDashed),LineColor(kRed)) ;
  model->plotOn(frame_3,Components(*BkgModel),LineStyle(kDashed),LineColor(kGreen)) ;
  frame_3->SetTitle("Fit of model to discriminating variable");
  frame_3->Draw() ;

  cdata3->cd(2);
  RooDataSet *dataw_sig_3 = new RooDataSet(data->GetName(),data->GetTitle(),data,*data->get(),0,"SigYield_sw") ;
  RooPlot* frame2_3 = emu->frame(0.,4000.,80);
  dataw_sig_3->plotOn(frame2_3, DataError(RooAbsData::SumW2), MarkerStyle(1) ) ;
  frame2_3->SetTitle("Muon energy distribution for signal");
  frame2_3->Draw() ;

  cdata3->cd(3);
  RooDataSet *dataw_bkg_3 = new RooDataSet(data->GetName(),data->GetTitle(),data,*data->get(),0,"BkgYield_sw") ;
  RooPlot* frame3_3 = emu->frame(0.,4000.,80);
  dataw_bkg_3->plotOn(frame3_3,DataError(RooAbsData::SumW2), MarkerStyle(1) ) ;
  frame3_3->SetTitle("Muon energy distribution for background");
  frame3_3->Draw() ;
  cdata3->SaveAs("SPlot_Emu_"+resonance+"_"+sample+".pdf");
  } 
  delete cdata1;
  //delete cdata2;
  //delete cdata3;

}

float getEntries(TString sample){
  int nentries;
  TChain *fChain;
  if (sample == "data"){
    fChain = new TChain("B2DsMuNuTuple/DecayTree");
    fChain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/s/sogilvy/RDs/WithVetoes/TupleRDS_DataDown_allNeutrals_iso.root");
    fChain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/s/sogilvy/RDs/WithVetoes/TupleRDS_DataUp_allNeutrals_iso.root");
  } else if (sample == "SS"){
    fChain = new TChain("B2DsMuNuSSTuple/DecayTree");
    fChain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/s/sogilvy/RDs/WithVetoes/TupleRDS_DataDown_allNeutrals_iso.root");
    fChain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/s/sogilvy/RDs/WithVetoes/TupleRDS_DataUp_allNeutrals_iso.root");
  } else if (sample == "BdDD"){
    fChain = new TChain("B2DsMuNuTuple/DecayTree");    
    fChain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/WithVetoes/TupleRDS_Sim09b_BdDstDs.root");
  } else if (sample == "BuDD"){
    fChain = new TChain("B2DsMuNuTuple/DecayTree");
    fChain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/WithVetoes/TupleRDS_Sim09b_BuD0Ds.root");
  } else if (sample == "BsDD"){
    fChain = new TChain("B2DsMuNuTuple/DecayTree");
    fChain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/WithVetoes/TupleRDS_Sim09b_BsDsDs.root");
  } else if (sample == "LbDD"){
    fChain = new TChain("B2DsMuNuTuple/DecayTree");
    fChain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/WithVetoes/TupleRDS_Sim09b_LbLcDs.root");
  } else if (sample == "sigmu"){
    fChain = new TChain("B2DsMuNuTuple/DecayTree");
    fChain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/WithVetoes/TupleRDS_Sim09b_DsMuNu.root");
  } else if (sample == "sigtau"){
    fChain = new TChain("B2DsMuNuTuple/DecayTree");
    fChain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/WithVetoes/TupleRDS_Sim09b_DsTauNu.root");
  }

  nentries = fChain->GetEntries();
  std::cout << "Total number of entries is = " << nentries << std::endl;
  delete fChain;
  return nentries;
}

void ComputeBMom2Fold(Double_t bMass, TLorentzVector b4V,
                      TVector3 bDir, Double_t & pL,
                      Double_t & pH, Double_t & det){
      // -----------------------------------------------------------------------------
      // Inputs:
      //    bMass: PDG mass of the Hadron 
      //    b4V: 4-momentum visible of the H, for H-->Cmunu, it is P(C)+P(mu)
      //    bDir: vector of the H direction, from vertex informations: H3-PV3
      // Output: 
      //    pH, pL: High and Low solution of the equation aaa*P^2 + bbb*P + ccc = 0
      //    det: value of bbb^2-4aaa*ccc
      //         if det < 0, solutions are not real, both are set to -bbb/2aaa
      // -----------------------------------------------------------------------------
      TVector3 b3V = b4V.Vect(); // 3-mom of the b-hadron
      Double_t ang=bDir.Angle(b3V);

      Double_t aaa = 4*(-pow(b4V.E(),2) + pow(b4V.P()*cos(ang),2));
      Double_t bbb = 4*b4V.P()*cos(ang)*( pow(bMass,2) + b4V.Mag2() );
      Double_t ccc = -4*pow(b4V.E(),2)*pow(b4V.P(),2) + pow(pow(bMass,2)-b4V.Mag2()-2*pow(b4V.P(),2),2);
      det=pow(bbb,2)-4*aaa*ccc;
      pH = -bbb/(2*aaa);
      pL = -bbb/(2*aaa);
      if( det>0 ){
          pL=(-bbb+sqrt(det))/(2*aaa);
          pH=(-bbb-sqrt(det))/(2*aaa);
      }
    return;
}
/*
Double_t hel( TLorentzVector M, TLorentzVector A1, TLorentzVector A2, TLorentzVector B ){
// ------------------------------------------
// Compute the helicity angle of the A meson
// M --> A B
//       A --> A1 A2
// ------------------------------------------      
      B.Boost(-M.BoostVector());
      A1.Boost(-M.BoostVector());
      A2.Boost(-M.BoostVector());

      TLorentzVector A=A1+A2;
      A1.Boost(-A.BoostVector());
      B.Boost(-A.BoostVector());

      TVector3 A1v3=A1.Vect();
      TVector3 Bv3=B.Vect();
      return (A1v3.Dot(Bv3))/(A1v3.Mag()*Bv3.Mag());
}

Double_t hel( TLorentzVector M, TLorentzVector A, TLorentzVector B ){
// ------------------------------------------
// Compute the helicity angle of the A meson
// M --> A B
//       A --> A1 A2
// ------------------------------------------      
      B.Boost(-M.BoostVector());
      A.Boost(-M.BoostVector());

      B.Boost(-A.BoostVector());

      TVector3 A1v3=A1.Vect();
      TVector3 Bv3=B.Vect();
      return (A1v3.Dot(Bv3))/(A1v3.Mag()*Bv3.Mag());
}
*/
