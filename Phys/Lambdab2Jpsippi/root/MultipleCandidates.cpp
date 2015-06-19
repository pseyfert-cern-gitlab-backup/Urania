// $Id: $
// Include files 

#include "TTree.h"
#include <iostream>

// local
#include "MultipleCandidates.h"
#include "NetTree.h"
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
  m_rndm = new TRandom2(seed); // 0 : use time
  m_rndm->SetSeed(seed);
  cout << "Seed = " << m_rndm->GetSeed() << " (" << seed << ")" << endl ;
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
void MultipleCandidates::fill(long int entry, unsigned int pv, long int run, ULong64_t event){
  if (m_cleaned){
    cout << "ERROR: You cannot fill after the map has been cleaned" << endl ;
    return ;
  }
  RunEvent er(run,event) ;
  EventMap::iterator ei = m_eventmap.find(er) ;
  if (ei==m_eventmap.end()){ // new
    Candidates evts;
    evts.push_back(Candidate(entry,pv));
    m_eventmap.insert(EventPair(er,evts));
    //    std::cout << "MC Inserted " << run << " " << event << " : " << entry << " " << pv << endl ;   
  } else {
    ei->second.push_back(Candidate(entry,pv)); // append entry to list of candidates at this event
    //    std::cout << "MC Added    " << run << " " << event << " : " << entry << " " << pv << endl ;   
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
    else {
      //      cout << "MC inserting single event " << i->first.first << " " << i->first.second << endl ;
      m_singleEvents.insert(*i); // just to allow access
    }
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
  int i = int(m_rndm->Uniform(evts.size())); // returns a number between 0 and size-1
  Candidates nevts ;
  nevts.push_back(evts[i]);
  for (unsigned int j = 0 ; j!= evts.size() ; ++j){
    if (i!=j) nevts.push_back(evts[j]); 
  }
  //  cout << "MC scrambling gets " << i << " " << nevts[0].first 
  //     << " " << nevts[0].second << std::endl ;
  return nevts ;
} 
//=============================================================================
/// return all candidates in an event
//=============================================================================
Candidates MultipleCandidates::allCandidatesInEvent(long int runNumber, ULong64_t eventNumber, bool fast ){
  clean(); // make sure it's clean
  RunEvent ep(runNumber,eventNumber);
  EventMap::iterator ie = m_eventmap.find(ep);
  if (ie==m_eventmap.end()) { // single candidate event
    if (fast) {
      Candidates empty;
      empty.push_back(Candidate(-1,0));//  return something random
      return empty ; 
    } else {
      ie = m_singleEvents.find(ep);
      if (ie!=m_singleEvents.end()) {
	//	cout << "MC single event " << ie->second[0].first << endl ;
	return ie->second ;
      } else cout << "ERROR : event/run " << eventNumber << "/" << runNumber << " not found" << endl ;
    }
  }
  else {
    //    cout << "MC not single event returning " << ie->second[0].first << endl ;
    return ie->second ;
  }
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
Candidate MultipleCandidates::randomCandidate(long int runNumber, ULong64_t eventNumber){
  return *(allCandidatesInEvent(runNumber, eventNumber, true).begin());
}
// ###################################################################
MultipleCandidates* createEventMap(NetTree* ntuple, double NNcut, bool debug ){
  MultipleCandidates* eventmap = new MultipleCandidates(m_theSeed) ; // 0 means no reproducibility
  std::cout << " * Filling Duplicate Event Map \n" << std::endl;
  const Long64_t nentries = ntuple->fChain->GetEntries();  
  double frac = printFrac(nentries);
  for ( Long64_t i = 0; i < nentries; ++i ){
    ntuple->fChain->GetEntry( i );
    if( debug || 0==i%((int)(0.1*nentries))) std::cout << " |-> " << i << " / " << nentries << " (" 
						       << 100*i/nentries << "%) - " 
						       << ntuple->EventNumber << "/" << ntuple->RunNumber << endl ;
    for( unsigned int pv = 0 ; pv!=ntuple->PVs ; ++pv){
      if (ntuple->netOutput[pv]>=NNcut && ntuple->ErrorCode[pv]==0){
        eventmap->fill(i, pv, ntuple->RunNumber, ntuple->EventNumber );
        //        break ;
      }
    }
  }
  return eventmap;
}
// ###################################################################
MultipleCandidates* createEventMap(Lambdab* ntuple, bool doVetoes, bool debug){
  MultipleCandidates* eventmap = new MultipleCandidates(m_theSeed) ; // 0 means no reproducibility
  std::cout << " * Filling Duplicate Event Map \n" << std::endl;
  const Long64_t nentries = ntuple->GetEntries(debug);  
  double frac = printFrac(nentries);
  for ( Long64_t i = 0; i < nentries; ++i ){
    ntuple->fChain->GetEntry( i );
    if( debug || 0==i%((int)(0.1*nentries))) std::cout << " |-> " << i << " / " << nentries << " (" 
						       << 100*i/nentries << "%) - " 
						       << ntuple->eventNumber << "/" << ntuple->runNumber << endl ;
    if (!ntuple->pid()) continue;
    if (!ntuple->trigger()) continue;
    for( unsigned int pv = 0 ; pv!=ntuple->nPVs ; ++pv){
      if (!ntuple->preselection(pv)) continue ;
      if (doVetoes && !ntuple->PassesMassVetoesForTeaching(pv)) continue ;
      eventmap->fill(i, pv, ntuple->runNumber, ntuple->eventNumber );
      break ;
    }
  }
  return eventmap;
}

// ###################################################################
unsigned int MultipleCandidates::chooseBPV(const std::map<unsigned int,bool>& passPVsM) const {
  std::list<unsigned int> passPVs;
  for ( std::map<unsigned int,bool>::const_iterator i = passPVsM.begin() ; i!=passPVsM.end() ; ++i){
    if (i->second) passPVs.push_back(i->first);
  }
  return chooseBPV(passPVs);
}
// ###################################################################
unsigned int MultipleCandidates::chooseBPV(const std::list<unsigned int>& passPVs) const {
  if (passPVs.empty()) return 0;
  unsigned int id = m_rndm->Uniform(passPVs.size());
  unsigned int increment = 0 ;
  for ( std::list<unsigned int>::const_iterator i = passPVs.begin() ; i!=passPVs.end() ; ++i){
    if (increment==id) return *i ;
    increment++ ;
  }
  std::cout << "How can I be there?" << std::endl ;
  return 11 ; // large
}
// ###################################################################
// printFrac
double printFrac(Long64_t n){ return n>0 ? 1./int(sqrt(sqrt(1.0*n))):1 ;}
