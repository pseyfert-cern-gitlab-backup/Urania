/** @function macro BCKplotter.C
 *  plots missid background composition as a function of the PID cut
 *
 *  @author Paul Seyfert
 *  @data   2011-11-03
 *
 * @code
 * gSystem->Load("lib/libBCKplott.so");
 * .x BCKplotter.C+O
 * @endcode
 *
 * @note
 * Due to the implementation
 * (keep it compatible to future changes without need of recreation of source files - you can cut on "undefined" variables,
 *  cuts don't need to be implemented - they remain single-occuring strings)
 * of the preselection handleing this macro is awfully slow and IO intense
 */

#include <TROOT.h>
#include <TH1.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TColor.h>
#include "src/flatclass.h"
#include <iostream>
//#include "./fillmassbins.C"

const TString filename4("~/tmpbuffer/v8/MC10inclC_DOWN_flat.root");
const TString filename2("~/tmpbuffer/v8/MC10inclC_UP_flat.root");
const TString filename3("~/tmpbuffer/v8/MC10inclB_UP_flat.root");
const TString filename1("~/tmpbuffer/v8/MC10inclB_DOWN_flat.root");
const TString sigfile1("~/tmpbuffer/v8/tau23mu_DOWN_flat.root");
const TString sigfile2("~/tmpbuffer/v8/tau23mu_UP_flat.root");
//const TString filename1("~/tmpbuffer/Bbkg.root");
//const TString filename2("~/tmpbuffer/Cbkg.root");
//const TString filename1("~/tmp/flato.root");

//const TString sigfile("~/phd/dropbox/rd/newtuples/mctru_tau23mu_mud_BDTv3e2_flatV3.root");
//const TString preselection("1==1");
//const TString preselection("L0Dec&&Hlt1Dec&&Hlt2Dec&&cleaningcut&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&mass_p0p1>250");


void macro() {
  gStyle->SetOptStat(0);
  gSystem->Load("lib/libBCKplot.so");
  //TChain* signal = new TChain("Tau23Mu");
  TChain* signal = new TChain("Tau23Mu");
  signal->Add(sigfile1);
  signal->Add(sigfile2);
  limit_interface* li = new limit_interface();
  TString preselection = li->getGeoRefString();
  preselection += "&&GeoMVA>0.35";
  preselection += "&&min(p0_singlePID,min(p1_singlePID,p2_singlePID))>-.125";
  //TChain* fChain = new TChain("Tau23Mu");
  TChain* fChain = new TChain("Tau23Mu");
  fChain->Add(filename1);
  fChain->Add(filename2);
  fChain->Add(filename3);
  fChain->Add(filename4);
  flatclass* f = new flatclass(fChain);
  TCanvas* b = new TCanvas("tmp");
  b->cd();
  //int allsignal = signal->Draw("mass",preselection+"&&truetau==15");
  int allsignal = signal->Draw("mass",preselection);
  TH1* one = f->Loop(preselection);
  TCanvas* c = new TCanvas("BCKs");
  c->cd();
  int rightbin = one->Fill("#mu#mu#mu",0);
  int rightbincontent = one->GetBinContent(rightbin);
  int allbincontents = one->GetSumOfWeights();
  float pur =  ((float)rightbincontent)/((float)allbincontents);
  one->SetTitle(Form("preselection  id-purity=%f",pur));
  one->Draw();
  one->GetXaxis()->SetRangeUser(0,23);
  one->GetXaxis()->SetLabelSize(.05);
  TH1* s = (TH1*)one->Clone("s");
  int color = 1;
  TString scanvar = "min(p0_singlePID,min(p1_singlePID,p2_singlePID))";//"GeoMVA";//"
  scanvar = "max(p0_TRACKghost,max(p1_TRACKghost,p2_TRACKghost))";
    float p = 0.5;
  if (true) {
    //for (float k = -1. ; k < 1. ; k+=0.3) 
    p = 0.5;
    //float g = -1.;
    {
      ++color;
      b->cd();
      TString thissel(Form("%s<=%f&&%s",scanvar.Data(),p,preselection.Data()));
      TH1* buffer = f->Loop(thissel,s);
      b->cd();
      int thissignal = signal->Draw("mass",thissel+"&&truetau==15");
      float eff = ((float)thissignal)/((float)allsignal);
      rightbin = buffer->Fill("#mu#mu#mu",0);
      rightbincontent = buffer->GetBinContent(rightbin);
      allbincontents = buffer->GetSumOfWeights();
      pur =  ((float)rightbincontent)/((float)allbincontents);
      c->cd();
      buffer->SetTitle(Form("#varepsilon=%f   id-purity=%f",eff,pur));
      c->cd();
      buffer->SetLineColor(TColor::GetColorDark(kGreen));
      buffer->Draw("same");

    }
//float g = .116;
p = 0.3;
    {
      ++color;
      b->cd();
      TString thissel(Form("%s<=%f&&%s",scanvar.Data(),p,preselection.Data()));
      TH1* buffer = f->Loop(thissel,s);
      b->cd();
      int thissignal = signal->Draw("mass",thissel+"&&truetau==15");
      float eff = ((float)thissignal)/((float)allsignal);
      rightbin = buffer->Fill("#mu#mu#mu",0);
      rightbincontent = buffer->GetBinContent(rightbin);
      allbincontents = buffer->GetSumOfWeights();
      pur =  ((float)rightbincontent)/((float)allbincontents);
      c->cd();
      buffer->SetTitle(Form("#varepsilon=%f   id-purity=%f",eff,pur));
      c->cd();
      buffer->SetLineColor(kRed);
      buffer->Draw("same");

    }
//float g = .44;
}
if (false) {
p = -.025;
    {
      ++color;
      b->cd();
      TString thissel(Form("%s>=%f&&%s",scanvar.Data(),p,preselection.Data()));
      TH1* buffer = f->Loop(thissel,s);
      b->cd();
      int thissignal = signal->Draw("mass",thissel+"&&truetau==15");
      float eff = ((float)thissignal)/((float)allsignal);
      rightbin = buffer->Fill("#mu#mu#mu",0);
      rightbincontent = buffer->GetBinContent(rightbin);
      allbincontents = buffer->GetSumOfWeights();
      pur =  ((float)rightbincontent)/((float)allbincontents);
      c->cd();
      buffer->SetTitle(Form("#varepsilon=%f   id-purity=%f",eff,pur));
      c->cd();
      buffer->SetLineColor(kBlue);
      buffer->Draw("same");

    }
p = .05;
//float g = .616;
    {
      b->cd();
      TString thissel(Form("%s>=%f&&%s",scanvar.Data(),p,preselection.Data()));
      TH1* buffer = f->Loop(thissel,s);
      b->cd();
      int thissignal = signal->Draw("mass",thissel+"&&truetau==15");
      float eff = ((float)thissignal)/((float)allsignal);
      rightbin = buffer->Fill("#mu#mu#mu",0);
      rightbincontent = buffer->GetBinContent(rightbin);
      allbincontents = buffer->GetSumOfWeights();
      pur =  ((float)rightbincontent)/((float)allbincontents);
      c->cd();
      buffer->SetTitle(Form("#varepsilon=%f   id-purity=%f",eff,pur));
      c->cd();
      buffer->SetLineColor(kBlack);
      buffer->Draw("same");

    }
  }
//  c->BuildLegend()->SetFillColor(kWhite);
  c->SetLogy();
  
  c->Print("/tmp/GP-BCK.eps");
}

void BCKplotter() {macro();}
/* else {
    // this just kept in case you want to apply various individual settings
    b->cd();
    TH1* buffer = f->Loop("PIDMVA>0.0",s);
    c->cd();
    buffer->Draw("same");
    rightbin = buffer->Fill("#mu#mu#mu",0);
    rightbincontent = buffer->GetBinContent(rightbin);
    allbincontents = buffer->GetSumOfWeights();
    std::cout << "right frac = " << ((float)rightbincontent)/((float)allbincontents) << std::endl;
    b->cd();
    buffer = f->Loop("PIDMVA>0.1",s);
    c->cd();
    buffer->Draw("same");
    rightbin = buffer->Fill("#mu#mu#mu",0);
    rightbincontent = buffer->GetBinContent(rightbin);
    allbincontents = buffer->GetSumOfWeights();
    std::cout << "right frac = " << ((float)rightbincontent)/((float)allbincontents) << std::endl;
    b->cd();
    buffer = f->Loop("PIDMVA>0.2",s);
    c->cd();
    buffer->Draw("same");
    rightbin = buffer->Fill("#mu#mu#mu",0);
    rightbincontent = buffer->GetBinContent(rightbin);
    allbincontents = buffer->GetSumOfWeights();
    std::cout << "right frac = " << ((float)rightbincontent)/((float)allbincontents) << std::endl;
    b->cd();
    buffer = f->Loop("PIDMVA>0.3",s);
    c->cd();
    buffer->Draw("same");
    rightbin = buffer->Fill("#mu#mu#mu",0);
    rightbincontent = buffer->GetBinContent(rightbin);
    allbincontents = buffer->GetSumOfWeights();
    std::cout << "right frac = " << ((float)rightbincontent)/((float)allbincontents) << std::endl;
    b->cd();
    buffer = f->Loop("PIDMVA>0.4",s);
    c->cd();
    buffer->Draw("same");
    rightbin = buffer->Fill("#mu#mu#mu",0);
    rightbincontent = buffer->GetBinContent(rightbin);
    allbincontents = buffer->GetSumOfWeights();
    std::cout << "right frac = " << ((float)rightbincontent)/((float)allbincontents) << std::endl;
    b->cd();
    buffer = f->Loop("PIDMVA>0.5",s);
    c->cd();
    buffer->Draw("same");
    rightbin = buffer->Fill("#mu#mu#mu",0);
    rightbincontent = buffer->GetBinContent(rightbin);
    allbincontents = buffer->GetSumOfWeights();
    std::cout << "right frac = " << ((float)rightbincontent)/((float)allbincontents) << std::endl;
  }





}*/
