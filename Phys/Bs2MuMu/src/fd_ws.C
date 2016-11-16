// ============================================================
// Francesco Dettori 
// francesco.dettori@cern.ch
// Adapted from Alessio Sarti's code. 
// ============================================================

#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2.h"
#include "TFile.h"
#include "TLatex.h"
#include "TPaveText.h"
#include "TTree.h"
#include "root_libs.h" 

#include "RooGlobalFunc.h"
#include "RooProfileLL.h"
#include "RooAbsPdf.h"
#include "RooStats/HypoTestResult.h"

#include "RooRealVar.h"
#include "RooPlot.h"
#include "RooDataSet.h"
#include "RooTreeDataStore.h"
#include "RooFitResult.h"
#include "RooCategory.h"
#include "RooSimultaneous.h" 
#include "RooWorkspace.h"
#include "RooPlot.h"
#include "RooBinning.h"
#include "RooRandom.h"
#include "RooGenericPdf.h"
#include "RooThresholdCategory.h"
#include "RooGlobalFunc.h"
#include "RooKeysPdf.h"
#include "RooRealVar.h"
#include "RooBDecay.h"
#include "RooAddPdf.h"
#include "RooCategory.h"
#include "RooMinuit.h"
#include "RooArgSet.h"
#include "RooArgList.h"
#include "RooFormulaVar.h"
#include "RooEffProd.h"
#include "RooRealConstant.h"
#include "RooGaussModel.h"
#include "RooGaussian.h"
#include "RooProdPdf.h"
#include "RooAddModel.h"
#include "RooDataHist.h"
#include "RooExponential.h"
#include "RooGenericPdf.h"
#include "RooCBShape.h"
#include "RooNumConvPdf.h"
#include "RooFFTConvPdf.h"
#include "RooExtendPdf.h"
#include "RooNLLVar.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "RooMCStudy.h"
#include "RooCmdArg.h"
#include "zstyle.h"
#include "RooStats/ModelConfig.h"
#include <string>

using namespace RooFit;
using namespace std;

vector<RooRealVar*> my_Nbkg, my_BDTfr;

RooAbsPdf* CreatePdfForABin(int bin, RooFormulaVar *fr, RooRealVar* m, RooAbsReal* nbd, 
                            RooAbsReal* nbs, RooFormulaVar* nmis, RooRealVar *mbd, RooRealVar *mbs, 
                            RooRealVar *wmbd, RooRealVar *wmbs, RooRealVar *tau, RooAbsPdf *hmis);

void ExpPlot(RooRealVar *abdt, RooDataSet *adt, RooAbsPdf *apdf, bool syst, int sys_id, string anm, 
             string flg, bool log, string dname, string pname, int bin);

RooArgList terms;

int main(int argc, char **argv) {
  zstyle();
  bool writedata = true;
  
  char hn[200];  
  char pdfnm[200];
  string flag = "outp";
  string infi = "fit1d/fake_unblind_bsmumu_1fb.txt";
  //  string infi = "fit1d/data_1fb_unblind.txt";
  
  string fconf = "myConf.txt";
  bool addPrior(kFALSE);  
  bool addGlobObs(kFALSE);  
  bool measureRatio(kFALSE);
  bool doData(kFALSE);  
  int  pr_bdmax, pr_bsmax;
  bool doModelConfig(kFALSE);
  bool bsOnly(kFALSE);
  for (int i = 0; i < argc; i++){
    if(strcmp(argv[i],"-in") == 0)    { infi = string(argv[++i]);  }    // Decide among different MC input
    if(strcmp(argv[i],"-flag") == 0)  { flag = string(argv[++i]);  }    // Flagging output eps files
    if(strcmp(argv[i],"-prior") == 0) { addPrior = kTRUE;       }        // add constraints for systematics
    if(strcmp(argv[i],"-globobs") == 0) { addGlobObs = kTRUE;       }   // add global observables ( auxiliary measurements) 
    if(strcmp(argv[i],"-ratio") == 0) { measureRatio = kTRUE;       }   // Measure R 
    if(strcmp(argv[i],"-data") == 0)  { doData = kTRUE;            }    // Number of toys
    if(strcmp(argv[i],"-maxbd") == 0)  { pr_bdmax = atoi(argv[++i]);  } // Number of toys
    if(strcmp(argv[i],"-maxbs") == 0)  { pr_bsmax = atoi(argv[++i]);}   // Number of toys
    if(strcmp(argv[i],"-mc") == 0)  { doModelConfig = kTRUE;            }                
    if(strcmp(argv[i],"-bs") == 0)  { bsOnly = kTRUE;            }                
  }

  my_Nbkg.clear();
  my_BDTfr.clear();


  /*********************************************/
  //    BDT distributions from FILE
  /*********************************************/
 
  TFile *f_misid = new TFile("fit1d/RookeysMisIDLarge_shift.root", "READ");
  RooWorkspace * ws_misid = (RooWorkspace*)f_misid->Get("w;1");
  //TFile *f_misid = new TFile("fit1d/rookeys_misID_name.root", "READ");
  // RooWorkspace * ws_misid = (RooWorkspace*)f_misid->Get("new;1");
  

  RooKeysPdf * key_misid = (RooKeysPdf*)ws_misid->pdf("misIDKernelPDF");
  
  (*key_misid->getVariables())["ShiftedBmass"].SetName("m_{#mu#mu}");
  
  
  /*
    TisTOT      =    16734 +/-  1312     (syst incluse)
    Tis2        =     1877 +/-  242
    Tis3        =     1486 +/-  158
    Tis4        =     1447 +/-  89
    Tis5        =     1729 +/-  100
    Tis6        =     1846 +/-  69
    Tis7        =     2133 +/-  107
    Tis8        =     2245 +/-  327
  */


  // Possibility: define Tis1 as a rooformula from the other TIS
  const Int_t nBinning = 8; 
  // Last bin is the total 
  Double_t tis_mean[nBinning+1]  = { 4116, 1877, 1486, 1447, 1729, 1846, 2133, 2245, 16734};
  Double_t tis_sigma[nBinning+1] = { 1312,  242,  258,   89,  100,   69,  107,  327,  1312};
  //         TisTOT      =    16734 +/-  1312     (syst incluse)
  //         Tis2        =     1877 +/-  242
  //         Tis3        =     1486 +/-  158
  //         Tis4        =     1447 +/-  89
  //         Tis5        =     1729 +/-  100
  //         Tis6        =     1846 +/-  69
  //         Tis7        =     2133 +/-  107
  //         Tis8        =     2245 +/-  327

  // 	Tis1(computed) = 4116 +- 1312 (assuming same error as total) 


  
  RooRealVar *Tis1 = new RooRealVar("Tis1","BDT calib events 1st bin",4116,100,10000);
  Tis1->setConstant(kTRUE);
  RooRealVar *Tis2 = new RooRealVar("Tis2","BDT calib events 2nd bin",1877,100,10000);
  Tis2->setConstant(kTRUE);
  RooRealVar *Tis3 = new RooRealVar("Tis3","BDT calib events 3rd bin",1486,100,10000);
  Tis3->setConstant(kTRUE);
  RooRealVar *Tis4 = new RooRealVar("Tis4","BDT calib events 4th bin",1447,100,10000);
  Tis4->setConstant(kTRUE);
  RooRealVar *Tis5 = new RooRealVar("Tis5","BDT calib events 5th bin",1729,100,10000);
  Tis5->setConstant(kTRUE);
  RooRealVar *Tis6 = new RooRealVar("Tis6","BDT calib events 6th bin",1846,100,10000);
  Tis6->setConstant(kTRUE);
  RooRealVar *Tis7 = new RooRealVar("Tis7","BDT calib events 7th bin",2133,100,10000);
  Tis7->setConstant(kTRUE);
  RooRealVar *Tis8 = new RooRealVar("Tis8","BDT calib events 8th bin",2245,100,10000);
  Tis8->setConstant(kTRUE);
  //  RooRealVar *TisAll = new RooRealVar("TisAll","BDT calib events normalization",16734,1000,100000);
  //   TisAll->setConstant(kTRUE);
  
  RooFormulaVar * TisAll = new RooFormulaVar("TisAll", "sum of tis must be tis all" ,
                                             "(@0 + @1 + @2 + @3 + @4 + @5 + @6 + @7)",
                                             RooArgList(*Tis1, *Tis2, *Tis3, *Tis4, 
                                                        *Tis5, *Tis6, *Tis7, *Tis8));

  
  RooRealVar *Tis[nBinning] = {Tis1, Tis2, Tis3, Tis4, Tis5, Tis6, Tis7, Tis8};
  for(Int_t b=0; b<nBinning;b++){
    Tis[b]->setMin(max(tis_mean[b] - 7*tis_sigma[b],0.));
    Tis[b]->setMax(tis_mean[b] + 7*tis_sigma[b]);
    
  }
  
  //epsilon-double_misID =  (7.5+/-0.5) *10^-5


  //BhhMisID_DLL = EVal(1.52e-5,[0.07e-5,0.07e-5]) # Jose/Fatima 240112
  //BhhMisID_DLL_factors = [1.04,1.07,1.06,1.07,1.04,0.95,0.87,0.81] # Jose/Fatima 240112

  RooRealVar *douMis = new RooRealVar("douMis","double misid eff",0.0000152,0.0,0.0001);
  douMis->setConstant(kTRUE);

  /*
    Justin trigger bias corrections from BDTparam_1fb.py 
    J1 = 0.9573;
    J2 = 0.9219;
    J3 = 0.9212;
    J4 = 1.0080;
    J5 = 1.0402;
    J6 = 1.0715;
    J7 = 1.0851;  
    J8 = 1.0979;  
  */
  
  //Justine factors are only used 'normalized'
  RooRealVar *J1 = new RooRealVar("J1","Justine factor 1st bin",0.9573,0.8,1.2);
  J1->setConstant(kTRUE);
  RooRealVar *J2 = new RooRealVar("J2","Justine factor 2nd bin",0.9219,0.8,1.2);
  J2->setConstant(kTRUE);
  RooRealVar *J3 = new RooRealVar("J3","Justine factor 3rd bin",0.9212,0.8,1.2);
  J3->setConstant(kTRUE);
  RooRealVar *J4 = new RooRealVar("J4","Justine factor 4th bin",1.0080,0.8,1.2);
  J4->setConstant(kTRUE);
  RooRealVar *J5 = new RooRealVar("J5","Justine factor 5th bin",1.0402,0.8,1.2);
  J5->setConstant(kTRUE);
  RooRealVar *J6 = new RooRealVar("J6","Justine factor 6th bin",1.0715,0.8,1.2);
  J6->setConstant(kTRUE);
  RooRealVar *J7 = new RooRealVar("J7","Justine factor 7th bin",1.0851,0.8,1.2);
  J7->setConstant(kTRUE);
  RooRealVar *J8 = new RooRealVar("J8","Justine factor 8th bin",1.0979,0.8,1.2);
  J8->setConstant(kTRUE);
  RooRealVar *Jave = new RooRealVar("Jave","Justine average factor",0.0567,0.050,0.060);
  Jave->setConstant(kTRUE);
  
  /*
    BhhMisID_DLL_factors = [1.04,1.07,1.06,1.07,1.04,0.95,0.87,0.81] # Jose/Fatima 240112
  */
  
  //DLL factors 
  RooRealVar *DLL1 = new RooRealVar("DLL2","DLL factor 2nd bin",1.04,0,2);
  DLL1->setConstant(kTRUE);
  RooRealVar *DLL2 = new RooRealVar("DLL2","DLL factor 2nd bin",1.07,0,2);
  DLL2->setConstant(kTRUE);
  RooRealVar *DLL3 = new RooRealVar("DLL3","DLL factor 3rd bin",1.06,0,2);
  DLL3->setConstant(kTRUE);
  RooRealVar *DLL4 = new RooRealVar("DLL4","DLL factor 4th bin",1.07,0,2);
  DLL4->setConstant(kTRUE);
  RooRealVar *DLL5 = new RooRealVar("DLL5","DLL factor 5th bin",1.04,0,2);
  DLL5->setConstant(kTRUE);
  RooRealVar *DLL6 = new RooRealVar("DLL6","DLL factor 6th bin",0.95,0,2);
  DLL6->setConstant(kTRUE);
  RooRealVar *DLL7 = new RooRealVar("DLL7","DLL factor 7th bin",0.87,0,2);
  DLL7->setConstant(kTRUE);
  RooRealVar *DLL8 = new RooRealVar("DLL8","DLL factor 8th bin",0.81,0,2);
  DLL8->setConstant(kTRUE);
  

  /***************************************************/
  //  Define and Initialize Fit vars and parameters
  /***************************************************/

  RooRealVar *mass = new RooRealVar("m_{#mu#mu}","m_{#mu#mu}",4900.,5700.,"MeV/c^{2}");
  mass->setBins(10000,"cache");
  RooRealVar *bdt = new RooRealVar("bdt","bdt",0.,1.,"");
  bdt->setBins(10000,"cache");


  RooRealVar* BrBd = new RooRealVar ("B_{Bd}","Branching fraction Bd",1e-10, -1e-10, 1e-6);
  RooRealVar* BrBs = new RooRealVar ("B_{Bs}","Branching fraction Bs",1e-10, -1e-10, 1e-6);

  const   double alpha_bd_mean = 8.38e-11;
  const   double alpha_bs_mean = 3.19e-10;
  const   double alpha_bd_sigma = 0.39e-11;
  const   double alpha_bs_sigma = 0.28e-10;  
  RooRealVar *alpha_bd = new RooRealVar("alpha_{Bd}", "Single event sensitivity for Bd", 
                                        alpha_bd_mean, alpha_bd_mean - 6*alpha_bd_sigma,
                                        alpha_bd_mean + 6*alpha_bd_sigma);
  alpha_bd->setConstant(kTRUE);
  RooRealVar *alpha_bs = new RooRealVar("alpha_{Bs}", "Single event sensitivity for Bs", 
                                        alpha_bs_mean, alpha_bs_mean - 6*alpha_bs_sigma,
                                        alpha_bs_mean + 6*alpha_bs_sigma);
  alpha_bs->setConstant(kTRUE);

  //  ============================================================
  // Definition of parameters of interest (POI)

  // First option: calculate number of events from branching ratio and normalisation
  // and use branching ratios as POI
  RooFormulaVar * NBd_f = new RooFormulaVar("NBd","Number of Bd", "(@0/@1)",
                                            RooArgList(*BrBd,*alpha_bd));
  RooFormulaVar * NBs_f = new RooFormulaVar("NBs","Number of Bs", "(@0/@1)",
                                            RooArgList(*BrBs,*alpha_bs));
  
  // Second option: use number of events as parameter of interest 
  RooRealVar* NBd_v = new RooRealVar ("N_{Bd}","Total number Bd",10.,-10.,50);
  RooRealVar* NBs_v = new RooRealVar ("N_{Bs}","Total number Bs",10.,-10.,50);

  // Third option: use N_Bs and R= BR(Bd)/BR(Bs) as parameters of interest 
  // R = ( NBd/NBs)*(fs/fd)*(eff_bs/eff_bd)
  RooRealVar* BRRatio = new RooRealVar ("R", "Ratio of branching fractions BR(Bd)/BR(Bs)", 0.1, -100, 1000000);
  RooRealVar* fsfd = new RooRealVar("fsfd","Value of fs/fd" , 0.267,0., 1); // 0.267 + 0.021 - 0.020
  RooRealVar* bdbs_eff_ratio = new RooRealVar("eff_ratio", "eff_ratio", 0.978, 0.5, 1.5);  // 0.9780 +-  0.0065
  
  RooFormulaVar* NBd_r = new RooFormulaVar("NBdr","Number of Bd", "(@0*@1)/(@2*@3)",
					   RooArgList(*BRRatio, *NBs_v, *fsfd, *bdbs_eff_ratio));
  
  RooAbsReal *NBd;
  RooAbsReal *NBs;
//   if(addPrior){
//     NBd = NBd_f;
//     NBs = NBs_f;
//   }else if(measureRatio){
//     NBs = NBs_v;
//     NBd = NBd_r; 
//   }else{
//     NBd = NBd_v;
//     NBs = NBs_v;
//   }
  if(measureRatio){
    NBs = NBs_v;
    NBd = NBd_r; 
  }else{
    NBd = NBd_f;
    NBs = NBs_f;
  }


 //N_double_misID=    TisTOT/ Jave*epsilon_double_misID
  //  RooFormulaVar* N_Mis = new RooFormulaVar ("N_{mis}","Total number Misid","(@0/@1)*(@2)",RooArgList(*TisAll,*Jall,*douMis));
  
  //Bd CB shape parameters
  /// mean mass 
  RooRealVar *mbd;
  RooRealVar *mbs;
  if(doData) {
    mbd = new RooRealVar("m_{Bd}","mbd",5284.6,5260,5300,"MeV/c^{2}");
    mbs = new RooRealVar("m_{Bs}","mbs",5373.,5350,5390,"MeV/c^{2}");
  } else {
    mbd = new RooRealVar("m_{Bd}","mbd",5278.,5260,5300,"MeV/c^{2}");
    mbs = new RooRealVar("m_{Bs}","mbs",5369.,5350,5390,"MeV/c^{2}");
  }
  /// Resolution 
  RooRealVar *mbdw   = new RooRealVar("#sigma_{Bd}","Bs mass resolution",24.2,20,30,"MeV/c^{2}");
  RooRealVar *mbsw   = new RooRealVar("#sigma_{Bs}","Bs mass resolution",24.8,20,30,"MeV/c^{2}");

  /*********************************************/
  //    Define  PDFs
  /*********************************************/

  /*
    Combinatorial Background
  */

  //Mass PDF

  //Exponential PDF definition
  bool fix_k = true;
  RooRealVar *tauBg[nBinning];

  // Values fitted without constraints ( to start with ) 
  double tau_values[nBinning] = {  -6.46945e-04,   -1.02567e-03, -8.66636e-04 ,  -1.00589e-03 ,
				   -7.99555e-04  , -2.58717e-03 , -5.20871e-03 , -5.20871e-03};
  

  for(Int_t b=0; b<nBinning; b++){
    TString _suffix = ""; _suffix += b+1;
    tauBg[b] = new RooRealVar("tk_"+_suffix,"Tau of bg mass dist", tau_values[b],-0.05,0.05,"");      
    //    tauBg[b]->setConstant(kTRUE);
    
  }
  if(fix_k){
    tauBg[7] = tauBg[6];
  }
  

  //Extended PDF
  sprintf(hn,"RootOutp_MCAll_%s.root",flag.data());   
  cout<<"Going to write file :: "<<hn<<endl;

  TFile f(hn,"RECREATE"); f.cd();
  vector<string> strcut;
  strcut.push_back("bdt<0.25");
  strcut.push_back("bdt>=0.25 && bdt<0.4");
  strcut.push_back("bdt>=0.4 && bdt<0.5");
  strcut.push_back("bdt>=0.5 && bdt<0.6");
  strcut.push_back("bdt>=0.6 && bdt<0.7");
  strcut.push_back("bdt>=0.7 && bdt<0.8");
  strcut.push_back("bdt>=0.8 && bdt<0.9");
  strcut.push_back("bdt>=0.9");           

  RooDataSet* data;

  // TTree *RootTree = new TTree("ProfileTree","Profile 2D results");
  // double t_nbs, t_nbd, t_nll;
  // double e_tbkg, t_tbkg;
  // double e_nbkg_2, t_nbkg_2, e_nbkg_3, t_nbkg_3, e_nbkg_4, t_nbkg_4;
  // double e_nbkg_5, t_nbkg_5, e_nbkg_6, t_nbkg_6, e_nbkg_7, t_nbkg_7, e_nbkg_8, t_nbkg_8;
  // RootTree->Branch("nbs",&t_nbs,"nbs/D");
  // RootTree->Branch("nbd",&t_nbd,"nbd/D");
  // RootTree->Branch("nll",&t_nll,"nll/D");
  // RootTree->Branch("tbkg",&t_tbkg,"tbkg/D");
  // RootTree->Branch("e_tbkg",&e_tbkg,"e_tbkg/D");
  // RootTree->Branch("nbkg_2",&t_nbkg_2,"nbkg_2/D");
  // RootTree->Branch("e_nbkg_2",&e_nbkg_2,"e_nbkg_2/D");
  // RootTree->Branch("nbkg_3",&t_nbkg_3,"nbkg_3/D");
  // RootTree->Branch("e_nbkg_3",&e_nbkg_3,"e_nbkg_3/D");
  // RootTree->Branch("nbkg_4",&t_nbkg_4,"nbkg_4/D");
  // RootTree->Branch("e_nbkg_4",&e_nbkg_4,"e_nbkg_4/D");
  // RootTree->Branch("nbkg_5",&t_nbkg_5,"nbkg_5/D");
  // RootTree->Branch("e_nbkg_5",&e_nbkg_5,"e_nbkg_5/D");
  // RootTree->Branch("nbkg_6",&t_nbkg_6,"nbkg_6/D");
  // RootTree->Branch("e_nbkg_6",&e_nbkg_6,"e_nbkg_6/D");
  // RootTree->Branch("nbkg_7",&t_nbkg_7,"nbkg_7/D");
  // RootTree->Branch("e_nbkg_7",&e_nbkg_7,"e_nbkg_7/D");
  // RootTree->Branch("nbkg_8",&t_nbkg_8,"nbkg_8/D");
  // RootTree->Branch("e_nbkg_8",&e_nbkg_8,"e_nbkg_8/D");


  RooWorkspace *w;



  /*
    Final PDF is created as a sum of all the PDFs listed in the 'pdfs' RooArgList object
  */
  
  //     RooFormulaVar * sumOfTis = new RooFormulaVar("sumAll", "sum of tis must be tis all" ,
  // 						 "(@0 + @1 + @2 + @3 + @4 + @5 + @6 + @7 - @8)",
  // 						 RooArgList(*Tis1, *Tis2, *Tis3, *Tis4, 
  // 							    *Tis5, *Tis6, *Tis7, *Tis8, 
  // 							    *TisAll));

						 

  RooFormulaVar * fr1 = new RooFormulaVar("fr1","Fr. events in 1st bdt bin",
					  "(@0/@1)*(1/@2)",
					  RooArgList(*Tis1,*TisAll,*J1));
  RooFormulaVar * fr2 = new RooFormulaVar("fr2","Fr. events in 2nd bdt bin",
					  "(@0/@1)*(1/@2)",
					  RooArgList(*Tis2,*TisAll,*J2));
  RooFormulaVar * fr3 = new RooFormulaVar("fr3","Fr. events in 3rd bdt bin",
					  "(@0/@1)*(1/@2)",
					  RooArgList(*Tis3,*TisAll,*J3));
  RooFormulaVar * fr4 = new RooFormulaVar("fr4","Fr. events in 4th bdt bin",
					  "(@0/@1)*(1/@2)",
					  RooArgList(*Tis4,*TisAll,*J4));
  RooFormulaVar * fr5 = new RooFormulaVar("fr5","Fr. events in 4th bdt bin",
					  "(@0/@1)*(1/@2)",
					  RooArgList(*Tis5,*TisAll,*J5));
  RooFormulaVar * fr6 = new RooFormulaVar("fr6","Fr. events in 6th bdt bin",
					  "(@0/@1)*(1/@2)",
					  RooArgList(*Tis6,*TisAll,*J6));
  RooFormulaVar * fr7 = new RooFormulaVar("fr7","Fr. events in 7th bdt bin",
					  "(@0/@1)*(1/@2)",
					  RooArgList(*Tis7,*TisAll,*J7));
  RooFormulaVar * fr8 = new RooFormulaVar("fr8","Fr. events in 8th bdt bin",
					  "(@0/@1)*(1/@2)",
					  RooArgList(*Tis8,*TisAll,*J8));
    
    
  // Total yield of mis-ID
  RooFormulaVar * misfr1 = new RooFormulaVar("misfr1","Misfr. events in 1st bdt bin",
					     "(@0/(@1*@3))*(@2*@4)",
					     RooArgList(*Tis1,*J1,*douMis,*Jave,*DLL1));
  RooFormulaVar * misfr2 = new RooFormulaVar("misfr2","Misfr. events in 2nd bdt bin",
					     "(@0/(@1*@3))*(@2*@4)",
					     RooArgList(*Tis2,*J2,*douMis,*Jave,*DLL2));
  RooFormulaVar * misfr3 = new RooFormulaVar("misfr3","Misfr. events in 3rd bdt bin",
					     "(@0/(@1*@3))*(@2*@4)",
					     RooArgList(*Tis3,*J3,*douMis,*Jave,*DLL3));
  RooFormulaVar * misfr4 = new RooFormulaVar("misfr4","Misfr. events in 4th bdt bin",
					     "(@0/(@1*@3))*(@2*@4)",
					     RooArgList(*Tis4,*J4,*douMis,*Jave,*DLL4));
  RooFormulaVar * misfr5 = new RooFormulaVar("misfr5","Misfr. events in 4th bdt bin",
					     "(@0/(@1*@3))*(@2*@4)",
					     RooArgList(*Tis5,*J5,*douMis,*Jave,*DLL5));
  RooFormulaVar * misfr6 = new RooFormulaVar("misfr6","Misfr. events in 6th bdt bin",
					     "(@0/(@1*@3))*(@2*@4)",
					     RooArgList(*Tis6,*J6,*douMis,*Jave,*DLL6));
  RooFormulaVar * misfr7 = new RooFormulaVar("misfr7","Misfr. events in 7th bdt bin",
					     "(@0/(@1*@3))*(@2*@4)",
					     RooArgList(*Tis7,*J7,*douMis,*Jave,*DLL7));
  RooFormulaVar * misfr8 = new RooFormulaVar("misfr8","Misfr. events in 8th bdt bin",
					     "(@0/(@1*@3))*(@2*@4)",
					     RooArgList(*Tis8,*J8,*douMis,*Jave,*DLL8));



  // RooKeysPdf for mis-ID distribution

  RooKeysPdf * key_misid_v[nBinning];
  for(Int_t i=0; i<nBinning; i++){
    key_misid_v[i] = (RooKeysPdf*)key_misid->clone(TString("keymisid")+TString(i));
  }
    
  // ==============
  // Total pdf: 
  // TODO: taubkg to be modified
  RooAbsPdf* pdf_fit_1 = CreatePdfForABin(1,  fr1, mass, NBd, NBs, misfr1, 
					  mbd, mbs, mbdw, mbsw, tauBg[0], key_misid_v[0]);
    
  RooAbsPdf* pdf_fit_2 = CreatePdfForABin(2,  fr2, mass, NBd, NBs, misfr2, 
					  mbd, mbs, mbdw, mbsw, tauBg[1], key_misid_v[1]);

  RooAbsPdf* pdf_fit_3 = CreatePdfForABin(3,  fr3, mass, NBd, NBs, misfr3, 
					  mbd, mbs, mbdw, mbsw, tauBg[2], key_misid_v[2]);

  RooAbsPdf* pdf_fit_4 = CreatePdfForABin(4,  fr4, mass, NBd, NBs, misfr4, 
					  mbd, mbs, mbdw, mbsw, tauBg[3], key_misid_v[3]);

  RooAbsPdf* pdf_fit_5 = CreatePdfForABin(5,  fr5, mass, NBd, NBs, misfr5, 
					  mbd, mbs, mbdw, mbsw, tauBg[4], key_misid_v[4]);

  RooAbsPdf* pdf_fit_6 = CreatePdfForABin(6,  fr6, mass, NBd, NBs, misfr6, 
					  mbd, mbs, mbdw, mbsw, tauBg[5], key_misid_v[5]);

  RooAbsPdf* pdf_fit_7 = CreatePdfForABin(7,  fr7, mass, NBd, NBs, misfr7, 
					  mbd, mbs, mbdw, mbsw, tauBg[6], key_misid_v[6]);

  RooAbsPdf* pdf_fit_8 = CreatePdfForABin(8,  fr8, mass, NBd, NBs, misfr8, 
					  mbd, mbs, mbdw, mbsw, tauBg[7], key_misid_v[7]);
    
  RooAbsPdf * pdf_fit[nBinning] = 
    { pdf_fit_1 , pdf_fit_2 , pdf_fit_3 , pdf_fit_4 , 
      pdf_fit_5 , pdf_fit_6 , pdf_fit_7 , pdf_fit_8};
  //  RooProdPdf *pdfWithPrior[nBinning];
  //    RooGaussian *TisAllPrior;
  bool add_tis_constr[nBinning] = {true, true,true, true,
                                   true, true,true, false
  };
  // bool add_tis_constr[nBinning] = { false
//   };
  
  
//     {true, true, true, true, 
//      true, true, true, true };

  RooGaussian *TisConstr[nBinning]; 
  RooGaussian *NormGauss_bd,  *NormGauss_bs;
  RooRealVar *NormMean_bd = new RooRealVar("NormMean_bd","NormMean_bd",alpha_bd_mean, 
                                           alpha_bd_mean-6*alpha_bd_sigma,
                                           alpha_bd_mean+6*alpha_bd_sigma);
  RooRealVar *NormMean_bs = new RooRealVar("NormMean_bs","NormMean_bs",alpha_bs_mean, 
                                           alpha_bs_mean-6*alpha_bs_sigma,
                                           alpha_bs_mean+6*alpha_bs_sigma);
  NormMean_bs->setConstant(kTRUE);
  NormMean_bd->setConstant(kTRUE);
  
  RooConstVar *NormSigma_bd = new RooConstVar("NormSigma_bd","NormSigma_bd",alpha_bd_sigma);
  RooConstVar *NormSigma_bs = new RooConstVar("NormSigma_bs","NormSigma_bs",alpha_bs_sigma);

  if(addPrior) {
    // Priors for TIS calibration
    /*
      TisTOT      =    16734 +/-  1312     (syst incluse)
      Tis2        =     1877 +/-  242
      Tis3        =     1486 +/-  158
      Tis4        =     1447 +/-  89
      Tis5        =     1729 +/-  100
      Tis6        =     1846 +/-  69
      Tis7        =     2133 +/-  107
      Tis8        =     2245 +/-  327

      Tis1(computed) = 4116 +- 1312 (assuming same error as total) 
	
      https://indico.cern.ch/getFile.py/access?contribId=6&resId=0&materialId=slides&confId=173406

    */


    // 
    // Do not att prior for TIS1 since we add prior for TisAll
    // Lets see... 
  
      
    RooConstVar *TisMean[nBinning], *TisSigma[nBinning]; 
    RooConstVar *TisAllMeanC, *TisAllSigmaC;

    
    for(Int_t b = 0; b<nBinning; b++){ 
      TString _suffix ="_"; _suffix+=b+1; 
      TisMean[b]  = new RooConstVar("TisMean"+_suffix,"TisMean"+_suffix, tis_mean[b]);
      TisSigma[b] = new RooConstVar("TisSigma"+_suffix,"TisSigma"+_suffix, tis_sigma[b]);
      TisConstr[b] = new RooGaussian("TisConstr"+_suffix, "TisConstr"+_suffix, 
                                     *Tis[b], *TisMean[b], *TisSigma[b]); 
      
      cout << "TIS prior " << _suffix << " " << tis_mean[b] << " " << tis_sigma[b] << endl;
      
      //       pdfWithPrior[b] = new RooProdPdf("pdfWithPrior"+_suffix,"pdfWithPrior"+_suffix, 
      // 				       RooArgSet(*pdf_fit[b], *TisConstr[b])) ;
      
      
    }
    
    // Priors on alpha 
    
    
    NormGauss_bd =new RooGaussian("NormPrior_bd","NormPrior_bd", 
                                  *alpha_bd, *NormMean_bd, *NormSigma_bd);
    NormGauss_bs =new RooGaussian("NormPrior_bs","NormPrior_bs", 
                                  *alpha_bs, *NormMean_bs, *NormSigma_bs);


  }// end addPrior

  /*
    Data Set Is Loaded from the file: Paper is bdtx!
  */

  //Write File Result
  sprintf(hn,"RootOutp_MCAll_%s.root",flag.data());   
  cout<<"Going to write file :: "<<hn<<endl;

  mbs->setConstant(kTRUE);
  mbd->setConstant(kTRUE);

  mbsw->setConstant(kTRUE);
  mbdw->setConstant(kTRUE);
  

  sprintf(pdfnm,"w");

  w = new RooWorkspace(pdfnm,"workspace");

  RooCategory binning("binning","binning") ;
  binning.defineType("bin1") ;
  binning.defineType("bin2") ;
  binning.defineType("bin3") ;
  binning.defineType("bin4") ;
  binning.defineType("bin5") ;
  binning.defineType("bin6") ;
  binning.defineType("bin7") ;
  binning.defineType("bin8") ;
  w->import(binning);



  cout<< "Create simultaneous pdf" << endl;
  // Create simultaneous PDF 
  RooSimultaneous *simPdf = new RooSimultaneous("simPdf","simultaneous pdf",binning) ;
  RooSimultaneous *simBkgPdf = new RooSimultaneous("simBkgPdf","simultaneous pdf for background only",binning) ;
  RooSimultaneous *simBsPdf = new RooSimultaneous("simBsPdf","simultaneous pdf for Bs signal only",binning) ;
  RooSimultaneous *simBdPdf = new RooSimultaneous("simBdPdf","simultaneous pdf for Bd signal only",binning) ;
  RooArgSet *allConstraints = new RooArgSet("constraints"); 
  for(Int_t b=0; b<nBinning; b++){
    TString _bin="" ;        _bin += b+1;
    simPdf->addPdf(*pdf_fit[b], "bin"+_bin);
    
    RooArgSet* bkgPdfs = new RooArgSet("fullbkglist"+_bin);
    bkgPdfs->add(*pdf_fit[b]->getComponents()->find("bkg_mass_"+_bin));  	  
    bkgPdfs->add(*pdf_fit[b]->getComponents()->find("mass_misid_"+_bin));  	  
    RooAddPdf* bkgPdfAdded = new RooAddPdf("fullbkg"+_bin,"Total background PDF",RooArgSet(*bkgPdfs));
    simBkgPdf->addPdf(*bkgPdfAdded, "bin"+_bin);

    RooArgSet* bsPdfs = new RooArgSet("fullbslist"+_bin);
    bsPdfs->add(*pdf_fit[b]->getComponents()->find("sig_bs_mass_"+_bin));  	  
    RooAddPdf* bsPdfAdded = new RooAddPdf("fullbs"+_bin,"Total bs PDF",RooArgSet(*bsPdfs));
    simBsPdf->addPdf(*bsPdfAdded, "bin"+_bin);

    RooArgSet* bdPdfs = new RooArgSet("fullbdlist"+_bin);
    bdPdfs->add(*pdf_fit[b]->getComponents()->find("sig_bd_mass_"+_bin));  	  
    RooAddPdf* bdPdfAdded = new RooAddPdf("fullbd"+_bin,"Total bd PDF",RooArgSet(*bdPdfs));
    simBdPdf->addPdf(*bdPdfAdded, "bin"+_bin);
    
    if(addPrior){
      if(add_tis_constr[b]){
        allConstraints->add(*TisConstr[b]);
      }
    }
  }
  if(addPrior){
    if(!bsOnly) allConstraints->add(*NormGauss_bd);
    allConstraints->add(*NormGauss_bs);
  }
  

  
  RooArgList *argonauti = new RooArgList(*allConstraints);
  argonauti->add(*simPdf);
  argonauti->Print();
  
  RooProdPdf * simPdfConstr = new RooProdPdf("simPdfC", "simPdfC", *argonauti);
  
  if(addPrior){
    simPdf->SetName("simPdf_nc");
    simPdfConstr->SetName("simPdf");
    w->import(*simPdfConstr);
  }
  

  w->import(*simPdf, RecycleConflictNodes() );
  w->import(*simBkgPdf, RecycleConflictNodes() );
  w->import(*simBsPdf, RecycleConflictNodes() );
  w->import(*simBdPdf, RecycleConflictNodes() );
  
  if(addPrior)w->defineSet("constraints",*allConstraints, true);

  RooArgSet * globObs;
  if(addGlobObs){
    
    cout << "Adding global observables " << endl;
    TString gobsvars = "";
    if(!bsOnly){ 
      gobsvars+= alpha_bd->GetName();
      gobsvars+=",";
    }
    gobsvars+= alpha_bs->GetName();
    for(Int_t b=0; b<nBinning; b++){
      gobsvars+=",";
      if(add_tis_constr[b]) gobsvars += Tis[b]->GetName();
    }
    
    cout << " Defining set globObs with " << gobsvars <<  endl;
    //    w->import(*globObs, RecycleConflictNodes());
    w->defineSet("globObs", gobsvars);
  }
  if(addPrior){
//     TString nuisance = "";
//    //  if(!bsOnly) {
// //       nuisance += alpha_bd->GetName();
// //       nuisance += ",";
// //     }
// //     nuisance += alpha_bs->GetName();
//     cout << " Definine set nuisance with " << nuisance <<  endl;
//     w->defineSet("nuisance", nuisance); 
    
  }
  
  
  cout << "SimPdf: Done" << endl;
  
  
  int _tmp =       gErrorIgnoreLevel;
  gErrorIgnoreLevel = kWarning;

  if(writedata){
    data = RooDataSet::read(infi.data(),RooArgList(*mass,*bdt));
    RooDataSet *data1 = (RooDataSet*)data->reduce(Cut(strcut.at(0).data())); 
    RooDataSet *data2 = (RooDataSet*)data->reduce(Cut(strcut.at(1).data()));
    RooDataSet *data3 = (RooDataSet*)data->reduce(Cut(strcut.at(2).data()));
    RooDataSet *data4 = (RooDataSet*)data->reduce(Cut(strcut.at(3).data()));
    RooDataSet *data5 = (RooDataSet*)data->reduce(Cut(strcut.at(4).data()));
    RooDataSet *data6 = (RooDataSet*)data->reduce(Cut(strcut.at(5).data()));
    RooDataSet *data7 = (RooDataSet*)data->reduce(Cut(strcut.at(6).data()));
    RooDataSet *data8 = (RooDataSet*)data->reduce(Cut(strcut.at(7).data()));
      
    sprintf(pdfnm,"mydata1");
    data1->SetName(pdfnm);
      
    sprintf(pdfnm,"mydata2");
    data2->SetName(pdfnm);
      
    sprintf(pdfnm,"mydata3");
    data3->SetName(pdfnm);
      
    sprintf(pdfnm,"mydata4");
    data4->SetName(pdfnm);
      
    sprintf(pdfnm,"mydata5");
    data5->SetName(pdfnm);
      
    sprintf(pdfnm,"mydata6");
    data6->SetName(pdfnm);
      
    sprintf(pdfnm,"mydata7");
    data7->SetName(pdfnm);
      
    sprintf(pdfnm,"mydata8");
    data8->SetName(pdfnm);
      
    // Binning in BDT 
    RooDataSet* mydata[nBinning] = {data1,data2,data3,data4,
				    data5,data6,data7,data8};
            
    //RooWorkspace * dataws  = (RooWorkspace*)f.Get("w;1");
    map<string,RooDataSet*> data_map; 
    for (Int_t b = 0; b< nBinning; b++){
      TString _bin="bin" ;  _bin += b+1;
      data_map[string(_bin)] = mydata[b];
    }
      
    //  Import(map<string,RooDataSet*>&) -
    cout<< "Combining the binned data " << endl;
    RooDataSet *combData =   
      new RooDataSet("combData", "combined data",
		     RooArgSet(*mass), Index(binning), Import(data_map));
      
    combData->Print();
    w->import(*combData);
  
  }
  gErrorIgnoreLevel = _tmp;
  if(doModelConfig){
    // TODO: add known parameters as global observables 
    
    bool useConstraints = 1;
    TString s_NBd =  useConstraints ? "B_{Bd}": "N_{Bd}";
    TString s_NBs =  useConstraints ? "B_{Bs}": "N_{Bs}";
  
    TString m_POI_set = "poi";
    TString _poi="";
    _poi+= s_NBs; _poi += ",";
    _poi+= s_NBd;
    w->defineSet(m_POI_set, _poi);
    TString m_obs_set = "obs";
    w->defineSet(m_obs_set, "m_{#mu#mu},binning");

    RooStats::ModelConfig *modelConfig = new RooStats::ModelConfig("myProblem", w);
    modelConfig->SetPdf(*simPdf);
    modelConfig->SetParametersOfInterest(*w->set(m_POI_set));
    if(addGlobObs)modelConfig->SetGlobalObservables(*globObs);
    
    modelConfig->SetObservables(*(w->set(m_obs_set)));
    modelConfig->Print();
    
    w->import(*modelConfig);
        
  }

    
  sprintf(hn,"RootWorksp_FD_%s.root",flag.data());   
  w->writeToFile(hn) ;

  w->Print();
  return 0;
}





void ExpPlot(RooRealVar *abdt, RooDataSet *adt, RooAbsPdf *apdf, bool syst, int sys_id, 
             string anm, string flg, bool log, string dname, string pname, int bin) {

  RooPlot *rpb; char hn[200];
  char evRange[200];
  TLatex *lhcbLatex;
  lhcbLatex = new TLatex(0.18, 0.83,"#splitline{LHCb}{Preliminary}");
  TCanvas *c_4 = new TCanvas("c_4","");
  //Expert plot

  if(log) gPad->SetLogy();

  c_4->Clear(); c_4->cd(); 
  //  gPad->SetLogy();

  //  rpb = abdt->frame(5100,5600,25);
  rpb = abdt->frame(4900,5700,40);
  gPad->SetLeftMargin(0.14);
  gPad->SetBottomMargin(0.14);
  gPad->SetRightMargin(0.05);
  gPad->SetTopMargin(0.05);
  rpb->SetTitle("");
  rpb->SetTitleSize(0.06,"x");
  rpb->SetTitleSize(0.06,"y");
  adt->plotOn(rpb,Name(dname.data()));
  apdf->plotOn(rpb,Name(pname.data()));
  //  apdf->paramOn(rpb,Layout(0.6,0.92,0.92));
  apdf->plotOn(rpb,"",Components("*bs*"), "", LineColor(2));
  apdf->plotOn(rpb,"",Components("*bd*"), "", LineColor(9));
  apdf->plotOn(rpb,"",Components("*bkg*"), "", LineColor(6));
  apdf->plotOn(rpb,"",Components("*mis*"), "", LineColor(8));

  sprintf(evRange,"%s%1.3lf","#chi^{2}: ",rpb->chiSquare(pname.data(),dname.data(),5));
  cout<<evRange<<endl;
    
  
  lhcbLatex->SetNDC(kTRUE);
  //  lhcbLatex->SetTextFont(lhcbFont);
  lhcbLatex->SetTextColor(1);
  lhcbLatex->SetTextSize(0.06);
  lhcbLatex->DrawLatex(0.18, 0.83,"#splitline{LHCb}{Preliminary}");
  //  rpb->addObject(lhcbLatex);
  rpb->SetMinimum(0.00001);
  rpb->Draw();
  rpb->Write();
  
  sprintf(hn,"%s_%s_Bin%d.eps",anm.data(),flg.data(),bin);   
  if(syst)  sprintf(hn,"%s_%s_Sys%d_Bin%d.eps",anm.data(),flg.data(),sys_id,bin);   
  c_4->Print(hn);

}


//==============================================================================
RooAbsPdf* CreatePdfForABin(int bin, RooFormulaVar* fr, RooRealVar* m, 
                            RooAbsReal* nbd, RooAbsReal* nbs, RooFormulaVar* nmis, RooRealVar *mbd, 
                            RooRealVar *mbs, RooRealVar *wmbd, RooRealVar *wmbs, 
                            RooRealVar *tau, RooAbsPdf *m_misid_pdf) {

  char name[200]; RooAbsPdf *fit;
  int bkg_in[8] = {10000,108,18,1, 1,1,1,1}; // just for the sake of it. 
  
  //Bd CB shape parameters
  sprintf(name,"#alpha_{Bd}_%d",bin);
  RooRealVar *bdalpha  = new RooRealVar(name,"Alpha",2.11,0,5,"");
  bdalpha->setConstant(kTRUE);
  sprintf(name,"CBn_{Bd}_%d",bin);
  RooRealVar *bdn  = new RooRealVar(name,"N",1,0,5,"");
  bdn->setConstant(kTRUE);

  //Bs CB shape parameters
  //  sprintf(name,"#sigma_{Bs}_%d",bin);
  //  RooRealVar *mbsw   = new RooRealVar(name,"Bs mass resolution",24.7,10,150,"MeV/c^{2}");
  //  mbsw->setConstant(kTRUE);
  sprintf(name,"#alpha_{Bs}_%d",bin);
  RooRealVar *bsalpha  = new RooRealVar(name,"Alpha",2.11,0,5,"");
  bsalpha->setConstant(kTRUE);
  sprintf(name,"CBn_{Bs}_%d",bin);
  RooRealVar *bsn  = new RooRealVar(name,"N",1,0,5,"");
  bsn->setConstant(kTRUE);

  // Crystal ball for Bd
  sprintf(name,"cb_bd_%d",bin);
  RooAbsPdf* cb_bd =  new RooCBShape(name,"Bd Mass signal PDF",*m,*mbd,*wmbd,*bdalpha,*bdn);
  sprintf(name,"Nb_%d",bin);
  RooFormulaVar *Nb = new RooFormulaVar(name,"signal in given bin","@0*@1",RooArgList(*nbd,*fr));
  sprintf(name,"sig_bd_mass_%d",bin);
  RooExtendPdf *sig_bd_mass = new RooExtendPdf(name,"Signal ext mass PDF Bd",*cb_bd,*Nb);

  // Crystal ball for Bs
  sprintf(name,"cb_bs_%d",bin);
  RooAbsPdf* cb_bs =  new RooCBShape(name,"Bs Mass signal PDF",*m,*mbs,*wmbs,*bsalpha,*bsn);
  sprintf(name,"Ns_%d",bin);
  RooFormulaVar *Ns = new RooFormulaVar(name,"signal in given bin","@0*@1",RooArgList(*nbs,*fr));
  sprintf(name,"sig_bs_mass_%d",bin);
  RooExtendPdf *sig_bs_mass = new RooExtendPdf(name,"Signal ext mass PDF Bs",*cb_bs,*Ns);

  // Build the full signal pdf 
  sprintf(name,"mpdfs_%d",bin);
//   RooArgSet *mpdfs = new RooArgSet(name);
//   mpdfs->add(*sig_bs_mass);
//   mpdfs->add(*sig_bd_mass);  
//   sprintf(name,"sig_mass_%d",bin);
  //RooAbsPdf *sig_mass = new RooAddPdf(name,"Sum of ext CB of Bd and Bs",RooArgSet(*mpdfs));


  // PDF for the combinatorial background 
  sprintf(name,"pdf_Bkg_%d",bin);
  RooAbsPdf* pdf_Bkg =  new RooExponential(name,"massBackgroundPdf",*m,*tau); 

  sprintf(name,"N_comb_%d",bin);
  RooRealVar* N_Bkg = new RooRealVar (name,"Total number Bkg",15558,0,1000000);
  my_Nbkg.push_back(N_Bkg);

  sprintf(name,"bkg_mass_%d",bin);
  N_Bkg->setVal(bkg_in[bin-1]);


  RooExtendPdf* bkg_mass = new RooExtendPdf(name,"extended background p.d.f",*pdf_Bkg,*N_Bkg) ;
    
  /* Peaking Background PDF: RooHist */
  //   sprintf(name,"data_misid_%d",bin);
  //   RooDataHist* data_misid= new RooDataHist(name,"mass*BDT",*m,hmis);

  //   sprintf(name,"m_misid_pdf_%d",bin);
  //   RooAbsPdf *m_misid_pdf =  new RooHistPdf(name,"Misid PDF",*m,*data_misid);
  

  // PDf for the Mis_ID is given in input to the function 
  sprintf(name,"mass_misid_%d",bin);
  m_misid_pdf->SetName("key"+TString(name));
  RooExtendPdf* mass_misid = new RooExtendPdf(name,"extended misid p.d.f",*m_misid_pdf,*nmis) ;
  
  //PDF1
  sprintf(name,"pdfs_%d",bin);

  RooArgSet* pdfs = new RooArgSet(name);
  //pdfs->add(*sig_mass);              //pdfs->add(*glob_pdf_sig);  
  pdfs->add(*sig_bs_mass);
  pdfs->add(*sig_bd_mass);  
  pdfs->add(*bkg_mass);  	     //pdfs->add(*glob_pdf_bkg);  
  pdfs->add(*mass_misid);            //pdfs->add(*glob_pdf_misid);
  
  
  sprintf(name,"pdf_fit_%d",bin);

  fit = new RooAddPdf(name,"Total(B+S) Bs -> mu+ mu- PDF",RooArgSet(*pdfs));
  
  fit->Print("v");
  fit->printCompactTree();

  return fit;

}
