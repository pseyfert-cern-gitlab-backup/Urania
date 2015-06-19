// $Id: $
// Include files 

// from Gaudi
#include "GaudiKernel/AlgFactory.h" 
#include "GaudiKernel/ToolFactory.h"

#include "Event/Track.h"
#include "Event/RecSummary.h"

// local
#include "NNToSwim.h"

//-----------------------------------------------------------------------------
// Implementation file for class : NNToSwim
//
// 2012-04-19 : Patrick Koppenburg
//-----------------------------------------------------------------------------

// Declaration of the Algorithm Factory
DECLARE_ALGORITHM_FACTORY( NNToSwim );


//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
NNToSwim::NNToSwim( const std::string& name,
                    ISvcLocator* pSvcLocator)
  : DVAlgorithm ( name , pSvcLocator )
{

  declareProperty("DTFChi2Cut",m_DTF_chi2 = 128) ; // (16*8) very loose
  declareProperty("MMErrCut",m_MMERR_cut = 30) ; // very loose
  declareProperty("NNCut",m_NN_cut = 0.67) ; // tight
  
  // variables 
  m_firstFill = true;
  
  m_dtfc =  0 ; // 9 2nd best
  m_dira =  1 ; // 3 in sigma:  64.5529486
  m_kspt =  2 ;// 20 3rd best
  m_b0me =  3 ; // 7
  m_jipc =  4 ; //11 BEST in sigma: 96
  
  m_b0ta =  5 ; // 2 RINGFENCED in sigma:  1.79424159   -> page 5
  m_bch2 =  6 ; // 4
  m_ipch =    -1 ; // 5 -> behaves strangely
  m_ipnx =  7 ; // 5
  m_bmom =  8 ; // 6
  m_b0pt =  9 ; // 7
  m_b0te = 10 ; // 8
  m_jchi =  -1 ; //10
  m_jfdc = 11 ; // ; //12 -> useless (0.34)
  m_jmas = 12 ; //12
  m_jmme = 13 ; //13
  m_jmom = 14 ; // 13 ; //15 -> useless (0.6)
  m_jppt = 15 ; 
  m_jpsc = 16 ;
  m_ksez = 17 ;// 14
  m_ksta = 18 ;// 21
  m_ksfd = 19 ;// 15
  m_ksch = 20 ;// 16
  m_kipc = 21 ;// 17
  m_ksmm = 22 ;// ; //20 -> Useless (0.16)
  m_ksme = 23 ;// 18
  m_ksmo = 24 ; //19
  m_muic = 25 ;// 22
  m_muip = 26 ; // in sigma:  0.518802103
  m_mumo = 27 ; //23 
  m_mupt = 28 ;// in sigma:  0.962181765
  m_muid = 29 ; //24 
  m_mutk = 30 ;//   in sigma:  0.0157334428
  m_piic = -1 ;// 25
  m_piip = 31 ;// in sigma:  0.363549249
  m_pipt = 32 ;// in sigma:  0.85242892
  m_pigp = 33 ;// 27
  m_pigc = 34 ;// 26
  m_pitk = 35 ;// 28 
  m_prim = 36 ;// 29 ;
  m_spdm = 37 ;// 30 ; 
  m_otcl = 38; // 31 ;
  m_nvar_without_ttype = 39 ; // 31 ;
  m_NNIvar = 5;
  
}
//=============================================================================
// Destructor
//=============================================================================
NNToSwim::~NNToSwim() {} 

//=============================================================================
// Initialization
//=============================================================================
StatusCode NNToSwim::initialize() {
  StatusCode sc = DVAlgorithm::initialize(); 
  if ( sc.isFailure() ) return sc;

  if ( msgLevel(MSG::DEBUG) ) debug() << "==> Initialize" << endmsg;

  return StatusCode::SUCCESS;
}

//=============================================================================
// Main execution
//=============================================================================
StatusCode NNToSwim::execute() {

  if ( msgLevel(MSG::DEBUG) ) debug() << "==> Execute" << endmsg;
  StatusCode sc = StatusCode::SUCCESS;
  // code goes here  
  const int nvar = m_nvar_without_ttype + 1 ;
  float* InputArray = new float[nvar] ;
  LHCb::Particle::Range parts = particles();
  for ( LHCb::Particle::Range::const_iterator p = parts.begin() ; p!=parts.end() ; ++p){
    sc = prepareArray(*p, nvar, InputArray, 0);
    info() << "Call NN here" << endmsg ;
    if (!sc) return sc;
  }
  setFilterPassed(true);  // Mandatory. Set to true if event is accepted. 
  return sc;
}

// ###################################################################
StatusCode NNToSwim::prepareArray(const LHCb::Particle* B, 
                                    const int nvar, 
                                    float* InputArray, 
                                    int ttype){

  // *** Identify Decay Products ***
  LHCb::Particle::ConstVector d = descendants()->descendants(B);
  const LHCb::Particle* KS0 = 0;
  const LHCb::Particle* Jpsi = 0;
  const LHCb::Particle* mup = 0;
  const LHCb::Particle* mum = 0;
  const LHCb::Particle* pip = 0;
  const LHCb::Particle* pim = 0;
  for (LHCb::Particle::ConstVector::const_iterator p=d.begin(); p!=d.end() ; ++p){
    if ((*p)->particleID().pid()==443 ) Jpsi = *p;
    else if ((*p)->particleID().pid()==310 ) KS0 = *p;
    else if ((*p)->particleID().pid()==13 ) mum = *p;
    else if ((*p)->particleID().pid()==-13 ) mup = *p;
    else if ((*p)->particleID().pid()==121 ) pip = *p;
    else if ((*p)->particleID().pid()==-121 ) pim = *p;
    else {
      err() << "I see a " << (*p)->particleID().pid() << endmsg ;
      return StatusCode::FAILURE;
    }
  }
  // *** Identify Tracks ***
  // See: TupleToolTrackInfo
  const LHCb::ProtoParticle* mumProto = mum->proto();
  const LHCb::ProtoParticle* mupProto = mup->proto();
  const LHCb::Track* mumTrack = mumProto->track();
  const LHCb::Track* mupTrack = mupProto->track();
  const LHCb::Track* pimTrack = pim->proto()->track();
  const LHCb::Track* pipTrack = pip->proto()->track();      


  // *** Feed all Observables ***
  //  unsigned int pv = 0 ;
  
// #####
// *** Code snippet from TupleToolDecayTreeFitter ***
// External input: fitter & tMap
/*
  test &= insert( prefix+"_chi2_B", fitter.chiSquare(), tMap  );
*/
// #####
  
//  fillArray(m_dtfc, B_FullFit_chi2_B[pv], "dtfc, B_FullFit_chi2_B", InputArray); // TupleToolDecayTreeFitter
  
// #####
// *** Code snippet from TupleToolGeometry ***
// External input: oriVtx
/*
    const LHCb::Vertex* evtx = P->endVertex();
    Gaudi::XYZVector A = P->momentum().Vect();
    Gaudi::XYZVector B = evtx->position() - oriVtx->position ();
    double cosPFD = A.Dot( B ) / std::sqrt( A.Mag2()*B.Mag2() );
    test &= tuple->column( prefix + "_DIRA"+trail, cosPFD );
*/
// #####
//fillArray(m_dira, acos(B_DIRA_OWNPV) , "dira, acos(B_DIRA_OWNPV)", InputArray); // TupleToolGeometry
  fillArray(m_kspt , KS0->pt(), "kspt, KS0_PT", InputArray); // TupleToolKinematics
  
// #####
// *** Code snippet from TupleToolDecayTreeFitter ***
// External input: fitter & tMap
/*
  const Gaudi::Math::ParticleParams* params = fitter.fitParams(P) ;
  Gaudi::Math::LorentzVectorWithError momentum = params->momentum() ;
  test &= insert( prefix+"_MERR", momentum.m().error(), tMap );
*/
// #####
//fillArray(m_b0me, B_FullFit_MERR[pv], "b0me, B_FullFit_MERR[pv]", InputArray); // TupleToolDecayTreeFitter
  
// #####
// *** Code snippet from TupleToolGeometry ***
// m_dva = Gaudi::Utils::getDVAlgorithm ( contextSvc() ) ;
// m_dist = m_dva->distanceCalculator ();
// m_pvReFitter = tool<IPVReFitter>("AdaptivePVReFitter", this ); 
/*
  double ipmin = -1;
  double minchi2 = -1 ;

  double ipminnextbest = -1;
  double minchi2nextbest = -1;
  if(msgLevel(MSG::VERBOSE)) verbose() << "Looking for Min IP"  << endmsg  ;
  const RecVertex::Range PV = m_dva->primaryVertices();
  if(msgLevel(MSG::VERBOSE)) verbose() << "PV size: "  << PV.size() << endmsg  ;
  if ( !PV.empty() )
  {
    if(msgLevel(MSG::VERBOSE)) verbose() << "Filling IP " << prefix + "_MINIP : "
                                         << P << " PVs:" << PV.size() << endmsg ;

    for ( RecVertex::Range::const_iterator pv = PV.begin() ; pv!=PV.end() ; ++pv)
    {
      RecVertex newPV(**pv);
      if (m_refitPVs)
      {

        StatusCode scfit = m_pvReFitter->remove(P, &newPV);
        if(!scfit) { Warning("ReFitter fails!",StatusCode::SUCCESS,10).ignore(); continue; }
      }

      double ip, chi2;

      LHCb::VertexBase* newPVPtr = (LHCb::VertexBase*)&newPV;
      StatusCode test2 = m_dist->distance ( P, newPVPtr, ip, chi2 );
      if( test2 )
      {
        if ((ip<ipmin) || (ipmin<0.))
        {
          ipminnextbest = ipmin;
          ipmin = ip ;
        }
        else
        {
          if((ip < ipminnextbest) || (ipminnextbest < 0))
          {
            ipminnextbest = ip;
          }
        }

        if ((chi2<minchi2) || (minchi2<0.))
        {
          minchi2nextbest = minchi2;
          minchi2 = chi2 ;
        }
        else
        {
          if((chi2 < minchi2nextbest) || (minchi2nextbest < 0))
          {
            minchi2nextbest = chi2;
          }
        }
      }
    }
  }
*/
//  test &= tuple->column( prefix + "_MINIP", ipmin );
//  test &= tuple->column( prefix + "_MINIPCHI2", minchi2 );
//  test &= tuple->column( prefix + "_MINIPNEXTBEST", ipminnextbest );
//  test &= tuple->column( prefix + "_MINIPCHI2NEXTBEST", minchi2nextbest );
// #####  
// fillArray(m_jipc, Psi_MINIPCHI2, "jipc, Psi_MINIPCHI2", InputArray); // TupleToolGeometry

  if(nvar>m_NNIvar){
// #####
// *** Code snippet from TupleToolDecayTreeFitter ***
// External input: fitter & tMap
/*  
  const Gaudi::Math::ParticleParams* tParams = fitter.fitParams(P);
  Gaudi::Math::ValueWithError ctau = tParams->ctau();
  test &= insert( prefix+"_ctau", ctau.value(), tMap  );
  test &= insert( prefix+"_ctauErr", ctau.error(), tMap  );  
*/
// #####
 // fillArray(m_b0ta, B_FullFit_ctau[pv], "b0ta, B_FullFit_ctau[pv]", InputArray); // TupleToolDecayTreeFitter
    fillArray(m_bch2, B->endVertex()->chi2()/B->endVertex()->nDoF(), "bch2, B_ENDVERTEX_CHI2/B_ENDVERTEX_NDOF", InputArray);
    // TupleToolGeometry
    
// #####
// *** Code snippet from TupleToolGeometry ***
// External input: primVtx
// m_dva = Gaudi::Utils::getDVAlgorithm ( contextSvc() ) ;
// m_dist = m_dva->distanceCalculator ();
/*
    test &= m_dist->distance ( P, primVtx, ip, chi2 );
    test &= tuple->column( prefix + "_IP"+trail, ip );
    test &= tuple->column( prefix + "_IPCHI2"+trail, chi2 );
*/
// #####
 // fillArray(m_ipch, B_IPCHI2_OWNPV , "ipch, B_IPCHI2_OWNPV", InputArray); // TupleToolGeometry
 // fillArray(m_ipnx, ( (B_MINIPCHI2NEXTBEST>=0) ? B_MINIPCHI2NEXTBEST : -999.) , "ipnx, B_MINIPCHI2NEXTBEST", InputArray);
 // TupleToolGeometry
    fillArray(m_bmom, B->p(), "bmom, B_P", InputArray); // TupleToolKinematics
    fillArray(m_b0pt, B->pt(), "b0pt, B_PT", InputArray); // TupleToolKinematics
 // fillArray(m_b0te, B_FullFit_ctauErr[pv], "b0te, B_FullFit_ctauErr[pv]", InputArray); // TupleToolDecayTreeFitter
    fillArray(m_jchi, Jpsi->endVertex()->chi2(), "jchi, Psi_ENDVERTEX_CHI2", InputArray); // TupleToolGeometry

// #####
// *** Code snippet from TupleToolGeometry ***
// External input: oriVtx
// m_dva = Gaudi::Utils::getDVAlgorithm ( contextSvc() ) ;
// m_dist = m_dva->distanceCalculator ();
/*
    double dist = 0;
    double chi2 = 0 ;
    StatusCode sc = m_dist->distance( oriVtx, P->endVertex(), dist, chi2 );
    test &= tuple->column( prefix + "_FD"+trail, dist );
    test &= tuple->column( prefix + "_FDCHI2"+trail, chi2 );
*/
// #####
 // fillArray(m_jfdc, Psi_FDCHI2_ORIVX, "jfdc, Psi_FDCHI2_ORIVX", InputArray); // TupleToolGeometry
    fillArray(m_jmas , fabs(Jpsi->measuredMass()-m_JpsiFittedMass), "jmas, Psi_MM-fitted", InputArray); // TupleToolKinematics
    fillArray(m_jmme , Jpsi->measuredMassErr(), "jmme, Psi_MMERR", InputArray); // TupleToolKinematics
    fillArray(m_jmom, Jpsi->p(), "jmom, Psi_P", InputArray); // TupleToolKinematics
    fillArray(m_jppt, Jpsi->pt() , "jppt, Psi_PT", InputArray); // TupleToolKinematics
    
// #####
// *** Code snippet from TupleToolVtxIsoln ***
/*
  const LHCb::Vertex* vtx;
  if (P->isBasicParticle() || isPureNeutralCalo(P) ){
    vtx = mother->endVertex();
  }
  else{
    vtx = P->endVertex();
  }
  double vtxChi2 = vtx->chi2();
  LHCb::Particle::ConstVector theParts;
  // More code including "theParts": Line 163 to 221
  LHCb::Particle::ConstVector parts2Vertex;
  parts2Vertex.clear();
  if (P->isBasicParticle()){
    parts2Vertex.push_back(P);
  }
  else{
    parts2Vertex = P->daughtersVector();
  }
  double smallestDeltaChi2 = -1 ;
  for(LHCb::Particle::ConstVector::const_iterator iparts = theParts.begin();
      iparts != theParts.end(); ++iparts){
    StatusCode sc = StatusCode::SUCCESS;
    LHCb::Vertex vtxWithExtraTrack;
    parts2Vertex.push_back(*iparts);
    sc = m_pVertexFit->fit (vtxWithExtraTrack,parts2Vertex);
    double dChi2 = vtxWithExtraTrack.chi2() - vtxChi2 ;
    if ( smallestDeltaChi2 < 0 || smallestDeltaChi2 > dChi2)  smallestDeltaChi2 = dChi2;
  }
  tuple->column( prefix + "_SMALLESTDELTACHI2",  smallestDeltaChi2 );
*/
// #####
 // fillArray(m_jpsc, ( (Psi_SMALLESTDELTACHI2>-0.5) ? Psi_SMALLESTDELTACHI2 : -999.), "jpsc, Psi_SMALLESTDELTACHI2", InputArray ) ;
    // TupleToolVtxIsoln

    fillArray(m_ksez, KS0->endVertex()->position().Z(), "ksez, KS0_ENDVERTEX_Z", InputArray); // TupleToolGeometry   
 // fillArray(m_ksta , B_FullFit_KS0_ctau[pv] , "ksta, B_FullFit_KS0_ctau[pv]", InputArray); // TupleToolDecayTreeFitter
 // fillArray(m_ksfd, B_FullFit_KS0_ctau[pv]/B_FullFit_KS0_ctauErr[pv], "ksfd,
       //"B_FullFit_KS0_ctau[pv]/B_FullFit_KS0_ctauErr[pv]", InputArray); // TupleToolDecayTreeFitter
    fillArray(m_ksch, KS0->endVertex()->chi2(), "ksch, KS0_ENDVERTEX_CHI2", InputArray); // TupleToolGeometry
 // fillArray(m_kipc, KS0_MINIPCHI2 , "kipc, KS0_MINIPCHI2", InputArray);  // TupleToolGeometry   
    fillArray(m_ksmm , fabs(KS0->measuredMass()-497.614), "ksmm, fabs(KS0_MM-497.614)", InputArray); // TupleToolKinematics
    fillArray(m_ksme , KS0->measuredMassErr(), "ksme, KS0_MMERR", InputArray); // TupleToolKinematics
    fillArray(m_ksmo, KS0->p(), "ksmo, KS0_P", InputArray); // TupleToolKinematics

    
 // fillArray(m_muic, std::min(muminus_MINIPCHI2,muplus_MINIPCHI2) , "muic, muminus_MINIPCHI2", InputArray); // TupleToolGeometry
 // fillArray(m_muip, std::min(muminus_MINIP,muplus_MINIP), "muip, muminus_MINIP", InputArray); // TupleToolGeometry
    fillArray(m_mumo, std::min(mum->p(),mup->p()), "mumo, muminus_P", InputArray); // TupleToolKinematics
    fillArray(m_mupt, std::min(mum->pt(),mup->pt()), "mupt, muminus_PT", InputArray); // TupleToolKinematics
    fillArray(m_muid, std::min(mumProto->info(LHCb::ProtoParticle::CombDLLmu,-1000),
         mupProto->info(LHCb::ProtoParticle::CombDLLmu,-1000)) , "muid, muminus_PIDmu", InputArray); // TupleToolPid
    fillArray(m_mutk, std::max((mupTrack->chi2())/(mupTrack->nDoF()),(mumTrack->chi2())/(mumTrack->nDoF())),
        "mutk, muplus_TRACK_CHI2NDOF", InputArray); // TupleToolTrackInfo
 // fillArray(m_piic, std::min(piminus_MINIPCHI2,piplus_MINIPCHI2),"piic piminus_MINIPCHI2", InputArray); // TupleToolGeometry
 // fillArray(m_piip, std::min(piminus_MINIP,piplus_MINIP),"piip, piminus_MINIP", InputArray); // TupleToolGeometry
    fillArray(m_pipt, std::min(pim->pt(),pip->pt()), "pipt, piminus_PT", InputArray); // TupleToolKinematics

    double gp = std::max(pipTrack->ghostProbability(),pimTrack->ghostProbability()); // TupleToolTrackInfo
    if (gp<0) {
      fillArray(m_pigc, 2, "pigc, piplus_TRACK_GhostProb category", InputArray); // very bad
      fillArray(m_pigp, -999. , "pigp, piplus_TRACK_GhostProb", InputArray); 
    } else if (fabs(gp-0.5)<0.001) {
      fillArray(m_pigc, 1, "pigc, piplus_TRACK_GhostProb category", InputArray); // OK but peaking
      fillArray(m_pigp, -999., "pigp, piplus_TRACK_GhostProb", InputArray); 
    } else {
      fillArray(m_pigc, 0, "pigc, piplus_TRACK_GhostProb category", InputArray); // OK
      fillArray(m_pigp, gp, "pigp, piplus_TRACK_GhostProb", InputArray); 
      // std::cout << "Ghost Probability: " << gp << std::endl ;
    }
      
    fillArray(m_pitk, std::max((pipTrack->chi2())/(pipTrack->nDoF()),(pimTrack->chi2())/(pimTrack->nDoF())),
         "piplus_TRACK_CHI2NDOF", InputArray); // TupleToolTrackInfo


    // *** Identify Reconstruction Summary ***
    // See: TupleToolRecoStats
    const LHCb::RecSummary* rS = NULL;
    if ( exist<LHCb::RecSummary>(LHCb::RecSummaryLocation::Default) )
    {
      rS = get<LHCb::RecSummary>(LHCb::RecSummaryLocation::Default);
    }
    else if ( exist<LHCb::RecSummary>(LHCb::RecSummaryLocation::Default,false) )
    {
      rS = get<LHCb::RecSummary>(LHCb::RecSummaryLocation::Default,false);
    }  
    int nSPDHits = rS ? rS->info(LHCb::RecSummary::nSPDhits,-1) : -2 ;
    int nOTClusters = rS ? rS->info(LHCb::RecSummary::nOTClusters,-1) : -2 ;
    int nPVs = rS ? rS->info(LHCb::RecSummary::nPVs,-1) : -2 ; // Alternative for "Primaries"
 
 
    fillArray(m_prim, nPVs , "prim, Primaries", InputArray); // TupleToolRecoStats || TupleToolEventInfo
    fillArray(m_spdm, nSPDHits , "spdm, nSPDHits", InputArray); // TupleToolRecoStats
    fillArray(m_otcl, nOTClusters , "otcl, nOTClusters", InputArray); // TupleToolRecoStats

// #####
// *** Code snippet from TupleToolEventInfo ***
//  declareProperty("InputLocation", m_pvLocation = "" ,"PV location to be used. If empty, take default");
//  unsigned int nPVs = 0 ;
//  if ( m_pvLocation.empty() )
//  {
//    const IOnOffline* oo = tool<IOnOffline>("OnOfflineTool",this);
//    m_pvLocation = oo->primaryVertexLocation();
//    if (msgLevel(MSG::DEBUG)) debug() << "Will be looking for PVs at " << m_pvLocation << endmsg ;
//  }
//  if (exist<RecVertex::Container>(m_pvLocation)) nPVs = (get<RecVertex::Container>(m_pvLocation))->size();
// ##### 

  
    if (ttype==0 && nvar>m_NNIvar){
      if ( nvar!=m_nvar_without_ttype+1) info() << "ERROR! var = " << nvar << ", expect: " << m_nvar_without_ttype+1 << endmsg;
        fillArray(nvar-1 , pimTrack->type(), "piminus_TRACK_Type", InputArray); // TupleToolTrackInfo
    } else if ( nvar!=m_nvar_without_ttype && nvar!=m_NNIvar) info() << "ERROR! var = " << nvar << endmsg;
  }
  m_firstFill = false ;

  return StatusCode::SUCCESS ;
  
}
// ###################################################################
  void NNToSwim::fillArray(const int var, const float value, std::string name, float* InputArray){
  if (var>=0) {
    InputArray[var] = value;
    if (m_firstFill) info() << "Filling variable " << var+2 << " (ID " 
                               << var << ", page " << var+5 << ") ``"<< name << "'' with " << value << endmsg ;
  } else {
    if (m_firstFill) info() << "Ignoring variable ``"<< name << endmsg ;
  }    
};

//=============================================================================
//  Finalize
//=============================================================================
StatusCode NNToSwim::finalize() {

  if ( msgLevel(MSG::DEBUG) ) debug() << "==> Finalize" << endmsg;

  return DVAlgorithm::finalize();
}

//=============================================================================
