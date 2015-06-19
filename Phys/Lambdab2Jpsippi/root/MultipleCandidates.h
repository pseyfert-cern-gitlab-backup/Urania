// $Id: $
#ifndef MULTIPLECANDIDATES_H 
#define MULTIPLECANDIDATES_H 1

// Include files
#include <map>
#include <vector>
#include <list>
#include <math.h>
#include <iostream>
typedef std::pair<long int, ULong64_t> RunEvent ;         ///< Unique Identifier of an event
typedef std::pair<long int, unsigned int> Candidate ;     ///< Unique Candidate Identifier
typedef std::vector< Candidate > Candidates ;             ///< List of Candidates belonging to event
typedef std::pair< RunEvent, Candidates > EventPair ;     ///< Pair of event, candidates
typedef std::map< RunEvent, Candidates > EventMap ;       ///< The big map of everything: event, candidates
#include "TRandom2.h"
#include "NetTree.h"
#include "Lambdab.h"
#include "Tuples.h"

class TTree ;
class IB2JpsiX;
/** @class MultipleCandidates MultipleCandidates.h MultipleCandidates.h
 *  
 *  Class that deals with multiple candidates. 
 *  Usuage example:
 *
 *  [some code to go here ] 
 *
 *  @author Patrick Koppenburg
 *  @date   2011-03-10
 */
class MultipleCandidates {

public: 
  /// Standard constructor
  MultipleCandidates( UInt_t seed ); 
  virtual ~MultipleCandidates( ); ///< Destructor

  /// fill one-by-one
  /// entry must be a unique identifier to your candidate (like entry in tuple)
  /// run and event must be the run a event number
  void fill(long int entry, unsigned int pv, long int run, ULong64_t event);

  /// return the number of candidates in that event
  unsigned int candidatesInEvent(long int runNumber, ULong64_t eventNumber );

  /// return 1/(the number of candidates in that event)
  double weight(long int runNumber, ULong64_t eventNumber );
  
  /// get the list of all candidates in events with more than one candidate
  /// or en empty vector if single candidate event
  /// when fast is set to true, it will not look for single events.
  Candidates allCandidatesInEvent(long int runNumber, ULong64_t eventNumber, bool fast=false );

  /// get a random candidate in that event (This is repoducible. Randommness is generated at fill time.)
  Candidate randomCandidate(long int runNumber, ULong64_t eventNumber);

  unsigned int chooseBPV(const std::map<unsigned int,bool>& passPVs) const;
  unsigned int chooseBPV(const std::list<unsigned int>& passPVs) const ;

protected:
  void clean(); ///< Remove useless entries with single events
  Candidates scramble( Candidates evts); ///< Put a random event at front

private:
  EventMap m_eventmap ;         /// map of events and candidates
  EventMap m_singleEvents ;     /// map of events and candidates for single events
  bool m_cleaned ;
  TRandom* m_rndm ;

};
MultipleCandidates* createEventMap(NetTree* ntuple, double NNcut, bool debug = false);
MultipleCandidates* createEventMap(Lambdab* ntuple, bool doVetoes=true, bool debug = false);
double printFrac(Long64_t n) ;

#endif // MULTIPLECANDIDATES_H
