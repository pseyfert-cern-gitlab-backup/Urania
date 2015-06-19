//////////////////////////////////////////////////////////////////////////////
// ********** Sampling Difference Between Tau_Single and Tau_Eff ********** //
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////
// ********** Loading useful classes ********** //
//////////////////////////////////////////////////

#include <Math/WrappedTF1.h>
#include <Math/BrentRootFinder.h>

#include <RooDataSet.h>
#include <RooFitResult.h>
#include <RooFormulaVar.h>
#include <RooGaussian.h>
#include <RooPlot.h>
#include <RooRealVar.h>
#include <RooRandom.h>

#include <TCanvas.h>
#include <TF1.h>
#include <TFile.h>
#include <TMath.h>
#include <TTree.h>

using namespace RooFit;

////////////////////////////////////////
// ********** Declarations ********** //
////////////////////////////////////////
double makeLHS(bool withAcc, double ypar, double zpar, double beta, double tauSingle);
double makeRHS(bool withAcc, double ypar, double zpar, double beta, double tauBs, double ys, double ADG);
double findTauSingle(bool withAcc, double ypar, double zpar, double beta, double tauBs, double ys, double ADG);
double findTauEff(double tauBs, double ys, double ADG);


//////////////////////////////////////////////
// ********** Integral Functions ********** //
//////////////////////////////////////////////
double makeLHS(bool withAcc, double ypar, double zpar, double beta, double tauSingle) {

  // *** Initialise ***
  double min = 0.2;
  double max = 15.;
  TString ExpFunc = "(exp(-x/[0])/[0])";
  TString AccFunc = (withAcc ? "(1 + [3]*x)/(1 + pow([2]*x,-[1]))" : "1");

  // *** Numerator ***
  TF1 *funcNum = new TF1("funcNum", "x*"+ExpFunc+"*"+AccFunc, min, max);
  if (withAcc) {
    funcNum->SetParameters(tauSingle, ypar, zpar, beta);
  }
  else {
    funcNum->SetParameter(0, tauSingle);
  }
  double intNum = funcNum->Integral(min, max);

  // *** Denominator ***
  TF1 *funcDen = new TF1("funcDen", ExpFunc+"*"+AccFunc, min, max);
  if (withAcc) {
    funcDen->SetParameters(tauSingle, ypar, zpar, beta);
  }
  else {
    funcDen->SetParameter(0, tauSingle);
  }
  double intDen = funcDen->Integral(min, max);
  
  // *** Return ***
  delete funcNum;
  delete funcDen;
  return intNum/intDen;
}

double makeRHS(bool withAcc, double ypar, double zpar, double beta, double tauBs, double ys, double ADG) {

  // *** Initialise ***
  double min = 0.2;
  double max = 15.;
  TString ExpFunc = "((1-[1]*[1])/([0]+[0]*[1]*[2])) * exp(-x/[0]) * (TMath::CosH([1]*x/[0]) + [2] * TMath::SinH([1]*x/[0]))";
  TString AccFunc = (withAcc ? "(1 + [5]*x)/(1 + pow([4]*x,-[3]))" : "1");

  // *** Numerator ***
  TF1 *funcNum = new TF1("funcNum", "x*"+ExpFunc+"*"+AccFunc, min, max);
  if (withAcc) {
    funcNum->SetParameters(tauBs, ys, ADG, ypar, zpar, beta);
  }
  else {
    funcNum->SetParameters(tauBs, ys, ADG);
  }
  double intNum = funcNum->Integral(min, max);

  // *** Denominator ***
  TF1 *funcDen = new TF1("funcDen", ExpFunc+"*"+AccFunc, min, max);
  if (withAcc) {
    funcDen->SetParameters(tauBs, ys, ADG, ypar, zpar, beta);
  }
  else {
    funcDen->SetParameters(tauBs, ys, ADG);
  }
  double intDen = funcDen->Integral(min, max);

  // *** Return ***
  delete funcNum;
  delete funcDen;
  return intNum/intDen;
}


//////////////////////////////////////
// ********** Tau_Single ********** //
//////////////////////////////////////
double findTauSingle(bool withAcc, double ypar, double zpar, double beta, double tauBs, double ys, double ADG) {

  // *** Initialise ***
  double RHS = makeRHS(withAcc, ypar, zpar, beta, tauBs, ys, ADG);
  
  // *** Function ***
  TString mybool = (withAcc ? "1" : "0");
  TF1 *func = new TF1("func", "makeLHS("+mybool+",[0],[1],[2],x)-[3]", 1., 2.);
  func->SetParameters(ypar, zpar, beta, RHS);
 
  // Wrap Function
  ROOT::Math::WrappedTF1 *wrapFunc = new ROOT::Math::WrappedTF1(*func);
 
  // *** Root Finder ***
  ROOT::Math::BrentRootFinder *brf = new ROOT::Math::BrentRootFinder();
  brf->SetFunction(*wrapFunc, 1., 2.);
  brf->Solve();
  double tauSol = brf->Root();
  
  // *** Return ***
  delete func;
  delete wrapFunc;
  delete brf;
  return tauSol;
}


//////////////////////////////////////
// ********** Tau_Eff ********** //
//////////////////////////////////////
double findTauEff(double tauBs, double ys, double ADG) {
  return (tauBs/(1 - pow(ys,2))) * (1 + 2 * ADG * ys + pow(ys,2))/(1 + ADG * ys);
}


/////////////////////////////////////////
// ********** Main Function ********** //
/////////////////////////////////////////
void Sample(int whichAcc = 1, int seed = 123, int nEvents = 100){

  // *** Initialise Tree ***
  TFile *save_data = new TFile("Sample_Data.root", "RECREATE");
  save_data->cd();
  TTree *dataTree = new TTree("Sampling", "Sampled Data");
  
  // Branches
  double accY = 0;
  dataTree->Branch("accY", &accY, "accY/D");
  double accZ = 0;
  dataTree->Branch("accZ", &accZ, "accZ/D");
  double accBeta = 0;
  dataTree->Branch("accBeta", &accBeta, "accBeta/D");
  double tauBs = 0;
  dataTree->Branch("tauBs", &tauBs, "tauBs/D");
  double ys = 0;
  dataTree->Branch("ys", &ys, "ys/D");
  double ADG = 0;
  dataTree->Branch("ADG", &ADG, "ADG/D");
  double tauSingle = 0;
  dataTree->Branch("tauSingle", &tauSingle, "tauSingle/D");	
  double tauEff = 0;
  dataTree->Branch("tauEff", &tauEff, "tauEff/D");
  double tauDiff = 0;
  dataTree->Branch("tauDiff", &tauDiff, "tauDiff/D");

	// *** Initialise Random Generator ***
	RooRandom::randomGenerator()->SetSeed(seed);
  
	std::cout << "*** Generating ***" << std::endl;
	for (int i=0; i<nEvents; i++) {
    if (i%100==0 ) std::cout << "Event " << i << "/" << nEvents << std::endl;
    if (whichAcc==1) {
      // Downstream
      accY    = 2.024 + 0.033 * RooRandom::gaussian(RooRandom::randomGenerator());
      accZ    = 1.112 + 0.040 * RooRandom::gaussian(RooRandom::randomGenerator());
      accBeta = 0.031 + 0.011 * RooRandom::gaussian(RooRandom::randomGenerator());
    }
    if (whichAcc==-1) {
      // Long
      accY    =  1.52  + 0.16  * RooRandom::gaussian(RooRandom::randomGenerator());
      accZ    =  2.33  + 0.20  * RooRandom::gaussian(RooRandom::randomGenerator());
      accBeta = -0.025 + 0.010 * RooRandom::gaussian(RooRandom::randomGenerator());
    }
    else {
      // No Acceptance
      accY    = -999;
      accZ    = -999;
      accBeta = -999;
    }
    tauBs = 1.513  + 0.011  * RooRandom::gaussian(RooRandom::randomGenerator());
    ys    = 0.0802 + 0.0099 * RooRandom::gaussian(RooRandom::randomGenerator());
    ADG   = -1. + 2 * RooRandom::uniform(RooRandom::randomGenerator());

    tauSingle = findTauSingle(fabs(whichAcc), accY, accZ, accBeta, tauBs, ys, ADG);
    tauEff = findTauEff(tauBs, ys, ADG);
    tauDiff = fabs(tauSingle - tauEff);
    dataTree->Fill();
	}
  // *** Write to Disk ***
  dataTree->Write("", TObject::kOverwrite);
  std::cout << "*** Data saved ***" << std::endl;
  save_data->Close();
}


///////////////////////////////////
// ********** Analyse ********** //
///////////////////////////////////
void Analyse(TString sample = "withAccDD") {

  if (!(sample=="withAccDD" || sample=="withAccLL" || sample=="withNoAcc")) {
    std::cout << "ERROR: Unknown sample" << std::endl;
    return;
  }

  // ***** Load Data ***** //
  ///////////////////////////

  // *** Initialise Tree ***
  TFile *save_data = new TFile("Sample_Data_"+sample+".root", "UPDATE");
  save_data->cd();
  TTree *outputTree = (TTree *) save_data->Get("Sampling");
  int nEntries = outputTree->GetEntries();

  // Branches
  double tauEff = 0;
  double tauSingle = 0;
  outputTree->SetBranchAddress("tauEff", &tauEff);
  outputTree->SetBranchAddress("tauSingle", &tauSingle);

  // *** Initialise data set ***
  RooRealVar *tauDiff = new RooRealVar("tauDiff", "Fit difference", 0.);
  RooDataSet *data = new RooDataSet("data", "Unbinned dataset", *tauDiff);

  // Fill
  for (int i = 0; i<nEntries; i++) {
    outputTree->GetEntry(i);
    tauDiff->setVal(tauEff-tauSingle);
    data->add(*tauDiff);
  }

  // ***** Fit Model ***** //
  ///////////////////////////

  RooRealVar *mean  = new RooRealVar("mean" , "mean", -0.0033, -0.01, 0.);
  RooRealVar *sigma = new RooRealVar("sigma", "sigma", 0.0015, 0.0001, 0.005);

  RooGaussian *gauss = new RooGaussian("gauss", "Gaussian",
    *tauDiff, *mean, *sigma);

  double max = (sample=="withAccDD" ? -0.0033 : -0.0007);
  double min = (sample=="withAccDD" ? -0.01 : (sample=="withAccLL" ? -0.005 : -0.0025));
  TString yText = (sample=="withAccDD" ? "/(0.0001 ps)" : (sample=="withAccLL" ? "/(0.00005 ps)" : "/(0.000025 ps)"));
  RooFitResult *fitgauss = gauss->fitTo(*data, Save(), Range(min, max));

  // ***** Plot Model ***** //
  ////////////////////////////

  RooPlot* ObsFrame = tauDiff->frame(Range(min, 0.), Bins(100));

  // *** Cosmetics ***
  ObsFrame->SetXTitle("#tau_{J/#psi K_{S}}^{eff}-#tau_{single} [ps]");
  ObsFrame->SetYTitle("Entries"+yText);

  ObsFrame->SetTitleOffset(1.2,"y");
  ObsFrame->SetTitleSize(0.07,"x");
  ObsFrame->SetTitleSize(0.07,"y");
  ObsFrame->SetTitleFont(132,"y");
  ObsFrame->SetTitleFont(132,"x");
  ObsFrame->SetLabelSize(0.05,"y");
  ObsFrame->SetLabelSize(0.05,"x");
  ObsFrame->SetLabelFont(132,"x");
  ObsFrame->SetLabelFont(132,"y");
  ObsFrame->SetNdivisions(-405);

  // *** Plot ***
  data->plotOn(ObsFrame, MarkerStyle(8), MarkerSize(0.8));
  gauss->plotOn(ObsFrame, Range(min, 0.), LineWidth(2), LineColor(4));

  ObsFrame->SetMaximum(3000);

  // *** Canvas ***
  TCanvas *doek = new TCanvas("doek","Observable", 900, 800);
	doek->cd(1);
	doek->SetLeftMargin(0.2);
	doek->SetBottomMargin(0.15);
  ObsFrame->Draw();
  doek->SaveAs("Tau_Difference_"+sample+".pdf");

  // *** Results ***
  std::cout << "*** RESULTS: FIT ***" << std::endl;
  fitgauss->Print();
  std::cout << "*** RESULTS: AVERAGES ***" << std::endl;
  std::cout << data->mean(*tauDiff) << std::endl;
  std::cout << data->sigma(*tauDiff) << std::endl;
}
