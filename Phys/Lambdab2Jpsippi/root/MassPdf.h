// ####################################################################################################
// Phys/Bs2JpsiKs Package
// PDF description
// Authors: Patrick Koppenburg & Kristof De Bruyn
// ####################################################################################################

#ifndef MASSPDF_H 
#define MASSPDF_H
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
//#include "RooExpAndGauss.h"
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
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TLegend.h"

using namespace RooFit;

class MassPdf{
 public:
  MassPdf(TString name, RooRealVar* mass, int nevents,  TString opt="", 
	  TString sigType="DoubleCB", TString bkgType="Poly2");
  ~MassPdf();
  
// *** Redefine Fit Functions ***
  RooFitResult* fit(RooDataSet* data, bool doSumW2, TString range="");
  RooPlot* plotOn(TCanvas* doek, RooDataSet* data, bool doSumW2, Int_t logy, bool param, bool pull);
  RooArgList massPdfList()const{
    RooArgList pdfList;
    pdfList.add(*m_Lambdab);
    pdfList.add(*m_comBKG);
    return pdfList;
  };
  RooArgList fracPdfList()const{
    RooArgList fracList;
    fracList.add(*m_nLambdab);
    if (m_extended) fracList.add(*m_nonPeaking);
    return fracList;
  }
  // ####################################################################################################
  // *** Accessors ***
  void setName(TString name){m_name = name ;};
  RooRealVar* mass()const{return m_mass;};
  RooRealVar* nLambdab()const { return m_nLambdab ;}; 
  RooRealVar* nNonPeaking(){ return m_nonPeaking ;};
  RooAbsPdf* pdf(){ return m_massPdf ;}; 
  void setConstant(TString which = "Signal") ;
  void setConstant(const MassPdf* pdf,TString which = "Signal" ) ;
  void Print(double& signal, double& error, bool print=false);
  void Print(){ // print without returning anything
    double s,e;
    Print(s,e,true);
  }
  
 private:
  void AddPull(TCanvas* pullCanvas, RooPlot* frame, Int_t logy);

  TString m_name ;
  bool m_extended;
  Long64_t m_nevents;
  RooRealVar* m_mass ;
  RooRealVar* m_nLambdab;
  RooRealVar* m_nonPeaking;

  RooRealVar* m_mean ;
  RooRealVar*  m_width;
  RooRealVar*  m_width2;
  RooRealVar* m_frac;
  RooRealVar* m_alpha;
  RooRealVar* m_n;
  RooRealVar* m_alpha2;
  RooRealVar* m_n2;
  RooAbsPdf* m_Lambdab;
  RooAbsPdf* m_Lambdab_I;
  RooAbsPdf* m_Lambdab_II;
  RooRealVar* m_bkg1;   
  RooRealVar* m_bkg2;   
  RooAbsPdf* m_comBKG;
  RooAddPdf* m_massPdf;

  bool m_debug ;
  
  
};
#endif
