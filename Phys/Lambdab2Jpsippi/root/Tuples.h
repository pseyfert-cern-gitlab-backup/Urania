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
#include "Lambdab.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include <string>

static const double DTF_chi2 = 72;//72 ; // (9*8) very loose
static const double MMERR_cut = 3000 ; // very loose
  
   // Neural Net Variables
static const int    dtfc =  0 ; // 2
static const int    pppt =  1 ; // 3 
static const int    pppz =  2 ; // 4
static const int    dira =  3 ; // 5
static const int    psfd =  4 ; // 6
static const int    fdch =  5 ; // 7
static const int    bfce =  6 ; // 8
static const int    pmpt =  7 ; // 9
static const int    nlts =  8 ; // 10 
static const int    bmip =  9 ; // 11
static const int    ppmi =  10 ; // 12
static const int    pmmi =  11 ; // 13
static const int    ppio =  12 ; // 14
static const int    pmio =  13 ; // 15
static const int    pppp =  14 ; // 16
static const int    pppK =  15 ; // 17
static const int    bevc =  16 ; // 18

static const int    bskp =  -1 ;
static const int    pmpK =  -1 ; 
static const int    pppm =  -1 ; 
static const int    prim =  -1 ; 
static const int    bfme =  -1 ;
static const int    pmpp =  -1 ; 



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
static const unsigned int nvar = 17 ;

// Setup
double printFrac(Long64_t n) ;

void fillArray(const int var, const float value, TString name, float* InputArray);

void prepareArray(const unsigned int nvar, float* InputArray, Lambdab* ntuple) ;

unsigned int individualPreproFlag(unsigned int i) ;

bool preselection(Lambdab* ntuple );

bool teaching(Lambdab* ntuple, bool signal );

#endif // ROOT_TUPLES_H
