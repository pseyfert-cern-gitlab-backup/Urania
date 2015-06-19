#define STEFANIA
#define calibrate_1fb_paper
#include "TMath.h"
#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include "TCut.h"
#include <iostream>


static const int asize = 1e7;

int type1Clone(float tx1, float tx2, float ty1, float ty2) {
  return ((TMath::Abs(tx1 -tx2) < 0.0004) && (TMath::Abs(ty1 -ty2) < 0.0002));
}

int type2Clone(float tx1, float tx2, float ty1, float ty2, float qDivp1, float qDivp2  ){
  return ((TMath::Abs(tx1 -tx2) < 0.005) && (TMath::Abs(ty1 -ty2) < 0.005) && TMath::Abs(qDivp1 - qDivp2) < 1e-6);
}

int t1Clone(float tx1, float tx2, float tx3, float tx4, float ty1, float ty2,float ty3, float ty4 ){

  //cout << tx1 << " " << tx2 << " " << ty1 << " " << ty2 << endl;
  if (type1Clone(tx1,tx2, ty1,ty2) == 1) return 1;
  if (type1Clone(tx1,tx3, ty1,ty3) == 1) return 1;   
  if (type1Clone(tx1,tx4, ty1,ty4) == 1) return 1;   
  if (type1Clone(tx2,tx3, ty2,ty3) == 1) return 1;  
  if (type1Clone(tx2,tx4, ty2,ty4) == 1) return 1;  
  if (type1Clone(tx3,tx4, ty3,ty4) == 1) return 1;  
  return 0;
}

int t2Clone(float tx1, float tx2, float tx3, float tx4, float ty1, float ty2,float ty3, float ty4 , float 
	     qp1, float qp2, float qp3, float qp4){

  if (type2Clone(tx1,tx2, ty1,ty2, qp1, qp2) == true) return 1;
  if (type2Clone(tx1,tx3, ty1,ty3, qp1, qp3) == true) return 1;   
  if (type2Clone(tx1,tx4, ty1,ty4, qp1, qp4) == true) return 1;   
  if (type2Clone(tx2,tx3, ty2,ty3, qp2, qp3) == true) return 1;  
  if (type2Clone(tx2,tx4, ty2,ty4, qp2, qp4) == true) return 1;  
  if (type2Clone(tx3,tx4, ty3,ty4,qp3, qp4) == true) return 1;  
  return 0;
}

void sel1Candidate_Bd2JpsiKstar(int polarity = 0)  {
  char inputDecayTreeFile1[] = "/tmp/svecchi/allChannels_DTT_merged_20120612.root";
  char outputFile[] = "/tmp/svecchi/Bd2JpsiKstar_DTT.root";

  TChain* decaytree = new TChain("BdTuple/DecayTree");
  //TChain* decaytree = new TChain("BdPrescaledTuple/DecayTree");
  decaytree->Add(inputDecayTreeFile1);


  //CPPM
  TCut cutMu = "min(muplus_PIDmu,muminus_PIDmu)>0&&max(muplus_TRACK_CHI2NDOF,muminus_TRACK_CHI2NDOF)<4&&min(muplus_PT,muminus_PT)>500";
  //  TCut cutJ = "J_psi_1S_ENDVERTEX_CHI2/J_psi_1S_ENDVERTEX_NDOF<11";
  TCut cutK = "Kplus_PIDK>0&&Kplus_PIDK-Kplus_PIDp>-2&&Kplus_TRACK_CHI2NDOF<4&&piminus_TRACK_CHI2NDOF<4";
  TCut cutKstar = "Kst_892_0_PT>1000&&Kst_892_0_ENDVERTEX_CHI2/Kst_892_0_ENDVERTEX_NDOF<20";
  TCut cutB = "B0_LOKI_DTF_VCHI2NDOF>0&&B0_LOKI_DTF_VCHI2NDOF<5&&B0_IPCHI2_OWNPV<25";
 
  TCut cut0 = "B0_M>5100&&B0_M<5450";

  TFile* f_out  =new TFile(outputFile,"RECREATE");
  TTree* smalltree = decaytree->CopyTree(cutMu&&cutK&&cutKstar&&cutB&&cut0);
  TTree*  newtree = smalltree->CloneTree(-1);

  TBranch* branch_polarity =  newtree->Branch("polarity",&polarity, "polarity/I");


  int hasBestVtxChi2;
  TBranch *branch_bestVtxChi2 =  newtree->Branch("hasBestVtxChi2",&hasBestVtxChi2, "hasBestVtxChi2/I");

  int cloneType1;
  TBranch *branch_type1Clone = newtree->Branch("type1Clone",&cloneType1, "type1Clone/I");

  int cloneType2;
  TBranch *branch_type2Clone = newtree->Branch("type2Clone",&cloneType2, "type2Clone/I");

  int klClone;
  TBranch *branch_klClone = newtree->Branch("klClone",&klClone, "klClone/I");

  int triggeredByUnbiasedHlt1AndHlt2, triggeredByBiasedHlt1AndHlt2;
  TBranch *branch_unbiased = newtree->Branch("triggeredByUnbiasedHlt1AndHlt2", &triggeredByUnbiasedHlt1AndHlt2, "triggeredByUnbiasedHlt1AndHlt2/I");
  TBranch *branch_biased   = newtree->Branch("triggeredByBiasedHlt1AndHlt2",   &triggeredByBiasedHlt1AndHlt2,   "triggeredByBiasedHlt1AndHlt2/I");


  UInt_t           runNumber;
  ULong64_t         eventNumber;
  Double_t         B0_LOKI_DTF_VCHI2NDOF;

  TBranch        *b_B0_LOKI_DTF_VCHI2NDOF;   
  TBranch        *b_runNumber;   
  TBranch        *b_eventNumber; 


  TBranch   *b_muplus_TRACK_CloneDist;
  TBranch   *b_muminus_TRACK_CloneDist;
  TBranch   *b_Kplus_TRACK_CloneDist;
  TBranch   *b_piminus_TRACK_CloneDist;
  Double_t muplus_TRACK_CloneDist, muminus_TRACK_CloneDist;
  Double_t Kplus_TRACK_CloneDist, piminus_TRACK_CloneDist;
  
  newtree->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
  newtree->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
  newtree->SetBranchAddress("B0_LOKI_DTF_VCHI2NDOF", &B0_LOKI_DTF_VCHI2NDOF, &b_B0_LOKI_DTF_VCHI2NDOF);
  
  Bool_t hlt1, hlt2, biasedHLT1_1, biasedHLT1_2;
  newtree->SetBranchAddress("B0Hlt1DiMuonHighMassDecision_TOS",&hlt1);     
  newtree->SetBranchAddress("B0Hlt2DiMuonDetachedJPsiDecision_TOS",&hlt2);
  newtree->SetBranchAddress("B0Hlt1TrackMuonDecision_TOS",&biasedHLT1_1);          
  newtree->SetBranchAddress("B0Hlt1TrackAllL0Decision_TOS",&biasedHLT1_2);     

  newtree->SetBranchAddress("muplus_TRACK_CloneDist", &muplus_TRACK_CloneDist, &b_muplus_TRACK_CloneDist);
  newtree->SetBranchAddress("muminus_TRACK_CloneDist", &muminus_TRACK_CloneDist, &b_muminus_TRACK_CloneDist);
  newtree->SetBranchAddress("Kplus_TRACK_CloneDist", &Kplus_TRACK_CloneDist, &b_Kplus_TRACK_CloneDist);
  newtree->SetBranchAddress("piminus_TRACK_CloneDist", &piminus_TRACK_CloneDist, &b_piminus_TRACK_CloneDist);
  
  Double_t px1, px2, px3, px4, py1, py2, py3, py4, pz1, pz2, pz3, pz4, p1, p2, p3, p4; 

  newtree->SetBranchAddress("muplus_PX", &px1 );
  newtree->SetBranchAddress("muminus_PX", &px2 );
  newtree->SetBranchAddress("Kplus_PX", &px3 );
  newtree->SetBranchAddress("piminus_PX", &px4 );
  newtree->SetBranchAddress("muplus_PY", &py1 );
  newtree->SetBranchAddress("muminus_PY", &py2 );
  newtree->SetBranchAddress("Kplus_PY", &py3 );
  newtree->SetBranchAddress("piminus_PY", &py4 );
  newtree->SetBranchAddress("muplus_PZ", &pz1 );
  newtree->SetBranchAddress("muminus_PZ", &pz2 );
  newtree->SetBranchAddress("Kplus_PZ", &pz3 );
  newtree->SetBranchAddress("piminus_PZ", &pz4 );
  newtree->SetBranchAddress("muplus_P", &p1 );
  newtree->SetBranchAddress("muminus_P", &p2 );
  newtree->SetBranchAddress("Kplus_P", &p3 );
  newtree->SetBranchAddress("piminus_P", &p4 );

  int kid;
  newtree->SetBranchAddress("Kplus_ID", &kid);

#ifdef STEFANIA
  Int_t           B0_TAGDECISION_OS,B0_TAGDECISION_OS_new;
  Int_t           B0_TAGCAT_OS,B0_TAGCAT_OS_new;
  Double_t         B0_TAGOMEGA_OS,B0_TAGOMEGA_OS_new;
  Int_t           B0_TAGDECISION,B0_TAGDECISION_new;
  Int_t           B0_TAGCAT,B0_TAGCAT_new;
  Double_t         B0_TAGOMEGA,B0_TAGOMEGA_new;
  Int_t           B0_SS_Pion_DEC,B0_SS_Pion_DEC_new;
    
  Double_t         B0_SS_Pion_PROB,B0_SS_Pion_PROB_new;
  TBranch 
    *bB0_TAGDECISION_OS_new, *bB0_TAGCAT_OS_new, *bB0_TAGOMEGA_OS_new,
    *bB0_TAGDECISION_new, *bB0_TAGCAT_new, *bB0_TAGOMEGA_new,
    *bB0_SS_Pion_DEC_new, *bB0_SS_Pion_PROB_new;
      
      
  bB0_TAGDECISION_OS_new = newtree->Branch("B0_TAGDECISION_OS_new", &B0_TAGDECISION_OS,"B0_TAGDECISION_OS_new/I");
  bB0_TAGOMEGA_OS_new    = newtree->Branch("B0_TAGOMEGA_OS_new",    &B0_TAGOMEGA_OS,   "B0_TAGOMEGA_OS_new/D");
  bB0_TAGCAT_OS_new      = newtree->Branch("B0_TAGCAT_OS_new",      &B0_TAGCAT_OS,     "B0_TAGCAT_OS_new/I");
  bB0_TAGDECISION_new    = newtree->Branch("B0_TAGDECISION_new",    &B0_TAGDECISION,   "B0_TAGDECISION_new/I");
  bB0_TAGOMEGA_new       = newtree->Branch("B0_TAGOMEGA_new",       &B0_TAGOMEGA,      "B0_TAGOMEGA_new/D");
  bB0_TAGCAT_new         = newtree->Branch("B0_TAGCAT_new",         &B0_TAGCAT,        "B0_TAGCAT_new/I");
  bB0_SS_Pion_PROB_new   = newtree->Branch("B0_SS_Pion_PROB_new",   &B0_SS_Pion_PROB,  "B0_SS_Pion_PROB_new/D");
  bB0_SS_Pion_DEC_new    = newtree->Branch("B0_SS_Pion_DEC_new",    &B0_SS_Pion_DEC,   "B0_SS_Pion_DEC_new/I");
    
  newtree->SetBranchAddress("B0_TAGDECISION_OS", &B0_TAGDECISION_OS);
  newtree->SetBranchAddress("B0_TAGOMEGA_OS",    &B0_TAGOMEGA_OS);
  newtree->SetBranchAddress("B0_TAGCAT_OS",      &B0_TAGCAT_OS);
  newtree->SetBranchAddress("B0_TAGDECISION",    &B0_TAGDECISION);
  newtree->SetBranchAddress("B0_TAGOMEGA",       &B0_TAGOMEGA);
  newtree->SetBranchAddress("B0_TAGCAT",         &B0_TAGCAT);
  newtree->SetBranchAddress("B0_SS_Pion_PROB",   &B0_SS_Pion_PROB);
  newtree->SetBranchAddress("B0_SS_Pion_DEC",    &B0_SS_Pion_DEC);
 #endif

  int num_entries  = newtree->GetEntries();
  int flag_VtxChi2[asize];

  if (num_entries > asize) {
    std::cout << "Array too small:: abort" << std::endl;
    return;
  } 
  
  int i =0;
  for(i=0;i<num_entries;i++) flag_VtxChi2[i]=0; 

  int i  =0;
  while (i <num_entries) {
    //cout <<"event " <<i <<endl;

    newtree->GetEntry(i);
    int run_i = runNumber;
    float event_i = eventNumber;
    double B0_LOKI_DTF_VCHI2NDOF_i = B0_LOKI_DTF_VCHI2NDOF;

    int best_by_VtxChi2 = i; 
    double minVtxChi2 = B0_LOKI_DTF_VCHI2NDOF_i;


    int next = i+1;
    for (int j=i+1;j<num_entries; j++) {
      newtree->GetEntry(j);
      int run_j = runNumber;
      float event_j = eventNumber;
      double B0_LOKI_DTF_VCHI2NDOF_j = B0_LOKI_DTF_VCHI2NDOF;

      if(run_j!=run_i||event_j!=event_i) {next =j;  break;}
      if(B0_LOKI_DTF_VCHI2NDOF_j<minVtxChi2) {
        best_by_VtxChi2 = j;
        minVtxChi2 = B0_LOKI_DTF_VCHI2NDOF_j;
      }
    }  
    flag_VtxChi2[best_by_VtxChi2] = 1;
    i= next;
  }


  for ( i=0;i<num_entries; i++) {
    hasBestVtxChi2 = flag_VtxChi2[i];
    branch_bestVtxChi2->Fill();
    newtree->GetEntry(i);
    klClone = 1;
    if (muminus_TRACK_CloneDist < 0 && muplus_TRACK_CloneDist < 0 && Kplus_TRACK_CloneDist < 0 &&  piminus_TRACK_CloneDist < 0 ) klClone = 0;
    cloneType1 = t1Clone(px1/pz1,px2/pz2,px3/pz3,px4/pz4, py1/pz1,py2/pz3,py3/pz3,py4/pz4);
    float signedP3 = 1/p3;  
    float signedP4 = 1/p4; 
    if (kid > 0) {
      signedP3 = 1/p3;
      signedP4 = -1/p4;
    }
    else {
      signedP3 = -1/p3;
      signedP4 = 1/p4;
    }
    cloneType2 = t2Clone(px1/pz1,px2/pz2,px3/pz3,px4/pz4, py1/pz1,py2/pz2,py3/pz3,py4/pz4, 1/p1,-1/p2,signedP3, signedP4);
    branch_type1Clone->Fill();
    branch_type2Clone->Fill();
    branch_klClone->Fill();
    triggeredByUnbiasedHlt1AndHlt2 = hlt1 && hlt2;
    triggeredByBiasedHlt1AndHlt2 = hlt2 && (biasedHLT1_1 || biasedHLT1_2);
    if ( triggeredByUnbiasedHlt1AndHlt2 == 1)  triggeredByBiasedHlt1AndHlt2 = 0;

#ifdef STEFANIA

    if(B0_SS_Pion_DEC == -1000) { // untagged
      B0_SS_Pion_DEC = 0;
      B0_SS_Pion_PROB = 0.5;
    }
    else if(B0_SS_Pion_PROB <0.001  || B0_SS_Pion_PROB >= 0.5 ) {
      B0_SS_Pion_DEC = 0;
      B0_SS_Pion_PROB = 0.5;
    }

    if(B0_TAGDECISION_OS == 0) B0_TAGOMEGA_OS = 0.5; // untagged
    else if(B0_TAGOMEGA_OS <0.001  || B0_TAGOMEGA_OS >= 0.5 ) {
      B0_TAGDECISION_OS = 0;
      B0_TAGOMEGA_OS = 0.5;
      B0_TAGCAT_OS=0;
    }
#ifdef calibrate_1fb_paper
    if(B0_TAGDECISION_OS != 0 ){
      const double p_0 = 0.392;
      const double p_1 = 1.035;
      const double eta_mean =0.391;
      
      B0_TAGOMEGA_OS =p_0 + p_1 *( B0_TAGOMEGA_OS - eta_mean ) ;      
      
      if(B0_TAGOMEGA_OS <0.001  || B0_TAGOMEGA_OS >= 0.5 ) { 
        B0_TAGDECISION_OS = 0;
        B0_TAGOMEGA_OS = 0.5;
      }    
    }    
    if(B0_SS_Pion_DEC != 0 ){
      const double p_0 = 0.407;
      const double p_1 = 0.76;
      const double p_2 = -2.2;
      const double eta_mean =0.374;
      
      B0_SS_Pion_PROB = 
        p_0 + p_1 *( B0_SS_Pion_PROB - eta_mean ) + p_2 *( B0_SS_Pion_PROB - eta_mean )*( B0_SS_Pion_PROB - eta_mean );

      if(B0_SS_Pion_PROB <0.001  || B0_SS_Pion_PROB >= 0.5 ) { 
        B0_SS_Pion_DEC = 0;
        B0_SS_Pion_PROB = 0.5;
      }    
    }
    // recompute the combined probability and tag decision for SSK+OS
    double SSeOS_omega    = 0; 
    if(B0_TAGDECISION_OS*B0_SS_Pion_DEC != 0 ) {

      double tagdecision = B0_TAGDECISION_OS;
      double pnsum       = 1-B0_TAGOMEGA_OS;
      
      double SSeOS_pnsum_a= ((1-tagdecision)/2 + tagdecision*pnsum );   //hypothesis of truetag=+1
      double SSeOS_pnsum_b= ((1+tagdecision)/2 - tagdecision*pnsum );   //hypothesis of truetag=-1

      double mtagss = B0_SS_Pion_DEC;      
      double pnss   = 1-B0_SS_Pion_PROB; //probability of 'right'
      SSeOS_pnsum_a *= ((1-mtagss)/2 + mtagss*pnss ); // p
      SSeOS_pnsum_b *= ((1+mtagss)/2 - mtagss*pnss ); //(1-p)

      double SSeOS_tagdecision=0;      
      if(SSeOS_pnsum_a > SSeOS_pnsum_b) SSeOS_tagdecision = +1;
      if(SSeOS_pnsum_a < SSeOS_pnsum_b) SSeOS_tagdecision = -1;
      //normalise probability to the only two possible flavours:
      double max=SSeOS_pnsum_a;
      if(SSeOS_pnsum_b>max) max=SSeOS_pnsum_b;      
      double SSeOS_pnsum = max /(SSeOS_pnsum_a + SSeOS_pnsum_b);

      SSeOS_omega       = fabs(1-SSeOS_pnsum); 
      
      B0_TAGOMEGA     = SSeOS_omega;
      B0_TAGDECISION  = SSeOS_tagdecision;

    } else if(B0_TAGDECISION_OS !=0) {

      SSeOS_omega       = B0_TAGOMEGA_OS; 
      B0_TAGOMEGA     = B0_TAGOMEGA_OS;      
      B0_TAGDECISION  = B0_TAGDECISION_OS;
      
    } else if(B0_SS_Pion_DEC !=0) {

      SSeOS_omega       = B0_SS_Pion_PROB;
      B0_TAGOMEGA     = B0_SS_Pion_PROB;
      B0_TAGDECISION  = B0_SS_Pion_DEC;
      
    } else if(B0_TAGDECISION_OS ==0 && B0_SS_Pion_DEC ==0) {

      SSeOS_omega       = 0.5;
      B0_TAGOMEGA     = 0.5;
      B0_TAGDECISION  = 0;
      
    }
    
    
    //sort decision into categories ------------------
    //cat=1 will be least reliable, cat=5 most reliable
    //ProbMin is a small offset to adjust for range of pnsum
    int    SSeOS_category = 0;
    if( B0_TAGDECISION !=0 ) {
    
      double m_omegamaxbin  = 0.38;
      double m_omegascale   = 0.07;
      
      if(      SSeOS_omega > m_omegamaxbin                ) SSeOS_category=1;
      else if( SSeOS_omega > m_omegamaxbin-m_omegascale   ) SSeOS_category=2;
      else if( SSeOS_omega > m_omegamaxbin-m_omegascale*2 ) SSeOS_category=3;
      else if( SSeOS_omega > m_omegamaxbin-m_omegascale*3 ) SSeOS_category=4;
      else                                                  SSeOS_category=5;
    }
    
    B0_TAGCAT  = SSeOS_category;
      
    
#endif

      
    if(B0_TAGDECISION == 0) B0_TAGOMEGA = 0.5; // untagged
    else if(B0_TAGOMEGA <0.001  || B0_TAGOMEGA >= 0.5 ) {
      B0_TAGDECISION = 0;
      B0_TAGOMEGA = 0.5;
      B0_TAGCAT=0;      
    } 
        
        
      
    bB0_TAGDECISION_OS_new->Fill();
    bB0_TAGCAT_OS_new->Fill();
    bB0_TAGOMEGA_OS_new->Fill();
    bB0_TAGDECISION_new->Fill();
    bB0_TAGCAT_new->Fill();
    bB0_TAGOMEGA_new->Fill();
    bB0_SS_Pion_DEC_new->Fill();
    bB0_SS_Pion_PROB_new->Fill();
    
#endif

    branch_unbiased->Fill();  
    branch_biased->Fill();   
    branch_polarity->Fill();  
 
  } 

  newtree->Write();
  f_out->Close();
  }
