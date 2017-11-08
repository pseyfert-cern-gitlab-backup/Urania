 // Include files
#include "GaudiKernel/ToolFactory.h"
#include "Event/Particle.h"
#include "Event/MCParticle.h"
// kernel
#include "GaudiAlg/Tuple.h"
#include "GaudiAlg/TupleObj.h"
#include "GaudiKernel/PhysicalConstants.h"
#include "Kernel/IParticle2MCAssociator.h"
// local
#include "TupleToolEWTrackIsolation.h"
//-----------------------------------------------------------------------------
// Implementation file for class : TupleToolEWTrackIsolation
//
// 2014-12-02 : Simone Bifani
//-----------------------------------------------------------------------------
// Declaration of the Algorithm Factory
DECLARE_TOOL_FACTORY( TupleToolEWTrackIsolation )
//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
TupleToolEWTrackIsolation::TupleToolEWTrackIsolation( const std::string &type,
                                                      const std::string &name,
                                                      const IInterface *parent)
   : TupleToolBase ( type, name, parent ) {
 
    declareInterface<IParticleTupleTool>( this );
    declareProperty( "MinConeRadius", m_minConeRadius = 0.,
                      "Set the minimal deltaR of the cone around the seed" );
    declareProperty( "MaxConeRadius", m_maxConeRadius = .5,
                      "Set the maximum deltaR of the cone around the seed" );
    declareProperty( "ConeStepSize", m_coneStepSize = .5,
                      "Set the step of deltaR between two iterations" );
    declareProperty( "TrackType", m_trackType = 3,
                      "Set the type of tracks which are considered inside the cone" );
    declareProperty( "ExtraParticlesLocation", m_extraParticlesLocation = "StdAllNoPIDsMuons",
                      "Set the type of particles which are considered in the charged cone" );
    declareProperty( "ExtraPhotonsLocation", m_extraPhotonsLocation = "StdVeryLooseAllPhotons",
                      "Set the type of photons which are considered in the neutral cone" );
    declareProperty( "ExtraPi0sLocation", m_extraPi0sLocation = "StdLoosePi02gg",
                      "Set the type of Pi0s which are considered in the neutral cone" );
    declareProperty( "FillComponents", m_fillComponents = true,
                      "Flag to fill all the 3-momentum components" );
    declareProperty( "isMC", m_isMC = false, 
                      "Flag to fill MC truth information" );
    // do as in TupleToolMCTruth
    m_p2mcAssocTypes.push_back( "DaVinciSmartAssociator" );
    m_p2mcAssocTypes.push_back( "MCMatchObjP2MCRelator"  );
    declareProperty( "IP2MCPAssociatorTypes", m_p2mcAssocTypes );
   }
//=============================================================================
// Destructor
//=============================================================================
TupleToolEWTrackIsolation::~TupleToolEWTrackIsolation() {}

//=============================================================================
// Initialization
//============================================================================
StatusCode TupleToolEWTrackIsolation::initialize() 
{
  StatusCode sc = TupleToolBase::initialize();
  if ( sc.isFailure() ) return sc;
  
  if ( m_minConeRadius > m_maxConeRadius) {
    if ( msgLevel(MSG::FATAL) ) fatal() << "Max conesize smaller than min conesize." << endmsg; 
    return StatusCode::FAILURE;
  }
  
  // the MC associators
  m_p2mcAssocs.clear();
  for ( std::vector<std::string>::const_iterator iMCAss = m_p2mcAssocTypes.begin();
        iMCAss != m_p2mcAssocTypes.end(); ++iMCAss ) {
    m_p2mcAssocs.push_back( tool<IParticle2MCAssociator>(*iMCAss,this) );
  }
  if ( m_p2mcAssocs.empty() ) { return Error("No MC associators configured"); }
  
  if ( msgLevel(MSG::DEBUG) ) debug() << "==> Initialize" << endmsg;
  return StatusCode::SUCCESS;
}

//=============================================================================
// Fill the tuple
//=============================================================================
StatusCode TupleToolEWTrackIsolation::fill( const LHCb::Particle *top,
                                            const LHCb::Particle *seed,
                                            const std::string &head,
                                            Tuples::Tuple &tuple ) 
{ 
  const std::string prefix = fullName( head );
  if ( msgLevel(MSG::DEBUG) ) debug() << "==> Fill" << endmsg;
  // -- The vector m_decayParticles contains all the particles that belong to the given decay
  // -- according to the decay descriptor.
  // -- Clear the vector with the particles in the specific decay
  m_decayParticles.clear();
 
  // -- Add the mother (prefix of the decay chain) to the vector
  if ( msgLevel(MSG::DEBUG) ) debug() << "Filling particle with ID " << top->particleID().pid() << endmsg;
  m_decayParticles.push_back( top );
  // -- Save all particles that belo
  saveDecayParticles( top );
  // -- Get all charged particles in the event
  LHCb::Particles *parts = get<LHCb::Particles>( "Phys/" + m_extraParticlesLocation + "/Particles" );
  if ( parts->size() == 0 ){
    if ( msgLevel(MSG::WARNING) ) warning() << "Could not retrieve extra-particles. Skipping" << endmsg;
    return StatusCode::FAILURE;   
  }

  // -- Get all the photons particles in the event
  LHCb::Particles *photons = NULL;
  if(msgLevel(MSG::DEBUG)) debug() << "Going to retrive photons" << endmsg;
  if(exist<LHCb::Particles>( "Phys/" + m_extraPhotonsLocation + "/Particles" )) photons = get<LHCb::Particles>( "Phys/" + m_extraPhotonsLocation + "/Particles" );
  if(!photons){
    if(msgLevel(MSG::WARNING)) warning() << "No container available in " << m_extraPhotonsLocation << endmsg;
    return StatusCode::SUCCESS;
  } 
  if(msgLevel(MSG::DEBUG)) debug()<< "Got the photons" << endmsg;

  // -- Get all the pi0s particles in the event
  LHCb::Particles *pi0s = NULL;
  if(msgLevel(MSG::DEBUG)) debug() << "Going to retrive pi0s" << endmsg;
  if(exist<LHCb::Particles>( "Phys/" + m_extraPi0sLocation + "/Particles" )) pi0s = get<LHCb::Particles>( "Phys/" + m_extraPi0sLocation + "/Particles" );
  if(!pi0s){
    if(msgLevel(MSG::WARNING)) warning() << "No container available in " << m_extraPi0sLocation << endmsg;
    return StatusCode::SUCCESS;
  }
  if(msgLevel(MSG::DEBUG)) debug()<< "Got the pi0s" << endmsg; 

  bool test = true;
  
  if ( seed ) {
    if ( msgLevel(MSG::VERBOSE) ) verbose() << "Start looping through different conesizes" << endmsg;
    // -- Loop over the different conesizes
    double coneSize = m_minConeRadius;
    while ( coneSize <= m_maxConeRadius ) {
      if ( msgLevel(MSG::VERBOSE) ) verbose() << "Filling variables with conesize " << coneSize << endmsg;
      // -- Convert the conesize to a string
      char coneNumber[4];
      sprintf(coneNumber, "%.2f", coneSize);
      std::string conesize(coneNumber);
      // -- Retrieve information in the charged cone
      int multiplicity = 0;
      std::vector < double > vectorP;
      double scalarPt = 0.;
      int maximumPt_Q = 0.;
      double maximumPt_PX = 0.;
      double maximumPt_PY = 0.;
      double maximumPt_PZ = 0.;
      double maximumPt_PE = 0.;
      StatusCode sc = ChargedCone( seed, parts, coneSize, multiplicity, vectorP, scalarPt, maximumPt_Q, maximumPt_PX, maximumPt_PY, maximumPt_PZ, maximumPt_PE );
      if ( sc.isFailure() ) multiplicity = -1;
 
      // -- Create a vector with the summed momentum of all tracks in the cone
      Gaudi::XYZVector coneMomentum;
      coneMomentum.SetX( vectorP[0] );
      coneMomentum.SetY( vectorP[1] );
      coneMomentum.SetZ( vectorP[2] );
    
      // -- Fill the tuple with the variables
      test &= tuple->column( prefix + "_" + conesize + "_cc_mult", multiplicity);  
      if (m_fillComponents) {
        test &= tuple->column( prefix + "_" + conesize + "_cc_PX", coneMomentum.X() ); 
        test &= tuple->column( prefix + "_" + conesize + "_cc_PY", coneMomentum.Y() ) ;
        test &= tuple->column( prefix + "_" + conesize + "_cc_PZ", coneMomentum.Z() );
      }
      test &= tuple->column( prefix + "_" + conesize + "_cc_vPT", sqrt( coneMomentum.Perp2() ) );
      test &= tuple->column( prefix + "_" + conesize + "_cc_sPT", scalarPt );
      if ( coneSize == 0. ) {
        test &= tuple->column( prefix + "_" + conesize + "_cc_maxPt_Q", maximumPt_Q ); 
        test &= tuple->column( prefix + "_" + conesize + "_cc_maxPt_PT", sqrt( pow(maximumPt_PX, 2) + pow(maximumPt_PY, 2) ) );
        if (m_fillComponents) {
          test &= tuple->column( prefix + "_" + conesize + "_cc_maxPt_PX", maximumPt_PX ); 
          test &= tuple->column( prefix + "_" + conesize + "_cc_maxPt_PY", maximumPt_PY );
          test &= tuple->column( prefix + "_" + conesize + "_cc_maxPt_PZ", maximumPt_PZ );
          test &= tuple->column( prefix + "_" + conesize + "_cc_maxPt_PE", maximumPt_PE );
        }
      }

      // -- Retrieve information in the photon cone
      int gmultiplicity = 0;
      std::vector < double > gvectorP;
      double gscalarPt = 0.;
      double gmaximumPt_PX = 0.;
      double gmaximumPt_PY = 0.;
      double gmaximumPt_PZ = 0.;
      double gmaximumPt_PE = 0.;
      double gsecondPt_PX = 0.;
      double gsecondPt_PY = 0.;
      double gsecondPt_PZ = 0.;
      double gsecondPt_PE = 0.;
      double gthirdPt_PX = 0.;
      double gthirdPt_PY = 0.;
      double gthirdPt_PZ = 0.; 
      double gthirdPt_PE = 0.;
      double gCL = 0.;
      double gshape = 0.;
      double gmatch = 0.;
      double gpid = 0.;
      double gcnv = 0.;
      double gprs = 0.;
      double gmaximumPt_TRUEPX = 0.;
      double gmaximumPt_TRUEPY = 0.;
      double gmaximumPt_TRUEPZ = 0.;
      double gmaximumPt_TRUEPE = 0.;
      double gsecondPt_TRUEPX = 0.;
      double gsecondPt_TRUEPY = 0.;
      double gsecondPt_TRUEPZ = 0.;
      double gsecondPt_TRUEPE = 0.;
      double gthirdPt_TRUEPX = 0.;
      double gthirdPt_TRUEPY = 0.;
      double gthirdPt_TRUEPZ = 0.;
      double gthirdPt_TRUEPE = 0.; 

      // neutral cone with photons
      StatusCode nscgamma = PhotonCone( seed, photons, coneSize, gmultiplicity, gvectorP, gscalarPt, gmaximumPt_PX, gmaximumPt_PY, gmaximumPt_PZ, gmaximumPt_PE, gsecondPt_PX, gsecondPt_PY, gsecondPt_PZ, gsecondPt_PE, gthirdPt_PX, gthirdPt_PY, gthirdPt_PZ, gthirdPt_PE, gCL, gshape, gmatch, gpid, gcnv, gprs ); 
      if ( nscgamma.isFailure() ) gmultiplicity = -1;
      StatusCode nscgammaMC = false;
      if ( m_isMC ) {
        StatusCode nscgammaMC = PhotonConeMC( seed, photons, coneSize, gmaximumPt_TRUEPX, gmaximumPt_TRUEPY, gmaximumPt_TRUEPZ, gmaximumPt_TRUEPE, gsecondPt_TRUEPX, gsecondPt_TRUEPY, gsecondPt_TRUEPZ, gsecondPt_TRUEPE, gthirdPt_TRUEPX, gthirdPt_TRUEPY, gthirdPt_TRUEPZ, gthirdPt_TRUEPE );  
      }
      
      // -- Create a vector with the summed momentum of all photons in the cone
      Gaudi::XYZVector gConeMomentum;
      gConeMomentum.SetX( gvectorP[0] );
      gConeMomentum.SetY( gvectorP[1] );
      gConeMomentum.SetZ( gvectorP[2] );

      // -- Fill the tuple with the photon variables
      test &= tuple->column( prefix + "_" + conesize + "_nc_mult", gmultiplicity);
      test &= tuple->column( prefix + "_" + conesize + "_nc_vPT", sqrt( gConeMomentum.Perp2() ) );
      test &= tuple->column( prefix + "_" + conesize + "_nc_sPT", gscalarPt );
      if (m_fillComponents) {
        test &= tuple->column( prefix + "_" + conesize + "_nc_PX", gConeMomentum.X() );
        test &= tuple->column( prefix + "_" + conesize + "_nc_PY", gConeMomentum.Y() );
        test &= tuple->column( prefix + "_" + conesize + "_nc_PZ", gConeMomentum.Z() );   
        test &= tuple->column( prefix + "_" + conesize + "_nc_maxPt_PT", sqrt( pow(gmaximumPt_PX, 2) + pow(gmaximumPt_PY, 2) ) );
        test &= tuple->column( prefix + "_" + conesize + "_nc_maxPt_PX", gmaximumPt_PX );
        test &= tuple->column( prefix + "_" + conesize + "_nc_maxPt_PY", gmaximumPt_PY );
        test &= tuple->column( prefix + "_" + conesize + "_nc_maxPt_PZ", gmaximumPt_PZ );
        test &= tuple->column( prefix + "_" + conesize + "_nc_maxPt_PE", gmaximumPt_PE );
        test &= tuple->column( prefix + "_" + conesize + "_nc_secPt_PX", gsecondPt_PX );
        test &= tuple->column( prefix + "_" + conesize + "_nc_secPt_PY", gsecondPt_PY );
        test &= tuple->column( prefix + "_" + conesize + "_nc_secPt_PZ", gsecondPt_PZ );
        test &= tuple->column( prefix + "_" + conesize + "_nc_secPt_PE", gsecondPt_PE );
        test &= tuple->column( prefix + "_" + conesize + "_nc_thiPt_PX", gthirdPt_PX );
        test &= tuple->column( prefix + "_" + conesize + "_nc_thiPt_PY", gthirdPt_PY );
        test &= tuple->column( prefix + "_" + conesize + "_nc_thiPt_PZ", gthirdPt_PZ );
        test &= tuple->column( prefix + "_" + conesize + "_nc_thiPt_PE", gthirdPt_PE );
        test &= tuple->column( prefix + "_" + conesize + "_nc_CL", gCL );
        test &= tuple->column( prefix + "_" + conesize + "_nc_Shape", gshape );
        test &= tuple->column( prefix + "_" + conesize + "_nc_Match", gmatch );
        test &= tuple->column( prefix + "_" + conesize + "_nc_PID", gpid );
        test &= tuple->column( prefix + "_" + conesize + "_nc_CNV", gcnv );
        test &= tuple->column( prefix + "_" + conesize + "_nc_PRS", gprs );
        if (m_isMC){
          test &= tuple->column( prefix + "_" + conesize + "_nc_MCmaxPt_PX", gmaximumPt_TRUEPX );
          test &= tuple->column( prefix + "_" + conesize + "_nc_MCmaxPt_PY", gmaximumPt_TRUEPY );
          test &= tuple->column( prefix + "_" + conesize + "_nc_MCmaxPt_PZ", gmaximumPt_TRUEPZ );
          test &= tuple->column( prefix + "_" + conesize + "_nc_MCmaxPt_PE", gmaximumPt_TRUEPE );
          test &= tuple->column( prefix + "_" + conesize + "_nc_MCsecPt_PX", gsecondPt_TRUEPX );
          test &= tuple->column( prefix + "_" + conesize + "_nc_MCsecPt_PY", gsecondPt_TRUEPY );
          test &= tuple->column( prefix + "_" + conesize + "_nc_MCsecPt_PZ", gsecondPt_TRUEPZ );
          test &= tuple->column( prefix + "_" + conesize + "_nc_MCsecPt_PE", gsecondPt_TRUEPE );
          test &= tuple->column( prefix + "_" + conesize + "_nc_MCthiPt_PX", gthirdPt_TRUEPX );
          test &= tuple->column( prefix + "_" + conesize + "_nc_MCthiPt_PY", gthirdPt_TRUEPY );
          test &= tuple->column( prefix + "_" + conesize + "_nc_MCthiPt_PZ", gthirdPt_TRUEPZ );
          test &= tuple->column( prefix + "_" + conesize + "_nc_MCthiPt_PE", gthirdPt_TRUEPE ); 
        }
      }

      // retrieve information in the pi0 cone
      int pi0multiplicity = 0;
      std::vector<double> pi0vectorP;
      double pi0scalarPt = 0.;
      double pi0maximumPt_PX = 0.;
      double pi0maximumPt_PY = 0.;
      double pi0maximumPt_PZ = 0.;
      double pi0maximumPt_MM = 0.;
      double pi0maximumPt_PE = 0.;
      double pi0secondPt_PX = 0.;
      double pi0secondPt_PY = 0.;
      double pi0secondPt_PZ = 0.;
      double pi0secondPt_MM = 0.;
      double pi0secondPt_PE = 0.;
      double pi0thirdPt_PX = 0.;
      double pi0thirdPt_PY = 0.;
      double pi0thirdPt_PZ = 0.;
      double pi0thirdPt_MM = 0.;
      double pi0thirdPt_PE = 0.;
      double pi0CL = 0.;
      double g1CL = 0.;
      double g2CL = 0.;
      double g1maxPt_PX = 0.;
      double g1maxPt_PY = 0.;
      double g1maxPt_PZ = 0.;
      double g2maxPt_PX = 0.;
      double g2maxPt_PY = 0.;
      double g2maxPt_PZ = 0.;

      // neutral cone with pi0s
      StatusCode nscpi0 = Pi0Cone( seed, pi0s, coneSize, pi0multiplicity, pi0vectorP, pi0scalarPt, pi0maximumPt_PX, pi0maximumPt_PY, pi0maximumPt_PZ, pi0maximumPt_MM, pi0maximumPt_PE, pi0secondPt_PX, pi0secondPt_PY, pi0secondPt_PZ, pi0secondPt_MM, pi0secondPt_PE, pi0thirdPt_PX, pi0thirdPt_PY, pi0thirdPt_PZ, pi0thirdPt_MM, pi0thirdPt_PE, pi0CL, g1CL, g2CL, g1maxPt_PX, g1maxPt_PY, g1maxPt_PZ, g2maxPt_PX, g2maxPt_PY, g2maxPt_PZ);
      if ( nscpi0.isFailure() ) pi0multiplicity = -1;

      // -- Create a vector with the summed momentum of all photons in the cone
      Gaudi::XYZVector pi0ConeMomentum;
      pi0ConeMomentum.SetX( pi0vectorP[0] );
      pi0ConeMomentum.SetY( pi0vectorP[1] );
      pi0ConeMomentum.SetZ( pi0vectorP[2] ); 
 
      // -- Fill the tuple with the photon variables
      test &= tuple->column( prefix + "_" + conesize + "_pi0_mult", pi0multiplicity);
      test &= tuple->column( prefix + "_" + conesize + "_pi0_vPT", sqrt( pi0ConeMomentum.Perp2() ) );
      test &= tuple->column( prefix + "_" + conesize + "_pi0_sPT", pi0scalarPt );
      if (m_fillComponents) {
        if(msgLevel(MSG::DEBUG)) debug() << "Filling for pi0" << endmsg;
        test &= tuple->column( prefix + "_" + conesize + "_pi0_PX", pi0ConeMomentum.X() );
        test &= tuple->column( prefix + "_" + conesize + "_pi0_PY", pi0ConeMomentum.Y() );
        test &= tuple->column( prefix + "_" + conesize + "_pi0_PZ", pi0ConeMomentum.Z() );
        test &= tuple->column( prefix + "_" + conesize + "_pi0_maxPt_PT", sqrt( pow(pi0maximumPt_PX, 2) + pow(pi0maximumPt_PY, 2) ) );
        test &= tuple->column( prefix + "_" + conesize + "_pi0_maxPt_PX", pi0maximumPt_PX );
        test &= tuple->column( prefix + "_" + conesize + "_pi0_maxPt_PY", pi0maximumPt_PY );
        test &= tuple->column( prefix + "_" + conesize + "_pi0_maxPt_PZ", pi0maximumPt_PZ );
        test &= tuple->column( prefix + "_" + conesize + "_pi0_maxPt_MM", pi0maximumPt_MM );
        test &= tuple->column( prefix + "_" + conesize + "_pi0_maxPt_PE", pi0maximumPt_PE );
        test &= tuple->column( prefix + "_" + conesize + "_pi0_secPt_PX", pi0secondPt_PX );
        test &= tuple->column( prefix + "_" + conesize + "_pi0_secPt_PY", pi0secondPt_PY );
        test &= tuple->column( prefix + "_" + conesize + "_pi0_secPt_PZ", pi0secondPt_PZ );
        test &= tuple->column( prefix + "_" + conesize + "_pi0_secPt_MM", pi0secondPt_MM );
        test &= tuple->column( prefix + "_" + conesize + "_pi0_secPt_PE", pi0secondPt_PE );
        test &= tuple->column( prefix + "_" + conesize + "_pi0_thiPt_PX", pi0thirdPt_PX );
        test &= tuple->column( prefix + "_" + conesize + "_pi0_thiPt_PY", pi0thirdPt_PY );
        test &= tuple->column( prefix + "_" + conesize + "_pi0_thiPt_PZ", pi0thirdPt_PZ );
        test &= tuple->column( prefix + "_" + conesize + "_pi0_thiPt_MM", pi0thirdPt_MM );
        test &= tuple->column( prefix + "_" + conesize + "_pi0_thiPt_PE", pi0thirdPt_PE );
        test &= tuple->column( prefix + "_" + conesize + "_pi0_CL", pi0CL );
        test &= tuple->column( prefix + "_" + conesize + "_g1_CL", g1CL );
        test &= tuple->column( prefix + "_" + conesize + "_g2_CL", g2CL );
        test &= tuple->column( prefix + "_" + conesize + "_g1maxPt_PX", g1maxPt_PX );
        test &= tuple->column( prefix + "_" + conesize + "_g1maxPt_PY", g1maxPt_PY );
        test &= tuple->column( prefix + "_" + conesize + "_g1maxPt_PZ", g1maxPt_PZ );
        test &= tuple->column( prefix + "_" + conesize + "_g2maxPt_PX", g2maxPt_PX );
        test &= tuple->column( prefix + "_" + conesize + "_g2maxPt_PY", g2maxPt_PY );
        test &= tuple->column( prefix + "_" + conesize + "_g2maxPt_PZ", g2maxPt_PZ );
      }

      // retrieve information in the pi0-gamma cone
      int trigmultiplicity = 0;
      std::vector<double> trigvectorP;
      double trigscalarPt = 0.;
      double trigmaximumPt_PX = 0.;
      double trigmaximumPt_PY = 0.;
      double trigmaximumPt_PZ = 0.;
      double trigmaximumPt_MM = 0.;
      double trigsecondPt_PX = 0.;
      double trigsecondPt_PY = 0.;
      double trigsecondPt_PZ = 0.;
      double trigsecondPt_MM = 0.;
      double trigthirdPt_PX = 0.;
      double trigthirdPt_PY = 0.;
      double trigthirdPt_PZ = 0.;
      double trigthirdPt_MM = 0.;
      double fCL = 0.;
      double sCL = 0.;
      double tCL = 0.;
      double fmaxPt_PX = 0.;
      double fmaxPt_PY = 0.;
      double fmaxPt_PZ = 0.;
      double smaxPt_PX = 0.;
      double smaxPt_PY = 0.;
      double smaxPt_PZ = 0.; 
      double tmaxPt_PX = 0.;
      double tmaxPt_PY = 0.;
      double tmaxPt_PZ = 0.;    

      // TriPhoton cone
      StatusCode nsc3g = TriGCone( seed, pi0s, photons, coneSize, trigmultiplicity, trigvectorP, trigscalarPt, trigmaximumPt_PX, trigmaximumPt_PY, trigmaximumPt_PZ, trigmaximumPt_MM, trigsecondPt_PX, trigsecondPt_PY, trigsecondPt_PZ, trigsecondPt_MM, trigthirdPt_PX, trigthirdPt_PY, trigthirdPt_PZ, trigthirdPt_MM, fCL, sCL, tCL, fmaxPt_PX, fmaxPt_PY, fmaxPt_PZ, smaxPt_PX, smaxPt_PY, smaxPt_PZ, tmaxPt_PX, tmaxPt_PY, tmaxPt_PZ);
      if ( nsc3g.isFailure() ) trigmultiplicity = -1;
   
      // -- Create a vector with the summed momentum of all photons in the cone
      Gaudi::XYZVector trigConeMomentum;
      pi0ConeMomentum.SetX( trigvectorP[0] );
      pi0ConeMomentum.SetY( trigvectorP[1] );
      pi0ConeMomentum.SetZ( trigvectorP[2] );

      // -- Fill the tuple with the photon variables
      test &= tuple->column( prefix + "_" + conesize + "_trig_mult", trigmultiplicity);
      test &= tuple->column( prefix + "_" + conesize + "_trig_vPT", sqrt( trigConeMomentum.Perp2() ) );
      test &= tuple->column( prefix + "_" + conesize + "_trig_sPT", trigscalarPt ); 

      if (m_fillComponents) {
        if(msgLevel(MSG::DEBUG)) debug() << "Filling for trigamma" << endmsg;
        test &= tuple->column( prefix + "_" + conesize + "_trig_PX", trigConeMomentum.X() );
        test &= tuple->column( prefix + "_" + conesize + "_trig_PY", trigConeMomentum.Y() );
        test &= tuple->column( prefix + "_" + conesize + "_trig_PZ", trigConeMomentum.Z() );
        test &= tuple->column( prefix + "_" + conesize + "_trig_maxPt_PT", sqrt( pow(trigmaximumPt_PX, 2) + pow(trigmaximumPt_PY, 2) ) );
        test &= tuple->column( prefix + "_" + conesize + "_trig_maxPt_PX", trigmaximumPt_PX );
        test &= tuple->column( prefix + "_" + conesize + "_trig_maxPt_PY", trigmaximumPt_PY );
        test &= tuple->column( prefix + "_" + conesize + "_trig_maxPt_PZ", trigmaximumPt_PZ );
        test &= tuple->column( prefix + "_" + conesize + "_trig_maxPt_MM", trigmaximumPt_MM );
        test &= tuple->column( prefix + "_" + conesize + "_trig_secPt_PX", trigsecondPt_PX );
        test &= tuple->column( prefix + "_" + conesize + "_trig_secPt_PY", trigsecondPt_PY );
        test &= tuple->column( prefix + "_" + conesize + "_trig_secPt_PZ", trigsecondPt_PZ );
        test &= tuple->column( prefix + "_" + conesize + "_trig_secPt_MM", trigsecondPt_MM );
        test &= tuple->column( prefix + "_" + conesize + "_trig_thiPt_PX", trigthirdPt_PX );
        test &= tuple->column( prefix + "_" + conesize + "_trig_thiPt_PY", trigthirdPt_PY );
        test &= tuple->column( prefix + "_" + conesize + "_trig_thiPt_PZ", trigthirdPt_PZ );
        test &= tuple->column( prefix + "_" + conesize + "_trig_thiPt_MM", trigthirdPt_MM );
        test &= tuple->column( prefix + "_" + conesize + "_fCL", fCL );
        test &= tuple->column( prefix + "_" + conesize + "_sCL", sCL );
        test &= tuple->column( prefix + "_" + conesize + "_tCL", tCL );
        test &= tuple->column( prefix + "_" + conesize + "_fmaxPt_PX", fmaxPt_PX );
        test &= tuple->column( prefix + "_" + conesize + "_fmaxPt_PY", fmaxPt_PY );
        test &= tuple->column( prefix + "_" + conesize + "_fmaxPt_PZ", fmaxPt_PZ );
        test &= tuple->column( prefix + "_" + conesize + "_smaxPt_PX", smaxPt_PX );
        test &= tuple->column( prefix + "_" + conesize + "_smaxPt_PY", smaxPt_PY );
        test &= tuple->column( prefix + "_" + conesize + "_smaxPt_PZ", smaxPt_PZ );
        test &= tuple->column( prefix + "_" + conesize + "_tmaxPt_PX", tmaxPt_PX );
        test &= tuple->column( prefix + "_" + conesize + "_tmaxPt_PY", tmaxPt_PY );
        test &= tuple->column( prefix + "_" + conesize + "_tmaxPt_PZ", tmaxPt_PZ );
      }


      // -- Increase the counter with the stepsize
      coneSize += m_coneStepSize;
    }
  }
  else {
    if ( msgLevel(MSG::WARNING) ) warning() << "The seed particle is not valid. Skipping" << endmsg;
    return StatusCode::FAILURE; 
  }
  if ( msgLevel(MSG::VERBOSE) ) verbose() << "Stop looping through different conesizes" << endmsg;
  return StatusCode( test );
}
 
//=============================================================================
// Save the particles in the decay chain (recursive function)
//=============================================================================
void TupleToolEWTrackIsolation::saveDecayParticles( const LHCb::Particle *top ) {

  // -- Get the daughters of the top particle
  const SmartRefVector< LHCb::Particle > daughters = top->daughters();
    
  // -- Fill all the daugthers in m_decayParticles
  for ( SmartRefVector< LHCb::Particle >::const_iterator ip = daughters.begin(); ip != daughters.end(); ++ip ) {
    // -- If the particle is stable, save it in the vector, or...
    if ( (*ip)->isBasicParticle() ) {
      if ( msgLevel(MSG::DEBUG) ) debug() << "Filling particle with ID " << (*ip)->particleID().pid() << endmsg;
      m_decayParticles.push_back( (*ip) );
    }
    else {
      // -- if it is not stable, call the function recursively
      m_decayParticles.push_back( (*ip) );
      if ( msgLevel(MSG::DEBUG) ) debug() << "Filling particle with ID " << (*ip)->particleID().pid() << endmsg;
      saveDecayParticles( (*ip) );
    }
  }
  return;
}
 
//=============================================================================
// Loop over all the tracks in the cone which do not belong to the desired decay
//=============================================================================
StatusCode TupleToolEWTrackIsolation::ChargedCone( const LHCb::Particle *seed,
                                                   const LHCb::Particles *parts,
                                                   const double rcut,
                                                   int &mult,
                                                   std::vector < double > &vP,
                                                   double &sPt,
                                                   int &maxPt_Q, double &maxPt_PX, double &maxPt_PY, double &maxPt_PZ, double &maxPt_PE ) 
{

  // -- Initialize values
  mult = 0;
  double sPx = 0.;
  double sPy = 0.;
  double sPz = 0.;
  sPt = 0.;
  maxPt_Q = 0;
  maxPt_PX = 0.;
  maxPt_PY = 0.;
  maxPt_PZ = 0.;
  maxPt_PE = 0.;
 
  // -- Get the 4-momentum of the seed particle
  Gaudi::LorentzVector seedMomentum = seed->momentum();
 
  for ( LHCb::Particles::const_iterator ip = parts->begin(); ip != parts->end(); ++ip ) {
    const LHCb::Particle *particle = (*ip);
    const LHCb::ProtoParticle *proto = particle->proto();
    if ( proto ) {
      const LHCb::Track *track = proto->track();
      if ( track ) {
        // -- Check if the track belongs to the decay itself
        bool isInDecay = isTrackInDecay( track );
        if ( isInDecay ) continue;
        // -- Get the 3-momentum of the track
        Gaudi::XYZVector trackMomentum = track->momentum();
        //-- Calculate the difference in Eta and Phi between the seed particle and a track
        double deltaPhi = fabs( seedMomentum.Phi() - trackMomentum.Phi() );
        if ( deltaPhi > M_PI ) deltaPhi = 2 * M_PI - deltaPhi;
        double deltaEta = seedMomentum.Eta() - trackMomentum.Eta();
        double deltaR = sqrt( deltaPhi * deltaPhi + deltaEta * deltaEta );
        if ( track->type() == m_trackType ) {
          if ( ( rcut == 0. ) || ( deltaR <= rcut ) ) {
            // -- Calculate vector information
            sPx += trackMomentum.X();
            sPy += trackMomentum.Y();
            sPz += trackMomentum.Z();
            // -- Calculate scalar information
            sPt += sqrt( trackMomentum.Perp2() );
            mult++;
          }
          if ( ( rcut == 0. ) || ( deltaR <= rcut ) ) {
            // Extra Muon
            double minP = 10.e3;
            if ( track->p() > minP ) {
              const LHCb::MuonPID *muonPID = proto->muonPID();
              if ( muonPID ) {
                if ( muonPID->IsMuon() ) {
                  if ( track->pt() > sqrt(pow(maxPt_PX, 2.) + pow(maxPt_PY, 2.)) ) {
                    maxPt_Q = track->charge();
                    maxPt_PX = track->momentum().X();
                    maxPt_PY = track->momentum().Y();
                    maxPt_PZ = track->momentum().Z();
                    maxPt_PE = particle->momentum().E();
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  vP.push_back( sPx );
  vP.push_back( sPy );
  vP.push_back( sPz );
 
  return StatusCode::SUCCESS;
 
}
 
//=============================================================================
// Loop over all the photons in the cone
//=============================================================================
StatusCode TupleToolEWTrackIsolation::PhotonCone( const LHCb::Particle *seed,
                                                   const LHCb::Particles *photons,
                                                   const double rcut,
                                                   int &mult,
                                                   std::vector < double > &vP,
                                                   double &sPt,
                                                   double &maxPt_PX, double &maxPt_PY, double &maxPt_PZ, double &maxPt_PE,
                                                   double &secPt_PX, double &secPt_PY, double &secPt_PZ, double &secPt_PE,
                                                   double &thiPt_PX, double &thiPt_PY, double &thiPt_PZ, double &thiPt_PE,
                                                   double &CL, double &shape, double &match, double &pid,
                                                   double &cnv, double &prs 
    )
{

  // -- Initialize values
  mult = 0;
  double sPx = 0.;
  double sPy = 0.;
  double sPz = 0.;
  sPt = 0.;
  maxPt_PX = 0.;
  maxPt_PY = 0.;
  maxPt_PZ = 0.;
  maxPt_PE = 0.;
  secPt_PX = 0.;
  secPt_PY = 0.;
  secPt_PZ = 0.;
  secPt_PE = 0.;
  thiPt_PX = 0.;
  thiPt_PY = 0.;
  thiPt_PZ = 0.;
  thiPt_PE = 0.;
  CL = 0.;
  shape = 0.;
  match = 0.;
  pid = 0.;
  cnv = 0.;
  prs = 0.;
  // -- Get the 4-momentum of the seed particle
  Gaudi::LorentzVector seedMomentum = seed->momentum();
    
  for ( LHCb::Particles::const_iterator ip = photons->begin(); ip != photons->end(); ++ip ) {
    const LHCb::Particle *photon = (*ip);
    if(msgLevel(MSG::DEBUG)) debug() << "Iterating Photon" << endmsg;
    // -- Get the 3-momentum of the photon
    Gaudi::XYZVector photonMomentum = photon->momentum().Vect();
    // -- Calculate the difference in Eta and Phi between the seed particle and a photons
    double deltaPhi = fabs( seedMomentum.Phi() - photonMomentum.Phi() );
    if ( deltaPhi > M_PI ) deltaPhi = 2 * M_PI - deltaPhi;
    double deltaEta = seedMomentum.Eta() - photonMomentum.Eta();
    double deltaR = sqrt( deltaPhi * deltaPhi + deltaEta * deltaEta );

    const LHCb::ProtoParticle* proto = photon->proto();
    if(NULL == proto)return StatusCode::SUCCESS;

    if ( ( rcut == 0. ) || ( deltaR <= rcut ) ) {
      // -- Calculate vector information
      sPx += photonMomentum.X();
      sPy += photonMomentum.Y();
      sPz += photonMomentum.Z();
      // -- Calculate scalar information
      sPt += sqrt( photonMomentum.Perp2() );
      mult++;
      // Extra Photon
      if ( sqrt( photonMomentum.Perp2() ) > sqrt(pow(maxPt_PX, 2.) + pow(maxPt_PY, 2.)) ) {
        maxPt_PX = photonMomentum.X();
        maxPt_PY = photonMomentum.Y();
        maxPt_PZ = photonMomentum.Z();
        maxPt_PE = photon->momentum().E();  
        CL = photon->confLevel();       
        shape = photon->proto()->info(LHCb::ProtoParticle::ShowerShape, 0.);
        match = proto->info(LHCb::ProtoParticle::CaloTrMatch, 9999.);
        pid = proto->info(LHCb::ProtoParticle::PhotonID, 0.);
        cnv = ( proto->info(LHCb::ProtoParticle::CaloDepositID, 0.)<0) ? 1 : 0;
        prs = proto->info(LHCb::ProtoParticle::CaloNeutralPrs, 0.);
      }
      else if ( sqrt( photonMomentum.Perp2() ) > sqrt(pow(secPt_PX, 2.) + pow(secPt_PY, 2.)) ) {
        secPt_PX = photonMomentum.X();
        secPt_PY = photonMomentum.Y();
        secPt_PZ = photonMomentum.Z();
        secPt_PE = photon->momentum().E();
      }
      else if ( sqrt( photonMomentum.Perp2() ) > sqrt(pow(thiPt_PX, 2.) + pow(thiPt_PY, 2.)) ) {
        thiPt_PX = photonMomentum.X();
        thiPt_PY = photonMomentum.Y();
        thiPt_PZ = photonMomentum.Z();
        thiPt_PE = photon->momentum().E();
      }
    }
  }
  
  vP.push_back( sPx );
  vP.push_back( sPy );
  vP.push_back( sPz );
  return StatusCode::SUCCESS;
}

//=============================================================================
// Loop over all the photons in the cone to get MC info
//=============================================================================
StatusCode TupleToolEWTrackIsolation::PhotonConeMC( const LHCb::Particle *seed,
                                                    const LHCb::Particles *photons,
                                                    const double rcut,
                                                    double &maxPt_PX, double &maxPt_PY, double &maxPt_PZ, double &maxPt_PE,
                                                    double &secPt_PX, double &secPt_PY, double &secPt_PZ, double &secPt_PE,
                                                    double &thiPt_PX, double &thiPt_PY, double &thiPt_PZ, double &thiPt_PE
    )
{
  // -- Initialize values
  maxPt_PX = 0.;
  maxPt_PY = 0.;
  maxPt_PZ = 0.;
  maxPt_PE = 0.;
  secPt_PX = 0.;
  secPt_PY = 0.;
  secPt_PZ = 0.;
  secPt_PE = 0.;
  thiPt_PX = 0.;
  thiPt_PY = 0.;
  thiPt_PZ = 0.;
  thiPt_PE = 0.;
  // -- Get the 4-momentum of the seed particle
  Gaudi::LorentzVector seedMomentum = seed->momentum();

  // Initialize MC photon
  const LHCb::MCParticle *mcphoton = NULL;

  for ( LHCb::Particles::const_iterator ip = photons->begin(); ip != photons->end(); ++ip ) {
    const LHCb::Particle *photon = (*ip);
    if(msgLevel(MSG::DEBUG)) debug() << "Iterating Photon" << endmsg;
    // -- Get the 3-momentum of the photon
    Gaudi::XYZVector photonMomentum = photon->momentum().Vect();
    // -- Calculate the difference in Eta and Phi between the seed particle and a photons
    double deltaPhi = fabs( seedMomentum.Phi() - photonMomentum.Phi() );
    if ( deltaPhi > M_PI ) deltaPhi = 2 * M_PI - deltaPhi;
    double deltaEta = seedMomentum.Eta() - photonMomentum.Eta();
    double deltaR = sqrt( deltaPhi * deltaPhi + deltaEta * deltaEta );

    const LHCb::ProtoParticle* proto = photon->proto();
    if(NULL == proto) return StatusCode::SUCCESS;

    // Associate to MC photon
    for ( std::vector<IParticle2MCAssociator*>::const_iterator iMCAss = m_p2mcAssocs.begin();
          iMCAss != m_p2mcAssocs.end(); ++iMCAss ) {
      mcphoton = (*iMCAss)->relatedMCP(photon);
      if ( !mcphoton ) return StatusCode::SUCCESS;
    }
    if (msgLevel(MSG::VERBOSE)) verbose() << "Got mcphoton " << mcphoton << endmsg ;
 
    Gaudi::XYZVector mcphotonMomentum = mcphoton->momentum().Vect();

    if ( ( rcut == 0. ) || ( deltaR <= rcut ) ) {
      // Extra Photon
      if ( sqrt( photonMomentum.Perp2() ) > sqrt(pow(maxPt_PX, 2.) + pow(maxPt_PY, 2.)) ) {
        maxPt_PX = mcphotonMomentum.X();
        maxPt_PY = mcphotonMomentum.Y();
        maxPt_PZ = mcphotonMomentum.Z();
        maxPt_PE = mcphoton->momentum().E();
      }
      else if ( sqrt( photonMomentum.Perp2() ) > sqrt(pow(secPt_PX, 2.) + pow(secPt_PY, 2.)) ) {
        secPt_PX = mcphotonMomentum.X();
        secPt_PY = mcphotonMomentum.Y();
        secPt_PZ = mcphotonMomentum.Z();
        secPt_PE = mcphoton->momentum().E();
      }
      else if ( sqrt( photonMomentum.Perp2() ) > sqrt(pow(thiPt_PX, 2.) + pow(thiPt_PY, 2.)) ) {
        thiPt_PX = mcphotonMomentum.X();
        thiPt_PY = mcphotonMomentum.Y();
        thiPt_PZ = mcphotonMomentum.Z();
        thiPt_PE = mcphoton->momentum().E();
      }
    }
  }

  return StatusCode::SUCCESS;
}
 
//=============================================================================
// Loop over all the pi0s in the cone
//=============================================================================
StatusCode TupleToolEWTrackIsolation::Pi0Cone( const LHCb::Particle *seed,
                                               const LHCb::Particles *pi0s,
                                               const double rcut,
                                               int &mult,
                                               std::vector < double > &vP,
                                               double &sPt,
                                               double &maxPt_PX, double &maxPt_PY, double &maxPt_PZ, double &maxPt_MM, double &maxPt_PE,
                                               double &secPt_PX, double &secPt_PY, double &secPt_PZ, double &secPt_MM, double &secPt_PE,
                                               double &thiPt_PX, double &thiPt_PY, double &thiPt_PZ, double &thiPt_MM, double &thiPt_PE,
                                               double &CL, double &g1CL, double &g2CL, 
                                               double &g1maxPt_PX, double &g1maxPt_PY, double &g1maxPt_PZ,
                                               double &g2maxPt_PX, double &g2maxPt_PY, double &g2maxPt_PZ 
    )
{

  // -- Initialize values
  mult = 0;
  double sPx = 0.;
  double sPy = 0.;
  double sPz = 0.;
  sPt = 0.;
  maxPt_PX = 0.;
  maxPt_PY = 0.;
  maxPt_PZ = 0.;
  maxPt_MM = 0.;
  maxPt_PE = 0.;
  secPt_PX = 0.;
  secPt_PY = 0.;
  secPt_PZ = 0.;
  secPt_MM = 0.;
  secPt_PE = 0.;
  thiPt_PX = 0.;
  thiPt_PY = 0.;
  thiPt_PZ = 0.;
  thiPt_MM = 0.;
  thiPt_PE = 0.;
  CL = 0.;
  g1CL = 0.;
  g2CL = 0.;
  g1maxPt_PX = 0.;
  g1maxPt_PY = 0.;
  g1maxPt_PZ = 0.;
  g2maxPt_PX = 0.;
  g2maxPt_PY = 0.;
  g2maxPt_PZ = 0.;
  // -- Get the 4-momentum of the seed particle
  Gaudi::LorentzVector seedMomentum = seed->momentum();

  for ( LHCb::Particles::const_iterator ip = pi0s->begin(); ip != pi0s->end(); ++ip ) {
    const LHCb::Particle *pi0 = (*ip);
    if(msgLevel(MSG::DEBUG)) debug() << "Iterating Pi0" << endmsg;
    // -- Get the 3-momentum of the pi0
    Gaudi::XYZVector pi0Momentum = pi0->momentum().Vect();
    // -- Calculate the difference in Eta and Phi between the seed particle and a pi0
    double deltaPhi = fabs( seedMomentum.Phi() - pi0Momentum.Phi() );
    if ( deltaPhi > M_PI ) deltaPhi = 2 * M_PI - deltaPhi;
    double deltaEta = seedMomentum.Eta() - pi0Momentum.Eta();
    double deltaR = sqrt( deltaPhi * deltaPhi + deltaEta * deltaEta );

    if ( ( rcut == 0. ) || ( deltaR <= rcut ) ) {
      // -- Calculate vector information
      sPx += pi0Momentum.X();
      sPy += pi0Momentum.Y();
      sPz += pi0Momentum.Z();
      // -- Calculate scalar information
      sPt += sqrt( pi0Momentum.Perp2() );
      mult++;
    }

    if ( ( rcut == 0. ) || ( deltaR <= rcut ) ) {
      // Extra Photon
      if ( sqrt( pi0Momentum.Perp2() ) > sqrt(pow(maxPt_PX, 2.) + pow(maxPt_PY, 2.)) ) {
        maxPt_PX = pi0Momentum.X();
        maxPt_PY = pi0Momentum.Y();
        maxPt_PZ = pi0Momentum.Z();
        maxPt_MM = pi0->measuredMass();
        maxPt_PE = pi0->momentum().E(); 
        CL = pi0->confLevel();
        if(msgLevel(MSG::DEBUG)) debug() << "Pi0 CL = " << CL << endmsg;
        const SmartRefVector<LHCb::Particle> daughters = pi0->daughters();
        if(msgLevel(MSG::DEBUG)) debug() << "daugters retrieved size = " << daughters.size() << endmsg;
        if(daughters.size()==2){
          g1CL = daughters.at(0)->confLevel();
          g2CL = daughters.at(1)->confLevel();
          if(msgLevel(MSG::DEBUG)) debug() << "CL1 = " << g1CL << ", CL2 = " << g2CL << endmsg;   
          g1maxPt_PX = daughters.at(0)->momentum().Vect().X();
          g1maxPt_PY = daughters.at(0)->momentum().Vect().Y();
          g1maxPt_PZ = daughters.at(0)->momentum().Vect().Z();
          g2maxPt_PX = daughters.at(1)->momentum().Vect().X();
          g2maxPt_PY = daughters.at(1)->momentum().Vect().Y();
          g2maxPt_PZ = daughters.at(1)->momentum().Vect().Z();      
        }
      }
      else if ( sqrt( pi0Momentum.Perp2() ) > sqrt(pow(secPt_PX, 2.) + pow(secPt_PY, 2.)) ) {
        secPt_PX = pi0Momentum.X();
        secPt_PY = pi0Momentum.Y();
        secPt_PZ = pi0Momentum.Z();
        secPt_MM = pi0->measuredMass();
        secPt_PE = pi0->momentum().E();
      }
      else if ( sqrt( pi0Momentum.Perp2() ) > sqrt(pow(thiPt_PX, 2.) + pow(thiPt_PY, 2.)) ) {
        thiPt_PX = pi0Momentum.X();
        thiPt_PY = pi0Momentum.Y();
        thiPt_PZ = pi0Momentum.Z();
        thiPt_MM = pi0->measuredMass();
        thiPt_PE = pi0->momentum().E();
      }
    }
  }

  if(msgLevel(MSG::DEBUG)) debug() << "Variables retrived" << endmsg; 

  vP.push_back( sPx );
  vP.push_back( sPy );
  vP.push_back( sPz );
  return StatusCode::SUCCESS;
}

//=============================================================================
// Loop over all the pi0s and gammas in the cone
//=============================================================================
StatusCode TupleToolEWTrackIsolation::TriGCone( const LHCb::Particle *seed,
                                                const LHCb::Particles *pi0s,
                                                const LHCb::Particles *photons,
                                                const double rcut,
                                                int &mult,
                                                std::vector < double > &vP,
                                                double &sPt,
                                                double &maxPt_PX, double &maxPt_PY, double &maxPt_PZ, double &maxPt_MM,
                                                double &secPt_PX, double &secPt_PY, double &secPt_PZ, double &secPt_MM,
                                                double &thiPt_PX, double &thiPt_PY, double &thiPt_PZ, double &thiPt_MM,
                                                double &fCL, double &sCL, double &tCL,
                                                double &fmaxPt_PX, double &fmaxPt_PY, double &fmaxPt_PZ,
                                                double &smaxPt_PX, double &smaxPt_PY, double &smaxPt_PZ,
                                                double &tmaxPt_PX, double &tmaxPt_PY, double &tmaxPt_PZ
    )
{

  // -- Initialize values
  mult = 0;
  double sPx = 0.;
  double sPy = 0.;
  double sPz = 0.;
  sPt = 0.;
  maxPt_PX = 0.;
  maxPt_PY = 0.;
  maxPt_PZ = 0.;
  maxPt_MM = 0.;
  secPt_PX = 0.;
  secPt_PY = 0.;
  secPt_PZ = 0.;
  secPt_MM = 0.;
  thiPt_PX = 0.;
  thiPt_PY = 0.;
  thiPt_PZ = 0.;
  thiPt_MM = 0.;
  fCL = 0.;
  sCL = 0.;
  tCL = 0.;
  fmaxPt_PX = 0.;
  fmaxPt_PY = 0.;
  fmaxPt_PZ = 0.;
  smaxPt_PX = 0.;
  smaxPt_PY = 0.;
  smaxPt_PZ = 0.;
  tmaxPt_PX = 0.;
  tmaxPt_PY = 0.;
  tmaxPt_PZ = 0.;

  // -- Get the 4-momentum of the seed particle
  Gaudi::LorentzVector seedMomentum = seed->momentum();

  for ( LHCb::Particles::const_iterator ip = pi0s->begin(); ip != pi0s->end(); ++ip ) {
    const LHCb::Particle *pi0 = (*ip);
    if(msgLevel(MSG::DEBUG)) debug() << "Iterating Pi0" << endmsg;
    for ( LHCb::Particles::const_iterator ip = photons->begin(); ip != photons->end(); ++ip ) {
      const LHCb::Particle *photon = (*ip);
      if(msgLevel(MSG::DEBUG)) debug() << "Iterating Photon" << endmsg;
      // -- Get the 3-momentum of the photon
      Gaudi::XYZVector photonMomentum = photon->momentum().Vect();
      // -- Get the 3-momentum of the pi0
      Gaudi::XYZVector pi0Momentum = pi0->momentum().Vect();
      // Build the 3-momentum of the pi0-gamma system
      Gaudi::XYZVector trigMomentum = photonMomentum + pi0Momentum;
      if(msgLevel(MSG::DEBUG)) debug() << "3g = " << trigMomentum.Phi() << ", " << trigMomentum.Eta() <<  endmsg;
      // -- Calculate the difference in Eta and Phi between the seed particle and a pi0
      double deltaPhi = fabs( seedMomentum.Phi() - trigMomentum.Phi() );
      if ( deltaPhi > M_PI ) deltaPhi = 2 * M_PI - deltaPhi;
      double deltaEta = seedMomentum.Eta() - trigMomentum.Eta();
      double deltaR = sqrt( deltaPhi * deltaPhi + deltaEta * deltaEta );

      if ( ( rcut == 0. ) || ( deltaR <= rcut ) ) {
        // -- Calculate vector information
        sPx += trigMomentum.X();
        sPy += trigMomentum.Y();
        sPz += trigMomentum.Z();
        // -- Calculate scalar information
        sPt += sqrt( trigMomentum.Perp2() );
        mult++;
      }
      if ( ( rcut == 0. ) || ( deltaR <= rcut ) ) {
        // Extra Photon
        if ( sqrt( trigMomentum.Perp2() ) > sqrt(pow(maxPt_PX, 2.) + pow(maxPt_PY, 2.)) ) {
          maxPt_PX = trigMomentum.X();
          maxPt_PY = trigMomentum.Y();
          maxPt_PZ = trigMomentum.Z();
          maxPt_MM = pi0->measuredMass();
          tCL = photon->confLevel();
          if(msgLevel(MSG::DEBUG)) debug() << "Single photon CL = " << tCL << endmsg;
          tmaxPt_PX = photon->momentum().Vect().X();
          tmaxPt_PY = photon->momentum().Vect().Y();
          tmaxPt_PZ = photon->momentum().Vect().Z();
          const SmartRefVector<LHCb::Particle> daughters = pi0->daughters();
          if(msgLevel(MSG::DEBUG)) debug() << "daugters retrieved size = " << daughters.size() << endmsg;
          if(daughters.size()==2){
            fCL = daughters.at(0)->confLevel();
            sCL = daughters.at(1)->confLevel();
            if(msgLevel(MSG::DEBUG)) debug() << "CL1 = " << fCL << ", CL2 = " << sCL << endmsg;
            fmaxPt_PX = daughters.at(0)->momentum().Vect().X();
            fmaxPt_PY = daughters.at(0)->momentum().Vect().Y();
            fmaxPt_PZ = daughters.at(0)->momentum().Vect().Z();
            smaxPt_PX = daughters.at(1)->momentum().Vect().X();
            smaxPt_PY = daughters.at(1)->momentum().Vect().Y();
            smaxPt_PZ = daughters.at(1)->momentum().Vect().Z();
          }
        }
        else if ( sqrt( trigMomentum.Perp2() ) > sqrt(pow(secPt_PX, 2.) + pow(secPt_PY, 2.)) ) {
          secPt_PX = trigMomentum.X();
          secPt_PY = trigMomentum.Y();
          secPt_PZ = trigMomentum.Z();
          secPt_MM = pi0->measuredMass();
        }
        else if ( sqrt( trigMomentum.Perp2() ) > sqrt(pow(thiPt_PX, 2.) + pow(thiPt_PY, 2.)) ) {
          thiPt_PX = trigMomentum.X();
          thiPt_PY = trigMomentum.Y();
          thiPt_PZ = trigMomentum.Z();
          thiPt_MM = pi0->measuredMass();
        }
      }
    }
  }

  if(msgLevel(MSG::DEBUG)) debug() << "Triphoton: Variables retrived" << endmsg;

  vP.push_back( sPx );
  vP.push_back( sPy );
  vP.push_back( sPz );
  return StatusCode::SUCCESS;
}

//=============================================================================
// Check if the track is already in the decay
//=============================================================================
bool TupleToolEWTrackIsolation::isTrackInDecay( const LHCb::Track *track ) 
{
  bool isInDecay = false;
  for ( std::vector<const LHCb::Particle*>::iterator ip = m_decayParticles.begin(); ip != m_decayParticles.end(); ++ip ) {
    const LHCb::ProtoParticle *proto = (*ip)->proto();
    if ( proto ) { 
      const LHCb::Track *myTrack = proto->track();
      if ( myTrack ) {
        if ( myTrack == track ) {
          if ( msgLevel( MSG::DEBUG ) ) debug() << "Track is in decay, skipping it" << endmsg;
          isInDecay = true;
        }
      }
    }
  }
  return isInDecay;
}
