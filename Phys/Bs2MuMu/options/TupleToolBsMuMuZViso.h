// $Id: TupleToolMuonVariables.h 
#ifndef TUPLEZVISO_H 
#define TUPLEZVISO_H 1

// Include files
#include "Kernel/IEventTupleTool.h"            // Interface
#include "GaudiKernel/ToolFactory.h" 
#include "Kernel/IParticleTupleTool.h" 
#include "DecayTreeTupleBase/TupleToolBase.h"
#include "Kernel/IDVAlgorithm.h"
#include "Kernel/IRelatedPVFinder.h"
#include "Event/RecVertex.h"
#include "LoKi/ParticleCuts.h"
#include "LoKi/AParticleCuts.h"
#include "LoKi/ParticleContextCuts.h"
#include "TH1D.h"
#include "IncTopoVert/IVertexFunctionTool.h"
#include "IncTopoVert/ITopoVertexTool.h"
#include "Kernel/IParticleDescendants.h"
#include "Kernel/IBackgroundCategory.h"
#include "Kernel/ILifetimeFitter.h"
#include "Kernel/ITriggerTisTos.h"
#include "Kernel/IPVReFitter.h"
#include "Kernel/IDistanceCalculator.h"
#include "Kernel/IParticleIsolation.h"
#include "Kernel/IParticleTransporter.h"
#include "OTDAQ/IOTRawBankDecoder.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"




//#if not defined(__CINT__) || defined(__MAKECINT__)
//#include "TMVA/Reader.h"
//#endif




/** @class TupleToolMuonVariables TupleToolMuonVariables.h

 * 
 *  @author Giampiero Mancinelli
 *  @date   2012-09-13
 */

using namespace TMVA;
using namespace std;

class IDistanceCalculator;
class IDVAlgorithm;
class IPVReFitter;
class IVertexFunctionTool;
class ITopoVertexTool;
class DVAlgorithm;
//class Reader;



class  TupleToolBsMuMuZViso : public TupleToolBase, virtual public IParticleTupleTool {
public: 




  typedef std::vector<LHCb::RecVertex*> RecVertexVector;
  typedef std::vector<const LHCb::Track*> TrackVector;

  /// Standard constructor
   TupleToolBsMuMuZViso( const std::string& type, 
              const std::string& name,
              const IInterface* parent );
  /// Loop over differnt conesizes and fill the variables into the tuple
  virtual StatusCode fill( const LHCb::Particle*
                           , const LHCb::Particle*
                           , const std::string&
                           , Tuples::Tuple& );
  
    

  StatusCode Initialize_tracksVF_ZVtop();
  StatusCode IsoTopo2Body(const LHCb::Particle *part, const std::string prefix, Tuples::Tuple& tuple );  //Isolation of Mathieu
  double VfAlongTrack(double zB, const LHCb::Particle* Part, double delta, float* z_f_m );//
  int VfProfile(double zB,const LHCb::Particle* Part, std::vector<double> *v_Vf, std::vector<double>* v_Position);//
  StatusCode GMPiso(const LHCb::Particle *part, const std::string prefix, Tuples::Tuple& tuple );//
  std::vector<LHCb::RecVertex*> zvtop(const LHCb::Particle* dau1, const LHCb::Particle* dau2, const std::string prefix, Tuples::Tuple& tuple );//
  void zvtop_iso(const LHCb::Particle* dau, const std::vector<LHCb::RecVertex*> vertices, const LHCb::VertexBase* primary, const std::string prefix, Tuples::Tuple& tuple);//
  Gaudi::XYZPoint close_point(Gaudi::XYZPoint o, Gaudi::XYZPoint o_mu, Gaudi::XYZVector p_mu);// 
  StatusCode ZViso(const LHCb::Particle *part, const std::string prefix, Tuples::Tuple& tuple );//



  virtual ~ TupleToolBsMuMuZViso( ); ///< Destructor
  
  virtual StatusCode initialize();    ///< Algorithm initialization
  virtual StatusCode finalize ();
  
protected:

private:

  //std::vector<const LHCb::Particle*> m_decayParticles;
  double m_pvdis_h;
  double m_pvdis;
  double m_svdis_h;
  double m_svdis;
  int    m_tracktype;
  double m_ips;
  double m_fc;
  double m_angle;

  double m_cosnk;
  double m_doca_iso;

  double m_cut_ips;
  bool   m_is_data;
  double m_cut_ghost;
  double m_cut_ips_VF;
  double m_cut_ips_high;
  double m_cut_imp;
  bool   m_recoverVF;
  bool   m_recover;
  bool   m_VF_from_MC;
  int    m_nvertex;
  int    m_event;
  double m_B_sPVz;
    
  float m_zv_ipsall;
  float m_zv_ipall   ;
  float m_zv_proba    ;
  float m_zv_proba_close ;
  float m_zv_chi2      ;
  float m_zv_dist      ;
  float m_zv_ntrkvtx  ;


  float  m_z_first_max;
  float  m_Vf_B;
  float    m_nb_peak;
  float    m_nb_peak_DwS;
  float    m_nb_peak_UpS;
  float  m_Vf_Muons_Max;
  float  m_Position_Muons_Max;
  float  m_Vf_Muons_Max_DwS;
  float  m_Position_Muons_Max_DwS ;
  float  m_Vf_Muons_Max_UpS;
  float  m_Position_Muons_Max_UpS;
  float  m_sum_VF_maxs;
  float  m_sum_VF_maxs_UpStr;
  float  m_zv_same;
  float  m_zv_nvtx;
  
  float   m_mum_zv_ipsall ;
  float   m_mum_zv_ipall ;
  float   m_mum_zv_proba ;
  float   m_mum_zv_proba_close  ;
  float   m_mum_zv_chi2  ;
  float   m_mum_zv_dist  ;
  float   m_mum_zv_ntrkvtx ; 
  float   m_mup_zv_ipsall ;
  float   m_mup_zv_ipall ;
  float   m_mup_zv_proba ;
  float   m_mup_zv_proba_close  ;
  float   m_mup_zv_chi2  ;
  float   m_mup_zv_dist  ;
  float   m_mup_zv_ntrkvtx ; 
  
  int m_n_step_m;
  int m_n_step_p;
  float m_step;
  float m_cut;
  


  std::string m_Weights_BDTG_ZViso;
  float m_ZViso;

 
  std::string m_TracksPath;
  std::string m_ParticlePath;
  std::string m_PVInputLocation;


  std::vector<const LHCb::Track*> m_tracksVF;
  std::vector<const LHCb::Track*> m_tracksZVTop;




  ITopoVertexTool* m_topotool;

  IVertexFunctionTool* m_vertextool;
  const IRelatedPVFinder* pFinder; 
  IDVAlgorithm* m_dva;
  IPVReFitter* m_pvReFitter;
  const IDistanceCalculator* m_dist;
  IDistanceCalculator*  m_Geom;
  IParticleTransporter* m_transporter;
  IParticleDescendants* m_descend;
  
  TMVA::Reader* m_reader_ZViso;//= new TMVA::Reader( "!Color:!Silent" );
   
 
  

};



#endif // TUPLETOOLMUONVARIABLES_H
