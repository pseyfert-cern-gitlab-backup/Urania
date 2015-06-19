// #############################################################################
// Phys/Bs2JpsiKs Package
// Create Tuple for Fitter
// Authors: Patrick Koppenburg & Kristof De Bruyn
// #############################################################################

// #############################################################################
// *** Load Useful Classes *** 
// General C++
#include <iostream>
#include <list>

// ROOT
#include <TBranch.h> 
#include <TFile.h>
#include <TTree.h>

// Bs2JpsiKs Package
#include "IB2JpsiX.h"
#include "MultipleCandidates.h"
#include "TupleLoader.h"


// #############################################################################
// *** Declarations ***
void make_canvas();

class createTuple {
public :
  createTuple(const TString module, const TString data, const TString step,
              const TString dir, const TString decay, const TString weightMethod);
  ~createTuple() {};
  int fillDataSet(const double netCut_LL, const double netCut_DD);

private:
  
  // General Settings
  TString m_weightMethod;
  TString m_data;
  TString m_step;

  // Data
  IB2JpsiX* m_ntuple;
  TFile* m_outfile;

};
  
// #############################################################################
// *** Constructor ***
createTuple::createTuple(const TString module, const TString data,
                         const TString step, const TString dir,
                         const TString decay, const TString weightMethod) {

  // *** Initialise ***
  m_weightMethod = weightMethod;
  m_data = data;
  m_step = step;

  // *** Load NTuple ***
  m_ntuple = loadTuple(module, data, step, dir, decay, weightMethod);
  if (!m_ntuple) {
    std::cout << "ERROR: Ntuple could not be loaded" << std::endl;
    return;
  }

  // *** Set Output ***
  TString outFileName = makeFileName(module, data, "Tuple", dir,
                                     decay, weightMethod);
  if (outFileName=="") {
    std::cout << "ERROR: Failed to generate output file." << std::endl;
    return;
  }

  m_outfile = new TFile(outFileName, "RECREATE" );
  m_outfile->cd();
}

// #############################################################################
// *** Filling ***
int createTuple::fillDataSet(const double netCut_LL, const double netCut_DD) {
  
  std::cout << "\n PROGRESS: Initialising TTree \n" << std::endl;

  // *** Initialise TTree ***
  // Variables
  int trackType = 0;
  double mass = 0;
  double time = 0;
  double terr = 0;
  int tagOS = 0;
  double etaOS = 0;
  int tagSSK = 0;
  double etaSSK = 0;
  int tagCombi = 0;
  double etaCombi = 0;
  int inputfile = 0;
  int polarity = 0;
  double gpsSecond = 0;

  // TTree
  TTree* outtree = new TTree("Bs2JpsiKs_Fitters", "Data Tree for Fitters");
  outtree->Branch("catTrackType", &trackType, "catTrackType/I");
  outtree->Branch("obsMass",      &mass,      "obsMass/D");
  outtree->Branch("obsTime",      &time,      "obsTime/D");
  outtree->Branch("obsTimeErr",   &terr,      "obsTimeErr/D");
  outtree->Branch("catTagOS",     &tagOS,     "catTagOS/I");
  outtree->Branch("obsEtaOS",     &etaOS,     "obsEtaOS/D");
  outtree->Branch("catTagSSK",    &tagSSK,    "catTagSSK/I");
  outtree->Branch("obsEtaSSK",    &etaSSK,    "obsEtaSSK/D");
  outtree->Branch("catTagCombi",  &tagCombi,  "catTagCombi/I");
  outtree->Branch("obsEtaCombi",  &etaCombi,  "obsEtaCombi/D");
  outtree->Branch("dataYear",     &inputfile, "dataYear/I");
  outtree->Branch("polarity",     &polarity,  "polarity/I");
  outtree->Branch("gpsSecond",    &gpsSecond, "gpsSecond/D");
  outtree->SetDirectory(m_outfile);

  std::cout << "\n PROGRESS: Multiple Candidates \n" << std::endl;

  // *** Multiple Candidates ***
  MultipleCandidates* m_eventMap = createEventMap(m_ntuple, m_data, netCut_LL, netCut_DD);
  
  std::cout << "\n PROGRESS: Filling TTree \n" << std::endl;
  
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
      bool pass = 
           ((m_ntuple->TrackType()==3 && m_ntuple->neuralnet(pv)>=netCut_LL) ||
            (m_ntuple->TrackType()==5 && m_ntuple->neuralnet(pv)>=netCut_DD));
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
    // Events surviving cuts
    } else {
      tempWeight = m_eventMap->weightMultipleCandidates(m_weightMethod,
                                                        m_ntuple, i);
      // Surviving Candidates
      if (tempWeight>0.) {
        nGood_LL += addLL; nGood_DD += addDD;
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
        // Pick random PV
        int pick = m_eventMap->pickRandomPV(goodPVs);
        std::list<unsigned int>::const_iterator it = goodPVs.begin();
        std::advance(it, pick);
        // Assign weight & fill dataset
        trackType = (addDD ? 55 : 33);
        mass = m_ntuple->mass(*it);
        time = m_ntuple->time(*it);
        terr = m_ntuple->timeErr(*it);
        tagOS = m_ntuple->tagOS(m_data);
        etaOS = m_ntuple->etaOS(m_data);
        tagSSK = m_ntuple->tagSSK();
        etaSSK = m_ntuple->etaSSK();
        tagCombi = m_ntuple->tagCombi();
        etaCombi = m_ntuple->etaCombi();
        inputfile = (m_ntuple->getInputFile()==0 ? 2011 : 2012);
        polarity = m_ntuple->getPolarity();
        gpsSecond = (double) m_ntuple->getGpsSecond();
        outtree->Fill();
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
  
  // *** Write to file ***
  std::cout << "\n PROGRESS: Writing File \n" << std::endl; 
  outtree->Write();
  m_outfile->Close();
  
  std::cout << "\n PROGRESS: Finished! \n" << std::endl;
  return 0;
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
  if (argc<5) {
    std::cout << "ERROR: Insufficient arguments" << std::endl;
    std::cout << "Don't forget to provide NN cuts" << std::endl;
    return 1;
  }

  // Extra argument
  double netCut_LL = (double) atoi(argv[3])/100.;
  double netCut_DD = (double) atoi(argv[4])/100.;
  std::cout << "Creating Final Tuple for NN: " << netCut_LL << "(LL) "
            << netCut_DD << "(DD)" << std::endl;  
  std::cout << "########################################" << std::endl;

  // *** Main Function ***
  make_canvas();
  createTuple* myTuple = new createTuple(module, data, step, dir, decay,
                                         weightMethod);
  return myTuple->fillDataSet(netCut_LL, netCut_DD);
}

// #############################################################################
