#include "deltaLQ.h"
#include "logstream.h"
#include <iostream>
#include "TChain.h"
#include <stdio.h>

const char* geo = "NeuroBayes_0x141cf818";
const char* pid = "min(p0_ANNmuon,min(p1_ANNmuon,p2_ANNmuon))";

int main(int argc, char** argv) {
  bool quick = (2==argc);
  if (quick)
    std::cout << "quick run" << std::endl;
  logstreams::logstream::setLogLevel(1);
    binning b(-1.f,1.f,19u,5u,geo);
  //binning b(-1.f,1.f,19u,2u,geo);
  binning b_2(-1.f,1.f,19u,5u,geo);
  binning b_3(-1.f,1.f,19u,5u,geo);
  //binning c(+0.f,1.f,2u,2u,"mass");
    binning c(+0.f,1.0f,18u,5u,pid);
  binning c_2(+0.f,1.0f,18u,5u,pid);
  //binning c(-0.1f,0.2f,19u,2u,pid);
  //binning c_2(-0.1f,0.2f,19u,2u,pid);
  //b.debug_statement();
  binningholder hold;
  multitrunkbinholder hold_c;
  multibinholder multihold;
  multitrunkbinholder multihold2;
  hold.setBinning(&b);
  hold_c.setBinning(&c_2);
  //hold_c.setBinning(&b);
  multihold.setBinning(&b_2);
  multihold2.setBinning(&b_3);
  multihold2.setBinning(&c);
  hold.setFoM(&cls_ffom);
  hold_c.setFoM(&cls_ffom);
  multihold.setFoM(&cls_ffom);
  multihold2.setFoM(&cls_ffom);
  TChain* sig = new TChain("Tau23Mu");
  sig->Add("/auto/data/pseyfert/Tau_MC/tau23mu_mix_test.root");
  TChain* bkg = new TChain("Tau23Mu");
  bkg->Add("/auto/data/pseyfert/Tau23Mu_Stripping20/BACK.root");
  //std::string cutstring("cleaningcut&&Hlt1Dec&&Hlt2Dec&&L0Dec&&mass_p0p1>250&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&GeoMVA>0.6&&min(p0_singlePID,min(p1_singlePID,p1_singlePID))>0.05&&((mass>1750&&mass<1763)||(mass>1794&&mass<1798))");
  std::string cutstring("L0Dec&&Hlt1Dec&&mass>1000&&(TriggerDecHlt2TriMuonTauDecision||TriggerDecHlt2CharmSemilepD2HMuMuDecision||TriggerDecHlt2DiMuonDetachedDecision)&&cleaningcut&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&mass_p0p1>250&&LifeTime<0.025&&LifeTime>-0.01&&dira>0.99");
  TTree* copy = bkg->CopyTree(cutstring.c_str());
  hold.setBackground(copy);
  hold.setSignal(sig);
  hold_c.setBackground(copy);
  hold_c.setSignal(sig);
  multihold.setBackground(copy);
  multihold.setSignal(sig);
  multihold2.setBackground(copy);
  multihold2.setSignal(sig);
  float bestfom = hold.compute_additive_fom(cutstring.c_str());
  float bestfom_c = hold_c.compute_additive_fom(cutstring.c_str());
  float bestfom_2 = multihold.compute_additive_fom(cutstring.c_str());
  float bestfom_3 = multihold2.compute_additive_fom(cutstring.c_str());
  float bestfom_con =  multihold2.compute_additive_fom(cutstring.c_str());
  binning bestbinning = b;
  binning bestbinning_2 = b_2;
  binning bestbinning_3 = b_3;
  binning bestbinning_c = c;
  binning bestbinning_c_2 = c_2;
  binning bestbinning_con = c_2;

  unsigned nSteps = 0;
  while(multihold2.increment()) {
    //c.debug_statement();
    //b_3.debug_statement();
    ++nSteps;
  }
  std::cout << "will need to do " << nSteps << " steps\n";
  nSteps = 0;
  while(b.increment()) {
    ++nSteps;
  }
  std::cout << "will need to do " << nSteps << " steps\n";
  b.reset();
  c.reset();
  b_3.reset();

  unsigned count = 0u;
  int buffer =  logstreams::logstream::logLevel();
  binning compare = b;
 // if (!quick)
  if (false)
  while(b.increment()) {
    //b.debug_statement();
    ++count;
//    if (100u==count) {
//      //logstreams::logstream::setLogLevel(1);
//      std::cout << "changing log level " << std::endl;
//      b.debug_statement();
//      compare = b;
//    }
//    if (101u==count)
//      logstreams::logstream::setLogLevel(buffer);
    float fomval = hold.compute_additive_fom(cutstring.c_str());
//    if (2u==count)
//      std::cout << "FOM = " << fomval << std::endl;    
    if (fomval > bestfom) {
      bestfom = fomval; //hold.compute_additive_fom(cutstring.c_str());
      bestbinning = b;
    }
  }

  logstreams::always << " NOW OPTIMISATION c " << std::endl;
  count = 0u;
  while(hold_c.increment()) {
    float fomval_c = hold_c.compute_additive_fom(cutstring.c_str());
    std::cout << "============================================ " << fomval_c << std::endl;
    c_2.debug_statement();
    if (fomval_c > bestfom_c) {
      bestfom_c = fomval_c; //hold.compute_additive_fom(cutstring.c_str());
      bestbinning_c_2 = c_2;
    }
  }
  logstreams::always << " NOW OPTIMISATION 2 " << std::endl;
  count = 0u;
  if (false)
  while(multihold.increment()) {
    ++count;
    //b.debug_statement();

//    if (100u==count) {
//      //logstreams::logstream::setLogLevel(1);
//      b_2.debug_statement();
//    }
//    if (101u==count)
//      logstreams::logstream::setLogLevel(buffer);
 
    float fomval = multihold.compute_additive_fom(cutstring.c_str());
//    std::cout << "FOM = " << fomval << std::endl;    
    if (fomval > bestfom_2) {
      bestfom_2 = fomval;
      bestbinning_2 = b_2;
    }
  }

  logstreams::always << " NOW OPTIMISATION 3 " << std::endl;
  count = 0u;
  bool there_it_was=false;
  if (false)
  while(multihold2.increment()) {
    std::cout << ".";
    fflush(stdout);
    ++count;
    //b.debug_statement();
//    if (b_3==compare) {
//      //logstreams::logstream::setLogLevel(1);
//      b_3.debug_statement();
//    }
//    if (there_it_was) {
//      logstreams::logstream::setLogLevel(buffer);
//      there_it_was = false;
//    }
//    if (b_3==compare) {
//      there_it_was = true;
//    }
 
///// optimise on optimised
    float fomval = multihold2.compute_additive_fom(cutstring.c_str());
    if (b_3==bestbinning) {
      //    std::cout << "FOM = " << fomval << std::endl;    
      if (fomval > bestfom_con) {
        bestfom_con = fomval;
        bestbinning_con = c;
      } 
    }


//    std::cout << "FOM = " << fomval << std::endl;    
    if (fomval > bestfom_3) {
      bestfom_3 = fomval;
      bestbinning_3 = b_3;
      bestbinning_c = c;
    }
  }
  std::cout << "done\n";
  std::cout << "best GeoMVA binning is " << bestfom << ":\n";
  bestbinning.debug_statement();
//  std::cout << "best multiholder binning is  " << bestfom_2 << ":\n";
//  bestbinning_2.debug_statement();
  std::cout << "best combined  binning is  " << bestfom_3 << ":\n";
  bestbinning_3.debug_statement();
  bestbinning_c.debug_statement();
  std::cout << "best constrained  binning is  " << bestfom_con << ":\n";
  bestbinning_3.debug_statement();
  bestbinning_con.debug_statement();
  std::cout << "best Dalitz binning is " << bestfom_c << std::endl;
  bestbinning_c_2.debug_statement();
  delete bkg;
//  delete bkg;
  delete sig;
  return 0;
}
