#include <iostream>
#include <cmath>
#include "TH1D.h"
#include "TTree.h"
#include "TCut.h"
#include "TPad.h"
#include "TString.h"
#include "TLine.h"
#include "RooPlot.h"
using namespace std;
TLine* plot_line(Double_t x1, Double_t y1, Double_t x2, Double_t y2){  
  TLine* line = new TLine(x1,y1,x2,y2);
  line->SetLineWidth(6);
  line->SetLineColor(40);
  line->Draw(); 
  cout << "Drawn " << x1 << "," << y1 << " to " << x2 << "," << y2 << endl ;
  //  delete line ;
  return line;
} 
TLine* overlay_line(Double_t x, TH1* h){  
  double y1 = h->GetYaxis()->GetXmin();
  double y2 = h->GetYaxis()->GetXmax();
  return plot_line(x,y1,x,y2);
} 
TLine* overlay_line(Double_t x, RooPlot* h){  
  double y1 = h->GetMinimum();
  double y2 = h->GetMaximum();
  return plot_line(x,y1,x,y2);
} 
RooPlot* NiceRooPlot(TH1* h, TH1* hB=0, TH1* hC=0, TH1* hD=0, TString opts="");
TString goodName(TString name);
void png(TString);
//=====================================================================================
// The ThreePlots function
//
//
RooPlot* ThreePlots(TTree* T1, TTree* T2, TTree* T3, 
                    char* cat1, char* cat2, char* cat3,
                    TString variable = "eventNumber", 
                    TString opts="NML", TString title="", 
                    Double_t limit = 0.,Double_t limit2 = -1.,int nbins=100){
 // options :
  // N : normalise
  // I : integer variable (bins of size 1)
  // g : gaussian
  // gg : double gaussian
  // p : polynomial background
  // D : debug
  // Cut : Show cut(s)
  // L : Log_10
  // R : Define Range (incompatible with C)
  // M : set minimum to 0.5
  // B : it's a B
  TString pvariable;
  if (opts.Contains("L",TString::kIgnoreCase)) {
    pvariable = "log("+variable+")/log(10.)";
    if (limit>0) limit = log(limit)/log(10.);
    if (limit2>0)  limit2 = log(limit2)/log(10.);
  }
  else pvariable = variable ;
  cout << "var :" << pvariable ;
  cout << ", opts : " << opts 
       << ", title : " << title ;
  cout << endl ;
  double nev = T1->Draw(pvariable, "1");

  TString name ;
  if ( ""==title) name=goodName("ThreePlots of "+variable);
  else name = goodName(title);

  TString name1 = "S_"+name ;
  TString name2 = "B_"+name ;
  TString name3 = "C_"+name ;
  TString tname = "T_"+name ;
  TH1* htemp = (TH1*)gPad->GetPrimitive("htemp");
  if (!htemp) return 0 ;
  double height = 1.05*htemp->GetMaximum();
  Double_t hmn = htemp->GetXaxis()->GetXmin();
  Double_t hmx = htemp->GetXaxis()->GetXmax();  
  if ( !opts.Contains("Cut",TString::kIgnoreCase) && limit2>limit){ // defined range
    hmn = limit ;
    hmx = limit2 ;
  } 
  if ( opts.Contains("I",TString::kIgnoreCase) ){ // integer variable
    hmn = int(hmn)-0.5;
    hmx = int(hmx)-0.5;
    if (opts.Contains("I",TString::kIgnoreCase)) hmx = hmx + 1 ; // else buggy
    nbins = int(hmx-hmn);
  }
  TH1D* h1 = new TH1D(name1,name,nbins,hmn,hmx) ;
  TH1D* h2 = new TH1D(name2,name+" 2",nbins,hmn,hmx);
  TH1D* h3 = new TH1D(name3,name+" 3",nbins,hmn,hmx);
  h1->Sumw2();
  h2->Sumw2();
  h3->Sumw2();
  
  T1->Draw(pvariable+" >> "+name1,cat1);
  T2->Draw(pvariable+" >> "+name2,cat2);
  T3->Draw(pvariable+" >> "+name3,cat3);
  h1->GetXaxis()->SetTitle(pvariable);
  if ( ""==title ) {
    h1->SetTitle(pvariable);
  } else {
    h1->SetTitle(title);
  }
  RooPlot* hrp= 0 ;
  hrp = NiceRooPlot(h1,h2,h3,0,opts);
  return hrp ;
}
//=====================================================================================
// The ThreePlots function for sWeighted data
//
//
RooPlot* ThreeSPlots(TTree* T25,TTree* THL,TTree* T12,
                    TString variable, 
                    TString opts="M", TString title="", 
                    Double_t limit = 0.,Double_t limit2 = -1.,int nbins=25){
  
  char* w25  = "390.889*sweight[0]*(sweight[0]>-5)" ;
  char* wHL  = "180.088*sweight[0]*(sweight[0]>-5)" ;
  char* w12  = "0.502977*sweight[0]*(sweight[0]>-5)" ;
 
  if ( ""==title) title=goodName("sThreePlots of "+variable);

  return ThreePlots(T25, THL, T12, 
                    w25, wHL, w12,
                    variable, opts,title, 
                    limit,limit2,nbins) ;
}
//=====================================================================================
// The ThreePlots function for sWeighted background
//
//
RooPlot* ThreeBPlots(TTree* T25,TTree* THL,TTree* T12,
                    TString variable, 
                    TString opts="M", TString title="", 
                    Double_t limit = 0.,Double_t limit2 = -1.,int nbins=25){
  
  char* w25  = "390.889*sweightNonPeaking[0]*(sweight[0]>-5)" ;
  char* wHL  = "180.088*sweightNonPeaking[0]*(sweight[0]>-5)" ;
  char* w12  = "0.502977*sweightNonPeaking[0]*(sweight[0]>-5)" ;
 
  if ( ""==title) title=goodName("bThreePlots of "+variable);

  return ThreePlots(T25, THL, T12, 
                    w25, wHL, w12,
                    variable, opts,title, 
                    limit,limit2,nbins) ;
}
//=====================================================================================
// The ThreePlots function for sWeighted data
//
//
RooPlot* ThreeLPlots(TTree* T25,TTree* THL,TTree* T12,
                    TString variable, 
                    TString opts="M", TString title="", 
                    Double_t limit = 0.,Double_t limit2 = -1.,int nbins=50){
  
  char* w25  = "390.889" ;
  char* wHL  = "180.088" ;
  char* w12  = "0.502977" ;
 
  if ( ""==title) title=goodName("LThreePlots of "+variable);

  return ThreePlots(T25, THL, T12, 
                    w25, wHL, w12,
                    variable, opts,title, 
                    limit,limit2,nbins) ;
}
//=====================================================================================
// The ThreePlots function for sWeighted data
//
//
void AllThreePlots(TTree* T25,TTree* THL,TTree* T12,
                TString variable, 
                TString opts="M", 
                Double_t limit = 0.,Double_t limit2 = -1.,int nbins=50){
  
  RooPlot* r = ThreeLPlots(T25,THL,T12,variable,opts,"",limit,limit2,nbins);
  TString t = r->GetXaxis()->GetTitle();
  RooPlot* r = ThreeBPlots(T25,THL,T12,variable,opts,"remove",limit,limit2,nbins);
  r->SetXTitle(TString("Bkg - "+t));
  png(TString("bThreePlots of "+variable));
  RooPlot* r = ThreeSPlots(T25,THL,T12,variable,opts,"remove",limit,limit2,nbins);
  r->SetXTitle(TString("Signal - "+t));
  png(TString("sThreePlots of "+variable));
}


