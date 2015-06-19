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
// The FourPlots function
//
//
RooPlot* FourPlots(TTree* T1, TTree* T2, TTree* T3, TTree* T4, 
                   char* cat1, char* cat2, char* cat3, char* cat4,
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
  if ( ""==title) name=goodName("FourPlots of "+variable);
  else name = goodName(title);

  TString name1 = "S_"+name ;
  TString name2 = "B_"+name ;
  TString name3 = "C_"+name ;
  TString name4 = "D_"+name ;
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
  TH1D* h4 = new TH1D(name4,name+" 4",nbins,hmn,hmx);
  h1->Sumw2();
  h2->Sumw2();
  h3->Sumw2();
  h4->Sumw2();
  
  T1->Draw(pvariable+" >> "+name1,cat1);
  T2->Draw(pvariable+" >> "+name2,cat2);
  T3->Draw(pvariable+" >> "+name3,cat3);
  T4->Draw(pvariable+" >> "+name4,cat4);
  h1->GetXaxis()->SetTitle(pvariable);
  if ( ""==title ) {
    h1->SetTitle(pvariable);
  } else {
    h1->SetTitle(title);
  }
  RooPlot* hrp= 0 ;
  hrp = NiceRooPlot(h1,h2,h3,h4,opts);
  return hrp ;
}
//=====================================================================================
// The FourPlots function for MC
//
//
RooPlot* FourMCPlots(TTree* T1, TTree* T2, TTree* T3, TTree* TT, 
                   TString variable, 
                   TString opts="NML", TString title="", 
                   Double_t limit = 0.,Double_t limit2 = -1.,int nbins=100){
  
  char* signal   = "BKGCAT==0 && Category==1";  // signal
  char* teaching = "Teaching && Category==1";   // incpsi
  char* pkcut    = "BKGCAT==1 && Category==-1";// pK (-1)
  char* dcut     = "Category==1" ;              // data
  
  if ( ""==title) title=goodName("FourPlots of "+variable);

  return FourPlots(T1, T2, T3, TT, 
	           signal,teaching,pkcut,dcut,
                   variable, opts,title, 
                   limit,limit2,nbins) ;
}
//=====================================================================================
// The FourPlots function for sWeighted data
//
//
RooPlot* FourPlots(TTree* T,
                   TString variable, 
                   TString opts="NML", TString title="", 
                   Double_t limit = 0.,Double_t limit2 = -1.,int nbins=50){
  
  char* Lb   = "sweightLb*(sweightLb>-5)*(wCategory==1)" ;
  char* Bkg  = "sweightBkg*(sweightLb>-5)*(wCategory==1)";
  char* LbK  = "sweightLb*(sweightLb>-5)*(wCategory==-1)";
  char* BkgK = "sweightBkg*(sweightLb>-5)*(wCategory==-1)";
 
  if ( ""==title) title=goodName("sFourPlots of "+variable);

  return FourPlots(T, T, T, T,
                   Lb,LbK,BkgK,Bkg, 
                   variable, opts,title, 
                   limit,limit2,nbins) ;
}
//=====================================================================================
// The FourPlots function for sWeighted data and MC
//
//
RooPlot* FourKPlots(TTree* T, TTree* TK, TTree* TI,
                    TString variable, 
                    TString opts="NML", TString title="", 
                    Double_t limit = 0.,Double_t limit2 = -1.,int nbins=25){
  
  char* Ksig   = "sweightLb*(sweightLb>-5)*(wCategory==-1)" ;
  char* Kbkg   = "sweightBkg*(sweightLb>-5)*(wCategory==-1)";
  char* Ktrue  = "Category==-1 && netOutput>0 && BKGCAT==1";
  char* Kinc   = "Category==-1 && netOutput>0 && BKGCAT!=1";
 
  if ( ""==title) title=goodName("FourPlotsComp of "+variable);

  return FourPlots(T, T, TK, TI,
                   Ksig,Kbkg,Ktrue,Kinc,
                   variable, opts,title, 
                   limit,limit2,nbins) ;
}

//=====================================================================================
// The FourPlots function for sWeighted data and MC signal
//
//
RooPlot* FourPlots(TTree* T, TTree* TPi, TTree* TK,
                   TString variable, TCut NNCut, TCut cut="1",
                   TString opts="NML", TString title="", 
                   Double_t limit = 0.,Double_t limit2 = -1.,int nbins=50){
  
  TCut KSig(TString("sweightLb*(sweightLb>-5)*(wCategory==-1)*(")+TString(cut.GetTitle())+TString(")")) ;
  TCut Pisig(TString("sweightLb*(sweightLb>-5)*(wCategory==1)*(")+TString(cut.GetTitle())+TString(")")) ;
  TCut Ktrue(cut && NNCut && "Category==-1 && BKGCAT==1") ;
  TCut Pitrue(cut && NNCut && "Category==1 && BKGCAT==0");
 
  if ( ""==title) title=goodName("FourPlotsComp of "+variable);

  return FourPlots(T, T, TPi, TK,
                   Pisig.GetTitle(),KSig.GetTitle(),Pitrue.GetTitle(),Ktrue.GetTitle(),
                   variable, opts,title, 
                   limit,limit2,nbins) ;
}







