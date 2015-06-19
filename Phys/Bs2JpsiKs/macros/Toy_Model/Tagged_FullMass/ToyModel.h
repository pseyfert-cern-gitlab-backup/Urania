//////////////////////////////////////
// ********** ToyModel.h ********** //
//////////////////////////////////////

#ifndef TOYMODEL
#define TOYMODEL



///////////////////////////////////////////////////
// ********** Loading usefull classes ********** //
///////////////////////////////////////////////////

#include <iostream>
#include <Rtypes.h>

#include <RooAddition.h>
#include <RooAddModel.h>
#include <RooAddPdf.h> 
#include <RooArgList.h>
#include <RooArgSet.h>
#include <RooBDecay.h>
#include <RooCategory.h>
#include <RooCBShape.h>
#include <RooDataSet.h>
#include <RooDecay.h> 
#include <RooEffProd.h>
#include <RooExponential.h>
#include <RooFit.h>
#include <RooFitResult.h>
#include <RooFormulaVar.h> 
#include <RooGaussian.h> 
#include <RooGaussModel.h>  
#include <RooPlot.h>
#include <RooProdPdf.h>
#include <RooRandom.h> 
#include <RooRealVar.h>

#include <TAxis.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TLegend.h>
#include <TMath.h> 
#include <TNtuple.h>
#include <TPaveText.h>
#include <TRandom3.h>
#include <TString.h>

#include "LHCbAcceptance.h"
#include "RooBinnedPdf.h"
#include "RooEffResModel.h"

using namespace RooFit;



//////////////////////////////////////////////
// ********** Defining new class ********** //
//////////////////////////////////////////////

class ToyModel {

public:

  ToyModel(){}; //simple constructor
 
  virtual ToyModel* clone() const { return new ToyModel(*this); }; //clone
  inline virtual ~ToyModel() { }; //destructor
  
  void DefiningConstantsAndVariables(int tracktype, double theLumi = 0);

  void BuildPdf();
  
  void GenerateData(int set_seed);

  void PullPlot(TString savestring, RooPlot* frame, int logy);
  
  void Plotting(TString label);

  void FittingParameters(TString setup = "Default");

  void Saving(TString setup = "Default");

protected:

private:

////////////////////////////////////////////////////////////
// ********** Defining Constants and Variables ********** //
////////////////////////////////////////////////////////////

  int TrackType;
  double LumiGen;

  // ********** Used variables ********** //
  //////////////////////////////////////////

  // *** B0 Mass ***
  RooRealVar *Bmass;

  // *** Bs lifetime ***
  RooRealVar *Btime;

  // ********** Used Constants: B0 Mass ********** //
  ///////////////////////////////////////////////////
  
  double input_Bmass_Bd;
  RooRealVar *Bmass_Bd;
  RooRealVar *Bmass_Diff;
  RooAddition *Bmass_Bs;

  // *** Signal ***
  double input_sigma_I;
  double input_sigma_II;
  double input_fraction;
  RooRealVar *Bmass_sigma_I;
  RooRealVar *Bmass_sigma_II;
  RooRealVar *Bmass_apar_I;
  RooRealVar *Bmass_npar_I;
  RooRealVar *Bmass_apar_II;
  RooRealVar *Bmass_npar_II;
  RooRealVar *Bmass_fraction;

  // *** Background ***
  double input_lambda;
  RooRealVar *Bmass_lambda;

  // ********** Used Constants: Time ********** //
  ////////////////////////////////////////////////
  
  // *** Tagged Parameters *** //
  ///////////////////////////////
  
	// *** Penguin parameters ***
  RooRealVar *a_penguin;
  RooRealVar *theta_penguin;

  // *** CKM Constants ***
  RooRealVar *gamma;
  RooRealVar *eta;
  RooRealVar *phi_Bs;
  RooRealVar *epsilon;

  // *** Lifetime Constants ***
  RooRealVar *tau_Bd;
  RooRealVar *dG_Bd;
  RooRealVar *dM_Bd;  
  RooRealVar *tau_Bs;
  RooRealVar *dG_Bs;
  RooRealVar *dM_Bs;
  
  // *** CP Observables *** 
  RooFormulaVar *Robs_Bd_input;
  RooFormulaVar *Adir_Bd_input;
  RooFormulaVar *Amix_Bd_input;
  RooFormulaVar *ADG_Bd_input;
  RooRealVar *Adir_Bd;
  RooRealVar *Amix_Bd;
  RooRealVar *ADG_Bd;
  RooFormulaVar *Robs_Bs_input;
  RooFormulaVar *Adir_Bs_input;
  RooFormulaVar *Amix_Bs_input;
  RooFormulaVar *ADG_Bs_input;
  RooRealVar *Adir_Bs;
  RooRealVar *Amix_Bs;
  RooRealVar *ADG_Bs;

  // *** Mistagging ***
  RooRealVar *mistag_Bd;
  RooRealVar *tageff_Bd;
  RooRealVar *mistag_Bs;
  RooRealVar *tageff_Bs;
  RooCategory *tag;
  
  // *** Coefficients for the decay equations ***
  RooFormulaVar *tagNorm_Bd;
  RooFormulaVar *ACosh_Bd;
  RooFormulaVar *DSinh_Bd;
  RooFormulaVar *CCos_Bd;
  RooFormulaVar *SSin_Bd;
  
  RooFormulaVar *tagNorm_Bs;
  RooFormulaVar *ACosh_Bs;
  RooFormulaVar *DSinh_Bs;
  RooFormulaVar *CCos_Bs;
  RooFormulaVar *SSin_Bs;
  
  
  // *** Untagged Parameters *** //
  /////////////////////////////////
  
  // *** Resolution ***
  RooRealVar *resMean;
  RooRealVar *coreSigma;
  RooRealVar *midSigma;
  RooRealVar *tailSigma;
  RooRealVar *Corefrac;
  RooRealVar *Midfrac;
  
  // *** Acceptance ***
  double input_accY;
  double input_accZ;
  double input_accVelo;
  RooRealVar *accX;
  RooRealVar *accY;
  RooRealVar *accZ;
  RooRealVar *accVelo;

  // *** Background ***
  double input_tau_short;
  double input_tau_long;
  double input_tau_fraction;
  double input_bkgY;
  double input_bkgZ;
  RooRealVar *tau_short;
  RooRealVar *tau_long;
  RooRealVar *tau_fraction;
  RooRealVar *bkgX;
  RooRealVar *bkgY;
  RooRealVar *bkgZ;
  RooRealVar *bkgVelo;


  // ********** Events ********** //
  //////////////////////////////////
   
  // *** Number of events in Current Sample ***
  RooRealVar *lumi_sample;
  RooRealVar *nBd_sample;
  RooRealVar *nBs_sample;
  RooRealVar *nBkg_sample;
  
  // *** Scale to desired luminosity ***
  RooRealVar *lumi_generated;
  RooFormulaVar *nBd_generated;
  RooFormulaVar *nBs_generated;
  RooFormulaVar *nBkg_generated;
  RooRealVar *nBd_fit;
  RooRealVar *nBs_fit;
  RooRealVar *nBkg_fit;    


////////////////////////////////////////
// ********** Building PDF ********** //
////////////////////////////////////////


  // ********** Mass PDFs ********** //
  /////////////////////////////////////

  // *** Crystal Ball ***
  RooCBShape *CBall_Bd_I;  
  RooCBShape *CBall_Bd_II;
  RooCBShape *CBall_Bs_I;  
  RooCBShape *CBall_Bs_II;

  // *** Exponential Background ***
  RooExponential *Bmass_Exp_bkg;

  // *** Composite PDFs ***
  RooAddPdf *Bmass_Sig_Bd;
  RooAddPdf *Bmass_Sig_Bs;

  // ********** Time PDFs ********** //
  /////////////////////////////////////

  // *** Resolution ***
  RooGaussModel *core;
  RooGaussModel *mid;
  RooGaussModel *tail;
  RooAddModel *resModel;
  
  // *** Acceptance ***
  LHCbAcceptance *acceptance;
  LHCbAcceptance *bkgAcc;
  
  // *** Binned Acceptance ***
  RooBinnedPdf* sigAccBinned;
  RooBinnedPdf* bkgAccBinned;
  RooEffResModel *sigResModel;
  RooEffResModel *bkgResModel;
  
  // *** Signal ***
  RooBDecay *decay_Bd;
  RooBDecay *decay_Bs;
  
  // *** Background ***
  RooDecay *decay_short;
  RooDecay *decay_long;
  RooDecay *decay_acc_bkg;
  RooAbsPdf *decay_background;

  // ********** Total PDFs ********** //
  //////////////////////////////////////
  RooProdPdf *total_Bd;
  RooProdPdf *total_Bs;
  RooProdPdf *total_Bkg;

  // *** Composite PDFs ***
  RooAddPdf *total_pdf;


///////////////////////////////////////////
// ********** Generating data ********** //
///////////////////////////////////////////

  int nEvents;
  RooDataSet *ToyData;

//////////////////////////////////////////////
// ********** Fitting parameters ********** //
//////////////////////////////////////////////

  // ********** Report status and results ********** //
  /////////////////////////////////////////////////////

  RooRealVar *temp_Par;
  int Minuit_status;
  int Minuit_covQual;
  double Minuit_edm;
  double Minuit_globalCorr_accY;
  double Minuit_globalCorr_accZ;
  double Minuit_globalCorr_accVelo;
  double Minuit_nBd_Val;
  double Minuit_nBd_Err;
  double Minuit_nBd_Pull;
  double Minuit_nBs_Val;
  double Minuit_nBs_Err;
  double Minuit_nBs_Pull;  
  double Minuit_nBkg_Val;
  double Minuit_nBkg_Err;  
  double Minuit_nBkg_Pull;
  double Minuit_Bmass_Bd_Val;
  double Minuit_Bmass_Bd_Err;
  double Minuit_Bmass_Bd_Pull; 
  double Minuit_sigma_I_Val;
  double Minuit_sigma_I_Err;
  double Minuit_sigma_I_Pull; 
  double Minuit_sigma_II_Val;
  double Minuit_sigma_II_Err;
  double Minuit_sigma_II_Pull; 
  double Minuit_fraction_Val;
  double Minuit_fraction_Err;
  double Minuit_fraction_Pull; 
  double Minuit_lambda_Val;
  double Minuit_lambda_Err;
  double Minuit_lambda_Pull;
  double Minuit_accY_Val;
  double Minuit_accY_Err;
  double Minuit_accY_Pull; 
  double Minuit_accZ_Val;
  double Minuit_accZ_Err;
  double Minuit_accZ_Pull; 
  double Minuit_accVelo_Val;
  double Minuit_accVelo_Err;
  double Minuit_accVelo_Pull;  
  double Minuit_bkgY_Val;
  double Minuit_bkgY_Err;
  double Minuit_bkgY_Pull; 
  double Minuit_bkgZ_Val;
  double Minuit_bkgZ_Err;
  double Minuit_bkgZ_Pull; 
  double Minuit_tau_short_Val;
  double Minuit_tau_short_Err;
  double Minuit_tau_short_Pull; 
  double Minuit_tau_long_Val;
  double Minuit_tau_long_Err;
  double Minuit_tau_long_Pull; 
  double Minuit_tau_fraction_Val;
  double Minuit_tau_fraction_Err;
  double Minuit_tau_fraction_Pull;
  double Minuit_ADG_Bs_Val;
  double Minuit_ADG_Bs_Err;
  double Minuit_ADG_Bs_Pull; 
  double Minuit_Adir_Bs_Val;
  double Minuit_Adir_Bs_Err;
  double Minuit_Adir_Bs_Pull; 
  double Minuit_Amix_Bs_Val;
  double Minuit_Amix_Bs_Err;
  double Minuit_Amix_Bs_Pull;


//////////////////////////////////
// ********** Saving ********** //
//////////////////////////////////
  TTree *outputTree;

  ClassDef(ToyModel,0) // This is the RooFit class written by Kristof De Bruyn for the decay Bd -> J/#psi Ks

};


#endif
