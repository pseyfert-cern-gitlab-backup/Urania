// #############################################################################
// Phys/Bs2JpsiKs Package
// Identify Events with Multiple Candidates
// Authors: Patrick Koppenburg & Kristof De Bruyn
// #############################################################################

// #############################################################################
// *** Load Useful Classes ***
#include "MultipleCandidates.h"

using namespace std;

// #############################################################################
// *** Constructor ***
MultipleCandidates::MultipleCandidates(const unsigned int  seed) {
  // Global Settings
  m_cleaned = false;

  // Set Random Seeds
  m_randomMuPV = new TRandom2(m_pvSeed);
  m_randomMuPV->SetSeed(m_pvSeed);
  std::cout << "MULTCAND: Primary Vertex Killing Seed = "
            << m_randomMuPV->GetSeed() << " (" << m_pvSeed << ")" << std::endl;
  m_randomMuCa = new TRandom2(seed);
  m_randomMuCa->SetSeed(seed);
  std::cout << "MULTCAND: Multiple Candidate Killing Seed = "
            << m_randomMuCa->GetSeed() << " (" << seed << ")" << std::endl;
}

// #############################################################################
// *** Accessors ***
// Get the list of all candidates in events with more than one candidate
// or en empty vector if single candidate event
// when fast is set to true, it will not look for single events.
Candidates MultipleCandidates::allCandidatesInEvent(const long int runNumber,
  const ULong64_t eventNumber, bool fast) {
  // make sure the map is cleaned
  clean();
  std::pair<long int,long int> ev_pair(runNumber,eventNumber);
  EventMap::iterator ev_iter = m_eventmap.find(ev_pair);
  // Events with only single candidate
  if (ev_iter==m_eventmap.end()) {
    if (fast) {
      Candidates empty;
      empty.push_back(-1); // return something random
      return empty;
    } else {
      ev_iter = m_singleEvents.find(ev_pair);
      if (ev_iter!=m_singleEvents.end()) {
        return ev_iter->second;
      } else {
        std::cout << "ERROR : Event/Run " << eventNumber << "/" << runNumber
                  << " not found" << std::endl;
      }
    }
  // Events with multiple candidates
  } else {
    return ev_iter->second;
  }
}

// #############################################################################
// *** Functions ***
// Fill eventmap
// entry must be a unique identifier to your candidate (like entry in tuple)
// run and event must be the run and event number
void MultipleCandidates::fill(const long int entry, const long int run, 
                              const ULong64_t event) {

  // Guard Clause
  if (m_cleaned) {
    std::cout << "ERROR: You cannot (re)fill the eventmap "
              << "after it has been cleaned." << std::endl;
    return;
  }

  // Fill
  RunEvent ev_run(run,event);
  EventMap::iterator ev_iter = m_eventmap.find(ev_run);
  // First event
  if (ev_iter==m_eventmap.end()) {
    Candidates evts;
    evts.push_back(entry);
    m_eventmap.insert(EventPair(ev_run,evts));
  // All other events
  } else {
    ev_iter->second.push_back(entry);
  }
}

// #############################################################################
//  Remove useless entries with single events
void MultipleCandidates::clean() {
  // Guard Clause
  if (m_cleaned) return;

  std::cout << "MULTCAND: Cleaning event map" << std::endl;
  // Split into events with multiple candidates and with single candidates
  EventMap cleanedmap;
  for (EventMap::const_iterator i = m_eventmap.begin();
       i!= m_eventmap.end(); i++) {
    // Multiple Candidates
    if (i->second.size()>1) {
      cleanedmap.insert(EventPair(i->first,scramble(i->second)));
    // Single Candidates
    } else {
      m_singleEvents.insert(*i);
    }
  }
  std::cout << "MULTCAND: EventMap has " << m_eventmap.size()
            << " events of which " << cleanedmap.size()
            << " have duplicates." << std::endl;
  // Keep only events with multiple candidates
  m_eventmap = cleanedmap;
  m_cleaned = true;
}

// #############################################################################
// Put a random event in the front
Candidates MultipleCandidates::scramble(Candidates evts) {
  // return a number between 0 and size-1
  int i = int(m_randomMuCa->Uniform(evts.size()));
  Candidates nevts;
  nevts.push_back(evts[i]);
  for (unsigned int j = 0; j!= evts.size(); j++) {
    if (i!=j) nevts.push_back(evts[j]);
  }
  return nevts;
} 

// #############################################################################
// Return weight of Multiple Candidate
double MultipleCandidates::weightMultipleCandidates(const TString weightMethod,
  IB2JpsiX* ntuple, const Long64_t entry) {
  if (m_random==weightMethod) {
    int nCand = this->candidatesInEvent(ntuple->getRunNumber(),
                                        ntuple->getEventNumber());
    if (nCand==1) {
      return 1.;
    } else if (nCand>1) {
      int chosenCand = this->randomCandidate(ntuple->getRunNumber(),
                                             ntuple->getEventNumber());
      if (entry==chosenCand) return 1.;
      else return 0.;
    } else {
      std::cout << "ERROR: Number of multiple candidates is "
                << nCand << std::endl;
      return 0;
    }
  } else if (m_downscaled==weightMethod) {
    return 0.1;
  } else if (m_weighted==weightMethod) {
    return this->weight(ntuple->getRunNumber(), ntuple->getEventNumber());
  } else if (m_noweight==weightMethod) {
    return 1.;
  } else {
    std::cout << "ERROR: Weight Method " << weightMethod 
              << " not supported." << std::endl;
    return 0.;
  }
}

// #############################################################################
// Choose a best primary vertex
int MultipleCandidates::pickRandomPV(const std::list<unsigned int>& passPVs) {
  if (passPVs.empty()) return -999;
  else return m_randomMuPV->Uniform(passPVs.size());
}


// #############################################################################
// *** Main Function ***
// Create & fill eventmap
MultipleCandidates* createEventMap(IB2JpsiX* ntuple, const TString data,
  const double netCut_LL, const double netCut_DD) {
  // *** Initialise ***
  MultipleCandidates* eventmap = new MultipleCandidates();
  const Long64_t nentries = ntuple->nEntries();
  const Long64_t printMod = printFrac(nentries);
  std::cout << "MULTCAND: Filling Duplicate Event Map for neural net cuts: "
            << netCut_LL << " and " << netCut_DD << std::endl;
  std::cout << "   Looping over " << nentries << " events" << std::endl;

  // *** Loop ***
  for (Long64_t i = 0; i<nentries; i++) {
    ntuple->GetChain()->GetEntry(i);
    // Progress
    if (i%printMod==0) {
      std::cout << " |-> " << i << " / " << nentries
                << " (" << 100*i/nentries << "%)" << std::endl;
    }
    
    // If any of the (B,PV) combinations survives, keep the event
    bool pass = false;
    for (unsigned int pv = 0; (pv!=ntuple->primaries() && !pass); pv++) {
      // First weighting
      if (netCut_LL<=-3.) {
        pass = ntuple->applyAllCuts(data, pv);
      // All other weighting
      } else {
        pass = ((ntuple->TrackType()==m_LL && ntuple->neuralnet(pv)>=netCut_LL)
          || (ntuple->TrackType()==m_DD && ntuple->neuralnet(pv)>=netCut_DD));
      }
    }
    if (pass) {
      eventmap->fill(i, ntuple->getRunNumber(), ntuple->getEventNumber());
    }
  }
  return eventmap;
}
