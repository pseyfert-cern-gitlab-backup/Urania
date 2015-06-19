// $Id: $
// Include files

// local
#include "Tuples.h"
using namespace std ;
bool firstFill = true ;
//-----------------------------------------------------------------------------
// Implementation file for class : Tuples
//
// 2012-07-13 : Patrick Koppenburg
//-----------------------------------------------------------------------------

void fillArray(const int var, const float value, TString name, float* InputArray){
  if (var>=0) {
    InputArray[var] = value;
    if (firstFill) std::cout << "Filling variable " << var+2 << " (ID " << 
      var << ", page " << var+5 << ") ``" << name << "'' with " << value << std::endl ;
  } else {
    if (firstFill) std::cout << "Ignoring variable ``" << name << "''" << std::endl ;
  }    
};

void prepareArray(const unsigned int nvar, float* InputArray, Lambdab* ntuple){

	
  unsigned int pv = 0 ;

  fillArray(dtfc, ntuple->Manage_B_FullFit_chi2_B(pv), "dtfc, B_FullFit_chi2_B", InputArray);
  fillArray(dira, acos(ntuple->B_DIRA_OWNPV) , "dira, acos(B_DIRA_OWNPV)", InputArray);
  fillArray(fdch, ntuple->B_FDCHI2_OWNPV , "fdch, B_FDCHI2_OWNPV", InputArray);
  fillArray(bfce, ntuple->B_FullFit_ctauErr[pv] , "bfce, B_FullFit_ctauErr", InputArray);
//  fillArray(bfme, ntuple->B_FullFit_MERR[pv] , "bfme, B_FullFit_MERR[pv]", InputArray); // Patdrick's removal
  fillArray(bmip, ntuple->B_MINIPCHI2 , "bmip, B_MINIPCHI2", InputArray);
  fillArray(bevc, ntuple->B_ENDVERTEX_CHI2 , "bevc, B_ENDVERTEX_CHI2", InputArray); // Patrick's addition
//  fillArray(bskp, ntuple->B_SubKpi_ctauErr[pv], "bskp, B_SubKpi_ctauErr", InputArray);

  fillArray(pppt, ntuple->pplus_PT , "pppt, pplus_PT", InputArray);
  fillArray(pppz, ntuple->pplus_PZ , "pppz, pplus_PZ", InputArray);
//  fillArray(pppe, ntuple->pplus_PE , "pppe, pplus_PE", InputArray);
  fillArray(pppp, ntuple->pplus_PIDp , "pppp, pplus_PIDp", InputArray);
  fillArray(pppK, ntuple->pplus_PIDp-ntuple->pplus_PIDK , "pppK, pplus_PIDK-pplus_PIDK", InputArray);
//  fillArray(pppm, ntuple->pplus_PIDmu , "pppm, pplus_PIDmu", InputArray);
  fillArray(ppio, ntuple->pplus_IPCHI2_ORIVX , "ppio, pplus_IPCHI2_ORIVX", InputArray); // Patdrick's removal
  fillArray(ppmi, ntuple->pplus_MINIPCHI2 , "ppmi, pplus_MINIPCHI2", InputArray);
//  fillArray(ppoc, ntuple->pplus_ORIVX_CHI2 , "ppoc, pplus_ORIVX_CHI2", InputArray);
//  fillArray(pptc, ntuple->pplus_TRACK_CHI2NDOF , "pptc, pplus_TRACK_CHI2NDOF", InputArray); // Patrick's addition
//  fillArray(pptg, ntuple->pplus_TRACK_GhostProb , "pptg, pplus_TRACK_GhostProb", InputArray); // Patrick's addition

//   have a look pplus_TRACK_CHI2NDOF, pplus_TRACK_GhostProb 

//  fillArray(pmpz, ntuple->piminus_PZ , "pmpz, piminus_PZ", InputArray);
  fillArray(pmpt, ntuple->piminus_PT , "pmpt, piminus_PT", InputArray);
//  fillArray(pmpp, ntuple->piminus_PIDp , "pmpp, piminus_PIDp", InputArray);
//  fillArray(pmpK, ntuple->piminus_PIDK , "pmpK, piminus_PIDK", InputArray);
  fillArray(pmio, ntuple->piminus_IPCHI2_ORIVX , "pmio, piminus_IPCHI2_ORIVX", InputArray); // Patdrick's removal
  fillArray(pmmi, ntuple->piminus_MINIPCHI2 , "pmmi, piminus_MINIPCHI2", InputArray);
//  fillArray(pmoc, ntuple->piminus_ORIVX_CHI2 , "pmoc, piminus_ORIVX_CHI2", InputArray);
//  fillArray(pmtc, ntuple->piminus_TRACK_CHI2NDOF , "pmtc, piminus_TRACK_CHI2NDOF", InputArray); // Patrick addition
//  fillArray(pmtg, ntuple->piminus_TRACK_GhostProb , "pmtg, piminus_TRACK_GhostProb", InputArray); // Patrick's addition

  fillArray(psfd, ntuple->Psi_FD_OWNPV , "psfd, Psi_FD_OWNPV", InputArray);
//  fillArray(psox, ntuple->Psi_ORIVX_CHI2 , "psox, Psi_ORIVX_CHI2", InputArray); correlates with bevc

//  fillArray(psmd , fabs(ntuple->Psi_MM-3099), "psmd, Psi_MM-3099", InputArray); //Patrick's addition 

//  fillArray(ttcd, ntuple->totCandidates , "ttcd, totCandidates", InputArray);  
  fillArray(nlts, ntuple->nLongTracks , "nlts, nLongTracks", InputArray);
//  fillArray(prim, ntuple->Primaries , "prim, Primaries", InputArray);

  
  /*
  fillArray(bpta, ntuple->B_FullFit_ctau[pv], "bpta, B_FullFit_ctau[0]", InputArray);
  fillArray(jmas , fabs(ntuple->Psi_MM), "jmas, Psi_MM-fitted", InputArray); 
  
  fillArray(kppt, ntuple->Kplus_PT , "kppt, K_PT", InputArray);  
  fillArray(bpme, ntuple->B_FullFit_MERR[pv], "bpme, B_FullFit_MERR[pv]", InputArray);
  fillArray(jipc, ntuple->Psi_MINIPCHI2, "jipc, Psi_MINIPCHI2", InputArray);

  fillArray(bch2, ntuple->B_ENDVERTEX_CHI2/ntuple->B_ENDVERTEX_NDOF , "bch2, B_ENDVERTEX_CHI2/B_ENDVERTEX_NDOF", InputArray);
  fillArray(ipch, ntuple->B_IPCHI2_OWNPV , "ipch, B_IPCHI2_OWNPV", InputArray);
  fillArray(ipnx, ( (ntuple->B_MINIPCHI2NEXTBEST>=0) ? ntuple->B_MINIPCHI2NEXTBEST : -999.) , 
            "ipnx, B_MINIPCHI2NEXTBEST", InputArray);  
  fillArray(bmom, ntuple->B_P, "bmom, B_P", InputArray);
  fillArray(bppt, ntuple->B_PT, "bppt, B_PT", InputArray); 
  fillArray(bpte, ntuple->B_FullFit_ctauErr[pv], "bpte, B_FullFit_ctauErr[pv]", InputArray); 
  fillArray(jchi, ntuple->Psi_ENDVERTEX_CHI2, "jchi, Psi_ENDVERTEX_CHI2", InputArray); 
  fillArray(jfdc, ntuple->Psi_FDCHI2_ORIVX, "jfdc, Psi_FDCHI2_ORIVX", InputArray);
  fillArray(jmme , ntuple->Psi_MMERR, "jmme, Psi_MMERR", InputArray); 
  fillArray(jmom, ntuple->Psi_P, "jmom, Psi_P", InputArray); 
  fillArray(jppt , ntuple->Psi_PT , "jppt, Psi_PT", InputArray);
  fillArray(jpsc, ( (ntuple->Psi_SMALLESTDELTACHI2>-0.5) ? ntuple->Psi_SMALLESTDELTACHI2 : -999.), 
            "jpsc, Psi_SMALLESTDELTACHI2", InputArray ) ;
  fillArray(kipc, ntuple->Kplus_MINIPCHI2 , "kipc, Kplus_MINIPCHI2", InputArray);
  fillArray(kpmo , ntuple->Kplus_P , "kpmo, Kplus_P", InputArray); 
  fillArray(kpid , ntuple->Kplus_ProbNNk , "kpid, Kplus_ProbNNk", InputArray); 
  fillArray(epic, ntuple->eplus_MINIPCHI2, "epic, eplus_MINIPCHI2", InputArray); 
  fillArray(emic, ntuple->eminus_MINIPCHI2, "emic, eminus_MINIPCHI2", InputArray); 
  fillArray(elip, min(ntuple->eminus_MINIP,ntuple->eplus_MINIP), "elip, eminus_MINIP", InputArray); 
  fillArray(elmo , min(ntuple->eminus_P,ntuple->eplus_P), "elmo, eminus_P", InputArray);
  fillArray(elpt , min(ntuple->eminus_PT,ntuple->eplus_PT), "elpt, eminus_PT", InputArray); 
  fillArray(emid, ntuple->eminus_ProbNNe , "emid, eminus_ProbNNe", InputArray); 
  fillArray(epid, ntuple->eplus_ProbNNe , "epid, eplus_ProbNNe", InputArray); 
  fillArray(eltk, max(max(ntuple->eplus_TRACK_CHI2NDOF,ntuple->eminus_TRACK_CHI2NDOF),ntuple->Kplus_TRACK_CHI2NDOF) , 
            "eltk, eplus_TRACK_CHI2NDOF", InputArray); 
  
  fillArray(spdm, ntuple->nSPDHits , "spdm, nSPDHits", InputArray); 
  fillArray(otcl, ntuple->nOTClusters , "otcl, nOTClusters", InputArray);
  */
  
  firstFill = false ;
   
}

unsigned int individualPreproFlag(unsigned int i){ ;

  if ( prim==i) return 19; // DISCRETE, ordered
  else if (    pppz==i    // p Pz
//            || bmip==i // B minip
            || bfce==i // B full fit ctau Err
//            || pmpz==i // pi Pz
            || pmpt==i // pi Pt
            || bskp==i // B sub K pi ctau Err
            || pmpK==i // pi PID K
            || pppm==i // p PID mu
            ) return 34 ; // not monotonous
  else return 35 ; // monotonous (default)

//  if (prim==i) return 19; // DISCRETE, ordered
//  /*else*/ return 34 ; // not monotonous (default)

}

// ####################################################################################################
// selections
bool preselection(Lambdab* ntuple ){ // more cuts here !!!
// veto psi at some point ??? what was this??? 
//  if (ntuple->pplus_PIDp < 21) return false ;
//  if (ntuple->pplus_PIDK-ntuple->pplus_PIDp > 0) return false ;
	
  Double_t pipInvMass;

  pipInvMass =  sqrt(
  		(ntuple->pplus_PE + ntuple->piminus_PE)*(ntuple->pplus_PE + ntuple->piminus_PE) -
  		(ntuple->pplus_PX + ntuple->piminus_PX)*(ntuple->pplus_PX + ntuple->piminus_PX) -
  		(ntuple->pplus_PY + ntuple->piminus_PY)*(ntuple->pplus_PY + ntuple->piminus_PY) -
  		(ntuple->pplus_PZ + ntuple->piminus_PZ)*(ntuple->pplus_PZ + ntuple->piminus_PZ));
		
  if (pipInvMass > 1110 && pipInvMass < 1120) return false ;	
  if (ntuple->B_SubKpi_M[0] > 5259.5 && ntuple->B_SubKpi_M[0] < 5299.5) return false ;	
  if (ntuple->B_SubpK_M[0] > 5600 && ntuple->B_SubpK_M[0] < 5640) return false ;	
  if (ntuple->piminus_PIDK > 0) return false ;	
  if (ntuple->B_FullFit_chi2_B[0]>72) return false ;
  if (ntuple->B_FullFit_M[0]<4900 || ntuple->B_FullFit_M[0]>6100)  return false ;
  return true ;
}
// selections
bool teaching(Lambdab* ntuple, bool signal ){
  // take care of teaching region
  if (signal && ntuple->B_BKGCAT!=0) return false ;
//  if ((!signal) && fabs(ntuple->B_FullFit_M[0]-5620)<100) return false ; // remove peak FIX !!!!
  return true ;
}

double printFrac(Long64_t n){ return n>0 ? 1./int(sqrt(sqrt(1.0*n))):1 ;} ;
