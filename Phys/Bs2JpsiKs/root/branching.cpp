// ####################################################################################################
// Phys/Bs2JpsiKs Package
// Scan for Optimal Neural Net Cut
// Authors: Patrick Koppenburg & Kristof De Bruyn
// ####################################################################################################

// ####################################################################################################
// *** Load Useful Classes ***

#include <iostream>
#include <string>

#include "TCanvas.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TMath.h"
#include "TPaveText.h"

#include "IB2JpsiX.h"
#include "JpsiKsPdf.h"
#include "MultipleCandidates.h"
#include "TupleLoader.h"

// ####################################################################################################
// *** Declarations ***
// TCanvas* PullPlot(RooPlot* frame, RooRealVar* x, int logy=0);
void make_canvas();

class branching {
public :
  branching(const TString module, const TString decay, const TString plotfilename, unsigned int ttype,
	    TString weightMethod, TString what, TString dir, unsigned int NNtype);
  ~branching(){};
  int branchingFraction();
  int scanPunzi();
  int systematics();
  int splitEventNumber();
  int splitOldNewData();
  int effectifeLifetime();
  int systematicsTau();
  int optimiseNet1();
    
private:
  char* makeCut(double cut, char* netcut, unsigned int LL=0, bool odd=false);
  void calcYield(double *All, double *Odd, double *Yield);
  void printBF(TString tag, double *Yield);
  void setPDFOptions(JpsiKsPdf* jpsiKs, TString tag);
  void PDGAverage(double *LL_yield, double *DD_yield, double *Av_yield);
  void PDGAverage(int index, double *yield, double *error, double *Av_yield);
  void Punzi(double nBs_Val, double nBs_Err, double nBkg_Val, double nBkg_Err, double *FoM, double alpha = 10);
  void setBestCut();
  double getBestCut(unsigned int LL);
  double getNet1Cut(unsigned int LL);
  void TwoDScan(double *bestcut, double alpha = 10); // Best match this with void Punzi!
  void TwoDPunzi(double myLLcut, double myDDcut, double alpha = 10); // Best match this with void Punzi!
  void OneDPunzi(double mycut, int LL);
  void doFullFit(char* netcut, double *Results, TString tag);
  void doBestFit(double cut_LL, double cut_DD, TString tag);
  void doLifetimeFit(double netVal, char* netcut, double *Results, TString tag);
  int fillDataset(double cut=min_opt_net);

  // General Settings
  static const bool m_debug = false;
  static const bool m_fitKstar = false;
  static const bool m_fastOpt = true; // Optimise without rechecking for Multiple Candidates, they are only killed the first time
  static const bool m_trainInd = true;
  static const bool m_unblind = true;
  
  // Neural Net Settings
  static const double min_opt_net = 0.;
  static const double stepsize    = 0.01; // 0.01
  static const int    min_events = 0; 
  static const bool   do_punzi = true;
  static const bool   fit_bkg = false;
  static const bool   opt_Sig = false; // Optimise using Signal to keep (true) or Background to eliminate (false)
  //static const double opt_net1 = 0.95; // Percentage of signal to keep
  static const double opt_net1 = 0.75; // Percentage of background to eliminate
  
  // Members
  unsigned int m_ttype;
  TString m_weightMethod;
  TString m_what;
  unsigned int m_NNtype;
  
  IB2JpsiX* m_ntuple;
  TFile* m_outfile;
  RooRealVar* m_mass;
  RooRealVar* m_time;
  RooDataSet* m_data;
  MultipleCandidates* m_eventMap;
  double previousNN;
  double m_bestCut_LL;
  double m_bestCut_DD;
  double m_bestCut_ANY;
  bool m_doMod;
  
  TGraphErrors* graph_Sig_LL;
  TGraphErrors* graph_Bkg_LL;
  TGraphErrors* graph_Punzi_LL;
  TGraphErrors* graph_Sig_DD;
  TGraphErrors* graph_Bkg_DD;
  TGraphErrors* graph_Punzi_DD;
  TGraphErrors* graph_Sig_Any;
  TGraphErrors* graph_Bkg_Any;
  TGraphErrors* graph_Punzi_Any;
};

  
// ####################################################################################################
// *** Branching Ratio Calculation ***
branching::branching(const TString module, const TString decay, const TString plotfilename, unsigned int ttype,
		     TString weightMethod, TString what, TString dir, unsigned int NNtype){

  // *** General Settings ***
  m_ttype = ttype; 
  m_weightMethod = weightMethod ;
  m_what = what ;
  m_NNtype = NNtype ;
  
  // *** Load NTuple ***
  m_ntuple = loadTuple(module, decay, dir, m_what, m_NNtype, m_weightMethod, m_ttype);
  if (!m_ntuple){
    std::cout << "WARNING: Ntuple could not be loaded" << std::endl;
    return ;
  }
  
  // *** Set Output ***
  m_outfile = new TFile( plotfilename, "RECREATE" );
  m_outfile->cd();
  
  // *** Initialise ***
  m_mass = new RooRealVar("mass","B mass",m_ntuple->sideband_low_min(),m_ntuple->sideband_high_max(),"MeV/c^{2}");
  m_time = new RooRealVar("time","B decay time",0.2,15.,"ps");  
  m_data = 0 ;
  m_eventMap = 0;
  previousNN = -999;
  m_bestCut_LL = min_opt_net;
  m_bestCut_DD = min_opt_net;
  m_bestCut_ANY = min_opt_net;
  m_doMod = false;
  
  graph_Sig_LL = 0 ;
  graph_Bkg_LL = 0 ;
  graph_Punzi_LL = 0 ;
  graph_Sig_DD = 0 ;
  graph_Bkg_DD = 0 ;
  graph_Punzi_DD = 0 ;
  graph_Sig_Any = 0 ;
  graph_Bkg_Any = 0 ;
  graph_Punzi_Any = 0 ;

}
// ####################################################################################################
// *** Small functions ***
char* branching::makeCut(double cut, char* netcut, unsigned int LL, bool odd){
  if (odd){
    if ( LL==0 ){
      sprintf( netcut , "odd && net>%.3f", cut );
    } else if  ( LL==m_LL ){
      sprintf( netcut , "odd && LL==3 && net>%.3f", cut );    
    } else if  ( LL==m_DD ){
      sprintf( netcut , "odd && LL==5 && net>%.3f", cut );
    } else std::cout << "ERROR: Unknown Cut specification: " << LL << std::endl ;
  } else {
    if ( LL==0 ){
      sprintf( netcut , "net>%.3f", cut );
    } else if  ( LL==m_LL ){
      sprintf( netcut , "LL==3 && net>%.3f", cut );    
    } else if  ( LL==m_DD ){
      sprintf( netcut , "LL==5 && net>%.3f", cut );
    } else std::cout << "ERROR: Unknown Cut specification: " << LL << std::endl ;
  }
}

// ####################################################################################################
void branching::calcYield(double *All, double *Odd, double *Yield){

  // *** Fit Results ***
  double nBd_Val = Odd[0]*frac_in_teaching/(frac_in_teaching-parts_in_teaching);
  double nBd_Err = Odd[1]*frac_in_teaching/(frac_in_teaching-parts_in_teaching);
  double nBs_Val = All[2];
  double nBs_Err = All[3];
  
  // *** Yield Ratio ***
  Yield[0] = nBs_Val/nBd_Val;
  Yield[1] = sqrt(pow(nBs_Err/nBd_Val,2)+pow(nBs_Val*nBd_Err/pow(nBd_Val,2),2));
}

// ####################################################################################################
void branching::printBF(TString tag, double *Yield){
  
  // *** Yield Ratio ***
  double yieldRatio_Val = Yield[0];
  double yieldRatio_Err = Yield[1];

  // *** Ratio of Branching Fractions ***
  double r = syst*yieldRatio_Val/fsfd ;
  double r_e = r*(yieldRatio_Err/yieldRatio_Val) ;
  double r_s0 = r*(esyst/syst) ;
  double r_s2 = r*(fsfde/fsfd) ;

  // *** Branching Fraction ***
  double bf = jpk0bf*r ;
  double bfe = jpk0bf*r_e ;
  double bfs0 = jpk0bf*r_s0;
  double bfs1 = bf*(jpk0bfe/jpk0bf) ;
  double bfs2 = jpk0bf*r_s2 ;
  
  // *** Results ***
  std::cout << "\n RESULT:" << std::endl;
  std::cout << "     " << tag << std::endl;
  std::cout << "     Yield Ratio = " << yieldRatio_Val << " +/- " << yieldRatio_Err << std::endl;
  std::cout << "     BR(Bs->J/psiKS)/BR(Bd->J/psiKS) =  " << r << " +/- " << r_e << "(stat) +/- " 
       << r_s0 << "(syst) +/- " << r_s2 << "(fd/fs)" << std::endl ;
  std::cout << "     BR(Bs->J/psiK0) = " << bf << " +/- " << bfe << "(stat) +/- " 
       << bfs0 << "(syst) +/- " << bfs2 << "(fd/fs) +/- " << bfs1 << "(BF)" << std::endl ;
  
}

// ####################################################################################################
void branching::setPDFOptions(JpsiKsPdf* jpsiKs, TString tag){

  // Background Models
  if(tag=="Poly" || tag=="Uni") jpsiKs->setModel("Default","Default",tag);
  
  // Signal Models
  if(tag=="GaussCB" || tag=="CB" || tag=="DoubleGauss") jpsiKs->setModel(tag,"Default","Default");
  
  // Signal Tails
  if(tag=="FitTails") jpsiKs->setModel("Default","Default","Default","FitTails"); // Change signal to fit CB tails
  
  // Mass Difference
  if(tag=="MassDiffPlus" || tag=="MassDiffMin" || tag=="MassDiffFit") jpsiKs->setMassDiff(tag); // Change the Bd-Bs mass difference
  
  // Mass Resolution
  // Change the Bs mass width scale factor
  if(tag=="BMass" || tag=="BJKMass" || tag=="PhSp" || tag=="MCfit" || tag=="MCfitPlus" || tag=="MCfitMin" || tag=="MCfree"){
    jpsiKs->scaleMassWidth(tag);
  }
  
  // Time Resolution
  if(tag=="Triple50" || tag=="TripleMC" || tag=="ResGauss" || tag=="ResGaussWide"){
    jpsiKs->setTimeModel(tag,"Default","Default",true);
  }
  
  // Time Acceptance
  if(tag=="TanOffset" || tag=="Tan" || tag=="Exp") jpsiKs->setTimeModel("Default",tag,"Default",true);
  
  // Time Background
  if(tag=="OneExp" || tag=="TwoExp") jpsiKs->setTimeModel("Default","Default",tag,true);
  
  // Bd Lifetime
  if(tag=="HFAGPlus" || tag=="HFAGMin" || tag=="LHCb" || tag=="LHCbPlus" || tag=="LHCbMin") jpsiKs->setBdLifetime(tag);
}

// ####################################################################################################
void branching::PDGAverage(double *LL_yield, double *DD_yield, double *Av_yield){
  // *** PDG Average ***
  double wLL = pow(LL_yield[1],-2);
  double wDD = pow(DD_yield[1],-2);
  
  Av_yield[0] = (wLL*LL_yield[0] + wDD*DD_yield[0])/(wLL+wDD);
  Av_yield[1] = 1/sqrt(wLL+wDD);
}

// ####################################################################################################
void branching::PDGAverage(int index, double *yield, double *error, double *Av_yield){

  double weight = 0;
  double sum = 0;
  double err = 0;
  
  for(int i=0; i<index; i++){
    weight = pow(error[i],-2);
    sum += weight*yield[i];
    err += weight;
  }

  // *** PDG Average ***  
  Av_yield[0] = sum/err;
  Av_yield[1] = 1/sqrt(err);
}

// ####################################################################################################
void branching::Punzi(double nBs_Val, double nBs_Err, double nBkg_Val, double nBkg_Err, double *FoM, double alpha){

  // *** Calculate Significance ***
  // Punzi-style optimisation
  double fomES, fomEB;
  if (do_punzi){
    FoM[0] = nBs_Val/(alpha/2+sqrt(nBkg_Val));
    fomES = nBs_Err/(alpha/2+sqrt(nBkg_Val)) ; //dP/dBs
    fomEB = -0.5*nBkg_Err*pow(FoM[0],2)/(nBs_Val*nBkg_Val) ; //dP/dBkg
  } else {
    FoM[0] = nBs_Val/sqrt(nBs_Val+nBkg_Val);
    fomEB = -0.5*nBkg_Err*nBs_Val/(sqrt(nBs_Val+nBkg_Val) * (nBs_Val+nBkg_Val)) ;
    fomES = nBs_Err*(0.5*nBs_Val + nBkg_Val)/(sqrt(nBs_Val+nBkg_Val) * (nBs_Val+nBkg_Val)) ;
  }
  FoM[1] = sqrt(pow(fomES,2) + pow(fomEB,2)) ;
}

// ####################################################################################################
void branching::setBestCut(){
  // Set the best NN cut in case we run this part separately
  if(m_bestCut_LL<=min_opt_net) m_bestCut_LL = 0.60;
  if(m_bestCut_DD<=min_opt_net) m_bestCut_DD = 0.75;
  if(m_bestCut_ANY<=min_opt_net) m_bestCut_ANY = 0.85;
}

// ####################################################################################################
// *** Determine Best Neural Net Cut ***
// Evaluate performance of the network by taking slices in network output and fitting resulting mass distribution 
double branching::getBestCut(unsigned int LL){
  
// ***** PART 0: Initialise ***** //
////////////////////////////////////

  char netcut[30];
  fillDataset() ;
  if (m_debug) std::cout << "getBestCut " << m_data << std::endl ;
  Int_t totEntries = m_data->numEntries();
  int lastentries = 2*totEntries+1 ;
  RooDataSet* dataset = 0;

  double bestFom = 0.;
  double bestCut = min_opt_net ;
  int npoints = -1 ;
  Double_t netVal = min_opt_net ;

  // *** Graphs for Signal, Background and Significance ***
  TGraphErrors* grS = new TGraphErrors();
  grS->SetMarkerStyle(20);
  grS->SetMarkerSize(0.8);
  grS->SetLineColor(kGreen);
  grS->SetMarkerColor(kGreen);  

  TGraphErrors* grB = new TGraphErrors();
  grB->SetMarkerStyle(20);
  grB->SetMarkerSize(0.8);
  grB->SetLineColor(kRed);
  grB->SetMarkerColor(kRed);

  TGraphErrors* grSig = new TGraphErrors();
  grSig->SetMarkerStyle(20);
  grSig->SetMarkerSize(0.8);
  grSig->SetLineColor(kBlue);
  grSig->SetMarkerColor(kBlue);

  
// ***** PART I: Setup PDF ***** //
///////////////////////////////////
  
  // *** Fix the Signal parameters ***
  JpsiKsPdf* jpsiKsExt = new JpsiKsPdf("",m_mass,false,m_fitKstar,LL,"Loose", totEntries); // no Bs, Double Crystal Ball
  jpsiKsExt->fitToMass(m_data,false);
  jpsiKsExt->setConstant("SigOnly");
  
  // *** Fix the fitting range ***
  m_mass->setRange("Bs", BsBox_min, BsBox_max);
  m_mass->setRange("Low", m_ntuple->sideband_low_min(), BdBox_max);
  m_mass->setRange("High", m_ntuple->sideband_high_min(), m_ntuple->sideband_high_max());
  jpsiKsExt->fitToMass(m_data,false,"Low,High");


// ***** PART II: Loop ***** //
///////////////////////////////
  std::cout << "\n PROGRESS: Looping over Neural Net Cuts \n" << std::endl;
  TCanvas *getBestPlot = new TCanvas("getBestPlot","Canvas for MassPlot",900,800);
  while ( lastentries>0 ){
    std::cout << " LOOP: Evaluating Neural Net cut " << netVal << std::endl;
    
    // *** Apply cut on Data ***
    makeCut(netVal,netcut,LL,true);
    if(!m_fastOpt) fillDataset(netVal);
    dataset = (RooDataSet*)m_data->reduce(netcut);
     
    int nent = dataset->sumEntries(0,"Low,High") ;
    if ( nent<=min_events) {
      std::cout << " LOOP: Ran out of stats! Only " << nent << " events remaining" << std::endl ;
      break ; // out of stats
    }
    
    // *** Analyse ***
    if(nent<lastentries){
      lastentries = nent ;      
      
      // *** Fit ***
      jpsiKsExt->fitToMass(dataset,false);
      std::cout << " LOOP: Done fitting." << std::endl;
      
      jpsiKsExt->plotOn(getBestPlot,dataset,false,1,1); // Plot with Parameters
      getBestPlot->Write(netcut);
      std::cout << " LOOP: Done plotting." << std::endl;


      // *** Estimate what's in the Bs box ***
      // Only running over the "odd" non-teaching sample
      RooAbsReal *integral_Bkg = (RooAbsReal *)jpsiKsExt->integralBKG();
      double Bs = (frac_in_teaching/(frac_in_teaching-parts_in_teaching))*fsBr*jpsiKsExt->nBd()->getVal();
      double BsE = (frac_in_teaching/(frac_in_teaching-parts_in_teaching))*fsBr*jpsiKsExt->nBd()->getError();
      double expBkg = 999;
      double expBkgErr = 999;
      
      // Alternative I: Fit and integrate
      if(fit_bkg){
        expBkg = (frac_in_teaching/(frac_in_teaching-parts_in_teaching))*integral_Bkg->getVal()*jpsiKsExt->nonPeaking()->getVal();
        expBkgErr = (frac_in_teaching/(frac_in_teaching-parts_in_teaching))*integral_Bkg->getVal()*jpsiKsExt->nonPeaking()->getError();
      }
      // Alternative II: Count and rescale
      else{
        char masscut[50];
        strcpy(masscut,netcut);
        strcat(masscut,"&& (mass>5400 || mass<5240)");
      
        RooDataSet *tempset = (RooDataSet *)m_data->reduce(masscut);
        expBkg = (frac_in_teaching/(frac_in_teaching-parts_in_teaching))*(5./18.)*tempset->numEntries();
        expBkgErr = (frac_in_teaching/(frac_in_teaching-parts_in_teaching))*(5./18.)*TMath::Sqrt(tempset->numEntries());
      }
      
      // *** Calculate Significance ***
      double fom[] = {0,0};
      Punzi(Bs,BsE,expBkg,expBkgErr, fom);
      
      std::cout << "++++++++++++++++++++ results ++++++++++++++++++++" << std::endl ;
      std::cout << "             Neural Net Cut : " << netVal << std::endl;
      std::cout << "     # Events in Data Sample: " << nent << std::endl;
      std::cout << "     # Estimated Bs->JpsiKs : " << Bs  << " +/- " << BsE << std::endl;
      std::cout << "     # Estimated Background : " << expBkg << " +/- " << expBkgErr << std::endl;
      std::cout << "            Figure of Merit : " << fom[0] << " +/- " << fom[1] << std::endl;
      std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ; 
      
      // *** Check if this FOM is better ***
      // Require that the improvement is significant, otherwise take the lowest value of the plateau
      if ( fom[0]-fom[1] > bestFom ){ 
        std::cout << "      This is the new best Figure of Merit!" << std::endl ;
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ; 
        bestFom = fom[0];
        bestCut = netVal ;
      }


      // *** Update Graphs ***
      npoints++ ; // counter of real points
      grS->SetPoint(npoints,netVal,Bs);
      grS->SetPointError(npoints,0.5*stepsize,BsE);
      grB->SetPoint(npoints,netVal,expBkg);
      grB->SetPointError(npoints,0.5*stepsize,expBkgErr);
      if(TMath::IsNaN(fom[1])==0){// Do not add infinities to the graph
        grSig->SetPoint(npoints,netVal,fom[0]);
        grSig->SetPointError(npoints,0.5*stepsize,fom[1]);
      }
    }
    else std::cout << "WARNING: Number of events is same as previous step: " << nent << " versus " << lastentries << std::endl;
    delete dataset ;
    netVal = netVal + stepsize ; 
  }
  
// ***** PART III: Return ***** //
//////////////////////////////////

  std::cout << "\n PROGRESS: Finished looping" << std::endl ;
  std::cout << " PROGRESS: Best Cut is " << bestCut << " \n" << std::endl ;
  if ( bestCut == min_opt_net ) std::cout << "ERROR: Best cut has not improved from initial guess! " << std::endl ;
  
  makeCut(bestCut,netcut,LL,true);
  grS->Write("Signal vs NNcut - "+TString(netcut));
  grB->Write("Background vs NNcut - "+TString(netcut));
  grSig->Write("Significance vs NNcut - "+TString(netcut));
  
  if(LL==3){
    graph_Sig_LL = (TGraphErrors*) grS;
    graph_Bkg_LL = (TGraphErrors*) grB;
    graph_Punzi_LL = (TGraphErrors*) grSig;
  }
  else if(LL==5){
    graph_Sig_DD = (TGraphErrors*) grS;
    graph_Bkg_DD = (TGraphErrors*) grB;
    graph_Punzi_DD = (TGraphErrors*) grSig;
  }
  else{
    graph_Sig_Any = (TGraphErrors*) grS;
    graph_Bkg_Any = (TGraphErrors*) grB;
    graph_Punzi_Any = (TGraphErrors*) grSig;
  }

  return bestCut ;
}

double branching::getNet1Cut(unsigned int LL){
  
// ***** PART 0: Initialise ***** //
////////////////////////////////////

  char netcut[30];
  fillDataset(-1.) ;
  Int_t totEntries = m_data->numEntries();
  int lastentries = 2*totEntries+1 ;
  RooDataSet* dataset = 0;
  
  double bestCut = (LL==3 ? -0.6 : -0.8);
  double netVal = bestCut;
  bool foundNet1Cut = false;
  
  TCanvas *getBestPlot = new TCanvas("getBestPlot","Canvas for MassPlot",900,800);

  
// ***** PART I: Setup PDF ***** //
///////////////////////////////////
  
  // *** Fix the Signal parameters ***
  JpsiKsPdf* jpsiKsExt = new JpsiKsPdf("",m_mass,false,m_fitKstar,LL,"Loose", totEntries); // no Bs, Double Crystal Ball
  jpsiKsExt->fitToMass(m_data,false);
  jpsiKsExt->setConstant("SigOnly");
  
  // *** Fix the fitting range ***
  //m_mass->setRange("Bs", BsBox_min, BsBox_max);
  //m_mass->setRange("Low", m_ntuple->sideband_low_min(), BdBox_max);
  //m_mass->setRange("High", m_ntuple->sideband_high_min(), m_ntuple->sideband_high_max());
  
  makeCut(-1.,netcut,LL,false);
  std::cout << netcut << std::endl;
  dataset = (RooDataSet*)m_data->reduce(netcut);  
  //jpsiKsExt->fitToMass(dataset,false,"Low,High");
  jpsiKsExt->fitToMass(dataset,false);
  
  jpsiKsExt->plotOn(getBestPlot,dataset,false,1,1); // Plot with Parameters
  getBestPlot->Write(netcut);
  
  double all_Bd = jpsiKsExt->nBd()->getVal();
  double all_Bkg = jpsiKsExt->nonPeaking()->getVal();
  
  std::cout << "++++++++++++++++++++ results ++++++++++++++++++++" << std::endl ;
  std::cout << "                 Loose Cuts : " << std::endl;
  std::cout << "     # Events in Data Sample: " << dataset->sumEntries() << std::endl;
  std::cout << "        # Fitted Bd->JpsiKs : " << all_Bd  << std::endl;
  std::cout << "        # Fitted Background : " << all_Bkg << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;


// ***** PART II: Loop ***** //
///////////////////////////////
  std::cout << "\n PROGRESS: Looping over Neural Net Cuts \n" << std::endl;
  while ( lastentries>0 && !foundNet1Cut){
    std::cout << " LOOP: Evaluating Neural Net cut " << netVal << std::endl;
    
    // *** Apply cut on Data ***
    makeCut(netVal,netcut,LL,false);
    if(!m_fastOpt) fillDataset(netVal);
    dataset = (RooDataSet*)m_data->reduce(netcut);
     
    //int nent = dataset->sumEntries(0,"Low,High") ;
    int nent = dataset->sumEntries() ;
    if ( nent<=min_events) {
      std::cout << " LOOP: Ran out of stats! Only " << nent << " events remaining" << std::endl ;
      break ; // out of stats
    }
    
    // *** Analyse ***
    if(nent<lastentries){
      lastentries = nent ;      
      
      // *** Fit ***
      jpsiKsExt->fitToMass(dataset,false);
      std::cout << " LOOP: Done fitting." << std::endl;
      
      jpsiKsExt->plotOn(getBestPlot,dataset,false,1,1); // Plot with Parameters
      getBestPlot->Write(netcut);
      std::cout << " LOOP: Done plotting." << std::endl;

      // *** Estimate what's in the Bs box ***
      // Only running over the "odd" non-teaching sample
      double cut_Bd = jpsiKsExt->nBd()->getVal();
      double cut_Bkg = jpsiKsExt->nonPeaking()->getVal();

      std::cout << "++++++++++++++++++++ results ++++++++++++++++++++" << std::endl ;
      std::cout << "             Neural Net Cut : " << netVal << std::endl;
      std::cout << "     # Events in Data Sample: " << nent << std::endl;
      std::cout << "        # Fitted Bd->JpsiKs : " << cut_Bd  << std::endl;
      std::cout << "        # Fitted Background : " << cut_Bkg << std::endl;
      std::cout << " Eliminating " << (all_Bkg - cut_Bkg)/all_Bkg << " of background while keeping "
                << cut_Bd/all_Bd << " of signal" << std::endl;
      std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
      
      if((opt_Sig && cut_Bd/all_Bd<opt_net1) || (!opt_Sig && (all_Bkg - cut_Bkg)/all_Bkg>opt_net1)){
        foundNet1Cut = true;
        bestCut = (opt_Sig ? netVal - stepsize : netVal); // Closest to, but above threshold
      }
    }
    else std::cout << "WARNING: Number of events is same as previous step: " << nent << " versus " << lastentries << std::endl;
    delete dataset ;
    netVal = netVal + stepsize ; 
  }
  
  // Calculate the point 0 for reference
  if(bestCut<0){
    std::cout << " Extra: Evaluating Neural Net cut 0" << std::endl;
    
    // *** Apply cut on Data ***
    makeCut(0.,netcut,LL,false);
    if(!m_fastOpt) fillDataset(0.);
    dataset = (RooDataSet*)m_data->reduce(netcut);     
      
    // *** Fit ***
    jpsiKsExt->fitToMass(dataset,false);
    std::cout << " LOOP: Done fitting." << std::endl;
      
    jpsiKsExt->plotOn(getBestPlot,dataset,false,1,1); // Plot with Parameters
    getBestPlot->Write(netcut);
    std::cout << " LOOP: Done plotting." << std::endl;

    // *** Estimate what's in the Bs box ***
    // Only running over the "odd" non-teaching sample
    double cut_Bd = jpsiKsExt->nBd()->getVal();
    double cut_Bkg = jpsiKsExt->nonPeaking()->getVal();

    std::cout << "++++++++++++++++++++ results ++++++++++++++++++++" << std::endl ;
    std::cout << "             Neural Net Cut : " << 0. << std::endl;
    std::cout << "     # Events in Data Sample: " << dataset->sumEntries() << std::endl;
    std::cout << "        # Fitted Bd->JpsiKs : " << cut_Bd  << std::endl;
    std::cout << "        # Fitted Background : " << cut_Bkg << std::endl;
    std::cout << " Eliminating " << (all_Bkg - cut_Bkg)/all_Bkg << " of background while keeping "
              << cut_Bd/all_Bd << " of signal" << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
  
  }
  
// ***** PART III: Return ***** //
//////////////////////////////////

  std::cout << "\n PROGRESS: Finished looping" << std::endl ;
  std::cout << " PROGRESS: Best Cut is " << bestCut << " \n" << std::endl ;
  if ( bestCut == min_opt_net ) std::cout << "ERROR: Best cut has not improved from initial guess! " << std::endl ;

  return bestCut ;
}


// ####################################################################################################
// *** More Optimisation ***
void branching::TwoDScan(double *bestcut, double alpha){

  if(!(graph_Sig_LL && graph_Sig_DD)){
    std::cout << "ERROR: You should optimise the individual samples first" << std::endl;
    return;
  }
  
  Int_t numLL = graph_Sig_LL->GetN();
  Int_t numDD = graph_Sig_DD->GetN();
  
  double LLcut = 0;
  double DDcut = 0;
  double nBsLL = 0;
  double nBsDD = 0;
  double nBs_Val = 0;
  double nBs_Err = 0;
  double nBkg_Val = 0;
  double nBkg_Err = 0;
  double Fom[] = {0,0};
  
  double bestFom_Val = 0;
  double bestFom_Err = 0;
  double bestLLcut = 0;
  double bestDDcut = 0;
  
  for(Int_t i=0; i<numLL; i++){
    for(Int_t j=0; j<numDD; j++){  
      graph_Sig_LL->GetPoint(i,LLcut,nBsLL);
      graph_Sig_DD->GetPoint(j,DDcut,nBsDD);
      nBs_Val = nBsLL + nBsDD;
      nBs_Err = TMath::Sqrt(pow(graph_Sig_LL->GetErrorY(i),2) + pow(graph_Sig_DD->GetErrorY(j),2));
      graph_Bkg_LL->GetPoint(i,LLcut,nBsLL);
      graph_Bkg_DD->GetPoint(j,DDcut,nBsDD);
      nBkg_Val = nBsLL + nBsDD;
      nBkg_Err = TMath::Sqrt(pow(graph_Bkg_LL->GetErrorY(i),2) + pow(graph_Bkg_DD->GetErrorY(j),2));
      
      Punzi(nBs_Val,nBs_Err,nBkg_Val,nBkg_Err,Fom,alpha);
      
      std::cout << std::endl;
      std::cout << "++++++++++++++++++++ results ++++++++++++++++++++" << std::endl ;
      std::cout << "    Neural Net Cut : " << LLcut << " (LL) + " << DDcut << " (DD)" << std::endl;
      std::cout << "   Figure of Merit : " << Fom[0] << " +/- " << Fom[1] << std::endl;
      std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ; 
      
      // *** Check if this FOM is better ***
      // Require that the improvement is significant, otherwise take the lowest value of the plateau
      if(Fom[0]-Fom[1]>bestFom_Val){  
        std::cout << "      This is the new best Figure of Merit!" << std::endl ;
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ; 
        bestFom_Val = Fom[0];
        bestFom_Err = Fom[1];
        bestLLcut = LLcut;
        bestDDcut = DDcut;
      }
    }
  }
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "++++++++++++++++++++ MAIN RESULTS ++++++++++++++++++++" << std::endl;
  std::cout << "    Neural Net Cut : " << bestLLcut << " (LL) + " << bestDDcut << " (DD)" << std::endl;
  std::cout << "   Figure of Merit : " << bestFom_Val << " +/- " << bestFom_Err << std::endl;
  std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
  
  // Set Best Cut values
  bestcut[0] = bestLLcut;
  bestcut[1] = bestDDcut;

}

// ####################################################################################################
void branching::TwoDPunzi(double myLLcut, double myDDcut, double alpha){

  if(!(graph_Sig_LL && graph_Sig_DD)){
    std::cout << "ERROR: You should optimise the individual samples first" << std::endl;
    return;
  }
  
  Int_t numLL = (Int_t) ((myLLcut - min_opt_net)/stepsize);
  Int_t numDD = (Int_t) ((myDDcut - min_opt_net)/stepsize);
  
  double LLcut = 0;
  double DDcut = 0;
  double nBsLL = 0;
  double nBsDD = 0;
  double nBs_Val = 0;
  double nBs_Err = 0;
  double nBkg_Val = 0;
  double nBkg_Err = 0;
  double Fom[] = {0,0};
  
  graph_Sig_LL->GetPoint(numLL,LLcut,nBsLL);
  graph_Sig_DD->GetPoint(numDD,DDcut,nBsDD);
  if(!(LLcut==myLLcut && DDcut==myDDcut)) std::cout << "ERROR: Did not select the correct point on Sig Graph" << std::endl;
  nBs_Val = nBsLL + nBsDD;
  nBs_Err = TMath::Sqrt(pow(graph_Sig_LL->GetErrorY(numLL),2) + pow(graph_Sig_DD->GetErrorY(numDD),2));
  graph_Bkg_LL->GetPoint(numLL,LLcut,nBsLL);
  graph_Bkg_DD->GetPoint(numDD,DDcut,nBsDD);
  if(!(LLcut==myLLcut && DDcut==myDDcut)) std::cout << "ERROR: Did not select the correct point on Bkg Graph" << std::endl;
  nBkg_Val = nBsLL + nBsDD;
  nBkg_Err = TMath::Sqrt(pow(graph_Bkg_LL->GetErrorY(numLL),2) + pow(graph_Bkg_DD->GetErrorY(numDD),2));
      
  Punzi(nBs_Val,nBs_Err,nBkg_Val,nBkg_Err,Fom,alpha);
      
  std::cout << std::endl;
  std::cout << "++++++++++++++++++++ RESULTS ++++++++++++++++++++" << std::endl ;
  std::cout << "    Neural Net Cut : " << LLcut << " (LL) + " << DDcut << " (DD)" << std::endl;
  std::cout << "   Figure of Merit : " << Fom[0] << " +/- " << Fom[1] << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ; 

}

// ####################################################################################################
void branching::OneDPunzi(double mycut, int LL){

  TGraphErrors* myGraph = 0;
  if(LL==3) myGraph = (TGraphErrors *) graph_Punzi_LL;
  else if(LL==5) myGraph = (TGraphErrors *) graph_Punzi_DD;
  else myGraph = (TGraphErrors *) graph_Punzi_Any;

  if(!myGraph){
    std::cout << "ERROR: You should optimise the sample first" << std::endl;
    return;
  }
  
  Int_t num = (Int_t) ((mycut - min_opt_net)/stepsize);
  
  double thecut = 0;
  double Fom_Val = 0;
  double Fom_Err = 0;  
  myGraph->GetPoint(num,thecut,Fom_Val);
  if(thecut!=mycut) std::cout << "ERROR: Did not select the correct point on Graph" << std::endl;
  Fom_Err = myGraph->GetErrorY(num);
      
  std::cout << std::endl;
  std::cout << "++++++++++++++++++++ RESULTS ++++++++++++++++++++" << std::endl ;
  std::cout << "        Track Type : " << LL << std::endl;
  std::cout << "    Neural Net Cut : " << mycut << std::endl;
  std::cout << "   Figure of Merit : " << Fom_Val << " +/- " << Fom_Err << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ; 

}


// ####################################################################################################
// *** Full Mass Fit ***
void branching::doFullFit(char* netcut, double *Results, TString tag){

  std::cout << "\n PROGRESS: Performing Full Fit for " << netcut << "\n" << std::endl ;

  // *** Prepare Data ***
  RooDataSet *fitdata = (RooDataSet *)m_data->reduce(netcut);
  Int_t totEntries = fitdata->numEntries();
  
  // *** Fit PDF ***
  string cutString (netcut);
  size_t isLL=cutString.find("LL==3");
  size_t isDD=cutString.find("LL==5");
  int track = 0;
  if(isLL!=string::npos) track = 3;
  else if(isDD!=string::npos) track = 5;
  else track = 0;

  JpsiKsPdf* jpsiKsExt = new JpsiKsPdf("",m_mass,true,m_fitKstar,track,"Optimal", totEntries); // With Bs, Double Crystal Ball
  //if(m_fitKstar==true) jpsiKsExt->setConstant("Kstar"); // Freeze parameters from MC11a Incl Jpsi
  setPDFOptions(jpsiKsExt, tag);
  if(m_doMod){
    if(cutString.find("odd")!=string::npos) jpsiKsExt->setConstant("ModOdd");
    else jpsiKsExt->setConstant("Mod");
  }
  RooFitResult* fitresult = (RooFitResult *)jpsiKsExt->fitToMass(fitdata,false);
  
  // *** Plot ***
  double chi2Val[] = {-999,-999};
  size_t absent=cutString.find("odd");
  
  if(tag=="LL+DD" || tag=="All"){
    TCanvas *massPlot = new TCanvas("massPlot","Canvas for MassPlot",900,800);
    jpsiKsExt->plotOn(massPlot,fitdata,false,1,0); // Plot with legend
    jpsiKsExt->plotLegend(0.64,0.50,0.93,0.89,"mass");
    massPlot->Write("Full Mass Fit "+tag+" "+netcut);
    
    if (absent==string::npos){
      TCanvas *pullPlot = new TCanvas("pullPlot","Canvas for MassPlot",900,800);
      jpsiKsExt->plotOn(pullPlot,fitdata,false,1,1); // Plot with parameters
      pullPlot->Write("Param Mass Fit "+tag+" "+netcut);
    }
  }
  if(absent==string::npos){
    TCanvas *pullPlot = new TCanvas("pullPlot","Canvas for MassPlot",900,800);
    jpsiKsExt->plotOn(pullPlot,fitdata,false,1,2,chi2Val); // Plot with pull
    jpsiKsExt->plotLegend(0.64,0.50,0.93,0.89,"mass"); // and legend
    
    TPaveText *lhcbTag = new TPaveText(0.64,0.89,0.93,0.93,"NDC");
    lhcbTag->SetFillColor(0);
    lhcbTag->SetTextAlign(12);
    lhcbTag->SetBorderSize(0);
    lhcbTag->SetTextSize(0.06);
    lhcbTag->SetTextFont(132); // lhcbFont
		lhcbTag->AddText("LHCb");
    lhcbTag->Draw("same");
    
    pullPlot->Write("Pull Mass Fit "+tag+" "+netcut);
  }
  
  // *** Results ***
  Results[0] = jpsiKsExt->nBd()->getVal();
  Results[1] = jpsiKsExt->nBd()->getError();
  Results[2] = jpsiKsExt->nBs()->getVal();
  Results[3] = jpsiKsExt->nBs()->getError();
  Results[4] = jpsiKsExt->nonPeaking()->getVal();
  Results[5] = jpsiKsExt->nonPeaking()->getError();
  
  std::cout << "++++++++++++++++++++ results ++++++++++++++++++++" << std::endl;
  std::cout << "              Tag : " << tag << std::endl;
  std::cout << "   Neural Net Cut : " << netcut << std::endl;
  std::cout << "     # Events     : " << totEntries << std::endl;
  std::cout << "     # Bd->JpsiKs : " << Results[0] << " +/- " << Results[1] << std::endl;
  std::cout << "     # Bs->JpsiKs : " << Results[2] << " +/- " << Results[3] << std::endl;
  std::cout << "     # Background : " << Results[4] << " +/- " << Results[5] << std::endl;
  fitresult->Print();
  if(chi2Val[0]!=-999){
    std::cout << " PULL: Goodness of Fit estimate -> chi2 = " << chi2Val[0] << "/" << chi2Val[1] << " bins" << std::endl;
  }
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
}

// ####################################################################################################
// *** All Best NN Cut Fits ***
void branching::doBestFit(double cut_LL, double cut_DD, TString tag){
  
  // *** All Together ***
  fillDataset(cut_LL);
    
  char All_netcut[30];
  makeCut(cut_LL,All_netcut,m_ANY);
  double pub_yield[] = {-999,-999};

  // Combined fit only makes sense for situation where you optimized the combined LL+DD sample
  if(cut_LL==cut_DD){
    double pub_all[] = {-999,-999,-999,-999,-999,-999};
    doFullFit(All_netcut, pub_all, tag);
    
    char All_netcutOdd[30];
    strcpy(All_netcutOdd,"odd && ");
    strcat(All_netcutOdd,All_netcut);
    double pub_odd[] = {-999,-999,-999,-999,-999,-999};
    doFullFit(All_netcutOdd, pub_odd, tag);
  
    calcYield(pub_all, pub_odd, pub_yield);
  }

  // *** Long Long ***
  fillDataset(cut_LL);
    
  char LL_netcut[30];
  makeCut(cut_LL,LL_netcut,m_LL);
  double LL_all[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcut, LL_all, tag);

  char LL_netcutOdd[30];
  strcpy(LL_netcutOdd,"odd && ");
  strcat(LL_netcutOdd,LL_netcut);
  double LL_odd[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcutOdd, LL_odd, tag);
  
  double LL_yield[] = {-999,-999};
  calcYield(LL_all, LL_odd, LL_yield);
  
  
  // *** Down Down ***
  fillDataset(cut_DD);  

  char DD_netcut[30];
  makeCut(cut_DD,DD_netcut,m_DD);
  double DD_all[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcut, DD_all, tag);
  
  char DD_netcutOdd[30];
  strcpy(DD_netcutOdd,"odd && ");
  strcat(DD_netcutOdd,DD_netcut);
  double DD_odd[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcutOdd, DD_odd, tag);
  
  double DD_yield[] = {-999,-999};
  calcYield(DD_all, DD_odd, DD_yield);
  
  
  // *** PDG Average ***  
  double Av_yield[] = {-999,-999};
  PDGAverage(LL_yield, DD_yield, Av_yield);

  // *** Group Results Together ***
  if(cut_LL==cut_DD){printBF(tag+" "+All_netcut, pub_yield);}
  printBF(tag+" "+LL_netcut, LL_yield);
  printBF(tag+" "+DD_netcut, DD_yield);
  printBF(tag+" Averaged "+All_netcut, Av_yield);

}

// ####################################################################################################
// *** Effective Lifetime Fit ***
void branching::doLifetimeFit(double netVal, char* netcut, double *Results, TString tag){

  std::cout << "\n PROGRESS: Performing Effective Lifetime Fit for " << netcut << "\n" << std::endl ;

  // *** Prepare Data ***
  fillDataset(netVal);
  
  RooDataSet *fitdata = 0;
  char cut_decaytime[100];
  strcpy(cut_decaytime,netcut);
  
  if(tag=="FitRange14"){
    strcat(cut_decaytime," && time<=14.");
    fitdata = (RooDataSet *)m_data->reduce(cut_decaytime);
    m_time->setRange(0.2,14.);
  }
  else if(tag=="FitRange12"){
    strcat(cut_decaytime," && time<=12.");
    fitdata = (RooDataSet *)m_data->reduce(cut_decaytime);
    m_time->setRange(0.2,12.);
  }
  else if(tag=="FitRange10"){
    strcat(cut_decaytime," && time<=10.");
    fitdata = (RooDataSet *)m_data->reduce(cut_decaytime);
    m_time->setRange(0.2,10.);
  }
  else if(tag=="FitRange8"){
    strcat(cut_decaytime," && time<=8.");
    fitdata = (RooDataSet *)m_data->reduce(cut_decaytime);
    m_time->setRange(0.2,8.);
  }
  else if(tag=="FitRange6"){
    strcat(cut_decaytime," && time<=6.");
    fitdata = (RooDataSet *)m_data->reduce(cut_decaytime);
    m_time->setRange(0.2,6.);
  }
  else fitdata = (RooDataSet *)m_data->reduce(netcut);
  Int_t totEntries = fitdata->numEntries();
  
  // *** Prepare PDF ***
  string cutString (netcut);

  size_t isLL=cutString.find("LL==3");
  size_t isDD=cutString.find("LL==5");
  int track = 0;
  if(isLL!=string::npos) track = 3;
  else if(isDD!=string::npos) track = 5;
  else track = 0;

  JpsiKsPdf* jpsiKsExt = new JpsiKsPdf("",m_mass,m_time,true,m_fitKstar,track,"Optimal",totEntries);
  setPDFOptions(jpsiKsExt, tag);
  if(m_doMod) jpsiKsExt->setConstant("Mod");

  // *** Mass Fit ***
  RooFitResult* fitresult_mass = (RooFitResult *)jpsiKsExt->fitToMass(fitdata,false);
  //jpsiKsExt->setConstant("Mass");
  
  // *** Lifetime Fit ***
  RooFitResult* fitresult_time = (RooFitResult *)jpsiKsExt->fitToAll(fitdata,false);
  
  // *** Plot ***
  TCanvas *massPlot = new TCanvas("massPlot","Canvas for MassPlot",900,800);
  jpsiKsExt->plotOn(massPlot,fitdata,false,1,0); // Plot with legend
  jpsiKsExt->plotLegend(0.6,0.5,0.89,0.89,"mass");
  massPlot->Write("Full Mass Fit "+tag+" "+netcut);
  
  size_t absent=cutString.find("odd");
  if (absent==string::npos){
    TCanvas *pullPlot = new TCanvas("pullPlot","Canvas for MassPlot",900,800);
    jpsiKsExt->plotOn(pullPlot,fitdata,false,1,1); // Plot with parameters
    pullPlot->Write("Pull Mass Fit "+tag+" "+netcut);
  }
  
  TPaveText *lhcbTag = new TPaveText(0.64,0.89,0.93,0.93,"NDC");
  lhcbTag->SetFillColor(0);
  lhcbTag->SetTextAlign(12);
  lhcbTag->SetBorderSize(0);
  lhcbTag->SetTextSize(0.06);
  lhcbTag->SetTextFont(132); // lhcbFont
  lhcbTag->AddText("LHCb");

  TCanvas *TauPlot = new TCanvas("TauPlot","Canvas for LifetimePlot",900,800);
  double chi2Val[] = {-999,-999};
  jpsiKsExt->plotOnTime(TauPlot,fitdata,false,1,2,0,chi2Val); // Pull with legend
  jpsiKsExt->plotLegend(0.64,0.50,0.93,0.89,"All_time");
  lhcbTag->Draw("same");
  TauPlot->Write("Full Time Fit "+tag+" "+netcut);
  
  TCanvas *TaupullPlot = new TCanvas("TaupullPlot","Canvas for LifetimePlot",900,800);
  jpsiKsExt->plotOnTime(TaupullPlot,fitdata,false,1,1,0); // Plot with parameters
  TaupullPlot->Write("Pull Time Fit "+tag+" "+netcut);
  
  TCanvas *TauZoomPlot = new TCanvas("TauZoomPlot","Canvas for LifetimePlot",900,800);
  jpsiKsExt->plotOnTime(TauZoomPlot,fitdata,false,1,2,1); // Pull with legend in Bs Box
  jpsiKsExt->plotLegend(0.64,0.58,0.93,0.89,"Bs_time");
  lhcbTag->Draw("same");
  TauZoomPlot->Write("BsBox Time Fit "+tag+" "+netcut);

  TCanvas *TauBkgPlot = new TCanvas("TauBkgPlot","Canvas for LifetimePlot",900,800);
  jpsiKsExt->plotOnTime(TauBkgPlot,fitdata,false,1,2,2); // Pull with legend in high mass sideband
  jpsiKsExt->plotLegend(0.64,0.66,0.93,0.89,"Bkg_time");
  lhcbTag->Draw("same");
  TauBkgPlot->Write("MassSidebands Time Fit "+tag+" "+netcut);

  // *** Results ***
  Results[2] = jpsiKsExt->nBd()->getVal();
  Results[3] = jpsiKsExt->nBd()->getError();
  Results[4] = jpsiKsExt->nBs()->getVal();
  Results[5] = jpsiKsExt->nBs()->getError();
  Results[6] = jpsiKsExt->nonPeaking()->getVal();
  Results[7] = jpsiKsExt->nonPeaking()->getError();
  Results[0] = jpsiKsExt->tauBs()->getVal();
  Results[1] = jpsiKsExt->tauBs()->getError();
  Results[8] = jpsiKsExt->unblindResult();
  
  std::cout << "++++++++++++++++++++ results ++++++++++++++++++++" << std::endl;
  std::cout << "              Tag : " << tag << std::endl;
  std::cout << "   Neural Net Cut : " << netcut << std::endl;
  std::cout << "     # Events     : " << totEntries << std::endl;
  std::cout << "     # Bd->JpsiKs : " << Results[2] << " +/- " << Results[3] << std::endl;
  std::cout << "     # Bs->JpsiKs : " << Results[4] << " +/- " << Results[5] << std::endl;
  std::cout << "     # Background : " << Results[6] << " +/- " << Results[7] << std::endl;
  std::cout << "   Bs Eff Lifetime: " << Results[0] << " +/- " << Results[1] << std::endl;
  fitresult_mass->Print();
  fitresult_time->Print();
  std::cout << " PULL: Goodness of Fit estimate -> chi2 = " << chi2Val[0] << "/" << chi2Val[1] << " bins" << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
  
  // *** Clean-up ***
  m_time->setRange(0.2,15.);
  delete fitdata;

}

// ####################################################################################################
// *** Create Dataset ***
int branching::fillDataset(double cut){
  
  if(cut==previousNN){
    std::cout << " * No need to re-make the dataset" << std::endl;
    return 0;
  }
  else previousNN = cut;
  
  // *** Search for Multiple Candidates ***
  if(m_random==m_weightMethod) m_eventMap = createEventMap(m_ntuple, m_ttype, m_what, m_NNtype, cut) ;
  else m_eventMap = new MultipleCandidates();
  
  // *** Initialize Dataset ***
  RooRealVar *net = new RooRealVar("net","net",-2.0,2.0);
  RooRealVar *odd = new RooRealVar("odd","odd",0.0,2.0);
  RooRealVar *LL = new RooRealVar("LL","LL",0.0,10.0);
  RooRealVar *noBs = new RooRealVar("noBs","noBs",0.0,2.0);
  RooRealVar *event = new RooRealVar("event","event",0.0,5.0);
  RooRealVar *olddata = new RooRealVar("olddata","olddata",0.0,2.0);
  if (m_data) delete m_data ;
  m_data = new RooDataSet("data","data",RooArgList(*m_mass,*m_time, *net, *odd, *LL, *noBs, *event,*olddata));

  const Long64_t nentries = m_ntuple->nEntries();
  double frac = printFrac(nentries);
  Long64_t nKept = 0, nKept_LL = 0, nKept_DD = 0;
  Long64_t nKilled = 0, nKilled_LL = 0, nKilled_DD = 0;
  Long64_t nGood = 0, nGood_LL = 0, nGood_DD = 0;
  Long64_t nSinglePV = 0, nSinglePV_LL = 0, nSinglePV_DD = 0;
  Long64_t nbestPV = 0, nbestPV_LL = 0, nbestPV_DD = 0;
  Long64_t nMultiPV = 0, nMultiPV_LL = 0, nMultiPV_DD = 0;
  Long64_t nMultiPVtot = 0, nMultiPVtot_LL = 0, nMultiPVtot_DD = 0;
  Long64_t nbestMultiPV = 0, nbestMultiPV_LL = 0, nbestMultiPV_DD = 0;
  Long64_t nMuCa = 0, nMuCa_LL = 0, nMuCa_DD = 0;
  Long64_t nMuCaSinglePV = 0, nMuCaSinglePV_LL = 0, nMuCaSinglePV_DD = 0;
  Long64_t nMuCaMultiPV = 0, nMuCaMultiPV_LL = 0, nMuCaMultiPV_DD = 0;
  Long64_t nMuCaMultiPVtot = 0, nMuCaMultiPVtot_LL = 0, nMuCaMultiPVtot_DD = 0;
  Long64_t nFailed = 0, nFailed_LL = 0, nFailed_DD = 0;
  int addLL = 0;
  int addDD = 0;
  
  // *** Fill DataSet ***
  std::cout << " * Will loop over " << nentries << " Entries with cut " << cut << std::endl;
  for (Long64_t i=0; i<nentries;i++) {
    m_ntuple->GetChain()->GetEntry(i);
    if(m_ntuple->TrackType()==3){ addLL = 1; addDD = 0; }
    else{ addLL = 0; addDD = 1; }
    
    // Progress
    if(0==i%((int)(frac*nentries))) std::cout << " |-> " << i << " / " << nentries 
					      << " (" << 100*i/nentries << "%)" << std::endl;


    // Check if one of the (B,PV) pairs passes the selection cuts
    unsigned int nPV = m_ntuple->primaries();
    std::list<unsigned int> goodPVs;
    for ( unsigned int pv = 0 ; pv!=nPV ; pv++){
      if (m_ntuple->neuralnet(pv)>=cut){
        nKept++; nKept_LL += addLL; nKept_DD += addDD;
        goodPVs.push_back(pv);
      }
      else { nKilled++; nKilled_LL += addLL; nKilled_DD += addDD; }
    }
    // Selected events
    if(!goodPVs.empty() && goodPVs.size()>=1){
      // Surviving Candidates
      if (m_eventMap->pickMultipleCandidates(i,m_ntuple,m_weightMethod)){
        nGood++; nGood_LL += addLL; nGood_DD += addDD;
        int bpv = m_eventMap->pickBestPV(goodPVs);
        if(goodPVs.size()==1) {
          nSinglePV++; nSinglePV_LL += addLL; nSinglePV_DD += addDD;
          if(0==goodPVs.front()){ nbestPV++ ; nbestPV_LL += addLL; nbestPV_DD += addDD; }
          else{
            if(cut>0.){
              std::cout << "Case of not picking up bestPV at event " << m_ntuple->getRunNumber() << " " 
                        << m_ntuple->getEventNumber() << std::endl ;
              //m_ntuple->printCandidate(0);
              //m_ntuple->printCandidate(bpv);
            }
          }
        } else if(goodPVs.size()>1){
          nMultiPV++; nMultiPV_LL += addLL; nMultiPV_DD += addDD;
          nMultiPVtot += goodPVs.size(); nMultiPVtot_LL += addLL*goodPVs.size(); nMultiPVtot_DD += addDD*goodPVs.size();
          //m_ntuple->printCandidates(goodPVs) ;
          //std::cout << "Selected PV " << bpv << std::endl;
          if(0==goodPVs.front()){ nbestMultiPV++; nbestMultiPV_LL += addLL; nbestMultiPV_DD += addDD; }
        }
        
        // Assign observables
        m_mass->setVal(m_ntuple->mass(bpv));
        m_time->setVal(m_ntuple->time(bpv));
        net->setVal(m_ntuple->neuralnet(bpv));
        odd->setVal(m_ntuple->expertSample());
        LL->setVal(m_ntuple->TrackType());
        noBs->setVal(m_ntuple->noSigRegion(bpv));
        event->setVal(m_ntuple->getEventNumber()%3);
        olddata->setVal(m_ntuple->getRunNumber()<=94386 ? 0 : 1);
        // Identify 0.41 fb of old analysis: Up to July technical stop = 28/6/2011 - run 94386
      
        m_data->add(RooArgList(*m_mass, *m_time, *net, *odd, *LL, *noBs, *event, *olddata));
      }
      // Killed Multiple Candidates
      else{
        nMuCa++; nMuCa_LL += addLL; nMuCa_DD += addDD;
        if(goodPVs.size()==1){ nMuCaSinglePV++; nMuCaSinglePV_LL += addLL; nMuCaSinglePV_DD += addDD; }
        else if(goodPVs.size()>1){
          nMuCaMultiPV++; nMuCaMultiPV_LL += addLL; nMuCaMultiPV_DD += addDD;
          nMuCaMultiPVtot += goodPVs.size(); nMuCaMultiPVtot_LL += addLL*goodPVs.size(); nMuCaMultiPVtot_DD += addDD*goodPVs.size();
        }
      }
    }
    // Failed Cuts
    else{ nFailed++; nFailed_LL += addLL; nFailed_DD += addDD; }
  }

  // *** Results ***
  std::cout << " * Filling Done! " << std::endl;
  
  Long64_t m_nGood = nSinglePV + nMultiPV;
  Long64_t m_nGood_LL = nSinglePV_LL + nMultiPV_LL;
  Long64_t m_nGood_DD = nSinglePV_DD + nMultiPV_DD;
  
  Long64_t nentries_LL = nFailed_LL + nMuCa_LL + nGood_LL;
  Long64_t nentries_DD = nFailed_DD + nMuCa_DD + nGood_DD;
  Long64_t npairs_LL = nKilled_LL + nKept_LL;
  Long64_t npairs_DD = nKilled_DD + nKept_DD;
  Long64_t npairs = npairs_LL + npairs_DD;
  
  std::cout << "######################### Results #########################" << std::endl ;
  std::cout << "  Total number of candidates            : "
    << nentries << " = " << nentries_LL << " (LL) + " << nentries_DD << " (DD)" << std::endl;
  std::cout << "  Number of candidates failing cuts     : "
    << nFailed << " = " << nFailed_LL << " (LL) + " << nFailed_DD << " (DD)" << std::endl;
  std::cout << "  Number of killed Multiple candidates  : "
    << nMuCa << " = " << nMuCa_LL << " (LL) + " << nMuCa_DD << " (DD)" << std::endl;
  std::cout << "  Number of Good candidates             : "
    << nGood << " = " << nGood_LL << " (LL) + " << nGood_DD << " (DD)" << std::endl;
  std::cout << "###########################################################" << std::endl ;
  std::cout << "  Total number of (B,PV) pairs          : "
    << npairs << " = " << npairs_LL << " (LL) + " << npairs_DD << " (DD)" << std::endl;
  std::cout << "  Number of killed (B,PV) pairs         : "
    << nKilled << " = " << nKilled_LL << " (LL) + " << nKilled_DD << " (DD)" << std::endl;
  std::cout << "  Number of surviving (B,PV) pairs      : "
    << nKept << " = " << nKept_LL << " (LL) + " << nKept_DD << " (DD)" << std::endl;
  std::cout << "  |-> Of which MuCa single (B,PV) pairs : "
    << nMuCaSinglePV << " = " << nMuCaSinglePV_LL << " (LL) + " << nMuCaSinglePV_DD << " (DD)" << std::endl;
  std::cout << "  |-> Of which MuCa multi (B,PV) pairs  : "
    << nMuCaMultiPV << " (" << nMuCaMultiPVtot << ")" << " = " << nMuCaMultiPV_LL << " (" << nMuCaMultiPVtot_LL << ")"
    << " (LL) + " << nMuCaMultiPV_DD << " (" << nMuCaMultiPVtot_DD << ")" << " (DD)" << std::endl;
  std::cout << "  |-> Of which Good single (B,PV) pairs : "
    << nSinglePV << " = " << nSinglePV_LL << " (LL) + " << nSinglePV_DD << " (DD)" << std::endl;
  std::cout << "      |-> In which DaVinci got it right : "
    << nbestPV << " = " << nbestPV_LL << " (LL) + " << nbestPV_DD << " (DD)" << std::endl;
  std::cout << "      |-> In which DaVinci got it wrong : "
    << nSinglePV-nbestPV << " = " << nSinglePV_LL-nbestPV_LL << " (LL) + " << nSinglePV_DD-nbestPV_DD << " (DD)" << std::endl;
  std::cout << "  |-> Of which Good multi (B,PV) pairs  : "
    << nMultiPV << " (" << nMultiPVtot << ")" << " = " << nMultiPV_LL << " (" << nMultiPVtot_LL << ")"
    << " (LL) + " << nMultiPV_DD << " (" << nMultiPVtot_DD << ")" << " (DD)" << std::endl;
  std::cout << "      |-> In which DaVinci got it right : "
    << nbestMultiPV << " = " << nbestMultiPV_LL << " (LL) + " << nbestMultiPV_DD << " (DD)" << std::endl;
  std::cout << "      |-> In which DaVinci got it wrong : " << nMultiPV - nbestMultiPV
    << " = " << nMultiPV_LL-nbestMultiPV_LL << " (LL) + " << nMultiPV_DD-nbestMultiPV_DD << " (DD)" << std::endl;
  std::cout << "  Total number of good (B,PV) pairs     : "
    << m_nGood << " = " << m_nGood_LL << " (LL) + " << m_nGood_DD << " (DD)" << std::endl;
  std::cout << "###########################################################" << std::endl ;
  
  Int_t dentries = m_data->numEntries();
  std::cout << " * Dataset contains " << dentries << " Entries." << std::endl;
  return 0 ;
}


// ####################################################################################################
// *** Core Function ***
int branching::branchingFraction(){
  if(m_debug){ 
    std::cout << "\n PROGRESS: Creating Dataset \n" << std::endl;
    return fillDataset(0.75);
  }
/* 
  // Individual LL and DD Samples
  double lin_bestCut_LL = getBestCut(m_LL);
  double lin_bestCut_DD = getBestCut(m_DD);
  doBestFit(lin_bestCut_LL, lin_bestCut_DD, "LL+DD" );
  double bestCut[] = {0,0};
  TwoDScan(bestCut);
  m_bestCut_LL = bestCut[0];
  m_bestCut_DD = bestCut[1];
  doBestFit(m_bestCut_LL, m_bestCut_DD, "LL+DD" );
  
  // Combined Sample
  if(!m_trainInd){
    m_bestCut_ANY = getBestCut(m_ANY);
    doBestFit(m_bestCut_ANY, m_bestCut_ANY, "All" );
  }
*/
  setBestCut();
  doBestFit(m_bestCut_LL, m_bestCut_DD, "LL+DD" );
  m_outfile->Close();
/* 
  std::cout << std::endl;
  std::cout << "\n PROGRESS: Compare Optimisations \n" << std::endl;
  
  std::cout << "Result from Individual Optimisation of LL and DD:" << std::endl;
  TwoDPunzi(lin_bestCut_LL,lin_bestCut_DD);
  std::cout << std::endl;
  std::cout << "Result from Two Dim Optimisation of LL and DD:" << std::endl;
  TwoDPunzi(m_bestCut_LL,m_bestCut_DD);
  
  if(!m_trainInd){
    std::cout << std::endl;
    std::cout << "Result from Combined Optimisation with LL+DD merged:" << std::endl;
    OneDPunzi(m_bestCut_ANY,0);
    std::cout << std::endl;
    std::cout << "For comparison (no optimisation), Result using Individual LL and DD" << std::endl;
    TwoDPunzi(m_bestCut_ANY,m_bestCut_ANY);
  }
*/
  return 0 ;
}

// ####################################################################################################
// *** Core Function ***
int branching::scanPunzi(){
  
  // Get the signal and background estimates (uses Alpha = 10, by default)
  double lin_bestCut_LL = getBestCut(m_LL);
  double lin_bestCut_DD = getBestCut(m_DD);
  m_outfile->Close();
  double temp_bestCut[] = {0,0};
  
  // Alpha = 2.5
  TwoDScan(temp_bestCut,2.5);
  double grid_bestCut_LL_P25 = temp_bestCut[0];
  double grid_bestCut_DD_P25 = temp_bestCut[1];
 
  // Alpha = 5
  TwoDScan(temp_bestCut,5);
  double grid_bestCut_LL_P50 = temp_bestCut[0];
  double grid_bestCut_DD_P50 = temp_bestCut[1];
  
  // Alpha = 7.5
  TwoDScan(temp_bestCut,7.5);
  double grid_bestCut_LL_P75 = temp_bestCut[0];
  double grid_bestCut_DD_P75 = temp_bestCut[1];
  
  // Alpha = 10 (Default)
  TwoDScan(temp_bestCut,10);
  double grid_bestCut_LL_P100 = temp_bestCut[0];
  double grid_bestCut_DD_P100 = temp_bestCut[1];
  
  // Alpha = 12.5
  TwoDScan(temp_bestCut,12.5);
  double grid_bestCut_LL_P125 = temp_bestCut[0];
  double grid_bestCut_DD_P125 = temp_bestCut[1];
 
  // Alpha = 15
  TwoDScan(temp_bestCut,15);
  double grid_bestCut_LL_P150 = temp_bestCut[0];
  double grid_bestCut_DD_P150 = temp_bestCut[1];
  
  // Alpha = 17.5
  TwoDScan(temp_bestCut,17.5);
  double grid_bestCut_LL_P175 = temp_bestCut[0];
  double grid_bestCut_DD_P175 = temp_bestCut[1];
  
  // Alpha = 20 (Default)
  TwoDScan(temp_bestCut,20);
  double grid_bestCut_LL_P200 = temp_bestCut[0];
  double grid_bestCut_DD_P200 = temp_bestCut[1];


  std::cout << std::endl;
  std::cout << "\n PROGRESS: Compare Optimisations \n" << std::endl;

  std::cout << "=== Alpha = 2.5 ===" << std::endl;
  TwoDPunzi(grid_bestCut_LL_P25,grid_bestCut_DD_P25,2.5);
  std::cout << std::endl;
  
  std::cout << "=== Alpha = 5 ===" << std::endl;
  TwoDPunzi(grid_bestCut_LL_P50,grid_bestCut_DD_P50,5);
  std::cout << std::endl;
  
  std::cout << "=== Alpha = 7.5 ===" << std::endl;
  TwoDPunzi(grid_bestCut_LL_P75,grid_bestCut_DD_P75,7.5);
  std::cout << std::endl;
  
  std::cout << "=== Alpha = 10 ===" << std::endl;
  TwoDPunzi(grid_bestCut_LL_P100,grid_bestCut_DD_P100,10);
  std::cout << std::endl;
  
  std::cout << "=== Alpha = 12.5 ===" << std::endl;
  TwoDPunzi(grid_bestCut_LL_P125,grid_bestCut_DD_P125,12.5);
  std::cout << std::endl;
  
  std::cout << "=== Alpha = 15 ===" << std::endl;
  TwoDPunzi(grid_bestCut_LL_P150,grid_bestCut_DD_P150,15);
  std::cout << std::endl;
  
  std::cout << "=== Alpha = 17.5 ===" << std::endl;
  TwoDPunzi(grid_bestCut_LL_P175,grid_bestCut_DD_P175,17.5);
  std::cout << std::endl;
  
  std::cout << "=== Alpha = 20 ===" << std::endl;
  TwoDPunzi(grid_bestCut_LL_P200,grid_bestCut_DD_P200,20);
  std::cout << std::endl;
  
  return 0 ;
}

// ####################################################################################################
// *** Core Function ***
int branching::systematics(){

  // ***** Initialise ***** //
  ////////////////////////////
  
  setBestCut();


  // Group Fits to LL and DD sample together to prevent having to remake the data all the time

  // ***** Long Long ***** //
  ///////////////////////////
  
  // *** Prepare Data ***
  fillDataset(m_bestCut_LL);
  
  // *** Prepare Cut Strings ***
  char LL_netcut[30];
  makeCut(m_bestCut_LL,LL_netcut,m_LL);
  
  char LL_netcutOdd[30];
  strcpy(LL_netcutOdd,"odd && ");
  strcat(LL_netcutOdd,LL_netcut);

  // *** Default ***
  double LL_all_Default[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcut, LL_all_Default, "Default"); 
  double LL_odd_Default[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcutOdd, LL_odd_Default, "Default");
  double LL_yield_Default[] = {-999,-999};
  calcYield(LL_all_Default, LL_odd_Default, LL_yield_Default);

  // *** Gauss + Crystal Ball Signal Model ***
  double LL_all_GaussCB[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcut, LL_all_GaussCB, "GaussCB");
  double LL_odd_GaussCB[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcutOdd, LL_odd_GaussCB, "GaussCB");
  double LL_yield_GaussCB[] = {-999,-999};
  calcYield(LL_all_GaussCB, LL_odd_GaussCB, LL_yield_GaussCB);
  
  // *** Crystal Ball Signal Model ***
  double LL_all_CB[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcut, LL_all_CB, "CB");
  double LL_odd_CB[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcutOdd, LL_odd_CB, "CB");
  double LL_yield_CB[] = {-999,-999};
  calcYield(LL_all_CB, LL_odd_CB, LL_yield_CB);
  
  // *** Double Gauss Signal Model ***
  double LL_all_DoubleGauss[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcut, LL_all_DoubleGauss, "DoubleGauss");
  double LL_odd_DoubleGauss[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcutOdd, LL_odd_DoubleGauss, "DoubleGauss");
  double LL_yield_DoubleGauss[] = {-999,-999};
  calcYield(LL_all_DoubleGauss, LL_odd_DoubleGauss, LL_yield_DoubleGauss);
  
  // *** Fit Crystal Ball Tails ***
  double LL_all_FitTails[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcut, LL_all_FitTails, "FitTails");
  double LL_odd_FitTails[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcutOdd, LL_odd_FitTails, "FitTails");
  double LL_yield_FitTails[] = {-999,-999};
  calcYield(LL_all_FitTails, LL_odd_FitTails, LL_yield_FitTails);
  
  // *** Polynomial Background Model ***
  double LL_all_Poly[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcut, LL_all_Poly, "Poly");
  double LL_odd_Poly[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcutOdd, LL_odd_Poly, "Poly");
  double LL_yield_Poly[] = {-999,-999};
  calcYield(LL_all_Poly, LL_odd_Poly, LL_yield_Poly);

  // *** Uniform Background Model ***
  double LL_all_Uni[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcut, LL_all_Uni, "Uni");
  double LL_odd_Uni[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcutOdd, LL_odd_Uni, "Uni");
  double LL_yield_Uni[] = {-999,-999};
  calcYield(LL_all_Uni, LL_odd_Uni, LL_yield_Uni);
  
  // *** MassDiffPlus ***
  double LL_all_MassDiffPlus[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcut, LL_all_MassDiffPlus, "MassDiffPlus");
  double LL_odd_MassDiffPlus[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcutOdd, LL_odd_MassDiffPlus, "MassDiffPlus");
  double LL_yield_MassDiffPlus[] = {-999,-999};
  calcYield(LL_all_MassDiffPlus, LL_odd_MassDiffPlus, LL_yield_MassDiffPlus);
  
  // *** MassDiffMin ***
  double LL_all_MassDiffMin[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcut, LL_all_MassDiffMin, "MassDiffMin");
  double LL_odd_MassDiffMin[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcutOdd, LL_odd_MassDiffMin, "MassDiffMin");
  double LL_yield_MassDiffMin[] = {-999,-999};
  calcYield(LL_all_MassDiffMin, LL_odd_MassDiffMin, LL_yield_MassDiffMin);

  // *** MassDiffFit ***
  double LL_all_MassDiffFit[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcut, LL_all_MassDiffFit, "MassDiffFit");
  double LL_odd_MassDiffFit[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcutOdd, LL_odd_MassDiffFit, "MassDiffFit");
  double LL_yield_MassDiffFit[] = {-999,-999};
  calcYield(LL_all_MassDiffFit, LL_odd_MassDiffFit, LL_yield_MassDiffFit);

  // *** Mass Width Full Difference ***
  double LL_all_BMass[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcut, LL_all_BMass, "BMass");
  double LL_odd_BMass[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcutOdd, LL_odd_BMass, "BMass");
  double LL_yield_BMass[] = {-999,-999};
  calcYield(LL_all_BMass, LL_odd_BMass, LL_yield_BMass);

  // *** Mass Width Full Difference ***
  double LL_all_BJKMass[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcut, LL_all_BJKMass, "BJKMass");
  double LL_odd_BJKMass[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcutOdd, LL_odd_BJKMass, "BJKMass");
  double LL_yield_BJKMass[] = {-999,-999};
  calcYield(LL_all_BJKMass, LL_odd_BJKMass, LL_yield_BJKMass);

  // *** Mass Width Phase Space ***
  double LL_all_PhSp[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcut, LL_all_PhSp, "PhSp");
  double LL_odd_PhSp[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcutOdd, LL_odd_PhSp, "PhSp");
  double LL_yield_PhSp[] = {-999,-999};
  calcYield(LL_all_PhSp, LL_odd_PhSp, LL_yield_PhSp);

  // *** Mass Width MC Fit ***
  double LL_all_MCfit[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcut, LL_all_MCfit, "MCfit");
  double LL_odd_MCfit[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcutOdd, LL_odd_MCfit, "MCfit");
  double LL_yield_MCfit[] = {-999,-999};
  calcYield(LL_all_MCfit, LL_odd_MCfit, LL_yield_MCfit);
 
  // *** Mass Width MC Fit (+1 Sigma) ***
  double LL_all_MCfitPlus[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcut, LL_all_MCfitPlus, "MCfitPlus");
  double LL_odd_MCfitPlus[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcutOdd, LL_odd_MCfitPlus, "MCfitPlus");
  double LL_yield_MCfitPlus[] = {-999,-999};
  calcYield(LL_all_MCfitPlus, LL_odd_MCfitPlus, LL_yield_MCfitPlus);
  
  // *** Mass Width MC Fit (-1 Sigma) ***
  double LL_all_MCfitMin[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcut, LL_all_MCfitMin, "MCfitMin");
  double LL_odd_MCfitMin[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcutOdd, LL_odd_MCfitMin, "MCfitMin");
  double LL_yield_MCfitMin[] = {-999,-999};
  calcYield(LL_all_MCfitMin, LL_odd_MCfitMin, LL_yield_MCfitMin);

  // *** Mass Width Free Scale Factors ***
  double LL_all_MCfree[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcut, LL_all_MCfree, "MCfree");
  double LL_odd_MCfree[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcutOdd, LL_odd_MCfree, "MCfree");
  double LL_yield_MCfree[] = {-999,-999};
  calcYield(LL_all_MCfree, LL_odd_MCfree, LL_yield_MCfree);



  // ***** Down Down ***** //
  ///////////////////////////
  
  // *** Prepare Data ***
  fillDataset(m_bestCut_DD);
  
  // *** Prepare Cut Strings ***
  char DD_netcut[30];
  makeCut(m_bestCut_DD,DD_netcut,m_DD);
  
  char DD_netcutOdd[30];
  strcpy(DD_netcutOdd,"odd && ");
  strcat(DD_netcutOdd,DD_netcut);

  // *** Default ***
  double DD_all_Default[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcut, DD_all_Default, "Default");
  double DD_odd_Default[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcutOdd, DD_odd_Default, "Default");
  double DD_yield_Default[] = {-999,-999};
  calcYield(DD_all_Default, DD_odd_Default, DD_yield_Default);

  // *** Gauss + Crystal Ball Signal Model ***
  double DD_all_GaussCB[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcut, DD_all_GaussCB, "GaussCB");
  double DD_odd_GaussCB[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcutOdd, DD_odd_GaussCB, "GaussCB");
  double DD_yield_GaussCB[] = {-999,-999};
  calcYield(DD_all_GaussCB, DD_odd_GaussCB, DD_yield_GaussCB);
  
  // *** Crystal Ball Signal Model ***
  double DD_all_CB[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcut, DD_all_CB, "CB");
  double DD_odd_CB[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcutOdd, DD_odd_CB, "CB");
  double DD_yield_CB[] = {-999,-999};
  calcYield(DD_all_CB, DD_odd_CB, DD_yield_CB);
  
  // *** Double Gauss Signal Model ***
  double DD_all_DoubleGauss[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcut, DD_all_DoubleGauss, "DoubleGauss");
  double DD_odd_DoubleGauss[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcutOdd, DD_odd_DoubleGauss, "DoubleGauss");
  double DD_yield_DoubleGauss[] = {-999,-999};
  calcYield(DD_all_DoubleGauss, DD_odd_DoubleGauss, DD_yield_DoubleGauss);
  
  // *** Fit Crystal Ball Tails ***
  double DD_all_FitTails[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcut, DD_all_FitTails, "FitTails");
  double DD_odd_FitTails[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcutOdd, DD_odd_FitTails, "FitTails");
  double DD_yield_FitTails[] = {-999,-999};
  calcYield(DD_all_FitTails, DD_odd_FitTails, DD_yield_FitTails);
  
  // *** Polynomial Background Model ***
  double DD_all_Poly[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcut, DD_all_Poly, "Poly");
  double DD_odd_Poly[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcutOdd, DD_odd_Poly, "Poly");
  double DD_yield_Poly[] = {-999,-999};
  calcYield(DD_all_Poly, DD_odd_Poly, DD_yield_Poly);

  // *** Uniform Background Model ***
  double DD_all_Uni[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcut, DD_all_Uni, "Uni");
  double DD_odd_Uni[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcutOdd, DD_odd_Uni, "Uni");
  double DD_yield_Uni[] = {-999,-999};
  calcYield(DD_all_Uni, DD_odd_Uni, DD_yield_Uni);
 
  // *** MassDiffPlus ***
  double DD_all_MassDiffPlus[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcut, DD_all_MassDiffPlus, "MassDiffPlus");
  double DD_odd_MassDiffPlus[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcutOdd, DD_odd_MassDiffPlus, "MassDiffPlus");
  double DD_yield_MassDiffPlus[] = {-999,-999};
  calcYield(DD_all_MassDiffPlus, DD_odd_MassDiffPlus, DD_yield_MassDiffPlus);
  
  // *** MassDiffMin ***
  double DD_all_MassDiffMin[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcut, DD_all_MassDiffMin, "MassDiffMin");
  double DD_odd_MassDiffMin[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcutOdd, DD_odd_MassDiffMin, "MassDiffMin");
  double DD_yield_MassDiffMin[] = {-999,-999};
  calcYield(DD_all_MassDiffMin, DD_odd_MassDiffMin, DD_yield_MassDiffMin);

  // *** MassDiffFit ***
  double DD_all_MassDiffFit[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcut, DD_all_MassDiffFit, "MassDiffFit");
  double DD_odd_MassDiffFit[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcutOdd, DD_odd_MassDiffFit, "MassDiffFit");
  double DD_yield_MassDiffFit[] = {-999,-999};
  calcYield(DD_all_MassDiffFit, DD_odd_MassDiffFit, DD_yield_MassDiffFit);

  // *** Mass Width Full Difference ***
  double DD_all_BMass[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcut, DD_all_BMass, "BMass");
  double DD_odd_BMass[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcutOdd, DD_odd_BMass, "BMass");
  double DD_yield_BMass[] = {-999,-999};
  calcYield(DD_all_BMass, DD_odd_BMass, DD_yield_BMass);
  
  // *** Mass Width Full Difference ***
  double DD_all_BJKMass[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcut, DD_all_BJKMass, "BJKMass");
  double DD_odd_BJKMass[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcutOdd, DD_odd_BJKMass, "BJKMass");
  double DD_yield_BJKMass[] = {-999,-999};
  calcYield(DD_all_BJKMass, DD_odd_BJKMass, DD_yield_BJKMass);

  // *** Mass Width Phase Space ***
  double DD_all_PhSp[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcut, DD_all_PhSp, "PhSp");
  double DD_odd_PhSp[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcutOdd, DD_odd_PhSp, "PhSp");
  double DD_yield_PhSp[] = {-999,-999};
  calcYield(DD_all_PhSp, DD_odd_PhSp, DD_yield_PhSp);

  // *** Mass Width MC Fit ***
  double DD_aDD_MCfit[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcut, DD_aDD_MCfit, "MCfit");
  double DD_odd_MCfit[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcutOdd, DD_odd_MCfit, "MCfit");
  double DD_yield_MCfit[] = {-999,-999};
  calcYield(DD_aDD_MCfit, DD_odd_MCfit, DD_yield_MCfit);

  // *** Mass Width MC Fit (+1 Sigma) ***
  double DD_aDD_MCfitPlus[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcut, DD_aDD_MCfitPlus, "MCfitPlus");
  double DD_odd_MCfitPlus[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcutOdd, DD_odd_MCfitPlus, "MCfitPlus");
  double DD_yield_MCfitPlus[] = {-999,-999};
  calcYield(DD_aDD_MCfitPlus, DD_odd_MCfitPlus, DD_yield_MCfitPlus);
  
  // *** Mass Width MC Fit (-1 Sigma) ***
  double DD_aDD_MCfitMin[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcut, DD_aDD_MCfitMin, "MCfitMin");
  double DD_odd_MCfitMin[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcutOdd, DD_odd_MCfitMin, "MCfitMin");
  double DD_yield_MCfitMin[] = {-999,-999};
  calcYield(DD_aDD_MCfitMin, DD_odd_MCfitMin, DD_yield_MCfitMin);

  // *** Mass Width Free Scale Factors ***
  double DD_aDD_MCfree[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcut, DD_aDD_MCfree, "MCfree");
  double DD_odd_MCfree[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcutOdd, DD_odd_MCfree, "MCfree");
  double DD_yield_MCfree[] = {-999,-999};
  calcYield(DD_aDD_MCfree, DD_odd_MCfree, DD_yield_MCfree);

  

  // ***** Average ***** //
  /////////////////////////

  double Av_yield_Default[] = {-999,-999};
  PDGAverage(LL_yield_Default, DD_yield_Default, Av_yield_Default);
  double Av_yield_GaussCB[] = {-999,-999};
  PDGAverage(LL_yield_GaussCB, DD_yield_GaussCB, Av_yield_GaussCB);
  double Av_yield_CB[] = {-999,-999};
  PDGAverage(LL_yield_CB, DD_yield_CB, Av_yield_CB);
  double Av_yield_DoubleGauss[] = {-999,-999};
  PDGAverage(LL_yield_DoubleGauss, DD_yield_DoubleGauss, Av_yield_DoubleGauss);
  double Av_yield_FitTails[] = {-999,-999};
  PDGAverage(LL_yield_FitTails, DD_yield_FitTails, Av_yield_FitTails);
  double Av_yield_Poly[] = {-999,-999};
  PDGAverage(LL_yield_Poly, DD_yield_Poly, Av_yield_Poly);
  double Av_yield_Uni[] = {-999,-999};
  PDGAverage(LL_yield_Uni, DD_yield_Uni, Av_yield_Uni);
  double Av_yield_MassDiffPlus[] = {-999,-999};
  PDGAverage(LL_yield_MassDiffPlus, DD_yield_MassDiffPlus, Av_yield_MassDiffPlus);
  double Av_yield_MassDiffMin[] = {-999,-999};
  PDGAverage(LL_yield_MassDiffMin, DD_yield_MassDiffMin, Av_yield_MassDiffMin);
  double Av_yield_MassDiffFit[] = {-999,-999};
  PDGAverage(LL_yield_MassDiffFit, DD_yield_MassDiffFit, Av_yield_MassDiffFit);
  double Av_yield_BMass[] = {-999,-999};
  PDGAverage(LL_yield_BMass, DD_yield_BMass, Av_yield_BMass);
  double Av_yield_BJKMass[] = {-999,-999};
  PDGAverage(LL_yield_BJKMass, DD_yield_BJKMass, Av_yield_BJKMass);
  double Av_yield_PhSp[] = {-999,-999};
  PDGAverage(LL_yield_PhSp, DD_yield_PhSp, Av_yield_PhSp);
  double Av_yield_MCfit[] = {-999,-999};
  PDGAverage(LL_yield_MCfit, DD_yield_MCfit, Av_yield_MCfit);
  double Av_yield_MCfitPlus[] = {-999,-999};
  PDGAverage(LL_yield_MCfitPlus, DD_yield_MCfitPlus, Av_yield_MCfitPlus);
  double Av_yield_MCfitMin[] = {-999,-999};
  PDGAverage(LL_yield_MCfitMin, DD_yield_MCfitMin, Av_yield_MCfitMin);
  double Av_yield_MCfree[] = {-999,-999};
  PDGAverage(LL_yield_MCfree, DD_yield_MCfree, Av_yield_MCfree);

  // ***** Results ***** //
  /////////////////////////

  std::cout << std::endl;
  printBF("Default Long", LL_yield_Default);
  printBF("Default Downstream", DD_yield_Default);
  printBF("Default Averaged", Av_yield_Default);
  
  std::cout << std::endl;
  printBF("Gauss + Crystal Ball Long", LL_yield_GaussCB);
  printBF("Gauss + Crystal Ball Downstream", DD_yield_GaussCB);
  printBF("Gauss + Crystal Ball Averaged", Av_yield_GaussCB);
  
  std::cout << std::endl;
  printBF("Crystal Ball Long", LL_yield_CB);
  printBF("Crystal Ball Downstream", DD_yield_CB);
  printBF("Crystal Ball Averaged", Av_yield_CB);
  
  std::cout << std::endl;
  printBF("Double Gauss Long", LL_yield_DoubleGauss);
  printBF("Double Gauss Downstream", DD_yield_DoubleGauss);
  printBF("Double Gauss Averaged", Av_yield_DoubleGauss);
  
  std::cout << std::endl;
  printBF("Fit CB Tails Long", LL_yield_FitTails);
  printBF("Fit CB Tails Downstream", DD_yield_FitTails);
  printBF("Fit CB Tails Averaged", Av_yield_FitTails);
  
  std::cout << std::endl;
  printBF("Polynomial Bkg Long", LL_yield_Poly);
  printBF("Polynomial Bkg Downstream", DD_yield_Poly);
  printBF("Polynomial Bkg Averaged", Av_yield_Poly);
  
  std::cout << std::endl;
  printBF("Uniform Bkg Long", LL_yield_Uni);
  printBF("Uniform Bkg Downstream", DD_yield_Uni);
  printBF("Uniform Bkg Averaged", Av_yield_Uni);
  
  std::cout << std::endl;
  printBF("MassDiffPlus Long", LL_yield_MassDiffPlus);
  printBF("MassDiffPlus Downstream", DD_yield_MassDiffPlus);
  printBF("MassDiffPlus Averaged", Av_yield_MassDiffPlus);
  
  std::cout << std::endl;
  printBF("MassDiffMin Long", LL_yield_MassDiffMin);
  printBF("MassDiffMin Downstream", DD_yield_MassDiffMin);
  printBF("MassDiffMin Averaged", Av_yield_MassDiffMin);

  std::cout << std::endl;
  printBF("MassDiffFit Long", LL_yield_MassDiffFit);
  printBF("MassDiffFit Downstream", DD_yield_MassDiffFit);
  printBF("MassDiffFit Averaged", Av_yield_MassDiffFit);

  std::cout << std::endl;
  printBF("Scale Mass Width BMass Long", LL_yield_BMass);
  printBF("Scale Mass Width BMass Downstream", DD_yield_BMass);
  printBF("Scale Mass Width BMass Averaged", Av_yield_BMass);
  
  std::cout << std::endl;
  printBF("Scale Mass Width BJKMass Long", LL_yield_BJKMass);
  printBF("Scale Mass Width BJKMass Downstream", DD_yield_BJKMass);
  printBF("Scale Mass Width BJKMass Averaged", Av_yield_BJKMass);

  std::cout << std::endl;
  printBF("Scale Mass Width PhSp Long", LL_yield_PhSp);
  printBF("Scale Mass Width PhSp Downstream", DD_yield_PhSp);
  printBF("Scale Mass Width PhSp Averaged", Av_yield_PhSp);

  std::cout << std::endl;
  printBF("Scale Mass Width MCfit Long", LL_yield_MCfit);
  printBF("Scale Mass Width MCfit Downstream", DD_yield_MCfit);
  printBF("Scale Mass Width MCfit Averaged", Av_yield_MCfit);

  std::cout << std::endl;
  printBF("Scale Mass Width MCfitPlus Long", LL_yield_MCfitPlus);
  printBF("Scale Mass Width MCfitPlus Downstream", DD_yield_MCfitPlus);
  printBF("Scale Mass Width MCfitPlus Averaged", Av_yield_MCfitPlus);

  std::cout << std::endl;
  printBF("Scale Mass Width MCfitMin Long", LL_yield_MCfitMin);
  printBF("Scale Mass Width MCfitMin Downstream", DD_yield_MCfitMin);
  printBF("Scale Mass Width MCfitMin Averaged", Av_yield_MCfitMin);

  std::cout << std::endl;
  printBF("Scale Mass Width MCfree Long", LL_yield_MCfree);
  printBF("Scale Mass Width MCfree Downstream", DD_yield_MCfree);
  printBF("Scale Mass Width MCfree Averaged", Av_yield_MCfree);

}

// ####################################################################################################
// *** Core Function ***
int branching::splitEventNumber(){

  // ***** Initialise ***** //
  ////////////////////////////
  
  setBestCut();


  // Group Fits to LL and DD sample together to prevent having to remake the data all the time

  // ***** Long Long ***** //
  ///////////////////////////
  
  // *** Prepare Data ***
  fillDataset(m_bestCut_LL);
  m_doMod = false;
  
  // *** Prepare Cut Strings ***
  char LL_netcut[100];
  makeCut(m_bestCut_LL,LL_netcut,m_LL);
  char LL_netcutOdd[100];
  strcpy(LL_netcutOdd,"odd && ");
  strcat(LL_netcutOdd,LL_netcut);
  
  char LL_modzero[100];
  strcpy(LL_modzero,LL_netcut);
  strcat(LL_modzero," && event==0");
  char LL_modzeroOdd[100];
  strcpy(LL_modzeroOdd,"odd && ");
  strcat(LL_modzeroOdd,LL_modzero);
  
  char LL_modone[100];
  strcpy(LL_modone,LL_netcut);
  strcat(LL_modone," && event==1");
  char LL_modoneOdd[100];
  strcpy(LL_modoneOdd,"odd && ");
  strcat(LL_modoneOdd,LL_modone);
  
  char LL_modtwo[100];
  strcpy(LL_modtwo,LL_netcut);
  strcat(LL_modtwo," && event==2");
  char LL_modtwoOdd[100];
  strcpy(LL_modtwoOdd,"odd && ");
  strcat(LL_modtwoOdd,LL_modtwo);
/*  
  char LL_modthree[100];
  strcpy(LL_modthree,LL_netcut);
  strcat(LL_modthree," && event==3");
  char LL_modthreeOdd[100];
  strcpy(LL_modthreeOdd,"odd && ");
  strcat(LL_modthreeOdd,LL_modthree);
  
  char LL_modfour[100];
  strcpy(LL_modfour,LL_netcut);
  strcat(LL_modfour," && event==4");
  char LL_modfourOdd[100];
  strcpy(LL_modfourOdd,"odd && ");
  strcat(LL_modfourOdd,LL_modfour);
*/
  // *** All ***
  double LL_netcut_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcut, LL_netcut_Results, "All"); 
  double LL_netcutOdd_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcutOdd, LL_netcutOdd_Results, "All");
  double LL_netcut_yield[] = {-999,-999};
  calcYield(LL_netcut_Results, LL_netcutOdd_Results, LL_netcut_yield);
  double LL_netcut_Lifetime[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  doLifetimeFit(m_bestCut_LL,LL_netcut,LL_netcut_Lifetime,"Default");
  
  //m_doMod = true;

  // *** Mod Zero ***
  double LL_modzero_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_modzero, LL_modzero_Results, "Default"); 
  double LL_modzeroOdd_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_modzeroOdd, LL_modzeroOdd_Results, "Default");
  double LL_modzero_yield[] = {-999,-999};
  calcYield(LL_modzero_Results, LL_modzeroOdd_Results, LL_modzero_yield);
  double LL_modzero_Lifetime[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  doLifetimeFit(m_bestCut_LL,LL_modzero,LL_modzero_Lifetime,"Default");
  
  // *** Mod One ***
  double LL_modone_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_modone, LL_modone_Results, "Default"); 
  double LL_modoneOdd_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_modoneOdd, LL_modoneOdd_Results, "Default");
  double LL_modone_yield[] = {-999,-999};
  calcYield(LL_modone_Results, LL_modoneOdd_Results, LL_modone_yield);
  double LL_modone_Lifetime[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  doLifetimeFit(m_bestCut_LL,LL_modone,LL_modone_Lifetime,"Default");
  
  // *** Mod Two ***
  double LL_modtwo_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_modtwo, LL_modtwo_Results, "Default"); 
  double LL_modtwoOdd_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_modtwoOdd, LL_modtwoOdd_Results, "Default");
  double LL_modtwo_yield[] = {-999,-999};
  calcYield(LL_modtwo_Results, LL_modtwoOdd_Results, LL_modtwo_yield);
  double LL_modtwo_Lifetime[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  doLifetimeFit(m_bestCut_LL,LL_modtwo,LL_modtwo_Lifetime,"Default");
/*  
  // *** Mod Three ***
  double LL_modthree_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_modthree, LL_modthree_Results, "Default"); 
  double LL_modthreeOdd_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_modthreeOdd, LL_modthreeOdd_Results, "Default");
  double LL_modthree_yield[] = {-999,-999};
  calcYield(LL_modthree_Results, LL_modthreeOdd_Results, LL_modthree_yield);
  double LL_modthree_Lifetime[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  doLifetimeFit(m_bestCut_LL,LL_modthree,LL_modthree_Lifetime,"Default");
  
  // *** Mod Four ***
  double LL_modfour_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_modfour, LL_modfour_Results, "Default"); 
  double LL_modfourOdd_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_modfourOdd, LL_modfourOdd_Results, "Default");
  double LL_modfour_yield[] = {-999,-999};
  calcYield(LL_modfour_Results, LL_modfourOdd_Results, LL_modfour_yield);
  double LL_modfour_Lifetime[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  doLifetimeFit(m_bestCut_LL,LL_modfour,LL_modfour_Lifetime,"Default");
*/

  // ***** Down Down ***** //
  ///////////////////////////
  
  // *** Prepare Data ***
  fillDataset(m_bestCut_DD);
  m_doMod = false;
  
  // *** Prepare Cut Strings ***
  char DD_netcut[100];
  makeCut(m_bestCut_DD,DD_netcut,m_DD);
  char DD_netcutOdd[100];
  strcpy(DD_netcutOdd,"odd && ");
  strcat(DD_netcutOdd,DD_netcut);
  
  char DD_modzero[100];
  strcpy(DD_modzero,DD_netcut);
  strcat(DD_modzero," && event==0");
  char DD_modzeroOdd[100];
  strcpy(DD_modzeroOdd,"odd && ");
  strcat(DD_modzeroOdd,DD_modzero);
  
  char DD_modone[100];
  strcpy(DD_modone,DD_netcut);
  strcat(DD_modone," && event==1");
  char DD_modoneOdd[100];
  strcpy(DD_modoneOdd,"odd && ");
  strcat(DD_modoneOdd,DD_modone);
  
  char DD_modtwo[100];
  strcpy(DD_modtwo,DD_netcut);
  strcat(DD_modtwo," && event==2");
  char DD_modtwoOdd[100];
  strcpy(DD_modtwoOdd,"odd && ");
  strcat(DD_modtwoOdd,DD_modtwo);
/*  
  char DD_modthree[100];
  strcpy(DD_modthree,DD_netcut);
  strcat(DD_modthree," && event==3");
  char DD_modthreeOdd[100];
  strcpy(DD_modthreeOdd,"odd && ");
  strcat(DD_modthreeOdd,DD_modthree);
  
  char DD_modfour[100];
  strcpy(DD_modfour,DD_netcut);
  strcat(DD_modfour," && event==4");
  char DD_modfourOdd[100];
  strcpy(DD_modfourOdd,"odd && ");
  strcat(DD_modfourOdd,DD_modfour);
*/

  // *** All ***
  double DD_netcut_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcut, DD_netcut_Results, "All"); 
  double DD_netcutOdd_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcutOdd, DD_netcutOdd_Results, "All");
  double DD_netcut_yield[] = {-999,-999};
  calcYield(DD_netcut_Results, DD_netcutOdd_Results, DD_netcut_yield);
  double DD_netcut_Lifetime[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  doLifetimeFit(m_bestCut_DD,DD_netcut,DD_netcut_Lifetime,"Default");
  
  //m_doMod = true;

  // *** Mod Zero ***
  double DD_modzero_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_modzero, DD_modzero_Results, "Default"); 
  double DD_modzeroOdd_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_modzeroOdd, DD_modzeroOdd_Results, "Default");
  double DD_modzero_yield[] = {-999,-999};
  calcYield(DD_modzero_Results, DD_modzeroOdd_Results, DD_modzero_yield);
  double DD_modzero_Lifetime[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  doLifetimeFit(m_bestCut_DD,DD_modzero,DD_modzero_Lifetime,"Default");
  
  // *** Mod One ***
  double DD_modone_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_modone, DD_modone_Results, "Default"); 
  double DD_modoneOdd_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_modoneOdd, DD_modoneOdd_Results, "Default");
  double DD_modone_yield[] = {-999,-999};
  calcYield(DD_modone_Results, DD_modoneOdd_Results, DD_modone_yield);
  double DD_modone_Lifetime[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  doLifetimeFit(m_bestCut_DD,DD_modone,DD_modone_Lifetime,"Default");
  
  // *** Mod Two ***
  double DD_modtwo_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_modtwo, DD_modtwo_Results, "Default"); 
  double DD_modtwoOdd_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_modtwoOdd, DD_modtwoOdd_Results, "Default");
  double DD_modtwo_yield[] = {-999,-999};
  calcYield(DD_modtwo_Results, DD_modtwoOdd_Results, DD_modtwo_yield);
  double DD_modtwo_Lifetime[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  doLifetimeFit(m_bestCut_DD,DD_modtwo,DD_modtwo_Lifetime,"Default");
/*  
  // *** Mod Three ***
  double DD_modthree_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_modthree, DD_modthree_Results, "Default"); 
  double DD_modthreeOdd_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_modthreeOdd, DD_modthreeOdd_Results, "Default");
  double DD_modthree_yield[] = {-999,-999};
  calcYield(DD_modthree_Results, DD_modthreeOdd_Results, DD_modthree_yield);
  double DD_modthree_Lifetime[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  doLifetimeFit(m_bestCut_DD,DD_modthree,DD_modthree_Lifetime,"Default");
  
  // *** Mod Four ***
  double DD_modfour_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_modfour, DD_modfour_Results, "Default"); 
  double DD_modfourOdd_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_modfourOdd, DD_modfourOdd_Results, "Default");
  double DD_modfour_yield[] = {-999,-999};
  calcYield(DD_modfour_Results, DD_modfourOdd_Results, DD_modfour_yield);
  double DD_modfour_Lifetime[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  doLifetimeFit(m_bestCut_DD,DD_modfour,DD_modfour_Lifetime,"Default");
*/

  // ***** Average ***** //
  /////////////////////////
  
  double Av_netcut_yield[] = {-999,-999};
  PDGAverage(LL_netcut_yield,DD_netcut_yield,Av_netcut_yield);
  
  double Av_modzero_yield[] = {-999,-999};
  PDGAverage(LL_modzero_yield,DD_modzero_yield,Av_modzero_yield);
  
  double Av_modone_yield[] = {-999,-999};
  PDGAverage(LL_modone_yield,DD_modone_yield,Av_modone_yield);
  
  double Av_modtwo_yield[] = {-999,-999};
  PDGAverage(LL_modtwo_yield,DD_modtwo_yield,Av_modtwo_yield);
/*  
  double Av_modthree_yield[] = {-999,-999};
  PDGAverage(LL_modthree_yield,DD_modthree_yield,Av_modthree_yield);
  
  double Av_modfour_yield[] = {-999,-999};
  PDGAverage(LL_modfour_yield,DD_modfour_yield,Av_modfour_yield);
*/

  double Av_LL_yield[] = {-999,-999};
  double LL_yield[] = {LL_modzero_yield[0],LL_modone_yield[0],LL_modtwo_yield[0]};
  double LL_error[] = {LL_modzero_yield[1],LL_modone_yield[1],LL_modtwo_yield[1]};
  PDGAverage(3,LL_yield,LL_error,Av_LL_yield);
  
  double Av_DD_yield[] = {-999,-999};
  double DD_yield[] = {DD_modzero_yield[0],DD_modone_yield[0],DD_modtwo_yield[0]};
  double DD_error[] = {DD_modzero_yield[1],DD_modone_yield[1],DD_modtwo_yield[1]};
  PDGAverage(3,DD_yield,DD_error,Av_DD_yield);
  
  double Av_Av_yield[] = {-999,-999};
  double Av_yield[] = {Av_modzero_yield[0],Av_modone_yield[0],Av_modtwo_yield[0]};
  double Av_error[] = {Av_modzero_yield[1],Av_modone_yield[1],Av_modtwo_yield[1]};
  PDGAverage(3,Av_yield,Av_error,Av_Av_yield);
  
  

  double Av_netcut_Lifetime[] = {-999,-999};
  PDGAverage(LL_netcut_Lifetime,DD_netcut_Lifetime,Av_netcut_Lifetime);

  double Av_modzero_Lifetime[] = {-999,-999};
  PDGAverage(LL_modzero_Lifetime,DD_modzero_Lifetime,Av_modzero_Lifetime);
  
  double Av_modone_Lifetime[] = {-999,-999};
  PDGAverage(LL_modone_Lifetime,DD_modone_Lifetime,Av_modone_Lifetime);
  
  double Av_modtwo_Lifetime[] = {-999,-999};
  PDGAverage(LL_modtwo_Lifetime,DD_modtwo_Lifetime,Av_modtwo_Lifetime);
/*  
  double Av_modthree_Lifetime[] = {-999,-999};
  PDGAverage(LL_modthree_Lifetime,DD_modthree_Lifetime,Av_modthree_Lifetime);
  
  double Av_modfour_Lifetime[] = {-999,-999};
  PDGAverage(LL_modfour_Lifetime,DD_modfour_Lifetime,Av_modfour_Lifetime);
*/

  double Av_LL_Lifetime[] = {-999,-999};
  double LL_Lifetime[] = {LL_modzero_Lifetime[0],LL_modone_Lifetime[0],LL_modtwo_Lifetime[0]};
  double LL_TauError[] = {LL_modzero_Lifetime[1],LL_modone_Lifetime[1],LL_modtwo_Lifetime[1]};
  PDGAverage(3,LL_Lifetime,LL_TauError,Av_LL_Lifetime);
  
  double Av_DD_Lifetime[] = {-999,-999};
  double DD_Lifetime[] = {DD_modzero_Lifetime[0],DD_modone_Lifetime[0],DD_modtwo_Lifetime[0]};
  double DD_TauError[] = {DD_modzero_Lifetime[1],DD_modone_Lifetime[1],DD_modtwo_Lifetime[1]};
  PDGAverage(3,DD_Lifetime,DD_TauError,Av_DD_Lifetime);
  
  double Av_Av_Lifetime[] = {-999,-999};
  double Av_Lifetime[] = {Av_modzero_Lifetime[0],Av_modone_Lifetime[0],Av_modtwo_Lifetime[0]};
  double Av_TauError[] = {Av_modzero_Lifetime[1],Av_modone_Lifetime[1],Av_modtwo_Lifetime[1]};
  PDGAverage(3,Av_Lifetime,Av_TauError,Av_Av_Lifetime);

  // ***** Results ***** //
  /////////////////////////

  std::cout << std::endl;
  printBF("All Long", LL_netcut_yield);
  printBF("All Downstream", DD_netcut_yield);
  printBF("All Averaged", Av_netcut_yield);

  std::cout << std::endl;
  printBF("Av Long", Av_LL_yield);
  printBF("Av Downstream", Av_DD_yield);
  printBF("Av Averaged", Av_Av_yield);

  std::cout << std::endl;
  printBF("EventNumber = 0 Mod 3 Long", LL_modzero_yield);
  printBF("EventNumber = 0 Mod 3 Downstream", DD_modzero_yield);
  printBF("EventNumber = 0 Mod 3 Averaged", Av_modzero_yield);
  
  std::cout << std::endl;
  printBF("EventNumber = 1 Mod 3 Long", LL_modone_yield);
  printBF("EventNumber = 1 Mod 3 Downstream", DD_modone_yield);
  printBF("EventNumber = 1 Mod 3 Averaged", Av_modone_yield);

  std::cout << std::endl;
  printBF("EventNumber = 2 Mod 3 Long", LL_modtwo_yield);
  printBF("EventNumber = 2 Mod 3 Downstream", DD_modtwo_yield);
  printBF("EventNumber = 2 Mod 3 Averaged", Av_modtwo_yield);
/*
  std::cout << std::endl;
  printBF("EventNumber = 3 Mod 5 Long", LL_modthree_yield);
  printBF("EventNumber = 3 Mod 5 Downstream", DD_modthree_yield);
  printBF("EventNumber = 3 Mod 5 Averaged", Av_modthree_yield);

  std::cout << std::endl;
  printBF("EventNumber = 4 Mod 5 Long", LL_modfour_yield);
  printBF("EventNumber = 4 Mod 5 Downstream", DD_modfour_yield);
  printBF("EventNumber = 5 Mod 5 Averaged", Av_modfour_yield);
*/

  std::cout << std::endl;
  std::cout << "++++++++++++++++++++ All ++++++++++++++++++++" << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << LL_netcut_Lifetime[0] << " +/- " << LL_netcut_Lifetime[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << DD_netcut_Lifetime[0] << " +/- " << DD_netcut_Lifetime[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << Av_netcut_Lifetime[0] << " +/- " << Av_netcut_Lifetime[1] << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
  
  std::cout << std::endl;
  std::cout << "++++++++++++++++++++ Average ++++++++++++++++++++" << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << Av_LL_Lifetime[0] << " +/- " << Av_LL_Lifetime[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << Av_DD_Lifetime[0] << " +/- " << Av_DD_Lifetime[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << Av_Av_Lifetime[0] << " +/- " << Av_Av_Lifetime[1] << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;

  std::cout << std::endl;
  std::cout << "++++++++++++++++++++ Mod Zero +++++++++++++++++++" << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << LL_modzero_Lifetime[0] << " +/- " << LL_modzero_Lifetime[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << DD_modzero_Lifetime[0] << " +/- " << DD_modzero_Lifetime[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << Av_modzero_Lifetime[0] << " +/- " << Av_modzero_Lifetime[1] << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
  
  std::cout << std::endl;
  std::cout << "++++++++++++++++++++ Mod One ++++++++++++++++++++" << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << LL_modone_Lifetime[0] << " +/- " << LL_modone_Lifetime[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << DD_modone_Lifetime[0] << " +/- " << DD_modone_Lifetime[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << Av_modone_Lifetime[0] << " +/- " << Av_modone_Lifetime[1] << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
  
  std::cout << std::endl;
  std::cout << "++++++++++++++++++++ Mod Two ++++++++++++++++++++" << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << LL_modtwo_Lifetime[0] << " +/- " << LL_modtwo_Lifetime[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << DD_modtwo_Lifetime[0] << " +/- " << DD_modtwo_Lifetime[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << Av_modtwo_Lifetime[0] << " +/- " << Av_modtwo_Lifetime[1] << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
/*
  std::cout << std::endl;
  std::cout << "++++++++++++++++++++ Mod Three ++++++++++++++++++" << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << LL_modthree_Lifetime[0] << " +/- " << LL_modthree_Lifetime[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << DD_modthree_Lifetime[0] << " +/- " << DD_modthree_Lifetime[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << Av_modthree_Lifetime[0] << " +/- " << Av_modthree_Lifetime[1] << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
  
  std::cout << std::endl;
  std::cout << "++++++++++++++++++++ Mod Four +++++++++++++++++++" << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << LL_modfour_Lifetime[0] << " +/- " << LL_modfour_Lifetime[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << DD_modfour_Lifetime[0] << " +/- " << DD_modfour_Lifetime[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << Av_modfour_Lifetime[0] << " +/- " << Av_modfour_Lifetime[1] << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
*/

  // *** Finilise ***
  m_outfile->Close();
  return 0;
}

// ####################################################################################################
// *** Core Function ***
int branching::splitOldNewData(){

  // ***** Initialise ***** //
  ////////////////////////////
  
  setBestCut();


  // Group Fits to LL and DD sample together to prevent having to remake the data all the time

  // ***** Long Long ***** //
  ///////////////////////////
  
  // *** Prepare Data ***
  fillDataset(m_bestCut_LL);
  m_doMod = false;
  
  // *** Prepare Cut Strings ***
  char LL_netcut[100];
  makeCut(m_bestCut_LL,LL_netcut,m_LL);
  char LL_netcutOdd[100];
  strcpy(LL_netcutOdd,"odd && ");
  strcat(LL_netcutOdd,LL_netcut);
  
  char LL_olddata[100];
  strcpy(LL_olddata,LL_netcut);
  strcat(LL_olddata," && olddata==0");
  char LL_olddataOdd[100];
  strcpy(LL_olddataOdd,"odd && ");
  strcat(LL_olddataOdd,LL_olddata);
  
  char LL_newdata[100];
  strcpy(LL_newdata,LL_netcut);
  strcat(LL_newdata," && olddata==1");
  char LL_newdataOdd[100];
  strcpy(LL_newdataOdd,"odd && ");
  strcat(LL_newdataOdd,LL_newdata);

  // *** All ***
  double LL_netcut_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcut, LL_netcut_Results, "All"); 
  double LL_netcutOdd_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_netcutOdd, LL_netcutOdd_Results, "All");
  double LL_netcut_yield[] = {-999,-999};
  calcYield(LL_netcut_Results, LL_netcutOdd_Results, LL_netcut_yield);
  double LL_netcut_Lifetime[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  doLifetimeFit(m_bestCut_LL,LL_netcut,LL_netcut_Lifetime,"Default");
  
  //m_doMod = true;

  // *** Mod Zero ***
  double LL_olddata_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_olddata, LL_olddata_Results, "Default"); 
  double LL_olddataOdd_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_olddataOdd, LL_olddataOdd_Results, "Default");
  double LL_olddata_yield[] = {-999,-999};
  calcYield(LL_olddata_Results, LL_olddataOdd_Results, LL_olddata_yield);
  double LL_olddata_Lifetime[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  doLifetimeFit(m_bestCut_LL,LL_olddata,LL_olddata_Lifetime,"Default");
  
  // *** Mod One ***
  double LL_newdata_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_newdata, LL_newdata_Results, "Default"); 
  double LL_newdataOdd_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(LL_newdataOdd, LL_newdataOdd_Results, "Default");
  double LL_newdata_yield[] = {-999,-999};
  calcYield(LL_newdata_Results, LL_newdataOdd_Results, LL_newdata_yield);
  double LL_newdata_Lifetime[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  doLifetimeFit(m_bestCut_LL,LL_newdata,LL_newdata_Lifetime,"Default");
  

  // ***** Down Down ***** //
  ///////////////////////////
  
  // *** Prepare Data ***
  fillDataset(m_bestCut_DD);
  m_doMod = false;
  
  // *** Prepare Cut Strings ***
  char DD_netcut[100];
  makeCut(m_bestCut_DD,DD_netcut,m_DD);
  char DD_netcutOdd[100];
  strcpy(DD_netcutOdd,"odd && ");
  strcat(DD_netcutOdd,DD_netcut);
  
  char DD_olddata[100];
  strcpy(DD_olddata,DD_netcut);
  strcat(DD_olddata," && olddata==0");
  char DD_olddataOdd[100];
  strcpy(DD_olddataOdd,"odd && ");
  strcat(DD_olddataOdd,DD_olddata);
  
  char DD_newdata[100];
  strcpy(DD_newdata,DD_netcut);
  strcat(DD_newdata," && olddata==1");
  char DD_newdataOdd[100];
  strcpy(DD_newdataOdd,"odd && ");
  strcat(DD_newdataOdd,DD_newdata);


  // *** All ***
  double DD_netcut_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcut, DD_netcut_Results, "All"); 
  double DD_netcutOdd_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_netcutOdd, DD_netcutOdd_Results, "All");
  double DD_netcut_yield[] = {-999,-999};
  calcYield(DD_netcut_Results, DD_netcutOdd_Results, DD_netcut_yield);
  double DD_netcut_Lifetime[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  doLifetimeFit(m_bestCut_DD,DD_netcut,DD_netcut_Lifetime,"Default");
  
  //m_doMod = true;

  // *** Mod Zero ***
  double DD_olddata_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_olddata, DD_olddata_Results, "Default"); 
  double DD_olddataOdd_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_olddataOdd, DD_olddataOdd_Results, "Default");
  double DD_olddata_yield[] = {-999,-999};
  calcYield(DD_olddata_Results, DD_olddataOdd_Results, DD_olddata_yield);
  double DD_olddata_Lifetime[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  doLifetimeFit(m_bestCut_DD,DD_olddata,DD_olddata_Lifetime,"Default");
  
  // *** Mod One ***
  double DD_newdata_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_newdata, DD_newdata_Results, "Default"); 
  double DD_newdataOdd_Results[] = {-999,-999,-999,-999,-999,-999};
  doFullFit(DD_newdataOdd, DD_newdataOdd_Results, "Default");
  double DD_newdata_yield[] = {-999,-999};
  calcYield(DD_newdata_Results, DD_newdataOdd_Results, DD_newdata_yield);
  double DD_newdata_Lifetime[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  doLifetimeFit(m_bestCut_DD,DD_newdata,DD_newdata_Lifetime,"Default");


  // ***** Average ***** //
  /////////////////////////
  
  double Av_netcut_yield[] = {-999,-999};
  PDGAverage(LL_netcut_yield,DD_netcut_yield,Av_netcut_yield);
  
  double Av_olddata_yield[] = {-999,-999};
  PDGAverage(LL_olddata_yield,DD_olddata_yield,Av_olddata_yield);
  
  double Av_newdata_yield[] = {-999,-999};
  PDGAverage(LL_newdata_yield,DD_newdata_yield,Av_newdata_yield);

  double Av_LL_yield[] = {-999,-999};
  double LL_yield[] = {LL_olddata_yield[0],LL_newdata_yield[0]};
  double LL_error[] = {LL_olddata_yield[1],LL_newdata_yield[1]};
  PDGAverage(2,LL_yield,LL_error,Av_LL_yield);
  
  double Av_DD_yield[] = {-999,-999};
  double DD_yield[] = {DD_olddata_yield[0],DD_newdata_yield[0]};
  double DD_error[] = {DD_olddata_yield[1],DD_newdata_yield[1]};
  PDGAverage(2,DD_yield,DD_error,Av_DD_yield);
  
  double Av_Av_yield[] = {-999,-999};
  double Av_yield[] = {Av_olddata_yield[0],Av_newdata_yield[0]};
  double Av_error[] = {Av_olddata_yield[1],Av_newdata_yield[1]};
  PDGAverage(2,Av_yield,Av_error,Av_Av_yield);
  
  
  double Av_netcut_Lifetime[] = {-999,-999};
  PDGAverage(LL_netcut_Lifetime,DD_netcut_Lifetime,Av_netcut_Lifetime);

  double Av_olddata_Lifetime[] = {-999,-999};
  PDGAverage(LL_olddata_Lifetime,DD_olddata_Lifetime,Av_olddata_Lifetime);
  
  double Av_newdata_Lifetime[] = {-999,-999};
  PDGAverage(LL_newdata_Lifetime,DD_newdata_Lifetime,Av_newdata_Lifetime);

  double Av_LL_Lifetime[] = {-999,-999};
  double LL_Lifetime[] = {LL_olddata_Lifetime[0],LL_newdata_Lifetime[0]};
  double LL_TauError[] = {LL_olddata_Lifetime[1],LL_newdata_Lifetime[1]};
  PDGAverage(2,LL_Lifetime,LL_TauError,Av_LL_Lifetime);
  
  double Av_DD_Lifetime[] = {-999,-999};
  double DD_Lifetime[] = {DD_olddata_Lifetime[0],DD_newdata_Lifetime[0]};
  double DD_TauError[] = {DD_olddata_Lifetime[1],DD_newdata_Lifetime[1]};
  PDGAverage(2,DD_Lifetime,DD_TauError,Av_DD_Lifetime);
  
  
  double Av_Av_Lifetime[] = {-999,-999};
  double Av_Lifetime[] = {Av_olddata_Lifetime[0],Av_newdata_Lifetime[0]};
  double Av_TauError[] = {Av_olddata_Lifetime[1],Av_newdata_Lifetime[1]};
  PDGAverage(2,Av_Lifetime,Av_TauError,Av_Av_Lifetime);

  // ***** Results ***** //
  /////////////////////////

  std::cout << std::endl;
  printBF("All Long", LL_netcut_yield);
  printBF("All Downstream", DD_netcut_yield);
  printBF("All Averaged", Av_netcut_yield);

  std::cout << std::endl;
  printBF("Av Long", Av_LL_yield);
  printBF("Av Downstream", Av_DD_yield);
  printBF("Av Averaged", Av_Av_yield);

  std::cout << std::endl;
  printBF("Spring 2011 Long", LL_olddata_yield);
  printBF("Spring 2011 Downstream", DD_olddata_yield);
  printBF("Spring 2011 Averaged", Av_olddata_yield);
  
  std::cout << std::endl;
  printBF("Summer/Autumn 2011 Long", LL_newdata_yield);
  printBF("Summer/Autumn 2011 Downstream", DD_newdata_yield);
  printBF("Summer/Autumn 2011 Averaged", Av_newdata_yield);


  std::cout << std::endl;
  std::cout << "++++++++++++++++++++ Full 2011 Data Sample ++++++++++++++++++++" << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << LL_netcut_Lifetime[0] << " +/- " << LL_netcut_Lifetime[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << DD_netcut_Lifetime[0] << " +/- " << DD_netcut_Lifetime[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << Av_netcut_Lifetime[0] << " +/- " << Av_netcut_Lifetime[1] << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
  
  std::cout << std::endl;
  std::cout << "++++++++++++++++++++ Average ++++++++++++++++++++" << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << Av_LL_Lifetime[0] << " +/- " << Av_LL_Lifetime[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << Av_DD_Lifetime[0] << " +/- " << Av_DD_Lifetime[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << Av_Av_Lifetime[0] << " +/- " << Av_Av_Lifetime[1] << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;

  std::cout << std::endl;
  std::cout << "++++++++++++++++++++ Spring 2011 Data Sample (old analysis) +++++++++++++++++++" << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << LL_olddata_Lifetime[0] << " +/- " << LL_olddata_Lifetime[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << DD_olddata_Lifetime[0] << " +/- " << DD_olddata_Lifetime[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << Av_olddata_Lifetime[0] << " +/- " << Av_olddata_Lifetime[1] << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
  
  std::cout << std::endl;
  std::cout << "++++++++++++++++++++ Summer/Autumn 2011 Data Sample ++++++++++++++++++++" << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << LL_newdata_Lifetime[0] << " +/- " << LL_newdata_Lifetime[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << DD_newdata_Lifetime[0] << " +/- " << DD_newdata_Lifetime[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << Av_newdata_Lifetime[0] << " +/- " << Av_newdata_Lifetime[1] << std::endl;
  std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;

  // *** Finilise ***
  m_outfile->Close();
  return 0;
}

// ####################################################################################################
// *** Core Function ***
int branching::effectifeLifetime(){

  setBestCut();
  
  // *** Long ***
  char LL_netcut[30];
  makeCut(m_bestCut_LL,LL_netcut,m_LL);

  double lifetime_LL[] = {-999,-999,-999,-999,-999,-999,-999,-999,-999};
  doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL,"Tau");
  double blinded_LL[] = {lifetime_LL[0],lifetime_LL[1]};
  double unblind_LL[] = {lifetime_LL[8],lifetime_LL[1]};
 
  // *** Downstream ***
  char DD_netcut[30];
  makeCut(m_bestCut_DD,DD_netcut,m_DD);

  double lifetime_DD[] = {-999,-999,-999,-999,-999,-999,-999,-999,-999};
  doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD,"Tau");
  double blinded_DD[] = {lifetime_DD[0],lifetime_DD[1]};
  double unblind_DD[] = {lifetime_DD[8],lifetime_DD[1]};
  
  // *** Average ***
  double blinded_Av[] = {-999,-999};
  PDGAverage(blinded_LL,blinded_DD,blinded_Av);
  std::cout << std::endl;
  std::cout << "++++++++++++++++++++ Blinded Results ++++++++++++++++++++" << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << blinded_LL[0] << " +/- " << blinded_LL[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << blinded_DD[0] << " +/- " << blinded_DD[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << blinded_Av[0] << " +/- " << blinded_Av[1] << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
  std::cout << std::endl;
  
  if(m_unblind){
    double unblind_Av[] = {-999,-999};
    PDGAverage(unblind_LL,unblind_DD,unblind_Av);
    std::cout << "++++++++++++++++++++ Unblind Results ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << unblind_LL[0] << " +/- " << unblind_LL[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << unblind_DD[0] << " +/- " << unblind_DD[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << unblind_Av[0] << " +/- " << unblind_Av[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
    std::cout << std::endl;
  }
 
  // *** Finilise ***
  m_outfile->Close();
  return 0;
}

// ####################################################################################################
// *** Core Function ***
int branching::systematicsTau(){

  TString doWhat = "MassModel";
  setBestCut();
  
  // Group Fits to LL and DD sample together to prevent having to remake the data all the time

  // ***** Long Long ***** //
  ///////////////////////////
  
  // *** Prepare Data ***
  fillDataset(m_bestCut_LL);
  
  char LL_netcut[30];
  makeCut(m_bestCut_LL,LL_netcut,m_LL);

  // *** Default ***
  double lifetime_LL_Default[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_Default,"Default");
  
  double lifetime_LL_Triple50[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_TripleMC[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_ResGauss[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_ResGaussWide[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_TanOffset[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_Tan[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_Exp[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_OneExp[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_HFAGPlus[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_HFAGMin[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_LHCb[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_LHCbPlus[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_LHCbMin[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_GaussCB[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_CB[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_DoubleGauss[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_FitTails[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_Poly[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_Uni[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_MassDiffPlus[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_MassDiffMin[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_MassDiffFit[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_MCfit[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_MCfitPlus[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_MCfitMin[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_MCfree[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_FitRange14[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_FitRange12[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_FitRange10[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_FitRange8[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_LL_FitRange6[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  
  if(doWhat=="Res" || doWhat=="All"){
    // *** Res Triple50 ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_Triple50,"Triple50");

    // *** Res TripleMC ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_TripleMC,"TripleMC");
  
    // *** Res ResGauss ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_ResGauss,"ResGauss");
  
    // *** Res ResGaussWide ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_ResGaussWide,"ResGaussWide");
  }
  
  if(doWhat=="Acc" || doWhat=="All"){
    // *** Acc TanOffset ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_TanOffset,"TanOffset");
    
    // *** Acc Tan ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_Tan,"Tan");

    // *** Acc Exp ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_Exp,"Exp");
  }
  
  if(doWhat=="Bkg" || doWhat=="All"){
    // *** Bkg OneExp ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_OneExp,"OneExp");
  }
  
  if(doWhat=="BdLifetime" || doWhat=="All"){
    // *** Bd Lifetime HFAGPlus ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_HFAGPlus,"HFAGPlus");
    
    // *** Bd Lifetime HFAGMin ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_HFAGMin,"HFAGMin");
    
    // *** Bd Lifetime LHCb ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_LHCb,"LHCb");
    
    // *** Bd Lifetime LHCbPlus ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_LHCbPlus,"LHCbPlus");
    
    // *** Bd Lifetime LHCbMin ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_LHCbMin,"LHCbMin");
  }
  
  if(doWhat=="MassModel" || doWhat=="All"){
    // *** Mass Model GaussCB ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_GaussCB,"GaussCB");
    
    // *** Mass Model CB ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_CB,"CB");
    
    // *** Mass Model DoubleGauss ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_DoubleGauss,"DoubleGauss");
    
    // *** Mass Model FitTails ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_FitTails,"FitTails");
    
    // *** Mass Model Poly ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_Poly,"Poly");
      
    // *** Mass Model Uni ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_Uni,"Uni");
    
    // *** Mass Model MassDiffPlus ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_MassDiffPlus,"MassDiffPlus");
    
    // *** Mass Model MassDiffMin ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_MassDiffMin,"MassDiffMin");
    
    // *** Mass Model MassDiffFit ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_MassDiffFit,"MassDiffFit");
    
    // *** Mass Model MCfit ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_MCfit,"MCfit");
    
    // *** Mass Model MCfitPlus ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_MCfitPlus,"MCfitPlus");
    
    // *** Mass Model MCfitMin ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_MCfitMin,"MCfitMin");
    
    // *** Mass Model MCfree ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_MCfree,"MCfree"); 
  }
  
  if(doWhat=="FitRange" || doWhat=="All"){
    // *** Fit Range 14 ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_FitRange14,"FitRange14");

    // *** Fit Range 12 ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_FitRange12,"FitRange12");
    
    // *** Fit Range 10 ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_FitRange10,"FitRange10");
    
    // *** Fit Range 8 ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_FitRange8,"FitRange8");
    
    // *** Fit Range 6 ***
    doLifetimeFit(m_bestCut_LL,LL_netcut,lifetime_LL_FitRange6,"FitRange6");
  }

 
  
  // ***** Down Down ***** //
  ///////////////////////////
  
  // *** Prepare Data ***
  fillDataset(m_bestCut_DD);
  
  char DD_netcut[30];
  makeCut(m_bestCut_DD,DD_netcut,m_DD);

  // *** Default ***
  double lifetime_DD_Default[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_Default,"Default");
  
  double lifetime_DD_Triple50[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_TripleMC[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_ResGauss[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_ResGaussWide[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_TanOffset[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_Tan[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_Exp[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_OneExp[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_TwoExp[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_HFAGPlus[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_HFAGMin[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_LHCb[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_LHCbPlus[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_LHCbMin[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_GaussCB[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_CB[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_DoubleGauss[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_FitTails[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_Poly[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_Uni[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_MassDiffPlus[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_MassDiffMin[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_MassDiffFit[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_MCfit[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_MCfitPlus[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_MCfitMin[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_MCfree[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_FitRange14[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_FitRange12[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_FitRange10[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_FitRange8[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double lifetime_DD_FitRange6[] = {-999,-999,-999,-999,-999,-999,-999,-999};

  if(doWhat=="Res" || doWhat=="All"){
    // *** Res Triple50 ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_Triple50,"Triple50");

    // *** Res TripleMC ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_TripleMC,"TripleMC");
  
    // *** Res ResGauss ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_ResGauss,"ResGauss");
  
    // *** Res ResGaussWide ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_ResGaussWide,"ResGaussWide");
  }
  
  if(doWhat=="Acc" || doWhat=="All"){
    // *** Acc TanOffset ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_TanOffset,"TanOffset");
    
    // *** Acc Tan ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_Tan,"Tan");

    // *** Acc Exp ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_Exp,"Exp");
  }
  
  if(doWhat=="Bkg" || doWhat=="All"){
    // *** Bkg OneExp ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_OneExp,"OneExp");
    
    // *** Bkg TwoExp ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_TwoExp,"TwoExp");
  }
  
  if(doWhat=="BdLifetime" || doWhat=="All"){
    // *** Bd Lifetime HFAGPlus ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_HFAGPlus,"HFAGPlus");
    
    // *** Bd Lifetime HFAGMin ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_HFAGMin,"HFAGMin");
    
    // *** Bd Lifetime LHCb ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_LHCb,"LHCb");
    
    // *** Bd Lifetime LHCbPlus ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_LHCbPlus,"LHCbPlus");
    
    // *** Bd Lifetime LHCbMin ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_LHCbMin,"LHCbMin");
  }
  
  if(doWhat=="MassModel" || doWhat=="All"){
    // *** Mass Model GaussCB ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_GaussCB,"GaussCB");
    
    // *** Mass Model CB ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_CB,"CB");
    
    // *** Mass Model DoubleGauss ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_DoubleGauss,"DoubleGauss");
    
    // *** Mass Model FitTails ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_FitTails,"FitTails");
    
    // *** Mass Model Poly ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_Poly,"Poly");
    
    // *** Mass Model Uni ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_Uni,"Uni");
    
    // *** Mass Model MassDiffPlus ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_MassDiffPlus,"MassDiffPlus");
    
    // *** Mass Model MassDiffMin ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_MassDiffMin,"MassDiffMin");
    
    // *** Mass Model MassDiffFit ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_MassDiffFit,"MassDiffFit");
    
    // *** Mass Model MCfit ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_MCfit,"MCfit");
    
    // *** Mass Model MCfitPlus ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_MCfitPlus,"MCfitPlus");
    
    // *** Mass Model MCfitMin ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_MCfitMin,"MCfitMin");
    
    // *** Mass Model MCfree ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_MCfree,"MCfree");  
  }
  
  if(doWhat=="FitRange" || doWhat=="All"){
    // *** Fit Range 14 ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_FitRange14,"FitRange14");

    // *** Fit Range 12 ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_FitRange12,"FitRange12");
    
    // *** Fit Range 10 ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_FitRange10,"FitRange10");
    
    // *** Fit Range 8 ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_FitRange8,"FitRange8");
    
    // *** Fit Range 6 ***
    doLifetimeFit(m_bestCut_DD,DD_netcut,lifetime_DD_FitRange6,"FitRange6");
  }
  
  
  
  // ***** Average ***** //
  /////////////////////////
  
  double lifetime_Av_Default[] = {-999,-999};
  PDGAverage(lifetime_LL_Default,lifetime_DD_Default,lifetime_Av_Default);
  double lifetime_Av_Triple50[] = {-999,-999};
  PDGAverage(lifetime_LL_Triple50,lifetime_DD_Triple50,lifetime_Av_Triple50);
  double lifetime_Av_TripleMC[] = {-999,-999};
  PDGAverage(lifetime_LL_TripleMC,lifetime_DD_TripleMC,lifetime_Av_TripleMC);
  double lifetime_Av_ResGauss[] = {-999,-999};
  PDGAverage(lifetime_LL_ResGauss,lifetime_DD_ResGauss,lifetime_Av_ResGauss);
  double lifetime_Av_ResGaussWide[] = {-999,-999};
  PDGAverage(lifetime_LL_ResGaussWide,lifetime_DD_ResGaussWide,lifetime_Av_ResGaussWide);
  double lifetime_Av_TanOffset[] = {-999,-999};
  PDGAverage(lifetime_LL_TanOffset,lifetime_DD_TanOffset,lifetime_Av_TanOffset);
  double lifetime_Av_Tan[] = {-999,-999};
  PDGAverage(lifetime_LL_Tan,lifetime_DD_Tan,lifetime_Av_Tan);
  double lifetime_Av_Exp[] = {-999,-999};
  PDGAverage(lifetime_LL_Exp,lifetime_DD_Exp,lifetime_Av_Exp);
  double lifetime_Av_OneExpLL[] = {-999,-999};
  PDGAverage(lifetime_LL_OneExp,lifetime_DD_Default,lifetime_Av_OneExpLL);
  double lifetime_Av_OneExpDD[] = {-999,-999};
  PDGAverage(lifetime_LL_Default,lifetime_DD_OneExp,lifetime_Av_OneExpDD);
  double lifetime_Av_OneExpAll[] = {-999,-999};
  PDGAverage(lifetime_LL_OneExp,lifetime_DD_OneExp,lifetime_Av_OneExpAll);
  double lifetime_Av_TwoExpDD[] = {-999,-999};
  PDGAverage(lifetime_LL_Default,lifetime_DD_TwoExp,lifetime_Av_TwoExpDD);
  double lifetime_Av_HFAGPlus[] = {-999,-999};
  PDGAverage(lifetime_LL_HFAGPlus,lifetime_DD_HFAGPlus,lifetime_Av_HFAGPlus);
  double lifetime_Av_HFAGMin[] = {-999,-999};
  PDGAverage(lifetime_LL_HFAGMin,lifetime_DD_HFAGMin,lifetime_Av_HFAGMin);
  double lifetime_Av_LHCb[] = {-999,-999};
  PDGAverage(lifetime_LL_LHCb,lifetime_DD_LHCb,lifetime_Av_LHCb);
  double lifetime_Av_LHCbPlus[] = {-999,-999};
  PDGAverage(lifetime_LL_LHCbPlus,lifetime_DD_LHCbPlus,lifetime_Av_LHCbPlus);
  double lifetime_Av_LHCbMin[] = {-999,-999};
  PDGAverage(lifetime_LL_LHCbMin,lifetime_DD_LHCbMin,lifetime_Av_LHCbMin);
  double lifetime_Av_GaussCB[] = {-999,-999};
  PDGAverage(lifetime_LL_GaussCB,lifetime_DD_GaussCB,lifetime_Av_GaussCB);
  double lifetime_Av_CB[] = {-999,-999};
  PDGAverage(lifetime_LL_CB,lifetime_DD_CB,lifetime_Av_CB);
  double lifetime_Av_DoubleGauss[] = {-999,-999};
  PDGAverage(lifetime_LL_DoubleGauss,lifetime_DD_DoubleGauss,lifetime_Av_DoubleGauss);
  double lifetime_Av_FitTails[] = {-999,-999};
  PDGAverage(lifetime_LL_FitTails,lifetime_DD_FitTails,lifetime_Av_FitTails);
  double lifetime_Av_Poly[] = {-999,-999};
  PDGAverage(lifetime_LL_Poly,lifetime_DD_Poly,lifetime_Av_Poly);
  double lifetime_Av_Uni[] = {-999,-999};
  PDGAverage(lifetime_LL_Uni,lifetime_DD_Uni,lifetime_Av_Uni);
  double lifetime_Av_MassDiffPlus[] = {-999,-999};
  PDGAverage(lifetime_LL_MassDiffPlus,lifetime_DD_MassDiffPlus,lifetime_Av_MassDiffPlus);
  double lifetime_Av_MassDiffMin[] = {-999,-999};
  PDGAverage(lifetime_LL_MassDiffMin,lifetime_DD_MassDiffMin,lifetime_Av_MassDiffMin);
  double lifetime_Av_MassDiffFit[] = {-999,-999};
  PDGAverage(lifetime_LL_MassDiffFit,lifetime_DD_MassDiffFit,lifetime_Av_MassDiffFit);
  double lifetime_Av_MCfit[] = {-999,-999};
  PDGAverage(lifetime_LL_MCfit,lifetime_DD_MCfit,lifetime_Av_MCfit);
  double lifetime_Av_MCfitPlus[] = {-999,-999};
  PDGAverage(lifetime_LL_MCfitPlus,lifetime_DD_MCfitPlus,lifetime_Av_MCfitPlus);
  double lifetime_Av_MCfitMin[] = {-999,-999};
  PDGAverage(lifetime_LL_MCfitMin,lifetime_DD_MCfitMin,lifetime_Av_MCfitMin);
  double lifetime_Av_MCfree[] = {-999,-999};
  PDGAverage(lifetime_LL_MCfree,lifetime_DD_MCfree,lifetime_Av_MCfree);
  double lifetime_Av_FitRange14[] = {-999,-999};
  PDGAverage(lifetime_LL_FitRange14,lifetime_DD_FitRange14,lifetime_Av_FitRange14);
  double lifetime_Av_FitRange12[] = {-999,-999};
  PDGAverage(lifetime_LL_FitRange12,lifetime_DD_FitRange12,lifetime_Av_FitRange12);
  double lifetime_Av_FitRange10[] = {-999,-999};
  PDGAverage(lifetime_LL_FitRange10,lifetime_DD_FitRange10,lifetime_Av_FitRange10);
  double lifetime_Av_FitRange8[] = {-999,-999};
  PDGAverage(lifetime_LL_FitRange8,lifetime_DD_FitRange8,lifetime_Av_FitRange8);
  double lifetime_Av_FitRange6[] = {-999,-999};
  PDGAverage(lifetime_LL_FitRange6,lifetime_DD_FitRange6,lifetime_Av_FitRange6);
  
  
  // ***** Results ***** //
  /////////////////////////

  std::cout << std::endl;
  std::cout << "++++++++++++++++++++ Default ++++++++++++++++++++" << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_Default[0] << " +/- " << lifetime_LL_Default[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_Default[0] << " +/- " << lifetime_DD_Default[1] << std::endl;
  std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_Default[0] << " +/- " << lifetime_Av_Default[1] << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
  
  if(doWhat=="Res" || doWhat=="All"){
    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ Triple50 ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_Triple50[0] << " +/- " << lifetime_LL_Triple50[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_Triple50[0] << " +/- " << lifetime_DD_Triple50[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_Triple50[0] << " +/- " << lifetime_Av_Triple50[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
  
    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ TripleMC ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_TripleMC[0] << " +/- " << lifetime_LL_TripleMC[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_TripleMC[0] << " +/- " << lifetime_DD_TripleMC[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_TripleMC[0] << " +/- " << lifetime_Av_TripleMC[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;

    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ ResGauss ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_ResGauss[0] << " +/- " << lifetime_LL_ResGauss[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_ResGauss[0] << " +/- " << lifetime_DD_ResGauss[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_ResGauss[0] << " +/- " << lifetime_Av_ResGauss[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
  
    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ ResGaussWide ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_ResGaussWide[0] << " +/- " << lifetime_LL_ResGaussWide[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_ResGaussWide[0] << " +/- " << lifetime_DD_ResGaussWide[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_ResGaussWide[0] << " +/- " << lifetime_Av_ResGaussWide[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
  }
  
  if(doWhat=="Acc" || doWhat=="All"){
    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ TanOffset ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_TanOffset[0] << " +/- " << lifetime_LL_TanOffset[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_TanOffset[0] << " +/- " << lifetime_DD_TanOffset[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_TanOffset[0] << " +/- " << lifetime_Av_TanOffset[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;

    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ Tan ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_Tan[0] << " +/- " << lifetime_LL_Tan[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_Tan[0] << " +/- " << lifetime_DD_Tan[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_Tan[0] << " +/- " << lifetime_Av_Tan[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;

    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ Exp ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_Exp[0] << " +/- " << lifetime_LL_Exp[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_Exp[0] << " +/- " << lifetime_DD_Exp[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_Exp[0] << " +/- " << lifetime_Av_Exp[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
  }
  
  if(doWhat=="Bkg" || doWhat=="All"){
    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ OneExpLL ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_OneExp[0] << " +/- " << lifetime_LL_OneExp[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_Default[0] << " +/- " << lifetime_DD_Default[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_OneExpLL[0] << " +/- " << lifetime_Av_OneExpLL[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
    
    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ OneExpDD ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_Default[0] << " +/- " << lifetime_LL_Default[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_OneExp[0] << " +/- " << lifetime_DD_OneExp[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_OneExpDD[0] << " +/- " << lifetime_Av_OneExpDD[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;

    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ OneExpAll ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_OneExp[0] << " +/- " << lifetime_LL_OneExp[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_OneExp[0] << " +/- " << lifetime_DD_OneExp[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_OneExpAll[0] << " +/- " << lifetime_Av_OneExpAll[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
    
    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ TwoExpDD ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_Default[0] << " +/- " << lifetime_LL_Default[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_TwoExp[0] << " +/- " << lifetime_DD_TwoExp[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_TwoExpDD[0] << " +/- " << lifetime_Av_TwoExpDD[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
  }
  
  if(doWhat=="BdLifetime" || doWhat=="All"){
    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ HFAGPlus ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_HFAGPlus[0] << " +/- " << lifetime_LL_HFAGPlus[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_HFAGPlus[0] << " +/- " << lifetime_DD_HFAGPlus[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_HFAGPlus[0] << " +/- " << lifetime_Av_HFAGPlus[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
    
    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ HFAGMin ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_HFAGMin[0] << " +/- " << lifetime_LL_HFAGMin[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_HFAGMin[0] << " +/- " << lifetime_DD_HFAGMin[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_HFAGMin[0] << " +/- " << lifetime_Av_HFAGMin[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
    
    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ LHCb ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_LHCb[0] << " +/- " << lifetime_LL_LHCb[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_LHCb[0] << " +/- " << lifetime_DD_LHCb[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_LHCb[0] << " +/- " << lifetime_Av_LHCb[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
    
    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ LHCbPlus ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_LHCbPlus[0] << " +/- " << lifetime_LL_LHCbPlus[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_LHCbPlus[0] << " +/- " << lifetime_DD_LHCbPlus[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_LHCbPlus[0] << " +/- " << lifetime_Av_LHCbPlus[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
    
    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ LHCbMin ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_LHCbMin[0] << " +/- " << lifetime_LL_LHCbMin[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_LHCbMin[0] << " +/- " << lifetime_DD_LHCbMin[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_LHCbMin[0] << " +/- " << lifetime_Av_LHCbMin[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
  }
  
  if(doWhat=="MassModel" || doWhat=="All"){
    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ GaussCB ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_GaussCB[0] << " +/- " << lifetime_LL_GaussCB[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_GaussCB[0] << " +/- " << lifetime_DD_GaussCB[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_GaussCB[0] << " +/- " << lifetime_Av_GaussCB[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;

    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ CB ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_CB[0] << " +/- " << lifetime_LL_CB[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_CB[0] << " +/- " << lifetime_DD_CB[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_CB[0] << " +/- " << lifetime_Av_CB[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
    
    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ DoubleGauss ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_DoubleGauss[0] << " +/- " << lifetime_LL_DoubleGauss[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_DoubleGauss[0] << " +/- " << lifetime_DD_DoubleGauss[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_DoubleGauss[0] << " +/- " << lifetime_Av_DoubleGauss[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
    
    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ FitTails ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_FitTails[0] << " +/- " << lifetime_LL_FitTails[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_FitTails[0] << " +/- " << lifetime_DD_FitTails[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_FitTails[0] << " +/- " << lifetime_Av_FitTails[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;

    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ Poly ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_Poly[0] << " +/- " << lifetime_LL_Poly[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_Poly[0] << " +/- " << lifetime_DD_Poly[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_Poly[0] << " +/- " << lifetime_Av_Poly[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;

    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ Uni ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_Uni[0] << " +/- " << lifetime_LL_Uni[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_Uni[0] << " +/- " << lifetime_DD_Uni[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_Uni[0] << " +/- " << lifetime_Av_Uni[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
    
    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ MassDiffPlus ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_MassDiffPlus[0] << " +/- " << lifetime_LL_MassDiffPlus[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_MassDiffPlus[0] << " +/- " << lifetime_DD_MassDiffPlus[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_MassDiffPlus[0] << " +/- " << lifetime_Av_MassDiffPlus[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;

    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ MassDiffMin ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_MassDiffMin[0] << " +/- " << lifetime_LL_MassDiffMin[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_MassDiffMin[0] << " +/- " << lifetime_DD_MassDiffMin[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_MassDiffMin[0] << " +/- " << lifetime_Av_MassDiffMin[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;

    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ MassDiffFit ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_MassDiffFit[0] << " +/- " << lifetime_LL_MassDiffFit[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_MassDiffFit[0] << " +/- " << lifetime_DD_MassDiffFit[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_MassDiffFit[0] << " +/- " << lifetime_Av_MassDiffFit[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
    
    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ MCfit ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_MCfit[0] << " +/- " << lifetime_LL_MCfit[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_MCfit[0] << " +/- " << lifetime_DD_MCfit[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_MCfit[0] << " +/- " << lifetime_Av_MCfit[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;

    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ MCfitPlus ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_MCfitPlus[0] << " +/- " << lifetime_LL_MCfitPlus[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_MCfitPlus[0] << " +/- " << lifetime_DD_MCfitPlus[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_MCfitPlus[0] << " +/- " << lifetime_Av_MCfitPlus[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;

    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ MCfitMin ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_MCfitMin[0] << " +/- " << lifetime_LL_MCfitMin[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_MCfitMin[0] << " +/- " << lifetime_DD_MCfitMin[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_MCfitMin[0] << " +/- " << lifetime_Av_MCfitMin[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
    
    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ MCfree ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_MCfree[0] << " +/- " << lifetime_LL_MCfree[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_MCfree[0] << " +/- " << lifetime_DD_MCfree[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_MCfree[0] << " +/- " << lifetime_Av_MCfree[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
  }
  
  if(doWhat=="FitRange" || doWhat=="All"){
    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ FitRange14 ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_FitRange14[0] << " +/- " << lifetime_LL_FitRange14[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_FitRange14[0] << " +/- " << lifetime_DD_FitRange14[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_FitRange14[0] << " +/- " << lifetime_Av_FitRange14[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;  
    
    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ FitRange12 ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_FitRange12[0] << " +/- " << lifetime_LL_FitRange12[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_FitRange12[0] << " +/- " << lifetime_DD_FitRange12[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_FitRange12[0] << " +/- " << lifetime_Av_FitRange12[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ; 
    
    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ FitRange10 ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_FitRange10[0] << " +/- " << lifetime_LL_FitRange10[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_FitRange10[0] << " +/- " << lifetime_DD_FitRange10[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_FitRange10[0] << " +/- " << lifetime_Av_FitRange10[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ; 
    
    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ FitRange8 ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_FitRange8[0] << " +/- " << lifetime_LL_FitRange8[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_FitRange8[0] << " +/- " << lifetime_DD_FitRange8[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_FitRange8[0] << " +/- " << lifetime_Av_FitRange8[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ; 
    
    std::cout << std::endl;
    std::cout << "++++++++++++++++++++ FitRange6 ++++++++++++++++++++" << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Long): " << lifetime_LL_FitRange6[0] << " +/- " << lifetime_LL_FitRange6[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Down): " << lifetime_DD_FitRange6[0] << " +/- " << lifetime_DD_FitRange6[1] << std::endl;
    std::cout << "  Bs->JpsiKs Eff Lifetime (Av. ): " << lifetime_Av_FitRange6[0] << " +/- " << lifetime_Av_FitRange6[1] << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ; 
  }
  
  // *** Finilise ***
  m_outfile->Close();
  return 0;
}

// ####################################################################################################
// *** Core Function ***
int branching::optimiseNet1(){
 
  // Individual LL and DD Samples
  double bestCut_LL = getNet1Cut(m_LL);
  double bestCut_DD = getNet1Cut(m_DD);
  m_outfile->Close();
  
  std::cout << "\n PROGRESS: Optimised cuts for NN 1 are " << bestCut_LL << "(LL) and " << bestCut_DD << "(DD) \n" << std::endl;
  
  return 0 ;
}

// ####################################################################################################
// *** Main ***
int main(int argc, char** argv){

  // *** Decode Arguments ***
  TString module, decay, dir, weightMethod, what;
  unsigned int NNtype, ttype;
  int out = decodeArgs(module, decay, NNtype, dir, weightMethod, ttype, what, argc, argv);
  // Extra argument
  TString doWhat = (argc > 7 ? TString(argv[7]) : "BR");
  std::cout << "Extra Arguments" << std::endl;
  std::cout << "  run option is: " << doWhat << std::endl;
  std::cout << "###################################################" << std::endl;
  // Error Analysis
  if (out!= 0) return out ;
  if(!(doWhat=="BR" || doWhat=="Tau" || doWhat=="All" || doWhat=="Syst" ||
       doWhat=="Punzi" || doWhat=="Mod" || doWhat=="SystTau" || doWhat=="OldNew")){
    std::cout << "ERROR: Unknown run option: " << doWhat << std::endl;
    return -255;
  }

  // *** Prepare Output ***
  TString brFile = "";
  TString tauFile = "";
  TString systFile = "";
  if(doWhat=="BR" || doWhat=="All"){
    brFile = makeFileName(module,decay,NNtype,weightMethod,what,ttype,dir);
    // Error Analysis
    if (""==brFile) {
      std::cout << "ERROR: Failed to generate file." << std::endl;
      return -255 ;
    }
  }
  else if(doWhat=="Tau"){
    tauFile = makeFileName(m_lifetime,decay,NNtype,weightMethod,what,ttype,dir);
    // Error Analysis
    if (""==tauFile) {
      std::cout << "ERROR: Failed to generate file." << std::endl;
      return -255 ;
    }
  }
  else if(doWhat=="Syst"){
    systFile = makeFileName(m_systematics,decay,NNtype,weightMethod,what,ttype,dir);
    // Error Analysis
    if (""==systFile) {
      std::cout << "ERROR: Failed to generate file." << std::endl;
      return -255 ;
    }
  }
  else if(doWhat=="Punzi"){
    systFile = makeFileName(m_punzi,decay,NNtype,weightMethod,what,ttype,dir);
    // Error Analysis
    if (""==systFile) {
      std::cout << "ERROR: Failed to generate file." << std::endl;
      return -255 ;
    }
  }
  else if(doWhat=="Mod" || doWhat=="OldNew"){
    systFile = makeFileName(m_mod,decay,NNtype,weightMethod,what,ttype,dir);
    // Error Analysis
    if (""==systFile) {
      std::cout << "ERROR: Failed to generate file." << std::endl;
      return -255 ;
    }
  }
  else if(doWhat=="SystTau"){
    systFile = makeFileName(m_systematicsTau,decay,NNtype,weightMethod,what,ttype,dir);
    // Error Analysis
    if (""==systFile) {
      std::cout << "ERROR: Failed to generate file." << std::endl;
      return -255 ;
    }
  }
  
  // *** Main Function ***
  make_canvas();
  
  if(NNtype==m_NNtype_one){
    branching b(module, decay, brFile, ttype, weightMethod, what, dir, NNtype);
    return b.optimiseNet1();
  }  
  else if(doWhat=="BR" || doWhat=="All"){
    branching b(module, decay, brFile, ttype, weightMethod, what, dir, NNtype);
    out = b.branchingFraction();
    if(out!=0 || doWhat=="BR") return out;
    else return b.effectifeLifetime();
  }
  else if(doWhat=="Tau"){
    branching b(module, decay, tauFile, ttype, weightMethod, what, dir, NNtype);
    return b.effectifeLifetime();
  }
  else if(doWhat=="Syst"){
    branching b(module, decay, systFile, ttype, weightMethod, what, dir, NNtype);
    return b.systematics();
  }
  else if(doWhat=="Punzi"){
    branching b(module, decay, systFile, ttype, weightMethod, what, dir, NNtype);
    return b.scanPunzi();
  }
  else if(doWhat=="Mod"){
    branching b(module, decay, systFile, ttype, weightMethod, what, dir, NNtype);
    return b.splitEventNumber();
  }
  else if(doWhat=="SystTau"){
    branching b(module, decay, systFile, ttype, weightMethod, what, dir, NNtype);
    return b.systematicsTau();
  }
  else if(doWhat=="OldNew"){
    branching b(module, decay, systFile, ttype, weightMethod, what, dir, NNtype);
    return b.splitOldNewData();
  }
}
