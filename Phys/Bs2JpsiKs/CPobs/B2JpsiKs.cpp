// #############################################################################
// Phys/Bs2JpsiKs Package
// Decay Specific Functions
// Authors: Patrick Koppenburg & Kristof De Bruyn
// #############################################################################


// #############################################################################
// *** Load Useful Classes ***
#define B2JpsiKs_cxx
#include "B2JpsiKs.h"

// #############################################################################
// *** Initialize ***
void B2JpsiKs::defineConstants(const TString step, const unsigned int track) {

  // Selection Cuts
  DTF_chi2 = 72; // NDOF: 8
  MMERR_cut = 30;

  // Map of Variables for Multivariate Selection
  (*mvaVars)["dtfc"] = (step==m_NNKstar ? -1 :
                       (step==m_NNUnbiased && track==m_LL ?  0 : 
                       (step==m_NNUnbiased && track==m_DD ?       0 :  0)));
  (*mvaVars)["otcl"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ?  1 : 
                       (step==m_NNUnbiased && track==m_DD ?       1 :  1)));
  (*mvaVars)["prim"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ?  2 : 
                       (step==m_NNUnbiased && track==m_DD ?       2 :  2)));
  (*mvaVars)["spdm"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ?  3 : 
                       (step==m_NNUnbiased && track==m_DD ?       3 :  3))); 
  (*mvaVars)["b0me"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ?  4 : 
                       (step==m_NNUnbiased && track==m_DD ?       4 :  4)));
  (*mvaVars)["b0pt"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ?  5 : 
                       (step==m_NNUnbiased && track==m_DD ?       5 :  5)));
  (*mvaVars)["bch2"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ?  6 : 
                       (step==m_NNUnbiased && track==m_DD ?       6 :  6)));
  (*mvaVars)["bmom"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ?  7 : 
                       (step==m_NNUnbiased && track==m_DD ?       7 :  7)));
  (*mvaVars)["dira"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ? -1 : 
                       (step==m_NNUnbiased && track==m_DD ?      -1 :  8)));
  (*mvaVars)["jchi"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ?  8 : 
                       (step==m_NNUnbiased && track==m_DD ?       8 :  9)));
  (*mvaVars)["jipc"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ? -1 : 
                       (step==m_NNUnbiased && track==m_DD ?      -1 : 10)));
  (*mvaVars)["jmas"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ?  9 : 
                       (step==m_NNUnbiased && track==m_DD ?       9 : 11)));
  (*mvaVars)["jmme"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ? 10 : 
                       (step==m_NNUnbiased && track==m_DD ?      10 : 12)));
  (*mvaVars)["jmom"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ? -1 : 
                       (step==m_NNUnbiased && track==m_DD ?      -1 : 13)));
  (*mvaVars)["jppt"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ? 11 : 
                       (step==m_NNUnbiased && track==m_DD ?      11 : 14)));
  (*mvaVars)["kipc"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ? -1 : 
                       (step==m_NNUnbiased && track==m_DD ?      -1 : 15)));
  (*mvaVars)["ksch"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ? -1 : 
                       (step==m_NNUnbiased && track==m_DD ?      -1 : 16)));
  (*mvaVars)["ksez"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ? 12 : 
                       (step==m_NNUnbiased && track==m_DD ?      12 : 17)));
  (*mvaVars)["ksfd"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ? -1 : 
                       (step==m_NNUnbiased && track==m_DD ?      -1 : 18)));
  (*mvaVars)["ksme"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ? 13 : 
                       (step==m_NNUnbiased && track==m_DD ?      13 : 19)));
  (*mvaVars)["ksmm"] = (step==m_NNKstar ?  2 : 
                       (step==m_NNUnbiased && track==m_LL ? 14 : 
                       (step==m_NNUnbiased && track==m_DD ?      14 : 20)));
  (*mvaVars)["ksmo"] = (step==m_NNKstar ?  4 : 
                       (step==m_NNUnbiased && track==m_LL ? -1 : 
                       (step==m_NNUnbiased && track==m_DD ?      -1 : 21)));
  (*mvaVars)["kspt"] = (step==m_NNKstar ?  3 : 
                       (step==m_NNUnbiased && track==m_LL ? 15 : 
                       (step==m_NNUnbiased && track==m_DD ?      15 : 22)));
  (*mvaVars)["ksta"] = (step==m_NNKstar ?  0 : 
                       (step==m_NNUnbiased && track==m_LL ? 16 : 
                       (step==m_NNUnbiased && track==m_DD ?      16 : 23)));
  (*mvaVars)["muic"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ? -1 : 
                       (step==m_NNUnbiased && track==m_DD ?      -1 : 24)));
  (*mvaVars)["muid"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ? 17 : 
                       (step==m_NNUnbiased && track==m_DD ?      17 : 25)));
  (*mvaVars)["muip"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ? -1 : 
                       (step==m_NNUnbiased && track==m_DD ?      -1 : 26)));
  (*mvaVars)["mumo"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ? -1 : 
                       (step==m_NNUnbiased && track==m_DD ?      -1 : 27)));
  (*mvaVars)["mupt"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ? 18 : 
                       (step==m_NNUnbiased && track==m_DD ?      18 : 28)));
  (*mvaVars)["mutk"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ? 19 : 
                       (step==m_NNUnbiased && track==m_DD ?      19 : 29)));
  (*mvaVars)["pidk"] = (step==m_NNKstar ?  1 : 
                       (step==m_NNUnbiased && track==m_LL ? -1 : 
                       (step==m_NNUnbiased && track==m_DD ?      -1 : 30)));
  (*mvaVars)["pigp"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ? 20 : 
                       (step==m_NNUnbiased && track==m_DD ?      20 : 31)));
  (*mvaVars)["piic"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ? -1 : 
                       (step==m_NNUnbiased && track==m_DD ?      -1 : 32)));
  (*mvaVars)["piip"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ? -1 : 
                       (step==m_NNUnbiased && track==m_DD ?      -1 : 33)));
  (*mvaVars)["pimo"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ? -1 : 
                       (step==m_NNUnbiased && track==m_DD ?      -1 : 34)));
  (*mvaVars)["pipt"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ? 21 : 
                       (step==m_NNUnbiased && track==m_DD ?      21 : 35)));
  (*mvaVars)["pitk"] = (step==m_NNKstar ? -1 : 
                       (step==m_NNUnbiased && track==m_LL ? 22 : 
                       (step==m_NNUnbiased && track==m_DD ?      22 : 36)));

  // Number of Variables defined here = highest number + 1 (start from 0)
  nvar = (step==m_NNKstar ? 5 :
         (step==m_NNUnbiased && track==m_LL ? 23 :
         (step==m_NNUnbiased && track==m_DD ?      23 : 37)));
}


// #############################################################################
// *** Accessors ***
int B2JpsiKs::TrackType() { return piplus_TRACK_Type; }
double B2JpsiKs::sideband_low_min() { return 5180; }
double B2JpsiKs::sideband_high_min() { return 5400; }
double B2JpsiKs::sideband_high_max(const TString data) {
  return (data==m_IncJpsi ? 5440 : 5520);
}


// #############################################################################
// *** Selection Cuts ***

// Decay Specific
bool B2JpsiKs::applyDecayCuts(const unsigned int pv) {
  bool pass = (TMath::Abs(KS0_M_with_pplus_piplus-1116)>2*piplus_TRACK_Type && 
               TMath::Abs(KS0_M_with_piplus_pplus-1116)>2*piplus_TRACK_Type &&
               piminus_ProbNNk>0 && piplus_ProbNNk>0 &&
               ((piplus_TRACK_Type==m_LL &&
                B0_FitDaughtersPVConst_KS0_ctau[pv]<30 &&
                B0_FitDaughtersPVConst_KS0_ctau[pv]>-5)
                || piplus_TRACK_Type==m_DD)
              );
  return pass;
};


// Monte Carlo Truth
bool B2JpsiKs::MCTruth(const TString what) {
  bool pass = false;
  if(what==m_SigBd || what==m_SigBdPrescaled) {
    pass = (TMath::Abs(B0_TRUEID)==511 && J_psi_1S_TRUEID==443 &&
            KS0_TRUEID==310 && (B0_BKGCAT==0 || B0_BKGCAT==10));
  } else if(what==m_SigBs || what==m_SigBsPrescaled) {
    pass = (TMath::Abs(B0_TRUEID)==531 && J_psi_1S_TRUEID==443 &&
            KS0_TRUEID==310 && B0_BKGCAT==20);
  } else if(what==m_SigKstar || what==m_SigKstarWM) {
    pass = (TMath::Abs(B0_TRUEID)==511 && J_psi_1S_TRUEID==443 &&
            TMath::Abs(KS0_TRUEID)==313 && B0_BKGCAT==30);
  }
  return pass ;
};

// Mass regions
bool B2JpsiKs::teachingRegion(unsigned int pv) { 
  return (mass(pv) < BsBox_min || mass(pv) > BsBox_max);
}

// #############################################################################
// *** Teacher ***
void B2JpsiKs::prepareNBArray(float* InputArray, const unsigned int pv,
                            const TString step, const unsigned int tracktype) {

  defineConstants(step, tracktype);
  if (firstFill) {
    std::cout << "\n  Filling Array for tracktype: " << tracktype << std::endl;
  }

  // *** Array for NeuroBayes ***
  fillNBArray("dtfc", pv, InputArray);
  fillNBArray("otcl", pv, InputArray);
  fillNBArray("prim", pv, InputArray);
  fillNBArray("spdm", pv, InputArray);
  fillNBArray("b0me", pv, InputArray);
  fillNBArray("b0pt", pv, InputArray);
  fillNBArray("bch2", pv, InputArray);
  fillNBArray("bmom", pv, InputArray);
  fillNBArray("dira", pv, InputArray);
  fillNBArray("jchi", pv, InputArray);
  fillNBArray("jipc", pv, InputArray);
  fillNBArray("jmas", pv, InputArray);
  fillNBArray("jmme", pv, InputArray);
  fillNBArray("jmom", pv, InputArray);
  fillNBArray("jppt", pv, InputArray);
  fillNBArray("kipc", pv, InputArray);
  fillNBArray("ksch", pv, InputArray);
  fillNBArray("ksez", pv, InputArray);
  fillNBArray("ksfd", pv, InputArray);
  fillNBArray("ksme", pv, InputArray);
  fillNBArray("ksmm", pv, InputArray);
  fillNBArray("ksmo", pv, InputArray);
  fillNBArray("kspt", pv, InputArray);
  fillNBArray("ksta", pv, InputArray);
  fillNBArray("muic", pv, InputArray);
  fillNBArray("muid", pv, InputArray);
  fillNBArray("muip", pv, InputArray);
  fillNBArray("mumo", pv, InputArray);
  fillNBArray("mupt", pv, InputArray);
  fillNBArray("mutk", pv, InputArray);
  fillNBArray("pidk", pv, InputArray);
  fillNBArray("pigp", pv, InputArray);
  fillNBArray("piic", pv, InputArray);
  fillNBArray("piip", pv, InputArray);
  fillNBArray("pimo", pv, InputArray);
  fillNBArray("pipt", pv, InputArray);
  fillNBArray("pitk", pv, InputArray);

  if (firstFill) std::cout << std::endl;
  firstFill = false ;
}

// #############################################################################
void B2JpsiKs::fillNBArray(const TString ID, const unsigned int pv,
                           float* InputArray) {
  int varID = (mvaVars->find(ID)->second);
  if (varID>=0) {
    TString name = "";
    float value = -999.;
    fillVar(ID, pv, name, value);

    InputArray[varID] = value;
    if (firstFill) {
      std::cout << "Filling variable ``" << ID << "'' ID =  " << varID
      << " (NB: " << varID+2 << ", page " << varID+5 << "), Name = " << name
      << ", Val = " << value << std::endl;
    }
  } else {
    if (firstFill) {
      std::cout << "Ignoring variable ``" << ID << "''" << std::endl;
    }
  }    
}

// #############################################################################
void B2JpsiKs::fillVar(const TString ID, const unsigned int pv,
                       TString& varName, float& varVal) {
  if (ID=="dtfc") {
    varName = "dtfc := B0_FitDaughtersPVConst_chi2[0]";
    varVal  = (float) B0_FitDaughtersPVConst_chi2[pv];
  } else if (ID=="otcl") {
    varName = "otcl := nOTClusters";
    varVal  = (float) nOTClusters;
  } else if (ID=="prim") {
    varName = "prim := B0_FitDaughtersPVConst_nPV";
    varVal  = (float) B0_FitDaughtersPVConst_nPV;
  } else if (ID=="spdm") {
    varName = "spdm := nSPDHits";
    varVal  = (float) nSPDHits;

  } else if (ID=="b0me") {
    varName = "b0me := B0_FitDaughtersPVConst_MERR[0]";
    varVal  = (float) B0_FitDaughtersPVConst_MERR[pv];
  } else if (ID=="b0pt") {
    varName = "b0pt := B0_FitDaughtersPVConst_PT[0]";
    varVal  = (float) B0_FitDaughtersPVConst_PT[pv];
  } else if (ID=="bch2") {
    varName = "bch2 := B0_ENDVERTEX_CHI2/B0_ENDVERTEX_NDOF";
    varVal  = (float) B0_ENDVERTEX_CHI2/B0_ENDVERTEX_NDOF;
  } else if (ID=="bmom") {
    varName = "bmom := B0_FitDaughtersPVConst_P[0]";
    varVal  = (float) B0_FitDaughtersPVConst_P[pv];
  } else if (ID=="dira") {
    varName = "dira := TMath::ACos(B0_AllDIRA[0])";
    varVal  = (float) TMath::ACos(B0_AllDIRA[pv]);

  } else if (ID=="jchi") {
    varName = "jchi := J_psi_1S_ENDVERTEX_CHI2";
    varVal  = (float) J_psi_1S_ENDVERTEX_CHI2;
  } else if (ID=="jipc") {
    varName = "jipc := B0_FitDaughtersPVConst_J_psi_1S_IPCHI2[0]";
    varVal  = (float) B0_FitDaughtersPVConst_J_psi_1S_IPCHI2[pv];
  } else if (ID=="jmas") {
    char buffer[10];
    std::sprintf(buffer, "%f)", m_JpsiFittedMass);
    varName = "jmas := TMath::Abs(B0_FitPVConst_J_psi_1S_M[0]-";
    varName.Append(buffer);
    varVal  = (float) TMath::Abs(B0_FitPVConst_J_psi_1S_M[pv]-m_JpsiFittedMass);
  } else if (ID=="jmme") {
    varName = "jmme := B0_FitPVConst_J_psi_1S_MERR[0]";
    varVal  = (float) B0_FitPVConst_J_psi_1S_MERR[pv];
  } else if (ID=="jmom") {
    varName = "jmom := B0_FitDaughtersPVConst_J_psi_1S_P[0]";
    varVal  = (float) B0_FitDaughtersPVConst_J_psi_1S_P[pv];
  } else if (ID=="jppt") {
    varName = "jppt := B0_FitDaughtersPVConst_J_psi_1S_PT[0]";
    varVal  = (float) B0_FitDaughtersPVConst_J_psi_1S_PT[pv];

  } else if (ID=="kipc") {
    varName = "kipc := B0_FitDaughtersPVConst_KS0_IPCHI2[0]";
    varVal  = (float) B0_FitDaughtersPVConst_KS0_IPCHI2[pv];
  } else if (ID=="ksch") {
    varName = "ksch := KS0_ENDVERTEX_CHI2";
    varVal  = (float) KS0_ENDVERTEX_CHI2;
  } else if (ID=="ksez") {
    varName = "ksez := KS0_ENDVERTEX_Z";
    varVal  = (float) KS0_ENDVERTEX_Z;
  } else if (ID=="ksfd") {
    varName = "ksfd := B0_FitDaughtersPVConst_KS0_ctau[0]/B0_FitDaughtersPVConst_KS0_ctauErr[0]";
    varVal  = (float) B0_FitDaughtersPVConst_KS0_ctau[pv]/B0_FitDaughtersPVConst_KS0_ctauErr[pv];
  } else if (ID=="ksme") {
    varName = "ksme := B0_FitPVConst_KS0_MERR[0]";
    varVal  = (float) B0_FitPVConst_KS0_MERR[pv];
  } else if (ID=="ksmm") {
    char buffer[10];
    std::sprintf(buffer, "%f)", m_Kzero);
    varName = "ksmm := TMath::Abs(B0_FitPVConst_KS0_M[0]-";
    varName.Append(buffer);
    varVal  = (float) TMath::Abs(B0_FitPVConst_KS0_M[pv]-m_Kzero);
  } else if (ID=="ksmo") {
    varName = "ksmo := B0_FitDaughtersPVConst_KS0_P[0]";
    varVal  = (float) B0_FitDaughtersPVConst_KS0_P[pv];
  } else if (ID=="kspt") {
    varName = "kspt := B0_FitDaughtersPVConst_KS0_PT[0]";
    varVal  = (float) B0_FitDaughtersPVConst_KS0_PT[pv];
  } else if (ID=="ksta") {
    varName = "ksta := B0_FitDaughtersPVConst_KS0_ctau[0]";
    varVal  = (float) B0_FitDaughtersPVConst_KS0_ctau[pv];

  } else if (ID=="muic") {
    varName = "muic := TMath::Min(B0_FitDaughtersPVConst_J_psi_1S_P0_IPCHI2[0], B0_FitDaughtersPVConst_J_psi_1S_P1_IPCHI2[0])";
    varVal  = (float) TMath::Min(B0_FitDaughtersPVConst_J_psi_1S_P0_IPCHI2[pv], B0_FitDaughtersPVConst_J_psi_1S_P1_IPCHI2[pv]);
  } else if (ID=="muid") {
    varName = "muid := TMath::Min(muminus_PIDmu, muplus_PIDmu)";
    varVal  = (float) TMath::Min(muminus_PIDmu, muplus_PIDmu);
  } else if (ID=="muip") {
    varName = "muip := TMath::Min(B0_FitDaughtersPVConst_J_psi_1S_P0_IP[0], B0_FitDaughtersPVConst_J_psi_1S_P1_IP[0])";
    varVal  = (float) TMath::Min(B0_FitDaughtersPVConst_J_psi_1S_P0_IP[pv], B0_FitDaughtersPVConst_J_psi_1S_P1_IP[pv]);
  } else if (ID=="mumo") {
    varName = "mumo := TMath::Min(B0_FitDaughtersPVConst_J_psi_1S_P0_P[0], B0_FitDaughtersPVConst_J_psi_1S_P1_P[0])";
    varVal  = (float) TMath::Min(B0_FitDaughtersPVConst_J_psi_1S_P0_P[pv], B0_FitDaughtersPVConst_J_psi_1S_P1_P[pv]);
  } else if (ID=="mupt") {
    varName = "mupt := TMath::Min(B0_FitDaughtersPVConst_J_psi_1S_P0_PT[0], B0_FitDaughtersPVConst_J_psi_1S_P1_PT[0])";
    varVal  = (float) TMath::Min(B0_FitDaughtersPVConst_J_psi_1S_P0_PT[pv], B0_FitDaughtersPVConst_J_psi_1S_P1_PT[pv]);
  } else if (ID=="mutk") {
    varName = "mutk := TMath::Max(muminus_TRACK_CHI2NDOF, muplus_TRACK_CHI2NDOF)";
    varVal  = (float) TMath::Max(muminus_TRACK_CHI2NDOF, muplus_TRACK_CHI2NDOF);

  } else if (ID=="pidk") {
    varName = "pidk := TMath::Max(piminus_ProbNNk, piplus_ProbNNk)";
    varVal  = (float) TMath::Max(piminus_ProbNNk, piplus_ProbNNk);
  } else if (ID=="pigp") {
    varName = "pigp := TMath::Max(piminus_TRACK_GhostProb, piplus_TRACK_GhostProb)";
    varVal  = (float) TMath::Max(piminus_TRACK_GhostProb, piplus_TRACK_GhostProb);
  } else if (ID=="piic") {
    varName = "piic := TMath::Min(B0_FitDaughtersPVConst_KS0_P0_IPCHI2[0], B0_FitDaughtersPVConst_KS0_P1_IPCHI2[0])";
    varVal  = (float) TMath::Min(B0_FitDaughtersPVConst_KS0_P0_IPCHI2[pv], B0_FitDaughtersPVConst_KS0_P1_IPCHI2[pv]);
  } else if (ID=="piip") {
    varName = "piip := TMath::Min(B0_FitDaughtersPVConst_KS0_P0_IP[0], B0_FitDaughtersPVConst_KS0_P1_IP[0])";
    varVal  = (float) TMath::Min(B0_FitDaughtersPVConst_KS0_P0_IP[pv], B0_FitDaughtersPVConst_KS0_P1_IP[pv]);
  } else if (ID=="pimo") {
    varName = "pimo := TMath::Min(B0_FitDaughtersPVConst_KS0_P0_P[0], B0_FitDaughtersPVConst_KS0_P1_P[0])";
    varVal  = (float) TMath::Min(B0_FitDaughtersPVConst_KS0_P0_P[pv], B0_FitDaughtersPVConst_KS0_P1_P[pv]);
  } else if (ID=="pipt") {
    varName = "pipt := TMath::Min(B0_FitDaughtersPVConst_KS0_P0_PT[0], B0_FitDaughtersPVConst_KS0_P1_PT[0])";
    varVal  = (float) TMath::Min(B0_FitDaughtersPVConst_KS0_P0_PT[pv], B0_FitDaughtersPVConst_KS0_P1_PT[pv]);
  } else if (ID=="pitk") {
    varName = "pitk := TMath::Max(piminus_TRACK_CHI2NDOF, piplus_TRACK_CHI2NDOF)";
    varVal  = (float) TMath::Max(piminus_TRACK_CHI2NDOF, piplus_TRACK_CHI2NDOF);
  }
}

// #############################################################################
unsigned int B2JpsiKs::individualPreproFlag(unsigned int i, 
                                 const unsigned int track, const TString step) {
// flag = ij
// i = 1: mean target, flatten the distribution, no delta-function
// j = 4: Regular fit
// j = 5: Monotonous fit
// j = 8: Discrete, unordered class

  // Discrete observables
  if (i==(mvaVars->find("prim")->second)) return 18;
  // Not Monotonous observables
  else if (i==(mvaVars->find("bmom")->second) ||
           i==(mvaVars->find("jmme")->second) ||
           (i==(mvaVars->find("ksez")->second) && track==3) ||
           (i==(mvaVars->find("ksme")->second) && track==5) ||
           (i==(mvaVars->find("ksta")->second) && step!=m_NNKstar) ||
           (i==(mvaVars->find("muid")->second) && track==3)
          ) return 14;
  // Monotonous observables
  else return 15;
}

// #############################################################################
