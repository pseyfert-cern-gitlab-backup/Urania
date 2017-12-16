#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <utility>
#include <string>

/**
* @file minmax.C
* @brief add a branch with the minimum PID and the maximum ghost probability to a tree using the friend interface
* @author Paul Seyfert
* @date 2012-09-28
*/


std::string org_file("~/tmpbuffer/v8/stp17unblinded_mu_BDTv4_405pb_flatV8.root");

int maxghost() {
  TChain* kette = new TChain("Ds2PhiPi");
  kette->Add(org_file.c_str());
  Float_t inghost1;
  Float_t inghost2;
  Float_t inghost3;
  kette->SetBranchAddress("p0_TRACKghost",&inghost1);
  kette->SetBranchAddress("p1_TRACKghost",&inghost2);
  kette->SetBranchAddress("p2_TRACKghost",&inghost3);
  Float_t inpid1;
  Float_t inpid2;
  Float_t inpid3;
  kette->SetBranchAddress("p0_singlePID",&inpid1);
  kette->SetBranchAddress("p1_singlePID",&inpid2);
  kette->SetBranchAddress("p2_singlePID",&inpid3);
  Float_t inann1;
  Float_t inann2;
  Float_t inann3;
  kette->SetBranchAddress("p0_ANNmuon",&inann1);
  kette->SetBranchAddress("p1_ANNmuon",&inann2);
  kette->SetBranchAddress("p2_ANNmuon",&inann3);
  TFile * ff = new TFile(org_file.c_str(),"update");
  TTree* baum = new TTree("minmax","minmax");
  Float_t wertghost;
  Float_t muonghost;
  Float_t wertpid;
  Float_t wertann;
  baum->Branch("maxghost",&wertghost,"maxghost/F");
  baum->Branch("mughost",&muonghost,"mughost/F");
  baum->Branch("minpid",&wertpid,"minpid/F");
  baum->Branch("minann",&wertann,"minann/F");
  unsigned u = 0 ;
  for ( ; u < kette->GetEntries() ; ++u) {
    kette->GetEntry(u);
    wertghost = std::max(inghost1,std::max(inghost2,inghost3));
    muonghost = (std::max(inghost2,inghost3));
    wertpid = std::min(inpid1,std::min(inpid2,inpid3));
    wertann = std::min(inann1,std::min(inann2,inann3));
//    std::cout << in1 << "\t" << in2 << "\t" << in3 << "\t" << wert << std::endl;
    baum->Fill();
  }
  baum->AddFriend("Ds2PhiPi",org_file.c_str());
  ff->WriteTObject(baum);
  ff->Close();
  return 0;
}

int main() {
  return maxghost();
}
