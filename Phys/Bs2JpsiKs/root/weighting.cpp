// ####################################################################################################
// Phys/Bs2JpsiKs Package
// Apply Selection Cuts && Calculate sWeights
// Authors: Patrick Koppenburg & Kristof De Bruyn
// ####################################################################################################

// ####################################################################################################
// *** Load Useful Classes *** 
// General C++
#include <iostream>
#include <map>
#include <vector>

// ROOT
#include "TBranch.h" 
#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"
#include "TObject.h"
#include "TTree.h"

// RooStats
#include "RooStats/SPlot.h"

// Bs2JpsiKs Package
#include "IB2JpsiX.h"
#include "JpsiKsPdf.h"
#include "MultipleCandidates.h"
#include "TupleLoader.h"

using namespace RooFit;

// ####################################################################################################
// *** Declarations ***
void make_canvas();
static const bool m_fitKstar = false ;
static const TString m_tag = "" ;

class weighting {
public :
  weighting(const TString module, const TString decay, const TString plotfilename,
	  TString weightMethod, TString what, TString dir, unsigned int NNtype);
  ~weighting(){};
  int run(double netCut_LL, double netCut_DD, bool);
 
private:
  // Declarations
  double pDist(double px1, double py1, double pz1, double px2, double py2, double pz2, TH1* TA=0);
  int fillDataSet(double netCut_LL, double netCut_DD);
  void fillOneEntry(unsigned int pv,RooRealVar* keep, RooRealVar* weight);
  int fit(unsigned int tracktype,bool);
  int writeTree(unsigned int tracktype);
  
  // General Settings
  static const bool m_debug = false;
  TString m_runFlag;

  // Members
  TString m_weightMethod ;
  TString m_what ;
  unsigned int m_NNtype;
  
  IB2JpsiX* m_ntuple ;
  TFile* m_outfile ;
  RooRealVar* m_mass ;
  RooRealVar* m_track ;
  Long64_t m_nGood, m_nGood_LL, m_nGood_DD;
  float fit_nBd, fit_nBd_LL, fit_nBd_DD ;
  float fit_nKstar, fit_nKstar_LL, fit_nKstar_DD ;
  float fit_nonPeaking, fit_nonPeaking_LL, fit_nonPeaking_DD ;
  RooDataSet* m_data ; 
  MultipleCandidates* m_eventMap ;
  RooStats::SPlot* m_sData ;
  RooStats::SPlot* m_sData_LL ;
  RooStats::SPlot* m_sData_DD ;
};
  
// ####################################################################################################
// *** Weighting constructor ***
weighting::weighting(const TString module, const TString decay, const TString plotfilename,
	  TString weightMethod, TString what, TString dir, unsigned int NNtype){

  // *** General Settings *** 
  m_runFlag = "All";
  m_weightMethod = weightMethod ;
  m_what = what ;
  m_NNtype = NNtype ;
  
  // *** Load NTuple ***
  m_ntuple = loadTuple(module, decay, dir, m_what, m_NNtype, m_weightMethod, m_ANY);
  if (!m_ntuple){
    std::cout << "WARNING: Ntuple could not be loaded" << std::endl;
    return ;
  }
  
  // *** Set Output ***
  m_outfile = new TFile( plotfilename, "RECREATE" );
  m_outfile->cd();
  
  // *** Initialise ***
  m_mass = new RooRealVar("mass","B mass",m_ntuple->sideband_low_min(),m_ntuple->sideband_high_max(),"MeV/c^{2}");
  m_track = new RooRealVar("track","track type",3.,5.);
  m_nGood = 0; m_nGood_LL = 0; m_nGood_DD = 0;
  fit_nBd = 0; fit_nBd_LL = 0; fit_nBd_DD = 0;
  fit_nKstar = 0; fit_nKstar_LL = 0; fit_nKstar_DD = 0;
  fit_nonPeaking = 0; fit_nonPeaking_LL = 0; fit_nonPeaking_DD = 0;
  m_data =  0;
  m_eventMap = 0;   
  m_sData = 0; m_sData_LL = 0; m_sData_DD = 0;
}

// ####################################################################################################
// *** Calculate angle between 2 Tracks ***
// Note: So far this is not used
double weighting::pDist(double px1, double py1, double pz1, double px2, double py2, double pz2, TH1* TA){
  // Calculate dot-product
  double p1 = sqrt(px1*px1+py1*py1+pz1*pz1);
  double p2 = sqrt(px2*px2+py2*py2+pz2*pz2);
  double dot =    (px1*px2+py1*py2+pz1*pz2)/(p1*p2); // = Cos(theta)
  
  // *** Error Analysis ***
  if ( dot > 1) {
    std::cout << "WARNING: Cosine bigger than 1" << std::endl;
    std::cout << "Input: p1 = (" << px1 << "," <<  py1 << "," <<  pz1 << ") and p2 = (" 
          << px2 << "," <<  py2 << "," <<  pz2 << ") => Giving cos(theta)= " << dot << std::endl ; 
  }
  // Calculate angle
  double theta = (dot<1 ? acos(dot) : 0) ;
  
  // Fill Histogram
  if (TA) TA->Fill(theta);
  
  return theta ;
}

// ####################################################################################################
void weighting::fillOneEntry(unsigned int pv,RooRealVar* keep, RooRealVar* weight){
  if (m_debug) std::cout << "Filling PV " << pv << " with mass " << m_ntuple->mass(pv) << " and weight:"
     <<  weight->getVal() << " - Compare to Best PV mass " <<  m_ntuple->mass(0) << std::endl ;
  m_mass->setVal(m_ntuple->mass(pv));
  m_track->setVal(m_ntuple->TrackType());
  m_data->add(RooArgSet(*m_mass, *m_track, *keep, *weight), weight->getVal());
}

// ####################################################################################################
int weighting::fillDataSet(double netCut_LL, double netCut_DD){
  
  std::cout << "\n PROGRESS: Filling DataSet for Fitting \n" << std::endl;
  
  // *** Multiple Candidates ***
  if (m_random==m_weightMethod || m_weighted==m_weightMethod){
    if(m_NNtype==m_NNtype_one) m_eventMap = createEventMap(m_ntuple, m_ANY, m_what, m_NNtype,-5.);
    else{
      std::cout << "WARNING: For convenience eventMap is only created for the minimum of the LL and DD cut." << std::endl;
      std::cout << "This is: Min(" << netCut_LL << "," << netCut_DD << ") = " << TMath::Min(netCut_LL,netCut_DD) << std::endl;
      m_eventMap = createEventMap(m_ntuple, m_ANY, m_what, m_NNtype,TMath::Min(netCut_LL,netCut_DD));
    }
  }
  else m_eventMap = new MultipleCandidates();
  
  // *** Initialise DataSet *** 
  RooRealVar* keep = new RooRealVar("keep","store what happened to the candidate",-10.,0.);
  RooRealVar* weight = new RooRealVar("weight","weight from multiple candidates",0.,1.); // access it using "data->weight()"
  m_data = new RooDataSet("fitdata","DataSet for Fitting", RooArgSet(*m_mass, *m_track, *keep, *weight ), WeightVar(*weight));
  
  // *** Fill DataSet ***
  const Long64_t nentries = m_ntuple->nEntries();
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
  Double_t tempWeight = 0;
  int addLL = 0;
  int addDD = 0;
  
  std::cout << " * Will loop over " << nentries << " Entries." << std::endl;

  // Because MultipleCandidates does not store an eventmap for each PV, it cannot remember which PV it has chosen.
  // Thus in order to keep the same PV used by the mass fit for by NeuroBayes we need to store it in m_data
  // The observable 'keep' makes it possible to easily eliminate these events for the mass fit later on
  double frac = printFrac(nentries);
  for ( Long64_t i = 0; i < nentries; ++i ){
    m_ntuple->GetChain()->GetEntry( i );
    if(m_ntuple->TrackType()==3){ addLL = 1; addDD = 0; }
    else{ addLL = 0; addDD = 1; }
    
    // Progress
    if( m_debug || 0==i%((int)(frac*nentries))) std::cout << " |-> " << i << " / " << nentries << " (" 
                                              << 100*i/nentries << "%)" << std::endl;
    
    // Check if one of the (B,PV) pairs passes the selection cuts
    unsigned int nPV = m_ntuple->primaries();
    std::list<unsigned int> goodPVs;
    for ( unsigned int pv = 0 ; pv!=nPV ; pv++){
      //      cout << "## " << m_NNtype << " " << m_what << " " << pv << " " << m_ANY << endl ;
      if((m_NNtype==m_NNtype_one && m_ntuple->applyAllCuts(m_NNtype,m_what,pv,m_ANY)) ||
         (m_NNtype==m_NNtype_two && m_ntuple->TrackType()==3 && m_ntuple->neuralnet(pv)>=netCut_LL) ||
         (m_NNtype==m_NNtype_two && m_ntuple->TrackType()==5 && m_ntuple->neuralnet(pv)>=netCut_DD)){
        nKept++; nKept_LL += addLL; nKept_DD += addDD; 
        goodPVs.push_back(pv);
      }
      else { nKilled++; nKilled_LL += addLL; nKilled_DD += addDD; }
    }
    // Selected events
    if(!goodPVs.empty() && goodPVs.size()>=1){
      tempWeight = m_eventMap->weightMultipleCandidates(i,m_ntuple,m_weightMethod);
      // Surviving Candidates
      if (tempWeight>0.){
        nGood++; nGood_LL += addLL; nGood_DD += addDD;
        // Stick to picking the ``best'' one for the training
        int bpv = goodPVs.front();//m_eventMap->pickBestPV(goodPVs);
        if(goodPVs.size()==1){
          nSinglePV++; nSinglePV_LL += addLL; nSinglePV_DD += addDD;
          if(0==goodPVs.front()){ nbestPV++ ; nbestPV_LL += addLL; nbestPV_DD += addDD; }
          else if(m_debug){
            std::cout << "Case of not picking up bestPV at event " << m_ntuple->getRunNumber() << " " 
                      << m_ntuple->getEventNumber() << std::endl ;
            //m_ntuple->printCandidate(0);
            //m_ntuple->printCandidate(bpv);
          }
        }
        else if(goodPVs.size()>1){
          nMultiPV++; nMultiPV_LL += addLL; nMultiPV_DD += addDD;
          nMultiPVtot += goodPVs.size(); nMultiPVtot_LL += addLL*goodPVs.size(); nMultiPVtot_DD += addDD*goodPVs.size();
          if(m_debug){
            m_ntuple->printCandidates(goodPVs) ;
            std::cout << "Selected PV " << bpv << std::endl;
          }
          if(0==goodPVs.front()){ nbestMultiPV++; nbestMultiPV_LL += addLL; nbestMultiPV_DD += addDD; }
        }
        for(unsigned int pv = 0 ; pv!=nPV ; pv++){
          // Keep random (B,PV) pair
          if(pv==bpv){
            keep->setVal(0);
            weight->setVal(tempWeight);
            fillOneEntry(bpv, keep, weight);
          }
          // Kill the other pairs
          else{
            bool found = false;
            for(std::list<unsigned int>::const_iterator j = goodPVs.begin(); j!=goodPVs.end() && found==false; j++) 
              found=(*j==pv);
            if(found){
              keep->setVal(ErrorCodes::KilledMuPV);
              weight->setVal(0);
              fillOneEntry(pv,keep,weight);
            }
            else{
              keep->setVal(ErrorCodes::FailsCuts);
              weight->setVal(0);
              fillOneEntry(pv,keep,weight);
            }
          }
        }
      }
      // Killed Multiple Candidates
      else{
        nMuCa++; nMuCa_LL += addLL; nMuCa_DD += addDD;
        if(goodPVs.size()==1){ nMuCaSinglePV++; nMuCaSinglePV_LL += addLL; nMuCaSinglePV_DD += addDD; }
        else if(goodPVs.size()>1){
          nMuCaMultiPV++; nMuCaMultiPV_LL += addLL; 
          nMuCaMultiPV_DD += addDD;
          nMuCaMultiPVtot += goodPVs.size(); 
          nMuCaMultiPVtot_LL += addLL*goodPVs.size(); 
          nMuCaMultiPVtot_DD += addDD*goodPVs.size();
        }
        for ( unsigned int pv = 0 ; pv!=nPV ; pv++){
          bool found = false;
          for(std::list<unsigned int>::const_iterator j = goodPVs.begin(); j!=goodPVs.end() && found==false; j++) found=(*j==pv);
          if(found){
            keep->setVal(ErrorCodes::KilledMuCa);
            weight->setVal(0);
            fillOneEntry(pv,keep,weight);
          }
          else{
            keep->setVal(ErrorCodes::FailsCuts);
            weight->setVal(0);
            fillOneEntry(pv,keep,weight);
          }
        }
      }
    }
    // Failed Cuts
    else{
      nFailed++; nFailed_LL += addLL; nFailed_DD += addDD;
      for ( unsigned int pv = 0 ; pv!=nPV ; pv++){
        keep->setVal(ErrorCodes::FailsCuts);
        weight->setVal(0);
        fillOneEntry(pv,keep,weight);
      }
    }
  }
  
  // *** Results ***
  std::cout << " * Filling Done! " << std::endl;
  
  m_nGood = nSinglePV + nMultiPV;
  m_nGood_LL = nSinglePV_LL + nMultiPV_LL;
  m_nGood_DD = nSinglePV_DD + nMultiPV_DD;
  
  Long64_t nentries_LL = nFailed_LL + nMuCa_LL + nGood_LL;
  Long64_t nentries_DD = nFailed_DD + nMuCa_DD + nGood_DD;
  Long64_t npairs = m_data->numEntries();
  Long64_t npairs_LL = nKilled_LL + nKept_LL;
  Long64_t npairs_DD = nKilled_DD + nKept_DD;
  

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

  if (m_debug) m_data->Print() ;
  
  // *** Error Analysis ***
  if(m_nGood==0){
    std::cout << "ERROR: No surviving events" << std::endl;
    return -55 ;
  }
  return 0 ;
  
}

// ####################################################################################################
// *** Fitting ***
int weighting::fit(unsigned int tracktype, bool isLambda){

  // ***** PART I: Mass Fit ***** //
  //////////////////////////////////

  std::cout << "\n PROGRESS: Fitting \n" << std::endl;
  
  // *** Data Set ***
  
  TString goodCut = "keep==0";
  if(tracktype==m_LL) goodCut = "keep==0 && track==3";
  else if(tracktype==m_DD) goodCut = "keep==0 && track==5";
  
  // Unfortunately SPlot does not work properly when the data sample is dominated by events with zero weight.
  // Therefore we have to give it only those with a non-zero weight
  RooDataSet *goodfitdata = (RooDataSet *)m_data->reduce(goodCut);
  Long64_t numGood = goodfitdata->numEntries();
  if(numGood!=m_nGood && numGood!=m_nGood_LL && numGood!=m_nGood_DD){
    std::cout << "WARNING: Mismatch in number of events to fit" << std::endl;
  }
  std::cout << "Running the fit on " << numGood << " candidates with total weight " 
       << goodfitdata->sumEntries() << std::endl ;
  
  // *** Create PDF ***
  TString setup = (isLambda?"Lambda":"Loose");
  JpsiKsPdf* jpsiKsExt = new JpsiKsPdf(m_tag,m_mass,false,m_fitKstar,0,setup,numGood); // no Bs, Double Crystal Ball
  if(tracktype==m_LL) jpsiKsExt->setModel("DoubleCB","ExpGauss","Poly"); // Change background to second order polynomial
  
  // *** Fit ***
  bool weightedFit = (m_weightMethod==m_weighted || m_weightMethod==m_downscaled);
  RooFitResult* fitresult = jpsiKsExt->fitToMass(goodfitdata,weightedFit);
  if(tracktype==m_ANY){
    fit_nBd = jpsiKsExt->nBd()->getVal();
    fit_nKstar = m_fitKstar ? jpsiKsExt->nKstar()->getVal() : 0;
    fit_nonPeaking = jpsiKsExt->nonPeaking()->getVal();
  }
  else if(tracktype==m_LL){
    fit_nBd_LL = jpsiKsExt->nBd()->getVal();
    fit_nKstar_LL = m_fitKstar ? jpsiKsExt->nKstar()->getVal() : 0;
    fit_nonPeaking_LL = jpsiKsExt->nonPeaking()->getVal();
  }
  else if(tracktype==m_DD){
    fit_nBd_DD = jpsiKsExt->nBd()->getVal();
    fit_nKstar_DD = m_fitKstar ? jpsiKsExt->nKstar()->getVal() : 0;
    fit_nonPeaking_DD = jpsiKsExt->nonPeaking()->getVal();
  }
  std::cout << "++++++++++++++++++++ results ++++++++++++++++++++" << std::endl ;
  std::cout << "     Fitted Extended PDF for " << (tracktype==3 ? "LL" : (tracktype==5 ? "DD" : "All")) << std::endl;
  std::cout << "     # Bd2JpsiKs = " << jpsiKsExt->nBd()->getVal() << " +/- " << jpsiKsExt->nBd()->getError() << std::endl;
  if (m_fitKstar){
    std::cout << "     # B2JpsiKstar = " << jpsiKsExt->nKstar()->getVal() 
      << " +/- " << jpsiKsExt->nKstar()->getError() << std::endl;
  }
  std::cout << "     # non Peaking = " << jpsiKsExt->nonPeaking()->getVal() 
    << " +/- " << jpsiKsExt->nonPeaking()->getError() << std::endl;
  float sumOfFit = jpsiKsExt->nBd()->getVal()+jpsiKsExt->nonPeaking()->getVal()+(m_fitKstar ? jpsiKsExt->nKstar()->getVal() : 0);
  std::cout << "     Sum = " << sumOfFit << " versus # Good: " << numGood << std::endl;
  fitresult->Print();  
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;  
  
  // *** Plot ***
  m_outfile->cd();
  TString tag = "";
  if(tracktype==m_LL) tag = "_LL";
  else if(tracktype==m_DD) tag = "_DD";
    
  TCanvas *massPlot_I = new TCanvas("massPlot_I","Canvas for MassPlot",900,800);
  jpsiKsExt->plotOn(massPlot_I,goodfitdata,weightedFit,1,1); // Plot with parameters -- weird
  massPlot_I->Write("MassPlot_Parameters"+tag);
  
  TCanvas *massPlot_II = new TCanvas("massPlot_II","Canvas for MassPlot",900,800);
  jpsiKsExt->plotOn(massPlot_II,goodfitdata,weightedFit,1,0); // Plot with legend
  jpsiKsExt->plotLegend(0.6,0.5,0.89,0.89);
  massPlot_II->Write("MassPlot_Legend"+tag);
  
  // *** Error Analysis ***
  if(sumOfFit<0.9*numGood){
    std::cout << "ERROR: Fit did not behave as expected " << sumOfFit << " << " << numGood << std::endl;
    return -1;
  }
  
  std::cout << " * Fitting Done! " << std::endl ;  
  
  // ***** PART II: sWeight ***** //
  //////////////////////////////////
  
  std::cout << "\n PROGRESS: sWeights \n" << std::endl;  
  
  // *** sWeight Magic ***
  if(tracktype==m_ANY) m_sData = new RooStats::SPlot("sData","sData", *goodfitdata, jpsiKsExt->massPdf(), 
                                                     jpsiKsExt->fracPdfList());
  else if(tracktype==m_LL){
    m_sData_LL = new RooStats::SPlot("sData_LL","sData", *goodfitdata, jpsiKsExt->massPdf(), jpsiKsExt->fracPdfList());
  }
  else if(tracktype==m_DD){
    m_sData_DD = new RooStats::SPlot("sData_DD","sData", *goodfitdata, jpsiKsExt->massPdf(), jpsiKsExt->fracPdfList());
  }
  
  // *** Error Analysis ***
  // would like to catch if sPlot went wrong ;
  
  return 0 ;
}

// ####################################################################################################
// *** Filling Weight Tree ***
int weighting::writeTree(unsigned int tracktype){
  std::cout << "\n PROGRESS: Creating Tree \n" << std::endl; 

  // *** Initialise ***
  TString tag = "_Combi";
  if(tracktype!=m_ANY) tag = "_Merged";
  
  unsigned int PVs = 0 ;
  Double_t sweightB[100], sweightKstar[100], sweightNonPeaking[100], sweight[100]; // sWeights
  Double_t myMass[100], origWeight[100], myWeight[100]; // Observables
  Int_t mytrack = 0;
  
  // Debug counters
  Double_t sumBd = 0;
  Double_t sumKstar = 0;
  Double_t sumNonPeaking = 0;

  // Histograms
  TH1F* histsweights = new TH1F("histsweights"+tag,"histsweights",100.,-0.5,1.5);
  
  // TTree
  TTree* outtree = new TTree("WeightTree"+tag,"Weight Tree");
  outtree->Branch("PVs",&PVs, "PVs/I");
  outtree->Branch("sweightB",&sweightB, "sweightB[PVs]/D");
  outtree->Branch("sweightKstar",&sweightKstar, "sweightKstar[PVs]/D");
  outtree->Branch("sweightNonPeaking",&sweightNonPeaking, "sweightNonPeaking[PVs]/D");
  outtree->Branch("sweight",&sweight, "sweight[PVs]/D");
  outtree->Branch("tracktype",&mytrack, "tracktype/I");
  outtree->Branch("mass",&myMass, "mass[PVs]/D");
  outtree->Branch("mcWeight", &origWeight, "mcWeight[PVs]/D");
  outtree->Branch("Weight", &myWeight, "Weight[PVs]/D");
  outtree->SetDirectory(m_outfile);

  // *** For accessing DataSets ***
  RooArgSet *fitVar = (RooArgSet *) m_data->get();
  RooRealVar *fit_mass = (RooRealVar *)fitVar->find("mass"); // limited to fit range
  RooRealVar *fit_keep = (RooRealVar *)fitVar->find("keep");
  
  
  // *** Fill Tree ***
  const Long64_t nentries = m_ntuple->nEntries();
  double frac = printFrac(nentries);
  Long64_t LLentry = 0; // Runs over the sWeighted dataset - LL
  Long64_t DDentry = 0; // Runs over the sWeighted dataset - DD
  Long64_t ANYentry = 0; // Runs over the sWeighted dataset - ANY
  Long64_t ifit = 0; // Runs over the flattened NTuple
  Int_t flag = 0;

  for(Long64_t i=0; i<nentries; i++){
    if(m_debug || 0==i%((int)(frac*nentries)))
      std::cout << " |-> " << i << " / " << nentries << " (" << 100*i/nentries << "%)" << std::endl; 
    m_ntuple->GetChain()->GetEntry(i);
    
    mytrack = m_ntuple->TrackType();
    PVs = m_ntuple->primaries();
    for(unsigned int pv = 0 ; pv<PVs ; ++pv){
      m_data->get(ifit);
      myMass[pv] = m_ntuple->mass(pv);  
          
      if (m_debug) std::cout << "Entry  " << i << " PV: " << pv << "/" << PVs << " MyMass " << myMass[pv] << std::endl ;
      
      // Error Analysis
      if (fabs(myMass[pv]-fit_mass->getVal())>0.1
          && myMass[pv]>=m_ntuple->sideband_low_min() && myMass[pv]<=m_ntuple->sideband_high_max()){
        std::cout << "Event " << i << " with PV " << pv << " has mismatch of mass " 
                  << myMass[pv] << " with flatted dataset entry " << ifit << " with mass " << fit_mass->getVal()
                  << " and is of type " << fit_keep->getVal() << std::endl ;
        return -8 ;
      }

      if ( !fit_keep ) {
        std::cout << "Error with fit_keep" << std::endl ;
        return -7 ;
      }
      // Events Failing Selection Cuts
      if(fit_keep->getVal()==ErrorCodes::FailsCuts){
        if (m_debug) cout << "  -> fails cuts" << endl ;
        sweightB[pv] = ErrorCodes::FailsCuts;
        sweightKstar[pv] = ErrorCodes::FailsCuts;
        sweightNonPeaking[pv] = ErrorCodes::FailsCuts;
        sweight[pv] = ErrorCodes::FailsCuts ;
        origWeight[pv] = ErrorCodes::FailsCuts ;
        myWeight[pv] =  ErrorCodes::FailsCuts;
      }
      // Killed Multiple Candidates
      else if(fit_keep->getVal()==ErrorCodes::KilledMuCa){
        if (m_debug) cout << "  -> killed as multiple candidate" << endl ;
        sweightB[pv] = (Double_t)ErrorCodes::KilledMuCa ;
        sweightKstar[pv] = (Double_t)ErrorCodes::KilledMuCa;
        sweightNonPeaking[pv] = (Double_t)ErrorCodes::KilledMuCa;
        sweight[pv] = (Double_t)ErrorCodes::KilledMuCa ;
        origWeight[pv] = (Double_t)ErrorCodes::KilledMuCa ;
        myWeight[pv] =  (Double_t)ErrorCodes::KilledMuCa;
      }
      // Killed Multiple PVs
      else if(fit_keep->getVal()==ErrorCodes::KilledMuPV){
        if (m_debug) cout << "  -> killed as multiple pv match" << endl ;
        sweightB[pv] = (Double_t)ErrorCodes::KilledMuPV ;
        sweightKstar[pv] = (Double_t)ErrorCodes::KilledMuPV;
        sweightNonPeaking[pv] = (Double_t)ErrorCodes::KilledMuPV;
        sweight[pv] = (Double_t)ErrorCodes::KilledMuPV ;
        origWeight[pv] = (Double_t)ErrorCodes::KilledMuPV ;
        myWeight[pv] =  (Double_t)ErrorCodes::KilledMuPV;
      }
      // Good Candidates
      else {
        if(isSigMC(m_what)){
          sweightB[pv] = 1;
          sweightKstar[pv] = 0;         
        }
        else if(tracktype!=m_ANY && m_ntuple->TrackType()==m_LL){
          sweightB[pv] = m_sData_LL->GetSWeight(LLentry,m_tag+"nBd");
          sweightKstar[pv] = (m_fitKstar ? m_sData->GetSWeight(LLentry,m_tag+"nKstar") : 0);
          LLentry++ ;
        }
        else if(tracktype!=m_ANY && m_ntuple->TrackType()==m_DD){
          sweightB[pv] = m_sData_DD->GetSWeight(DDentry,m_tag+"nBd");
          sweightKstar[pv] = (m_fitKstar ? m_sData->GetSWeight(DDentry,m_tag+"nKstar") : 0);
          DDentry++ ;
        }
        else if(tracktype==m_ANY){
          sweightB[pv] = m_sData->GetSWeight(ANYentry,m_tag+"nBd");
          sweightKstar[pv] = (m_fitKstar ? m_sData->GetSWeight(ANYentry,m_tag+"nKstar") : 0);
          ANYentry++ ;
        }
        
        sweightNonPeaking[pv] = 1-sweightB[pv]-sweightKstar[pv];
        sweight[pv] = sweightB[pv];
        origWeight[pv] = m_data->weight() ;
        myWeight[pv] = origWeight[pv]*sweightB[pv] ;
        
        // Error Analysis
        if (m_debug) std::cout << "M_Fitdata    " << i << " Pv: " << pv << " " << " Passes cuts as " << ifit 
          << " w= " <<  sweightB[pv] << std::endl ;
        
        sumBd += sweightB[pv] ;
        sumKstar += sweightKstar[pv] ;
        sumNonPeaking += sweightNonPeaking[pv] ;

        if(sumBd+sumKstar+sumNonPeaking<(LLentry+DDentry)-(5+5*flag)){
          flag++;
          std::cout << "WARNING: mismatch of " << (5+5*flag) << " events at entry " << LLentry << " + " << DDentry
		        << " with sum of weights " << sumBd+sumKstar+sumNonPeaking << std::endl;
        }
        if(sumBd+sumKstar+sumNonPeaking<ANYentry-(5+5*flag)){
          flag++;
          std::cout << "WARNING: mismatch of " << (5+5*flag) << " events at entry " << ANYentry
		        << " with sum of weights " << sumBd+sumKstar+sumNonPeaking << std::endl;
        }
          
        histsweights->Fill( sweightB[pv] );
      }
      ifit++;
    } // PV loop
    outtree->Fill() ;
  } // Ntuple loop
  
  std::cout << " * Filling Done!" << std::endl ;
  

  // *** Error Analysis Results *** 
  if(!isSigMC(m_what)){
    std::cout << "++++++++++++++++++++ results ++++++++++++++++++++" << std::endl ;
    std::cout << "     Filled sWeights" << std::endl;
    
    // Combined
    if(tracktype==m_ANY){
      std::cout << "     # Bd2JpsiKs: " << sumBd << " versus " << fit_nBd << " Fitted." << std::endl;
      if(m_fitKstar){
        std::cout << "     # B2JpsiKstar: " << sumKstar << " versus " << fit_nKstar << " Fitted" << std::endl;
      }
      std::cout << "     # non Peaking: " << sumNonPeaking << " versus " << fit_nonPeaking << " Fitted" << std::endl;
      std::cout << "     Sum: " << sumBd + sumKstar + sumNonPeaking << " versus " << ANYentry << std::endl;
      
      if(fabs(sumBd - fit_nBd)>5 || fabs(sumKstar - fit_nKstar)>5 || fabs(sumNonPeaking - fit_nonPeaking)>15){
        std::cout << "ERROR: Mismatch between number of fitted and filled good entries" << std::endl;
        return -6;
      }
    }
    
    // Merged
    else{
      std::cout << "     # Bd2JpsiKs: " << sumBd << " versus " << fit_nBd_LL << " + " << fit_nBd_DD << " Fitted." << std::endl;
      if(m_fitKstar){
        std::cout << "     # B2JpsiKstar: " << sumKstar << " versus "
          << fit_nKstar_LL << " + " << fit_nKstar_DD << " Fitted" << std::endl;
      }
      std::cout << "     # non Peaking: " << sumNonPeaking << " versus "
        << fit_nonPeaking_LL << " + " << fit_nonPeaking_DD << " Fitted" << std::endl;
      std::cout << "     Sum: " << sumBd + sumKstar + sumNonPeaking << " versus " << LLentry << " + " << DDentry << std::endl;
      
      if(fabs(sumBd - fit_nBd_LL - fit_nBd_DD)>5 || fabs(sumKstar - fit_nKstar_LL - fit_nKstar_DD)>5
        || fabs(sumNonPeaking - fit_nonPeaking_LL - fit_nonPeaking_DD)>15){
        std::cout << "ERROR: Mismatch between number of fitted and filled good entries" << std::endl;
        return -6;
      }
    }
    
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ; 
  }

  // *** Write to file ***
  std::cout << "\n PROGRESS: Writing File \n" << std::endl; 
  outtree->Write();
  histsweights->Write() ;

  return 0 ;
}  

// ####################################################################################################
// *** Weighting ***
int weighting::run(double netCut_LL, double netCut_DD,bool isLambda){ 

  // ***** PART I: Dataset ***** //
  /////////////////////////////////
  if (!m_ntuple) return -1;

  int err = fillDataSet(netCut_LL, netCut_DD);
  if (0!=err) return err ;


  // ***** PART II: Fitting ***** //
  //////////////////////////////////

  if(isSigMC(m_what)){
    std::cout << "\n PROGRESS: This is pure signal, no need for Fitting \n" << std::endl;
    err += writeTree(m_ANY); // Both Trees will be identical
  }
  else{
    if(m_runFlag=="All" || m_runFlag=="Any"){
      std::cout << "\n PROGRESS: Combined LL+DD sWeights \n" << std::endl;
      err += fit(m_ANY,isLambda);
      err += writeTree(m_ANY);
    }
    if(m_runFlag=="All" || m_runFlag=="Merged"){
      std::cout << "\n PROGRESS: LL sWeights \n" << std::endl;
      err += fit(m_LL,isLambda);
      std::cout << "\n PROGRESS: DD sWeights \n" << std::endl;
      err += fit(m_DD,isLambda);
      err += writeTree(m_LL);
    }
  }  

  m_outfile->Close();
  std::cout << "\n PROGRESS: Finished! \n" << std::endl;
  return err;
}

// ####################################################################################################
// *** Main ***
int main(int argc, char** argv){

  // *** Decode Arguments ***
  TString module, decay, dir, weightMethod, what;
  unsigned int NNtype, ttype;
  int out = decodeArgs(module, decay, NNtype, dir, weightMethod, ttype, what, argc, argv);
  // Extra argument
  double netCut_LL= (argc > 7 ? (double) atoi(argv[7])/100. : 0.);
  double netCut_DD= (argc > 8 ? (double) atoi(argv[8])/100. : 0.);
  std::cout << "Extra Arguments" << std::endl;
  std::cout << "  cut on NN 1: " << netCut_LL << "(LL) " << netCut_DD << "(DD)" << std::endl;
  std::cout << "###################################################" << std::endl;
  // Error Analysis
  if (out != 0) return out ;
  
  TString wFile = makeFileName(module,decay,NNtype,weightMethod,what,ttype,dir);
  // Error Analysis
  if (""==wFile) {
    std::cout << "ERROR: Failed to generate file." << std::endl;
    return -255 ;
  }

  // *** Main Function ***
  make_canvas();
  weighting w(module, decay, wFile, weightMethod, what, dir, NNtype);
  int e = w.run(netCut_LL,netCut_DD,(m_Lb2JpsiL==decay));
  if ( 0!=e ) help(argv[0]);
  return e;
}

// ####################################################################################################
