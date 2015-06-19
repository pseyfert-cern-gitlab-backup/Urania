// $Id: $
// Include files 

// from Gaudi
#include "GaudiKernel/AlgFactory.h"
#include "GaudiAlg/GaudiTupleAlg.h"
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/INTupleSvc.h"
#include "GaudiKernel/PhysicalConstants.h"
#include "Kernel/IParticlePropertySvc.h" 
#include "Kernel/ParticleProperty.h" 

#include "Kernel/ParticleID.h"

#include "Event/HepMCEvent.h"
#include "HepMC/GenParticle.h"
#include "HepMC/GenVertex.h"

#include <boost/regex.hpp> 
#include <string>
#include <list>
#include <sstream>
#include <algorithm>
#include "TMath.h"

// local
#include "GaussDecayTupleTool.h"

//-----------------------------------------------------------------------------
// Implementation file for class : GaussDecayTupleTool
//
// Write Mother and Final State Daughters to nTuple 
//    e.g. D0 -> K- pi- pi+ pi+
//
// 
// 2009-01-18 : Thomas BLAKE
//-----------------------------------------------------------------------------

// Declaration of the Algorithm Factory
DECLARE_ALGORITHM_FACTORY( GaussDecayTupleTool );
//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
GaussDecayTupleTool::GaussDecayTupleTool( const std::string& name,
                                          ISvcLocator* pSvcLocator)
  : GaudiTupleAlg ( name , pSvcLocator )
{
  declareProperty( "NTupleName"   , m_tuplename   = "DecayTuple" ) ;
  declareProperty( "Mother"       , m_motherstring = "D0" );
  declareProperty( "Daughters"    , m_daughterstring = "K- pi- pi+ pi+" );
  declareProperty( "DeclareStable", m_stable );
}
//=============================================================================
// Destructor
//=============================================================================
GaussDecayTupleTool::~GaussDecayTupleTool() {} 

//=============================================================================
// Initialization
//=============================================================================
StatusCode GaussDecayTupleTool::initialize() {
  StatusCode sc = GaudiAlgorithm::initialize(); // must be executed first
  if ( sc.isFailure() ) return sc;  // error printed already by GaudiAlgorithm

  if ( msgLevel(MSG::DEBUG) ) debug() << "==> Initialize" << endmsg;

  debug() << "Initializing Particle Property Svc" << endmsg;
  
  m_ppsvc = svc< LHCb::IParticlePropertySvc> ( "LHCb::ParticlePropertySvc" , true ) ;

  const LHCb::ParticleProperty* pp = m_ppsvc->find( m_motherstring );
  
  if ( NULL == pp ) return Warning( "Could not find particle " + m_motherstring, StatusCode::FAILURE );
  
  m_motherid = pp->pdgID().pid();

  debug() << "Parsing mother + daughter strings" << endmsg;
  
  std::istringstream stream( m_daughterstring );
  char particlename[20];  
  
  while ( stream.good() ){
    stream >> particlename;
    addParticle( particlename );
  }

  std::sort( m_daughters.begin(), m_daughters.end(), EntryProperty() );
  m_ndaughters = m_daughters.size();

  // Create Unique nTuple labels
  
  unsigned int counter  = 2;
  unsigned int lastname = 0;
  
  char acounter[3];
  
  for ( unsigned int ipart = 1 ; ipart < m_ndaughters ; ++ipart ){
    
    if ( ( m_daughters[lastname].name ).compare( m_daughters[ipart].name ) == 0 ){
      sprintf(acounter,"%i",counter);
      m_daughters[ipart].name += acounter;
      ++counter;
    }
    else {
      if ( counter > 2 ) m_daughters[lastname].name += "1";
      counter = 2;
      lastname = ipart;
    }
  }  
  
  if ( counter > 2 && lastname < m_ndaughters ) m_daughters[lastname].name += "1";  

  return StatusCode::SUCCESS;
}

void  GaussDecayTupleTool::addParticle( const char* charstring ) {

  std::string stdname( charstring );
  if ( stdname.size() == 0 ) return;
  
  char* expr = "([[:word:]])|^(~)|([~])|(\\*)|([+])|([-])|(.)";
  char* replace = "(?1$1)(?2anti)(?3_anti)(?4st)(?5)(?6)(?7_)";

  verbose() << stdname << endmsg  ;
  
  std::string name;
  boost::regex expression( expr );

  name = boost::regex_replace( stdname, expression, replace, 
                               boost::match_default | boost::format_all );
  
  
  verbose() << name << endmsg  ;

  expression.assign(  "(^_+)|(_+$)|(_{2,})" );
  
  name =  boost::regex_replace( name, expression, "(?1)(?2)(?3_)", 
                                boost::match_default | boost::format_all );
  
  
  verbose() << name << endmsg  ;

  const LHCb::ParticleProperty* pp = m_ppsvc->find( charstring );

  if ( !pp ) Exception("Unknown particle");
  
  EntryProperty prop = { name, pp->pdgID().pid() };
  
  m_daughters.push_back( prop );
  
  info() << " Adding " << charstring << " as " << name <<  endmsg;

  return;
}

//=============================================================================
// Main execution
//=============================================================================

StatusCode GaussDecayTupleTool::execute() {

  if ( msgLevel(MSG::DEBUG) ) debug() << "==> Execute" << endmsg;
  StatusCode sc = StatusCode::SUCCESS;
  
  const LHCb::HepMCEvents* events =
    get<LHCb::HepMCEvents>( LHCb::HepMCEventLocation::Default );

    
  LHCb::HepMCEvents::const_iterator ievent;
  HepMC::GenEvent::particle_const_iterator ip;

  for ( ievent = events->begin(); ievent != events->end(); ++ievent ){
    for ( ip = (*ievent)->pGenEvt()->particles_begin();
          ip != (*ievent)->pGenEvt()->particles_end(); ++ip ){
      
      const HepMC::GenParticle* particle = (*ip);
      
      if ( abs(particle->pdg_id()) == m_motherid ) {
        debug() << " Found mother with ID = " << particle->pdg_id() << endmsg;
        fillCandidate( particle );
      }
    }
  }
  
  return sc ;// StatusCode::SUCCESS;
}


void GaussDecayTupleTool::addDaughters( ParticleVector& Daughters, const HepMC::GenParticle* particle )
{
  
  HepMC::GenVertex *decayVertex = particle -> end_vertex();
  HepMC::GenVertex::particles_out_const_iterator idaughter;
  
  if ( !decayVertex ) return;

  for ( idaughter = decayVertex -> particles_out_const_begin() ;
        idaughter != decayVertex -> particles_out_const_end() ;	
        ++idaughter ) {
    verbose() << "Daughter " << (*idaughter)->pdg_id() 
              << " LL: " << isLongLived( *idaughter ) << endmsg ;
    if ( isLongLived( *idaughter ) ) Daughters.push_back( (*idaughter) );
    else {
      addDaughters( Daughters, (*idaughter) );
    }
  }
  
  return;
}

void GaussDecayTupleTool::fillParticle( const HepMC::GenParticle* particle, 
                                        Tuple& tuple, const unsigned int number )
{

  std::string name = m_daughters[number].name;

  tuple->column( name + "ID", particle->pdg_id() );
  tuple->column( name + "Mass", particle->momentum().m() );
  tuple->column( name + "Px", particle->momentum().px() );
  tuple->column( name + "Py", particle->momentum().py() );
  tuple->column( name + "Pz", particle->momentum().pz() );
 
  // parent of daughter particle
  HepMC::GenVertex* prod = particle->production_vertex();
  
  HepMC::GenVertex::particles_in_const_iterator iparent = 
    prod->particles_in_const_begin();

  tuple->column( name + "Parent", (*iparent)->pdg_id() );
  
  return;
}


void GaussDecayTupleTool::fillCandidate( const HepMC::GenParticle* parent ){

  debug() << "Trying Candidate" << endmsg;
  
  ParticleVector Daughters;
  ParticleVector::iterator iter;
  
  addDaughters( Daughters, parent );

  unsigned int ndaughters = Daughters.size();

  verbose() << ndaughters << " " << m_ndaughters << endmsg ;

  if ( ndaughters !=  m_ndaughters ) return;
  
  int assigned[ m_ndaughters ];
  
  for ( unsigned int idaughter = 0; idaughter < m_ndaughters; ++idaughter ){
    assigned[idaughter] = -1;
  }
  
  int daughterid , pid;

  for ( unsigned int ipart = 0; ipart < m_ndaughters; ++ipart ){
    debug() << " i = " << ipart 
            << " --> " << Daughters[ipart]->pdg_id() << endmsg;
    
    unsigned int idaughter = 0;
    bool noassign = true;
    
    pid = Daughters[ipart]->pdg_id();
    pid = ( parent->pdg_id() > 0 ? pid : -pid );
    
    while ( idaughter < m_ndaughters && noassign ){
      daughterid = m_daughters[idaughter].pdgID;
      
      if ( (pid == daughterid) && (assigned[idaughter]  < 0) ){
        assigned[idaughter] = ipart;       
        noassign = false;
      } 
      ++idaughter;
    }
    
  }
  
  for ( unsigned int ipart = 0; ipart < m_ndaughters; ++ipart ){
    if ( assigned[ipart] < 0 ) return;
  }
  
  debug() << "Found Candidate! Filling nTuple " << endmsg;
  
  Tuple tuple = nTuple( m_tuplename );


  
  tuple->column("MotherID", parent->pdg_id() );
  tuple->column("MotherMass", parent->momentum().m() );
  tuple->column("MotherPx", parent->momentum().px() );
  tuple->column("MotherPy", parent->momentum().py() );
  tuple->column("MotherPz", parent->momentum().pz() );
  tuple->column("mprime", mprime( Daughters ) );
  tuple->column("thetaprime", thetaprime( Daughters ) );
  
  for ( unsigned int idaughter = 0; idaughter < ndaughters; ++idaughter ){ 
    
    debug() << " Daughter " << idaughter 
            << " = " << Daughters[idaughter]->pdg_id() << endmsg;
    unsigned int tofill = assigned[idaughter];
    fillParticle( Daughters[tofill] , tuple, idaughter  );
  }
  
  StatusCode sc = tuple->write();
  
  if (!sc.isSuccess()) {
    Exception("Error writing to ntuple !");
  }
  
  return;
}


bool GaussDecayTupleTool::isLongLived( const HepMC::GenParticle* particle ) const  {
  int pid = abs( particle->pdg_id() );
  if ( m_stable.empty() ){
    if ( pid == 321 || pid == 211 || pid == 11 || 
         pid == 13  || pid == 12  || pid == 14 || pid == 16 ){
      return true;
    }
  }
  else {
    for ( unsigned int i = 0; i < m_stable.size(); ++i ){
      if ( pid == m_stable[i] ) return true;
    } 
  }

  return false;
}


//=============================================================================
//  Finalize
//=============================================================================
StatusCode GaussDecayTupleTool::finalize() {

  if ( msgLevel(MSG::DEBUG) ) debug() << "==> Finalize" << endmsg;

  return GaudiAlgorithm::finalize();  // must be called after all other actions
}

//=============================================================================
double GaussDecayTupleTool::mprime(  ParticleVector Daughters )
{
  if ((13!=abs(Daughters[0]->pdg_id())) && 
      (13 != abs(Daughters[1]->pdg_id())) &&
      (2212 != abs(Daughters[2]->pdg_id()))){
    Exception("Beuh");
  };            
  const HepMC::FourVector m1 = Daughters[0]->momentum();
  const HepMC::FourVector m2 = Daughters[1]->momentum();
  const HepMC::FourVector jpsi(m1.px()+m2.px(),m1.py()+m2.py(),m1.pz()+m2.pz(),m1.e()+m2.e());
  const HepMC::FourVector p = Daughters[2]->momentum() ;
  //  const HepMC::FourVector pi = Daughters[3]->momentum() ;
  bool isPion = (211==abs(Daughters[3]->pdg_id()));
  double m = (sqrt(twoMass2(jpsi,p))-m_psi-m_p)/(m_Lb-m_psi-m_p-(isPion?m_pi:m_K));  
  double mp = (1./TMath::Pi())*acos(2*m-1) ;
  if (!(mp>=0.)){
    verbose() << "Bad m' " << sqrt(twoMass2(jpsi,p)) << endmsg ;
  }
  return mp ;  
}
double GaussDecayTupleTool::thetaprime( ParticleVector Daughters )
{
  const HepMC::FourVector m1 = Daughters[0]->momentum();
  const HepMC::FourVector m2 = Daughters[1]->momentum();
  const HepMC::FourVector jpsi(m1.px()+m2.px(),m1.py()+m2.py(),m1.pz()+m2.pz(),m1.e()+m2.e());
  verbose() << jpsi.m() << endmsg ;
  const HepMC::FourVector p = Daughters[2]->momentum() ;
  const HepMC::FourVector pi = Daughters[3]->momentum() ;
  bool isPion = (211==abs(Daughters[3]->pdg_id()));
  Double_t mjp2 = twoMass2(jpsi,p);  
  Double_t mph2 = twoMass2(p,pi);
  Double_t mjh2 = twoMass2(jpsi,pi);
  Double_t mh2 = (isPion?m_pi*m_pi:m_K*m_K);
  Double_t t1 = mjp2*(mph2-mjh2)-(m_p*m_p-m_psi*m_psi)*(m_Lb*m_Lb-mh2);
  Double_t t2a = mjp2+m_psi*m_psi-m_p*m_p;
  Double_t t2 = t2a*t2a - 4*mjp2*m_psi*m_psi;
  Double_t t3a = m_Lb*m_Lb-mh2-mjp2 ;
  Double_t t3 = t3a*t3a - 4*mjp2*mh2;
  Double_t th = (1./TMath::Pi())*acos(t1/(sqrt(t2)*sqrt(t3))) ;
  if (!(th>=0.)){
    verbose() << "Bad comb. t':" << th << " - Jp:" << sqrt(mjp2) << " ph:" << sqrt(mph2) << " jh:" << sqrt(mjh2) 
              << " " << Daughters[3]->pdg_id() << endmsg ;
    //    return -1. ;
  }
  return th ;
}


