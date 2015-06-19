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

static const TString c_PsippiMass = "PsippiMass" ;
static const TString c_PsipKMass = "PsipKMass" ;
static const TString c_PsiKpiMass = "PsiKpiMass" ;
static const TString c_Category = "Category" ;
static const TString c_NetOutput = "netOutput" ;
static const TString c_ErrorCode = "ErrorCode" ;
static const TString c_Baryon = "Baryon" ;

static const double c_DTF_chi2 = 72;//72 ; // (9*8) very loose
static const double c_MMERR_cut = 20 ; // very loose
static const double c_LambdaMin = 1110 ;
static const double c_LambdaMax = 1120 ;
static const double c_NormMin = 5600  ;
static const double c_NormMax = 5640 ;
static const double c_pplus_Pcut = 0.1 ;
// local
static const double c_ppi_minMass = 4900 ; ///< lower limit of mass range
static const double c_ppi_maxMass = 6100 ; ///< upper limit of mass range
static const double c_ppi_minFit  = 5500 ; ///< lower limit of fit 
static const double c_ppi_maxFit  = 5800 ; ///< upper limit of fit (above is training)
//static const double c_ppi_minSig  = 5587 ; ///< 5620-33 signal window for Punzi. See cheatSheet-Toy
//static const double c_ppi_maxSig  = 5653 ; ///< 5620+33 signal window for Punzi. See cheatSheet-Toy

static const double m_psi = 3096.916 ;
static const double m_p   =  938.272 ;
static const double m_pi  =  139.570 ;
static const double m_K   =  493.677 ;
static const double m_Bd  =  5279.5 ;
static const double m_Bs  =  5366.5 ;
static const double m_Lb  =  5620.0 ;
static const double m_W   =    20.0 ;
static const int c_psipK_BKGCAT = 1 ;

// Namespace
namespace ErrorCodes{
  enum EC{ Error = -33 ,
           FailsCuts = -9 ,
           KilledMuCa = -8,
           FailsTrigger = -7,
           Splitter = -5,
           OK = 0 };
}
// Namespace
namespace CatCodes{
  enum CC{ SignalCand = 1 ,           
           ElseCand = 0 , 
           pKCand = -1,
           Reflection = -2, 
           Lambda = -3 };
}

   // Neural Net Variables
static const int    dtfc =   0 ; 
static const int    bfct =   1 ; 
static const int    bevc =   2 ; 
static const int    bmic =   3 ; 
static const int    pppt =   4 ; 
static const int    pppz =   5 ; 
static const int    ppmi =   6 ; 
static const int    pppp =   7 ; 
static const int    pppK =   8 ; 
static const int    pppi =   9 ; 
static const int    ppri =  10 ;
static const int    pppc =  -1 ; 
static const int    pppg =  11 ; 
static const int    pmpt =  12 ; 
static const int    pmpz =  13 ; 
static const int    pmmi =  14 ; 
static const int    pmpc =  -1 ; 
static const int    pmpg =  15 ; 
static const int    prim  = 16 ; 
static const unsigned int nvar = 17 ;
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
static const int    spdm =  -1 ; // DO NOT USE
static const int    otcl =  -1 ;// DO NOT USE

void make_canvas() ;
void printLHCb(char* optLR="L", char* optPrelim="Final", char* optText="");


#endif // ROOT_TUPLES_H
