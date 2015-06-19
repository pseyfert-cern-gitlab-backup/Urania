// $Id: $
#ifndef PKOPPENB_NNTOSWIM_H 
#define PKOPPENB_NNTOSWIM_H 1

// Include files
// from DaVinci, this is a specialized GaudiAlgorithm
#include "Kernel/DVAlgorithm.h"

#include <math.h>

 
/** @class NNToSwim NNToSwim.h pkoppenb/NNToSwim.h
 *  
 *  Bs->J/psiKs to be swum
 *
 *  @author Patrick Koppenburg
 *  @date   2012-04-19
 */
class NNToSwim : public DVAlgorithm {
public: 
  /// Standard constructor
  NNToSwim( const std::string& name, ISvcLocator* pSvcLocator );

  virtual ~NNToSwim( ); ///< Destructor

  virtual StatusCode initialize();    ///< Algorithm initialization
  virtual StatusCode execute   ();    ///< Algorithm execution
  virtual StatusCode finalize  ();    ///< Algorithm finalization

protected:

private:

  // Temporary
  static const double m_JpsiFittedMass = 3099.0 ; // a bit on the high side
  
  // end

  StatusCode prepareArray(const LHCb::Particle* P, 
               const int nvar, 
               float* InputArray, 
               int ttype);
  void fillArray(const int var, const float value, std::string name, float* InputArray) ;//
  

  double m_DTF_chi2 ; // 
  double m_MMERR_cut ; // 
  double m_NN_cut ; // 
  bool m_firstFill ;
  int m_dtfc ; ///< =   0 ; // 9 2nd best
  int m_dira ; ///< =   1 ; // 3 in sigma:  64.5529486
  int m_kspt ; ///< =   2 ;// 20 3rd best
  int m_b0me ; ///< =   3 ; // 7
  int m_jipc ; ///< =   4 ; //11 BEST in sigma: 96
  
  int m_b0ta ; ///< =   5 ; // 2 RINGFENCED in sigma:  1.79424159   -> page 5
  int m_bch2 ; ///< =   6 ; // 4
  int m_ipch ; ///< =     -1 ; // 5 -> behaves strangely
  int m_ipnx ; ///< =   7 ; // 5
  int m_bmom ; ///< =   8 ; // 6
  int m_b0pt ; ///< =   9 ; // 7
  int m_b0te ; ///< =  10 ; // 8
  int m_jchi ; ///< =   -1 ; //10
  int m_jfdc ; ///< =  11 ; // ; //12 -> useless (0.34)
  int m_jmas ; ///< =  12 ; //12
  int m_jmme ; ///< =  13 ; //13
  int m_jmom ; ///< =  14 ; // 13 ; //15 -> useless (0.6)
  int m_jppt ; ///< =  15 ; 
  int m_jpsc ; ///< =  16 ;
  int m_ksez ; ///< =  17 ;// 14
  int m_ksta ; ///< =  18 ;// 21
  int m_ksfd ; ///< =  19 ;// 15
  int m_ksch ; ///< =  20 ;// 16
  int m_kipc ; ///< =  21 ;// 17
  int m_ksmm ; ///< =  22 ;// ; //20 -> Useless (0.16)
  int m_ksme ; ///< =  23 ;// 18
  int m_ksmo ; ///< =  24 ; //19
  int m_muic ; ///< =  25 ;// 22
  int m_muip ; ///< =  26 ; // in sigma:  0.518802103
  int m_mumo ; ///< =  27 ; //23 
  int m_mupt ; ///< =  28 ;// in sigma:  0.962181765
  int m_muid ; ///< =  29 ; //24 
  int m_mutk ; ///< =  30 ;//   in sigma:  0.0157334428
  int m_piic ; ///< =  -1 ;// 25
  int m_piip ; ///< =  31 ;// in sigma:  0.363549249
  int m_pipt ; ///< =  32 ;// in sigma:  0.85242892
  int m_pigp ; ///< =  33 ;// 27
  int m_pigc ; ///< =  34 ;// 26
  int m_pitk ; ///< =  35 ;// 28 
  int m_prim ; ///< =  36 ;// 29 ;
  int m_spdm ; ///< =  37 ;// 30 ; 
  int m_otcl ; ///< =  38; // 31 ;
  int m_nvar_without_ttype ; ///< =  39 ; // 31 ;
  int m_NNIvar ; ///< =  5;

};
#endif // PKOPPENB_NNTOSWIM_H
