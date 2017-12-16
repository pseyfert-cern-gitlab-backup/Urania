#include <TChain.h>
#include <TFile.h>
#include <TH1.h>
#include <iostream>
#include <utility>
#include <vector>

int weight(int argc, char** argv) {
  std::vector<TTree*> vektor;
  std::vector<TFile*> files;
  for (int k = 1 ; k < argc ; ++k) {
    TTree* b;
    vektor.push_back(b);
    TFile* f = new TFile(argv[k],"update");
    files.push_back(f);
    files.back()->GetObject("Tau23Mu",vektor.back());
  }
  TFile* f_norm = new TFile("/tmp/GeoMVA_calib.root","read");
  TFile* f_pol = new TFile("/tmp/GeoMVA_pol_calib.root","read");
  TFile* f_dimu = new TFile("/tmp/GeoMVA_dimu_calib.root","read");
  TFile* f_poldimu = new TFile("/tmp/GeoMVA_dimu_calib.root","read");
  TH1* h_norm;
  TH1* h_pol;
  TH1* h_dimu;
  TH1* h_poldimu;
  f_norm->GetObject("w_GeoMVA",h_norm);
  f_pol->GetObject("w_GeoMVA_pol",h_pol);
  f_dimu->GetObject("w_GeoMVA_dimu",h_dimu);
  f_poldimu->GetObject("w_GeoMVA_dimu",h_poldimu);

  /// sanity checks
  {
    if (NULL == h_norm) return 1;
    if (NULL == h_pol) return 1;
    if (NULL == h_dimu) return 1;
    if (NULL == h_poldimu) return 1;
  }

  Float_t geomva;
  Float_t geomva_pol;
  Float_t geomva_dimu;
  Float_t geomva_poldimu;
  Float_t w_geomva;
  Float_t w_geomva_pol;
  Float_t w_geomva_dimu;
  Float_t w_geomva_poldimu;
  for (unsigned k = 0 ; k < vektor.size() ; ++k) {
    TTree* kette = vektor[k];
    TFile* kk = files[k];
    kk->cd();
    kette->SetBranchAddress("GeoMVA",&geomva);
    kette->SetBranchAddress("GeoMVA_pol",&geomva_pol);
    kette->SetBranchAddress("GeoMVA_dimu",&geomva_dimu);
    kette->SetBranchAddress("GeoMVA_poldimu",&geomva_poldimu);
    TTree* baum = new TTree("minmax","minmax");
    baum->Branch("w_GeoMVA",&w_geomva,"w_GeoMVA/F");
    baum->Branch("w_GeoMVA_pol",&w_geomva_pol,"w_GeoMVA_pol/F");
    baum->Branch("w_GeoMVA_dimu",&w_geomva_dimu,"w_GeoMVA_dimu/F");
    baum->Branch("w_GeoMVA_poldimu",&w_geomva_poldimu,"w_GeoMVA_poldimu/F");
    unsigned u = 0 ;
    for ( ; u < kette->GetEntries() ; ++u) {
      kette->GetEntry(u);
      w_geomva = h_norm->GetBinContent(h_norm->FindBin(geomva));
      w_geomva_pol = h_pol->GetBinContent(h_pol->FindBin(geomva));
      w_geomva_dimu = h_dimu->GetBinContent(h_dimu->FindBin(geomva));
      w_geomva_poldimu = h_poldimu->GetBinContent(h_poldimu->FindBin(geomva));
      baum->Fill();
    }
    baum->AddFriend("Tau23Mu",kk->GetName());
    kk->WriteTObject(baum);
    kk->Close();
    delete kk;
  }
  return 0;
}

int main(int argc, char** argv) {
  int ret =  weight(argc,argv);
  if (1==ret) std::cerr << "histograms not found" << std::endl;
  return ret;
}

