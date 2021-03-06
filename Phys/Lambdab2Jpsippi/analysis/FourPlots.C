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
  
  char* Lb   = "sweightLb*(sweightLb>-3)*(wCategory==1)" ;
  char* Bkg  = "sweightBkg*(sweightLb>-3)*(wCategory==1)";
  char* LbK  = "sweightLb*(sweightLb>-3)*(wCategory==-1)";
  char* BkgK = "sweightBkg*(sweightLb>-3)*(wCategory==-1)";
 
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
  
  char* Ksig   = "sweightLb*(sweightLb>-3)*(wCategory==-1)" ;
  char* Kbkg   = "sweightBkg*(sweightLb>-3)*(wCategory==-1)";
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
  
  TCut KSig(TString("sweightLb*(sweightLb>-3)*(tCategory==-1)*(")+TString(cut.GetTitle())+TString(")")) ;
  TCut Pisig(TString("sweightLb*(sweightLb>-3)*(tCategory==1)*(")+TString(cut.GetTitle())+TString(")")) ;
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
  
  TCut KSig("sweightLb*(sweightLb>-3)*(tCategory==-1)") ;
  TCut KBkg("sweightBkg*(sweightLb>-3)*(tCategory==-1)") ;
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
  
  TCut KSig("sweightLb*(sweightLb>-3)*(tCategory==-1)") ;
  TCut KBkg("sweightBkg*(sweightLb>-3)*(tCategory==-1)") ;
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
// Polarity
//
//
RooPlot* OldPolarityPlots(TTree* T, TTree* TMC,
                       TString variable, TString category,
                       TString opts="NML", TString title="", 
                       Double_t limit = 0.,Double_t limit2 = -1.,int nbins=50){
  
  TString mc = "(Category==1)*(BKGCAT==0)" ;
  TString md = "(Category==1)" ;
  if ("K"==category){
    mc = "(Category==-1)*(BKGCAT==1)";
    md = "(Category==-1)";
  }
  TCut SigU("sweightLb*(sweightLb>-3)*(Polarity==1)*("+md+")") ;
  TCut SigD("sweightLb*(sweightLb>-3)*(Polarity==-1)*("+md+")") ;
  TCut WtrueU("(ErrorCode==0)*DalitzWeight*SPDWeight*PTWeight2*(Polarity==1)*("+mc+")") ;
  TCut WtrueD("(ErrorCode==0)*DalitzWeight*SPDWeight*PTWeight2*(Polarity==-1)*("+mc+")") ;
 
  if ( ""==title) title=goodName("PolarityPlots of "+variable);

  return SevenPlots(T, T, TMC, TMC,0,0,0,
                    SigD.GetTitle(),SigU.GetTitle(),WtrueD.GetTitle(),WtrueU.GetTitle(),
                    "","","",
                    variable, opts,title, 
                    limit,limit2,nbins) ;
}
//=====================================================================================
// Polarity
//
//
RooPlot* PolarityPlots(TTree* T, 
                       TString variable, TString category,
                       TString opts="M", TString title="", 
                       Double_t limit = 0.,Double_t limit2 = -1.,int nbins=50){
  
  TString UW = "(Polarity==1)" ;  // extracted from LbK yield before weighting
  TString DW = "(0.893222264293828117)*(Polarity==-1)" ;  // 0.4718/0.5282
  
  TString md = "Category==1" ;
  if ("K"==category){
    md = "(Category==-1)*(eventNumber%2==0)";
  }
  TCut SigUB(UW+"*sweightLb*(sweightLb>-3)*(Baryon==1)*("+md+")") ;
  TCut SigDB(DW+"*sweightLb*(sweightLb>-3)*(Baryon==1)*("+md+")") ;
  TCut SigUAB(UW+"*sweightLb*(sweightLb>-3)*(Baryon==-1)*("+md+")") ;
  TCut SigDAB(DW+"*sweightLb*(sweightLb>-3)*(Baryon==-1)*("+md+")") ;
 
  if ( ""==title) title=goodName("PolarityPlots of "+variable);

  RooPlot* s = SevenPlots(T, T, T, T,0,0,0,
			  SigUB.GetTitle(),SigDB.GetTitle(),SigUAB.GetTitle(),SigDAB.GetTitle(),
			  "","","",
			  variable, opts,title, 
			  limit,limit2,nbins) ;
  s->SetMinimum(0.);
  return s;
}
//=====================================================================================
// The FourPlots function for sWeighted data and MC signal
//
//
RooPlot* FourUnblindedPlots(TTree* T, TTree* TPi, TTree* TK,
			    TString variable, TCut NNCut,
			    TString opts="ML", TString title="", 
			    Double_t limit = 0.,Double_t limit2 = -1.,int nbins=50){
  
  TCut PiSig("sweightLb*(sweightLb>-3)*(Category==1)*("+TString(NNCut.GetTitle())+")") ;
  TCut KSig("sweightLb*(sweightLb>-3)*(Category==-1)*("+TString(NNCut.GetTitle())+")") ;
  TCut Pitrue("(Category==1)*(BKGCAT==0)*(ErrorCode==0)*DalitzWeight2*SPDWeight*PTWeight*("+
              TString(NNCut.GetTitle())+")");
  TCut Ktrue("(Category==-1)*(BKGCAT==1)*(ErrorCode==0)*DalitzWeight*SPDWeight*PTWeight2*NNEffWeight*("+
             TString(NNCut.GetTitle())+")");
 
  if ( ""==title) title=goodName("FourUnblindedPlots of "+variable);

  return SevenPlots(T, T, TPi, TK, 0, 0, 0,
                    PiSig.GetTitle(),KSig.GetTitle(),Pitrue.GetTitle(),Ktrue.GetTitle(),0,0,0,
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
  
  char* sweight = "sweightLb*(sweightLb>-3)*(tCategory==-1)";
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
  TCut TCS("sweightLb*(sweightLb>-3)*("+TString(cut.GetTitle())+")");
  cout << TCS.GetTitle() << endl ;
  TCut TCN("sweightNon*(sweightLb>-3)*("+TString(cut.GetTitle())+")");
  TCut TCKpi("sweightKpi*(sweightLb>-3)*("+TString(cut.GetTitle())+")");
  TCut TCpiK("sweightpiK*(sweightLb>-3)*("+TString(cut.GetTitle())+")");
  TCut TCKK("sweightKK*(sweightLb>-3)*("+TString(cut.GetTitle())+")");
  TCut TCKp("sweightKp*(sweightLb>-3)*("+TString(cut.GetTitle())+")");
  TCut TCL("sweightLref*(sweightLb>-3)*("+TString(cut.GetTitle())+")");
  return SevenPlots(T,T,T,T,T,T,T,TCS.GetTitle(),TCN.GetTitle(),TCKpi.GetTitle(),TCpiK.GetTitle(),
		  TCKK.GetTitle(),TCKp.GetTitle(),TCL.GetTitle(),variable,opts,title,limit,limit2,nbins);
}

//=====================================================================================
// The TheePlots function for reflections
//
//
RooPlot* ThreeSpecies(TTree* T, TString variable, TCut cut, TString opts="", TString title="", 
		      Double_t limit = 0,Double_t limit2 = -1.,int nbins=50){
  TCut TCS("sweightLb*(sweightLb>-3)*("+TString(cut.GetTitle())+")");
  cout << TCS.GetTitle() << endl ;
  TCut TCN("sweightNon*(sweightLb>-3)*("+TString(cut.GetTitle())+")");
  TCut TCR("(sweightKpi+sweightpiK+sweightKK+sweightKp+sweightLref)*(sweightLb>-3)*("+TString(cut.GetTitle())+")");
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
//===================================================================
TH2D* Miranda(TH2D* B, TH2D* A, TString how = ""){
  int nx = B->GetNbinsX();
  int ny = B->GetNbinsY();
  TH2D* M = new TH2D("Miranda "+TString(B->GetName()),"Miranda",
		     nx,B->GetXaxis()->GetXmin(),B->GetXaxis()->GetXmax(),
		     ny,B->GetYaxis()->GetXmin(),B->GetYaxis()->GetXmax());
  for ( int ix = 1 ; ix<=nx ; ix++){
    for ( int iy = 1 ; iy<=ny ; iy++){
      double nb = B->GetBinContent(ix,iy);
      double na = A->GetBinContent(ix,iy);
      double eb = B->GetBinError(ix,iy);
      double ea = A->GetBinError(ix,iy);
      double as = (nb-na)/sqrt(ea*ea+eb*eb);
      if (na+nb>0){
	cout << nb << "+/-" << eb << " " << na << "+/-" << ea << " = " << as << endl ;
	if (""==how) M->SetBinContent(ix,iy,as);
	else  M->SetBinContent(ix,iy,nb-na);
      } else {
	if (""==how) M->SetBinContent(ix,iy,-999.);
	else M->SetBinContent(ix,iy,0.);
      }
    }   
  }
  if (""==how) M->SetMinimum(-5.0);
  if (""==how) M->SetMaximum(5.0);
  M->SetStats(0);
  M->Draw("COLtext");
  M->GetXaxis()->SetTitle(B->GetXaxis()->GetTitle());
  M->GetYaxis()->SetTitle(B->GetYaxis()->GetTitle());
  return M;
}
//===================================================================
TObject* Miranda(TH2D* M, TString opt = "NLL"){
  int nx = M->GetNbinsX();
  int ny = M->GetNbinsY();
  TH1D* m = new TH1D("Miranda","Miranda",20,-5.,5.);
  for ( int ix = 1 ; ix<=nx ; ix++){
    for ( int iy = 1 ; iy<=ny ; iy++){
      double a = M->GetBinContent(ix,iy);
      if (a>-100) {
	//	cout << a << endl ;
	m->Fill(a);
      }
    }   
  }
  if ("chi2"==opt) {
    TF1* f1 = new TF1("gaus1","[0]*exp(-0.5*(x/[1])^2)"); 
    f1->SetParameter(1,1.);
    m->Fit(f1);
    TF1* f2 = new TF1("gaus2","[0]*exp(-0.5*(x)^2)"); 
    m->Fit(f2);
    m->Fit("gaus");
    TF1 *g1 = m->GetFunction("gaus");
    cout << g1->GetParameter(1) << "\\pm" << g1->GetParError(1) << " & " 
	 << g1->GetParameter(2) << "\\pm" << g1->GetParError(2) << " & " 
	 << g1->GetChisquare() << "/" << g1->GetNDF() << "\\\\" << endl ;
    cout  << "0 & " 
	 << f1->GetParameter(1) << "\\pm" << f1->GetParError(1) << " & " 
	 << f1->GetChisquare() << "/" << f1->GetNDF() << "\\\\" << endl ;
    cout << "0 & 1 & " 
	 << f2->GetChisquare() << "/" << f2->GetNDF() << "\\\\" << endl ;
    return m;
  } else {
    RooRealVar roovar(m->GetName(),"Miranda",-5,5) ;
    RooDataHist Hist(m->GetName()+TString("H"),m->GetTitle(),roovar,m);
    RooRealVar mean1("mean1","mean1",0,-1.,1.);
    RooRealVar mean2("mean2","mean2",0);
    RooRealVar sigma1("sigma","core sigma",1,0.1,2);
    RooRealVar sigma2("sigma","core sigma",1,0.1,2);
    RooRealVar sigma3("sigma2","core sigma",1);
    RooGaussian G1("G1","Gaussian",roovar,mean1,sigma1);
    RooGaussian G2("G2","Gaussian",roovar,mean2,sigma2);
    RooGaussian G3("G3","Gaussian",roovar,mean2,sigma3);
    RooChi2Var chi21("chi21","chi2",G1,Hist,DataError(RooAbsData::SumW2)) ;
    RooChi2Var chi22("chi22","chi2",G2,Hist,DataError(RooAbsData::SumW2)) ;
    RooChi2Var chi23("chi23","chi2",G3,Hist,DataError(RooAbsData::SumW2)) ;
    RooFitResult* rf1 = 0 ;
    RooFitResult* rf2 = 0 ;
    RooFitResult* rf3 = 0 ;
    if ("chi2-roofit"==opt){  // does not work
      // Start Minuit session on Chi2
      RooMinuit m21(chi21) ;
      m21.migrad() ;
      m21.hesse() ;
      rf1 = m21.save() ;
      RooMinuit m22(chi22) ;
      m22.migrad() ;
      m22.hesse() ;
      rf2 = m22.save() ;
      RooMinuit m23(chi23) ;
      m23.migrad() ;
      m23.hesse() ;
      rf3 = m23.save() ;
    } else {
      rf1 = G1.fitTo(Hist,Save());
      rf2 = G2.fitTo(Hist,Save());
      rf3 = G3.fitTo(Hist,Save());
      RooPlot* xframe = roovar.frame();
      Hist.plotOn(xframe);
      G1.plotOn(xframe,RooFit::LineColor(kRed));
      if ("PAPER"!=opt){
        G2.plotOn(xframe,RooFit::LineColor(kBlue),RooFit::LineStyle(kDashed));
        G3.plotOn(xframe,RooFit::LineColor(kGreen),RooFit::LineStyle(kDotted));
      }
      xframe->Draw();
      rf1->Print("v");
      rf2->Print("v");
      rf3->Print("v");
      cout << mean1.getVal() << "\\pm" << mean1.getError() << " & " 
	   << sigma1.getVal() << "\\pm" << sigma1.getError() << " & " 
	   << rf1->minNll() << "\\\\" << endl ;
      cout << 0 << " & " 
	   << sigma2.getVal() << "\\pm" << sigma2.getError() << " & " 
	   << rf2->minNll() << "\\\\" << endl ;
      cout << 0 << " & " << 1 << " & " << rf3->minNll() << "\\\\" << endl ;
      if ("chi2"==opt)  m->Fit("gaus");
      SetTitle("A/#sigma_{A}","Bins",xframe);
      return xframe;
    }
  }
}
