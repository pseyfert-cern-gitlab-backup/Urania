// ####################################################################################################
// Phys/Bs2JpsiKs Package
// PDF description
// Authors: Patrick Koppenburg & Kristof De Bruyn
// ####################################################################################################

#ifndef B2JPSIKS_JPSIKSPDF_H 
#define B2JPSIKS_JPSIKSPDF_H

// ####################################################################################################
// *** Load Useful Classes ***

// From RooFit
#include "RooAbsReal.h"
#include "RooAddModel.h"
#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooArgusBG.h"
#include "RooCBShape.h"
#include "RooChebychev.h"
#include "RooCmdArg.h"
#include "RooDataSet.h"
#include "RooDecay.h"
#include "RooEffProd.h"
#include "RooExpAndGauss.h"
#include "RooExponential.h"
#include "RooFitResult.h"
#include "RooFormulaVar.h"
#include "RooGaussian.h"
#include "RooGaussModel.h"
#include "RooPlot.h"
#include "RooProdPdf.h"
#include "RooRealVar.h"
#include "RooUnblindUniform.h"
#include "RooUniform.h"

// From ROOT
#include "TF1.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TMath.h"
#include "TLegend.h"

// From Bs2JpsiKs Package
#include "IB2JpsiX.h"

using namespace RooFit;

void AddPull(TCanvas* pullCanvas, RooPlot* frame, Int_t logy);
void AddPull(TCanvas* pullCanvas, RooPlot* frame, Int_t logy, double *chi2Val);

class JpsiKsPdf {
public: 
// ####################################################################################################
// *** Constructors - Destructors *** 
  JpsiKsPdf(TString name, RooRealVar* mass, bool fitBs, bool fitKstar, int ttype, TString setup, int nevents);
  JpsiKsPdf(TString name, RooRealVar* mass, RooRealVar* time, bool fitBs, bool fitKstar, int ttype, TString setup, int nevents);

  virtual ~JpsiKsPdf( );

// ####################################################################################################
// *** Declarations ***

  RooFitResult* fitToMass(RooDataSet* data, bool doSumW2);
  RooFitResult* fitToMass(RooDataSet* data, bool doSumW2, TString range);
  RooFitResult* fitToAll(RooDataSet* data, bool doSumW2);
  
  void plotLegend(double x1=0.65,double y1=0.84,double x2=0.92,double y2=0.47, TString what = "mass") const;
  void plotOn(TCanvas* doek, RooDataSet* data, bool doSumW2, Int_t logy, int param){
    double chi2Val[] = {-999,-999};
    plotOn(doek, data, doSumW2, logy, param, chi2Val);
  };
  void plotOn(TCanvas* doek, RooDataSet* data, bool doSumW2, Int_t logy, int param, double *chi2Val);
  void plotOnTime(TCanvas* doek, RooDataSet* data, bool doSumW2, Int_t logy, int param, int massBox){
    double chi2Val[] = {-999,-999};
    plotOnTime(doek, data, doSumW2, logy, param, massBox, chi2Val);
  };
  void plotOnTime(TCanvas* doek, RooDataSet* data, bool doSumW2, Int_t logy, int param, int massBox, double *chi2Val);
  
  void setConstant(TString which = "All");
  void setModel(TString setSigType, TString setKstarType, TString setBkgType, TString setSigTails = "Optimal");
  void setBdLifetime(TString setDiff);
  void setMassDiff(TString setDiff);
  void scaleMassWidth(TString setDiff);
  void setTimeModel(TString setResModel, TString setAccModel, TString setBkgType, bool fitRel);

  RooArgList fracPdfList()const;
  RooArgList massPdfList()const;
  RooArgList lifetimePdfList()const;
  RooArgList twoDPdfList()const;

// ####################################################################################################
// *** Accessors ***
  RooRealVar* mass()const{return m_mass;};
  RooRealVar* time()const{return m_tau;};
  
  RooRealVar* nBd()const{return m_nBd;};
  RooRealVar* nBs()const{return m_nBs;};
  RooRealVar* nKstar()const{return m_nKstar;};
  RooRealVar* nonPeaking()const{return m_nonPeaking;};
  RooRealVar* expo()const{return m_bkg1;};
  RooRealVar* pol1()const{return m_bkg1;};
  RooRealVar* pol2()const{return m_bkg2;};
  RooRealVar* frac()const{return m_frac;};
  RooRealVar* meanBd()const{return m_meanBd;};
  RooRealVar* width()const{return m_width;};
  RooRealVar* width2()const{return m_width2;};
  
  RooAbsPdf* Bd()const{return m_Bd;};
  RooAbsPdf* Bs()const{return m_Bs;};
  RooAbsPdf* Kstar()const{return m_Kstar;};
  RooAbsPdf* comBKG()const{return m_comBKG;};
  RooAbsPdf* massPdf()const{return m_massPdf;};
  
  RooRealVar* accY()const{return m_accY;};
  RooRealVar* accZ()const{return m_accZ;};
  RooRealVar* accOffset()const{return m_accOffset;};
  RooRealVar* accVelo()const{return m_accVelo;};
  RooRealVar* tauBd()const{return m_tau_Bd;};
  RooRealVar* tauBs()const{return m_tau_Bs;};
  RooRealVar* tauLong()const{return m_tau_long;};
  RooRealVar* tauShort()const{return m_tau_short;};
  RooRealVar* frac_bkg()const{return m_frac_bkg;};
  double unblindResult(){return m_tau_Bsunblind->getHiddenVal();};
  
  RooAbsPdf* lifeBkg()const{return m_decay_background;};
  RooAbsPdf* lifeBd()const{return m_decay_acc_Bd;};
  RooAbsPdf* lifeBs()const{return m_decay_acc_Bs;};
  RooAbsPdf* lifetimePdf()const{return m_lifetimePdf;};

  RooAbsPdf* twoDBd()const{return m_twoD_Bd;};
  RooAbsPdf* twoDBs()const{return m_twoD_Bs;};
  RooAbsPdf* twoDKstar()const{return m_twoD_Kstar;}; 
  RooAbsPdf* twoDBKG()const{return m_twoD_comBKG;}; 
  RooAbsPdf* twoDPdf()const{return m_twoDPdf;};
  
  RooAbsReal* integralBKG(){
    m_mass->setRange("BsBox",BsBox_min,BsBox_max);
    return (RooAbsReal *)m_comBKG->createIntegral(*m_mass,NormSet(*m_mass),Range("BsBox"));
  }
  
// ####################################################################################################
// *** Manipulators ***
  void setAlpha(double val){m_alpha->setVal(val);};
  void setAlpha2(double val){m_alpha2->setVal(val);};
  void setN(double val){m_n->setVal(val);};
  void setN2(double val){m_n2->setVal(val);};
  
  
private:
// ####################################################################################################
// *** Declarations ***
  void buildFractions(int nevents);
  void buildMassPdf();
  void buildTimePdf();
  void buildtwoDPdf();
  
  void setToZero(TString which);
  void reInitialise(TString which);
  void setTails();
  void setResolution();
  
// ####################################################################################################
// *** Initialisation ***
  // Settings
  TString m_name;
  bool m_fitBs;
  bool m_fitKstar;
  bool m_fitRel;
  bool m_extended;
  int m_ttype;
  TString m_setup;

  TString m_sigType;
  TString m_KstarType;  
  TString m_bkgType;
  TString m_bkgTauType;
  TString m_AccModel;
  TString m_ResModel;

  // Fractions
  Int_t m_nevents;
  RooRealVar* m_nBd;
  RooRealVar* m_nBs;
  RooRealVar* m_nKstar;
  RooRealVar* m_nonPeaking;
  
  // Mass PDF  
  RooRealVar* m_mass;
  RooRealVar*  m_meanBd;
  RooRealVar*  m_massDiff;
  RooFormulaVar*  m_meanBs;
  RooRealVar*  m_width;
  RooRealVar*  m_width2;
  RooRealVar* m_frac;
  RooRealVar* m_alpha;
  RooRealVar* m_n;
  RooRealVar* m_alpha2;
  RooRealVar* m_n2;
  RooRealVar* m_scale;
  RooRealVar* m_scale2;
  RooFormulaVar* m_Bswidth;
  RooFormulaVar* m_Bswidth2;
  
  RooAbsPdf* m_Bd;
  RooAbsPdf* m_Bd_I;
  RooAbsPdf* m_Bd_II;
  RooAbsPdf* m_Bs;
  RooAbsPdf* m_Bs_I;
  RooAbsPdf* m_Bs_II;

  RooRealVar* m_Kstar_mean;
  RooRealVar* m_Kstar_sigma; 
  RooRealVar* m_Kstar_shift;
  RooFormulaVar* m_Kstar_trans;
  RooAbsPdf* m_Kstar;
  
  RooRealVar* m_bkg1;   
  RooRealVar* m_bkg2;   
  RooAbsPdf* m_comBKG;
  RooAddPdf* m_massPdf;


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
  RooResolutionModel* m_resModel;

  RooRealVar* m_tau_long;  
  RooRealVar* m_tau_short;
  RooRealVar* m_frac_bkg;
  RooRealVar* m_bkgY;
  RooRealVar* m_bkgZ;
  RooFormulaVar* m_bkgAcc;
  RooDecay* m_decay_long;
  RooEffProd* m_decay_acc_bkg;
  RooDecay* m_decay_short;  
  RooAbsPdf* m_decay_background;

  RooRealVar* m_accY;
  RooRealVar* m_accZ;
  RooRealVar* m_accOffset;
  RooRealVar* m_accVelo;
  RooFormulaVar* m_acceptance;
  
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
};
#endif // B2JPSIKS_JPSIKSPDF_H
