#include <TChain.h>
#include <TString.h>
#include <vector>

/**
* @file mcroc.C
* @brief make two quick ROC curves from MC w/o calibration
* @author Paul Seyfert
* @date 2012-10-18
*/


TString tmmm_f = "~/tmpbuffer/v8/tau23mu_DOWN_flat.root";
TString tpmm_f = "~/phd/Tau23Mu/scripts/TMVA_training/149cf818tau2pmumu.root";//"~/tmprescue/tau2pmumuOS_DOWN_flat.root";


TString tmmm_b = "Tau23Mu";
TString tpmm_b = "TestTree";//"Tau2PMuMuOS";

TString tmmm_m = "GeoMVA";
TString tpmm_m = "BDT";

const int signalID = 0;
const int backgroundID = 1;

void mcroc() {
  float scanpoint = -0.;
  std::vector<float> tmmm_sigeff;
  std::vector<float> tmmm_bkgeff;

  std::vector<float> tpmm_sigeff;
  std::vector<float> tpmm_bkgeff;

  TChain* testtree = new TChain(tpmm_b.Data());
  testtree->Add(tpmm_f.Data());

  TTree* signal = testtree->CopyTree(Form("classID==%d",signalID));
  TTree* background = testtree->CopyTree(Form("classID==%d",backgroundID));

  TH1F* buffer = new TH1F("buffer","buffer",100,-1.1,1.1);
  background->Draw("BDT>>buffer","1");
  float allbkg = buffer->GetSum();
  signal->Draw("BDT>>buffer","productionweightMC11");
  float allsig = buffer->GetSum();

  while (scanpoint < 1.02) {
    scanpoint += 0.005;
    signal->Draw("BDT>>buffer",Form("productionweightMC11*(%s>%f)",tmmm_m.Data(),scanpoint));
    float tmmm_thissig = buffer->GetSum();
    background->Draw("BDT>>buffer",Form("1*(%s>%f)",tmmm_m.Data(),scanpoint));
    float tmmm_thisbkg = buffer->GetSum();

    signal->Draw("BDT>>buffer",Form("productionweightMC11*(%s>%f)",tpmm_m.Data(),scanpoint));
    float tpmm_thissig = buffer->GetSum();
    background->Draw("BDT>>buffer",Form("1*(%s>%f)",tpmm_m.Data(),scanpoint));
    float tpmm_thisbkg = buffer->GetSum();


    tmmm_sigeff.push_back(((float)tmmm_thissig)/((float)allsig));
    tmmm_bkgeff.push_back(1.-((float)tmmm_thisbkg)/((float)allbkg));

    tpmm_sigeff.push_back(((float)tpmm_thissig)/((float)allsig));
    tpmm_bkgeff.push_back(1.-((float)tpmm_thisbkg)/((float)allbkg));
  }


  TGraph* tmmm_r = new TGraph(tmmm_sigeff.size(), &tmmm_sigeff[0], &tmmm_bkgeff[0]);
  TGraph* tpmm_r = new TGraph(tpmm_sigeff.size(), &tpmm_sigeff[0], &tpmm_bkgeff[0]);
  tmmm_r->SetLineColor(kBlue);
  tpmm_r->SetLineColor(kRed);

  TCanvas* c = new TCanvas();
  tmmm_r->Draw("ac");
  tpmm_r->Draw("same");

}
