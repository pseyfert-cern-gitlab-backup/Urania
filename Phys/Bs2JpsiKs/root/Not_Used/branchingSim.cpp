// ####################################################################################################
// Phys/Bs2JpsiKs Package
// Scan for Optimal Neural Net Cut
// Authors: Patrick Koppenburg & Kristof De Bruyn
// ####################################################################################################

// ####################################################################################################
// *** Load Useful Classes ***

#include <iostream>
#include <string>

#include "RooCBShape.h"
#include "RooChebychev.h"
#include "RooCmdArg.h"
#include "RooGaussian.h"
#include "RooExponential.h"

#include "TCanvas.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TMath.h"
#include "TPaveText.h"

#include "IB2JpsiX.h"
#include "JpsiKsPdf.h"
#include "JpsiKsSimPdf.h"
#include "MultipleCandidates.h"
#include "TupleLoader.h"

// ####################################################################################################
// *** Declarations ***
// TCanvas* PullPlot(RooPlot* frame, RooRealVar* x, int logy=0);
void make_canvas();

class branchingSim {
public :
  branchingSim(const TString module, const TString decay, const TString plotfilename, unsigned int ttype,
	    TString weightMethod, TString what, TString dir, unsigned int NNtype);
  ~branchingSim(){};
  int branchingFraction();
    
private:
  char* makeCut(double cut, char* netcut, unsigned int LL=0, bool odd=false);
  void calcYield(double *All, double *Odd, double *Yield);
  void printBF(TString tag, double *Yield);
  double getBestCut(unsigned int LL);
  void doFullFit(double netVal_LL, double netVal_DD, bool doOdd, double *Results_LL, double *Results_DD, TString tag);
  void doBestFit(double cut_LL, double cut_DD, TString tag) ;
  int fillDataset(double cut=min_opt_net);

private:
  // General Settings
  static const bool m_debug = false;
  static const bool m_killPVs = true;
  static const bool m_fitKstar = true;
  
  // Neural Net Settings
  static const double min_opt_net = 0.00;
  static const double stepsize    = 0.01; // 0.01
  static const int    min_events = 0; 
  static const double punzi_alpha = 10; // I want 10 sigma to beat CDF
  static const bool   do_punzi = true;
  
  // Members
  unsigned int m_ttype ;
  TString m_weightMethod ;
  TString m_what ;
  unsigned int m_NNtype;
  
  IB2JpsiX* m_ntuple ;
  TFile* m_outfile ;
  RooRealVar* m_mass ;
  RooDataSet* m_data;
  MultipleCandidates* m_eventMap ;
  double previousNN;
};

  
// ####################################################################################################
// *** Branching Ratio Calculation ***
branchingSim::branchingSim(const TString module, const TString decay, const TString plotfilename, unsigned int ttype,
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
  m_data = 0 ;
  m_eventMap = 0;
  previousNN = -999;

}
// ####################################################################################################
// *** Small functions ***
char* branchingSim::makeCut(double cut, char* netcut, unsigned int LL, bool odd){
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
void branchingSim::calcYield(double *All, double *Odd, double *Yield){

  // *** Fit Results ***
  double nBd_Val = Odd[0]*parts_in_teaching;
  double nBd_Err = Odd[1]*parts_in_teaching;
  double nBs_Val = All[2];
  double nBs_Err = All[3];
  
  // *** Yield Ratio ***
  Yield[0] = nBs_Val/nBd_Val;
  Yield[1] = sqrt(pow(nBs_Err/nBd_Val,2)+pow(nBs_Val*nBd_Err/pow(nBd_Val,2),2));
}

// ####################################################################################################
void branchingSim::printBF(TString tag, double *Yield){
  
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
// *** Determine Best Neural Net Cut ***
// Evaluate performance of the network by taking slices in network output and fitting resulting mass distribution 
double branchingSim::getBestCut(unsigned int LL){
  
// ***** PART 0: Initialise ***** //
////////////////////////////////////

  char netcut[30];
  fillDataset() ;
  if (m_debug) cout << "getBestCut " << m_data << endl ;
  Int_t totEntries = m_data->numEntries();
  int lastentries = 2*totEntries+1 ;
  RooDataSet* dataset = 0;

  double bestFom = 0.;
  double bestCut = min_opt_net ;
  int npoints = -1 ;
  Double_t netVal = min_opt_net ;

  // *** Graphs for Signal, Background and Significance ***
  TGraphErrors* grS   = new TGraphErrors();
  grS->SetMarkerStyle(20);
  grS->SetMarkerSize(0.8);
  grS->SetLineColor(kGreen);
  grS->SetMarkerColor(kGreen);  

  TGraphErrors* grB   = new TGraphErrors();
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
  JpsiKsPdf* jpsiKsExt = new JpsiKsPdf("",m_mass,false,m_fitKstar,0,"Loose",totEntries); // Extended fit, no Bs, Double Crystal Ball
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
    fillDataset(netVal);
    dataset = (RooDataSet*)m_data->reduce(netcut);
     
    int nent = dataset->sumEntries(0,"Low,High") ;
    if ( nent<=min_events) {
      std::cout << " LOOP: Ran out of stats! Only " << nent << " events remaining" << std::endl ;
      break ; // out of stats
    }
    
    // *** Analyse ***
    if(nent<0.999*lastentries){
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
      double expBkg = parts_in_teaching*integral_Bkg->getVal()*jpsiKsExt->nonPeaking()->getVal();
      double expBkgErr = parts_in_teaching*integral_Bkg->getVal()*jpsiKsExt->nonPeaking()->getError();
      double Bs = parts_in_teaching*fsBr*jpsiKsExt->nBd()->getVal();
      double BsE = parts_in_teaching*fsBr*jpsiKsExt->nBd()->getError();

      // *** Calculate Significance ***
      // Punzi-style optimisation
      double fom, fomE, fomES, fomEB;
      if (do_punzi){
        fom = Bs/(punzi_alpha/2+sqrt(expBkg));
        fomES = BsE/(punzi_alpha/2+sqrt(expBkg)) ; //dP/dBs
        fomEB = -0.5*expBkgErr*fom*fom/(Bs*expBkg) ; //dP/dBkg
        fomE = sqrt(fomES*fomES+fomEB*fomEB) ;
      } else {
        fom = Bs/sqrt(Bs+expBkg);
        fomEB = -0.5*expBkgErr*(Bs/sqrt(Bs+expBkg))/(Bs+expBkg) ;
        fomES = BsE*(sqrt(Bs+expBkg)-(0.5*Bs/sqrt(Bs+expBkg)))/(Bs+expBkg) ;
        fomE = sqrt(fomES*fomES+fomEB*fomEB) ;
      }
      std::cout << "++++++++++++++++++++ results ++++++++++++++++++++" << std::endl ;
      std::cout << "             Neural Net Cut : " << netVal << std::endl;
      std::cout << "     # Events in Data Sample: " << nent << std::endl;
      std::cout << "     # Estimated Bs->JpsiKs : " << Bs  << " +/- " << BsE << std::endl;
      std::cout << "     # Estimated Background : " << expBkg << " +/- " << expBkgErr << std::endl;
      std::cout << "            Figure of Merit : " << fom << " +/- " << fomES << " (S) +/- " << fomEB << " (B)" << std::endl;
      std::cout << "            Figure of Merit : " << fom << " +/- " << fomE << std::endl;
      std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ; 
      
      // *** Check if this FOM is better ***
      if ( fom-fomE > bestFom ){  
        std::cout << "      This is the new best Figure of Merit!" << std::endl ;
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ; 
        bestFom = fom-fomE ;
        bestCut = netVal ;
      }


      // *** Update Graphs ***
      npoints++ ; // counter of real points
      grS->SetPoint(npoints,netVal,Bs);
      grS->SetPointError(npoints,0.5*stepsize,BsE);
      grB->SetPoint(npoints,netVal,expBkg);
      grB->SetPointError(npoints,0.5*stepsize,expBkgErr);
      if(TMath::IsNaN(fomE)==0){// Do not add infinities to the graph
        grSig->SetPoint(npoints,netVal,fom);
        grSig->SetPointError(npoints,0.5*stepsize,fomE);
      }
    }
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

  return bestCut ;
}

// ####################################################################################################
// *** Full Mass Fit ***
void branchingSim::doFullFit(double netVal_LL, double netVal_DD, bool doOdd, double *Results_LL, double *Results_DD, TString tag){

  std::cout << "\n PROGRESS: Performing Full Fit for NN>" << netVal_LL << " (LL) and NN>" << netVal_DD
            << " (DD) selection only Odd:" << doOdd << "\n" << std::endl ;

  // *** Prepare Data ***
  
  // LL
  char LL_netcut[30];
  if (!doOdd) makeCut(netVal_LL,LL_netcut,m_LL);
  else makeCut(netVal_LL,LL_netcut,m_LL,true);
  fillDataset(netVal_LL);
  RooDataSet *fitdata_LL = (RooDataSet *)m_data->reduce(LL_netcut);
  Int_t totEntries_LL = fitdata_LL->numEntries();
  
  // DD
  char DD_netcut[30];
  if (!doOdd) makeCut(netVal_DD,DD_netcut,m_DD);
  else makeCut(netVal_DD,DD_netcut,m_DD,true);
  fillDataset(netVal_DD);
  RooDataSet *fitdata_DD = (RooDataSet *)m_data->reduce(DD_netcut);
  Int_t totEntries_DD = fitdata_DD->numEntries();
  
  // *** Fit PDF ***
  Int_t totEntries = TMath::Max(totEntries_LL,totEntries_DD);
  JpsiKsSimPdf* jpsiKsExt = new JpsiKsSimPdf("",m_mass,true,m_fitKstar,totEntries); // Simultaneous fit with Kstar
  //if(m_fitKstar==true) jpsiKsExt->setConstant("Kstar"); // Freeze parameters from MC11a Incl Jpsi
  //jpsiKsExt->setModel("DoubleCB","Argus","Poly"); // Change background to second order polynomial
  RooFitResult* fitresult = (RooFitResult *)jpsiKsExt->fitToMass(fitdata_LL,fitdata_DD,false);

  // *** Results ***
  Results_LL[0] = jpsiKsExt->nBd(m_LL)->getVal();
  Results_LL[1] = jpsiKsExt->nBd(m_LL)->getError();
  Results_LL[2] = jpsiKsExt->nBs(m_LL)->getVal();
  Results_LL[3] = jpsiKsExt->nBs(m_LL)->getError();
  Results_LL[4] = jpsiKsExt->nKstar(m_LL)->getVal();
  Results_LL[5] = jpsiKsExt->nKstar(m_LL)->getError();
  Results_LL[6] = jpsiKsExt->nonPeaking(m_LL)->getVal();
  Results_LL[7] = jpsiKsExt->nonPeaking(m_LL)->getError();
  
  Results_DD[0] = jpsiKsExt->nBd(m_DD)->getVal();
  Results_DD[1] = jpsiKsExt->nBd(m_DD)->getError();
  Results_DD[2] = jpsiKsExt->nBs(m_DD)->getVal();
  Results_DD[3] = jpsiKsExt->nBs(m_DD)->getError();
  Results_DD[4] = jpsiKsExt->nKstar(m_DD)->getVal();
  Results_DD[5] = jpsiKsExt->nKstar(m_DD)->getError();
  Results_DD[6] = jpsiKsExt->nonPeaking(m_DD)->getVal();
  Results_DD[7] = jpsiKsExt->nonPeaking(m_DD)->getError();
  
  std::cout << "++++++++++++++++++++ results ++++++++++++++++++++" << std::endl;
  std::cout << "              Tag : " << tag << std::endl;
  std::cout << "   === Long Long Ks ===" << std::endl;
  std::cout << "   Neural Net Cut : " << netVal_LL << std::endl;
  std::cout << "     # Events     : " << totEntries_LL << std::endl;
  std::cout << "     # Bd->JpsiKs : " << Results_LL[0] << " +/- " << Results_LL[1] << std::endl;
  std::cout << "     # Bs->JpsiKs : " << Results_LL[2] << " +/- " << Results_LL[3] << std::endl;
  std::cout << "     # B->JpsiK*X : " << Results_LL[4] << " +/- " << Results_LL[5] << std::endl;
  std::cout << "     # Background : " << Results_LL[6] << " +/- " << Results_LL[7] << std::endl;
  std::cout << "   === Down Down Ks ===" << std::endl;
  std::cout << "   Neural Net Cut : " << netVal_DD << std::endl;
  std::cout << "     # Events     : " << totEntries_DD << std::endl;
  std::cout << "     # Bd->JpsiKs : " << Results_DD[0] << " +/- " << Results_DD[1] << std::endl;
  std::cout << "     # Bs->JpsiKs : " << Results_DD[2] << " +/- " << Results_DD[3] << std::endl;
  std::cout << "     # B->JpsiK*X : " << Results_DD[4] << " +/- " << Results_DD[5] << std::endl;
  std::cout << "     # Background : " << Results_DD[6] << " +/- " << Results_DD[7] << std::endl;
  fitresult->Print();
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
  
  // *** Plot ***
  TCanvas *massPlot_LL = new TCanvas("massPlot_LL","Canvas for MassPlot",900,800);
  jpsiKsExt->plotOn(massPlot_LL,fitdata_LL,m_LL,false,1,false); // Plot with legend
  jpsiKsExt->plotLegend(0.6,0.5,0.89,0.89);
  massPlot_LL->Write("Full Mass Fit "+tag+" "+LL_netcut);
  
  TCanvas *massPlot_DD = new TCanvas("massPlot_DD","Canvas for MassPlot",900,800);
  jpsiKsExt->plotOn(massPlot_DD,fitdata_DD,m_DD,false,1,false); // Plot with legend
  jpsiKsExt->plotLegend(0.6,0.5,0.89,0.89);
  massPlot_DD->Write("Full Mass Fit "+tag+" "+DD_netcut);
  
  if (!doOdd){
    TCanvas *pullPlot_LL = new TCanvas("pullPlot_LL","Canvas for MassPlot",900,800);
    jpsiKsExt->plotOn(pullPlot_LL,fitdata_LL,m_LL,false,1,true); // Plot with parameters
    pullPlot_LL->Write("Pull Mass Fit "+tag+" "+LL_netcut);
  
    TCanvas *pullPlot_DD = new TCanvas("pullPlot_DD","Canvas for MassPlot",900,800);
    jpsiKsExt->plotOn(pullPlot_DD,fitdata_DD,m_DD,false,1,true); // Plot with parameters
    pullPlot_DD->Write("Pull Mass Fit "+tag+" "+DD_netcut);
  }

}

// ####################################################################################################
// *** Best NN Cut Fits ***
void branchingSim::doBestFit(double cut_LL, double cut_DD, TString tag){
  
  // *** Simultaneous Fit ***
  // All -> Bs Yield
  double LL_all[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double DD_all[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  doFullFit(cut_LL, cut_DD, false, LL_all, DD_all, tag);
  
  // Odd only -> Bd Yield
  double LL_odd[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  double DD_odd[] = {-999,-999,-999,-999,-999,-999,-999,-999};
  doFullFit(cut_LL, cut_DD, true, LL_odd, DD_odd, tag);

  double LL_yield[] = {-999,-999};
  calcYield(LL_all, LL_odd, LL_yield);

  double DD_yield[] = {-999,-999};
  calcYield(DD_all, DD_odd, DD_yield);

  // *** PDG Average ***
  double wLL = pow(LL_yield[1],-2);
  double wDD = pow(DD_yield[1],-2);
  
  double av_yield[] = {-999,-999};
  av_yield[0] = (wLL*LL_yield[0] + wDD*DD_yield[0])/(wLL+wDD);
  av_yield[1] = 1/sqrt(wLL+wDD);

  // *** Branching Ratio ***
  printBF(tag+" Averaged", av_yield);

}

// ####################################################################################################
// *** Create Dataset ***
int branchingSim::fillDataset(double cut){
  
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
  if (m_data) delete m_data ;
  m_data = new RooDataSet("data","data",RooArgList(*m_mass, *net, *odd, *LL, *noBs));

  const Long64_t nentries = m_ntuple->nEntries();
  double frac = printFrac(nentries);
  Long64_t nKept = 0;
  Long64_t nKilled = 0;
  Long64_t nGood = 0;
  Long64_t nSinglePV = 0;
  Long64_t nMultiPV = 0;
  Long64_t nMultiPVtot = 0;
  Long64_t nMuCa = 0;
  Long64_t nMuCaSinglePV = 0;
  Long64_t nMuCaMultiPV = 0;
  Long64_t nMuCaMultiPVtot = 0;
  Long64_t nFailed = 0;
  
  // *** Fill DataSet ***
  std::cout << " * Will loop over " << nentries << " Entries with cut " << cut << std::endl;
  for (Long64_t i=0; i<nentries;i++) {
    m_ntuple->GetChain()->GetEntry(i);
    
    // Progress
    if(0==i%((int)(frac*nentries))) std::cout << " |-> " << i << " / " << nentries 
					      << " (" << 100*i/nentries << "%)" << std::endl;


    // Check if one of the (B,PV) pairs passes the selection cuts
    unsigned int nPV = m_ntuple->primaries();
    std::list<unsigned int> goodPVs;
    for ( unsigned int pv = 0 ; pv!=nPV ; pv++){
      if (m_ntuple->neuralnet(pv)>=cut || !m_killPVs){
        nKept++ ;
        goodPVs.push_back(pv);
      }
      else nKilled++ ;
    }
    // Selected events
    if(!goodPVs.empty() && goodPVs.size()>=1){
      // Surviving Candidates
      if (m_eventMap->pickMultipleCandidates(i,m_ntuple,m_weightMethod)){
        nGood++;
        if(goodPVs.size()==1)nSinglePV++;
        else if(goodPVs.size()>1){
          nMultiPV++;
          nMultiPVtot = nMultiPVtot + goodPVs.size();
        }
        int bpv = m_eventMap->pickBestPV(goodPVs);
        if(m_debug && goodPVs.size()>1){
          m_ntuple->printCandidates( goodPVs );
          std::cout << "Selected PV " << bpv << std::endl;
        }
        
        // Assign observables
        m_mass->setVal(m_ntuple->mass(bpv));
        net->setVal(m_ntuple->neuralnet(bpv));
        odd->setVal(m_ntuple->expertSample());
        LL->setVal(m_ntuple->TrackType());
        noBs->setVal(m_ntuple->noSigRegion(bpv));
      
        m_data->add(RooArgList(*m_mass, *net, *odd, *LL, *noBs));
      }
      // Killed Multiple Candidates
      else{
        nMuCa++;
        if(goodPVs.size()==1) nMuCaSinglePV++;
        else if(goodPVs.size()>1){
          nMuCaMultiPV++;
          nMuCaMultiPVtot = nMuCaMultiPVtot + goodPVs.size();
        }
      }
    }
    // Failed Cuts
    else nFailed++;
  }

  // *** Results ***
  std::cout << " * Filling Done! " << std::endl;
  
  Long64_t m_nGood = nSinglePV + nMultiPV;
  
  std::cout << "######################### Results #########################" << std::endl ;
  std::cout << "  Total number of candidates            : " << nentries << std::endl;
  std::cout << "  Number of candidates failing cuts     : " << nFailed << std::endl;
  std::cout << "  Number of killed Multiple candidates  : " << nMuCa << std::endl ;
  std::cout << "  Number of Good candidates             : " << nGood << std::endl;
  std::cout << "###########################################################" << std::endl ;
  std::cout << "  Total number of (B,PV) pairs          : " << nKilled+nKept << std::endl;
  std::cout << "  Number of killed (B,PV) pairs         : " << nKilled << std::endl ;
  std::cout << "  Number of surviving (B,PV) pairs      : " << nKept << std::endl ;
  std::cout << "  |-> Of which MuCa single (B,PV) pairs : " << nMuCaSinglePV << std::endl ;
  std::cout << "  |-> Of which MuCa multi (B,PV) pairs  : " << nMuCaMultiPV << " (" << nMuCaMultiPVtot << ")" << std::endl ;
  std::cout << "  |-> Of which Good single (B,PV) pairs : " << nSinglePV << std::endl ;
  std::cout << "  |-> Of which Good multi (B,PV) pairs  : " << nMultiPV << " (" << nMultiPVtot << ")" << std::endl ;
  std::cout << "  Total number of good (B,PV) pairs     : " << m_nGood << std::endl;
  std::cout << "###########################################################" << std::endl ;
  
  Int_t dentries = m_data->numEntries();
  std::cout << " * Dataset contains " << dentries << " Entries." << std::endl;
  return 0 ;
}

// ####################################################################################################
// *** Core Function ***
int branchingSim::branchingFraction(){
  std::cout << "\n PROGRESS: Creating Dataset \n" << std::endl;
  if(m_debug){ 
    return fillDataset(0.7);
  }
  
  // Individual LL and DD Samples
  //double bestCut_LL = getBestCut(m_LL);
  //double bestCut_DD = getBestCut(m_DD);
  //doBestFit(bestCut_LL, bestCut_DD, "LL+DD" );
  
  // Combined Sample
  double bestCut = 0.7;//getBestCut(m_ANY);
  doBestFit(bestCut, bestCut, "All" );
  
  m_outfile->Close();
  return 0 ;
}

// ####################################################################################################
// *** Main ***
int main(int argc, char** argv){

  // *** Decode Arguments ***
  TString module, decay, dir, weightMethod, what;
  unsigned int NNtype, ttype;
  int out = decodeArgs(module, decay, NNtype, dir, weightMethod, ttype, what, argc, argv);
  // Error Analysis
  if (out != 0) return out ;

  TString brFile = makeFileName(module,decay,NNtype,weightMethod,what,ttype);
  // Error Analysis
  if (""==brFile) {
    std::cout << "ERROR: Failed to generate file." << std::endl;
    return -255 ;
  }
  
  // *** Main Function ***
  make_canvas();
  branchingSim b(module, decay, brFile, ttype, weightMethod, what, dir, NNtype);
  return b.branchingFraction();
}
