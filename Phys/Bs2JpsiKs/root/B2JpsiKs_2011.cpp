// ####################################################################################################
// Phys/Bs2JpsiKs Package
// Decay Specific Functions
// Authors: Patrick Koppenburg & Kristof De Bruyn
// ####################################################################################################


// ####################################################################################################
// *** Load Useful Classes ***
#define B2JpsiKs_2011_cxx
#include "B2JpsiKs_2011.h"

using namespace std ;

// ####################################################################################################
// *** Initialize ***
void B2JpsiKs_2011::defineConstants(){
   // Selection Cuts
   DTF_chi2 = 72 ; // 128 ; // (9*8) very loose
   MMERR_cut = 30 ; // very loose
  
   // Neural Net Variables
   dtfc =  0 ;
   dira =  1 ;
   kspt =  2 ;
   b0me =  3 ;
   jipc =  4 ;
  
   b0ta =  5 ;
   bch2 =  6 ;
   ipch =    -1 ; // -> behaves strangely
   ipnx =    -1 ;
   bmom =  7 ;
   b0pt =  8 ;
   b0te =  9 ;
   jchi =    -1 ;
   jfdc = 10 ;
   jmas = 11 ;
   jmme = 12 ;
   jmom = 13 ;
   jppt = 14 ; 
   jpsc =    -1 ; // -> All values < -0.5
   ksez = 15 ;
   ksta = 16 ;
   ksfd = 17 ;
   ksch = 18 ;
   kipc = 19 ;
   ksmm = 20 ;
   ksme = 21 ;
   ksmo = 22 ;
   muic = 23 ;
   muip = 24 ;
   mumo = 25 ;
   mupt = 26 ;
   muid = 27 ;
   mutk = 28 ;
   piic =    -1 ;
   piip = 29 ;
   pipt = 30 ;
   pigp = 31 ;
   pigc = 32 ;
   pitk = 33 ; 
   prim = 34 ;
   spdm = 35 ; 
   otcl = 36 ;
   nvar_without_ttype = 37 ; // Variables defined here + 1 (Bmass)
   NNIvar = 5;
}


// ####################################################################################################
// *** Accessors ***
Int_t B2JpsiKs_2011::TrackType(){return piplus_TRACK_Type ;}


// ####################################################################################################
// *** Selection Cuts ***

// Decay Specific
bool B2JpsiKs_2011::applyDecayCuts(unsigned int pv, unsigned int ttype ){
  Double_t Kstar_minMass = TMath::Sqrt(pow(Psi_PE + piplus_PE
    + TMath::Sqrt(pow(m_Kplus,2) + pow(piminus_PX,2) + pow(piminus_PY,2) + pow(piminus_PZ,2)),2)
    - pow(Psi_PX+piplus_PX+piminus_PX,2) - pow(Psi_PY+piplus_PY+piminus_PY,2) - pow(Psi_PZ+piplus_PZ+piminus_PZ,2));
  Double_t Kstar_plusMass = TMath::Sqrt(pow(Psi_PE + piminus_PE
    + TMath::Sqrt(pow(m_Kplus,2) + pow(piplus_PX,2) + pow(piplus_PY,2) + pow(piplus_PZ,2)),2)
    - pow(Psi_PX+piplus_PX+piminus_PX,2) - pow(Psi_PY+piplus_PY+piminus_PY,2) - pow(Psi_PZ+piplus_PZ+piminus_PZ,2));

 bool pass = ((piplus_TRACK_Type==ttype || 0==ttype ) &&
              (piplus_TRACK_Type==m_DD || (piplus_TRACK_Type==m_LL && 
              std::abs(Kstar_minMass-m_BdPDG)>KstarVeto && std::abs(Kstar_plusMass-m_BdPDG)>KstarVeto)) &&
              std::abs(KS0_M_with_pplus_piplus-1116)>2*piplus_TRACK_Type && 
              std::abs(KS0_M_with_piplus_pplus-1116)>2*piplus_TRACK_Type &&
              B_FullFit_KS0_ctau[pv]/B_FullFit_KS0_ctauErr[pv]>5); // mean ctau is 2.68 cm
 // std::cout << "applyDecayCuts " << pass << std::endl ;
 return pass;
};


// Monte Carlo Truth
bool B2JpsiKs_2011::MCTruth(TString what){
  bool pass = false;
  if(what==m_SigBd || what==m_SigBdPrescaled){
    pass = (TMath::Abs(B_TRUEID)==511 && Psi_TRUEID==443 && KS0_TRUEID==310 && (B_BKGCAT==0 || B_BKGCAT==10));
  } else if(what==m_SigBs || what==m_SigBsPrescaled){
    pass = (TMath::Abs(B_TRUEID)==531 && Psi_TRUEID==443 && KS0_TRUEID==310 && B_BKGCAT==20);
  } else if(what==m_SigKstar || what==m_SigKstarWM){
    pass = (TMath::Abs(B_TRUEID)==511 && Psi_TRUEID==443 && TMath::Abs(KS0_TRUEID)==313 && B_BKGCAT==30);
  }
  //  std::cout << "MCTruth " << pass << std::endl ;
  return pass ;
	  
};


// Mass regions
bool B2JpsiKs_2011::teachingRegion(unsigned int pv){ 
  return ( mass(pv) < BsBox_min || mass(pv) > BsBox_max ) ; }; // Exclude Bs
bool B2JpsiKs_2011::noSigRegion(unsigned int pv) { 
  return ( mass(pv) > sideband_high_min() ||mass(pv) < BdBox_max ) ; }; // Exclude Bs - wider region



// ####################################################################################################
// *** Data Manipulation ***
void B2JpsiKs_2011::prepareArray(const unsigned int nvar, float* InputArray, unsigned int pv, unsigned int ttype){

  fillArray(dtfc, DTFchi2(pv), "dtfc, B_FullFit_chi2", InputArray);
  fillArray(dira, acos(B_DIRA_OWNPV) , "dira, acos(B_DIRA_OWNPV)", InputArray);
  fillArray(kspt , KS0_PT , "kspt, KS0_PT", InputArray);  
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
    fillArray(jmas , fabs(Psi_MM-m_JpsiFittedMass), "jmas, Psi_MM-fitted", InputArray); 
    fillArray(jmme , Psi_MMERR, "jmme, Psi_MMERR", InputArray); 
    fillArray(jmom, Psi_P, "jmom, Psi_P", InputArray); 
    fillArray(jppt , Psi_PT , "jppt, Psi_PT", InputArray);
    fillArray(jpsc, ( (Psi_SMALLESTDELTACHI2>-0.5) ? Psi_SMALLESTDELTACHI2 : -999.), "jpsc, Psi_SMALLESTDELTACHI2", InputArray ) ;
    fillArray(ksez, KS0_ENDVERTEX_Z, "ksez, KS0_ENDVERTEX_Z", InputArray);      
    fillArray(ksta , B_FullFit_KS0_ctau[pv] , "ksta, B_FullFit_KS0_ctau[pv]", InputArray); 
    fillArray(ksfd, B_FullFit_KS0_ctau[pv]/B_FullFit_KS0_ctauErr[pv],
                "ksfd, B_FullFit_KS0_ctau[pv]/B_FullFit_KS0_ctauErr[pv]", InputArray); 
    fillArray(ksch, KS0_ENDVERTEX_CHI2, "ksch, KS0_ENDVERTEX_CHI2", InputArray); 
    fillArray(kipc, KS0_MINIPCHI2 , "kipc, KS0_MINIPCHI2", InputArray);
    fillArray(ksmm , fabs(KS0_MM-497.614), "ksmm, fabs(KS0_MM-497.614)", InputArray); 
    fillArray(ksme , KS0_MMERR, "ksme, KS0_MMERR", InputArray); 
    fillArray(ksmo , KS0_P , "ksmo, KS0_P", InputArray); 
    fillArray(muic, min(muminus_MINIPCHI2,muplus_MINIPCHI2) , "muic, muminus_MINIPCHI2", InputArray); 
    fillArray(muip, min(muminus_MINIP,muplus_MINIP), "muip, muminus_MINIP", InputArray); 
    fillArray(mumo , min(muminus_P,muplus_P), "mumo, muminus_P", InputArray);
    fillArray(mupt , min(muminus_PT,muplus_PT), "mupt, muminus_PT", InputArray); 
    fillArray(muid, min(muminus_PIDmu,muplus_PIDmu) , "muid, muminus_PIDmu", InputArray); 
    fillArray(mutk, max(muplus_TRACK_CHI2NDOF,muminus_TRACK_CHI2NDOF) , "mutk, muplus_TRACK_CHI2NDOF", InputArray); 
    fillArray(piic, min(piminus_MINIPCHI2,piplus_MINIPCHI2), "piic piminus_MINIPCHI2", InputArray); 
    fillArray(piip, min(piminus_MINIP,piplus_MINIP), "piip, piminus_MINIP", InputArray); 
    fillArray(pipt, min(piminus_PT,piplus_PT), "pipt, piminus_PT", InputArray); 
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
    double gp = piminus_TRACK_GhostProb ;
    if ( piplus_TRACK_GhostProb > gp) gp = piplus_TRACK_GhostProb; // max gp
    if (gp<0) {
      fillArray(pigc, 2, "pigc, piplus_TRACK_GhostProb category", InputArray); // very bad
      fillArray(pigp, -999. , "pigp, piplus_TRACK_GhostProb", InputArray); 
    } else if (fabs(gp-0.5)<0.001) {
      fillArray(pigc, 1, "pigc, piplus_TRACK_GhostProb category", InputArray); // OK but peaking
      fillArray(pigp, -999., "pigp, piplus_TRACK_GhostProb", InputArray); 
    } else {
      fillArray(pigc, 0, "pigc, piplus_TRACK_GhostProb category", InputArray); // OK
      fillArray(pigp, gp, "pigp, piplus_TRACK_GhostProb", InputArray); 
    }
    fillArray(pitk, max(piplus_TRACK_CHI2NDOF,piminus_TRACK_CHI2NDOF) , "piplus_TRACK_CHI2NDOF", InputArray); 
    fillArray(prim, nPVs , "prim, Primaries", InputArray);
    fillArray(spdm, nSPDHits , "spdm, nSPDHits", InputArray); 
    fillArray(otcl, nOTClusters , "otcl, nOTClusters", InputArray);
    if (ttype==m_ANY && nvar>NNIvar){
      if ( nvar!=nvar_without_ttype+1) cout << "ERROR! var = " << nvar << ", expect: " << nvar_without_ttype+1 << endl;
      fillArray( nvar-1 , piminus_TRACK_Type, "piminus_TRACK_Type", InputArray); 
    } else if ( nvar!=nvar_without_ttype && nvar!=NNIvar) cout << "ERROR! var = " << nvar << endl;
  }
  firstFill = false ;
}
             

// ####################################################################################################
// *** Teacher interaction ***
unsigned int B2JpsiKs_2011::individualPreproFlag(unsigned int i){ ;
  if (i==nvar_without_ttype || i==prim || i==pigc ) return 18; // DISCRETE
  else if (i==b0ta || // B0 tau
           i==bmom || // B0 momentum
           i==b0me || // B mass fit error (strangely)
           i==jipc || // J/psi IP chi2 (strangely) 
           i==jfdc || // J/psi flight chi2
           i==jmme || // J/psi mass error (strangely)
           i==jmom || // J/psi mometum
           i==ksez || // Ks endvertex z
           i==ksfd || // Ks FD
           i==ksmo || // Ks momentum
           i==ksta || // Ks lifetime
           i==mumo || // muon momentum
           i==muic || // muon IP chi2
           i==muip || // muon IP
           i==piip || // pion IP
           i==prim    // primaries (more is good if spd is low)
          ) return 34 ; // NOT MONOTONOUS 
  else return 35 ;
}
// ####################################################################################################
