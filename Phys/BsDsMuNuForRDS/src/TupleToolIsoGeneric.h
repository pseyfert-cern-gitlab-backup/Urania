#ifndef TUPLETOOLISOGENERIC_H 
#define TUPLETOOLISOGENERIC_H 1

// from Gaudi
#include "DecayTreeTupleBase/TupleToolBase.h"
#include "Kernel/IParticleTupleTool.h" 

#include "Kernel/IParticleDescendants.h"
#include <Kernel/IDVAlgorithm.h>
#include <Kernel/GetIDVAlgorithm.h>
#include "Kernel/IVertexFit.h"



class IDVAlgorithm;
class IDistanceCalculator;
class IPVReFitter;
class IVertexFit;
// from local

/** @class IsoBDT_small IsoBDT_small.h
 *
 *
 *  Tuple designed for isolation study
 *  @ Basem KHANJI
 *  @ date   01/04/2013
 */

class TupleToolIsoGeneric : public TupleToolBase, virtual public IParticleTupleTool {

public:
  
  /// Standard constructor
  TupleToolIsoGeneric( const std::string& type, 
                       const std::string& name,
                       const IInterface* parent);
  
  virtual ~TupleToolIsoGeneric( ){}; ///< Destructor
  
  virtual StatusCode initialize();
  
  virtual StatusCode fill(   const LHCb::Particle*
                             , const LHCb::Particle*
                             , const std::string&
                             , Tuples::Tuple& );
  
  double calculateThetaL( const LHCb::Particle* particle );
  double calculateThetaK( const LHCb::Particle* particle );
  double calculatePhi( const LHCb::Particle* particle );
  double calculateTransThetaTr( const LHCb::Particle* particle );
  double calculateTransPhiTr( const LHCb::Particle* particle );
  double calculateTransThetaV( const LHCb::Particle* particle );
  
private:
  
  std::string m_ParticlePath;
  std::string aux_name ;
  //const IDistanceCalculator* m_dist;
  IDVAlgorithm* m_dva;
  const IDistanceCalculator* m_dist;
  IParticleDescendants* m_descend;
  std::string  m_pvReFitterName;
  IPVReFitter* m_pvReFitter;
  IVertexFit *m_vtxfitter;
  
  double get_MINIPCHI2(const LHCb::Particle* p);
      
  std::vector<std::string>  m_inNames_SignalTrack ;
  // New BDT tunning for B+
  std::vector<std::string>  m_inNames_SignalTrack_New ;
  //
  std::string m_inputLocation;
  // New BDT tunning for B+ 
  std::vector<double>* m_input_SignalTrack;
  std::vector<double>* m_input_SignalTrack_New;
  //
  IClassifierReader* m_read_BDT_SignalTrack;
  // New BDT tunning for B+
  IClassifierReader* m_read_BDT_SignalTrack_New;
  //
  void BDTvariableNames_bb_bkg_training(std::vector<std::string>& inNames ) const;
  void BDTvariableNames_Bplus_training(std::vector<std::string>& inNames ) const;
  
  void InCone(Gaudi::XYZPoint o1,
              Gaudi::XYZVector p1,
              Gaudi::XYZPoint o2,
              Gaudi::XYZVector p2,
              Gaudi::XYZPoint& vtx, double&
              doca, double& angle) const;

  double pointer (Gaudi::XYZVector vtx,
                  Gaudi::XYZVector P_tr,
                  Gaudi::XYZVector P_mu) const;

  double arcosine(Gaudi::XYZVector p1,
                  Gaudi::XYZVector p2) const;

  void closest_point(Gaudi::XYZPoint o,
                     Gaudi::XYZVector p,
                     Gaudi::XYZPoint o_mu,
                     Gaudi::XYZVector p_mu, 
                     Gaudi::XYZPoint& close1,
                     Gaudi::XYZPoint& close2,
                     Gaudi::XYZPoint& vertex, 
                     bool& fail) const ;
    
};
//===========================================================================//
#endif // USER_ISOBDT_SMALL_H
