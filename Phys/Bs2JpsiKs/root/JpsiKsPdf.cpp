// ####################################################################################################
// Phys/Bs2JpsiKs Package
// PDF description
// Authors: Patrick Koppenburg & Kristof De Bruyn
// ####################################################################################################

// ####################################################################################################
// *** Load Useful Classes ***
#include "JpsiKsPdf.h"


// ####################################################################################################
// *** Constructor ***
// Mass only
JpsiKsPdf::JpsiKsPdf(TString name, RooRealVar* mass, bool fitBs, bool fitKstar, int ttype, TString setup, int nevents){

  setToZero("All");
  m_name = name;  
  m_mass = mass;
  
  m_fitBs = fitBs;
  m_fitKstar = fitKstar;
  m_ttype = ttype;
  m_setup = setup;
  m_sigType = "DoubleCB";
  m_KstarType = "ExpGauss";
  m_bkgType = "Exp";
  
  m_nevents = nevents;
  m_extended = (m_nevents>0);
  buildFractions( ( m_extended ? m_nevents : 1 ) );
  buildMassPdf();
}

// ####################################################################################################
// Mass and Lifetime
JpsiKsPdf::JpsiKsPdf(TString name, RooRealVar* mass, RooRealVar* time, bool fitBs,
                     bool fitKstar, int ttype, TString setup, int nevents){

  setToZero("All");
  m_name = name;  
  m_mass = mass;
  m_tau = time;
  
  m_fitBs = fitBs;
  m_fitKstar = fitKstar;
  m_fitRel = true;
  m_ttype = ttype;
  m_setup = setup;
  m_sigType = "DoubleCB";
  m_KstarType = "ExpGauss";
  m_bkgType = "Exp";
  m_bkgTauType = (m_ttype==5 ? "OneAcc" : "TwoExp");
  m_AccModel = "Frac";
  m_ResModel = "Triple25";
  
  m_nevents = nevents;
  m_extended = (m_nevents>0);
  buildFractions( ( m_extended ? m_nevents : 1 ) );
  buildMassPdf();

  buildTimePdf();
  buildtwoDPdf();
}


// ####################################################################################################
// *** Initialisation ***
void JpsiKsPdf::setToZero(TString which){
  // grep "* m_" JpsiKsPdf.h | awk -F"\*" '{print $2}' | awk -F";" '{print " "$1"=0;"}'
  
  if(which=="All" || which=="Mass"){
    //m_nevents=0; // Keep the general settings
    m_nBd=0;
    m_nBs=0;
    m_nKstar=0;
    m_nonPeaking=0;
    //m_mass=0; // Keep the observable
    m_alpha=0;
    m_n=0;
    m_alpha2=0;
    m_n2=0;
    m_width=0;
    m_width2=0;
    m_frac=0;
    m_Bd=0;
    m_Bd_I=0;
    m_Bd_II=0;
    m_scale=0;
    m_scale2=0;
    m_Bswidth=0;
    m_Bswidth2=0;
    m_Bs=0;
    m_Bs_I=0;
    m_Bs_II=0;
    m_Kstar_mean=0;
    m_Kstar_sigma=0;
    m_Kstar_shift=0;
    m_Kstar_trans=0;
    m_Kstar=0;
    m_bkg1=0;
    m_bkg2=0;
    m_comBKG=0;
    m_massPdf=0;
  }
  if(which=="All" || which=="Time"){
    // m_tau=0; // Keep the observable
    m_resMean=0;
    m_coreSigma=0;
    m_midSigma=0;
    m_tailSigma=0;
    m_Corefrac=0;
    m_Midfrac=0;
    m_core=0;
    m_mid=0;
    m_tail=0;
    m_resModel=0;
    m_tau_long=0;
    m_tau_short=0;
    m_frac_bkg=0;
    m_bkgY=0;
    m_bkgZ=0;
    m_bkgAcc=0;
    m_decay_long=0;
    m_decay_acc_bkg=0;
    m_decay_short=0;
    m_decay_background=0;
    m_accY=0;
    m_accZ=0;
    m_accOffset=0;
    m_accVelo=0;
    m_acceptance=0;
    m_tau_Bd=0;
    m_tau_Bs=0;
    m_tau_Bsunblind=0;
    m_decay_Bd=0;
    m_decay_acc_Bd=0;
    m_decay_Bs=0;
    m_decay_acc_Bs=0;
    m_lifetimePdf=0;
    m_twoD_Bd=0;
    m_twoD_Bs=0;
    m_twoD_Kstar=0;
    m_twoD_comBKG=0;
    m_twoDPdf=0;
  }
} 

// ####################################################################################################
void JpsiKsPdf::setConstant(TString which){
  if(which=="Mod"){
    if(m_meanBd) m_meanBd->setVal(m_ttype==3 ? 5281.259 : 5281.946);
    if(m_width) m_width->setVal(m_ttype==3 ? 5.2844 : 7.3066);
    if(m_frac) m_frac->setVal(m_ttype==3 ? 0.48809 : 0.76813);
    if(m_width2) m_width2->setVal(m_ttype==3 ? 8.5789 : 13.758);
    if(m_bkg1) m_bkg1->setVal(m_ttype==3 ? -0.0023543 : -0.0033796);
    if(m_accVelo) m_accVelo->setVal(m_ttype==3 ? -0.025283 : 0.030792);
    if(m_accY) m_accY->setVal(m_ttype==3 ? 1.5197 : 2.0243);
    if(m_accZ) m_accZ->setVal(m_ttype==3 ? 2.3311 : 1.1124);
    if(m_bkgY) m_bkgY->setVal(m_ttype==3 ? 1. : 3.1140);
    if(m_bkgZ) m_bkgZ->setVal(m_ttype==3 ? 1. : 2.6337);
    if(m_frac_bkg) m_frac_bkg->setVal(m_ttype==3 ? 0.41475: 1.);
    if(m_tau_long) m_tau_long->setVal(m_ttype==3 ? 1.7524 : 1.7783);
    if(m_tau_short) m_tau_short->setVal(m_ttype==3 ? 0.40135 : 1.);
  }
  if(which=="ModOdd"){
    if(m_meanBd) m_meanBd->setVal(m_ttype==3 ? 5281.25 : 5281.95);
    if(m_width) m_width->setVal(m_ttype==3 ? 5.5334 : 7.6562);
    if(m_frac) m_frac->setVal(m_ttype==3 ? 0.51475 : 0.83404);
    if(m_width2) m_width2->setVal(m_ttype==3 ? 8.7215 : 14.888);
    if(m_bkg1) m_bkg1->setVal(m_ttype==3 ? -0.0015351 : -0.0019538);
  }
  std::cout << "* Setting parameters to constant: " << which  << std::endl;
  if(which=="Mass" || which=="All" || which=="SigOnly" || which=="Tails"){
    if(m_alpha) m_alpha->setConstant(true);
    if(m_n) m_n->setConstant(true);
    if(m_alpha2) m_alpha2->setConstant(true);
    if(m_n2) m_n2->setConstant(true);
  }
  if(which=="Mass" || which=="All" || which=="SigOnly" || which=="Mod" || which=="ModOdd"){
    if(m_meanBd) m_meanBd->setConstant(true);
    if(m_width) m_width->setConstant(true);
    if(m_frac) m_frac->setConstant(true);
    if(m_width2) m_width2->setConstant(true);
  }
  if(which=="Mass" || which=="All" || which=="Bkg" || which=="Mod" || which=="ModOdd"){
    if(m_bkg1) m_bkg1->setConstant(true);
    if(m_bkg2) m_bkg2->setConstant(true);
  }
  if(which=="Mass" || which=="All" || which=="Kstar" || which=="Mod" || which=="ModOdd"){
    if(m_Kstar_mean) m_Kstar_mean->setConstant(true);
    if(m_Kstar_sigma) m_Kstar_sigma->setConstant(true);
    if(m_Kstar_shift) m_Kstar_shift->setConstant(true);
  }
  if(which=="Mass"){
    if(m_nBd) m_nBd->setConstant(true);
    if(m_nBs) m_nBs->setConstant(true);
    if(m_nKstar) m_nKstar->setConstant(true);
    if(m_nonPeaking) m_nonPeaking->setConstant(true);
  }
  if(which=="Time" || which=="Mod"){
    if(m_accOffset) m_accOffset->setConstant(true);
    if(m_accVelo) m_accVelo->setConstant(true);
    if(m_accY) m_accY->setConstant(true);
    if(m_accZ) m_accZ->setConstant(true);
    if(m_bkgY) m_bkgY->setConstant(true);
    if(m_bkgZ) m_bkgZ->setConstant(true);
    if(m_frac_bkg) m_frac_bkg->setConstant(true);
    if(m_tau_long) m_tau_long->setConstant(true);
    if(m_tau_short) m_tau_short->setConstant(true);
  }
}

// ####################################################################################################
void JpsiKsPdf::reInitialise(TString which){
  std::cout << "* Re-initialising PDF" << std::endl;
  setToZero(which);
  if(which=="Mass" || which=="All"){
    buildFractions( ( m_extended ? m_nevents : 1 ) );
    buildMassPdf();
  }
  if(which=="Time" || which=="All"){
    buildTimePdf();
    buildtwoDPdf();
  }
}

// ####################################################################################################
void JpsiKsPdf::setModel(TString setSigType, TString setKstarType, TString setBkgType, TString setSigTails){
  if(setSigType!="Default") m_sigType = setSigType;
  if(!(m_sigType=="CB" || m_sigType=="Gauss" || m_sigType=="DoubleCB" || m_sigType=="GaussCB" || m_sigType=="DoubleGauss")){
    std::cout << "ERROR: Unknown Signal Model." << std::endl;
  }
  if(setKstarType!="Default") m_KstarType = setKstarType;
  if(!(m_KstarType=="Argus" || m_KstarType=="ExpGauss")) std::cout << "ERROR: Unknown Kstar Model." << std::endl;
  
  if(setBkgType!="Default")m_bkgType = setBkgType;
  if(!(m_bkgType=="Exp" || m_bkgType=="Poly" || m_bkgType=="Uni")) std::cout << "ERROR: Unknown Background Model." << std::endl;
  
  if(setSigType!="Default") m_setup = setSigTails;
  if(!(m_setup=="Loose" || m_setup=="Optimal" || m_setup=="FitTails"|| m_setup=="Lambda")) std::cout << "ERROR: Unknow Setup for Tails." << std::endl;
  
  // Re-Initialise model
  if(m_tau_Bd) reInitialise("All");
  else reInitialise("Mass");
}

// ####################################################################################################
void JpsiKsPdf::setBdLifetime(TString setDiff){
  // HFAG 2012: 1.519 +/- 0.007 && LHCb-ANA-2011-001: 1.558 +/- 0.056 (stat.) +/- 0.022 (syst.)

  if(setDiff=="HFAG") m_tau_Bd->setVal(1.519);
  else if(setDiff=="HFAGPlus") m_tau_Bd->setVal(1.519+0.007);
  else if(setDiff=="HFAGMin") m_tau_Bd->setVal(1.519-0.007);
  
  if(setDiff=="LHCb") m_tau_Bd->setVal(1.558);
  else if(setDiff=="LHCbPlus") m_tau_Bd->setVal(1.558+TMath::Sqrt(pow(0.056,2)+pow(0.022,2)));
  else if(setDiff=="LHCbMin") m_tau_Bd->setVal(1.558-TMath::Sqrt(pow(0.056,2)+pow(0.022,2)));  
}

// ####################################################################################################
void JpsiKsPdf::setMassDiff(TString setDiff){
  if(setDiff=="MassDiffPlus") m_massDiff->setVal(87.52 + TMath::Sqrt(pow(0.30,2) + pow(0.12,2)));
  else if(setDiff=="MassDiffMin") m_massDiff->setVal(87.52 - TMath::Sqrt(pow(0.30,2) + pow(0.12,2)));
  else if(setDiff="MassDiffFit") m_massDiff->setConstant(false);
}

// ####################################################################################################
void JpsiKsPdf::scaleMassWidth(TString setDiff){
  if(setDiff=="BMass"){
    m_scale->setVal(m_BsPDG/m_BdPDG);
    m_scale2->setVal(m_scale->getVal());
  }
  else if(setDiff=="BJKMass"){
    m_scale->setVal((m_BsPDG - m_JpsiPDG - m_Kzero)/(m_BdPDG - m_JpsiPDG - m_Kzero));
    m_scale2->setVal(m_scale->getVal());
  }
  else if(setDiff=="PhSp"){
    double xs = m_JpsiPDG/m_BsPDG;
    double ys = m_Kzero/m_BsPDG;
    double phspBs = m_BsPDG*TMath::Sqrt((1-pow(xs+ys,2))*(1-pow(xs-ys,2)))/2;
    double xd = m_JpsiPDG/m_BdPDG;
    double yd = m_Kzero/m_BdPDG;
    double phspBd = m_BdPDG*TMath::Sqrt((1-pow(xd+yd,2))*(1-pow(xd-yd,2)))/2;
    m_scale->setVal(phspBs/phspBd);
    m_scale2->setVal(m_scale->getVal());
  }
  else if(setDiff=="MCfit"){
    m_scale->setVal(m_ttype==3 ? 1.133 : 1.000);
    m_scale2->setVal(m_ttype==3 ? 1.023 : 1.035);
  }
  else if(setDiff=="MCfitPlus"){
    m_scale->setVal(m_ttype==3 ? 1.133+0.054 : 1.000+0.015);
    m_scale2->setVal(m_ttype==3 ? 1.023+0.033 : 1.035+0.024);
  }
  else if(setDiff=="MCfitMin"){
    m_scale->setVal(m_ttype==3 ? 1.133-0.054 : 1.000-0.015);
    m_scale2->setVal(m_ttype==3 ? 1.023-0.033 : 1.035-0.024);
  }
  else if(setDiff=="MCfree"){
    m_scale->setConstant(false);
    m_scale2->setConstant(false);
  }
  std::cout << " SETUP: Mass Width scale factors = (" << m_scale->getVal() << "," << m_scale2->getVal() << ")" << std::endl;
}

// ####################################################################################################
void JpsiKsPdf::setTails(){
  if(m_setup=="Optimal"){
    if(m_alpha) m_alpha->setVal(m_ttype==3 ? 1.21 : (m_ttype==5 ? 2.478 : 2.387));
    if(m_n) m_n->setVal(m_ttype==3 ? 5.28 : (m_ttype==5 ? 1.81 : 1.94));
    if(m_alpha2) m_alpha2->setVal(m_ttype==3 ? -1.517 : (m_ttype==5 ? -2.54 : -2.410));
    if(m_n2) m_n2->setVal(m_ttype==3 ? 145.501 : (m_ttype==5 ? 7.5 : 8.9));
    setConstant("Tails");
  }
  else if(m_setup=="Loose" || m_setup=="Lambda"){
    if(m_alpha) m_alpha->setVal(m_ttype==3 ? 1.312 : (m_ttype==5 ? 2.339 : 2.305));
    if(m_n) m_n->setVal(m_ttype==3 ? 4.02 : (m_ttype==5 ? 1.71 : 1.75));
    if(m_alpha2) m_alpha2->setVal(m_ttype==3 ? -1.431 : (m_ttype==5 ? -2.248 : -2.207));
    if(m_n2) m_n2->setVal(m_ttype==3 ? 124.48 : (m_ttype==5 ? 6.7 : 7.4));
    setConstant("Tails");
  }
}

// ####################################################################################################
void JpsiKsPdf::setResolution(){
  if(m_ResModel=="Triple25"){
    if(m_coreSigma) m_coreSigma->setVal(m_ttype==3 ? 0.0339915 : (m_ttype==5 ? 0.0397601 : 0.0397601));
    if(m_midSigma) m_midSigma->setVal(m_ttype==3 ? 0.0648249 : (m_ttype==5 ? 0.0720899 : 0.0720899));
    if(m_tailSigma) m_tailSigma->setVal(m_ttype==3 ? 0.37931 : (m_ttype==5 ? 0.210496 : 0.210496));// From MC
    if(m_Corefrac) m_Corefrac->setVal(m_ttype==3 ? 0.625239 : (m_ttype==5 ? 0.491009 : 0.491009));
    if(m_Midfrac) m_Midfrac->setVal(m_ttype==3 ? 0.362524 : (m_ttype==5 ? 0.43744 : 0.43744));
  }
  else if(m_ResModel=="Triple50"){
    if(m_coreSigma) m_coreSigma->setVal(m_ttype==3 ? 0.0348902 : (m_ttype==5 ? 0.0328314 : 0.0328314));
    if(m_midSigma) m_midSigma->setVal(m_ttype==3 ? 0.0741641 : (m_ttype==5 ? 0.0711455 : 0.0711455));
    if(m_tailSigma) m_tailSigma->setVal(m_ttype==3 ? 0.37931 : (m_ttype==5 ? 0.210496 : 0.210496));// From MC
    if(m_Corefrac) m_Corefrac->setVal(m_ttype==3 ? 0.641135 : (m_ttype==5 ? 0.417324 : 0.417324));
    if(m_Midfrac) m_Midfrac->setVal(m_ttype==3 ? 0.349782 : (m_ttype==5 ? 0.39845 : 0.39845));
  }
  else if(m_ResModel=="TripleMC"){
    if(m_coreSigma) m_coreSigma->setVal(m_ttype==3 ? 0.0313289 : (m_ttype==5 ? 0.0313592 : 0.0313592));
    if(m_midSigma) m_midSigma->setVal(m_ttype==3 ? 0.0612225 : (m_ttype==5 ? 0.0634281 : 0.0634281));
    if(m_tailSigma) m_tailSigma->setVal(m_ttype==3 ? 0.37931 : (m_ttype==5 ? 0.210496 : 0.210496));
    if(m_Corefrac) m_Corefrac->setVal(m_ttype==3 ? 0.702295 : (m_ttype==5 ? 0.633399 : 0.633399));
    if(m_Midfrac) m_Midfrac->setVal(m_ttype==3 ? 0.28924 : (m_ttype==5 ? 0.354031 : 0.354031));
  }
  else if(m_ResModel=="ResGauss"){
    if(m_tailSigma) m_tailSigma->setVal(m_ttype==3 ? 0.0551586 : (m_ttype==5 ? 0.0798146 : 0.0798146));
  }
  else if(m_ResModel=="ResGaussWide"){
    if(m_tailSigma) m_tailSigma->setVal(0.5);
  }
  
}

// ####################################################################################################
void JpsiKsPdf::setTimeModel(TString setResModel, TString setAccModel, TString setBkgType, bool fitRel){
  if(setResModel!="Default") m_ResModel = setResModel;
  if(!(m_ResModel=="Triple25" || m_ResModel=="Triple50" || m_ResModel=="TripleMC" || m_ResModel=="ResGauss" ||
       m_ResModel=="ResGaussWide")){
    std::cout << "ERROR: Unknown Resolution Model." << std::endl;
  }
  if(setAccModel!="Default") m_AccModel = setAccModel;
  if(!(m_AccModel=="Exp" || m_AccModel=="Frac" || m_AccModel=="FracOffset" || m_AccModel=="Tan" || m_AccModel=="TanOffset")){
    std::cout << "ERROR: Unknown Acceptance Model." << std::endl;
  }
  if(setBkgType!="Default") m_bkgTauType = setBkgType;
  if(!(m_bkgTauType=="OneExp" || m_bkgTauType=="TwoExp" || m_bkgTauType=="OneAcc")){
    std::cout << "ERROR: Unknown Background Decay Time Model." << std::endl;
  }
  m_fitRel = fitRel;
  
  // Re-Initialise
  reInitialise("Time");
}

// ####################################################################################################
// *** Destructor ***
JpsiKsPdf::~JpsiKsPdf() {
  // grep "* m_" JpsiKsPdf.h | awk -F"\*" '{print $2}' | awk -F";" '{print "  if("$1") delete"$1";"}'

  if(m_nBd) delete m_nBd;
  if(m_nBs) delete m_nBs;
  if(m_nKstar) delete m_nKstar;
  if(m_nonPeaking) delete m_nonPeaking;
  //  if(m_mass) delete m_mass; // not owned
  if(m_alpha) delete m_alpha;
  if(m_n) delete m_n;
  if(m_alpha2) delete m_alpha2;
  if(m_n2) delete m_n2;
  if(m_width) delete m_width;
  if(m_width2) delete m_width2;
  if(m_Bd) delete m_Bd;
  if(m_scale) delete m_scale;
  if(m_scale2) delete m_scale2;
  if(m_Bswidth) delete m_Bswidth;
  if(m_Bswidth2) delete m_Bswidth2;
  if(m_Bs) delete m_Bs;
  if(m_Kstar_mean) delete m_Kstar_mean;
  if(m_Kstar_sigma) delete m_Kstar_sigma;
  if(m_Kstar_shift) delete m_Kstar_shift;
  if(m_Kstar_trans) delete m_Kstar_trans;
  if(m_Kstar) delete m_Kstar;
  if(m_bkg1) delete m_bkg1;
  if(m_bkg2) delete m_bkg2;
  if(m_comBKG) delete m_comBKG;
  if(m_massPdf) delete m_massPdf;
  //  if(m_tau) delete m_tau; // not owned
  if(m_resMean) delete m_resMean;
  if(m_coreSigma) delete m_coreSigma;
  if(m_midSigma) delete m_midSigma;
  if(m_tailSigma) delete m_tailSigma;
  if(m_Corefrac) delete m_Corefrac;
  if(m_Midfrac) delete m_Midfrac;
  if(m_core) delete m_core;
  if(m_mid) delete m_mid;
  if(m_tail) delete m_tail;
  if(m_resModel) delete m_resModel;
  if(m_tau_long) delete m_tau_long;
  if(m_tau_short) delete m_tau_short;
  if(m_frac_bkg) delete m_frac_bkg;
  if(m_bkgY) delete m_bkgY;
  if(m_bkgZ) delete m_bkgZ;
  if(m_bkgAcc) delete m_bkgAcc;
  if(m_decay_long) delete m_decay_long;
  if(m_decay_acc_bkg) delete m_decay_acc_bkg;
  if(m_decay_short) delete m_decay_short;
  if(m_decay_background) delete m_decay_background;
  if(m_accY) delete m_accY;
  if(m_accZ) delete m_accZ;
  if(m_accOffset) delete m_accOffset;
  if(m_accVelo) delete m_accVelo;
  if(m_acceptance) delete m_acceptance;
  if(m_tau_Bd) delete m_tau_Bd;
  if(m_tau_Bs) delete m_tau_Bs;
  if(m_tau_Bsunblind) delete m_tau_Bsunblind;
  if(m_decay_Bd) delete m_decay_Bd;
  if(m_decay_acc_Bd) delete m_decay_acc_Bd;
  if(m_decay_Bs) delete m_decay_Bs;
  if(m_decay_acc_Bs) delete m_decay_acc_Bs;
  if(m_lifetimePdf) delete m_lifetimePdf;
  if(m_twoD_Bd) delete m_twoD_Bd;
  if(m_twoD_Bs) delete m_twoD_Bs;
  if(m_twoD_Kstar) delete m_twoD_Kstar;
  if(m_twoD_comBKG) delete m_twoD_comBKG;
  if(m_twoDPdf) delete m_twoDPdf;
  std::cout << "* Deleting done" << std::endl;

}

// ####################################################################################################
// *** Definitions ***
void JpsiKsPdf::buildFractions(int nevents){

  // Individual Components 
  double fracBd = 0.5*nevents;
  double fracBs = (m_fitBs ? fracBd*fsBr : 0.);
  double fracKs = (m_fitKstar ? 0.001*fracBd : 0.);
  double fracCombi = nevents-fracBd-fracBs-fracKs;
  
  // RooRealVars
  m_nBd = new RooRealVar(m_name+"nBd", "number of Bd",fracBd, 0.0, 1.0*nevents);
  m_nBs = new RooRealVar(m_name+"nBs","number of Bs",fracBs, 0.0, 0.15*nevents);
  m_nKstar = new RooRealVar(m_name+"nKstar","number of Kstar", fracKs, 0.0, 0.1*nevents);
  m_nonPeaking = new RooRealVar(m_name+"nonPeaking","number of Background not peaking", fracCombi, 0.0, 1.0*nevents);
}

// ####################################################################################################
void JpsiKsPdf::buildMassPdf(){

  // *** Signal Bd ***
  if ("Lambda"==m_setup){
    m_meanBd = new RooRealVar(m_name+"meanLb","mean Lb mass", 5620, 5610., 5630.);
  } else {
    m_meanBd = new RooRealVar(m_name+"meanBd","mean Bd mass", 5279.50, 5279.50-10., 5279.50+10.);
  }
  m_width = new RooRealVar(m_name+"width","width",5.,1.,10.);

  // Individual Components
  if(m_sigType=="CB" || m_sigType=="DoubleCB" || m_sigType=="GaussCB"){
    m_alpha = new RooRealVar(m_name+"alpha","alpha",2.,0.,5.);
    m_n = new RooRealVar(m_name+"n","n",2.,0.,25.);
    m_Bd_I = new RooCBShape(m_name+"CBshapeBd","Bd Crystal Ball",*m_mass,*m_meanBd,*m_width,*m_alpha,*m_n);
  }
  if(m_sigType=="DoubleCB"){
    m_width2 = new RooRealVar(m_name+"width2","width2",10.,1.,25.);
    m_alpha2 = new RooRealVar(m_name+"alpha2","alpha2",-2.,-5.,0.); 
    m_n2 = new RooRealVar(m_name+"n2","n2",7.,0.,150.);
    m_Bd_II = new RooCBShape(m_name+"CBshapeBd_refl","Bd Refl Crystal Ball",*m_mass,*m_meanBd,*m_width2,*m_alpha2,*m_n2);
  }
  if(m_sigType=="Gauss" || m_sigType=="DoubleGauss"){
    m_Bd_I = new RooGaussian(m_name+"BdGauss_core", "Bd core gaussian" , *m_mass, *m_meanBd, *m_width);
  }
  if(m_sigType=="GaussCB" || m_sigType=="DoubleGauss"){
    m_width2 = new RooRealVar(m_name+"width2","width2",10.,1.,25.);
    m_Bd_II = new RooGaussian(m_name+"BdGauss_wide", "Bd wide gaussian" , *m_mass, *m_meanBd, *m_width2);
  }
  // Set the correct tail parameters
  setTails();
  
  // Final Model
  if(m_sigType=="CB"){
    std::cout << " SETUP: Signal Model = Single Crystal Ball" << std::endl;
    m_Bd = (RooAbsPdf *)m_Bd_I;
  }
  if(m_sigType=="Gauss"){
    std::cout << " SETUP: Signal Model = Single Gauss" << std::endl;
    m_Bd = (RooAbsPdf *)m_Bd_I;
  }
  if(m_sigType=="DoubleCB") std::cout << " SETUP: Signal Model = Double Crystal Ball" << std::endl;
  if(m_sigType=="GaussCB") std::cout << " SETUP: Signal Model = Gauss + Crystal Ball" << std::endl;
  if(m_sigType=="DoubleGauss") std::cout << " SETUP: Signal Model = Double Gauss" << std::endl;
  if(m_sigType=="DoubleCB" || m_sigType=="GaussCB" || m_sigType=="DoubleGauss"){
    m_frac = new RooRealVar(m_name+"frac", "Fraction of narrow component", 0.67521, 0.0, 1.0);
    m_Bd = new RooAddPdf(m_name+"Bd PDF","Bd PDF",RooArgList(*m_Bd_I,*m_Bd_II),RooArgList(*m_frac));
  }

  // *** Signal Bs ***  
  if(m_fitBs){
    m_massDiff = new RooRealVar(m_name+"MassDiff","Bs - Bd mass difference", 87.52, 80., 100.);
    m_massDiff->setConstant(true);
    m_meanBs = new RooFormulaVar(m_name+"meanBs","@0+@1", RooArgSet(*m_meanBd,*m_massDiff));
    m_scale = new RooRealVar(m_name+"scale","Mass width scale factor", 1.,0.5,1.5);
    m_scale2 = new RooRealVar(m_name+"scale2","Mass width scale factor", 1.,0.5,1.5);
    m_scale->setConstant(true);
    m_scale2->setConstant(true);
    m_Bswidth = new RooFormulaVar(m_name+"Bswidth","@0*@1", RooArgSet(*m_scale,*m_width));
    if(m_width2) m_Bswidth2 = new RooFormulaVar(m_name+"Bswidth2","@0*@1", RooArgSet(*m_scale2,*m_width2));
    
    // Individual Components
    if(m_sigType=="CB" || m_sigType=="DoubleCB" || m_sigType=="GaussCB"){
      m_Bs_I = new RooCBShape(m_name+"CBshapeBs","Bs Crystal Ball",*m_mass,*m_meanBs,*m_Bswidth,*m_alpha,*m_n);
    }
    if(m_sigType=="DoubleCB"){
      m_Bs_II = new RooCBShape(m_name+"CBshapeBs_refl","Bs Refl Crystal Ball",*m_mass,*m_meanBs,*m_Bswidth2,*m_alpha2,*m_n2);
    }
    if(m_sigType=="Gauss" || m_sigType=="DoubleGauss"){
      m_Bs_I = new RooGaussian(m_name+"BsGauss_core", "Bs core gaussian" , *m_mass, *m_meanBs, *m_Bswidth);
    }
    if(m_sigType=="GaussCB" || m_sigType=="DoubleGauss"){
      m_Bs_II = new RooGaussian(m_name+"BsGauss_wide", "Bs wide gaussian" , *m_mass, *m_meanBs, *m_Bswidth2);
    }
  
    // Final Model
    if(m_sigType=="CB" || m_sigType=="Gauss") m_Bs = (RooAbsPdf *)m_Bs_I;
    if(m_sigType=="DoubleCB" || m_sigType=="GaussCB" || m_sigType=="DoubleGauss"){
      m_Bs = new RooAddPdf(m_name+"Bs PDF","Bs PDF",RooArgList(*m_Bs_I,*m_Bs_II),RooArgList(*m_frac));
    }
  }
  else m_Bs = 0;
  
  // *** Peaking Background ***
  if(m_fitKstar){
    if(m_KstarType=="Argus"){
      std::cout << " SETUP: Kstar Model = Argus" << std::endl;
      m_Kstar_mean = new RooRealVar(m_name+"Kstar cutoff","Argus Cutoff",5229.2,5150.,5250.);
      m_Kstar_sigma = new RooRealVar(m_name+"Kstar slope","Argus Slope",-0.0546,-1.,0.);
      m_Kstar_shift = new RooRealVar(m_name+"Kstar power","Argus power",1.07,0.,2.5);
      m_Kstar = new RooArgusBG(m_name+"Argus","Kstar BKG",*m_mass,*m_Kstar_mean,*m_Kstar_sigma,*m_Kstar_shift);
    }
    else if(m_KstarType=="ExpGauss"){
      std::cout << " SETUP: Kstar Model = Exp and Gauss" << std::endl;
      m_Kstar_mean = new RooRealVar(m_name+"Kstar mean","mean",5179.9,5100,5300);
      m_Kstar_sigma = new RooRealVar(m_name+"Kstar sigma","sigma",22.07,10.,30.); 
      m_Kstar_shift = new RooRealVar(m_name+"Kstar shift","transition to Exp",4.50,0.,25.);
      m_Kstar_trans = new RooFormulaVar(m_name+"Kstar trans","transition to Exp","@0-@1",RooArgSet(*m_Kstar_mean,*m_Kstar_shift));
      m_Kstar = new RooExpAndGauss(m_name+"EaGKstar","Kstar BKG",*m_mass,*m_Kstar_mean,*m_Kstar_sigma,*m_Kstar_trans);
    }
    else std::cout << "ERROR: No Kstar model specified." << std::endl;
  }
  else m_Kstar = 0;
  
  // *** Background ***
  if(m_bkgType=="Exp"){
    std::cout << " SETUP: Background Model = Exponential \n" << std::endl;
    m_bkg1 = new RooRealVar(m_name+"expo","expo", -0.004,-0.1,0.);
    m_comBKG = new RooExponential(m_name+"comBKG" , "combinatorial BKG", *m_mass, *m_bkg1);
  }
  else if(m_bkgType=="Poly"){
    std::cout << " SETUP: Background Model = Second Order Chebychev Polynomial \n" << std::endl;
    m_bkg1 = new RooRealVar(m_name+"pol1","Chebychev Par 1", -0.17993 , -1., 1.); // DO NOT ALLLOW FOR TOO LARGE SLOPES
    m_bkg2 = new RooRealVar(m_name+"pol2","Chebychev Par 2", -0.00823 , -1., 1.); // DO NOT ALLLOW FOR TOO LARGE SLOPES
    m_comBKG = new RooChebychev(m_name+"comBKG","combinatorial BKG", *m_mass, RooArgList(*m_bkg1, *m_bkg2));
  }
  else if(m_bkgType=="Uni"){
    std::cout << " SETUP: Background Model = Uniform \n" << std::endl;
    m_comBKG = new RooUniform(m_name+"comBKG","combinatorial BKG", *m_mass);
  }
  else std::cout << "ERROR: No background model specified. \n" << std::endl;
  
  // *** Composite Model ***
  m_massPdf = new RooAddPdf(m_name+"massPdf", "Mass PDF for Sig + Bkg" , massPdfList(), fracPdfList());
  if(m_extended && !m_massPdf->canBeExtended()) std::cout << "ERROR: PDF cannot be extended, although requested" << std::endl;  
}

// ####################################################################################################
void JpsiKsPdf::buildTimePdf(){

  // *** Resolution ***  
  m_resMean = new RooRealVar(m_name+"resMean","Resolution - Mean",0.0,"ps");
  
  if(m_ResModel=="Triple25" || m_ResModel=="Triple50" || m_ResModel=="TripleMC"){
    std::cout << " SETUP: Resolution Model = triple Gaussian with parameter set " << m_ResModel << std::endl;
    m_coreSigma = new RooRealVar(m_name+"coreSigma","Resolution - Core Width",0.03,"ps");
    m_midSigma = new RooRealVar(m_name+"midSigma","Resolution - Middle Width",0.05,"ps");
    m_tailSigma = new RooRealVar(m_name+"tailSigma","Resolution - Tail Width",0.12,"ps");
    m_Corefrac = new RooRealVar(m_name+"Corefrac","Fraction of Core", 0.5);
    m_Midfrac = new RooRealVar(m_name+"Midfrac","Fraction of Middle", 0.45);
    setResolution();
  
    m_core = new RooGaussModel(m_name+"core","Core Gaussian",*m_tau,*m_resMean,*m_coreSigma);
    m_mid = new RooGaussModel(m_name+"mid","Middle Gaussian",*m_tau,*m_resMean,*m_midSigma);
    m_tail = new RooGaussModel(m_name+"tail","Tail Gaussian",*m_tau,*m_resMean,*m_tailSigma);
    m_resModel = new RooAddModel(m_name+"resModel","Resolution Model",RooArgList(*m_core,*m_mid,*m_tail),
                               RooArgList(*m_Corefrac,*m_Midfrac));
  }
  else if(m_ResModel=="ResGauss" || m_ResModel=="ResGaussWide"){
    std::cout << " SETUP: Resolution Model = Single Gaussian with parameter set " << m_ResModel << std::endl;
    m_tailSigma = new RooRealVar(m_name+"tailSigma","Resolution - Tail Width",0.12,"ps");
    setResolution();
    m_resModel = new RooGaussModel(m_name+"resModel","Tail Gaussian",*m_tau,*m_resMean,*m_tailSigma);
  }
                               
  // *** Background ***
  m_tau_long = new RooRealVar(m_name+"tau_long","Long Lifetime for Bkg",1.525,0.5,5.,"ps"); 
  m_tau_short = new RooRealVar(m_name+"tau_short","Short lifetime for Bkg",0.3,0.,1.5,"ps");
  m_frac_bkg = new RooRealVar(m_name+"frac_bkg","Fraction of Short",0.5,0.,1.);
  m_bkgY = new RooRealVar(m_name+"bkgY","Acceptance for Bkg",1.8,0.,5.);
	m_bkgZ = new RooRealVar(m_name+"bkgZ","Acceptance for Bkg",1.4,0.,5.);
  
  m_bkgAcc = new RooFormulaVar(m_name+"bkgAcc","Acceptance for Bkg", "1/(1+pow(@1*@2,-@0))",RooArgList(*m_bkgY,*m_bkgZ,*m_tau));
  
  m_decay_long = new RooDecay(m_name+"decay_long","Long Lifetimes",*m_tau,*m_tau_long,*m_resModel,RooDecay::SingleSided);
  m_decay_acc_bkg = new RooEffProd(m_name+"decay_acc_bkg","Decay with acceptance",*m_decay_long,*m_bkgAcc);
  if(m_bkgTauType=="TwoExp"){
    std::cout << " SETUP: Background Model = Short + Long-lived Exponential" << std::endl;
    m_decay_short = new RooDecay(m_name+"decay_short","Short Lifetimes",*m_tau,*m_tau_short,*m_resModel,RooDecay::SingleSided);
    m_decay_background = new RooAddPdf(m_name+"decay_background","Background Model",
      RooArgList(*m_decay_short,*m_decay_long),*m_frac_bkg);
  }
  else if(m_bkgTauType=="OneExp"){
    std::cout << " SETUP: Background Model = Long-lived Exponential" << std::endl;
    m_decay_background = m_decay_long;
  }
  else if(m_bkgTauType=="OneAcc"){
    std::cout << " SETUP: Background Model = Long-lived Exponential X Acceptance" << std::endl;
    m_decay_background = m_decay_acc_bkg;
  }
  else std::cout << "ERROR: No background decay time model specified. \n" << std::endl;
  
  // *** Acceptance ***
	m_accY = new RooRealVar(m_name+"accY","For Acceptance Function",1.8,0.,5.);
	m_accZ = new RooRealVar(m_name+"accZ","For Acceptance Function",1.4,0.,5.);	
  m_accOffset = new RooRealVar(m_name+"accOffset","For Acceptance Function",0.2,-1.,1.);	
	m_accVelo = new RooRealVar(m_name+"accVelo","For Acceptance Function",-0.016,-0.5,0.5);
  
  if(m_AccModel=="Exp"){
    std::cout << " SETUP: Acceptance Model: (1-Exp[-y*(tau-offset)])*(1+beta*tau)" << std::endl;
    m_acceptance = new RooFormulaVar(m_name+"acceptance","acceptance",
      "(1-TMath::Exp(-(@3-@1)*@0))*(1+@2*@3)",RooArgList(*m_accY,*m_accOffset,*m_accVelo,*m_tau));
  }
  else if(m_AccModel=="Frac"){
    std::cout << " SETUP: Acceptance Model: (1+beta*tau)/(1+(z*tau)^-y)" << std::endl;
    m_acceptance = new RooFormulaVar(m_name+"acceptance","acceptance",
      "(1+@2*@3)/(1+pow(@1*@3,-@0))",RooArgList(*m_accY,*m_accZ,*m_accVelo,*m_tau));
  }
  else if(m_AccModel=="FracOffset"){
    std::cout << " SETUP: Acceptance Model: (1+beta*tau)/(1+(z*[tau-offset])^-y)" << std::endl;
    m_acceptance = new RooFormulaVar(m_name+"acceptance","acceptance",
      "(1+@3*@4)/(1+pow(@1*(@4-@2),-@0))",RooArgList(*m_accY,*m_accZ,*m_accOffset,*m_accVelo,*m_tau));
  }
  else if(m_AccModel=="Tan"){
    std::cout << " SETUP: Acceptance Model: (2/acos(-1))*ArcTan[y*tau]*(1+beta*tau)" << std::endl;
    m_acceptance = new RooFormulaVar(m_name+"acceptance","acceptance",
      "(2/acos(-1))*TMath::ATan(@0*@2)*(1+@1*@2)",RooArgList(*m_accY,*m_accVelo,*m_tau));
  }
  else if(m_AccModel=="TanOffset"){
    std::cout << " SETUP: Acceptance Model: (2/acos(-1))*ArcTan[y*(tau-offset)]*(1+beta*tau)" << std::endl;
    m_acceptance = new RooFormulaVar(m_name+"acceptance","acceptance",
      "(2/acos(-1))*TMath::ATan(@0*(@3-@1))*(1+@2*@3)",RooArgList(*m_accY,*m_accOffset,*m_accVelo,*m_tau));
  }

  // *** Signal ***
  std::cout << " SETUP: Signal Model = Single Exponential" << std::endl;
  // HFAG 2012: 1.519 +/- 0.007 && LHCb-ANA-2011-001: 1.558 +/- 0.056 (stat.) +/- 0.022 (syst.)
  m_tau_Bd = new RooRealVar(m_name+"tau_Bd","Average lifetime for Bd",1.519,0.,3.,"ps");
  m_tau_Bs = new RooRealVar(m_name+"tau_Bs","Average lifetime for Bs",1.509,0.,3.,"ps");
  m_tau_Bsunblind = new RooUnblindUniform(m_name+"tau_Bsunblind","Unblinded value of tau_Bs","BsEffLifetime",0.5,*m_tau_Bs);

  m_decay_Bd = new RooDecay(m_name+"decay_Bd","Fitted Decay",*m_tau,*m_tau_Bd,*m_resModel,RooDecay::SingleSided);
  m_decay_acc_Bd = new RooEffProd(m_name+"decay_acc_Bd","Decay with acceptance",*m_decay_Bd,*m_acceptance);
  if(m_fitBs){
    m_decay_Bs = new RooDecay(m_name+"decay_Bs","Fitted Decay",*m_tau,*m_tau_Bsunblind,*m_resModel,RooDecay::SingleSided);
    m_decay_acc_Bs = new RooEffProd(m_name+"decay_acc_Bs","Decay with acceptance",*m_decay_Bs,*m_acceptance);
    std::cout << "   WARNING: Bs Lifetime has been Blinded" << std::endl;
  }
  else m_decay_acc_Bs = 0;
  
  // *** Composite Model ***
  m_lifetimePdf = new RooAddPdf(m_name+"lifetimePdf", "lifetime PDF for Sig + Bkg" , lifetimePdfList(), fracPdfList());
  
  // *** Type of measurement ***
  // For Absolute measurements: Freeze acceptance parameters
  if(!m_fitRel){
    std::cout << " SETUP: Performing absolute measurement" << std::endl;
    m_accY->setConstant(true);
    m_accZ->setConstant(true);
    m_accOffset->setConstant(true);
    m_accVelo->setConstant(true);
  }
  else{
    std::cout << " SETUP: Performing relative measurement" << std::endl;
    m_tau_Bd->setConstant(true);
  }
}

// ####################################################################################################
void JpsiKsPdf::buildtwoDPdf(){
  std::cout << " SETUP: Building 2D PDF \n" << std::endl;

  m_twoD_Bd = new RooProdPdf(m_name+"twoD_Bd","Signal PDF",RooArgList(*m_Bd,*m_decay_acc_Bd));
  if(m_fitBs) m_twoD_Bs = new RooProdPdf(m_name+"twoD_Bs","Signal PDF",RooArgList(*m_Bs,*m_decay_acc_Bs));
  else m_twoD_Bs = 0;
  if(m_fitKstar) m_twoD_Kstar = new RooProdPdf(m_name+"twoD_Kstar","Background PDF",RooArgList(*m_Kstar,*m_decay_background));
  else m_twoD_Kstar = 0;
  m_twoD_comBKG = new RooProdPdf(m_name+"twoD_comBKG","Background PDF",RooArgList(*m_comBKG,*m_decay_background));
  
  m_twoDPdf = new RooAddPdf(m_name+"twoDPdf","PDF for Sig_Bkg",twoDPdfList(), fracPdfList());

}

// ####################################################################################################
// *** Accessors ***

// ####################################################################################################
// PDF fractions
RooArgList JpsiKsPdf::fracPdfList()const{
  RooArgList fracList;
  fracList.add(*m_nBd);
  if (m_fitBs) fracList.add(*m_nBs);
  if (m_fitKstar) fracList.add(*m_nKstar);
  if (m_extended) fracList.add(*m_nonPeaking);
  return fracList;
}

// ####################################################################################################
// PDFs - WARNING: Synchronize with above
RooArgList JpsiKsPdf::massPdfList()const{
  RooArgList pdfList;
  pdfList.add(*m_Bd);
  if (m_fitBs) pdfList.add(*m_Bs);
  if (m_fitKstar) pdfList.add(*m_Kstar); 
  pdfList.add(*m_comBKG);
  return pdfList;
};

// ####################################################################################################
RooArgList JpsiKsPdf::lifetimePdfList()const{
  RooArgList pdfList;
  pdfList.add(*m_decay_acc_Bd);
  if (m_fitBs) pdfList.add(*m_decay_acc_Bs);
  if (m_fitKstar) pdfList.add(*m_decay_background); // no dedicated lifetime model
  pdfList.add(*m_decay_background);
  return pdfList;
};

// ####################################################################################################
RooArgList JpsiKsPdf::twoDPdfList()const{
  RooArgList pdfList;
  pdfList.add(*m_twoD_Bd);
  if (m_fitBs) pdfList.add(*m_twoD_Bs);
  if (m_fitKstar) pdfList.add(*m_twoD_Kstar);
  pdfList.add(*m_twoD_comBKG);
  return pdfList;
};

// ####################################################################################################
// *** Redefine Fit Functions ***
RooFitResult* JpsiKsPdf::fitToMass(RooDataSet* data, bool doSumW2){
  if (!data) return 0 ;
  //  std::cout << "Fitting " << data->numEntries() << " " << data->sumEntries() << " " << doSumW2 << std::endl ;
  if(doSumW2) return m_massPdf->fitTo(*data, Save(), SumW2Error(true));
  else return m_massPdf->fitTo(*data, Save());
}
// ####################################################################################################
RooFitResult* JpsiKsPdf::fitToMass(RooDataSet* data, bool doSumW2, TString range){
  if (!data) return 0 ;
  //std::cout << "Range Fitting " << data->numEntries() << " " << data->sumEntries() << " " << doSumW2 << std::endl ;
  if(doSumW2) return m_massPdf->fitTo(*data, Range(range), Save(), SumW2Error(true));
  else return m_massPdf->fitTo(*data, Range(range), Save());
}
// ####################################################################################################
RooFitResult* JpsiKsPdf::fitToAll(RooDataSet* data, bool doSumW2){
  if (!data) return 0 ;
  // WARNING: Ranges do not work for multi-dimensional fits
  if(doSumW2) return m_twoDPdf->fitTo(*data, Save(), SumW2Error(true));
  else return m_twoDPdf->fitTo(*data, Save());
}

// ####################################################################################################
// *** Plot PDF ***
void JpsiKsPdf::plotOn(TCanvas* doek, RooDataSet* data, bool doSumW2, Int_t logy, int param, double *chi2Val){

  std::cout << "@@ Start Plotting PDF" << std::endl;
  
  // *** Frame ***
  RooPlot* massFrame = m_mass->frame(Bins((m_mass->getMax() - m_mass->getMin())/5));
  
  // Titles
  massFrame->SetTitle("");
  massFrame->SetYTitle("Candidates / (5 MeV/#it{c}^{2})");
  massFrame->SetXTitle("m_{J/#psi K_{S}^{0}} [MeV/#it{c}^{2}]");
  
  // Data
  if(doSumW2) data->plotOn(massFrame, DataError(RooAbsData::SumW2),MarkerStyle(8),MarkerSize(0.8));
  else data->plotOn(massFrame,MarkerStyle(8),MarkerSize(0.8));
  
  // PDF components
  if (!m_massPdf) {
    std::cout <<"Can't plot null" << std::endl;
    return;
  }
  m_massPdf->plotOn(massFrame, Components(*m_Bd), Range(m_mass->getMin(),m_mass->getMax()),
    FillColor(m_BdCol), FillStyle(1001), DrawOption("F"));
  if (m_Bs) m_massPdf->plotOn(massFrame, Components(*m_Bs), Range(m_mass->getMin(),m_mass->getMax()),
    FillColor(m_BsCol), FillStyle(1001), DrawOption("F"));
  m_massPdf->plotOn(massFrame, Components(*m_comBKG), Range(m_mass->getMin(),m_mass->getMax()),
    LineStyle(kDashed), LineColor(kBlack) );
  if (m_Kstar) m_massPdf->plotOn(massFrame, Components(*m_Kstar), Range(m_mass->getMin(),m_mass->getMax()),
    FillColor(m_KstarCol), FillStyle(1001), DrawOption("F"));
  
  // Data
  if(doSumW2) data->plotOn(massFrame, DataError(RooAbsData::SumW2),MarkerStyle(8),MarkerSize(0.8));
  else data->plotOn(massFrame,MarkerStyle(8),MarkerSize(0.8));
  m_massPdf->plotOn(massFrame, Range(m_mass->getMin(),m_mass->getMax()), LineColor(1) );
  
  std::cout << "@@ Finished Plotting PDF" << std::endl;  
  
  // Add Parameters and pull
  if(param==1){
    m_massPdf->paramOn(massFrame,Layout(0.5,0.92,0.92));
    massFrame->getAttText()->SetTextSize(0.03);
    std::cout << "@@ Adding Pull" << std::endl; 
    AddPull(doek,massFrame,logy); 
  }
  else if(param==2){
    massFrame->SetMinimum(0.9);
    massFrame->SetMaximum(10000);
    std::cout << "@@ Adding Pull" << std::endl; 
    AddPull(doek,massFrame,logy); 
  }
  else{
    doek->SetLeftMargin(0.15);
    doek->SetBottomMargin(0.15);
    doek->cd(1);
    gPad->SetLogy(logy);
    massFrame->Draw("");
  }
}

// ####################################################################################################
void JpsiKsPdf::plotOnTime(TCanvas* doek, RooDataSet* data, bool doSumW2, Int_t logy, int param, int massBox, double *chi2Val){

  std::cout << "@@ Start Plotting PDF" << std::endl;
  if (!m_lifetimePdf) {
    std::cout <<"Can't plot null" << std::endl;
    return;
  }

  // *** Frame ***
  RooPlot* timeFrame = m_tau->frame(Bins((m_tau->getMax() - m_tau->getMin())/0.2));

  // Titles
  timeFrame->SetTitle("");
  timeFrame->SetYTitle("Candidates / (0.2 ps)");
  timeFrame->SetXTitle("B decay time [ps]");
  
  // Data
  if(massBox>0){
    if(massBox==1) m_mass->setRange("massRange",5340,5390);
    else m_mass->setRange("massRange",5400,m_mass->getMax());
    
    if(doSumW2) data->plotOn(timeFrame,CutRange("massRange"), DataError(RooAbsData::SumW2),MarkerStyle(8),MarkerSize(0.8));
    else data->plotOn(timeFrame,CutRange("massRange"),MarkerStyle(8),MarkerSize(0.8));
  
    // PDF components
    m_twoDPdf->plotOn(timeFrame, ProjectionRange("massRange"), Components(*m_twoD_Bd), LineColor(1), LineStyle(6));
    m_twoDPdf->plotOn(timeFrame, ProjectionRange("massRange"), Components(*m_twoD_Bs), LineColor(1), LineStyle(4));
    m_twoDPdf->plotOn(timeFrame, ProjectionRange("massRange"), Components(*m_twoD_comBKG), LineColor(1), LineStyle(9));
    m_twoDPdf->plotOn(timeFrame, ProjectionRange("massRange"), LineColor(1));
  }
  else{
    if(doSumW2) data->plotOn(timeFrame, DataError(RooAbsData::SumW2),MarkerStyle(8),MarkerSize(0.8));
    else data->plotOn(timeFrame,MarkerStyle(8),MarkerSize(0.8));
  
    // PDF components
    m_twoDPdf->plotOn(timeFrame, Components(*m_twoD_Bd), LineColor(1), LineStyle(6));
    m_twoDPdf->plotOn(timeFrame, Components(*m_twoD_Bs), LineColor(1), LineStyle(4));
    m_twoDPdf->plotOn(timeFrame, Components(*m_twoD_comBKG), LineColor(1), LineStyle(9));
    m_twoDPdf->plotOn(timeFrame, LineColor(1));
  }
  std::cout << "@@ Finished Plotting PDF" << std::endl;
  
  timeFrame->SetMinimum(1.);

  // Add Parameters and pull
  if(param==1){
    m_lifetimePdf->paramOn(timeFrame,Layout(0.5,0.92,0.92));
    timeFrame->getAttText()->SetTextSize(0.03);
    std::cout << "@@ Adding Pull" << std::endl; 
    AddPull(doek,timeFrame,logy,chi2Val); 
  }
  else if(param==2){
    timeFrame->SetMinimum(0.9);
    timeFrame->SetMaximum((massBox>0 ? 50 : 10000));
    std::cout << "@@ Adding Pull" << std::endl; 
    AddPull(doek,timeFrame,logy,chi2Val); 
  }
  else{
    doek->SetLeftMargin(0.15);
    doek->SetBottomMargin(0.15);
    doek->cd(1);
    gPad->SetLogy(logy);
    timeFrame->Draw("");
  }
}

// ####################################################################################################
// *** Legend ***
void JpsiKsPdf::plotLegend(double x1,double y1,double x2,double y2, TString what) const {
  string sWhat (what);

  std::cout << "@@ Starting Legend" << std::endl;
  TLegend* leg = new TLegend(x1,y1,x2,y2,""); // memory leak

  TGraphErrors* gr = new TGraphErrors(1);
  gr->SetLineWidth(2);
  leg->AddEntry(gr,"data","lep");

  TH1F* HBs = new TH1F("Bs","Bs",10,0,1);
  if (m_Bs) {
    if (sWhat.find("mass")!=string::npos) {
      HBs->SetLineColor(0);  
      HBs->SetFillColor(m_BsCol);
      leg->AddEntry(HBs,"B_{s}^{0}#rightarrow J/#psiK_{S}^{0}","f");
    }
    else if (sWhat.find("time")!=string::npos) {
      HBs->SetLineColor(1);  
      HBs->SetLineStyle(4);
      if (!(sWhat.find("Bkg")!=string::npos)) {
        leg->AddEntry(HBs,"B_{s}^{0}#rightarrow J/#psiK_{S}^{0}","l");
      }
    }
  }
  
  TH1F* HBd = new TH1F("Bd","Bd",10,0,1);
  if (m_Bd) {
    if (sWhat.find("mass")!=string::npos) {
      HBd->SetLineColor(0);  
      HBd->SetFillColor(m_BdCol);
      leg->AddEntry(HBd,"B^{0}#rightarrow J/#psiK_{S}^{0}","f");
    }
    else if (sWhat.find("time")!=string::npos) {
      HBd->SetLineColor(1);  
      HBd->SetLineStyle(6);
      if (sWhat.find("All")!=string::npos) {
        leg->AddEntry(HBd,"B^{0}#rightarrow J/#psiK_{S}^{0}","l");
      }
    }
  }

  TH1F* HKstar = new TH1F("Kstar","Kstar",10,0,1);
  HKstar->SetLineColor(0);  
  HKstar->SetFillColor(m_KstarCol);  
  if (m_Kstar) leg->AddEntry(HKstar,"B#rightarrow J/#psiK_{S}^{0}X","f");
  
  TF1* bkg = new TF1("bkg","x",0,1);
  bkg->SetLineColor(1);
  bkg->SetLineWidth(2);
  if (sWhat.find("mass")!=string::npos) {
    bkg->SetLineStyle(kDashed);  
  }
  else if (sWhat.find("time")!=string::npos) {
    bkg->SetLineStyle(9);
  }
  leg->AddEntry(bkg,"background","l"); 

  TF1* total = new TF1("total","x",0,1);
  total->SetLineColor(1);
  total->SetLineWidth(2);  
  leg->AddEntry(total,"total","l"); 

  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);

  std::cout << "@@ Adding Legend" << std::endl;
  leg->Draw("same");
}

// ####################################################################################################
