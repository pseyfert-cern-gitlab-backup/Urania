// $Id: $
#ifndef _GAUSSDECAYTUPLETOOL_H 
#define _GAUSSDECAYTUPLETOOL_H 1

// Include files
// from Gaudi

/** @class GaussDecayTupleTool GaussDecayTupleTool.h Sim/GaussDecayTupleTool.h
 *  
 *
 *  @author Thomas BLAKE
 *  @date   2009-01-19
 */
static const double m_psi = 3096.916 ;
static const double m_p   =  938.272 ;
static const double m_pi  =  139.570 ;
static const double m_K   =  493.677 ;
static const double m_Lb  =  5620.2 ;
struct EntryProperty 
{
  bool operator()( EntryProperty One, EntryProperty Two ) {
    return ( ( One.name ).compare( Two.name ) < 0 );
  }
  
  std::string name;
  int pdgID;
};


typedef std::vector< const HepMC::GenParticle* > ParticleVector;

class GaussDecayTupleTool : public GaudiTupleAlg {
public: 
  /// Standard constructor
  GaussDecayTupleTool( const std::string& name, ISvcLocator* pSvcLocator );

  virtual ~GaussDecayTupleTool( ); ///< Destructor

  virtual StatusCode initialize();    ///< Algorithm initialization
  virtual StatusCode execute   ();    ///< Algorithm execution
  virtual StatusCode finalize  ();    ///< Algorithm finalization
  

protected:

private:
  
  /// Methods
  void addParticle( const char* charstring );
  void addDaughters( ParticleVector& Daughters, 
                     const HepMC::GenParticle* particle );
  
  void fillParticle( const HepMC::GenParticle* particle, 
                     Tuple& tuple, const unsigned int number );
  void fillCandidate( const HepMC::GenParticle* parent );
  
  bool isLongLived( const HepMC::GenParticle* particle ) const ;
  
  std::vector< EntryProperty > m_daughters;

  std::string m_daughterstring;
  std::string m_tuplename;
  std::string m_motherstring;

  unsigned int m_ndaughters;
  int m_motherid ;
  
  LHCb::IParticlePropertySvc* m_ppsvc;

  std::vector< int > m_stable;
  
  double mprime(  ParticleVector P );
  double thetaprime( ParticleVector );

  double twoMass2(const HepMC::FourVector p1, const HepMC::FourVector p2){
    return ((p1.e() + p2.e())*(p1.e() + p2.e())-
            (p1.px()+p2.px())*(p1.px()+p2.px())-
            (p1.py()+p2.py())*(p1.py()+p2.py())-
            (p1.pz()+p2.pz())*(p1.pz()+p2.pz()));
  };
  
};
#endif // SIM_GAUSSDECAYTUPLETOOL_H
