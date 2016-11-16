// $Id: TupleToolMuonVariables.h 
#ifndef TUPLETOOLMUONVARIABLES_H 
#define TUPLETOOLMUONVARIABLES_H 1

// Include files
#include "Kernel/IParticleTupleTool.h" 
#include "DecayTreeTupleBase/TupleToolBase.h"
#include "Kernel/IDVAlgorithm.h"
#include "Kernel/IRelatedPVFinder.h"
#include "Event/RecVertex.h"
#include "LoKi/ParticleCuts.h"
#include "LoKi/AParticleCuts.h"
#include "LoKi/ParticleContextCuts.h"
#include "TMVA/Reader.h"
#include "TH1D.h"

//includes for Track2MC2D
#include "Kernel/Track2MC.h"
#include "Relations/IRelationWeighted2D.h"
//#include "Kernel/IParticle2MCAssociator.h"
/*
#include "GaudiKernel/ToolFactory.h" 
#include "Event/Particle.h"  
// kernel 
#include "GaudiAlg/Tuple.h"
#include "GaudiAlg/TupleObj.h"
#include "GaudiKernel/PhysicalConstants.h"
#include "Kernel/IParticle2MCAssociator.h"
#include <Kernel/IDistanceCalculator.h>
#include "Kernel/IPVReFitter.h"
//#include "Kernel/IOnOffline.h"
#include "Kernel/IDVAlgorithm.h"
#include <Kernel/GetIDVAlgorithm.h>

// MC stuff
#include "Event/GenHeader.h" 
#include "Event/MCHeader.h" 

#include "TupleToolMuonVariables.h"
#include "TMath.h"
#include "TFile.h"
#include "TString.h"
#include <TROOT.h>
#include <TObject.h>
#include "TH1D.h"
//#include"E "TMVA/Reader.h"
#include "Kernel/IRelatedPVFinder.h"
#include "Math/Boost.h"

#include "GaudiKernel/DeclareFactoryEntries.h"
*/

using namespace std;

/** @class TupleToolMuonVariables TupleToolMuonVariables.h

 * 
 *  @author Fatima Soomro
 *  @date   2011-08-08
 */

class IDistanceCalculator;
class IDVAlgorithm;
class IPVReFitter;

class TupleToolMuonVariables : public TupleToolBase, virtual public IParticleTupleTool {
public: 
  /// Standard constructor
  TupleToolMuonVariables( const std::string& type, 
              const std::string& name,
              const IInterface* parent );
  /// Loop over differnt conesizes and fill the variables into the tuple
  virtual StatusCode fill( const LHCb::Particle*
                           , const LHCb::Particle*
                           , const std::string&
                           , Tuples::Tuple& );
  
  
  StatusCode fillIsolation(const LHCb::Particle *part, std::string, Tuples::Tuple&);
  //MR
  StatusCode fillTrackIsoBDT(const LHCb::Particle *part, std::string, Tuples::Tuple&);//BDT track isolation
  StatusCode fillPVList(Tuples::Tuple&);//fill the primary vertices of the event
  StatusCode fillPVrefitList(const LHCb::Particle*part,Tuples::Tuple&);//fill the primary vertices of the event removing the tracks from part
  StatusCode fillBposmomCov(const LHCb::Particle*, std::string, Tuples::Tuple&);//fill 7x7 B pos-mom Cov matrix
  StatusCode fillVeloTracksInfo(Tuples::Tuple& tuple);
  StatusCode fillUpstreamTracksInfo(Tuples::Tuple& tuple);
  

   void trkPVassociator(std::vector<double>&,std::vector<double>&,std::vector<int>&,std::string);
   int getAssociatedPV(const LHCb::Track*,const std::vector<double>&,const std::vector<double>&, const std::vector<int>&);
   StatusCode fillMCDecayTree(Tuples::Tuple& tuple);
   void fillMCInfo(const LHCb::MCParticle* part,int part_id,int depth,int flag);
   std::vector<int> mc_motindex_vec,mc_lundid_vec,mc_partindex_vec,mc_origtype_vec;
   std::vector<double> mc_px_vec,mc_py_vec,mc_pz_vec,mc_vtx_x_vec,mc_vtx_y_vec,mc_vtx_z_vec;
   int mc_partindex;
   //end MR

  StatusCode ATLASIsolation(const LHCb::Particle* B, std::string, Tuples::Tuple&); 

  StatusCode CDFIsolation(const LHCb::Particle* B, 
			  const LHCb::Particle* vdau1, 
			  const LHCb::Particle* vdau2,
			  std::string, Tuples::Tuple&);

  StatusCode CDFIsolation_2(const LHCb::Particle* B, 
			  const LHCb::Particle* vdau1, 
			  const LHCb::Particle* vdau2,
			  std::string, Tuples::Tuple&);

  StatusCode OtherB(const LHCb::Particle* B,
			const LHCb::Particle* vdau1,
			const LHCb::Particle* vdau2,
			std::string, Tuples::Tuple&);
  
  StatusCode ConstrMass(const LHCb::Particle* B, const std::string prefix, Tuples::Tuple& tuple );
    
  StatusCode CDFIsolation_Yuri(const LHCb::Particle* B, const LHCb::Particle* vdau1, const LHCb::Particle* vdau2,
			       std::string, Tuples::Tuple&);
  StatusCode fillCosNK(const LHCb::Particle *part, std::string, Tuples::Tuple&);
  StatusCode fillDoca(const LHCb::Particle *part, std::string, Tuples::Tuple&);
  StatusCode fillEta(const LHCb::Particle *part, std::string, Tuples::Tuple&);
  StatusCode fillTrackHitInfo(const LHCb::Particle *part, std::string, Tuples::Tuple&);
  StatusCode fillFakeVtx(const LHCb::Particle *part, const LHCb::Particle*, std::string, Tuples::Tuple&);
  StatusCode fillBDTS(const LHCb::Particle *part, const LHCb::Particle*, bool, std::string, Tuples::Tuple&);
  StatusCode fillLoKiTau(const LHCb::Particle *part,   const std::string prefix,   Tuples::Tuple& tuple );
  
  StatusCode fillMCTruth(const LHCb::Particle *part, std::string, Tuples::Tuple&);
  StatusCode fillTrackInfo(Tuples::Tuple& tuple );
  
  const LHCb::MCParticle* originof( const LHCb::MCParticle* ) ;
  
  virtual ~TupleToolMuonVariables( ); ///< Destructor
  
  virtual StatusCode initialize();    ///< Algorithm initialization
  virtual StatusCode finalize ();
  
protected:

private:

  //std::vector<const LHCb::Particle*> m_decayParticles;
  bool JpsiInDau ;
  double m_pvdis_h;
  double m_pvdis;
  double m_svdis_h;
  double m_svdis;
  int m_tracktype;
  double m_ips;
  double m_fc;
  double m_angle;
  double m_count_mup_Giampi; 
  double m_count_mum_Giampi; 
  double m_count_mum;
  double m_count_mup;
  double m_count_mum_f;
  double m_count_mup_f;
  double m_isoCDFyuri;
  double m_CDFIso;
  double m_cosnk;
  double m_doca_iso;
  double m_doca_tr;
  double m_doca;

  bool m_isMC;
  bool m_is_microDST;
  bool m_dumpFullInfo;
  double m_mcancestorpid1;
  double m_mcancestorpid2;
  double m_mcancestorpid;
  double m_endVertices1;
  double m_endVertices2;
  double m_endVertices;
  double m_typeDecay1 ;   double m_zDecay1 ;
  double m_typeDecay2 ;   double m_zDecay2 ;
  double m_typeOrigin1;   double m_zOrigin1;
  double m_typeOrigin2;   double m_zOrigin2;
  double m_typeOrigin; double m_zOrigin;

  bool m_dumpVeloTracks;
  bool m_dumpUpstreamTracks;

  //Particle2MCLinker* m_pLinker;
  std::string m_particlePaths;
  double m_MCI ;
  double m_MCPV ;
  IParticle2MCAssociator* m_p2mcAssoc;
  std::string m_p2mcAssocType;
  
  std::string m_TracksPath;
  std::string m_ParticlePath;
  std::string m_PVInputLocation;		\

  // TMVA stuff, Francesco
  std::string m_bdts_root_file;
  std::string m_bdts_xml_file;
  TMVA::Reader *m_reader_BDTS;
  TMVA::Reader *m_readera;
  std::string m_methodName;
  const int m_nvariables;
  float *m_values;
  TH1D *m_h_cumul_BDTS;

  const IRelatedPVFinder* pFinder; 
  IDVAlgorithm* m_dva;
  IPVReFitter* m_pvReFitter;
  const IDistanceCalculator* m_dist;

  std::vector<int> getIso(const LHCb::Particle*,  int isotype, bool);
  void dumpIsoVariables(const LHCb::Particle* B, Tuples::Tuple& tuple );

  void IsHltGood(Gaudi::XYZPoint o, Gaudi::XYZVector p, Gaudi::XYZPoint o_mu,Gaudi::XYZVector p_mu, Gaudi::XYZPoint PV, bool& hltgood, double& fc);
  double pointer (Gaudi::XYZVector vtx, Gaudi::XYZVector P_tr,  Gaudi::XYZVector P_mu);
  double gettheta(const LHCb::Particle* vdau1, const LHCb::Particle* vdau2);
  double getphi(const LHCb::Particle* vdau1, const LHCb::Particle* vdau2);
  double ratio( double p1, double p2);
  double IsClose(const LHCb::Particle* p1, const LHCb::Particle* p2);
  void InCone(Gaudi::XYZPoint o1, Gaudi::XYZVector p1,Gaudi::XYZPoint o2,
              Gaudi::XYZVector p2, Gaudi::XYZPoint& vtx, double& doca, double& angle);
  void closest_point(Gaudi::XYZPoint o,Gaudi::XYZVector p, Gaudi::XYZPoint o_mu,Gaudi::XYZVector p_mu, 
                     Gaudi::XYZPoint& close1, Gaudi::XYZPoint& close2, Gaudi::XYZPoint& vertex, bool& fail);
  double arcosine (Gaudi::XYZVector, Gaudi::XYZVector);
  
  //
  //MR: additions to compute the isoBDT
  //
  double calcIPToAnyPV( const LHCb::Particle * part ) ;
  double  enclosedAngle( Gaudi::XYZVector, Gaudi::XYZVector );
  void    getPerpFeet(  Gaudi::XYZPoint track_pos,Gaudi::XYZVector track_p,Gaudi::XYZPoint mu_pos, Gaudi::XYZVector mu_p, Gaudi::XYZPoint& perpFootTrack,Gaudi::XYZPoint& perpFootMu,Gaudi::XYZPoint& vertex, bool& fail);
  double calcFC(  Gaudi::XYZVector track_mom, Gaudi::XYZVector mu_mom, Gaudi::XYZPoint mu_track_vertex, const LHCb::VertexBase* PV);
  double calcVertexDist(Gaudi::XYZPoint muTrack,const LHCb::VertexBase* v);

  //isoBDT stuff
  float isobdt_values[15];
  TMVA::Reader* isobdt_reader[4];
  std::string isobdt_methodName;

  std::string m_isoBDT1_xmlFile;
  std::string m_isoBDT2_xmlFile;
  std::string m_isoBDT3_xmlFile;
  std::string m_isoBDT4_xmlFile;
  std::string m_isoBDT_xmlFilePath;


  void fillTruthMatchedInfo(const LHCb::Track*,LHCb::Track2MC2D* table2d);
  void ClearTruthMatchedVectors();
  void fillTruthMatchedNtuple(Tuples::Tuple& tuple,TString block_name,const int max_num);

  vector<bool> _MC_match,_MC_par_hasMother,_MC_mot_hasMother,_MC_gra_hasMother,_MC_mogra_hasMother;
  
  vector<double> _MC_origin_id,_MC_ori_vtx_y,_MC_ori_vtx_z,_MC_ori_vtx_x;
  vector<int> _MC_ori_type;
  vector<double> _MC_par_py, _MC_par_pz, _MC_par_px, _MC_par_M, _MC_par_E;
  vector<int> _MC_par_trueID,_MC_par_isnoniso_mup,_MC_par_isnoniso_mum;

  vector<double> _MC_mot_ori_vtx_y, _MC_mot_ori_vtx_z, _MC_mot_ori_vtx_x;
  vector<double> _MC_mot_py, _MC_mot_pz, _MC_mot_px, _MC_mot_M, _MC_mot_E;
  vector<int> _MC_mot_trueID;

  vector<double> _MC_gra_ori_vtx_y, _MC_gra_ori_vtx_z, _MC_gra_ori_vtx_x;
  vector<double> _MC_gra_py, _MC_gra_pz, _MC_gra_px, _MC_gra_M, _MC_gra_E;
  vector<int> _MC_gra_trueID;

  vector<double> _MC_mogra_ori_vtx_y, _MC_mogra_ori_vtx_z, _MC_mogra_ori_vtx_x;
  vector<double> _MC_mogra_py, _MC_mogra_pz, _MC_mogra_px, _MC_mogra_M, _MC_mogra_E;
  vector<int> _MC_mogra_trueID;

  vector<double> _MC_grgra_ori_vtx_y, _MC_grgra_ori_vtx_z, _MC_grgra_ori_vtx_x;
  vector<double> _MC_grgra_py, _MC_grgra_pz, _MC_grgra_px, _MC_grgra_M, _MC_grgra_E;
  vector<int> _MC_grgra_trueID;
 
  void get_decayTree(const LHCb::MCParticle* mcp,vector<int>& key_vec);
  void init_muonsMCDecayTree(const LHCb::Particle* part);
  std::vector<int> _mup_mcdecaytree_vec;
  std::vector<int> _mum_mcdecaytree_vec;
  bool isNonIso(const LHCb::MCParticle* mcp,TString mu_flag);
  
};



#endif // TUPLETOOLMUONVARIABLES_H
