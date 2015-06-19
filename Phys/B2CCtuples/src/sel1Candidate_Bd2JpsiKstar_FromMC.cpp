#include <iostream>

#include <TChain.h>
#include <TCut.h>
#include <TBranch.h>
#include <TFile.h>
#include <TTree.h>

using namespace std;

int doIt()
{
  char inputDecayTreeFile1[] = "/tmp/jluisier/Overall-Bd-recoFromStrip.root";
  char outputFile[] = "/tmp/jluisier/Bd2JpsiKstar_stripping10_1cand.root";
  
  TChain* decaytree = new TChain("DecayTree");
  decaytree->Add(inputDecayTreeFile1);
  TCut cutMu, cutJ, cutK, cutKstar, cutB;

  //CPPM
  cutMu = "min(muplus_PIDmu,muminus_PIDmu)>0&&max(muplus_TRACK_CHI2NDOF,muminus_TRACK_CHI2NDOF)<4"\
    "&&min(muplus_PT,muminus_PT)>500";
  cutJ = "J_psi_1S_ENDVERTEX_CHI2/J_psi_1S_ENDVERTEX_NDOF<11 && "\
    "TMath::Abs( J_psi_1S_MM - 3096.9) / J_psi_1S_MMERR < 4.2";
  cutK = "Kplus_PIDK>0&&Kplus_PIDK-Kplus_PIDp>-2&&Kplus_TRACK_CHI2NDOF<4&&piminus_TRACK_CHI2NDOF<4";
  cutKstar = "Kst_892_0_PT>1000&&Kst_892_0_ENDVERTEX_CHI2/Kst_892_0_ENDVERTEX_NDOF<20&&"\
    "abs(Kst_892_0_MM-892)<70";
  cutB = "B0_LOKI_DTF_VCHI2NDOF<5&&B0_IPCHI2_OWNPV<25 &&"\
    " ( B0_MINIPCHI2NEXTBEST > 50 || B0_MINIPCHI2NEXTBEST < 0 )";
 
  TCut cut0 = "B0_LOKI_MASS_JpsiConstr>5100&&B0_LOKI_MASS_JpsiConstr<5450";

  TFile* f_out  =new TFile(outputFile,"RECREATE");
  TTree* smalltree = decaytree->CopyTree( cutMu && cutJ && cutK && cutKstar && cutB && cut0 );
  TTree*  newtree = smalltree->CloneTree(-1);

  int hasBestVtxChi2, take;
  TBranch *branch_bestVtxChi2  = newtree->Branch("hasBestVtxChi2",&hasBestVtxChi2, "hasBestVtxChi2/I");
  TBranch *branch_take         = newtree->Branch("take", &take, "take/I" );

  Int_t   runNumber;
  Int_t   eventNumber;
  Int_t   nCandidate;
  Float_t B0_LOKI_DTF_VCHI2NDOF;

  Int_t unbiasedTrTOS;

  TBranch *b_B0_LOKI_DTF_VCHI2NDOF;   
  TBranch *b_runNumber;   
  TBranch *b_eventNumber; 
  TBranch *b_unbiasedTrTOS;//, *b_biasedTrTOS;

  newtree->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
  newtree->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
  newtree->SetBranchAddress("B0_LOKI_DTF_VCHI2NDOF", &B0_LOKI_DTF_VCHI2NDOF, &b_B0_LOKI_DTF_VCHI2NDOF);

  newtree->SetBranchAddress("unbiasedTrTOS"           , &unbiasedTrTOS           , &b_unbiasedTrTOS );
  newtree->SetBranchAddress( "nCandidate"             , &nCandidate );

  int num_entries  = newtree->GetEntries();
  int flag_VtxChi2[num_entries],
    flag_take[num_entries];
  for(int i=0;i<num_entries;i++)
  {
    flag_VtxChi2[i]=0;
    flag_take[i] = 0;
  }

  int i  =0;
  int candNbr0;
  while (i <num_entries) {
    cout <<"event " <<i <<endl;

    newtree->GetEntry(i);

    if ( nCandidate == 0 )
      candNbr0 = i;

    if ( unbiasedTrTOS == 0 )
    {
      i++;
      continue;
    }

    int run_i = runNumber;
    int event_i = eventNumber;
    double B0_LOKI_DTF_VCHI2NDOF_i = B0_LOKI_DTF_VCHI2NDOF;

    int best_by_VtxChi2 = i; 
    double minVtxChi2 = B0_LOKI_DTF_VCHI2NDOF_i;

    int next = i+1;
    for (int j=i+1;j<num_entries; j++) {
      newtree->GetEntry(j);

      if ( unbiasedTrTOS == 0 )
      {
        continue;
      }

      int run_j = runNumber;
      int event_j = eventNumber;
      double B0_LOKI_DTF_VCHI2NDOF_j = B0_LOKI_DTF_VCHI2NDOF;

      if(run_j!=run_i||event_j!=event_i) {next =j;  break;}
      if(B0_LOKI_DTF_VCHI2NDOF_j<minVtxChi2)
      {
        minVtxChi2 = B0_LOKI_DTF_VCHI2NDOF_j;
        best_by_VtxChi2 = j;
      }
      
    }  
    flag_VtxChi2[best_by_VtxChi2] = 1;
    flag_take[ candNbr0 ] = 1;
    
    i= next;
  }
  
  for (int i=0;i<num_entries; i++)
  {
    hasBestVtxChi2 = flag_VtxChi2[i];
    take = flag_take[i];
    branch_bestVtxChi2->Fill();
    branch_take->Fill();
  }  

  newtree->Write();
  f_out->Close();

  return 0;
}
