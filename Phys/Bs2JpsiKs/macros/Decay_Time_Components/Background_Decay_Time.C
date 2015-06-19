///////////////////////////////////////
// ***** Background Decay Time ***** //
///////////////////////////////////////

// This is the ROOT Macro written by Kristof De Bruyn for the effective lifetime measurement of Bs->JpsiKs at LHCb
// - Study the B decay time of the combinatoric background


/////////////////////////////////////
// ***** Load useful classes ***** //
/////////////////////////////////////

#include "RooAddModel.h"
#include "RooAddPdf.h"
#include "RooArgSet.h"
#include "RooCategory.h"
#include "RooCBShape.h"
#include "RooDataSet.h"
#include "RooDecay.h"
#include "RooEffProd.h"
#include "RooExponential.h"
#include "RooFit.h"
#include "RooFitResult.h"
#include "RooGaussian.h"
#include "RooGaussModel.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "RooUniform.h"

#include "RooStats/SPlot.h"

#include "TAxis.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TMath.h"
#include "TNtuple.h"
#include "TPaveText.h"

using namespace RooFit;

//////////////////////////////
// ***** Declarations ***** //
//////////////////////////////
void PullPlot(TString savestring, RooPlot* frame, Int_t logy=0);
void FitDecayTime(RooDataSet *data, RooRealVar *time, double *Minuit, TString saveString);

///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void RDDecayTime(TString what = "Bkg", TString whichLL = "TwoExp",TString whichDD = "OneAccFlat", Double_t NNCut = 0.5){

// ***** Initialize ***** //
////////////////////////////

  bool debug = false;
  
  // Using Optimisation VIIb
  Double_t NNcut_LL = (NNCut==1 ? 0.60 : NNCut);
  Double_t NNcut_DD = (NNCut==1 ? 0.75 : NNCut);

  // *** Plot Ranges ***
  Double_t Bmass_min = 5180;
  Double_t Bmass_max = 5520;


// ***** Part I: From NTuple to DataSet ***** //
////////////////////////////////////////////////

  std::cout << " " << std::endl;
  std::cout << "== Part I: From NTuple to DataSet ==" << std::endl;
  std::cout << "====================================" << std::endl;

  // ***** Load NTuples ***** //
  //////////////////////////////
	
  TFile* netFile = TFile::Open("B2JpsiKs-Eval-2-random-LHCb2011.root");// Double Net
  TTree* neural_net = (TTree*)netFile->Get("NetTree");

  TChain* chain = new TChain("chain");
  chain->Add("B2JpsiKs-Slim-LHCb2011.root/Slim_B2JpsiKs_Tuple");
	chain->AddFriend(neural_net);
	
  Long64_t nEntries_NTuple = chain->GetEntries();
	//nEntries_NTuple = 10000;	
  std::cout << "Number of entries from DaVinci: " << nEntries_NTuple << std::endl;		


  // ***** Define DataSet Observables ***** //
  ////////////////////////////////////////////

  // *** Define Observables & Selection Variables ***
				
  // Observable
	Float_t B_FullFit_ctau[10];
  Float_t B_FullFit_M[10];
  // Neural Net
  Float_t netOutput[10];
  Int_t nPV2 = -999;
  Int_t piminus_TRACK_Type = -999;

  // *** Initialize Arrays ***
  for(Int_t i=0; i<10; i++){
		B_FullFit_ctau[i] = -999;
    B_FullFit_M[i] = -999;
    netOutput[i] = -999;
  }


  // *** Set Branch Addresses ***
  // Observable
  chain->SetBranchAddress("B_FullFit_ctau", &B_FullFit_ctau);
  chain->SetBranchAddress("B_FullFit_M", &B_FullFit_M);	
  // Neural Net
  chain->SetBranchAddress("netOutput", &netOutput);
  chain->SetBranchAddress("nPV2", &nPV2);
  chain->SetBranchAddress("piminus_TRACK_Type", &piminus_TRACK_Type);
  
  // ***** Initialize DataSet ***** //
  ////////////////////////////////////

  // *** Observable ***
  RooRealVar *Bmass = new RooRealVar("Bmass","mass",Bmass_min,Bmass_max,"MeV/c^{2}");
  RooRealVar *Blife = new RooRealVar("Blife","lifetime",0.,15.,"ps");

  // *** DataSet ***
  RooArgSet *Obs = new RooArgSet(*Blife,*Bmass);
  RooDataSet *data_LL = new RooDataSet("data_LL","Unbinned dataset",*Obs);
  RooDataSet *data_DD = new RooDataSet("data_DD","Unbinned dataset",*Obs);


  // ***** Loop over Entries: Apply Selection Cuts ***** //
  /////////////////////////////////////////////////////////

  std::cout << " " << std::endl;
  std::cout << "== Loop 1: Selection Cuts ==" << std::endl;
  std::cout << "============================" << std::endl;

  for(Long64_t i=0; i<nEntries_NTuple; i++){
    chain->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_NTuple << " (" << 100*i/nEntries_NTuple << "%)" << std::endl;

    for(Int_t pv = 0; pv < nPV2 ; pv++){
      if((piminus_TRACK_Type==3 && netOutput[pv]>NNcut_LL) || (piminus_TRACK_Type==5 && netOutput[pv]>NNcut_DD)){// Selection Cuts

        // Fill DataSet
        Bmass->setVal(B_FullFit_M[pv]);
        Blife->setVal(B_FullFit_ctau[pv]*pow(10.,12)/(299792458*pow(10.,3)));	// convert from mm/c to ps
        if(piminus_TRACK_Type==3) data_LL->add(*Obs);
        else if(piminus_TRACK_Type==5) data_DD->add(*Obs);
      } 
		}
  }

  Int_t nEvents_LL = data_LL->numEntries();
  Int_t nEvents_DD = data_DD->numEntries();

  // Free Memory
  delete chain;
  
  
// ***** Part II: sWeights ***** //
///////////////////////////////////	

  std::cout << std::endl;
  std::cout << "== Part II: sWeights/High Mass Sideband ==" << std::endl;
  std::cout << "==========================================" << std::endl;
  
  // ***** Mass Model ***** //
  ////////////////////////////

  // *** Define Parameters ***  
  RooRealVar *meanBd = new RooRealVar("meanBd","Position of Bd mass peak",5279.5,Bmass_min,Bmass_max);
  RooFormulaVar *meanBs = new RooFormulaVar("meanBs","Position of Bs mass peak","@0+87.52",RooArgList(*meanBd));
  RooRealVar *frac_LL = new RooRealVar("frac_LL","Fraction of model I",0.47134,0.,1.);
  RooRealVar *frac_DD = new RooRealVar("frac_DD","Fraction of model I",0.64519,0.,1.);
  RooRealVar *sigma_I_LL = new RooRealVar("sigma_I_LL","Width of Bd mass peak",5.0722,1.0,25.0);
  RooRealVar *sigma_I_DD = new RooRealVar("sigma_I_DD","Width of Bd mass peak",6.2499,1.0,25.0);
  RooRealVar *sigma_II_LL = new RooRealVar("sigma_II_LL","Width of Bd mass peak",6.9036,1.0,25.0);
  RooRealVar *sigma_II_DD = new RooRealVar("sigma_II_DD","Width of Bd mass peak",10.677,1.0,25.0);
  RooRealVar *apar_I_LL = new RooRealVar("apar_I_LL","A parameter of Crystal Ball I",1.312);
  RooRealVar *apar_I_DD = new RooRealVar("apar_I_DD","A parameter of Crystal Ball I",2.339);
  RooRealVar *apar_II_LL = new RooRealVar("apar_II_LL","A parameter of Crystal Ball II",-1.434);
  RooRealVar *apar_II_DD = new RooRealVar("apar_II_DD","A parameter of Crystal Ball II",-2.248);
  RooRealVar *npar_I_LL = new RooRealVar("npar_I_LL","N parameter of Crystal Ball I",4.02);
  RooRealVar *npar_I_DD = new RooRealVar("npar_I_DD","N parameter of Crystal Ball I",1.71);
  RooRealVar *npar_II_LL = new RooRealVar("npar_II_LL","N parameter of Crystal Ball II",124.48);
  RooRealVar *npar_II_DD = new RooRealVar("npar_II_DD","N parameter of Crystal Ball II",4.7);
  
  RooRealVar *lambda_LL = new RooRealVar("lambda_LL","decay constant",-0.0027,-0.1,0.);
  RooRealVar *lambda_DD = new RooRealVar("lambda_DD","decay constant",-0.0027,-0.1,0.);
    
  // *** Crystal Ball ***
  RooCBShape *CBall_LL_Bd_I = new RooCBShape("CBall_LL_Bd_I","Crystal Ball",*Bmass,*meanBd,*sigma_I_LL,*apar_I_LL,*npar_I_LL);
  RooCBShape *CBall_LL_Bd_II = new RooCBShape("CBall_LL_Bd_II","Reflected Crystal Ball",*Bmass,*meanBd,*sigma_II_LL,*apar_II_LL,*npar_II_LL);
  RooAddPdf *double_CBall_LL_Bd = new RooAddPdf("double_CBall_LL_Bd","Double Crystal Ball",RooArgList(*CBall_LL_Bd_I,*CBall_LL_Bd_II),*frac_LL);
  RooCBShape *CBall_DD_Bd_I = new RooCBShape("CBall_DD_Bd_I","Crystal Ball",*Bmass,*meanBd,*sigma_I_DD,*apar_I_DD,*npar_I_DD);
  RooCBShape *CBall_DD_Bd_II = new RooCBShape("CBall_DD_Bd_II","Reflected Crystal Ball",*Bmass,*meanBd,*sigma_II_DD,*apar_II_DD,*npar_II_DD);
  RooAddPdf *double_CBall_DD_Bd = new RooAddPdf("double_CBall_DD_Bd","Double Crystal Ball",RooArgList(*CBall_DD_Bd_I,*CBall_DD_Bd_II),*frac_DD);

  RooCBShape *CBall_LL_Bs_I = new RooCBShape("CBall_LL_Bs_I","Crystal Ball",*Bmass,*meanBs,*sigma_I_LL,*apar_I_LL,*npar_I_LL);
  RooCBShape *CBall_LL_Bs_II = new RooCBShape("CBall_LL_Bs_II","Reflected Crystal Ball",*Bmass,*meanBs,*sigma_II_LL,*apar_II_LL,*npar_II_LL);
  RooAddPdf *double_CBall_LL_Bs = new RooAddPdf("double_CBall_LL_Bs","Double Crystal Ball",RooArgList(*CBall_LL_Bs_I,*CBall_LL_Bs_II),*frac_LL);
  RooCBShape *CBall_DD_Bs_I = new RooCBShape("CBall_DD_Bs_I","Crystal Ball",*Bmass,*meanBs,*sigma_I_DD,*apar_I_DD,*npar_I_DD);
  RooCBShape *CBall_DD_Bs_II = new RooCBShape("CBall_DD_Bs_II","Reflected Crystal Ball",*Bmass,*meanBs,*sigma_II_DD,*apar_II_DD,*npar_II_DD);
  RooAddPdf *double_CBall_DD_Bs = new RooAddPdf("double_CBall_DD_Bs","Double Crystal Ball",RooArgList(*CBall_DD_Bs_I,*CBall_DD_Bs_II),*frac_DD);
  
  // *** exponential (Background) ***
  RooExponential *exponential_LL = new RooExponential("exponential_LL","Exponential for background",*Bmass,*lambda_LL);
  RooExponential *exponential_DD = new RooExponential("exponential_DD","Exponential for background",*Bmass,*lambda_DD);

  // *** Combined signal and background ***
  RooRealVar *nBkg_LL = new RooRealVar("nBkg_LL","fraction",0.042311*nEvents_LL,0,nEvents_LL);
  RooRealVar *nBd_LL = new RooRealVar("nBd_LL","fraction",0.947600*nEvents_LL,0,nEvents_LL);
  RooRealVar *nBs_LL = new RooRealVar("nBs_LL","fraction",0.010089*nEvents_LL,0,nEvents_LL);

  RooAddPdf *massPDF_LL= new RooAddPdf("massPDF_LL","PDF for Sig + Bkg",RooArgList(*exponential_LL,*double_CBall_LL_Bd,*double_CBall_LL_Bs),RooArgList(*nBkg_LL,*nBd_LL,*nBs_LL));
  
  RooRealVar *nBkg_DD = new RooRealVar("nBkg_DD","fraction",0.042311*nEvents_DD,0,nEvents_DD);
  RooRealVar *nBd_DD = new RooRealVar("nBd_DD","fraction",0.947600*nEvents_DD,0,nEvents_DD);
  RooRealVar *nBs_DD = new RooRealVar("nBs_DD","fraction",0.010089*nEvents_DD,0,nEvents_DD);

  RooAddPdf *massPDF_DD= new RooAddPdf("massPDF_DD","PDF for Sig + Bkg",RooArgList(*exponential_DD,*double_CBall_DD_Bd,*double_CBall_DD_Bs),RooArgList(*nBkg_DD,*nBd_DD,*nBs_DD));


  // *** Fit ***
  if(what!="MassSidebands"){
    massPDF_LL->fitTo(*data_LL,Save(),NumCPU(2));
    massPDF_DD->fitTo(*data_DD,Save(),NumCPU(2)); 
  }
  
  if(debug){
    // ***** Plot: Mass ***** //
    ////////////////////////////
	
    // *** Signal ***
    RooPlot* mBframe = Bmass->frame(Bins(60));

    // Titles
    mBframe->SetYTitle("# Events/(5 MeV/c^{2})");
    mBframe->SetXTitle("B mass (MeV/c^{2})");

    // Cosmetics
    mBframe->SetTitleOffset(1.2,"y");
    mBframe->SetTitleSize(0.07,"x");
    mBframe->SetTitleSize(0.07,"y");
    mBframe->SetTitleFont(132,"y");
    mBframe->SetTitleFont(132,"x");
    mBframe->SetLabelSize(0.05,"y");
    mBframe->SetLabelSize(0.05,"x");
    mBframe->SetLabelFont(132,"x");
    mBframe->SetLabelFont(132,"y");

    data_LL->plotOn(mBframe,MarkerStyle(20),MarkerSize(1),MarkerColor(2));
    massPDF_LL->plotOn(mBframe,Components("exponential_LL"),LineColor(1),LineWidth(2));
    massPDF_LL->plotOn(mBframe,LineColor(2),LineWidth(2));
  
    data_DD->plotOn(mBframe,MarkerStyle(20),MarkerSize(1),MarkerColor(4));
    massPDF_DD->plotOn(mBframe,Components("exponential_DD"),LineColor(3),LineWidth(2));
    massPDF_DD->plotOn(mBframe,LineColor(4),LineWidth(2));

    mBframe->SetMinimum(0.9);
    mBframe->SetMaximum(10000);

	  // *** Canvas ***
    TCanvas *doek_mass = new TCanvas("doek_mass","B Mass Spectrum",900,800);
    doek_mass->SetLeftMargin(0.2);
    doek_mass->SetBottomMargin(0.15);
    doek_mass->cd(1);
    gPad->SetLogy(1);
    mBframe->Draw("");
  }
  
  // ***** sPlot ***** //
  ///////////////////////
  
  std::cout << " " << std::endl;
  std::cout << "==============" << std::endl;
  std::cout << "== sWeights ==" << std::endl;
  std::cout << "==============" << std::endl;
  
  RooRealVar *sWeight = new RooRealVar("sWeight","sWeight for component",0);

	// ***** sWeighted Datasets - LL ***** //
  /////////////////////////////////////////
	
  // *** Mass Sidebands ***
  RooDataSet *Data_sWeight_LL = 0;
  if(what=="MassSidebands") Data_sWeight_LL = (RooDataSet *) data_LL->reduce("Bmass>5400");
  
  // *** sWeighted Dataset ***
  else{
    // Initialise
    RooArgSet *sWeightVar = (RooArgSet *)data_LL->get();
	  RooRealVar *sWeight_Blife = (RooRealVar *)sWeightVar->find(Blife->GetName());
    //Double_t tot_LL = sData_LL->GetYieldFromSWeight("n"+what+"_LL");
    Data_sWeight_LL = new RooDataSet("Data_sWeight_LL","sWeighted Dataset",RooArgSet(*Blife,*sWeight),WeightVar(*sWeight));
		
    // Get Weights
    RooStats::SPlot *sData_LL = new RooStats::SPlot("sData_LL","sData", *data_LL, massPDF_LL, RooArgSet(*nBkg_LL,*nBd_LL,*nBs_LL));
	  for(Int_t i=0; i<nEvents_LL; i++){	
	    data_LL->get(i);
	    Blife->setVal(sWeight_Blife->getVal());
      sWeight->setVal(sData_LL->GetSWeight(i,"n"+what+"_LL"));
      Data_sWeight_LL->add(RooArgSet(*Blife,*sWeight),sWeight->getVal());	
	  }
  }
  
  // ***** sWeighted Datasets - DD ***** //
  /////////////////////////////////////////
  // *** Mass Sidebands ***
  RooDataSet *Data_sWeight_DD = 0;
  if(what=="MassSidebands") Data_sWeight_DD = (RooDataSet *) data_DD->reduce("Bmass>5400");
  
  // *** sWeighted Dataset ***
  else{
    // Initialise
    RooArgSet *sWeightVar = (RooArgSet *)data_DD->get();
	  RooRealVar *sWeight_Blife = (RooRealVar *)sWeightVar->find(Blife->GetName());
    Data_sWeight_DD = new RooDataSet("Data_sWeight_DD","sWeighted Dataset",RooArgSet(*Blife,*sWeight),WeightVar(*sWeight));
		
    // Get Weights
    RooStats::SPlot *sData_DD = new RooStats::SPlot("sData_DD","sData", *data_DD, massPDF_DD, RooArgSet(*nBkg_DD,*nBd_DD,*nBs_DD));
	  for(Int_t i=0; i<nEvents_DD; i++){	
	    data_DD->get(i);
	    Blife->setVal(sWeight_Blife->getVal());
      sWeight->setVal(sData_DD->GetSWeight(i,"n"+what+"_DD"));
      Data_sWeight_DD->add(RooArgSet(*Blife,*sWeight),sWeight->getVal());	
	  }
  }

// ***** Part III: Determine Distribution ***** //
//////////////////////////////////////////////////	

  std::cout << std::endl;
  std::cout << "== Part III: Determine Distribution ==" << std::endl;
  std::cout << "======================================" << std::endl;

  char buffer[3];
  Int_t NNVal_LL = NNcut_LL*100;
  Int_t NNVal_DD = NNcut_DD*100;
  std::sprintf(buffer,"NN%d+%d",NNVal_LL,NNVal_DD);
  TString saveString("Background_LL_"+what+"_"+whichLL+"_");
  saveString.Append(buffer);
  saveString.Append(".pdf");
  
  double Minuit_BkgLL[] = {-999,-999,-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
  if(whichLL!="None") FitDecayTime(Data_sWeight_LL,Blife,Minuit_BkgLL,saveString);


  saveString = "Background_DD_"+what+"_"+whichDD+"_";
  saveString.Append(buffer);
  saveString.Append(".pdf");
  
  double Minuit_BkgDD[] = {-999,-999,-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
  if(whichDD!="None") FitDecayTime(Data_sWeight_DD,Blife,Minuit_BkgDD,saveString);
  
  // ***** Output ***** //
  ////////////////////////

  std::cout << std::endl;	
  std::cout << "==================================================" << std::endl;
  std::cout << "== PDF Results: Background Distribution for "+what+" ==" << std::endl;
  std::cout << "==================================================" << std::endl;
  std::cout << "Neural Net: " << buffer << std::endl;
  std::cout << std::endl;
  std::cout << "== Long Long ==" << std::endl;
  std::cout << "Model: " << whichLL << std::endl;
  if(Minuit_BkgLL[2]!=-999) std::cout << "Tau Short = " << Minuit_BkgLL[2] << " +/- " << Minuit_BkgLL[3] << std::endl;
  if(Minuit_BkgLL[0]!=-999)std::cout << "Tau Long = " << Minuit_BkgLL[0] << " +/- " << Minuit_BkgLL[1] << std::endl;
  if(Minuit_BkgLL[4]!=-999)std::cout << "Frac = " << Minuit_BkgLL[4] << " +/- " << Minuit_BkgLL[5] << std::endl;
  if(Minuit_BkgLL[6]!=-999)std::cout << "Frac II = " << Minuit_BkgLL[6] << " +/- " << Minuit_BkgLL[7] << std::endl;
  if(Minuit_BkgLL[8]!=-999)std::cout << "Acc Y = " << Minuit_BkgLL[8] << " +/- " << Minuit_BkgLL[9] << std::endl;
  if(Minuit_BkgLL[10]!=-999)std::cout << "Acc Z = " << Minuit_BkgLL[10] << " +/- " << Minuit_BkgLL[11] << std::endl;
  std::cout << std::endl;
  std::cout << "== Down Down ==" << std::endl;
  std::cout << "Model: " << whichDD << std::endl;
  if(Minuit_BkgDD[2]!=-999) std::cout << "Tau Short = " << Minuit_BkgDD[2] << " +/- " << Minuit_BkgDD[3] << std::endl;
  if(Minuit_BkgDD[0]!=-999)std::cout << "Tau Long = " << Minuit_BkgDD[0] << " +/- " << Minuit_BkgDD[1] << std::endl;
  if(Minuit_BkgDD[4]!=-999)std::cout << "Frac = " << Minuit_BkgDD[4] << " +/- " << Minuit_BkgDD[5] << std::endl;
  if(Minuit_BkgDD[6]!=-999)std::cout << "Frac II = " << Minuit_BkgDD[6] << " +/- " << Minuit_BkgDD[7] << std::endl;
  if(Minuit_BkgDD[8]!=-999)std::cout << "Acc Y = " << Minuit_BkgDD[8] << " +/- " << Minuit_BkgDD[9] << std::endl;
  if(Minuit_BkgDD[10]!=-999)std::cout << "Acc Z = " << Minuit_BkgDD[10] << " +/- " << Minuit_BkgDD[11] << std::endl;
 
}

///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void FitDecayTime(RooDataSet *data, RooRealVar *time, double *Minuit, TString saveString){


  // ********** Initialise ********** //
  //////////////////////////////////////
  
  string convSave (saveString);
  
  TString what = "";
  if(convSave.find("Bkg")!=string::npos) what = "Bkg";
  else if(convSave.find("MassSidebands")!=string::npos) what = "MassSidebands";
  Int_t ttype = 0;
  if(convSave.find("LL")!=string::npos) ttype = 3;
  else if(convSave.find("DD")!=string::npos) ttype = 5;
  TString model = "";
  if(convSave.find("OneAccFlat")!=string::npos) model = "OneAccFlat";
  else if(convSave.find("OneExpFlat")!=string::npos) model = "OneExpFlat";
  else if(convSave.find("TwoExpFlat")!=string::npos) model = "TwoExpFlat";
  else if(convSave.find("OneExp")!=string::npos) model = "OneExp";
  else if(convSave.find("OneAcc")!=string::npos) model = "OneAcc";
  else if(convSave.find("TwoExp")!=string::npos) model = "TwoExp";
  Double_t plotMin = 0.;
  Double_t plotMax = 1000;
  if(what=="MassSidebands" && convSave.find("NN25")!=string::npos) plotMax = 1000;
  else if(what=="MassSidebands" && convSave.find("NN50")!=string::npos) plotMax = 200;
  else if(convSave.find("NN25")!=string::npos) plotMax = 5000;
  else if(convSave.find("NN60")!=string::npos) plotMax = 200;

  // *** Resolution ***	
  RooRealVar *resMean = new RooRealVar("resMean","Resolution - Mean",0.,"ps");
	RooRealVar *coreSigma = new RooRealVar("coreSigma","Resolution - Core Width",0.03,"ps");
	RooRealVar *midSigma = new RooRealVar("midSigma","Resolution - Middle Width",0.06,"ps");
	RooRealVar *tailSigma = new RooRealVar("tailSigma","Resolution - Tail Width",0.10,"ps");
  RooRealVar *Corefrac = new RooRealVar("Corefrac","Fraction of Core", 0.45);
  RooRealVar *Midfrac = new RooRealVar("Midfrac","Fraction of Mid", 0.45);
  // Set Values
  if(ttype==3){
    coreSigma->setVal(0.0340);
    midSigma->setVal(0.0648);
    tailSigma->setVal(0.379);
    Corefrac->setVal(0.63);
    Midfrac->setVal(0.36);
  }
  else if(ttype==5){
    coreSigma->setVal(0.0398);
    midSigma->setVal(0.0721);
    tailSigma->setVal(0.210);
    Corefrac->setVal(0.491);
    Midfrac->setVal(0.437);
  }
  
  // *** Lifetime ***	
	RooRealVar *tau_long = new RooRealVar("tau_long","Long Lifetime for Bkg",1.525,0.5,100.,"ps");		
	RooRealVar *tau_short = new RooRealVar("tau_short","Short lifetime for Bkg",0.3,0.,1.5,"ps");	
  RooRealVar *frac_I = new RooRealVar("frac_I","Fraction of Short",0.5,0.,1.);
  RooRealVar *frac_II = new RooRealVar("frac_II","Fraction of Short",0.4,0.,1.);

  // *** Acceptance ***
	RooRealVar *accY = new RooRealVar("accY","For Acceptance Function",0.95,0.,5.);
	RooRealVar *accZ = new RooRealVar("accZ","For Acceptance Function",1., 0. ,10.);	


  // ********** Time PDFs ********** //
  /////////////////////////////////////

  // *** Resolution ***	
  RooGaussModel *core = new RooGaussModel("core","Core Gaussian",*time,*resMean,*coreSigma);
  RooGaussModel *mid = new RooGaussModel("mid","Middle Gaussian",*time,*resMean,*midSigma);
  RooGaussModel *tail = new RooGaussModel("tail","Tail Gaussian",*time,*resMean,*tailSigma);
  RooAddModel *Res_Model = new RooAddModel("Res_Model","Resolution Model",RooArgList(*core,*mid,*tail),RooArgList(*Corefrac,*Midfrac));
  
  // *** Acceptance ***
  RooFormulaVar *acceptance = new RooFormulaVar("acceptance","an acceptance function","1/(1+pow(@1*@2,-@0))",RooArgList(*accY,*accZ,*time));
  
  // *** RooDecays ***
  RooDecay *decay_short = new RooDecay("decay_short","Short Lifetimes",*time,*tau_short,*Res_Model,RooDecay::SingleSided);
	RooDecay *decay_long = new RooDecay("decay_long","Long Lifetimes",*time,*tau_long,*Res_Model,RooDecay::SingleSided);
  RooUniform *uniform = new RooUniform("uniform","Flat Lifetime", *time);
  RooEffProd *decay_acc = new RooEffProd("decay_acc","Decay with acceptance",*decay_long,*acceptance);

  // *** Composite ***
  RooAddPdf *background = 0;
  if(model=="TwoExp") background = new RooAddPdf("background","Background Model",RooArgList(*decay_short,*decay_long),*frac_I);
  else if(model=="TwoExpFlat"){
    tau_short->setVal(0.549075);
    //tau_short->setConstant();
    tau_long->setVal(1.33109);
    tau_long->setConstant();
    frac_I->setVal(0.389095);
    frac_I->setConstant();
    frac_II->setVal(0.581665);
    frac_II->setConstant();
    background = new RooAddPdf("background","Background Model",RooArgList(*decay_short,*decay_long,*uniform),RooArgSet(*frac_I,*frac_II));
  }
  else if(model=="OneExpFlat") background = new RooAddPdf("background","Background Model",RooArgList(*decay_long,*uniform),RooArgSet(*frac_I));
  else if(model=="OneAccFlat") background = new RooAddPdf("background","Background Model",RooArgList(*decay_acc,*uniform),RooArgSet(*frac_I));

  // ********** Fit ********** //
  ///////////////////////////////
  
  std::cout << std::endl;
  std::cout << "== Fit ==" << std::endl;
  std::cout << model << std::endl;
  bool weighted = false;
  if(what=="Bkg") weighted = true;
  
  time->setRange("FitPrompt",0.2 ,4.);
  time->setRange("FitRange",0.2 ,15.);

  RooFitResult *fitresult = 0;
  RooFitResult *fitresult_prompt = 0;
  if(model=="OneExp") fitresult = decay_long->fitTo(*data,Range("FitRange"),SumW2Error(weighted),Save(),NumCPU(2));
  else if(model=="OneAcc") fitresult = decay_acc->fitTo(*data,Range("FitRange"),SumW2Error(weighted),Save(),NumCPU(2));
  else if(model=="OneAccFlat"){
    fitresult_prompt = decay_acc->fitTo(*data,Range("FitPrompt"),SumW2Error(weighted),Save(),NumCPU(2));
    accY->setConstant();
    accZ->setConstant();
    fitresult = background->fitTo(*data,Range("FitRange"),SumW2Error(weighted),Save(),NumCPU(2));
  }
  else fitresult = background->fitTo(*data,Range("FitRange"),SumW2Error(weighted),Save(),NumCPU(2));
  
  if(fitresult_prompt) fitresult_prompt->Print();
  fitresult->Print();
  RooRealVar* temp = 0;
  if(fitresult && (fitresult->covQual()!=0)){

    const RooArgList& fitted_par = fitresult->floatParsFinal();

    temp = (RooRealVar*)fitted_par.find("tau_long");
    if(temp){
      Minuit[0] = temp->getVal();
      Minuit[1] = temp->getError();
      delete temp;
    }
    temp = (RooRealVar*)fitted_par.find("tau_short");
    if(temp){
      Minuit[2] = temp->getVal();
      Minuit[3] = temp->getError();
      delete temp;
    }
    temp = (RooRealVar*)fitted_par.find("frac_I");
    if(temp){
      Minuit[4] = temp->getVal();
      Minuit[5] = temp->getError();
      delete temp;
    }
    temp = (RooRealVar*)fitted_par.find("frac_II");
    if(temp){
      Minuit[6] = temp->getVal();
      Minuit[7] = temp->getError();
      delete temp;
    }
    temp = (RooRealVar*)fitted_par.find("accY");
    if(temp){
      Minuit[8] = temp->getVal();
      Minuit[9] = temp->getError();
      delete temp;
    }
    temp = (RooRealVar*)fitted_par.find("accZ");
    if(temp){
      Minuit[10] = temp->getVal();
      Minuit[11] = temp->getError();
      delete temp;
    }
  }
  if(fitresult_prompt && (fitresult_prompt->covQual()==3 || fitresult_prompt->covQual()<0)){

    const RooArgList& fitted_par = fitresult_prompt->floatParsFinal();

    temp = (RooRealVar*)fitted_par.find("accY");
    if(temp){
      Minuit[8] = temp->getVal();
      Minuit[9] = temp->getError();
      delete temp;
    }
    temp = (RooRealVar*)fitted_par.find("accZ");
    if(temp){
      Minuit[10] = temp->getVal();
      Minuit[11] = temp->getError();
      delete temp;
    }
  }

  
	// ***** Plot ***** //
  //////////////////////
	
	// *** Frame ***
	RooPlot* BFrame = time->frame(Range(0.,15.),Bins(75));

	// Titles
	BFrame->SetYTitle("Events/(0.20 ps)");
	BFrame->SetXTitle("Reco B decay time (ps)");

	// Cosmetics
	BFrame->SetTitleOffset(1.2,"y");
	BFrame->SetTitleSize(0.07,"x");
	BFrame->SetTitleSize(0.07,"y");
	BFrame->SetTitleFont(132,"y");
	BFrame->SetTitleFont(132,"x");
	BFrame->SetLabelSize(0.05,"y");
	BFrame->SetLabelSize(0.05,"x");
	BFrame->SetLabelFont(132,"x");
	BFrame->SetLabelFont(132,"y");

  data->plotOn(BFrame,MarkerStyle(8),MarkerSize(0.8));
  if(model=="OneExp") decay_long->plotOn(BFrame,Range(plotMin,15.),LineColor(4),LineWidth(2));
  else if(model=="OneAcc") decay_acc->plotOn(BFrame,Range(plotMin,15.),LineColor(4),LineWidth(2));
  else{
    if(model=="TwoExp" || model=="TwoExpFlat"){
      background->plotOn(BFrame,Range(plotMin,15.),Components("decay_short"),LineColor(1),LineWidth(2));
    }
    if(model=="TwoExp" || model=="TwoExpFlat" || model=="OneExpFlat"){
      background->plotOn(BFrame,Range(plotMin,15.),Components("decay_long"),LineColor(3),LineWidth(2));
    }
    if(model=="OneAccFlat") background->plotOn(BFrame,Range(plotMin,15.),Components("decay_acc"),LineColor(3),LineWidth(2));
    if(model=="TwoExpFlat" || model=="OneAccFlat" || model=="OneExpFlat"){
      background->plotOn(BFrame,Range(plotMin,15.),Components("uniform"),LineColor(2),LineWidth(2));
    }
    background->plotOn(BFrame,Range(plotMin,15.),LineColor(4),LineWidth(2));
  }
  
  BFrame->SetMinimum(0.9);
  BFrame->SetMaximum(plotMax);	

  PullPlot(saveString,BFrame,1);
}

/////////////////////////////////
// ***** Helper Function ***** //
/////////////////////////////////
void PullPlot(TString savestring, RooPlot* frame, Int_t logy){
  // *** Canvas ***
  TCanvas *doek = new TCanvas("doek","Observable",900,800);
	doek->cd(1);
	Float_t ratio = 0.30; // Percentage of the plot for Pull distributions
	
	// *** Pull Plot ***
  RooPlot* pullframe = (RooPlot *)frame->emptyClone("pullframe");
	
	// Titles
  pullframe->SetYTitle("Pull");
  pullframe->SetXTitle(frame->GetXaxis()->GetTitle());

  // Cosmetics
  pullframe->SetTitleOffset(0.9,"x");
  pullframe->SetTitleSize(0.07,"x");
  pullframe->SetTitleFont(132,"x");
  pullframe->SetLabelSize(0.05,"x");
  pullframe->SetLabelFont(132,"x");
  pullframe->SetTitleSize(0,"y");// No title here	
	pullframe->SetLabelSize(0.03,"y");// and no labels
  pullframe->SetLabelFont(132,"y");	
	
	// Fill - And specify plot option: Bar-chart
	pullframe->addObject((TObject*)frame->pullHist(),"B");
	// Extract the histogram in orde to apply plot options
	TGraph* pullgraph = (TGraph*) pullframe->getObject(0);
	//pullgraph->SetLineWidth(2);
	pullgraph->SetFillColor(4);
	pullgraph->SetFillStyle(1001);
	
	// General Settings
  pullframe->SetMinimum(-5);
	pullframe->SetMaximum(5);
	pullframe->GetYaxis()->SetNdivisions(503,kTRUE);
	
	// *** Place the first frame ***
	// To keep the correct scale of the labels, use the Margins instead of Pad coordinates
	TPad* xPad = new TPad("xPad", "Pad for Observable Plot", 0., 0, 1., 1.);
	xPad->SetLeftMargin(0.2);
	xPad->SetBottomMargin(ratio);	
	// Draw Pad	
	xPad->Draw();
	xPad->cd();
	xPad->SetLogy(logy);
	// Suppress X-axis decoration
	frame->SetLabelSize(0,"x");
	frame->SetTitleSize(0,"x");
  frame->SetLabelOffset(0.015,"y");
	// Fill Pad	
	frame->Draw("");
	
	
  // *** LHCb Tag *** 
  string convSave (savestring);
  size_t isBd=convSave.find("SigBd");
  size_t isBs=convSave.find("SigBs");
  size_t isLL=convSave.find("LL");
  size_t isDD=convSave.find("DD");
  
  TString track("");
  if(isLL!=string::npos) track = "Long K_{S}^{0}";
  else if(isDD!=string::npos) track = "Downstream K_{S}^{0}";
  
	TPaveText *lhcbTag = 0;
  double offset = 0.;
  if(isBd==string::npos && isBs==string::npos) offset = 0.05;
	//if(logy==1){lhcbTag = new TPaveText(0.23,0.70,0.47+offset,0.89,"NDC");}
	if(logy==1){lhcbTag = new TPaveText(0.65,0.70,0.89,0.89,"NDC");}
	if(logy==0){lhcbTag = new TPaveText(0.65,0.35,0.89,0.47,"NDC");}

  lhcbTag->SetFillColor(0);
  lhcbTag->SetTextAlign(32);
  lhcbTag->SetBorderSize(0);
  lhcbTag->SetTextSize(0.05);
  lhcbTag->SetTextFont(132);
  if(isBd!=string::npos) lhcbTag->AddText("#splitline{LHCb MC11a}{#splitline{#scale[0.7]{B_{d}^{0}#rightarrow J/#psi K_{S}^{0}}}{#scale[0.7]{"+track+"}}}");
  else if(isBs!=string::npos) lhcbTag->AddText("#splitline{LHCb MC11a}{#splitline{#scale[0.7]{B_{s}^{0}#rightarrow J/#psi K_{S}^{0}}}{#scale[0.7]{"+track+"}}}");
  else lhcbTag->AddText("#splitline{LHCb 2011}{#splitline{#scale[0.7]{Reco 12 - Stripping 17b}}{#scale[0.7]{"+track+"}}}");
  lhcbTag -> Draw("");
		
	
	// *** Place the second frame ***
	// go back to the Bottom layer
	doek->cd();
	// To keep the correct scale of the labels, use the Margins instead of Pad coordinates
	TPad* pullPad = new TPad("pullPad", "Pad for Pull Plot", 0., 0., 1., 1);
	pullPad->SetLeftMargin(0.2);
	pullPad->SetBottomMargin(0.15);	
	pullPad->SetTopMargin(1-ratio+0.01);
	// Make the pad transparent
	pullPad->SetFillColor(0);
	pullPad->SetFillStyle(0);
	// Draw Pad	
	pullPad->Draw();
	pullPad->cd();
	// Fill Pad - Draw Y axis on the right side such that it doesn't overlap
	pullframe->Draw("");

	// *** Save ***
	doek->SaveAs(savestring);
	
	// *** Clean Up ***
	delete lhcbTag;
	delete xPad;
	delete pullPad;
	delete pullframe;
	delete doek;
	return;
}
