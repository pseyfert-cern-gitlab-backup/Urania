/** @file calibrateGEO.C
 *  @brief calibration of the geometric classifier
 *
 *  @author Paul Seyfert
 *  @date   2011-12-13
 */


#include "TString.h"
#include "TTree.h"
#include <iostream>
#include <fstream>
#include "TH2.h"
#include <TCanvas.h>
#include "TFile.h"
#include "TStyle.h"
#include "TROOT.h"

#include "../params/limit_interface.h"


TH1F* finehist(std::string);


TH1* correctionFactors(TTree* dsMC, TTree* tauMC) {
  TCanvas* buffer = new TCanvas();
  limit_interface* li = new limit_interface();
  /// @todo determine min and max automatically
  TH1F* denominator = finehist(std::string("denom"));//new TH1F("denom","denom",90,-.8,.8);
  TH1F* numerator   = finehist(std::string("numer"));//new TH1F("numer","numer",90,-.8,.8);


  TString tauweight("(");
  tauweight += li->getGeoRefString() + ")";
  if (reweighttau) {
    tauweight += "*productionweightMC11v3";
  }

  //TString dsweight("L0Dec*Hlt1Dec*Hlt2Dec*(mass_p0p1>250)*cleaningcut");
  TString dsweight("1");
  if (reweightds) { 
    dsweight += "*productionweightMC11v3";
  }

  dsweight += "*yield_dst_sw";


  denominator->Sumw2();
  numerator->Sumw2();
  dsMC->Draw(li->the_geo()+">>denom",dsweight);
  std::cout << "dsMC " << dsweight << std::endl;
  tauMC->Draw(li->the_geo()+">>numer",tauweight);
  std::cout << "tauMC " << tauweight << std::endl;

  //numerator->Sumw2();
  //denominator->Sumw2();

  denominator->Scale(1./((float)denominator->GetSum()));
  numerator->Scale(1./((float)numerator->GetSum()));

  TH1* correction = (TH1*)numerator->Clone("correction");

  correction->Sumw2();
  correction->Divide(denominator);

  delete li;
  //delete denominator;
  //delete numerator;
  delete buffer;
  return correction;
}

TH1* mctruedistribution(TTree* tau23mu) {
  limit_interface* li = new limit_interface();
  TH1* retval = new TH1F("mctru","mctru",li->the_geobins(),li->the_geobinning());

  tau23mu->Draw("GeoMVA>>mctru",TString("(")+li->getGeoRefString()+")*productionweightMC11v3");


  delete li;
  return retval;
}

TH1* geocalibration(TTree* dsData, TH1* correction) {
  TCanvas* buffer = new TCanvas();
  TH1* data = finehist(std::string("data"));//new TH1F("data","data",90,-.8,.8);

  data->Sumw2();
  limit_interface* li = new limit_interface();
  dsData->Draw(li->the_geo()+">>data","yield_dst_sw");
  std::cout << "dsData " << "yield_dst_sw" << std::endl;

  data->Multiply(correction);

  float contents = 0;
  for (unsigned b = 0 ; b <= 1+data->GetNbinsX() ; ++b) {
    contents += data->GetBinContent(b);
  }

  data->Scale(1./contents);

  TH1* retval = new TH1F("calibration","calibration",li->the_geobins(),li->the_geobinning());
  for (int i = 0 ; i <= li->the_geobins() ; ++i ) {
    std::cout << li->the_geobinning()[i] << std::endl;
  }
  retval->Sumw2();

  for (unsigned b = 0 ; b <= 1+data->GetNbinsX() ; ++b) {
    unsigned int bb = retval->FindBin(data->GetBinCenter(b));
    float c = retval->GetBinContent(bb);
    float e = retval->GetBinError(bb);

    c += data->GetBinContent(b);
    retval->SetBinContent(bb,c);
    e = sqrt(e*e + data->GetBinError(b) * data->GetBinError(b));
    retval->SetBinError(bb,e);
  }

  contents=0.;
  for (unsigned bb = 0 ; bb <= 1+retval->GetNbinsX() ; ++bb) {
    contents += retval->GetBinContent(bb);
  }

  retval->Scale(1./contents);
  retval->SetMinimum(0.);

  //delete data;
  delete li;
  delete buffer;

  TCanvas* canvas = new TCanvas();
  retval->Draw();
  return retval;
}

TH1F* finehist(std::string n) {
  limit_interface* li = new limit_interface();
  int bins = 50;
  float binning[50+1];
  binning[0] = -1.;
  binning[1] = -0.60;
  for (unsigned k = 2 ; k < 51 ; ++k ) {
    binning[k] = -0.60 + (1. + 0.60) / ((float) 49) * ((float) k-1);
    std::cout << binning[k] << std::endl;
  }
  return new TH1F(n.c_str(),n.c_str(),bins,binning);
  return new TH1F(n.c_str(),n.c_str(),051,-1.,1.00000001);
  return new TH1F(n.c_str(),n.c_str(),li->the_geobins(),li->the_geobinning());
}
