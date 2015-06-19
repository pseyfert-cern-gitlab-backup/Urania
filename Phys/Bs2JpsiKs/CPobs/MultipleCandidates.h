// #############################################################################
// Phys/Bs2JpsiKs Package
// Identify Events with Multiple Candidates
// Authors: Patrick Koppenburg & Kristof De Bruyn
// #############################################################################

#ifndef MULTIPLECANDIDATES_H 
#define MULTIPLECANDIDATES_H 1

// #############################################################################
// *** Load Useful Classes ***
// General C++
#include <iostream>
#include <list>
#include <map>
#include <utility>
#include <vector>

// ROOT
#include <TRandom2.h>
#include <TTree.h>

// Bs2JpsiKs Package
#include "TupleLoader.h"
#include "IB2JpsiX.h"

using namespace std;


// #############################################################################
// *** Declarations ***

// Constants
static const int m_pvSeed   = 123456789;
static const int m_mucaSeed = 123456789;

// Types
// --> Unique Identifier of an event
typedef std::pair<long int, ULong64_t> RunEvent;
// --> List of Candidates belonging to event
typedef std::vector<long int> Candidates;
// --> Pair of (event, candidates)
typedef std::pair<RunEvent, Candidates> EventPair;
// --> The big map of everything: event, candidates
typedef std::map<RunEvent, Candidates> EventMap;

// Classes
class TTree;
class IB2JpsiX;
class MultipleCandidates {

public: 
  // *** Constructor - Destructor ***
  MultipleCandidates(const unsigned int seed = m_mucaSeed); 
  virtual ~MultipleCandidates() {};
  
  // *** Accessors ***
  // Get the list of all candidates
  Candidates allCandidatesInEvent(const long int runNumber,
    const ULong64_t eventNumber, bool fast=false);

  // Return the number of candidates in that event
  unsigned int candidatesInEvent(const long int runNumber,
                                 const ULong64_t eventNumber) {
    return (allCandidatesInEvent(runNumber, eventNumber, true)).size();
  }

  double weight(const long int runNumber,
                const ULong64_t eventNumber) {
    return 1./candidatesInEvent(runNumber, eventNumber);
  }

  // Get a random candidate in given event
  // Repoducible: Randommness is generated at fill time.
  long int randomCandidate(const long int runNumber,
                           const ULong64_t eventNumber) {
    return *(allCandidatesInEvent(runNumber, eventNumber, true).begin());
  }

  // *** Functions ***
  void fill(const long int entry, const long int run, const ULong64_t event);

  double weightMultipleCandidates(const TString weightMethod, IB2JpsiX* ntuple,
                                  const Long64_t entry);
  bool pickMultipleCandidates(const TString weightMethod, IB2JpsiX* ntuple,
                              const Long64_t entry) {
    return (this->weightMultipleCandidates(weightMethod, ntuple, entry)>0);
  }
  int pickRandomPV(const std::list<unsigned int>& passPVs);

protected:
  void clean(); // Remove useless entries with single events
  Candidates scramble(Candidates evts); // Put a random event in the front

private:
  // Settings
  bool m_cleaned;

  // Randomisers
  TRandom2* m_randomMuPV;
  TRandom2* m_randomMuCa;

  // Big maps of everything
  EventMap m_eventmap;
  EventMap m_singleEvents;
};

MultipleCandidates* createEventMap(IB2JpsiX* ntuple, const TString data,
  const double netCut_LL, const double netCut_DD);

#endif // MULTIPLECANDIDATES_H
