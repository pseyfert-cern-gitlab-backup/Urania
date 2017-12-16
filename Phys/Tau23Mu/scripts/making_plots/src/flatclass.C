#define flatclass_cxx
#include "flatclass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <iostream>

TString bckconvert(int i) {
  int muons = i&0xF;
  int pion = (i&0xF0)>>4;
  int kaons = (i&0xF00)>>8;
  int ghosts = (i&0xF000)>>12;
  int rest = (i&0xF0000)>>16;
  int protons = (i&0xF00000)>>20;
  TString buffer="";
  for (int j = 0 ; j < muons ; ++j) buffer+="#mu";
  for (int j = 0 ; j < pion ; ++j) buffer+="#pi";
  for (int j = 0 ; j < kaons ; ++j) buffer+="K";
  for (int j = 0 ; j < rest ; ++j) buffer+="X";
  for (int j = 0 ; j < protons ; ++j) buffer+="p";
  //for (int j = 0 ; j < ghosts ; ++j) buffer+="(ghost)";
  if (ghosts>0&&ghosts<3) buffer+="+";
  if (ghosts==1) buffer+=Form("%dghost",ghosts);
  if (ghosts>1) buffer+=Form("%dghosts",ghosts);
  return buffer;

}

TH1* flatclass::Loop(const char* eventselection,TH1* bcks=NULL)
{
   const TString mysel(eventselection);
   ++loopcount;
//   In a ROOT session, you can do:
//      Root > .L flatclass.C
//      Root > flatclass t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (NULL==bcks)
     bcks = new TH1F(Form("BCK_%d",loopcount),"BCK",100,0,100);
   else {
     bcks = (TH1*)bcks->Clone(Form("BCK_%d",loopcount));
     for (int i = 1 ; i <= bcks->GetNbinsX() ; ++i)
       bcks->SetBinContent(i,0);
   }
   if (fChain == 0) return NULL;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   std::cout << mysel.Data() << std::endl;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      //std::cout << "fChain->Draw((const char*)\"BCK\",\""<<mysel.Data()<<"\",(Option_t*)\"\",1,"<<jentry<<"))"<<std::endl;
      if (0<fChain->Draw((const char*)"BCK",(const char*)mysel.Data(),(Option_t*)"",1,jentry))
        bcks->Fill(bckconvert(BCK).Data(),1);
   }
   return bcks;
}

void flatclass::Loop() {
  Loop("",NULL);
}
