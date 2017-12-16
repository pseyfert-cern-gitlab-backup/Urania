#include "deltaLQ.h"
#include "TFile.h"
#include "logstream.h"
#include <iostream>
#include "TChain.h"
#include <stdio.h>

int main(int argc, char** argv) {
 sighist1=NULL;
 sighist2=NULL;
 bkghist=NULL;
  std::string addition = "";
  if (argc>=2) {
    addition += "_";
    addition += argv[1];
  }
  std::string pid = "min(p0_ANNmuon,min(p1_ANNmuon,p2_ANNmuon))";
  std::string geo = "NeuroBayes_0x141cf818";
  logstreams::logstream::setLogLevel(1);
  logstreams::logstream::setLogLevel(2);
  binning b(-1.f,1.f,8u,3u,geo.c_str());
  binning p(-0.1f,1.f,8u,3u,pid.c_str());
  multitrunkbinholder holder;
  holder.setBinning(&b);
  holder.setBinning(&p);
  holder.setFoM(&cls_ffom);
  TChain* sig = new TChain("Tau23Mu");
  sig->Add("/auto/data/autodata/pseyfert/Tau_MC/SIGNAL.root");
  TChain* bkg = new TChain("Tau23Mu");
  bkg->Add("/auto/data/autodata/pseyfert/Tau23Mu_Stripping20/v9.2/merged.root");
  TFile* ff = new TFile("buffer9.root","recreate");
  ff->cd();
  std::string cutstring("L0Dec&&Hlt1Dec&&mass>1000&&(TriggerDecHlt2TriMuonTauDecision||TriggerDecHlt2CharmSemilepD2HMuMuDecision||TriggerDecHlt2DiMuonDetachedDecision)&&cleaningcut&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&mass_p0p1>250&&LifeTime<0.025&&LifeTime>-0.01&&dira>0.99");
  TTree* copy = bkg->CopyTree(cutstring.c_str());
  cutstring = std::string("truetau==15==L0Dec&&Hlt1Dec&&mass>1000&&(TriggerDecHlt2TriMuonTauDecision||TriggerDecHlt2CharmSemilepD2HMuMuDecision||TriggerDecHlt2DiMuonDetachedDecision)&&cleaningcut&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&mass_p0p1>250&&LifeTime<0.025&&LifeTime>-0.01&&dira>0.99");
  TTree* scopy = sig->CopyTree(cutstring.c_str());
  cutstring = std::string("1");
  holder.setBackground(copy);
  holder.setSignal(sig);
  float bestfom = holder.compute_additive_fom(cutstring.c_str());
  binning bestbinning = b;
  binning bestbinning_p = p;

  unsigned nSteps = 0;
  while(holder.increment()) {
    //c.debug_statement();
    //b_3.debug_statement();
    ++nSteps;
  }
  std::cout << "will need to do " << nSteps << " steps\n";
  b.reset();
  p.reset();

  unsigned count = 0u;
  int buffer =  logstreams::logstream::logLevel();
  binning compare = b;
  while(holder.increment()) {
    ++count;
    if (count == (nSteps%200))
      std::cout << "." << std::endl;
    float fomval = holder.compute_additive_fom(cutstring.c_str());
    if (fomval > bestfom) {
      bestfom = fomval; //hold.compute_additive_fom(cutstring.c_str());
      bestbinning = b;
      bestbinning_p = p;
    }
  }

  std::cout << "done\n";
  std::cout << "best " << geo << " binning is " << bestfom << ":\n";
  bestbinning.debug_statement();
  bestbinning_p.debug_statement();
  delete bkg;
  delete sig;
  return 0;
}
