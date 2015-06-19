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
#include "background.h"

// From ROOT
#include "TF1.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TLegend.h"

const TString c_range = "All";

using namespace RooFit;

class MassPdf{
 public:
  MassPdf(TString name, RooRealVar* mass, int nevents,  backgrounds bkgs, 
          TString opt="", TString range = "",
          TString sigType="DoubleCB", TString bkgType="Poly2",
	  bool withXib=false){
    make(name,mass,nevents,bkgs,opt,range,sigType,bkgType,withXib);
  } ;
  
  MassPdf(TString name, RooRealVar* mass, int nevents,
          TString opt="", TString range = "",
          TString sigType="DoubleCB", TString bkgType="Poly2",
	  bool withXib=false){
    backgrounds bkgs;
    make(name,mass,nevents,bkgs,opt,range,sigType,bkgType,withXib);
  };
  
  ~MassPdf();
  
// *** Redefine Fit Functions ***
  RooFitResult* fit(RooDataSet* data, bool doSumW2);
  RooPlot* plotOn(TCanvas* doek, RooDataSet* data, bool doSumW2, Int_t logy, bool param, bool pull);
  RooArgList massPdfList(){
    RooArgList pdfList;
    pdfList.add(*m_Lambdab);
    if (m_Xib) pdfList.add(*m_Xib);
    if (!m_backgrounds.empty()){
      for (backgrounds::iterator b = m_backgrounds.begin(); b!=m_backgrounds.end() ; ++b){
        pdfList.add(*((*b)->pdf()));
      }
    }
    pdfList.add(*m_comBKG);
    return pdfList;
  };
  RooArgList fracPdfList(){
    RooArgList fracList;
    fracList.add(*m_nLambdab);
    if (m_Xib) fracList.add(*m_nXib);
    if (!m_backgrounds.empty()){
      for (backgrounds::iterator b = m_backgrounds.begin(); b!=m_backgrounds.end() ; ++b){
        fracList.add(*((*b)->yield()));
      }
    }
    if (m_extended) fracList.add(*m_nonPeaking);
    return fracList;
  }
  RooArgList externalConstraintsList(){
    RooArgList externalConstraints;
    if (!m_backgrounds.empty()){
      for (backgrounds::iterator b = m_backgrounds.begin(); b!=m_backgrounds.end() ; ++b){
        externalConstraints.add(*((*b)->constraint()));
      }
    }
    return externalConstraints;
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
  void Print(double& signal, double& error, double factor =1, TString print="");
  void Print(RooRealVar* var, double& signal, double& error, double factor =1, TString print="");
  void Print(TString name, double signal, double error);
  void Print(RooRealVar* var);
  void Print();
  
 private:
  void make(TString name, RooRealVar* mass, int nevents,backgrounds bkgs,
            TString opt, TString range ,
            TString sigType, TString bkgType, bool withXib);
  
  void AddPull(TCanvas* pullCanvas, RooPlot* frame, Int_t logy);

  TString m_name ;
  bool m_extended;
  Long64_t m_nevents;
  RooRealVar* m_mass ;
  RooRealVar* m_nLambdab;
  RooRealVar* m_nonPeaking;
  RooRealVar* m_nXib;

  RooRealVar* m_mean ;
  RooRealVar* m_meanXib ;
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
  RooAbsPdf* m_Xib;
  RooAbsPdf* m_Xib_I;
  RooAbsPdf* m_Xib_II;
  RooRealVar* m_bkg1;   
  RooRealVar* m_bkg2;   
  RooAbsPdf* m_comBKG;
  RooAddPdf* m_massPdf;

  bool m_debug ;
  TString m_range ;
  RooFitResult* m_lastFit ;
  backgrounds m_backgrounds ;
  
};

double ebRule(double v, double e);   // v is the value, e the error
double ebRule(double e); ///< display only the error
void printEbRule(double v, double e, TString sep="\\pm") ;

#endif
