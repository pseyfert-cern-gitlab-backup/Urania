// ####################################################################################################
// Phys/Bs2JpsiKs Package
// PDF description
// Authors: Patrick Koppenburg & Kristof De Bruyn
// ####################################################################################################

// ####################################################################################################
// *** Load Useful Classes ***
#include "JpsiKsSimPdf.h"


// ####################################################################################################
// *** Constructor ***
// Mass only
JpsiKsSimPdf::JpsiKsSimPdf(TString name, RooRealVar* mass, bool fitBs, bool fitKstar, int nevents){

  setToZero("All");
  m_name = name;  
  m_mass = mass;
  
  m_fitBs = fitBs;
  m_fitKstar = fitKstar;
  m_sigType = "DoubleCB";
  m_KstarType = "Gauss";
  m_bkgType = "Exp";
  
  m_nevents = nevents;
  m_extended = (m_nevents>0);
  buildFractions( ( m_extended ? m_nevents : 1 ) );
  buildMassPdf();
}

/*
// Mass and Lifetime
JpsiKsSimPdf::JpsiKsSimPdf(TString name, RooRealVar* mass, RooRealVar* time, bool fitBs, bool fitKstar, bool fitRel, int nevents){

  setToZero("All");
  m_name = name;  
  m_mass = mass;
  m_tau = time;
  
  m_fitBs = fitBs;
  m_fitKstar = fitKstar;
  m_fitRel = fitRel;
  m_sigType = "DoubleCB";
  m_KstarType = "Argus";
  m_bkgType = "Exp";
  m_bkgTauType = "OneExp";
  
  m_nevents = nevents;
  m_extended = (m_nevents>0);
  buildFractions( ( m_extended ? m_nevents : 1 ) );
  buildMassPdf();

  buildTimePdf(m_fitRel);
  buildtwoDPdf();
}
*/

// ####################################################################################################
// *** Initialisation ***
void JpsiKsSimPdf::setToZero(TString which){
  // grep "* m_" JpsiKsSimPdf.h | awk -F"\*" '{print $2}' | awk -F";" '{print " "$1"=0;"}'
  
  if(which=="All" || which=="Mass"){
    //m_nevents=0; // Keep the general settings
    m_nBd_LL=0;
    m_nBs_LL=0;
    m_nKstar_LL=0;
    m_nonPeaking_LL=0;
    m_nBd_DD=0;
    m_nBs_DD=0;
    m_nKstar_DD=0;
    m_nonPeaking_DD=0;
    //m_mass=0; // Keep the observable
    m_alpha=0;
    m_n=0;
    m_alpha2=0;
    m_n2=0;
    m_width_LL=0;
    m_width_DD=0;
    m_width2_LL=0;
    m_width2_DD=0;
    m_frac_LL=0;
    m_frac_DD=0;
    m_Bd_LL=0;
    m_Bd_I_LL=0;
    m_Bd_II_LL=0;
    m_Bd_DD=0;
    m_Bd_I_DD=0;
    m_Bd_II_DD=0;
    m_Bs_LL=0;
    m_Bs_I_LL=0;
    m_Bs_II_LL=0;
    m_Bs_DD=0;
    m_Bs_I_DD=0;
    m_Bs_II_DD=0;
    m_Kstar_cutoff=0;
    m_Kstar_cpar=0;
    m_Kstar_ppar=0;
    m_Kstar=0;
    m_bkg1=0;
    m_bkg2=0;
    m_comBKG=0;
    m_massPdf_LL=0;
    m_massPdf_DD=0;
  }
/*  
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
    m_decay_long=0;
    m_decay_short=0;
    m_decay_background=0;
    m_accX=0;
    m_accY=0;
    m_accZ=0;
    m_accA=0;
    m_accB=0;
    m_accVeLo=0;
    m_acceptance_combi=0;
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
*/
} 

// ####################################################################################################
void JpsiKsSimPdf::setConstant(TString which){
  std::cout << "* Setting parameters to constant" << std::endl;
  if(which=="Mass" || which=="All" || which=="SigOnly"){
    if(m_meanBd) m_meanBd->setConstant(true);
    if(m_width_LL) m_width_LL->setConstant(true);
    if(m_width_DD) m_width_DD->setConstant(true);
    if(m_alpha) m_alpha->setConstant(true);
    if(m_n) m_n->setConstant(true);
    if(m_frac_LL) m_frac_LL->setConstant(true);
    if(m_frac_DD) m_frac_DD->setConstant(true);
    if(m_width2_LL) m_width2_LL->setConstant(true);
    if(m_width2_DD) m_width2_DD->setConstant(true);
    if(m_alpha2) m_alpha2->setConstant(true);
    if(m_n2) m_n2->setConstant(true);
  }
  if(which=="Mass" || which=="All" || which=="Bkg"){
    if(m_bkg1) m_bkg1->setConstant(true);
    if(m_bkg2) m_bkg2->setConstant(true);
  }
  if(which=="Mass" || which=="All" || which=="Kstar"){
    if(m_Kstar_cutoff) m_Kstar_cutoff->setConstant(true);
    if(m_Kstar_cpar) m_Kstar_cpar->setConstant(true);
    if(m_Kstar_ppar) m_Kstar_ppar->setConstant(true);
  }
  if(which=="Mass"){
    if(m_nBd_LL) m_nBd_LL->setConstant(true);
    if(m_nBs_LL) m_nBs_LL->setConstant(true);
    if(m_nKstar_LL) m_nKstar_LL->setConstant(true);
    if(m_nonPeaking_LL) m_nonPeaking_LL->setConstant(true);
    if(m_nBd_DD) m_nBd_DD->setConstant(true);
    if(m_nBs_DD) m_nBs_DD->setConstant(true);
    if(m_nKstar_DD) m_nKstar_DD->setConstant(true);
    if(m_nonPeaking_DD) m_nonPeaking_DD->setConstant(true);
  }
}

// ####################################################################################################
void JpsiKsSimPdf::setModel(TString setSigType, TString setKstarType, TString setBkgType){
  m_sigType = setSigType;
  if(!(m_sigType=="CB" || m_sigType=="Gauss" || m_sigType=="DoubleCB" || m_sigType=="GaussCB" || m_sigType=="DoubleGauss")){
    std::cout << "ERROR: Unknown Signal Model." << std::endl;
  }
  m_KstarType = setKstarType;
  if(!(m_KstarType=="Argus" || m_KstarType=="Gauss")){
    std::cout << "ERROR: Unknown Kstar Model." << std::endl;
  }
  m_bkgType = setBkgType;
  if(!(m_bkgType=="Exp" || m_bkgType=="Poly" || m_bkgType=="Uni")){
    std::cout << "ERROR: Unknown Background Model." << std::endl;
  }
  
  // Re-Initialise
  std::cout << "* Re-initialising PDF" << std::endl;
  setToZero("Mass");
  buildFractions( ( m_extended ? m_nevents : 1 ) );
  buildMassPdf();
}
/*
// ####################################################################################################
void JpsiKsSimPdf::setTimeModel(TString setBkgType){
  m_bkgTauType = setBkgType;
  if(!(m_bkgTauType=="OneExp" || m_bkgTauType=="TwoExp")){
    std::cout << "ERROR: Unknown Background Decay Time Model." << std::endl;
  }
  
  // Re-Initialise
  std::cout << "* Re-initialising PDF" << std::endl;
  setToZero("Time");
  buildTimePdf(m_fitRel);
  buildtwoDPdf();
}
*/
// ####################################################################################################
// *** Destructor ***
JpsiKsSimPdf::~JpsiKsSimPdf() {
  // grep "* m_" JpsiKsSimPdf.h | awk -F"\*" '{print $2}' | awk -F";" '{print "  if("$1") delete"$1";"}'

  if(m_nBd_LL) delete m_nBd_LL;
  if(m_nBs_LL) delete m_nBs_LL;
  if(m_nKstar_LL) delete m_nKstar_LL;
  if(m_nonPeaking_LL) delete m_nonPeaking_LL;
  if(m_nBd_DD) delete m_nBd_DD;
  if(m_nBs_DD) delete m_nBs_DD;
  if(m_nKstar_DD) delete m_nKstar_DD;
  if(m_nonPeaking_DD) delete m_nonPeaking_DD;
  //  if(m_mass) delete m_mass; // not owned
  if(m_alpha) delete m_alpha;
  if(m_n) delete m_n;
  if(m_alpha2) delete m_alpha2;
  if(m_n2) delete m_n2;
  if(m_width_LL) delete m_width_LL;
  if(m_width_DD) delete m_width_DD;
  if(m_width2_LL) delete m_width2_LL;
  if(m_width2_DD) delete m_width2_DD;
  if(m_Bd_I_LL) delete m_Bd_I_LL;
  if(m_Bd_II_LL) delete m_Bd_II_LL;
  if(m_Bd_LL) delete m_Bd_LL;
  if(m_Bd_I_DD) delete m_Bd_I_DD;
  if(m_Bd_II_DD) delete m_Bd_II_DD;
  if(m_Bd_DD) delete m_Bd_DD;
  if(m_Bs_I_LL) delete m_Bs_II_LL;
  if(m_Bs_II_LL) delete m_Bs_LL;
  if(m_Bs_LL) delete m_Bs_I_LL;
  if(m_Bs_I_DD) delete m_Bs_II_DD;
  if(m_Bs_II_DD) delete m_Bs_DD;
  if(m_Bs_DD) delete m_Bs_I_DD;
  if(m_Kstar_cutoff) delete m_Kstar_cutoff;
  if(m_Kstar_cpar) delete m_Kstar_cpar;
  if(m_Kstar_ppar) delete m_Kstar_ppar;
  if(m_Kstar) delete m_Kstar;
  if(m_bkg1) delete m_bkg1;
  if(m_bkg2) delete m_bkg2;
  if(m_comBKG) delete m_comBKG;
  if(m_massPdf_LL) delete m_massPdf_LL;
  if(m_massPdf_DD) delete m_massPdf_DD;
/*  
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
  if(m_decay_long) delete m_decay_long;
  if(m_decay_short) delete m_decay_short;
  if(m_decay_background) delete m_decay_background;
  if(m_accX) delete m_accX;
  if(m_accY) delete m_accY;
  if(m_accZ) delete m_accZ;
  if(m_accA) delete m_accA;
  if(m_accB) delete m_accB;
  if(m_accVeLo) delete m_accVeLo;
  if(m_acceptance_combi) delete m_acceptance_combi;
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
*/  
  std::cout << "* Deleting done" << std::endl;

}



// ####################################################################################################
// *** Definitions ***
void JpsiKsSimPdf::buildFractions(int nevents){

  // Individual Components 
  double fracBd = 0.5*nevents;
  double fracBs = (m_fitBs ? fracBd*fsBr : 0.);
  double fracKs = (m_fitKstar ? 0.001*fracBd : 0.);
  double fracCombi = nevents-fracBd-fracBs-fracKs;
  
  // RooRealVars
  m_nBd_LL = new RooRealVar(m_name+"nBd_LL", "number of Bd",fracBd, 0.0, 1.0*nevents);
  m_nBs_LL = new RooRealVar(m_name+"nBs_LL","number of Bs",fracBs, 0.0, 0.15*nevents);
  m_nKstar_LL = new RooRealVar(m_name+"nKstar_LL","number of Kstar", fracKs, 0.0, 0.1*nevents);
  m_nonPeaking_LL = new RooRealVar(m_name+"nonPeaking_LL","number of Background not peaking", fracCombi, 0.0, 1.0*nevents);
  m_nBd_DD = new RooRealVar(m_name+"nBd_DD", "number of Bd",fracBd, 0.0, 1.0*nevents);
  m_nBs_DD = new RooRealVar(m_name+"nBs_DD","number of Bs",fracBs, 0.0, 0.15*nevents);
  m_nKstar_DD = new RooRealVar(m_name+"nKstar_DD","number of Kstar", fracKs, 0.0, 0.1*nevents);
  m_nonPeaking_DD = new RooRealVar(m_name+"nonPeaking_DD","number of Background not peaking", fracCombi, 0.0, 1.0*nevents);
}

// ####################################################################################################
void JpsiKsSimPdf::buildMassPdf(){

/* 
Setup
=====
- Fix CB tail parameters (alpha and n) from Bu2JpsiK
apar_I  =  1.113
apar_II = -1.05
npar_I  = 16.0
npar_II = 11.2

- CB have equal sigma  

NNCut = 0.28
============
    Floating Parameter    FinalValue +/-  Error   
  --------------------  --------------------------
                  frac    6.7521e-01 +/-  3.23e-02
                lambda   -2.7243e-03 +/-  5.50e-04
                meanBd    5.2782e+03 +/-  1.09e-01
                   nBd    8.3588e+03 +/-  9.37e+01
                  nBkg    6.1301e+02 +/-  3.65e+01
               sigma_I    7.3535e+00 +/-  8.11e-02  
*/

  // *** Signal Bd ***
  m_meanBd = new RooRealVar(m_name+"meanBd","mean Bd mass", 5279.50, 5279.50-10., 5279.50+10.);
  m_width_LL = new RooRealVar(m_name+"width_LL","width", 7., 3.0, 15.);
  m_width_DD = new RooRealVar(m_name+"width_DD","width", 7., 3.0, 15.);

  // Individual Components
  if(m_sigType=="CB" || m_sigType=="DoubleCB" || m_sigType=="GaussCB"){
    m_alpha = new RooRealVar(m_name+"alpha","alpha",1.113); // Fixed from Bu2JpsiK
    m_n = new RooRealVar(m_name+"n","n",16.0); // Fixed from Bu2JpsiK
    m_Bd_I_LL = new RooCBShape(m_name+"CBshapeBd_LL","Bd Crystal Ball",*m_mass,*m_meanBd,*m_width_LL,*m_alpha,*m_n);
    m_Bd_I_DD = new RooCBShape(m_name+"CBshapeBd_DD","Bd Crystal Ball",*m_mass,*m_meanBd,*m_width_DD,*m_alpha,*m_n);
  }
  if(m_sigType=="DoubleCB"){
    m_alpha2 = new RooRealVar(m_name+"alpha2","alpha2",-1.05); // Fixed from Bu2JpsiK 
    m_n2 = new RooRealVar(m_name+"n2","n2",11.2); // Fixed from Bu2JpsiK
    m_Bd_II_LL = new RooCBShape(m_name+"CBshapeBd_refl_LL","Bd Refl Crystal Ball",*m_mass,*m_meanBd,*m_width_LL,*m_alpha2,*m_n2);
    m_Bd_II_DD = new RooCBShape(m_name+"CBshapeBd_refl_DD","Bd Refl Crystal Ball",*m_mass,*m_meanBd,*m_width_DD,*m_alpha2,*m_n2);
  }
  if(m_sigType=="Gauss" || m_sigType=="DoubleGauss"){
    m_Bd_I_LL = new RooGaussian(m_name+"BdGauss_core_LL", "Bd core gaussian" , *m_mass, *m_meanBd, *m_width_LL);
    m_Bd_I_DD = new RooGaussian(m_name+"BdGauss_core_DD", "Bd core gaussian" , *m_mass, *m_meanBd, *m_width_DD);
  }
  if(m_sigType=="GaussCB" || m_sigType=="DoubleGauss"){
    m_width2_LL = new RooRealVar(m_name+"width2_LL","width2",10. , 7., 25.);
    m_width2_DD = new RooRealVar(m_name+"width2_DD","width2",10. , 7., 25.);
    m_Bd_II_LL = new RooGaussian(m_name+"BdGauss_wide_LL", "Bd wide gaussian" , *m_mass, *m_meanBd, *m_width2_LL);
    m_Bd_II_DD = new RooGaussian(m_name+"BdGauss_wide_DD", "Bd wide gaussian" , *m_mass, *m_meanBd, *m_width2_DD);
  }
  
  // Final Model
  if(m_sigType=="CB"){
    std::cout << " SETUP: Signal Model = Single Crystal Ball" << std::endl;
    m_Bd_LL = (RooAbsPdf *)m_Bd_I_LL;
    m_Bd_DD = (RooAbsPdf *)m_Bd_I_DD;
  }
  if(m_sigType=="Gauss"){
    std::cout << " SETUP: Signal Model = Single Gauss" << std::endl;
    m_Bd_LL = (RooAbsPdf *)m_Bd_I_LL;
    m_Bd_DD = (RooAbsPdf *)m_Bd_I_DD;
  }
  if(m_sigType=="DoubleCB") std::cout << " SETUP: Signal Model = Double Crystal Ball" << std::endl;
  if(m_sigType=="GaussCB") std::cout << " SETUP: Signal Model = Gauss + Crystal Ball" << std::endl;
  if(m_sigType=="DoubleGauss") std::cout << " SETUP: Signal Model = Double Gauss" << std::endl;
  if(m_sigType=="DoubleCB" || m_sigType=="GaussCB" || m_sigType=="DoubleGauss"){
    m_frac_LL = new RooRealVar(m_name+"frac_LL", "Fraction of narrow component", 0.5, 0.0, 1.0);
    m_frac_DD = new RooRealVar(m_name+"frac_DD", "Fraction of narrow component", 0.5, 0.0, 1.0);
    m_Bd_LL = new RooAddPdf(m_name+"Bd_PDF_LL","Bd PDF",RooArgList(*m_Bd_I_LL,*m_Bd_II_LL),RooArgList(*m_frac_LL));
    m_Bd_DD = new RooAddPdf(m_name+"Bd_PDF_DD","Bd PDF",RooArgList(*m_Bd_I_DD,*m_Bd_II_DD),RooArgList(*m_frac_DD));
  }

  // *** Signal Bs ***  
  if(m_fitBs){
    m_massDiff = new RooRealVar(m_name+"MassDiff","Bs - Bd mass difference", 87.52);
    m_meanBs = new RooFormulaVar(m_name+"meanBs","@0+@1", RooArgSet(*m_meanBd,*m_massDiff) );
    
    // Individual Components
    if(m_sigType=="CB" || m_sigType=="DoubleCB" || m_sigType=="GaussCB"){
      m_Bs_I_LL = new RooCBShape(m_name+"CBshapeBs_LL","Bs Crystal Ball",*m_mass,*m_meanBs,*m_width_LL,*m_alpha,*m_n);
      m_Bs_I_DD = new RooCBShape(m_name+"CBshapeBs_DD","Bs Crystal Ball",*m_mass,*m_meanBs,*m_width_DD,*m_alpha,*m_n);
    }
    if(m_sigType=="DoubleCB"){
      m_Bs_II_LL = new RooCBShape(m_name+"CBshapeBs_refl_LL","Bs Refl Crystal Ball",*m_mass,*m_meanBs,*m_width_LL,*m_alpha2,*m_n2);
      m_Bs_II_DD = new RooCBShape(m_name+"CBshapeBs_refl_DD","Bs Refl Crystal Ball",*m_mass,*m_meanBs,*m_width_DD,*m_alpha2,*m_n2);
    }
    if(m_sigType=="Gauss" || m_sigType=="DoubleGauss"){
      m_Bs_I_LL = new RooGaussian(m_name+"BsGauss_core_LL", "Bs core gaussian" , *m_mass, *m_meanBs, *m_width_LL);
      m_Bs_I_DD = new RooGaussian(m_name+"BsGauss_core_DD", "Bs core gaussian" , *m_mass, *m_meanBs, *m_width_DD);
    }
    if(m_sigType=="GaussCB" || m_sigType=="DoubleGauss"){
      m_Bs_II_LL = new RooGaussian(m_name+"BsGauss_wide_LL", "Bs wide gaussian" , *m_mass, *m_meanBs, *m_width2_LL);
      m_Bs_II_DD = new RooGaussian(m_name+"BsGauss_wide_DD", "Bs wide gaussian" , *m_mass, *m_meanBs, *m_width2_DD);
    }
  
    // Final Model
    if(m_sigType=="CB" || m_sigType=="Gauss"){
      m_Bs_LL = (RooAbsPdf *)m_Bs_I_LL;
      m_Bs_DD = (RooAbsPdf *)m_Bs_I_DD;
    }
    if(m_sigType=="DoubleCB" || m_sigType=="GaussCB" || m_sigType=="DoubleGauss"){
      m_Bs_LL = new RooAddPdf(m_name+"Bs_PDF_LL","Bs PDF",RooArgList(*m_Bs_I_LL,*m_Bs_II_LL),RooArgList(*m_frac_LL));
      m_Bs_DD = new RooAddPdf(m_name+"Bs_PDF_DD","Bs PDF",RooArgList(*m_Bs_I_DD,*m_Bs_II_DD),RooArgList(*m_frac_DD));
    }
  }
  else{
    m_Bs_LL = 0;
    m_Bs_DD = 0;
  }
  
  // *** Peaking Background ***
  if(m_fitKstar){
    if(m_KstarType=="Argus"){
      std::cout << " SETUP: Kstar Model = Argus" << std::endl;
      m_Kstar_cutoff = new RooRealVar(m_name+"Kstar cutoff","Argus Cutoff",5230,5150.,5250.);
      m_Kstar_cpar = new RooRealVar(m_name+"Kstar slope","Argus Slope",-0.5,-1.,0.);
      m_Kstar_ppar = new RooRealVar(m_name+"Kstar power","Argus power",0.5,0.,1.5);
      m_Kstar = new RooArgusBG(m_name+"Argus","Kstar BKG",*m_mass,*m_Kstar_cutoff,*m_Kstar_cpar,*m_Kstar_ppar);
    }
    else if(m_KstarType=="Gauss"){
      std::cout << " SETUP: Kstar Model = Gauss" << std::endl;
      m_Kstar_cutoff = new RooRealVar(m_name+"Kstar mean","mean",5150,5100,5220);
      m_Kstar_cpar = new RooRealVar(m_name+"Kstar sigma","sigma",10.,1.,50.);
      m_Kstar = new RooGaussian(m_name+"GaussKstar","Kstar BKG",*m_mass,*m_Kstar_cutoff,*m_Kstar_cpar);
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
  m_massPdf_LL = new RooAddPdf(m_name+"massPdf_LL", "Mass PDF for Sig + Bkg" , massPdfList(m_LL), fracPdfList(m_LL));
  m_massPdf_DD = new RooAddPdf(m_name+"massPdf_DD", "Mass PDF for Sig + Bkg" , massPdfList(m_DD), fracPdfList(m_DD));
  if(m_extended && !m_massPdf_LL->canBeExtended()) std::cout << "ERROR: PDF cannot be extended, although requested" << std::endl;  
}
/*
// ####################################################################################################
void JpsiKsSimPdf::buildTimePdf(bool fitRel){

  // *** Resolution ***	
  std::cout << " SETUP: Resolution Model = triple Gaussian" << std::endl;
  m_resMean = new RooRealVar(m_name+"resMean","Resolution - Mean",0.0,"ps");
	m_coreSigma = new RooRealVar(m_name+"coreSigma","Resolution - Core Width",0.0398,"ps");
	m_midSigma = new RooRealVar(m_name+"midSigma","Resolution - Middle Width",0.0709,"ps");
	m_tailSigma = new RooRealVar(m_name+"tailSigma","Resolution - Tail Width",0.229,"ps");
  m_Corefrac = new RooRealVar(m_name+"Corefrac","Fraction of Core", 0.737);
  m_Midfrac = new RooRealVar(m_name+"Midfrac","Fraction of Middle", 0.255);
  
  m_core = new RooGaussModel(m_name+"core","Core Gaussian",*m_tau,*m_resMean,*m_coreSigma);
  m_mid = new RooGaussModel(m_name+"mid","Middle Gaussian",*m_tau,*m_resMean,*m_midSigma);
  m_tail = new RooGaussModel(m_name+"tail","Tail Gaussian",*m_tau,*m_resMean,*m_tailSigma);
  m_resModel = new RooAddModel(m_name+"resModel","Resolution Model",RooArgList(*m_core,*m_mid,*m_tail),
                               RooArgList(*m_Corefrac,*m_Midfrac));
  
  
  // *** Background ***
  std::cout << " SETUP: Background Model = Short + Long-lived Exponential" << std::endl;
  m_tau_long = new RooRealVar(m_name+"tau_long","Long Lifetime for Bkg",1.525,1.,2.,"ps");	
	m_tau_short = new RooRealVar(m_name+"tau_short","Short lifetime for Bkg",0.3,0.,1.5,"ps");
  m_frac_bkg = new RooRealVar(m_name+"frac_bkg","Fraction of Short",0.5,0.,1.);
  
	m_decay_long = new RooDecay(m_name+"decay_long","Long Lifetimes",*m_tau,*m_tau_long,*m_resModel,RooDecay::SingleSided);
  if(m_bkgTauType=="TwoExp"){
	  m_decay_short = new RooDecay(m_name+"decay_short","Short Lifetimes",*m_tau,*m_tau_short,*m_resModel,RooDecay::SingleSided);
    m_decay_background = new RooAddPdf(m_name+"decay_background","Background Model",RooArgList(*m_decay_short,*m_decay_long),
                                     *m_frac_bkg);
  }
  else if(m_bkgTauType=="OneExp"){
    m_decay_background = m_decay_long;
  }
  else std::cout << "ERROR: No background decay time model specified. \n" << std::endl;
  
  // *** Acceptance ***
  std::cout << " SETUP: Acceptance = x*(1-Exp(-(tau-z)*y))*(1-Exp(-(b-tau)*a))*(1+VeLo*tau)" << std::endl;
	m_accX = new RooRealVar(m_name+"accX","For Acceptance Function",0.67709,0.5,1.);
	m_accY = new RooRealVar(m_name+"accY","For Acceptance Function",1.02327,0.,2.);
	m_accZ = new RooRealVar(m_name+"accZ","For Acceptance Function",-0.0395487,-0.5,0.5);	
	m_accA = new RooRealVar(m_name+"accA","For Acceptance Function",0.425515,0.,1.);
	m_accB = new RooRealVar(m_name+"accB","For Acceptance Function",15.5247,15.,16.);
  m_accVeLo = new RooRealVar(m_name+"accVeLo","For Acceptance Function",0.); // Without Velo effect
  
  m_acceptance_combi = new RooFormulaVar(m_name+"acceptance_combi","The overall acceptance function",
                           "@0*(1-TMath::Exp(-(@6-@2)*@1))*(1-TMath::Exp(-(@4-@6)*@3))*(1+@5*@6)",
                            RooArgList(*m_accX,*m_accY,*m_accZ,*m_accA,*m_accB,*m_accVeLo,*m_tau));

	// *** Signal ***
  std::cout << " SETUP: Signal Model = Single Exponential" << std::endl;
  // HFAG 2012: 1.519 +/- 0.007 && LHCb-ANA-2011-001: 1.558 +/- 0.056 (stat.) +/- 0.022 (syst.)
	m_tau_Bd = new RooRealVar(m_name+"tau_Bd","Average lifetime for Bd",1.519,1.,2.,"ps");
	m_tau_Bs = new RooRealVar(m_name+"tau_Bs","Average lifetime for Bs",1.525,0.,3.,"ps");
  m_tau_Bsunblind = new RooUnblindUniform(m_name+"tau_Bsunblind","Unblinded value of tau_Bs","BsEffLifetime",0.5,*m_tau_Bs);

	m_decay_Bd = new RooDecay(m_name+"decay_Bd","Fitted Decay",*m_tau,*m_tau_Bd,*m_resModel,RooDecay::SingleSided);
	m_decay_acc_Bd = new RooEffProd(m_name+"decay_acc_Bd","Decay with acceptance",*m_decay_Bd,*m_acceptance_combi);
  if(m_fitBs){
	  m_decay_Bs = new RooDecay(m_name+"decay_Bs","Fitted Decay",*m_tau,*m_tau_Bsunblind,*m_resModel,RooDecay::SingleSided);
	  m_decay_acc_Bs = new RooEffProd(m_name+"decay_acc_Bs","Decay with acceptance",*m_decay_Bs,*m_acceptance_combi);
    std::cout << " WARNING: Bs Lifetime has been Blinded" << std::endl;
  }
  else m_decay_acc_Bs = 0;
  
  // *** Composite Model ***
  m_lifetimePdf = new RooAddPdf(m_name+"lifetimePdf", "lifetime PDF for Sig + Bkg" , lifetimePdfList(), fracPdfList());
  
  // *** Type of measurement ***
  
  // For Absolute measurements: Freeze acceptance parameters
  if(!fitRel){
    std::cout << " SETUP: Performing absolute measurement" << std::endl;
    m_accX->setConstant();
    m_accY->setConstant();
    m_accZ->setConstant();
    m_accA->setConstant();
    m_accB->setConstant();    
  }
  else{
    std::cout << " SETUP: Performing relative measurement" << std::endl;
    m_tau_Bd->setConstant();
    // For now fix tail to MC11a
    m_accA->setConstant();
    m_accB->setConstant();
  }
}

// ####################################################################################################
void JpsiKsSimPdf::buildtwoDPdf(){
  std::cout << " SETUP: Building 2D PDF \n" << std::endl;

  m_twoD_Bd = new RooProdPdf(m_name+"twoD_Bd","Signal PDF",RooArgList(*m_Bd,*m_decay_acc_Bd));
  if(m_fitBs) m_twoD_Bs = new RooProdPdf(m_name+"twoD_Bs","Signal PDF",RooArgList(*m_Bs,*m_decay_acc_Bs));
  else m_twoD_Bs = 0;
  if(m_fitKstar) m_twoD_Kstar = new RooProdPdf(m_name+"twoD_Kstar","Background PDF",RooArgList(*m_Kstar,*m_decay_background));
  else m_twoD_Kstar = 0;
  m_twoD_comBKG = new RooProdPdf(m_name+"twoD_comBKG","Background PDF",RooArgList(*m_comBKG,*m_decay_background));
  
  m_twoDPdf = new RooAddPdf(m_name+"twoDPdf","PDF for Sig_Bkg",twoDPdfList(), fracPdfList());

}
*/
// ####################################################################################################
// *** Accessors ***

// PDF fractions
RooArgList JpsiKsSimPdf::fracPdfList(unsigned int tracktype)const{
  RooArgList fracList;
  if(tracktype==m_LL){
    fracList.add(*m_nBd_LL);
    if (m_fitBs) fracList.add(*m_nBs_LL);
    if (m_fitKstar) fracList.add(*m_nKstar_LL);
    if (m_extended) fracList.add(*m_nonPeaking_LL);
  }
  if(tracktype==m_DD){
    fracList.add(*m_nBd_DD);
    if (m_fitBs) fracList.add(*m_nBs_DD);
    if (m_fitKstar) fracList.add(*m_nKstar_DD);
    if (m_extended) fracList.add(*m_nonPeaking_DD);
  }
  return fracList;
}

// PDFs - WARNING: Synchronize with above
RooArgList JpsiKsSimPdf::massPdfList(unsigned int tracktype)const{
  RooArgList pdfList;
  if(tracktype==m_LL){
    pdfList.add(*m_Bd_LL);
    if (m_fitBs) pdfList.add(*m_Bs_LL);
  }
  if(tracktype==m_DD){
    pdfList.add(*m_Bd_DD);
    if (m_fitBs) pdfList.add(*m_Bs_DD);
  }
  if (m_fitKstar) pdfList.add(*m_Kstar); 
  pdfList.add(*m_comBKG);
  return pdfList;
};
/*
RooArgList JpsiKsSimPdf::lifetimePdfList()const{
  RooArgList pdfList;
  pdfList.add(*m_decay_acc_Bd);
  if (m_fitBs) pdfList.add(*m_decay_acc_Bs);
  if (m_fitKstar) pdfList.add(*m_decay_background); // no dedicated lifetime model
  pdfList.add(*m_decay_background);
  return pdfList;
};

RooArgList JpsiKsSimPdf::twoDPdfList()const{
  RooArgList pdfList;
  pdfList.add(*m_twoD_Bd);
  if (m_fitBs) pdfList.add(*m_twoD_Bs);
  if (m_fitKstar) pdfList.add(*m_twoD_Kstar);
  pdfList.add(*m_twoD_comBKG);
  return pdfList;
};
*/
// ####################################################################################################
// *** Redefine Fit Functions ***
RooFitResult* JpsiKsSimPdf::fitToMass(RooDataSet* data_LL,RooDataSet* data_DD, bool doSumW2, TString range){
  
  // *** Combined data sample ***
  RooCategory *m_trackType = new RooCategory("m_trackType","Combine LL and DD");
  m_trackType->defineType("LL");
  m_trackType->defineType("DD");
  
  RooDataSet *m_combiData = new RooDataSet("m_combiData","Combined data sample",RooArgList(*m_mass),Index(*m_trackType),Import("LL",*data_LL),Import("DD",*data_DD));

  RooSimultaneous *m_combiPdf = new RooSimultaneous("m_combiPdf","Simultaneous PDF",*m_trackType);
  m_combiPdf->addPdf(*m_massPdf_LL,"LL");
  m_combiPdf->addPdf(*m_massPdf_DD,"DD");
  
  // *** Fit ***
  if(range==""){
    if(doSumW2) return m_combiPdf->fitTo(*m_combiData, Save(), SumW2Error(true));
    else return m_combiPdf->fitTo(*m_combiData,Save());
  }
  else{
    if(doSumW2) return m_combiPdf->fitTo(*m_combiData, Save(), Range(range),SumW2Error(true));
    else return m_combiPdf->fitTo(*m_combiData,Save(), Range(range));
  }
}

/*
RooFitResult* JpsiKsSimPdf::fitToAll(RooDataSet* data, bool doSumW2){
  if(doSumW2) return m_twoDPdf->fitTo(*data, Save(), SumW2Error(true));
  else return m_twoDPdf->fitTo(*data, Save());
}
*/
// ####################################################################################################
// *** Plot PDF ***
void JpsiKsSimPdf::plotOn(TCanvas* doek, RooDataSet* data,unsigned int tracktype, bool doSumW2, Int_t logy, bool param){

  std::cout << "@@ Start Plotting PDF" << std::endl;

  // *** Frame ***
	RooPlot* massFrame = m_mass->frame(Bins((m_mass->getMax() - m_mass->getMin())/5));

	// Titles
  massFrame->SetTitle("");
	massFrame->SetYTitle("Events/(5 MeV/c^{2})");
	massFrame->SetXTitle("m_{J/#psi K_{S}} [MeV/c^{2}]");
  
  // Data
  if(doSumW2) data->plotOn(massFrame, DataError(RooAbsData::SumW2),MarkerStyle(8),MarkerSize(0.8));
  else data->plotOn(massFrame,MarkerStyle(8),MarkerSize(0.8));
  
  // PDF components
  if (!m_massPdf_LL) {
    std::cout <<"Can't plot null" << std::endl;
    return;
  }
  if(tracktype==m_LL){
    m_massPdf_LL->plotOn(massFrame, Components(*m_Bd_LL), Range(m_mass->getMin(),m_mass->getMax()),
      FillColor(m_BdCol), FillStyle(1001), DrawOption("F"));
    if (m_Bs_LL) m_massPdf_LL->plotOn(massFrame, Components(*m_Bs_LL), Range(m_mass->getMin(),m_mass->getMax()),
      FillColor(m_BsCol), FillStyle(1001), DrawOption("F"));
    m_massPdf_LL->plotOn(massFrame, Components(*m_comBKG), Range(m_mass->getMin(),m_mass->getMax()),
      LineStyle(kDashed), LineColor(kBlack) );
    if (m_Kstar) m_massPdf_LL->plotOn(massFrame, Components(*m_Kstar), Range(m_mass->getMin(),m_mass->getMax()),
      FillColor(m_KstarCol), FillStyle(1001), DrawOption("F"));
  }
  else if(tracktype==m_DD){
    m_massPdf_DD->plotOn(massFrame, Components(*m_Bd_DD), Range(m_mass->getMin(),m_mass->getMax()),
      FillColor(m_BdCol), FillStyle(1001), DrawOption("F"));
    if (m_Bs_DD) m_massPdf_DD->plotOn(massFrame, Components(*m_Bs_DD), Range(m_mass->getMin(),m_mass->getMax()),
      FillColor(m_BsCol), FillStyle(1001), DrawOption("F"));
    m_massPdf_DD->plotOn(massFrame, Components(*m_comBKG), Range(m_mass->getMin(),m_mass->getMax()),
      LineStyle(kDashed), LineColor(kBlack) );
    if (m_Kstar) m_massPdf_DD->plotOn(massFrame, Components(*m_Kstar), Range(m_mass->getMin(),m_mass->getMax()),
      FillColor(m_KstarCol), FillStyle(1001), DrawOption("F"));
  }
  
  // Data
  if(doSumW2) data->plotOn(massFrame, DataError(RooAbsData::SumW2),MarkerStyle(8),MarkerSize(0.8));
  else data->plotOn(massFrame,MarkerStyle(8),MarkerSize(0.8));
  if(tracktype==m_LL) m_massPdf_LL->plotOn(massFrame, Range(m_mass->getMin(),m_mass->getMax()), LineColor(1) );
  else if(tracktype==m_DD) m_massPdf_DD->plotOn(massFrame, Range(m_mass->getMin(),m_mass->getMax()), LineColor(1) );
  
  std::cout << "@@ Finished Plotting PDF" << std::endl;  

  // Add Parameters and pull
  if(param){
    if(tracktype==m_LL) m_massPdf_LL->paramOn(massFrame,Layout(0.5,0.92,0.92));
    else if(tracktype==m_DD) m_massPdf_DD->paramOn(massFrame,Layout(0.5,0.92,0.92));
    massFrame->getAttText()->SetTextSize(0.03);
    std::cout << "@@ Adding Pull" << std::endl; 
    AddPull(doek,massFrame,logy); 
  }
  else{
    doek->SetLeftMargin(0.2);
    doek->SetBottomMargin(0.15);
    doek->cd(1);
    gPad->SetLogy(logy);
    massFrame->Draw("");
  }
}
/*
void JpsiKsSimPdf::plotOnTime(TCanvas* doek, RooDataSet* data, bool doSumW2, Int_t logy, bool param){

  std::cout << "@@ Start Plotting PDF" << std::endl;

  // *** Frame ***
	RooPlot* timeFrame = m_tau->frame(Bins((m_tau->getMax() - m_tau->getMin())/0.2));

	// Titles
  timeFrame->SetTitle("");
	timeFrame->SetYTitle("Events/(0.2 ps)");
	timeFrame->SetXTitle("B decay time [ps]");
  
  // Data
  if(doSumW2) data->plotOn(timeFrame, DataError(RooAbsData::SumW2),MarkerStyle(8),MarkerSize(0.8));
  else data->plotOn(timeFrame,MarkerStyle(8),MarkerSize(0.8));
  
  // PDF components
  if (!m_lifetimePdf) {
    std::cout <<"Can't plot null" << std::endl;
    return;
  }
  m_lifetimePdf->plotOn(timeFrame, Components(*m_decay_acc_Bd), Range(m_tau->getMin(),m_tau->getMax()),
    LineColor(m_BdCol));
  if (m_Bs) m_lifetimePdf->plotOn(timeFrame, Components(*m_decay_acc_Bs), Range(m_tau->getMin(),m_tau->getMax()),
    LineColor(m_BsCol));
  m_lifetimePdf->plotOn(timeFrame, Components(*m_decay_background), Range(m_tau->getMin(),m_tau->getMax()),
    LineStyle(kDashed), LineColor(kBlack) );
  m_lifetimePdf->plotOn(timeFrame, Range(m_tau->getMin(),m_tau->getMax()), LineColor(1) );
  
  std::cout << "@@ Finished Plotting PDF" << std::endl;
  
  timeFrame->SetMinimum(1.);

  // Add Parameters and pull
  if(param){
    m_lifetimePdf->paramOn(timeFrame,Layout(0.5,0.92,0.92));
    timeFrame->getAttText()->SetTextSize(0.03);
    std::cout << "@@ Adding Pull" << std::endl; 
    AddPull(doek,timeFrame,logy); 
  }
  else{
    doek->SetLeftMargin(0.2);
    doek->SetBottomMargin(0.15);
    doek->cd(1);
    gPad->SetLogy(logy);
    timeFrame->Draw("");
  }
}
*/
// ####################################################################################################
// *** Legend ***
void JpsiKsSimPdf::plotLegend(double x1,double y1,double x2,double y2) const {
  std::cout << "@@ Starting Legend" << std::endl;
  TLegend* leg = new TLegend(x1,y1,x2,y2,""); // memory leak

  TGraphErrors* gr = new TGraphErrors(1);
  gr->SetLineWidth(2);
  leg->AddEntry(gr,"data","lep"); 

  TH1F* HBs = new TH1F("Bs","Bs",10,0,1);
  HBs->SetLineColor(0);  
  HBs->SetFillColor(m_BsCol);  
  if (m_Bs_LL) { // This macro is not design to work with Bu2JpsiKs and B2JpsiPhi anyway
    //if (m_name=="B2JpsiKs") 
    leg->AddEntry(HBs,"B_{s}^{0}#rightarrow J/#psiK_{S}^{0}","f"); 
    //else if (m_name=="Bu2JpsiK") std::cout << "No charged Bs" << std::endl;
    //else if (m_name=="Bs2JpsiPhi") leg->AddEntry(HBs,"B_{s}^{0}#rightarrow J/#psi#phi","f"); 
    //else std::cout << "Unknown name " << m_name << std::endl;
  }
  
  TH1F* HBd = new TH1F("Bd","Bd",10,0,1);
  HBd->SetLineColor(0);  
  HBd->SetFillColor(m_BdCol);  
  if (m_Bd_LL) {
    //if (m_name=="B2JpsiKs") 
    leg->AddEntry(HBd,"B^{0}#rightarrow J/#psiK_{S}^{0}","f");  
    //else if (m_name=="Bu2JpsiK") leg->AddEntry(HBd,"B^{+}#rightarrow J/#psiK^{+}","f");  
    //else if (m_name=="Bs2JpsiPhi") leg->AddEntry(HBd,"B^{0}#rightarrow J/#psi#phi","f"); 
    //else std::cout << "Unknown name " << m_name << std::endl;
  }

  TH1F* HKstar = new TH1F("Kstar","Kstar",10,0,1);
  HKstar->SetLineColor(0);  
  HKstar->SetFillColor(m_KstarCol);  
  if (m_Kstar) leg->AddEntry(HKstar,"B#rightarrow J/#psiK_{S}^{0}X","f");
  
  TF1* bkg = new TF1("bkg","x",0,1);
  bkg->SetLineColor(1);
  bkg->SetLineWidth(2);  
  bkg->SetLineStyle(kDashed);  
  leg->AddEntry(bkg,"background","l"); 

  TF1* sum = new TF1("sum","x",0,1);
  sum->SetLineColor(1);
  sum->SetLineWidth(2);  
  leg->AddEntry(sum,"sum","l"); 

  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);

  std::cout << "@@ Adding Legend" << std::endl;
  leg->Draw("same");
}

// ####################################################################################################