// ####################################################################################################
// Phys/Bs2JpsiKs Package
// PDF description
// Authors: Patrick Koppenburg & Kristof De Bruyn
// ####################################################################################################

#ifndef B2JPSIKS_JPSIKSSIMPDF_H 
#define B2JPSIKS_JPSIKSSIMPDF_H

// ####################################################################################################
// *** Load Useful Classes ***

// From RooFit
#include "RooAbsReal.h"
#include "RooAddModel.h"
#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooArgusBG.h"
#include "RooCategory.h"
#include "RooCBShape.h"
#include "RooChebychev.h"
#include "RooCmdArg.h"
#include "RooDataSet.h"
#include "RooDecay.h"
#include "RooEffProd.h"
#include "RooExponential.h"
#include "RooFitResult.h"
#include "RooFormulaVar.h"
#include "RooGaussian.h"
#include "RooGaussModel.h"
#include "RooPlot.h"
#include "RooProdPdf.h"
#include "RooRealVar.h"
#include "RooSimultaneous.h"
#include "RooUnblindUniform.h"
#include "RooUniform.h"

// From ROOT
#include "TF1.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TLegend.h"

// From Bs2JpsiKs Package
#include "IB2JpsiX.h"

using namespace RooFit;

void AddPull(TCanvas* pullCanvas, RooPlot* frame, Int_t logy);

class JpsiKsSimPdf {
public: 
// ####################################################################################################
// *** Constructors - Destructors *** 
  JpsiKsSimPdf(TString name, RooRealVar* mass, bool fitBs, bool fitKstar, int nevents);
  //JpsiKsSimPdf(TString name, RooRealVar* mass, RooRealVar* time, bool fitBs, bool fitKstar, bool fitRel, int nevents);

  virtual ~JpsiKsSimPdf( );

// ####################################################################################################
// *** Declarations ***

  void buildFractions(int nevents);
  void buildMassPdf();
  //void buildTimePdf(bool fitRel);
  //void buildtwoDPdf();

  RooFitResult* fitToMass(RooDataSet* data_LL,RooDataSet* data_DD, bool doSumW2, TString range = "");
  //RooFitResult* fitToAll(RooDataSet* data, bool doSumW2);
  
  void plotLegend(double x1=0.65,double y1=0.84,double x2=0.92,double y2=0.47) const;
  void plotOn(TCanvas* doek, RooDataSet* data, unsigned int tracktype, bool doSumW2, Int_t logy = 0, bool param = true );
  //void plotOnTime(TCanvas* doek, RooDataSet* data, bool doSumW2, Int_t logy = 0, bool param = true );
  
  void setConstant(TString which = "All");
  void setModel(TString setSigType, TString setKstarType, TString setBkgType);
  //void setTimeModel(TString setBkgType);
  void setToZero(TString which);


// ####################################################################################################
// *** Accessors ***
  RooRealVar* mass()const{return m_mass;};
  //RooRealVar* time()const{return m_tau;};
  
  RooRealVar* nBd(unsigned int tracktype)const{return (tracktype==m_LL ? m_nBd_LL : m_nBd_DD);};
  RooRealVar* nBs(unsigned int tracktype)const{return (tracktype==m_LL ? m_nBs_LL : m_nBs_DD);};
  RooRealVar* nKstar(unsigned int tracktype)const{return (tracktype==m_LL ? m_nKstar_LL : m_nKstar_DD);};
  RooRealVar* nonPeaking(unsigned int tracktype)const{return (tracktype==m_LL ? m_nonPeaking_LL : m_nonPeaking_DD);};
  
  RooAbsPdf* Bd(unsigned int tracktype)const{return (tracktype==m_LL ? m_Bd_LL : m_Bd_DD);};
  RooAbsPdf* Bs(unsigned int tracktype)const{return (tracktype==m_LL ? m_Bs_LL : m_Bs_DD);};
  RooAbsPdf* Kstar()const{return m_Kstar;};
  RooAbsPdf* comBKG()const{return m_comBKG;};
  RooAbsPdf* massPdf(unsigned int tracktype)const{return (tracktype==m_LL ? m_massPdf_LL : m_massPdf_DD);};
/*  
  RooAbsPdf* lifeBkg()const{return m_decay_background;};
  RooAbsPdf* lifeBd()const{return m_decay_acc_Bd;};
  RooAbsPdf* lifeBs()const{return m_decay_acc_Bs;};
  RooAbsPdf* lifetimePdf()const{return m_lifetimePdf;};

  RooAbsPdf* twoDBd()const{return m_twoD_Bd;};
  RooAbsPdf* twoDBs()const{return m_twoD_Bs;};
  RooAbsPdf* twoDKstar()const{return m_twoD_Kstar;}; 
  RooAbsPdf* twoDBKG()const{return m_twoD_comBKG;}; 
  RooAbsPdf* twoDPdf()const{return m_twoDPdf;};
*/  
  RooAbsReal* integralBKG(){
    m_mass->setRange("BsBox",BsBox_min,BsBox_max);
    return (RooAbsReal *)m_comBKG->createIntegral(*m_mass,NormSet(*m_mass),Range("BsBox"));
  }

  RooArgList fracPdfList(unsigned int tracktype)const;
  RooArgList massPdfList(unsigned int tracktype)const;
  //RooArgList lifetimePdfList()const;
  //RooArgList twoDPdfList()const;
  
  
private:
  // Settings
  TString m_name;
  bool m_fitBs;
  bool m_fitKstar;
  bool m_fitRel;
  bool m_extended;

  TString m_sigType;
  TString m_KstarType;  
  TString m_bkgType;
  TString m_bkgTauType;

  // Fractions
  Int_t m_nevents;
  RooRealVar* m_nBd_LL;
  RooRealVar* m_nBs_LL;
  RooRealVar* m_nKstar_LL;
  RooRealVar* m_nonPeaking_LL;
  RooRealVar* m_nBd_DD;
  RooRealVar* m_nBs_DD;
  RooRealVar* m_nKstar_DD;
  RooRealVar* m_nonPeaking_DD;
  
  // Mass PDF
  RooRealVar* m_mass;
  RooRealVar* m_meanBd;
  RooRealVar* m_massDiff;
  RooFormulaVar* m_meanBs;
  RooRealVar* m_width_LL;
  RooRealVar* m_width_DD;
  RooRealVar* m_width2_LL;
  RooRealVar* m_width2_DD;
  RooRealVar* m_frac_LL;
  RooRealVar* m_frac_DD;
  RooRealVar* m_alpha;
  RooRealVar* m_n;
  RooRealVar* m_alpha2;
  RooRealVar* m_n2;
  
  RooAbsPdf* m_Bd_LL;
  RooAbsPdf* m_Bd_I_LL;
  RooAbsPdf* m_Bd_II_LL;
  RooAbsPdf* m_Bd_DD;
  RooAbsPdf* m_Bd_I_DD;
  RooAbsPdf* m_Bd_II_DD;
  RooAbsPdf* m_Bs_LL;
  RooAbsPdf* m_Bs_I_LL;
  RooAbsPdf* m_Bs_II_LL;
  RooAbsPdf* m_Bs_DD;
  RooAbsPdf* m_Bs_I_DD;
  RooAbsPdf* m_Bs_II_DD;

  RooRealVar* m_Kstar_cutoff;
  RooRealVar* m_Kstar_cpar; 
  RooRealVar* m_Kstar_ppar;
  RooAbsPdf* m_Kstar;
  
  RooRealVar* m_bkg1;   
  RooRealVar* m_bkg2;   
  RooAbsPdf* m_comBKG;
  
  RooAddPdf* m_massPdf_LL;
  RooAddPdf* m_massPdf_DD;

/*
  // Lifetime PDF
  RooRealVar* m_tau;
  
  RooRealVar* m_resMean;
  RooRealVar* m_coreSigma;
  RooRealVar* m_midSigma;
  RooRealVar* m_tailSigma;
  RooRealVar* m_Corefrac;
  RooRealVar* m_Midfrac;
  RooGaussModel* m_core;
  RooGaussModel* m_mid;
  RooGaussModel* m_tail;
  RooAddModel* m_resModel;

  RooRealVar* m_tau_long;  
  RooRealVar* m_tau_short;
  RooRealVar* m_frac_bkg;
  RooDecay* m_decay_long;
  RooDecay* m_decay_short;  
  RooAbsPdf* m_decay_background;

  RooRealVar* m_accX;
  RooRealVar* m_accY;
  RooRealVar* m_accZ;  
  RooRealVar* m_accA;
  RooRealVar* m_accB;
  RooRealVar* m_accVeLo;
  RooFormulaVar* m_acceptance_combi;
  
  RooRealVar* m_tau_Bd;
  RooRealVar* m_tau_Bs;
  RooUnblindUniform* m_tau_Bsunblind;
  RooDecay* m_decay_Bd;
  RooEffProd* m_decay_acc_Bd;
  RooDecay* m_decay_Bs;
  RooEffProd* m_decay_acc_Bs;

  RooAddPdf* m_lifetimePdf;

  // TwoD PDF
  RooProdPdf* m_twoD_Bd;
  RooProdPdf* m_twoD_Bs;
  RooProdPdf* m_twoD_Kstar;
  RooProdPdf* m_twoD_comBKG;
  RooAddPdf* m_twoDPdf; 
*/
};
#endif // B2JPSIKS_JPSIKSSIMPDF_H
