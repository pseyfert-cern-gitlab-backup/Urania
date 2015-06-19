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

int t1Clone(float tx1, float tx2, float tx3, float ty1, float ty2,float ty3 ){

  if (type1Clone(tx1,tx2, ty1,ty2) == 1) return 1;
  if (type1Clone(tx1,tx3, ty1,ty3) == 1) return 1;   
  if (type1Clone(tx2,tx3, ty2,ty3) == 1) return 1;   

  return 0;
}

int t2Clone(float tx1, float tx2, float tx3,  float ty1, float ty2,float ty3, float 
	    qp1, float qp2, float qp3){

  if (type2Clone(tx1,tx2, ty1,ty2, qp1, qp2) == true) return 1;
  if (type2Clone(tx1,tx3, ty1,ty3, qp1, qp3) == true) return 1;   
  if (type2Clone(tx1,tx3, ty1,ty3, qp2, qp3) == true) return 1;   

  return 0;
}


void sel1Candidate_Bu2JpsiK(int polarity = 0){

  char inputDecayTreeFile1[] = "/tmp/svecchi/allChannels_DTT_merged_20120612.root";
  char outputFile[] = "/tmp/svecchi/Bu2JpsiK_DTT.root";
  //TChain* decaytree = new TChain("BuPrescaledTuple/DecayTree");
  TChain* decaytree = new TChain("BuTuple/DecayTree");
  decaytree->Add(inputDecayTreeFile1);
  

  //CPPM
  TCut cutMu = "min(muplus_PIDmu,muminus_PIDmu)>0 && max(muplus_TRACK_CHI2NDOF,muminus_TRACK_CHI2NDOF)<4 && min(muplus_PT,muminus_PT)>500";
  // TCut cutJ = "J_psi_1S_ENDVERTEX_CHI2/J_psi_1S_ENDVERTEX_NDOF<11";
  TCut cutK = "Kplus_PIDK>0 && Kplus_PIDK-Kplus_PIDp>-2 && Kplus_TRACK_CHI2NDOF<4 && Kplus_PT>1000 && Kplus_P>10000";
  TCut cutB = "Bplus_LOKI_DTF_VCHI2NDOF>0&&Bplus_LOKI_DTF_VCHI2NDOF<5 && Bplus_IPCHI2_OWNPV<25";
 
  TCut cut0 = "Bplus_M>5100 && Bplus_M<5450";
  TCut trig = "(BplusHlt1SingleMuonNoIPL0Decision_TOS   == 1 || BplusHlt1DiMuonNoIPL0DiDecision_TOS     == 1) && BplusHlt2DiMuonUnbiasedJPsiDecision_TOS == 1";

  TFile* f_out  =new TFile(outputFile,"RECREATE");
  TTree* smalltree = decaytree->CopyTree(cutMu && cutK && cutB && cut0);
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

  TBranch   *b_muplus_TRACK_CloneDist;
  TBranch   *b_muminus_TRACK_CloneDist;
  TBranch   *b_Kplus_TRACK_CloneDist;
  Double_t muplus_TRACK_CloneDist, muminus_TRACK_CloneDist, Kplus_TRACK_CloneDist; 
  

  int triggeredByUnbiasedHlt1AndHlt2, triggeredByBiasedHlt1AndHlt2;
  TBranch *branch_unbiased = newtree->Branch("triggeredByUnbiasedHlt1AndHlt2", &triggeredByUnbiasedHlt1AndHlt2, "triggeredByUnbiasedHlt1AndHlt2/I");
  TBranch *branch_biased   = newtree->Branch("triggeredByBiasedHlt1AndHlt2",   &triggeredByBiasedHlt1AndHlt2,   "triggeredByBiasedHlt1AndHlt2/I");

  UInt_t           runNumber;
  ULong64_t           eventNumber;
  Double_t         Bplus_LOKI_DTF_VCHI2NDOF;
 
  TBranch        *b_Bplus_LOKI_DTF_VCHI2NDOF;   
  TBranch        *b_runNumber;   
  TBranch        *b_eventNumber; 
  
  Double_t px1, px2, px3, py1, py2, py3, pz1, pz2, pz3, p1, p2, p3; 

  Bool_t hlt1, hlt2, biasedHLT1_1, biasedHLT1_2;
  newtree->SetBranchAddress("BplusHlt1DiMuonHighMassDecision_TOS",&hlt1);     
  newtree->SetBranchAddress("BplusHlt2DiMuonDetachedJPsiDecision_TOS",&hlt2);
  newtree->SetBranchAddress("BplusHlt1TrackMuonDecision_TOS",&biasedHLT1_1);          
  newtree->SetBranchAddress("BplusHlt1TrackAllL0Decision_TOS",&biasedHLT1_2);     

  newtree->SetBranchAddress("muplus_TRACK_CloneDist", &muplus_TRACK_CloneDist, &b_muplus_TRACK_CloneDist);
  newtree->SetBranchAddress("muminus_TRACK_CloneDist", &muminus_TRACK_CloneDist, &b_muminus_TRACK_CloneDist);
  newtree->SetBranchAddress("Kplus_TRACK_CloneDist", &Kplus_TRACK_CloneDist, &b_Kplus_TRACK_CloneDist);
  
  newtree->SetBranchAddress("muplus_PX", &px1 );
  newtree->SetBranchAddress("muminus_PX", &px2 );
  newtree->SetBranchAddress("Kplus_PX", &px3 );
 
  newtree->SetBranchAddress("muplus_PY", &py1 );
  newtree->SetBranchAddress("muminus_PY", &py2 );
  newtree->SetBranchAddress("Kplus_PY", &py3 );

  newtree->SetBranchAddress("muplus_PZ", &pz1 );
  newtree->SetBranchAddress("muminus_PZ", &pz2 );
  newtree->SetBranchAddress("Kplus_PZ", &pz3 );
 
  newtree->SetBranchAddress("muplus_P", &p1 );
  newtree->SetBranchAddress("muminus_P", &p2 );
  newtree->SetBranchAddress("Kplus_P", &p3 );
 
  int kid;
  newtree->SetBranchAddress("Kplus_ID", &kid);

  newtree->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
  newtree->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
  newtree->SetBranchAddress("Bplus_LOKI_DTF_VCHI2NDOF", &Bplus_LOKI_DTF_VCHI2NDOF, &b_Bplus_LOKI_DTF_VCHI2NDOF);

#ifdef STEFANIA
  Int_t           Bplus_TAGDECISION_OS,Bplus_TAGDECISION_OS_new;
  Int_t           Bplus_TAGCAT_OS,Bplus_TAGCAT_OS_new;
  Double_t         Bplus_TAGOMEGA_OS,Bplus_TAGOMEGA_OS_new;
  Int_t           Bplus_TAGDECISION,Bplus_TAGDECISION_new;
  Int_t           Bplus_TAGCAT,Bplus_TAGCAT_new;
  Double_t         Bplus_TAGOMEGA,Bplus_TAGOMEGA_new;
  Int_t           Bplus_SS_Pion_DEC,Bplus_SS_Pion_DEC_new;

  Double_t         Bplus_SS_Pion_PROB,Bplus_SS_Pion_PROB_new;
  TBranch
    *bBplus_TAGDECISION_OS_new, *bBplus_TAGCAT_OS_new, *bBplus_TAGOMEGA_OS_new,
    *bBplus_TAGDECISION_new, *bBplus_TAGCAT_new, *bBplus_TAGOMEGA_new,
    *bBplus_SS_Pion_DEC_new, *bBplus_SS_Pion_PROB_new;


  bBplus_TAGDECISION_OS_new = newtree->Branch("Bplus_TAGDECISION_OS_new", &Bplus_TAGDECISION_OS,"Bplus_TAGDECISION_OS_new/I");
  bBplus_TAGOMEGA_OS_new    = newtree->Branch("Bplus_TAGOMEGA_OS_new",    &Bplus_TAGOMEGA_OS,   "Bplus_TAGOMEGA_OS_new/D");
  bBplus_TAGCAT_OS_new      = newtree->Branch("Bplus_TAGCAT_OS_new",      &Bplus_TAGCAT_OS,     "Bplus_TAGCAT_OS_new/I");  
  bBplus_TAGDECISION_new    = newtree->Branch("Bplus_TAGDECISION_new",    &Bplus_TAGDECISION,   "Bplus_TAGDECISION_new/I");
  bBplus_TAGOMEGA_new       = newtree->Branch("Bplus_TAGOMEGA_new",       &Bplus_TAGOMEGA,      "Bplus_TAGOMEGA_new/D");
  bBplus_TAGCAT_new         = newtree->Branch("Bplus_TAGCAT_new",         &Bplus_TAGCAT,       "Bplus_TAGCAT_new/I");  
  bBplus_SS_Pion_PROB_new   = newtree->Branch("Bplus_SS_Pion_PROB_new",   &Bplus_SS_Pion_PROB,  "Bplus_SS_Pion_PROB_new/D");
  bBplus_SS_Pion_DEC_new    = newtree->Branch("Bplus_SS_Pion_DEC_new",    &Bplus_SS_Pion_DEC,   "Bplus_SS_Pion_DEC_new/I");
  
  newtree->SetBranchAddress("Bplus_TAGDECISION_OS", &Bplus_TAGDECISION_OS);
  newtree->SetBranchAddress("Bplus_TAGOMEGA_OS",    &Bplus_TAGOMEGA_OS);
  newtree->SetBranchAddress("Bplus_TAGCAT_OS",      &Bplus_TAGCAT_OS);
  newtree->SetBranchAddress("Bplus_TAGDECISION",    &Bplus_TAGDECISION);
  newtree->SetBranchAddress("Bplus_TAGOMEGA",       &Bplus_TAGOMEGA);
  newtree->SetBranchAddress("Bplus_TAGCAT",         &Bplus_TAGCAT);
  newtree->SetBranchAddress("Bplus_SS_Pion_PROB",   &Bplus_SS_Pion_PROB);
  newtree->SetBranchAddress("Bplus_SS_Pion_DEC",    &Bplus_SS_Pion_DEC);
 #endif

  //int num_entries  = newtree->GetEntries();
  // int flag_VtxChi2[asize];
  int num_entries  = newtree->GetEntries();
  //  num_entries = 50000;
  int flag_VtxChi2[asize];

  if (num_entries > asize) {
    std::cout << "Array too small:: abort" << std::endl;
    return;
  } 
  
  int i = 0;
  for(i=0;i<num_entries;i++) flag_VtxChi2[i]=0; 

  //  int i  =0;
  i = 0;
  while (i <num_entries) {
   //cout <<"event " <<i <<endl;

    newtree->GetEntry(i);
    int run_i = runNumber;
    float event_i = eventNumber;
    double Bplus_LOKI_DTF_VCHI2NDOF_i = Bplus_LOKI_DTF_VCHI2NDOF;

    int best_by_VtxChi2 = i; 
    double minVtxChi2 = Bplus_LOKI_DTF_VCHI2NDOF_i;


    int next = i+1;
    for (int j=i+1;j<num_entries; j++) {
      newtree->GetEntry(j);
      int run_j = runNumber;
      float event_j = eventNumber;
      double Bplus_LOKI_DTF_VCHI2NDOF_j = Bplus_LOKI_DTF_VCHI2NDOF;

      if(run_j!=run_i||event_j!=event_i) {next =j;  break;}
      if(Bplus_LOKI_DTF_VCHI2NDOF_j<minVtxChi2) {
        best_by_VtxChi2 = j;
        minVtxChi2 = Bplus_LOKI_DTF_VCHI2NDOF_j;
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
    if (muminus_TRACK_CloneDist < 0 && muplus_TRACK_CloneDist < 0 && Kplus_TRACK_CloneDist < 0 ) klClone = 0;
    cloneType1 = t1Clone(px1/pz1,px2/pz2,px3/pz3, py1/pz1,py2/pz3,py3/pz3);
    float signedP = 1/p3; if (kid < 0) signedP *= -1; 
    cloneType2 = t2Clone(px1/pz1,px2/pz2,px3/pz3, py1/pz1,py2/pz2,py3/pz3, 1/p1,-1/p2, signedP);
    branch_type1Clone->Fill();
    branch_type2Clone->Fill();
    branch_klClone->Fill();
    triggeredByUnbiasedHlt1AndHlt2 = hlt1 && hlt2;
    triggeredByBiasedHlt1AndHlt2 = hlt2 && (biasedHLT1_1 || biasedHLT1_2);
    if ( triggeredByUnbiasedHlt1AndHlt2 == 1)  triggeredByBiasedHlt1AndHlt2 = 0;

#ifdef STEFANIA

    if(Bplus_SS_Pion_DEC == -1000) { // untagged
      Bplus_SS_Pion_DEC = 0;
      Bplus_SS_Pion_PROB = 0.5;
    }
    else if(Bplus_SS_Pion_PROB <0.001  || Bplus_SS_Pion_PROB >= 0.5 ) {
      Bplus_SS_Pion_DEC = 0;
      Bplus_SS_Pion_PROB = 0.5;
    }

    if(Bplus_TAGDECISION_OS == 0) Bplus_TAGOMEGA_OS = 0.5; // untagged
    else if(Bplus_TAGOMEGA_OS <0.001  || Bplus_TAGOMEGA_OS >= 0.5 ) {
      Bplus_TAGDECISION_OS = 0;
      Bplus_TAGOMEGA_OS = 0.5;
      Bplus_TAGCAT_OS=0;
    }

#ifdef calibrate_1fb_paper

    if(Bplus_TAGDECISION_OS != 0 ){
      const double p_0 = 0.392;
      const double p_1 = 1.035;
      const double eta_mean = 0.391;
      
      Bplus_TAGOMEGA_OS =p_0 + p_1 *( Bplus_TAGOMEGA_OS - eta_mean ) ;      
      
      if(Bplus_TAGOMEGA_OS <0.001  || Bplus_TAGOMEGA_OS >= 0.5 ) { 
        Bplus_TAGDECISION_OS = 0;
        Bplus_TAGOMEGA_OS = 0.5;
      }    
    }    
    if(Bplus_SS_Pion_DEC != 0 ){
      const double p_0 = 0.407;
      const double p_1 = 0.76;
      const double p_2 = -2.2;
      const double eta_mean =0.374;
      
      Bplus_SS_Pion_PROB = 
        p_0 + p_1 *( Bplus_SS_Pion_PROB - eta_mean ) + p_2 *( Bplus_SS_Pion_PROB - eta_mean )*( Bplus_SS_Pion_PROB - eta_mean );

      if(Bplus_SS_Pion_PROB <0.001  || Bplus_SS_Pion_PROB >= 0.5 ) { 
        Bplus_SS_Pion_DEC = 0;
        Bplus_SS_Pion_PROB = 0.5;
      }    
    }    
    // recompute the combined probability and tag decision for SSK+OS
    double SSeOS_omega    = 0; 
    if(Bplus_TAGDECISION_OS*Bplus_SS_Pion_DEC != 0 ) {

      double tagdecision = Bplus_TAGDECISION_OS;
      double pnsum       = 1-Bplus_TAGOMEGA_OS;
      
      double SSeOS_pnsum_a= ((1-tagdecision)/2 + tagdecision*pnsum );   //hypothesis of truetag=+1
      double SSeOS_pnsum_b= ((1+tagdecision)/2 - tagdecision*pnsum );   //hypothesis of truetag=-1

      double mtagss = Bplus_SS_Pion_DEC;
      double pnss   = 1-Bplus_SS_Pion_PROB; //probability of 'right'
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
      
      Bplus_TAGOMEGA     = SSeOS_omega;
      Bplus_TAGDECISION  = SSeOS_tagdecision;
      //cout<<" OS=("<<Bplus_TAGOMEGA_OS<<","<< Bplus_TAGDECISION_OS<<")  SSpi=("<<Bplus_SS_Pion_PROB<<","<<Bplus_SS_Pion_DEC<<") OS&SSpi=("<<Bplus_TAGOMEGA<<","<<Bplus_TAGDECISION<<")"<<endl;
      
    } else if(Bplus_TAGDECISION_OS !=0) {

      SSeOS_omega       = Bplus_TAGOMEGA_OS; 
      Bplus_TAGOMEGA     = Bplus_TAGOMEGA_OS;      
      Bplus_TAGDECISION  = Bplus_TAGDECISION_OS;
      
    } else if(Bplus_SS_Pion_DEC !=0) {

      SSeOS_omega       = Bplus_SS_Pion_PROB;
      Bplus_TAGOMEGA     = Bplus_SS_Pion_PROB;
      Bplus_TAGDECISION  = Bplus_SS_Pion_DEC;
      
    } else if(Bplus_TAGDECISION_OS ==0 && Bplus_SS_Pion_DEC ==0) {

      SSeOS_omega       = 0.5;
      Bplus_TAGOMEGA     = 0.5;
      Bplus_TAGDECISION  = 0;
      
    }
    
    
    //sort decision into categories ------------------
    //cat=1 will be least reliable, cat=5 most reliable
    //ProbMin is a small offset to adjust for range of pnsum
    int    SSeOS_category = 0;
    if( Bplus_TAGDECISION !=0 ) {
    
      double m_omegamaxbin  = 0.38;
      double m_omegascale   = 0.07;
      
      if(      SSeOS_omega > m_omegamaxbin                ) SSeOS_category=1;
      else if( SSeOS_omega > m_omegamaxbin-m_omegascale   ) SSeOS_category=2;
      else if( SSeOS_omega > m_omegamaxbin-m_omegascale*2 ) SSeOS_category=3;
      else if( SSeOS_omega > m_omegamaxbin-m_omegascale*3 ) SSeOS_category=4;
      else                                                  SSeOS_category=5;
    }
    
    Bplus_TAGCAT  = SSeOS_category;
      
    
#endif
      
    if(Bplus_TAGDECISION == 0) Bplus_TAGOMEGA = 0.5; // untagged
    else if(Bplus_TAGOMEGA <0.001  || Bplus_TAGOMEGA >= 0.5 ) {
      Bplus_TAGDECISION = 0;
      Bplus_TAGOMEGA = 0.5;
      Bplus_TAGCAT=0;      
    } 
        
        
      
    bBplus_TAGDECISION_OS_new->Fill();
    bBplus_TAGCAT_OS_new->Fill();
    bBplus_TAGOMEGA_OS_new->Fill();
    bBplus_TAGDECISION_new->Fill();
    bBplus_TAGCAT_new->Fill();
    bBplus_TAGOMEGA_new->Fill();
    bBplus_SS_Pion_DEC_new->Fill();
    bBplus_SS_Pion_PROB_new->Fill();
    
#endif


    branch_unbiased->Fill();  
    branch_biased->Fill();   
    branch_polarity->Fill(); 

  } 

  newtree->Write();
  f_out->Close();
  }
