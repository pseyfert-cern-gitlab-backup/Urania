#include <TH2.h>

#include <cstdlib>
#include <TF1.h>
#include <TFile.h>
#include <TChain.h>
#include <TCanvas.h>
#include <math.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TColor.h>
#include <TApplication.h>
#include <TRandom.h>
#include <iostream>
#include "lhcb.h"
#include "gamma.h"

typedef float (*fillfunction)(const double,const double,const double);

float Number = 1.;
float norm = 1.;
float normR = 1.;
float normRAD = 1.;
float normRAD_L = 1.;
float normRAD_R = 1.;
double m23sq_max(double m12sq) ;
double m23sq_min(double m12sq) ;


TH2F* checkfillwith(TH2F* hist, fillfunction func) {
  for (unsigned x = 1u ; x <= (unsigned)hist->GetNbinsX() ; ++x) {
    for (unsigned y = 1u ; y <= (unsigned)hist->GetNbinsY() ; ++y) {
      int bin = hist->GetBin(x,y);
      float xval = hist->GetXaxis()->GetBinCenter(x);
      float yval = hist->GetYaxis()->GetBinCenter(y);
      float zval = taumass*taumass+3.*mumass*mumass-xval-yval;

      float val = 0.;
      if (zval>4*mumass*mumass && yval<m23sq_max(xval) && yval>m23sq_min(xval)) {
        val = func(xval,zval,yval);
      }
      hist->SetBinContent(bin,val);
    }
  }
  return hist;
}

TH2F* fillwith(TH2F* hist, fillfunction func) {
  for (unsigned x = 1u ; x <= (unsigned)hist->GetNbinsX() ; ++x) {
    for (unsigned y = 1u ; y <= (unsigned)hist->GetNbinsY() ; ++y) {
      int bin = hist->GetBin(x,y);
      float xval = hist->GetXaxis()->GetBinCenter(x);
      float yval = hist->GetYaxis()->GetBinCenter(y);
      float zval = taumass*taumass+3.*mumass*mumass-xval-yval;

      float val = 0.;
      if (zval>4*mumass*mumass && yval<m23sq_max(xval) && yval>m23sq_min(xval)) {
        val = func(xval,yval,zval);
      }
      hist->SetBinContent(bin,val);
    }
  }
  return hist;
}

//double mumass = 105.752;
//double taumass = 1776.41;


double m23sq_max(double m12sq) {
  double e2star = (m12sq-mumass*mumass+mumass*mumass)/2/sqrt(m12sq);
  double e3star = (taumass*taumass-m12sq-mumass*mumass)/2/sqrt(m12sq);
  double parenthesis = sqrt(e2star*e2star-mumass*mumass) - sqrt(e3star*e3star-mumass*mumass);
  return (e2star+e3star)*(e2star+e3star)-parenthesis*parenthesis;
}
double m23sq_min(double m12sq) {
  double e2star = (m12sq-mumass*mumass+mumass*mumass)/2/sqrt(m12sq);
  double e3star = (taumass*taumass-m12sq-mumass*mumass)/2/sqrt(m12sq);
  double parenthesis = sqrt(e2star*e2star-mumass*mumass) + sqrt(e3star*e3star-mumass*mumass);
  return (e2star+e3star)*(e2star+e3star)-parenthesis*parenthesis;
}
double m12sq_max() {
  return (taumass-mumass)*(taumass-mumass);
}
double m12sq_min() {
  return 4*mumass*mumass;
}

float flat(double m12sq, double m23sq, double m13sq) {
  return 1./Number;
}

double m23sq_max(double* m12sq, double* pars) {
  return m23sq_max(*m12sq);
}
double m23sq_min(double* m12sq, double* pars) {
  return m23sq_min(*m12sq);
}
int main(int argc, char** argv) {
  int palette;
  char* buffer;
  if (argc>1) {
    palette = strtol(argv[1],&buffer,0);
  } else {
    palette = 51;
  }
  lhcb();
  //gStyle->SetPalette(palette);
  //gStyle->SetPalette(1,0);
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  Double_t stops[NRGBs] = { 0.00, 0.10, 0.50, 0.90, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.51, 1.00, 1.00, 1.00 };
  Double_t green[NRGBs] = { 0.00, 0.51, 1.00, 0.51, 0.00 };
  Double_t blue[NRGBs]  = { 1.00, 1.00, 1.00, 0.51, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);
  int year = 2011;
  float toys = 1000.;

  TApplication* theApp = new TApplication("App", &argc, argv); 
  TH2F* da = new TH2F("da","da",50,0,3000000,50,0,3000000);
  TAxis* xax = da->GetXaxis();
  TAxis* yax = da->GetYaxis();
  for (int x = 1 ; x <= da->GetNbinsX() ; ++x) {
    for (int y = 1 ; y <= da->GetNbinsY() ; ++y) {
      float xl = xax->GetBinLowEdge(x);
      float xu = xax->GetBinUpEdge(x);
      float yl = yax->GetBinLowEdge(y);
      float yu = yax->GetBinUpEdge(y);
      for (int i = 0 ; i < toys ; ++i) {
        float thex = xl + gRandom->Rndm() * (xu-xl);
        float they = yl + gRandom->Rndm() * (yu-yl);
        float zval = taumass*taumass+3.*mumass*mumass-thex-they;
        if (zval>4*mumass*mumass && they<m23sq_max(thex) && they>m23sq_min(thex)) {
          da->Fill(thex,they);
        }
      }
    }
  }
  float theeff = 0.0035728470432;
  if (2012==year) {theeff = 0.00417331809;}
  da->Scale(theeff/toys);

  TCanvas* c = new TCanvas();
  da->Draw("colz");
  TF1* upper = new TF1("upper",m23sq_max,m12sq_min()-100.,m12sq_max()+100.,0);
  upper->SetLineColor(kBlack);
  upper->SetNpx(9000);
  TF1* lower = new TF1("lower",m23sq_min,m12sq_min()-100.,m12sq_max()+100.,0);
  lower->SetLineColor(kBlack);
  lower->SetNpx(9000);
  upper->Draw("same");
  lower->Draw("same");
  c->SaveAs("test.png");

  TChain* mc = new TChain("Tau23Mu");
  TString cutstring;
  if (2011==year) {
    mc->Add("/auto/data/pseyfert/thesis/MC12for11_tau23mu.root");
    cutstring = ("truetau==15 && mass_p0p1 > 250 && abs(mass_p1p2 - 1019.5) > 20 && abs(mass_p0p2 - 1019.5) > 20 && mass_p1p2 > 450 && mass_p0p2 > 450 && cleaningcut && TriggerTOSL0Muon && TriggerTOSHlt1TrackMuonDecision && (TriggerTOSHlt2TriMuonTauDecision || TriggerTOSHlt2CharmSemilepD2HMuMuDecision)");
  } else {
    mc->Add("/auto/data/pseyfert/thesis/MC12_tau23mu.root");
    cutstring = ("truetau==15 && mass_p0p1 > 250 && abs(mass_p1p2 - 1019.5) > 20 && abs(mass_p0p2 - 1019.5) > 20 && mass_p1p2 > 450 && mass_p0p2 > 450 && cleaningcut && TriggerTOSL0Muon && TriggerTOSHlt1TrackMuonDecision && TriggerTOSHlt2TriMuonTauDecision");
  }
  TH2F* da2 = new TH2F("da2","da2",50,0,3000000,50,0,3000000);
  mc->Draw("(abs(EventHash%2)==0)*mass_p0p2*mass_p0p2+(abs(EventHash%2)==1)*mass_p1p2*mass_p1p2:mass_p0p1*mass_p0p1>>da2",cutstring.Data());
  da2->Scale(da->GetSum()/da2->GetSum());
  da2->Add(da,-1.);
  da2->Divide(da);
  da2->SetMinimum(-1.);
  da2->SetMaximum(1.);
  da2->Draw("colz");
  upper->Draw("same");
  lower->Draw("same");
  c->SaveAs("test2.png");



  theApp->Run();
  return 0;
}

int main2(int argc, char** argv) {
  char* buffer;
  lhcb();
  gStyle->SetPalette(55);
  //TApplication* theApp = new TApplication("App", &argc, argv); 
  unsigned xbins = ((3==argc)?(strtol(argv[1],&buffer,0)):(2000));
  unsigned ybins = ((3==argc)?(strtol(argv[2],&buffer,0)):(2000));
  TH2F* ll = new TH2F("ll","ll",xbins,0,taumass*taumass,ybins,0,taumass*taumass);
  TH2F* ll2 = new TH2F("ll2","ll2",xbins,0,taumass*taumass,ybins,0,taumass*taumass);
  ll->SetContour(256);
  ll2->SetContour(256);

  fillwith(ll,&flat);

  std::cout << "integral for LHCb MC    = " << ll->GetSum() << std::endl;
  float storeNumber = ll->GetSum();
  Number = ll->GetSum();

  fillwith(ll,&flat);
  std::cout << "integral for LHCb MC    = " << ll->GetSum() << std::endl;
  Number = 1.;
  fillwith(ll,&gammaVLLLL);
  std::cout << "integral for gammaVLLLL = " << ll->GetSum() << std::endl;
  norm = ll->GetSum();
  Number = storeNumber;
  fillwith(ll,&gammaVLLLL);
  
  std::cout << "integral for gammaVLLLL = " << ll->GetSum() << std::endl;
  std::cout << "Number / norm =                                " << Number/norm << std::endl;
  TCanvas* c = new TCanvas();
  gStyle->SetPalette(55);
  ll->GetXaxis()->SetTitle("m_{#mu^{-}#mu^{-}}^{2} [MeV^{2}/c^{4}]");
  ll->GetYaxis()->SetTitle("m_{#mu^{+}#mu^{-}}^{2} [MeV^{2}/c^{4}]");
  ll->Draw("col");
  TFile* plots = new TFile("/tmp/plots.root","recreate");
  plots->WriteTObject(ll);
  c->SaveAs("/tmp/gammallll.eps");



  Number = 1.;
  fillwith(ll,&gammaVLLRR);
  
  std::cout << "integral for gammaVLLRR = " << ll->GetSum() << std::endl;
  normR = ll->GetSum();

  Number=storeNumber;
  fillwith(ll,&gammaVLLRR);
  
  std::cout << "integral for gammaVLLRR = " << ll->GetSum() << std::endl;
  std::cout << "Number / normR =                                " << Number/normR << std::endl;

  ll->GetXaxis()->SetTitle("m_{#mu^{-}#mu^{-}}^{2} [MeV^{2}/c^{4}]");
  ll->GetYaxis()->SetTitle("m_{#mu^{+}#mu^{-}}^{2} [MeV^{2}/c^{4}]");
  ll->Draw("col");
  plots->WriteTObject(ll);
  c->SaveAs("/tmp/gammallrr.eps");
  checkfillwith(ll2,&gammaVLLRR);
  ll2->Draw("col");
  plots->WriteTObject(ll2);
  c->SaveAs("/tmp/checkgammallrr.eps");



  Number = 1.;
  fillwith(ll,&gammaRAD);
  std::cout << "integral for gammaRAD = " << ll->GetSum() << std::endl;
  normRAD = ll->GetSum();
  Number=storeNumber;
  fillwith(ll,&gammaRAD);
  std::cout << "integral for gammaRAD = " << ll->GetSum() << std::endl;
  std::cout << "Number / normRAD =                                " << Number/normRAD << std::endl;

  ll->GetXaxis()->SetTitle("m_{#mu^{-}#mu^{-}}^{2} [MeV^{2}/c^{4}]");
  ll->GetYaxis()->SetTitle("m_{#mu^{+}#mu^{-}}^{2} [MeV^{2}/c^{4}]");
  ll->Draw("col");
  plots->WriteTObject(ll);
  c->SaveAs("/tmp/gammarad.eps");
  checkfillwith(ll2,&gammaRAD);
  ll->GetXaxis()->SetTitle("m_{#mu^{-}#mu^{-}}^{2} [MeV^{2}/c^{4}]");
  ll->GetYaxis()->SetTitle("m_{#mu^{+}#mu^{-}}^{2} [MeV^{2}/c^{4}]");
  ll2->Draw("col");
  plots->WriteTObject(ll2);
  c->SaveAs("/tmp/checkgammarad.eps");
  ll->Add(ll2,-1.);
  ll->GetXaxis()->SetTitle("m_{#mu^{-}#mu^{-}}^{2} [MeV^{2}/c^{4}]");
  ll->GetYaxis()->SetTitle("m_{#mu^{+}#mu^{-}}^{2} [MeV^{2}/c^{4}]");
  ll->Draw("col");
  plots->WriteTObject(ll);
  c->SaveAs("/tmp/diffgammarad.eps");
  std::cout << ll->GetSum() << std::endl;

  Number = 1.;
  fillwith(ll,&interferenceVLLLL_RAD);
  std::cout << "integral for interferenceVLLLL_RAD = " << ll->GetSum() << std::endl;
  normRAD_L = ll->GetSum();
  Number=storeNumber;
  fillwith(ll,&interferenceVLLLL_RAD);
  std::cout << "integral for interferenceVLLLL_RAD = " << ll->GetSum() << std::endl;
  std::cout << "Number / normRAD_L =                                " << Number/normRAD_L << std::endl;

  ll->GetXaxis()->SetTitle("m_{#mu^{-}#mu^{-}}^{2} [MeV^{2}/c^{4}]");
  ll->GetYaxis()->SetTitle("m_{#mu^{+}#mu^{-}}^{2} [MeV^{2}/c^{4}]");
  ll->Draw("col");
  plots->WriteTObject(ll);
  c->SaveAs("/tmp/gammarad-llll.eps");
  checkfillwith(ll2,&interferenceVLLLL_RAD);
  ll2->Draw("col");
  plots->WriteTObject(ll2);
  c->SaveAs("/tmp/checkgammarad-llll.eps");


  Number = 1.;
  fillwith(ll,&interferenceVLLRR_RAD);
  std::cout << "integral for interferenceVLLRR_RAD = " << ll->GetSum() << std::endl;
  normRAD_R = ll->GetSum();
  Number=storeNumber;
  fillwith(ll,&interferenceVLLRR_RAD);
  std::cout << "integral for interferenceVLLRR_RAD = " << ll->GetSum() << std::endl;
  std::cout << "Number / normRAD_R =                                " << Number/normRAD_R << std::endl;

  ll->GetXaxis()->SetTitle("m_{#mu^{-}#mu^{-}}^{2} [MeV^{2}/c^{4}]");
  ll->GetYaxis()->SetTitle("m_{#mu^{+}#mu^{-}}^{2} [MeV^{2}/c^{4}]");
  ll->Draw("col");
  plots->WriteTObject(ll);
  c->SaveAs("/tmp/gammarad-llrr.eps");
  checkfillwith(ll2,&interferenceVLLRR_RAD);
  ll2->Draw("col");
  plots->WriteTObject(ll2);
  c->SaveAs("/tmp/checkgammarad-llrr.eps");


  std::cout << "max = " << ll->GetMaximum() << std::endl;
  std::cout << "min = " << ll->GetMinimum() << std::endl;


  return 0;
}
