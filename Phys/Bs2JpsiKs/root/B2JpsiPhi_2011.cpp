// ####################################################################################################
// Phys/Bs2JpsiKs Package
// Decay Specific Functions
// Authors: Patrick Koppenburg & Kristof De Bruyn
// ####################################################################################################


// ####################################################################################################
// *** Load Useful Classes ***
#define B2JpsiPhi_2011_cxx
#include "B2JpsiPhi_2011.h"

using namespace std ;

// ####################################################################################################
// *** Initialize ***
void B2JpsiPhi_2011::defineConstants(){
   // Selection Cuts
   DTF_chi2 = 72 ; // (9*8) very loose
   MMERR_cut = 30 ; // very loose
  
   // Neural Net Variables
   dtfc =  0 ;
   dira =  1 ;
   phpt =  2 ;
   b0me =  3 ;
   jipc =  4 ;
  
   b0ta =  5 ;
   bch2 =  6 ;
   ipch =    -1 ; // -> behaves strangely
   ipnx =  7 ;
   bmom =  8 ;
   b0pt =  9 ;
   b0te = 10 ;
   jchi =    -1 ;
   jfdc = 11 ;
   jmas = 12 ;
   jmme = 13 ;
   jmom = 14 ;
   jppt = 15 ; 
   jpsc = 16 ;
   phez = 17 ;
   phch = 18 ;
   pipc = 19 ;
   phmm = 20 ;
   phme = 21 ;
   phmo = 22 ;
   muic = 23 ;
   muip = 24 ;
   mumo = 25 ;
   mupt = 26 ;
   muid = 27 ; 
   mutk = 28 ;
   kaic =    -1 ;
   kaip = 29 ;
   kapt = 30 ;
   kagp = 31 ;
   kagc = 32 ;
   katk = 33 ; 
   prim = 34 ;
   spdm = 35 ; 
   otcl = 36 ; 
   nvar_without_ttype = 37 ; // Variables defined here + 1 (Bmass)
   NNIvar = 5;
}

// ####################################################################################################
// *** Accessors ***
Int_t B2JpsiPhi_2011::TrackType(){return Kplus_TRACK_Type ;}

// ####################################################################################################
// *** Selection Cuts ***

// Decay Specific
bool B2JpsiPhi_2011::applyDecayCuts(unsigned int pv, unsigned int ttype ){
  bool pass =  true; // No additional cuts so far
  return pass;
};


// Monte Carlo Truth
bool B2JpsiPhi_2011::MCTruth(TString what){
  return (TMath::Abs(B_TRUEID)==511 && Psi_TRUEID==443 && phi_1020_TRUEID==333 && (B_BKGCAT==0 || B_BKGCAT==10));
};

//  Mass regions
bool B2JpsiPhi_2011::teachingRegion(unsigned int pv){ 
  return ( mass(pv) < BdBox_min || mass(pv) > BdBox_max ) ; }; // Exclude Bd
bool B2JpsiPhi_2011::noSigRegion(unsigned int pv) { 
  return ( mass(pv) > sideband_high_min() || mass(pv) < BdBox_max ) ; // Exclude Bd - wider region
};   

// ####################################################################################################
// *** Data Manipulation ***
void B2JpsiPhi_2011::prepareArray(const unsigned int nvar, float* InputArray, unsigned int pv, unsigned int ttype){

  fillArray(dtfc, DTFchi2(pv), "B_FullFit_chi2", InputArray);
  fillArray(dira, acos(B_DIRA_OWNPV) , "acos(B_DIRA_OWNPV)", InputArray);
  fillArray(phpt , phi_1020_PT , "phi_1020_PT", InputArray);  
  fillArray(b0me, B_FullFit_MERR[pv], "B_FullFit_MERR[pv]", InputArray);
  fillArray(jipc, Psi_MINIPCHI2, "Psi_MINIPCHI2", InputArray);
  if(nvar>NNIvar){  
    fillArray(b0ta, B_FullFit_ctau[pv], "B_FullFit_ctau[pv]", InputArray);
    fillArray(bch2, B_ENDVERTEX_CHI2/B_ENDVERTEX_NDOF , "B_ENDVERTEX_CHI2/B_ENDVERTEX_NDOF", InputArray);
    fillArray(ipch, B_IPCHI2_OWNPV , "B_IPCHI2_OWNPV", InputArray);
    fillArray(ipnx, ( (B_MINIPCHI2NEXTBEST>=0) ? B_MINIPCHI2NEXTBEST : -999.) , "B_MINIPCHI2NEXTBEST", InputArray);
    fillArray(bmom, B_P, "B_P", InputArray);
    fillArray(b0pt, B_PT, "B_PT", InputArray); 
    fillArray(b0te, B_FullFit_ctauErr[pv], "B_FullFit_ctauErr[pv]", InputArray); 
    fillArray(jchi, Psi_ENDVERTEX_CHI2, "Psi_ENDVERTEX_CHI2", InputArray); 
    fillArray(jfdc, Psi_FDCHI2_ORIVX, "Psi_FDCHI2_ORIVX", InputArray);
    fillArray(jmas , fabs(Psi_MM-3096.916), "Psi_MM-3096.916", InputArray); 
    fillArray(jmme , Psi_MMERR, "Psi_MMERR", InputArray); 
    fillArray(jmom, Psi_P, "Psi_P", InputArray); 
    fillArray(jppt , Psi_PT , "Psi_PT", InputArray); 
    fillArray(jpsc, ( (Psi_SMALLESTDELTACHI2>-0.5) ? Psi_SMALLESTDELTACHI2 : -999.), "", InputArray ) ;
    fillArray(phez, phi_1020_ENDVERTEX_Z, "phi_1020_ENDVERTEX_Z", InputArray);      
    fillArray(phch, phi_1020_ENDVERTEX_CHI2, "phi_1020_ENDVERTEX_CHI2", InputArray); 
    fillArray(pipc, phi_1020_MINIPCHI2 , "phi_1020_MINIPCHI2", InputArray);
    fillArray(phmm , fabs(phi_1020_MM-1020), "fabs(phi_1020_MM-1020)", InputArray); 
    fillArray(phme , phi_1020_MMERR, "phi_1020_MMERR", InputArray); 
    fillArray(phmo , phi_1020_P , "phi_1020_P", InputArray); 
    fillArray(muic, min(muminus_MINIPCHI2,muplus_MINIPCHI2) , "muminus_MINIPCHI2", InputArray); 
    fillArray(muip, min(muminus_MINIP,muplus_MINIP), "muminus_MINIP", InputArray); 
    fillArray(mumo , min(muminus_P,muplus_P), "muminus_P", InputArray);
    fillArray(mupt , min(muminus_PT,muplus_PT), "muminus_PT", InputArray); 
    fillArray(muid, min(muminus_PIDmu,muplus_PIDmu) , "muminus_PIDmu", InputArray);
    fillArray(mutk, max(muplus_TRACK_CHI2NDOF,muminus_TRACK_CHI2NDOF) , "muplus_TRACK_CHI2NDOF", InputArray); 
    fillArray(kaic, min(Kminus_MINIPCHI2,Kplus_MINIPCHI2), "Kminus_MINIPCHI2", InputArray); 
    fillArray(kaip, min(Kminus_MINIP,Kplus_MINIP), "Kminus_MINIP", InputArray); 
    fillArray(kapt, min(Kminus_PT,Kplus_PT), "Kminus_PT", InputArray); 
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
    double gp = Kminus_TRACK_GhostProb ;
    if ( Kplus_TRACK_GhostProb > gp) gp = Kplus_TRACK_GhostProb; // max gp
    if (gp<0) {
      fillArray(kagc, 2, "Kplus_TRACK_GhostProb category", InputArray); // very bad
      fillArray(kagp, -999. , "Kplus_TRACK_GhostProb", InputArray); 
    } else if (fabs(gp-0.5)<0.001) {
      fillArray(kagc, 1, "Kplus_TRACK_GhostProb category", InputArray); // OK but peaking
      fillArray(kagp, -999., "Kplus_TRACK_GhostProb", InputArray); 
    } else {
      fillArray(kagc, 0, "Kplus_TRACK_GhostProb category", InputArray); // OK
      fillArray(kagp, gp, "Kplus_TRACK_GhostProb", InputArray); 
    }
    fillArray(katk, max(Kplus_TRACK_CHI2NDOF,Kminus_TRACK_CHI2NDOF) , "Kplus_TRACK_CHI2NDOF", InputArray); 
    fillArray(prim, Primaries , "Primaries", InputArray);
    fillArray(spdm, spdMult , "spdMult", InputArray); 
    fillArray(otcl, OTClusters , "OTClusters", InputArray);
    if (ttype==m_ANY && nvar>NNIvar){
      if ( nvar!=nvar_without_ttype+1) cout << "ERROR! var = " << nvar << ", expect: " << nvar_without_ttype+1 << endl;
      fillArray( nvar-1 , Kminus_TRACK_Type, "Kminus_TRACK_Type", InputArray); 
    } else if ( nvar!=nvar_without_ttype && nvar!=NNIvar) cout << "ERROR! var = " << nvar << endl;
  }
  firstFill = false ;
}


// ####################################################################################################
// *** Teacher interaction ***
unsigned int B2JpsiPhi_2011::individualPreproFlag(unsigned int i){ ;
  if (i==nvar_without_ttype || i==prim || i==kagc ) return 18; // DISCRETE
  else if (i==b0ta || // B0 tau
           i==b0me || // B mass fit error (strangely)
           i==jipc || // J/psi IP chi2 (strangely) 
           i==jfdc || // J/psi flight chi2
           i==jmme || // J/psi mass error (strangely)
           i==jmom || // J/psi mometum
           i==phez || // Phi endvertex z
           i==phmo || // Phi momentum
           i==mumo || // muon momentum
           i==muic || // muon momentum
           i==kaip    // kaon IP
          ) return 34 ; // NOT MONOTONOUS 
  else return 35 ;
}
// ####################################################################################################

