// ####################################################################################################
// Phys/Bs2JpsiKs Package
// Decay Specific Functions
// Authors: Patrick Koppenburg & Kristof De Bruyn
// ####################################################################################################


// ####################################################################################################
// *** Load Useful Classes ***
#define Bu2JpsiK_2011_cxx
#include "Bu2JpsiK_2011.h"

using namespace std ;

// ####################################################################################################
// *** Initialize ***
void Bu2JpsiK_2011::defineConstants(){
   // Selection Cuts  
   DTF_chi2 = 54 ; //54 ; // (9*6) very loose
   MMERR_cut = 30*1000 ; // very loose - do not cut, for the sake of argument
   cout << "Mass Error cut is set to " << MMERR_cut << " " << (MMERR_cut>50?" !! WARNING!!":"") << endl ;
  
   // Neural Net Variables
   dtfc =  0 ;
   dira =  1 ;
   kppt =  2 ;
   jipc =  3 ;
  
   b0me =    -1 ; // Do NOT use - that's the whole point of B->J/psiK
   b0ta =  4 ;
   bch2 =  5 ;
   ipch =    -1 ;
   ipnx =  6 ;
   bmom =  7 ; 
   b0pt =  8 ; 
   b0te =  9 ; 
   jchi =    -1 ;
   jfdc = 10 ; 
   jmas = 11 ;
   jmme = 12 ;
   jmom = 13 ;
   jppt = 14 ;
   jpsc = 15 ;
   kpid = 16 ;
   kipc = 17 ;
   kpmo = 18 ;
   muic = 19 ;
   muip = 20 ;
   mumo = 21 ;
   mupt = 22 ;
   muid = 23 ;
   mutk = 24 ;
   kagc = 25 ;
   kagp = 26 ;
   katk = 27 ;
   prim = 28 ;
   spdm = 29 ;
   otcl = 30 ; 
   nvar_without_ttype = 31 ;// Variables defined here + 1 (Bmass)
   NNIvar = 4;
}


// ####################################################################################################
// *** Accessors ***
Int_t Bu2JpsiK_2011::TrackType(){return m_LL ;} // Only LONG tracks


// ####################################################################################################
// *** Selection Cuts ***

// Decay Specific
bool Bu2JpsiK_2011::applyDecayCuts(unsigned int pv, unsigned int ttype ){
  bool pass =  true; // No additional cuts so far
  return pass;
};


// Monte Carlo Truth
bool Bu2JpsiK_2011::MCTruth(TString what){
  return (TMath::Abs(B_TRUEID)==521 && Psi_TRUEID==443 && (B_BKGCAT==0 || B_BKGCAT==10));
};


/// Mass regions
bool Bu2JpsiK_2011::teachingRegion(unsigned int pv){ return true ; }; // use all
bool Bu2JpsiK_2011::noSigRegion(unsigned int pv) { return true ; }; // use all


// ####################################################################################################
// *** Data Manipulation ***
void Bu2JpsiK_2011::prepareArray(const unsigned int nvar, float* InputArray, unsigned int pv, unsigned int ttype)
{
  fillArray(dtfc, DTFchi2(pv), "dtfc, B_FullFit_chi2_B", InputArray);
  fillArray(dira, acos(B_DIRA_OWNPV) , "dira, acos(B_DIRA_OWNPV)", InputArray);
  fillArray(kppt, Kplus_PT , "kppt, Kplus_PT", InputArray);  
  fillArray(b0me, B_FullFit_MERR[pv], "b0me, B_FullFit_MERR[pv]", InputArray);
  fillArray(jipc, Psi_MINIPCHI2, "jipc, Psi_MINIPCHI2", InputArray);   
  if(nvar>NNIvar){  
    fillArray(b0ta, B_FullFit_ctau[pv], "b0ta, B_FullFit_ctau[pv]", InputArray);
    fillArray(bch2, B_ENDVERTEX_CHI2/B_ENDVERTEX_NDOF , "bch2, B_ENDVERTEX_CHI2/B_ENDVERTEX_NDOF", InputArray);
    fillArray(ipch, B_IPCHI2_OWNPV , "ipch, B_IPCHI2_OWNPV", InputArray);
    fillArray(ipnx, ( (B_MINIPCHI2NEXTBEST>=0) ? B_MINIPCHI2NEXTBEST : -999.) , "ipnx, B_MINIPCHI2NEXTBEST", InputArray);
    fillArray(bmom, B_P, "bmom, B_P", InputArray);
    fillArray(b0pt, B_PT, "b0pt, B_PT", InputArray); 
    fillArray(b0te, B_FullFit_ctauErr[pv], "b0te, B_FullFit_ctauErr[pv]", InputArray); 
    fillArray(jchi, Psi_ENDVERTEX_CHI2, "jchi, Psi_ENDVERTEX_CHI2", InputArray); 
    fillArray(jfdc, Psi_FDCHI2_ORIVX, "jfdc, Psi_FDCHI2_ORIVX", InputArray);
    fillArray(jmas, fabs(Psi_MM-m_JpsiFittedMass), "mas, Psi_MM-(fitted mass)", InputArray); 
    fillArray(jmme, Psi_MMERR, "jmme, Psi_MMERR", InputArray); 
    fillArray(jmom, Psi_P, "jmom, Psi_P", InputArray); 
    fillArray(jppt, Psi_PT , "jppt, Psi_PT", InputArray);
    fillArray(jpsc, ( (Psi_SMALLESTDELTACHI2>-0.5) ? Psi_SMALLESTDELTACHI2 : -999.), "jpsc, Psi_SMALLESTDELTACHI2", InputArray ) ;
    fillArray(kpid, Kplus_PIDK, "kpid, Kplus_PIDK", InputArray);      
    fillArray(kipc, Kplus_MINIPCHI2 , "kipc, Kplus_MINIPCHI2", InputArray);
    fillArray(kpmo, Kplus_P , "kpmo, Kplus_P", InputArray); 
    fillArray(muic, min(muminus_MINIPCHI2,muplus_MINIPCHI2) , "muic, muminus_MINIPCHI2", InputArray); 
    fillArray(muip, min(muminus_MINIP,muplus_MINIP), "muip, muminus_MINIP", InputArray); 
    fillArray(mumo, min(muminus_P,muplus_P), "mumo, muminus_P", InputArray);
    fillArray(mupt, min(muminus_PT,muplus_PT), "mupt, muminus_PT", InputArray); 
    fillArray(muid, min(muminus_PIDmu,muplus_PIDmu) , "muid, muminus_PIDmu", InputArray);   // > 0
    fillArray(mutk, max(muplus_TRACK_CHI2NDOF,muminus_TRACK_CHI2NDOF) , "mutk, muplus_TRACK_CHI2NDOF", InputArray); 
      /*
        Yes, the 0.5 comes from something in the pattern recognition or 
        whatever and will be gone in Reco 12 / Strip 17
        (at least I don't see it there).
        
        However, yes, technically but all delta functions into -999
        If you have more than one, add a new variable with is, say
        0: value of the other variable is in the "smooth" area
        1: delta function 1
        2: delta function 2
        etc, and use pre-processing option 18
        Then NeuroBayes has the information about the different delta funcs as well.
      */
    double gp = Kplus_TRACK_GhostProb ;
    if (gp<0) {
      fillArray(kagc, 2, "kagc, Kplus_TRACK_GhostProb category", InputArray); // very bad
      fillArray(kagp, -999. , "(kagp, Kplus_TRACK_GhostProb", InputArray); 
    } else if (fabs(gp-0.5)<0.001) {
      fillArray(kagc, 1, "kagc, Kplus_TRACK_GhostProb category", InputArray); // OK but peaking
      fillArray(kagp, -999., "kagp, Kplus_TRACK_GhostProb", InputArray); 
    } else {
      fillArray(kagc, 0, "kagc, Kplus_TRACK_GhostProb category", InputArray); // OK
      fillArray(kagp, gp, "kagp, Kplus_TRACK_GhostProb", InputArray); 
    }
    fillArray(katk, Kplus_TRACK_CHI2NDOF , "katk, Kplus_TRACK_CHI2NDOF", InputArray); 
    fillArray(prim, Primaries , "prim, Primaries", InputArray);
    fillArray(spdm, nSPDHits , "spdm, spdMult", InputArray); 
    fillArray(otcl, nOTClusters , "otcl, OTClusters", InputArray);
  }
  firstFill = false ;
}

// ####################################################################################################
// *** Teacher interaction ***
unsigned int Bu2JpsiK_2011::individualPreproFlag(unsigned int i){ ;
  if ( i==prim || i==kagc ) return 18; // DISCRETE
  else if (i==b0ta || // B0 tau
           i==b0te || // B tau error
           i==b0me || // B mass fit error (strangely)
           i==jipc || // J/psi IP chi2 (strangely) 
           i==jfdc || // J/psi flight chi2
           i==jmme || // J/psi mass error (strangely)
           i==jpsc || // J/psi IP chi2
           i==jmom || // J/psi mometum
           i==kpmo || // K momentum
           i==mumo || // muon momentum
           i==muic || // muon IPC
           i==muip || // muon IP
           i==kipc    // Kaon IPS 
           ) return 34 ; // NOT MONOTONOUS 
  else return 35 ; // MONOTONOUS 
}

// ####################################################################################################
