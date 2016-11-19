#include "GaudiKernel/ToolFactory.h"
#include "GaudiAlg/Tuple.h"
#include "GaudiAlg/TupleObj.h"
#include "Event/Particle.h"
#include "Kernel/IPVReFitter.h"
#include "Kernel/IDVAlgorithm.h"
#include <Kernel/GetIDVAlgorithm.h>
#include <Kernel/IDistanceCalculator.h>
#include <Kernel/DaVinciFun.h> 
#include "TMath.h"
#include "IsoBDT_Bs.C"
#include "TMVAClassification_Bs2KmuNu.class.C"
#include "TupleToolIsoGeneric.h"
#include <utility>
#include <iostream>     
#include <algorithm>    

//-----------------------------------------------------------------------------
// Implementation file for class : TupleToolIsoGeneric
//
// Author: Basem KHANJI 
//-----------------------------------------------------------------------------
using namespace LHCb ;
using namespace DaVinci;

using namespace Gaudi::Units;
using namespace ROOT::Math;
//Declaration of Factory
DECLARE_TOOL_FACTORY( TupleToolIsoGeneric )  //commented to adapt to DecayTreeTuple
//============================================================================
TupleToolIsoGeneric::TupleToolIsoGeneric(const std::string& type,
                                         const std::string& name,
                                         const IInterface* parent )
  : TupleToolBase ( type, name , parent ),
  m_dva(0), 
  m_dist(0),
  m_descend(0),
  m_pvReFitterName( "LoKi::PVReFitter:PUBLIC" ),
  m_vtxfitter(0),
  m_read_BDT_SignalTrack(0),
  m_read_BDT_SignalTrack_New(0)
    
{
  declareInterface<IParticleTupleTool>(this);
  declareProperty("ParticlePath",
                  m_ParticlePath="/Event/Phys/StdAllNoPIDsPions/Particles"
                  );
  declareProperty("VarSuffix",
                  aux_name  = "_Long"
                  );
  
}
// =============================================================================
StatusCode TupleToolIsoGeneric::initialize() {

  const StatusCode sc = TupleToolBase::initialize();
  if ( sc.isFailure() ) return sc;
  
  std::vector<std::string> BDT_Var_names;

  m_dva = Gaudi::Utils::getIDVAlgorithm ( contextSvc(), this ) ;
  if (!m_dva) return Error("Couldn't get parent DVAlgorithm");
  
  m_dist = m_dva->distanceCalculator();
  
  m_descend = tool<IParticleDescendants> ( "ParticleDescendants", this );
  if( ! m_descend ) {fatal() << "Unable to retrieve ParticleDescendants tool "<< endreq;
    return StatusCode::FAILURE; }
  
  m_pvReFitter = tool<IPVReFitter>( m_pvReFitterName, this );
  if ( !m_pvReFitter )
  {
    return Error( "Unable to retrieve IPVReFitter instance" );
  }
    
  m_vtxfitter = tool<IVertexFit>("LoKi::VertexFitter");
  if(!m_vtxfitter ) 
  {
    fatal() << "Unable to retrieve Loki VertexFitter" << endreq;
    return StatusCode::FAILURE;
  }
  
  BDTvariableNames_bb_bkg_training(m_inNames_SignalTrack );
  BDTvariableNames_Bplus_training(m_inNames_SignalTrack_New );
  
  m_read_BDT_SignalTrack = new ReadBDT_bS(m_inNames_SignalTrack);
  m_read_BDT_SignalTrack_New = new ReadBDTG_isoBDT_Bplus(m_inNames_SignalTrack_New);
  m_input_SignalTrack = new std::vector<double>;
  m_input_SignalTrack_New = new std::vector<double>;
    
  return sc;
}
//=============================================================================
StatusCode TupleToolIsoGeneric::fill(const LHCb::Particle* mother 
                                     , const LHCb::Particle* P
                                     , const std::string& head
                                     , Tuples::Tuple& tuple)
{
  Assert( P && m_dva
          , "No mother or particle, or tools misconfigured." );
  
  const std::string prefix=fullName(head);
  bool test = true;
  if( !P ) return StatusCode::FAILURE;
  if( !(  P->isBasicParticle() ) ) return StatusCode::SUCCESS;
  
  int iso_SignalTrack   = 0    ; 
  double minSumBDT      = -100 ;        
  double minMinBDT_New  =  1.5 ;  
    
  double Best_PAIR_M_fromiso      = -1 ;
  double Best_OppC_PAIR_M_fromiso = -1 ;
  double Best_PAIR_VCHI2     = -1 ;
  double Best_PAIR_D         = -1 ;
  double Best_PAIR_DCHI2     = -1 ;
  
  XYZTVector NonIsolatedTrack_4Vec ;
    
  const VertexBase* aPV = NULL ;
  aPV = m_dva->bestVertex(mother);//bestVertex
  
  Gaudi::XYZPoint PosPV(0,0,200000)    ;
  if(!aPV){ return StatusCode::SUCCESS ; }
  if( aPV){ PosPV = aPV->position()    ; }
  
  const Vertex* endv = mother->endVertex();
  
  
  Particle::ConstVector parts_cand = m_descend->descendants(mother);
  
  Gaudi::XYZPoint PosSV(0,0,200000);
  if( !endv ) { return StatusCode::FAILURE; }
  if(  endv ) { PosSV= mother->endVertex()->position(); } 
  
  double Bd_eta = mother->momentum().Eta();
  double Bd_phi = mother->momentum().Phi();
  double Bd_pT  = mother->pt();
  double Sum_of_trackpt = 0;
  /*
  // Get info from B to estimate the function used in the isolation BDT:
  double Bd_mass     = mother->momentum().M();
  Gaudi::XYZVector A = mother->momentum().Vect();
  Gaudi::XYZVector B = endv->position() - aPV->position();
  double cosPFD = A.Dot( B ) / std::sqrt( A.Mag2()*B.Mag2() );
  double Bd_PointingAngle  = std::acos(cosPFD);
  // Estimate corrected mass
  double pNuT        = sin(Bd_PointingAngle)*std::sqrt( A.Mag2());
  double Bs_corrMass    = sqrt(Bd_mass*Bd_mass +pNuT*pNuT) + pNuT;
  */
  XYZTVector SignalParticle4vect = P->momentum();
  double PAIR_VtxChi2 = -1 ;
  
  LHCb::Particle::Range allparts ;
  if (exist<LHCb::Particle::Range>(m_ParticlePath))
  { allparts = get<LHCb::Particle::Range>(m_ParticlePath); }
  else return Error("Nothing found at "+ m_ParticlePath , StatusCode::SUCCESS,1);
  
  LHCb::Particle::Range::const_iterator im;
  for(im = allparts.begin() ; im != allparts.end() ; ++im)
  {
    const Particle * axp  = (*im);
    const Track* track = axp->proto()->track();
    bool isInDecay = false;
    Particle::ConstVector::const_iterator it_p;
    for( it_p=parts_cand.begin(); it_p!=parts_cand.end(); it_p++){
      if(!(*it_p)->isBasicParticle()) continue;
      const LHCb::Track* Track_decay = (*it_p)->proto()->track();
      //if(!track || !Track_decay) continue;
      if(Track_decay && track){
        //debug()<<"track of decay particle exist!"<<endreq;
        if(Track_decay == track){
          //debug()<<"This track is in decay .. remove it"<<endreq;
          isInDecay = true;
        }  
      } 
    }
    
    if(isInDecay) continue;
        
    const double track_minIPchi2 = get_MINIPCHI2(axp);
    double track_pt  = axp->pt();
    double track_eta = track->momentum().eta();
    double track_phi = track->momentum().phi();
    double track_Matchchi2 = track->info(LHCb::Track::FitMatchChi2,-1);
    XYZTVector track4vect = axp->momentum();
        
    XYZTVector PAIR_mom = SignalParticle4vect + track4vect;
    double PAIR_mass    = std::abs(std::sqrt(PAIR_mom.M2()) );
    
    Gaudi::XYZPoint pos_track(track->position());
    Gaudi::XYZVector mom_track(track->momentum());
    Gaudi::XYZPoint pos_SignalTrack(P->proto()->track()->position() );
    Gaudi::XYZVector mom_SignalTrack(P->proto()->track()->momentum());
        
    // Calculate the input of ISO variable :
    Gaudi::XYZPoint vtx_SignalTrack(0.,0.,0.);
        
    double doca_SignalTrack(-1.) , angle_SignalTrack(-1.) ; 
    
    InCone(pos_SignalTrack   , mom_SignalTrack , pos_track , mom_track , vtx_SignalTrack  , doca_SignalTrack, angle_SignalTrack);//
        
    double PVdis_SignalTrack_track   = ( vtx_SignalTrack.z() -PosPV.z() ) / fabs(vtx_SignalTrack.z()-PosPV.z())*(vtx_SignalTrack-PosPV).R() ;
    double SVdis_SignalTrack_track   = ( vtx_SignalTrack.z() -PosSV.z() ) / fabs(vtx_SignalTrack.z()-PosSV.z())*(vtx_SignalTrack-PosSV).R() ;
    double fc_mu = pointer(vtx_SignalTrack -PosPV ,mom_track , mom_SignalTrack );
    
    m_input_SignalTrack->clear();
    m_input_SignalTrack->reserve(6);
    m_input_SignalTrack->push_back(track_minIPchi2);
    m_input_SignalTrack->push_back(PVdis_SignalTrack_track);
    m_input_SignalTrack->push_back(SVdis_SignalTrack_track);
    m_input_SignalTrack->push_back(doca_SignalTrack);
    m_input_SignalTrack->push_back(angle_SignalTrack);
    m_input_SignalTrack->push_back(fc_mu);
    
    double BDT_val_SignalTrack =0;
    BDT_val_SignalTrack =  m_read_BDT_SignalTrack->GetMvaValue( *m_input_SignalTrack );
    
    // New BDT tunning:
    m_input_SignalTrack_New->clear();
    m_input_SignalTrack_New->reserve(10);
    m_input_SignalTrack_New->push_back(track_minIPchi2);
    m_input_SignalTrack_New->push_back(track_eta);
    m_input_SignalTrack_New->push_back(track_phi);
    m_input_SignalTrack_New->push_back(track_pt);
    m_input_SignalTrack_New->push_back(track_Matchchi2);
    m_input_SignalTrack_New->push_back(PVdis_SignalTrack_track);
    m_input_SignalTrack_New->push_back(SVdis_SignalTrack_track);
    m_input_SignalTrack_New->push_back(doca_SignalTrack);
    m_input_SignalTrack_New->push_back(angle_SignalTrack);
    m_input_SignalTrack_New->push_back(fc_mu);
    
    double BDT_val_SignalTrack_New =0;
    BDT_val_SignalTrack_New = m_read_BDT_SignalTrack_New->GetMvaValue( *m_input_SignalTrack_New );
    
    double track_signal_sign = P->charge()/( axp->charge());
    // calculate the track-signaltrack vertex quantities: 
    LHCb::Vertex vtx_PAIR;         
    double PAIR_distance =  0 ; double PAIR_chi2 =  0 ;
    StatusCode ok_TrackSignalTrack =  m_dist->distance( P , axp , PAIR_distance, PAIR_chi2 );
    StatusCode PAIR_Vtx_fit = m_vtxfitter ->fit( vtx_PAIR, *P , *axp );
    if ( !PAIR_Vtx_fit ) { PAIR_VtxChi2 = -1; }
    PAIR_VtxChi2 = vtx_PAIR.chi2()/(double)vtx_PAIR.nDoF();
    
    if( minSumBDT< BDT_val_SignalTrack_New ) { minSumBDT = BDT_val_SignalTrack ; }
    
    if( minMinBDT_New > BDT_val_SignalTrack_New)
    {
      Best_PAIR_VCHI2      = PAIR_VtxChi2  ;
      Best_PAIR_D          = PAIR_distance ;
      Best_PAIR_DCHI2      = PAIR_chi2     ;
      minMinBDT_New        = BDT_val_SignalTrack_New    ;
      Best_PAIR_M_fromiso  = PAIR_mass ;
      if (track_signal_sign<1) Best_OppC_PAIR_M_fromiso = PAIR_mass ;
    }
    // Apply giampie's iso cut:
    if ( angle_SignalTrack < 0.27 && fc_mu<0.60 && doca_SignalTrack<0.13 && track_minIPchi2 > 3.0 &&
         SVdis_SignalTrack_track >-0.15 && SVdis_SignalTrack_track<30. && PVdis_SignalTrack_track>0.5 && PVdis_SignalTrack_track<40.
         ) {
      iso_SignalTrack += 1;
    }
    
    double cone_radius = std::sqrt(std::pow((Bd_eta - track_eta) , 2)  + 
                                   std::pow((Bd_phi - track_phi) , 2)  ) ;
    if ( cone_radius <1){
      Sum_of_trackpt += axp->pt() ;
    }
  }
  
  double Bd_CDF3 = Bd_pT/(Bd_pT+Sum_of_trackpt);
  
  test &= tuple->column(prefix+"_iso_SignalTrack"+aux_name    , iso_SignalTrack);
  //test &= tuple->column(prefix+"_iso_SumBDT"+aux_name         , minSumBDT);
  test &= tuple->column(prefix+"_iso_MinBDT"+aux_name         , minMinBDT_New);
  test &= tuple->column(prefix+"_ConeIso"+aux_name            , Bd_CDF3);
  test &= tuple->column(prefix+"_PAIR_M_iso"+aux_name         , Best_PAIR_M_fromiso);
  test &= tuple->column(prefix+"_OppC_PAIR_M_iso"+aux_name    , Best_OppC_PAIR_M_fromiso);
  test &= tuple->column(prefix+"_PAIR_VtxChi2"+aux_name       , Best_PAIR_VCHI2  );
  test &= tuple->column(prefix+"_PAIR_distance"+aux_name      , Best_PAIR_D );
  test &= tuple->column(prefix+"_PAIR_distance_chi2"+aux_name , Best_PAIR_DCHI2 );
  
  //   test &= tuple->column(prefix+"_CorrMass" , Bs_corrMass);
  
  return StatusCode(test);
}

//=============================================================================
double TupleToolIsoGeneric::get_MINIPCHI2(const Particle* p){  
  double minchi2 = -1 ;
  
  const RecVertex::Range PV = m_dva->primaryVertices();
  if ( !PV.empty() ){
    for (RecVertex::Range::const_iterator pv = PV.begin(); pv!=PV.end(); ++pv){
      double ip, chi2;
      
      RecVertex newPV(**pv);
      StatusCode scfit = m_pvReFitter->remove(p, &newPV);
      if(!scfit) { err()<<"ReFitter fails!"<<endreq; continue; }
      
      LHCb::VertexBase* newPVPtr = (LHCb::VertexBase*)&newPV; 
      bool test2  =  m_dist->distance ( p, newPVPtr, ip, chi2 );
      if( test2 ) {
        if ((chi2<minchi2) || (minchi2<0.)) minchi2 = chi2 ;        
      }
    }
  }
  return minchi2;
}
//=============================================================================
void TupleToolIsoGeneric::InCone(Gaudi::XYZPoint o1,
                                   Gaudi::XYZVector p1,Gaudi::XYZPoint o2,
                                   Gaudi::XYZVector p2,
                                   Gaudi::XYZPoint& vtx, double&
                                   doca, double& angle) const
{

  Gaudi::XYZPoint rv;
  Gaudi::XYZPoint close;
  Gaudi::XYZPoint close_mu;
  bool fail(false);
  closest_point(o1,p1,o2,p2,close,close_mu,vtx, fail);
  if (fail) {
    doca =-1.;
    angle=-1.;
  }
  else {
    doca = (close-close_mu).R();
    angle = arcosine(p1,p2);
  }
}

//============================================================================
double TupleToolIsoGeneric::pointer (Gaudi::XYZVector vertex,
                                  Gaudi::XYZVector p, Gaudi::XYZVector p_mu) const
{
  double pt=p.Rho()+p_mu.Rho();
  Gaudi::XYZVector ptot(p+p_mu);
  double  num=ptot.R()*sin(arcosine(vertex,ptot));
  double  den=(num+pt);
  double fc = num/den;
  return fc;
}
//============================================================================
void TupleToolIsoGeneric::closest_point(Gaudi::XYZPoint o,Gaudi::XYZVector p,
                                     Gaudi::XYZPoint o_mu,Gaudi::XYZVector
                                     p_mu, Gaudi::XYZPoint& close1,
                                     Gaudi::XYZPoint& close2,
                                     Gaudi::XYZPoint& vertex, bool&
                                     fail) const
{
  Gaudi::XYZVector v0(o - o_mu);
  Gaudi::XYZVector v1(p.unit());
  Gaudi::XYZVector v2(p_mu.unit());
  Gaudi::XYZPoint temp1(0.,0.,0.);
  Gaudi::XYZPoint temp2(0.,0.,0.);
  fail = false;

  double  d02 = v0.Dot(v2);
  double  d21 = v2.Dot(v1);
  double  d01 = v0.Dot(v1);
  double  d22 = v2.Dot(v2);
  double  d11 = v1.Dot(v1);
  double  denom = d11 * d22 - d21 * d21;
  if (fabs(denom) <= 0.) {
    close1 = temp1;
    close2 = temp2;
    fail = true;
  }
  else {
    double numer = d02 * d21 - d01 * d22;
    double mu1 = numer / denom;
    double mu2 = (d02 + d21 * mu1) / d22;
    close1 = o+v1*mu1;
    close2 = o_mu+v2*mu2;
  }
  vertex = (close1+(close2-close1)*0.5);
}
//============================================================================
double TupleToolIsoGeneric::arcosine(Gaudi::XYZVector p1,
                                 Gaudi::XYZVector p2) const
{

  double num=(p1.Cross(p2)).R();
  double den=p1.R()*p2.R();
  double seno = num/den;
  double coseno = p1.Dot(p2)/den;
  double alpha = asin(fabs(seno));
  if (coseno < 0 ) {
    alpha = ROOT::Math::Pi() - alpha;
  }
  return alpha; 
}
//============================================================================
void TupleToolIsoGeneric::BDTvariableNames_bb_bkg_training(std::vector<std::string>& inNames) const {
  inNames.clear();
  inNames.push_back("track_minIPchi2");
  inNames.push_back("track_pvdis_mu");
  inNames.push_back("tracksvdis_mu" );
  inNames.push_back("track_doca_mu" );
  inNames.push_back("track_angle_mu");
  inNames.push_back("track_fc_mu"   );
  return; 
}
//============================================================================
//============================================================================
void TupleToolIsoGeneric::BDTvariableNames_Bplus_training(std::vector<std::string>& inNames) const {
  inNames.clear();
  inNames.push_back("track_minIPchi2" );
  inNames.push_back("track_eta" );
  inNames.push_back("track_phi" );
  inNames.push_back("track_pt" );
  inNames.push_back("track_MatchChi2" );
  inNames.push_back("track_pvdis_mu");
  inNames.push_back("tracksvdis_mu" );
  inNames.push_back("track_doca_mu" );
  inNames.push_back("track_angle_mu");
  inNames.push_back("track_fc_mu");
  return; 
}
//====================================================================================

