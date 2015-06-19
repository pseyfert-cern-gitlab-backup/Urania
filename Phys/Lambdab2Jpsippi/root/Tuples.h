// $Id: $
#ifndef ROOT_TUPLES_H 
#define ROOT_TUPLES_H 1

// Include files

/** @Tuples Tuples.h root/Tuples.h
 *  
 *  Shared Tuple definitions
 *
 *  @author Patrick Koppenburg
 *  @date   2012-07-13
 */

// Lb2Jpsippi Package
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include <string>
#include "TString.h"
#include "TMath.h"
#include "Math/Vector3D.h"
#include "Math/Vector4D.h"
#include "Math/Boost.h"

static const TString c_PsippiName = "PsippiFit" ;
static const TString c_PsipKName = "PsipKFit" ;

static const TString c_PsippiMass = "PsippiMass" ;  // signal
static const TString c_PsipKMass  = "PsipKMass" ;    // control
static const TString c_PsiKpiMass = "PsiKpiMass" ;  // reflection
static const TString c_PsipiKMass = "PsipiKMass" ;  // reflection
static const TString c_PsiKKMass  = "PsiKKMass" ;    // reflection
static const TString c_PsiKpMass  = "PsiKpMass" ;    // reflection
static const TString c_NonPeaking = "NonPeaking" ;  // background
static const TString c_PartReco   = "PartReco" ;  // background
static const TString c_Lambdab    = "Lambdab" ;  // signal
static const TString c_Yield      = "Yield" ;  // signal

static const TString c_Category = "Category" ;
static const TString c_NetOutput = "netOutput" ;
static const TString c_ErrorCode = "ErrorCode" ;
static const TString c_Baryon = "Baryon" ;
static const TString c_pTrueID = "pTrueID" ;
static const TString c_BKGCAT = "BKGCAT" ;
static const TString c_DalitzWeight = "DalitzWeight" ;
static const TString c_PTWeight = "PTWeight" ;
static const TString c_NNEffWeight = "NNEffWeight" ;
static const TString c_All = "All" ;
static const TString c_Opt = "Opt" ;

static const double c_DTF_chi2 = 72;//72 ; // (9*8) very loose
static const double c_MMERR_cut = 20 ; // very loose
static const double c_LambdaMin = 1110 ;
static const double c_LambdaMax = 1120 ;
static const double c_PhiMax = 1035 ;
static const double c_NormMin = 5600  ;
static const double c_NormMax = 5640 ;
static const double c_pplus_Pcut = 0.05 ;
static const double c_piminus_Pcut = 0.05 ;
static const double c_pplus_momcut = 5000. ;
static const double c_piminus_momcut = 3000. ;
static const int c_pID = 2212 ;
static const int c_KID = 321 ;
static const int c_piID = 211 ;
static const int c_muID = 13 ;
// local
static const double c_minMass = 4900 ; ///< lower limit of mass range
static const double c_maxMass = 6100 ; ///< upper limit of mass range
static const double c_minFit  = 5450 ; ///< lower limit of fit 
static const double c_maxFit  = 5770 ; ///< upper limit of fit (above is training)
static const double c_maxFitXib = 5900 ; ///< upper limit of fit with Xib
static const double c_minMCFit  = 5400 ; ///< lower limit of fit 
static const double c_maxMCFit  = 5900 ; ///< upper limit of fit (above is training)
static const double c_minpKFit  = 5300 ; ///< lower limit of fit for pK weigthing
static const double c_maxpKFit  = 6100 ; ///< upper limit of fit for pK weigthing
//static const double c_ppi_minSig  = 5587 ; ///< 5620-33 signal window for Punzi. See cheatSheet-Toy
//static const double c_ppi_maxSig  = 5653 ; ///< 5620+33 signal window for Punzi. See cheatSheet-Toy
static const double c_ppi_minBlind  = 5580 ; ///< Blinding window
static const double c_ppi_maxBlind  = 5650 ; ///< Blinding window

static const double m_psi = 3096.916 ;
static const double m_p   =  938.272 ;
static const double m_pi  =  139.570 ;
static const double m_K   =  493.677 ;
static const double m_Bd  =  5279.5 ;
static const double m_Bs  =  5366.5 ;
static const double m_Lb  =  5620.0 ;
static const double m_W   =    20.0 ;
static const double m_win =   100.0 ;
static const int c_psipK_BKGCAT = 1 ;
static const int c_piK_BKGCAT = 31 ;
static const int c_Kpi_BKGCAT = 32 ;
static const int c_KK_BKGCAT = 33 ;
static const int c_Kp_BKGCAT = 34 ;
static const int c_ppi_BKGCAT = 0 ;
static const unsigned int c_trainFrac = 2 ;
static const unsigned int c_MCtrainFrac = 2 ;
static const double c_vetoFactor = 0.84 ;

static const int m_theSeed = 123456789 ;

// Namespace
namespace ErrorCodes{
  enum EC{ Error = -33 ,
           Teaching = -12,
           Blind = -11 ,
           FailsCuts = -10 ,
           FailsTrigger = -9,
           FailsCategory = -8,
           Lambda = -7,
           Phi = -6,
           Reflection = -5,
           KilledMuCa = -4,
           Splitter = -5,
           OK = 0 };
}
// Namespace
namespace CatCodes{
  enum CC{ SignalCand = 1 ,           
           ElseCand = 0 , 
           pKCand = -1
  };  
}

namespace TrainingType{
  enum TT{ Signal = 1 , 
           Background = -1,
           Weighted = 0};
}


   // Neural Net Variables
static const int    dtfc =   0 ; 
static const int    bfct =   1 ; 
static const int    bevc =   2 ; 
static const int    bmic =   3 ; 
static const int    mmmi =   4 ; 
static const int    pppt =   5 ; 
static const int    pppz =   6 ; 
static const int    ppmi =   7 ; 
static const int    pppp =   8 ; 
static const int    pppK =   9 ; 
static const int    pppi =  10 ; 
static const int    ppri =  -1 ;
static const int    pppc =  -1 ; 
static const int    pppg =  -1 ; 
static const int    pmpt =  11 ; 
static const int    pmpz =  12 ; 
static const int    pmmi =  13 ; 
static const int    pmpc =  -1 ; 
static const int    pmpg =  -1 ; 
static const int    prim  = -1 ; 
static const int    spdm  = 14 ; 
static const int    gpst  = -1 ; // DO NOT USE in MC
static const unsigned int nvar = 15 ;
static const int max_name_length = 50 ; // TString constructor wants int

static const int    psfd =  -1 ; 
static const int    fdch =  -1 ; 
static const int    ppio =  -1 ; 
static const int    pmio =  -1 ;
static const int    bmip =  -1 ; 
static const int    nlts =  -1  ; 
static const int    bskp =  -1 ;
static const int    pmpK =  -1 ; 
static const int    pppm =  -1 ; 
static const int    bfme =  -1 ;
static const int    pmpp =  -1 ;
static const int    bfce =  -1 ; 
static const int    dira =   -1 ;
static const int    kppt =    -1 ;
static const int    bpme =    -1 ;
static const int    jipc =    -1 ;
static const int    bpta =  -1 ;
static const int    bch2 =  -1 ;
static const int    ipch =    -1 ; // -> behaves strangely
static const int    ipnx =    -1 ;
static const int    bmom =    -1 ;
static const int    bppt =    -1 ;
static const int    bpte =    -1 ;
static const int    jchi =    -1 ;
static const int    jfdc =    -1 ;
static const int    jmas =    -1 ; // not to be used
static const int    jmme =    -1 ;
static const int    jmom =    -1 ;
static const int    jppt =    -1 ; 
static const int    jpsc =    -1 ; // -> All values < -0.5
static const int    kipc =  -1 ;
static const int    kpmo =    -1 ;
static const int    kpid =  -1 ;
static const int    epic =  -1 ;
static const int    emic =  -1 ;
static const int    elip =    -1 ;
static const int    elmo =    -1 ;
static const int    elpt =    -1 ;
static const int    emid =  -1 ;
static const int    epid =  -1 ;
static const int    eltk =    -1 ;// not when tuning on MC
//static const int    spdm =  -1 ; 
static const int    otcl =  -1 ;// DO NOT USE

void make_canvas() ;
void printLHCb(const char* optLR="L", const char* optPrelim="Final", const char* optText="");


#endif // ROOT_TUPLES_H
