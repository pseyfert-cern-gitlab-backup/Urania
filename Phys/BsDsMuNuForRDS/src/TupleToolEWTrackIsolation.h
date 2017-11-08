#ifndef TUPLETOOLEWTRACKISOLATION_H
#define TUPLETOOLEWTRACKISOLATION_H 1     
// Include files
// from DaVinci, this is a specialized GaudiAlgorithm
#include "Kernel/IParticleTupleTool.h"
#include "DecayTreeTupleBase/TupleToolBase.h"
    
class IParticle2MCAssociator;

class TupleToolEWTrackIsolation : public TupleToolBase, virtual public IParticleTupleTool {
         
  public: 
    TupleToolEWTrackIsolation( const std::string &type, 
                               const std::string &name,
                               const IInterface *parent ); 
    virtual ~TupleToolEWTrackIsolation();
    virtual StatusCode initialize();
    virtual StatusCode fill( const LHCb::Particle*,
                             const LHCb::Particle*,
                             const std::string&,
                             Tuples::Tuple& ); 
  protected:
  private:

    std::vector<IParticle2MCAssociator*> m_p2mcAssocs;
    std::vector<std::string> m_p2mcAssocTypes;    
    double m_minConeRadius;
    double m_maxConeRadius;
    double m_coneStepSize;
    int m_trackType;
    bool m_isMC;
    std::string m_extraParticlesLocation;
    std::string m_extraPhotonsLocation;
    std::string m_extraPi0sLocation;
    bool m_fillComponents;
    std::vector<const LHCb::Particle*> m_decayParticles;
    void saveDecayParticles( const LHCb::Particle *top );
    StatusCode ChargedCone( const LHCb::Particle *seed,
                            const LHCb::Particles *parts,
                            const double rcut,
                            int &mult,
                            std::vector<double> &vP,
                            double &sPt,
                            int &maxPt_Q,
                            double &maxPt_PX,
                            double &maxPt_PY,
                            double &maxPt_PZ,
                            double &maxPt_PE );
   
    StatusCode PhotonCone( const LHCb::Particle *seed,
                           const LHCb::Particles *parts,
                           const double rcut,
                           int &mult,
                           std::vector<double> &vP,
                           double &sPt,
                           double &maxPt_PX,
                           double &maxPt_PY,
                           double &maxPt_PZ,
                           double &maxPt_PE,
                           double &secPt_PX,
                           double &secPt_PY,
                           double &secPt_PZ,
                           double &secPt_PE, 
                           double &thiPt_PX,
                           double &thiPt_PY,
                           double &thiPt_PZ,
                           double &thiPt_PE,
                           double &CL,
                           double &shape,
                           double &match,
                           double &pid,
                           double &cnv,
                           double &prs );

    StatusCode PhotonConeMC( const LHCb::Particle *seed,
                           const LHCb::Particles *parts,
                           const double rcut,
                           double &maxPt_PX,
                           double &maxPt_PY,
                           double &maxPt_PZ,
                           double &maxPt_PE,
                           double &secPt_PX,
                           double &secPt_PY,
                           double &secPt_PZ,
                           double &secPt_PE,
                           double &thiPt_PX,
                           double &thiPt_PY,
                           double &thiPt_PZ,
                           double &thiPt_PE );

   StatusCode Pi0Cone( const LHCb::Particle *seed,
                       const LHCb::Particles *parts,
                       const double rcut,
                       int &mult,
                       std::vector<double> &vP,
                       double &sPt,
                       double &maxPt_PX,
                       double &maxPt_PY,
                       double &maxPt_PZ,
                       double &maxPt_MM,
                       double &maxPt_PE, 
                       double &secPt_PX,
                       double &secPt_PY,
                       double &secPt_PZ,
                       double &secPt_MM,
                       double &secPt_PE,        
                       double &thiPt_PX,
                       double &thiPt_PY,
                       double &thiPt_PZ,
                       double &thiPt_MM,
                       double &thiPt_PE,        
                       double &CL,
                       double &g1CL, 
                       double &g2CL, 
                       double &g1maxPt_PX,
                       double &g1maxPt_PY,
                       double &g1maxPt_PZ,
                       double &g2maxPt_PX,
                       double &g2maxPt_PY,
                       double &g2maxPt_PZ
                       );

    StatusCode TriGCone( const LHCb::Particle *seed,
                         const LHCb::Particles *parts,
                         const LHCb::Particles *photons,
                         const double rcut,
                         int &mult,
                         std::vector<double> &vP,
                         double &sPt,
                         double &maxPt_PX,
                         double &maxPt_PY,
                         double &maxPt_PZ,
                         double &maxPt_MM,
                         double &secPt_PX,
                         double &secPt_PY,
                         double &secPt_PZ,
                         double &secPt_MM,
                         double &thiPt_PX,
                         double &thiPt_PY,
                         double &thiPt_PZ,
                         double &thiPt_MM,
                         double &g1CL,
                         double &g2CL,
                         double &g3CL,
                         double &g1maxPt_PX,
                         double &g1maxPt_PY,
                         double &g1maxPt_PZ,
                         double &g2maxPt_PX,
                         double &g2maxPt_PY,
                         double &g2maxPt_PZ,
                         double &g3maxPt_PX,
                         double &g3maxPt_PY,
                         double &g3maxPt_PZ 
                         );


    bool isTrackInDecay( const LHCb::Track *track );    
}
      ;
#endif // TUPLETOOLTRACKISOLATION_H
