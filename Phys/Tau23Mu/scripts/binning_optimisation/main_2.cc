#include "deltaLQ.h"
#include "logstream.h"
#include <iostream>
#include "TChain.h"
#include <cmath>
#include <stdio.h>
int main() {
  logstreams::logstream::setLogLevel(2);
  binning b(+0.f,1.f,19u,5u,"GeoMVA");
  binning b_2(+0.f,1.f,19u,5u,"GeoMVA");
  //b.debug_statement();
  binningholder hold;
  multibinholder multihold;
  hold.setBinning(&b);
  multihold.setBinning(&b_2);
  hold.setFoM(&cls_ffom);
  multihold.setFoM(&cls_ffom);
  TChain* sig = new TChain("Tau23Mu");
  sig->Add("~/tmpbuffer/mctru_tau23mu_mu_BDTv3e2_flatV7.root");
  TChain* bkg = new TChain("Tau23Mu");
  bkg->Add("~/tmpbuffer/stp17unblinded_mu_BDTv3e2_4xxpb_flatV6.root");
  //std::string cutstring("cleaningcut&&Hlt1Dec&&Hlt2Dec&&L0Dec&&mass_p0p1>250&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&min(p0_singlePID,min(p1_singlePID,p1_singlePID))>0.05&&((mass>1750&&mass<1763)||(mass>1794&&mass<1798))");
  std::string cutstring("cleaningcut&&Hlt1Dec&&Hlt2Dec&&L0Dec&&mass_p0p1>250&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&min(p0_singlePID,min(p1_singlePID,p1_singlePID))>-0.95&&((mass<1600)||(mass>1950))");
  std::cout << "start" << std::endl;
  TTree* copy = bkg->CopyTree(cutstring.c_str());
  hold.setBackground(copy);
  hold.setSignal(sig);
  multihold.setBackground(copy);
  multihold.setSignal(sig);
  std::cout << "start2" << std::endl;
  float bestfom = hold.compute_additive_fom(cutstring.c_str());
  std::cout << "start3" << std::endl;
  float bestfom_2 = multihold.compute_additive_fom(cutstring.c_str());
  std::cout << "start4" << std::endl;
  binning bestbinning = b;
  binning bestbinning_2 = b_2;

  unsigned nSteps = 0;
  while(b.increment()) {
    ++nSteps;
  }
  std::cout << "will need to do " << nSteps << " steps\n";
  b.reset();

  unsigned count = 0u;
  int buffer = logstreams::logstream::logLevel();
  while(b.increment()) {
    std::cout << ".";
    fflush(stdout);
    //b.debug_statement();
    ++count;
    float fomval = hold.compute_additive_fom(cutstring.c_str());
    if (std::isnan(fomval)) logstreams::error << "nan computed" << std::endl;
    if (std::isinf(fomval)) logstreams::error << "inf computed" << std::endl;
    if (1000u==count) {
      logstreams::logstream::setLogLevel(0);
      b.debug_statement();
      std::cout << "FOM = " << fomval << std::endl;    
    }
    if (1001u==count)
      logstreams::logstream::setLogLevel(buffer);
    if (fomval > bestfom) {
      bestfom = fomval; //hold.compute_additive_fom(cutstring.c_str());
      bestbinning = b;
    }
  }

  count = 0u;
  if (false)
  while(multihold.increment()) {
    //b.debug_statement();

    if (100u==count)
      logstreams::logstream::setLogLevel(0);
    if (101u==count)
      logstreams::logstream::setLogLevel(buffer);
 
    float fomval = multihold.compute_additive_fom(cutstring.c_str());
//    std::cout << "FOM = " << fomval << std::endl;    
    if (fomval > bestfom_2) {
      bestfom_2 = fomval;
      bestbinning_2 = b_2;
    }
  }

  std::cout << "best = " << bestfom << std::endl;    
  std::cout << "done\n";
  std::cout << "best binning is :\n";
  bestbinning.debug_statement();
  bestbinning_2.debug_statement();
  delete bkg;
//  delete bkg;
  delete sig;
  return 0;
}
