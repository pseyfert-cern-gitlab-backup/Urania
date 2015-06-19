// #############################################################################
// Phys/Bs2JpsiKs Package
// Apply Selection Cuts && Calculate sWeights
// Authors: Patrick Koppenburg & Kristof De Bruyn
// #############################################################################

// #############################################################################
// *** Load Useful Classes *** 
// General C++
#include <iostream>
#include <list>

// ROOT
#include <TBranch.h> 
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>

// RooStats
#include <RooStats/SPlot.h>

// Bs2JpsiKs Package
#include "IB2JpsiX.h"
#include "JpsiKsPdf.h"
#include "MultipleCandidates.h"
#include "TupleLoader.h"

using namespace RooFit;

// #############################################################################
// *** Declarations ***
void make_canvas();
static const TString m_tag = "";

class weighting {
public :
  weighting(const TString module, const TString data, const TString step,
            const TString dir, const TString decay, const TString weightMethod,
            const bool doOptimisation);
  ~weighting() {};
  int run(const double netCut_LL, const double netCut_DD);
  int optimise(const double netCut_LL, const double netCut_DD);

private:
  // Declarations
  int fillDataSet(const double netCut_LL, const double netCut_DD);
  void fillOneEntry(const unsigned int pv, RooRealVar* weight);
  int fit(const unsigned int tracktype);
  int optfit(const unsigned int tracktype);
  int weightCode(const unsigned int pv);
  int writeTree();
  
  // General Settings
  bool m_fitBs;
  bool m_fitKstar;
  TString m_weightMethod;
  TString m_data;
  TString m_step;
  bool m_doOptimisation;

  // Data
  IB2JpsiX* m_ntuple;
  TFile* m_outfile;

  RooRealVar* m_mass;
  RooRealVar* m_track;
  RooRealVar* m_netval;
  RooDataSet* m_dataset;
  MultipleCandidates* m_eventMap;
  RooStats::SPlot* m_sData_LL;
  RooStats::SPlot* m_sData_DD;

  // Debug Counters
  Long64_t m_nGood_LL, m_nGood_DD;
  float fit_nBd_LL, fit_nBd_DD;
  float fit_nBs_LL, fit_nBs_DD;
  float fit_nKstar_LL, fit_nKstar_DD;
  float fit_nbkg_LL, fit_nbkg_DD;
};
  
// #############################################################################
// *** Constructor ***
weighting::weighting(const TString module, const TString data,
                     const TString step, const TString dir,
                     const TString decay, const TString weightMethod,
                     const bool doOptimisation) {

  // *** Initialise ***
  m_weightMethod = weightMethod;
  m_data = data;
  m_step = step;
  m_fitBs = true; //!(data==m_LHCb2012Prescaled);
  m_fitKstar = (m_step==m_NNKstar ? true : false);
  m_doOptimisation = doOptimisation;

  // *** Load NTuple ***
  m_ntuple = loadTuple(module, data, step, dir, decay, weightMethod);
  if (!m_ntuple) {
    std::cout << "ERROR: Ntuple could not be loaded" << std::endl;
    return;
  }

  // *** Set Output ***
  TString outFileName = "";
  if (m_doOptimisation) {
    TString prevstep = (step==m_NNSecond ? m_NNUnbiased :
                       (step==m_NNAnalyse ? m_NNSecond : m_NNKstar));
    outFileName = makeFileName(m_optimisation, data, prevstep, dir, decay,
                               weightMethod);
  } else {
    outFileName = makeFileName(module, data, step, dir, decay, weightMethod);    
  }
  // Error Handling
  if (outFileName=="") {
    std::cout << "ERROR: Failed to generate output file." << std::endl;
    return;
  }

  m_outfile = new TFile(outFileName, "RECREATE" );
  m_outfile->cd();

  // *** Data ***
  m_mass = new RooRealVar("mass", "B mass", m_ntuple->sideband_low_min(),
                          m_ntuple->sideband_high_max(m_data), "MeV/c^{2}");
  m_track = new RooRealVar("track", "track type", 3., 5.);
  m_netval = new RooRealVar("netval", "NN output", -10., 1.);
  m_dataset =  0;
  m_eventMap = 0;
  m_sData_LL = 0; m_sData_DD = 0;

  // Debug Counters
  m_nGood_LL = 0; m_nGood_DD = 0;
  fit_nBd_LL = 0; fit_nBd_DD = 0;
  fit_nKstar_LL = 0; fit_nKstar_DD = 0;
  fit_nbkg_LL = 0; fit_nbkg_DD = 0;
}

// #############################################################################
// *** Small Functions ***
void weighting::fillOneEntry(const unsigned int pv, RooRealVar* weight) {
  m_mass->setVal(m_ntuple->mass(pv));
  m_track->setVal(m_ntuple->TrackType());
  if (m_doOptimisation && m_step!=m_NNKstar) {
    m_netval->setVal(m_ntuple->neuralnet(pv));
  }
  else {
    m_netval->setVal(1.);
  }
  m_dataset->add(RooArgSet(*m_mass, *m_track, *weight, *m_netval));
}

int weighting::weightCode(const unsigned int pv) {
  int outval = -999;
  if (m_step==m_NNKstar) {
    outval = ErrorCodes::FailsCuts;
  } else if (m_ntuple->neuralnet(pv)<-3) {
    outval = m_ntuple->neuralnet(pv);
  } else {
    if (m_step==m_NNUnbiased) {
      outval = ErrorCodes::KstarNet;
    } else if (m_step==m_NNSecond) {
      outval = ErrorCodes::UnbiasNet;
    } else {
      std::cout << "ERROR: you should not get here" << std::endl;
      outval = ErrorCodes::FailsCuts;
    }
  }
  return outval;
}

// #############################################################################
// *** Filling ***
int weighting::fillDataSet(const double netCut_LL, const double netCut_DD) {
  
  std::cout << "\n PROGRESS: Filling DataSet for Fitting \n" << std::endl;
  
  // *** Multiple Candidates ***
  if (m_step==m_NNKstar) {
    m_eventMap = createEventMap(m_ntuple, m_data, -3., -3.);
  } else {
    m_eventMap = createEventMap(m_ntuple, m_data, netCut_LL, netCut_DD);
  }
  
  // *** Initialise DataSet *** 
  RooRealVar* weight = new RooRealVar("weight",
                                   "weight from multiple candidates", -10., 1.);
  m_dataset = new RooDataSet("fitdata", "DataSet for Fitting",
                             RooArgSet(*m_mass, *m_track, *weight, *m_netval));
  
  // *** Fill DataSet ***
  const Long64_t nentries = m_ntuple->nEntries();
  const Long64_t printMod = printFrac(nentries);
  // Counters
  Long64_t nbestMultiPV_LL = 0, nbestMultiPV_DD = 0;
  Long64_t nbestPV_LL = 0, nbestPV_DD = 0;
  Long64_t nFailed_LL = 0, nFailed_DD = 0;
  Long64_t nGood_LL = 0, nGood_DD = 0;
  Long64_t nKept_LL = 0, nKept_DD = 0;
  Long64_t nKilled_LL = 0, nKilled_DD = 0;
  Long64_t nMuCa_LL = 0, nMuCa_DD = 0;
  Long64_t nMuCaMultiPV_LL = 0, nMuCaMultiPV_DD = 0;
  Long64_t nMuCaMultiPVtot_LL = 0, nMuCaMultiPVtot_DD = 0;
  Long64_t nMuCaSinglePV_LL = 0, nMuCaSinglePV_DD = 0;
  Long64_t nMultiPV_LL = 0, nMultiPV_DD = 0;
  Long64_t nMultiPVtot_LL = 0, nMultiPVtot_DD = 0;
  Long64_t nSinglePV_LL = 0, nSinglePV_DD = 0;
  Double_t tempWeight = 0;
  int addLL = 0, addDD = 0;
  
  std::cout << "WEIGHT: Will loop over " << nentries << " entries." << std::endl;
  for (Long64_t i = 0; i < nentries; i++) {
    m_ntuple->GetChain()->GetEntry(i);

    // Progress
    if (i%printMod==0) {
      std::cout << " |-> " << i << " / " << nentries
                << " (" << 100*i/nentries << "%)" << std::endl;
    }

    if (m_ntuple->TrackType()==3) {
      addLL = 1; addDD = 0;
    } else {
      addLL = 0; addDD = 1;
    }
    
    // Check if one of the (B,PV) pairs passes the previous cuts
    unsigned int nPV = m_ntuple->primaries();
    std::list<unsigned int> goodPVs;
    for ( unsigned int pv = 0; pv!=nPV; pv++) {
      bool pass = false;
      if (m_step==m_NNKstar) {
        pass = (m_ntuple->applyAllCuts(m_data, pv) &&
          (m_ntuple->jpsiIPchi2(pv)<0 ||
           (addLL==1 && m_ntuple->jpsiIPchi2(pv)>ipcut_LL) ||
           (addLL==0 && m_ntuple->jpsiIPchi2(pv)>ipcut_DD)));
      } else {
        pass = 
           ((m_ntuple->TrackType()==3 && m_ntuple->neuralnet(pv)>=netCut_LL) ||
            (m_ntuple->TrackType()==5 && m_ntuple->neuralnet(pv)>=netCut_DD));
      }
      if (pass) {
        nKept_LL += addLL; nKept_DD += addDD; 
        goodPVs.push_back(pv);
      } else {
        nKilled_LL += addLL; nKilled_DD += addDD;
      }
    }

    // Events failing cuts: update counters
    if (goodPVs.empty()) {
      nFailed_LL += addLL; nFailed_DD += addDD;
      // Assign weight & fill dataset
      for (unsigned int pv = 0; pv!=nPV; pv++) {
        weight->setVal(weightCode(pv));
        fillOneEntry(pv, weight);
      }
    // Events surviving cuts
    } else {
      tempWeight = m_eventMap->weightMultipleCandidates(m_weightMethod,
                                                        m_ntuple, i);
      // Surviving Candidates
      if (tempWeight>0.) {
        nGood_LL += addLL; nGood_DD += addDD;
        // Take the ``best'' one for the training
        int bpv = goodPVs.front();
        // Surviving Candidate with single good PV
        if (goodPVs.size()==1) {
          nSinglePV_LL += addLL; nSinglePV_DD += addDD;
          if (0==goodPVs.front()) {
            nbestPV_LL += addLL; nbestPV_DD += addDD;
          }
        // Surviving Candidate with multiple good PVs
        } else if (goodPVs.size()>1) {
          nMultiPV_LL += addLL; nMultiPV_DD += addDD;
          nMultiPVtot_LL += addLL*goodPVs.size();
          nMultiPVtot_DD += addDD*goodPVs.size();
          if (0==goodPVs.front()) {
            nbestMultiPV_LL += addLL; nbestMultiPV_DD += addDD;
          }
        }
        // Assign weight & fill dataset
        for (unsigned int pv = 0; pv!=nPV; pv++) {
          // Keep one (B,PV) pair
          if (pv==bpv) {
            weight->setVal(tempWeight);
            fillOneEntry(bpv, weight);
          // Kill the other pairs
          } else {
            bool found = false;
            for (std::list<unsigned int>::const_iterator j = goodPVs.begin();
                 j!=goodPVs.end() && found==false; j++) found=(*j==pv);
            // True Multiple PVs in event
            if (found) {
              weight->setVal(ErrorCodes::KilledMuPV);
              fillOneEntry(pv, weight);
            // Other PVs in the event
            } else {
              weight->setVal(weightCode(pv));
              fillOneEntry(pv, weight);
            }
          }
        }
      // Eliminated Multiple Candidates: update counters
      } else {
        nMuCa_LL += addLL; nMuCa_DD += addDD;
        // Multiple Candidate with single good PV
        if (goodPVs.size()==1) {
          nMuCaSinglePV_LL += addLL; nMuCaSinglePV_DD += addDD;
        // Multiple Candidate with multiple good PVs
        } else if (goodPVs.size()>1) {
          nMuCaMultiPV_LL += addLL; nMuCaMultiPV_DD += addDD;
          nMuCaMultiPVtot_LL += addLL*goodPVs.size(); 
          nMuCaMultiPVtot_DD += addDD*goodPVs.size();
        } else {
          std::cout << "ERROR: you should not end up here." << std::endl;
        }
        // Assign weight & fill dataset
        for ( unsigned int pv = 0; pv!=nPV; pv++) {
          bool found = false;
          // Identify PVs that survive
          for (std::list<unsigned int>::const_iterator j = goodPVs.begin();
               j!=goodPVs.end() && found==false; j++) found=(*j==pv);
          // True Multiple Candidate
          if (found) {
            weight->setVal(ErrorCodes::KilledMuCa);
            fillOneEntry(pv, weight);
          // Other PVs in the event
          } else {
            weight->setVal(weightCode(pv));
            fillOneEntry(pv, weight);
          }
        } // End of pv-loop
      } // End of multiple candidates condition
    } // End of surviving events condition
  }

  // *** Results ***
  Long64_t nentries_LL = nFailed_LL + nMuCa_LL + nGood_LL;
  Long64_t nentries_DD = nFailed_DD + nMuCa_DD + nGood_DD;
  Long64_t npairs_LL = nKilled_LL + nKept_LL;
  Long64_t npairs_DD = nKilled_DD + nKept_DD;
  Long64_t npairs = npairs_LL + npairs_DD;

  Long64_t nbestMultiPV = nbestMultiPV_LL + nbestMultiPV_DD;
  Long64_t nbestPV = nbestPV_LL + nbestPV_DD;
  Long64_t nFailed = nFailed_LL + nFailed_DD;
  Long64_t nGood = nGood_LL + nGood_DD;
  Long64_t nKept = nKept_LL + nKept_DD;
  Long64_t nKilled = nKilled_LL + nKilled_DD;
  Long64_t nMuCa = nMuCa_LL + nMuCa_DD;
  Long64_t nMuCaMultiPV = nMuCaMultiPV_LL + nMuCaMultiPV_DD;
  Long64_t nMuCaMultiPVtot = nMuCaMultiPVtot_LL + nMuCaMultiPVtot_DD;
  Long64_t nMuCaSinglePV = nMuCaSinglePV_LL + nMuCaSinglePV_DD;
  Long64_t nMultiPV = nMultiPV_LL + nMultiPV_DD;
  Long64_t nMultiPVtot = nMultiPVtot_LL + nMultiPVtot_DD;
  Long64_t nSinglePV = nSinglePV_LL + nSinglePV_DD;

  m_nGood_LL = nGood_LL; m_nGood_DD = nGood_DD;

  std::cout << "########################################" << std::endl;
  std::cout << "  RESULTS" << std::endl;
  std::cout << "########################################" << std::endl;
  std::cout << "  Total number of candidates                    : "
            << nentries << " = " << nentries_LL << " (LL) + "
            << nentries_DD << " (DD)" << std::endl;
  std::cout << "  |-> Number of candidates failing cuts         : "
            << nFailed << " = " << nFailed_LL << " (LL) + "
            << nFailed_DD << " (DD)" << std::endl;
  std::cout << "  |-> Number of killed Multiple candidates      : "
            << nMuCa << " = " << nMuCa_LL << " (LL) + "
            << nMuCa_DD << " (DD)" << std::endl;
  std::cout << "  |-> Number of Good candidates                 : "
            << nGood << " = " << nGood_LL << " (LL) + "
            << nGood_DD << " (DD)" << std::endl;
  std::cout << "########################################" << std::endl;
  std::cout << "  Total number of (B,PV) pairs                  : "
            << npairs << " = " << npairs_LL << " (LL) + "
            << npairs_DD << " (DD)" << std::endl;
  std::cout << "  |-> Number of killed (B,PV) pairs             : "
            << nKilled << " = " << nKilled_LL << " (LL) + "
            << nKilled_DD << " (DD)" << std::endl;
  std::cout << "  |-> Number of surviving (B,PV) pairs          : "
            << nKept << " = " << nKept_LL << " (LL) + "
            << nKept_DD << " (DD)" << std::endl;
  std::cout << "      |-> Of which MuCa single (B,PV) pairs     : "
            << nMuCaSinglePV << " = " << nMuCaSinglePV_LL << " (LL) + "
            << nMuCaSinglePV_DD << " (DD)" << std::endl;
  std::cout << "      |-> Of which MuCa multi (B,PV) pairs      : "
            << nMuCaMultiPV << " (" << nMuCaMultiPVtot << ")" << " = "
            << nMuCaMultiPV_LL << " (" << nMuCaMultiPVtot_LL << ")" << " (LL) + "
            << nMuCaMultiPV_DD << " (" << nMuCaMultiPVtot_DD << ")" << " (DD)"
            << std::endl;
  std::cout << "      |-> Total number of good (B,PV) pairs     : "
            << nGood << " = " << nGood_LL << " (LL) + "
            << nGood_DD << " (DD)" << std::endl;
  std::cout << "          |-> Of which Good single (B,PV) pairs : "
            << nSinglePV << " = " << nSinglePV_LL << " (LL) + "
            << nSinglePV_DD << " (DD)" << std::endl;
  std::cout << "              |-> In which DaVinci got it right : "
            << nbestPV << " = " << nbestPV_LL << " (LL) + "
            << nbestPV_DD << " (DD)" << std::endl;
  std::cout << "              |-> In which DaVinci got it wrong : "
            << nSinglePV-nbestPV << " = " << nSinglePV_LL-nbestPV_LL << " (LL) + "
            << nSinglePV_DD-nbestPV_DD << " (DD)" << std::endl;
  std::cout << "          |-> Of which Good multi (B,PV) pairs  : "
            << nMultiPV << " (" << nMultiPVtot << ")" << " = "
            << nMultiPV_LL << " (" << nMultiPVtot_LL << ")" << " (LL) + "
            << nMultiPV_DD << " (" << nMultiPVtot_DD << ")" << " (DD)"
            << std::endl;
  std::cout << "              |-> In which DaVinci got it right : "
            << nbestMultiPV << " = " << nbestMultiPV_LL << " (LL) + "
            << nbestMultiPV_DD << " (DD)" << std::endl;
  std::cout << "              |-> In which DaVinci got it wrong : "
            << nMultiPV - nbestMultiPV << " = "
            << nMultiPV_LL-nbestMultiPV_LL << " (LL) + "
            << nMultiPV_DD-nbestMultiPV_DD << " (DD)" << std::endl;
  std::cout << "########################################" << std::endl;
  
  // *** Error Analysis ***
  if (nGood==0) {
    std::cout << "ERROR: No surviving events" << std::endl;
    return -1;
  }
  return 0;
}

// #############################################################################
// *** Fitting ***
int weighting::fit(const unsigned int tracktype) {

  // ***** PART I: Mass Fit ***** //
  //////////////////////////////////

  std::cout << "\n PROGRESS: Fitting \n" << std::endl;
  
  // *** Data Set ***
  TString goodCut = "";
  if (tracktype==m_LL) goodCut = "weight>=0 && track==3";
  else if (tracktype==m_DD) goodCut = "weight>=0 && track==5";

  RooDataSet *goodfitdata = (RooDataSet *)m_dataset->reduce(goodCut);
  if (m_weightMethod==m_weighted) {
    std::cout << "WARNING: Should still implement the transformation to"
              << " a weighted data set." << std::endl;
  }
  Long64_t numGood = goodfitdata->numEntries();
  std::cout << "Running the fit on " << numGood << " candidates, expected "
            << (tracktype==m_LL ? m_nGood_LL : m_nGood_DD) << std::endl;
  if (numGood!=m_nGood_LL && numGood!=m_nGood_DD) {
    std::cout << "ERROR: Mismatch in number of events to fit." << std::endl;
    return -1;
  }
  
  // *** Create PDF ***
  bool m_addKstar = (tracktype!=m_DD && m_fitKstar ? true : false);
  JpsiKsPdf* jpsiKsExt = new JpsiKsPdf(m_tag, m_mass, m_fitBs, m_addKstar,
    (tracktype==m_LL ? 3 : 5), m_step, numGood);
  if (m_data==m_LHCb2012Prescaled) {
    if (tracktype==m_LL) {
      jpsiKsExt->setConstant("Prescaled_LL");
    } else {
      jpsiKsExt->setConstant("Prescaled_DD");
    }
  }

  // *** Fit ***
  bool weightedFit = (m_weightMethod==m_weighted ||
                      m_weightMethod==m_downscaled);
  RooFitResult* fitresult = jpsiKsExt->fitToMass(goodfitdata, weightedFit);
  if (tracktype==m_LL) {
    fit_nBd_LL = jpsiKsExt->nBd()->getVal();
    fit_nBs_LL = (m_fitBs ? jpsiKsExt->nBs()->getVal() : 0);
    fit_nKstar_LL = (m_addKstar ? jpsiKsExt->nKstar()->getVal() : 0);
    fit_nbkg_LL = jpsiKsExt->nonPeaking()->getVal();
  } else if (tracktype==m_DD) {
    fit_nBd_DD = jpsiKsExt->nBd()->getVal();
    fit_nBs_DD = (m_fitBs ? jpsiKsExt->nBs()->getVal() : 0);
    fit_nKstar_DD = 0;
    fit_nbkg_DD = jpsiKsExt->nonPeaking()->getVal();
  }
  std::cout << "########################################" << std::endl;
  std::cout << "  RESULTS for " << (tracktype==3 ? "Long Ks" : "Downstream Ks")
            << std::endl;
  std::cout << "  # Bd2JpsiKs = " << jpsiKsExt->nBd()->getVal() << " +/- "
            << jpsiKsExt->nBd()->getError() << std::endl;
  if (m_fitBs) {
    std::cout << "  # Bs2JpsiKs = " << jpsiKsExt->nBs()->getVal() << " +/- "
              << jpsiKsExt->nBs()->getError() << std::endl;
  }
  if (m_addKstar) {
    std::cout << "  # B2JpsiKstar = " << jpsiKsExt->nKstar()->getVal() 
              << " +/- " << jpsiKsExt->nKstar()->getError() << std::endl;
  }
  std::cout << "  # Background = " << jpsiKsExt->nonPeaking()->getVal() 
            << " +/- " << jpsiKsExt->nonPeaking()->getError() << std::endl;
  float sumOfFit = jpsiKsExt->nBd()->getVal() +
                   (m_fitBs ? jpsiKsExt->nBs()->getVal() : 0) +
                   jpsiKsExt->nonPeaking()->getVal() +
                   (m_addKstar ? jpsiKsExt->nKstar()->getVal() : 0);
  std::cout << "  Sum = " << sumOfFit << " fitted versus " << numGood
            << " selected." << std::endl;
  std::cout << "########################################" << std::endl;
  fitresult->Print();  
  std::cout << "########################################" << std::endl;  

  // *** Plot ***
  m_outfile->cd();
  TString tag = (tracktype==m_LL ? "_LL" : "_DD");

  // Plot with parameters -- weird
  TCanvas *massPlot_Par = new TCanvas("massPlot_Par","Canvas",900,800);
  jpsiKsExt->plotOn(massPlot_Par, goodfitdata, weightedFit, 1, 1);
  massPlot_Par->Write("MassPlot_Parameters"+tag);

  // Plot with legend
  TCanvas *massPlot_Leg = new TCanvas("massPlot_Leg","Canvas",900,800);
  jpsiKsExt->plotOn(massPlot_Leg, goodfitdata, weightedFit, 1, 0);
  jpsiKsExt->plotLegend(0.6,0.5,0.89,0.89);
  massPlot_Leg->Write("MassPlot_Legend"+tag);

  // Plot with Legend & Pull
  TCanvas *massPlot_Pull = new TCanvas("massPlot_Pull","Canvas",900,800);
  jpsiKsExt->plotOn(massPlot_Pull, goodfitdata, weightedFit, 1, 2);
  jpsiKsExt->plotLegend(0.6,0.5,0.89,0.89);
  massPlot_Pull->Write("MassPlot_Pull"+tag);

  // Error Handling
  if (sumOfFit<0.9*numGood) {
    std::cout << "ERROR: Fit did not behave as expected " << sumOfFit
              << " << " << numGood << std::endl;
    return -1;
  }
  std::cout << "WEIGHT: Plotting Done! " << std::endl;  


  // ***** PART II: sWeight ***** //
  //////////////////////////////////

  std::cout << "\n PROGRESS: sWeights \n" << std::endl;  

  // *** sWeight Magic ***
  if (tracktype==m_LL) {
    m_sData_LL = new RooStats::SPlot("sData_LL","sData", *goodfitdata,
                 jpsiKsExt->massPdf(), jpsiKsExt->fracPdfList());
  } else if (tracktype==m_DD) {
    m_sData_DD = new RooStats::SPlot("sData_DD","sData", *goodfitdata,
                 jpsiKsExt->massPdf(), jpsiKsExt->fracPdfList());
  }
  return 0;
}

// #############################################################################
// *** Fitting ***
int weighting::optfit(const unsigned int tracktype) {

  // ***** PART I: Mass Fit ***** //
  //////////////////////////////////

  std::cout << "\n PROGRESS: Fitting \n" << std::endl;
  
  // *** Data Set ***
  TString goodCut = "";
  if (tracktype==m_LL) goodCut = "weight>=0 && track==3";
  else if (tracktype==m_DD) goodCut = "weight>=0 && track==5";

  RooDataSet *goodfitdata = (RooDataSet *)
                      m_dataset->reduce(RooArgSet(*m_mass, *m_netval), goodCut);
  if (m_weightMethod==m_weighted) {
    std::cout << "WARNING: Should still implement the transformation to"
              << " a weighted data set." << std::endl;
  }
  Long64_t numGood = goodfitdata->numEntries();
  std::cout << "Running the fit on " << numGood << " candidates." << std::endl;

  // *** Create PDF ***
  TString prevStep = (m_step==m_NNSecond ? m_NNUnbiased : m_NNKstar);
  JpsiKsPdf* jpsiKsExt = new JpsiKsPdf(m_tag, m_mass, m_fitBs, false,
    (tracktype==m_LL ? 3 : 5), prevStep, numGood);
  
  // *** Fit ***
  bool weightedFit = (m_weightMethod==m_weighted ||
                      m_weightMethod==m_downscaled);
  RooFitResult* fitresult = jpsiKsExt->fitToMass(goodfitdata, weightedFit);
  std::cout << "########################################" << std::endl;
  std::cout << "  RESULTS for " << (tracktype==3 ? "Long Ks" : "Downstream Ks")
            << std::endl;
  std::cout << "  # Bd2JpsiKs = " << jpsiKsExt->nBd()->getVal() << " +/- "
            << jpsiKsExt->nBd()->getError() << std::endl;
  if (m_fitBs) {
    std::cout << "  # Bs2JpsiKs = " << jpsiKsExt->nBs()->getVal() << " +/- "
              << jpsiKsExt->nBs()->getError() << std::endl;
  }
  std::cout << "  # Background = " << jpsiKsExt->nonPeaking()->getVal() 
            << " +/- " << jpsiKsExt->nonPeaking()->getError() << std::endl;
  std::cout << "########################################" << std::endl;
  fitresult->Print();  
  std::cout << "########################################" << std::endl;
  
  // Freeze parameters
  double looseBd_Val = jpsiKsExt->nBd()->getVal();
  double looseBd_Err = jpsiKsExt->nBd()->getError();
  double looseBkg_Val = jpsiKsExt->nonPeaking()->getVal();
  double looseBkg_Err = jpsiKsExt->nonPeaking()->getError();
  jpsiKsExt->setConstant("SigOnly");

  // *** Plot ***
  m_outfile->cd();
  TString tag = (tracktype==m_LL ? "_LL" : "_DD");

  // Plot with parameters -- weird
  TCanvas *massPlot_Par = new TCanvas("massPlot_Par","Canvas",900,800);
  jpsiKsExt->plotOn(massPlot_Par, goodfitdata, weightedFit, 1, 1);
  massPlot_Par->Write("MassPlot_Parameters"+tag);

  std::cout << "OPT: Plotting Done! " << std::endl;  

  // ***** PART II: Loop Fit ***** //
  ///////////////////////////////////

  // *** Initialise ***
  double netCut = -1.;
  int mytrack = tracktype;

  double nBd_Val = 0;
  double nBd_Err = 0;
  double nBs_Val = 0;
  double nBs_Err = 0;
  double nBkg_Val = 0;
  double nBkg_Err = 0;
  double cBkg_Val = 0;
  double cBkg_Err = 0;
  double Brej_Val = 0;
  double Brej_Err = 0;
  double Seff_Val = 0;
  double Seff_Err = 0;
  double ratio = 0.0116;
  double bkgWin = 6./34.;
  double SSB_Val = 0;
  double SSB_Err = 0;
  double bestSSB_Val = 0;
  double bestSSB_Err = 0;
  double bestSSBCut = -1.;
  double optSSB_Val = 0;
  double optSSB_Err = 0;
  double optSSBCut = -1.;
  bool foundSSB = false;
  int alpha = 10;
  double Punzi_Val = 0;
  double Punzi_Err = 0;
  double bestPunzi_Val = 0;
  double bestPunzi_Err = 0;
  double bestPunziCut = -1.;
  double optPunzi_Val = 0;
  double optPunzi_Err = 0;
  double optPunziCut = -1.;
  bool foundPunzi = false;
  
  // *** Tree ***
  TTree *outtree = (TTree *) m_outfile->Get("FitTree");
  if (!outtree) {
    outtree = new TTree("FitTree", "Tree");
    outtree->Branch("netCut",    &netCut,    "netCut/D");
    outtree->Branch("tracktype", &mytrack,   "tracktype/I");
    outtree->Branch("nBd_Val",   &nBd_Val,   "nBd_Val/D");
    outtree->Branch("nBd_Err",   &nBd_Err,   "nBd_Err/D");
    outtree->Branch("nBs_Val",   &nBs_Val,   "nBs_Val/D");
    outtree->Branch("nBs_Err",   &nBs_Err,   "nBs_Err/D");
    outtree->Branch("nBkg_Val",  &nBkg_Val,  "nBkg_Val/D");
    outtree->Branch("nBkg_Err",  &nBkg_Err,  "nBkg_Err/D");
    outtree->Branch("cBkg_Val",  &cBkg_Val,  "cBkg_Val/D");
    outtree->Branch("cBkg_Err",  &cBkg_Err,  "cBkg_Err/D");
    outtree->Branch("Brej_Val",  &Brej_Val,  "Brej_Val/D");
    outtree->Branch("Brej_Err",  &Brej_Err,  "Brej_Err/D");
    outtree->Branch("Seff_Val",  &Seff_Val,  "Seff_Val/D");
    outtree->Branch("Seff_Err",  &Seff_Err,  "Seff_Err/D");
    outtree->Branch("SSB_Val",   &SSB_Val,   "SSB_Val/D");
    outtree->Branch("SSB_Err",   &SSB_Err,   "SSB_Err/D");
    outtree->Branch("Punzi_Val", &Punzi_Val, "Punzi_Val/D");
    outtree->Branch("Punzi_Err", &Punzi_Err, "Punzi_Err/D");
  } else {
    outtree->SetBranchAddress("netCut",    &netCut);
    outtree->SetBranchAddress("tracktype", &mytrack);
    outtree->SetBranchAddress("nBd_Val",   &nBd_Val);
    outtree->SetBranchAddress("nBd_Err",   &nBd_Err);
    outtree->SetBranchAddress("nBs_Val",   &nBs_Val);
    outtree->SetBranchAddress("nBs_Err",   &nBs_Err);
    outtree->SetBranchAddress("nBkg_Val",  &nBkg_Val);
    outtree->SetBranchAddress("nBkg_Err",  &nBkg_Err);
    outtree->SetBranchAddress("cBkg_Val",  &cBkg_Val);
    outtree->SetBranchAddress("cBkg_Err",  &cBkg_Err);
    outtree->SetBranchAddress("Brej_Val",  &Brej_Val);
    outtree->SetBranchAddress("Brej_Err",  &Brej_Err);
    outtree->SetBranchAddress("Seff_Val",  &Seff_Val);
    outtree->SetBranchAddress("Seff_Err",  &Seff_Err);
    outtree->SetBranchAddress("SSB_Val",   &SSB_Val);
    outtree->SetBranchAddress("SSB_Err",   &SSB_Err);
    outtree->SetBranchAddress("Punzi_Val", &Punzi_Val);
    outtree->SetBranchAddress("Punzi_Err", &Punzi_Err);
  }
  outtree->SetDirectory(m_outfile);

  // *** Loop ***
  char buffer[30];
  Long64_t nEvents = 0;
  Long64_t previous = 0;
  RooDataSet *cutdata = 0;

  for (int i=0; i<200; i++) {
    netCut = 1. - 0.01 * i;
    //netCut = -1. + 0.01 * i;
    sprintf(buffer,"netval>%.2f", netCut);

    cutdata = (RooDataSet *)goodfitdata->reduce(buffer);
    nEvents = cutdata->numEntries();
    std::cout << "OPT: Evaluating cut " << buffer << " with " << nEvents
              << " entries" << std::endl;
    if (netCut<-1. || netCut>1.) {
      break;
    }
    else if (nEvents==previous || nEvents<10.) {
      continue;
    }
    else {
      previous = nEvents;
    }

    // *** Fit & Plot ***
    jpsiKsExt->fitToMass(cutdata, weightedFit);
    std::cout << " LOOP: Done fitting." << std::endl;

    if ((netCut<0. && i%25==0) || (netCut>=0. && i%10==0)) {
      // Plot with Parameters
      jpsiKsExt->plotOn(massPlot_Par, cutdata, weightedFit, 1, 1);
      if (tracktype==3) {
        sprintf(buffer,"%s && LL", buffer);
      } else {
        sprintf(buffer,"%s && DD", buffer);
      }
      massPlot_Par->Write(buffer);
      std::cout << " LOOP: Done plotting." << std::endl;
    }

    // *** Process ***
    nBd_Val = jpsiKsExt->nBd()->getVal();
    nBd_Err = jpsiKsExt->nBd()->getError();
    nBs_Val = jpsiKsExt->nBs()->getVal();
    nBs_Err = jpsiKsExt->nBs()->getError();
    nBkg_Val = jpsiKsExt->nonPeaking()->getVal();
    nBkg_Err = jpsiKsExt->nonPeaking()->getError(); 

    cutdata = (RooDataSet *)cutdata->reduce("mass<5240 || mass>5400");
    cBkg_Val = (34./18.)*cutdata->numEntries();
    cBkg_Err = (34./18.)*TMath::Sqrt(cutdata->numEntries());

    // yield ratio = 0.0116 +/- 0.0008
    // 60 MeV mass window
    Brej_Val = 1 - nBkg_Val/looseBkg_Val;
    Brej_Err = TMath::Sqrt( pow(nBkg_Err/looseBkg_Val, 2) +
                            pow(looseBkg_Err * nBkg_Val/pow(looseBkg_Val, 2),2));
    SSB_Val = nBd_Val*ratio/TMath::Sqrt(nBd_Val*ratio + bkgWin * nBkg_Val);
    Seff_Val = nBd_Val/looseBd_Val;
    Seff_Err = TMath::Sqrt( pow(nBd_Err/looseBd_Val, 2) +
                            pow(looseBd_Err * nBd_Val/pow(looseBd_Val, 2),2));
    SSB_Val = nBd_Val*ratio/TMath::Sqrt(nBd_Val*ratio + bkgWin * nBkg_Val);
    SSB_Err = (ratio/TMath::Sqrt(nBd_Val*ratio + bkgWin * nBkg_Val)) *
      TMath::Sqrt(
      pow((1 - ratio * nBd_Val/(2*(nBd_Val*ratio + bkgWin * nBkg_Val)))* nBd_Err, 2)
      + pow(nBkg_Err * bkgWin * nBd_Val/(2*(nBd_Val*ratio + bkgWin * nBkg_Val)), 2) );

    Punzi_Val = nBd_Val*ratio/(alpha/2 + TMath::Sqrt(bkgWin * nBkg_Val));
    Punzi_Err = (ratio/(alpha/2 + TMath::Sqrt(bkgWin * nBkg_Val))) * TMath::Sqrt(
      pow(nBd_Err,2) + pow(nBkg_Err * nBd_Val * bkgWin/(2 * TMath::Sqrt(
      bkgWin * nBkg_Val) * (alpha/2 + TMath::Sqrt(bkgWin * nBkg_Val))), 2));

 
    std::cout << "########################################" << std::endl;
    std::cout << "  LOOP RESULTS for " << buffer << std::endl;
    std::cout << "   # Bd2JpsiKs = " << nBd_Val << " +/- "
              << nBd_Err << std::endl;
    if (m_fitBs) {
      std::cout << "   # Bs2JpsiKs = " << nBs_Val << " +/- "
                << nBs_Err << std::endl;
    }
    std::cout << "  # Background = " << nBkg_Val << " +/- "
              << nBkg_Err << std::endl;
    std::cout << "########################################" << std::endl;
    std::cout << "  Background rejection: " << Brej_Val  << " +/- " << Brej_Err
              << std::endl;
    std::cout << "     Signal efficiency: " << Seff_Val  << " +/- " << Seff_Err
              << std::endl;
    std::cout << "           S/Sqrt(S+B): " << SSB_Val   << " +/- " << SSB_Err
              << std::endl;
    std::cout << "             Punzi FoM: " << Punzi_Val << " +/- " << Punzi_Err
              << std::endl;
    std::cout << "########################################" << std::endl;

    // First: determine best possible Figure of Merit
    //  Next: find beginning of the plateau
    if (SSB_Val>bestSSB_Val) {
      bestSSB_Val = SSB_Val;
      bestSSB_Err = SSB_Err;
      bestSSBCut = netCut;
      foundSSB = false;
    }
    if (!foundSSB && (bestSSB_Val - SSB_Val >
        TMath::Sqrt(pow(bestSSB_Err,2) + pow(SSB_Err,2)))) {
      optSSB_Val = SSB_Val;
      optSSB_Err = SSB_Err;
      optSSBCut = netCut;
      foundSSB = true;
    }
    if (Punzi_Val>bestPunzi_Val) {
      bestPunzi_Val = Punzi_Val;
      bestPunzi_Err = Punzi_Err;
      bestPunziCut = netCut;
      foundPunzi = false;
    }
    if (!foundPunzi && (bestPunzi_Val - Punzi_Val >
        TMath::Sqrt(pow(bestPunzi_Err,2) + pow(Punzi_Err,2)))) {
      optPunzi_Val = Punzi_Val;
      optPunzi_Err = Punzi_Err;
      optPunziCut = netCut;
      foundPunzi = true;
    }
    outtree->Fill();
    // reset
    cutdata = 0;
  }
  
  if (!foundSSB) {
      optSSB_Val = SSB_Val;
      optSSB_Err = SSB_Err;
      optSSBCut = -1;
  }
  if (!foundPunzi) {
      optPunzi_Val = Punzi_Val;
      optPunzi_Err = Punzi_Err;
      optPunziCut = -1;
  }

  std::cout << std::endl;
  std::cout << "########################################" << std::endl;
  std::cout << "  OPTIMISATION RESULTS" << std::endl;
  std::cout << "       Best cut on NN (SSB): " << bestSSBCut   << " with SSB = "
            << bestSSB_Val   << " +/- " << bestSSB_Err   << std::endl;
  std::cout << "    Optimal cut on NN (SSB): " << optSSBCut    << " with SSB = "
            << optSSB_Val    << " +/- " << optSSB_Err    << std::endl;
  std::cout << "     Best cut on NN (Punzi): " << bestPunziCut << " with FoM = "
            << bestPunzi_Val << " +/- " << bestPunzi_Err << std::endl;
  std::cout << "  Optimal cut on NN (Punzi): " << optPunziCut  << " with FoM = "
            << optPunzi_Val  << " +/- " << optPunzi_Err  << std::endl;
  std::cout << "########################################" << std::endl;

  // *** Write to file ***
  std::cout << "\n PROGRESS: Writing File \n" << std::endl; 
  outtree->Write("", TObject::kOverwrite);
  delete goodfitdata;
  return 0;
}

// #############################################################################
// *** Filling Weight Tree ***
int weighting::writeTree() {
  std::cout << "\n PROGRESS: Creating Tree \n" << std::endl; 

  // *** Initialise ***
  // Variables
  const int nleafs = 25;
  ULong64_t eventNumber = 0;
  UInt_t runNumber = 0;
  unsigned int nPVs  = 0;
  Int_t tracktype = 0;
  Double_t sweightBd[nleafs];
  Double_t sweightBs[nleafs];
  Double_t sweightKstar[nleafs];
  Double_t sweightBkg[nleafs];
  Double_t sweight[nleafs];
  Double_t mass[nleafs];
  Double_t time[nleafs];
  unsigned int unbiased = 0;

  // TTree
  TTree* outtree = new TTree("WeightTree","Weight Tree");
  outtree->Branch("eventNumberWeight", &eventNumber, "eventNumberWeight/l");
  outtree->Branch("runNumberWeight",   &runNumber,   "runNumberWeight/i");
  outtree->Branch("nPVsWeight",        &nPVs,        "nPVsWeight/I");
  outtree->Branch("tracktypeWeight",   &tracktype,   "tracktypeWeight/I");
  outtree->Branch("sweightBd",         &sweightBd,   "sweightBd[nPVsWeight]/D");
  outtree->Branch("sweightBs",         &sweightBs,   "sweightBs[nPVsWeight]/D");
  outtree->Branch("sweightKstar",      &sweightKstar,"sweightKstar[nPVsWeight]/D");
  outtree->Branch("sweightBkg",        &sweightBkg,  "sweightBkg[nPVsWeight]/D");
  outtree->Branch("sweight",           &sweight,     "sweight[nPVsWeight]/D");
  outtree->Branch("massWeight",        &mass,        "massWeight[nPVsWeight]/D");
  outtree->Branch("timeWeight",        &time,        "timeWeight[nPVsWeight]/D");
  if (m_step==m_NNUnbiased) {
    outtree->Branch("unbiased", &unbiased, "unbiased/I");
  }
  outtree->SetDirectory(m_outfile); 

  // *** For accessing DataSets ***
  RooArgSet *flatVar = (RooArgSet *) m_dataset->get();
  RooRealVar *flatMass   = (RooRealVar *)flatVar->find("mass");
  RooRealVar *flatWeight = (RooRealVar *)flatVar->find("weight");
  
  // *** Fill Tree ***
  const Long64_t nentries = m_ntuple->nEntries();
  Long64_t printMod = printFrac(nentries);
  Long64_t flatEntry = 0; // Runs over the flattened NTuple
  Long64_t sLLEntry  = 0; // Runs over the sWeighted dataset - LL
  Long64_t sDDEntry  = 0; // Runs over the sWeighted dataset - DD

  // Error handling: identify bad fits
  Double_t sumBd    = 0;
  Double_t sumBs    = 0;
  Double_t sumKstar = 0;
  Double_t sumBkg   = 0;
  Int_t flag = 0;

  std::cout << "WEIGHT: Will loop over " << nentries << " entries." << std::endl;
  for (Long64_t i=0; i<nentries; i++) {
    m_ntuple->GetChain()->GetEntry(i);

    // Progress
    if (i%printMod==0) {
      std::cout << " |-> " << i << " / " << nentries
                << " (" << 100*i/nentries << "%)" << std::endl;
    }

    // Fill Variables
    runNumber   = m_ntuple->getRunNumber();
    eventNumber = m_ntuple->getEventNumber();
    nPVs        = m_ntuple->primaries();
    tracktype   = m_ntuple->TrackType();
    unbiased    = m_ntuple->unbiasedTrigger();

    for (unsigned int pv = 0; pv<nPVs; pv++) {
      // Fill Arrays
      mass[pv]    = m_ntuple->mass(pv);
      time[pv]    = m_ntuple->time(pv);

      // Get decision of selection cuts
      m_dataset->get(flatEntry);
      // Error Handling: make sure the datasets are aligned
      if (TMath::Abs(mass[pv]-flatMass->getVal())>0.1 &&
          // flatMass is only defined in the proper mass range
          mass[pv]>=m_ntuple->sideband_low_min() &&
          mass[pv]<=m_ntuple->sideband_high_max(m_data)) {
        std::cout << "ERROR: Event " << i << " with PV " << pv
                  << " has mismatch of tuple mass " << mass[pv]
                  << " with flatted dataset entry " << flatEntry
                  << " mass " << flatMass->getVal()
                  << " and is of type " << flatWeight->getVal() << std::endl;
        return -1;
      }

      // Events Failing previous cuts
      if (flatWeight->getVal()<=-3) {
        sweightBd[pv]    = flatWeight->getVal();
        sweightBs[pv]    = sweightBd[pv];
        sweightKstar[pv] = sweightBd[pv];
        sweightBkg[pv]   = sweightBd[pv];
        sweight[pv]      = sweightBd[pv];
      // Good Candidates
      } else {
        // Signal Monte Carlo
        if (isSigMC(m_data)) {
          sweightBd[pv]    = 1; // By construction
          sweightBs[pv]    = 1;
          sweightKstar[pv] = 0;   
        // Long Data
        } else if (m_ntuple->TrackType()==m_LL) {
          sweightBd[pv]    = m_sData_LL->GetSWeight(sLLEntry, m_tag+"nBd");
          sweightBs[pv]    = (m_fitBs ?
                             m_sData_LL->GetSWeight(sLLEntry, m_tag+"nBs") : 0);
          sweightKstar[pv] = (m_fitKstar ?
                          m_sData_LL->GetSWeight(sLLEntry, m_tag+"nKstar") : 0);
          sLLEntry++;
        // Downstream Data
        } else if (m_ntuple->TrackType()==m_DD) {
          sweightBd[pv]    = m_sData_DD->GetSWeight(sDDEntry, m_tag+"nBd");
          sweightBs[pv]    = (m_fitBs ?
                             m_sData_DD->GetSWeight(sDDEntry, m_tag+"nBs") : 0);
          sweightKstar[pv] = 0; // By construction
          sDDEntry++;
        }
        sweightBkg[pv] = 1-sweightBd[pv]-sweightBs[pv]-sweightKstar[pv];
        sweight[pv]    = sweightBd[pv];
        
        // Error handling: identify bad fits
        sumBd    += sweightBd[pv];
        sumBs    += sweightBs[pv];
        sumKstar += sweightKstar[pv];
        sumBkg   += sweightBkg[pv];
        if (sumBd+sumBs+sumKstar+sumBkg<(sLLEntry+sDDEntry) - 5*(1+flag)) {
          flag++;
          std::cout << "WARNING: Mismatch of " << 5*(1+flag)
                    << " events at entry " << i << " corresponding to flat entry"
                    << flatEntry << " and sData entry "
                    << sLLEntry << " + " << sDDEntry
		                << " with sum of weights "
                    << sumBd+sumBs+sumKstar+sumBkg << std::endl;
        }
      }
      flatEntry++;
    } // End of pv-loop
    outtree->Fill();
  } // End of Ntuple loop


  // *** Error Analysis Results *** 
  if (!isSigMC(m_data)) {
    std::cout << "########################################" << std::endl;
    std::cout << "  RESULTS" << std::endl;
    std::cout << "  # Bd2JpsiKs: " << sumBd << " weighted versus "
              << fit_nBd_LL << " + " << fit_nBd_DD << " fitted." << std::endl;
    if (m_fitBs) {
      std::cout << "  # Bs2JpsiKs: " << sumBs << " weighted versus "
                << fit_nBs_LL << " + " << fit_nBs_DD << " fitted." << std::endl;
    }
    if (m_fitKstar) {
      std::cout << "  # B2JpsiK*: " << sumKstar << " weighted versus "
                << fit_nKstar_LL << " + " << fit_nKstar_DD << " fitted."
                << std::endl;
    }
    std::cout << "  # Background: " << sumBkg << " weighted versus "
              << fit_nbkg_LL << " + " << fit_nbkg_DD
              << " fitted." << std::endl;
    std::cout << "  Sum: " << sumBd + sumBs + sumKstar + sumBkg
              << " weighted versus " << sLLEntry << " + " << sDDEntry
              << " fitted." << std::endl;

    if (TMath::Abs(sumBd - fit_nBd_LL - fit_nBd_DD)>10 ||
        TMath::Abs(sumBs - fit_nBs_LL - fit_nBs_DD)>10 ||
        TMath::Abs(sumKstar - fit_nKstar_LL - fit_nKstar_DD)>5 ||
        TMath::Abs(sumBkg - fit_nbkg_LL - fit_nbkg_DD)>35) {
      std::cout << "ERROR: Mismatch between number of fitted and filled events"
                << std::endl;
      if (!isPrescaled (m_data)) return -1;
    }
    std::cout << "########################################" << std::endl; 
  }

  // *** Write to file ***
  std::cout << "\n PROGRESS: Writing File \n" << std::endl; 
  outtree->Write();

  return 0;
}  

// #############################################################################
// *** Weighting ***
int weighting::run(const double netCut_LL, const double netCut_DD) {

  // ***** PART I: Dataset ***** //
  /////////////////////////////////

  int err = fillDataSet(netCut_LL, netCut_DD);

  // Guard clause
  if (0!=err) return err;


  // ***** PART II: Fitting ***** //
  //////////////////////////////////

  if (isSigMC(m_data)) {
    std::cout << "\n PROGRESS: This is pure signal, no need for Fitting \n"
              << std::endl;
    err += writeTree();
  }
  else {
    err += fit(m_LL);
    err += fit(m_DD);
    err += writeTree();
  }

  m_outfile->Close();
  std::cout << "\n PROGRESS: Finished! \n" << std::endl;
  return err;
}

// #############################################################################
// *** Optimisation ***
int weighting::optimise(const double netCut_LL, const double netCut_DD) {

  // ***** PART I: Initialise ***** //
  ////////////////////////////////////

  // Guard clause
  if (!isLHCb(m_data)) {
    std::cout << "\n PROGRESS: This is Simulation, will not optimise \n"
              << std::endl;
    return 0;
  }

  int err = fillDataSet(netCut_LL, netCut_DD);

  // Guard clause
  if (0!=err) return err;

  // ***** PART II: Fitting ***** //
  //////////////////////////////////

  err += optfit(m_LL);
  err += optfit(m_DD);

  m_outfile->Close();
  std::cout << "\n PROGRESS: Finished! \n" << std::endl;
  return err;
}

// #############################################################################
// *** Main ***
int main(int argc, char** argv) {

  // *** Decode Arguments ***
  TString module, data, step, dir, decay, weightMethod;
  bool hasOpt;
  int out = decodeArgs(argc, argv,
                       module, data, step, dir, decay, weightMethod, hasOpt);
  if (out!=0) return out;

  // Extra argument
  double netCut_LL = -1.;
  double netCut_DD = -1.;
  bool doOptimisation = false;
  if (hasOpt) {
    doOptimisation = (argc>3 ? (int) atoi(argv[3]) : false);
    netCut_LL = (argc>4 ? (double) atoi(argv[4])/100. : -1.);
    netCut_DD = (argc>5 ? (double) atoi(argv[5])/100. : netCut_LL);
    std::cout << "Extra Arguments for " << module << std::endl;  
    std::cout << "  cut on NN: " << netCut_LL << "(LL) "
              << netCut_DD << "(DD)" << std::endl;
    if (doOptimisation) {
      std::cout << "  MODE: Optimisation" << std::endl;
    } else {
      std::cout << "  MODE: sWeighting" << std::endl;
    }   
    std::cout << "########################################" << std::endl;
  }

  // *** Main Function ***
  make_canvas();
  weighting* myWeight = new weighting(module, data, step, dir, decay,
                                      weightMethod, doOptimisation);
  if (doOptimisation) {
    return myWeight->optimise(netCut_LL, netCut_DD);
  } else {
    return myWeight->run(netCut_LL, netCut_DD);
  }
}

// #############################################################################
