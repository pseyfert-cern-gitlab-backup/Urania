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


#include <string>

using namespace RooFit;
using namespace std;

vector<RooRealVar*> my_Nbkg, my_BDTfr;

RooAbsPdf* CreatePdfForABin(int bin, int sysi, RooFormulaVar *fr, RooRealVar* m, RooRealVar* nbd, RooRealVar* nbs, RooFormulaVar* nmis, RooRealVar *mbd, RooRealVar *mbs, RooRealVar *wmbd, RooRealVar *wmbs, RooRealVar *tau, TH1D *hmis, bool sys);

void ExpPlot(RooRealVar *abdt, RooDataSet *adt, RooAbsPdf *apdf, bool syst, int sys_id, string anm, string flg, bool log, string dname, string pname, int bin);

RooArgList terms;

int main(int argc, char **argv) {

  char hn[200];  int ntoy(100);
  char pdfnm[200];
  string flag = "outp";
  string infi = "InputForMCFit.txt";
  string fconf = "myConf.txt";
  bool doFit = kTRUE;
  bool addPrio(kFALSE);  
  bool doProf(kFALSE);  
  bool doProfileTD(kFALSE);  
  bool doToy(kFALSE);  
  bool doScan(kFALSE);  
  bool doData(kFALSE);  
  int maxbd(0),maxbs(0);
  int  pr_bdmax, pr_bsmax;

  for (int i = 0; i < argc; i++){
    if(strcmp(argv[i],"-in") == 0)    { infi = string(argv[++i]);  }                        // Decide among different MC input
    if(strcmp(argv[i],"-flag") == 0)  { flag = string(argv[++i]);  }                        // Flagging output eps files
    if(strcmp(argv[i],"-ntoy") == 0)  { ntoy = atoi(argv[++i]);    }                 // Number of toys
    if(strcmp(argv[i],"-prior") == 0) { addPrio = kTRUE;       }                 // Number of toys
    if(strcmp(argv[i],"-dopro") == 0) { doProfileTD = kTRUE;       }                 // Number of toys
    if(strcmp(argv[i],"-dotoy") == 0) { doToy = kTRUE;             }                 // Number of toys
    if(strcmp(argv[i],"-data") == 0)  { doData = kTRUE;            }                 // Number of toys
    if(strcmp(argv[i],"-maxbd") == 0)  { pr_bdmax = atoi(argv[++i]);            }                 // Number of toys
    if(strcmp(argv[i],"-maxbs") == 0)  { pr_bsmax = atoi(argv[++i]);            }                 // Number of toys
  }

  my_Nbkg.clear();
  my_BDTfr.clear();

  RooNumIntConfig &conf=RooNumIntConfig::defaultConfig();
  conf.method1D().setLabel("RooAdaptiveGaussKronrodIntegrator1D");
  RooAbsReal::defaultIntegratorConfig()->setEpsAbs(1e-8) ;
  RooAbsReal::defaultIntegratorConfig()->setEpsRel(1e-8) ;
  RooAbsReal::defaultIntegratorConfig()->Print("v");

  //Here you should include your Fit Code
  gROOT->ProcessLine(".x lhcbstyle.C");

  gSystem->Load("libRooFit.so");

  gROOT->SetStyle("Plain"); 

  /*********************************************/
  //    BDT distributions from FILE
  /*********************************************/
 
  bool doSyst = kFALSE;

  int maxsys = 1;
  if(doSyst) { maxsys = 100;}

  TFile*  f_misid = new TFile("misidPDF.root","READ"); f_misid->cd();
  TH1D* h_misid =  ((TH1D*)gDirectory->Get("myH_mis"));

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
  RooRealVar *TisAll = new RooRealVar("TisAll","BDT calib events normalization",16734,1000,100000);
  TisAll->setConstant(kTRUE);

  //epsilon-double_misID =  (7.5+/-0.5) *10^-5


  //BhhMisID_DLL = EVal(1.52e-5,[0.07e-5,0.07e-5]) # Jose/Fatima 240112
  //BhhMisID_DLL_factors = [1.04,1.07,1.06,1.07,1.04,0.95,0.87,0.81] # Jose/Fatima 240112

  RooRealVar *douMis = new RooRealVar("douMis","double misid eff",0.0000152,0.0,0.0001);
  douMis->setConstant(kTRUE);

  /*
    J2 = 0.9219;
    J3 = 0.9212;
    J4 = 1.0080;
    J5 = 1.0402;
    J6 = 1.0715;
    J7 = 1.0851;  
    J8 = 1.0979;  
  */
  
  //Justine factors are only used 'normalized'
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

  //Number of combinatorial Bkg evts
  RooRealVar* NBd = new RooRealVar ("N_{Bd}","Total number Bd",1.,0,1000);
  RooRealVar* NBs = new RooRealVar ("N_{Bs}","Total number Bs",1.,0,1000);
  //5.2 in full range. 

  //N_double_misID=    TisTOT/ Jave*epsilon_double_misID
  //  RooFormulaVar* N_Mis = new RooFormulaVar ("N_{mis}","Total number Misid","(@0/@1)*(@2)",RooArgList(*TisAll,*Jall,*douMis));
  
  //Bd CB shape parameters
  RooRealVar *mbd;
  RooRealVar *mbs;
  if(doData) {
    mbd = new RooRealVar("m_{Bd}","mbd",5284.6,5260,5300,"MeV/c^{2}");
    mbs = new RooRealVar("m_{Bs}","mbs",5373.,5350,5390,"MeV/c^{2}");
  } else {
    mbd = new RooRealVar("m_{Bd}","mbd",5278.,5260,5300,"MeV/c^{2}");
    mbs = new RooRealVar("m_{Bs}","mbs",5369.,5350,5390,"MeV/c^{2}");
  }

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
  RooRealVar *tauBg  = new RooRealVar("tk_{1}","Tau of bg mass dist",-0.000767864,-0.02,0.0,"");         

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

  TTree *RootTree = new TTree("ProfileTree","Profile 2D results");
  double t_nbs, t_nbd, t_nll;
  double e_tbkg, t_tbkg;
  double e_nbkg_2, t_nbkg_2, e_nbkg_3, t_nbkg_3, e_nbkg_4, t_nbkg_4;
  double e_nbkg_5, t_nbkg_5, e_nbkg_6, t_nbkg_6, e_nbkg_7, t_nbkg_7, e_nbkg_8, t_nbkg_8;
  RootTree->Branch("nbs",&t_nbs,"nbs/D");
  RootTree->Branch("nbd",&t_nbd,"nbd/D");
  RootTree->Branch("nll",&t_nll,"nll/D");
  RootTree->Branch("tbkg",&t_tbkg,"tbkg/D");
  RootTree->Branch("e_tbkg",&e_tbkg,"e_tbkg/D");
  RootTree->Branch("nbkg_2",&t_nbkg_2,"nbkg_2/D");
  RootTree->Branch("e_nbkg_2",&e_nbkg_2,"e_nbkg_2/D");
  RootTree->Branch("nbkg_3",&t_nbkg_3,"nbkg_3/D");
  RootTree->Branch("e_nbkg_3",&e_nbkg_3,"e_nbkg_3/D");
  RootTree->Branch("nbkg_4",&t_nbkg_4,"nbkg_4/D");
  RootTree->Branch("e_nbkg_4",&e_nbkg_4,"e_nbkg_4/D");
  RootTree->Branch("nbkg_5",&t_nbkg_5,"nbkg_5/D");
  RootTree->Branch("e_nbkg_5",&e_nbkg_5,"e_nbkg_5/D");
  RootTree->Branch("nbkg_6",&t_nbkg_6,"nbkg_6/D");
  RootTree->Branch("e_nbkg_6",&e_nbkg_6,"e_nbkg_6/D");
  RootTree->Branch("nbkg_7",&t_nbkg_7,"nbkg_7/D");
  RootTree->Branch("e_nbkg_7",&e_nbkg_7,"e_nbkg_7/D");
  RootTree->Branch("nbkg_8",&t_nbkg_8,"nbkg_8/D");
  RootTree->Branch("e_nbkg_8",&e_nbkg_8,"e_nbkg_8/D");

  char name[200];
  RooWorkspace *w;
  RooFitResult * res;
  RooNLLVar *nll2, *nll3, *nll4, *nll5, *nll6, *nll7, *nll8;
  RooMinuit *m1;
  //    RooArgList myVals;
  double pr_bdmin, pr_bsmin, pr_bd_step, pr_bs_step;
  TLatex *lhcbLatex;

  double mbd_p(1.), s_mbd_p(1.);
  double mbs_p(1.), s_mbs_p(1.);
  double mbdw_p(1.), s_mbdw_p(1.);
  double mbsw_p(1.), s_mbsw_p(1.);

  vector<string> sum;

  if(doSyst) {
    doToy = kFALSE;
    doScan = kFALSE;
    doProf = kFALSE;
    doProfileTD = kFALSE;
  }

  for(int sysi=0; sysi<maxsys; sysi++) {
    cout<<sysi<<endl;

    /*
      Final PDF is created as a sum of all the PDFs listed in the 'pdfs' RooArgList object
    */


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
    


    RooAbsPdf* pdf_fit_2 = CreatePdfForABin(2, sysi, fr2, mass, NBd, NBs, misfr2, mbd, mbs, mbdw, mbsw, tauBg, h_misid, doSyst);
    if(addPrio) sum.push_back("@0");
    RooAbsPdf* pdf_fit_3 = CreatePdfForABin(3, sysi, fr3, mass, NBd, NBs, misfr3, mbd, mbs, mbdw, mbsw, tauBg, h_misid, doSyst);
    if(addPrio) sum.push_back("+@1");
    RooAbsPdf* pdf_fit_4 = CreatePdfForABin(4, sysi, fr4, mass, NBd, NBs, misfr4, mbd, mbs, mbdw, mbsw, tauBg, h_misid, doSyst);
    if(addPrio) sum.push_back("+@2");
    RooAbsPdf* pdf_fit_5 = CreatePdfForABin(5, sysi, fr5, mass, NBd, NBs, misfr5, mbd, mbs, mbdw, mbsw, tauBg, h_misid, doSyst);
    if(addPrio) sum.push_back("+@3");
    RooAbsPdf* pdf_fit_6 = CreatePdfForABin(6, sysi, fr6, mass, NBd, NBs, misfr6, mbd, mbs, mbdw, mbsw, tauBg, h_misid, doSyst);
    if(addPrio) sum.push_back("+@4");
    RooAbsPdf* pdf_fit_7 = CreatePdfForABin(7, sysi, fr7, mass, NBd, NBs, misfr7, mbd, mbs, mbdw, mbsw, tauBg, h_misid, doSyst);
    if(addPrio) sum.push_back("+@5");
    RooAbsPdf* pdf_fit_8 = CreatePdfForABin(8, sysi, fr8, mass, NBd, NBs, misfr8, mbd, mbs, mbdw, mbsw, tauBg, h_misid, doSyst);
    if(addPrio) sum.push_back("+@6");

    if(addPrio) sum.push_back("+@7");



    if(addPrio) {

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

      RooRealVar* TisMean_2  = new RooRealVar("TisMean_2","mean ",1877);
      RooRealVar* TisSigma_2 = new RooRealVar("TisSigma_2","sigma ",242);
      // Prior paramter definition 
      sprintf(name,"TisPrior_2");
      RooFormulaVar * TisPrior_2 = new RooFormulaVar(name,"prior",
						     "0.5*(@0-@1)**2/@2**2",
						     RooArgList(*Tis2,*TisMean_2,*TisSigma_2));
      terms.add(*TisPrior_2); 
      
      RooRealVar* TisMean_3  = new RooRealVar("TisMean_3","mean ",1486);
      RooRealVar* TisSigma_3 = new RooRealVar("TisSigma_3","sigma ",158);
      // Prior paramter definition 
      sprintf(name,"TisPrior_3");
      RooFormulaVar * TisPrior_3 = new RooFormulaVar(name,"prior",
						     "0.5*(@0-@1)**2/@2**2",
						     RooArgList(*Tis3,*TisMean_3,*TisSigma_3));
      terms.add(*TisPrior_3); 
      
      RooRealVar* TisMean_4  = new RooRealVar("TisMean_4","mean ",1447);
      RooRealVar* TisSigma_4 = new RooRealVar("TisSigma_4","sigma ",89);
      // Prior paramter definition 
      sprintf(name,"TisPrior_4");
      RooFormulaVar * TisPrior_4 = new RooFormulaVar(name,"prior",
						     "0.5*(@0-@1)**2/@2**2",
						     RooArgList(*Tis4,*TisMean_4,*TisSigma_4));
      terms.add(*TisPrior_4); 
      
      RooRealVar* TisMean_5  = new RooRealVar("TisMean_5","mean ",1729);
      RooRealVar* TisSigma_5 = new RooRealVar("TisSigma_5","sigma ",100);
      // Prior paramter definition 
      sprintf(name,"TisPrior_5");
      RooFormulaVar * TisPrior_5 = new RooFormulaVar(name,"prior",
						     "0.5*(@0-@1)**2/@2**2",
						     RooArgList(*Tis5,*TisMean_5,*TisSigma_5));
      terms.add(*TisPrior_5); 
      
      RooRealVar* TisMean_6  = new RooRealVar("TisMean_6","mean ",1846);
      RooRealVar* TisSigma_6 = new RooRealVar("TisSigma_6","sigma ",69);
      // Prior paramter definition 
      sprintf(name,"TisPrior_6");
      RooFormulaVar * TisPrior_6 = new RooFormulaVar(name,"prior",
						     "0.5*(@0-@1)**2/@2**2",
						     RooArgList(*Tis6,*TisMean_6,*TisSigma_6));
      terms.add(*TisPrior_6); 
      
      RooRealVar* TisMean_7  = new RooRealVar("TisMean_7","mean ",2133);
      RooRealVar* TisSigma_7 = new RooRealVar("TisSigma_7","sigma ",107);
      // Prior paramter definition 
      sprintf(name,"TisPrior_7");
      RooFormulaVar * TisPrior_7 = new RooFormulaVar(name,"prior",
						     "0.5*(@0-@1)**2/@2**2",
						     RooArgList(*Tis7,*TisMean_7,*TisSigma_7));
      terms.add(*TisPrior_7); 
      
      RooRealVar* TisMean_8  = new RooRealVar("TisMean_8","mean ",2245);
      RooRealVar* TisSigma_8 = new RooRealVar("TisSigma_8","sigma ",327);
      // Prior paramter definition 
      sprintf(name,"TisPrior_8");
      RooFormulaVar * TisPrior_8 = new RooFormulaVar(name,"prior",
						     "0.5*(@0-@1)**2/@2**2",
						     RooArgList(*Tis8,*TisMean_8,*TisSigma_8));
      terms.add(*TisPrior_8); 
      
      RooRealVar* TisMean_All  = new RooRealVar("TisMean_All","mean ",16734);
      RooRealVar* TisSigma_All = new RooRealVar("TisSigma_All","sigma ",1312);
      // Prior paramter definition 
      sprintf(name,"TisPrior_All");
      RooFormulaVar * TisPrior_All = new RooFormulaVar(name,"prior",
						     "0.5*(@0-@1)**2/@2**2",
						     RooArgList(*TisAll,*TisMean_All,*TisSigma_All));
      terms.add(*TisPrior_All); 
      
      Tis2->setConstant(kFALSE);
      Tis3->setConstant(kFALSE);
      Tis4->setConstant(kFALSE);
      Tis5->setConstant(kFALSE);
      Tis6->setConstant(kFALSE);
      Tis7->setConstant(kFALSE);
      Tis8->setConstant(kFALSE);
      TisAll->setConstant(kFALSE);
    }

    /*
      Data Set Is Loaded from the file: Paper is bdtx!
    */

    //Write File Result
    sprintf(hn,"RootOutp_MCAll_%s.root",flag.data());   
    if(doSyst)  sprintf(hn,"RootOutp_MCAll_%s_Sys%d.root",flag.data(),sysi);   
    cout<<"Going to write file :: "<<hn<<endl;

    mbs->setConstant(kTRUE);
    mbd->setConstant(kTRUE);

    mbsw->setConstant(kTRUE);
    mbdw->setConstant(kTRUE);
  
    //    bdalpha->setConstant(kTRUE);
    //    bsalpha->setConstant(kTRUE);
  
    //    bdn->setConstant(kTRUE);
    //    bsn->setConstant(kTRUE);

    sprintf(pdfnm,"w");
    if(doSyst) sprintf(pdfnm,"w_%d",sysi);
    w = new RooWorkspace(pdfnm,"workspace");
    //    w->import(*pdf_fit_1);
    //    w->import(*pdf_fit_2,RenameConflictNodes("2"));
    w->import(*pdf_fit_2);
    w->import(*pdf_fit_3);
    w->import(*pdf_fit_4);
    w->import(*pdf_fit_5);
    w->import(*pdf_fit_6);
    w->import(*pdf_fit_7);
    w->import(*pdf_fit_8);
  
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
    if(doSyst) sprintf(pdfnm,"mydata1_%d",sysi);
    data1->SetName(pdfnm);
    w->import(*data1);
    
    sprintf(pdfnm,"mydata2");
    if(doSyst) sprintf(pdfnm,"mydata2_%d",sysi);
    data2->SetName(pdfnm);
    w->import(*data2);
    
    sprintf(pdfnm,"mydata3");
    if(doSyst) sprintf(pdfnm,"mydata3_%d",sysi);
    data3->SetName(pdfnm);
    w->import(*data3);
    
    sprintf(pdfnm,"mydata4");
    if(doSyst) sprintf(pdfnm,"mydata4_%d",sysi);
    data4->SetName(pdfnm);
    w->import(*data4);
    
    sprintf(pdfnm,"mydata5");
    if(doSyst) sprintf(pdfnm,"mydata5_%d",sysi);
    data5->SetName(pdfnm);
    w->import(*data5);
    
    sprintf(pdfnm,"mydata6");
    if(doSyst) sprintf(pdfnm,"mydata6_%d",sysi);
    data6->SetName(pdfnm);
    w->import(*data6);
    
    sprintf(pdfnm,"mydata7");
    if(doSyst) sprintf(pdfnm,"mydata7_%d",sysi);
    data7->SetName(pdfnm);
    w->import(*data7);
    
    sprintf(pdfnm,"mydata8");
    if(doSyst) sprintf(pdfnm,"mydata8_%d",sysi);
    data8->SetName(pdfnm);
    w->import(*data8);
    
    
    /*********************************************/
    //     Fitting Parameters are defined
    /*********************************************/
    
    gRandom->SetSeed(3123);
    
    /*
      FIT
    */
    NBd->setVal(1.);
    NBs->setVal(1.);
    
    my_Nbkg.at(0)->setVal(108);
    my_Nbkg.at(1)->setVal(18);
    my_Nbkg.at(2)->setVal(5);
    my_Nbkg.at(3)->setVal(5);
    my_Nbkg.at(4)->setVal(5);
    my_Nbkg.at(5)->setVal(5);
    my_Nbkg.at(6)->setVal(5);
    
    tauBg->setVal(-0.001134);
    
    
    //  RooNLLVar *nll = new RooNLLVar("nll","-log(L)",*pdf_fit,*data,Extended(true),EvalErrorWall(kFALSE));
    sprintf(pdfnm,"nll");
    if(doSyst) sprintf(pdfnm,"nll_%d",sysi);
    //    nll1 = new RooNLLVar("nll1","-log(L)",*pdf_fit_1,*data1,Extended(true));
    nll2 = new RooNLLVar("nll2","-log(L)",*pdf_fit_2,*data2,Extended(true));
    nll3 = new RooNLLVar("nll3","-log(L)",*pdf_fit_3,*data3,Extended(true));
    nll4 = new RooNLLVar("nll4","-log(L)",*pdf_fit_4,*data4,Extended(true));
    nll5 = new RooNLLVar("nll5","-log(L)",*pdf_fit_5,*data5,Extended(true));
    nll6 = new RooNLLVar("nll6","-log(L)",*pdf_fit_6,*data6,Extended(true));
    nll7 = new RooNLLVar("nll7","-log(L)",*pdf_fit_7,*data7,Extended(true));
    nll8 = new RooNLLVar("nll8","-log(L)",*pdf_fit_8,*data8,Extended(true));

    if(doData) {
      mbd_p = 5284.6;  s_mbd_p = 0.3;
      mbs_p = 5373.;  s_mbs_p = 0.4;
      mbdw_p = 24.2;  s_mbdw_p = 0.6;
      mbsw_p = 24.8;  s_mbsw_p = 0.6;
    } else {
      mbd_p = 5278.;  s_mbd_p = 1.;
      mbs_p = 5369.;  s_mbs_p = 1.;
      mbdw_p = 24.3;  s_mbdw_p = 1.;
      mbsw_p = 24.6;  s_mbsw_p = 1.;
    }

    terms.add(*nll2); 
    terms.add(*nll3); 
    terms.add(*nll4); 
    terms.add(*nll5); 
    terms.add(*nll6); 
    terms.add(*nll7); 
    terms.add(*nll8); 
    if(addPrio) {
      sum.push_back("+@8");
      sum.push_back("+@9");
      sum.push_back("+@10");
      sum.push_back("+@11");
      sum.push_back("+@12");
      sum.push_back("+@13");
      sum.push_back("+@14");
    } else {
      sum.push_back("@0");
      sum.push_back("+@1");
      sum.push_back("+@2");
      sum.push_back("+@3");
      sum.push_back("+@4");
      sum.push_back("+@5");
      sum.push_back("+@6");
    }


    //  RooRealVar * offset = new RooRealVar("offset","offset",0);
    //  *offset = nll->getVal()+0.1;
    if(addPrio) {
      RooRealVar* mbdMean  = new RooRealVar("mbdMean","mean (prior)",mbd_p);
      RooRealVar* mbdSigma = new RooRealVar("mbdSigma","sigma (prior)",s_mbd_p);
      
      // Prior paramter definition 
      RooFormulaVar * mbdPrior = new RooFormulaVar("mbdPrior","prior",
						   "0.5*(@0-@1)**2/@2**2",
						   RooArgList(*mbd,*mbdMean,*mbdSigma));

      terms.add(*mbdPrior); sum.push_back("+@15");
      mbd->setConstant(kFALSE);

      RooRealVar* mbsMean  = new RooRealVar("mbsMean","mean (prior)",mbs_p);
      RooRealVar* mbsSigma = new RooRealVar("mbsSigma","sigma (prior)",s_mbs_p);
      
      // Prior paramter definition 
      RooFormulaVar * mbsPrior = new RooFormulaVar("mbsPrior","prior",
						   "0.5*(@0-@1)**2/@2**2",
						   RooArgList(*mbs,*mbsMean,*mbsSigma));

      terms.add(*mbsPrior); sum.push_back("+@16");
      mbs->setConstant(kFALSE);

      RooRealVar* mbdwMean  = new RooRealVar("mbdwMean","mean (prior)",mbdw_p);
      RooRealVar* mbdwSigma = new RooRealVar("mbdwSigma","sigma (prior)",s_mbdw_p);
      
      // Prior paramter definition 
      RooFormulaVar * mbdwPrior = new RooFormulaVar("mbdwPrior","prior",
						   "0.5*(@0-@1)**2/@2**2",
						   RooArgList(*mbdw,*mbdwMean,*mbdwSigma));

      terms.add(*mbdwPrior); sum.push_back("+@17");
      mbdw->setConstant(kFALSE);

      RooRealVar* mbswMean  = new RooRealVar("mbswMean","mean (prior)",mbsw_p);
      RooRealVar* mbswSigma = new RooRealVar("mbswSigma","sigma (prior)",s_mbsw_p);
      
      // Prior paramter definition 
      RooFormulaVar * mbswPrior = new RooFormulaVar("mbswPrior","prior",
						   "0.5*(@0-@1)**2/@2**2",
						   RooArgList(*mbsw,*mbswMean,*mbswSigma));

      terms.add(*mbswPrior); sum.push_back("+@18");
      mbsw->setConstant(kFALSE);


      //BhhMisID_DLL = EVal(1.52e-5,[0.07e-5,0.07e-5]) # Jose/Fatima 240112
      RooRealVar* doueMean  = new RooRealVar("doueMean","mean (prior)",0.0000152);
      RooRealVar* doueSigma = new RooRealVar("doueSigma","sigma (prior)",0.000001);
      
      // Prior paramter definition 
      RooFormulaVar * douePrior = new RooFormulaVar("douePrior","prior",
						    "0.5*(@0-@1)**2/@2**2",
						    RooArgList(*douMis,*doueMean,*doueSigma));

      terms.add(*douePrior); sum.push_back("+@19");
      douMis->setConstant(kFALSE);
    }
    string mysum = "";
    for(int i=0; i<sum.size(); i++){
      mysum += sum.at(i);
    }
    cout<<"Summing terms:: "<<mysum.data()<<endl;

    RooFormulaVar * L = new RooFormulaVar("L",mysum.data(),terms);
    
    if(doProfileTD) {
      pr_bd_step = 0.4;
      pr_bs_step = 0.4;
      pr_bdmin = 0.;
      pr_bsmin = 0.;
      maxbd = (pr_bdmax-pr_bdmin)/pr_bd_step;
      maxbs = (pr_bsmax-pr_bsmin)/pr_bs_step;
    }
    
    
    m1 = new RooMinuit(*L);
    
    m1->setVerbose(kTRUE) ;    
    m1->setLogFile("FitLog.txt");  
    m1->setProfile(1);
    m1->setPrintLevel(3);    m1->setStrategy(2);
    
    res = m1->save();
    res->Print("v") ; 
    //    doFit = kTRUE;
    if(doFit) {
      m1->minos() ;
      m1->migrad() ;
    }
    res = m1->save();
    
    if(doSyst) {
      t_nll = L->getVal();
      t_nbd = NBd->getVal();
      t_nbs = NBs->getVal();
      t_tbkg = tauBg->getVal();
      e_tbkg = tauBg->getError();
      
      RootTree->Fill();
    }
    
    RooArgList myVals  = res->floatParsFinal(); 
    cout<<" My final L value:: "<<L->getVal()<<endl;
        
    res->Print("v") ; 
    res->Print() ; 
    
    
    // Extract covariance and correlation matrix as TMatrixDSym
    const TMatrixDSym& cor = res->correlationMatrix() ;
    const TMatrixDSym& cov = res->covarianceMatrix() ;
    
    // Print correlation, covariance matrix
    cout << "correlation matrix" << endl ;
    cor.Print() ;
    cout << "covariance matrix" << endl ;
    cov.Print() ;
    
    
    if(res) res->Write();
    
    /*************************************************/
    //          Produce some control plots
    /*************************************************/
    
    lhcbLatex = new TLatex(0.18, 0.83,"#splitline{#splitline{LHCb}{Preliminary}}{#scale[0.7]{#sqrt{s} = 7 TeV Data}}");
            
    //    ExpPlot(mass, data1, pdf_fit_1, doSyst, sysi, "Mass_Distribution", flag, kFALSE ,"mydata1", "pdf_fit_1", 1);

    //    ExpPlot(mass, data1, pdf_fit_1, doSyst, sysi, "Mass_Distribution_log", flag, kTRUE ,"mydata1", "pdf_fit_1", 1);    

    ExpPlot(mass, data2, pdf_fit_2, doSyst, sysi, "Mass_Distribution", flag, kFALSE ,"mydata2", "pdf_fit_2", 2);

    ExpPlot(mass, data2, pdf_fit_2, doSyst, sysi, "Mass_Distribution_log", flag, kTRUE ,"mydata2", "pdf_fit_2", 2);    

    ExpPlot(mass, data3, pdf_fit_3, doSyst, sysi, "Mass_Distribution", flag, kFALSE ,"mydata3", "pdf_fit_3", 3);

    ExpPlot(mass, data3, pdf_fit_3, doSyst, sysi, "Mass_Distribution_log", flag, kTRUE ,"mydata3", "pdf_fit_3", 3);    

    ExpPlot(mass, data4, pdf_fit_4, doSyst, sysi, "Mass_Distribution", flag, kFALSE ,"mydata4", "pdf_fit_4", 4);

    ExpPlot(mass, data4, pdf_fit_4, doSyst, sysi, "Mass_Distribution_log", flag, kTRUE ,"mydata4", "pdf_fit_4", 4);    

    ExpPlot(mass, data5, pdf_fit_5, doSyst, sysi, "Mass_Distribution", flag, kFALSE ,"mydata5", "pdf_fit_5", 5);

    ExpPlot(mass, data5, pdf_fit_5, doSyst, sysi, "Mass_Distribution_log", flag, kTRUE ,"mydata5", "pdf_fit_5", 5);    

    ExpPlot(mass, data6, pdf_fit_6, doSyst, sysi, "Mass_Distribution", flag, kFALSE ,"mydata6", "pdf_fit_6", 6);

    ExpPlot(mass, data6, pdf_fit_6, doSyst, sysi, "Mass_Distribution_log", flag, kTRUE ,"mydata6", "pdf_fit_6", 6);    

    ExpPlot(mass, data7, pdf_fit_7, doSyst, sysi, "Mass_Distribution", flag, kFALSE ,"mydata7", "pdf_fit_7", 7);

    ExpPlot(mass, data7, pdf_fit_7, doSyst, sysi, "Mass_Distribution_log", flag, kTRUE ,"mydata7", "pdf_fit_7", 7);    

    ExpPlot(mass, data8, pdf_fit_8, doSyst, sysi, "Mass_Distribution", flag, kFALSE ,"mydata8", "pdf_fit_8", 8);

    ExpPlot(mass, data8, pdf_fit_8, doSyst, sysi, "Mass_Distribution_log", flag, kTRUE ,"mydata8", "pdf_fit_8", 8);    

    cout<<"Performing scan in the range from 0,0 to "<<maxbs<<","<<maxbd<<endl;

    for(int ibs=0; ibs<maxbs; ibs++){
      for(int ibd=0; ibd<maxbd; ibd++){

	//Second step or greater
	//a) save reference params from fit 0,0 
	//b) reinitialize fit params to default
	//c) initialize - fix params to scanned values
	NBd->setVal(pr_bdmin+ibd*pr_bd_step);
	NBs->setVal(pr_bsmin+ibs*pr_bs_step);
	
	NBd->setConstant(kTRUE);
	NBs->setConstant(kTRUE);

	my_Nbkg.at(0)->setVal(108);
	my_Nbkg.at(1)->setVal(18);
	my_Nbkg.at(2)->setVal(5);
	my_Nbkg.at(3)->setVal(5);
	my_Nbkg.at(4)->setVal(5);
	my_Nbkg.at(5)->setVal(5);
	my_Nbkg.at(6)->setVal(5);

	tauBg->setVal(-0.001134);

	m1 = new RooMinuit(*L);
	
	m1->setVerbose(kTRUE) ;    
	m1->setLogFile("FitLog.txt");  
	m1->setProfile(1);
	m1->setPrintLevel(3);    m1->setStrategy(2);
	
	//	res = m1->save();
	//	res->Print("v") ; 
	if(doFit) {
	  m1->minos() ;
	  m1->migrad() ;
	}
	//	res = m1->save();

	//	myVals  = res->floatParsFinal(); 
	//	cout << "fit result on NLL" << endl ;
	//	res->Print("v") ; 
	//	res->Print() ; 
	
	t_nll = L->getVal();
	t_nbd = NBd->getVal();
	t_nbs = NBs->getVal();
	t_tbkg = tauBg->getVal();
	e_tbkg = tauBg->getError();

	t_nbkg_2 = my_Nbkg.at(0)->getVal();
	e_nbkg_2 = my_Nbkg.at(0)->getError();
	t_nbkg_3 = my_Nbkg.at(1)->getVal();
	e_nbkg_3 = my_Nbkg.at(1)->getError();
	t_nbkg_4 = my_Nbkg.at(2)->getVal();
	e_nbkg_4 = my_Nbkg.at(2)->getError();
	t_nbkg_5 = my_Nbkg.at(3)->getVal();
	e_nbkg_5 = my_Nbkg.at(3)->getError();
	t_nbkg_6 = my_Nbkg.at(4)->getVal();
	e_nbkg_6 = my_Nbkg.at(4)->getError();
	t_nbkg_7 = my_Nbkg.at(5)->getVal();
	e_nbkg_7 = my_Nbkg.at(5)->getError();
	t_nbkg_8 = my_Nbkg.at(6)->getVal();
	e_nbkg_8 = my_Nbkg.at(6)->getError();

	RootTree->Fill();

	cout<<"Resi:: "<<ibd<<" "<<ibs<<" "<<L->getVal()<<" "<<NBd->getVal()<<" "<<NBs->getVal()<<endl;
	m1->cleanup();
	delete m1;
      }

    }

  }
  RootTree->Write();
  f.Close();

  sprintf(hn,"RootWorksp_MCAll_%s.root",flag.data());   
  w->writeToFile(hn) ;

  return 0;
}


void ExpPlot(RooRealVar *abdt, RooDataSet *adt, RooAbsPdf *apdf, bool syst, int sys_id, string anm, string flg, bool log, string dname, string pname, int bin) {

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



RooAbsPdf* CreatePdfForABin(int bin, int sysi, RooFormulaVar* fr, RooRealVar* m, RooRealVar* nbd, RooRealVar* nbs, RooFormulaVar* nmis, RooRealVar *mbd, RooRealVar *mbs, RooRealVar *wmbd, RooRealVar *wmbs, RooRealVar *tau, TH1D *hmis, bool sys) {

  char name[200]; RooAbsPdf *fit;
  int bkg_in[4] = {10000,108,18,1};

  //  sprintf(name,"#sigma_{Bd}_%d",bin);
  //  RooRealVar *mbdw   = new RooRealVar(name,"Bs mass resolution",24.3,10,150,"MeV/c^{2}");
  //  mbdw->setConstant(kTRUE);
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

  sprintf(name,"cb_bd_%d",bin);
  RooAbsPdf* cb_bd =  new RooCBShape(name,"Bd Mass signal PDF",*m,*mbd,*wmbd,*bdalpha,*bdn);
  sprintf(name,"Nb_%d",bin);
  RooFormulaVar *Nb = new RooFormulaVar(name,"signal in first bin","@0*@1",RooArgList(*nbd,*fr));
  sprintf(name,"sig_bd_mass_%d",bin);
  RooExtendPdf *sig_bd_mass = new RooExtendPdf(name,"Signal ext mass PDF Bd",*cb_bd,*Nb);

  sprintf(name,"cb_bs_%d",bin);
  RooAbsPdf* cb_bs =  new RooCBShape(name,"Bs Mass signal PDF",*m,*mbs,*wmbs,*bsalpha,*bsn);
  sprintf(name,"Ns_%d",bin);
  RooFormulaVar *Ns = new RooFormulaVar(name,"signal in first bin","@0*@1",RooArgList(*nbs,*fr));
  sprintf(name,"sig_bs_mass_%d",bin);
  RooExtendPdf *sig_bs_mass = new RooExtendPdf(name,"Signal ext mass PDF Bs",*cb_bs,*Ns);

  sprintf(name,"mpdfs_%d",bin);
  RooArgSet *mpdfs = new RooArgSet(name);
  mpdfs->add(*sig_bs_mass);
  mpdfs->add(*sig_bd_mass);  

  sprintf(name,"sig_mass_%d",bin);
  RooAbsPdf *sig_mass = new RooAddPdf(name,"Sum of ext CB of Bd and Bs",RooArgSet(*mpdfs));


  //Mass PDF
  //  sprintf(name,"tk_%d",bin);
  //  RooRealVar *tauBg  = new RooRealVar(name,"Tau of bg mass dist",-0.000767864,-1,0,"");         
  sprintf(name,"pdf_Bkg_%d",bin);
  RooAbsPdf* pdf_Bkg =  new RooExponential(name,"massBackgroundPdf",*m,*tau);

  sprintf(name,"N_comb_%d",bin);
  RooRealVar* N_Bkg = new RooRealVar (name,"Total number Bkg",15558,0,1000000);
  my_Nbkg.push_back(N_Bkg);

  sprintf(name,"bkg_mass_%d",bin);
  N_Bkg->setVal(bkg_in[bin-1]);

  RooAbsPdf* bkg_mass = new RooExtendPdf(name,"extended background p.d.f",*pdf_Bkg,*N_Bkg) ;

  /* Peaking Background PDF: RooHist */
  sprintf(name,"data_misid_%d",bin);
  RooDataHist* data_misid= new RooDataHist(name,"mass*BDT",*m,hmis);

  sprintf(name,"m_misid_pdf_%d",bin);
  RooAbsPdf *m_misid_pdf =  new RooHistPdf(name,"Misid PDF",*m,*data_misid);

  sprintf(name,"mass_misid_%d",bin);
  RooAbsPdf* mass_misid = new RooExtendPdf(name,"extended misid p.d.f",*m_misid_pdf,*nmis) ;
  
  //PDF1
  sprintf(name,"pdfs_%d",bin);
  if(sys) sprintf(name,"pdfs_%d_%d",bin,sysi);
  RooArgSet* pdfs = new RooArgSet(name);
  pdfs->add(*sig_mass);              //pdfs->add(*glob_pdf_sig);  
  pdfs->add(*bkg_mass);  	     //pdfs->add(*glob_pdf_bkg);  
  pdfs->add(*mass_misid);            //pdfs->add(*glob_pdf_misid);
  
  
  sprintf(name,"pdf_fit_%d",bin);
  if(sys) sprintf(name,"pdf_fit_%d_%d",bin,sysi);
  fit = new RooAddPdf(name,"Total(B+S) Bs -> mu+ mu- PDF",RooArgSet(*pdfs));
  
  fit->Print("v");
  fit->printCompactTree();

  return fit;

}
