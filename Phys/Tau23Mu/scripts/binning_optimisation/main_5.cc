#include "deltaLQ.h"
#include "logstream.h"
#include <iostream>
#include "TChain.h"
#include <stdio.h>

int main(int argc, char** argv) {
  std::string addition = "";
  if (argc>=2) {
    addition += "_";
    addition += argv[1];
  }
  std::string dalitz = "Dalitz";
  dalitz+=addition;
  std::string geo = "GeoMVA";
  geo += addition;
  logstreams::logstream::setLogLevel(1);
  logstreams::logstream::setLogLevel(2);
  binning b(+0.f,1.f,19u,5u,geo.c_str());
  //binning b(+0.f,1.f,19u,2u,geo.c_str());
  binning b_2(+0.f,1.f,19u,5u,geo.c_str());
  binning b_3(+0.f,1.f,19u,5u,geo.c_str());
  //binning c(+0.f,1.f,2u,2u,"mass");
  //binning c(-1.f,1.0f,18u,2u,"Dalitz");
  //binning c_2(-1.f,1.0f,18u,2u,"Dalitz");
  binning c(-0.1f,0.2f,19u,2u,dalitz.c_str());
  binning c_2(-0.1f,0.2f,19u,2u,dalitz.c_str());
  //b.debug_statement();
  binningholder hold;
//  multibinholder hold_c;
  multitrunkbinholder hold_c;
  multibinholder multihold;
//  multibinholder multihold2;
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
  TChain* sig = new TChain("minmax");
  sig->Add("/auto/data/pseyfert/tmpbuffer/tau23mu_UP_flat.root");
  sig->Add("/auto/data/pseyfert/tmpbuffer/tau23mu_DOWN_flat.root");
  TChain* bkg = new TChain("Tau23Mu");
  bkg->Add("/auto/data/pseyfert/stp17unblinded_mu_BDTv4_405pb_flatV8.root");
  bkg->Add("/auto/data/pseyfert/stp17unblinded_md_BDTv4_522pb_flatV8.root");
  std::string cutstring("cleaningcut&&Hlt1Dec&&Hlt2Dec&&L0Dec&&mass_p0p1>250&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&min(p0_singlePID,min(p1_singlePID,p1_singlePID))>0.05&&((mass>1750&&mass<1763)||(mass>1794&&mass<1798))");
  TTree* copy = bkg->CopyTree(cutstring.c_str());
  hold.setBackground(copy);
  hold.setSignal(sig);
  hold.setGeoNAME(geo);
  hold_c.setBackground(copy);
  hold_c.setSignal(sig);
  multihold.setBackground(copy);
  multihold.setSignal(sig);
  multihold2.setBackground(copy);
  multihold2.setSignal(sig);
  float bestfom = hold.compute_additive_fom(cutstring.c_str());
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
  binning compare = b;
 // if (!quick)
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

  std::cout << "done\n";
  std::cout << "best " << geo << " binning is " << bestfom << ":\n";
  bestbinning.debug_statement();
  delete bkg;
  delete sig;
  return 0;
}
