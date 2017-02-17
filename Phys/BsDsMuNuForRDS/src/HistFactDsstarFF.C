#include <iostream>
#include <stdio.h>

#include "TRandom3.h"
#include "TCanvas.h"
#include "TDatime.h"
#include "TStopwatch.h"
#include "TLegend.h"
#include "TIterator.h"
#include "TH2.h"
#include "TLatex.h"

#include "RooChi2Var.h"
#include "RooAbsData.h"
#include "RooRealSumPdf.h"
#include "RooPoisson.h"
#include "RooGaussian.h"
#include "RooRealVar.h"
#include "RooMCStudy.h"
#include "RooMinuit.h"
#include "RooCategory.h"
#include "RooHistPdf.h"
#include "RooSimultaneous.h"
#include "RooExtendPdf.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooFitResult.h"
#include "RooMsgService.h"
#include "RooParamHistFunc.h"
#include "RooHist.h"
#include "RooRandom.h"

#include "RooStats/ModelConfig.h"
#include "RooStats/ToyMCSampler.h"
#include "RooStats/MinNLLTestStat.h"

#include "RooStats/HistFactory/FlexibleInterpVar.h"
#include "RooStats/HistFactory/PiecewiseInterpolation.h"
#include "RooStats/HistFactory/HistFactorySimultaneous.h"
#include "RooStats/HistFactory/Channel.h"
#include "RooStats/HistFactory/MakeModelAndMeasurementsFast.h"
#include "RooStats/HistFactory/Measurement.h"
#include "RooStats/HistFactory/ParamHistFunc.h"
#include "RooStats/HistFactory/HistFactoryModelUtils.h"
#include "RooStats/HistFactory/RooBarlowBeestonLL.h"

//#define UNBLIND

TDatime *date = new TDatime();

void HistFactDsstarFF() {
  TLatex *t=new TLatex();
  t->SetTextAlign(22);
  t->SetTextSize(0.06);
  t->SetTextFont(132);
  gROOT->ProcessLine("gStyle->SetLabelFont(132,\"xyz\");");
  gROOT->ProcessLine("gStyle->SetTitleFont(132,\"xyz\");");
  gROOT->ProcessLine("gStyle->SetTitleFont(132,\"t\");");
  gROOT->ProcessLine("gStyle->SetTitleSize(0.08,\"t\");");
  gROOT->ProcessLine("gStyle->SetTitleY(0.970);");
  char substr[128];
  RooRandom::randomGenerator()->SetSeed(date->Get()%100000);
  cout << date->Get()%100000 << endl; //For ToyMC, so I can run multiple copies 
                                      //with different seeds without recompiling

  RooMsgService::instance().setGlobalKillBelow(RooFit::WARNING) ; //avoid accidental unblinding!

  // Below: Read histogram file to generate normalization constants required to make
  // each histo normalized to unity. Not totally necessary here, but convenient
  // need to open all of them
  TFile q1("../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCutSignal_Bs0DstaMu_Weight.root");
  TFile q2("../Templates/output/RootOutp_MCAll_bin0_TauNorBIsoPIDCutSignal_Bs0DstaTau_Weight.root");
  TFile q3("../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCutBdDstDs_Weight.root");
  TFile q4("../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCut_SameSign_Weight.root");
  TFile q5("../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCutLbLcDs_Weight.root");
  TFile q6("../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCutBsDsDs_Weight.root");
  TFile q7("../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCutBuD0Ds_Weight.root");
  TH1 *htemp1, *htemp2, *htemp3, *htemp4, *htemp5, *htemp6, *htemp7;
  double mcN_sigmu,mcN_tau,mcN_BdDD,mcN_BsDD,mcN_BuDD,mcN_LbDD,mcN_misID;
  q1.GetObject("histoMassQsq",htemp1);
  assert(htemp1!=NULL);
  mcN_sigmu=1./htemp1->Integral();
  cout << "mcN_sig = " << 1./mcN_sigmu << endl;
  q2.GetObject("histoMassQsq",htemp2);
  assert(htemp2!=NULL);
  mcN_tau=1./htemp2->Integral();
  cout << "mcN_tau = " << 1./mcN_tau << endl; 
  q3.GetObject("histoMassQsq",htemp3);
  assert(htemp3!=NULL);
  mcN_BdDD=1./htemp3->Integral();
  cout << "mcN_BdDD = " << 1./mcN_BdDD << endl;  
  q4.GetObject("histoMassQsq",htemp4);
  assert(htemp4!=NULL);
  mcN_misID=1./htemp4->Integral();
  cout << "mcN_misID = " << 1./mcN_misID << endl;
  q5.GetObject("histoMassQsq",htemp5);
  assert(htemp5!=NULL);
  mcN_LbDD=1./htemp5->Integral();
  cout << "mcN_LbDD = " << 1./mcN_LbDD << endl;
  q6.GetObject("histoMassQsq",htemp6);
  assert(htemp6!=NULL);
  mcN_BsDD=1./htemp6->Integral();
  cout << "mcN_BsDD = " << 1./mcN_BsDD << endl;
  q7.GetObject("histoMassQsq",htemp7);
  assert(htemp7!=NULL);
  mcN_BuDD=1./htemp7->Integral();
  cout << "mcN_BuDD = " << 1./mcN_BuDD << endl;

  // Useful later to have the bin max and min for drawing
  TH2 *JUNK;
  q1.GetObject("histoMassQsq",JUNK);
  double q2_low=JUNK->GetYaxis()->GetXmin();
  double q2_high=JUNK->GetYaxis()->GetXmax();
  const int q2_bins = JUNK->GetYaxis()->GetNbins();
  std::cout << q2_low << ", " << q2_high << ", " << q2_bins << std::endl; 
  JUNK->SetDirectory(0);
  q1.Close();

  TStopwatch sw, sw2;
  
  TRandom *r3 = new TRandom3(date->Get());

  using namespace RooFit;
  using namespace RooStats;
  using namespace HistFactory;

  // Many many flags for steering
  /* STEERING OPTIONS */ 
  const bool useMinos=true;
  const bool useMuShapeUncerts = false;
  const bool useTauShapeUncerts = false;
  const bool useDDShapeUncerts = false;
  const bool useMisIDShapeUncerts = false;
  const bool fixshapes = false;
  const bool fixshapesdstst = false;
  const bool dofit = true;
  const bool toyMC = false;
  const bool fitfirst = false;
  const bool slowplots = true;
  const bool BBon3d = false; //flag to enable Barlow-Beeston procedure for all histograms.
                           //Should allow easy comparison of fit errors with and 
			                     //without the technique. 3d or not is legacy from an old
                           //(3+1)d fit configuration
  const int numtoys = 1;
  const int toysize = 384236;
  // Set the prefix that will appear before
  // all output for this measurement
  RooStats::HistFactory::Measurement meas("my_measurement","my measurement");
  meas.SetOutputFilePrefix("results/my_measurement");
  meas.SetExportOnly(kTRUE); //Tells histfactory to not run the fit and display
                             //results using its own 

  meas.SetPOI("Nmu");

  // set the lumi for the measurement.
  // only matters for the data-driven
  // pdfs the way I've set it up. in invfb
  // variable rellumi gives the relative luminosity between the
  // data used to generate the pdfs and the sample
  // we are fitting

  // actually, now this is only used for the misID
  meas.SetLumi(1.0);
  meas.SetLumiRelErr(0.05);

  /******* Fit starting constants ***********/

  //ISOLATED FULL RANGE NONN
  //*
  const double expTau =0.252*0.1742*0.781/0.85;
  const double e_iso = 0.314;
  double expMu = 18e3;

  double RelLumi = 1.0;

  RooStats::HistFactory::Channel chan("Dstmu_kinematic");
  chan.SetStatErrorConfig(1e-5,"Poisson");

  // tell histfactory what data to use
  chan.SetData("histDataMassQsq", "signal.root");

  // Now that data is set up, start creating our samples
  // describing the processes to model the data

  /*********************** B_s0->Ds*munu (SIG) *******************************/

  RooStats::HistFactory::Sample sigmu("histoMassQsq_mu","histoMassQsq", "../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCutSignal_Bs0DstaMu_Weight.root");
  if(useMuShapeUncerts){
    sigmu.AddHistoSys("mu","histoMassQsq_M","../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCutSignal_Bs0DstaMu_Weight.root","","histoMassQsq_P","../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCutSignal_Bs0DstaMu_Weight.root","");
  }
  if(BBon3d) sigmu.ActivateStatError();
  sigmu.SetNormalizeByTheory(kFALSE);
  sigmu.AddNormFactor("Nmu", expMu, 1e-6, 1e6);
  sigmu.AddNormFactor("mcNorm_sigmu", mcN_sigmu, 1e-9, 1.);
  chan.AddSample(sigmu);
  
  /************************* B_s0->Ds*taunu  *******************************/

  RooStats::HistFactory::Sample sigtau("histoMassQsq_tau","histoMassQsq", "../Templates/output/RootOutp_MCAll_bin0_TauNorBIsoPIDCutSignal_Bs0DstaTau_Weight.root");
  if(useTauShapeUncerts){
    sigtau.AddHistoSys("tau","histoMassQsq_M","../Templates/output/RootOutp_MCAll_bin0_TauNorBIsoPIDCutSignal_Bs0DstaTau_Weight.root","","histoMassQsq_P","../Templates/output/RootOutp_MCAll_bin0_TauNorBIsoPIDCutSignal_Bs0DstaTau_Weight.root","");
  }
  if(BBon3d) sigtau.ActivateStatError();
  sigtau.SetNormalizeByTheory(kFALSE);
  sigtau.AddNormFactor("Nmu",expMu,1e-6,1e6);
  sigtau.AddNormFactor("RawRDst",expTau,1e-6,0.5);
  sigtau.AddNormFactor("mcNorm_tau", mcN_tau, 1e-9, 1.);
  chan.AddSample(sigtau);
  
  // for the moment add each component separately to the fit
  /************************* Bd->DD **************************************/

  RooStats::HistFactory::Sample bdddmu("histoMassQsq_bddd","histoMassQsq", "../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCutBdDstDs_Weight.root");
  if(useDDShapeUncerts){
    bdddmu.AddHistoSys("bddd","histoMassQsq_M","../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCutBdDstDs_Weight.root","","histoMassQsq_P","../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCutBdDstDs_Weight.root","");
  }
  if(BBon3d) bdddmu.ActivateStatError();
  bdddmu.SetNormalizeByTheory(kFALSE);
  bdddmu.AddNormFactor("mcNorm_BdDD", mcN_BdDD, 1e-9, 1.);
  bdddmu.AddNormFactor("NBdDD",0.102,1e-6,1e0);
  bdddmu.AddNormFactor("Nmu",expMu,1e-6,1e6);
  chan.AddSample(bdddmu);
  
  /************************* Bs->DD **************************************/

  RooStats::HistFactory::Sample bsddmu("histoMassQsq_bsdd","histoMassQsq", "../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCutBsDsDs_Weight.root");
  if(useDDShapeUncerts){
    bsddmu.AddHistoSys("bsdd","histoMassQsq_M","../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCutBsDsDs_Weight.root","","histoMassQsq_P","../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCutBsDsDs_Weight.root","");
  }
  if(BBon3d) bsddmu.ActivateStatError();
  bsddmu.SetNormalizeByTheory(kFALSE);
  bsddmu.AddNormFactor("mcNorm_BsDD", mcN_BsDD, 1e-9, 1.);
  bsddmu.AddNormFactor("NBsDD",0.102,1e-6,1e0);
  bsddmu.AddNormFactor("Nmu",expMu,1e-6,1e6);
  chan.AddSample(bsddmu);

  /************************* Bu->DD **************************************/

  RooStats::HistFactory::Sample buddmu("histoMassQsq_budd","histoMassQsq", "../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCutBuD0Ds_Weight.root");
  if(useDDShapeUncerts){
    buddmu.AddHistoSys("budd","histoMassQsq_M","../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCutBuD0Ds_Weight.root","","histoMassQsq_P","../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCutBuD0Ds_Weight.root","");
  }
  if(BBon3d) buddmu.ActivateStatError();
  buddmu.SetNormalizeByTheory(kFALSE);
  buddmu.AddNormFactor("mcNorm_BuDD", mcN_BuDD, 1e-9, 1.);
  buddmu.AddNormFactor("NBuDD",0.102,1e-6,1e0);
  buddmu.AddNormFactor("Nmu",expMu,1e-6,1e6);
  chan.AddSample(buddmu); 

  /************************* Lb->DD **************************************/

  RooStats::HistFactory::Sample lbddmu("histoMassQsq_lbdd","histoMassQsq", "../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCutLbLcDs_Weight.root");
  if(useDDShapeUncerts){
    lbddmu.AddHistoSys("lbdd","histoMassQsq_M","../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCutLbLcDs_Weight.root","","histoMassQsq_P","../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCutLbLcDs_Weight.root","");
  }
  if(BBon3d) lbddmu.ActivateStatError();
  lbddmu.SetNormalizeByTheory(kFALSE);
  lbddmu.AddNormFactor("mcNorm_LbDD", mcN_LbDD, 1e-9, 1.);
  lbddmu.AddNormFactor("NLbDD",0.05,1e-6,1e0);
  lbddmu.AddNormFactor("Nmu",expMu,1e-6,1e6);
  chan.AddSample(lbddmu); 
  
  

  /*********************** MisID BKG (FROM SS DATA)  *******************************/

  RooStats::HistFactory::Sample misID("histoMassQsq_misID","histoMassQsq", "../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCut_SameSign_Weight.root");
  if(useMisIDShapeUncerts){
    misID.AddHistoSys("misID","histoMassQsq_M","../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCut_SameSign_Weight.root","","histoMassQsq_P","../Templates/output/RootOutp_MCAll_bin0_NorBIsoPIDCut_SameSign_Weight.root","");
  } 
  if(BBon3d) misID.ActivateStatError();
  misID.SetNormalizeByTheory(kTRUE);
  misID.AddNormFactor("NmisID",RelLumi,1e-6,1e5); // from data
  chan.AddSample(misID);

  /****** END SAMPLE CHANNELS *******/

  meas.AddChannel(chan);
  meas.CollectHistograms();
  /*meas.AddConstantParam("mcNorm_sigmu");
  meas.AddConstantParam("mcNorm_sigtau");
  meas.AddConstantParam("mcNorm_D1");
  meas.AddConstantParam("fD1");
  meas.AddConstantParam("NDD");
  meas.AddConstantParam("NmisID");
  */

  RooWorkspace *w;
  w=RooStats::HistFactory::MakeModelAndMeasurementFast(meas);
 
  // Print the Workspace
  w->Print();

  ModelConfig *mc = (ModelConfig*) w->obj("ModelConfig"); // Get model manually
  RooSimultaneous *model = (RooSimultaneous*)mc->GetPdf();

  RooRealVar* poi = (RooRealVar*) mc->GetParametersOfInterest()->createIterator()->Next();
  std::cout << "Param of Interest: " << poi->GetName() << std::endl;  

  // Lets tell roofit the right names for our histogram variables //
  RooArgSet *obs = (RooArgSet*) mc->GetObservables();
  RooRealVar *x = (RooRealVar*) obs->find("obs_x_Dstmu_kinematic");
  RooRealVar *y = (RooRealVar*) obs->find("obs_y_Dstmu_kinematic");
  x->SetTitle("m_{corr}");
  x->setUnit("GeV^{2}");
  y->SetTitle("q^{2}");
  y->setUnit("MeV^{2}");

  // For simultaneous fits, this is the category histfactory uses to sort the channels

  RooCategory *idx = (RooCategory*) obs->find("channelCat");
  RooAbsData *data = (RooAbsData*) w->data("obsData");
  
/* FIX SOME MODEL PARAMS */
  if (((RooRealVar*)(mc->GetNuisanceParameters()->find("mcNorm_sigmu")))!=NULL) {
    ((RooRealVar*)(mc->GetNuisanceParameters()->find("mcNorm_sigmu")))->setConstant(kTRUE);
    cout << "mcNorm_sigmu = " << ((RooRealVar*)(mc->GetNuisanceParameters()->find("mcNorm_sigmu")))->getVal() << endl;
  }

  if (((RooRealVar*)(mc->GetNuisanceParameters()->find("mcNorm_tau")))!=NULL) {
    ((RooRealVar*)(mc->GetNuisanceParameters()->find("mcNorm_tau")))->setConstant(kTRUE);
    cout << "mcNorm_tau = " << ((RooRealVar*)(mc->GetNuisanceParameters()->find("mcNorm_tau")))->getVal() << endl;
  }

  if (((RooRealVar*)(mc->GetNuisanceParameters()->find("mcNorm_BdDD")))!=NULL) {
    ((RooRealVar*)(mc->GetNuisanceParameters()->find("mcNorm_BdDD")))->setConstant(kTRUE);
    cout << "mcNorm_BdDD = " << ((RooRealVar*)(mc->GetNuisanceParameters()->find("mcNorm_BdDD")))->getVal() << endl;
  }
 
  if (((RooRealVar*)(mc->GetNuisanceParameters()->find("mcNorm_LbDD")))!=NULL) {
    ((RooRealVar*)(mc->GetNuisanceParameters()->find("mcNorm_LbDD")))->setConstant(kTRUE);
    cout << "mcNorm_LbDD = " << ((RooRealVar*)(mc->GetNuisanceParameters()->find("mcNorm_LbDD")))->getVal() << endl;
  }

  if (((RooRealVar*)(mc->GetNuisanceParameters()->find("mcNorm_BuDD")))!=NULL) {
    ((RooRealVar*)(mc->GetNuisanceParameters()->find("mcNorm_BuDD")))->setConstant(kTRUE);
    cout << "mcNorm_BuDD = " << ((RooRealVar*)(mc->GetNuisanceParameters()->find("mcNorm_BuDD")))->getVal() << endl;
  }

  if (((RooRealVar*)(mc->GetNuisanceParameters()->find("mcNorm_BsDD")))!=NULL) {
    ((RooRealVar*)(mc->GetNuisanceParameters()->find("mcNorm_BsDD")))->setConstant(kTRUE);
    cout << "mcNorm_BsDD = " << ((RooRealVar*)(mc->GetNuisanceParameters()->find("mcNorm_BsDD")))->getVal() << endl;
  } 

  if (((RooRealVar*)(mc->GetNuisanceParameters()->find("mcNorm_misID")))!=NULL) {
    ((RooRealVar*)(mc->GetNuisanceParameters()->find("mcNorm_misID")))->setConstant(kTRUE);
    cout << "mcNorm_misID = " << ((RooRealVar*)(mc->GetNuisanceParameters()->find("mcNorm_misID")))->getVal() << endl;
  } 

  //((RooRealVar*)(mc->GetNuisanceParameters()->find("NDD")))->setVal(0.102);
  //((RooRealVar*)(mc->GetNuisanceParameters()->find("NDD")))->setConstant(kTRUE);
  //((RooRealVar*)(mc->GetNuisanceParameters()->find("fD1")))->setConstant(kTRUE);
  //((RooRealVar*)(mc->GetNuisanceParameters()->find("NmisID")))->setConstant(kTRUE);

  //if(useDDShapeUncerts) ((RooRealVar*)(mc->GetNuisanceParameters()->find("alpha_IW")))->setRange(-3.0,3.0);  
  if(useMuShapeUncerts) ((RooRealVar*)(mc->GetNuisanceParameters()->find("alpha_mu")))->setRange(-8,8);
  //((RooRealVar*)(mc->GetNuisanceParameters()->find("alpha_BFD1")))->setRange(-3,3);
  if(fixshapes) {
    ((RooRealVar*)(mc->GetNuisanceParameters()->find("alpha_mu")))->setVal(1.06);
    ((RooRealVar*)(mc->GetNuisanceParameters()->find("alpha_mu")))->setConstant(kTRUE);
  }
  if(fixshapesdstst) {
    ((RooRealVar*)(mc->GetNuisanceParameters()->find("alpha_IW")))->setVal(-0.005);//-2.187);
    ((RooRealVar*)(mc->GetNuisanceParameters()->find("alpha_IW")))->setConstant(kTRUE);
  }
  
  // This switches the model to a class written to handle analytic Barlow-Beeston lite.
  // Otherwise, every bin gets a minuit variable to minimize over!
  // This class, on the other hand, allows a likelihood where the bin parameters
  // are analyitically minimized at each step
  HistFactorySimultaneous* model_hf = new HistFactorySimultaneous( *model );
 
  RooFitResult *toyresult;
  RooAbsReal *nll_hf; 

  RooFitResult *result, *result2;

  std::cout << "Saving PDF snapshot" << std::endl;
  RooArgSet *allpars;
  allpars=(RooArgSet*)((RooArgSet*) mc->GetNuisanceParameters())->Clone();
  allpars->add(*poi);
  RooArgSet *constraints;
  constraints = (RooArgSet*) mc->GetConstraintParameters();
  if(constraints != NULL) allpars->add(*constraints);
  w->saveSnapshot("TMCPARS",*allpars,kTRUE);
  RooRealVar poierror("poierror","poierror",0.00001,0.010);
  TIterator *iter = allpars->createIterator();
  RooAbsArg *tempvar;
  RooArgSet *theVars = (RooArgSet*) allpars->Clone();
  theVars->add(poierror);
  RooDataSet *toyresults = new RooDataSet("toyresults","toyresults",*theVars,StoreError(*theVars));
  RooDataSet *toyminos = new RooDataSet("toyminos","toyminos",*theVars,StoreError(*theVars));
  // The following code is very messy. Sorry.
  if (toyMC) {
    double checkvar;
    double checkvarmean=0;
    if(fitfirst) {
      nll_hf = model_hf->createNLL(*data);
      RooMinuit* minuit_temp = new RooMinuit(*nll_hf) ;
      minuit_temp->setPrintLevel(-1);
      minuit_temp->optimizeConst(1);
      minuit_temp->setErrorLevel(0.5); // 1-sigma = DLL of 0.5
      minuit_temp->setOffsetting(kTRUE);
      minuit_temp->fit("smh");
      poi->setVal(expTau*0.85);
      checkvar = ((RooRealVar*)allpars->find("Nmu"))->getVal();
      cout << checkvar << endl;
    }
    else {
      //lets set some params
      if(useMuShapeUncerts) {
        ((RooRealVar*)(mc->GetNuisanceParameters()->find("alpha_mu")))->setVal(1.06);
      }
      if(useTauShapeUncerts) {
        ((RooRealVar*)(mc->GetNuisanceParameters()->find("alpha_tau")))->setVal(0.0002);
      }
      if(useDDShapeUncerts) {
        ((RooRealVar*)(mc->GetNuisanceParameters()->find("alpha_DD")))->setVal(0.2);//-2.187);
      }
    }

    w->saveSnapshot("GENPARS",*allpars,kTRUE);
      
    RooDataSet* datanom;
    cerr << "Attempting to generate toyMC..." << endl;
    sw2.Reset();
    sw2.Start();
    double running_mean=0;
    double running_RMS=0;
    for (int runnum =0; runnum<numtoys ; runnum++) {
      w->loadSnapshot("GENPARS");
      cerr << "DEBUG CHECK: Ntau=" << poi->getVal() << endl; 
      cout << "PROGRESS: SAMPLE NUMBER " << runnum << " STARTING GENERATION... " << endl;
      RooDataSet* data2 = model->generate(RooArgSet(*x,*y,model->indexCat()),Name("test"),AllBinned(),NumEvents(toysize),Extended());
      double wsum=0.;
      data2->Print();
      cout << "DONE" << endl;
      w->loadSnapshot("TMCPARS");
      nll_hf=model_hf->createNLL(*data2);
      RooMinuit *minuit_toy = new RooMinuit(*nll_hf);
      minuit_toy->optimizeConst(1);
      //minuit_toy->setPrintLevel(-1);
      minuit_toy->setOffsetting(kFALSE);
      minuit_toy->setOffsetting(kTRUE);
      minuit_toy->setErrorLevel(0.5);
      minuit_toy->setStrategy(2);
      //minuit_toy->setEps(5e-16);
      cout << "PROGRESS: FITTING SAMPLE " << runnum << " NOW...\t";
      minuit_toy->fit("smh");
       cout << " DONE. SAVING RESULT.\n" << endl;
      checkvarmean += ((RooRealVar*)allpars->find("Nmu"))->getVal();
      cout << "DEBUG CHECK: <Nmu>-Nmu_input = " << checkvarmean/(runnum+1) - checkvar << endl;
      poierror.setVal(poi->getError());
      toyresults->add(*theVars);
      cout << "PROGRESS: ATTEMPTING MINOS FOR SAMPLE " << runnum << " NOW...\t";
      minuit_toy->minos(RooArgSet(*poi));
      RooFitResult *testresult = minuit_toy->save("TOY","TOY");
      result=testresult;
      double edm=testresult->edm();
      if(edm > 0.1) {
        cout << "BAD FIT. SKIPPING..." << endl;
        continue;
      }
      cout << " DONE. SAVING RESULT.\n" << endl;
      toyminos->add(*theVars);
      delete minuit_toy;
      delete nll_hf;
      if(runnum+1<numtoys) {
        delete data2;
        delete testresult;
      }
      data=data2;
      double pulli=(poi->getVal()-expTau*0.85)/poi->getError();
      running_mean+=pulli;
      running_RMS+=pulli*pulli;
      cout << "RUNNING MEAN IS " << running_mean/(runnum+1) << "\tRUNNING RMS IS " << sqrt(running_RMS/(runnum+1)) << endl;
    }
    sw2.Stop();
    RooFormulaVar poi_pull("poi_pull","(@0-0.03428)/@1",RooArgList(*poi,poierror));
    RooRealVar *pulls = (RooRealVar*)toyminos->addColumn(poi_pull);
    pulls->setRange(-5,5);
    pulls->setBins(50);
    RooRealVar fitmu("fitmu","#mu",0.,-5,5);
    RooRealVar fitsig("fitsig","#sigma",1.,0.1,10);
    RooGaussian gaus("gaus","gaus",*pulls,fitmu,fitsig);
    gaus.fitTo(*toyminos,Range(-5,5));
    TCanvas *toytest=new TCanvas("toytest","toytest");
    toytest->Divide(2,1);
    toytest->cd(1);
    RooPlot *testframe = pulls->frame(Title("POI Pull"));
    toyminos->plotOn(testframe);
    gaus.plotOn(testframe);
    gaus.paramOn(testframe);
    testframe->Draw();
    //toytest->cd(2);
    //RooPlot *errframe = poierror.frame(Title("POI Error"));
    //toyresults->plotOn(errframe, Cut("poi_pull > -5 && poi_pull < 5"));
    //errframe->Draw();
    toytest->cd(2);
    RooPlot *valframe = poi->frame(Title("POI"));
    toyresults->plotOn(valframe);
    valframe->Draw();
  }

  if(dofit) {
    nll_hf= model_hf->createNLL(*data,Offset(kTRUE));

    RooMinuit* minuit_hf = new RooMinuit(*nll_hf) ;
    RooArgSet *temp = new RooArgSet();
    nll_hf->getParameters(temp)->Print("V");
    cout << "**********************************************************************" << endl;
    minuit_hf->setErrorLevel(0.5);
    //#ifndef UNBLIND
    //minuit_hf->setPrintLevel(-1);
    //#endif

    std::cout << "Minimizing the Minuit (Migrad)" << std::endl;
    if(toyMC) {w->loadSnapshot("TMCPARS");}
    else {w->saveSnapshot("TMCPARS",*allpars,kTRUE);}
    sw.Reset();
    sw.Start();
    minuit_hf->setStrategy(2);
    minuit_hf->fit("smh");
    RooFitResult *tempResult=minuit_hf->save("TempResult","TempResult");

    cout << tempResult->edm() << endl;
    if (useMinos) minuit_hf->minos(RooArgSet(*poi));
    sw.Stop();
    result = minuit_hf->save("Result","Result");

  }

  std::cout << "******************** F I N A L   P A R A M E T E R S *****************" << std::endl;
  RooArgSet *temp2 = new RooArgSet();
  nll_hf->getParameters(temp2)->Print("V");  

  RooPlot *mm2_frame = x->frame(Title("m_{corr}"));
  RooPlot *q2_frame = y->frame(Title("q^{2}"));
  q2_frame->Print();
  RooPlot *mm2q2_frame[q2_bins];

  const int nframes = 2;
  RooPlot *drawframes[nframes] = {mm2_frame, q2_frame};
  RooPlot *q2frames[q2_bins];
  RooPlot *q2bframes[q2_bins];
  for (int i=0; i < q2_bins; i++){
    mm2q2_frame[i] = x->frame();
    q2frames[i] = mm2q2_frame[i];
    q2bframes[i] = x->frame();
  }

  const int ncomps = 10;

  if(result != NULL) {
    printf("Fit ran with status %d\n",result->status());
    printf("Stat error on R(D*) is %f\n",poi->getError());
    printf("EDM at end was %f\n",result->edm());
    result->floatParsInit().Print();
    cout << "CURRENT NUISANCE PARAMETERS:" << endl;
    //TIterator *paramiter = mc->GetNuisanceParameters()->createIterator();
    TIterator *paramiter = result->floatParsFinal().createIterator();
    RooRealVar *__temp= (RooRealVar *)paramiter->Next();
    int final_par_counter=0;
    while (__temp!=NULL){
      if(!__temp->isConstant()){
        if(!(TString(__temp->GetName()).EqualTo(poi->GetName()))) {
          cout << final_par_counter << ": "
          << __temp->GetName() << "\t\t\t = "
          << ((RooRealVar*)result->floatParsFinal().find(__temp->GetName()))->getVal()
          << " +/- "
          << ((RooRealVar*)result->floatParsFinal().find(__temp->GetName()))->getError() << endl;
        }
      }
      final_par_counter++;
      __temp=(RooRealVar *)paramiter->Next();
    }
      
    result->correlationMatrix().Print();
    if (dofit) printf("Stopwatch: fit ran in %f seconds\n",sw.RealTime());
  }
  if (toyMC) {
    printf("Stopwatch: Generated test data in %f seconds\n",sw2.RealTime());
  }
  int colors[ncomps]={kRed,kBlue+1,kViolet,kViolet+1,kViolet+2,kGreen,kGreen+1,kOrange+1,kOrange+2,kOrange+3};
  const int ncomps2 = 8;
  TString names[ncomps2+1] = {"Data","Total Fit"
                             ,"B #rightarrow D*#mu#nu"
                             ,"B #rightarrow D**#mu#nu"
                             ,"B #rightarrow D**#tau#nu"
                             ,"B #rightarrow D*[D_{q} #rightarrow #mu#nuX]Y"
                             ,"Combinatoric (wrong-sign)"
                             ,"Misidentification BKG"
                             ,"Wrong-sign slow #pi"
  };
      
  RooHist* mm2resid;// = mm2_frame->pullHist() ;
  RooHist* q2resid;// = q2_frame->pullHist() ;

  RooHist *resids[nframes];

  for (int i = 0; i < nframes; i++){
    data->plotOn(drawframes[i],DataError(RooAbsData::Poisson),Cut("channelCat==0"),MarkerSize(0.4),DrawOption("ZP"));
    model->plotOn(drawframes[i], Slice(*idx),ProjWData(*idx,*data),DrawOption("F"),FillColor(kRed));
    model->plotOn(drawframes[i], Slice(*idx),ProjWData(*idx,*data),DrawOption("F"),FillColor(kViolet),Components("*tau*,*misID*,*bddd*,*lbdd*,*bsdd*,*budd*"));
    model->plotOn(drawframes[i], Slice(*idx),ProjWData(*idx,*data),DrawOption("F"),FillColor(kViolet+2),Components("*tau*,*misID*,*bddd*,*lbdd*,*bsdd*"));
    model->plotOn(drawframes[i], Slice(*idx),ProjWData(*idx,*data),DrawOption("F"),FillColor(kViolet+3),Components("*tau*,*misID*,*bddd*,*lbdd*"));
    model->plotOn(drawframes[i], Slice(*idx),ProjWData(*idx,*data),DrawOption("F"),FillColor(kViolet+4),Components("*tau*,*misID*,*bddd*"));
    model->plotOn(drawframes[i], Slice(*idx),ProjWData(*idx,*data),DrawOption("F"),FillColor(kBlue),Components("*tau*,*misID*"));
    model->plotOn(drawframes[i], Slice(*idx),ProjWData(*idx,*data),DrawOption("F"),FillColor(kOrange),Components("*tau*"));
    resids[i]=drawframes[i]->pullHist();
    data->plotOn(drawframes[i],DataError(RooAbsData::Poisson),Cut("channelCat==0"),MarkerSize(0.4),DrawOption("ZP"));
  }

  mm2resid=resids[0];
  q2resid=resids[1];
  
  char cutstrings[q2_bins][128];
  char rangenames[q2_bins][32];
  char rangelabels[q2_bins][128];
  RooHist *mm2q2_pulls[q2_bins];

  Double_t binlow[6] = {0., 2000000., 4000000., 6000000., 8000000., 10000000.};
  Double_t binhigh[6] = {2000000., 4000000., 6000000., 8000000., 10000000., 12000000.};
  for (int i=0; i < q2_bins; i++) {
    //double binlow = q2_low+i*(q2_high-q2_low)/q2_bins;
    //double binhigh = q2_low+(i+1)*(q2_high-q2_low)/q2_bins;
    sprintf(rangelabels[i],"%.2f < q^{2} < %.2f",binlow[i]*1e-6,binhigh[i]*1e-6);
    sprintf(cutstrings[i],"obs_y_Dstmu_kinematic > %f && obs_y_Dstmu_kinematic < %f && channelCat==0", q2_low+i*(q2_high-q2_low)/q2_bins, q2_low+(i+1)*(q2_high-q2_low)/q2_bins);
    sprintf(rangenames[i],"q2bin_%d",i);
    y->setRange(rangenames[i],binlow[i],binhigh[i]);
  }

  if(slowplots == true) {
    cout << "Drawing Slow Plots" << endl;
    for (int i = 0; i < q2_bins; i++) {
      data->plotOn(mm2q2_frame[i],Cut(cutstrings[i]),DataError(RooAbsData::Poisson),MarkerSize(0.4),DrawOption("ZP"));
      model->plotOn(mm2q2_frame[i], Slice(*idx),ProjWData(*idx,*data),ProjectionRange(rangenames[i]),DrawOption("F"),FillColor(kRed));
      
      //Grab pulls
      mm2q2_pulls[i]=mm2q2_frame[i]->pullHist();
      
      model->plotOn(mm2q2_frame[i], Slice(*idx), ProjWData(*idx,*data), ProjectionRange(rangenames[i]), DrawOption("F"), FillColor(kViolet), Components("*tau*,*misID*,*bddd*,*lbdd*,*bsdd*,*budd*"));
      model->plotOn(mm2q2_frame[i], Slice(*idx), ProjWData(*idx,*data), ProjectionRange(rangenames[i]), DrawOption("F"), FillColor(kViolet+2), Components("*tau*,*misID*,*bddd*,*lbdd*,*bsdd*"));
      model->plotOn(mm2q2_frame[i], Slice(*idx), ProjWData(*idx,*data), ProjectionRange(rangenames[i]), DrawOption("F"), FillColor(kViolet+3), Components("*tau*,*misID*,*bddd*,*lbdd*"));
      model->plotOn(mm2q2_frame[i], Slice(*idx), ProjWData(*idx,*data), ProjectionRange(rangenames[i]), DrawOption("F"), FillColor(kViolet+4), Components("*tau*,*misID*,*bddd*"));
      model->plotOn(mm2q2_frame[i], Slice(*idx), ProjWData(*idx,*data), ProjectionRange(rangenames[i]), DrawOption("F"), FillColor(kBlue), Components("*tau*,*misID*"));
      model->plotOn(mm2q2_frame[i], Slice(*idx), ProjWData(*idx,*data), ProjectionRange(rangenames[i]), DrawOption("F"), FillColor(kOrange), Components("*tau*"));
      data->plotOn(mm2q2_frame[i],Cut(cutstrings[i]),DataError(RooAbsData::Poisson),MarkerSize(0.4),DrawOption("ZP"));
    }
  }
  TCanvas *c1 = new TCanvas("c1","c1",1000,300);
  c1->SetTickx();
  c1->SetTicky();
  c1->Divide(2,1);
  TVirtualPad *curpad;
  curpad=c1->cd(1);
  curpad->SetTickx();
  curpad->SetTicky();
  curpad->SetRightMargin(0.02);
  curpad->SetLeftMargin(0.20);
  curpad->SetTopMargin(0.02);
  curpad->SetBottomMargin(0.13);
  mm2_frame->SetTitle("");
  mm2_frame->GetXaxis()->SetLabelSize(0.06);
  mm2_frame->GetXaxis()->SetTitleSize(0.06);
  mm2_frame->GetYaxis()->SetLabelSize(0.06);
  mm2_frame->GetYaxis()->SetTitleSize(0.06);
  mm2_frame->GetYaxis()->SetTitleOffset(1.75);
  mm2_frame->GetXaxis()->SetTitleOffset(0.9);
  TString thetitle=mm2_frame->GetYaxis()->GetTitle();
  thetitle.Replace(0,6,"Candidates");
  mm2_frame->GetYaxis()->SetTitle(thetitle);
  mm2_frame->Draw();
  curpad=c1->cd(2);
  curpad->SetTickx();
  curpad->SetTicky();
  curpad->SetRightMargin(0.02);
  curpad->SetLeftMargin(0.20);
  curpad->SetTopMargin(0.02);
  curpad->SetBottomMargin(0.13);
  q2_frame->SetTitle("");
  q2_frame->GetXaxis()->SetLabelSize(0.06);
  q2_frame->GetXaxis()->SetTitleSize(0.06);
  q2_frame->GetYaxis()->SetLabelSize(0.06);
  q2_frame->GetYaxis()->SetTitleSize(0.06);
  q2_frame->GetYaxis()->SetTitleOffset(1.75);
  q2_frame->GetXaxis()->SetTitleOffset(0.9);
  thetitle=q2_frame->GetYaxis()->GetTitle();
  thetitle.Replace(0,6,"Candidates");
  q2_frame->GetYaxis()->SetTitle(thetitle);
  q2_frame->Draw();

  RooPlot *mm2_resid_frame=x->frame(Title("mm2"));
  RooPlot *q2_resid_frame=y->frame(Title("q2"));
  RooPlot *DOCA_resid_frame;
      
  TCanvas *c2;
  if(slowplots == true) {
    c2 = new TCanvas("c2","c2",1200,600);
    c2->Divide(q2_bins/2,2);
    double max_scale=1.05;
    double max_scale2=1.05;
    char thename[32];
    for (int k = 0 ; k < q2_bins; k++) {
      c2->cd(k+1);
      sprintf(thename,"bottompad_%d",k);
      TPad *padbottom = new TPad(thename,thename,0.,0.,1.,0.3);
      padbottom->SetFillColor(0);
      padbottom->SetGridy();
      padbottom->SetTickx();
      padbottom->SetTicky();
      padbottom->SetFillStyle(0);
      padbottom->Draw();
      padbottom->cd();
      padbottom->SetLeftMargin(padbottom->GetLeftMargin()+0.08);
      padbottom->SetTopMargin(0);//0.01);
      padbottom->SetRightMargin(0.04);
      padbottom->SetBottomMargin(0.5);
      TH1 *temphist2lo, *temphist2, *tempdathist;
      RooHist *temphist;
      temphist = mm2q2_pulls[k];
      temphist->SetFillColor(kBlue);
      temphist->SetLineColor(kWhite);
      q2bframes[k]->SetTitle(q2frames[k]->GetTitle());
      q2bframes[k]->addPlotable(temphist,"B");
      q2bframes[k]->GetXaxis()->SetLabelSize(0.33*0.22/0.3);
      q2bframes[k]->GetXaxis()->SetTitleSize(0.36*0.22/0.3);
      q2bframes[k]->GetXaxis()->SetTickLength(0.10);
      q2bframes[k]->GetXaxis()->SetNdivisions(205);
      q2bframes[k]->GetYaxis()->SetTickLength(0.05);
      q2bframes[k]->SetTitle("");
      q2bframes[k]->GetYaxis()->SetTitleSize(0.33*0.22/0.3);
      q2bframes[k]->GetYaxis()->SetTitle("Pulls");
      q2bframes[k]->GetYaxis()->SetTitleOffset(0.2);
      q2bframes[k]->GetXaxis()->SetTitleOffset(0.78);
      q2bframes[k]->GetYaxis()->SetLabelSize(0.33*0.22/0.3);
      q2bframes[k]->GetYaxis()->SetLabelOffset(99);
      q2bframes[k]->GetYaxis()->SetNdivisions(205);
      q2bframes[k]->Draw();
      double xloc=-2.25;
      //t->SetTextSize(0.33*0.22/0.3);
      //t->DrawLatex(xloc,-2,"-2");
      //t->DrawLatex(xloc*0.99,2," 2");
      c2->cd(k+1);
      sprintf(thename,"toppad_%d",k);
      TPad *padtop = new TPad(thename,thename,0.,0.3,1.,1.);
      padtop->SetLeftMargin(padtop->GetLeftMargin()+0.08);
      padtop->SetBottomMargin(0);//padtop->GetBottomMargin()+0.08);
      padtop->SetTopMargin(0.02);//padtop->GetBottomMargin()+0.08);
      padtop->SetRightMargin(0.04);
      padtop->SetFillColor(0);
      padtop->SetFillStyle(0);
      padtop->SetTickx();
      padtop->SetTicky();
      padtop->Draw();
      padtop->cd();
      q2frames[k]->SetMinimum(1e-4);
      //q2frames[k]->SetMaximum(q2frames[k]->GetMaximum()*max_scale);
      q2frames[k]->SetTitle(rangelabels[(k % q2_bins)]);
      q2frames[k]->SetTitleFont(132,"t");
      q2frames[k]->GetXaxis()->SetLabelSize(0.09*0.78/0.7);
      q2frames[k]->GetXaxis()->SetTitleSize(0.09*0.78/0.7);
      q2frames[k]->GetXaxis()->SetNdivisions(205);
      q2frames[k]->GetYaxis()->SetTitleSize(0.09*0.78/0.7);
      TString thetitle=q2frames[k]->GetYaxis()->GetTitle();
      q2frames[k]->GetYaxis()->SetLabelSize(0.09*0.78/0.7);
      q2frames[k]->GetXaxis()->SetTitleOffset(0.95);
      q2frames[k]->GetYaxis()->SetTitleOffset(0.95);
      q2frames[k]->GetYaxis()->SetNdivisions(506);
      q2frames[k]->Draw();
      //t->SetTextSize(0.07);
      //t->SetTextAlign(33);
      //t->SetTextAngle(90);
      c2->cd(2*k+1);
      //t->DrawLatex(0.01,0.99,thetitle);
      //t->SetTextAlign(22);
      //t->SetTextAngle(0);
      padtop->cd();
      //t->SetTextSize(0.09*0.78/0.7);
    }
  }
}
