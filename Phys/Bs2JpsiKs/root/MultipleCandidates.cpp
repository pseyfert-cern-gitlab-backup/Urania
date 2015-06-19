// $Id: $
// Include files 

#include "TTree.h"
#include <iostream>

// local
#include "MultipleCandidates.h"
#include "TupleLoader.h"
#include "IB2JpsiX.h"
using namespace std;

//-----------------------------------------------------------------------------
// Implementation file for class : MultipleCandidates
//
// 2011-03-10 : Patrick Koppenburg
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
MultipleCandidates::MultipleCandidates( UInt_t seed ) {
  m_cleaned = false ;
  m_randomMuPV = new TRandom2(m_pvSeed);
  m_randomMuPV->SetSeed(m_pvSeed);
  std::cout << "Primary Vertex Killing Seed = " << m_randomMuPV->GetSeed() << " (" << m_pvSeed << ")" << std::endl;
  m_randomMuCa = new TRandom2(seed); // 0 : use time
  m_randomMuCa->SetSeed(seed);
  cout << "Multiple Candidate Killing Seed = " << m_randomMuCa->GetSeed() << " (" << seed << ")" << endl ;
  cout << "MultipleCandidates() doing nothing. You must call fill(...)" << endl ;
}
//=============================================================================
// Destructor
//=============================================================================
MultipleCandidates::~MultipleCandidates() {} 
//=============================================================================
/// fill one-by-one
/// entry must be a unique identifier to your candidate (like entry in tuple)
/// run and event must be the run a event number
//=============================================================================
void MultipleCandidates::fill(long int entry, long int run, ULong64_t event){
  if (m_cleaned){
    cout << "ERROR: You cannot fill after the map has been cleaned" << endl ;
    return ;
  }
  RunEvent er(run,event) ;
  EventMap::iterator ei = m_eventmap.find(er) ;
  if (ei==m_eventmap.end()){ // new
    Candidates evts;
    evts.push_back(entry);
    m_eventmap.insert(EventPair(er,evts));
  } else {
    ei->second.push_back(entry); // append entry to list of candidates at this event
  }
}
//=============================================================================
//  Remove useless entries with single events
//=============================================================================
void MultipleCandidates::clean(){
  if (m_cleaned) return ;
  cout << "cleaning event map" << endl ;
  EventMap cleanedmap;
  for (EventMap::const_iterator i = m_eventmap.begin() ; i!= m_eventmap.end() ; ++i){
    if (i->second.size()>1) {
      cleanedmap.insert(EventPair(i->first,scramble(i->second)));
    }
    else m_singleEvents.insert(*i); // just to allow access
  }
  cout << "EventMap has " << m_eventmap.size() << " events of which " 
       << cleanedmap.size() << " have duplicates. Keeping only one candidate." << endl ;
  m_eventmap = cleanedmap ; // overwrite
  m_cleaned = true ;
}
//=============================================================================
// Scramble
//=============================================================================
Candidates MultipleCandidates::scramble(Candidates evts) {
  int i = int(m_randomMuCa->Uniform(evts.size())); // returns a number between 0 and size-1
  Candidates nevts ;
  nevts.push_back(evts[i]);
  for (unsigned int j = 0 ; j!= evts.size() ; ++j){
    if (i!=j) nevts.push_back(evts[j]); 
  }
  return nevts ;
} 
//=============================================================================
/// return all candidates in an event
//=============================================================================
Candidates MultipleCandidates::allCandidatesInEvent(long int runNumber, ULong64_t eventNumber, bool fast ){
  clean(); // make sure it's clean
  std::pair<long int,long int> ep(runNumber,eventNumber);
  EventMap::iterator ie = m_eventmap.find(ep);
  if (ie==m_eventmap.end()) { // single candidate event
    if (fast) {
      Candidates empty;
      empty.push_back(-1);//  return something random
      return empty ; 
    } else {
      ie = m_singleEvents.find(ep);
      if (ie!=m_singleEvents.end()) return ie->second ;
      else cout << "ERROR : event/run " << eventNumber << "/" << runNumber << " not found" << endl ;
    }
  }
  else return ie->second ;
}
//=============================================================================
/// return the number of candidates in that event
//=============================================================================
unsigned int MultipleCandidates::candidatesInEvent(long int runNumber, ULong64_t eventNumber ){
  return (allCandidatesInEvent(runNumber, eventNumber, true)).size();
}
//=============================================================================
/// return 1/(the number of candidates in that event)
//=============================================================================
double MultipleCandidates::weight(long int runNumber, ULong64_t eventNumber ){
  return 1./candidatesInEvent(runNumber, eventNumber );
}
//=============================================================================
/// return random candidate
//=============================================================================
long int MultipleCandidates::randomCandidate(long int runNumber, ULong64_t eventNumber){
  return *(allCandidatesInEvent(runNumber, eventNumber, true).begin());
}
//=============================================================================
/// create & fill eventmap
//=============================================================================
MultipleCandidates* createEventMap(IB2JpsiX* ntuple, unsigned int ttype, TString what, unsigned int NNtype, double netCut){
  MultipleCandidates* eventmap = new MultipleCandidates() ; // 0 means no reproducibility
  const Long64_t nentries = ntuple->nEntries();  
  std::cout << " * Filling Duplicate Event Map for neural net cut: " << netCut << " n: " << nentries << "\n" << std::endl;
  double frac = printFrac(nentries);
  for ( Long64_t i = 0; i < nentries; ++i ){
    ntuple->GetChain()->GetEntry( i );
    if(0==i%((int)(frac*nentries))) std::cout << " |-> " << i << " / " << nentries << " (" << 100*i/nentries << "%)" << std::endl;
    
    // If any of the (B,PV) combinations survives, keep the event
    bool pass = false;
    for( unsigned int pv = 0 ; (pv!=ntuple->primaries() && !pass) ; ++pv){
      if(netCut<=-5.) pass = ntuple->applyAllCuts(NNtype,what,pv,ttype); // In case of MuCa killing at weighting
      else pass = (ntuple->neuralnet(pv)>=netCut); // In case of MuCa Kill at branching
    }
    if (pass) eventmap->fill(i, ntuple->getRunNumber(), ntuple->getEventNumber() );
  }
  return eventmap;
}


//=============================================================================
/// choose random candidate
//=============================================================================
double MultipleCandidates::weightMultipleCandidates(Long64_t entry, IB2JpsiX* ntuple, TString weightMethod){
  if ( m_random==weightMethod ){
    int nCand = this->candidatesInEvent(ntuple->getRunNumber(), ntuple->getEventNumber());
    if (nCand==1){
      return 1.;
    } else if (nCand>1){
      int chosenCand = this->randomCandidate(ntuple->getRunNumber(), ntuple->getEventNumber());
      if ( entry==chosenCand )return 1.;
      else return 0.;
    } else {
      std::cout << "WARNING: Number of multiple candidates is " << nCand << std::endl ;
      return 0 ;
    }
  } else if( m_noweight==weightMethod ){
    return 1.;
  } else if ( m_downscaled==weightMethod ){
    return 0.1;
  } else if ( m_weighted==weightMethod ){
    return this->weight(ntuple->getRunNumber(), ntuple->getEventNumber());
  } else {
    std::cout << "Weight Method not supported: " << weightMethod << std::endl ;
    return 0.;
  }
}

bool MultipleCandidates::pickMultipleCandidates(Long64_t entry, IB2JpsiX* ntuple, TString weightMethod){
  return (this->weightMultipleCandidates(entry, ntuple, weightMethod)>0);
}

//=============================================================================
/// choose best primary vertex
//=============================================================================
unsigned int MultipleCandidates::pickBestPV(const std::list<unsigned int>& passPVs){
  if (passPVs.empty()) return -999;
  unsigned int id = (unsigned int) m_randomMuPV->Uniform(passPVs.size());
  unsigned int increment = 0 ;
  for ( std::list<unsigned int>::const_iterator i = passPVs.begin() ; i!=passPVs.end() ; ++i){
    if (increment==id) return *i ;
    increment++ ;
  }
  std::cout << "ERROR: Got out of loop without assigning best PV" << std::endl ;
  return -999;
}
