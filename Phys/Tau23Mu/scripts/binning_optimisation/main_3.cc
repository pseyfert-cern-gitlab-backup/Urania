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
  std::string geoname = "GeoMVA";
  dalitz+=addition;
  logstreams::logstream::setLogLevel(1);
  logstreams::logstream::setLogLevel(6);
  binning b(+0.f,1.f,19u,5u,geoname.c_str());
  binning b_2(+0.f,1.f,19u,5u,geoname.c_str());
  binning b_3(+0.f,1.f,19u,5u,geoname.c_str());
  //binning c(+0.f,1.f,2u,2u,"mass");
  //binning c(-1.f,1.0f,18u,2u,"Dalitz");
  //binning c_2(-1.f,1.0f,18u,2u,"Dalitz");
  binning c(-0.1f,0.2f,19u,2u,dalitz.c_str());
  binning c_2(-0.1f,0.2f,19u,2u,dalitz.c_str());
  //b.debug_statement();
  binningholder hold;
  multibinholder hold_c;
//  multitrunkbinholder hold_c;
  multibinholder multihold2;
//  multitrunkbinholder multihold2;
  hold.setBinning(&b);
  hold_c.setBinning(&c_2);
  multihold2.setBinning(&b_3);
  multihold2.setBinning(&c);
  hold.setFoM(&cls_ffom);
  hold_c.setFoM(&cls_ffom);
  multihold2.setFoM(&cls_ffom);
  TChain* sig = new TChain("minmax");
  sig->Add("/home/pseyfert/tmpbuffer/v8/tau23mu_UP_flat.root");
  sig->Add("/home/pseyfert/tmpbuffer/v8/tau23mu_DOWN_flat.root");
  TChain* bkg = new TChain("Tau23Mu");
  bkg->Add("/home/pseyfert/tmpbuffer/v8/stp17unblinded_mu_BDTv4_405pb_flatV8.root");
  bkg->Add("/home/pseyfert/tmpbuffer/v8/stp17unblinded_md_BDTv4_522pb_flatV8.root");
//  std::string cutstring("cleaningcut&&Hlt1Dec&&Hlt2Dec&&L0Dec&&mass_p0p1>250&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&min(p0_singlePID,min(p1_singlePID,p1_singlePID))>0.05&&((mass>1750&&mass<1763)||(mass>1794&&mass<1798))");
  std::string cutstring("cleaningcut&&Hlt1Dec&&Hlt2Dec&&L0Dec&&mass_p0p1>250&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&min(p0_singlePID,min(p1_singlePID,p1_singlePID))>0.05&&((mass>1748&&mass<1763)||(mass>1794&&mass<1809))");
  TTree* copy = bkg->CopyTree(cutstring.c_str());
  hold.setBackground(copy);
  hold.setSignal(sig);
  hold_c.setBackground(copy);
  hold_c.setSignal(sig);
  multihold2.setBackground(copy);
  multihold2.setSignal(sig);
  hold.setGeoNAME(geoname);
  hold_c.setGeoNAME(geoname);
  multihold2.setGeoNAME(geoname);
  float fomval ;
  std::vector<unsigned> bl;
  std::vector<unsigned> cl;

  g_cls_norm = 100.;
  bl.clear();
  bl.push_back(6u);
  bl.push_back(8u);
  bl.push_back(11u);
  bl.push_back(13u);
  b_3.set(bl);
  cl.clear();
  cl.push_back(0u);
  c.set(cl);


  fomval = multihold2.compute_additive_fom(cutstring.c_str());
  logstreams::logstream::setLogLevel(1);
  std::cout << "done\n";
  std::cout << "fomval is " << fomval << ":\n";
  b_3.debug_statement();
  c.debug_statement();
  logstreams::logstream::setLogLevel(6);

  bl.clear();
  bl.push_back(7u);
  bl.push_back(9u);
  bl.push_back(12u);
  bl.push_back(14u);
  b_3.set(bl);
  cl.clear();
  cl.push_back(8u);
  c.set(cl);

  fomval = multihold2.compute_additive_fom(cutstring.c_str());
  logstreams::logstream::setLogLevel(1);
  std::cout << "done\n";
  std::cout << "fomval is " << fomval << ":\n";
  b_3.debug_statement();
  c.debug_statement();
  logstreams::logstream::setLogLevel(6);


  g_cls_norm = 10.;
   bl.clear();
  bl.push_back(6u);
  bl.push_back(8u);
  bl.push_back(11u);
  bl.push_back(13u);
  b_3.set(bl);
  cl.clear();
  cl.push_back(0u);
  c.set(cl);


  fomval = multihold2.compute_additive_fom(cutstring.c_str());
  logstreams::logstream::setLogLevel(1);
  std::cout << "done\n";
  std::cout << "fomval is " << fomval << ":\n";
  b_3.debug_statement();
  c.debug_statement();
  logstreams::logstream::setLogLevel(6);

  bl.clear();
  bl.push_back(7u);
  bl.push_back(9u);
  bl.push_back(12u);
  bl.push_back(14u);
  b_3.set(bl);
  cl.clear();
  cl.push_back(8u);
  c.set(cl);

  fomval = multihold2.compute_additive_fom(cutstring.c_str());
  logstreams::logstream::setLogLevel(1);
  std::cout << "done\n";
  std::cout << "fomval is " << fomval << ":\n";
  b_3.debug_statement();
  c.debug_statement();
  logstreams::logstream::setLogLevel(6);

 
  g_cls_norm = 1.;
   bl.clear();
  bl.push_back(6u);
  bl.push_back(8u);
  bl.push_back(11u);
  bl.push_back(13u);
  b_3.set(bl);
  cl.clear();
  cl.push_back(0u);
  c.set(cl);


  fomval = multihold2.compute_additive_fom(cutstring.c_str());
  logstreams::logstream::setLogLevel(1);
  std::cout << "done\n";
  std::cout << "fomval is " << fomval << ":\n";
  b_3.debug_statement();
  c.debug_statement();
  logstreams::logstream::setLogLevel(6);

  bl.clear();
  bl.push_back(7u);
  bl.push_back(9u);
  bl.push_back(12u);
  bl.push_back(14u);
  b_3.set(bl);
  cl.clear();
  cl.push_back(8u);
  c.set(cl);

  fomval = multihold2.compute_additive_fom(cutstring.c_str());
  logstreams::logstream::setLogLevel(1);
  std::cout << "done\n";
  std::cout << "fomval is " << fomval << ":\n";
  b_3.debug_statement();
  c.debug_statement();
  logstreams::logstream::setLogLevel(6);



  delete bkg;
//  delete bkg;
  delete sig;
  return 0;
}
