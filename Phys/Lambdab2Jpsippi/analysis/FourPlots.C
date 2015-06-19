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
RooPlot* NiceRooPlot(TH1* h, TH1* hB=0, TH1* hC=0, TH1* hD=0, TString opts="");
TString goodName(TString name);
void png(TString);
//=====================================================================================
// The SevenPlots function
//
//
RooPlot* SevenPlots(TTree* T1, TTree* T2, TTree* T3, TTree* T4, TTree* T5, TTree* T6, TTree* T7, 
                  char* cat1, char* cat2, char* cat3, char* cat4, char* cat5, char* cat6, char* cat7, 
                  TString variable , 
                  TString opts="NML", TString title="", 
                  Double_t limit = 0.,Double_t limit2 = -1.,int nbins=100){
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
  TString name5 = "E_"+name ;
  TString name6 = "F_"+name ;
  TString name7 = "G_"+name ;
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
  TH1D* h5 = new TH1D(name5,name+" 5",nbins,hmn,hmx);
  TH1D* h6 = new TH1D(name6,name+" 6",nbins,hmn,hmx);
  TH1D* h7 = new TH1D(name7,name+" 7",nbins,hmn,hmx);
  h1->Sumw2();h2->Sumw2();h3->Sumw2();h4->Sumw2();;h5->Sumw2();h6->Sumw2();h7->Sumw2();
  
  T1->Draw(pvariable+" >> "+name1,cat1);
  if (T2) T2->Draw(pvariable+" >> "+name2,cat2);
  if (T3) T3->Draw(pvariable+" >> "+name3,cat3);
  if (T4) T4->Draw(pvariable+" >> "+name4,cat4);
  if (T5) T5->Draw(pvariable+" >> "+name5,cat5);
  if (T6) T6->Draw(pvariable+" >> "+name6,cat6);
  if (T7) T7->Draw(pvariable+" >> "+name7,cat7);
  if (!T2) h2 = 0 ;
  if (!T3) h3 = 0 ;
  if (!T4) h4 = 0 ;
  if (!T5) h5 = 0 ;
  if (!T6) h6 = 0 ;
  if (!T7) h7 = 0 ;

  if ( opts.Contains(">") || opts.Contains("<")){
    TString o = opts.Contains(">")?">E":"<E";
    h1 = AccumulatedHisto(h1,o);
    if (h2) h2 = AccumulatedHisto(h2,o);
    if (h3) h3 = AccumulatedHisto(h3,o);
    if (h4) h4 = AccumulatedHisto(h4,o);
    if (h5) h5 = AccumulatedHisto(h5,o);
    if (h6) h6 = AccumulatedHisto(h6,o);
    if (h7) h7 = AccumulatedHisto(h7,o);
  }

  h1->GetXaxis()->SetTitle(pvariable);
  if ( ""==title ) {
    h1->SetTitle(pvariable);
  } else {
    h1->SetTitle(title);
  }
  RooPlot* hrp= 0 ;
  hrp = NiceRooPlot(h1,h2,h3,h4,h5,h6,h7,0,opts);
  return hrp ;
}
//=====================================================================================
// The FourPlots function
//
//
RooPlot* FourPlots(TTree* T1, TTree* T2, TTree* T3, TTree* T4, 
                   char* cat1, char* cat2, char* cat3, char* cat4,
                   TString variable , 
                   TString opts="NML", TString title="", 
                   Double_t limit = 0.,Double_t limit2 = -1.,int nbins=100){
  return SevenPlots(T1,T2,T3,T4,0,0,0,cat1,cat2,cat3,cat4,"","","",variable,opts,title,limit,limit2,nbins);
}
//=====================================================================================
// The FourPlots function for MC
//
//
RooPlot* FourPreselPlots(TTree* T1, TTree* T2, TTree* T3, 
                         TString variable, 
                         TString opts="NML", TString title="", 
                         Double_t limit = 0.,Double_t limit2 = -1.,int nbins=100){
  
  char* dpicut   = "piminus_ProbNNk<piminus_ProbNNpi" ;              // data
  char* dkcut    = "piminus_ProbNNk>=piminus_ProbNNpi";               // pK data
  char* signal   = "piminus_ProbNNk<piminus_ProbNNpi && BKGCAT==0";  // signal
  char* pkcut    = "piminus_ProbNNk>=piminus_ProbNNpi && BKGCAT==1"; // pK (-1)
  
  if ( ""==title) title=goodName("FourPreselPlots of "+variable);

  return FourPlots(T1, T1, T2, T3, 
	                 dpicut,dkcut,signal,pkcut,
                   variable, opts,title, 
                   limit,limit2,nbins) ;
}
//=====================================================================================
// The FourPlots function for MC
//
//
RooPlot* FourMCPlots(TTree* T1, TTree* T2, TTree* T3, 
                   TString variable, 
                   TString opts="NML", TString title="", 
                   Double_t limit = 0.,Double_t limit2 = -1.,int nbins=100){
  
  char* dcut     = "Category==1 && (PsippiMass<5580 || PsippiMass>5650) && ErrorCode==0" ;              // data
  char* teaching = "Category==-1 && ErrorCode==0";               // pK data
  char* signal   = "BKGCAT==0 && Category==1 && ErrorCode==0";  // signal
  char* pkcut    = "BKGCAT==1 && Category==-1 && ErrorCode==0"; // pK (-1)
  
  if ( ""==title) title=goodName("FourPlots of "+variable);

  return FourPlots(T1, T1, T2, T3, 
	           dcut,teaching,signal,pkcut,
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
  
  char* Lb   = "sweightLb*(sweightLb>-4)*(wCategory==1)" ;
  char* Bkg  = "sweightBkg*(sweightLb>-4)*(wCategory==1)";
  char* LbK  = "sweightLb*(sweightLb>-4)*(wCategory==-1)";
  char* BkgK = "sweightBkg*(sweightLb>-4)*(wCategory==-1)";
 
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
  
  char* Ksig   = "sweightLb*(sweightLb>-4)*(wCategory==-1)" ;
  char* Kbkg   = "sweightBkg*(sweightLb>-4)*(wCategory==-1)";
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
  
  TCut KSig(TString("sweightLb*(sweightLb>-4)*(tCategory==-1)*(")+TString(cut.GetTitle())+TString(")")) ;
  TCut Pisig(TString("sweightLb*(sweightLb>-4)*(tCategory==1)*(")+TString(cut.GetTitle())+TString(")")) ;
  TCut Ktrue(cut && NNCut && "Category==-1 && BKGCAT==1 && ErrorCode==0") ;
  TCut Pitrue(cut && NNCut && "Category==1 && BKGCAT==0 && ErrorCode==0");
 
  if ( ""==title) title=goodName("FourPlotsComp of "+variable);

  return FourPlots(T, T, TPi, TK,
                   Pisig.GetTitle(),KSig.GetTitle(),Pitrue.GetTitle(),Ktrue.GetTitle(),
                   variable, opts,title, 
                   limit,limit2,nbins) ;
}

//=====================================================================================
// The FourPlots function for sWeighted data and MC signal
//
//
RooPlot* FourTrainPlots(TTree* T, TTree* TPi, TTree* TK,
                   TString variable, 
                   TString opts="NML", TString title="", 
                   Double_t limit = 0.,Double_t limit2 = -1.,int nbins=50){
  
  TCut KSig("sweightLb*(sweightLb>-4)*(tCategory==-1)") ;
  TCut KBkg("sweightBkg*(sweightLb>-4)*(tCategory==-1)") ;
  TCut Ktrue("Category==-1 && BKGCAT==1 && ErrorCode==0") ;
  TCut Pitrue("Category==1 && BKGCAT==0 && ErrorCode==0");
 
  if ( ""==title) title=goodName("FourTrainPlots of "+variable);

  return FourPlots(T, T, TPi, TK,
                   KSig.GetTitle(),KBkg.GetTitle(),Pitrue.GetTitle(),Ktrue.GetTitle(),
                   variable, opts,title, 
                   limit,limit2,nbins) ;
}

//=====================================================================================
// The FourPlots function for sWeighted data and MC signal
//
//
RooPlot* FiveWeightedTrainPlots(TTree* T, TTree* TPi, TTree* TK,
				TString variable, 
				TString opts="ML", TString title="", 
				Double_t limit = 0.,Double_t limit2 = -1.,int nbins=50){
  
  TCut KSig("sweightLb*(sweightLb>-4)*(tCategory==-1)") ;
  TCut KBkg("sweightBkg*(sweightLb>-4)*(tCategory==-1)") ;
  TCut Pitrue("(Category==1)*(BKGCAT==0)*(ErrorCode==0)");
  TCut Ktrue("(Category==-1)*(BKGCAT==1)*(ErrorCode==0)");
  TCut KWtrue("(Category==-1)*(BKGCAT==1)*(ErrorCode==0)*DalitzWeight*SPDWeight*PTWeight2") ;
 
  if ( ""==title) title=goodName("FiveWeightedTrainPlots of "+variable);

  return SevenPlots(T, T, TPi, TK, TK, 0, 0,
                    KSig.GetTitle(),KBkg.GetTitle(),Pitrue.GetTitle(),Ktrue.GetTitle(),
                    KWtrue.GetTitle(),"","",
                    variable, opts,title, 
                    limit,limit2,nbins) ;
}
//=====================================================================================
// The FourPlots function for sWeighted data and MC signal
//
//
RooPlot* ThreeDalitzWeightPlots(TTree* T, TTree* TK,
				TString variable, 
				TString opts="", TString title="", 
				Double_t limit = 0.,Double_t limit2 = -1.,int nbins=50){
  
  char* sweight = "sweightLb*(sweightLb>-4)*(tCategory==-1)";
  char* trueK = "(BKGCAT==1)*(Category==-1)*(ErrorCode==0)";
  char* trueWK = "DalitzWeight*PTWeight2*SPDWeight*(BKGCAT==1)*(Category==-1)*(ErrorCode==0)";

  if ( ""==title) title=goodName("ThreeDalitzWeightPlots of "+variable);

  return FourPlots(T, TK, TK, 0,
                   sweight, trueK,trueWK,"",
                   variable, opts,title, 
                   limit,limit2,nbins) ;
}

//=====================================================================================
// The FourPlots function for reflections
//
//
RooPlot* FourReflections(TTree* TKpi, TTree* TKK,TTree* TpK, 
                         TString variable, TCut Cut,
                         TString opts="NM", TString title="", 
                         Double_t limit = 4900.,Double_t limit2 = 6100.,int nbins=55){
  //  TCut Cpi("BKGCAT==30" && Cut);
  TCut CKp("BKGCAT==34" && Cut);
  TCut CKpi("BKGCAT==32" && Cut);
  TCut CpiK("BKGCAT==31" && Cut);
  TCut CKK("BKGCAT==33" && Cut);
  
  return FourPlots(TKpi,TKpi,TKK,TpK,CKpi,CpiK,CKK,CKp,variable,opts,title,limit,limit2,nbins) ;
}


//=====================================================================================
// The SevenPlots function for reflections
//
//
RooPlot* SevenSpecies(TTree* T, TString variable, TCut cut, TString opts="NM", TString title="", 
		    Double_t limit = 0,Double_t limit2 = -1.,int nbins=50){
  TCut TCS("sweightLb*(sweightLb>-4)*("+TString(cut.GetTitle())+")");
  cout << TCS.GetTitle() << endl ;
  TCut TCN("sweightNon*(sweightLb>-4)*("+TString(cut.GetTitle())+")");
  TCut TCKpi("sweightKpi*(sweightLb>-4)*("+TString(cut.GetTitle())+")");
  TCut TCpiK("sweightpiK*(sweightLb>-4)*("+TString(cut.GetTitle())+")");
  TCut TCKK("sweightKK*(sweightLb>-4)*("+TString(cut.GetTitle())+")");
  TCut TCKp("sweightKp*(sweightLb>-4)*("+TString(cut.GetTitle())+")");
  TCut TCL("sweightLref*(sweightLb>-4)*("+TString(cut.GetTitle())+")");
  return SevenPlots(T,T,T,T,T,T,T,TCS.GetTitle(),TCN.GetTitle(),TCKpi.GetTitle(),TCpiK.GetTitle(),
		  TCKK.GetTitle(),TCKp.GetTitle(),TCL.GetTitle(),variable,opts,title,limit,limit2,nbins);
}

//=====================================================================================
// The TheePlots function for reflections
//
//
RooPlot* ThreeSpecies(TTree* T, TString variable, TCut cut, TString opts="", TString title="", 
		      Double_t limit = 0,Double_t limit2 = -1.,int nbins=50){
  TCut TCS("sweightLb*(sweightLb>-4)*("+TString(cut.GetTitle())+")");
  cout << TCS.GetTitle() << endl ;
  TCut TCN("sweightNon*(sweightLb>-4)*("+TString(cut.GetTitle())+")");
  TCut TCR("(sweightKpi+sweightpiK+sweightKK+sweightKp+sweightLref)*(sweightLb>-4)*("+TString(cut.GetTitle())+")");
  return FourPlots(T,T,T,0,TCS.GetTitle(),TCN.GetTitle(),TCR.GetTitle(),"",
		   variable,opts,title,limit,limit2,nbins);
}

// ========================================================================================
//
// The three/four profiles function
//
//
RooPlot* FourProfile(TTree* T, TTree* T2, TTree* T3, TTree* T4, 
		     char* cut1, char* cut2,  char* cut3, char* cut4, 
		     char* variable, char* variable2, char* refine="",
		     TString opts="", TString title="", 
		     Double_t limit = 0.,Double_t limit2 = 0.,int nbins=100, 
		     double ymin=0, double ymax=-1){
  if (opts.Contains("D",TString::kIgnoreCase)) 
    std::cout << T << " " << T2 << ", variable " << variable << ", variable2 " << variable 
              << ", opts " << opts << ", title " << title  
              << ", limits " << limit << " " << limit2 << ", nbins " << nbins << endl ;
  
  TString pvariable;
  TString pvariable2;
  if (opts.Contains("L",TString::kIgnoreCase)) {
    pvariable = "log("+TString(variable)+")/log(10.)";
    if (opts.Contains("LL",TString::kIgnoreCase)) {
      pvariable2 = "log("+TString(variable2)+")/log(10.)";
    } else pvariable2 = variable2 ;
    if (limit>0) limit = log(limit)/log(10.);
    if (limit2>0)  limit2 = log(limit2)/log(10.);
  }
  else {
    pvariable = variable ;
    pvariable2 = variable2 ;
  }

  cout << "var :" << pvariable2 << ":" << pvariable ;
  if (opts.Contains("D",TString::kIgnoreCase))
    cout << ", cut1 : " << cut1
         << ", cut2 : " << cut2 
         << ", cut3 : " << cut3
         << ", cut4 : " << cut4 
         << ", refine : " << refine ;
  cout << ", opts : " << opts 
       << ", title : " << title << endl ;
  TCut Tcut1 = mergeCuts(refine,cut1) ;
  TCut Tcut2 = mergeCuts(refine,cut2) ;
  TCut Tcut3 = mergeCuts(refine,cut3) ;
  TCut Tcut4 = mergeCuts(refine,cut4) ;

  // this is to get htemp
  if ( 0==T2 ){
    T->Draw(pvariable2+":"+pvariable, Tcut1 || Tcut2);
  } else {
    T->Draw(pvariable2+":"+pvariable, Tcut1);    
  }
  
  TString name ;
  if ( ""==title) name=goodName(variable);
  else name = goodName(title);

  TString sname = "S_"+name ;
  TString b2name = "B2_"+name ;
  TString b3name = "B3_"+name ;
  TString b4name = "B4_"+name ;
  TString tname = "T_"+name ;
  TH1* htemp = (TH1*)gPad->GetPrimitive("htemp");
  double height = 1.05*htemp->GetYaxis()->GetXmax();
  double bottom = (htemp->GetYaxis()->GetXmin()>0) ? 0.95*htemp->GetYaxis()->GetXmin() : 
                                                     1.05*htemp->GetYaxis()->GetXmin() ;
  Double_t hmn = htemp->GetXaxis()->GetXmin();
  Double_t hmx = htemp->GetXaxis()->GetXmax(); 
  if (limit2>limit){
    hmn = limit ;
    hmx = limit2 ;
  }
  if ( opts.Contains("I",TString::kIgnoreCase) ){ // integer variable
    hmn = int(hmn)-0.5;
    hmx = int(hmx)-0.5;
    if (opts.Contains("I",TString::kIgnoreCase)) hmx = hmx + 1 ; // else buggy
    nbins = int(hmx-hmn);
  }
  TProfile* hs = new TProfile(sname,name,nbins,hmn,hmx,bottom,height) ;
  TProfile* hb2 = 0;
  TProfile* hb3 = 0;
  TProfile* hb4 = 0;
  if (T2) hb2 = new TProfile(b2name,name+" cut2",nbins,hmn,hmx,bottom,height);
  if (T3) hb3 = new TProfile(b3name,name+" cut3",nbins,hmn,hmx,bottom,height);
  if (T4) hb4 = new TProfile(b4name,name+" cut4",nbins,hmn,hmx,bottom,height);
  
  T->Draw(pvariable2+":"+pvariable+" >> "+sname,Tcut1);
  if (T2) T2->Draw(pvariable2+":"+pvariable+" >> "+b2name, Tcut2);
  if (T3) T3->Draw(pvariable2+":"+pvariable+" >> "+b3name, Tcut3);
  if (T4) T4->Draw(pvariable2+":"+pvariable+" >> "+b4name, Tcut4);

  hs->GetXaxis()->SetTitle(pvariable);
  hs->GetYaxis()->SetTitle(pvariable2);
  TString func = "";
  if ( opts.Contains("p1",TString::kIgnoreCase) ) func = "pol1";
  else if ( opts.Contains("p2",TString::kIgnoreCase) ) func = "pol2";
  else if ( opts.Contains("p3",TString::kIgnoreCase) ) func = "pol3";
  else if ( opts.Contains("p4",TString::kIgnoreCase) ) func = "pol4";
  else if ( opts.Contains("p0",TString::kIgnoreCase) ) func = "pol0";
  if (ymin<ymax){
    hs->SetMinimum(ymin);
    hs->SetMaximum(ymax);
  }
  if ( ""!=func) {
    hs->Fit(func);
    if (hb2) hb2->Fit(func);
    if (hb3) hb3->Fit(func);
    if (hb4) hb4->Fit(func);
    NicePlot(hs,hb2,hb3,hb4,0) ;
    return 0;
  }
  return NiceRooPlot(hs,hb2,hb3,hb4,0,0,0,0) ;
}
