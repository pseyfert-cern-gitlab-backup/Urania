#include "deltaLQ.h"
#include "convert.h"
#include "TMath.h"
#include <algorithm>
#include "logstream.h"
#include <iostream>
#include "TChain.h"
#include "TH2F.h"
#include "TFile.h"
#include <stdio.h>

float h_cls_norm ;

float this_cls_fom(int bkg, float sigeff) {
  double Qsb = TMath::Poisson(sigeff*h_cls_norm+bkg,sigeff*h_cls_norm+bkg) / TMath::Poisson(sigeff*h_cls_norm+bkg,bkg);
  if (isnan(Qsb) || isinf(Qsb)) { logstreams::error << "insane Qsb" << std::endl;
    logstreams::error << "bkg = " << bkg << "\t\tsig = " << sigeff << std::endl;
  return -999.;
  }
  double denom = TMath::Poisson(sigeff*h_cls_norm+bkg,bkg);
  if (isnan(denom) || isinf(denom)) logstreams::error << "insane denom" << std::endl;
  if (isnan(denom) || isinf(denom)) logstreams::error << "insane denom: Poisson(" << sigeff*h_cls_norm+bkg << "," << bkg << ")" << std::endl;
  if (0.==denom) logstreams::error << "zero denom: Poisson(" << sigeff*h_cls_norm+bkg << "," << bkg << ")" << std::endl;
  double Qb = TMath::Poisson(bkg,sigeff*h_cls_norm+bkg) / TMath::Poisson(bkg,bkg);
  if (isnan(Qb) || isinf(Qb)) logstreams::error << "insane Qb" << std::endl;
  double returnvalue =  2*(TMath::Log(Qsb)-TMath::Log(Qb));
  if (isnan(returnvalue) || isinf(returnvalue)) logstreams::error << "insane DeltaLQ" << std::endl;
  return 2*(TMath::Log(Qsb)-TMath::Log(Qb));
}

int main(int argc, char** argv) {
  unsigned gbins = 5u;
  unsigned pbins = 5u;
  if (argc>=2) {
     pbins = atoi(argv[1]);
  }
  std::string pid = "min(p0_ANNmuon,min(p1_ANNmuon,p2_ANNmuon))";
  std::string geo = "GeoMVA";
  unsigned gfinebins = 20u;
  unsigned pfinebins = 20u;
  binning p(0.f,1.0001f,pfinebins-1,pbins,pid.c_str());
  binning b(0.f,1.0001f,gfinebins-1,gbins,geo.c_str());
  std::vector<float> tmpvec;
  tmpvec.clear();
  //tmpvec.push_back(-0.2);
  //tmpvec.push_back(-0.1);
  //tmpvec.push_back(0.0);
  tmpvec.push_back(0.1);
  //tmpvec.push_back(0.3);
  //tmpvec.push_back(0.4);
  tmpvec.push_back(0.5);
  tmpvec.push_back(0.6);
  tmpvec.push_back(0.70);
  tmpvec.push_back(0.75);
  tmpvec.push_back(0.775);
  tmpvec.push_back(0.80);
  tmpvec.push_back(0.825);
  tmpvec.push_back(0.85);
  tmpvec.push_back(0.875);
  tmpvec.push_back(0.90);
  tmpvec.push_back(0.925);
  tmpvec.push_back(0.95);
  tmpvec.push_back(0.96);
  tmpvec.push_back(0.97);
  tmpvec.push_back(0.98);
  tmpvec.push_back(0.985);
  tmpvec.push_back(0.99);
  tmpvec.push_back(0.995);
  if (tmpvec.size() != b.fine_binning().size()) {
//    logstreams::fatal << "tmpvec is too large " << ((tmpvec.size())>(b.fine_binning().size())) << std::endl;
//    return 33;
  }
  b.set_fine_binning(tmpvec);

  std::vector<float> bmpvec;
  bmpvec.clear();
  bmpvec.push_back(-1.);
  for (unsigned u = 0 ; u < b.fine_binning().size() ; ++u) {
    bmpvec.push_back(p.fine_binning()[u]);
    /// don't use tmpvec
  //for (unsigned u = 0 ; u < tmpvec.size() ; ++u) {
  //  bmpvec.push_back(tmpvec[u]);
  }
  bmpvec.push_back(1.0001f);
  std::vector<float> pmpvec;
  pmpvec.clear();
  pmpvec.push_back(0.);
  for (unsigned u = 0 ; u < p.fine_binning().size() ; ++u) {
    pmpvec.push_back(p.fine_binning()[u]);
  }
  pmpvec.push_back(1.0001f);
  float* a = &(pmpvec[0]);
  float* aa = &(bmpvec[0]);
  TH2F* hsig = new TH2F("sig","sig",(int)gfinebins,aa,(int)pfinebins,a);
  TH2F* hbkg = new TH2F("bkg","bkg",(int)gfinebins,aa,(int)pfinebins,a);

  TChain* sig = new TChain("Tau23Mu");
  sig->Add("/auto/data/pseyfert/Tau_MC/buffer.root");
  //sig->Add("/auto/data/pseyfert/Tau_MC/classified_test.root");
  TChain* bkg = new TChain("Tau23Mu");
  //bkg->Add("/auto/data/pseyfert/Tau23Mu_Stripping20/v9_2nd/merged_classified.root");
  bkg->Add("/auto/data/pseyfert/Tau23Mu_Stripping20/v9_2nd/buffer.root");
  std::string cutstring("L0Dec&&Hlt1Dec&&mass>1000&&(TriggerDecHlt2TriMuonTauDecision||TriggerDecHlt2CharmSemilepD2HMuMuDecision||TriggerDecHlt2DiMuonDetachedDecision)&&cleaningcut&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&mass_p0p1>250&&LifeTime<0.025&&LifeTime>-0.01&&dira>0.99");
  std::cout << "start copying" << std::endl;
  //TFile* ff = new TFile("buffer23.root","recreate");
  //ff->cd();
  std::cout << "filled " << bkg->Draw(Form("%s:%s>>bkg",pid.c_str(),geo.c_str()),cutstring.c_str()) << std::endl;
  //TTree* copy = bkg->CopyTree(cutstring.c_str());
  cutstring = std::string("truetau==15&&L0Dec&&Hlt1Dec&&mass>1000&&(TriggerDecHlt2TriMuonTauDecision||TriggerDecHlt2CharmSemilepD2HMuMuDecision||TriggerDecHlt2DiMuonDetachedDecision)&&cleaningcut&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&mass_p0p1>250&&LifeTime<0.025&&LifeTime>-0.01&&dira>0.99");
  std::cout << "filled " << sig->Draw(Form("%s:%s>>sig",pid.c_str(),geo.c_str()),cutstring.c_str()) << std::endl;
  //TTree* scopy = sig->CopyTree(cutstring.c_str());
  std::cout << "finished copying" << std::endl;
  h_cls_norm = 1./hsig->GetSum();
  //ff->Close();
  //delete ff;
  //delete scopy;
  //delete copy;

  std::cout << hsig->GetSum() << std::endl;
  std::cout << hbkg->GetSum() << std::endl;

  multitrunkbinholder holder;
  holder.setBinning(&b);
  holder.setBinning(&p);
  //holder.setFoM(&cls_ffom);

  cutstring = std::string("1");
  float bestfom = 0.;
  binning bestbinning = b;
  binning bestbinning_p = p;

  unsigned nSteps = 0;
  std::cout << "step counting" << std::endl;
  while(holder.increment()) {
    ++nSteps;
  }
  std::cout << "need " << nSteps << " steps\n";
  b.reset();
  p.reset();
  int infosteps = nSteps/15;
  nSteps=0;
  if (true)
  while(holder.increment()) {
    ++nSteps;
    //if (1==(nSteps%infosteps)) std::cout << "now at step " << nSteps << std::endl;
    //c.debug_statement();
    //b_3.debug_statement();
    float thisfom = 0.;
    bool removetrash = true;
    for (unsigned gbin = ((removetrash)?1:0) ; gbin<gbins ; ++gbin) {

      int finegbinlow = ((gbin)?(b.boundaries()[gbin-1]+2):(1));
      int finegbinhigh =((gbin==b.boundaries().size())?(gfinebins):(b.boundaries()[gbin]+1));
      for (unsigned pbin = ((removetrash)?1:0) ; pbin<pbins ; ++pbin) {
        int finepbinlow = ((pbin)?(p.boundaries()[pbin-1]+2):(1));
        int finepbinhigh =((pbin==p.boundaries().size())?(pfinebins):(p.boundaries()[pbin]+1));
        int signals = 0;
        int backgrounds = 0;
        for (unsigned gsub = finegbinlow; gsub <= finegbinhigh ; ++gsub) {
          for (unsigned psub = finepbinlow; psub <= finepbinhigh ; ++psub) {
            int globalbin = hsig->GetBin((int)gsub,(int)psub);
            signals+=hsig->GetBinContent(globalbin);
            backgrounds+=hbkg->GetBinContent(globalbin);
          }
        }
        if (signals>0&&backgrounds>0) {
          float binfom = this_cls_fom(backgrounds,signals);
          thisfom += binfom;
        } else {
//          std::cout << "empty bin!" << std::endl;
          thisfom -=1.;
        }
      }
    }
    if (thisfom > bestfom) {
      bestfom = thisfom;
      bestbinning = b;
      bestbinning_p = p;
    }
    ++nSteps;
  }

  std::cout << "done\n";
  std::cout << "best " << geo << " binning is " << bestfom << ":\n";
  bestbinning.debug_statement();
  bestbinning_p.debug_statement();
  delete bkg;
  delete sig;
  return 0;
}


